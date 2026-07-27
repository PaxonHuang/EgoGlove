# EchoGlove V7.0 — 双表示层详解 (D3 核心壁垒)

> **Version**: V7.0
> **Date**: 2026-07-25
> **Status**: v1 协议层已实现待测 (host 单测 / pytest 金标) · v2 Skeleton Layer 设计冻结待实现 (D11) · 语义映射 🟡
> **参见**: `STRATEGY.md` D3/D10/D11, `ARCHITECTURE.md` §2/§3, `../BP/research_5_data_formats_interop.md`

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

---

## 1b. Hand Token v2 — Skeleton Layer 互操作层 (D11 冻结, 代码待实现 🟡)

> **状态**: 设计冻结 (D11, 2026-07-27 用户签核) · spec = `docs/superpowers/specs/2026-07-27-hand-token-v2-design.md` · 研究底稿 = `../BP/research_5_data_formats_interop.md` · **协议代码未写** (下一阶段 TDD 落地)。v1 (§1.2) 保持不变并永久兼容。

D10/D11 把 Hand Token 升级为**双向手部运动互操作层**。v2 在 v1 (Sensor-level 紧凑帧) 之上引入 **Skeleton Layer**: 通用手部骨架表示, 可 ingest 第三方手套 (Hi5/mHand/Manus/Rokoko/OpenXR) 并 export 到生态 (MANO/BVH/FBX/OpenXR/ROS)。

### 1b.1 canonical 骨架 = 20 旋转关节 (D11)
```
 0  Wrist (根; 全局腕位姿单独承载)
 拇指: 1 CMC(Metacarpal) → 2 MCP(Proximal) → 3 IP(Distal)
 食/中/无名/小指(各4): Metacarpal → Proximal → Intermediate(PIP) → Distal
   食 4-7 · 中 8-11 · 无名 12-15 · 小 16-19
 指尖(5) = 派生 (每 Distal 经 rest-offset 固定偏移), 不存储
```
- **四元数 `w,x,y,z` (w-first, 与 v1 一致), 父相对, 右手 +Y up/-Z fwd/+X right, 米。**
- **= Noitom Axis 每手20 · = OpenXR-26 去 6 可派生 · ⊃ MANO-16** → 无损 ingest 专业手套的最小完整旋转集。
- **21 MediaPipe 关键点 = 派生视图** (20 旋转 + rest-offset 经 FK → 16 MANO 关节 + 5 指尖位置)。D10 的 21 对外锚点/web 前端/视觉融合公共空间不变。
- 四元数分量顺序**不通用** (w-first: v1/Manus/Rokoko; w-last: OpenXR/glTF/ROS2/Noitom) → v2 帧头 `caps` 显式声明并在 ingest/export swap。

### 1b.2 v2 二进制帧 (capability-flagged TLV 变长, version 0x02, 待实现)
| off | len | field | 说明 |
|---|---|---|---|
| 0 | 2 | magic `"HT"` | 不变 (0x48 0x54) |
| 2 | 1 | version=`0x02` | 新值; v1-only 解析器在此干净拒绝 |
| 3 | 1 | device_id | 不变位域 (product\|hand\|serial) |
| 4 | 4 | timestamp_us | 不变 uint32 LE |
| 8 | 1 | caps 位域 | bit0 HAS_SKELETON, bit1 HAS_FORCE, bit2 HAS_VEL/ACC, bit3 GLOBAL_WRIST, bit4 QUAT_WLAST(0=wxyz), bit5 HANDEDNESS/axis, bit6 SKEL_SMALLEST3(0=f16×4), bit7 reserved |
| 9 | 2 | total_len | 新 uint16 LE, 全帧含 CRC |
| 11 | .. | BASE BLOCK | v1兼容核 (Lite 发, SKELETON=0): flex[5]f16·quat[4]f16(腕)·wrist_6dof[6]f32·vel[3]f16·acc[3]f16·contact[5]u8·force[5]f16 |
| .. | .. | TLV REGION | 0+ 条 {type u8, len u16 LE, value[len]}; 未知类型按 len 跳过 |
| end-2 | 2 | crc16 | CRC-16/MODBUS over [0…crc), 小端 (同 v1) |

**TLV 初始注册表**: `0x01 SKELETON_QUAT20` (20×quat, f16×4=160B 或 smallest-three=80B) · `0x02 REST_OFFSETS` (20×(dx,dy,dz)f16, 使能 FK/派生21) · `0x03 JOINT_ANGLES` (Manus-ergo 式紧凑角/快速 retarget) · `0x04 GLOBAL_WRIST_POSE` · `0x05 FINGERTIP_CONTACT_FORCE` · `0x06 SOURCE_PROVENANCE` (厂商id+源格式+fps) · `0x07 HAND_SHAPE_BETA` (MANO β 10×f16)。

**载荷**: Lite `[头11B]+[base 69B]+[crc 2B] ≈ 82B` (≈v1 +3B); Pro/ingested + `SKELETON_QUAT20` ≈ 166–246B。version-gate 向后兼容: v1 帧永久有效, v2 解析器兼收。

### 1b.3 双向映射 (ingest / export)
- **Ingest**: Noitom/Hi5 (20关节 x,y,z,w, 近1:1) · Manus (skeleton w,x,y,z 或 ergo 角) · Rokoko (15骨 keyed quat, 补掌骨) · OpenXR (26→去派生, global→local) · BVH (Euler ZXY→quat, 名重映射) · mHand (经 BVH 导出, schema 待核实)。
- **Export**: MANO (20→16 折掌骨, θ/β) · BVH/FBX (HIERARCHY+MOTION) · OpenXR/SteamVR (派生 palm/指尖/Aux) · ROS2 (`JointState` name/position/**effort=force**, `PoseStamped` 腕 x,y,z,w) · 21 MediaPipe (FK 派生)。
- 完整映射矩阵见 `research_5` §B。

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
| Hand Token **v2** Skeleton Layer (20-rotation canonical, TLV 变长帧) | 🟡 **设计冻结 (D11), 代码待写** | spec `docs/superpowers/specs/2026-07-27-hand-token-v2-design.md`; 研究 `../BP/research_5`; 下一阶段 TDD 落地, v1 永久兼容 |
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
