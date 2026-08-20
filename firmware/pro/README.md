# EgoGlove firmware/pro — Demo1 Phase 1B (native ESP-IDF, ESP32-S3)

Demo1 = **EgoGlove Pro Engineering Validation Prototype**: ESP32-S3 + 11×LSM6DSV16X +
3×HKVT-M3A, unified acquisition timeline → USB. Phase 1B advances the **single
LSM6DSV16X** acquisition path first; the 11-IMU (1C) and 3×HKVT (1D) are later.

## Status (2026-08-20)

| 项 | 状态 | 证据 |
|---|---|---|
| `firmware/pro` native ESP-IDF 工程 | ✅ **build OK** (ESP-IDF v6.0.2, target esp32s3) | `build/egoglove_demo1_p1b.bin` (0x2e960 B) |
| 复用 Lite LSM6DSV16X 核心（未改） | ✅ byte-identical 复用 | `components/lsm6dsv16x/` = `firmware/lite/lib/LSM6DSV16X/` |
| ESP-IDF I2C transport adapter | ✅ 实现 | `components/imu_i2c_adapter/` |
| Raw / Derived / Metadata 分离 | ✅ raw accel/gyro + sensor_id/seq/timestamp_us/quality | `main/demo1_imu_acq.{h,c}` |
| 200Hz（HAODR）配置 | 🟡 **code-level, datasheet-derived, NOT HW-verified** | `main/demo1_imu_acq.c` |
| 真实硬件采集（真 LSM6DSV16X read） | 🔬 **未验证**（本环境无连接 ESP32-S3 + 传感器） | 需实机 |

> Phase 1B 的完成判据 = 真实硬件上单颗 LSM6DSV16X 能经 WHO_AM_I + 寄存器配置后，
> 通过 ESP-IDF I2C 读到真实 accel/gyro，并产出带 timestamp/seq/raw/quality 的样本流。
> 当前只有 **code + build 验证**；**真实硬件验证仍是唯一缺口门**。

## 200Hz 目标（数据手册核实）

**LSM6DSV16X 无原生 200Hz ODR**（高性能模式最近为 240Hz）。精确 200Hz 只能经
**High-Accuracy ODR (HAODR)** 模式：`HAODR_SEL_[1:0]=10` + ODR code `0111` →
200Hz（`docs/datasheet/lsm6dsv16x.md` §6.5 / Table 20）。本工程按此 datasheet 路线
配置（OP_MODE=001 + HAODR_EN + HAODR_SEL=10 + ODR=0111）。**该路径为 datasheet-
derived，未在真实芯片上验证**——必须实机确认后才把 200Hz 视为达成，绝不静默降
到 120Hz 蒙混。

## 复用清单

- **未改动**：`components/lsm6dsv16x/*`（与 `firmware/lite/lib/LSM6DSV16X/*` 逐字节一致；
  M2 host-verified）。寄存器逻辑零改写。
- **新增**：`components/imu_i2c_adapter/`（唯一 ESP-IDF 专属层，实现 `imu_transport_t`）、
  `main/demo1_imu_acq.{h,c}`（single-sensor 采集 + 200Hz 配置 + 错误/恢复）、
  `main/demo1_main.c`（app_main + 采集任务 + replay-able 输出）、`main/demo1_config.h`。

## 构建

```bash
. /root/.espressif/v6.0.2/esp-idf/export.sh
cd firmware/pro
idf.py set-target esp32s3     # 首次
idf.py build
```

## 烧录与输出（需真实硬件）

```bash
cd firmware/pro && idf.py -p PORT flash monitor   # 115200
```

每样本一行（raw 字节 + 全部 metadata，离线可回放）：
```
t=<us> seq=<n> sid=<id> st=<status_hex> q=<quality_hex> g=<12hex> a=<12hex>
```

## 错误/恢复

- I2C / STATUS 读取失败 → 样本打 quality 标志并跳过；连续失败达到阈值 →
  重新 `lsm6dsv16x_init()` + 200Hz 重应用。
- 初始化失败 → 明确上报并退避重试，**不伪装成功**。

## 已知限制（设计内）

- 本阶段只采集 **单颗** LSM6DSV16X，不涉及 11-IMU 同步、HKVT、姿态融合或运动学。
- `demo1_config.h` 的 I2C 引脚为 Phase 1B 单传感器测试节点默认值；若存在 PCB pinmap 请按实机更新（NOT HW-verified）。
- offline raw replay 作为后续 Gate（raw 已完整保留可回放，此处不建 replay 子项目）。

## 相关性文档

- 伞仓真相源：`EgoMotion/docs/STATUS.md`、`DOC_MATRIX.md`
- 传感器总线：`EgoGlove/docs/superpowers/specs/adr/ADR-002-sensor-bus-topology.md`
- Firmware 架构：`docs/V7/ARCHITECTURE.md`（历史基线）、`docs/V8/`（语义层，未实现）
