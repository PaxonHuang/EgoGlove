#include "lite_sensor_manager.h"
#include <math.h>
#include <string.h>

bool lite_sm_init(lite_sensor_manager_t *m, uint8_t product, uint8_t hand,
                  uint8_t serial, float beta,
                  lite_flex_read_fn flex_read, void *flex_ctx,
                  imu_transport_t transport, void *imu_ctx) {
    if (!m) return false;
    memset(m, 0, sizeof(*m));
    m->product   = product;
    m->hand      = hand;
    m->serial    = serial;
    m->flex_read = flex_read;
    m->flex_ctx  = flex_ctx;
    m->imu.t = transport;
    m->imu.ctx = imu_ctx;
    if (!lsm6dsv16x_init(&m->imu)) return false;
    madgwick_init(&m->filter, beta);
    m->started = true;
    return true;
}

static void fill_identity(hand_token_t *out) {
    memset(out, 0, sizeof(*out));
    out->quat[0] = 1.0f;   /* w=1, x=y=z=0 */
}

bool lite_sm_update(lite_sensor_manager_t *m, uint32_t timestamp_us,
                    hand_token_t *out) {
    if (!m || !m->started || !out) return false;

    float acc[3], gyro[3];
    if (!lsm6dsv16x_read(&m->imu, acc, gyro)) return false;

    float dt = 0.0f;
    if (m->last_us != 0) {
        uint32_t du = timestamp_us - m->last_us;   /* 单调回绕安全 */
        dt = (float)du * 1e-6f;
    }
    m->last_us = timestamp_us;

    /* gyro: deg/s (driver contract) → rad/s (Madgwick contract). 2026-08-11
       fix — without this, real-IMU gyro integration is 57.3x too fast (host
       tests use zero gyro, so cannot catch it). See Task 4 decision record. */
    const float deg2rad = 0.0174532925199433f;
    madgwick_update(&m->filter,
                    gyro[0]*deg2rad, gyro[1]*deg2rad, gyro[2]*deg2rad,
                    acc[0], acc[1], acc[2], dt);

    fill_identity(out);
    out->product = m->product;
    out->hand    = m->hand;
    out->serial  = m->serial;
    out->timestamp_us = timestamp_us;
    if (m->flex_read) m->flex_read(out->flex, m->flex_ctx);   /* 失败则留 0 */
    madgwick_get_quat(&m->filter, out->quat);
    memcpy(out->acc, acc, sizeof(acc));
    return true;
}

void lite_sm_euler_deg(const float q[4], float out_deg[3]) {
    float w = q[0], x = q[1], y = q[2], z = q[3];
    float roll  = atan2f(2.0f*(w*x + y*z), 1.0f - 2.0f*(x*x + y*y));
    float pitch = asinf(2.0f*(w*y - z*x));
    float yaw   = atan2f(2.0f*(w*z + x*y), 1.0f - 2.0f*(y*y + z*z));
    out_deg[0] = roll  * 180.0f / 3.14159265358979f;
    out_deg[1] = pitch * 180.0f / 3.14159265358979f;
    out_deg[2] = yaw   * 180.0f / 3.14159265358979f;
}
