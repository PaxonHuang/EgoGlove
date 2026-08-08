# Human Motion Infrastructure V8

> 状态：Architecture proposal only（架构提案，不代表实现）  
> 日期：2026-08  
> 上游冻结：Hand Token v2、canonical-20、wire protocol、firmware

## 1. 目标与非目标

EgoMotion 的目标是从 motion transport project 演进为 **Human Motion Infrastructure**：为采集、对齐、审计、数据集构建和下游模型提供稳定的 semantic layer。

本 V8 不定义新的设备协议，也不替换 Hand Token。明确非目标：

- 不修改 Hand Token v2 或 canonical-20；
- 不修改任何 wire protocol 或 firmware；
- 不改现有 OpenXR 或其他 adapter；
- 不实现 SDK、adapter、训练 pipeline 或 runtime service。

## 2. 分层原则

```text
Sensor / external source
        ↓ adapter（现有边界，保持不变）
Hand Token v2
        ↓ decode（Motion Transport Layer）
Observation Layer
        ├── Coordinate Profile
        ├── Provenance Model
        └── Episode Model
                ↓
MANO / FreeMoCap / OpenXR / ROS2 / LeRobot / foundation models
```

**Hand Token = Motion Transport Layer**：负责紧凑、自描述、可校验的手部运动传输。  
**Observation Layer = semantic observation abstraction**：负责解释一条运动记录在什么坐标系、来自什么源、具有什么质量，并为时间序列消费提供统一语义。

四个新模型均位于 decode 后、下游生态前。它们可以引用 Hand Token 字段，但不得向 Hand Token 反向施加新的 wire 约束。

## 3. 四个模型的职责

| 模型 | 解决的问题 | 不负责的内容 |
|---|---|---|
| Observation Layer | 一条 observation 表示什么可消费的状态 | 不重新定义骨架或协议 |
| Coordinate Profile | 不同坐标、单位、frame 和 quaternion convention 如何声明与转换 | 不隐式猜测坐标系 |
| Episode Model | 如何把 observations、actions、事件和任务组织为 dataset episode | 不规定模型架构 |
| Provenance Model | 数据从哪里来、经过什么变换、可信度如何 | 不把 provenance 当作运动载荷 |

## 3a. 冻结的表示层级

- **canonical-20** 是 Hand Token v2 解码后的 frozen rotation topology，不是 V8 新增的 schema。
- **FK21** 是由 canonical-20、rest-offset model 和 FK implementation 派生的 positional view，不是第二个 canonical skeleton。
- Observation 只能承载这两种表示的明确状态：`decoded`、`derived`、`estimated` 或 `fused`；不得把 estimated/derived 值标记为 measured。
- 任何 FK21 view 都必须携带 topology/index map、rest-offset identity、Coordinate Profile 和 derivation metadata。

V8 的 semantic layer 还必须保留 raw Hand Token frame/sequence reference，使上层 schema 演进不会丢失原始 transport evidence。

## 3b. Projection status vocabulary

跨生态映射统一使用以下状态：`exact`、`derived`、`projected`、`estimated`、`lossy`、`unsupported`。生态名称不表示 native support；MANO、FreeMoCap、OpenXR、ROS2、LeRobot 和 Behavior Foundation Models 均是 adapter、export/import projection 或 downstream consumer。

## 4. 真实性分级

- **Implemented（✅）**：Hand Token v2 codec/FK、cross-language golden tests、OpenXR offline ingest 等已有实现证据；本 V8 新模型本身尚未实现。
- **Engineering feasible（🟡）**：在现有 relay/SDK/data 边界上可实现的 schema、离线转换和验证工具。
- **Research required（🔬）**：需要数据、标注、误差实验或生态实测才能冻结的语义，例如跨源 uncertainty calibration、位置到旋转的 IK。
- **Long-term vision（🌌）**：面向大规模 multimodal dataset、LeRobot 生态和 Behavior Foundation Models 的统一数据基础设施。

## 5. 生态兼容性原则

- **MANO**：作为参数化 hand representation 的 downstream view；20→MANO-16 是明确的 projection，真实 θ/β regression 与 license 仍需单独处理。
- **FreeMoCap**：作为 21-landmark position ecosystem；由 canonical-20 FK 导出位置，反向 ingest 需要 IK，存在旋转歧义。
- **OpenXR**：既可作为 source，也可作为 export target；Coordinate Profile 必须声明 global pose、单位、handedness 和 quaternion order。现有 adapter 保持不变。
- **ROS2**：作为 robot/action boundary；Episode 可映射 `JointState`、`PoseStamped` 和任务事件，但 ROS2 message 不取代 Observation schema。
- **Hugging Face LeRobot**：作为 dataset/training consumer；Episode 应能投影到其 observation/action/time-series 组织，但不把 LeRobot 的当前 tensor layout 写入底层 canonical contract。
- **Behavior Foundation Models**：作为长期 consumer；需要保留多模态 observation、action、language/task context、mask、quality 和 provenance，避免为单一模型冻结格式。

## 6. 迁移顺序

1. 只读冻结 V7 与 Hand Token v2 truth hierarchy；（✅ 已完成）
2. 定义四个 semantic schemas 和 status boundaries；（🟡 本文提案）
3. 建立离线 validators 与 fixtures，不修改 wire 或 firmware；（🟡 后续，待批准）
4. 在不改现有 adapter 的前提下，将 decoded Hand Token 投影成 Observation；（🟡 后续，待批准）
5. 增加 dataset export/import projections：MANO、FreeMoCap、ROS2、LeRobot；（🔬 需验证）
6. 以 provenance 和 episode-level evaluation 支撑长期 foundation-model 数据飞轮；（🌌 长期方向）。

## 7. 设计决策

V8 采用 **semantic envelope above transport**：transport 保持稳定，semantic layers 可版本化、可扩展、可审计。任何未来 adapter 只能在边界处把 source 映射到 Hand Token 或 Observation，不得将 source-specific fields 变成 canonical wire 字段。

相关专题：

- [Observation Layer](01_OBSERVATION_LAYER.md)
- [Coordinate Profile](02_COORDINATE_PROFILE.md)
- [Episode Model](03_EPISODE_MODEL.md)
- [Provenance Model](04_PROVENANCE_MODEL.md)
- [Architecture Freeze Review](05_ARCHITECTURE_FREEZE_REVIEW.md)
- [Offline Semantic Fixtures (Phase 1)](06_SEMANTIC_FIXTURES.md)
- [Migration Proposal](../migrations/2026-08-human-motion-infrastructure-proposal.md)
