#ifndef ECHOGLOVE_LSM6DSV16X_H
#define ECHOGLOVE_LSM6DSV16X_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LSM6DSV16X_I2C_ADDR        0x6Au

#define LSM6DSV16X_REG_WHO_AM_I    0x0Fu
#define LSM6DSV16X_WHO_AM_I_VALUE  0x70u
#define LSM6DSV16X_REG_CTRL1_XL    0x10u
#define LSM6DSV16X_REG_CTRL2_G     0x11u
#define LSM6DSV16X_REG_CTRL3       0x12u
#define LSM6DSV16X_REG_CTRL6_G     0x15u
#define LSM6DSV16X_REG_CTRL8_XL    0x17u
#define LSM6DSV16X_REG_STATUS_REG  0x1Eu
#define LSM6DSV16X_REG_OUTX_L_G    0x22u
#define LSM6DSV16X_REG_OUTX_L_A    0x28u

/* CTRL1(10h): [7]=0 OP_MODE_XL[6:4] ODR_XL[3:0]; ODR 120Hz=0110, HP=000 */
#define LSM6DSV16X_OPMODE_XL_HP    0x00u
#define LSM6DSV16X_ODR_120HZ       0x06u
#define LSM6DSV16X_CTRL1_120HZ     ((LSM6DSV16X_OPMODE_XL_HP << 4) | LSM6DSV16X_ODR_120HZ)

/* CTRL2(11h): [7]=0 OP_MODE_G[6:4] ODR_G[3:0] */
#define LSM6DSV16X_OPMODE_G_HP     0x00u
#define LSM6DSV16X_CTRL2_120HZ     ((LSM6DSV16X_OPMODE_G_HP << 4) | LSM6DSV16X_ODR_120HZ)

/* CTRL3(12h): BDU[6] IF_INC[2] (chip default 0x44; explicit for determinism) */
#define LSM6DSV16X_CTRL3_DEFAULT   0x44u

/* CTRL6(15h): [7]=0 LPF1_G_BW[6:4] FS_G[3:0]; FS_G=0100 → ±2000dps */
#define LSM6DSV16X_FS_G_2000DPS    0x04u
#define LSM6DSV16X_CTRL6_2000DPS   LSM6DSV16X_FS_G_2000DPS

/* CTRL8(17h): HP_LPF2_XL_BW[7:5] [4]=0 XL_DualC_EN[3] [2]=0 FS_XL[1:0]; FS_XL=01 → ±4g */
#define LSM6DSV16X_FS_XL_4G        0x01u
#define LSM6DSV16X_CTRL8_4G        LSM6DSV16X_FS_XL_4G

/* STATUS_REG(1Eh): bit1 GDA, bit0 XLDA */
#define LSM6DSV16X_STAT_XLDA       0x01u
#define LSM6DSV16X_STAT_GDA        0x02u

typedef struct {
    bool (*write)(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx);
    bool (*read)(uint8_t reg, uint8_t *data, uint8_t len, void *ctx);
} imu_transport_t;

typedef struct {
    imu_transport_t t;
    void           *ctx;
    bool            ok;
    float           accel_mg_per_lsb;
    float           gyro_mdps_per_lsb;
} lsm6dsv16x_t;

bool lsm6dsv16x_init(lsm6dsv16x_t *imu);
bool lsm6dsv16x_read(lsm6dsv16x_t *imu, float acc[3], float gyro[3]);

int16_t lsm6dsv16x_decode_i16(const uint8_t raw[2]);  /* 小端 */
float   lsm6dsv16x_accel_scale(uint8_t fs_xl_bits);   /* mg/LSB */
float   lsm6dsv16x_gyro_scale(uint8_t fs_g_bits);     /* mdps/LSB */

#ifdef __cplusplus
}
#endif
#endif
