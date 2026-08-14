// EchoGlove Lite — M2: LSM6DSV16X(120Hz) + Madgwick → quat 进 Hand Token
// 串口遥测 (115200) 10Hz CSV: t=<us> flex=... euler=<roll,pitch,yaw> deg
#include <Arduino.h>
#include <Wire.h>
#include "lsm6dsv16x.h"
#include "madgwick.h"
#include "lite_sensor_manager.h"
#include "hand_token.h"

static lite_sensor_manager_t g_sm;
static volatile hand_token_t g_last;
static volatile bool          g_has_sample = false;

// ---- I2C transport over Arduino Wire (SDA=GPIO8, SCL=GPIO9, 400kHz) ----
static bool i2c_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx) {
    (void)ctx;
    Wire.beginTransmission((uint8_t)LSM6DSV16X_I2C_ADDR);
    Wire.write(reg);
    for (uint8_t i = 0; i < len; i++) Wire.write(data[i]);
    return Wire.endTransmission() == 0;
}
static bool i2c_read(uint8_t reg, uint8_t *data, uint8_t len, void *ctx) {
    (void)ctx;
    Wire.beginTransmission((uint8_t)LSM6DSV16X_I2C_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom((uint8_t)LSM6DSV16X_I2C_ADDR, (uint8_t)len) != len) return false;
    for (uint8_t i = 0; i < len; i++) data[i] = Wire.read();
    return true;
}

// ---- Flex via internal ADC1, GPIO1-5 (raw normalize 0..1; NVS calib = M4) ----
static const int kFlexPins[5] = {1, 2, 3, 4, 5};
static bool flex_read(float out[5], void *ctx) {
    (void)ctx;
    for (int i = 0; i < 5; i++) out[i] = (float)analogRead(kFlexPins[i]) / 4095.0f;
    return true;
}

// ---- 120Hz 采样 + Madgwick 融合 ----
static void taskSensorRead(void *arg) {
    (void)arg;
    for (;;) {
        hand_token_t tok;
        if (lite_sm_update(&g_sm, micros(), &tok)) {
            // TODO(M3): cross-core g_last snapshot is a formal data race (10Hz read vs 120Hz write); portENTER_CRITICAL copy or seqlock when M3 replaces this path.
            memcpy((void *)&g_last, &tok, sizeof(tok));   /* volatile struct → memcpy */
            g_has_sample = true;
        }
        vTaskDelay(pdMS_TO_TICKS(8));   /* ~120Hz loop; DRDY 门控实际工作 */
    }
}

// ---- 10Hz 串口遥测 (漂移/响应验证) ----
static void taskTelemetry(void *arg) {
    (void)arg;
    vTaskDelay(pdMS_TO_TICKS(2000));    /* 等 IMU 初始化 */
    for (;;) {
        if (g_has_sample) {
            hand_token_t t;
            // TODO(M3): cross-core g_last snapshot is a formal data race (10Hz read vs 120Hz write); portENTER_CRITICAL copy or seqlock when M3 replaces this path.
            memcpy(&t, (const void *)&g_last, sizeof(t)); /* 快照 (volatile → memcpy) */
            float e[3];
            lite_sm_euler_deg(t.quat, e);
            Serial.printf("t=%lu flex=%.3f,%.3f,%.3f,%.3f,%.3f euler=%.1f,%.1f,%.1f quat=%.3f,%.3f,%.3f,%.3f\n",
                          (unsigned long)t.timestamp_us,
                          t.flex[0], t.flex[1], t.flex[2], t.flex[3], t.flex[4],
                          e[0], e[1], e[2],
                          t.quat[0], t.quat[1], t.quat[2], t.quat[3]);
        }
        vTaskDelay(pdMS_TO_TICKS(100)); /* 10Hz */
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Wire.begin(8, 9, 400000);           /* SDA=GPIO8, SCL=GPIO9, 400kHz */
    imu_transport_t t = { i2c_write, i2c_read };
    if (!lite_sm_init(&g_sm, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_RIGHT, 0,
                      0.1f, flex_read, NULL, t, NULL)) {
        Serial.println("LITE SM INIT FAILED (check I2C wiring / WHO_AM_I)");
        while (1) vTaskDelay(pdMS_TO_TICKS(1000));
    }
    Serial.println("LITE SM INIT OK");
    xTaskCreatePinnedToCore(taskSensorRead, "SensorRead", 4096, NULL, 3, NULL, 1);
    xTaskCreatePinnedToCore(taskTelemetry, "Telemetry", 4096, NULL, 1, NULL, 0);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
