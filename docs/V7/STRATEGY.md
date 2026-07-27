# EchoGlove V7 — 战略决策冻结书 (STRATEGY)

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: Frozen (D1–D12 全部冻结)
> **Supersedes**: V6.0 战略 (Beta 仓库 docs/V6/)
> **来源**: 用户与 GPT5.6 对话校验 + 代码实测修正 (2026-07-22/23)

本文件是 EchoGlove 所有 BP/白皮书/产业合作/产品方案的**战略唯一真相源**。任何偏离需走战略变更评审。

---

## 0. 公司主航道

**具身智能人机交互入口公司** —— 三战略融合，以③为主航道：

1. 无障碍手语翻译（社会价值 + 首个商业验证场景）
2. 低成本 MOCAP 对标 Manus / SenseGlove / XR 动捕
3. **具身智能遥操作 / VLA / Agent 入口**（主航道）

**使命**：构建连接人类动作智能与 AI 系统的低成本多模态交互基础设施，让人类手部成为 AI 理解现实世界、学习操作、控制智能体的入口。

**定位**：**Human Hand Intelligence Layer（人体手部智能层）** —— 介于机器人本体/基础模型 与 应用 之间的数据入口层。**不**被框死成"动捕设备"或"机器人控制设备"。亦是**开放手部运动基础设施（open Hand Motion Infrastructure）**——Hi5/Manus/mHand 等厂商手套是**外部数据源/适配器，不是竞品**（D12）。

---

## 1. 冻结决策 D1–D12

| # | 决策 | 选择 | 冻结日期 |
|---|------|------|---------|
| D1 | 感知主线 | 视觉主导 + 可穿戴增强（非纯 CV，非纯手套）。Vision=World State，Glove=Hand State，融合=Human Intent | 2026-07-23 |
| D2 | 目标市场 | 具身智能遥操作 / 数据采集为优先 | 2026-07-23 |
| D3 | 数据标准 | **双表示层架构**（MANO Layer + Robot Action Layer）—— 核心壁垒 | 2026-07-23 |
| D4 | 对外定位 | B：面向具身智能的数据采集与人机交互基础设施；避开机器人本体/高端光学动捕/纯手语硬件三个正面战场 | 2026-07-23 |
| D5 | 数据战略 | C：Open Core + Commercial Data Asset | 2026-07-23 |
| D6 | 双产品线 | EchoGlove Lite（<¥500 BOM）+ EchoGlove Pro | 2026-07-23 |
| D7 | 第一代视觉 | AI 视觉**不进入第一代硬件**，Pro **预留 EGO Camera 接口**，后期 AI 眼镜融合 | 2026-07-23 |
| D8 | 手语模型 | 保留但战略降级 —— 手语是 Hand Token 的一种解释方式，非唯一输出 | 2026-07-23 |
| D9 | Pro 视觉接口 | **C 双生态兼容**：USB-C/WiFi/BT（消费侧接 AI 眼镜）+ ROS2/Ethernet/USB3 Vision（机器人侧） | 2026-07-23 |
| D10 | 数据格式路线 | **格式先行 + Open Hand Motion Infrastructure**：不对标 Hi5/mHand 硬件；Hand Token 升级为双向互操作层（通用 21-joint 骨架）；硬件方向不变（Lite=flex+单IMU→IK/ML 估计 21 关节；Pro 多 IMU 仅路线图，现在不启动） | 2026-07-26 |
| D11 | v2 canonical 表示 | **20 旋转关节为主表示 + 派生 21**：Hand Token v2 内部 canonical = 20-joint 旋转骨架（quaternion+rest-offset），前向运动学派生 21 MediaPipe 关键点位置作导出视图。**细化 D10**（21 仍是对外/视觉锚点与 web 前端）；换取对 Hi5/mHand/Manus/OpenXR 的无损 ingest | 2026-07-27 |
| D12 | 生态对齐与定位 | **EgoGlove = 开放手部运动基础设施（open Hand Motion Infrastructure），非 Hi5/Manus/mHand 竞品**：厂商手套 = 外部数据源/适配器。方向锚定 **MANO/SMPL-X + FreeMoCap + OpenXR Hands + ROS2·DexRetargeting/AnyTeleop + egocentric-AI 数据集**。Hand Token v2 = 厂商无关通用中间表示。管线 `Sensor Source → Hand Token v2 → Canonical Skeleton Layer → MANO/OpenXR/FreeMoCap/ROS2/Robot`。确认 P0–P3 优先级；硬件不变、不启 IMU 阵列竞争。**细化 D10/D11** | 2026-07-27 |

---

### D10 详解 — Open Hand Motion Infrastructure（2026-07-26 冻结，用户拍板）

EchoGlove/EgoGlove 定位从"手套设备"升级为 **开放手部运动基础设施 (Open Hand Motion Infrastructure)**：不正面对标 Hi5 / mHand / Manus 硬件，而是建立开放的双向互操作层，让任何手套（含第三方）都能进出统一手部运动表示。

**1. 硬件策略（格式先行，IMU 阵列仅路线图）**
- **Lite**：维持低成本 `flex(5) + 单腕 IMU`；用 sensor fusion + IK/ML **估计 21-joint 手骨架**（不新增指节 IMU）。
- **Pro**：**仅路线图**——预留 hybrid sensing / 多 IMU 指节架构能力；**现在不启动 IMU 阵列硬件研发**。
- 原则：**不改当前硬件方向，先做协议与生态。**

**2. 协议策略（双向互操作层）**
Hand Token 成为**双向手部运动互操作层**：既能 **ingest** 第三方手套流（Hi5 / mHand / Manus / Rokoko 式四元数骨架、通用 21-joint 骨架、外部手套适配器），也能 **export** 到生态格式（MANO / BVH / FBX / OpenXR / ROS·ROS2）。EgoGlove = 基础设施，非单一设备。

**3. Hand Token v2 数据模型（P0 冻结目标）**
- 数据模型字段：`wrist pose`、`joint rotations`、`joint angles`、`confidence`、`timestamp`、`source metadata`。
- 详细 wire-format 字节布局 + 适配器映射矩阵 → 待 3 份研究（`research_5`）落地后出 spec，交用户 **P0 冻结签核**，见 `07_dual_rep_layer.md`（v2 更新）与 `docs/superpowers/specs/`。

**4. 两层架构原则**
- **Sensor Layer**：flex / IMU / 未来传感器（设备侧，可保持紧凑 sensor-level 帧）。
- **Skeleton Layer**：通用 **21-joint** 表示（MediaPipe 拓扑：腕1 + 每指4×5=21）→ MANO → 生态。**Hand Token v2 = Skeleton Layer 的互操作货币**。

**优先级**：`P0` 冻结 Hand Token v2 数据模型 · `P1` 骨架抽象层 · `P2` 外部手套适配器 · `P3` MANO/BVH/FBX/OpenXR/ROS 导出器。

> **与 D3 关系**：D10 在 D3 双表示层（MANO + Robot Action）**上游**新增通用 Skeleton Layer。管线变为 `Sensor → Skeleton Layer(21-joint Hand Token v2) → {MANO Layer, Robot Action Layer} + 各格式导出器`，且可被外部手套在 Skeleton Layer 注入。**强化而非取代 D3**。21-joint 与 MANO(16)/OpenXR(26) 可互映射。

---

### D11 详解 — v2 canonical = 20 旋转关节为主 + 派生 21（2026-07-27 冻结，用户拍板；细化 D10）

研究 `research_5_data_formats_interop.md` 落地后, 明确 **21 MediaPipe 关键点是"位置"表示**(视觉/web 语系), 而 Hi5/mHand/Manus/OpenXR 等专业手套输出的是**"旋转"表示**(每关节四元数)。二者不可互相替代: 只存 21 位置无法无损 ingest 旋转骨架 (丢关节朝向), 只存旋转则需 FK 才得位置。用户拍板采**调和方案**:

- **canonical 主表示 = 20 旋转关节** (腕1 + 拇指3[CMC/MCP/IP] + 4指×4[掌骨/近节/中节/远节]; 指尖派生)。理由: = Noitom Axis 每手20、= OpenXR-26 去 6 可派生 (PALM+5指尖)、⊃ MANO-16 (多出4非拇指掌骨)、覆盖 SteamVR 20 DOF 骨。**是无损 ingest 专业手套的最小完整旋转集**。四元数 `w,x,y,z` (w-first, 与 v1 一致)、父相对、右手 +Y up/-Z fwd; 附 rest-offset 表。
- **21 MediaPipe = 派生导出视图**: 由 20 旋转 + rest-offset 经前向运动学派生 (16 MANO 关节 + 5 指尖位置 ≈ MediaPipe 21)。**D10 的 21-keypoint 对外锚点、web 前端、视觉融合公共空间全部不变**——只是内部主存储从"位置"改为"旋转"。
- **v1 保持不变**; **v2 = capability-flagged TLV 变长帧** (magic `HT`, version `0x02`, `caps` 位域声明四元数序/handedness, `total_len`, v1兼容 base 块 + TLV 区; 未知 TLV 按长度跳过)。Lite ~82B、Pro/ingested ~166–246B。version-gate 向后兼容。详见 `07_dual_rep_layer.md` v2 章与 `docs/superpowers/specs/2026-07-27-hand-token-v2-design.md`。

> **为何是"细化"而非推翻 D10**: D10 的战略实质(格式先行、双向互操作、21 为生态锚点、硬件不变)全部保留; D11 只是把"通用 21-joint 骨架"的**内部实现**精确化为"20 旋转主 + 派生 21", 以获得 D10 追求的"无损 ingest 第三方手套"能力。管线更新为 `Sensor → Skeleton Layer(v2: 20-rotation canonical, 派生 21) → {MANO, Robot Action} + BVH/FBX/OpenXR/ROS 导出器`。

---

### D12 详解 — 生态对齐: 开放手部运动基础设施（2026-07-27 冻结，用户拍板；细化 D10/D11）

用户在批准 D11 后，要求在写协议代码前做一次**生态对齐**：把定位锚定到一组开放标准/生态，并明确厂商手套的角色。

**1. 定位: 非竞品, 是枢纽**
EgoGlove **不是** Hi5/Manus/mHand 的竞品。这些商业手套被视为**外部数据源 + 适配器**（在 Skeleton Layer ingest）。EgoGlove 的方向 = 开放 **Hand Motion Infrastructure** 层，锚定:
- **MANO/SMPL-X** — 人手 canonical 参数化表示（数字人/研究事实标准）。
- **FreeMoCap** — 开放动捕数据管线 + 导出生态的参照。
- **OpenXR Hand Tracking** — XR 运行时兼容。
- **ROS2 + DexRetargeting/AnyTeleop** — 人手→机器人灵巧手的桥。
- **egocentric-AI 数据集**（InterHand2.6M / COCO-WholeBody / Ego 类） — 未来具身智能数据集兼容。

**2. Hand Token v2 = 厂商无关的通用中间表示**
v2 **不围绕任何厂商手套设计**。canonical 骨架（D11 的 20 旋转关节）是数学中立的最小完整旋转集；任何源（flex/IMU/视觉/外部手套）ingest 进来，任何生态（MANO/OpenXR/FreeMoCap/ROS2/Robot）export 出去。

**3. 管线（四段）**
```
Sensor Source (flex / IMU / vision / external gloves)
        ↓  ingest / encode
Hand Token v2             (通用中间表示 = 自描述 wire 帧)
        ↓  decode
Canonical Skeleton Layer (20 旋转关节, w-first, 父相对; FK 派生 21)
        ↓  export / retarget
MANO / OpenXR / FreeMoCap / ROS2 / Robot   (经 DexRetargeting/AnyTeleop)
```
> Hand Token v2（序列化载体）与 Canonical Skeleton Layer（解码后的 20 关节语义模型）是同一 D11 设计的两面：v2 帧承载骨架，消费者解码为 canonical 骨架后再 export/retarget。与 D3 双表示层一致（MANO Layer + Robot Action Layer 是两个 export 目标）。

**4. 优先级（确认）**
- **P0**: 冻结 canonical 骨架 + Hand Token v2（wire format + 跨语言金标）。← 当前，待代码签核
- **P1**: 构建 **adapters（ingest）与 exporters**（MANO/OpenXR/FreeMoCap/ROS2·DexRetargeting）——协议侧软件，可用录制流/schema 离线做。
- **P2**: **集成外部物理设备** Hi5/Manus/mHand（用 P1 适配器接真实设备流）。
- **P3**: 未来 Pro 硬件扩展（多 IMU 等，仅路线图）。

**5. 硬约束（不变）**
- **不改当前硬件决策**（D6/D10）：Lite = flex+单腕 IMU；Pro 多 IMU 仅路线图。
- **不启动 IMU 阵列竞争**——不做"每指节 9 轴 IMU"军备竞赛去对标 Hi5/mHand 硬件；专注**协议 / 互操作 / 生态**。

> **为何"细化"而非新战略**: D12 不改 D1–D11 任何选择，只把 D10 的"开放基础设施"用一组具体开放生态锚点（MANO/FreeMoCap/OpenXR/ROS2·DexRetargeting/egocentric 数据集）钉死，并确认 P0–P3 落地次序 + 厂商手套=外部源/适配器（非竞品）的角色。

---

## 2. 核心壁垒：双表示层架构 (D3)

```
                     ┌── MANO Layer ────→ Unity / Unreal / XR / 数字人 / 手语
Sensor Stream ──→ Hand Token ──┤
                     └── Robot Action Layer ──→ joint angle + 6DoF 腕位姿 + vel/acc
                                              + contact + force → ROS2 / 机械臂 / 灵巧手 / VLA / RL
```

**为什么这是壁垒**：
- 避免被单一应用框死：同一硬件流，XR/数字人侧取 MANO，机器人侧取 Robot Action，互不污染。
- **MANO 层**：服务 Unity/Unreal/XR/数字人/手语，参数化手部 mesh，兼容 ms-MANO / MediaPipe 生态。
- **Robot Action Layer**：输出 joint angle + 6DoF 腕位姿 + 速度/加速度 + 接触状态 + 力估计，服务 ROS2/机械臂/灵巧手/VLA/RL 训练数据。
- 数据飞轮：硬件 → 采集 → 训练 → 模型 → SDK → 应用 → 用户 → 数据。

## 3. 五层壁垒体系

1. **低成本多模态硬件**（Lite <¥500 BOM，对标 Manus 数千元）
2. **双表示层数据标准**（核心，D3）
3. **数据闭环**（采集→训练→部署→反馈）
4. **开放生态**（兼容 PyTorch/TFLite/ROS2/Unity/Unreal/MANO/MediaPipe）
5. **人类操作数据资产**（长期壁垒，行业垂直数据）

---

## 4. 双产品线 (D6)

| 产品线 | BOM 目标 | 核心硬件 | 目标场景 | 视觉 |
|---|---|---|---|---|
| **EchoGlove Lite** | <¥500 | ESP32-S3 + Flex + IMU + BLE/WiFi | 消费 / 教育 / XR / 手语入口 | 无（D7） |
| **EchoGlove Pro** | 企业级 | ESP32-P4 + 工业级 IMU + 柔性传感 + 力接口 + EGO Camera 接口 + Depth 接口 | 具身智能数据入口 / 遥操作 / VLA 训练 | 预留接口（D7），双生态兼容（D9） |

**Pro 传感器升级排序**（来自 GPT5.6 校验，认可）：
柔性电阻/电容 eSkin ★★★★★ > 磁感应（磁跟踪）★★★★ > PVDF 压电（动态好静态差）★★★ > sEMG（数据难，延后）

**Flex 风险点**（一致性差/老化/标定难/无力信息）：Lite 保留 Flex，Pro 升级 eSkin/Force。

---

## 5. 数据战略 (D5)：Open Core + Commercial Data Asset

- **开放基础数据**（传感器原始 + MANO 基础动作）→ 建开发者生态
- **商业高级数据**（工业操作 / 机器人任务 / 医疗康复 / 专业手语）→ 形成壁垒
- `data/` 分层：`data/open/`（Open Core）vs `data/commercial/`（gitignore，不入库）

---

## 6. GPT5.6 精华（认可并保留）

- **核心洞察**："捕获的是手势（gesture label）不是手部状态（hand state）" —— 从 Classifier 转向 Pose Estimation → MANO → Action。商业价值差一个数量级。
- **Vision + Proprioception 互补**（类人：眼睛看世界 + 本体感觉知手位）。
- **EGO 视角排序**：头戴 AI 眼镜 ★★★★★（最符 VLA/Gemini Robotics/UMI/Ego4D）> 腕部 ★★★ > 胸口 ★★。
- **硬件不必推倒**：ESP32-S3 / LSM6DSV16X 值得保留甚至升级（工业级 IMU）。
- **技术真实性 4 级**：已实现 / 工程可实现（6-12 月）/ 需研发验证 / 长期方向。BP 与文档强制按此分级。
- **诚实修正**："<3ms TinyML" 跑不了完整 Transformer+fusion —— 拆为"传感器预处理在 MCU，AI 推理在 edge gateway / 移动 / 云"。
- **UMI/ALOHA 不替代**，成为 Human Data Capture Layer 的互补件。

## 7. GPT5.6 糟粕 / 代码现实修正（GPT 没读代码导致）

1. **GPT 的"已实现资产"过度乐观**：它把设计文档当实现。实测（2026-07-10）：LSM6DSV16X 驱动**不存在**（IMU 输出全零）、S3→P4 有线 UART（`WIRED_UART`）**不在代码里**、on-board C6 是 ESP-Hosted **跑不了 ESP-NOW 桥**、唯一真实端到端 = P4 mock 数据点亮屏幕。文档"已实现"严格只列：flex-internal-ADC、S3 ESP-NOW、P4 UART-RX+USB-CDC、P4 standalone mock。
2. **数据集基本不存在**：`data/` 只有零星 CSV。"数据飞轮/数据资产"是 plan 不是 asset，必须诚实标注为路线图。
3. **通信栈硬伤**：on-board C6 = ESP-Hosted 不能 ESP-NOW 透传。生产期 C6 走 ESP-Hosted Wi-Fi/UDP；开发期走 S3→P4 直连 UART（仅设计）。
4. **"亚秒级连续手语识别"未证明** → 需建 benchmark（延迟/字词错误率/连续准确率），BP 降级为目标。
5. **UWB 定位**：对 egocentric VLA 可能冗余（视觉可给位姿），且增 BOM 成本 → Pro 可选、Lite 不做。
6. **竞品分析需定量矩阵**：送审中关村/WRC/京东需 6 维度 × N 竞品矩阵，见 BP 第 6 章 + `docs/BP/research_*.md`。

---

## 8. 战略变更评审

D1–D12 全部冻结，进入 BP 撰写与产品落地阶段。任何战略变更需：
1. 在本文件追加 Dn 条目并标注日期
2. 同步更新 `docs/BP/` 与 `docs/V7/ARCHITECTURE.md`
3. commit 信息注明 "strategic change: Dn"

---

## 相关文档

- `ARCHITECTURE.md` — 双表示层系统架构与数据流
- `06_decision_summary.md` — V6→V7 决策记录与真实性分级
- `../BP/EchoGlove_BP_V2.1.md` — 产业级商业计划书（按本战略编写）
- `../BP/research_*.md` — 4 份竞品/学术研究（支撑第 6 章）
