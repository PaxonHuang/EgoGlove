# EchoGlove V7.0 — 主规格书 (SOP-SPEC-PLAN)

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: 设计目标 + 实现路线
> **参见**: `STRATEGY.md`, `ARCHITECTURE.md`; 商业计划见独立仓 `PaxonHuang/BP`（private，唯一 BP 资产仓）

本文件为 V7 主规格书，涵盖系统/硬件/固件/通信/relay/前端/数据/路线图。所有能力带 ✅/🟡/🔬/🌌 四级真实性标注。

---

## 1. 系统总览

EchoGlove V7 = 面向具身智能的双产品线手部智能层基础设施：
- **Lite** (ESP32-S3, <¥500) → 消费/教育/XR/手语
- **Pro** (ESP32-P4, 企业级) → 具身智能遥操作/数据采集/VLA 训练数据

核心 = **双表示层** (D3): Sensor → Hand Token → MANO Layer + Robot Action Layer。

## 2. 硬件规格

### 2.1 Lite
- MCU: ESP32-S3 N16R8 (8MB Flash + 8MB PSRAM)
- IMU: LSM6DSV16X @0x6A, 6-axis, SFLP 🟡
- Flex: 5× 2.2" 内部 ADC1, N=16, NVS cal ✅
- 通信: BLE/WiFi 🟡 + USB-CDC ✅
- BOM: <¥500/手

### 2.2 Pro
- MCU: ESP32-P4 (400MHz RV32, 32MB PSRAM) 🟡
- IMU: 工业级升级款 🟡
- 传感: 5× eSkin + 5× Force 🔬
- 视觉接口: EGO Camera + Depth (预留 🌌, D7)
- 通信: 双生态 (D9) USB-C/Ethernet 🟡 + WiFi/BT 🌌 + USB3 Vision 🌌
- BOM: ~¥450/手 🔬

## 3. 固件规格

### 3.1 共享 (`firmware/shared/`)
- `uart_frame.h`: CRC-16/MODBUS 帧 ✅ (V6 已有)
- `hand_token.h`: Hand Token 协议 🟡
- `calibration.*`: NVS 校准 ✅ (Flex 部分)

### 3.2 Lite (`firmware/lite/`, PlatformIO)
- FreeRTOS: Task_SensorRead (100Hz, core1) / Task_Inference (30Hz, core0) / Task_Comms (100Hz, core0) ✅ 结构
- IMU 驱动 🟡 (待实现 LSM6DSV16X)
- BLE/WiFi 🟡

### 3.3 Pro (`firmware/pro/`, ESP-IDF)
- 双生态协议栈 🟡
- eSkin/Force 驱动 🔬
- ROS2 bridge 🟡

### 3.4 Base Station (`base_station/`, ESP-IDF)
- P4 UART-RX + USB-CDC ✅ (V6 已有)
- P4 standalone mock ✅
- Tier2 推理 🟡

## 4. 通信规格

详见 `01_architecture_diagrams.md` §3。要点：
- Lite: BLE/WiFi → Phone/PC → WS:8765 → Frontend
- Pro: USB-C/Ethernet → Base Station → ROS2/Ethernet → 机器人；USB3 Vision → 工业相机
- 历史栈 (V6): ESP-NOW→C6→UART→P4 ⚠️ C6=ESP-Hosted 不能 ESP-NOW

## 5. Relay (`relay/`, Python FastAPI)
- WS:8765 服务 ✅ (V6 已有)
- USB CDC 输入 ✅
- Model hot-switch (YAML) ✅ 结构
- NLP + TTS ✅
- 双表示层生成 🟡 (待实现 Hand Token 分叉)
- ROS2 bridge 🟡 (Pro)

## 6. 前端 (`web/`, React3F)
- WebSocket 自动重连 ✅ (V6 已有)
- 21-keypoint 3D hand skeleton ✅
- 手语教学页 + 仪表盘 ✅ (V6 已有)
- MANO mesh 渲染 🟡
- 机器人侧 Robot Action 可视化 🟡

## 7. 数据 (`data/`)
- `data/open/`: Open Core 基础数据 (传感器原始 + MANO 基础动作) 🟡 (当前仅零星 CSV)
- `data/commercial/`: 商业高级数据 (gitignore, 不入库) 🌌
- 连续手语 benchmark 数据集 🔬 (待建)

## 8. SDK (`sdk/`)
- Python (PyTorch) 🟡
- TFLite 🟡
- ROS2 pkg 🟡 (Pro)
- Unity ms-MANO 🟡

## 9. 研发路线图 (4 级真实性)

| 阶段 | 时间 | 内容 | 真实性 |
|------|------|------|--------|
| V7-α | 2026 Q3 | Lite LSM6DSV16X 驱动 + S3→P4 有线 UART + Hand Token 规范定稿 | 🟡→✅ |
| V7-β | 2026 Q4 | 双表示层 SDK (MANO+Robot) + MediaPipe+glove 融合 + 连续手语 benchmark | 🟡/🔬 |
| V7-RC | 2027 H1 | Pro 原型 (eSkin+Force) + ROS2 bridge + 首批行业数据集 | 🔬→🟡 |
| V7-1.0 | 2027 H2 | Lite 量产 + Pro 小批量 + 生态合作 (机器人厂商/数据集联调) | 🌌→🟡 |
| 长期 | 2028+ | Human Hand Foundation Model + AI 眼镜 EGO 融合 | 🌌 |

## 10. 风险

| 风险 | 等级 | 应对 |
|------|------|------|
| Flex/eSkin 量产一致性 | 高 | 来料筛选 + NVS 校准 + 供应链合作 |
| P4 供货 | 中 | 二供 STM32H7 |
| 双表示层标准被替代 | 中 | 速度 + 生态开放 (兼容 MANO/MediaPipe) |
| 连续手语 benchmark 未建 | 中 | V7-β 优先建 |
| UWB 冗余 | 低 | Pro 可选, Lite 不做 (D6/D7) |

## 11. 兼容矩阵

| 目标 | 协议/格式 | 真实性 |
|------|-----------|--------|
| Unity | ms-MANO | 🟡 |
| Unreal | MANO | 🟡 |
| ROS2 | joint+6DoF+force | 🟡 |
| PyTorch | Hand Token tensor | 🟡 |
| TFLite | Tier1/2 模型 | 🟡 |
| MediaPipe | 融合 hand landmark | 🟡 |
| VLA | Robot Action 训练数据 | 🔬 |
