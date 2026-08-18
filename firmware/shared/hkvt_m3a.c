/*
 * hkvt_m3a.c — HKVT-M3A 驱动实现 (纯 C, protocol + 状态机 + 校准)
 *
 * 本文件不依赖任何 HAL; 硬件交互通过 hkvt_transport_t 注入。
 * host 单测注入 stub transport 即可完全脱离 ESP32。
 */
#include "hkvt_m3a.h"
#include <string.h>

/* ---- 纯逻辑层 ---- */

int16_t hkvt_decode_i16(const uint8_t raw[2]) {
    return (int16_t)((uint16_t)raw[0] | ((uint16_t)raw[1] << 8));
}

bool hkvt_parse_xyz(const uint8_t *buf, uint8_t len, hkvt_m3a_raw_t *out) {
    /* short-read 防御: 不足 6 字节拒绝, 不写入 out */
    if (!buf || !out || len < HKVT_FORCE_FRAME_BYTES) return false;
    out->force_x_raw = hkvt_decode_i16(&buf[0]);
    out->force_y_raw = hkvt_decode_i16(&buf[2]);
    out->force_z_raw = hkvt_decode_i16(&buf[4]);
    return true;
}

bool hkvt_validate_address(uint8_t addr7) {
    /* datasheet §3.3: 禁 0x00 / 0xFF;
     * I2C 7-bit 保留段 0x00-0x07 与 0x78-0x7F 均视为非法。 */
    if (addr7 == HKVT_ADDR_ILLEGAL_LOW)  return false;
    if (addr7 == HKVT_ADDR_ILLEGAL_HIGH) return false;
    if (addr7 < HKVT_ADDR_MIN)            return false;
    if (addr7 > HKVT_ADDR_MAX)            return false;
    return true;
}

void hkvt_apply_calibration(const hkvt_m3a_raw_t *raw,
                            const hkvt_m3a_calib_t *cal,
                            hkvt_m3a_force_t *out) {
    if (!raw || !cal || !out) return;
    /* F = K * (raw - zero_offset)  (datasheet §4.3) */
    out->force_x_n = cal->k[0] * (float)(raw->force_x_raw - cal->zero_offset[0]);
    out->force_y_n = cal->k[1] * (float)(raw->force_y_raw - cal->zero_offset[1]);
    out->force_z_n = cal->k[2] * (float)(raw->force_z_raw - cal->zero_offset[2]);
}

/* ---- 状态机 ---- */

bool hkvt_state_step(hkvt_m3a_t *d) {
    if (!d || !d->t.now_ms) return false;

    switch (d->state) {
    case HKVT_STATE_RESET: {
        d->boot_start_ms = d->t.now_ms(d->ctx);
        d->state = HKVT_STATE_BOOT;
        return false;   /* 进入稳定期, 本轮不可读 */
    }
    case HKVT_STATE_BOOT: {
        uint32_t elapsed = d->t.now_ms(d->ctx) - d->boot_start_ms;
        /* datasheet §4.1: 至少 1000ms; 期间发命令会导致校准失效 */
        if (elapsed < HKVT_BOOT_STABILIZE_MS) return false;
        d->state = HKVT_STATE_READY;
        return true;
    }
    case HKVT_STATE_READY:
        return true;
    default:
        return false;
    }
}

/* ---- driver API ---- */

static const hkvt_m3a_calib_t s_unit_calib = {
    .zero_offset = {0, 0, 0},
    .k = {1.0f, 1.0f, 1.0f},
};

bool hkvt_m3a_init(hkvt_m3a_t *d, const hkvt_transport_t *t, void *ctx,
                   uint8_t addr, const hkvt_m3a_calib_t *calib) {
    if (!d || !t || !t->read_force || !t->now_ms) return false;
    memset(d, 0, sizeof(*d));
    d->t    = *t;
    d->ctx  = ctx;
    d->addr = addr;
    if (!hkvt_validate_address(d->addr)) return false;
    d->calib = calib ? *calib : s_unit_calib;
    /* init 即进入 BOOT 并记录起点; 稳定期判定基于上电后经过的时间,
     * 不依赖是否先调过 read (set_address 也需通过稳定期门). */
    d->boot_start_ms = d->t.now_ms(d->ctx);
    d->state = HKVT_STATE_BOOT;
    d->seq   = 0;
    d->ok    = false;   /* ok 在 state_step 推进到 READY 后才为 true */
    return true;
}

bool hkvt_m3a_read(hkvt_m3a_t *d, hkvt_m3a_sample_t *out) {
    if (!d || !out) return false;

    /* 上电稳定期内禁止命令 (datasheet §4.1) */
    if (!hkvt_state_step(d)) {
        d->ok = false;
        return false;
    }
    if (d->state != HKVT_STATE_READY) return false;

    uint8_t buf[HKVT_FORCE_FRAME_BYTES];
    /* transport 负责保证 NACK+STOP 末字节行为 (真机在 adapter 验证) */
    if (!d->t.read_force(d->addr, buf, HKVT_FORCE_FRAME_BYTES, d->ctx)) {
        d->ok = false;
        return false;   /* I2C 错误 / short-read */
    }

    hkvt_m3a_raw_t raw;
    if (!hkvt_parse_xyz(buf, HKVT_FORCE_FRAME_BYTES, &raw)) {
        d->ok = false;
        return false;   /* 二次 short-read 防御 */
    }

    memset(out, 0, sizeof(*out));
    out->sensor_id    = d->addr;   /* 用 7-bit 地址作 sensor_id; 后续 acquisition 表可重映射 */
    out->raw          = raw;       /* raw 层: 原始 ADC */
    hkvt_apply_calibration(&raw, &d->calib, &out->derived);  /* derived 层: N */
    out->seq          = d->seq++;  /* metadata: 独立 seq */
    /* timestamp = MCU clock; transport 注入的 now_ms 为 ms 精度,
     * acquisition task 在更上层补 us 精度 (esp_timer_get_us). 本层保证字段存在. */
    out->timestamp_us = d->t.now_ms(d->ctx) * 1000u;
    out->quality_flags = 0;
    d->ok = true;
    return true;
}

bool hkvt_m3a_set_address(hkvt_m3a_t *d, uint8_t new_addr7) {
    if (!d || !d->t.set_address) return false;
    /* 写入前先校验新地址合法性 (datasheet §3.3) */
    if (!hkvt_validate_address(new_addr7)) return false;
    /* 上电稳定期内禁止写地址命令 */
    if (!hkvt_state_step(d)) return false;
    if (!d->t.set_address(d->addr, new_addr7, d->ctx)) return false;
    d->addr = new_addr7;   /* 地址持久化在 sensor Flash; 驱动仅同步内存 */
    return true;
}
