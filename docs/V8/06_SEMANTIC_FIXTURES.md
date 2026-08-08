# V8 Offline Semantic Fixtures and Validators (Phase 1)

> 状态：Phase 1 离线 fixtures 与 validators（✅ 已实现并通过离线测试）  
> 日期：2026-08  
> 分支：`feature/human-motion-infrastructure`  
> 上游冻结：Hand Token v2、canonical-20、wire protocol、firmware（本阶段未触碰）

## 1. 目的与严格范围

本阶段把冻结架构边界从“文档约定”落到“可执行的离线证据”：

```text
Hand Token v2 (Motion Transport Layer)
        ↓ decode
Observation Layer (semantic state)
        ↓ references
Coordinate Profile + Provenance Model
        ↓ (后续 Phase 2)
Episode Model
```

范围**仅限**：Observation Layer fixtures、Coordinate Profile validation、Provenance validation。

本阶段**明确不做**（与迁移提案 §7 和 freeze review §9 一致）：

- 不修改 Hand Token v2 或新增 TLV 字段；
- 不修改 firmware；
- 不实现 LeRobot integration；
- 不安装 ML 依赖（全部仅用 Python 标准库）；
- 不新增 runtime services；
- 不创建 dataset pipelines。

实现物为两个文件，均离线、零依赖、可直接执行：

- `relay/semantic_fixtures.py`：semantic-layer fixture schema（`CoordinateProfile`、`CoordinateTransform`、`ProvenanceRecord`/`ArtifactIdentity`/`Transformation`、`Observation`/`MotionState`/`Quality`/`RawTransportRef`）+ validators + builders；
- `relay/test_semantic_fixtures.py`：三个具体 fixtures 与四组边界验证测试。

## 2. Fixtures（复用既有离线 artifacts）

每个 fixture 复用一条**已存在**的 Hand Token 离线 artifact，decode 后包装为 Observation，并绑定 Coordinate Profile 与 Provenance record。

| Fixture | 来源 artifact | 可用字段 | 演示重点 |
|---|---|---|---|
| `golden_skeleton_fixture` | `GOLDEN_V2_SKELETON_HEX`（Pro，右手，405B） | 全部 8 个 motion 字段 | 完整 decode + FK21 derived + 完整 lineage |
| `openxr_fixture` | OpenXR 26-joint frame → `openxr_to_hand_token` → v2 skeleton frame | `canonical_20_rotation`/`wrist_pose`/`derived_landmarks_21` | source adapter、显式 profile 转换、availability mask（flex/force 等 OpenXR 不提供的字段被 mask，而非填零） |
| `lite_fixture` | `GOLDEN_V2_LITE_HEX`（无 skeleton，82B） | 6 个 base 字段 | 无 skeleton 时 `canonical_20_rotation`/`derived_landmarks_21` 明确 unavailable |

关键设计决策：

- **availability 是声明的，不是推断的。** `build_observation_from_token(..., available_fields=...)` 要求调用方基于对 source 的了解显式声明哪些字段可用；validator 强制「available ⇒ 有值、unavailable ⇒ 值为 `None`」，从而杜绝「用零值伪装缺失数据」（01_OBSERVATION_LAYER §1）。
- **FK21 永远只是 derived view。** Observation 中 `derived_landmarks_21` 必须标记为 `derived`，并携带 `method`/`input_fields`/`topology`/`index_map`/`rest_model_id`/`rest_revision` 完整 derivation metadata（00 §3a、01 §1）；不得标记为 `measured`/`decoded`。
- **content digest 用 sha256（stdlib）。** transport frame 以原始字节取 digest（跨环境稳定）；semantic payload 以 canonical JSON 取 digest。provenance terminal artifact digest 与 observation payload digest 的一致性在运行期校验，避免跨环境浮点脆性。

## 3. Validators

| Validator | 强制的契约 | 文档依据 |
|---|---|---|
| `validate_coordinate_profile` | profile 必须完整声明 handedness、三轴正交、单位、quaternion order、wrist scope、rotation composition、clock domain、mirror policy；禁止隐式猜测 | 02 §2、§5 |
| `validate_coordinate_transform` / `assert_no_implicit_conversion` | 跨 profile 的任何 reinterpretation 必须携带显式 transform，且 transform 声明的 `convention_changes` 必须**恰好等于**两 profile 实际差异的 convention 集合（部分声明即视为隐式转换，拒绝） | 02 §2、§4 |
| `validate_observation` | field-status 词汇表、derived 必须带 metadata、availability mask 一致性、FK21 完整 derivation、quality 区间 | 01 §1-§4 |
| `validate_provenance_record` | source/acquisition/validation/policy 齐备；artifact 有 content digest 与 schema identity；transformation 链连通、无环、无 overwrite（每个 artifact 至多被产出一次）、单一 source root 与单一 terminal sink | 04 §2-§4 |
| `validate_boundary` | 跨层一致性：observation 引用的 profile/provenance 必须解析；observation clock domain 必须等于其 profile；provenance lineage 中必须包含该 observation 所 decode 的那条 transport frame（不必是 root——上游 source 可经 ingest 接入）；terminal artifact digest 必须等于本 observation payload | 00 §3、§3a |

`validate_boundary` 对「frame 在 lineage 中」而非「frame 是 root」的要求，是刻意放宽：OpenXR fixture 的 lineage root 是 `artifact:openxr_source`，Hand Token frame 是 ingest 之后的中间节点。这正是 adapter 边界（00 §5、§7）的正确表达。

## 4. 四条验证要求的落实

| 要求 | 落实方式 | 关键测试 |
|---|---|---|
| **1. Hand Token 仍是 Motion Transport Layer** | golden frame 原样 round-trip；构造 observation 不改变 token；semantic metadata 不进 wire（frame 仍 405/82B、caps 不变）；observation 以 frame digest 锚定 transport | `test_transport_frame_round_trips_unmodified`、`test_observation_anchors_to_frame_without_mutating_token`、`test_semantic_metadata_never_enters_the_wire`、`test_boundary_accepts_all_three_fixtures` |
| **2. Observation 仍是 semantic layer** | status 词汇表受控；FK21 必须 derived+metadata；禁止 zero-masquerade；decoded 不得带 derivation | `test_fk21_landmarks_are_derived_with_full_metadata`、`test_field_status_vocabulary_is_enforced`、`test_landmarks_cannot_be_marked_measured`、`test_derived_value_requires_derivation_metadata`、`test_decoded_field_must_not_carry_derivation`、`test_availability_mask_forbids_zero_masquerade`、`test_openxr_observation_masks_unsourced_fields` |
| **3. Coordinate Profile 阻止隐式转换** | 不完整 profile 被拒绝而非猜测；无 transform 的跨 profile reinterpretation 抛 `ImplicitConversionError`；transform 必须声明全部差异 convention；profile 缺失/未解析的 observation 只能 `unresolved`，不得宣称 normalized | `test_incomplete_profile_is_rejected_not_guessed`、`test_implicit_cross_profile_conversion_is_blocked`、`test_explicit_transform_must_declare_every_difference`、`test_unresolved_profile_cannot_claim_normalization`、`test_observation_clock_must_match_its_profile` |
| **4. Provenance 追踪 source 与 transformation lineage** | lineage 有序连通；记录 transport frame 的 codec version + frame hash；拒绝未知端点与 overwrite；policy 必须有 license/permitted_use；篡改 observation 会使 terminal digest 失配 | `test_provenance_lineage_is_ordered_and_connected`、`test_provenance_records_transport_frame_identity`、`test_unknown_transformation_endpoint_is_rejected`、`test_lineage_overwrite_is_rejected`、`test_policy_requires_license_and_use`、`test_tampered_observation_breaks_terminal_digest` |

## 5. 真实性分级

- **Implemented（✅）**：本阶段的 fixtures 与五个 validators 已实现并通过离线测试；它们只读既有 Hand Token golden/OpenXR fixtures，未改动任何 transport/firmware 代码（既有 `test_hand_token.py`、`test_openxr_adapter.py` 全部回归通过）。
- **Engineering feasible（🟡）**：把这些 fixtures 固化为独立 schema package，并在 Phase 2 将验证过的 Observation 序列组织为 Episode。
- **Research required（🔬）**：跨生态统一 round-trip tolerance、跨源 uncertainty calibration、位置→旋转 IK。
- **Long-term vision（🌌）**：LeRobot/BFM-scale 数据基础设施与数据治理。

## 6. 运行方式

```bash
cd relay
python3 test_semantic_fixtures.py   # 本阶段 fixtures + 边界 validators
python3 test_hand_token.py          # transport 回归（authority）
python3 test_openxr_adapter.py      # OpenXR adapter 回归
```

三个套件均为零依赖、直接执行（仓库不依赖 pytest）。

## 7. 下一步（Phase 2，需另行批准）

在独立 scope review 后，下一步是 **dataset episode projection**：把已验证的 Observation 序列组织为 Episode，加入 resampling/mask/event/action 对齐语义，并生成 MANO/FreeMoCap/ROS2/LeRobot 的**离线** projection manifests。在此之前不接入 runtime、不改 wire、不实现 LeRobot exporter（见 freeze review §10 与迁移提案 §5 Phase 2）。

相关专题：

- [Human Motion Infrastructure V8](00_HUMAN_MOTION_INFRASTRUCTURE.md)
- [Observation Layer](01_OBSERVATION_LAYER.md)
- [Coordinate Profile](02_COORDINATE_PROFILE.md)
- [Episode Model](03_EPISODE_MODEL.md)
- [Provenance Model](04_PROVENANCE_MODEL.md)
- [Architecture Freeze Review](05_ARCHITECTURE_FREEZE_REVIEW.md)
