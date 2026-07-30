/*
 * test_hand_token.c — Hand Token v1 主机单元测试 (host gcc, 无需硬件)
 *
 * 构建运行:  make -C firmware/shared/test   (或见 Makefile)
 * 退出码 0 = 全部通过。验证: CRC-16/MODBUS 已知向量、float16 转换、device_id
 * 编解码、序列化定长、round-trip 无损、CRC/magic 负例、跨语言金标向量。
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#include "../hand_token.h"
#include "../hand_skeleton.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

static int g_fail = 0;
#define CHECK(cond, msg) do { \
    if (!(cond)) { printf("  [FAIL] %s\n", (msg)); g_fail++; } \
    else         { printf("  [ ok ] %s\n", (msg)); } \
} while (0)

/*
 * 金标向量 (canonical reference token 的序列化 79B, 全部 float16 字段取
 * 可精确表示值 → 与 Python struct.pack('<e'/'<f') 逐字节一致)。
 * 由本测试首轮打印的 GOLDEN= 行填入; C 与 relay/test_hand_token.py 共用同一串。
 */
static const char *GOLDEN_HEX =
    "485401c74e61bc00000000340038003a003c003c0000000000000000003e000080be0000003f000000000000c03f000040c00038003400300040000000c0010001000100380000003d000000408e4c";

/* 构造 canonical reference token (所有 f16 字段可精确表示) */
static void make_ref(hand_token_t *t)
{
    memset(t, 0, sizeof(*t));
    t->product = HAND_TOKEN_PRODUCT_PRO;   /* 1 */
    t->hand    = HAND_TOKEN_HAND_RIGHT;    /* 1 */
    t->serial  = 7;                        /* device_id = 0xC7 */
    t->timestamp_us = 12345678u;           /* 0x00BC614E */
    float flex[5] = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    float quat[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    float wr[6]   = {0.125f, -0.25f, 0.5f, 0.0f, 1.5f, -3.0f};
    float vel[3]  = {0.5f, 0.25f, 0.125f};
    float acc[3]  = {2.0f, 0.0f, -2.0f};
    uint8_t ct[5] = {1, 0, 1, 0, 1};
    float force[5]= {0.5f, 0.0f, 1.25f, 0.0f, 2.0f};
    memcpy(t->flex, flex, sizeof(flex));
    memcpy(t->quat, quat, sizeof(quat));
    memcpy(t->wrist_6dof, wr, sizeof(wr));
    memcpy(t->vel, vel, sizeof(vel));
    memcpy(t->acc, acc, sizeof(acc));
    memcpy(t->contact, ct, sizeof(ct));
    memcpy(t->force, force, sizeof(force));
}

static void print_hex(const char *label, const uint8_t *b, size_t n)
{
    printf("%s", label);
    for (size_t i = 0; i < n; ++i) printf("%02x", b[i]);
    printf("\n");
}

static void put_u16_le(uint8_t *p, uint16_t value)
{
    p[0] = (uint8_t)value;
    p[1] = (uint8_t)(value >> 8);
}

static uint16_t get_u16_le(const uint8_t *p)
{
    return (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
}

static void refresh_v2_crc(uint8_t *frame, size_t length)
{
    put_u16_le(&frame[length - 2], hand_token_crc16(frame, length - 2));
}

static void make_ref_skeleton(hand_skeleton_t *skeleton)
{
    memset(skeleton, 0, sizeof(*skeleton));
    skeleton->model_id = HAND_REST_MODEL_CANONICAL_HUMAN;
    skeleton->revision = 1;
    for (int i = 0; i < HAND_SKELETON_JOINT_COUNT; ++i) {
        skeleton->quat[i][0] = 1.0f;
    }
    skeleton->quat[0][0] = 0.5f;
    skeleton->quat[0][1] = 0.5f;
    skeleton->quat[0][2] = 0.5f;
    skeleton->quat[0][3] = -0.5f;
    for (int i = 1; i < HAND_SKELETON_OFFSET_COUNT; ++i) {
        skeleton->offsets[i][0] = 0.25f;
    }
}

int main(void)
{
    printf("== Hand Token v1 host tests ==\n");

    /* 1) CRC-16/MODBUS 已知向量: crc16("123456789") == 0x4B37 */
    CHECK(hand_token_crc16((const uint8_t *)"123456789", 9) == 0x4B37,
          "CRC-16/MODBUS known vector 0x4B37");

    /* 2) float16 精确值转换 */
    CHECK(hand_token_f32_to_f16(0.0f)  == 0x0000, "f16(0.0)=0x0000");
    CHECK(hand_token_f32_to_f16(0.25f) == 0x3400, "f16(0.25)=0x3400");
    CHECK(hand_token_f32_to_f16(0.5f)  == 0x3800, "f16(0.5)=0x3800");
    CHECK(hand_token_f32_to_f16(0.75f) == 0x3A00, "f16(0.75)=0x3A00");
    CHECK(hand_token_f32_to_f16(1.0f)  == 0x3C00, "f16(1.0)=0x3C00");
    CHECK(hand_token_f32_to_f16(1.25f) == 0x3D00, "f16(1.25)=0x3D00");
    CHECK(hand_token_f32_to_f16(2.0f)  == 0x4000, "f16(2.0)=0x4000");
    CHECK(hand_token_f16_to_f32(0x3C00) == 1.0f,  "f16->f32(0x3C00)=1.0");
    CHECK(hand_token_f16_to_f32(hand_token_f32_to_f16(-2.0f)) == -2.0f, "f16 sign round-trip -2.0");

    /* 3) device_id 编解码 */
    uint8_t id = hand_token_make_device_id(1, 1, 7);
    CHECK(id == 0xC7, "device_id(Pro,R,7)=0xC7");
    uint8_t p, h, s;
    hand_token_split_device_id(id, &p, &h, &s);
    CHECK(p == 1 && h == 1 && s == 7, "device_id split round-trip");

    /* 4) 序列化定长 + 帧头 */
    hand_token_t ref;
    make_ref(&ref);
    uint8_t frame[HAND_TOKEN_FRAME_SIZE];
    size_t n = hand_token_serialize(&ref, frame, sizeof(frame));
    CHECK(n == HAND_TOKEN_FRAME_SIZE, "serialize returns 79");
    CHECK(frame[0] == 0x48 && frame[1] == 0x54, "magic 'HT'");
    CHECK(frame[2] == 0x01, "version 1");
    CHECK(frame[3] == 0xC7, "device_id byte 0xC7");

    /* 5) round-trip 无损 (ref 全部字段可精确表示) */
    hand_token_t got;
    CHECK(hand_token_parse(frame, n, &got), "parse ok");
    int eq = (got.product == ref.product) && (got.hand == ref.hand) &&
             (got.serial == ref.serial) && (got.timestamp_us == ref.timestamp_us);
    for (int i = 0; i < 5; ++i) eq &= (got.flex[i]    == ref.flex[i]);
    for (int i = 0; i < 4; ++i) eq &= (got.quat[i]    == ref.quat[i]);
    for (int i = 0; i < 6; ++i) eq &= (got.wrist_6dof[i] == ref.wrist_6dof[i]);
    for (int i = 0; i < 3; ++i) eq &= (got.vel[i]     == ref.vel[i]);
    for (int i = 0; i < 3; ++i) eq &= (got.acc[i]     == ref.acc[i]);
    for (int i = 0; i < 5; ++i) eq &= (got.contact[i] == ref.contact[i]);
    for (int i = 0; i < 5; ++i) eq &= (got.force[i]   == ref.force[i]);
    CHECK(eq, "round-trip lossless (exact-representable fields)");

    /* 6) 负例: CRC 损坏 / magic 错误 / 短帧 */
    uint8_t bad[HAND_TOKEN_FRAME_SIZE];
    memcpy(bad, frame, sizeof(bad));
    bad[10] ^= 0xFF;                       /* 破坏一个 payload 字节 */
    CHECK(!hand_token_parse(bad, sizeof(bad), &got), "corrupt payload rejected (CRC)");
    memcpy(bad, frame, sizeof(bad));
    bad[0] = 0xAA;                         /* 错误 magic */
    CHECK(!hand_token_parse(bad, sizeof(bad), &got), "wrong magic rejected");
    CHECK(!hand_token_parse(frame, HAND_TOKEN_FRAME_SIZE - 1, &got), "short frame rejected");

    /* 7) canonical-20 skeleton + 25 offsets -> derived MediaPipe-21 */
    static const int8_t expected_parent[HAND_SKELETON_JOINT_COUNT] = {
        -1, 0, 1, 2, 0, 4, 5, 6, 0, 8, 9, 10, 0, 12, 13, 14, 0, 16, 17, 18
    };
    int parents_ok = 1;
    for (int i = 0; i < HAND_SKELETON_JOINT_COUNT; ++i) {
        parents_ok &= (hand_skeleton_parent[i] == expected_parent[i]);
    }
    CHECK(parents_ok, "canonical-20 parent table");

    hand_skeleton_t skel;
    memset(&skel, 0, sizeof(skel));
    skel.model_id = HAND_REST_MODEL_CANONICAL_HUMAN;
    skel.revision = 1;
    for (int i = 0; i < HAND_SKELETON_JOINT_COUNT; ++i) skel.quat[i][0] = 1.0f;
    for (int i = 1; i < HAND_SKELETON_JOINT_COUNT; ++i) skel.offsets[i][0] = 1.0f;
    for (int i = 20; i < HAND_SKELETON_OFFSET_COUNT; ++i) skel.offsets[i][0] = 2.0f;

    float landmarks[HAND_MEDIAPIPE_LANDMARK_COUNT][3];
    CHECK(hand_skeleton_fk21(&skel, landmarks) == HAND_SKELETON_OK,
          "identity skeleton FK succeeds");
    static const float expected_x[HAND_MEDIAPIPE_LANDMARK_COUNT] = {
        0, 1, 2, 3, 5,
        2, 3, 4, 6,
        2, 3, 4, 6,
        2, 3, 4, 6,
        2, 3, 4, 6
    };
    int mapping_ok = 1;
    for (int i = 0; i < HAND_MEDIAPIPE_LANDMARK_COUNT; ++i) {
        mapping_ok &= (landmarks[i][0] == expected_x[i]);
        mapping_ok &= (landmarks[i][1] == 0.0f && landmarks[i][2] == 0.0f);
    }
    CHECK(mapping_ok, "MediaPipe-21 excludes extra metacarpals but preserves FK chains");
    CHECK(landmarks[8][0] == 6.0f, "Index tip uses REST_OFFSETS[21]");

    skel.offsets[0][0] = 1.0f;
    CHECK(hand_skeleton_fk21(&skel, landmarks) == HAND_SKELETON_INVALID_WRIST_OFFSET,
          "nonzero wrist offset rejected");
    skel.offsets[0][0] = 0.0f;
    skel.model_id = 99;
    CHECK(hand_skeleton_fk21(&skel, landmarks) == HAND_SKELETON_UNSUPPORTED_MODEL,
          "unsupported rest model rejected by FK");
    skel.model_id = HAND_REST_MODEL_CANONICAL_HUMAN;
    skel.revision = 0;
    CHECK(hand_skeleton_fk21(&skel, landmarks) == HAND_SKELETON_INVALID_REVISION,
          "rest model revision zero rejected");
    skel.revision = 1;
    make_ref_skeleton(&skel);
    skel.offsets[1][2] = NAN;
    CHECK(hand_skeleton_fk21(&skel, landmarks) == HAND_SKELETON_INVALID_ARGUMENT,
          "FK rejects nonfinite non-wrist offsets");

    /* 8) v2 Lite frame + version gate */
    hand_token_v2_t v2;
    memset(&v2, 0, sizeof(v2));
    v2.base = ref;
    uint8_t v2_frame[HAND_TOKEN_V2_MAX_FRAME_SIZE];
    size_t v2_n = hand_token_v2_serialize(&v2, v2_frame, sizeof(v2_frame));
    CHECK(v2_n == HAND_TOKEN_V2_LITE_FRAME_SIZE, "v2 Lite serialize returns 82");
    CHECK(v2_frame[2] == HAND_TOKEN_VERSION_V2, "v2 version byte");
    CHECK(v2_frame[HAND_TOKEN_V2_OFF_CAPS] == 0, "v2 Lite caps zero");
    CHECK(HAND_TOKEN_V2_OFF_BASE == 11 && HAND_TOKEN_V2_OFF_TLV == 80,
          "v2 header is 11 bytes and CRC begins at 80");
    CHECK((size_t)(v2_frame[9] | ((uint16_t)v2_frame[10] << 8)) == v2_n,
          "v2 total_len includes CRC");
    CHECK(hand_token_detect_version(frame, n) == HAND_TOKEN_WIRE_V1,
          "version gate detects v1");
    CHECK(hand_token_detect_version(v2_frame, v2_n) == HAND_TOKEN_WIRE_V2,
          "version gate detects v2");
    CHECK(hand_token_detect_version(v2_frame, 2) == HAND_TOKEN_WIRE_INVALID,
          "version gate rejects short prefix");
    CHECK(!hand_token_parse(v2_frame, v2_n, &got), "v1 parser cleanly rejects v2");
    hand_token_v2_t v2_got;
    CHECK(hand_token_v2_parse(v2_frame, v2_n, &v2_got), "v2 Lite parse ok");
    CHECK(v2_got.base.timestamp_us == ref.timestamp_us && !v2_got.has_skeleton,
          "v2 Lite base round-trip");
    CHECK(hand_token_v2_parse_compatible(frame, n, &v2_got),
          "v2 compatibility helper explicitly accepts v1");
    CHECK(v2_got.base.timestamp_us == ref.timestamp_us && v2_got.caps == 0 &&
          !v2_got.has_skeleton, "v1 compatibility result has no v2 capabilities");
    uint8_t v1_with_trailing[HAND_TOKEN_FRAME_SIZE + 1];
    memcpy(v1_with_trailing, frame, n);
    v1_with_trailing[n] = 0;
    CHECK(!hand_token_parse(v1_with_trailing, sizeof(v1_with_trailing), &got),
          "direct v1 parser rejects trailing data");
    CHECK(!hand_token_v2_parse_compatible(v1_with_trailing,
                                           sizeof(v1_with_trailing), &v2_got),
          "v1 compatibility parser rejects trailing data");

    uint8_t invalid_v2[HAND_TOKEN_V2_LITE_FRAME_SIZE + 1];
    memcpy(invalid_v2, v2_frame, v2_n);
    invalid_v2[HAND_TOKEN_V2_OFF_CAPS] = HAND_TOKEN_CAP_RESERVED;
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n, &v2_got),
          "v2 reserved capability rejected");
    invalid_v2[HAND_TOKEN_V2_OFF_CAPS] = HAND_TOKEN_CAP_SKEL_SMALLEST3;
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n, &v2_got),
          "v2 smallest-three capability rejected");
    invalid_v2[HAND_TOKEN_V2_OFF_CAPS] = HAND_TOKEN_CAP_GLOBAL_WRIST;
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n, &v2_got),
          "v2 unimplemented global wrist capability rejected");
    v2.caps = HAND_TOKEN_CAP_GLOBAL_WRIST;
    CHECK(hand_token_v2_serialize(&v2, invalid_v2, sizeof(invalid_v2)) == 0,
          "v2 serializer rejects unimplemented global wrist capability");
    v2.caps = 0;
    invalid_v2[HAND_TOKEN_V2_OFF_CAPS] = HAND_TOKEN_CAP_HAS_SKELETON;
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n, &v2_got),
          "v2 skeleton capability deferred to TLV codec");
    memcpy(invalid_v2, v2_frame, v2_n);
    invalid_v2[HAND_TOKEN_V2_OFF_TOTAL_LEN]++;
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n, &v2_got),
          "v2 mismatched total length rejected");
    memcpy(invalid_v2, v2_frame, v2_n);
    invalid_v2[v2_n - 1] ^= 0x01u;
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n, &v2_got), "v2 corrupt CRC rejected");
    memcpy(invalid_v2, v2_frame, v2_n);
    invalid_v2[v2_n] = 0;
    invalid_v2[HAND_TOKEN_V2_OFF_TOTAL_LEN] = (uint8_t)(v2_n + 1);
    invalid_v2[HAND_TOKEN_V2_OFF_TOTAL_LEN + 1] = 0;
    uint16_t extended_crc = hand_token_crc16(invalid_v2, v2_n - 1);
    invalid_v2[v2_n - 1] = (uint8_t)extended_crc;
    invalid_v2[v2_n] = (uint8_t)(extended_crc >> 8);
    CHECK(!hand_token_v2_parse(invalid_v2, v2_n + 1, &v2_got),
          "v2 non-Lite length rejected before TLV support");

    /* 9) v2 self-contained canonical-20 skeleton TLVs */
    hand_token_v2_t skeleton_token;
    memset(&skeleton_token, 0, sizeof(skeleton_token));
    skeleton_token.base = ref;
    skeleton_token.base.quat[0] = 0.5f;
    skeleton_token.base.quat[1] = 0.5f;
    skeleton_token.base.quat[2] = -0.5f;
    skeleton_token.base.quat[3] = 0.5f;
    skeleton_token.caps = HAND_TOKEN_CAP_HAS_SKELETON | HAND_TOKEN_CAP_QUAT_WLAST;
    skeleton_token.has_skeleton = true;
    make_ref_skeleton(&skeleton_token.skeleton);
    skeleton_token.skeleton.quat[1][0] = 2.0f;

    uint8_t skeleton_frame[HAND_TOKEN_V2_MAX_FRAME_SIZE];
    size_t skeleton_n = hand_token_v2_serialize(&skeleton_token, skeleton_frame,
                                                sizeof(skeleton_frame));
    CHECK(skeleton_n == HAND_TOKEN_V2_SKELETON_FRAME_SIZE,
          "v2 skeleton serialize returns deterministic 405 bytes");
    if (skeleton_n != HAND_TOKEN_V2_SKELETON_FRAME_SIZE) {
        printf("== FAILED ==\n");
        return 1;
    }
    CHECK(get_u16_le(&skeleton_frame[HAND_TOKEN_V2_OFF_TOTAL_LEN]) == skeleton_n,
          "v2 skeleton total_len includes all TLVs and CRC");
    CHECK(skeleton_frame[HAND_TOKEN_V2_OFF_TLV] == HAND_TOKEN_TLV_SKELETON_QUAT20 &&
          get_u16_le(&skeleton_frame[HAND_TOKEN_V2_OFF_TLV + 1]) == 160 &&
          skeleton_frame[243] == HAND_TOKEN_TLV_REST_OFFSETS &&
          get_u16_le(&skeleton_frame[244]) == 150 &&
          skeleton_frame[396] == HAND_TOKEN_TLV_REST_MODEL_ID &&
          get_u16_le(&skeleton_frame[397]) == 4,
          "v2 skeleton emits required TLVs in 01/02/08 order");
    CHECK(fabsf(hand_token_f16_to_f32(get_u16_le(&skeleton_frame[91]))) <= 0.001f &&
          fabsf(hand_token_f16_to_f32(get_u16_le(&skeleton_frame[93]))) <= 0.001f &&
          fabsf(hand_token_f16_to_f32(get_u16_le(&skeleton_frame[95]))) <= 0.001f &&
          fabsf(hand_token_f16_to_f32(get_u16_le(&skeleton_frame[97])) - 1.0f) <= 0.001f,
          "QUAT_WLAST emits normalized f16 skeleton quaternion as x/y/z/w");
    CHECK(hand_token_f16_to_f32(get_u16_le(&skeleton_frame[21])) == 0.5f &&
          hand_token_f16_to_f32(get_u16_le(&skeleton_frame[23])) == -0.5f &&
          hand_token_f16_to_f32(get_u16_le(&skeleton_frame[25])) == 0.5f &&
          hand_token_f16_to_f32(get_u16_le(&skeleton_frame[27])) == 0.5f,
          "QUAT_WLAST serializes base wrist quaternion as x/y/z/w");

    hand_token_v2_t skeleton_got;
    CHECK(hand_token_v2_parse(skeleton_frame, skeleton_n, &skeleton_got),
          "v2 skeleton parse succeeds");
    CHECK(skeleton_got.has_skeleton &&
          skeleton_got.skeleton.model_id == HAND_REST_MODEL_CANONICAL_HUMAN &&
          skeleton_got.skeleton.revision == 1 &&
          skeleton_got.skeleton.quat[0][0] == 0.5f &&
          skeleton_got.skeleton.quat[0][1] == 0.5f &&
          skeleton_got.skeleton.quat[0][2] == 0.5f &&
          skeleton_got.skeleton.quat[0][3] == -0.5f,
          "v2 parser normalizes QUAT_WLAST skeleton data to w-first");
    uint8_t skeleton_roundtrip[HAND_TOKEN_V2_MAX_FRAME_SIZE];
    uint8_t skeleton_canonical[HAND_TOKEN_V2_MAX_FRAME_SIZE];
    uint8_t malformed[HAND_TOKEN_V2_MAX_FRAME_SIZE];
    size_t skeleton_roundtrip_n = hand_token_v2_serialize(&skeleton_got,
                                                            skeleton_roundtrip,
                                                            sizeof(skeleton_roundtrip));
    CHECK(skeleton_roundtrip_n == skeleton_n &&
          memcmp(skeleton_roundtrip, skeleton_frame, skeleton_n) == 0,
          "v2 skeleton serialize(parse(frame)) is byte-stable");
    memcpy(skeleton_canonical, skeleton_roundtrip, skeleton_roundtrip_n);
    CHECK(hand_token_v2_parse(skeleton_roundtrip, skeleton_roundtrip_n, &skeleton_got) &&
          hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                  sizeof(skeleton_roundtrip)) == skeleton_roundtrip_n &&
          memcmp(skeleton_roundtrip, skeleton_canonical, skeleton_roundtrip_n) == 0,
          "canonical skeleton serialization remains stable on repeated cycles");

    memcpy(malformed, skeleton_frame, skeleton_n);
    put_u16_le(&malformed[21], 0x4000u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "parser accepts finite non-unit base wrist quaternion (W-last)");
    CHECK(hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                  sizeof(skeleton_roundtrip)) == skeleton_n &&
          memcmp(skeleton_roundtrip, malformed, skeleton_n) != 0 &&
          hand_token_v2_parse(skeleton_roundtrip, skeleton_n, &skeleton_got) &&
          hand_token_v2_serialize(&skeleton_got, malformed, sizeof(malformed)) == skeleton_n &&
          memcmp(malformed, skeleton_roundtrip, skeleton_n) == 0,
          "W-last base wrist canonicalization reaches a byte-stable fixed point");

    memcpy(malformed, skeleton_frame, skeleton_n);
    put_u16_le(&malformed[83], 0x4000u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "parser accepts finite non-unit skeleton quaternion (W-last)");
    CHECK(hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                  sizeof(skeleton_roundtrip)) == skeleton_n &&
          memcmp(skeleton_roundtrip, malformed, skeleton_n) != 0 &&
          hand_token_v2_parse(skeleton_roundtrip, skeleton_n, &skeleton_got) &&
          hand_token_v2_serialize(&skeleton_got, malformed, sizeof(malformed)) == skeleton_n &&
          memcmp(malformed, skeleton_roundtrip, skeleton_n) == 0,
          "W-last skeleton canonicalization reaches a byte-stable fixed point");

    uint8_t skeleton_wfirst[HAND_TOKEN_V2_MAX_FRAME_SIZE];
    skeleton_token.caps = HAND_TOKEN_CAP_HAS_SKELETON;
    skeleton_token.skeleton.quat[1][0] = 2.0f;
    CHECK(hand_token_v2_serialize(&skeleton_token, skeleton_wfirst, sizeof(skeleton_wfirst)) == skeleton_n &&
          hand_token_v2_parse(skeleton_wfirst, skeleton_n, &skeleton_got) &&
          hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                  sizeof(skeleton_roundtrip)) == skeleton_n &&
          memcmp(skeleton_roundtrip, skeleton_wfirst, skeleton_n) == 0,
          "W-first canonical base and skeleton quaternions are byte-stable");

    memcpy(malformed, skeleton_wfirst, skeleton_n);
    put_u16_le(&malformed[21], 0x4000u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "parser accepts finite non-unit base wrist quaternion (W-first)");
    CHECK(hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                  sizeof(skeleton_roundtrip)) == skeleton_n &&
          memcmp(skeleton_roundtrip, malformed, skeleton_n) != 0 &&
          hand_token_v2_parse(skeleton_roundtrip, skeleton_n, &skeleton_got) &&
          hand_token_v2_serialize(&skeleton_got, malformed, sizeof(malformed)) == skeleton_n &&
          memcmp(malformed, skeleton_roundtrip, skeleton_n) == 0,
          "W-first base wrist canonicalization reaches a byte-stable fixed point");

    memcpy(malformed, skeleton_wfirst, skeleton_n);
    put_u16_le(&malformed[83], 0x4000u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "parser accepts finite non-unit skeleton quaternion (W-first)");
    CHECK(hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                  sizeof(skeleton_roundtrip)) == skeleton_n &&
          memcmp(skeleton_roundtrip, malformed, skeleton_n) != 0 &&
          hand_token_v2_parse(skeleton_roundtrip, skeleton_n, &skeleton_got) &&
          hand_token_v2_serialize(&skeleton_got, malformed, sizeof(malformed)) == skeleton_n &&
          memcmp(malformed, skeleton_roundtrip, skeleton_n) == 0,
          "W-first skeleton canonicalization reaches a byte-stable fixed point");
    skeleton_token.caps = HAND_TOKEN_CAP_HAS_SKELETON | HAND_TOKEN_CAP_QUAT_WLAST;

    /* Multi-component, rounding-sensitive non-unit input across both wire orders
     * and both quaternion-bearing regions; verify canonical bytes are fixed. */
    static const float rounding_quat[4] = {0.3123f, -0.4711f, 0.5837f, 0.6919f};
    for (int w_last = 0; w_last <= 1; ++w_last) {
        for (int target = 0; target <= 1; ++target) {
            skeleton_token.caps = HAND_TOKEN_CAP_HAS_SKELETON |
                                  (w_last ? HAND_TOKEN_CAP_QUAT_WLAST : 0);
            if (target == 0) {
                memcpy(skeleton_token.base.quat, rounding_quat,
                       sizeof(rounding_quat));
            } else {
                memcpy(skeleton_token.skeleton.quat[1], rounding_quat,
                       sizeof(rounding_quat));
            }
            size_t rounding_n = hand_token_v2_serialize(&skeleton_token, malformed,
                                                         sizeof(malformed));
            CHECK(rounding_n == skeleton_n &&
                  hand_token_v2_parse(malformed, rounding_n, &skeleton_got) &&
                  hand_token_v2_serialize(&skeleton_got, skeleton_roundtrip,
                                          sizeof(skeleton_roundtrip)) == rounding_n &&
                  hand_token_v2_parse(skeleton_roundtrip, rounding_n, &skeleton_got) &&
                  hand_token_v2_serialize(&skeleton_got, malformed,
                                          sizeof(malformed)) == rounding_n &&
                  memcmp(malformed, skeleton_roundtrip, rounding_n) == 0,
                  "multi-component quaternion canonical bytes are fixed");
        }
    }
    skeleton_token.caps = HAND_TOKEN_CAP_HAS_SKELETON | HAND_TOKEN_CAP_QUAT_WLAST;
    put_u16_le(&malformed[21], 0x7C00u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "W-last parser rejects NaN base wrist quaternion");
    memcpy(malformed, skeleton_frame, skeleton_n);
    memset(&malformed[21], 0, 8);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "W-last parser rejects zero base wrist quaternion");

    memcpy(malformed, skeleton_wfirst, skeleton_n);
    put_u16_le(&malformed[21], 0x7C00u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "W-first parser rejects NaN base wrist quaternion");
    memcpy(malformed, skeleton_wfirst, skeleton_n);
    memset(&malformed[21], 0, 8);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "W-first parser rejects zero base wrist quaternion");

    memcpy(malformed, skeleton_frame, skeleton_n);
    malformed[HAND_TOKEN_V2_OFF_CAPS] &= (uint8_t)~HAND_TOKEN_CAP_HAS_SKELETON;
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "skeleton TLVs without HAS_SKELETON are rejected");

    memcpy(malformed, v2_frame, v2_n);
    malformed[HAND_TOKEN_V2_OFF_CAPS] = HAND_TOKEN_CAP_HAS_SKELETON;
    refresh_v2_crc(malformed, v2_n);
    CHECK(!hand_token_v2_parse(malformed, v2_n, &skeleton_got),
          "HAS_SKELETON without required TLVs is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    malformed[243] = HAND_TOKEN_TLV_SKELETON_QUAT20;
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "duplicate required skeleton TLV is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    put_u16_le(&malformed[81], 159);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "wrong required skeleton TLV length is rejected");

    CHECK(!hand_token_v2_parse(skeleton_frame, skeleton_n - 1, &skeleton_got),
          "truncated skeleton TLV frame is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    put_u16_le(&malformed[83], 0x7C00u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "nonfinite skeleton quaternion is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    memset(&malformed[83], 0, 8);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "zero skeleton quaternion is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    put_u16_le(&malformed[246], 0x3C00u);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "nonzero skeleton wrist offset is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    put_u16_le(&malformed[401], 0);
    refresh_v2_crc(malformed, skeleton_n);
    CHECK(!hand_token_v2_parse(malformed, skeleton_n, &skeleton_got),
          "zero rest model revision is rejected");

    memcpy(malformed, skeleton_frame, skeleton_n);
    memmove(&malformed[247], &malformed[243], skeleton_n - 243);
    malformed[243] = 0x7Fu;
    put_u16_le(&malformed[244], 1);
    malformed[246] = 0xA5u;
    size_t unknown_tlv_n = skeleton_n + 4;
    put_u16_le(&malformed[HAND_TOKEN_V2_OFF_TOTAL_LEN], (uint16_t)unknown_tlv_n);
    refresh_v2_crc(malformed, unknown_tlv_n);
    CHECK(hand_token_v2_parse(malformed, unknown_tlv_n, &skeleton_got) &&
          skeleton_got.has_skeleton && skeleton_got.skeleton.revision == 1,
          "unknown bounded TLV is skipped without losing skeleton data");

    skeleton_token.skeleton.revision = 0;
    CHECK(hand_token_v2_serialize(&skeleton_token, skeleton_frame, sizeof(skeleton_frame)) == 0,
          "serializer rejects zero rest model revision");
    skeleton_token.skeleton.revision = 1;
    skeleton_token.skeleton.offsets[0][0] = 0.25f;
    CHECK(hand_token_v2_serialize(&skeleton_token, skeleton_frame, sizeof(skeleton_frame)) == 0,
          "serializer rejects nonzero wrist offset");
    skeleton_token.skeleton.offsets[0][0] = 0.0f;
    skeleton_token.skeleton.offsets[1][0] = INFINITY;
    CHECK(hand_token_v2_serialize(&skeleton_token, skeleton_frame, sizeof(skeleton_frame)) == 0,
          "serializer rejects offsets that cannot be represented as finite f16");
    skeleton_token.skeleton.offsets[1][0] = 0.25f;
    for (int component = 0; component < 4; ++component) {
        skeleton_token.skeleton.quat[1][component] = 1.0e-20f;
    }
    CHECK(hand_token_v2_serialize(&skeleton_token, skeleton_frame, sizeof(skeleton_frame)) != 0,
          "serializer accepts finite non-unit quaternion input");

    /* 10) 金标向量: 打印 + (若已填) 断言 */
    print_hex("GOLDEN=", frame, n);
    size_t glen = strlen(GOLDEN_HEX);
    int golden_filled = (glen == (size_t)(HAND_TOKEN_FRAME_SIZE * 2)) &&
                        (strspn(GOLDEN_HEX, "0123456789abcdefABCDEF") == glen);
    if (golden_filled) {
        char hex[HAND_TOKEN_FRAME_SIZE * 2 + 1];
        for (size_t i = 0; i < n; ++i) sprintf(&hex[i * 2], "%02x", frame[i]);
        CHECK(strcmp(hex, GOLDEN_HEX) == 0, "frame matches GOLDEN_HEX (cross-lang contract)");
    } else {
        printf("  [note] GOLDEN_HEX 未填/占位, 跳过金标断言 (首轮用上面 GOLDEN= 填入)\n");
    }

    printf("== %s ==\n", g_fail ? "FAILED" : "ALL PASS");
    return g_fail ? 1 : 0;
}
