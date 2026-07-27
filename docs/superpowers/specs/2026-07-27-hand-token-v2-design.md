# Hand Token v2 — Skeleton Layer 互操作协议设计 (Design Spec)

> **Date**: 2026-07-27
> **Status**: 🔒 待用户 P0 冻结签核 (Design frozen pending sign-off) — **签核前不写实现代码**
> **Owner**: PaxonHuang
> **Decision**: 实现 STRATEGY.md **D11**（细化 D10）
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

- 21 = 由 20 旋转 + `REST_OFFSETS` 经 FK 派生：16 MANO 关节位置 + 5 指尖位置（每 Distal 经 rest-offset 偏移）。
- MediaPipe 索引契约（research_5 §3，核对 `HandLandmark` enum）：`WRIST=0`；`THUMB_CMC/MCP/IP/TIP=1..4`；`INDEX 5..8`；`MIDDLE 9..12`；`RING 13..16`；`PINKY 17..20`。
- 21 是**导出视图**，不进 wire 帧（可由任意消费者本地 FK 得出）；web 前端 / 视觉融合公共空间继续用 21。

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
| 6 | `SKEL_SMALLEST3` | 骨架四元数编码：0 = f16×4（160B）；1 = smallest-three（80B） |
| 7 | reserved | 置 0 |

### 4.4 TLV 初始注册表

| type | 名 | value |
|---|---|---|
| `0x01` | `SKELETON_QUAT20` | 20 × quaternion；编码按 `caps` bit6（f16×4=160B 或 smallest-three=80B）；顺序 = §3.1 关节 0..19 |
| `0x02` | `REST_OFFSETS` | 20 × (dx,dy,dz) f16 父→子骨向量 → 使能 FK / local↔global / 派生 21 MediaPipe |
| `0x03` | `JOINT_ANGLES` | Manus-ergonomics 式紧凑角（每手 20：{MCP spread, MCP stretch, PIP stretch, DIP stretch}×5）供快速 retarget |
| `0x04` | `GLOBAL_WRIST_POSE` | 腕 pos f32×3 + quat f16×4，于命名系（当 `caps` bit3） |
| `0x05` | `FINGERTIP_CONTACT_FORCE` | 超出 base `contact[5]`/`force[5]` 的扩展每指尖接触/力 |
| `0x06` | `SOURCE_PROVENANCE` | u8 厂商 id + u8 源格式 + u16 fps → 记录该帧由 OpenXR/Manus/Noitom/Rokoko/BVH ingest 而来 |
| `0x07` | `HAND_SHAPE_BETA` | 已知校准手型时的 MANO β（10 × f16） |

> 厂商 id / 源格式的枚举值在实现阶段随代码固化（`hand_token.h` 常量），本 spec 只定义字段存在性与语义。

### 4.5 载荷大小

| 帧 | 组成 | 大小 |
|---|---|---|
| **Lite v2** | 头 11B + base 69B + CRC 2B（`caps=0`，无 TLV） | **≈ 82B**（v1 79B + 3B caps/len） |
| **Pro/ingested (f16 骨架)** | Lite 核 + `SKELETON_QUAT20`(3+160) + 可选 TLV | **≈ 246B** |
| **Pro/ingested (smallest-three)** | Lite 核 + `SKELETON_QUAT20`(3+80) + 可选 TLV | **≈ 166B** |

双手 = 两帧（device_id bit6 区分 L/R）。

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

### 5.2 Hand Token → Export（canonical-20 → 生态）

| 目标 | 规则 | 有损? |
|---|---|---|
| **MANO** | 20→16 折 4 掌骨进掌 → θ/β（16⊂20，投影非猜测） | 20→16 轻损（掌骨并入） |
| **BVH / FBX** | 由 20 关节生成 HIERARCHY + MOTION（quat→Euler） | Euler 无损；拓扑/命名映射有损 |
| **OpenXR / SteamVR** | 合成 26（派生 PALM/指尖）或 31（加 Aux）；w-first→w-last | 指尖/palm 派生 |
| **ROS2** | `JointState`：name/position(rad)/**effort = force[5]**；腕→`PoseStamped`(quat x,y,z,w) | quat→单 DOF/关节有损（丢离轴旋转） |
| **21 MediaPipe** | FK 派生（§3.4） | 无损（位置视图） |

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
| **跨语言金标** | v2 canonical 参考帧（Lite base-only + Pro with-skeleton 各一）以 `GOLDEN_HEX` 常量共享于 host C 单测（`firmware/shared/test/`）与 `relay/test_hand_token.py`，**逐字节双向一致** |
| **round-trip** | `serialize(parse(frame)) == frame`；`parse(serialize(token)) == token`（含 f16 量化容差断言） |
| **version-gate** | v2 parser 正确分流 v1/v2 帧；v1-only parser 干净拒绝 v2；损坏 CRC / 错 magic / 截断 `total_len` 均被拒 |
| **TLV 前向兼容** | 注入未知 `type` TLV → parser 按 `len` 跳过、其余字段正确 |
| **caps 语义** | `QUAT_WLAST` 置位帧 ingest 后归一到 w-first；`SKEL_SMALLEST3` 编解码 round-trip |
| **FK 派生** | 由 `SKELETON_QUAT20` + `REST_OFFSETS` FK → 21 MediaPipe 位置，对已知手型断言几何正确 |

---

## 8. 实现分期 (D10 优先级 → 本 spec 落地顺序)

| 阶段 | 内容 | 真实性目标 |
|---|---|---|
| **P0** | 本 spec 冻结签核（当前）；v2 wire format（caps/TLV/version-gate）+ 金标帧 | 🟡 代码待写 |
| **P1** | canonical-20 骨架抽象层（C struct + Python `HandTokenV2` + FK 派生 21） | 🟡 |
| **P2** | 外部手套适配器（先 Noitom/Manus 近 1:1；OpenXR；Rokoko；BVH；mHand 待 schema） | 🟡→🔬 |
| **P3** | 导出器（MANO / BVH / FBX / OpenXR / ROS2） | 🟡→🔬 |

> P0/P1 是纯格式 + FK（可 host 单测，无硬件依赖）= 🟡。P2/P3 依赖第三方 SDK/权威 schema，部分 🔬（mHand schema、Hi5 独立 SDK struct 待核实）。

---

## 9. 未决 / 待核实 (research_5 待核实清单)

签核前用户可就以下拍板；实现阶段取得权威 artifact 前**不编造字段名**：

- **mHand / Virdyn** 整条 wire schema — 无公开 artifact；暂经 BVH 导出 ingest。
- **Noitom Hi5** 独立 Unity SDK struct（拓扑由 Axis MocapApi 推断，精确流布局未确认）。
- **Rokoko** 默认 UDP 端口（常引 14043，插件可配）及每骨字段集。
- **Manus SDK** enum 值（读自社区镜像，出版前对官方 release 核对）。
- **smallest-three** 是否作为 v2.0 首发编码，或延后到 v2.1（P0 只需 f16×4 即可实现；smallest-three 是带宽优化）。← **建议延后**，降低首版复杂度（YAGNI）。

---

## 10. 签核清单 (P0)

请用户逐项确认（或指出需改）：

- [ ] canonical = **20 旋转关节**（§3.1 关节集 + 层级）
- [ ] 旋转约定 = **w-first 四元数 / 父相对 / 右手 +Y up -Z fwd / 米**（§3.3）
- [ ] wire = **version 0x02 capability-flagged TLV 变长帧**，v1 version-gate 并存（§4）
- [ ] `caps` 位域 + TLV 注册表（§4.3 / §4.4）
- [ ] 21 MediaPipe = **FK 派生视图**，不进 wire 帧（§3.4）
- [ ] smallest-three **延后到 v2.1**，v2.0 首发只 f16×4（§9 建议）
- [ ] 非目标边界（§2.2，尤其"不改硬件、不写回归/retarget、不改 v1"）

签核后 → `superpowers:writing-plans` 生成 TDD 实现计划 → firmware/shared C + relay Python 镜像 + 金标测试。

---

## 相关

- `../../BP/research_5_data_formats_interop.md` — 格式互操作研究底稿（§A canonical-20 / §B 映射矩阵 / §C TLV 帧 / §D MANO 优势）
- `../../V7/STRATEGY.md` — D10 / D11 战略冻结
- `../../V7/07_dual_rep_layer.md` §1b — v2 Skeleton Layer 摘要
- `../../V7/ARCHITECTURE.md` §3/§8 — 数据流 + 真实性总表
- `firmware/shared/hand_token.{h,c}` + `relay/hand_token.py` — v1 实现（v2 复用 base 块 + CRC/f16）
