# EchoGlove V7 — 战略决策冻结书 (STRATEGY)

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: Frozen (D1–D9 全部冻结)
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

**定位**：**Human Hand Intelligence Layer（人体手部智能层）** —— 介于机器人本体/基础模型 与 应用 之间的数据入口层。**不**被框死成"动捕设备"或"机器人控制设备"。

---

## 1. 冻结决策 D1–D9

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

D1–D9 全部冻结，进入 BP 撰写与产品落地阶段。任何战略变更需：
1. 在本文件追加 Dn 条目并标注日期
2. 同步更新 `docs/BP/` 与 `docs/V7/ARCHITECTURE.md`
3. commit 信息注明 "strategic change: Dn"

---

## 相关文档

- `ARCHITECTURE.md` — 双表示层系统架构与数据流
- `06_decision_summary.md` — V6→V7 决策记录与真实性分级
- `../BP/EchoGlove_BP_V2.1.md` — 产业级商业计划书（按本战略编写）
- `../BP/research_*.md` — 4 份竞品/学术研究（支撑第 6 章）
