/*
 * hand_token.h — EchoGlove/EgoGlove V7 Hand Token v1 (跨产品线横切合同, D3)
 *
 * Hand Token 是双表示层 (STRATEGY.md D3) 的统一中间表示: 同一硬件传感器流
 * 归一化为 Hand Token, 再分叉为 MANO Layer (数字人侧) 与 Robot Action Layer
 * (机器人侧)。本协议是 Lite (ESP32-S3) 与 Pro (ESP32-P4) 共享的自描述、
 * 传输无关 (UART / ESP-NOW / BLE / USB-CDC / WiFi-UDP 均可承载) 的二进制帧。
 *
 * 设计约定 (与 V6 glove_firmware/shared/uart_frame.h 一致):
 *   - 小端序 (ESP32 与 x86 均为 LE, 双端无需字节交换)
 *   - CRC-16/MODBUS (poly 0xA001, init 0xFFFF), 帧尾小端存储 (L, H)
 *   - float16 (IEEE754 half) 压缩多数浮点字段; 腕位姿用 float32 保精度
 *
 * 真实性 (docs/V7/ARCHITECTURE.md §8):
 *   - 协议 serialize/parse/CRC: ✅ (host 单测验证, firmware/shared/test/)
 *   - Lite: flex ✅ / quat 🟡(IMU驱动待) / wrist·vel·contact·force 填 0
 *   - Pro:  force/contact 🔬 / wrist 🔬(需外部位姿源)
 *
 * 规范全文: docs/V7/07_dual_rep_layer.md
 * 版权/署名: PaxonHuang <quenchkidney@outlook.com>
 */
#ifndef ECHOGLOVE_HAND_TOKEN_H
#define ECHOGLOVE_HAND_TOKEN_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- 协议常量 ---- */
#define HAND_TOKEN_MAGIC0      0x48u   /* 'H' */
#define HAND_TOKEN_MAGIC1      0x54u   /* 'T'  → magic "HT", 区别于 uart_frame 的 0xAA55 */
#define HAND_TOKEN_VERSION     0x01u
#define HAND_TOKEN_FRAME_SIZE  79u     /* 固定帧长 (含 magic..crc) */

/* device_id 位域: bit7 product | bit6 hand | bits5-0 serial(0..63) */
#define HAND_TOKEN_PRODUCT_LITE 0u
#define HAND_TOKEN_PRODUCT_PRO  1u
#define HAND_TOKEN_HAND_LEFT    0u
#define HAND_TOKEN_HAND_RIGHT   1u

/*
 * 内存态结构 (float32, 便于上层使用)。序列化时按 canonical 布局压缩。
 * Lite 未采集字段应置 0 (由生产端保证), 协议本身不区分产品线语义。
 */
typedef struct {
    uint8_t  product;         /* 0=Lite, 1=Pro */
    uint8_t  hand;            /* 0=Left, 1=Right */
    uint8_t  serial;         /* 0..63 设备序号 */
    uint32_t timestamp_us;    /* 单调微秒时戳 (~71min 回绕, 由 relay 处理) */
    float    flex[5];         /* 指间关节角, 归一化 0..1 (拇->小) */
    float    quat[4];         /* 手掌姿态四元数 w,x,y,z (SFLP) */
    float    wrist_6dof[6];   /* 腕世界/基座位姿 x,y,z,roll,pitch,yaw (Lite=0) */
    float    vel[3];          /* 线速度 (无源则 0) */
    float    acc[3];          /* 线加速度 (IMU) */
    uint8_t  contact[5];      /* 指尖接触布尔 0/1 (Lite=0) */
    float    force[5];        /* 指尖力估计 N (Lite=0) */
} hand_token_t;

/* ---- Canonical 布局偏移 (字节), 供文档/交叉实现核对 ---- */
enum {
    HAND_TOKEN_OFF_MAGIC     = 0,
    HAND_TOKEN_OFF_VERSION   = 2,
    HAND_TOKEN_OFF_DEVICE_ID = 3,
    HAND_TOKEN_OFF_TIMESTAMP = 4,
    HAND_TOKEN_OFF_FLEX      = 8,   /* 5 x f16 */
    HAND_TOKEN_OFF_QUAT      = 18,  /* 4 x f16 */
    HAND_TOKEN_OFF_WRIST     = 26,  /* 6 x f32 */
    HAND_TOKEN_OFF_VEL       = 50,  /* 3 x f16 */
    HAND_TOKEN_OFF_ACC       = 56,  /* 3 x f16 */
    HAND_TOKEN_OFF_CONTACT   = 62,  /* 5 x u8  */
    HAND_TOKEN_OFF_FORCE     = 67,  /* 5 x f16 */
    HAND_TOKEN_OFF_CRC       = 77   /* u16 LE  */
};

/* ---- device_id 编解码 ---- */
uint8_t hand_token_make_device_id(uint8_t product, uint8_t hand, uint8_t serial);
void    hand_token_split_device_id(uint8_t id, uint8_t *product, uint8_t *hand, uint8_t *serial);

/* ---- CRC-16/MODBUS (与 uart_frame 同算法) ---- */
uint16_t hand_token_crc16(const uint8_t *buf, size_t n);

/*
 * 序列化 hand_token_t → 定长 79B 帧。
 * buf 至少 HAND_TOKEN_FRAME_SIZE 字节。返回写入字节数 (79) 或 0 (参数非法)。
 */
size_t hand_token_serialize(const hand_token_t *t, uint8_t *buf, size_t buflen);

/*
 * 解析 79B 帧 → hand_token_t。校验 magic/version/长度/CRC。
 * 成功返回 true 并填充 *out; 失败 (帧非法或 CRC 不符) 返回 false。
 */
bool hand_token_parse(const uint8_t *buf, size_t n, hand_token_t *out);

/* ---- float16 <-> float32 (供交叉实现/测试核对) ---- */
uint16_t hand_token_f32_to_f16(float f);
float    hand_token_f16_to_f32(uint16_t h);

#ifdef __cplusplus
}
#endif

#endif /* ECHOGLOVE_HAND_TOKEN_H */
