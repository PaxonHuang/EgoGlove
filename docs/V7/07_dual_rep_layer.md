# EchoGlove V7.0 — 双表示层详解 (D3 核心壁垒)

> **Version**: V7.0
> **Date**: 2026-07-24
> **Status**: 规范草案 (🟡 待定稿实现)
> **参见**: `STRATEGY.md` D3, `ARCHITECTURE.md` §2/§3

双表示层是 EchoGlove 的核心壁垒 (D3): 同一硬件传感器流, 统一为 Hand Token, 再分叉为 MANO Layer (数字人侧) 与 Robot Action Layer (机器人侧), 互不污染。本文件定义 Hand Token 规范与两层映射。

---

## 1. Hand Token 规范

Hand Token = 跨产品线 (Lite/Pro) 统一的归一化手部状态向量。

### 1.1 字段表

| 字段 | 维度 | Lite | Pro | 说明 |
|------|------|------|-----|------|
| flex / joint angle | 5/hand | ✅ (ADC) | ✅ (eSkin) | 指间关节角 (归一化 0-1) |
| IMU euler / quat | 3-4/hand | 🟡 | 🟡 | 手掌姿态 (SFLP fusion) |
| 6DoF wrist pose | 6 | 🔬 | 🔬 | 腕世界位姿 (需外部位姿源: 视觉/UWB/磁跟踪) |
| velocity | 3 | 🔬 | 🔬 | 速度 (差分或 IMU 积分) |
| acceleration | 3 | 🔬 | 🔬 | 加速度 (IMU) |
| contact state | 5/hand | — (无) | 🔬 (Force) | 指尖接触布尔 |
| force estimate | 5/hand | — (填 0) | 🔬 (Force) | 指尖力估计 (N) |
| timestamp | 1 | ✅ | ✅ | 单调时戳, 用于时间同步 |
| device_id | 1 | ✅ | ✅ | Lite/Pro + L/R + 序号 |

**Lite 兼容**: force/contact 填 0, Pro 有效字段填实测。Hand Token 协议版本号区分。

### 1.2 二进制帧 (草案)

```
[0xGG magic(2)] [version(1)] [device_id(1)] [timestamp_us(4)]
[flex(5×float16)] [imu_quat(4×float16)] [wrist_6dof(6×float32)]
[vel(3×float16)] [acc(3×float16)] [contact(5×uint8)] [force(5×float16)]
[CRC16(2)]
```

实现见 `firmware/shared/hand_token.h` (🟡 待) + `relay/` 解析。

---

## 2. MANO Layer 映射

**目标**: Unity / Unreal / XR / 数字人 / 手语

- 输入: Hand Token (flex + IMU)
- 输出: MANO 参数 (pose params + shape params) → 手部 mesh + vertices
- 兼容: ms-MANO, MediaPipe hand landmark (21-keypoint)
- SDK: `sdk/python/mano.py` + `sdk/unity/` (🟡)

### 映射逻辑 (🟡 待实现)
1. flex 5-dim → MANO 手指 pose params (拇指/食指/中指/无名/小指弯曲)
2. IMU quat → MANO 全局腕旋转
3. shape params: 默认中性手, 可校准个人手型
4. 输出 MANO θ + β → mesh 渲染

---

## 3. Robot Action Layer 映射

**目标**: ROS2 / 机械臂 / 灵巧手 / VLA / RL 训练数据

- 输入: Hand Token (全字段)
- 输出: `{joint, wrist_6dof, vel, acc, contact, force}` 结构化动作向量
- 兼容: ROS2 sensor_msgs/JointState + geometry_msgs/PoseStamped, OpenVLA/π0 训练格式
- SDK: `sdk/python/robot_action.py` + `sdk/ros2/` (🟡)

### 映射逻辑 (🟡 待实现)
1. flex → joint angle (rad, 针对目标灵巧手自由度映射)
2. wrist_6dof → PoseStamped (世界系或基座系)
3. vel/acc → 附加通道 (动量/接触检测)
4. contact + force → 力控密集任务 (π0 已证数据规模决定 VLA 上限, 力字段稀缺 = 壁垒)

---

## 4. Vision + Proprioception 融合 (D1)

```
Vision (World State) ──┐
                       ├──> Human Intent (融合层)
Glove (Hand State) ────┘
```

- Vision (MediaPipe/EGO Camera): 给世界状态 + 手部全局位姿 (补 6DoF wrist)
- Glove: 给手部本体状态 (flex + 力, 视觉遮挡时唯一源)
- 融合: 视觉给位姿, 手套给关节/力, 互补

第一代硬件不进 CV (D7), 但 SDK 预留 `fuse(vision, glove)` 接口 (🟡)。

---

## 5. 双表示层为何是壁垒

1. **不被框死**: XR 取 MANO, 机器人取 Robot Action, 同一硬件两类客户
2. **标准树立**: Hand Token 若成事实标准, 后续者需兼容 (类似 MANO 之于数字人)
3. **数据飞轮**: 硬件 → 采集 → 训练 → 模型 → SDK → 应用 → 用户 → 数据, 双表示层使数据可跨场景复用
4. **力字段稀缺**: OpenX-Embodiment/DROID 主流格式无力/触觉, Pro 的 force 字段是差异化数据资产

---

## 6. SDK 接口草案

```python
# sdk/python/hand_token_sdk.py (🟡)
class HandTokenSDK:
    def parse(self, frame: bytes) -> HandToken: ...
    def to_mano(self, t: HandToken) -> ManoParams: ...
    def to_robot_action(self, t: HandToken) -> RobotAction: ...
    def to_ros2_msgs(self, t: HandToken) -> tuple: ...
    def fuse(self, vision: VisionState, glove: HandToken) -> HumanIntent: ...
```

```cpp
// firmware/shared/hand_token.h (🟡)
typedef struct {
    float flex[5];
    float quat[4];
    float wrist_6dof[6];
    float vel[3], acc[3];
    uint8_t contact[5];
    float force[5];
    uint32_t timestamp_us;
    uint8_t device_id;
} hand_token_t;
size_t hand_token_serialize(const hand_token_t* t, uint8_t* buf);
bool hand_token_parse(const uint8_t* buf, size_t n, hand_token_t* out);
uint16_t hand_token_crc16(const uint8_t* buf, size_t n);
```

---

## 7. 真实性

- Hand Token 规范: 🟡 (草案, 待定稿 + 实现)
- MANO Layer: 🟡 (映射逻辑待实现, 兼容 ms-MANO)
- Robot Action Layer: 🟡 (映射逻辑待实现, ROS2 msg 待)
- Vision+Glove 融合: 🟡 (接口预留, 第一代无 CV)
- 力字段 (Pro): 🔬 (Force 硬件待)
- 6DoF wrist 外部位姿: 🔬 (需视觉/UWB/磁跟踪之一)

## 8. 相关

- `STRATEGY.md` D3 (数据标准), D1 (感知主线)
- `ARCHITECTURE.md` §2/§3 (数据流图)
- `../BP/EchoGlove_BP_V2.1.md` 第三章 (产品体系) / 第四章 (壁垒)
