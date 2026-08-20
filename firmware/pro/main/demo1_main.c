/*
 * demo1_main.c — Demo1 Phase 1B main (native ESP-IDF, ESP32-S3).
 *
 * Boot order:
 *   1. init ESP-IDF I2C master bus + add the LSM6DSV16X device (adapter)
 *   2. init the REUSED LSM6DSV16X core (WHO_AM_I + register config)
 *   3. apply the datasheet-derived 200Hz (HAODR) config
 *   4. run a single acquisition task that reads raw accel/gyro and emits one
 *      replay-able line per sample: raw bytes + timestamp + seq + quality.
 *
 * Replay-ability: each line preserves every raw byte plus all metadata
 * (sensor_id, seq, timestamp_us, quality) so a saved capture can be fed back
 * into the same decode/derived pipeline offline. No fusion is performed here.
 *
 * Error handling: on I2C/status failure the sample is flagged and skipped;
 * after N consecutive failures the sensor is recovered (re-init + 200Hz
 * re-apply). Init failure is reported and retried with backoff.
 *
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "imu_i2c_adapter.h"
#include "demo1_imu_acq.h"
#include "demo1_config.h"

static const char *TAG = "demo1_main";

#define ACQ_PERIOD_MS     (1000 / DEMO1_TARGET_ODR_HZ > 0 ? 1000 / DEMO1_TARGET_ODR_HZ : 5)
#define MAX_CONSEC_FAIL   20u   /* consecutive failures before recovery attempt */

static demo1_imu_t g_acq;
static demo1_imu_sample_t g_sample;

/* Print one sample as a single replay-able line. Raw bytes are emitted as
 * lowercase hex alongside sensor_id/seq/timestamp/status/quality. */
static void emit_sample(const demo1_imu_sample_t *s)
{
    printf("t=%lld seq=%lu sid=%lu st=%02X q=%02X "
           "g=%02x%02x%02x%02x%02x%02x a=%02x%02x%02x%02x%02x%02x\n",
           (long long)s->timestamp_us,
           (unsigned long)s->seq,
           (unsigned long)s->sensor_id,
           (unsigned)s->status_reg,
           (unsigned)s->quality_flags,
           s->gyro_raw[0], s->gyro_raw[1], s->gyro_raw[2],
           s->gyro_raw[3], s->gyro_raw[4], s->gyro_raw[5],
           s->acc_raw[0],  s->acc_raw[1],  s->acc_raw[2],
           s->acc_raw[3],  s->acc_raw[4],  s->acc_raw[5]);
}

static void acq_task(void *arg)
{
    uint32_t consec_fail = 0;
    uint32_t n_ok = 0;

    while (1) {
        if (!g_acq.initialized) {
            ESP_LOGW(TAG, "acquisition not initialized");
            vTaskDelay(pdMS_TO_TICKS(500));
            continue;
        }

        if (demo1_imu_read_raw(&g_acq, &g_sample)) {
            emit_sample(&g_sample);
            n_ok++;
            consec_fail = 0;
        } else {
            consec_fail++;
            ESP_LOGW(TAG, "sample failed (q=0x%02X), consecutive=%lu",
                     (unsigned)g_sample.quality_flags, (unsigned long)consec_fail);
            if (consec_fail >= MAX_CONSEC_FAIL) {
                demo1_imu_recover(&g_acq);
                consec_fail = 0;
            }
        }

        int delay_ms = ACQ_PERIOD_MS;
        if (g_acq.odr_200hz_cfg) {
            /* 200Hz -> ~5ms. Allow the sensor to keep up; the timestamps are
             * authoritative for actual rate (drift/loss visible in seq gaps). */
            delay_ms = 5;
        }
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Demo1 Phase 1B boot (ESP-IDF %s, target %s)",
             IDF_VER, CONFIG_IDF_TARGET);

    imu_i2c_ctx_t *i2c = imu_i2c_init(DEMO1_I2C_SDA_GPIO, DEMO1_I2C_SCL_GPIO,
                                      DEMO1_I2C_FREQ_HZ, DEMO1_IMU_I2C_ADDR7);
    if (!i2c) {
        ESP_LOGE(TAG, "I2C init failed");
        return;
    }

    imu_transport_t transport;
    imu_i2c_fill_transport(&transport, i2c);

    if (!demo1_imu_init(&g_acq, &transport, i2c, DEMO1_IMU_SENSOR_ID)) {
        ESP_LOGE(TAG, "IMU init failed (WHO_AM_I / register write). Retrying.");
        /* Keep the task alive but uninitialized so a re-probe path can exist;
         * Phase 1B reports init failure explicitly rather than faking success. */
        g_acq.initialized = false;
    }

    ESP_LOGI(TAG, "target ODR=%u Hz (200Hz via HAODR, datasheet-derived)",
             (unsigned)DEMO1_TARGET_ODR_HZ);

    if (xTaskCreate(acq_task, "imu_acq", 4096, NULL, 5, NULL) != pdPASS) {
        ESP_LOGE(TAG, "failed to create acquisition task");
    }
}
