/*
 * demo1_imu_acq.h — Demo1 Phase 1B: single-sensor LSM6DSV16X acquisition.
 *
 * Goal: a real, minimal, repeatable single-sensor acquisition path on
 * ESP32-S3 under native ESP-IDF — reliable WHO_AM_I + register config,
 * raw accel/gyro capture through the ESP-IDF I2C adapter, with an explicit
 * timestamp + sequence + raw sample + quality/error state, plus init-failure,
 * I2C-read-failure and recovery handling.
 *
 * Raw / Derived / Metadata discipline (kept from the Phase 1A HKVT driver):
 *   - raw  : the 12 decoded-ADC bytes from the sensor (identified & preservable)
 *   - derived: calibrated/fused physical quantities (out of scope for hot loop)
 *   - metadata: sensor_id, seq, timestamp_us, quality_flags, status
 *
 * ODR note (datasheet-authoritative, from docs/datasheet/lsm6dsv16x.md §6.5):
 *   The LSM6DSV16X has NO native 200 Hz ODR in high-performance mode
 *   (closest is 240 Hz). Exact 200 Hz is reachable ONLY via High-Accuracy ODR
 *   (HAODR) mode with HAODR_SEL_[1:0]=10 and ODR code 0111. That path is
 *   DATASHEET-DERIVED and NOT HARDWARE-VERIFIED in this environment — it is
 *   applied as an explicit 200 Hz config step and must be validated on real
 *   hardware before 200 Hz is treated as achieved.
 *
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#ifndef EGO_DEMO1_IMU_ACQ_H
#define EGO_DEMO1_IMU_ACQ_H

#include <stdint.h>
#include <stdbool.h>
#include "lsm6dsv16x.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Quality/error flags (bitmask, 0 = ok) */
enum {
    DEMO1_Q_OK                 = 0x00,
    DEMO1_Q_I2C_READ_FAIL      = 0x01,  /* transport read returned false */
    DEMO1_Q_STATUS_NOT_READY   = 0x02,  /* XLDA/GDA not both set before timeout */
    DEMO1_Q_RECOVERED          = 0x04,  /* a recovery re-init happened */
    DEMO1_Q_NOT_INIT           = 0x80,  /* acquisition running without init */
};

/* One raw sample (raw + metadata; derived kept separate/offline) */
typedef struct {
    uint32_t sensor_id;          /* metadata: which sensor (0 in Phase 1B single) */
    uint32_t seq;                /* metadata: per-sensor monotonically increasing */
    int64_t  timestamp_us;       /* metadata: MCU free-running clock (esp_timer) */
    uint8_t  status_reg;         /* metadata: STATUS_REG snapshot at read time */
    uint8_t  acc_raw[6];         /* raw little-endian ADC: X_L,X_H,Y_L,Y_H,Z_L,Z_H */
    uint8_t  gyro_raw[6];        /* raw little-endian ADC: X_L,X_H,Y_L,Y_H,Z_L,Z_H */
    uint8_t  quality_flags;      /* metadata: 0=ok (see DEMO1_Q_*) */
} demo1_imu_sample_t;

/* Acquisition handle */
typedef struct {
    lsm6dsv16x_t   imu;          /* reused, M2-verified core */
    imu_transport_t t;           /* ESP-IDF I2C adapter transport */
    void          *ctx;          /* adapter context */
    uint32_t       sensor_id;
    uint32_t       seq;
    bool           initialized;
    bool           odr_200hz_cfg;  /* true after HAODR 200Hz config applied */
} demo1_imu_t;

/* Init transport + driver (WHO_AM_I, register config), then apply the
 * documented 200Hz (HAODR) config. Returns true on success. */
bool demo1_imu_init(demo1_imu_t *d, imu_transport_t *t, void *ctx,
                    uint32_t sensor_id);

/* Apply the datasheet-derived 200 Hz (HAODR, HAODR_SEL=10, ODR=0111) config.
 * No-op safety: must be called while the sensors are in power-down.
 * Returns true if the write sequence completed. NOT hardware-verified. */
bool demo1_imu_apply_odr_200hz(demo1_imu_t *d);

/* Read one raw sample (raw + status + timestamp + seq + quality).
 * Returns false if the sensor could not produce a sample (caller may retry). */
bool demo1_imu_read_raw(demo1_imu_t *d, demo1_imu_sample_t *out);

/* Attempt recovery: re-init the driver (clears error state). */
bool demo1_imu_recover(demo1_imu_t *d);

#ifdef __cplusplus
}
#endif
#endif /* EGO_DEMO1_IMU_ACQ_H */
