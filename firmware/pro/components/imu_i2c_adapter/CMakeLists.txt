idf_component_register(SRCS "imu_i2c_adapter.c"
                       INCLUDE_DIRS "include"
                       REQUIRES esp_driver_i2c lsm6dsv16x)
