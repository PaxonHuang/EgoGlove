/*
 * demo1_config.h — Demo1 Phase 1B single-sensor config (ESP32-S3).
 *
 * Hardware baseline (unchanged, ADR-002): ESP32-S3 + LSM6DSV16X over I2C.
 * Phase 1B validates a single LSM6DSV16X only — not the 11-IMU array.
 *
 * Pins below are the Phase 1B default I2C bus (SDA/SCL). If a PCB pinmap for
 * the single-IMU test node exists, update these to match; otherwise they are
 * the documented default for a breakout build. NOT hardware-verified.
 *
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#ifndef EGO_DEMO1_CONFIG_H
#define EGO_DEMO1_CONFIG_H

/* ESP32-S3 I2C bus pins (default for Phase 1B single-IMU test node) */
#define DEMO1_I2C_SDA_GPIO     8u
#define DEMO1_I2C_SCL_GPIO     9u

/* I2C clock: 400 kHz (fast mode, matches LSM6DSV16X / HKVT datasheets) */
#define DEMO1_I2C_FREQ_HZ      400000u

/* LSM6DSV16X default 7-bit I2C address (SA0=0 -> 0x6A) */
#define DEMO1_IMU_I2C_ADDR7    0x6Au

/* Target ODR for Phase 1B (200 Hz). See demo1_imu_acq.h for the HAODR path. */
#define DEMO1_TARGET_ODR_HZ    200u

/* sensor_id for the Phase 1B single sensor (0 based on Demo1 wrist/finger
 * ordering; the 11-IMU Phase 1C will extend this to a stable scheme). */
#define DEMO1_IMU_SENSOR_ID    0u

#endif /* EGO_DEMO1_CONFIG_H */
