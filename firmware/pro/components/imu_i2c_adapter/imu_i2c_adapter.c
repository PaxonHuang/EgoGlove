#include "imu_i2c_adapter.h"

#include <stdlib.h>
#include <string.h>
#include "esp_log.h"

static const char *TAG = "imu_i2c_adapter";

/* ---- imu_transport_t implementation (register-addressed I2C) ----
 * The LSM6DSV16X core calls:
 *   write(reg, data, len): transmit [reg, data...]
 *   read(reg, buf, len):   transmit reg, then (repeated-start) read len bytes
 * We map these onto i2c_master_transmit / i2c_master_transmit_receive.
 */
static bool t_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx)
{
    imu_i2c_ctx_t *c = (imu_i2c_ctx_t *)ctx;
    uint8_t frame[16];
    if ((size_t)(len + 1) > sizeof(frame)) return false;

    frame[0] = reg;
    if (len && data) memcpy(&frame[1], data, len);

    esp_err_t e = i2c_master_transmit(c->dev, frame, (size_t)len + 1, 100);
    if (e != ESP_OK) {
        ESP_LOGW(TAG, "i2c write reg=0x%02x len=%u failed: %s", reg, len,
                 esp_err_to_name(e));
        return false;
    }
    return true;
}

static bool t_read(uint8_t reg, uint8_t *buf, uint8_t len, void *ctx)
{
    imu_i2c_ctx_t *c = (imu_i2c_ctx_t *)ctx;
    esp_err_t e = i2c_master_transmit_receive(c->dev, &reg, 1, buf, len, 100);
    if (e != ESP_OK) {
        ESP_LOGW(TAG, "i2c read reg=0x%02x len=%u failed: %s", reg, len,
                 esp_err_to_name(e));
        return false;
    }
    return true;
}

void imu_i2c_fill_transport(imu_transport_t *t, imu_i2c_ctx_t *ctx)
{
    t->write = t_write;
    t->read  = t_read;
}

imu_i2c_ctx_t *imu_i2c_init(int sda_gpio, int scl_gpio, uint32_t freq_hz,
                            uint8_t addr7)
{
    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = sda_gpio,
        .scl_io_num = scl_gpio,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags = { .enable_internal_pullup = true },
    };

    i2c_master_bus_handle_t bus = NULL;
    esp_err_t e = i2c_new_master_bus(&bus_cfg, &bus);
    if (e != ESP_OK) {
        ESP_LOGE(TAG, "i2c_new_master_bus failed: %s", esp_err_to_name(e));
        return NULL;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = addr7,
        .scl_speed_hz = freq_hz,
    };
    i2c_master_dev_handle_t dev = NULL;
    e = i2c_master_bus_add_device(bus, &dev_cfg, &dev);
    if (e != ESP_OK) {
        ESP_LOGE(TAG, "i2c_master_bus_add_device failed: %s", esp_err_to_name(e));
        i2c_del_master_bus(bus);
        return NULL;
    }

    imu_i2c_ctx_t *ctx = calloc(1, sizeof(*ctx));
    if (!ctx) {
        i2c_master_bus_rm_device(dev);
        i2c_del_master_bus(bus);
        return NULL;
    }
    ctx->bus = bus;
    ctx->dev = dev;
    ctx->addr7 = addr7;

    ESP_LOGI(TAG, "I2C bus ready: SDA=%d SCL=%d @%luHz addr=0x%02X",
             sda_gpio, scl_gpio, (unsigned long)freq_hz, addr7);
    return ctx;
}
