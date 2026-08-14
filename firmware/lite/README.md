# EchoGlove Lite (ESP32-S3) — M2: LSM6DSV16X + Madgwick

✅ 已实现（M2, 2026-08-11）：LSM6DSV16X 驱动（120Hz、±4g/±2000dps）、Host Madgwick
6-axis AHRS、LiteSensorManager（flex+IMU → Hand Token v1 `quat[4]`）、串口遥测。
🟡 工程可实现：79B 线上序列化（M3）、NVS flex 校准（M4）、46 类 SLR（M4）。

## 构建 / 单测

```bash
pio run -d firmware/lite                 # 固件编译门
cd firmware/lite/test && make run        # host 单测 (驱动/滤波器/管理器)
```

## 烧录与遥测

```bash
pio run -d firmware/lite -t upload -t monitor   # 115200; USB CDC
```

启动 2s 后每 100ms 一行：
`t=<us> flex=f0..f4 euler=roll,pitch,yaw quat=w,x,y,z`

## 板上验证清单（M2 验收，需硬件）

| # | 项 | 通过标准 | 步骤 |
|---|----|---------|------|
| 1 | I²C 枚举 | 串口首行 `LITE SM INIT OK`（无 FAILED） | 上电观察日志；WHO_AM_I=0x70 校验在驱动内 |
| 2 | 静止 60s 漂移 | euler **roll/pitch** 全程 <3°（yaw 不设限，见下） | 平放静止 60s，记录 euler 列极差 |
| 3 | 翻转 90° 响应 | roll 从 0→90° 跳变到稳定 <200ms | 沿 x 轴快速翻转 90°，从遥测时间戳差分 |
| 4 | flex 通路 | 弯折各指 → 对应 flex[i] 0..1 显著变化 | 逐指弯折观察 CSV |
| 5 | 手别正确 | hand 字段与物理手套一致（当前硬编码 RIGHT） | 观察 `quat` 与 flex 行为一致性 |

## 已知限制（设计内）

- **yaw 不可观测**：加速度计不提供绕重力轴信息；静止时 yaw 保持初始值但有界漂移（陀螺积分），需磁力计/视觉（Pro/roadmap）。
- flex 为 raw 归一化（未 NVS 校准），范围校准归 M4。
- 左右手硬编码 `RIGHT`；设备配置化归 M3。
