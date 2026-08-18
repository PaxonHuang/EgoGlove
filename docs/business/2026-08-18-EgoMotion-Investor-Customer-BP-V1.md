# EgoMotion × 甲方需求确认及技术方案 V1

> **文档性质**：投资方 / 甲方技术负责人汇报与需求确认方案  
> **日期**：2026-08-18  
> **适用对象**：甲方技术负责人、投资方、EgoMotion 内部研发  
> **基线仓库**：`PaxonHuang/EgoGlove`（实现仓，分支 `feature/human-motion-infrastructure`，HEAD `f29f398`）；`PaxonHuang/EgoMotion`（伞仓）  
> **上游冻结**：Hand Token v2、canonical-20、wire protocol、firmware transport、V8 四模型语义边界（不变）

---

## 事实等级声明（贯穿全文）

本方案所有结论严格区分以下状态，**禁止把"设计目标"写成"已实现"，禁止把传感器规格写成整机实测指标**：

| 代号 | 含义 | 标记 |
|---|---|---|
| **A** | 已实现（代码存在 + 主机单测 PASS） | ✅ |
| **B** | 原厂 / 文档已确认（datasheet / 手册规格） | 📄 |
| **C** | 架构已设计（spec / ADR 已写，未实现） | 🏗️ |
| **D** | Demo 已部分验证（局部实物或仿真，未系统联调） | 🟡 |
| **E** | 设计目标（路线图，未实现未验证） | 🎯 |
| **F** | 待硬件验证（须 Demo1 实物实测） | 🔬 |
| **G** | 暂不承诺（当前阶段不适合对外承诺） | 🚫 |

凡证据不足处，明确写 **"待硬件验证"** 或 **"建议值 / 目标值"**。

---

## 01 项目定位

**EgoMotion = Human Motion & Tactile Data Acquisition Platform**。

不是"一个手套"，而是为 Physical AI / 具身智能提供多模态人手数据采集、标定、同步、标准化与导出的**数据基础设施**：

```
Sensor (IMU + Tactile)
  + Calibration (EgoCal)
  + Synchronization (SPEC-004 时间基)
  + Data Standard (EgoMotion Data Standard / Hand Token v2 + V8)
  + SDK (EgoMotion SDK)
  + Data Platform (EgoData)
  + Data Factory (EgoMotion Factory, 规模化采集)
  + Teleop (EgoTeleop, human → robot)
```

**商业定位**：从"数据手套"升级为 Physical AI 数据采集基础设施。手语翻译降级为 vertical application（不删除，保留为数据集入口）。

---

## 02 为什么需要 3D Tactile

| 维度 | 只有运动 (IMU) | 加上 3D Tactile |
|---|---|---|
| 采集内容 | 手部运动 | 手部运动 **+ 操作接触** |
| 可表征 | pose / joint | pose / joint **+ force / contact / slip** |
| Physical AI 训练价值 | 抓取的"动作" | 抓取的"**力-运动耦合**" |
| 对甲方商业价值 | 动作数据 | **接触与操控数据**，直接对接 manipulation / teleop |

**结论**：3D tactile 把 EgoMotion 从"动作采集"升级为"**操作采集**"，是 Physical AI 数据工厂的必要一层。

---

## 03 3D Tactile 技术路线对比

| # | 技术路线 | Fz | Fx/Fy | 空间分辨率 | 力分辨率 | 动态响应 | 静态保持 | 摩擦/滑移 | 成本 | 厚度 | 柔性 | 量产 | 标定 | 数据价值 | 适合 EgoMotion |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 单点 FSR / 压阻 | ✅ | ❌ | 单点 | 中 | 中 | 中 | ❌ | 极低 | 薄 | 高 | 高 | 易 | 低 | Lite 备选 |
| 2 | 多点压阻阵列 | ✅ | ❌ | 高(阵列) | 中 | 中 | 中 | 弱 | 中 | 中 | 中 | 中 | 中 | 中 | EgoTouch-Flex 候选 |
| 3 | 电容式 | ✅ | 部分 | 高 | 高 | 高 | 中 | 弱 | 中 | 中 | 中 | 中 | 难 | 中 | 备选 |
| 4 | 应变 / 压电 | ✅ | 部分 | 单点 | 高 | 高 | 弱 | 弱 | 中 | 中 | 低 | 中 | 中 | 中 | 量产力弱 |
| 5 | Hall / 磁触觉 | ✅ | ✅ | 中 | 高 | 中 | 高 | ✅ | 中 | 中 | 高 | 中 | 中 | 高 | **EgoTouch 自研中期** |
| 6 | xMR / TMR / GMR | ✅ | ✅ | 中 | 高 | 高 | 高 | ✅ | 中高 | 中 | 高 | 中 | 难 | 高 | Research 方向 |
| 7 | 光学 tactile (GelSight 类) | ✅ | ✅ | 极高 | 极高 | 中 | 中 | ✅ | 高 | 厚 | 低 | 低 | 难 | 极高 | Research / benchmark |
| 8 | **商用 3-axis force (HKVT-M3A)** | ✅ | ✅ | 单点 | 高(2%FS) | 高(200Hz) | 高 | 推导 | 低 | 薄 | 低 | 高 | 中 | 高 | **EgoTouch V0 / Ground Truth** |
| 9 | ReSkin / 磁弹性 | ✅ | ✅ | 中(分布) | 中 | 中 | 高 | ✅ | 中 | 薄 | 高 | 中 | 中 | 高 | **EgoTouch V2 自研** |
| 10 | 柔性大面积低成本 array | ✅ | 部分 | 高 | 中 | 中 | 中 | 弱 | 低 | 薄 | 高 | 高 | 中 | 中 | **EgoMotion Factory 长期** |

**结论（三阶段）**：
- **当前**：HKVT-M3A / 商用 3-axis force = **Ground Truth / EgoTouch V0**（📄 规格确认，🔬 待硬件验证）
- **中期**：EgoTouch magnetic tactile（Hall / 磁弹性）= **自研技术路线**（🎯 设计目标）
- **长期**：EgoTouch scalable tactile skin / array = **大规模数据采集工厂路线**（🌌 长期方向）

---

## 04 EgoTouch 技术方案

### 04.1 定义
**EgoTouch = 3D tactile / force sensing module**，不是一个"压力传感器"。

### 04.2 当前 V0
- 传感器：HKVT-M3A 3-axis force sensor（📄 原厂 Ver.01 手册为 source of truth）
- 原生输出：`Fx`, `Fy`, `Fz`（int16 little-endian raw ADC，6 字节）

### 04.3 工程定义
```
Normal Force:      Fn = |Fz|
Tangential Force:  Ft = sqrt(Fx² + Fy²)
Effective Friction: mu_eff ≈ Ft / (Fn + epsilon)
```

### 04.4 分层（HKVT 原生 vs EgoMotion Derived）

| 层 | 字段 | 是否 HKVT 原生 |
|---|---|---|
| Raw | timestamp, sensor_id, seq, clock_domain, fx_raw, fy_raw, fz_raw | ❌ raw 是 HKVT 输出但 timestamp/seq 由 MCU 打 |
| Calibration | zero_offset, K, calibration_id, calibration_version, calibration_timestamp | ❌ EgoCal |
| Derived | fx_N, fy_N, fz_N, force_norm, contact | ❌ EgoMotion Derived Layer |
| Future/reserved | slip, contact_centroid, dF_dt | ❌ Phase 2 |

**明确**：`contact` / `slip` / `friction` / `force_norm` **均不是 HKVT-M3A 原生输出**，属 EgoMotion Derived Layer。

### 04.5 HKVT-M3A 规格基准（📄 原厂 Ver.01 手册确认）

| 项 | 值 | 等级 |
|---|---|---|
| 3D force | Fx / Fy / Fz | 📄 |
| Fz (法向) | 15 N | 📄 |
| Fx / Fy (切向) | 10 N | 📄 |
| 精度 | 2% FS | 📄 |
| 安全过载 | 400% | 📄 |
| 工作电压 | 2.5 ~ 3.3 V | 📄 |
| 接口 | I2C | 📄 |
| I2C speed | 400 kHz | 📄 |
| 默认 7-bit 地址 | 0x0A | 📄 |
| ODR | 200 Hz | 📄 |
| XYZ 数据 | 6 字节, signed short int, little-endian | 📄 |
| READ_XYZ 命令 | **0x03** | 📄 |
| WRITE_ADDR 命令 | **0x1A** | 📄 |
| 地址约束 | 不能为 0x00 / 0xFF | 📄 |
| 地址持久化 | 写入 Flash, 掉电保持 | 📄 |
| 上电校准 | 约 1 秒（期间禁止 I2C 命令） | 📄 |
| 磁场警告 | 原厂明确提醒避免强磁场 | 📄 |

> **opcode 历史冲突声明**：旧版 `HKVT-M3A_Datasheet_v1.0.md` 中曾存在 `0x01 / 0x04` 的历史错误。现统一以原厂 Ver.01 用户手册为准：`READ_XYZ = 0x03`，`WRITE_ADDR = 0x1A`。**opcode 正确性最终须经真实硬件实测确认（🔬 待硬件验证）**，不重新把 0x01/0x04 带回主线。

---

## 05 Fx/Fy/Fz 与摩擦 / 滑移分析

### 05.1 可直接放 BP 的表述

> EgoMotion 不把摩擦力简单理解为一个额外传感器通道，而是将**三轴力矢量、时间序列、接触状态和手部运动联合建模**。通过法向力与切向力的关系获得有效摩擦表征，并进一步通过时间变化和相对运动识别**静态接触、临界滑移与动态滑移**。

### 05.2 工程公式

```
Fn      = |Fz|
Ft      = sqrt(Fx² + Fy²)
mu_eff  = Ft / (Fn + epsilon)

动态变化:
dFt/dt
dFz/dt
```

### 05.3 现状分级

| 项 | 状态 |
|---|---|
| 3D force vector (Fx/Fy/Fz) 采集 | 📄 规格 + 🏗️ driver 已写（🔬 待硬件） |
| contact / normal / tangential 派生 | 🎯 设计目标 / Phase 2 |
| incipient slip / dynamic slip 检测 | 🎯 算法路线 / **Phase 2，未实现** |
| mu_eff 计算 | 🎯 设计目标 |

**重要**：**不宣称已完成 slip detection**。当前应标为"算法路线 / Phase 2"。

---

## 06 当前 Demo 已实现能力

### 06.1 Demo Capability Matrix（投资方可读）

| Capability | Current Status | Evidence | Commercial Meaning |
|---|---|---|---|
| ESP32-S3 embedded acquisition | ✅ 代码 + 主机单测 | `firmware/lite/src/main.cpp`, platformio.ini, 120Hz sensor task + 10Hz telemetry | 现有 MCU 平台可采集 |
| LSM6DSV16X driver | ✅ 代码 + 单测 PASS | `firmware/lite/lib/LSM6DSV16X/`, `test_lsm6dsv16x.c` PASS | 6 轴 IMU 驱动就绪（单颗） |
| Sensor abstraction (transport-injected) | ✅ | `lite_sensor_manager.h`, `hkvt_m3a.h` transport 模式 | 驱动与 HAL 解耦，可移植 |
| Raw data pipeline | ✅ partial | hand_token raw + hkvt raw frame 结构定义 | 原始数据可结构化 |
| Timestamp architecture | 🏗️ 设计 + ✅ 字段存在 | sample 结构含 `timestamp_us`, `seq`, `clock_domain` | 多模态时间基已设计（🔬 实测未做） |
| Calibration architecture | 🏗️ 设计 + ✅ 结构存在 | `hkvt_m3a_calib_t` (zero_offset, K), SPEC-002 修订计划 | 标定框架就位（🔬 未实测） |
| 3-axis tactile spec integration | 📄 + ✅ driver(协议层) | `hkvt_m3a.{h,c}`, 16 单测 PASS, opcode 0x03/0x1A | 触觉协议层就绪（🔬 真机未验证） |
| Canonical data architecture | ✅ | Hand Token v2 + canonical-20, C/Python golden tests | 数据传输标准冻结 |
| Derived data architecture | ✅ partial | `hand_pose`, `joint_angles`, `tactile_force` 派生路径定义 | 派生层框架就位 |
| Future multi-sensor synchronization | 🎯 设计目标 | SPEC-004 提案, sync_error<1ms 目标 | 多传感器同步未实现 |

### 06.2 测试通过证据（2026-08-18 实测）

| 测试套 | 结果 | 命令 |
|---|---|---|
| firmware/shared (Hand Token + HKVT) | **104 PASS** (88 Hand Token + 16 HKVT) | `cd firmware/shared/test && make` |
| firmware/lite (LSM6DSV16X + Madgwick + LiteSensorManager) | **ALL PASS** | `cd firmware/lite/test && make run` |
| relay Python (hand_token + openxr + semantic_fixtures) | **15 PASS** | `python3 test_*.py` |

**全部为主机单测（host gcc / python3），无硬件实物测试。**

---

## 07 当前 Demo 尚未实现能力

| 模块 | 状态 | 说明 |
|---|---|---|
| 11 IMU 阵列物理集成 | 🎯 / 🔬 | 仅 1 颗 LSM6DSV16X（腕部）实现；11 颗是全新硬件 |
| HKVT-M3A 真机驱动 | 🔬 | driver 协议层已写，opcode 0x03/0x1A 未硬件实测 |
| I2C mux (TCA9548A) | 🚫 | **0 文件**，未实现 |
| Tactile acquisition task | 🚫 | 未实现 |
| 多传感器时间同步 | 🎯 | sync_error<1ms 是目标，未验证 |
| shape-aware calibration | 🎯 | SPEC-002 修订提案，未实现 |
| slip / contact_centroid / dF_dt | 🎯 | Phase 2 预留 schema |
| 数据 schema 落地 (`data/`) | 🚫 | `data/` 空 |
| SDK (`sdk/`) | 🚫 | `sdk/` 空 |
| ROS2 集成 | 🚫 | 未实现 |
| LeRobot exporter | 🚫 | 未实现 |
| 腕部 6DoF adapter | 🎯 | SPEC-005 提案，未实现 |
| 端到端系统联调 | 🔬 | 未做 |

---

## 08 甲方需求确认表（逐项填写）

> **来源**：甲方《需求确认清单_含Wuji参考值-回复.xlsx》（6 sheets：触觉/IMU/数据传输/数据格式/电源/机械）。下表"甲方填写"列为甲方在"选项/填写"中的实际填入值（下划线 `_..._` 内容）；"舞肌参考值"为竞品参考；"XSLAB 建议回复"为本方案逐项答复。状态标记同 §事实等级。

### A. 触觉传感器子系统（T01–T09）

| 编号 | 甲方确认项 | 甲方填写 | 舞肌参考值 | XSLAB 建议回复 | 状态 | 依据 | 风险/待验证 |
|---|---|---|---|---|---|---|---|
| T01 | 指尖传感器数量 | 5 指（勾选） | — | **5 指均配置触觉**（拇/食/中/无名/小） | 🏗️ 设计目标 | EgoTouch 路线 | 当前 V0 driver 仅支持 3 指(拇/食/中) 需求 🔬 |
| T02 | 每指尖通道数 | **8×8**（填入） | — | **拓扑不同：HKVT-M3A 是单点 3-axis force，非 8×8 阵列**。建议方案 C Hybrid：3-axis force + tactile skin（见 §12） | 🎯 设计目标 | HKVT datasheet | 拓扑差异须甲方确认；8×8 属 EgoTouch V2/Factory 🌌 |
| T03 | 其他触觉区域(指腹侧面) | 未明确 | — | Pro 默认仅指尖腹面；侧面扩展属 V2 skin 路线 | 🎯 | EgoTouch 路线 | 需甲方确认是否必须 |
| T04 | 单通道采样率 | **>70 Hz**（填入） | — | HKVT ODR 200Hz (📄) **满足 >70Hz** | 📄 | 原厂手册 | 真机 200Hz 行为 🔬 |
| T05 | 力量程最小值 | 未明确（0.1N / 0.05N） | — | HKVT 精度 2%FS, 量程 Fz 15N/Fx,Fy 10N；最小可分辨 ~0.15N(Fz)/~0.1N(Fx,Fy) | 📄 | datasheet | raw→N 换算 🔬 |
| T06 | 力量程最大值 | **>25N**（填入） | — | HKVT Fz=15N, 安全过载 400%(=60N)。**>25N 超出 Fz 量程**。【决策 2026-08-18】先与甲方沟通以我方实际量程为准；同时暂定方案 C（Hybrid，补大量程力传感器）或更换向量程更大的力传感器。 | 📄+⚠️ | datasheet | 量程匹配待甲方沟通确认 🔬 |
| T07 | ADC 分辨率 | 未明确（12/16 bit） | — | HKVT 输出 int16 signed short（16-bit 等效） | 📄 | 原厂手册 | — |
| T08 | 温度补偿 | "算法补偿，物理上无需测温"（填入） | — | HKVT 有温度寄存器 0x13 可读；算法补偿路线契合，硬件无需额外测温 | 📄+🎯 | datasheet §3.4 | 温度对力漂移影响 🔬 |
| T09 | 触觉接口方案 | "需讨论" | — | HKVT-M3A = I2C 400kHz, 4-Pin FPC, 默认地址 0x0A；多指需 TCA9548A mux 或改地址(0x1A) | 📄+🎯 | datasheet | 多指总线方案 🔬 |

### B. 位置传感器子系统 IMU（I01–I09）

| 编号 | 甲方确认项 | 甲方填写 | 舞肌参考值 | XSLAB 建议回复 | 状态 | 依据 | 风险/待验证 |
|---|---|---|---|---|---|---|---|
| I01 | 手指关节 IMU 数量 | **5**（填入） | 5(指尖EMF) | **EgoMotion Pro = 11 IMU**（每指 MCP+PIP=2×5 + Wrist 1）。甲方填 5(仅指尖) 对应 Lite 级或低密度配置 | 🎯 设计目标 | spec §3.1 | 总线方案 🔬 |
| I02 | 手掌 IMU 数量 | 未明确（1/2/0） | 1(手背) | **Pro 含 1 颗腕部 IMU**（11 颗之一）；与舞肌一致 | 🎯 | spec §3.1 | — |
| I03 | 总 IMU 数量 | **6**（填入） | 6(5EMF+1IMU) | 甲方 6 颗 = 5 指 + 1 掌；EgoMotion Pro 11 颗更高密度，Lite 6 颗与甲方一致 | 🎯 | D13 修订 | — |
| I04 | IMU 自由度 | 未明确（6/9 轴） | EMF 6DOF+IMU 6 轴 | **LSM6DSV16X = 6 轴（accel+gyro，无磁力计）**；绝对 yaw 需腕部 6DoF adapter(SPEC-005) | 📄+🚫 | datasheet | 绝对 yaw 暂不承诺 |
| I05 | 采样率 | **EMF 120Hz / IMU 800Hz**（填入） | 同 | LSM6DSV16X ODR 可配（现 lite 120Hz）；800Hz 需验证总线占用 | 📄+🔬 | datasheet+lite | 11 颗 800Hz 总线 🔬 |
| I06 | 加速度量程 | 未明确（±16g/±8g） | ±16g | LSM6DSV16X 支持 ±16g | 📄 | datasheet | — |
| I07 | 陀螺仪量程 | 未明确（±2000/±1000°/s） | ±2000°/s | LSM6DSV16X 支持 ±2000°/s；注意 deg→rad 转换(lite 已修) | 📄 | datasheet | — |
| I08 | 接口协议 | "EMF 无线接收 / IMU SPI"（填入） | 同 | **当前 lite 用 I2C**；11 颗建议 SPI 多 CS 或 I2C+TCA9548A。甲方偏好 SPI 与 EgoMotion Pro 路线可对齐 | 🎯 | spec §3.2 | 总线方案未验证 🔬 |
| I09 | 主 IMU 芯片 | 未明确 | ICM-20602 | **EgoMotion 选 LSM6DSV16X**（6 轴, 已实现 driver+单测）；ICM-42688-P/BMI270 为备选, 需重写 driver | ✅ LSM6DSV16X | lite 实测 | 换芯片须重写 driver |

### C. 数据传输与通信（D01–D11）

| 编号 | 甲方确认项 | 甲方填写 | 舞肌参考值 | XSLAB 建议回复 | 状态 | 依据 | 风险/待验证 |
|---|---|---|---|---|---|---|---|
| D01 | USB 功能 | 未明确 | 充电+数据 | **充电+数据**（与舞肌一致） | 🎯 | spec | — |
| D02 | USB 速率 | 未明确 | 12Mbps(全速,实际 RJ45) | 全速 12Mbps 可覆盖 11IMU+3 触觉数据量；如需 RJ45 属 base_station 范畴 | 🎯 | spec | 吞吐实测 🔬 |
| D03 | USB DFU 固件升级 | 未明确 | 是 | **支持**（ESP32-S3 原生 USB-DFU） | 🎯 | ESP32-S3 | — |
| D04 | 无线协议 | 未明确 | N/A(EMF 无线) | **BLE 5.x 为目标**（未实现）；舞肌用 EMF 无线属不同技术路线 | 🎯 | spec §5 | BLE 未实现 🔬 |
| D05 | 最小持续吞吐 | 未明确 | N/A | 11IMU@200Hz+3 触觉@200Hz ≈ <0.5Mbps，1Mbps 足够 | 🎯 | 估算 | 实测 🔬 |
| D06 | 实时最大延迟 | 未明确 | ≤10ms(有线) | **目标 USB ≤20ms / BLE ≤50ms**（spec §5）；≤10ms 有线可达 | 🎯 | spec §5 | 实测 🔬 |
| D07 | OTA 固件升级 | 未明确 | 是 | **BLE OTA 为目标**（未实现） | 🎯 | spec | — |
| D08 | 本地存储 | 未明确 | 否(依赖有线) | **首版不本地存储**（流式上传）；离线兜底属 V2 | 🚫 暂不承诺 | spec | — |
| D09 | 存储介质 | 暂无 | N/A | 随 D08，首版不做 | 🚫 | — | — |
| D10 | 最小写入速度 | 暂无 | N/A | 随 D08 | 🚫 | — | — |
| D11 | 最小存储容量 | 暂无 | N/A | 随 D08 | 🚫 | — | — |

### D. 数据格式与协议（F01–F06）

| 编号 | 甲方确认项 | 甲方填写 | 舞肌参考值 | XSLAB 建议回复 | 状态 | 依据 | 风险/待验证 |
|---|---|---|---|---|---|---|---|
| F01 | 序列化格式 | 未明确 | 二进制流(含 CRC) | **Hand Token v2 = 自定义二进制 + CRC16**（冻结 ✅）；开发期可 JSON 投影, 量产用二进制 | ✅ | golden tests | — |
| F02 | 触觉数据精度 | **32bit**（填入） | f32 归一化 | HKVT raw=int16；**Derived 层输出 f32（N 归一化）**，与甲方 32bit 一致 | 🎯 | spec §4 | — |
| F03 | IMU 输出格式 | 未明确 | 物理单位(m/s²,°/s) | **Raw 层保原始 ADC, Derived 层输出物理单位**（与舞肌一致, 强制 Raw/Derived 双存） | 🎯 | spec §4 | — |
| F04 | 时间戳精度 | 未明确 | ms 级 | **MCU 侧 timestamp_us 微秒级**（sample 结构已含）；多模态同步目标 sync_error<1ms | 🎯 | spec §4/5 | 实测 🔬 |
| F05 | 数据发送模式 | 未明确 | 持续流式 120Hz | **持续流式**（与舞肌一致）；事件触发为 V2 | 🎯 | spec | — |
| F06 | 数据压缩 | 未明确 | 否 | **首版不压缩**（与舞肌一致） | 🚫 暂不承诺 | — | — |

### E. 电源与功耗（P01–P04）

| 编号 | 甲方确认项 | 甲方填写 | 舞肌参考值 | XSLAB 建议回复 | 状态 | 依据 | 风险/待验证 |
|---|---|---|---|---|---|---|---|
| P01 | 电池容量 | 未明确 | N/A(有线) | 首版倾向**有线供电**（与舞肌一致）；电池容量待 PCB 定型 | 🚫 暂不承诺 | spec | 🔬 |
| P02 | 目标续航 | 未明确 | N/A | 随 P01，首版不承诺续航 | 🚫 | — | 🔬 |
| P03 | 充电方式 | 未明确 | USB-C PD | **USB-C**（ESP32-S3 原生 USB） | 🎯 | ESP32-S3 | — |
| P04 | 边充边用 | 未明确 | N/A | 首版有线供电即支持边用边充 | 🎯 | spec | — |

### F. 机械与可靠性（M01–M04）

| 编号 | 甲方确认项 | 甲方填写 | 舞肌参考值 | XSLAB 建议回复 | 状态 | 依据 | 风险/待验证 |
|---|---|---|---|---|---|---|---|
| M01 | FPC 弯曲寿命 | 未明确 | ≥10 万次 | HKVT FPC 0.3mm 厚; **目标 ≥10 万次**(与舞肌一致); 待整机 FPC 设计验证 | 🎯 | datasheet+舞肌 | 🔬 |
| M02 | 工作温度 | 未明确 | -5~40°C | HKVT -20~85°C(📄); 系统目标 0~45°C(可穿戴常用) | 📄+🎯 | datasheet | 整机 🔬 |
| M03 | 防护等级 | 未明确 | 无标称(实验室) | 首版**实验室级, 无 IP 标称**(与舞肌一致); IP54 属 V2 | 🚫 暂不承诺 | — | — |
| M04 | 集成方式 | 未明确 | 布料缝入式 | **缝入织物**(与舞肌一致) | 🎯 | spec | 整机机械 🔬 |

---

## 09 IMU 方案

- **型号**：LSM6DSV16X（6 轴 accel + gyro，无磁力计）📄
- **Lite**：6 IMU（D13 修订，放弃 flex）🎯
- **Pro**：11 IMU（每指 MCP+PIP=2×5 + Wrist 1）🎯
- **Research**：15+ IMU（FSGlove 类，论文/benchmark，不量产）🌌
- **总线**：11 颗 I2C 地址仅 2 个，需 TCA9548A mux / SPI 多 CS / 多 controller，**接法未验证（🔬）**
- **同步**：MCU 侧 hw_timestamp + ODR 同步启动，**sync_error <1ms 是目标（🔬）**

---

## 10 数据传输方案

- **Wire protocol**：Hand Token v2（冻结 ✅，C/Python golden tests PASS）
- **特性**：紧凑、自描述、可校验、canonical-20 旋转拓扑 + FK21 派生 21 点
- **目标延迟**：USB <20ms, BLE <50ms（🎯 未实测）
- **抽象**：transport-injected driver（驱动与 HAL 解耦）

---

## 11 数据格式方案

**沿用 V8，不重写 canonical schema**：

```
Sensor
  ↓
Raw Frame (timestamp, sensor_id, seq, clock_domain, fx/fy/fz_raw 或 IMU raw)
  ↓
Decode
  ↓
Timestamp (SPEC-004)
  ↓
Calibration (SPEC-002)
  ↓
Normalized Observation (V8 Observation Layer)
  ↓
Motion / Tactile Derived (hand_pose, joint_angles, tactile_force, contact)
  ↓
Episode (V8 Episode Model)
  ↓
Dataset Projection (ROS2 / Unity / MANO / LeRobot / RLDS / Teleop)
```

**原则**：EgoMotion Canonical Data 是核心，通过 projection 对接下游，**不把 EgoMotion 格式强行定义成 LeRobot 或 RLDS**。

---

## 12 针对甲方 5 指 / 8×8 / 24 通道需求

**甲方要求**：5 fingertips × 8×8 tactile channels × >70Hz。  
**当前 HKVT-M3A**：单点 3-axis force, 200Hz。  
**二者不是同一种 sensing topology**，必须明确区分：

| 方案 | 拓扑 | 优势 | 适合 |
|---|---|---|---|
| **A. 5 × 3-axis force** | 5 个单点 3D 力 | 高质量 3D force / 低通道数 | Demo / benchmark / manipulation force |
| **B. 5 × tactile arrays (8×8)** | 5 个空间分布阵列 | 空间分布 / contact map | 压力分布图 |
| **C. Hybrid (推荐)** | 3-axis force + tactile skin | 既有力矢量又有空间图 | **EgoTouch Pro/Research 方向** |

**建议**：**不要为迎合 8×8 而牺牲 3D force**。应将 **Force Vector + Spatial Tactile Map** 设计成两层互补 sensing。8×8 阵列属 EgoTouch V2/Factory 路线（🌌），当前 V0 用 HKVT 3-axis force（📄+🔬）。

**T06 量程冲突提示**：甲方填入力量程最大值 **>25N**，而 HKVT-M3A Fz 量程仅 **15N**（安全过载 400% = 60N）。

**【决策 2026-08-18】**：
1. 先与甲方沟通，以我方实际量程为准（HKVT Fz 15N / Fx,Fy 10N）；
2. 同时暂定方案 C（Hybrid，补大量程力传感器）或更换向量程更大的力传感器，作为备选技术路线。

此项待甲方沟通后最终冻结。

---

## 13 摩擦（动态/静态）回答

见 §05。要点：
- 传感器直接获得 **3D force vector**
- 结合时间序列 + 接触 + 手部运动**推导** contact / normal / tangential / mu_eff / incipient slip / dynamic slip
- **不宣称已完成 slip detection**（算法路线 / Phase 2）

---

## 14 技术成熟度定位

| Stage | 内容 | EgoMotion 状态 |
|---|---|---|
| 0 架构 / 规格 | spec / ADR / V8 | ✅ 完成 |
| 1 单传感器验证 | 单颗 IMU + HKVT 协议层 | ✅ 单颗 IMU；HKVT 🔬 待硬件 |
| 2 多传感器采集 | 11 IMU + 3 tactile | 🎯 未实现 |
| 3 同步多模态采集 | IMU↔tactile 同步 | 🎯 未实现 |
| 4 标定 + 触觉派生 | shape-aware + contact/slip | 🎯 未实现 |
| 5 数据工厂 | 多设备并发 + provenance | 🌌 长期 |
| 6 机器人遥操作 | ROS2 + LeRobot | 🌌 长期 |
| 7 Embodied AI 数据基础设施 | foundation-model 飞轮 | 🌌 长期 |

**当前定位：Stage 0 完成 + Stage 1 部分（单颗 IMU 已验证，HKVT 待硬件）。**尚未进入 Stage 2。

---

## 15 当前风险

| 风险 | 等级 | 说明 |
|---|---|---|
| HKVT opcode 真机不符 | 🔬 高 | 0x03/0x1A 来自原厂手册但未硬件实测 |
| 11 IMU 总线方案 | 🔬 高 | TCA9548A/SPI/多 controller 三选一未验证 |
| 多传感器同步 | 🔬 中 | sync_error<1ms 目标，HKVT 无 sensor-side timestamp |
| raw→N 换算 | 🔬 中 | 原手册未给完整线性公式 |
| BLE 吞吐 | 🔬 中 | 未实测 |
| 量产一致性 | 🌌 高 | 未量产，Factory 长期 |
| 强磁场环境 | 📄 中 | 原厂警告，使用环境须规避 |

---

## 16 待硬件验证清单

1. HKVT-M3A READ_XYZ = 0x03 在真机有效（6 字节, 第6字节 NACK+STOP）
2. HKVT-M3A WRITE_ADDR = 0x1A 真机有效（掉电保持）
3. HKVT-M3A 200Hz ODR 真机行为
4. 3 颗 HKVT 地址冲突解决方案（改地址 0x1A）
5. 11 颗 LSM6DSV16X 总线方案（TCA9548A×2 / SPI / 多 controller）
6. DRDY/INT 引脚路由、GPIO/CS 资源
7. USB 吞吐、buffer/ISR/DMA 任务划分
8. IMU↔tactile sync_error（目标 <1ms）
9. raw→Newton 精确换算公式
10. fps / drop_rate / jitter / latency 实测值
11. sensor_noise vs datasheet 典型值
12. orientation_error vs 光学参考
13. tactile_error vs 标定砝码

---

## 17 产品线统一

| 实体 | 名称 | 能力 |
|---|---|---|
| 生态/平台 | EgoMotion | — |
| 手套 Lite | EgoMotion Glove Lite | IMU + basic hand motion |
| 手套 Pro | EgoMotion Glove Pro | IMU + tactile + wrist |
| 手套 Research | EgoMotion Glove Research | high-density IMU + tactile + raw + advanced sync |
| 触觉 | EgoTouch | 3D tactile / force |
| SDK | EgoMotion SDK | 开发者接入 |
| 数据平台 | EgoData | 数据管理 |
| 数据标准 | EgoMotion Data Standard | 标准化 |
| 遥操作 | EgoTeleop | human → robot |
| 标定 | EgoCal | 个体化标定 |
| 工厂 | EgoMotion Factory | 规模化采集 |
| 旧名 | EchoGlove | 历史 lineage 保留，不制造新命名冲突 |

**三种产品软件数据接口尽可能统一**。

---

## 18 EgoTouch 产品路线

| 版本 | 内容 | 状态 |
|---|---|---|
| **V0** | 商用 3D force sensor (HKVT-M3A) 集成 | 📄+🔬 driver 协议层已写，待硬件 |
| **V1** | 3D tactile + calibration + contact/slip analytics | 🎯 设计目标 |
| **V2** | 可替换 tactile skin / 磁弹性 | 🎯 自研路线 |
| **Factory** | 低成本、高一致性、大面积、可量产 tactile acquisition module | 🌌 长期 |

**不把未来方案说成已完成。**

---

## 19 技术路线图（Phase 1/2/3）

| Phase | 周期 | 目标 | 交付物 |
|---|---|---|---|
| 0 架构冻结 | 第1周（✅） | 修订 D6/D10/D12, 命名冻结, 目录定型 | 本 spec + ADR-001/002 |
| 1 Pro V1 原型 | 2-4 周 | Demo1: 11IMU+三指触觉+ESP32-S3 稳定采原始数据 | hardware BOM, firmware 采集, I2C mux 同步 |
| 2 数据契约层 | 3-5 周 | SPEC-003/004/006/007 落地, Raw/Derived/Metadata + quality manifest | data schemas, acquisition pipeline, LeRobot exporter 雏形 |
| 3 标定系统 | 4-6 周 | shape-aware calibration | EgoCal 雏形 |
| 4 腕部 6DoF | 5-8 周 | SPEC-005 可插拔接口 (Level0 IMU → Level1 SteamVR) | wrist adapter |
| 5 EgoTouch V0 | 7-10 周 | contact/slip 语义完整 | 触觉语义分层全通 |
| 6 机器人/导出 | 8-12 周 | ROS2 + LeRobot exporter + DexRetargeting | EgoTeleop 雏形 |
| 7 数据工厂 | 12-16 周 | 多设备并发采集 + provenance 飞轮 | EgoData V1 |

**Phase 0 不做**：新手语模型 / LLM / Transformer / EMG / App 大改 / 云平台大改。

---

## 20 面向甲方的最终建议

1. **触觉拓扑**：当前 V0 用 5×3-axis force（HKVT），不为迎合 8×8 牺牲三维力；Hybrid (force + skin) 为 Pro/Research 方向。
2. **数据标准优先**：先冻结 EgoMotion Data Standard（Raw/Derived/Metadata + quality manifest），再扩硬件。
3. **硬件验证节奏**：Phase 1 先做 Demo1 实物（11IMU+3 tactile），把 13 项待硬件验证清单逐条闭环。
4. **不承诺未验证项**：所有 🔬 项在实测前不写入对外性能承诺。
5. **甲方可共定义**：下一代采集设备的触觉拓扑（force vs array vs hybrid）、ODR、通道数、同步精度门槛，可与甲方在 Phase 1 实测数据基础上共同冻结。

---

## 21 商业价值速查（每个技术模块三问）

| 模块 | 技术上是什么 | 为什么重要 | 对甲方商业价值 |
|---|---|---|---|
| **Time Synchronization** | 统一 IMU + tactile timestamp | 保证多模态对齐 | 数据可用于 Physical AI training |
| **Calibration (EgoCal)** | sensor + 个性化标定 | 跨用户/跨设备一致 | 数据可复用、可对比 |
| **Tactile (EgoTouch)** | 3D force + tactile | 从运动数据升级到操作/接触数据 | 对接 manipulation / teleop |
| **Data Standard** | canonical schema | 统一格式 | 降低跨硬件/客户/机器人平台转换成本 |
| **SDK** | 开发者接入 | 降低集成门槛 | 甲方团队可快速二次开发 |
| **EgoData** | 数据管理 + provenance | 可审计、可追溯 | 数据资产化、合规 |
| **EgoTeleop** | human → robot | 直接驱动机器人 | 遥操作 / 示教场景 |
| **EgoMotion Factory** | 规模化采集 | 并发多设备 | 数据工厂量产 |

---

## 附录 A：工程问题记录（不改主线）

本次审计发现以下工程问题，按 §19 指令**仅记录，不自行改主线**：

### A.1 HKVT driver header 引用过时 datasheet 文件名
- **[Engineering Issue]** `firmware/shared/hkvt_m3a.h` 第 31 行注释引用 `datasheet/HKVT-M3A_Datasheet_v1.0.md`，该文件已被 `HKVT-M3A_M3A-T_V2.1_Agent_Canonical.md` 取代（datasheet 目录中 v1.0 文件已不存在）。
- **[Impact]** 注释引用失效；不影响代码逻辑。
- **[Recommendation]** 将 header 注释更新为指向 `HKVT-M3A_M3A-T_V2.1_Agent_Canonical.md`，并保留"opcode 历史冲突已修正，以原厂 Ver.01 manual 为 source of truth"声明。
- **[Mainline Change Required?]** **YES**（文档注释修正，须用户批准后改主线）。

### A.2 HKVT driver opcode 真机未验证
- **[Engineering Issue]** driver 已写 0x03/0x1A（来自原厂手册），但未硬件实测。
- **[Impact]** 真机若 opcode 不符，driver 须改。
- **[Recommendation]** Phase 1 硬件验证时优先闭环。
- **[Mainline Change Required?]** NO（仅验证，不改代码直至实测）。

### A.3 工作树存在未追踪构建产物
- **[Engineering Issue]** `firmware/shared/test/test_hand_token`、`test_hkvt_m3a` 等二进制在 git status 中显示为 modified/untracked。
- **[Impact]** 无功能影响；建议加入 .gitignore。
- **[Recommendation]** 将测试二进制加入 .gitignore。
- **[Mainline Change Required?]** YES（.gitignore 微调，须用户批准）。

---

## 附录 B：审计基线（2026-08-18 实测）

- 仓库：`PaxonHuang/EgoGlove`，分支 `feature/human-motion-infrastructure`，HEAD `f29f398`
- 测试：firmware/shared 104 PASS，firmware/lite ALL PASS，relay 15 PASS（全主机单测）
- 文件：HKVT driver `firmware/shared/hkvt_m3a.{h,c}` + 16 测试存在；TCA9548A 0 文件；tactile acquisition 0 文件；`data/` `sdk/` `models/*` 空
- datasheet：`HKVT-M3A_M3A-T_V2.1_Agent_Canonical.md`（1584 行，2026-08-18）为当前 source of truth
- CBM datasheet 项目：776 节点（2026-08-18 重索引）

---

*本方案所有 🔬 项在硬件实测前不构成对外性能承诺。EgoMotion 保留根据 Phase 1 实测结果调整方案的权利。*
