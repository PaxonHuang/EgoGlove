#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lsm6dsv16x.h"

typedef struct {
    uint8_t who_am_i;
    uint8_t status;
    uint8_t g_raw[6];
    uint8_t a_raw[6];
    uint8_t written[8][2];
    int     n_written;
    int     n_status_polls;
} stub_t;

static bool stub_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx) {
    stub_t *s = (stub_t*)ctx;
    assert(len == 1);
    assert(s->n_written < 8);
    s->written[s->n_written][0] = reg;
    s->written[s->n_written][1] = data[0];
    s->n_written++;
    return true;
}

static bool stub_read(uint8_t reg, uint8_t *data, uint8_t len, void *ctx) {
    (void)len;
    stub_t *s = (stub_t*)ctx;
    if (reg == LSM6DSV16X_REG_WHO_AM_I) { data[0] = s->who_am_i; return true; }
    if (reg == LSM6DSV16X_REG_STATUS_REG) { data[0] = s->status; s->n_status_polls++; return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_G) { memcpy(data, s->g_raw, 6); return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_A) { memcpy(data, s->a_raw, 6); return true; }
    return false;
}

static void init_stub(stub_t *s) {
    memset(s, 0, sizeof(*s));
    s->who_am_i = LSM6DSV16X_WHO_AM_I_VALUE;
    s->status   = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
}

static void test_init_writes_expected_config(void) {
    stub_t s; init_stub(&s);
    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(lsm6dsv16x_init(&imu));

    static const uint8_t expect[5][2] = {
        { LSM6DSV16X_REG_CTRL3,   LSM6DSV16X_CTRL3_DEFAULT   },
        { LSM6DSV16X_REG_CTRL2_G, LSM6DSV16X_CTRL2_120HZ    },
        { LSM6DSV16X_REG_CTRL6_G, LSM6DSV16X_CTRL6_2000DPS  },
        { LSM6DSV16X_REG_CTRL1_XL,LSM6DSV16X_CTRL1_120HZ    },
        { LSM6DSV16X_REG_CTRL8_XL,LSM6DSV16X_CTRL8_4G       },
    };
    assert(s.n_written == 5);
    for (int i = 0; i < 5; i++) {
        assert(s.written[i][0] == expect[i][0]);
        assert(s.written[i][1] == expect[i][1]);
    }
    /* scales: ±4g → 0.122 mg/LSB, ±2000dps → 70 mdps/LSB */
    assert(imu.accel_mg_per_lsb == 0.122f);
    assert(imu.gyro_mdps_per_lsb == 70.0f);
}

static void test_init_rejects_bad_whoami(void) {
    stub_t s; init_stub(&s); s.who_am_i = 0x00;
    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(!lsm6dsv16x_init(&imu));
}

static void test_decode_i16_le(void) {
    const uint8_t a[2] = { 0x34, 0x12 };          /* 0x1234 = +4660 */
    const uint8_t b[2] = { 0x00, 0x80 };          /* 0x8000 = -32768 */
    const uint8_t c[2] = { 0x00, 0x00 };
    assert(lsm6dsv16x_decode_i16(a) == 0x1234);
    assert(lsm6dsv16x_decode_i16(b) == -32768);
    assert(lsm6dsv16x_decode_i16(c) == 0);
}

static void test_scale_constants(void) {
    assert(lsm6dsv16x_accel_scale(0x00) == 0.061f);
    assert(lsm6dsv16x_accel_scale(0x01) == 0.122f);
    assert(lsm6dsv16x_accel_scale(0x02) == 0.244f);
    assert(lsm6dsv16x_accel_scale(0x03) == 0.488f);
    assert(lsm6dsv16x_gyro_scale(0x04) == 70.0f);
    assert(lsm6dsv16x_gyro_scale(0x0C) == 140.0f);  /* ±4000 */
}

static void test_read_physical_units(void) {
    stub_t s; init_stub(&s);
    /* gyro raw 1000 LSB @ ±2000dps → 1000 * 70 mdps = 70.0 dps */
    s.g_raw[0] = 0xE8; s.g_raw[1] = 0x03;          /* 1000 LE */
    /* accel raw 0x2000 = 8192 LSB @ ±4g → 8192 * 0.122 mg = 0.9994 g */
    s.a_raw[1] = 0x20;                              /* (0x00,0x20) LE */

    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(lsm6dsv16x_init(&imu));
    float acc[3], gyro[3];
    assert(lsm6dsv16x_read(&imu, acc, gyro));
    assert(gyro[0] > 69.9f && gyro[0] < 70.1f);
    assert(acc[0] > 0.99f && acc[0] < 1.01f);
    assert(acc[1] == 0.0f && acc[2] == 0.0f);
    assert(gyro[1] == 0.0f && gyro[2] == 0.0f);
}

static void test_read_waits_for_drdy(void) {
    stub_t s; init_stub(&s);
    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(lsm6dsv16x_init(&imu));

    s.status = 0x00;                        /* no data ready yet */
    float acc[3], gyro[3];
    assert(!lsm6dsv16x_read(&imu, acc, gyro));
    assert(s.n_status_polls == 1);

    s.status = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
    assert(lsm6dsv16x_read(&imu, acc, gyro));   /* next poll succeeds */
    assert(s.n_status_polls == 2);
}

int main(void) {
    test_init_writes_expected_config();
    test_init_rejects_bad_whoami();
    test_decode_i16_le();
    test_scale_constants();
    test_read_physical_units();
    test_read_waits_for_drdy();
    printf("LSM6DSV16X: all tests PASS\n");
    return 0;
}
