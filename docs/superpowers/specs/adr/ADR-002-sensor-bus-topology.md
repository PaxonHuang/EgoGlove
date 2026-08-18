# ADR-002: Sensor Bus Topology — 2×TCA9548A + I2C as Demo1 Baseline

> 日期：2026-08-18
> 状态：Proposed / Baseline（**NOT HARDWARE VERIFIED**）
> 关联 spec：`docs/superpowers/specs/2026-08-17-egomotion-architecture-upgrade-design.md` §6
> 前置：ADR-001（仓库拓扑冻结）

## Context

Demo1 目标硬件：ESP32-S3 + **11 × LSM6DSV16X** + **3 × HKVT-M3A**，目标 ODR ≥ 200 Hz，统一 acquisition timeline，sync_error 工程目标 <1 ms。在进入 driver 实现前需快速回答：11 颗 IMU 最终应采用哪种 physical bus topology？

候选：

- **A — 2 × TCA9548A + I2C**（现有 baseline）：
  ```
  ESP32-S3
  ├── I2C bus 0 → TCA9548A → 8 × LSM6DSV16X
  └── I2C bus 1 → TCA9548A → 3 × LSM6DSV16X + 3 × HKVT-M3A
  ```
- **B — 紧凑 I2C**：利用 LSM6DSV16X 两个可设 I2C 地址（SA0 → 0x6A/0x6B），减少 mux 数量。
- **C — 11 × LSM6DSV16X 走 SPI**（共享 SCLK/MOSI/MISO + 独立 CS），HKVT 走 I2C。

## Engineering Feasibility（理论值，非实测）

| 维度 | A: 2×TCA9548A+I2C | B: 紧凑 I2C | C: 11×SPI+HKVT I2C |
|---|---|---|---|
| 单帧负载 @200Hz | 11×12B(AXL+G)≈132B/帧 | 同 A | 11×14B≈154B/帧 |
| 总线占用率 | I2C@400k ≈26% + mux 开销 ~10% | ≈26%，mux 开销低 | SPI@40MHz <2%，极宽裕 |
| GPIO 成本 | 2×I2C(4) + 2×mux RST(2) = 6 | 2×I2C(4) + 1 mux RST = 5 | 3(SPI)+11×CS = 14 |
| Mux 切换开销 | ~150μs/通道 | 较少 | 无 |
| 同步确定性 | 中（串行轮询，逐通道时延累积） | 中 | 高（可并发/连续读） |
| 错误隔离 | 好（mux 可关单通道，TCA9548A RESET 可恢复挂死总线） | 中 | 好（CS 独立隔离） |
| PCB routing 复杂度 | 低-中 | 中 | 高（11 CS 走线） |
| 未来扩展性 | 一般 | 差（地址耗尽） | 好 |

LSM6DSV16X 原生支持 SPI，ESP32-S3 有通用 SPI + DMA，故 C 不能默认否决。但无真实 PCB pinmap，无法确认 CS/INT 资源是否够用。

## Decision

**Demo1 baseline = A（2 × TCA9548A + I2C）**。理由：

1. 现有文档/器件已按 A 准备；I2C@400k 在 11×200Hz 下占用率 ~26-36%，尚在可接受范围。
2. TCA9548A 的 RESET（active-low，≥6 ns pulse）可在下游 I2C 挂死时恢复状态机，error isolation 是其核心价值，契合 multi-sensor acquisition 的容错需求（见 `datasheet/tca9548a.md` §7.4.1）。
3. A 的 mux 切换 + 串行轮询虽引入时延累积，但 Demo1 用 **MCU free-running timestamp** 统一 acquisition timeline，每颗 sensor 独立 seq，sync_error 留给 Phase 1C 实测（工程目标 <1ms，非已验证事实）。

**C（SPI）作为 future hardware revision candidate**，不阻塞当前开发：理论吞吐/确定性更优，但 11×CS GPIO 走线对当前 PCB 风险高，且无 pinmap 无法定 pin。

**B 不推荐**：双地址最多省 1 颗 mux，扩展性差，得不偿失。

## Constraints & NOT-VERIFIED Markers

- ❗ **NOT HARDWARE VERIFIED**：仓库内无 PCB pinmap 文件，无法确认现有硬件是否已按 A 出板。
- 若用户提供真实 PCB pinmap 且已按 A 出板 → 锁定 A。
- 若未出板 → 仍以 A 为默认实现目标，C 留作记录。
- HKVT-M3A 无 documented sensor-side timestamp / DRDY pin → Demo1 用 MCU clock 作 acquisition timestamp（ADR 与 spec §3 一致）。
- TCA9548A 默认地址 0x70（A2A1A0=000），3 颗 mux 在同总线需设不同地址——当前方案 2 颗 mux 分挂两条 I2C bus，无地址冲突。

## Scope Boundary（本轮不动）

- 不修改 V8 / Hand Token v2 / canonical-20 / wire contract。
- 不修改仓库拓扑（ADR-001）。
- 不大规模重构文档。
- 不在本轮迁移 `firmware/lite/`（Arduino）到 ESP-IDF。
