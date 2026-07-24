# EchoGlove V7.0 — System Architecture Diagrams

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: Design target
> **See also**: `STRATEGY.md` (D1–D9), `ARCHITECTURE.md` (总表)

真实性与 V6 一致：仅 flex-ADC / S3-ESP-NOW / P4-UART+USBCDC / P4-mock 为 ✅，余为 🟡/🔬/🌌。图示为目标架构。

---

## 1. System Architecture Overview — 双产品线

```
+============================================================================+
|                   EchoGlove V7.0 System Architecture                       |
|                                                                            |
|  Lite Line (消费/教育/XR/手语)        Pro Line (具身智能数据入口)            |
|                                                                            |
|  +-----------------------+            +----------------------------+       |
|  | EchoGlove Lite (单手) |            | EchoGlove Pro (单手)        |       |
|  | ESP32-S3 N16R8        |            | ESP32-P4 400MHz RV32        |       |
|  | 5× Flex (internal ADC)|  ✅        | 5× eSkin/Force (升级)   🔬  |       |
|  | LSM6DSV16X IMU    🟡  |            | 工业级 IMU            🟡   |       |
|  | BLE / WiFi         🟡 |            | 力接口                 🔬   |       |
|  | Tier1 预处理       ✅ |            | EGO Camera 接口 (预留) 🌌  |       |
|  | BOM <¥500             |            | 双生态通信 (D9)        🟡  |       |
|  +-----------+-----------+            +-------------+--------------+      |
|              |                                      |                     |
|        BLE/WiFi 🟡                  USB-C/Ethernet 🟡 | WiFi/BT 🌌          |
|              v                                      v                     |
|  +-----------------------+            +------------------------------+     |
|  | Phone/PC Relay        |            | Base Station / Edge Gateway  |     |
|  | Tier2/3 推理          |            | Tier2 推理 + 双表示层生成    |     |
|  +-----------+-----------+            +---------------+--------------+     |
|              |                                      |                     |
|              v                  +--------------------+                     |
|  +-----------------------+      |  Hand Token 分叉  |                     |
|  | Frontend (React3F)    |      |  MANO | Robot Act |                     |
|  +-----------------------+      +--------+-----+----+                     |
|                                          |     |                          |
|                            +-------------+     +--------------+           |
|                            v                    v              v          |
|                       Unity/Unreal         ROS2/机械臂     VLA/RL 数据      |
|                       XR/数字人/手语       灵巧手                        |
+============================================================================+
```

---

## 2. Dual-Representation Data Flow (核心, D3)

```
Sensor Layer         Preprocess (MCU)       Hand Token Generator       Representation Fork
+-----------+        +-----------+          +-----------------+        +---------------------+
| Flex      |  raw   | Filter    | feature  | Joint+Pose+Vel  |  token |  MANO Layer         |
| IMU       |------->| Normalize |--------->| +Contact+Force  |------->|  → mesh/verts       |--> Unity/Unreal/XR
| Force(Pro)|        | <3ms      |  vec     | (规范待定 🟡)   |        +---------------------+
+-----------+        +-----------+          +--------+--------+        |  Robot Action Layer |
                                                      |                 |  → joint+6DoF+vel  |--> ROS2/机械臂/VLA
                                                      +----------------->|  +contact+force    |
                                                                        +---------------------+
```

Hand Token 字段规范见 `07_dual_rep_layer.md`。

---

## 3. Communication Stack (双生态, D9)

### 3.1 Lite
```
Gloves ──BLE/WiFi🟡──> Phone/PC Relay ──WS:8765✅──> Frontend (React3F)
```

### 3.2 Pro
```
                        +-- USB-C/Ethernet 🟡 --> Base Station
Glove (P4) ──双生态──---+
                        +-- WiFi/BT 🌌 ----------> AI 眼镜 (EGO 融合)

Base Station ──ROS2/Ethernet 🟡--> 机械臂/灵巧手
Base Station ──USB3 Vision 🌌----> 工业相机
```

### 3.3 历史栈 (V6, archive 参考)
```
S3 ──ESP-NOW 69B✅──> C6 relay ──UART 2Mbps✅──> P4 ──USB HS CDC✅──> PC Relay
⚠️ on-board C6 = ESP-Hosted, 不能 ESP-NOW 透传 (生产期走 Wi-Fi/UDP)
```

---

## 4. Three-Tier Inference (诚实分工)

```
Tier1 (MCU <3ms)        Tier2 (Edge/P4/手机 ~30ms)     Tier3 (PC/Cloud)
+-----------------+     +-----------------------+      +-------------------+
| 传感器预处理    |     | 中等模型推理          |      | ST-GCN+MS-TCN+CTC |
| 滤波/归一化     |---->| Gated Bi-CrossAttn    |----->| VLA / 大模型      |
| 轻量 CNN 🟡     |     | 🟡                    |      | 🟡                |
+-----------------+     +-----------------------+      +-------------------+
⚠️ <3ms 跑不了完整 Transformer+fusion, 预处理在 MCU, AI 推理在 edge/cloud
```

---

## 5. Repository Layout

```
firmware/{lite,pro,shared}/   base_station/   relay/
models/{mano,robot,slr,shared}/   web/   sdk/   data/{open,commercial}/
docs/{V7,BP}/   templates/   scripts/
```

详见 `ARCHITECTURE.md` §6。
