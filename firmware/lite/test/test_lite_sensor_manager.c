#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lite_sensor_manager.h"
#include "lsm6dsv16x.h"

typedef struct {
    uint8_t who_am_i;
    uint8_t status;
    uint8_t g_raw[6];
    uint8_t a_raw[6];
    int     n_reads;
} stub_t;

static bool stub_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx) {
    (void)reg; (void)data; (void)len; (void)ctx;
    return true;
}
static bool stub_read(uint8_t reg, uint8_t *data, uint8_t len, void *ctx) {
    (void)len;
    stub_t *s = (stub_t*)ctx;
    if (reg == LSM6DSV16X_REG_WHO_AM_I) { data[0] = s->who_am_i; return true; }
    if (reg == LSM6DSV16X_REG_STATUS_REG) { data[0] = s->status; return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_G) { memcpy(data, s->g_raw, 6); s->n_reads++; return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_A) { memcpy(data, s->a_raw, 6); return true; }
    return false;
}

static void set_gravity_z_up(stub_t *s) {
    /* 静止: acc = +1g (z), gyro = 0 */
    memset(s->g_raw, 0, 6);
    memset(s->a_raw, 0, 6);
    s->status = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
    int16_t z = (int16_t)(1.0f / (0.122f * 0.001f));   /* ~8197 LSB = 1g @ ±4g */
    s->a_raw[4] = (uint8_t)(z & 0xFF);
    s->a_raw[5] = (uint8_t)((z >> 8) & 0xFF);
}

static bool flex_half(float out[5], void *ctx) {
    (void)ctx;
    for (int i = 0; i < 5; i++) out[i] = 0.5f;
    return true;
}
static bool flex_fail(float out[5], void *ctx) {
    (void)out; (void)ctx;
    return false;
}

static void test_init_sets_fields(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_RIGHT, 3,
                        0.5f, flex_half, NULL, t, &s));
    assert(m.started);
    assert(m.hand == HAND_TOKEN_HAND_RIGHT);
    assert(m.serial == 3);
}

static void test_update_fills_token(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_LEFT, 1,
                        0.5f, flex_half, NULL, t, &s));

    hand_token_t tok;
    assert(lite_sm_update(&m, 100000, &tok));        /* t=0.1s */
    assert(lite_sm_update(&m, 200000, &tok));        /* t=0.2s */
    assert(lite_sm_update(&m, 300000, &tok));        /* t=0.3s */

    assert(tok.product == HAND_TOKEN_PRODUCT_LITE);
    assert(tok.hand == HAND_TOKEN_HAND_LEFT);
    assert(tok.serial == 1);
    assert(tok.timestamp_us == 300000);
    for (int i = 0; i < 5; i++) assert(tok.flex[i] == 0.5f);
    /* 静止重力 → 身份四元数 (w→1, tilt 很小) */
    assert(tok.quat[0] > 0.99f);
    assert(fabsf(tok.quat[1]) < 1e-2f);
    assert(fabsf(tok.quat[2]) < 1e-2f);
    /* acc 归一 1g (z) */
    assert(fabsf(tok.acc[2] - 1.0f) < 0.01f);
    assert(tok.acc[0] == 0.0f && tok.acc[1] == 0.0f);
}

static void test_flex_failure_leaves_zero(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_LEFT, 0,
                        0.5f, flex_fail, NULL, t, &s));
    hand_token_t tok;
    assert(lite_sm_update(&m, 100000, &tok));
    for (int i = 0; i < 5; i++) assert(tok.flex[i] == 0.0f);
}

static void test_no_new_data_returns_false(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    s.status = 0x00;                                   /* DRDY 未就绪 */
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_LEFT, 0,
                        0.5f, flex_half, NULL, t, &s));
    hand_token_t tok;
    memset(&tok, 0xAA, sizeof(tok));
    assert(!lite_sm_update(&m, 100000, &tok));
}

static void test_euler_identity(void) {
    float q[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float d[3];
    lite_sm_euler_deg(q, d);
    assert(fabsf(d[0]) < 1e-3f && fabsf(d[1]) < 1e-3f && fabsf(d[2]) < 1e-3f);

    /* 绕 x 转 90°: roll ≈ 90° */
    float q90[4] = { 0.70710678f, 0.70710678f, 0.0f, 0.0f };
    lite_sm_euler_deg(q90, d);
    assert(fabsf(d[0] - 90.0f) < 0.5f);
}

static void test_gyro_deg_to_rad_integration(void) {
    /* Regression lock for the deg/s→rad/s fix (commit 2e9c585): drives NON-ZERO
       gyro through lite_sm_update. gyro x = 1000 LSB @ 70 mdps/LSB = 70 dps;
       a_raw = 0 → Madgwick's a≠0 guard DISABLES accel feedback → pure gyro
       integration. 100 × 10 ms = 1.0 s at 70 dps → 70° about x → q =
       (cos 35°, sin 35°, 0, 0) = (0.8192, 0.5736, 0, 0). Without the deg→rad
       fix the gyro is 57.3× too fast (~4000° wrap) and these asserts fail. */
    stub_t s; memset(&s, 0, sizeof(s));
    s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE;
    s.status   = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
    s.g_raw[0] = 0xE8; s.g_raw[1] = 0x03;      /* +1000 LSB gyro x */
    /* a_raw stays all-zeros (memset above) — accel feedback disabled */

    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_RIGHT, 2,
                        0.5f, flex_half, NULL, t, &s));

    hand_token_t tok;
    uint32_t t_us = 100000;                     /* seed: dt=0 (m->last_us==0) */
    for (int i = 0; i < 100; i++) {
        t_us += 10000;                          /* +10 ms = dt 0.01 s */
        assert(lite_sm_update(&m, t_us, &tok));
    }
    assert(fabsf(tok.quat[0] - 0.8192f) < 0.05f);
    assert(fabsf(tok.quat[1] - 0.5736f) < 0.05f);
    assert(fabsf(tok.quat[2]) < 0.05f);
    assert(fabsf(tok.quat[3]) < 0.05f);
}

int main(void) {
    test_init_sets_fields();
    test_update_fills_token();
    test_flex_failure_leaves_zero();
    test_no_new_data_returns_false();
    test_euler_identity();
    test_gyro_deg_to_rad_integration();
    printf("LITE_SENSOR_MANAGER: all tests PASS\n");
    return 0;
}
