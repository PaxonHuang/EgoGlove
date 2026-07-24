# EgoGlove — Claude Code 项目指南

> EgoGlove: Egocentric Hand Intelligence Layer — dual-line wearable+vision human-robot interaction infrastructure for embodied AI.

本文件是 Claude Code 在本仓库工作时的上下文与纪律。每次会话开始必读。

## 1. 项目定位（已冻结）

EgoGlove 是**具身智能人机交互入口公司**的基础设施层。主航道 = 具身智能遥操作/数据采集；手语翻译是第一个商业验证场景，不是终局。

核心壁垒 = **双表示层数据标准**：
- **MANO Layer** → Unity/Unreal/XR/数字人/手语
- **Robot Action Layer** → joint angle + 6DoF 腕位姿 + 速度/加速度 + 接触状态 + 力估计 → ROS2/机械臂/灵巧手/VLA/RL

冻结战略决策见 `docs/V7/STRATEGY.md`（D1–D9 全部冻结）。所有 BP/白皮书/产业合作材料按此编写，不得偏离。

## 2. 仓库结构（Monorepo）

```
firmware/
  lite/      # EchoGlove Lite: ESP32-S3 + Flex + IMU + BLE/WiFi, <¥500 BOM (消费/教育/XR/手语入口)
  pro/       # EchoGlove Pro:  ESP32-P4 + 高精度IMU + 柔性传感 + 力接口 + EGO Camera接口 + Depth接口 (具身智能数据入口)
  shared/    # 跨产品线共享驱动/协议/校准
base_station/  # P4/网关侧固件与上位机桥接
relay/          # Python FastAPI 中继 (WS/NLP/TTS/路由)
models/
  mano/      # MANO 参数化手部表示
  robot/     # Robot Action Layer 推理与对齐
  slr/       # 手语识别模型 (战略降级: Hand Token 的一种解释方式)
  shared/    # 跨模型骨干/工具
web/           # React3F / 前端
sdk/           # PyTorch/TFLite/ROS2/Unity 集成 SDK
data/          # Open Core 数据 + 商业数据资产 (分层)
docs/          # V7/ BP/ archive/
templates/     # 项目模板 (PlatformIO/ROS2 pkg/Unity)
scripts/       # 仓库工具脚本
```

## 3. 分支策略

```
main (stable)  ←  develop (integration)  ←  feature/*
```

- `main` 仅接受来自 `develop` 的 PR / merge，保持可发布
- `develop` 为集成分支
- `feature/<scope>-<desc>` 特性分支，完成后合回 develop
- 重大重构走 `refactor/*`，紧急修复走 `hotfix/*` 合回 main+develop

## 4. 真实性分级（BP 与文档强制）

所有能力描述必须带四级标注，不写想象中的能力：
- ✅ 已实现 (code-verified)
- 🟡 工程可实现 (6–12 月)
- 🔬 需研发验证
- 🌌 长期方向

详见 `docs/BP/` 附录与 `docs/V7/06_decision_summary.md`。

## 5. 工作纪律

### Git 身份（强制）
- **始终以 `PaxonHuang <quenchkidney@outlook.com>` 提交**，绝不使用 root/host 默认身份
- **绝不加 AI co-author 署名** (无 `Co-Authored-By: Claude` 等)
- 提交前自检: `git config user.email` 必须是 quenchkidney@outlook.com

### 提交
- commit message 用 `type(scope): 描述` 格式 (feat/fix/docs/refactor/chore/test)
- 中文摘要可接受，描述体可中英混排
- 未经用户明确指示不 push；push 用 `--force-with-lease` 而非 `--force`
- 每完成一个阶段性任务或重要更改 → 更新 memory + commit

### 知识图谱 (graphify)
- 当 `graphify-out/graph.json` 存在时，代码库问题先 `graphify query "<问题>"`
- 内容落地（V7 文档 + 首批固件代码）后再跑 `graphify update .`，目前未生成

### 遇阻
- 思考执行遇决策问题/重大发现/重大 bug → **停下让用户决策**，不要自行绕过
- 不编造数据：引用前核实来源；待人工核对项明确标注 "待人工核对"

## 6. 历史仓库迁移指引

本仓库是 V7 统一 monorepo，整合并取代以下历史仓库：

| 历史仓库 | 状态 | 迁移指引 |
|---|---|---|
| `EchoGlove-SLR-MOCAP-Beta` (Flex+IMU 双手) | **archive** | `glove_firmware/` → `archive/beta/firmware/` 参考；V6 文档 → `docs/V6-legacy/` (如需) |
| `EchoGlove-SLR-MOCAP-Alpha` (Hall+IMU) | **archive** | 仅作硬件演进参考，不直接迁入 |
| `EchoGlove-SLR-MOCAP-Portal-old` | GitHub archived | 历史门户，不迁移 |

历史仓库保留只读，新工作全部在 `EgoGlove` 进行。`firmware/*/` 的新代码不照搬 Beta，按 V7 双产品线重写。

## 7. Memory 分层

- **战略/架构** memory → 已落入 `docs/V7/STRATEGY.md` + `docs/V7/ARCHITECTURE.md`（repo 内，协作者可见）
- **git/个人纪律** memory → 保留在 `~/.claude/projects/.../memory/`（不进 repo）
- 跨会话恢复上下文：先读本文件 + `docs/V7/STRATEGY.md`，勿重读全文文档

## 8. 关键技术约束（来自 V7 冻结）

- D7: 第一代硬件**不进 CV**，但 Pro **预留 EGO Camera 接口**，后期 AI 眼镜融合。BP/路线图中 CV 仅写 roadmap。
- D9: Pro 第一代视觉模块接口 = **双生态兼容** (USB-C/WiFi/BT 消费侧 + ROS2/Ethernet/USB3 Vision 机器人侧)
- UWB 对 egocentric VLA 可能冗余 → Pro 可选、Lite 不做
- "亚秒级连续手语识别" 未证明 → BP 降级为目标，需建 benchmark
- 推理分工诚实化：传感器预处理在 MCU，AI 推理在 edge gateway/移动/云（<3ms TinyML 跑不了完整 Transformer+fusion）
