/*
 * hand_token.c — EchoGlove/EgoGlove V7 Hand Token v1 实现
 * 可移植 C11 (host gcc / ESP32 Arduino / ESP-IDF 通用), 无平台依赖。
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#include "hand_token.h"
#include <string.h>

/* ---------- device_id ---------- */
uint8_t hand_token_make_device_id(uint8_t product, uint8_t hand, uint8_t serial)
{
    return (uint8_t)(((product & 0x01u) << 7) |
                     ((hand    & 0x01u) << 6) |
                      (serial  & 0x3Fu));
}

void hand_token_split_device_id(uint8_t id, uint8_t *product, uint8_t *hand, uint8_t *serial)
{
    if (product) *product = (uint8_t)((id >> 7) & 0x01u);
    if (hand)    *hand    = (uint8_t)((id >> 6) & 0x01u);
    if (serial)  *serial  = (uint8_t)(id & 0x3Fu);
}

/* ---------- CRC-16/MODBUS (poly 0xA001, init 0xFFFF) ---------- */
uint16_t hand_token_crc16(const uint8_t *buf, size_t n)
{
    uint16_t crc = 0xFFFFu;
    for (size_t i = 0; i < n; ++i) {
        crc ^= (uint16_t)buf[i];
        for (int b = 0; b < 8; ++b) {
            if (crc & 1u) crc = (uint16_t)((crc >> 1) ^ 0xA001u);
            else          crc = (uint16_t)(crc >> 1);
        }
    }
    return crc;
}

/* ---------- float16 (IEEE754 half) 转换 ----------
 * f32->f16 采用 round-to-nearest-even, 与 Python struct.pack('<e') 一致,
 * 保证跨语言金标向量逐字节相同。
 */
uint16_t hand_token_f32_to_f16(float f)
{
    uint32_t x;
    memcpy(&x, &f, sizeof(x));
    uint32_t sign = (x >> 16) & 0x8000u;
    uint32_t expo = (x >> 23) & 0xFFu;
    uint32_t mant = x & 0x7FFFFFu;

    if (expo == 0xFFu) {                 /* Inf / NaN */
        return (uint16_t)(sign | 0x7C00u | (mant ? 0x0200u : 0u));
    }

    int32_t e = (int32_t)expo - 127 + 15;

    if (e >= 0x1F) {                     /* 上溢 → Inf */
        return (uint16_t)(sign | 0x7C00u);
    }
    if (e <= 0) {                        /* 次正规 / 0 */
        if (e < -10) {
            return (uint16_t)sign;       /* 太小 → ±0 */
        }
        mant |= 0x800000u;               /* 补隐含 1 */
        uint32_t shift = (uint32_t)(14 - e);
        uint16_t half = (uint16_t)(mant >> shift);
        uint32_t rem  = mant & ((1u << shift) - 1u);
        uint32_t halfway = 1u << (shift - 1);
        if (rem > halfway || (rem == halfway && (half & 1u))) {
            half++;                      /* round half to even */
        }
        return (uint16_t)(sign | half);
    }

    uint16_t half = (uint16_t)(sign | ((uint32_t)e << 10) | (mant >> 13));
    uint32_t rem  = mant & 0x1FFFu;      /* 被丢弃的低 13 位 */
    uint32_t halfway = 0x1000u;
    if (rem > halfway || (rem == halfway && (half & 1u))) {
        half++;                          /* 进位可自然溢入指数域 */
    }
    return half;
}

float hand_token_f16_to_f32(uint16_t h)
{
    uint32_t sign = (uint32_t)(h & 0x8000u) << 16;
    uint32_t expo = (h >> 10) & 0x1Fu;
    uint32_t mant = h & 0x3FFu;
    uint32_t out;

    if (expo == 0) {
        if (mant == 0) {
            out = sign;                  /* ±0 */
        } else {                         /* 次正规 → 正规化 */
            int e = -1;
            do { e++; mant <<= 1; } while ((mant & 0x400u) == 0);
            mant &= 0x3FFu;
            out = sign | (uint32_t)((127 - 15 - e) << 23) | (mant << 13);
        }
    } else if (expo == 0x1F) {           /* Inf / NaN */
        out = sign | 0x7F800000u | (mant << 13);
    } else {
        out = sign | (uint32_t)((int)expo - 15 + 127) << 23 | (mant << 13);
    }
    float f;
    memcpy(&f, &out, sizeof(f));
    return f;
}

/* ---------- 小端写入 helpers ---------- */
static void put_u16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); }
static void put_u32(uint8_t *p, uint32_t v) {
    p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}
static uint16_t get_u16(const uint8_t *p) { return (uint16_t)(p[0] | ((uint16_t)p[1] << 8)); }
static uint32_t get_u32(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}
static void put_f16(uint8_t *p, float v)  { put_u16(p, hand_token_f32_to_f16(v)); }
static float get_f16(const uint8_t *p)    { return hand_token_f16_to_f32(get_u16(p)); }
static void put_f32(uint8_t *p, float v)  { uint32_t u; memcpy(&u, &v, 4); put_u32(p, u); }
static float get_f32(const uint8_t *p)    { uint32_t u = get_u32(p); float f; memcpy(&f, &u, 4); return f; }

/* ---------- 序列化 ---------- */
size_t hand_token_serialize(const hand_token_t *t, uint8_t *buf, size_t buflen)
{
    if (!t || !buf || buflen < HAND_TOKEN_FRAME_SIZE) return 0;

    buf[HAND_TOKEN_OFF_MAGIC + 0] = HAND_TOKEN_MAGIC0;
    buf[HAND_TOKEN_OFF_MAGIC + 1] = HAND_TOKEN_MAGIC1;
    buf[HAND_TOKEN_OFF_VERSION]   = HAND_TOKEN_VERSION;
    buf[HAND_TOKEN_OFF_DEVICE_ID] = hand_token_make_device_id(t->product, t->hand, t->serial);
    put_u32(&buf[HAND_TOKEN_OFF_TIMESTAMP], t->timestamp_us);

    for (int i = 0; i < 5; ++i) put_f16(&buf[HAND_TOKEN_OFF_FLEX + i * 2], t->flex[i]);
    for (int i = 0; i < 4; ++i) put_f16(&buf[HAND_TOKEN_OFF_QUAT + i * 2], t->quat[i]);
    for (int i = 0; i < 6; ++i) put_f32(&buf[HAND_TOKEN_OFF_WRIST + i * 4], t->wrist_6dof[i]);
    for (int i = 0; i < 3; ++i) put_f16(&buf[HAND_TOKEN_OFF_VEL + i * 2], t->vel[i]);
    for (int i = 0; i < 3; ++i) put_f16(&buf[HAND_TOKEN_OFF_ACC + i * 2], t->acc[i]);
    for (int i = 0; i < 5; ++i) buf[HAND_TOKEN_OFF_CONTACT + i] = t->contact[i] ? 1u : 0u;
    for (int i = 0; i < 5; ++i) put_f16(&buf[HAND_TOKEN_OFF_FORCE + i * 2], t->force[i]);

    uint16_t crc = hand_token_crc16(buf, HAND_TOKEN_OFF_CRC);
    put_u16(&buf[HAND_TOKEN_OFF_CRC], crc);
    return HAND_TOKEN_FRAME_SIZE;
}

/* ---------- 解析 ---------- */
bool hand_token_parse(const uint8_t *buf, size_t n, hand_token_t *out)
{
    if (!buf || !out || n < HAND_TOKEN_FRAME_SIZE) return false;
    if (buf[HAND_TOKEN_OFF_MAGIC + 0] != HAND_TOKEN_MAGIC0 ||
        buf[HAND_TOKEN_OFF_MAGIC + 1] != HAND_TOKEN_MAGIC1) return false;
    if (buf[HAND_TOKEN_OFF_VERSION] != HAND_TOKEN_VERSION) return false;

    uint16_t want = get_u16(&buf[HAND_TOKEN_OFF_CRC]);
    uint16_t have = hand_token_crc16(buf, HAND_TOKEN_OFF_CRC);
    if (want != have) return false;

    hand_token_split_device_id(buf[HAND_TOKEN_OFF_DEVICE_ID],
                               &out->product, &out->hand, &out->serial);
    out->timestamp_us = get_u32(&buf[HAND_TOKEN_OFF_TIMESTAMP]);

    for (int i = 0; i < 5; ++i) out->flex[i]       = get_f16(&buf[HAND_TOKEN_OFF_FLEX + i * 2]);
    for (int i = 0; i < 4; ++i) out->quat[i]       = get_f16(&buf[HAND_TOKEN_OFF_QUAT + i * 2]);
    for (int i = 0; i < 6; ++i) out->wrist_6dof[i] = get_f32(&buf[HAND_TOKEN_OFF_WRIST + i * 4]);
    for (int i = 0; i < 3; ++i) out->vel[i]        = get_f16(&buf[HAND_TOKEN_OFF_VEL + i * 2]);
    for (int i = 0; i < 3; ++i) out->acc[i]        = get_f16(&buf[HAND_TOKEN_OFF_ACC + i * 2]);
    for (int i = 0; i < 5; ++i) out->contact[i]    = buf[HAND_TOKEN_OFF_CONTACT + i] ? 1u : 0u;
    for (int i = 0; i < 5; ++i) out->force[i]      = get_f16(&buf[HAND_TOKEN_OFF_FORCE + i * 2]);
    return true;
}
