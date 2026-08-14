#ifndef ECHOGLOVE_LITE_SENSOR_MANAGER_H
#define ECHOGLOVE_LITE_SENSOR_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include "lsm6dsv16x.h"
#include "madgwick.h"
#include "hand_token.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 归一化指尖弯折 0..1 (拇->小), 由板级 ADC 读取器注入 */
typedef bool (*lite_flex_read_fn)(float out[5], void *ctx);

typedef struct {
    lsm6dsv16x_t    imu;
    madgwick_t      filter;
    uint8_t         product;      /* HAND_TOKEN_PRODUCT_LITE */
    uint8_t         hand;         /* HAND_TOKEN_HAND_LEFT/RIGHT */
    uint8_t         serial;
    uint32_t        last_us;
    bool            started;
    lite_flex_read_fn flex_read;
    void            *flex_ctx;
} lite_sensor_manager_t;

/* 初始化: 注入 flex 读取器 + 启动 IMU + 复位滤波 */
bool lite_sm_init(lite_sensor_manager_t *m, uint8_t product, uint8_t hand,
                  uint8_t serial, float beta,
                  lite_flex_read_fn flex_read, void *flex_ctx,
                  imu_transport_t transport, void *imu_ctx);

/*
 * 单步采样 + 融合, 填充 out。
 * dt 由 timestamp_us 差分计算 (首帧 dt=0)。flex 缺失时置 0。
 * 返回 true; IMU 无新数据时返回 false (out 不更新)。
 */
bool lite_sm_update(lite_sensor_manager_t *m, uint32_t timestamp_us,
                    hand_token_t *out);

/* 调试用: quat → roll/pitch/yaw (度, ZYX)。Lite 遥测串口打印。 */
void lite_sm_euler_deg(const float quat[4], float out_deg[3]);

#ifdef __cplusplus
}
#endif
#endif
