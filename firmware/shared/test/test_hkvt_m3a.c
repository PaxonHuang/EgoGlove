/*
 * test_hkvt_m3a.c — HKVT-M3A 驱动 host 单测 (Layer 1: 纯 C, 无硬件)
 *
 * 覆盖 handoff 第十八节 18 项:
 *   1. little-endian decoding
 *   2. signed int16 decoding
 *   3. 6-byte XYZ frame
 *   4. command constant = 0x03
 *   5. address command = 0x1A
 *   6. default address = 0x0A
 *   7. reject address 0x00
 *   8. reject address 0xFF
 *   9. accept valid 7-bit address
 *  10. zero_offset calibration
 *  11. K conversion to physical force
 *  12. startup state machine
 *  13. no command before startup stabilization period
 *  14. short-read handling
 *  15. I2C error handling
 *  16. sequence number presence
 *  17. timestamp presence
 *  18. raw/derived separation
 *
 * ⚠ 这些单测只证明软件行为, 不证明 0x03/0x1A 真机有效、200Hz、sync_error<1ms、
 *   NACK+STOP 真机行为 — 这些留给 hardware validation (Phase 2/3).
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hkvt_m3a.h"

/* ---- stub transport ---- */
typedef struct {
    uint8_t  force_buf[6];   /* 返回给 read_force 的数据 */
    bool     force_ok;        /* false → 模拟 I2C 错误 */
    uint8_t  force_len;      /* 返回字节数 (<6 → short-read 模拟) */
    uint32_t now_ms;         /* 注入时钟 */
    uint8_t  last_new_addr;  /* set_address 记录 */
    int      n_read_force;
    int      n_set_addr;
} stub_t;

static bool stub_read_force(uint8_t addr, uint8_t *buf, uint8_t len, void *ctx) {
    (void)addr;
    stub_t *s = (stub_t*)ctx;
    s->n_read_force++;
    if (!s->force_ok) return false;
    uint8_t n = s->force_len < len ? s->force_len : len;
    memcpy(buf, s->force_buf, n);
    /* 末字节 NACK+STOP 行为由真机 adapter 保证; 此处 stub 仅给数据 */
    return n == len;   /* short-read → false */
}

static bool stub_read_temp(uint8_t addr, uint8_t *buf, uint8_t len, void *ctx) {
    (void)addr; (void)buf; (void)len; (void)ctx;
    return true;
}

static bool stub_set_address(uint8_t old_addr, uint8_t new_addr, void *ctx) {
    (void)old_addr;
    stub_t *s = (stub_t*)ctx;
    s->last_new_addr = new_addr;
    s->n_set_addr++;
    return true;
}

static uint32_t stub_now_ms(void *ctx) { return ((stub_t*)ctx)->now_ms; }

static hkvt_transport_t stub_transport = {
    stub_read_force, stub_read_temp, stub_set_address, stub_now_ms
};

static void init_stub(stub_t *s) {
    memset(s, 0, sizeof(*s));
    s->force_ok  = true;
    s->force_len = 6;
    s->now_ms    = 0;
}

/* ==================================================================== */

/* 1 & 2: little-endian + signed int16 */
static void test_decode_i16_le(void) {
    uint8_t a[2] = {0x34, 0x12};  /* 0x1234 = +4660 */
    uint8_t b[2] = {0x00, 0x80};  /* 0x8000 = -32768 */
    uint8_t c[2] = {0xFF, 0xFF};  /* 0xFFFF = -1 */
    uint8_t d[2] = {0x01, 0x00};  /* +1 */
    assert(hkvt_decode_i16(a) == 4660);
    assert(hkvt_decode_i16(b) == -32768);
    assert(hkvt_decode_i16(c) == -1);
    assert(hkvt_decode_i16(d) == 1);
}

/* 3: 6-byte XYZ frame */
static void test_parse_xyz_frame(void) {
    uint8_t buf[6] = {0xE8,0x03, 0x0C,0xFE, 0x64,0x00};
    /* X = 0x03E8 = 1000, Y = 0xFE0C = -500 (LE: 0x0C,0xFE), Z = 0x0064 = 100 */
    hkvt_m3a_raw_t r;
    assert(hkvt_parse_xyz(buf, 6, &r));
    assert(r.force_x_raw == 1000);
    assert(r.force_y_raw == -500);
    assert(r.force_z_raw == 100);
}

/* 4: read-force command = 0x03 */
static void test_cmd_read_force_is_0x03(void) {
    assert(HKVT_REG_READ_FORCE == 0x03);
    assert(HKVT_REG_READ_FORCE != 0x01);   /* 废弃值 */
}

/* 5: address command = 0x1A */
static void test_cmd_set_address_is_0x1A(void) {
    assert(HKVT_REG_SET_ADDRESS == 0x1A);
    assert(HKVT_REG_SET_ADDRESS != 0x04);   /* 废弃值 */
}

/* 6: default address = 0x0A */
static void test_default_address(void) {
    assert(HKVT_DEFAULT_I2C_ADDR == 0x0A);
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    assert(d.addr == 0x0A);
}

/* 7: reject 0x00 */
static void test_reject_addr_0x00(void) {
    assert(!hkvt_validate_address(0x00));
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(!hkvt_m3a_init(&d, &stub_transport, &s, 0x00, NULL));
}

/* 8: reject 0xFF */
static void test_reject_addr_0xFF(void) {
    assert(!hkvt_validate_address(0xFF));
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(!hkvt_m3a_init(&d, &stub_transport, &s, 0xFF, NULL));
}

/* 9: accept valid 7-bit */
static void test_accept_valid_7bit(void) {
    assert(hkvt_validate_address(0x0A));
    assert(hkvt_validate_address(0x08));
    assert(hkvt_validate_address(0x77));
    /* 保留段 */
    assert(!hkvt_validate_address(0x07));
    assert(!hkvt_validate_address(0x78));
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(hkvt_m3a_init(&d, &stub_transport, &s, 0x12, NULL));
    assert(d.addr == 0x12);
}

/* 10 & 11: zero_offset + K conversion */
static void test_calibration(void) {
    hkvt_m3a_raw_t raw = {1000, -500, 100};
    hkvt_m3a_calib_t cal = { .zero_offset = {100, 0, 50}, .k = {0.001f, 0.002f, 0.005f} };
    hkvt_m3a_force_t f;
    hkvt_apply_calibration(&raw, &cal, &f);
    /* x: 0.001*(1000-100) = 0.9 N */
    /* y: 0.002*(-500-0)  = -1.0 N */
    /* z: 0.005*(100-50)   = 0.25 N */
    assert(f.force_x_n > 0.899f && f.force_x_n < 0.901f);
    assert(f.force_y_n > -1.001f && f.force_y_n < -0.999f);
    assert(f.force_z_n > 0.249f && f.force_z_n < 0.251f);
}

/* 12: startup state machine — 进入 READY 后才能读 */
static void test_startup_state_machine(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    s.force_buf[0] = 0xE8; s.force_buf[1] = 0x03;  /* X=1000 */
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    assert(d.state == HKVT_STATE_BOOT);   /* init 即 BOOT, 等稳定期 */

    hkvt_m3a_sample_t samp;
    s.now_ms = 0;   /* 稳定期内 (< 1000ms) */
    assert(!hkvt_m3a_read(&d, &samp));
    assert(d.state == HKVT_STATE_BOOT);

    s.now_ms = 500;  /* 仍 < 1000ms */
    assert(!hkvt_m3a_read(&d, &samp));
    assert(d.state == HKVT_STATE_BOOT);

    s.now_ms = 1001;  /* >= 1000ms → READY */
    assert(hkvt_m3a_read(&d, &samp));
    assert(d.state == HKVT_STATE_READY);
}

/* 13: no command before stabilization — set_address 也被拦 */
static void test_no_cmd_before_stabilize(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    s.now_ms = 100;  /* 稳定期内 */
    assert(!hkvt_m3a_set_address(&d, 0x12));
    assert(s.n_set_addr == 0);   /* transport 未被调用 */
    s.now_ms = 1001;
    assert(hkvt_m3a_set_address(&d, 0x12));
    assert(s.n_set_addr == 1);
    assert(s.last_new_addr == 0x12);
    assert(d.addr == 0x12);
}

/* 14: short-read handling */
static void test_short_read(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    s.now_ms = 1001;
    s.force_len = 3;   /* 只返回 3 字节 */
    hkvt_m3a_sample_t samp;
    assert(!hkvt_m3a_read(&d, &samp));   /* short-read → false */
    assert(!d.ok);
}

/* 15: I2C error handling */
static void test_i2c_error(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    s.now_ms = 1001;
    s.force_ok = false;   /* 模拟 NACK/总线错误 */
    hkvt_m3a_sample_t samp;
    assert(!hkvt_m3a_read(&d, &samp));
    assert(!d.ok);
    /* 恢复后可继续读 */
    s.force_ok = true; s.force_len = 6;
    assert(hkvt_m3a_read(&d, &samp));
    assert(d.ok);
}

/* 16 & 17: sequence + timestamp presence */
static void test_seq_and_timestamp(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    s.force_buf[0] = 0x64; s.force_buf[1] = 0x00;  /* X=100 */
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    s.now_ms = 1500;
    hkvt_m3a_sample_t a, b;
    assert(hkvt_m3a_read(&d, &a));
    assert(hkvt_m3a_read(&d, &b));
    assert(b.seq == a.seq + 1);            /* seq 独立递增 */
    assert(a.timestamp_us == 1500u * 1000u); /* timestamp 存在且来自 MCU clock */
    assert(b.timestamp_us >= a.timestamp_us);
    assert(a.sensor_id == 0x0A);
}

/* 18: raw / derived separation — raw 是未校准 ADC, derived 是 N */
static void test_raw_derived_separation(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    /* raw X = 1100, 零点 100 → 偏移后 1000, K=0.001 → 1.0 N */
    s.force_buf[0] = 0x4C; s.force_buf[1] = 0x04;  /* 0x044C = 1100 LE */
    hkvt_m3a_calib_t cal = { .zero_offset = {100,0,0}, .k = {0.001f, 0.001f, 0.001f} };
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, &cal));
    s.now_ms = 1500;
    hkvt_m3a_sample_t samp;
    assert(hkvt_m3a_read(&d, &samp));
    /* raw 层: 原始 ADC 计数, 未经校准 */
    assert(samp.raw.force_x_raw == 1100);
    /* derived 层: 校准后物理量 */
    assert(samp.derived.force_x_n > 0.999f && samp.derived.force_x_n < 1.001f);
    /* 两者数值不同, 证明未混淆 */
    assert((float)samp.raw.force_x_raw != samp.derived.force_x_n);
}

/* 附加: set_address 拒绝非法地址 (驱动层防线) */
static void test_set_addr_rejects_illegal(void) {
    hkvt_m3a_t d;
    stub_t s; init_stub(&s);
    assert(hkvt_m3a_init(&d, &stub_transport, &s, HKVT_DEFAULT_I2C_ADDR, NULL));
    s.now_ms = 1001;
    assert(!hkvt_m3a_set_address(&d, 0x00));
    assert(!hkvt_m3a_set_address(&d, 0xFF));
    assert(s.n_set_addr == 0);
    assert(d.addr == 0x0A);   /* 未变 */
}

int main(void) {
    test_decode_i16_le();
    test_parse_xyz_frame();
    test_cmd_read_force_is_0x03();
    test_cmd_set_address_is_0x1A();
    test_default_address();
    test_reject_addr_0x00();
    test_reject_addr_0xFF();
    test_accept_valid_7bit();
    test_calibration();
    test_startup_state_machine();
    test_no_cmd_before_stabilize();
    test_short_read();
    test_i2c_error();
    test_seq_and_timestamp();
    test_raw_derived_separation();
    test_set_addr_rejects_illegal();
    printf("HKVT-M3A: all tests PASS\n");
    return 0;
}
