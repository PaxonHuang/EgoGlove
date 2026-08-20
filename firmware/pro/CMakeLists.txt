# EgoGlove firmware/pro — Demo1 Phase 1B (native ESP-IDF, ESP32-S3)
# Single LSM6DSV16X reliable acquisition: WHO_AM_I, register config (200Hz
# target via HAODR per datasheet), accel/gyro raw read over an ESP-IDF I2C
# transport adapter, with MCU timestamp + seq + quality/error + recovery.

cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(egoglove_demo1_p1b)
