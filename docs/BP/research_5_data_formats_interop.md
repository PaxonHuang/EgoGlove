# 竞品研究 (5/5) — 手部数据/骨架格式与流协议互操作

> 来源: 并行研究Agent (数据标准分析), 2026-07-26。本会话 WebSearch/WebFetch 后端间歇性不可用, 凡标 **高/中** 的 spec 细节均经 headless 浏览器**从权威源实时抓取** (Khronos registry / 各厂商官方 GitHub / ROS2 common_interfaces / MANO·SMPL-X 代码); 无法对权威源核对的厂商项标 **待核实** 并只给一般形态, **不编造字段名**。v1 帧直接读自本仓库 `firmware/shared/hand_token.h` / `relay/hand_token.py` / `docs/V7/07_dual_rep_layer.md`。
>
> **本文定位**: 这是支撑 D10 (Open Hand Motion Infrastructure) 与 Hand Token v2 双向互操作层的**格式研究底稿**。与 research_1 (硬件竞品) / research_3 (机器人遥操作/RLDS) 互补: research_1 回答"有哪些手套", 本文回答"它们说什么语言、Hand Token 如何成为通用枢纽"。

---

## ⚠️ P0 待用户签核的关键设计决策 (canonical joint count)

本研究给出的核心工程建议是 **20-joint-per-hand 旋转骨架** 作为 Hand Token v2 的 canonical 内部表示 (见 §A)。**这与已冻结的 D10 (STRATEGY.md) 表述存在张力, 需用户 P0 拍板**:

- **D10 冻结原文**: Skeleton Layer = 通用 **21-joint** (MediaPipe 拓扑: 腕1 + 每指4×5=21, 含指尖、不含掌骨)。
- **本研究建议**: canonical = **20 旋转关节** (腕1 + 拇指3 + 4指×4[掌骨/近节/中节/远节], 指尖=派生), 与 Noitom Axis 每手20、OpenXR-26 去掉6个可派生关节 (PALM+5指尖) 精确对齐, 且是 MANO-16 的严格超集。
- **本质区别**: **21 = 位置关键点** (positions, 视觉/web/MediaPipe 语系); **20 = 旋转关节** (rotations, IMU/专业手套/retarget 语系)。二者不是替代关系。
- **候选调和方案 (推荐带给用户)**: 以 **20 旋转关节为主表示** (承载 quaternion + rest-offset), 前向运动学**派生 21 MediaPipe 关键点位置**作为导出视图。如此 D10 的 21-keypoint 前端/视觉锚点不变, 而内部获得可无损 ingest 专业手套 (Hi5/mHand/Manus/OpenXR) 的旋转承载力。

> 本文以**研究结论**身份如实报告 20-joint 建议; **是否修改 D10、v2 字节布局如何冻结, 属 P0 决策, 未在本文擅自变更**。docs/V7 (STRATEGY/07_dual_rep_layer/ARCHITECTURE) 的绑定性更新**待用户签核后**再落。
>
> **✅ 已决 (2026-07-27)**: 用户 P0 拍板采**调和方案** → 冻结为 **D11** (canonical=20 旋转主 + FK 派生 21); 并追加 **D12** 生态对齐 (开放 Hand Motion Infrastructure, 厂商手套=外部源/适配器)。绑定文档 (STRATEGY D11/D12、07_dual_rep_layer §1b、ARCHITECTURE §3/§8、spec `docs/superpowers/specs/2026-07-27-hand-token-v2-design.md`) 已同步。本节保留作决策留痕。

---

## 0. 贯穿性事实 — 四元数分量顺序不通用 (最高频静默损坏点)

| 顺序 | 使用方 |
|---|---|
| **`w,x,y,z` (w-first)** | Hand Token v1 `quat[4]`、**Manus** `ManusQuaternion`、Rokoko JSON (keyed) |
| **`x,y,z,w` (w-last)** | **OpenXR** `XrQuaternionf`、**glTF** node rotation、**ROS2** `geometry_msgs/Quaternion`、**Noitom** `GetJointLocalRotation(x,y,z,w)` |

任何枢纽 (hub) **必须显式声明自身顺序并在 ingest/export 时做 swap**。这是手部数据互操作中最常见的静默数据损坏来源, v2 必须在帧头 `caps` 位声明 (§C)。

---

## 1. BVH (Biovision Hierarchy) — 动捕通用语 【高】

- 来源: Thingvold BVH reference, research.cs.wisc.edu/graphics/Courses/cs-838-1999/Jeff/BVH.html (内容实时核对, 高)。
- **两段结构**: `HIERARCHY` (骨架 + rest pose) 后接 `MOTION` (逐帧通道值)。
- **层级语法**: `ROOT <name> { OFFSET x y z … }`, 递归 `JOINT <name> { … }`, 以 `End Site { OFFSET x y z }` (叶/指尖) 终结。
- **ROOT 通道 (通常6)**: `Xposition Yposition Zposition Zrotation Xrotation Yrotation`; **每个非根关节 3 通道 (仅旋转)**。通道数+顺序**逐关节在头部声明**, 解析 MOTION 扁平行时必须遵守。
- **OFFSET 仅平移**: BVH 编码骨长/方向但**无旋转 rest offset** (无完整 basis pose) — 已文档化的局限。指尖长度来自 `End Site` OFFSET。
- **Euler 顺序陷阱**: canonical 顺序为 **Z→X→Y** ("somewhat unusual"), 各导出器不一 → 经典 BVH 互操作失败点, 易 gimbal-lock。世界系右手 **Y-up**。
- **手部编码**: 手指是腕/手关节下的嵌套 `JOINT`。典型每指链 `…Hand → {Finger}1(MCP) → {Finger}2(PIP) → {Finger}3(DIP) → End Site(tip)` = 3旋转关节/指 ×5 + 手 ≈ **16/手**。**BVH 无 canonical 手关节集** — 全由导出器命名 (Rokoko/Noitom/mHand 各写各的, 见 §5)。故 BVH 适合**传输**、不适合做**语义标准**。

---

## 2. FBX / glTF 2.0 / VRM humanoid

- **glTF 2.0 skinning 【高】** (Khronos glTF spec): 右手, **Y-up**, 米, **-Z forward**。`skins[] = { joints:[node idx], inverseBindMatrices, skeleton:root }`; 网格顶点 `JOINTS_0`+`WEIGHTS_0` → 线性混合蒙皮。node 变换 = TRS: `translation[3]`, **`rotation` = quaternion `[x,y,z,w]` (w-last)**, `scale[3]` 或 `matrix[16]`; 旋转**父相对**。核心 glTF **无 humanoid 骨骼命名** — 该语义层是 VRM。
- **FBX 【中】** (Autodesk 专有, 知识域): 骨架 = `Model::LimbNode` 层级; 蒙皮 `Deformer(Skin)`+`SubDeformer(Cluster)`。旋转存 **Euler + 每节 `RotationOrder` + `PreRotation`/`PostRotation`**; 轴/单位在 `GlobalSettings`。手关节 rig 相关无 canonical 集。**SteamVR 参考手骨架即以 `.fbx`+`.glb` 发布** (§4)。
- **VRM humanoid 手骨 【高】** (核对 `vrm-c/vrm-specification` `VRMC_vrm-1.0/humanoid.md`): 骨为 glTF node (quaternion, 父相对)。**每手 15 指骨 (全可选)**:
  - 拇指 (VRM 1.0): `{side}ThumbMetacarpal → ThumbProximal → ThumbDistal`
  - 食/中/无名/小: `{side}{Finger}Proximal → Intermediate → Distal`, 挂 `{side}Hand → LowerArm` 下。
  - **VRM 0.x 差异 【中/待核实】**: 0.x 拇指用 `Proximal/Intermediate/Distal`, 1.0 改名 `Metacarpal/Proximal/Distal` — 真实的 0↔1 迁移陷阱。
  - **实时 retarget**: VRM 以定义好的 **rest/T-pose** 归一化骨旋转, 源骨架逐骨旋转经 rest-pose 归一后映射到 VRM humanoid (Unity Humanoid/Mecanim 模型); Rokoko Blender 插件即 `源quat × inverse(rest) → 目标骨`。

---

## 3. MANO / SMPL-X hand 【高】

- 来源: MANO "Embodied Hands" SIGGRAPH Asia 2017 (Romero/Tzionas/Black), mano.is.tue.mpg.de; `hassony2/manopth`; `vchoutas/smplx` (代码实时核对)。
- **16 关节/手** = 1 腕/根 + 15 指节关节 (3/指 ×5)。**指尖不是关节** — 是 mesh 顶点; 追加5指尖 = **21-keypoint** 拓扑 (与 MediaPipe 一致)。
- **Pose θ (axis-angle, 父相对)**: 15 非根关节×3 = **45**; +3 全局根旋转 = **48** 全量 (manopth 核对: `random_pose = ncomps + 3`, 满 DOF=45)。
- **PCA pose space**: MANO 自带 45-D 姿态的 PCA 基; `ManoLayer(use_pca=True, ncomps=…)` (typ. 6–45)。姿态 = 均值 + 基@系数 → 自然手先验, 正则化噪声输入。**这正是 EgoGlove "5 flex → 全手回归" 应利用的先验。**
- **Shape β = 10** (核对 `random_shape=(B,10)`); 778 顶点/手。`MANO_RIGHT.pkl`/`MANO_LEFT.pkl` 分离。MANO 是 SMPL+H / SMPL-X 的手块 (SMPL-X: K=54 关节, N=10,475 顶点)。
- **与 MediaPipe 21 关系** (核对 `HandLandmark` enum): `WRIST=0`, `THUMB_CMC/MCP/IP/TIP=1..4`, `INDEX 5..8`, `MIDDLE 9..12`, `RING 13..16`, `PINKY 17..20`。MediaPipe = **仅位置** (无朝向), 归一化图像坐标或世界 (米, 原点手心)。标准做法: 用 MANO (16关节+5指尖) 拟合 MediaPipe 21 landmarks。
- **许可证警示**: MANO 为**非商用研究许可** — 商用 EgoGlove 需 MANO 商用条款或自研 MANO-拓扑模型。**BP 成本/合规章节须计入。**

---

## 4. OpenXR hand tracking + SteamVR Skeletal Input 【高】

- **OpenXR `XR_EXT_hand_tracking`** (核对 Khronos registry v1.1.61 + `openxr.h`):
  - **26 关节 (`XrHandJointEXT`)**: `PALM=0, WRIST=1`, 拇指 `METACARPAL/PROXIMAL/DISTAL/TIP=2..5` (4, 无 intermediate), 食/中/无名/小 各 `METACARPAL/PROXIMAL/INTERMEDIATE/DISTAL/TIP` (5×4)。2+4+20 = **26**。
  - 每关节 `XrHandJointLocationEXT = { locationFlags; XrPosef pose; float radius }`; `XrPosef = { XrQuaternionf orientation; XrVector3f position }`; **`XrQuaternionf = {x,y,z,w}` (w-last)**。可选 `XrHandJointVelocityEXT`。
  - **关键: pose 是 GLOBAL** (对 `baseSpace` 一起定位, 非父相对)。米; +Y up, -Z forward, +X right。每手载荷 26×(pos3+quat4+radius1)。
- **SteamVR Skeletal Input** (核对 ValveSoftware/openvr wiki):
  - **31 骨 (`HandSkeletonBone`)**: `Root=0, Wrist=1, Thumb0..3`(4), `Index/Middle/Ring/Pinky Finger0..4`(5×4), `Aux_*`(5 辅助骨)。1+1+4+20+5 = **31**。父先于子; 无 twist; 无 scale (仅平移+旋转)。
  - **两种保真度**: `GetSkeletalBoneData()` → 每骨 `VRBoneTransform_t` (父相对或 model space 可选); `GetSkeletalSummaryData()` → **每指 curl[0..1](5) + splay[0..1](4)** — 低 DOF 摘要, **直接类比 EgoGlove `flex[5]`**。`GetSkeletalBoneDataCompressed()` → 变长网络 blob。

---

## 5. 厂商 LIVE 流协议

### 5.1 Rokoko Studio Live 【高】 (核对官方 `Rokoko/rokoko-studio-live-blender` 源)
- 传输: JSON over **UDP**, 可选 **LZ4 压缩**; 接收 socket buf 81920B; 默认端口 **14043 (待核实, 插件可配)**。
- 版本化 schema (`version` 字段): v2 `{version,timestamp,props[],trackers[],faces[],actors[]}`; v3 `{version,fps,scene:{timestamp,actors[],props[]}}`。
- Actor: `{name, meta:{hasFace,hasGloves,…}, dimensions, body:{<bone>:{rotation:{w,x,y,z}, position:{x,y,z}}}, face}`。旋转 = **keyed quaternion (w,x,y,z 按名)**。
- 手指骨 (present when `meta.hasGloves`): `{side}{Thumb|Index|Middle|Ring|Little}{Proximal|Medial|Distal}(+Tip)` — Rokoko 用 **"Medial"** (非 Intermediate), **3 骨/指**。
- 坐标: Studio Y-up; 插件转 Blender Z-up 时 pos `(x,y,z)→(-x,-z,y)`, rot `(w,x,y,z)→(w,x,z,-y)`。
- 另有 HTTP Command API (控制非数据): `http://<ip>:<port>/v1/<api_key>/…` → `/calibrate`,`/recording/start|stop`。

### 5.2 Manus Core / MANUS SDK 【高】 (核对 `ManusSDKTypes.h` + `etaoxing/manus_glove/_enums.py`; 类型经社区镜像, enum 值为 Manus canonical)
Manus 暴露**两套并行表示 — 值得直接借鉴**:
- **(a) Skeleton 流**: `SkeletonNode = {uint32 id; ManusTransform transform}`, `ManusTransform = {ManusVec3 position; ManusQuaternion rotation; ManusVec3 scale}`, **`ManusQuaternion = {w,x,y,z}` (w-first, 默认 w=1)**。local/global 由 init 时坐标系选择 (`CoreSdk_InitializeCoordinateSystemWithVUH` = View/Up/Handedness)。`ChainType{Arm,…,FingerThumb/Index/Middle/Ring/Pinky,Hand,…}` + `FingerJointType{Metacarpal,Proximal,Intermediate,Distal,Tip}` (拇指无 Intermediate)。
- **(b) Ergonomics 流**: `ErgonomicsData = float[40]` (`MAX_SIZE=40`)。**每手 20 值 = 5指×{MCPSpread, MCPStretch, PIPStretch, DIPStretch}** (拇指复用4槽)。左 0..19, 右 20..39。这是**关节角** (外展"spread"+屈曲"stretch"), 紧凑、retarget 友好。
- **四元数 w-first 与 Hand Token 一致**; 存在 `manus_ros2` 桥 → Manus→ROS2。

### 5.3 Noitom Axis Studio / Hi5 SDK 【高】 (核对官方 `pnmocap/MocapApi.h`)
- SDK = "MocapApi" (Axis Studio)。`EMCPJointTag`, **60 身体关节**。**每手 20 关节**: `{side}Hand`, `{side}HandThumb1/2/3`, `{side}InHandIndex + HandIndex1/2/3`, InHandMiddle+Middle1/2/3, InHandRing+Ring1/2/3, InHandPinky+Pinky1/2/3 (拇指3骨无 InHand; 其余指 InHand掌骨+3指节=4)。经典 3ds Max biped 命名。
- 访问 (`IMCPJoint`): `GetJointLocalRotation(x,y,z,w)` **quaternion (w-last)**, `…ByEuler`, `GetJointLocalPosition`; `IMCPSensorModule`: 姿态四元数 + **角速度 + 加速度** + compass + timecode。另有 **BVH 广播** + `.calc` 原始文件。`pnmocap` 出 `mocap_ros_py/cpp`, `mocap_ros_urdf`, `robot_retarget_tool` → **Noitom→ROS2 机器人 retarget 是现成路径**。
- **Hi5 手套 【中/待核实】**: 走同一 Axis/MocapApi 手管线 (每手20关节链); 独立 Unity "Hi5 SDK" 暴露每指关节变换, 精确 struct 本会话未对权威源核实。

### 5.4 mHand (Virdyn 虚拟动点 mHand Pro) 【待核实】
- 未找到公开 SDK/schema artifact (中文厂商; 惯性数据手套, 配 VDMocap Studio)。**仅一般形态、不编造字段**: 每指 IMU → 每关节 quaternion; **导出 BVH** (指骨层级, 约 3关节/指+腕, Axis/3ds-Max 式命名) 和/或专有 UDP/SDK 帧。**整条 wire schema 待核实** — 取得 SDK 头前当作 "BVH-兼容手套"。

---

## 6. ROS2 + VLA 动作编码

- **ROS2 消息 【高】** (核对 `ros2/common_interfaces`):
  - `sensor_msgs/JointState`: `Header; string[] name; float64[] position; float64[] velocity; float64[] effort`。名索引并行数组 (rad/m; rad·s; **Nm/N**)。**无朝向** — 每命名 DOF 一标量。手 = 关节名 (`{hand}_{finger}_{joint}`) + position(rad); **`effort` 即 EgoGlove force 的落点**。
  - `geometry_msgs/PoseStamped`: `Header + Pose{Point position; Quaternion orientation}`; **`Quaternion = {x,y,z,w}` (w-last)**。腕 6DoF → 命名 tf `frame_id` 下的 PoseStamped。
  - 灵巧手关节命名: 约定用目标 **URDF joint 名** (Allegro `joint_0..15`, Shadow `rh_FFJ1..4/rh_THJ1..5`, LEAP)。Noitom `mocap_ros_urdf`+`robot_retarget_tool` 演示 mocap→URDF retarget。
- **OpenX-Embodiment / RLDS / DROID** (OXE 高, DROID 中; 核对 `google-deepmind/open_x_embodiment` README):
  - RLDS = TFDS 情节格式: dataset→episodes→`steps{observation, action, reward, discount, is_first/last/terminal, language_instruction}`。
  - **OXE canonical action (README 原文)**: "seven variables for the gripper movement (x, y, z, roll, pitch, yaw, opening of the gripper)" → **末端位姿(6) + 夹爪(1标量)**。
  - **承重发现: 主流 VLA 数据无逐关节手骨架 — 手= 单 1-DOF 夹爪标量, 无力/触觉通道**; 且 22+ OXE 数据集夹爪编码不一致 (连续0..1 / 二值 / 米宽度, 开合符号翻转) — 已知归一化痛点。**这正是 research_3 "力字段无处安放 → 推动 RLDS schema 扩展" 论点的格式侧实证。**

---

## A. 推荐的 Hand Token v2 canonical 内部骨架

**建议: 每手 20-joint canonical 旋转骨架。** 数学"甜点": = **OpenXR-26 去掉 6 个可派生关节 (PALM + 5 TIP)**, = **Noitom Axis 每手 20**, 是 **MANO-16 的严格超集** (多出的4 = MANO 折进手掌的非拇指掌骨), 并覆盖 **SteamVR 20 个 DOF 承载骨** (31 去5 Aux 去5 tip 去 root-as-wrist)。

### 关节集 + 层级 (parent → child)
```
 0  Wrist            (手 token 根; 全局腕位姿单独承载)
 拇指: 1 ThumbMetacarpal(CMC) → 2 ThumbProximal(MCP) → 3 ThumbDistal(IP)
 食指: 4 IndexMetacarpal → 5 IndexProximal(MCP) → 6 IndexIntermediate(PIP) → 7 IndexDistal(DIP)
 中指: 8 MiddleMetacarpal → 9 …Proximal → 10 …Intermediate → 11 …Distal
 无名:12 RingMetacarpal  → 13 …Proximal → 14 …Intermediate → 15 …Distal
 小指:16 LittleMetacarpal→ 17 …Proximal → 18 …Intermediate → 19 …Distal
 指尖(5) = 派生 (每 Distal 经 rest-offset 表固定偏移) — 不存储
```

### 旋转约定 (逐项明确声明)
- **单位四元数, 父相对** (每关节相对父的局部旋转)。选父相对因 MANO/BVH/FBX/glTF/VRM/SteamVR-parent/Manus-local 皆父相对; OpenXR-global 与 Manus-global 经父链 + rest-offset 表**一次性**转换。
- **分量顺序 `w,x,y,z` (w-first)** — 与 v1 `quat[4]` 及 Manus 一致; 为 w-last 阵营 (OpenXR/glTF/ROS/Noitom) 记录单次 swap。
- **坐标系: 右手, +Y up, -Z forward, +X right, 米** (对齐 OpenXR/glTF)。
- **附带 rest-offset 表** (每关节父→子平移, BVH-`OFFSET` 式), 置于 capability 块, 使消费者可做前向运动学恢复**全局**关节位置 → Hand Token 自足于 FK (不像裸 BVH MOTION 需分离 HIERARCHY)。**并由此派生 21 MediaPipe 关键点位置** (调和 D10, 见文首 P0)。

### 为何选 20 (非 16 / 26)
- **16 (MANO-min)**: 丢 4 个非拇指掌骨 DOF → 无法忠实 ingest OpenXR/Manus/Noitom 掌骨展开 → **对专业手套 ingest 有损**。(仍可 20→16 投影出 MANO 输出; 但从未存则无法恢复掌骨。)
- **26 (OpenXR-full)**: PALM+5 TIP 非 DOF 且几何可派生 → 6 冗余关节 = 每帧浪费字节。
- **20**: 最小**完整 DOF 承载**集; MANO 超集; 精确匹配 Noitom Axis 与 OpenXR-去派生; 覆盖 SteamVR 有意义骨与 Manus 指链。**选 20。**

### 载荷大小 (每手, 仅骨架块)
| 编码 | 字节/关节 | 20 关节 |
|---|---|---|
| `float16 × 4` (推荐默认) | 8 | **160 B** |
| `int16 × 4` (定点归一) | 8 | 160 B |
| **smallest-three** (弃最大分量, 2-bit 索引 + 3×10-bit) | 4 | **80 B** |

完整 Pro/ingested 帧 ≈ v2 头(~12B) + v1兼容核(69B) + 骨架TLV(3B头+160B) + CRC(2B) ≈ **~246B** (float16) 或 **~166B** (smallest-three)。**Lite 帧维持 v1 核 ≈ ~79–82B**。双手 = 两帧。

---

## B. 映射矩阵

列: **关节/手 · 旋转编码 · ingest→HandToken · HandToken→export · 有损? · 备注** (HT canonical = 20 关节, quaternion w,x,y,z, 父相对)。

| 格式 | 关节/手 | 旋转编码 | Ingest → HT | HT → export | 有损? | 备注 |
|---|---|---|---|---|---|---|
| **BVH** | ~16 (3/指+手; 导出器定义) | Euler **ZXY**, 父相对; OFFSET=平移 | 中 — 解析 HIERARCHY, Euler→quat, 名重映射; 常缺掌骨 | 高 — 由20关节生成 HIERARCHY+MOTION | Euler→quat 无损; **名/拓扑映射有损**; 掌骨进出皆无 | 通用传输、零语义。Rokoko/Noitom/mHand 皆导 BVH。 |
| **FBX / VRM** | FBX rig定义; **VRM 15** | FBX Euler+RotationOrder+PreRot; VRM/glTF **quat x,y,z,w** 父相对 | VRM 高 (名映射); FBX 中 (rig 相关) | 高 — VRM humanoid 指骨 1:1 | VRM 近无损; VRM 食-小指无显式掌骨→折进 Proximal | VRM = 语义 humanoid 层; 实时 retarget = rest-pose 归一后应用。 |
| **MANO / SMPL-X** | **16** (+5指尖顶点) | **axis-angle**, 父相对, 45(+3)维, PCA 先验 | 高 — axis-angle→quat; 16⊂20 精确 | 高 — 20→16 折掌骨进掌; 回归 θ/β | 20→16 **轻损** (掌骨并入); 16→20 精确 | canonical 数字人模型 (§D)。非商用许可警示。 |
| **OpenXR / SteamVR** | **26 / 31** | quat **x,y,z,w**; OXR **global**+pos+radius(+vel); SteamVR 父/model + curl/splay | 高 — OXR 去 PALM+指尖→20, global→local 经 offsets; SteamVR 去5 Aux+指尖→20 | 高 — 合成 26 (派生 palm/指尖) 或 31 (加 Aux) | OXR→HT 丢 radius (非DOF) 可接受; HT→OXR 指尖/palm 派生 | OXR global pose 需 rest-offset 本地化。SteamVR summary curl[5]/splay[4] ↔ HT flex[5]。 |
| **Rokoko Live** | 15 (3/指, "Medial") | keyed quat **w,x,y,z** + position; JSON/UDP(+LZ4) | 中 — 解析 `actor.body[*]`; **无掌骨**; Studio→canonical 轴修正 | 中 — 出 body[*] quats; 掌骨→Proximal | in: 无掌骨(有损); 需轴/handedness swap | 数据走 UDP, 控制走 HTTP `/v1/<key>`。`meta.hasGloves` 门控手指。 |
| **Manus** | skeleton (Metacarpal→Tip 链) **或** 20-float ergo/手 | **quat w,x,y,z** + pos + scale (local/global 可配); ergo = 20 角 {MCP spread/stretch, PIP, DIP} | 高 — skeleton ~1:1 到 20; ergo→关节角→quat | 高 — 出 skeleton nodes 或 ergo 角 | skeleton 近无损; ergo↔quat 经解剖模型(轻) | **双表示模型值得效仿。** Quat w-first 与 HT 一致。init 时定坐标系 (VUH)。 |
| **Noitom / Hi5** | **20** (Hand+Thumb1-3+InHand{f}+{f}1-3) | quat **x,y,z,w** local (+Euler, +axis-angle); IMU 角速度/加速度 | 高 — **近 1:1 到 HT-20** (拓扑一致) | 高 — 出 20关节 MocapApi 姿态 / BVH | 基本无损 (拓扑匹配) | **对 HT-20 结构最佳匹配。** 出 ROS2 retarget 工具。Hi5 流 待核实。 |
| **mHand (Virdyn)** | ~16 待核实 | 待核实 (likely quat + BVH 导出) | 待核实 — 当 BVH 手套 | 待核实 | 待核实 | **无权威 schema。** 暂经其 BVH 导出 ingest。 |
| **ROS2 JointState** | N 命名 DOF (无固定数) | **标量 position(rad)**/名; +velocity, **+effort(N/Nm)**; 无朝向 | 高 — HT quats→关节角 (按 URDF 名) | 高 — 出 `name[]/position[]/(effort[])` | quat→单DOF/关节 **有损** (丢离轴旋转) | 机器人侧。**`effort` = EgoGlove force[5] 的家。** 配 `PoseStamped` (quat x,y,z,w) 承载腕。 |

---

## C. v1 79字节帧应如何演进 (capability-flagged TLV)

**结论**: Lite 保持 v1 原样; 演进为 **capability 标志的变长 TLV 帧 (version `0x02`)** — 骨架能力的 Pro/ingested-第三方手套承载完整 20-关节骨架, 而仅 flex 的 Lite 维持 ~79B。**不**加宽定长帧 (否则每个 Lite 包塞零膨胀; 现 `wrist_6dof` f32 块已让 Lite 花 24B 零)。

### 设计规则
1. **Magic `"HT"` 不变; `version=0x02`。** 新增 `caps` 位域 + TLV 区自描述。保留 CRC-16/MODBUS over `[0…crc)`, 小端, float16 — 全部 v1 约定。
2. **向后兼容: v1 与 v2 并行。** v1(`version==1`, 定长79B) 解析器对 Lite v1 emitter 永久有效; v2 解析器兼收 (v1→79B 路径; v2→length+TLV 路径); v1-only 解析器在 version 检查处干净拒绝 v2。**不**在 v1 定长 CRC 后夹带 TLV — 用 version-gate。
3. **在 `caps` 声明四元数顺序 + handedness** — 消除 ingest w-last (OpenXR/Noitom/ROS) vs w-first (Manus/HT) 歧义。
4. **未知 TLV 类型按 length 跳过** → 前向可扩展不破坏旧 v2 解析器。

### 建议 v2 字段布局
```
 off  len  field           notes
 0    2    magic "HT"       不变 (0x48 0x54)
 2    1    version = 0x02   新值
 3    1    device_id        不变位域 (product|hand|serial)
 4    4    timestamp_us     不变 (uint32 LE)
 8    1    caps  (位域)      新: bit0 HAS_SKELETON, bit1 HAS_FORCE, bit2 HAS_VEL/ACC,
                             bit3 GLOBAL_WRIST, bit4 QUAT_WLAST(0=wxyz,1=xyzw),
                             bit5 HANDEDNESS/axis profile, bit6 SKEL_SMALLEST3(0=f16x4),
                             bit7 reserved
 9    2    total_len        新 (uint16 LE): 全帧含 CRC → 变长
 11   ..   BASE BLOCK       v1兼容核, Lite 发 (SKELETON=0):
                              flex[5]f16 | quat[4]f16(腕) | wrist_6dof[6]f32
                              | vel[3]f16 | acc[3]f16 | contact[5]u8 | force[5]f16
 ..   ..   TLV REGION       零或多条 (Pro/ingested): 每条 = {type u8, len u16 LE, value[len]}
 end-2 2   crc16            CRC-16/MODBUS over [0…crc)
```

### 初始 TLV 类型注册表
| type | 名 | value |
|---|---|---|
| `0x01` | `SKELETON_QUAT20` | 20 × quaternion; 编码按 `caps` (f16×4=160B, 或 smallest-three=80B); 顺序 = canonical 关节 0..19 |
| `0x02` | `REST_OFFSETS` | 20 × (dx,dy,dz) f16 父→子骨向量 → 使能 FK / local↔global / 派生 21 MediaPipe 关键点 |
| `0x03` | `JOINT_ANGLES` | Manus-ergonomics 式紧凑角 (每手20: spread/stretch/指) 供快速 retarget |
| `0x04` | `GLOBAL_WRIST_POSE` | 腕 pos f32×3 + quat f16×4 于命名系 (当 `GLOBAL_WRIST`) |
| `0x05` | `FINGERTIP_CONTACT_FORCE` | 超出 base `contact[5]`/`force[5]` 的扩展每指尖接触/力 |
| `0x06` | `SOURCE_PROVENANCE` | u8 厂商id + u8 源格式 + fps → 记录该帧由 OpenXR/Manus/Noitom/Rokoko/BVH ingest 而来 |
| `0x07` | `HAND_SHAPE_BETA` | 已知校准手型时的 MANO β (10 × f16) |

**结果**: Lite 发 `[头11B]+[base 69B]+[crc 2B] ≈ 82B` (实为 v1 +3B caps/len)。Pro/ingested 加 `SKELETON_QUAT20`(+163B f16 或 +83B smallest-three) 及可选 TLV, 自描述、面向未来。**在保持冻结 v1 wire 契约不变的同时**实现"仅flex的Lite保持小、骨架能力的Pro承载全骨架"。

---

## D. MANO 层已给 EgoGlove 的既有优势

1. **MANO 是数字人/XR/手-物研究的事实 canonical 手模型** (AMASS/GRAB/InterHand2.6M/HOI, 及 SMPL-X 手块)。无专业手套厂商以 MANO 为**互换**格式 — Manus/Noitom/Rokoko 各出专有骨架。EgoGlove 认定 MANO 为一个 canonical 输出 → Hand Token 可成为 **ingest 各厂骨架、export 公认标准的枢纽** — STRATEGY.md D3 的"手套界 MANO"定位结构性成立。
2. **20-joint canonical 已内含 MANO-16** (16⊂20)。故 Hand Token→MANO 是**投影非有损猜测**: 折4掌骨进掌即得 MANO 精确关节集; 逆向 (MANO→HT) 对16共享关节精确。选 canonical-20 正为让 MANO 干净落出。
3. **MANO 45-D pose + PCA 先验 = 免费正则化** EgoGlove 最难问题: 把 Lite **5 flex 变可信全手**。回归进 MANO PCA 空间 (`ncomps` 基) 得解剖有效姿态而非逐关节噪声 — `models/mano/` 的正确目标。
4. **MediaPipe 桥低成本**: MANO 16关节+5指尖 ≈ MediaPipe 21 landmarks, 视觉融合路径 (D1 `fuse(vision,glove)`) 有天然公共空间 — 视觉供全局腕位姿+landmark 位置, 手套供逐关节 flex+力, 皆表达于 MANO。
5. **双表示对称**: MANO(XR侧) + canonical-20(机器人/BVH/厂商侧) 使 EgoGlove 骑跨该领域精确断层 — **专业手套只出骨架; VLA/OXE 只出 1-DOF 夹爪标量无力/触觉**。Hand Token 兼 ingest 二者、兼 export MANO 与 ROS2 `JointState`+`effort`, 是真正差异化枢纽; Pro `force[5]`/`contact[5]` 填 OXE/DROID 留下的触觉空洞。

**诚实标注 (按 CLAUDE.md 真实性纪律)**:
- 现 `relay/hand_token.py` 的 `to_mano()`/`to_robot_action()` 是**结构视图 (🟡)** — 真实 flex→θ/β 回归与 joint→URDF retarget **未建** (`models/mano/`, `models/robot/`)。MANO 优势是**架构/战略性**, 待回归落地才兑现。
- **MANO 许可为非商用研究** — 上市商用品需 MANO 商用授权或自研 MANO-拓扑模型。BP 须标。

---

## E. 生态对齐锚点 (D12 新增) — 开放 Hand Motion Infrastructure / 非竞品

> **核实状态**: 本节 anchors 于本会话 WebSearch/WebFetch 后端不可用 (400 config error) 下依领域知识撰写, 统一标 **【中】** (可信但未本会话再核实) 或 **【待核实】**; 出版前须对各官方源核对, 尤其 【待核实】 项。与 research_1/2 同纪律。原拟并行研究子代理因 web 后端卡死被中止, 由主循环内联补写。

**定位 (D12 冻结)**: EgoGlove **不是** Hi5/Manus/mHand 竞品; 厂商手套 = **外部数据源/适配器**。EgoGlove = 开放 **Hand Motion Infrastructure**, 以 Hand Token v2 (厂商无关通用中间表示) 为枢纽。四段管线:
`Sensor Source(flex/IMU/vision/外部手套) → Hand Token v2 → Canonical Skeleton Layer(20 旋转关节, FK 派生 21) → MANO / OpenXR / FreeMoCap / ROS2 / Robot(经 DexRetargeting/AnyTeleop)`。

### E.1 FreeMoCap (开放动捕数据管线参照) 【中】
- **是什么**: 开源免费**无标记**动捕项目; 多台普通摄像头同步 + CV 姿态估计三角化出 3D。
- **手部表示**: 经 MediaPipe (Holistic) → **每手 21 关键点 (位置/keypoints)**; **非旋转骨架、非原生 MANO**, 与 MediaPipe 同语系 (位置)。
- **导出**: CSV / `.npy` / Blender (插件装配骨架) 等, 面向开放数据管线。【待核实 具体 schema】
- **许可 / 仓库**: 【待核实 许可】(社区印象 AGPL 类, 出版前核对); `github.com/freemocap/freemocap`【中】。
- **互操作**: **Export 目标为主** — Hand Token→FK 派生 21 关键点即落入 FreeMoCap 位置语系; 反向 (FreeMoCap→HT) 需 IK 恢复旋转 (有损, 同 MediaPipe)。代表"开放、位置语系"的参照生态, 呼应 D12 开放基础设施定位。

### E.2 DexRetargeting / AnyTeleop (人手→机器人灵巧手桥) 【中】
- **AnyTeleop** (Qin 等, RSS 2023): 通用视觉遥操作系统; 检测人手 → retarget → 控机器人臂+灵巧手。详见 `research_3` 平台表 #5 与其优劣势分析。
- **dex-retargeting** (`dexsuite/dex-retargeting`, MIT): 人手运动 retarget 到机器人灵巧手的 Python 库。
  - **输入表示**: 人手**关键点位置** (task/vector 定义在关键点之间), **非四元数骨架**。【中】
  - **retarget 类型**: position / vector / DexPilot 三型优化。【中】
  - **目标手**: Allegro / Shadow / Leap / Ability 等 (经 URDF 配置)。【待核实 确切列表】
- **互操作**: **Export/retarget 目标** — Hand Token 20 关节 → FK 派生 21 关键点 → dex-retargeting → 机器人 URDF 关节角。是 Robot Action Layer 下游现成的人手→机器人手桥; **EgoGlove 喂它而非与之竞争**。**错配风险**: dex-retargeting 吃**位置**, 须先 FK 出关键点 (我们能无损 FK) 再喂, 不能直接喂四元数。

### E.3 具身智能手部数据集 (数据飞轮兼容) 【中/待核实】
- **InterHand2.6M** (Moon 等, ECCV 2020) 【中】: 大规模**双手交互** 2.6M 帧, Meta/FRL; **MANO 拟合标注** (3D pose+shape)。表示 = MANO + 3D 关键点 → 与 canonical-20/MANO 桥天然对齐。
- **COCO-WholeBody** (Jin 等, ECCV 2020) 【中】: COCO 全身扩展, 133 关键点 (身17+脚6+脸68+**手42=21×2**), **2D 关键点/位置语系**。
- **egocentric 数据集** 【中】: Ego4D (CVPR2022 大规模第一视角)、EgoBody (ECCV2022)、Ego-Exo4D、HOI4D、ARCTIC (双手-物)、DexYCB (抓取, MANO 标注) 等; 多为视频/关键点, 部分 MANO 标注。
- **⚠️ "HumanEgo" 【待核实】**: 用户提及 "HumanEgo" 作 egocentric-AI 数据集, **但未检出确切以此为名的 canonical 数据集** (本会话 web 不可用无法核实)。**不当作确定数据集名写入**; 极可能是"egocentric 人手数据集"类目泛称或与上列某数据集混称。引用前须人工核实确切名称。
- **互操作**: **数据集/训练兼容目标** — MANO 标注类 (InterHand2.6M/DexYCB) 经 canonical-20⊃MANO-16 对齐; 关键点类 (COCO-WholeBody/MediaPipe) 经 FK 派生 21 对齐。支撑 D5 数据飞轮"训练数据跨源复用"。

### E.4 生态角色速查
| 锚点 | 角色 | 与 HT canonical-20 的桥 | 最大错配风险 |
|---|---|---|---|
| MANO/SMPL-X | export (数字人 canonical) | 20→16 折掌骨 (投影) | 非商用许可 |
| OpenXR Hands | ingest+export (XR 运行时) | 26↔20 去/补派生 | 四元数 w-last |
| FreeMoCap | export (开放位置语系) | FK 派生 21 | 位置↔旋转 (反向需 IK) |
| ROS2 + DexRetargeting | export/retarget (机器人手) | FK 21 → retarget URDF | 吃位置非四元数; 关节 DOF 差异 |
| InterHand2.6M/DexYCB | dataset (MANO 标注) | ⊃MANO-16 对齐 | 手型 β / 许可 |
| COCO-WholeBody/egocentric | dataset (关键点) | FK 派生 21 对齐 | 仅位置无朝向 |

---

## 待核实 (取得权威 artifact 前勿引用)
- **mHand / Virdyn** 整条 wire schema — 无公开 artifact, 勿造字段名; 暂经 BVH 导出 ingest。
- **Noitom Hi5** 独立 Unity SDK struct (拓扑由 Axis MocapApi 推断, 精确流布局未确认)。
- **Rokoko** 默认 UDP 端口 (常引 14043, 插件可配) 及 `rotation`/`position` 外的每骨字段集。
- **VRM 0.x** 拇指骨串 (0.x `Proximal/Intermediate/Distal` vs 1.0 `Metacarpal/Proximal/Distal`; 1.0 已核实, 0.x 凭记忆)。
- **DROID** 精确 action/observation tensor 规格 (README 未实时呈现; EE+gripper 描述来自既有知识, 中)。
- **Manus SDK** 类型读自社区镜像 (`JamesBridgewater51/MANUS_Core_SDK`); enum 值为 Manus canonical, 出版前对官方 Manus Core SDK release 核对。
- **"HumanEgo" 数据集名** (E.3) — 未检出确切以此为名的 canonical 数据集; 视为 egocentric 人手数据集泛称, 确切名称待人工核实。
- **FreeMoCap** (E.1) 精确导出 schema 与许可证。
- **dex-retargeting** (E.2) 支持的目标灵巧手确切列表与输入关键点拓扑。
- **InterHand2.6M / COCO-WholeBody / egocentric 数据集** (E.3) 标注格式与许可 (依领域知识, 未本会话核实)。

## 来源 (本会话实时抓取)
- OpenXR: registry.khronos.org/OpenXR/specs/1.1/man/html/XrHandJointEXT.html; KhronosGroup/OpenXR-SDK `openxr.h` — 高
- SteamVR: ValveSoftware/openvr wiki Hand-Skeleton + Skeletal-Input — 高
- MANO/SMPL-X: hassony2/manopth, vchoutas/smplx, mano.is.tue.mpg.de (Embodied Hands 2017) — 高
- VRM: vrm-c/vrm-specification `VRMC_vrm-1.0/humanoid.md` — 高
- MediaPipe: google-ai-edge/mediapipe `solutions/hands.py` — 高
- BVH: research.cs.wisc.edu/graphics/Courses/cs-838-1999/Jeff/BVH.html — 高
- Rokoko: Rokoko/rokoko-studio-live-blender (`live_data_manager.py`, `command_api.py` 等) — 高
- Manus: `ManusSDKTypes.h` + etaoxing/manus_glove `_enums.py` — 高
- Noitom: pnmocap/MocapApi `include/MocapApi.h` — 高
- ROS2: ros2/common_interfaces `sensor_msgs/JointState.msg`, `geometry_msgs/PoseStamped|Quaternion.msg` — 高
- OXE/RLDS: google-deepmind/open_x_embodiment README — 高
- glTF 2.0 skinning (Khronos) — 高(知识); FBX (Autodesk) — 中(知识)

---

## 关键结论 (供 BP 第6章 + V7 v2 设计引用)
1. **四元数分量顺序 w-first/w-last 不通用**, 是最高频静默损坏点; v2 帧头 `caps` 必须声明并 swap。【高】
2. **canonical = 20 旋转关节** (⊃MANO-16, =Noitom Axis-20, =OpenXR去派生), 是无损 ingest 专业手套的最小完整集; **21 MediaPipe 由 FK 派生** → 调和 D10 (P0 待签核)。
3. **v1 保持不变; v2 = capability-flagged TLV 变长帧**, version-gate 向后兼容; Lite ~82B, Pro/ingested ~166–246B。
4. **主流 VLA (OXE/RLDS) 无逐关节手、无力/触觉** — EgoGlove `force[5]`/`contact[5]` 是稀缺资产, 印证 research_3 的"力字段无处安放→推动 schema 扩展"卡位。
5. **MANO 是唯一被生态公认的 canonical 手模型**, 无厂商以之为互换 → Hand Token 作"ingest 各厂骨架 / export MANO"枢纽有结构性优势; 但 MANO 非商用许可须在 BP 计入。
6. **D12 生态对齐**: EgoGlove = 开放 Hand Motion Infrastructure (非 Hi5/Manus/mHand 竞品; 厂商手套=外部源/适配器), 锚定 MANO/FreeMoCap/OpenXR/ROS2·DexRetargeting/egocentric 数据集。FreeMoCap / DexRetargeting / 关键点数据集吃**位置** → 经 FK 派生 21 对接; MANO 类数据集经 ⊃MANO-16 对齐。【中/待核实, 见 §E】
