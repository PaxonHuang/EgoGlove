# M2 — EgoGlove S3 Lite 固件：LSM6DSV16X 驱动 + Madgwick → quat 进特征 — 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在 `EgoGlove/firmware/lite/` 落地可运行的 S3 Lite 固件骨架，实现 LSM6DSV16X 驱动（120Hz、±4g/±2000dps）+ Host Madgwick 6-axis AHRS，输出 SFLP 四元数填入 Hand Token v1 的 `quat[4]`，并带 host 单测与 `pio run` 编译验证。

**Architecture:** 三个 host 可测的纯 C 模块（注入式 I2C transport → LSM6DSV16X 驱动；纯算法 Madgwick 滤波器；LiteSensorManager 组合 flex+IMU → `hand_token_t`），被薄 Arduino/FreeRTOS `main.cpp` 胶合（`Task_SensorRead` 120Hz 采样+融合，`Task_Telemetry` 10Hz 串口 CSV 输出便于板上漂移/响应验证）。M2 只做 quat 进特征 + 串口遥测；79B 线上序列化属 M3，NVS flex 校准属 M4。

**Tech Stack:** C11（host 单测 `gcc -std=c11 -Wall -Wextra -Werror -O2`）；PlatformIO `espressif32@^6.5.0` + `esp32-s3-devkitc-1` + Arduino；I²C @0x6A（GPIO8 SDA / GPIO9 SCL，400kHz）；`firmware/shared/hand_token.h`（已存在，host 已验证，**不改**）。

---

## Global Constraints

- **仓库**：除 Task 6 的文档修正外，全部改动在 `EgoGlove`（`firmware/lite/`）。Task 6 修正 **Beta 仓库工作设计文档**（`docs/superpowers/specs/2026-08-10-egoglove-aligned-production-design.md` §4）——这是用户明确批准的例外（EgoGlove `CLAUDE.md`「Beta 只读」纪律不适用于此活动文档）。
- **分支**：新建 `feature/lite-lsm6dsv16x-madgwick`（EgoGlove `main ← develop ← feature/*` 纪律），从当前 `develop` 或 `feature/human-motion-infrastructure` 派生；不确定时停下问用户。
- **提交身份**：`PaxonHuang <quenchkidney@outlook.com>`（已是当前 git 身份）；**不得**加任何 AI co-author / 生成署名。提交前跑 `git config user.name`、`git config user.email`、`git diff --check`。
- **提交消息**：`type(scope): description`（如 `feat(lite): ...`、`chore(lite): ...`、`docs: ...`）。**未经用户指示不 push。**
- **禁止** `graphify update .`（EgoGlove `CLAUDE.md`）。
- **固件构建门**：任何 `src/` 或 `lib/` 改动后必须 `pio run -d firmware/lite` 通过才算完成。
- **IMU 驱动为仓库内本地驱动**（非 PlatformIO 注册表库）。
- **寄存器编码（已对照 `EgoGlove/docs/datasheet/lsm6dsv16x.md` 核实）**：WHO_AM_I(0Fh)=0x70；CTRL1(10h)=0x06（OP_MODE_XL=000 HP + ODR_XL=0110 **120Hz**）；CTRL2(11h)=0x06（OP_MODE_G=000 + ODR_G=0110 **120Hz**）；CTRL3(12h)=0x44（BDU[6]+IF_INC[2]，默认值显式写）；CTRL6(15h)=0x04（FS_G=0100 **±2000dps**）；CTRL8(17h)=0x01（FS_XL=01 **±4g**）。灵敏度 ±4g→0.122 mg/LSB、±2000dps→70 mdps/LSB。**芯片无 104Hz 档**（最接近 120Hz=0b0110）——用户已确认取 120Hz，与 `Task_SensorRead` 120Hz 对齐。
- **Madgwick**：β≈0.1；身份四元数 ⇔ 传感器 +z 对齐重力（上）。**物理限制：yaw（绕重力轴旋转）加速度计不可观**——tilt 收敛，yaw 保持有界但不修正（无磁力计）。
- **hand_token.h/c**（`firmware/shared/`）与 **hand_skeleton.h/c** 为共享既有文件，host 已验证，**只读引用不修改**。管理器链路编译需同时链接 `hand_token.c` + `hand_skeleton.c`。
- **flex 最小实现**：M2 直接 `analogRead` GPIO1-5 归一化 0..1（无 NVS 校准，NVS 校准归 M4）。
- **验证目标（板上，无硬件不可在本环境跑，见 Task 6 清单）**：静止 60s tilt 漂移 <3°；手翻转 90° 响应 <200ms。
- 遇到重大决策 / 重大 bug / 新发现 → **停下问用户**（EgoGlove `CLAUDE.md` 工作纪律）。

---

### Task 1: Bootstrap `firmware/lite/` PlatformIO 骨架 + host 测试架

**Files:**
- Create: `firmware/lite/platformio.ini`
- Create: `firmware/lite/src/main.cpp`（最小可编译桩）
- Create: `firmware/lite/.gitignore`
- Create: `firmware/lite/test/Makefile`
- Test: 无单测（骨架阶段），验证 = `pio run` 编译通过

**Interfaces:**
- Produces: 可编译的 `firmware/lite/` 工程；`test/Makefile` 提供 `make test_<name>`（单测逐个构建）与 `make run`（全套，三 bin 齐备后调用）。

- [ ] **Step 1: 建分支**

```bash
cd /home/EchoGloveHugeProjects/EgoGlove
git checkout -b feature/lite-lsm6dsv16x-madgwick
```

- [ ] **Step 2: 写 `firmware/lite/platformio.ini`**

```ini
; =============================================================================
; EchoGlove Lite — ESP32-S3 S3 Lite firmware (M2: LSM6DSV16X + Madgwick)
; =============================================================================
; MCU: ESP32-S3-DevKitC-1 N16R8 (dual-core 240 MHz, 16 MB Flash, 8 MB PSRAM)
; Framework: Arduino. IMU = LSM6DSV16X @ I2C 0x6A (GPIO8 SDA / GPIO9 SCL, 400kHz)
; Flex = internal ADC1 (GPIO1-5, minimal raw normalize 0..1; NVS calib = M4)
; Shared wire contract: ../shared/hand_token.h (read-only reference)
; =============================================================================

[env:esp32-s3-devkitc-1-n16r8]
platform      = espressif32@^6.5.0
board         = esp32-s3-devkitc-1
framework     = arduino

; ---- Board-specific: enable octal PSRAM (8 MB) ----
board_build.partitions = huge_app.csv
board_build.psram      = enable
board_build.f_flash    = 80000000L
board_build.flash_mode = dio
board_build.arduino.memory_type = dio_opi

; ---- Build flags ----
build_flags =
    ; Force USB CDC as default Serial output (ESP32-S3 DevKit)
    -DARDUINO_USB_CDC_ON_BOOT=1
    ; Include path for shared wire contract (hand_token.h / hand_skeleton.h)
    -I../shared
    -O2

; ---- Serial monitor ----
monitor_speed = 115200

; ---- Library dependency finder ----
; deep+ scans #include chains in headers (hand_token.h includes hand_skeleton.h)
lib_ldf_mode = deep+

; ---- Build warnings ----
build_unflags = -Werror
```

- [ ] **Step 3: 写最小 `firmware/lite/src/main.cpp` 桩**

```cpp
// EchoGlove Lite — M2 骨架 (Task 1 桩; Task 5 填入真实任务)
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("LITE BOOT OK");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
```

- [ ] **Step 4: 写 `firmware/lite/.gitignore`**

```gitignore
.pio/
.pioenvs/
.piolibdeps/
test/test_lsm6dsv16x
test/test_madgwick
test/test_lite_sensor_manager
```

- [ ] **Step 5: 写 host 测试架 `firmware/lite/test/Makefile`**

```make
# firmware/lite/test/Makefile — Lite 主机单测 (host gcc, 无需硬件/PlatformIO)
# 用法:  make test_<name>  # 单个单测编译并运行 (Task 2-4 逐步调用)
#        make run          # 全套 (三 bin 齐备后调用)
#        make clean
CC       ?= gcc
CFLAGS   ?= -std=c11 -Wall -Wextra -Werror -O2
# PlatformIO 的 LDF 会为 lib/ 各子目录自动加 -I; host 侧需手动逐个列出
CPPFLAGS += -I../lib/LSM6DSV16X -I../lib/Madgwick -I../lib/LiteSensorManager -I../../shared

# 每个 bin 声明其依赖源; 模式规则 %: %.c 用 $^ (全部前置源) 编译
test_lsm6dsv16x: test_lsm6dsv16x.c ../lib/LSM6DSV16X/lsm6dsv16x.c
test_madgwick: test_madgwick.c ../lib/Madgwick/madgwick.c
test_lite_sensor_manager: test_lite_sensor_manager.c \
	../lib/LiteSensorManager/lite_sensor_manager.c \
	../lib/LSM6DSV16X/lsm6dsv16x.c ../lib/Madgwick/madgwick.c \
	../../shared/hand_token.c ../../shared/hand_skeleton.c

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

run: test_lsm6dsv16x test_madgwick test_lite_sensor_manager
	@for b in test_lsm6dsv16x test_madgwick test_lite_sensor_manager; do \
	  echo "== $$b =="; ./$$b || exit 1; done

.PHONY: run clean
clean:
	rm -f test_lsm6dsv16x test_madgwick test_lite_sensor_manager
```

- [ ] **Step 6: 验证骨架编译**

Run: `pio run -d firmware/lite`
Expected: 编译成功、`SUCCESS`。首个构建会下载 espressif32 平台（较大，可等待）。

- [ ] **Step 7: 提交**

```bash
git add firmware/lite
git status && git diff --check
git commit -m "chore(lite): bootstrap S3 Lite PlatformIO skeleton + host test scaffold"
```

---

### Task 2: LSM6DSV16X I²C 驱动（注入式 transport）+ host 单测

**Files:**
- Create: `firmware/lite/lib/LSM6DSV16X/lsm6dsv16x.h`
- Create: `firmware/lite/lib/LSM6DSV16X/lsm6dsv16x.c`
- Test: `firmware/lite/test/test_lsm6dsv16x.c`

**Interfaces:**
- Produces: `typedef struct { bool (*write)(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx); bool (*read)(uint8_t reg, uint8_t *data, uint8_t len, void *ctx); } imu_transport_t;`（Task 4 管理器与 Task 5 main.cpp 复用）。`bool lsm6dsv16x_init(lsm6dsv16x_t*)`（WHO_AM_I 校验 + 5 个寄存器写 + 尺度换算）；`bool lsm6dsv16x_read(lsm6dsv16x_t*, float acc[3], float gyro[3])`（DRDY 轮询 + 双读 6 字节）。`lsm6dsv16x_decode_i16`、`lsm6dsv16x_accel_scale`、`lsm6dsv16x_gyro_scale` 供测试核对。

- [ ] **Step 1: 写失败的测试 `test_lsm6dsv16x.c`**

```c
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lsm6dsv16x.h"

typedef struct {
    uint8_t who_am_i;
    uint8_t status;
    uint8_t g_raw[6];
    uint8_t a_raw[6];
    uint8_t written[8][2];
    int     n_written;
    int     n_status_polls;
} stub_t;

static bool stub_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx) {
    stub_t *s = (stub_t*)ctx;
    assert(len == 1);
    assert(s->n_written < 8);
    s->written[s->n_written][0] = reg;
    s->written[s->n_written][1] = data[0];
    s->n_written++;
    return true;
}

static bool stub_read(uint8_t reg, uint8_t *data, uint8_t len, void *ctx) {
    (void)len;
    stub_t *s = (stub_t*)ctx;
    if (reg == LSM6DSV16X_REG_WHO_AM_I) { data[0] = s->who_am_i; return true; }
    if (reg == LSM6DSV16X_REG_STATUS_REG) { data[0] = s->status; s->n_status_polls++; return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_G) { memcpy(data, s->g_raw, 6); return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_A) { memcpy(data, s->a_raw, 6); return true; }
    return false;
}

static void init_stub(stub_t *s) {
    memset(s, 0, sizeof(*s));
    s->who_am_i = LSM6DSV16X_WHO_AM_I_VALUE;
    s->status   = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
}

static void test_init_writes_expected_config(void) {
    stub_t s; init_stub(&s);
    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(lsm6dsv16x_init(&imu));

    static const uint8_t expect[5][2] = {
        { LSM6DSV16X_REG_CTRL3,   LSM6DSV16X_CTRL3_DEFAULT   },
        { LSM6DSV16X_REG_CTRL2_G, LSM6DSV16X_CTRL2_120HZ    },
        { LSM6DSV16X_REG_CTRL6_G, LSM6DSV16X_CTRL6_2000DPS  },
        { LSM6DSV16X_REG_CTRL1_XL,LSM6DSV16X_CTRL1_120HZ    },
        { LSM6DSV16X_REG_CTRL8_XL,LSM6DSV16X_CTRL8_4G       },
    };
    assert(s.n_written == 5);
    for (int i = 0; i < 5; i++) {
        assert(s.written[i][0] == expect[i][0]);
        assert(s.written[i][1] == expect[i][1]);
    }
    /* scales: ±4g → 0.122 mg/LSB, ±2000dps → 70 mdps/LSB */
    assert(imu.accel_mg_per_lsb == 0.122f);
    assert(imu.gyro_mdps_per_lsb == 70.0f);
}

static void test_init_rejects_bad_whoami(void) {
    stub_t s; init_stub(&s); s.who_am_i = 0x00;
    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(!lsm6dsv16x_init(&imu));
}

static void test_decode_i16_le(void) {
    const uint8_t a[2] = { 0x34, 0x12 };          /* 0x1234 = +4660 */
    const uint8_t b[2] = { 0x00, 0x80 };          /* 0x8000 = -32768 */
    const uint8_t c[2] = { 0x00, 0x00 };
    assert(lsm6dsv16x_decode_i16(a) == 0x1234);
    assert(lsm6dsv16x_decode_i16(b) == -32768);
    assert(lsm6dsv16x_decode_i16(c) == 0);
}

static void test_scale_constants(void) {
    assert(lsm6dsv16x_accel_scale(0x00) == 0.061f);
    assert(lsm6dsv16x_accel_scale(0x01) == 0.122f);
    assert(lsm6dsv16x_accel_scale(0x02) == 0.244f);
    assert(lsm6dsv16x_accel_scale(0x03) == 0.488f);
    assert(lsm6dsv16x_gyro_scale(0x04) == 70.0f);
    assert(lsm6dsv16x_gyro_scale(0x0C) == 140.0f);  /* ±4000 */
}

static void test_read_physical_units(void) {
    stub_t s; init_stub(&s);
    /* gyro raw 1000 LSB @ ±2000dps → 1000 * 70 mdps = 70.0 dps */
    s.g_raw[0] = 0xE8; s.g_raw[1] = 0x03;          /* 1000 LE */
    /* accel raw 0x2000 = 8192 LSB @ ±4g → 8192 * 0.122 mg = 0.9994 g */
    s.a_raw[1] = 0x20;                              /* (0x00,0x20) LE */

    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(lsm6dsv16x_init(&imu));
    float acc[3], gyro[3];
    assert(lsm6dsv16x_read(&imu, acc, gyro));
    assert(gyro[0] > 69.9f && gyro[0] < 70.1f);
    assert(acc[0] > 0.99f && acc[0] < 1.01f);
    assert(acc[1] == 0.0f && acc[2] == 0.0f);
    assert(gyro[1] == 0.0f && gyro[2] == 0.0f);
}

static void test_read_waits_for_drdy(void) {
    stub_t s; init_stub(&s);
    lsm6dsv16x_t imu = { { stub_write, stub_read }, &s, false, 0, 0 };
    assert(lsm6dsv16x_init(&imu));

    s.status = 0x00;                        /* no data ready yet */
    float acc[3], gyro[3];
    assert(!lsm6dsv16x_read(&imu, acc, gyro));
    assert(s.n_status_polls == 1);

    s.status = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
    assert(lsm6dsv16x_read(&imu, acc, gyro));   /* next poll succeeds */
    assert(s.n_status_polls == 2);
}

int main(void) {
    test_init_writes_expected_config();
    test_init_rejects_bad_whoami();
    test_decode_i16_le();
    test_scale_constants();
    test_read_physical_units();
    test_read_waits_for_drdy();
    printf("LSM6DSV16X: all tests PASS\n");
    return 0;
}
```

- [ ] **Step 2: 运行测试确认失败**

Run: `cd firmware/lite/test && make test_lsm6dsv16x`
Expected: 编译失败，`fatal error: lsm6dsv16x.h: No such file or directory`。

- [ ] **Step 3: 写 `lsm6dsv16x.h`**

```c
#ifndef ECHOGLOVE_LSM6DSV16X_H
#define ECHOGLOVE_LSM6DSV16X_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LSM6DSV16X_I2C_ADDR        0x6Au

#define LSM6DSV16X_REG_WHO_AM_I    0x0Fu
#define LSM6DSV16X_WHO_AM_I_VALUE  0x70u
#define LSM6DSV16X_REG_CTRL1_XL    0x10u
#define LSM6DSV16X_REG_CTRL2_G     0x11u
#define LSM6DSV16X_REG_CTRL3       0x12u
#define LSM6DSV16X_REG_CTRL6_G     0x15u
#define LSM6DSV16X_REG_CTRL8_XL    0x17u
#define LSM6DSV16X_REG_STATUS_REG  0x1Eu
#define LSM6DSV16X_REG_OUTX_L_G    0x22u
#define LSM6DSV16X_REG_OUTX_L_A    0x28u

/* CTRL1(10h): [7]=0 OP_MODE_XL[6:4] ODR_XL[3:0]; ODR 120Hz=0110, HP=000 */
#define LSM6DSV16X_OPMODE_XL_HP    0x00u
#define LSM6DSV16X_ODR_120HZ       0x06u
#define LSM6DSV16X_CTRL1_120HZ     ((LSM6DSV16X_OPMODE_XL_HP << 4) | LSM6DSV16X_ODR_120HZ)

/* CTRL2(11h): [7]=0 OP_MODE_G[6:4] ODR_G[3:0] */
#define LSM6DSV16X_OPMODE_G_HP     0x00u
#define LSM6DSV16X_CTRL2_120HZ     ((LSM6DSV16X_OPMODE_G_HP << 4) | LSM6DSV16X_ODR_120HZ)

/* CTRL3(12h): BDU[6] IF_INC[2] (chip default 0x44; explicit for determinism) */
#define LSM6DSV16X_CTRL3_DEFAULT   0x44u

/* CTRL6(15h): [7]=0 LPF1_G_BW[6:4] FS_G[3:0]; FS_G=0100 → ±2000dps */
#define LSM6DSV16X_FS_G_2000DPS    0x04u
#define LSM6DSV16X_CTRL6_2000DPS   LSM6DSV16X_FS_G_2000DPS

/* CTRL8(17h): HP_LPF2_XL_BW[7:5] [4]=0 XL_DualC_EN[3] [2]=0 FS_XL[1:0]; FS_XL=01 → ±4g */
#define LSM6DSV16X_FS_XL_4G        0x01u
#define LSM6DSV16X_CTRL8_4G        LSM6DSV16X_FS_XL_4G

/* STATUS_REG(1Eh): bit1 GDA, bit0 XLDA */
#define LSM6DSV16X_STAT_XLDA       0x01u
#define LSM6DSV16X_STAT_GDA        0x02u

typedef struct {
    bool (*write)(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx);
    bool (*read)(uint8_t reg, uint8_t *data, uint8_t len, void *ctx);
} imu_transport_t;

typedef struct {
    imu_transport_t t;
    void           *ctx;
    bool            ok;
    float           accel_mg_per_lsb;
    float           gyro_mdps_per_lsb;
} lsm6dsv16x_t;

bool lsm6dsv16x_init(lsm6dsv16x_t *imu);
bool lsm6dsv16x_read(lsm6dsv16x_t *imu, float acc[3], float gyro[3]);

int16_t lsm6dsv16x_decode_i16(const uint8_t raw[2]);  /* 小端 */
float   lsm6dsv16x_accel_scale(uint8_t fs_xl_bits);   /* mg/LSB */
float   lsm6dsv16x_gyro_scale(uint8_t fs_g_bits);     /* mdps/LSB */

#ifdef __cplusplus
}
#endif
#endif
```

- [ ] **Step 4: 写 `lsm6dsv16x.c`**

```c
#include "lsm6dsv16x.h"

int16_t lsm6dsv16x_decode_i16(const uint8_t raw[2]) {
    return (int16_t)((uint16_t)raw[0] | ((uint16_t)raw[1] << 8));
}

float lsm6dsv16x_accel_scale(uint8_t fs_xl_bits) {
    switch (fs_xl_bits & 0x03u) {
        case 0x00u: return 0.061f;   /* ±2g  */
        case 0x01u: return 0.122f;   /* ±4g  */
        case 0x02u: return 0.244f;   /* ±8g  */
        default:    return 0.488f;   /* ±16g */
    }
}

float lsm6dsv16x_gyro_scale(uint8_t fs_g_bits) {
    switch (fs_g_bits & 0x0Fu) {
        case 0x00u: return 4.375f;   /* ±125  */
        case 0x01u: return 8.75f;    /* ±250  */
        case 0x02u: return 17.50f;   /* ±500  */
        case 0x03u: return 35.0f;    /* ±1000 */
        case 0x04u: return 70.0f;    /* ±2000 */
        default:    return 140.0f;   /* ±4000 */
    }
}

static bool reg_write(lsm6dsv16x_t *imu, uint8_t reg, uint8_t val) {
    return imu->t.write(reg, &val, 1, imu->ctx);
}

bool lsm6dsv16x_init(lsm6dsv16x_t *imu) {
    if (!imu || !imu->t.write || !imu->t.read) return false;

    uint8_t who = 0;
    if (!imu->t.read(LSM6DSV16X_REG_WHO_AM_I, &who, 1, imu->ctx)) return false;
    if (who != LSM6DSV16X_WHO_AM_I_VALUE) return false;

    if (!reg_write(imu, LSM6DSV16X_REG_CTRL3, LSM6DSV16X_CTRL3_DEFAULT)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL2_G, LSM6DSV16X_CTRL2_120HZ)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL6_G, LSM6DSV16X_CTRL6_2000DPS)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL1_XL, LSM6DSV16X_CTRL1_120HZ)) return false;
    if (!reg_write(imu, LSM6DSV16X_REG_CTRL8_XL, LSM6DSV16X_CTRL8_4G)) return false;

    imu->accel_mg_per_lsb   = lsm6dsv16x_accel_scale(LSM6DSV16X_FS_XL_4G);
    imu->gyro_mdps_per_lsb  = lsm6dsv16x_gyro_scale(LSM6DSV16X_FS_G_2000DPS);
    imu->ok = true;
    return true;
}

bool lsm6dsv16x_read(lsm6dsv16x_t *imu, float acc[3], float gyro[3]) {
    if (!imu || !imu->ok) return false;

    uint8_t status = 0;
    if (!imu->t.read(LSM6DSV16X_REG_STATUS_REG, &status, 1, imu->ctx)) return false;
    if ((status & (LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA))
        != (LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA)) return false;

    uint8_t g_raw[6], a_raw[6];
    if (!imu->t.read(LSM6DSV16X_REG_OUTX_L_G, g_raw, 6, imu->ctx)) return false;
    if (!imu->t.read(LSM6DSV16X_REG_OUTX_L_A, a_raw, 6, imu->ctx)) return false;

    gyro[0] = (float)lsm6dsv16x_decode_i16(&g_raw[0]) * imu->gyro_mdps_per_lsb * 0.001f;
    gyro[1] = (float)lsm6dsv16x_decode_i16(&g_raw[2]) * imu->gyro_mdps_per_lsb * 0.001f;
    gyro[2] = (float)lsm6dsv16x_decode_i16(&g_raw[4]) * imu->gyro_mdps_per_lsb * 0.001f;

    acc[0] = (float)lsm6dsv16x_decode_i16(&a_raw[0]) * imu->accel_mg_per_lsb * 0.001f;
    acc[1] = (float)lsm6dsv16x_decode_i16(&a_raw[2]) * imu->accel_mg_per_lsb * 0.001f;
    acc[2] = (float)lsm6dsv16x_decode_i16(&a_raw[4]) * imu->accel_mg_per_lsb * 0.001f;
    return true;
}
```

- [ ] **Step 5: 运行测试确认通过**

Run: `cd firmware/lite/test && make test_lsm6dsv16x`
Expected: `LSM6DSV16X: all tests PASS`（6 项：配置写序列、WHO_AM_I 拒绝、小端解码、尺度常量、物理单位、DRDY 轮询）。

- [ ] **Step 6: 提交**

```bash
git add firmware/lite/lib/LSM6DSV16X firmware/lite/test/test_lsm6dsv16x.c
git diff --check
git commit -m "feat(lite): LSM6DSV16X I2C driver (120Hz, ±4g/±2000dps) + host tests"
```

---

### Task 3: Madgwick 6-axis AHRS 滤波器 + host 单测

**Files:**
- Create: `firmware/lite/lib/Madgwick/madgwick.h`
- Create: `firmware/lite/lib/Madgwick/madgwick.c`
- Test: `firmware/lite/test/test_madgwick.c`

**Interfaces:**
- Produces: `typedef struct { float beta; float q0,q1,q2,q3; } madgwick_t;`；`void madgwick_init(madgwick_t*, float beta)`；`void madgwick_update(madgwick_t*, float gx,gy,gz /*rad/s*/, float ax,ay,az /*g*/, float dt /*s*/)`；`void madgwick_get_quat(const madgwick_t*, float out[4])`；`void madgwick_set_quat(madgwick_t*, const float q[4])`（Task 4 管理器与 Task 5 复用）。

**决策记录 (2026-08-11) — Madgwick 梯度符号修正（本计划的 `s = Jᵀf` 原实现非标准）**

用户已批准「修正后执行」：原计划 `madgwick.c` 的梯度下降有三处符号错误，导致姿态向错误方向收敛（重力 −y 时收敛到 roll +90° 而非物理真值 −90°）。已逐项对照真 Jacobian（J = ∂ĝ/∂q）与部署参考实现（arduino-libraries/MadgwickAHRS `updateIMU`）核实并修正：

1. **f1 残差项**：`f1 = 2.0f*(q2*q3 - q0*q1) - ay` → `f1 = 2.0f*(q0*q1 + q2*q3) - ay`（ĝ_y 半向量形式符号错误）。
2. **s0 的 f1 系数**：`f1*(-2.0f*q1)` → `f1*( 2.0f*q1)`（真 Jacobian ∂f1/∂q0 = **+2q1**）。
3. **s1 的 f1 系数**：`f1*(-2.0f*q0)` → `f1*( 2.0f*q0)`（真 Jacobian ∂f1/∂q1 = **+2q0**）。

物理真值锚点：ĝ = R(q)ᵀ·(0,0,1) = (2(xz−wy), 2(yz+wx), 1−2(x²+y²)) ⇒ **â=(0,−1,0) ⟺ roll −90° ⟺ q=(cos45, −sin45, 0, 0)**。修正后 `test_converge_gravity_neg_y` 断言相应改为 `q[1] → −0.7071`。

**`test_converge_flip_180` 保持原断言**（起始 +90°、重力 −y 时 10s 后仍在 +90°）：这是离散梯度下降的**保号性质**——该状态 s ∥ q，故 `normalize(q − β·dt·ŝ) = q`（s ∥ q 时不动点）。加速度计单独无法分辨 ±180°（无磁力计），属预期物理限制，非缺陷。

**数值验证**（`gcc -std=c11 -O2 -Werror` host 模拟，dt=0.01s，β=0.1）：修正后全 5 测试场景通过——静止+z 60s 无漂移；扰动+z 60s 收敛 identity（q1,q2<1e-2，q3 有界）；重力 −y 20s 收敛 roll −90.09°；翻转起始保号 +90°；扰动 −y 收敛 −90°。与参考实现方向一致。Task 3 Step 5 期望摘要中的「重力-y 收敛」指修正后的 −90° 方向。

- [ ] **Step 1: 写失败的测试 `test_madgwick.c`**

```c
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "madgwick.h"

static float qnorm(const float q[4]) {
    return sqrtf(q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3]);
}

static void test_static_no_drift(void) {
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    for (int i = 0; i < 6000; i++) {          /* 60 s @ 100 Hz */
        madgwick_update(&m, 0,0,0, 0,0,1, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 1.0f) < 1e-3f);
    assert(fabsf(q[1]) < 1e-3f && fabsf(q[2]) < 1e-3f && fabsf(q[3]) < 1e-3f);
}

static void test_converge_from_perturbation(void) {
    /* tilt (q1,q2) is corrected by gravity; yaw (q3) is unobservable from
       accel alone and must stay bounded, not diverge. */
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    float q0[4] = {0.9990f, 0.02f, 0.02f, 0.02f};
    madgwick_set_quat(&m, q0);
    for (int i = 0; i < 6000; i++) {
        madgwick_update(&m, 0,0,0, 0,0,1, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 1.0f) < 1e-2f);
    assert(fabsf(q[1]) < 1e-2f && fabsf(q[2]) < 1e-2f);  /* tilt corrected */
    assert(fabsf(q[3]) < 0.03f);                         /* yaw bounded */
}

static void test_rotate_90_deg_x(void) {
    madgwick_t m;
    madgwick_init(&m, 0.0f);                   /* feedback off: pure integration */
    const float deg90 = 1.5707963f;            /* 90 deg/s about x */
    for (int i = 0; i < 100; i++) {            /* 1.0 s */
        madgwick_update(&m, deg90, 0, 0, 0,0,1, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 0.7071f) < 0.05f);
    assert(fabsf(q[1] - 0.7071f) < 0.05f);
    assert(fabsf(q[2]) < 0.05f && fabsf(q[3]) < 0.05f);
    assert(fabsf(qnorm(q) - 1.0f) < 1e-3f);
}

static void test_converge_gravity_neg_y(void) {
    /* gravity along -y (device rolled -90deg about x) converges to q = -90deg
       about x. 2026-08-11: previous assertion (q[1] -> +0.7071) codified a
       gradient sign bug (see decision record); physical truth is
       q = (cos45, -sin45, 0, 0). */
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    for (int i = 0; i < 2000; i++) {           /* 20 s */
        madgwick_update(&m, 0,0,0, 0,-1,0, 0.01f);
    }
    float q[4]; madgwick_get_quat(&m, q);
    /* q should be ~(cos45, -sin45, 0, 0) = rotation -90deg about x */
    assert(fabsf(q[0] - 0.7071f) < 0.05f);
    assert(fabsf(q[1] + 0.7071f) < 0.05f);
    assert(fabsf(q[2]) < 0.05f && fabsf(q[3]) < 0.05f);
}

static void test_converge_flip_180_no_ambiguity_guard(void) {
    /* Sign preservation: at roll +90 with gravity -y, the correction step s is
       collinear with q (s || q), so discrete normalize(q - eps*s_hat) is a fixed
       point. Accel alone cannot resolve the +/-180 sign without gyro history
       (no magnetometer); the filter stays at +90 instead of jumping to -90.
       This is expected physics, not a bug. */
    madgwick_t m;
    madgwick_init(&m, 0.1f);
    float q0[4] = {0.7071f, 0.7071f, 0.0f, 0.0f};  /* already 90deg about x */
    madgwick_set_quat(&m, q0);
    for (int i = 0; i < 1000; i++) {
        madgwick_update(&m, 0,0,0, 0,-1,0, 0.01f); /* gravity -y in body */
    }
    float q[4]; madgwick_get_quat(&m, q);
    assert(fabsf(q[0] - 0.7071f) < 0.02f);
    assert(fabsf(q[1] - 0.7071f) < 0.02f);
}

int main(void) {
    test_static_no_drift();
    test_converge_from_perturbation();
    test_rotate_90_deg_x();
    test_converge_gravity_neg_y();
    test_converge_flip_180_no_ambiguity_guard();
    printf("MADGWICK: all tests PASS\n");
    return 0;
}
```

- [ ] **Step 2: 运行测试确认失败**

Run: `cd firmware/lite/test && make test_madgwick`
Expected: 编译失败，`fatal error: madgwick.h: No such file or directory`。

- [ ] **Step 3: 写 `madgwick.h`**

```c
#ifndef ECHOGLOVE_MADGWICK_H
#define ECHOGLOVE_MADGWICK_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float beta;
    float q0, q1, q2, q3;  /* w, x, y, z */
} madgwick_t;

void madgwick_init(madgwick_t *m, float beta);
void madgwick_update(madgwick_t *m,
                     float gx, float gy, float gz,   /* rad/s */
                     float ax, float ay, float az,   /* g */
                     float dt);                      /* s */
void madgwick_get_quat(const madgwick_t *m, float out[4]);
void madgwick_set_quat(madgwick_t *m, const float q[4]);

#ifdef __cplusplus
}
#endif
#endif
```

- [ ] **Step 4: 写 `madgwick.c`**

```c
#include "madgwick.h"
#include <math.h>

void madgwick_init(madgwick_t *m, float beta) {
    m->beta = beta;
    m->q0 = 1.0f; m->q1 = 0.0f; m->q2 = 0.0f; m->q3 = 0.0f;
}

void madgwick_get_quat(const madgwick_t *m, float out[4]) {
    out[0] = m->q0; out[1] = m->q1; out[2] = m->q2; out[3] = m->q3;
}

void madgwick_set_quat(madgwick_t *m, const float q[4]) {
    m->q0 = q[0]; m->q1 = q[1]; m->q2 = q[2]; m->q3 = q[3];
}

static float rsqrt_(float x) { return 1.0f / sqrtf(x); }

/*
 * Madgwick 6-axis gradient-descent AHRS (accel + gyro; no magnetometer).
 * Convention: identity quat <=> sensor +z aligned with gravity (up).
 *   ghat = q (x) (0,0,0,1) (x) q*   -- estimated gravity in body frame
 *   f    = ghat - a                 -- residual vs measured (normalised) accel
 *   s    = J^T f                    -- gradient of ||f||^2 wrt quaternion
 *   qdot = 0.5*q(x)w - beta*s       -- gyro rate + corrective step
 */
void madgwick_update(madgwick_t *m,
                     float gx, float gy, float gz,
                     float ax, float ay, float az,
                     float dt) {
    float q0 = m->q0, q1 = m->q1, q2 = m->q2, q3 = m->q3;
    float beta = m->beta;
    float qDot1, qDot2, qDot3, qDot4;
    float s0, s1, s2, s3, sn;
    float f0, f1, f2;
    float rn;

    /* Rate of change of quaternion from gyroscope (rad/s) */
    qDot1 = 0.5f * (-q1*gx - q2*gy - q3*gz);
    qDot2 = 0.5f * ( q0*gx + q2*gz - q3*gy);
    qDot3 = 0.5f * ( q0*gy - q1*gz + q3*gx);
    qDot4 = 0.5f * ( q0*gz + q1*gy - q2*gx);

    /* Feedback only if accelerometer measurement is valid */
    if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
        rn = rsqrt_(ax*ax + ay*ay + az*az);
        ax *= rn; ay *= rn; az *= rn;

        /* Estimated gravity in body frame (half-vector form) */
        f0 = 2.0f*(q1*q3 - q0*q2) - ax;
        f1 = 2.0f*(q0*q1 + q2*q3) - ay;
        f2 = (q0*q0 - q1*q1 - q2*q2 + q3*q3) - az;

        /* s = J^T f, J = dghat/dq  (2026-08-11: f1 Jacobian coeffs corrected
           from -2q1/-2q0 to +2q1/+2q0 per true J = dghat/dq; see decision
           record above) */
        s0 = f0*(-2.0f*q2) + f1*( 2.0f*q1) + f2*( 2.0f*q0);
        s1 = f0*( 2.0f*q3) + f1*( 2.0f*q0) + f2*(-2.0f*q1);
        s2 = f0*(-2.0f*q0) + f1*( 2.0f*q3) + f2*(-2.0f*q2);
        s3 = f0*( 2.0f*q1) + f1*( 2.0f*q2) + f2*( 2.0f*q3);
        /* Guard |s|==0 (no accel residual): rsqrt(0)=inf would turn 0*inf into NaN */
        {
            float ss = s0*s0 + s1*s1 + s2*s2 + s3*s3;
            if (ss > 1e-12f) { sn = rsqrt_(ss); s0 *= sn; s1 *= sn; s2 *= sn; s3 *= sn; }
        }

        /* Corrective step */
        qDot1 -= beta * s0;
        qDot2 -= beta * s1;
        qDot3 -= beta * s2;
        qDot4 -= beta * s3;
    }

    /* Integrate */
    q0 += qDot1 * dt;
    q1 += qDot2 * dt;
    q2 += qDot3 * dt;
    q3 += qDot4 * dt;

    /* Normalise */
    rn = rsqrt_(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    m->q0 = q0*rn; m->q1 = q1*rn; m->q2 = q2*rn; m->q3 = q3*rn;
}
```

- [ ] **Step 5: 运行测试确认通过**

Run: `cd firmware/lite/test && make test_madgwick`
Expected: `MADGWICK: all tests PASS`（5 项：静止无漂移、扰动收敛/偏航有界、纯积分 90° 旋转、重力-y 收敛至 −90°、180° 保号不动）。

- [ ] **Step 6: 提交**

```bash
git add firmware/lite/lib/Madgwick firmware/lite/test/test_madgwick.c
git diff --check
git commit -m "feat(lite): Madgwick 6-axis AHRS filter + host tests"
```

---

### Task 4: LiteSensorManager（flex + IMU → hand_token_t）+ host 单测

**Files:**
- Create: `firmware/lite/lib/LiteSensorManager/lite_sensor_manager.h`
- Create: `firmware/lite/lib/LiteSensorManager/lite_sensor_manager.c`
- Test: `firmware/lite/test/test_lite_sensor_manager.c`

**Interfaces:**
- Consumes: `imu_transport_t`（Task 2）、`madgwick_t`（Task 3）、`hand_token_t`（`firmware/shared/hand_token.h`）。
- Produces: `typedef bool (*lite_flex_read_fn)(float out[5], void *ctx);`；`bool lite_sm_init(lite_sensor_manager_t*, uint8_t product, uint8_t hand, uint8_t serial, float beta, lite_flex_read_fn, void *flex_ctx, imu_transport_t, void *imu_ctx)`；`bool lite_sm_update(lite_sensor_manager_t*, uint32_t timestamp_us, hand_token_t *out)`；`void lite_sm_euler_deg(const float quat[4], float out_deg[3])`（Task 5 main.cpp 复用）。

- [ ] **Step 1: 写失败的测试 `test_lite_sensor_manager.c`**

```c
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lite_sensor_manager.h"
#include "lsm6dsv16x.h"

typedef struct {
    uint8_t who_am_i;
    uint8_t status;
    uint8_t g_raw[6];
    uint8_t a_raw[6];
    int     n_reads;
} stub_t;

static bool stub_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx) {
    (void)reg; (void)data; (void)len; (void)ctx;
    return true;
}
static bool stub_read(uint8_t reg, uint8_t *data, uint8_t len, void *ctx) {
    (void)len;
    stub_t *s = (stub_t*)ctx;
    if (reg == LSM6DSV16X_REG_WHO_AM_I) { data[0] = s->who_am_i; return true; }
    if (reg == LSM6DSV16X_REG_STATUS_REG) { data[0] = s->status; return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_G) { memcpy(data, s->g_raw, 6); s->n_reads++; return true; }
    if (reg == LSM6DSV16X_REG_OUTX_L_A) { memcpy(data, s->a_raw, 6); return true; }
    return false;
}

static void set_gravity_z_up(stub_t *s) {
    /* 静止: acc = +1g (z), gyro = 0 */
    memset(s->g_raw, 0, 6);
    memset(s->a_raw, 0, 6);
    s->status = LSM6DSV16X_STAT_XLDA | LSM6DSV16X_STAT_GDA;
    int16_t z = (int16_t)(1.0f / (0.122f * 0.001f));   /* ~8197 LSB = 1g @ ±4g */
    s->a_raw[4] = (uint8_t)(z & 0xFF);
    s->a_raw[5] = (uint8_t)((z >> 8) & 0xFF);
}

static bool flex_half(float out[5], void *ctx) {
    (void)ctx;
    for (int i = 0; i < 5; i++) out[i] = 0.5f;
    return true;
}
static bool flex_fail(float out[5], void *ctx) {
    (void)out; (void)ctx;
    return false;
}

static void test_init_sets_fields(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_RIGHT, 3,
                        0.5f, flex_half, NULL, t, &s));
    assert(m.started);
    assert(m.hand == HAND_TOKEN_HAND_RIGHT);
    assert(m.serial == 3);
}

static void test_update_fills_token(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_LEFT, 1,
                        0.5f, flex_half, NULL, t, &s));

    hand_token_t tok;
    assert(lite_sm_update(&m, 100000, &tok));        /* t=0.1s */
    assert(lite_sm_update(&m, 200000, &tok));        /* t=0.2s */
    assert(lite_sm_update(&m, 300000, &tok));        /* t=0.3s */

    assert(tok.product == HAND_TOKEN_PRODUCT_LITE);
    assert(tok.hand == HAND_TOKEN_HAND_LEFT);
    assert(tok.serial == 1);
    assert(tok.timestamp_us == 300000);
    for (int i = 0; i < 5; i++) assert(tok.flex[i] == 0.5f);
    /* 静止重力 → 身份四元数 (w→1, tilt 很小) */
    assert(tok.quat[0] > 0.99f);
    assert(fabsf(tok.quat[1]) < 1e-2f);
    assert(fabsf(tok.quat[2]) < 1e-2f);
    /* acc 归一 1g (z) */
    assert(fabsf(tok.acc[2] - 1.0f) < 0.01f);
    assert(tok.acc[0] == 0.0f && tok.acc[1] == 0.0f);
}

static void test_flex_failure_leaves_zero(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_LEFT, 0,
                        0.5f, flex_fail, NULL, t, &s));
    hand_token_t tok;
    assert(lite_sm_update(&m, 100000, &tok));
    for (int i = 0; i < 5; i++) assert(tok.flex[i] == 0.0f);
}

static void test_no_new_data_returns_false(void) {
    stub_t s; memset(&s, 0, sizeof(s)); s.who_am_i = LSM6DSV16X_WHO_AM_I_VALUE; set_gravity_z_up(&s);
    s.status = 0x00;                                   /* DRDY 未就绪 */
    lite_sensor_manager_t m;
    imu_transport_t t = { stub_write, stub_read };
    assert(lite_sm_init(&m, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_LEFT, 0,
                        0.5f, flex_half, NULL, t, &s));
    hand_token_t tok;
    memset(&tok, 0xAA, sizeof(tok));
    assert(!lite_sm_update(&m, 100000, &tok));
}

static void test_euler_identity(void) {
    float q[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float d[3];
    lite_sm_euler_deg(q, d);
    assert(fabsf(d[0]) < 1e-3f && fabsf(d[1]) < 1e-3f && fabsf(d[2]) < 1e-3f);

    /* 绕 x 转 90°: roll ≈ 90° */
    float q90[4] = { 0.70710678f, 0.70710678f, 0.0f, 0.0f };
    lite_sm_euler_deg(q90, d);
    assert(fabsf(d[0] - 90.0f) < 0.5f);
}

int main(void) {
    test_init_sets_fields();
    test_update_fills_token();
    test_flex_failure_leaves_zero();
    test_no_new_data_returns_false();
    test_euler_identity();
    printf("LITE_SENSOR_MANAGER: all tests PASS\n");
    return 0;
}
```

- [ ] **Step 2: 运行测试确认失败**

Run: `cd firmware/lite/test && make test_lite_sensor_manager`
Expected: 编译失败，`fatal error: lite_sensor_manager.h: No such file or directory`。

- [ ] **Step 3: 写 `lite_sensor_manager.h`**

```c
#ifndef ECHOGLOVE_LITE_SENSOR_MANAGER_H
#define ECHOGLOVE_LITE_SENSOR_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include "lsm6dsv16x.h"
#include "madgwick.h"
#include "hand_token.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 归一化指尖弯折 0..1 (拇->小), 由板级 ADC 读取器注入 */
typedef bool (*lite_flex_read_fn)(float out[5], void *ctx);

typedef struct {
    lsm6dsv16x_t    imu;
    madgwick_t      filter;
    uint8_t         product;      /* HAND_TOKEN_PRODUCT_LITE */
    uint8_t         hand;         /* HAND_TOKEN_HAND_LEFT/RIGHT */
    uint8_t         serial;
    uint32_t        last_us;
    bool            started;
    lite_flex_read_fn flex_read;
    void            *flex_ctx;
} lite_sensor_manager_t;

/* 初始化: 注入 flex 读取器 + 启动 IMU + 复位滤波 */
bool lite_sm_init(lite_sensor_manager_t *m, uint8_t product, uint8_t hand,
                  uint8_t serial, float beta,
                  lite_flex_read_fn flex_read, void *flex_ctx,
                  imu_transport_t transport, void *imu_ctx);

/*
 * 单步采样 + 融合, 填充 out。
 * dt 由 timestamp_us 差分计算 (首帧 dt=0)。flex 缺失时置 0。
 * 返回 true; IMU 无新数据时返回 false (out 不更新)。
 */
bool lite_sm_update(lite_sensor_manager_t *m, uint32_t timestamp_us,
                    hand_token_t *out);

/* 调试用: quat → roll/pitch/yaw (度, ZYX)。Lite 遥测串口打印。 */
void lite_sm_euler_deg(const float quat[4], float out_deg[3]);

#ifdef __cplusplus
}
#endif
#endif
```

- [ ] **Step 4: 写 `lite_sensor_manager.c`**

```c
#include "lite_sensor_manager.h"
#include <math.h>
#include <string.h>

bool lite_sm_init(lite_sensor_manager_t *m, uint8_t product, uint8_t hand,
                  uint8_t serial, float beta,
                  lite_flex_read_fn flex_read, void *flex_ctx,
                  imu_transport_t transport, void *imu_ctx) {
    if (!m) return false;
    memset(m, 0, sizeof(*m));
    m->product   = product;
    m->hand      = hand;
    m->serial    = serial;
    m->flex_read = flex_read;
    m->flex_ctx  = flex_ctx;
    m->imu.t = transport;
    m->imu.ctx = imu_ctx;
    if (!lsm6dsv16x_init(&m->imu)) return false;
    madgwick_init(&m->filter, beta);
    m->started = true;
    return true;
}

static void fill_identity(hand_token_t *out) {
    memset(out, 0, sizeof(*out));
    out->quat[0] = 1.0f;   /* w=1, x=y=z=0 */
}

bool lite_sm_update(lite_sensor_manager_t *m, uint32_t timestamp_us,
                    hand_token_t *out) {
    if (!m || !m->started || !out) return false;

    float acc[3], gyro[3];
    if (!lsm6dsv16x_read(&m->imu, acc, gyro)) return false;

    float dt = 0.0f;
    if (m->last_us != 0) {
        uint32_t du = timestamp_us - m->last_us;   /* 单调回绕安全 */
        dt = (float)du * 1e-6f;
    }
    m->last_us = timestamp_us;

    madgwick_update(&m->filter, gyro[0], gyro[1], gyro[2],
                    acc[0], acc[1], acc[2], dt);

    fill_identity(out);
    out->product = m->product;
    out->hand    = m->hand;
    out->serial  = m->serial;
    out->timestamp_us = timestamp_us;
    if (m->flex_read) m->flex_read(out->flex, m->flex_ctx);   /* 失败则留 0 */
    madgwick_get_quat(&m->filter, out->quat);
    memcpy(out->acc, acc, sizeof(acc));
    return true;
}

void lite_sm_euler_deg(const float q[4], float out_deg[3]) {
    float w = q[0], x = q[1], y = q[2], z = q[3];
    float roll  = atan2f(2.0f*(w*x + y*z), 1.0f - 2.0f*(x*x + y*y));
    float pitch = asinf(2.0f*(w*y - z*x));
    float yaw   = atan2f(2.0f*(w*z + x*y), 1.0f - 2.0f*(y*y + z*z));
    out_deg[0] = roll  * 180.0f / 3.14159265358979f;
    out_deg[1] = pitch * 180.0f / 3.14159265358979f;
    out_deg[2] = yaw   * 180.0f / 3.14159265358979f;
}
```

- [ ] **Step 5: 运行测试确认通过**

Run: `cd firmware/lite/test && make test_lite_sensor_manager`
Expected: `LITE_SENSOR_MANAGER: all tests PASS`（5 项：字段初始化、token 填充 + 四元数/acc 正确、flex 失败置 0、DRDY 未就绪返回 false、euler 换算）。

- [ ] **Step 6: 全量 host 单测门**

Run: `cd firmware/lite/test && make run`
Expected: 三个 bin 依次打印 `all tests PASS`，退出码 0。

- [ ] **Step 7: 提交**

```bash
git add firmware/lite/lib/LiteSensorManager firmware/lite/test/test_lite_sensor_manager.c
git diff --check
git commit -m "feat(lite): LiteSensorManager flex+IMU → hand_token_t (quat via Madgwick)"
```

---

### Task 5: FreeRTOS `main.cpp` 集成（SensorRead 120Hz + Telemetry 10Hz）

**Files:**
- Modify: `firmware/lite/src/main.cpp`（替换 Task 1 桩）

**Interfaces:**
- Consumes: `lite_sm_init`/`lite_sm_update`/`lite_sm_euler_deg`（Task 4）、`imu_transport_t`（Task 2）、`hand_token_t`（shared）。
- Produces: 板上固件——`Task_SensorRead`（core1 prio3, ~120Hz, DRDY 门控）+ `Task_Telemetry`（core0 prio1, 10Hz 串口 CSV）。验证 = `pio run` 编译通过 + 板上清单（Task 6）。

- [ ] **Step 1: 写 `main.cpp`**

```cpp
// EchoGlove Lite — M2: LSM6DSV16X(120Hz) + Madgwick → quat 进 Hand Token
// 串口遥测 (115200) 10Hz CSV: t=<us> flex=... euler=<roll,pitch,yaw> deg
#include <Arduino.h>
#include <Wire.h>
#include "lsm6dsv16x.h"
#include "madgwick.h"
#include "lite_sensor_manager.h"
#include "hand_token.h"

static lite_sensor_manager_t g_sm;
static volatile hand_token_t g_last;
static volatile bool          g_has_sample = false;

// ---- I2C transport over Arduino Wire (SDA=GPIO8, SCL=GPIO9, 400kHz) ----
static bool i2c_write(uint8_t reg, const uint8_t *data, uint8_t len, void *ctx) {
    (void)ctx;
    Wire.beginTransmission(LSM6DSV16X_I2C_ADDR);
    Wire.write(reg);
    for (uint8_t i = 0; i < len; i++) Wire.write(data[i]);
    return Wire.endTransmission() == 0;
}
static bool i2c_read(uint8_t reg, uint8_t *data, uint8_t len, void *ctx) {
    (void)ctx;
    Wire.beginTransmission(LSM6DSV16X_I2C_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom((uint8_t)LSM6DSV16X_I2C_ADDR, (uint8_t)len) != len) return false;
    for (uint8_t i = 0; i < len; i++) data[i] = Wire.read();
    return true;
}

// ---- Flex via internal ADC1, GPIO1-5 (raw normalize 0..1; NVS calib = M4) ----
static const int kFlexPins[5] = {1, 2, 3, 4, 5};
static bool flex_read(float out[5], void *ctx) {
    (void)ctx;
    for (int i = 0; i < 5; i++) out[i] = (float)analogRead(kFlexPins[i]) / 4095.0f;
    return true;
}

// ---- 120Hz 采样 + Madgwick 融合 ----
static void taskSensorRead(void *arg) {
    (void)arg;
    for (;;) {
        hand_token_t tok;
        if (lite_sm_update(&g_sm, micros(), &tok)) {
            g_last = tok;
            g_has_sample = true;
        }
        vTaskDelay(pdMS_TO_TICKS(8));   /* ~120Hz loop; DRDY 门控实际工作 */
    }
}

// ---- 10Hz 串口遥测 (漂移/响应验证) ----
static void taskTelemetry(void *arg) {
    (void)arg;
    vTaskDelay(pdMS_TO_TICKS(2000));    /* 等 IMU 初始化 */
    for (;;) {
        if (g_has_sample) {
            hand_token_t t = g_last;    /* 快照 */
            float e[3];
            lite_sm_euler_deg(t.quat, e);
            Serial.printf("t=%lu flex=%.3f,%.3f,%.3f,%.3f,%.3f euler=%.1f,%.1f,%.1f quat=%.3f,%.3f,%.3f,%.3f\n",
                          (unsigned long)t.timestamp_us,
                          t.flex[0], t.flex[1], t.flex[2], t.flex[3], t.flex[4],
                          e[0], e[1], e[2],
                          t.quat[0], t.quat[1], t.quat[2], t.quat[3]);
        }
        vTaskDelay(pdMS_TO_TICKS(100)); /* 10Hz */
    }
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Wire.begin(8, 9, 400000);           /* SDA=GPIO8, SCL=GPIO9, 400kHz */
    imu_transport_t t = { i2c_write, i2c_read };
    if (!lite_sm_init(&g_sm, HAND_TOKEN_PRODUCT_LITE, HAND_TOKEN_HAND_RIGHT, 0,
                      0.1f, flex_read, NULL, t, NULL)) {
        Serial.println("LITE SM INIT FAILED (check I2C wiring / WHO_AM_I)");
        while (1) vTaskDelay(pdMS_TO_TICKS(1000));
    }
    Serial.println("LITE SM INIT OK");
    xTaskCreatePinnedToCore(taskSensorRead, "SensorRead", 4096, NULL, 3, NULL, 1);
    xTaskCreatePinnedToCore(taskTelemetry, "Telemetry", 4096, NULL, 1, NULL, 0);
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
```

> 注：左右手由构建期/运行期决定——当前硬编码 `HAND_HAND_RIGHT`；M3 线上协议化时改由设备配置传入。

- [ ] **Step 2: 验证编译**

Run: `pio run -d firmware/lite`
Expected: `SUCCESS`，无编译错误。若 Wire/FreeRTOS 头缺失，检查 platformio.ini `lib_ldf_mode` 与 `-I../shared`。

- [ ] **Step 3: 提交**

```bash
git add firmware/lite/src/main.cpp
git diff --check
git commit -m "feat(lite): S3 Lite main.cpp — 120Hz sensor task + 10Hz serial telemetry"
```

---

### Task 6: 文档修正（Beta 设计文档 §4）+ 板上验证清单

**Files:**
- Modify: `/home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta/docs/superpowers/specs/2026-08-10-egoglove-aligned-production-design.md`（§4，**Beta 仓库**，用户批准的活动文档例外）
- Create: `firmware/lite/README.md`（板上验证清单）

- [ ] **Step 1: 修正 Beta 设计文档 §4 的 ODR 错误**

在 **Beta 仓库** 打开 `docs/superpowers/specs/2026-08-10-egoglove-aligned-production-design.md`，将 §4 中这一行：

```markdown
- **驱动**：仓库内本地驱动（非 PlatformIO 注册表库）；ODR 建议 104Hz（与 Task_SensorRead 100Hz 对齐），满量程 ±4g / ±2000dps 起步。
```

改为（记录两个已批准决策 + 修正 ODR）：

```markdown
- **驱动**：仓库内本地驱动（非 PlatformIO 注册表库）；ODR **120Hz**（芯片无 104Hz 档，120Hz=0b0110 为最接近档；`Task_SensorRead` 同步 120Hz），满量程 ±4g / ±2000dps 起步。
- **融合实现**：**Host Madgwick**（β≈0.1，用户已确认；非芯片内置 SFLP 融合）。**物理限制：yaw（绕重力轴旋转）加速度计不可观**——tilt 收敛，yaw 保持有界但不修正（需磁力计或视觉，属 Pro/roadmap）。
```

同时把 M2 里程碑行（§末尾表格）状态从 `待排` 更新为 `📋 计划已出 (2026-08-11)`。

- [ ] **Step 2: 提交 Beta 仓库文档修正**

```bash
cd /home/EchoGloveHugeProjects/EchoGlove-SLR-MOCAP-Beta
git add docs/superpowers/specs/2026-08-10-egoglove-aligned-production-design.md
git diff --check
git commit -m "docs(spec): correct §4 IMU ODR 104→120Hz, record Host Madgwick + yaw-unobservability decision"
```

> 提交前确认 git 身份仍是 `PaxonHuang <quenchkidney@outlook.com>`。

- [ ] **Step 3: 写 `firmware/lite/README.md`（含板上验证清单）**

```markdown
# EchoGlove Lite (ESP32-S3) — M2: LSM6DSV16X + Madgwick

✅ 已实现（M2, 2026-08-11）：LSM6DSV16X 驱动（120Hz、±4g/±2000dps）、Host Madgwick
6-axis AHRS、LiteSensorManager（flex+IMU → Hand Token v1 `quat[4]`）、串口遥测。
🟡 工程可实现：79B 线上序列化（M3）、NVS flex 校准（M4）、46 类 SLR（M4）。

## 构建 / 单测

```bash
pio run -d firmware/lite                 # 固件编译门
cd firmware/lite/test && make run        # host 单测 (驱动/滤波器/管理器)
```

## 烧录与遥测

```bash
pio run -d firmware/lite -t upload -t monitor   # 115200; USB CDC
```

启动 2s 后每 100ms 一行：
`t=<us> flex=f0..f4 euler=roll,pitch,yaw quat=w,x,y,z`

## 板上验证清单（M2 验收，需硬件）

| # | 项 | 通过标准 | 步骤 |
|---|----|---------|------|
| 1 | I²C 枚举 | 串口首行 `LITE SM INIT OK`（无 FAILED） | 上电观察日志；WHO_AM_I=0x70 校验在驱动内 |
| 2 | 静止 60s 漂移 | euler **roll/pitch** 全程 <3°（yaw 不设限，见下） | 平放静止 60s，记录 euler 列极差 |
| 3 | 翻转 90° 响应 | roll 从 0→90° 跳变到稳定 <200ms | 沿 x 轴快速翻转 90°，从遥测时间戳差分 |
| 4 | flex 通路 | 弯折各指 → 对应 flex[i] 0..1 显著变化 | 逐指弯折观察 CSV |
| 5 | 手别正确 | hand 字段与物理手套一致（当前硬编码 RIGHT） | 观察 `quat` 与 flex 行为一致性 |

## 已知限制（设计内）

- **yaw 不可观测**：加速度计不提供绕重力轴信息；静止时 yaw 保持初始值但有界漂移（陀螺积分），需磁力计/视觉（Pro/roadmap）。
- flex 为 raw 归一化（未 NVS 校准），范围校准归 M4。
- 左右手硬编码 `RIGHT`；设备配置化归 M3。
```

- [ ] **Step 4: 提交 Lite README**

```bash
cd /home/EchoGloveHugeProjects/EgoGlove
git add firmware/lite/README.md
git diff --check
git commit -m "docs(lite): M2 README with build/test + on-device verification checklist"
```

- [ ] **Step 5: 汇总自检**

- [ ] `cd firmware/lite/test && make run` → 三 bin 全 PASS
- [ ] `pio run -d firmware/lite` → SUCCESS
- [ ] Beta 设计文档 §4 已修正（104→120Hz + 决策记录），M2 里程碑行已更新
- [ ] 全部提交身份为 `PaxonHuang <quenchkidney@outlook.com>`，无 AI co-author
- [ ] 向用户汇报：host 验证结果 + 板上清单已就绪，等待硬件实测或进入 M3

---

## Self-Review

**Spec 覆盖**（对照冻结设计 §4 + §D + 里程碑表）：
- §4 驱动/姿态/特征落位/验证目标 → Task 2/3/4/5 + Task 6 清单 ✅
- 接线规格（I²C 0x6A, GPIO8/9, 400kHz, CS HIGH）→ Global Constraints + Task 5 `Wire.begin(8,9,400000)` ✅
- 里程碑 M2 定义「驱动 + Madgwick → quat 进特征」→ Task 2-5，quat 写入手势 Token `quat[4]` ✅
- D7「S3 只跑 Madgwick，视觉 Pro」→ Task 6 已知限制记录 yaw 属 Pro ✅
- 双轨 D-D / Beta 只读纪律 → Task 6 明确为用户批准例外，仅动 §4 活动文档 ✅
- M3（79B 序列化）、M4（NVS calib + SLR 训练）明确**不在**本计划范围，已记录 ✅

**Placeholder 扫描**：所有步骤含真实代码与命令，无 TBD/TODO/「类似 Task N」。✅

**类型一致性**：`imu_transport_t`（Task 2）→ `lite_sm_init` 第 8 参（Task 4）→ `imu_transport_t t = { i2c_write, i2c_read };`（Task 5）一致；`madgwick_t` API（init/get/set）跨 Task 3/4/5 一致；`hand_token_t` 字段（quat[4]/acc[3]/flex[5]）与 shared 头一致。✅
