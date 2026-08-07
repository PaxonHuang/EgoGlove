# Human Motion Infrastructure Migration Proposal

> 日期：2026-08  
> 类型：Architecture-only proposal  
> 分支：`feature/human-motion-infrastructure`

## 1. 决策请求

批准在 EgoMotion 中建立位于 Hand Token 之上的四个 semantic layers：Observation Layer、Coordinate Profile、Episode Model、Provenance Model。当前阶段只冻结架构边界和迁移顺序，不批准代码、adapter、训练 pipeline 或硬件变更。

## 2. 不变项

本提案明确不修改：

- Hand Token v2；
- canonical-20；
- wire protocol；
- firmware；
- 现有 OpenXR adapter 或其他 adapters。

Hand Token v2 继续作为 **Motion Transport Layer**。V8 只消费其 decoded semantic state，并将上层语义包装为独立、可版本化的 metadata/data contracts。

## 3. 目标架构

```text
source devices / OpenXR / datasets
              ↓ existing adapters (unchanged)
        Hand Token v2
              ↓ decode
       Observation Layer
       ↙       ↓        ↘
Coordinate  Provenance  Episode
 Profile      Model       Model
              ↓
MANO · FreeMoCap · OpenXR · ROS2 · LeRobot · Behavior FMs
```

四层互相引用 ID，但不互相复制 frozen motion contract：Observation 引用 Coordinate Profile 和 Provenance；Episode 聚合 Observation、action、event 和 lineage；exporter 读取这些对象生成生态-specific views。

## 4. 生态兼容性评估

| 生态 | 角色 | 推荐桥接 | 风险/状态 |
|---|---|---|---|
| MANO | parameterized hand downstream view | 20→16 projection、可选 θ/β view | 真实回归与 license：🔬 |
| FreeMoCap | 21-landmark position ecosystem | FK 导出 21；反向 IK 仅研究路径 | 旋转不可由位置唯一恢复：🔬 |
| OpenXR | source/export runtime ecosystem | explicit global↔local 与 quaternion profile | 当前 adapter 是 offline ingest：✅；runtime integration：🔬 |
| ROS2 | robot/action boundary | PoseStamped + JointState + retargeting | clock/QoS/URDF mapping：🟡/🔬 |
| Hugging Face LeRobot | dataset/training consumer | Episode projection 到 time-series features | layout/version 需实测：🟡 |
| Behavior Foundation Models | long-term multimodal consumer | episode + language + action + provenance | unified benchmark/contract：🌌 |

LeRobot 和 Behavior Foundation Models 不应反向定义 Hand Token；它们是 dataset projection 和 model-consumer boundary。

## 5. 迁移阶段

### Phase 0：文档与边界（当前，🟡）

- 建立 `docs/V8/` 五份架构文档；
- 建立本 proposal；
- 将四层的责任、版本、状态和冻结边界写清楚；
- 不改任何代码和现有协议。

### Phase 1：离线 semantic fixtures（🟡）

- 从现有 Hand Token golden/FK/OpenXR offline fixtures 生成 Observation fixtures；
- 为每个 fixture 附 Coordinate Profile 和 Provenance Record；
- 建立 schema/quality/lineage validators；
- 验证失败时保留原始证据，不静默修复。

### Phase 2：dataset episode projection（🟡/🔬）

- 将已验证的 Observation 序列组织为 Episode；
- 增加 resampling、mask、event 和 action alignment 的明确语义；
- 生成 MANO、FreeMoCap、ROS2、LeRobot 的离线 projection；
- 通过 round-trip 与 task-level checks 评估误差。

### Phase 3：生态适配与数据治理（🔬）

- 在独立 adapter/export package 中接入更多源和目标；
- 评估 MANO license、FreeMoCap AGPL、数据 consent 与 commercial/open 分层；
- 以 ROS2 bag、LeRobot dataset revision 和 provenance graph 验证可复现性。

### Phase 4：foundation-model readiness（🌌）

- 形成 multimodal episode contract：hand state、world context、language、action、contact/force；
- 建立跨源质量 calibration 和 benchmark；
- 仅在数据规模、许可和任务指标充分后评估 Behavior Foundation Models。

## 6. 成功标准

1. 任一 Observation 都能回答：时间是什么、坐标是什么、数据来自哪里、哪些字段有效。
2. 任一 Episode 都能重建其 observation/action 时间关系和所有变换 lineage。
3. 下游 projection 的失败不会污染 Hand Token 或覆盖原始数据。
4. 同一 decoded Hand Token 可同时投影到 MANO、FreeMoCap、ROS2 和 dataset consumer，而无需 source-specific wire changes。
5. 所有能力按 `Implemented / Engineering feasible / Research required / Long-term vision` 标注，不把架构目标写成已实现事实。

## 7. 明确暂缓

- 不实现 MANO θ/β regression；
- 不实现 FreeMoCap reverse IK；
- 不实现 OpenXR runtime streaming；
- 不实现 ROS2 package、LeRobot exporter 或训练 pipeline；
- 不修改 firmware、Hand Token、canonical-20、wire protocol 或现有 adapter。

## 8. 后续审批门

下一步仅在用户批准后进行：先实现离线 semantic fixtures 和 validators，再单独评审每个生态 projection。任何需要新依赖、外部数据、license 或协议变化的工作，都必须在实施前重新请求确认。
