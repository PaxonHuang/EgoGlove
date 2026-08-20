#include "demo1_imu_acq.h"

#include <string.h>
#include "esp_timer.h"
#include "esp_log.h"

static const char *TAG = "demo1_imu_acq";

/* ---- LSM6DSV16X registers/values for the 200Hz (HAODR) config ----
 * Datasheet (docs/datasheet/lsm6dsv16x.md): §6.5, Table 20, CTRL1/CTRL2, HAODR_CFG.
 *  - HAODR mode is enabled by OP_MODE = 001 in CTRL1/CTRL2 and must be enabled
 *    while the device is in power-down.
 *  - With HAODR_SEL_[1:0] = 10 and ODR code 0111, both XL and G run at 200 Hz.
 *  - HAODR_CFG (62h): bit7 = HAODR_EN, bits[3:2] = HAODR_SEL_[1:0].
 */
#define LSM_CTRL1_HAODR_200HZ 0x17u   /* OP_MODE_XL=001, ODR_XL=0111 */
#define LSM_CTRL2_HAODR_200HZ 0x17u   /* OP_MODE_G =001, ODR_G =0111 */
#define LSM_POWER_DOWN         0x00u
#define LSM_HAODR_CFG_VALUE    0x88u  /* HAODR_EN | (HAODR_SEL=10 << 2) */
#define LSM_HAODR_CFG_REG      0x62u

#define LSM_STATUS_REG_SNAPSHOT   /* status read happens via driver constant */

static bool acq_write_reg(demo1_imu_t *d, uint8_t reg, uint8_t val)
{
    return d->t.write(reg, &val, 1, d->ctx);
}

bool demo1_imu_apply_odr_200hz(demo1_imu_t *d)
{
    /* Power-down both sensors first (required to change HAODR). */
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL1_XL, LSM_POWER_DOWN)) return false;
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL2_G,  LSM_POWER_DOWN)) return false;

    /* Enable HAODR + select 200Hz table (HAODR_SEL = 10). */
    if (!acq_write_reg(d, LSM_HAODR_CFG_REG, LSM_HAODR_CFG_VALUE)) return false;

    /* Bring both sensors up in high-accuracy ODR mode at ODR = 0111 (200 Hz). */
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL1_XL, LSM_CTRL1_HAODR_200HZ)) return false;
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL2_G,  LSM_CTRL2_HAODR_200HZ)) return false;

    /* Re-assert BDU + full-scale settings (unchanged by the ODR switch). */
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL3,    LSM6DSV16X_CTRL3_DEFAULT)) return false;
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL6_G,  LSM6DSV16X_CTRL6_2000DPS)) return false;
    if (!acq_write_reg(d, LSM6DSV16X_REG_CTRL8_XL, LSM6DSV16X_CTRL8_4G))      return false;

    /* Read back HAODR_CFG to confirm the write landed. */
    uint8_t back = 0;
    if (!d->t.read(LSM_HAODR_CFG_REG, &back, 1, d->ctx)) return false;
    if (back != LSM_HAODR_CFG_VALUE) {
        ESP_LOGW(TAG, "HAODR_CFG readback 0x%02X != expected 0x%02X", back,
                 LSM_HAODR_CFG_VALUE);
        return false;
    }

    d->odr_200hz_cfg = true;
    ESP_LOGI(TAG, "200Hz config applied (HAODR HAODR_SEL=10, ODR=0111) — datasheet-derived, NOT HW-verified");
    return true;
}

bool demo1_imu_init(demo1_imu_t *d, imu_transport_t *t, void *ctx,
                    uint32_t sensor_id)
{
    if (!d || !t || !t->read || !t->write || !ctx) return false;

    memset(d, 0, sizeof(*d));
    d->t = *t;
    d->ctx = ctx;
    d->sensor_id = sensor_id;

    d->imu.t = *t;
    d->imu.ctx = ctx;

    if (!lsm6dsv16x_init(&d->imu)) {
        ESP_LOGE(TAG, "lsm6dsv16x_init failed (WHO_AM_I / register config)");
        return false;
    }
    d->initialized = true;

    /* Apply the datasheet-derived 200Hz config. Failure here is non-fatal for
     * the acquisition path (sensor remains at the init 120Hz baseline) but is
     * logged so 200Hz is never silently assumed. */
    if (!demo1_imu_apply_odr_200hz(d)) {
        ESP_LOGW(TAG, "200Hz (HAODR) config FAILED -> staying at init 120Hz baseline");
    }

    ESP_LOGI(TAG, "imu init OK: sensor_id=%lu", (unsigned long)sensor_id);
    return true;
}

bool demo1_imu_read_raw(demo1_imu_t *d, demo1_imu_sample_t *out)
{
    if (!d || !out || !d->initialized) return false;

    memset(out, 0, sizeof(*out));

    /* Wait until both accel and gyro data are available. */
    uint8_t status = 0;
    int spins = 0;
    do {
        if (!d->t.read(LSM6DSV16X_REG_STATUS_REG, &status, 1, d->ctx)) {
            out->quality_flags = DEMO1_Q_I2C_READ_FAIL;
            return false;
        }
        if ((status & (LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA))
            == (LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA)) break;
        /* ~1ms per spin; give the ODR several periods to produce data. */
        if (++spins > 50) {
            out->quality_flags = DEMO1_Q_STATUS_NOT_READY;
            out->status_reg = status;
            return false;
        }
    } while (1);

    out->sensor_id     = d->sensor_id;
    out->seq           = ++d->seq;
    out->status_reg    = status;
    out->timestamp_us  = (int64_t)esp_timer_get_time();

    /* Raw ADC reads (little-endian int16, as decoded by the driver). */
    if (!d->t.read(LSM6DSV16X_REG_OUTX_L_G, out->gyro_raw, 6, d->ctx)) {
        out->quality_flags = DEMO1_Q_I2C_READ_FAIL;
        return false;
    }
    if (!d->t.read(LSM6DSV16X_REG_OUTX_L_A, out->acc_raw, 6, d->ctx)) {
        out->quality_flags = DEMO1_Q_I2C_READ_FAIL;
        return false;
    }

    out->quality_flags = DEMO1_Q_OK;
    return true;
}

bool demo1_imu_recover(demo1_imu_t *d)
{
    if (!d) return false;
    ESP_LOGW(TAG, "attempting acquisition recovery (re-init)");
    bool ok = lsm6dsv16x_init(&d->imu);
    if (ok) {
        demo1_imu_apply_odr_200hz(d); /* best-effort re-apply; failure logged inside */
        d->initialized = true;
    }
    return ok;
}
