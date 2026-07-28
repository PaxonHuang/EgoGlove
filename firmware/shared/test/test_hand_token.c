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

    /* 8) 金标向量: 打印 + (若已填) 断言 */
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
