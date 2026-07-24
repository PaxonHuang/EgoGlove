# EchoGlove V7.0 — 接线图

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: 设计目标
> **真实性**: Lite 接线基于 V6 已验证；Pro 接线为设计 🟡/🔬

---

## 1. EchoGlove Lite 接线 (ESP32-S3)

### 1.1 IMU: LSM6DSV16X (breakout, I²C) 🟡

| Breakout Pin | ESP32-S3 Pin | Notes |
|--------------|--------------|-------|
| VCC | 3.3V | **NOT 5V** (1.71–3.6V) |
| GND | GND | |
| ADO/SA0 | GND | LOW=0x6A (HIGH=0x6B) |
| SDA | GPIO8 | 4.7kΩ pull-up |
| SCL | GPIO9 | 4.7kΩ pull-up |
| CS | **3.3V** | **mandatory HIGH for I²C** (LOW→SPI) |
| INT1 | GPIO10 (opt) | NC if polling |
| SDX/SCX | **NC** | aux bus, 勿接 (常见错误) |

### 1.2 Flex: 5× 内部 ADC1 ✅

| Flex | ADC1 通道 | GPIO |
|------|-----------|------|
| 拇指 | ADC1_CH0 | GPIO1 |
| 食指 | ADC1_CH1 | GPIO2 |
| 中指 | ADC1_CH2 | GPIO3 |
| 无名 | ADC1_CH3 | GPIO4 |
| 小指 | ADC1_CH4 | GPIO5 |

分压: Flex + 47kΩ → 3.3V，N=16 oversample，NVS 校准。

### 1.3 通信
- BLE/WiFi: 走 ESP32-S3 内置天线 🟡
- USB-CDC: GPIO19/20 (D-/D+) 用于固件烧录+调试 ✅

---

## 2. EchoGlove Pro 接线 (ESP32-P4) 🟡/🔬

### 2.1 传感器
| 传感器 | 接口 | 引脚 (待定) | 真实性 |
|--------|------|-------------|--------|
| eSkin ×5 | ADC1 (内部) | GPIO1-5 | 🔬 |
| Force ×5 | ADC2 或外置 ADC | 待定 | 🔬 |
| 工业级 IMU | I²C/SPI | 待定 | 🟡 |

### 2.2 双生态通信 (D9)
| 接口 | 协议 | 用途 | 真实性 |
|------|------|------|--------|
| USB-C | USB2.0 | 消费侧主链路 | 🟡 |
| Ethernet | RMII + PHY | 机器人侧 ROS2 | 🟡 |
| WiFi/BT | 外置模组 | AI 眼镜融合 | 🌌 |
| USB3 Vision | USB3 | 工业相机 | 🌌 |

### 2.3 EGO Camera 接口 (预留, D7) 🌌
- MIPI-CSI 或 USB3，物理连接器预留，第一代不进 CV

---

## 3. Base Station 接线 (P4 EV Board, 历史 V6 参考)

| 信号 | P4 Pin | 对端 |
|------|--------|------|
| UART RX | GPIO38 | S3/C6 TX |
| UART TX | GPIO37 | S3/C6 RX |
| USB HS CDC | GPIO19/20 | PC |
| C6 SDIO | (板载) | ESP32-C6 (ESP-Hosted) |

⚠️ on-board C6 = ESP-Hosted，**不能** ESP-NOW 透传。详见 V6 `03_wiring_diagram.md` (archive)。

---

## 4. 历史接线 (V6, archive 参考)

V6 完整接线（LSM6DSV16X LGA-14L bare pad map、BNO085→LSM6DSV16X 迁移、C6↔P4 UART）保留在 `EchoGlove-SLR-MOCAP-Beta/docs/V6/03_wiring_diagram.md`，本文件为 V7 重写，不重复。

## 5. 注意事项

- **CS 拉高**: LSM6DSV16X breakout 的 CS 必须接 3.3V，否则无 I²C 响应（V6 验证过的坑）
- **SDX/SCX 勿接**: aux sensor-hub bus，常见接线错误
- **ADC1 vs ADC2**: WiFi 启用时 ADC2 不可用，Flex 必须用 ADC1
- **Pro 双生态走线**: USB3/Ethernet 差分对需等长，PCB 4层板起
