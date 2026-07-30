# Hand Token v2 — Skeleton Layer 互操作协议设计 (Design Spec)

> **Date**: 2026-07-27
> **Status**: 🔒 P0 设计已签核（2026-07-28）；进入 writing-plans → TDD 实现
> **Owner**: PaxonHuang
> **Decision**: 实现 STRATEGY.md **D11 + D12**（细化 D10）
> **研究底稿**: `../../BP/research_5_data_formats_interop.md`（源实时核对，高/中/待核实分级）
> **绑定文档**: `../../V7/STRATEGY.md` §1 D11 · `../../V7/07_dual_rep_layer.md` §1b · `../../V7/ARCHITECTURE.md` §3/§8
> **前置**: Hand Token v1（79B 定长帧）已实现于 `firmware/shared/hand_token.{h,c}` + `relay/hand_token.py`，v2 **永久兼容 v1**。

本 spec 是 Hand Token v2 的**唯一可实现真相源**。经用户 P0 签核后，才进入 `writing-plans` → TDD 实现（firmware/shared C + relay Python 镜像 + 跨语言金标）。能力描述带四级真实性标注：✅ 已实现 / 🟡 工程可实现 / 🔬 需研发验证 / 🌌 长期方向。

---

## 1. 动机与背景

D10（Open Hand Motion Infrastructure）把 EgoGlove 从"手套设备"升级为**开放手部运动基础设施**：Hand Token 成为**双向手部运动互操作层**，既能 ingest 第三方手套流（Hi5 / mHand / Manus / Rokoko / OpenXR），也能 export 到生态格式（MANO / BVH / FBX / OpenXR / ROS2）。

research_5 落地后暴露一个 D10 表述内的**张力**，需要在协议层精确化：

- **21 MediaPipe 关键点 = 位置表示**（positions，视觉 / web / MediaPipe 语系，无关节朝向）。
- **专业手套（Hi5 / mHand / Manus / OpenXR）输出 = 旋转表示**（每关节四元数）。
- 二者**不可互相替代**：只存 21 位置无法无损 ingest 旋转骨架（丢关节朝向）；只存旋转需 FK 才得位置。

**D11 拍板的调和方案**：canonical 内部主表示 = **20 旋转关节**，前向运动学（FK）**派生 21 MediaPipe 位置**作导出视图。D10 的 21-keypoint 对外锚点 / web 前端 / 视觉融合公共空间**全部不变**，内部换取对专业手套的无损 ingest 能力。

> **为何"细化"而非推翻 D10**：D10 的战略实质（格式先行、双向互操作、21 为生态锚点、硬件不变）全部保留；D11 只把"通用 21-joint 骨架"的**内部实现**精确化为"20 旋转主 + 派生 21"。

**D12 生态对齐**：EgoGlove = 开放 **Hand Motion Infrastructure**，**非** Hi5/Manus/mHand 竞品——厂商手套是**外部数据源/适配器**。Hand Token v2 是**厂商无关的通用中间表示**（不围绕任何厂商手套设计），方向锚定 MANO/SMPL-X · FreeMoCap · OpenXR Hands · ROS2·DexRetargeting/AnyTeleop · egocentric-AI 数据集。四段管线：

```
Sensor Source (flex / IMU / vision / external gloves)
        ↓  ingest / encode
Hand Token v2             (通用中间表示 = 自描述 wire 帧, 本 spec §4)
        ↓  decode
Canonical Skeleton Layer (20 旋转关节, §3; FK 派生 21)
        ↓  export / retarget
MANO / OpenXR / FreeMoCap / ROS2 / Robot   (经 DexRetargeting/AnyTeleop)
```

> Hand Token v2（序列化载体）与 Canonical Skeleton Layer（解码后的 20 关节语义模型）是同一设计的两面：v2 帧承载骨架，消费者解码为 canonical 骨架后再 export/retarget。

---

## 2. 目标与非目标

### 2.1 目标（本 spec 范围内）

1. 定义 v2 **canonical 骨架**：每手 20 旋转关节 + 层级 + 旋转约定 + rest-offset。
2. 定义 v2 **wire format**：capability-flagged TLV 变长帧（version `0x02`），与 v1 version-gate 并存。
3. 定义 **caps 位域**（显式声明四元数顺序 / handedness，消除最高频静默损坏）。
4. 定义 **TLV 初始注册表**（骨架 / rest-offset / 关节角 / 全局腕 / 力 / provenance / β）。
5. 定义 **ingest / export 映射规则**（引用 research_5 §B 矩阵为权威细节）。
6. 定义 **FK 派生 21 MediaPipe 关键点** 的契约。
7. 定义 **测试策略**：跨语言金标帧 + round-trip + version-gate 断言。

### 2.2 非目标（本 spec 明确不做，YAGNI）

- ❌ **不改硬件方向**（D10）：Lite 仍 `flex(5) + 单腕 IMU`；Pro 多 IMU 指节仅路线图，本 spec 不启动。
- ❌ **不启动 IMU 阵列竞争**（D12）：不做"每指节 9 轴 IMU"军备竞赛去对标 Hi5/mHand 硬件；专注协议 / 互操作 / 生态。厂商手套 = 外部源/适配器，非竞品。
- ❌ **不实现真实 flex→θ/β 回归 / joint→URDF retarget**（属 `models/mano/`、`models/robot/`，本 spec 只定义承载它们的**格式**）。
- ❌ **不改 v1 wire 契约**：v1 79B 定长帧字节不变、永久有效。
- ❌ **不写实现代码**：本 spec 是 P0 签核对象；代码在签核 + `writing-plans` 后。
- ❌ **不加宽 v1 定长帧塞骨架**（否则每个纯 flex 的 Lite 包塞零膨胀）→ 用 version-gate + TLV。
- ❌ **不为 mHand 编造 wire schema**（无公开 artifact）→ 暂经其 BVH 导出 ingest（研究结论）。

---

## 3. Canonical 骨架 = 20 旋转关节 (D11)

### 3.1 关节集 + 层级 (parent → child)

```
 0  Wrist              (手 token 根; 全局腕位姿由 GLOBAL_WRIST_POSE TLV 单独承载)
 拇指: 1 ThumbMetacarpal(CMC) → 2 ThumbProximal(MCP) → 3 ThumbDistal(IP)
 食指: 4 IndexMetacarpal  → 5 IndexProximal(MCP) → 6 IndexIntermediate(PIP) → 7 IndexDistal(DIP)
 中指: 8 MiddleMetacarpal → 9 MiddleProximal → 10 MiddleIntermediate → 11 MiddleDistal
 无名:12 RingMetacarpal   → 13 RingProximal → 14 RingIntermediate → 15 RingDistal
 小指:16 LittleMetacarpal → 17 LittleProximal → 18 LittleIntermediate → 19 LittleDistal
 指尖(5) = 派生 (每 Distal 经 rest-offset 固定偏移) — 不存储
```

关节编号 `0..19` 即 `SKELETON_QUAT20` TLV 内四元数的固定顺序。

### 3.2 为何选 20（研究结论，research_5 §A）

- **数学甜点**：= **OpenXR-26 去 6 个可派生关节（PALM + 5 TIP）** = **Noitom Axis 每手 20** ⊃ **MANO-16 严格超集**（多出的 4 = MANO 折进手掌的非拇指掌骨），覆盖 **SteamVR 20 个 DOF 承载骨**。
- **16（MANO-min）不够**：丢 4 个非拇指掌骨 DOF → 无法忠实 ingest OpenXR/Manus/Noitom 掌骨展开 → 对专业手套 ingest 有损。
- **26（OpenXR-full）冗余**：PALM + 5 TIP 非 DOF 且几何可派生 → 6 冗余关节 = 每帧浪费字节。
- **结论**：20 = 无损 ingest 专业手套的**最小完整旋转集**。

### 3.3 旋转约定（逐项明确声明，避免歧义）

| 项 | 约定 | 理由 |
|---|---|---|
| 四元数分量顺序 | **`w,x,y,z` (w-first)** | 与 v1 `quat[4]` 及 Manus 一致；为 w-last 阵营（OpenXR/glTF/ROS/Noitom）记录单次 swap |
| 参考系 | **父相对**（每关节相对父的局部旋转） | MANO/BVH/FBX/glTF/VRM/SteamVR-parent/Manus-local 皆父相对；OpenXR-global/Manus-global 经父链 + rest-offset 一次性转换 |
| 坐标系 | **右手，+Y up，-Z forward，+X right，米** | 对齐 OpenXR / glTF |
| rest-offset | 每关节父→子平移向量（BVH-`OFFSET` 式），置于 `REST_OFFSETS` TLV | 使消费者可做 FK 恢复全局关节位置 → 帧自足于 FK（不像裸 BVH MOTION 需分离 HIERARCHY），并由此**派生 21 MediaPipe 关键点** |

> **贯穿性风险（research_5 §0，【高】）**：四元数分量顺序 w-first vs w-last **不通用**，是手部数据互操作**最高频静默损坏点**。v2 必须在帧头 `caps` bit4 显式声明，并在 ingest/export 时 swap。

### 3.4 FK 派生 21 MediaPipe 关键点（D10 锚点不变）

- 21 = 由 20 旋转 + `REST_OFFSETS` 经 FK 派生：16 MANO 关节位置 + 5 指尖位置。
- `REST_OFFSETS` 固定为 **25 × vec3 f16**：索引 `0..19` 是 canonical joint 的 parent-offset（`0=Wrist` 固定零向量），索引 `20..24` 依次是 Thumb / Index / Middle / Ring / Little 的 Distal→Tip offset。**禁止启发式外推指尖，也不为 v2.0 增加独立 tip TLV。**
- 每个含 `SKELETON_QUAT20` 的 v2.0 帧必须同时含 `REST_OFFSETS` 与 `REST_MODEL_ID`，使 skeleton / FK / fingertip reconstruction **frame-self-contained**；缺任一项即语义非法。
- MediaPipe 索引契约（research_5 §3，核对 `HandLandmark` enum）：`WRIST=0`；`THUMB_CMC/MCP/IP/TIP=1..4`；`INDEX 5..8`；`MIDDLE 9..12`；`RING 13..16`；`PINKY 17..20`。
- **冻结映射表**（canonical index → MediaPipe index）：`0→0`；Thumb `1,2,3,tip20 → 1,2,3,4`；Index `5,6,7,tip21 → 5,6,7,8`；Middle `9,10,11,tip22 → 9,10,11,12`；Ring `13,14,15,tip23 → 13,14,15,16`；Little `17,18,19,tip24 → 17,18,19,20`。
- canonical 的额外掌骨关节 `4/8/12/16` **参与各自父链 FK，但不映射为 MediaPipe MCP，也不直接出现在 MediaPipe-21**。MediaPipe MCP 对应 canonical Proximal `5/9/13/17`；Metacarpal 与 MCP 解剖语义不得混用。
- 21 是**派生应用视图**，不进 wire 帧且不改变 canonical-20 真相源；web 前端 / 视觉融合公共空间继续用 21。

---

## 4. Wire Format v2

### 4.1 设计规则

1. **Magic `"HT"` 不变；`version=0x02`。** 新增 `caps` 位域 + `total_len` + 自描述 TLV 区。保留 v1 全部约定：CRC-16/MODBUS over `[0…crc)`、小端、float16 round-to-nearest-even、float32 IEEE754。
2. **向后兼容 = version-gate**：v1（`version==0x01`，定长 79B）与 v2（`version==0x02`，变长）**并行**。v2 解析器兼收两者；v1-only 解析器在 version 检查处**干净拒绝** v2（不误读）。**不**在 v1 定长 CRC 后夹带 TLV。
3. **`caps` 声明四元数顺序 + handedness** — 消除 ingest 歧义。
4. **未知 TLV 类型按 `len` 跳过** → 前向可扩展不破坏旧 v2 解析器。

### 4.2 帧布局

```
 off   len  field           说明
 0     2    magic "HT"       不变 (0x48 0x54)
 2     1    version = 0x02   新值；v1-only 解析器在此干净拒绝
 3     1    device_id        不变位域: bit7 product(0=Lite,1=Pro) | bit6 hand(0=L,1=R) | bits5..0 serial(0..63)
 4     4    timestamp_us     不变 (uint32 LE)
 8     1    caps  (位域)      见 §4.3
 9     2    total_len        新 (uint16 LE): 全帧总字节数含 CRC → 变长自定界
 11    ..   BASE BLOCK       v1兼容核, Lite 恒发 (69B, 同 v1 的 [8,77) 语义):
                              flex[5]f16 | quat[4]f16(腕 wxyz) | wrist_6dof[6]f32
                              | vel[3]f16 | acc[3]f16 | contact[5]u8 | force[5]f16
 ..    ..   TLV REGION       0 或多条 (Pro/ingested): 每条 = {type u8, len u16 LE, value[len]}
 end-2 2    crc16            CRC-16/MODBUS over [0…crc), 小端
```

> **BASE BLOCK 语义等同 v1 payload**：v1 帧 `[8,77)` 的 69 字节字段布局原样搬入，保证 v1↔v2 base 块的编解码代码可复用、金标可交叉验证。

### 4.3 `caps` 位域

| bit | 名 | 含义 |
|---|---|---|
| 0 | `HAS_SKELETON` | 存在 `SKELETON_QUAT20` TLV（Lite=0） |
| 1 | `HAS_FORCE` | base `force[5]`/`contact[5]` 有效（Pro=1） |
| 2 | `HAS_VEL_ACC` | base `vel[3]`/`acc[3]` 有效 |
| 3 | `GLOBAL_WRIST` | 存在 `GLOBAL_WRIST_POSE` TLV（腕在命名系全局位姿） |
| 4 | `QUAT_WLAST` | 0 = `w,x,y,z`（canonical）；1 = `x,y,z,w`（ingest 源标注，解析后应归一到 w-first） |
| 5 | `HANDEDNESS_AXIS` | handedness / 轴 profile 标志（0 = canonical 右手 +Y up/-Z fwd） |
| 6 | `SKEL_SMALLEST3` | 骨架四元数编码：v2.0 必须为 0（f16×4）；值 1 保留给 v2.1，v2.0 parser 必须拒绝 |
| 7 | reserved | 置 0 |

### 4.6 Quaternion Canonicalization and Ingest Policy

v2 internal quaternion state is always finite, normalized `w,x,y,z`; `QUAT_WLAST` changes only the emitted/read component order. v1 serialization and parsing are unchanged.

- **Ingest/parser acceptance**: accept any finite, non-zero f16 quaternion quartet in either declared wire order. Parse converts it to internal w-first and normalizes it. A parser must not reject a valid external finite quaternion merely because it is non-unit or not already canonical.
- **Canonical v2 serialization**: normalize the w-first input; quantize each component with the protocol f32→f16 round-to-nearest-even helper; decode to f32; normalize again; repeat f16 quantization plus normalization until the four f16 component bit patterns are unchanged. The bounded iteration limit is 32; failure to produce a finite non-zero fixed point fails serialization rather than emitting unstable bytes.
- **Wire ordering**: after selecting the fixed-point w-first quartet, write `w,x,y,z` when `QUAT_WLAST=0`, or the same selected components as `x,y,z,w` when it is set. The rule applies to the v2 base wrist quaternion and every `SKELETON_QUAT20` quaternion.
- **Canonical-frame invariant**: for a canonical valid v2 frame, `serialize_v2(parse_v2(frame)) == frame`. A noncanonical but valid external frame may change on its first serialization, then remains byte-stable. This invariant is intentionally distinct from permissive ingest acceptance.


| type | 名 | value |
|---|---|---|
| `0x01` | `SKELETON_QUAT20` | 20 × quaternion；v2.0 固定 f16×4=160B；顺序 = §3.1 关节 0..19；存在时 `REST_OFFSETS` + `REST_MODEL_ID` 也必须存在 |
| `0x02` | `REST_OFFSETS` | **25 × (dx,dy,dz) f16 = 150B**；`0..19` canonical joint parent-offset（Wrist 为零），`20..24` 五指 Distal→Tip → 使 frame 自足于 FK / local↔global / 精确派生 21 MediaPipe |
| `0x03` | `JOINT_ANGLES` | Manus-ergonomics 式紧凑角（每手 20：{MCP spread, MCP stretch, PIP stretch, DIP stretch}×5）供快速 retarget |
| `0x04` | `GLOBAL_WRIST_POSE` | 腕 pos f32×3 + quat f16×4，于命名系（当 `caps` bit3） |
| `0x05` | `FINGERTIP_CONTACT_FORCE` | 超出 base `contact[5]`/`force[5]` 的扩展每指尖接触/力 |
| `0x06` | `SOURCE_PROVENANCE` | u8 厂商 id + u8 源格式 + u16 fps → 记录该帧由 OpenXR/Manus/Noitom/Rokoko/BVH ingest 而来 |
| `0x07` | `HAND_SHAPE_BETA` | 已知校准手型时的 MANO β（10 × f16） |
| `0x08` | `REST_MODEL_ID` | **u16 model_id + u16 revision（LE，4B）**；`0=canonical human hand`、`1=MANO aligned`、`2=OpenXR aligned`，revision 从 `1` 起；未知 ID 可保留/转发，但在无 adapter 时不得做语义 export |

> **v2.0 skeleton 完整性不变式**：`SKELETON_QUAT20`、`REST_OFFSETS`、`REST_MODEL_ID` 三者必须同时出现且各最多一次；`REST_OFFSETS.len==150`、`REST_MODEL_ID.len==4`、`model_id` 已知且 `revision>=1` 才可执行 FK / 语义 export。未知 model 可完成结构解析并保留原始 TLV，但消费者必须报告 unsupported model，不能悄然套用 canonical offsets。

> 厂商 id / 源格式的枚举值在实现阶段随代码固化（`hand_token.h` 常量），本 spec 只定义字段存在性与语义。

### 4.5 载荷大小

| 帧 | 组成 | 大小 |
|---|---|---|
| **Lite v2** | 头 11B + base 69B + CRC 2B（`caps=0`，无 TLV） | **82B**（v1 79B + 3B caps/len） |
| **Skeleton v2.0（P0）** | Lite 核 82B + `SKELETON_QUAT20`(3+160) + `REST_OFFSETS`(3+150) + `REST_MODEL_ID`(3+4) | **405B** |
| **未来 smallest-three（v2.1 候选）** | skeleton v2.0 将 quaternion value 160B→80B；其余自足 geometry 不变 | **325B** |

双手 = 两帧（device_id bit6 区分 L/R）。`405B` 是 v2.0 完整 skeleton 的 deterministic P0 金标长度；不再使用未携带 rest geometry 的 246B 估算作为合法 skeleton 帧。

---

## 5. Ingest / Export 映射

完整逐格式映射矩阵（关节数 / 旋转编码 / ingest / export / 有损性 / 备注）= **research_5 §B 为权威**。此处只列规则与关键结论：

### 5.1 Ingest → Hand Token（第三方手套 → canonical-20）

| 源 | 规则 | 有损? |
|---|---|---|
| **Noitom / Hi5** | 每手 20 关节 `x,y,z,w` local → **近 1:1**（拓扑一致）；swap 到 w-first | 基本无损 |
| **Manus** | skeleton `w,x,y,z`（已 w-first）→ ~1:1；或 ergo 20 角 → 关节角 → quat | skeleton 近无损 |
| **Rokoko** | 解析 `actor.body[*]` keyed quat `w,x,y,z`；**无掌骨**→补进 Proximal；Studio→canonical 轴修正 | 无掌骨（有损） |
| **OpenXR** | 26 关节去 PALM+5 TIP → 20；`x,y,z,w`→w-first；global→local 经 rest-offset | 丢 radius（非 DOF，可接受） |
| **BVH** | 解析 HIERARCHY，Euler(ZXY)→quat，名重映射；常缺掌骨 | 名/拓扑映射有损 |
| **mHand (Virdyn)** | **无权威 schema**（待核实）→ 暂当"BVH 兼容手套"经其 BVH 导出 ingest | 待核实 |
| **FreeMoCap** | 多机位三角化的每手 21 个 3D 关键点 → 按 MediaPipe 拓扑重映射 → 带解剖约束的 IK 反解 canonical-20 | 有位置无旋转；掌骨扭转存在歧义【高】 |

### 5.2 Hand Token → Export（canonical-20 → 生态）

| 目标 | 规则 | 有损? |
|---|---|---|
| **MANO** | 20→16 折 4 掌骨进掌 → θ/β（16⊂20，投影非猜测） | 20→16 轻损（掌骨并入） |
| **BVH / FBX** | 由 20 关节生成 HIERARCHY + MOTION（quat→Euler） | Euler 无损；拓扑/命名映射有损 |
| **OpenXR / SteamVR** | 合成 26（派生 PALM/指尖）或 31（加 Aux）；w-first→w-last | 指尖/palm 派生 |
| **ROS2** | `JointState`：name/position(rad)/**effort = force[5]**；腕→`PoseStamped`(quat x,y,z,w) | quat→单 DOF/关节有损（丢离轴旋转） |
| **FreeMoCap** | FK 派生 21 关键点位置 → `.npy` / `.csv` / Blender 开放动捕管线 | 位置视图本身无损；再导回旋转需 IK【高】 |
| **DexRetargeting/AnyTeleop** | FK 得 3D 关键点位置；按优化器所需 position/vector 引用与目标 URDF joint names 对齐 → qpos | retarget 依目标手 DOF；输入是位置/向量而非四元数【高】 |
| **21 MediaPipe** | FK 派生（§3.4） | 无损（位置视图） |

### 5.3 Dataset / 训练兼容（不直接定义 wire）

| 数据集 / 项目 | 对齐 canonical-20 的规则 | 约束 / 风险 |
|---|---|---|
| **InterHand2.6M** | MANO 轴角按父子链转 parent-relative quaternion；共享 MANO-16 关节直接映射，4 个非拇指掌骨按 rest-pose / 手型模型补齐 | 含 3D 关节与 MANO，MS COCO 标注格式，当前最易对齐；补出的 4 掌骨并非观测 DOF【高】 |
| **COCO-WholeBody** | 每手 21 个 2D 关键点按 MediaPipe 拓扑对齐，用于 2D 检测器预训练 / 重投影监督 | 仅 2D、无深度、无 MANO、无旋转，不能直接生成 canonical-20【高】 |
| **HumanEgo** | 仅作为 egocentric 数据飞轮与策略学习范式参照；取得 Aria MPS 手格式后才定义 adapter | 2026-06 新项目，非经典数据集；手关节数 / 精确表示与 License【待核实】，当前不得声称已完成映射【高存在 / 细节待核实】 |

> **映射边界**：FreeMoCap 是可双向连接的位置语系（ingest 需 IK，export 经 FK）；DexRetargeting/AnyTeleop 是 Robot Action Layer 下游 export/retarget 目标；InterHand2.6M、COCO-WholeBody、HumanEgo 属 dataset/训练兼容，不是 v2 wire emitter。以上锚点已于 2026-07-27 经权威仓库 README / GitHub API 核实；仍未确认的字段维持【待核实】，不据此编造 adapter schema。

> **关键卡位（research_5 §D §6）**：主流 VLA（OXE/RLDS）**无逐关节手、无力/触觉**（手 = 单 1-DOF 夹爪标量）。Hand Token 兼 ingest 专业手套骨架 + export MANO/ROS2 `effort`，Pro `force[5]`/`contact[5]` 填 OXE/DROID 的触觉空洞 = 真正差异化枢纽。

---

## 6. 向后兼容 (version-gate)

| 场景 | 行为 |
|---|---|
| v1 emitter → v1 parser | 79B 定长，原样（不受本 spec 影响） |
| v1 emitter → v2 parser | v2 parser 见 `version==0x01` → 走 79B 定长路径 |
| v2 emitter → v2 parser | 见 `version==0x02` → 读 `total_len`，解析 base + TLV |
| v2 emitter → v1-only parser | v1-only parser 在 version 检查处**干净拒绝**（不误读、不崩溃） |

**不变式**：CRC-16/MODBUS 多项式 `0xA001`、初值 `0xFFFF`、覆盖 `[0…crc)`、小端存储 —— v1/v2 一致。

---

## 7. 测试策略 (TDD，代码阶段执行)

| 层 | 断言 |
|---|---|
| **跨语言金标** | 三个固定向量：现有 v1 79B（不得改变）、v2 Lite base-only 82B、v2 skeleton-self-contained 405B；分别以 `GOLDEN_V1_HEX` / `GOLDEN_V2_LITE_HEX` / `GOLDEN_V2_SKELETON_HEX` 同值固化在 host C 与 Python测试，**不得跳过空金标，逐字节双向一致** |
| **round-trip** | canonical valid frame: `serialize(parse(frame)) == frame`; noncanonical finite input is accepted and may canonicalize once, then repeated serialize/parse cycles are byte-stable; `parse(serialize(token)) == token` with normalized quaternion/f16 quantization semantics |
| **version-gate** | v2 parser 正确分流 v1/v2 帧；v1-only parser 干净拒绝 v2；损坏 CRC / 错 magic / 截断 `total_len` 均被拒 |
| **TLV 前向兼容** | 注入未知 `type` TLV → parser 按 `len` 跳过、其余字段正确 |
| **caps / TLV 语义** | `QUAT_WLAST` 置位帧解析后归一到 w-first；重复 TLV、caps 与 TLV 不一致、非法 length、截断 TLV 均拒绝；未知 TLV 按 length 跳过 |
| **Skeleton 自足性** | `HAS_SKELETON` 时强制 `SKELETON_QUAT20 + REST_OFFSETS(25×vec3) + REST_MODEL_ID` 三件套；缺一、重复、Wrist offset 非零、revision=0 均拒绝语义解码 |
| **FK 派生** | 由 `SKELETON_QUAT20` + 25 个 offsets 做 FK → 21 MediaPipe 位置；identity rotations 下逐链累加；5 个 tip 必须严格使用 offsets `20..24`，禁止启发式外推 |

---

## 8. 实现分期 (D12 确认的 P0–P3 优先级)

| 阶段 | 内容 | 真实性目标 |
|---|---|---|
| **P0** | **冻结 canonical 骨架 + Hand Token v2**：本 spec 签核 → v2 wire format(caps/TLV/version-gate) + canonical-20 骨架抽象层(C struct + Python `HandTokenV2` + FK 派生 21) + 跨语言金标帧 | 🟡 代码待写 |
| **P1** | **构建 adapters(ingest) + exporters**：ingest(Noitom/Manus 近 1:1 · OpenXR · Rokoko · BVH) + export(MANO · BVH/FBX · OpenXR · ROS2 · FreeMoCap · DexRetargeting/AnyTeleop)。可用录制流/schema 离线做，无需物理设备 | 🟡→🔬 |
| **P2** | **集成外部物理设备**：Hi5 / Manus / mHand 接真实设备流(用 P1 适配器)。mHand schema 待核实 → 暂经 BVH 导出 ingest | 🔬 |
| **P3** | **未来 Pro 硬件扩展**：多 IMU 指节等，**仅路线图**(不改当前硬件决策，不启 IMU 阵列竞争) | 🌌 |

> P0 = 纯格式 + FK（可 host 单测，无硬件依赖）。P1 = 协议侧软件（用 recorded streams/schema，无需物理设备）。P2 依赖第三方 SDK / 物理设备（mHand schema、Hi5 独立 SDK struct 待核实）。P3 = 长期路线图。**厂商手套 = 外部源/适配器，非竞品（D12）。**

---

## 9. 未决 / 待核实 (research_5 待核实清单)

签核前用户可就以下拍板；实现阶段取得权威 artifact 前**不编造字段名**：

- **mHand / Virdyn** 整条 wire schema — 无公开 artifact；暂经 BVH 导出 ingest。
- **Noitom Hi5** 独立 Unity SDK struct（拓扑由 Axis MocapApi 推断，精确流布局未确认）。
- **Rokoko** 默认 UDP 端口（常引 14043，插件可配）及每骨字段集。
- **Manus SDK** enum 值（读自社区镜像，出版前对官方 release 核对）。
- **smallest-three** 已按 P0 签核延后到 v2.1；`caps.SKEL_SMALLEST3=1` 的 v2.0 帧必须拒绝，不实现 80B 编解码。

---

## 10. 签核清单 (P0)

请用户逐项确认（或指出需改）：

- [x] canonical = **20 旋转关节**（§3.1 关节集 + 层级）
- [x] 旋转约定 = **w-first 四元数 / 父相对 / 右手 +Y up -Z fwd / 米**（§3.3）
- [x] wire = **version 0x02 capability-flagged TLV 变长帧**，v1 version-gate 并存（§4）
- [x] `caps` 位域 + TLV 注册表（§4.3 / §4.4）
- [x] 21 MediaPipe = **FK 派生视图**，不进 wire 帧（§3.4）
- [x] skeleton geometry = `REST_OFFSETS[25]` + `REST_MODEL_ID{u16 id,u16 revision}`，与 skeleton TLV 同帧必备，禁止指尖启发式外推（§3.4 / §4.4）
- [x] smallest-three **延后到 v2.1**，v2.0 首发只 f16×4（§9 建议）
- [x] 非目标边界（§2.2，尤其"不改硬件、不写回归/retarget、不改 v1"）
- [x] **生态对齐（D12）**：非竞品定位 + 厂商无关 v2 + 四段管线（§1）+ P0–P3 优先级（§8）

**签核状态：用户于 2026-07-28 批准全部 P0 项，并追加冻结 self-contained rest geometry 契约。**

签核后 → `superpowers:writing-plans` 生成 TDD 实现计划 → firmware/shared C + relay Python 镜像 + 金标测试。

---

## 相关

- `../../BP/research_5_data_formats_interop.md` — 格式互操作研究底稿（§A canonical-20 / §B 映射矩阵 / §C TLV 帧 / §D MANO 优势）
- `../../V7/STRATEGY.md` — D10 / D11 / D12 战略冻结
- `../../V7/07_dual_rep_layer.md` §1b — v2 Skeleton Layer 摘要
- `../../V7/ARCHITECTURE.md` §3/§8 — 数据流 + 真实性总表
- `firmware/shared/hand_token.{h,c}` + `relay/hand_token.py` — v1 实现（v2 复用 base 块 + CRC/f16）
