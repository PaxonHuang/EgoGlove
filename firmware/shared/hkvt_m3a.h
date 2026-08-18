/*
 * hkvt_m3a.h — HKVT-M3A 指尖触觉传感器驱动 (Demo1 Phase 1A)
 *
 * 传感器: Suzhou Hangkai Microelectronics HKVT-M3A
 *   - 3-axis force (Fx/Fy 切向 ±10N, Fz 法向 0~15N), ±2%FS
 *   - ODR 200Hz, I2C 400kHz, 默认 7-bit 地址 0x0A
 *   - 输出原始 ADC int16 小端, 6 字节 XYZ
 *   - 上电零点自校准 ≈1s (期间禁止 I2C 命令)
 *   - 无 documented sensor-side timestamp / DRDY pin → 用 MCU clock
 *
 * 分层 (与 LSM6DSV16X 一致, protocol 与 ESP-IDF I2C 解耦):
 *   hkvt_m3a_protocol  (本文件 + .c, 纯 C, 无 HAL)
 *       ↓
 *   hkvt_m3a_driver    (state machine + calibration, 本文件)
 *       ↓
 *   esp-idf_i2c_adapter (Phase 2, 真实硬件; adapter 实现 hkvt_transport_t)
 *       ↓
 *   application/acquisition task
 *
 * opcode 现状 (datasheet §3, 2026-08-17 修订):
 *   READ_FORCE  = 0x03   (早期错误版本 0x01, 已废弃)
 *   SET_ADDRESS = 0x1A   (早期错误版本 0x04, 已废弃)
 *   READ_TEMP   = 0x13
 *   ⚠ opcode 正确性最终须经真实硬件实测 (NOT HARDWARE VERIFIED)
 *
 * 真实性:
 *   - 协议解析/地址校验/状态机/校准: ✅ host 单测 (本层)
 *   - 0x03/0x1A 真机有效: 🔬 待 hardware validation
 *   - 200Hz 真机行为 / NACK+STOP 真机 / sync_error: 🔬 待 hardware validation
 *
 * 规范: datasheet/HKVT-M3A_Datasheet_v1.0.md
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#ifndef ECHOGLOVE_HKVT_M3A_H
#define ECHOGLOVE_HKVT_M3A_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- 协议常量 (datasheet §3) ---- */
#define HKVT_DEFAULT_I2C_ADDR   0x0Au   /* 7-bit 默认地址 (8-bit W=0x14, R=0x15) */
#define HKVT_REG_READ_FORCE     0x03u   /* 读 3 轴力, 6 字节 XYZ (datasheet §3.2) */
#define HKVT_REG_READ_TEMP      0x13u   /* 读温度/状态, 2 字节 (datasheet §3.4) */
#define HKVT_REG_SET_ADDRESS    0x1Au   /* 修改 I2C 从机地址 (datasheet §3.3) */

/* 非法地址 (datasheet §3.3 安全约束) */
#define HKVT_ADDR_ILLEGAL_LOW   0x00u   /* 广播地址, 禁用 */
#define HKVT_ADDR_ILLEGAL_HIGH  0xFFu   /* 禁用 */

/* 7-bit 地址有效范围 */
#define HKVT_ADDR_MIN           0x08u   /* 0x00-0x07 为 I2C 保留 */
#define HKVT_ADDR_MAX           0x77u

/* 帧长 */
#define HKVT_FORCE_FRAME_BYTES   6u      /* X_L,X_H,Y_L,Y_H,Z_L,Z_H */
#define HKVT_TEMP_FRAME_BYTES    2u

/* 上电零点自校准稳定期 (datasheet §4.1: 至少 1000ms) */
#define HKVT_BOOT_STABILIZE_MS   1000u

/* 驱动状态机 */
typedef enum {
    HKVT_STATE_RESET = 0,      /* 上电未初始化 */
    HKVT_STATE_BOOT,           /* 等待上电稳定期 (≥1s) */
    HKVT_STATE_READY,          /* 可读 */
} hkvt_state_t;

/* 6 字节原始力帧 (int16 小端, 3 轴) */
typedef struct {
    int16_t force_x_raw;
    int16_t force_y_raw;
    int16_t force_z_raw;
} hkvt_m3a_raw_t;

/* 校准后的物理量 (N) — derived 层, 不与 raw 混淆 */
typedef struct {
    float force_x_n;
    float force_y_n;
    float force_z_n;
} hkvt_m3a_force_t;

/* 零点偏置 + 系数矩阵 K (N/LSB), 用户端 Load Cell 标定获得 (datasheet §4.3) */
typedef struct {
    int16_t zero_offset[3];    /* x,y,z raw 零点 */
    float   k[3];              /* x,y,z N/LSB */
} hkvt_m3a_calib_t;

/*
 * 传输抽象 (transport-injected, 与 LSM6DSV16X imu_transport_t 同模式)。
 * host 单测注入 stub; 真机由 esp-idf_i2c_adapter 实现。
 *
 * read_force: 写 [0x03] + repeated-start + 读 6 字节;
 *             末字节 Z_H 后必须 master NACK + STOP (datasheet §4.2)。
 *             返回 false 表示 I2C 错误 (NACK/总线错误/short-read)。
 *             实现负责保证 len==6, 否则返回 false。
 */
typedef struct {
    bool (*read_force)(uint8_t addr, uint8_t *buf, uint8_t len, void *ctx);
    bool (*read_temp)(uint8_t addr, uint8_t *buf, uint8_t len, void *ctx);
    bool (*set_address)(uint8_t old_addr, uint8_t new_addr, void *ctx);
    /* now_ms: 注入 MCU 时钟, 用于上电稳定期判定 (单测可控) */
    uint32_t (*now_ms)(void *ctx);
} hkvt_transport_t;

/* 采样结构: raw + derived 严格分离 + seq + timestamp (metadata) */
typedef struct {
    uint8_t           sensor_id;
    hkvt_m3a_raw_t    raw;            /* raw 层: 未经校准的 ADC 计数 */
    hkvt_m3a_force_t  derived;        /* derived 层: 校准后物理量 (N) */
    uint32_t          seq;            /* metadata: 本 sensor 独立序号 */
    uint32_t          timestamp_us;  /* metadata: MCU free-running clock */
    uint8_t           quality_flags; /* metadata: 0=ok, bit0=short-read, bit1=i2c-err-recovered */
} hkvt_m3a_sample_t;

/* 驱动句柄 */
typedef struct {
    hkvt_transport_t  t;
    void             *ctx;
    uint8_t           addr;           /* 当前 7-bit 地址 */
    hkvt_m3a_calib_t  calib;
    hkvt_state_t      state;
    uint32_t          boot_start_ms;  /* 进入 BOOT 态的时刻 */
    uint32_t          seq;            /* 独立 seq 计数 */
    bool              ok;
} hkvt_m3a_t;

/* ---- 纯逻辑层 (无 HAL 依赖, host 单测目标) ---- */

/* 小端 int16 解码 (datasheet §4.3) */
int16_t hkvt_decode_i16(const uint8_t raw[2]);

/* 解析 6 字节 XYZ 原始帧 */
bool hkvt_parse_xyz(const uint8_t *buf, uint8_t len, hkvt_m3a_raw_t *out);

/* 地址校验: 拒绝 0x00/0xFF, 拒绝保留段, 接受有效 7-bit */
bool hkvt_validate_address(uint8_t addr7);

/* 校准: F_calibrated = K_i * (F_raw - zero_offset_i) */
void hkvt_apply_calibration(const hkvt_m3a_raw_t *raw,
                            const hkvt_m3a_calib_t *cal,
                            hkvt_m3a_force_t *out);

/* 状态机推进: 上电→BOOT→READY。now_ms 注入, 单测可控 */
bool hkvt_state_step(hkvt_m3a_t *d);

/* ---- driver API ---- */

/* 初始化: addr 必须是有效 7-bit 地址 (用 HKVT_DEFAULT_I2C_ADDR 走默认);
 * 拒绝 0x00/0xFF/保留段. calib 可为 NULL (用单位默认). */
bool hkvt_m3a_init(hkvt_m3a_t *d, const hkvt_transport_t *t, void *ctx,
                   uint8_t addr, const hkvt_m3a_calib_t *calib);

/* 读取一次力: 成功填 sample (raw + derived + seq + timestamp) */
bool hkvt_m3a_read(hkvt_m3a_t *d, hkvt_m3a_sample_t *out);

/* 修改从机地址 (datasheet §3.3, 写后持久 Flash) */
bool hkvt_m3a_set_address(hkvt_m3a_t *d, uint8_t new_addr7);

#ifdef __cplusplus
}
#endif
#endif /* ECHOGLOVE_HKVT_M3A_H */
