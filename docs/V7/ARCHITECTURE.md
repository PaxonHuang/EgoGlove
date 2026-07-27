# EchoGlove V7 — 系统架构 (ARCHITECTURE)

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: Design target (V7)
> **Implements**: `STRATEGY.md` D1–D12
> **Supersedes**: V6.0 架构（Beta 仓库 docs/V6/01_architecture_diagrams.md）

本文件描述 V7 双产品线（Lite/Pro）的目标系统架构。所有能力描述带四级真实性标注：✅ 已实现 / 🟡 工程可实现（6-12 月）/ 🔬 需研发验证 / 🌌 长期方向。

---

## 1. 设计原则

1. **双表示层优先**（D3）：硬件流统一，输出分叉为 MANO Layer 与 Robot Action Layer，互不污染。
2. **视觉主导 + 可穿戴增强**（D1）：Vision = World State，Glove = Hand State，融合 = Human Intent。第一代硬件不进 CV（D7），但 Pro 预留 EGO Camera 接口。
3. **推理分工诚实化**：传感器预处理在 MCU，AI 推理在 edge gateway / 移动 / 云（<3ms TinyML 跑不了完整 Transformer+fusion）。
4. **开放生态**（D4/D5）：兼容 PyTorch / TFLite / ROS2 / Unity / Unreal / MANO / MediaPipe。
5. **双产品线共享核心**（D6）：`firmware/shared/` 跨 Lite/Pro 复用协议、校准、Hand Token 生成。
6. **开放手部运动基础设施 / 非竞品**（D12）：EgoGlove **不**对标 Hi5/Manus/mHand 硬件；厂商手套 = **外部数据源/适配器**。方向锚定 MANO/SMPL-X · FreeMoCap · OpenXR Hands · ROS2·DexRetargeting/AnyTeleop · egocentric-AI 数据集。Hand Token v2 = **厂商无关**通用中间表示。

---

## 2. 双产品线硬件架构

### 2.1 EchoGlove Lite（消费 / 教育 / XR / 手语入口）

```
┌─────────────────────────────────────────────┐
│           EchoGlove Lite (单手)              │
│  ESP32-S3 N16R8                              │
│  ├── 5× Flex (2.2" resistive, internal ADC1) │ ✅ V6 已实现
│  ├── LSM6DSV16X 6-axis IMU @0x6A            │ 🟡 驱动待实现
│  ├── BLE / WiFi                              │ 🟡
│  └── Tier1 预处理 (filter/normalize)         │ ✅ 结构在
│  BOM 目标 <¥500/手                            │
└─────────────────────────────────────────────┘
         │ BLE/WiFi
         ▼
   Phone / PC Relay (Tier2/3 推理)
```

### 2.2 EchoGlove Pro（具身智能数据入口）

```
┌──────────────────────────────────────────────────────────┐
│                EchoGlove Pro (单手)                       │
│  ESP32-P4 (400MHz RV32, 32MB PSRAM)                      │
│  ├── 5× 柔性 eSkin / Force 传感 (升级自 Flex) 🔬          │
│  ├── 工业级 IMU (LSM6DSV16X 升级款) 🟡                    │
│  ├── 力接口 (contact + force estimate) 🔬                 │
│  ├── EGO Camera 接口 (预留, D7) 🌌                        │
│  ├── Depth 接口 (预留) 🌌                                  │
│  └── 双生态通信 (D9):                                     │
│      ├── USB-C / WiFi / BT  (消费侧 → AI 眼镜)           │
│      └── ROS2 / Ethernet / USB3 Vision (机器人侧) 🟡      │
└──────────────────────────────────────────────────────────┘
         │
         ▼
   Base Station / Edge Gateway / Cloud (Tier2/3)
```

---

## 3. 双表示层数据流（核心，D3）

```
┌──────────┐   raw sensor     ┌──────────────┐   Hand Token    ┌─────────────────────────┐
│  Sensor  │ ───────────────→ │ Preprocess   │ ──────────────→ │   Hand Token Generator  │
│  Layer   │  flex/imu/force  │ (MCU, <3ms)  │  normalized     │  (joint+pose+vel+force) │
└──────────┘                  └──────────────┘  feature vec    └────────────┬────────────┘
                                                                                   │
                                              ┌────────────────────────────────────┴──┐
                                              │                                         │
                                    ┌─────────▼──────────┐                  ┌──────────▼───────────┐
                                    │   MANO Layer       │                  │  Robot Action Layer  │
                                    │  (parametric hand) │                  │  (action vector)     │
                                    │  → mesh + verts    │                  │  → joint + 6DoF腕    │
                                    └─────────┬──────────┘                  │  + vel/acc + contact │
                                              │                              │  + force             │
                                ┌─────────────┼──────────────┐               └──────────┬───────────┘
                                │             │              │                          │
                          ┌─────▼──┐   ┌──────▼─────┐  ┌──────▼─────┐          ┌────────▼────────┐
                          │ Unity  │   │ Unreal     │  │ XR / 数字人 │          │ ROS2 / 机械臂   │
                          │ ms-MANO│   │            │  │ 手语翻译    │          │ 灵巧手 / VLA    │
                          └────────┘   └────────────┘  └────────────┘          │ RL 训练数据     │
                                                                                   └─────────────────┘
```

**Hand Token 规范**（v1 已实现待测 ✅→🟡；v2 Skeleton Layer 设计冻结 D11 🟡）：

> **v2 = Skeleton Layer（D10/D11，位于双表示层上游）**：管线细化为 `Sensor → Skeleton Layer(20-rotation canonical Hand Token v2, 派生 21 MediaPipe) → {MANO Layer, Robot Action Layer} + BVH/FBX/OpenXR/ROS 导出器`，且可被第三方手套(Hi5/mHand/Manus/Rokoko/OpenXR)在 Skeleton Layer 注入(ingest)。canonical=20 旋转关节(⊃MANO-16, =Noitom Axis-20, =OpenXR去派生)；v1(79B) 永久兼容, v2=capability-flagged TLV 变长帧。详见 `07_dual_rep_layer.md` §1b + `../BP/research_5_data_formats_interop.md`。

> **D12 生态对齐 — 开放手部运动基础设施（非竞品）**：EgoGlove 不是 Hi5/Manus/mHand 竞品；厂商手套 = **外部数据源/适配器**。通用四段管线：`Sensor Source(flex/IMU/vision/外部手套) → Hand Token v2(通用中间表示) → Canonical Skeleton Layer(20 旋转关节, FK 派生 21) → MANO / OpenXR / FreeMoCap / ROS2 / Robot(经 DexRetargeting/AnyTeleop)`。Hand Token v2 **不围绕任何厂商设计**。优先级 P0 冻结骨架+v2 · P1 adapters/exporters · P2 集成 Hi5/Manus/mHand · P3 Pro 硬件扩展。详见 `STRATEGY.md` D12。

| 字段 | 维度 | 说明 | 真实性 |
|------|------|------|--------|
| flex/joint angle | 5/hand | 指间关节 | ✅ (Lite adc) |
| IMU euler/quat | 3-4/hand | 手掌姿态 | 🟡 (驱动待) |
| 6DoF wrist pose | 6 | 腕世界位姿 | 🔬 (需外部位姿源) |
| velocity / accel | 6 | 速度/加速度 | 🔬 |
| contact state | 5/hand | 指尖接触 | 🔬 (Pro force) |
| force estimate | 5/hand | 指尖力 | 🔬 (Pro force) |

---

## 4. 通信栈

### 4.1 Lite（BLE/WiFi 为主）
- Gloves → Phone/PC: BLE GATT 或 WiFi UDP 🟡
- Phone/PC Relay → Frontend: WebSocket ✅ (V6 已有)

### 4.2 Pro（双生态，D9）

| 路径 | 协议 | 用途 | 真实性 |
|------|------|------|--------|
| Glove → Base Station | USB-C / Ethernet | 高带宽低延迟主链路 | 🟡 |
| Glove → AI 眼镜 | WiFi / BT | 消费侧 EGO 融合 | 🌌 |
| Base Station → Robot | ROS2 / Ethernet | 机器人侧遥操作 | 🟡 |
| Base Station → Vision | USB3 Vision | 工业相机集成 | 🌌 |

### 4.3 历史通信栈（V6，archive 参考）
- S3 ESP-NOW 69B → C6 relay → UART 2Mbps → P4 → USB HS CDC → PC ✅ (部分)
- **已知硬伤**：on-board C6 = ESP-Hosted，**不能** ESP-NOW 透传。生产期 C6 走 ESP-Hosted Wi-Fi/UDP；开发期走 S3→P4 直连 UART（仅设计，`WIRED_UART` 不在代码）。

---

## 5. 三级推理分工（诚实版）

| Tier | 位置 | 职责 | 真实性 |
|------|------|------|--------|
| Tier1 | MCU (S3/P4) | 传感器预处理、滤波、归一化、轻量 CNN（<3ms） | ✅ 结构在 / 🟡 模型待 |
| Tier2 | Edge Gateway / P4 / 手机 | 中等模型推理（Gated Bi-CrossAttn 等 ~30ms） | 🟡 |
| Tier3 | PC / Cloud | ST-GCN + MS-TCN + CTC、VLA、大模型 | 🟡 |

> **诚实修正**：原 V6 设计"<3ms TinyML 跑完整 Transformer+fusion" 不成立。拆为：预处理在 MCU，AI 推理在 edge gateway/移动/云。

---

## 6. 仓库结构映射

```
firmware/lite/      → Lite 固件 (ESP32-S3, PlatformIO)
firmware/pro/       → Pro 固件 (ESP32-P4, ESP-IDF)
firmware/shared/    → 共享: uart_frame, Hand Token 协议, 校准
base_station/       → P4/网关侧固件与上位机桥接
relay/              → Python FastAPI 中继 (WS/NLP/TTS/路由)
models/mano/        → MANO Layer 推理与对齐
models/robot/       → Robot Action Layer 推理与对齐
models/slr/         → 手语识别 (战略降级, D8)
models/shared/      → 跨模型骨干/工具
web/                → React3F 前端
sdk/                → PyTorch/TFLite/ROS2/Unity SDK
data/               → Open Core (open/) + Commercial (commercial/, gitignore)
```

---

## 7. 与 V6 的差异（迁移要点）

| 维度 | V6 (Beta) | V7 (本仓库) |
|------|-----------|-------------|
| 产品线 | 单一 Beta (Flex+IMU) | Lite + Pro 双线 (D6) |
| 输出 | 11-dim 特征 → 46 类手势分类 | Hand Token → 双表示层 (D3) |
| 视觉 | 无 | Pro 预留 EGO Camera 接口 (D7) |
| 通信 | ESP-NOW→C6→UART→P4 | 双生态 (D9) USB-C/WiFi/BT + ROS2/Ethernet |
| 数据 | edge_impulse 零星 CSV | Open Core + Commercial 分层 (D5) |
| 仓库 | EchoGlove-SLR-MOCAP-Beta | EgoGlove monorepo |

---

## 8. 真实性现状总表（投资人/协作者必读）

| 能力 | 状态 | 说明 |
|------|------|------|
| Flex internal ADC1 采集 | ✅ | V6 已落地，GPIO1-5, N=16 oversample, NVS cal |
| S3 ESP-NOW 通信 | ✅ | V6 已落地 |
| P4 UART-RX + USB-CDC | ✅ | V6 已落地 |
| P4 standalone mock | ✅ | V6 已验证 |
| LSM6DSV16X IMU 驱动 | 🟡 | 驱动不存在，IMU 输出全零 |
| S3→P4 有线 UART | 🟡 | `WIRED_UART` 设计但不在代码 |
| ROS2 SDK | 🟡 | 待实现 |
| Hand Token v1 协议 (79B 帧) | 🟡→✅ | 实现完成待首轮测试确认 (`firmware/shared` + `relay`) |
| Hand Token v2 Skeleton Layer (20-rotation, TLV) | 🟡 | 设计冻结 (D11); spec `docs/superpowers/specs/2026-07-27-hand-token-v2-design.md`; 代码待写 |
| 生态导出器 (MANO/OpenXR/FreeMoCap/ROS2) | 🟡 | 格式导出器待写 (D12 P1) |
| DexRetargeting/AnyTeleop 机器人手 retarget | 🔬 | 人手→灵巧手 retarget 桥, 待接 (D12 P1) |
| 外部手套物理集成 (Hi5/Manus/mHand) | 🔬 | 适配器接真实设备流 (D12 P2); mHand schema 待核实 |
| egocentric/InterHand2.6M/WholeBody 数据集兼容 | 🌌 | 具身智能数据飞轮 (D12), 长期方向 |
| MANO 双表示层 | 🟡 | `to_mano`/`to_robot_action` 结构视图; 真实 θ/β 回归与 retarget 待 `models/` |
| MediaPipe+glove 融合 | 🟡 | 待实现 |
| 连续手语 benchmark | 🔬 | 需建，延迟/WER/连续准确率 |
| 柔性 eSkin / Force | 🔬 | Pro 升级方向 |
| EGO Camera 融合 | 🌌 | 第一代不进，预留接口 |
| Human Hand Foundation Model | 🌌 | 2028+ 长期 |

---

## 相关文档

- `STRATEGY.md` — 战略冻结（D1–D12）
- `01_architecture_diagrams.md` — 详细架构图（V7 版）
- `02_BOM_table.md` — Lite/Pro BOM
- `04_SOP-SPEC-PLAN_V7.md` — 主规格书
- `07_dual_rep_layer.md` — 双表示层 + Hand Token v1/v2 (Skeleton Layer)
- `../BP/research_5_data_formats_interop.md` — 手部数据格式互操作研究底稿
- `../BP/EchoGlove_BP_V2.1.md` — 产业级 BP
