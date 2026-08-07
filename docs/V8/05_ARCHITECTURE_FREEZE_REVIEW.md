# V8 Architecture Freeze Review

> 日期：2026-08  
> 分支：`feature/human-motion-infrastructure`  
> 基线 commit：`1a162f6 docs(v8): define human motion infrastructure layers`  
> Review 类型：Read-only red-team architecture freeze review

## 1. Review 结论

**Architecture Freeze：通过（Approved with documentation clarifications）。**

Human Motion Infrastructure 可以在不修改 Hand Token v2 的前提下承载未来的 dataset、robotics、XR 和 foundation-model ecosystems。冻结的边界如下：

```text
Hand Token v2
  = Motion Transport Layer

canonical-20
  = frozen decoded rotation topology

FK21
  = derived positional view

Observation Layer
  = semantic state container

Coordinate Profile
  = explicit frame and convention boundary

Episode Model
  = dataset / foundation-model projection boundary

Provenance Model
  = lineage, quality evidence and policy metadata
```

本次 review 未发现需要修改 Hand Token v2、canonical topology、wire protocol、firmware 或现有 adapters 的问题。

## 2. Review 范围

已审查：

- `docs/V8/00_HUMAN_MOTION_INFRASTRUCTURE.md`
- `docs/V8/01_OBSERVATION_LAYER.md`
- `docs/V8/02_COORDINATE_PROFILE.md`
- `docs/V8/03_EPISODE_MODEL.md`
- `docs/V8/04_PROVENANCE_MODEL.md`
- `docs/migrations/2026-08-human-motion-infrastructure-proposal.md`

审查维度：术语一致性、transport boundary、ecosystem claims、真实性分级、未来 breaking risk 与 unnecessary complexity。

## 3. Terminology Freeze

| 术语 | 冻结含义 | 禁止误用 |
|---|---|---|
| Human Motion Infrastructure | 位于 motion transport 与下游应用/模型之间的开放 semantic infrastructure | 不等同于单一手套产品或模型 |
| Motion Transport Layer | Hand Token v2 的职责：承载、校验和传输 motion representation | 不承载 dataset policy 或训练 schema |
| Observation Layer | decoded motion 的 semantic state abstraction | 不重新定义 canonical-20 或 wire fields |
| Coordinate Profile | 显式声明 frame、axis、unit、rotation 和 temporal convention 的边界 | 不隐式猜测或修正 source frame |
| Episode Model | 按时间组织 observation/action/event 的 dataset interface | 不成为 Hand Token streaming replacement |
| Provenance Model | source、artifact、transformation、validation 和 policy lineage | 不把 metadata 注入 frozen transport payload |
| canonical-20 | Hand Token v2 的 frozen parent-relative rotation topology | 不与任意 21-point positional schema 混称 |
| FK21 | canonical-20 经 rest offsets/FK 派生的 positional view | 不称为第二个 canonical skeleton |

## 4. Boundary Correctness

### 4.1 Hand Token boundary

通过。V8 文档统一将 Hand Token v2 定义为 Motion Transport Layer；上层只消费 decoded state，并以 references 关联 raw frame/sequence。V8 不定义新的 TLV、不改变 framing、CRC、versioning 或 firmware behavior。

### 4.2 canonical-20 / FK21 boundary

通过，且已补充冻结说明：canonical-20 是 rotation source of truth；FK21 是 derived positional view。FK21 输出需要携带 topology/index map、rest-offset identity、Coordinate Profile 和 derivation metadata。

### 4.3 Adapter boundary

通过。OpenXR、MANO、FreeMoCap、ROS2、LeRobot 和 Behavior Foundation Models 都被定义为 adapter、projection 或 downstream consumer，而非 Hand Token native support。现有 adapter 不在本次变更范围内。

## 5. Ecosystem Claim Review

| Ecosystem | V8 定位 | Freeze 判断 |
|---|---|---|
| MANO / SMPL-X | downstream parameterized-hand projection | 研究/工程边界已声明，不宣称现成 regression |
| MediaPipe / FreeMoCap | FK21 positional projection / source ecosystem | 不将 21 points 误写成 rotation canonical |
| OpenXR | source/export adapter boundary | 不宣称 runtime streaming 已实现 |
| ROS2 / robotics | action、tf、retargeting projection | 不宣称 ROS2 package 或 robot retarget 已实现 |
| Hugging Face LeRobot | dataset projection target | 不把当前 LeRobot layout 冻结为底层 contract |
| RLDS-style datasets | episode projection vocabulary | 不虚构 reward/discount |
| Behavior Foundation Models | long-term downstream consumer | 明确为 future direction，不宣称 training readiness |
| Unity | downstream runtime/visualization projection | 不把 Unity transform hierarchy 当 canonical topology |

## 6. Reality Status Audit

所有文档采用项目约定的四级状态：

- `Implemented（✅）`：已有 Hand Token v2 codec/FK、cross-language golden tests 和 OpenXR offline ingest 证据；不将 V8 schema 写为已实现。
- `Engineering feasible（🟡）`：semantic schemas、offline fixtures、validators 和 projection manifests 的工程方向。
- `Research required（🔬）`：IK、MANO/SMPL-X regression、跨源 uncertainty calibration、runtime integration、round-trip tolerance。
- `Long-term vision（🌌）`：LeRobot/BFM-scale multimodal data infrastructure、数据治理和 foundation-model readiness。

Review 未发现将未来生态能力整体误标为 native implementation 的表述。

## 7. Remaining Risks（不阻塞架构冻结）

1. MANO 与 SMPL-X 的 hand/body alignment 仍需单独定义；
2. robotics frame taxonomy、tf timing 和 retarget latency 需要在 projection 设计时落地；
3. RLDS/LeRobot projection 需要 feature manifest、dtype/shape/unit、mask 和 timestamp preservation；
4. confidence、uncertainty 和 derived-value quality propagation 需要验证实验；
5. provenance 的 artifact identity、schema identity 和 transformation digest 需要后续 validator 支持；
6. bimanual/multi-source synchronization 需要 Episode-level contract。

这些风险均位于 V8 semantic/projection layer，不要求改变 Hand Token v2。

## 8. Unnecessary Complexity Control

当前不新增第五个核心 layer。Coordinate Profile 暂时同时包含 spatial、rotation、temporal 和 bilateral conventions；只有当 temporal alignment 复杂到无法维护时，才重新评估独立 Temporal Profile。

Provenance 后续应分层实现：

```text
Core Provenance
Quality Evidence
Policy Metadata
```

第一阶段优先保证 artifact lineage 和 validation evidence，避免将 V8 变成完整 data-governance platform。

## 9. Freeze Decision

**V8 architecture layer 可冻结。** 冻结内容是语义边界与职责，不是尚未实现的 adapter 或 dataset schema implementation。

冻结后仍禁止：

- 修改 Hand Token v2；
- 新增 Hand Token TLV；
- 修改 canonical-20；
- 修改 FK21 的既有协议边界；
- 修改 firmware；
- 添加 runtime dependencies；
- 实现 LeRobot integration 或 Behavior Foundation Model training pipeline。

## 10. 下一推荐工程步骤

在另行批准后，下一步应是 **离线 semantic fixtures + validators**：

1. 读取既有 Hand Token v2 golden/FK/OpenXR offline fixtures；
2. 为 decoded state 建立 Observation fixture；
3. 为每个 fixture 绑定 canonical Coordinate Profile 和 Provenance identity；
4. 验证 FK21 topology、quality masks、timestamp semantics 和 raw transport references；
5. 只生成离线 projection manifests，不连接 runtime、不修改 wire、不实现 LeRobot exporter。

在该 validator 阶段通过前，不应开始生态 adapter 或 foundation-model pipeline。
