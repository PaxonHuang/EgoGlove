#include "lsm6dsv16x.h"

int16_t lsm6dsv16x_decode_i16(const uint8_t raw[2]) {
    return (int16_t)((uint16_t)raw[0] | ((uint16_t)raw[1] << 8));
}

float lsm6dsv16x_accel_scale(uint8_t fs_xl_bits) {
    switch (fs_xl_bits & 0x03u) {
        case 0x00u: return 0.061f;   /* ±2g  */
        case 0x01u: return 0.122f;   /* ±4g  */
        case 0x02u: return 0.244f;   /* ±8g  */
        default:    return 0.488f;   /* ±16g */
    }
}

float lsm6dsv16x_gyro_scale(uint8_t fs_g_bits) {
    switch (fs_g_bits & 0x0Fu) {
        case 0x00u: return 4.375f;   /* ±125  */
        case 0x01u: return 8.75f;    /* ±250  */
        case 0x02u: return 17.50f;   /* ±500  */
        case 0x03u: return 35.0f;    /* ±1000 */
        case 0x04u: return 70.0f;    /* ±2000 */
        default:    return 140.0f;   /* ±4000 */
    }
}

static bool reg_write(lsm6dsv16x_t *imu, uint8_t reg, uint8_t val) {
    return imu->t.write(reg, &val, 1, imu->ctx);
}

bool lsm6dsv16x_init(lsm6dsv16x_t *imu) {
    if (!imu || !imu->t.write || !imu->t.read) return false;

    uint8_t who = 0;
    if (!imu->t.read(LSM6DSV16X_REG_WHO_AM_I, &who, 1, imu->ctx)) return false;
    if (who != LSM6DSV16X_WHO_AM_I_VALUE) return false;

    if (!reg_write(imu, LSM6DSV16X_REG_CTRL3, LSM6DSV16X_CTRL3_DEFAULT)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL2_G, LSM6DSV16X_CTRL2_120HZ)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL6_G, LSM6DSV16X_CTRL6_2000DPS)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL1_XL, LSM6DSV16X_CTRL1_120HZ)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL8_XL, LSM6DSV16X_CTRL8_4G)) return false;

    imu->accel_mg_per_lsb   = lsm6dsv16x_accel_scale(LSM6DSV16X_FS_XL_4G);
    imu->gyro_mdps_per_lsb  = lsm6dsv16x_gyro_scale(LSM6DSV16X_FS_G_2000DPS);
    imu->ok = true;
    return true;
}

bool lsm6dsv16x_read(lsm6dsv16x_t *imu, float acc[3], float gyro[3]) {
    if (!imu || !imu->ok) return false;

    uint8_t status = 0;
    if (!imu->t.read(LSM6DSV16X_REG_STATUS_REG, &status, 1, imu->ctx)) return false;
    if ((status & (LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA))
        != (LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA)) return false;

    uint8_t g_raw[6], a_raw[6];
    if (!imu->t.read(LSM6DSV16X_REG_OUTX_L_G, g_raw, 6, imu->ctx)) return false;
    if (!imu->t.read(LSM6DSV16X_REG_OUTX_L_A, a_raw, 6, imu->ctx)) return false;

    gyro[0] = (float)lsm6dsv16x_decode_i16(&g_raw[0]) * imu->gyro_mdps_per_lsb * 0.001f;
    gyro[1] = (float)lsm6dsv16x_decode_i16(&g_raw[2]) * imu->gyro_mdps_per_lsb * 0.001f;
    gyro[2] = (float)lsm6dsv16x_decode_i16(&g_raw[4]) * imu->gyro_mdps_per_lsb * 0.001f;

    acc[0] = (float)lsm6dsv16x_decode_i16(&a_raw[0]) * imu->accel_mg_per_lsb * 0.001f;
    acc[1] = (float)lsm6dsv16x_decode_i16(&a_raw[2]) * imu->accel_mg_per_lsb * 0.001f;
    acc[2] = (float)lsm6dsv16x_decode_i16(&a_raw[4]) * imu->accel_mg_per_lsb * 0.001f;
    return true;
}
