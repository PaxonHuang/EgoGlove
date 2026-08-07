# Observation Layer

## 1. 定义

Observation Layer 是 Hand Token decode 后的 **semantic observation abstraction**。它把某一时刻、某一只手或双手的可消费状态表达为稳定的逻辑对象，而不是新的 transport frame。

```text
Hand Token v2 frame → decoded canonical state → Observation
```

Observation 可以包含 canonical motion、派生 landmark、腕部状态、velocity/acceleration、contact/force、quality、Coordinate Profile 引用和 Provenance 引用。不存在的数据必须由 mask/availability 明确表示，不能用零值伪装。

每个 observation 还必须保留 `raw_transport_ref`（Hand Token frame/sequence identity）。字段应区分 `decoded`、`measured`、`derived`、`estimated` 和 `fused`；FK21 只能在提供 derivation metadata 后作为 `derived` 值出现。

## 2. 建议逻辑结构

```text
Observation {
  observation_id
  sequence_id / timestamp
  hand_scope: left | right | bimanual
  motion {
    canonical_20_rotation
    wrist_pose
    derived_landmarks_21 (optional)
    joint_angles (optional)
    velocity / acceleration (optional)
    contact / force (optional)
  }
  availability_mask
  quality
  coordinate_profile_id
  provenance_ref
}
```

字段是 semantic contract，不是 Hand Token TLV 的新增要求。`canonical_20_rotation` 继续使用已冻结的 Hand Token v2 解码语义；21 landmarks 继续由 FK 派生。

## 3. 语义规则

- 时间戳必须同时说明 clock domain；不同源不能仅凭数值直接排序。
- observation 是状态，不是动作命令；机器人 action 属于下游 projection。
- derived value 必须注明 derivation method 和输入字段。
- 缺失、无效、低置信度和未观测是不同状态，应由 mask/quality 区分。
- 单手记录与双手记录共享 schema，通过 `hand_scope` 表达，不复制两套不兼容协议。

## 4. 质量模型

建议质量分为 availability、validity、confidence、uncertainty 四个正交概念：

- availability：源是否提供该字段；
- validity：值是否通过有限值、范围和拓扑检查；
- confidence：源或估计器对结果的置信度；
- uncertainty：可量化误差或区间（若可得）。

跨设备 confidence 的数值不可直接比较，需在 Provenance 中记录 calibration/evaluation context。

## 5. 生态投影

| 目标 | Observation 投影 | 状态 |
|---|---|---|
| MANO | canonical-20 → MANO-16/mesh 参数视图 | 🟡 结构路径可行；真实 θ/β regression 与商业许可 🔬 |
| FreeMoCap | FK → 21 个 3D landmarks | 🟡 工程可行；反向 IK 🔬 |
| OpenXR | 生成或消费 runtime joint locations | 🟡 schema 映射；runtime integration 🔬 |
| ROS2 | wrist → `PoseStamped`，手指 DOF → `JointState` | 🟡；机器人 retarget 🔬 |
| LeRobot | 作为 time-indexed observation columns 的来源 | 🟡 schema projection；官方版本细节需实测 |
| Behavior FMs | multimodal state token / feature input | 🌌，需要 benchmark 与训练研究 |

## 6. 版本策略

Observation schema 使用独立 semantic version。新增 optional field 不改变既有 field meaning；改变坐标、单位、拓扑或估计语义必须升 major version 或创建新的 Coordinate Profile/Provenance record。
