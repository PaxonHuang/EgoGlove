/*
 * imu_i2c_adapter.h — ESP-IDF I2C transport adapter for the LSM6DSV16X
 * (and any other sensor exposing an imu_transport_t).
 *
 * Implements the HAL-decoupled `imu_transport_t` contract (write/read) that
 * firmware/lite/lib/LSM6DSV16X expects, using ESP-IDF's i2c_master API
 * (ESP-IDF v6.0).
 *
 * Reuse intent: the verified LSM6DSV16X core (lsm6dsv16x.{h,c}) is untouched;
 * this adapter is the ONLY ESP-IDF-specific piece needed to run that core on
 * ESP32-S3 under native ESP-IDF. Same pattern as the planned HKVT-M3A
 * esp-idf_i2c_adapter.
 *
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#ifndef EGO_DEMO1_IMU_I2C_ADAPTER_H
#define EGO_DEMO1_IMU_I2C_ADAPTER_H

#include <stdint.h>
#include <stdbool.h>
#include "driver/i2c_master.h"
#include "lsm6dsv16x.h"   /* for imu_transport_t */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t dev;
    uint8_t                 addr7;   /* 7-bit I2C address (0x6A default) */
} imu_i2c_ctx_t;

/* Configure + init the ESP32-S3 I2C master bus and add the sensor device.
 * sda/scl are GPIO numbers. Returns the ctx (heap-allocated) on success. */
imu_i2c_ctx_t *imu_i2c_init(int sda_gpio, int scl_gpio, uint32_t freq_hz,
                            uint8_t addr7);

/* Fill an imu_transport_t that drives the given ctx. Must outlive use. */
void imu_i2c_fill_transport(imu_transport_t *t, imu_i2c_ctx_t *ctx);

#ifdef __cplusplus
}
#endif
#endif /* EGO_DEMO1_IMU_I2C_ADAPTER_H */
