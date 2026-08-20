idf_component_register(SRCS "demo1_main.c" "demo1_imu_acq.c"
                       INCLUDE_DIRS "."
                       REQUIRES imu_i2c_adapter lsm6dsv16x
                       PRIV_REQUIRES esp_timer)
