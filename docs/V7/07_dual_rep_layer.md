# EchoGlove V7.0 — 双表示层详解 (D3 核心壁垒)

> **Version**: V7.0
> **Date**: 2026-07-25
> **Status**: 协议层已实现待测 (host 单测 / pytest 金标) · 语义映射 🟡
> **参见**: `STRATEGY.md` D3, `ARCHITECTURE.md` §2/§3

双表示层是 EchoGlove 的核心壁垒 (D3): 同一硬件传感器流, 统一为 Hand Token, 再分叉为 MANO Layer (数字人侧) 与 Robot Action Layer (机器人侧), 互不污染。本文件定义 Hand Token 规范与两层映射。

---

## 1. Hand Token 规范

Hand Token = 跨产品线 (Lite/Pro) 统一的归一化手部状态向量。

### 1.1 字段表 (数据可用性视角)

下表标注各字段的**数据可用性** (传感器能否产出真实值), 与 §1.2 的**传输格式** (帧能否承载该字段) 是两个维度: 传输层承载全部字段, 数据层按硬件真实性分级填充。

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

**Lite 兼容**: force/contact 填 0, Pro 有效字段填实测。device_id bit7 区分产品线。

### 1.2 二进制帧 (Hand Token v1 · 定长 79 字节 · 小端)

已**冻结并实现**于 `firmware/shared/hand_token.{h,c}` (可移植 C11) 与 `relay/hand_token.py` (Python 镜像), 二者逐字节兼容。帧**自包含 · 传输无关**, 不依赖外层 uart_frame, 可直接经 USB-CDC / WS / UDP / BLE 承载。

| 偏移 | 长度 | 字段 | 类型 | 说明 |
|------|------|------|------|------|
| 0  | 2  | magic         | ASCII `"HT"` (0x48 0x54) | 帧同步 |
| 2  | 1  | version       | uint8 = `0x01` | 协议版本 |
| 3  | 1  | device_id     | uint8 位域 | bit7=product(0=Lite,1=Pro), bit6=hand(0=L,1=R), bits5..0=serial(0..63) |
| 4  | 4  | timestamp_us  | uint32 LE | 微秒时戳 |
| 8  | 10 | flex[5]       | float16 LE ×5 | 归一化关节弯曲 (拇→小) |
| 18 | 8  | quat[4]       | float16 LE ×4 | 腕四元数 wxyz |
| 26 | 24 | wrist_6dof[6] | float32 LE ×6 | 腕 6DoF 位姿 (全精度) |
| 50 | 6  | vel[3]        | float16 LE ×3 | 线速度 |
| 56 | 6  | acc[3]        | float16 LE ×3 | 加速度 |
| 62 | 5  | contact[5]    | uint8 ×5 | 指尖接触 0/1 |
| 67 | 10 | force[5]      | float16 LE ×5 | 指尖力 (Pro 密集力控字段) |
| 77 | 2  | crc16         | uint16 LE | CRC-16/MODBUS, 覆盖 bytes[0,77) |
| **=79** | | **(总长)** | | |

**编码规则**:
- 所有多字节字段 **little-endian**。
- `float16` = IEEE754 half, **round-to-nearest-even** (与 Python `struct.pack('<e')` 逐字节一致)。
- `float32` = IEEE754 single (`struct '<f'`)。
- `wrist_6dof` 用 float32 保精度 (位姿对量化敏感); 其余浮点字段用 float16 压缩带宽。
- CRC-16/MODBUS: 多项式 `0xA001`, 初值 `0xFFFF`, 结果小端存储, 覆盖帧首到 CRC 前 (bytes 0..76)。
- **跨语言金标**: canonical 79B 参考帧由 host C 单测 (`firmware/shared/test/`) 与 `relay/test_hand_token.py` 共用同一 `GOLDEN_HEX`, 双向断言逐字节一致。

实现: `firmware/shared/hand_token.{h,c}` (序列化/解析/CRC/f16) + `relay/hand_token.py` (Python 镜像 + 双表示层分叉)。

---

## 2. MANO Layer 映射

**目标**: Unity / Unreal / XR / 数字人 / 手语

- 输入: Hand Token (flex + IMU quat)
- 输出: MANO 参数 (pose params θ + shape params β) → 手部 mesh + vertices
- 兼容: ms-MANO, MediaPipe hand landmark (21-keypoint)
- 参考实现: `relay/hand_token.py` `to_mano()` (🟡 结构视图) → SDK: `sdk/python/mano.py` + `sdk/unity/` (🟡)

### 映射逻辑 (🟡 待实现)
1. flex 5-dim → MANO 手指 pose params (拇指/食指/中指/无名/小指弯曲)
2. IMU quat → MANO 全局腕旋转
3. shape params: 默认中性手, 可校准个人手型
4. 输出 MANO θ + β → mesh 渲染

> 现状: `to_mano()` 返回结构化视图 (hand/flex/quat/wrist_pose), **不做真实 θ/β 回归**; 回归模型待 `models/mano/`。

---

## 3. Robot Action Layer 映射

**目标**: ROS2 / 机械臂 / 灵巧手 / VLA / RL 训练数据

- 输入: Hand Token (全字段)
- 输出: `{joint, wrist_6dof, vel, acc, contact, force}` 结构化动作向量
- 兼容: ROS2 sensor_msgs/JointState + geometry_msgs/PoseStamped, OpenVLA/π0 训练格式
- 参考实现: `relay/hand_token.py` `to_robot_action()` (🟡 结构视图) → SDK: `sdk/python/robot_action.py` + `sdk/ros2/` (🟡)

### 映射逻辑 (🟡 待实现)
1. flex → joint angle (rad, 针对目标灵巧手自由度 retarget)
2. wrist_6dof → PoseStamped (世界系或基座系)
3. vel/acc → 附加通道 (动量/接触检测)
4. contact + force → 力控密集任务 (π0 已证数据规模决定 VLA 上限, 力字段稀缺 = 壁垒)

> 现状: `to_robot_action()` 返回结构化动作向量, **不做真实 joint retarget**; 重定向到目标灵巧手自由度待 `models/robot/`。

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

## 6. SDK 接口

### 6.1 已实现: C 协议 + Python 镜像

```c
// firmware/shared/hand_token.h (已实现, 可移植 C11)
typedef struct {
    uint8_t  product;        // 0=Lite, 1=Pro
    uint8_t  hand;           // 0=Left, 1=Right
    uint8_t  serial;         // 0..63
    uint32_t timestamp_us;
    float    flex[5];
    float    quat[4];        // wxyz
    float    wrist_6dof[6];
    float    vel[3], acc[3];
    uint8_t  contact[5];
    float    force[5];
} hand_token_t;

size_t   hand_token_serialize(const hand_token_t* t, uint8_t* buf, size_t buflen); // 成功=79, 缓冲不足=0
bool     hand_token_parse(const uint8_t* buf, size_t n, hand_token_t* out);        // 校验 magic/version/len/CRC
uint16_t hand_token_crc16(const uint8_t* buf, size_t n);                           // CRC-16/MODBUS
uint8_t  hand_token_make_device_id(uint8_t product, uint8_t hand, uint8_t serial);
void     hand_token_split_device_id(uint8_t id, uint8_t* product, uint8_t* hand, uint8_t* serial);
uint16_t hand_token_f32_to_f16(float f);
float    hand_token_f16_to_f32(uint16_t h);
```

```python
# relay/hand_token.py (已实现, 与 C 逐字节兼容)
serialize(t: HandToken) -> bytes            # 79B canonical 帧
parse(frame: bytes) -> HandToken            # 非法 (len/magic/version/CRC) 抛 ValueError
to_mano(t: HandToken) -> dict               # 🟡 MANO Layer 结构视图
to_robot_action(t: HandToken) -> dict       # 🟡 Robot Action Layer 结构视图
```

### 6.2 待实现: 高层 SDK 封装 (🟡)

```python
# sdk/python/hand_token_sdk.py (🟡 待实现)
class HandTokenSDK:
    def parse(self, frame: bytes) -> HandToken: ...       # 复用 relay/hand_token.py
    def to_mano(self, t: HandToken) -> ManoParams: ...    # 真实 θ/β 回归 (models/mano)
    def to_robot_action(self, t: HandToken) -> RobotAction: ...  # 真实 retarget (models/robot)
    def to_ros2_msgs(self, t: HandToken) -> tuple: ...
    def fuse(self, vision: VisionState, glove: HandToken) -> HumanIntent: ...
```

---

## 7. 真实性

| 能力 | 状态 | 佐证 |
|------|------|------|
| Hand Token 二进制协议 (serialize/parse/CRC-16/float16/device_id) | 🟡→✅ **实现完成, 待首轮测试确认** | `firmware/shared/hand_token.{h,c}` + `relay/hand_token.py`; host 单测 + pytest 金标双向校验待运行 |
| 双表示层分叉 (`to_mano`/`to_robot_action` 结构视图) | 🟡 | `relay/hand_token.py` 结构视图, 非真实回归/重定向 |
| MANO Layer (flex→θ/β 回归) | 🟡 | `models/mano/` 待实现 |
| Robot Action Layer (joint retarget) | 🟡 | `models/robot/` 待实现 |
| Vision+Glove 融合 | 🟡 | 接口预留, 第一代无 CV (D7) |
| 力字段 (Pro force/contact) | 🔬 | Force 硬件待 |
| 6DoF wrist 外部位姿 | 🔬 | 需视觉/UWB/磁跟踪之一 |

> 首轮 host 单测 + pytest 金标校验通过后, 第一行升 **✅** 并同步 `ARCHITECTURE.md §8` 与 `06_decision_summary.md §3`。

## 8. 相关

- `STRATEGY.md` D3 (数据标准), D1 (感知主线)
- `ARCHITECTURE.md` §2/§3 (数据流图), §8 (真实性总表)
- `../BP/EchoGlove_BP_V2.1.md` 第三章 (产品体系) / 第四章 (壁垒)
