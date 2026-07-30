/*
 * hand_token.c — EchoGlove/EgoGlove V7 Hand Token v1 实现
 * 可移植 C11 (host gcc / ESP32 Arduino / ESP-IDF 通用), 无平台依赖。
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#include "hand_token.h"
#include <math.h>
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

static void serialize_base69(const hand_token_t *t, uint8_t *buf, uint8_t w_last)
{
    for (int i = 0; i < 5; ++i) put_f16(&buf[i * 2], t->flex[i]);
    if (w_last) {
        put_f16(&buf[10], t->quat[1]);
        put_f16(&buf[12], t->quat[2]);
        put_f16(&buf[14], t->quat[3]);
        put_f16(&buf[16], t->quat[0]);
    } else {
        for (int i = 0; i < 4; ++i) put_f16(&buf[10 + i * 2], t->quat[i]);
    }
    for (int i = 0; i < 6; ++i) put_f32(&buf[18 + i * 4], t->wrist_6dof[i]);
    for (int i = 0; i < 3; ++i) put_f16(&buf[42 + i * 2], t->vel[i]);
    for (int i = 0; i < 3; ++i) put_f16(&buf[48 + i * 2], t->acc[i]);
    for (int i = 0; i < 5; ++i) buf[54 + i] = t->contact[i] ? 1u : 0u;
    for (int i = 0; i < 5; ++i) put_f16(&buf[59 + i * 2], t->force[i]);
}

static void parse_base69(const uint8_t *buf, hand_token_t *out, uint8_t w_last)
{
    for (int i = 0; i < 5; ++i) out->flex[i]       = get_f16(&buf[i * 2]);
    if (w_last) {
        out->quat[1] = get_f16(&buf[10]);
        out->quat[2] = get_f16(&buf[12]);
        out->quat[3] = get_f16(&buf[14]);
        out->quat[0] = get_f16(&buf[16]);
    } else {
        for (int i = 0; i < 4; ++i) out->quat[i] = get_f16(&buf[10 + i * 2]);
    }
    for (int i = 0; i < 6; ++i) out->wrist_6dof[i] = get_f32(&buf[18 + i * 4]);
    for (int i = 0; i < 3; ++i) out->vel[i]        = get_f16(&buf[42 + i * 2]);
    for (int i = 0; i < 3; ++i) out->acc[i]        = get_f16(&buf[48 + i * 2]);
    for (int i = 0; i < 5; ++i) out->contact[i]    = buf[54 + i] ? 1u : 0u;
    for (int i = 0; i < 5; ++i) out->force[i]      = get_f16(&buf[59 + i * 2]);
}

static int finite_f16(float value)
{
    return isfinite(hand_token_f16_to_f32(hand_token_f32_to_f16(value)));
}

static int skeleton_valid(const hand_skeleton_t *skeleton)
{
    if (!skeleton || skeleton->revision == 0 ||
        skeleton->offsets[0][0] != 0.0f || skeleton->offsets[0][1] != 0.0f ||
        skeleton->offsets[0][2] != 0.0f) return 0;

    for (int joint = 0; joint < HAND_SKELETON_JOINT_COUNT; ++joint) {
        float norm2 = 0.0f;
        for (int component = 0; component < 4; ++component) {
            float value = skeleton->quat[joint][component];
            if (!isfinite(value)) return 0;
            norm2 += value * value;
        }
        if (!isfinite(norm2) || norm2 <= 0.0f) return 0;
    }
    for (int offset = 0; offset < HAND_SKELETON_OFFSET_COUNT; ++offset) {
        for (int component = 0; component < 3; ++component) {
            if (!finite_f16(skeleton->offsets[offset][component])) return 0;
        }
    }
    return 1;
}

static int normalize_quaternion(float quat[4])
{
    float norm2 = 0.0f;
    for (int component = 0; component < 4; ++component) {
        if (!isfinite(quat[component])) return 0;
        norm2 += quat[component] * quat[component];
    }
    if (!isfinite(norm2) || norm2 <= 0.0f) return 0;

    float inverse_norm = 1.0f / sqrtf(norm2);
    for (int component = 0; component < 4; ++component) {
        quat[component] *= inverse_norm;
    }
    return 1;
}

static int normalize_quaternion_wire(const float in[4], float out[4])
{
    float candidate[4];
    uint16_t bits[4];

    if (!in || !out) return 0;
    for (int component = 0; component < 4; ++component) candidate[component] = in[component];
    if (!normalize_quaternion(candidate)) return 0;
    for (int component = 0; component < 4; ++component) {
        bits[component] = hand_token_f32_to_f16(candidate[component]);
        candidate[component] = hand_token_f16_to_f32(bits[component]);
        if (!isfinite(candidate[component])) return 0;
    }

    /* Iterate f16 rounding and normalization to a deterministic wire fixed point. */
    for (int iteration = 0; iteration < 32; ++iteration) {
        float normalized[4];
        uint16_t next_bits[4];
        int stable = 1;
        for (int component = 0; component < 4; ++component) normalized[component] = candidate[component];
        if (!normalize_quaternion(normalized)) return 0;
        for (int component = 0; component < 4; ++component) {
            next_bits[component] = hand_token_f32_to_f16(normalized[component]);
            candidate[component] = hand_token_f16_to_f32(next_bits[component]);
            if (!isfinite(candidate[component]) || next_bits[component] != bits[component]) stable = 0;
        }
        for (int component = 0; component < 4; ++component) bits[component] = next_bits[component];
        if (stable) {
            for (int component = 0; component < 4; ++component) out[component] = candidate[component];
            return 1;
        }
    }
    return 0;
}

static int serialize_v2_base69(const hand_token_t *t, uint8_t *buf, uint8_t w_last)
{
    float quat[4];
    if (!normalize_quaternion_wire(t->quat, quat)) return 0;
    serialize_base69(t, buf, w_last);
    if (w_last) {
        put_f16(&buf[10], quat[1]);
        put_f16(&buf[12], quat[2]);
        put_f16(&buf[14], quat[3]);
        put_f16(&buf[16], quat[0]);
    } else {
        for (int component = 0; component < 4; ++component) {
            put_f16(&buf[10 + component * 2], quat[component]);
        }
    }
    return 1;
}

static uint8_t *write_tlv_header(uint8_t *cursor, uint8_t type, uint16_t length)
{
    cursor[0] = type;
    put_u16(&cursor[1], length);
    return cursor + 3;
}

static int serialize_skeleton_tlvs(const hand_token_v2_t *token, uint8_t *cursor)
{
    const hand_skeleton_t *skeleton = &token->skeleton;
    uint8_t w_last = token->caps & HAND_TOKEN_CAP_QUAT_WLAST;

    cursor = write_tlv_header(cursor, HAND_TOKEN_TLV_SKELETON_QUAT20, 160);
    for (int joint = 0; joint < HAND_SKELETON_JOINT_COUNT; ++joint) {
        float quat[4];
        if (!normalize_quaternion_wire(skeleton->quat[joint], quat)) return 0;
        if (w_last) {
            put_f16(cursor, quat[1]);
            put_f16(cursor + 2, quat[2]);
            put_f16(cursor + 4, quat[3]);
            put_f16(cursor + 6, quat[0]);
        } else {
            for (int component = 0; component < 4; ++component) {
                put_f16(cursor + component * 2, quat[component]);
            }
        }
        cursor += 8;
    }

    cursor = write_tlv_header(cursor, HAND_TOKEN_TLV_REST_OFFSETS, 150);
    for (int offset = 0; offset < HAND_SKELETON_OFFSET_COUNT; ++offset) {
        for (int component = 0; component < 3; ++component) {
            put_f16(cursor + component * 2, skeleton->offsets[offset][component]);
        }
        cursor += 6;
    }

    cursor = write_tlv_header(cursor, HAND_TOKEN_TLV_REST_MODEL_ID, 4);
    put_u16(cursor, skeleton->model_id);
    put_u16(cursor + 2, skeleton->revision);
    return 1;
}

/* ---------- 序列化 ---------- */
size_t hand_token_serialize(const hand_token_t *t, uint8_t *buf, size_t buflen)
{
    if (!t || !buf || buflen < HAND_TOKEN_FRAME_SIZE) return 0;

    buf[HAND_TOKEN_OFF_MAGIC + 0] = HAND_TOKEN_MAGIC0;
    buf[HAND_TOKEN_OFF_MAGIC + 1] = HAND_TOKEN_MAGIC1;
    buf[HAND_TOKEN_OFF_VERSION]   = HAND_TOKEN_VERSION;
    buf[HAND_TOKEN_OFF_DEVICE_ID] = hand_token_make_device_id(t->product, t->hand, t->serial);
    put_u32(&buf[HAND_TOKEN_OFF_TIMESTAMP], t->timestamp_us);
    serialize_base69(t, &buf[HAND_TOKEN_OFF_FLEX], 0);

    uint16_t crc = hand_token_crc16(buf, HAND_TOKEN_OFF_CRC);
    put_u16(&buf[HAND_TOKEN_OFF_CRC], crc);
    return HAND_TOKEN_FRAME_SIZE;
}

/* ---------- 解析 ---------- */
bool hand_token_parse(const uint8_t *buf, size_t n, hand_token_t *out)
{
    if (!buf || !out || n != HAND_TOKEN_FRAME_SIZE) return false;
    if (buf[HAND_TOKEN_OFF_MAGIC + 0] != HAND_TOKEN_MAGIC0 ||
        buf[HAND_TOKEN_OFF_MAGIC + 1] != HAND_TOKEN_MAGIC1) return false;
    if (buf[HAND_TOKEN_OFF_VERSION] != HAND_TOKEN_VERSION) return false;

    uint16_t want = get_u16(&buf[HAND_TOKEN_OFF_CRC]);
    uint16_t have = hand_token_crc16(buf, HAND_TOKEN_OFF_CRC);
    if (want != have) return false;

    hand_token_split_device_id(buf[HAND_TOKEN_OFF_DEVICE_ID],
                               &out->product, &out->hand, &out->serial);
    out->timestamp_us = get_u32(&buf[HAND_TOKEN_OFF_TIMESTAMP]);
    parse_base69(&buf[HAND_TOKEN_OFF_FLEX], out, 0);
    return true;
}

hand_token_wire_version_t hand_token_detect_version(const uint8_t *buf, size_t n)
{
    if (!buf || n < 3 || buf[0] != HAND_TOKEN_MAGIC0 || buf[1] != HAND_TOKEN_MAGIC1) {
        return HAND_TOKEN_WIRE_INVALID;
    }
    if (buf[2] == HAND_TOKEN_VERSION_V1) return HAND_TOKEN_WIRE_V1;
    if (buf[2] == HAND_TOKEN_VERSION_V2) return HAND_TOKEN_WIRE_V2;
    return HAND_TOKEN_WIRE_INVALID;
}

size_t hand_token_v2_serialize(const hand_token_v2_t *t, uint8_t *buf, size_t buflen)
{
    if (!t || !buf || t->caps & (HAND_TOKEN_CAP_GLOBAL_WRIST |
                                  HAND_TOKEN_CAP_SKEL_SMALLEST3 |
                                  HAND_TOKEN_CAP_RESERVED)) {
        return 0;
    }

    uint8_t has_skeleton = (t->caps & HAND_TOKEN_CAP_HAS_SKELETON) != 0;
    size_t frame_size = has_skeleton ? HAND_TOKEN_V2_SKELETON_FRAME_SIZE :
                                       HAND_TOKEN_V2_LITE_FRAME_SIZE;
    if (buflen < frame_size || has_skeleton != t->has_skeleton ||
        (has_skeleton && !skeleton_valid(&t->skeleton))) return 0;

    buf[0] = HAND_TOKEN_MAGIC0;
    buf[1] = HAND_TOKEN_MAGIC1;
    buf[2] = HAND_TOKEN_VERSION_V2;
    buf[3] = hand_token_make_device_id(t->base.product, t->base.hand, t->base.serial);
    put_u32(&buf[4], t->base.timestamp_us);
    buf[HAND_TOKEN_V2_OFF_CAPS] = t->caps;
    put_u16(&buf[HAND_TOKEN_V2_OFF_TOTAL_LEN], (uint16_t)frame_size);
    if (!serialize_v2_base69(&t->base, &buf[HAND_TOKEN_V2_OFF_BASE],
                             t->caps & HAND_TOKEN_CAP_QUAT_WLAST)) return 0;
    if (has_skeleton && !serialize_skeleton_tlvs(t, &buf[HAND_TOKEN_V2_OFF_TLV])) return 0;
    put_u16(&buf[frame_size - 2], hand_token_crc16(buf, frame_size - 2));
    return frame_size;
}

bool hand_token_v2_parse(const uint8_t *buf, size_t n, hand_token_v2_t *out)
{
    if (!buf || !out || n < HAND_TOKEN_V2_LITE_FRAME_SIZE ||
        hand_token_detect_version(buf, n) != HAND_TOKEN_WIRE_V2) return false;

    const uint8_t *end = buf + n;
    if (end - buf < HAND_TOKEN_V2_OFF_BASE + 69 + 2) return false;
    uint16_t total_len = get_u16(&buf[HAND_TOKEN_V2_OFF_TOTAL_LEN]);
    if (total_len != n || total_len < HAND_TOKEN_V2_LITE_FRAME_SIZE) return false;
    uint8_t caps = buf[HAND_TOKEN_V2_OFF_CAPS];
    if (caps & (HAND_TOKEN_CAP_GLOBAL_WRIST |
                HAND_TOKEN_CAP_SKEL_SMALLEST3 |
                HAND_TOKEN_CAP_RESERVED)) return false;
    if (get_u16(end - 2) != hand_token_crc16(buf, n - 2)) return false;

    uint8_t has_skeleton = (caps & HAND_TOKEN_CAP_HAS_SKELETON) != 0;
    if (!has_skeleton && n != HAND_TOKEN_V2_LITE_FRAME_SIZE) return false;
    if (has_skeleton && n != HAND_TOKEN_V2_SKELETON_FRAME_SIZE && n > HAND_TOKEN_V2_MAX_FRAME_SIZE) {
        return false;
    }

    hand_token_v2_t parsed;
    memset(&parsed, 0, sizeof(parsed));
    hand_token_split_device_id(buf[3], &parsed.base.product, &parsed.base.hand, &parsed.base.serial);
    parsed.base.timestamp_us = get_u32(&buf[4]);
    parse_base69(&buf[HAND_TOKEN_V2_OFF_BASE], &parsed.base,
                 caps & HAND_TOKEN_CAP_QUAT_WLAST);
    if (!normalize_quaternion(parsed.base.quat)) return false;
    parsed.caps = caps;

    const uint8_t *cursor = buf + HAND_TOKEN_V2_OFF_TLV;
    const uint8_t *crc = end - 2;
    uint8_t seen = 0;
    while (cursor < crc) {
        if ((size_t)(crc - cursor) < 3) return false;
        uint8_t type = cursor[0];
        uint16_t length = get_u16(cursor + 1);
        cursor += 3;
        if ((size_t)(crc - cursor) < length) return false;

        if (type == HAND_TOKEN_TLV_SKELETON_QUAT20) {
            if (seen & 0x01u || length != 160) return false;
            seen |= 0x01u;
            for (int joint = 0; joint < HAND_SKELETON_JOINT_COUNT; ++joint) {
                float *quat = parsed.skeleton.quat[joint];
                if (caps & HAND_TOKEN_CAP_QUAT_WLAST) {
                    quat[1] = get_f16(cursor);
                    quat[2] = get_f16(cursor + 2);
                    quat[3] = get_f16(cursor + 4);
                    quat[0] = get_f16(cursor + 6);
                } else {
                    for (int component = 0; component < 4; ++component) {
                        quat[component] = get_f16(cursor + component * 2);
                    }
                }
                if (!normalize_quaternion(quat)) return false;
                cursor += 8;
            }
            continue;
        }
        if (type == HAND_TOKEN_TLV_REST_OFFSETS) {
            if (seen & 0x02u || length != 150) return false;
            seen |= 0x02u;
            for (int offset = 0; offset < HAND_SKELETON_OFFSET_COUNT; ++offset) {
                for (int component = 0; component < 3; ++component) {
                    parsed.skeleton.offsets[offset][component] = get_f16(cursor + component * 2);
                }
                cursor += 6;
            }
            continue;
        }
        if (type == HAND_TOKEN_TLV_REST_MODEL_ID) {
            if (seen & 0x04u || length != 4) return false;
            seen |= 0x04u;
            parsed.skeleton.model_id = get_u16(cursor);
            parsed.skeleton.revision = get_u16(cursor + 2);
            cursor += 4;
            continue;
        }
        cursor += length;
    }

    if (cursor != crc) return false;
    if (has_skeleton) {
        if (seen != 0x07u || !skeleton_valid(&parsed.skeleton)) return false;
        parsed.has_skeleton = true;
    } else if (seen != 0) {
        return false;
    }

    *out = parsed;
    return true;
}

bool hand_token_v2_parse_compatible(const uint8_t *buf, size_t n, hand_token_v2_t *out)
{
    if (!buf || !out) return false;

    if (hand_token_detect_version(buf, n) == HAND_TOKEN_WIRE_V2) {
        return hand_token_v2_parse(buf, n, out);
    }
    if (hand_token_detect_version(buf, n) != HAND_TOKEN_WIRE_V1 ||
        n != HAND_TOKEN_FRAME_SIZE) return false;

    memset(out, 0, sizeof(*out));
    return hand_token_parse(buf, n, &out->base);
}
