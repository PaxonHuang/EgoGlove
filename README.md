# EgoGlove

> **EgoGlove: Egocentric Hand Intelligence Layer** — dual-line wearable + vision human-robot interaction infrastructure for embodied AI.

EgoGlove 是面向具身智能的**人体手部智能层**：以低成本多模态硬件捕获手部状态，以**双表示层数据标准**（MANO Layer + Robot Action Layer）同时服务 XR/数字人/手语 与 ROS2/机械臂/灵巧手/VLA/RL，构建连接人类动作智能与 AI 系统的交互基础设施。

## 双产品线

| 产品线 | 定位 | 硬件 | 目标 |
|---|---|---|---|
| **EgoGlove Lite** | 消费/教育/XR/手语入口 | ESP32-S3 + Flex + IMU + BLE/WiFi, <¥500 BOM | 低成本多模态手部状态采集 |
| **EgoGlove Pro** | 具身智能数据入口 | ESP32-P4 + 工业级 IMU + 柔性传感 + 力接口 + EGO Camera 接口 + Depth 接口 | 遥操作/数据采集/VLA 训练数据 |

## 核心壁垒：双表示层架构

```
Sensor Stream → Hand Token → ┌─ MANO Layer      (Unity/Unreal/XR/数字人/手语)
                             └─ Robot Action Layer (joint + 6DoF + vel/acc + contact + force → ROS2/机械臂/灵巧手/VLA/RL)
```

避免被框死成"动捕设备"或"机器人控制设备"——定位为**人体手部智能层**。

## 仓库结构

```
firmware/{lite,pro,shared}/   base_station/   relay/
models/{mano,robot,slr,shared}/   web/   sdk/   data/
docs/{V7,V8}/   templates/   scripts/
```

详见 `CLAUDE.md`。伞仓（项目定位/跨仓真相源/ADR）见 [PaxonHuang/EgoMotion](https://github.com/PaxonHuang/EgoMotion)。

## 文档

- **战略**: `docs/V7/STRATEGY.md` (D1–D12 冻结决策)
- **架构**: `docs/V7/ARCHITECTURE.md` (双表示层 + 系统架构 + 真实性总表)
- **V8 语义层**: `docs/V8/` (Human Motion Infrastructure proposal，**未实现**)
- **ADR**: `docs/superpowers/specs/adr/` (ADR-001 仓库拓扑 / ADR-002 传感器总线)
- **BP**: 独立 BP 仓 [PaxonHuang/BP](https://github.com/PaxonHuang/BP)（**private**，唯一 BP 资产仓）

## Demo1 当前进度（2026-08-19）

ESP32-S3 + 11×LSM6DSV16X + 3×HKVT-M3A → 统一 acquisition timeline → USB。

| 阶段 | 状态 |
|---|---|
| Phase 1A — HKVT-M3A minimal driver | ✅ 软件层完成（commit `f29f398`，16 host 单测 PASS；opcode 0x03/0x1A 待 HW 验证） |
| Phase 1B — 单颗 LSM6DSV16X (native ESP-IDF, `firmware/pro/`) | 🏗️ 未开始 |
| Phase 1C/1D — 11 IMU + 3 HKVT acquisition | 🏗️ 未开始 |

真实性与完整真相源见伞仓 `EgoMotion/docs/STATUS.md`。

## 分支策略

`main (stable) ← develop (integration) ← feature/*`

## 历史仓库迁移

本仓库为 V7 统一 monorepo，取代以下历史仓库（保留只读 archive）：

- **EchoGlove-SLR-MOCAP-Beta** (Flex+IMU 双手, V5/V6) → archive，固件代码参考但不直接迁入，按 V7 双产品线重写
- **EchoGlove-SLR-MOCAP-Alpha** (Hall+IMU) → archive，仅作硬件演进参考
- **EchoGlove-SLR-MOCAP-Portal-old** → GitHub 已 archived

新工作**全部**在 `EgoGlove` 进行。

## 真实性分级

所有能力描述带四级标注：✅ 已实现 / 🟡 工程可实现 / 🔬 需研发验证 / 🌌 长期方向。详见 `docs/V7/06_decision_summary.md`。

## License

MIT (见 `LICENSE`)
