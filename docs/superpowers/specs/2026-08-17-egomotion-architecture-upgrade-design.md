# EgoMotion 架构升级设计 (2026-08-17)

> 状态：Architecture proposal（待用户审阅批准）
> 日期：2026-08-17
> 路径：Brainstorming architectural path
> 上游冻结（不变）：Hand Token v2、canonical-20、wire protocol、firmware transport、V8 四模型语义边界
> 本 spec 不写代码、不改 wire、不改 firmware

---

## 0. 背景与目标

投资方催研发升级，目标对接具身智能数据采集工厂，新增触觉方案。本设计把 EgoGlove 从"手语翻译手套"升级为 **Human Motion & Tactile Data Infrastructure**，作为 EgoMotion 生态主线。手语降级为 vertical application（不删除，保留为数据集入口）。

**核心约束（用户明确）**：
- 不做新手语模型 / LLM / Transformer / EMG / App 大改 / 云平台大改
- 数据采集必须同时保存 Raw、Derived、Metadata
- 数据质量指标必须正式定义
- 选择性兼容升级，不重写全部代码；必要时接受修订被冻结的 SPEC/TRD/TSD

**已实现资产（冻结保留）**：Hand Token v2 codec/FK21、C/Python golden 测试、OpenXR offline ingest、semantic_fixtures（位于 EgoGlove 仓库 `relay/`、`firmware/shared/`）。V8 architecture freeze review 已通过，明确不需要修改 Hand Token v2 / canonical-20 / wire protocol / firmware。

---

## 1. 战略决策（用户拍板）

### 1.1 全面采纳 0816 三级硬件

正式修订 V7 STRATEGY 的 D6/D10/D12：

| 决策 | V7 冻结内容 | 修订后（0816） |
|---|---|---|
| D6 | Lite=flex(5)+单腕IMU | 修订：Lite=6 IMU 放弃 flex（保留 supersede 记录）|
| D10 | Lite 维持 flex+单IMU、Pro 多IMU 仅路线图；**D10 详解含"不启 IMU 阵列竞争——不做每指节 9 轴 IMU 军备竞赛"硬约束** | 修订：Pro=11 IMU+触觉+腕部6DoF接口；**明确删除 D10 详解的 IMU 阵列军备竞赛禁令**（保留 supersede 记录）|
| D12 | **不启 IMU 阵列竞争** | 修订：FSGlove 类多 IMU 三级硬件；**明确删除 D12 的阵列竞争禁令**（保留 supersede 记录）|
| D3/D11 | canonical-20 + Hand Token v2 + 双表示层 | 不变（冻结保留），升格为 EgoMotion Data Standard |

flex 降级为 experimental/低成本分支，不进 Pro 主线。Research=15+IMU（FSGlove 类，论文/benchmark 用，不量产）。

### 1.2 触觉三指定位

触觉三指（拇/食/中）只放 Pro，Lite 不带触觉。保持"一套软件三种硬件、能力清晰分级"。

---

## 2. 目录 / 仓库名 / 产品线命名

### 2.1 Repository Topology（2026-08-17 用户冻结，见 ADR-001）

| GitHub 仓库 | 角色 | 本地路径 | 关系 |
|---|---|---|---|
| `PaxonHuang/EgoMotion` | **Umbrella / Platform / Architecture 仓**（导航、roadmap、跨仓 spec、ADR、Data Standard、集成契约、产品线关系）| `/home/EchoGloveHugeProjects/EgoMotion`（不变）| 文档链接指向 EgoGlove 实现仓，不用 submodule |
| `PaxonHuang/EgoGlove` | **Glove Implementation 仓**（firmware、relay、Hand Token v2、canonical-20、FK21、OpenXR adapter、V8 实现、未来触觉集成、对应测试）| `/home/EchoGloveHugeProjects/EgoGlove`（不变）| 不搬移、不重写 |

**冻结原则**：不 rename、不改本地目录、不改父目录 `EchoGloveHugeProjects`、不改 remote URL、不引入 submodule。仓库名 ≠ 产品品牌名。EgoMotion 伞仓**不提前建** firmware/hardware/algorithms/models/simulation/web/data 等空目录（YAGNI）；只有当某模块具备独立生命周期/CI/版本/依赖/贡献者/规模时才拆仓。

**依赖机制**：当前用文档链接 + 显式版本契约 + Git references/releases（真正需要时），不用 submodule。

### 2.2 未来产品线关系（导航，不预建仓库）

```
EgoMotion Platform (umbrella)
├── EgoGlove       → Wearable Motion Capture Implementation（现有实现仓）
├── EgoTouch       → Tactile Subsystem（Phase 3+，条件满足才拆）
├── EgoData        → Dataset / Data Infrastructure（Phase 7+）
├── EgoTeleop      → Robotics / Teleoperation Integration
└── EgoCal         → Calibration Infrastructure
```

实现仓内增量目录（纯新增，不破坏现有 `firmware/{lite,pro,shared}`、`relay/`、`models/`、`sdk/`、`web/`）：
- `firmware/pro/tactile/`（触觉驱动，进入 Phase 1 实现时）
- `relay/tactile_adapter.py`
- `data/{schemas,acquisition,quality,provenance,episodes,exporters/}`
- `docs/specs/`（SPEC-003/004/005）
- `docs/superpowers/specs/adr/`（ADR-001 起）

### 2.3 产品线命名表

| 实体 | 名称 |
|---|---|
| 生态/平台 | EgoMotion |
| 手套 Lite | EgoMotion Glove Lite |
| 手套 Pro | EgoMotion Glove Pro |
| 手套 Research | EgoMotion Glove X |
| 触觉子系统 | EgoTouch（Touch-Core / Touch-Skin / Touch-Flex）|
| SDK | EgoMotion SDK |
| 数据平台 | EgoData |
| 数据标准 | EgoMotion Data Standard |
| 机器人遥操作 | EgoTeleop |
| 标定 | EgoCal |
| 旧名 | EgoMotion Glove (formerly EchoGlove) |

---

## 3. 首个原型：EgoMotion Glove Pro V1（Demo1）

### 3.1 硬件配置（事实分级）

**A 类（已核实事实）**：
- IMU：LSM6DSV16X（6 轴 accel+gyro，无磁力计；有 `docs/datasheet/lsm6dsv16x.md` 与 V7 BOM/wiring 依据）
- 触觉：HKVT-M3A（datasheet v1.0 已核实：三轴 Fx/Fy/Fz；Fz 0~15N、Fx/Fy±10N；±2%FS；ODR 固定 200Hz；4-Pin FPC I2C 400kHz；默认 7-bit 地址 0x0A；小端 int16 raw ADC；上电静置≥1000ms；读力命令 0x03 读 6 字节，第 6 字节必须 NACK+STOP；改地址命令 0x1A。**opcode 经 datasheet-vs-原厂手册冲突修正，须硬件实测确认**）
- MCU：ESP32-S3（V7 BOM 有据）
- 数量：11 × LSM6DSV16X（每指 MCP+PIP=2×5 + Wrist 1）、3 × HKVT-M3A（拇/食/中）

**B 类（0816 设计建议）**：11 IMU Pro 布局、三级硬件分级。

**C 类（未验证工程假设，须 Demo1 前/中实测）**：
- 11 颗 LSM6DSV16X 在 ESP32-S3 上的总线方案（I2C mux TCA9548A×2 vs SPI 11-CS vs 多 I2C controller）——LSM6DSV16X I2C 地址仅 2 个，>2 颗需 mux 或改地址或分总线，**具体接法未验证**
- DRDY/INT 引脚路由、GPIO/CS 资源是否够用、USB 吞吐、buffer/ISR/DMA 任务划分
- 3 颗 HKVT-M3A 地址冲突解决方案（见 §Part B.3）
- HKVT-M3A 与 IMU 时间对齐机制（HKVT **无 sensor-side hardware timestamp 规格**，须 MCU 侧打时间戳）

**D 类（必须 Demo1 实测冻结）**：fps、drop_rate、jitter、latency、sync_error 等质量指标的实际值（见 §5）。

> 纪律：C/D 类内容不得以"已确定架构"口吻写入 TRD/TSD，须标注"待验证假设"。

### 3.2 工程风险与对策（C/D 类，须验证）

1. **11 IMU 总线**：I2C mux 分组 / SPI 多 CS / 多 controller 三选一，**未验证**。须 PCB 原理图 + 实测总线占用确认。
2. **采样同步**：11 IMU 轮询导致时间错位。对策方向：MCU 侧 hw_timestamp（每帧带 MCU tick + seq）+ ODR 同步启动。**sync_error <1ms 是目标，非已验证**。
3. **触觉-运动时间对齐**：HKVT-M3A 无 sensor-side timestamp 规格，须 MCU 在读取时刻打 timestamp。对策方向：acquisition task 统一时间基。**未验证**。
4. **LSM6DSV16X 无磁力计**：绝对 yaw 不存在。对策：不依赖 SFLP 作最终姿态，走 raw→bias→fusion→kinematic constraint→FK/MANO。

### 3.3 触觉语义分层（EgoTouch）

```
raw_tactile → calibrated_tactile → contact → contact_residual
           → contact_point → force(Fx,Fy,Fz,Tx,Ty,Tz) → slip
```

**Demo1 最小实现**：`raw_tactile`（HKVT 6 字节 raw ADC）+ `force(Fx,Fy,Fz)`（标定后）+ `contact`(bool)。slip / contact_centroid / dF_dt **预留 schema，Phase 2 实现**。

明确：`force_norm` / `contact` / `slip` / `contact_centroid` / `dF_dt` 均**非 HKVT-M3A 原生输出**，属 EgoMotion Derived Layer。

触觉三层：
- Touch-Core = HKVT-M3A（已核实，benchmark 候选；0816 另推荐 PaXini PX-6AX 作更高精度 ground-truth，未采购）
- Touch-Skin = ReSkin-like 磁弹性（Phase 3 自研）
- Touch-Flex = FlexiTac-like 压阻（低成本量产分支）

---

## 4. 数据契约：Raw / Derived / Metadata 与 V8 四模型归属

### 4.0 层级归属（对齐 V8，不重复定义）

| 数据类 | 归属层 | 与 V8 关系 |
|---|---|---|
| **Raw** | **Acquisition Layer**（V8 未显式定义，位于 Hand Transport Layer 之下、sensor 边界之外）| V8 Observation 的 `raw_transport_ref` 只引用 Hand Token frame/sequence；设备侧原始 IMU/tactile 采样低于 transport 层，需本 spec 显式定义 acquisition layer |
| **Derived** | **Observation Layer 的输入 / 字段**| V8 Observation §2 `motion{canonical_20_rotation, joint_angles}` 是 source of truth；本 spec 的 `hand_pose`/`joint_angles` 即 Observation motion 字段，不另立第二套。Derived 是产生 Observation 的过程，Observation 是 decode 后的 semantic container |
| **Coordinate transform** | **Coordinate Profile**（V8 独立模型）| 不归 metadata 字段；变换链记录在 Provenance transformations[] |
| **Provenance** | **V8 Provenance 独立模型**（source/acquisition/transformations/validation/policy 五块）| **不降级为 metadata 字段**；spec §4.3 的 `provenance` 字段是对 ProvenanceRecord 的引用（provenance_ref），不是把整个 provenance 塞进 metadata |
| **quality manifest** | **SPEC-007 Provenance & Quality** 定义、随 Episode 存 | V8 Observation 有 quality 四正交概念（availability/validity/confidence/uncertainty），Episode 有 masks/quality[t]；本 spec §5 的 11 项指标是 quality 的**可计算度量**，须与 V8 四概念对齐映射（见 §5.1）|

### 4.1 Raw（原始，不可变，永不丢弃，属 Acquisition Layer）

- `raw_imu[11]`：每颗 LSM6DSV16X 的 accel(3)+gyro(3) 原始 ADC
- `raw_tactile[3]`：三指 HKVT-M3A 原始 6 字节 ADC（Fx_raw/Fy_raw/Fz_raw）
- `raw_wrist`：腕部 IMU（11 颗之一）
- 必带 `sensor_id`、`hw_timestamp`(MCU tick)、`seq`、`clock_domain`
- HKVT-M3A 无 sensor-side timestamp，hw_timestamp 由 MCU 在读取时刻打入

### 4.2 Derived（派生，可重算，产生 Observation）

- `hand_pose`：canonical-20 旋转 + FK21 派生 21 点 → 填入 Observation.motion
- `joint_angles`：20 关节角 → Observation.motion.joint_angles
- `tactile_force`：Fx,Fy,Fz（标定后）→ Observation.motion.contact/force
- `contact`：bool
- 所有 derived 必带 `derivation_method` + `calibration_id`，可从 Raw 重算
- Observation 的 `raw_transport_ref` 保留对 Raw 的引用

### 4.3 Metadata（引用，非容器）

Metadata 是**对独立模型的引用集合**，不是把所有东西塞进一个字段：
- `subject`（匿名 id、手部尺寸）、`device`（序列号、固件版本、IMU 型号批次）
- `calibration_ref`（引用 SPEC-002 校准记录）、`session`、`task`、`object`、`environment`
- `timestamp`（UTC + clock_offset，引用 SPEC-004）、`coordinate_profile_ref`（引用 V8 Coordinate Profile）、`provenance_ref`（引用 V8 ProvenanceRecord）、`quality_ref`（引用 SPEC-007 quality manifest）

**原则**：provenance 不进实时 wire packet（V8 已冻结），只在离线 episode 层记录。

---

## 5. 数据质量指标（正式定义，随 episode 存 quality manifest，归属 SPEC-007）

> **纪律**：以下目标值均为 **D 类待实测冻结**，不得伪装成已验证系统能力。Demo1 实测前仅作工程目标，不写入对外性能承诺。

### 5.1 与 V8 Observation quality 四概念的对齐

V8 Observation 定义 quality 四正交概念：availability / validity / confidence / uncertainty。本 spec 11 项指标是这四概念的**可计算度量**：

| V8 概念 | 对应指标 |
|---|---|
| availability | fps, drop_rate, sensor_noise（是否提供）|
| validity | jitter, clock_offset, calibration_error（值是否通过检查）|
| confidence | calibration_error, tactile_error（源/估计器置信）|
| uncertainty | orientation_error, joint_error, sync_error, latency（可量化误差区间）|

### 5.2 11 项指标

| 指标 | 定义 | 当前证据 | 目标（待实测冻结） | 验收门槛 |
|---|---|---|---|---|
| fps | N_received / duration | 无实测 | IMU ≥200Hz, tactile ≥100Hz | 60s 采集达标 |
| drop_rate | (N_exp − N_recv) / N_exp | 无实测 | <1% | 60s 内达标 |
| jitter | std(Δt_i) | 无实测 | <2ms | 静止段统计达标 |
| latency | t_consumer − t_sensor | 无实测 | <20ms USB / <50ms BLE | 端到端测量达标 |
| clock_offset | sensor_clock − host_clock，带漂移模型 | 无实测 | 启动校准 + 周期重同步 | 漂移残差达标 |
| calibration_error | 校准残差 RMS | 无实测 | IMU <0.5°, 触觉 <5%FS | 标定实验达标 |
| sensor_noise | 静止段 std(raw) | LSM6DSV16X datasheet 可查 | 按 datasheet 验收 | 实测 ≤ datasheet 典型值 |
| orientation_error | vs 参考 RMS | 无实测 | <3° | Phase 2 光学参考达标 |
| joint_error | 关节角 vs 参考 RMS | FSGlove 论文报告 <2.7°（外部对标，非自证）| <2.7° | vs 参考达标 |
| tactile_error | 力重建 vs 标定砝码 | 无实测 | <5%FS | 标定砝码达标 |
| sync_error | IMU↔tactile 时间对齐 | 无实测 | <1ms | 同时间基测量达标 |

quality manifest 随每条 episode 保存（归属 SPEC-007），不是事后才算。

---

## 6. SPEC 修订清单

| 0816 SPEC | 现状 | 动作 |
|---|---|---|
| SPEC-001 Motion Canonical | Hand Token v2 + canonical-20（冻结✅）| 升格为 EgoMotion Data Standard，不改协议 |
| SPEC-002 Sensor Calibration | V7 产测（flex+IMU六轴）| 修订：加 shape-aware calibration |
| SPEC-003 Tactile Data | 无 | 新建（`docs/specs/`）|
| SPEC-004 Time Sync | 无 | 新建（Demo1 同步方案落这）|
| SPEC-005 Wrist 6DoF | 无 | 新建（可插拔 adapter 接口）|
| SPEC-006 Episode & Dataset | V8 Episode Model（提案🟡）| 推进实现 |
| SPEC-007 Provenance & Quality | V8 Provenance（提案🟡）| 推进 + 落 §5 指标 |

**不动**：Hand Token v2 spec、canonical-20、wire protocol、firmware transport、V8 四模型语义边界。

### 6.1 SPEC 边界矩阵（Owns / Does NOT Own / Depends On）

| SPEC | Owns | Does NOT Own | Depends On |
|---|---|---|---|
| SPEC-001 | Hand Token v2 wire、canonical-20 旋转拓扑、FK21 派生规则 | observation 语义、坐标 profile | 无（冻结基线）|
| SPEC-002 | IMU bias/scale、触觉力标定、shape-aware hand shape、mounting 校准、校准 id 生成 | timestamp 语义、episode 容器 | SPEC-001 |
| SPEC-003 | raw_tactile 字段、calibrated_tactile、force(Fx,Fy,Fz)、contact 定义、tactile 语义分层 | tactile 的 timestamp 语义（归 SPEC-004）、episode 容器 | SPEC-004（时间基）、SPEC-002（力标定）|
| SPEC-004 | timestamp 语义、clock domain、clock_offset、sync_error、DRDY/INT/ODR 同步、IMU↔tactile 对齐 | force/contact 字段、episode 时间投影 | SPEC-001（frame seq）|
| SPEC-005 | 可插拔 wrist adapter 接口、Level 0-4 分级、输出(position/orientation/covariance/timestamp/frame_id/source/quality) | hand pose、IMU 内部标定 | SPEC-002（wrist 标定）、SPEC-004（时间）|
| SPEC-006 | episode 容器结构、observations[t]/actions[t]/events[t]、observed_at/issued_at 时间语义、masks、terminal/truncated | force/contact 字段语义（归 SPEC-003）、timestamp 基（归 SPEC-004）、quality 指标定义（归 SPEC-007）| SPEC-001/003/004/007 |
| SPEC-007 | provenance 五块模型、quality 11 项指标定义与计算、quality manifest 格式、trust 分级 | episode 容器、校准参数、timestamp 基 | SPEC-002（calibration_ref）、SPEC-004（clock）、SPEC-006（episode 容器）|

---

## 7. 现有项目不足清单（诚实审阅）

**P0（阻塞数据工厂）**
1. 产品定位仍偏手语（STRATEGY §0 第1条）→ 修订，手语降为 vertical app
2. 数据 schema 非第一公民（`data/` 空）→ 建数据契约层
3. 无腕部 6DoF 接口 → SPEC-005 新建
4. 无触觉架构 → SPEC-003 新建

**P1（数据工厂致命）**
5. 无 sensor/time sync contract → SPEC-004 新建
6. Calibration 不够高级（无 shape-aware）→ SPEC-002 修订
7. 缺 QA/provenance 工程化（`models/` `sdk/` 空）→ 推进 SPEC-006/007

**P2（克制）**
8. 过早追求端侧 AI（ESP32-P4）→ Pro 用 STM32H7+ESP32-S3，不上 P4
9. Lite/Pro 接口不统一 → 统一 `stream(imu/tactile/wrist/hand_pose/quality)`
10. STRATEGY §0 主航道仍以手语为首个商业验证场景 → 需同步降级为 vertical app

---

## 8. 分阶段路线图

| Phase | 周期 | 目标 | 交付物 |
|---|---|---|---|
| 0 架构冻结 | 第1周 | 修订 D6/D10/D12，命名冻结，目录定型 | 战略变更记录、本 spec |
| 1 Pro V1 原型 | 2-4周 | Demo1：11IMU+三指触觉+ESP32-S3 稳定采原始数据 | hardware BOM、firmware 采集、I2C mux 同步 |
| 2 数据契约层 | 3-5周 | SPEC-003/004/006/007 落地，Raw/Derived/Metadata + quality manifest | data schemas、acquisition pipeline、LeRobot exporter 雏形 |
| 3 标定系统 | 4-6周 | shape-aware calibration | EgoCal 雏形 |
| 4 腕部6DoF | 5-8周 | SPEC-005 可插拔接口（Level0 IMU→Level1 SteamVR）| wrist adapter 接口 |
| 5 EgoTouch V0 | 7-10周 | contact/slip 语义完整 | 触觉语义分层全通 |
| 6 机器人/导出 | 8-12周 | ROS2 + LeRobot exporter + DexRetargeting | EgoTeleop 雏形 |
| 7 数据工厂 | 12-16周 | 多设备并发采集、provenance 飞轮 | EgoData V1 |

**Phase 0 不做**：新手语模型/LLM/Transformer/EMG/App大改/云平台大改。

---

## 9. 被冻结文档修订步骤

### 9.1 STRATEGY.md：新增 D13 战略变更

走 `docs/V7/STRATEGY.md` §8 战略变更评审。D13 记录：
- **修订对象**：D6（Lite 硬件）、D10（Lite/Pro 硬件 + 删除 IMU 阵列军备竞赛禁令）、D12（删除阵列竞争禁令）
- **保留不变**：D3、D11（canonical-20 + Hand Token v2 + 双表示层）
- **新增**：Research 第三级硬件、手语降级为 vertical app
- **评审与签核流程**（本 spec 定义，须用户执行）：
  1. 在 STRATEGY.md §1 冻结决策表追加 D13 行，标注"2026-08-17 战略变更，supersede D6/D10/D12 硬件部分"
  2. 在 §1 后新增"D13 详解"小节，列出修订点与保留点
  3. **保留 D6/D10/D12 原文**，标注 `[superseded by D13, 2026-08-17]`，不删除（历史可追溯）
  4. 签核：用户显式批准后，在 D13 行填冻结日期，状态改为 Frozen
  5. 未签核前，D13 状态为 Proposal，不生效

### 9.2 SPEC-003/004/005 新建

放 `docs/specs/`，状态 🟡。每个 SPEC 按 §6.1 边界矩阵的 Owns/Does NOT Own/Depends On 起草。

### 9.3 TRD/TSD

Demo1 hardware TRD、firmware TSD 新建于实现仓 `docs/`。C/D 类假设须标注"待验证"。

### 9.4 不动

Hand Token v2 spec、canonical-20、wire protocol、firmware transport、V8 四模型语义边界。

---

## 10. 依赖异常规避

- 不 rename、不搬移代码 → `docs/V8` 对 `relay/*.py` 相对回链有效，CBM 索引 `home-EchoGloveHugeProjects-EgoGlove` 不失效。
- 新增 `data/` `firmware/pro/tactile/` 等为纯增量，不破坏现有结构。
- EgoMotion 伞仓用文档链接而非 submodule。
- **二级风险**：若未来 rename 本地 EgoGlove 目录为其他名，CBM 项目名 `home-EchoGloveHugeProjects-EgoGlove`（按路径 hash 派生）会失效，须先重建索引。

---

## 11. 真实性分级

- ✅ 已实现：Hand Token v2 codec/FK、C/Python golden tests、OpenXR offline ingest、semantic_fixtures
- 🟡 工程可行：本 spec 的目录重构、SPEC-003/004/005/006/007、数据契约层、quality manifest
- 🔬 需研发验证：shape-aware calibration、腕部 6DoF adapter、触觉 slip/contact 语义、FSGlove 级关节误差 <2.7°
- 🌺 长期方向：EgoData 数据工厂、EgoTeleop、foundation-model 数据飞轮

---

## 12. 下一步

本 spec 经用户审阅批准后，转入 `writing-plans` skill 产出实现计划。第一个实现计划目标：Phase 0（架构冻结 + 目录定型 + D13 战略变更记录），不含代码改动。
