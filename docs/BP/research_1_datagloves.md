# 竞品研究 (1/5) — 数据手套/MOCAP手套竞品

> 来源: 并行研究Agent, 2026-07-23 (§一~三); 深度惯性/非惯性研究 2026-07-26 (§四~六)。数值来自官方产品页/SDK 文档/GitHub, 未公开项标注, 未编造。
> **配套**: 数据格式/骨架互操作见 `research_5_data_formats_interop.md` (BVH/MANO/OpenXR/Hi5/mHand/Manus wire schema + Hand Token v2 枢纽设计)。

## 一、商用数据手套/MOCAP手套矩阵

| 产品 | 定位 | 传感器方案 | DoF/关节 | 采样率/延迟 | 精度 | 力反馈/触觉 | 接口 | 价格 | 开/闭源 | 用户 | EchoGlove空白点 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Manus Metagloves Pro | 企业/科研动捕, 机器人遥操, 具身AI数据 | 电磁场(EMF)追踪(非IMU/flex/光学), 无遮挡无漂移 | 25 DoF(解剖学全手) | 未公开(仅称最低延迟) | 定性"毫米级"无数值 | 仅Pro Haptic变体有触觉; 标准版无 | Manus Core3.0+SDK; Unity/Unreal/OpenXR/SteamVR/ROS2/Maya/MotionBuilder/Blender/OptiTrack/Xsens | Pro€4,500; Pro Haptic€4,500; Legacy Quantum€2,500 | 闭源 | 企业/科研 | 价格高; 无数据平台; 消费级缺位; 触觉仅高端变体 |
| SenseGlove Nova 2 | VR力反馈手套, 企业训练/虚拟原型/遥机器人 | 线缆伸缩弯曲(4指屈伸+拇指外展), 小指不追踪; 外部CV追踪 | 未公开(5路,4指) | 力反馈≤100Hz; 采样/延迟未公开(R1 1kHz外部) | 未公开(R1称毫米级) | 有,三合一:磁摩擦刹车4×≤20N/指+掌部主动压力带+拇食指音圈振动 | C#/C++ API, Unity, Unreal4; ROS/OpenXR/Python未公开 | Nova2 €6,299; 小批量€3,999; 学术折扣20% | API部分开源, 硬件闭源 | 企业/科研 | 小指不追踪; 缺数据集/平台; ROS/OpenXR缺位; 价位偏高 |
| HaptX Gloves G1 | 高端触觉手套, 企业VR训练/遥操/设计 | 专利磁式动捕+微流控触觉执行器 | 36 DoF/单手 | 追踪"无可感延迟"(无Hz/ms); 力反馈启用23ms | 0.3mm RMS位置分辨率 | 有,强:微流控阻力+振动; ≤178N/手, ≤35.6N/指, 135触觉执行器/手, 1.5mm触觉位移, 62kPa峰值, 刺激~75%手部受体 | HaptX SDK(Unity/Unreal), C++ API, ROS1&2; OpenXR未提 | 未公开(直销订阅; 2020报道G1开发套件~$5,000/双非官方) | 闭源(SDK对客户免费但专有) | 企业/科研 | 纯高端无消费级; 重且需外接; 无数据平台; 价格不透明 |
| CyberGlove III | 经典数据手套, 动捕/动画/人因 | 专利HyperSensor弯曲/flex+Active Palm Arch; 无IMU/无力 | 18或22传感器(DoF未明) | SD卡≤100Hz; USB/WiFi≤120Hz | 分辨率<1°; 重复性3°; 线性度≤0.6%SD | 无(纯输入; 触觉由CyberTouch/CyberGrasp承担) | VirtualHand SDK(C++); WiFi/USB/microSD; Unity/Unreal/ROS/OpenXR未公开 | 未公开(询价) | 闭源(专利) | 企业/科研 | 老旧SDK(官方OS仍列Win XP/Vista); 无现代引擎原生插件; 无数据平台; 无开源 |
| Rokoko Smartgloves II | 手指动捕, 动画/VR/AR/机器人/AI训练数据 | IMU(加速度+陀螺+磁力计)+可选Coil Pro EMF | 输出位姿39 DoF(Coil Pro 45); 骨骼25+ | IMU采样250Hz; 输出83.33Hz; 磁力计83.33Hz; 延迟未公开(称低延迟) | 定性"毫米精度"无数值 | 无 | Rokoko Studio+SDK; Unity/Unreal/Blender/Maya/ROS/OptiTrack/Qualisys/MOVIN; OpenXR未公开 | ¥375,000 JPY/双(约$2,500); USD未公开 | 闭源 | 企业/科研/专业半消费 | 无触觉; 无数据集产品化; OpenXR缺位; 价格中等 |
| Noitom 诺亦腾 PN3/PN Studio | 国产动捕, 动画/虚拟制作/生物力学/机器人科研 | IMU 9轴(PN3最多27传感器全身+手指; Studio弹性织物嵌入式IMU) | 手指关节DoF未公开(仅总传感器数) | PN3: 计算600Hz/输出60Hz/延迟<20ms; Studio: 100Hz/100Hz | PN3静态Roll1°/Pitch1°/Yaw2°; Studio Roll/Pitch0.7°/Yaw2.0°; 最小分辨率0.02° | 无 | Axis Studio(专有); Unity/Unreal/ROS/OpenXR未公开 | 未公开(询价400-107-8298) | 闭源 | 企业/科研/专业半消费 | 手指DoF不透明; 引擎插件不公开; 无数据平台; 价格不透明 |
| StretchSense | 柔性电容拉伸传感手套, 机器人AI/XR训练/游戏 | 专利超薄柔性电容拉伸传感器嵌入织物(无摄像头, 接触/自遮挡下可用) | 32传感器/手; "22+ DoF毫米精度"; 原生6DoF空间追踪 | 120Hz; 端到端延迟<10ms(设备端处理) | 0.6%追踪精度(营销页) | 无 | "APIs和SDKs", 平台无关, 设备端ML; ROS/Unity/Unreal/OpenXR未公开 | $895/双(预购消费价); 企业批量询价 | 闭源(专利) | 企业+消费 | 无触觉; SDK细节不透明; 无开源; 无数据集平台 |
| LucidVR/lucidgloves+opengloves-driver | DIY VR触觉手套, VR爱好者/创客 | 电位器+线轴张力机构(非flex/IMU); Proto4加伺服力反馈 | ~5指屈伸(5卷扬/张力器), DoF未明 | 未公开 | 未公开 | 有(Proto4: 5×9g舵机MG90S/SG90主动腱索力反馈) | SteamVR/OpenVR驱动(C++); 通讯:蓝牙串口(ESP32)/Named Pipes/串口USB; 无ROS/Unity/Unreal/OpenXR原生 | DIY BOM ~$60/双(目标价, 无逐件报价) | 开源MIT(2.4k★) | DIY/消费创客 | 无精度/延迟数据; 无数据平台; 仅VR输入; 工程化/产品化弱 |
| bHaptics TactGlove DK3 | 手部触觉手套, XR训练/医疗/国防/社交VR/HCI科研 | 无内置追踪, 依赖外部摄像头(如Quest3) | 未公开(追踪外部) | 延迟<20ms; 采样率未公开 | 未公开 | 有:7×高清LRA+1×高保真VCM(TITAN)/手; 8触觉点/手(16/双) | BLE5.0; SDK: Unity/Unreal/Python/JavaScript/Android | ¥54,900 | 闭源硬件 | 企业 | 纯触觉无传感/动捕; 价格高; 无数据平台 |

## 二、GitHub开源手套项目矩阵

| 仓库 | 目标 | 传感器 | MCU | DoF | 领域 | 接口 | 精度/延迟 | License | 空白点 |
|---|---|---|---|---|---|---|---|---|---|
| LucidVR/lucidgloves | DIY VR触觉手套+SteamVR | 电位器(线轴张力)+伺服力反馈 | Arduino Nano/ESP32 | ~5指(未明) | VR | 串口/BLE串口+opengloves-driver | 未公开 | MIT(2.4k★) | 无精度数据; 无数据平台; 工程化弱 |
| LucidVR/opengloves-driver | SteamVR/OpenVR驱动, 支持全指+splay+力反馈 | 硬件无关(驱动侧) | — | 全指+splay+逐关节 | VR | BT串口/Named Pipes/USB; SteamVR | 未公开 | MIT(518★) | 仅驱动层, 无硬件标准化 |
| farhanfuadabir/ASL-DataGlove | ESP32 ASL字母+词识别(14静态+3动态) | 5×flex+MPU6050(6轴IMU) | ESP32 | 11路(5flex+6IMU) | ASL | 串口(Pyserial)→Processing GUI; CSV录制 | 未公开 | MIT | 仅ASL; 无产品化; 无云端/平台 |
| Redgerd/Smart-Glove-Sign-Language-Predictor | ASL→文本+语音, 听障沟通 | 5×flex+MPU6050(6轴IMU) | Arduino Nano | 11路(5flex+6IMU) | ASL | BT→Flutter App+FastAPI后端; TTS | 准确率97%/精度98%/召回97%/F1 98%(~1.4万样本,80/20,3折CV) | 公开 | 仅ASL静态+少量动态; 无多模态; 无硬件产品化 |
| isurusasangaetam/Hand-Tracking-Glove | 实时动捕, VR/AR交互/手势识别 | MPU9250(9轴IMU)/指+掌, TCA9548A I2C多路 | ESP32 NodeMCU | 未公开(每MPU9250 9DoF) | VR/AR+手势 | Unity C#+Arduino .ino; I2C多路 | 未公开 | CC-BY-NC-4.0(7★) | 非商用许可; 无精度; 原型级 |
| ReikiC/CASA0018-Gloves-Edge-AI | 手语→文本 边缘ML(6手势) | 5×flex+LSM9DS1(9轴IMU) | Arduino Nano 33 BLE | 9轴IMU+5flex; 系统DoF未公开 | 手语识别(课程项目) | LCD2004 I2C显示; 串口115200 | 采样50Hz; 推理300ms; LCD200ms; 置信阈值0.60; 准确率未公开 | 学术开源 | 课程原型; 手势少; 无产品化 |
| weibayang/rehabilitation_glove | 便携软包康复手套, 闭环精细动作恢复 | 角度传感器(LED标定)+SMA形状记忆合金驱动 | STM32F407ZET6 | 未公开 | 手康复 | MATLAB GUI调试/采集; ST-Link/J-Link | 未公开; SMA经1万次循环验证 | MIT | 仅康复; 无多模态; 无数据平台; 精度未公开 |

## 三、EchoGlove相对空白点小结

基于9款商用+7款开源硬数据, 竞品格局空白:

1. **价格带断层, 中端消费级缺位**: 高端(HaptX/Manus/SenseGlove/bHaptics €4,500/$5,000+/¥54,900/询价)纯企业; 低端(LucidVR $60 DIY/StretchSense $895)工程化弱或偏高无触觉。**$200-800区间成品化+精度承诺消费级几乎无人占据**——EchoGlove定价此处填补最大空白。

2. **多模态融合普遍弱项**: 商用多单一传感(Manus=EMF, Rokoko/Noitom=IMU, CyberGlove=flex, StretchSense=电容, SenseGlove=线缆); 几乎无"flex+IMU+压力+触觉"多模态融合成品。开源ASL类多用"5flex+1IMU"基础组合。**EchoGlove做flex+IMU+压力(抓握力)+触觉多模态融合, 数据丰富度直接领先**。

3. **数据平台/数据集产品化几乎为零**: 所有竞品"卖硬件+SDK", 无一家把"采集→标注→训练数据集→模型评估"作产品闭环。ASL开源数据散落未平台化。**这是EchoGlove"硬件+数据平台"双轮驱动最大蓝海, 面向WRC/具身AI训练数据市场**。

4. **精度与延迟数据不透明**: Manus/SenseGlove/Rokoko/Noitom无数值化精度(仅定性毫米级)或延迟(仅Noitom PN3<20ms/StretchSense<10ms/bHaptics<20ms公开)。开源普遍无精度/延迟。**EchoGlove公开可复现精度/延迟基准即形成可信硬指标差**。

5. **引擎/生态接口碎片化**: OpenXR仅Manus明确支持; ROS仅HaptX/Manus/Rokoko明确。**EchoGlove同时提供Unity/Unreal/ROS/OpenXR/Python五件套即覆盖面超多数竞品**。

6. **应用场景单一**: 商用锁VR训练/动捕/遥操; 开源锁ASL或单点康复。**无一同时覆盖手势识别+康复+VR/MR+机器人遥操+数据采集多场景——EchoGlove多场景定位独有**。

7. **触觉反馈与传感分离**: 有触觉的(HaptX/SenseGlove/bHaptics/LucidVR)多纯输出或高价; 有传感的(CyberGlove/Rokoko/Noitom/StretchSense)多无触觉。**"传感+触觉"一体化中价位产品空白明显**。

8. **国产化与供应链**: Noitom虽国产但价格不透明/闭源/无数据平台; 其余均海外。**EchoGlove国产+开源+数据平台定位, 在京东/WRC/国产替代语境下无直接对手**。

## 四、惯性/混合/磁传感手套深度矩阵 (2026-07-26 深度研究)

> 来源: 深度研究Agent, 2026-07-26。经 headless 浏览器抓官方 SDK 文档/spec 页/经销商页 (sdk.rokoko.com, github.com/pnmocap/MocapApi, manus-meta.com/products/compare-gloves, Noitom, Virdyn gzvirdyn.com)。**关键发现: "每指节 9轴 IMU + AHRS" 的心智模型只对部分产品成立** —— 仅 Noitom (Hi5/PN Studio) 与 Virdyn (mHand/mHand Pro) 是纯惯性; Rokoko/Manus 已迁离纯 IMU。

| 产品 | 传感器/手 | 轴/类型 | 位置? | 融合&标定 | 输出/骨架 | 速率 | 延迟 | 定价 | 流/格式 |
|---|---|---|---|---|---|---|---|---|---|
| **Noitom Hi5 (2.0)** | 5–6 IMU(每指) 【待核实数】 | **9轴 IMU** 【高】 | 否(需 Vive tracker) | 专有 AHRS; ~30s B-pose 【高】 | 5指骨架, 每关节 quaternion 【中】 | 500fps算/**120fps出**(v1 180) 【高】 | 待核实 | ~$1k/双, 准专业 【待核实】 | SDK C/C++/C#, Unity/Unreal, **SteamVR** 【中】 |
| **Noitom PN Studio Gloves** | **6 IMU** 【高】 | **9轴 IMU** 【高】 | 否(属全身系统) | Noitom solver, 磁免疫 【高】 | Avatar joints, quaternion (MocapApi) 【高】 | 待核实(~120类) | "ultra-low" 待核实 | pro 附加件 【待核实】 | Axis Studio, **BVH/FBX**, UDP/TCP, MocapApi, iClone/MoBu/Unity/UE 【高】 |
| **Rokoko Smartgloves I** | 7 (5指+臂+**hub EMF**) 【高】 | **6轴 IMU + EMF** 【高】 | **是**(EMF 相对 hub; Coil Pro=绝对) 【高】 | 专有 IMU+EMF; **自动init 无手动标定** 【高】 | 每传感器朝向(命名系)→hand-solve 【中】 | **~100fps** 【中】 | 待核实 | ~$2.5k/双, 准专业 【待核实】 | **RGMP v2** UDP, Wi-Fi; Rokoko Studio; Blender/UE/Unity/Maya 【高】 |
| **Rokoko Smartgloves II** | 7 【高】 | **9轴 IMU + EMF**(加磁力计) 【高】 | **是** 【高】 | +磁力计 heading(LTP) 【高】 | 同上 + heading-reliable flags 【高】 | **250Hz** 【中】 | 待核实 | 准专业 【待核实】 | RGMP v2 UDP/**USB**, Wi-Fi 【高】 |
| **Manus Quantum Metagloves** | **5 EMF 指尖** + hand IMU 【高】 | **磁/EMF** 6-DoF 指尖 + 3轴 IMU 【高】 | **是**(绝对指尖位置) 【高】 | Hand Solver 3; **4步~50s** 标定 【高】 | **25-DoF 解剖手** (CMC/MCP/PIP/DIP; 拇指 CMC/MCP/IP); user+retarget skeleton 【高】 | **120Hz** 【高】 | **30ms 有线/50ms 无线** 【高】 | 高端 pro 【待核实】 | MANUS Core 3.0, BT5.0/USB-C, **SteamVR**, UE/Unity/MoBu, FBX 【高】 |
| **Manus Prime X / Prime 3** | ~10 flex(2/指) + 5指 IMU 【高】 | **Flex + 9-DoF IMU/指** 【高】 | 否(相对) | MANUS Core solver 【中】 | MANUS 手骨架 【中】 | ~90Hz 【待核实】 | 待核实 | ~$2–3k/双 【待核实】 | MANUS Core, SteamVR, UE/Unity/MoBu/iClone 【高】 |
| **Virdyn mHand Pro (虚拟动点)** | **16 节点** 9轴 IMU + 指关节 【中, 数待核实】 | **9轴 IMU** (每指节) 【高】 | 否(Vive/Quest/PICO tracker) 【高】 | 惯性 solver; mHand Studio 【中】 | 手骨架; UDP 数据流 【中】 | ~800Hz 声称 【待核实】 | **<30ms** 【高】 | **≈€1,550/双**, 准专业 【高】 | **UDP**, C++/C#/Linux SDK, Unity/UE4/UE5/MoBu/Maya/3DMAX; 18手势 【高】 |
| **SenseGlove Nova 2** | 1 腕 IMU + 指 flex 【高】 | **9轴腕 IMU + flex** 【高】 | 否(外部 tracker) | 朝向 IMU 【高】 | 有限 DoF 手 + 触觉 【高】 | 待核实 | 待核实 | ~$5k+, pro 触觉 【待核实】 | SenseGlove SDK, Unity/UE 【中】 |
| **Weart TouchDIVER Pro** | 指模块(拓扑待核实) | 待核实 | ~2mm 指追踪 【中】 | WEART 数字手模型 【中】 | WEART SDK 手模型 【中】 | 待核实 | 待核实 | **€3,900**, pro 触觉 【中】 | WEART SDK, Unity/UE 【中】 |
| **Movella/Xsens Prime 3** | = Manus Prime 3 (rebrand) 【高】 | Flex + IMU 【高】 | 否 | MANUS/Xsens 【高】 | Xsens body + Manus hand 【高】 | ~90Hz 【待核实】 | 待核实 | pro 【待核实】 | MVN/BVH/FBX + MANUS Core 【高】 |

**关键洞察 (对 EgoGlove 兼容策略)**:
1. **市场已分叉**: 纯惯性 (Noitom/Virdyn, 只出朝向, 位置需外部 tracker) vs 位置承载磁/混合 (Manus Quantum 绝对指尖位置、Rokoko EMF 相对 hub)。**通用格式不能只是"每关节四元数"** —— 必须把 position 作一等可选通道 (详见 research_5 §8/§A)。
2. **用户点名的三家**: **mHand Pro=纯9轴IMU每指节** (最贴合原始心智模型), **Hi5=纯9轴IMU每指**, **Rokoko=IMU+EMF混合** (非纯IMU)。兼容三者需同时承载 quaternion 骨架 + 可选 position/fingertip。
3. **Noitom Axis 每手 20 关节拓扑 = Hand Token v2 canonical-20 的最佳结构匹配** (近 1:1, 见 research_5 §B); mHand 走 BVH 导出可 ingest。
4. **BVH/FBX 是这些厂商的公共导出格式** (Noitom/Rokoko/mHand/Xsens 皆导 BVH) —— EgoGlove 支持 BVH ingest 即打通大半互操作。

## 五、传感原理横向对比 (非惯性 vs IMU) (2026-07-26)

> 来源: 深度研究Agent, 2026-07-26 (本会话 WebFetch 间歇性中断, 物理原理级标 高, 时效/数值项标 待核实; 唯一实时核实项: bendlabs.com → nitto.com/nbt 301 重定向, Bend Labs 现属 Nitto)。完整版见 research_5 配套与本节。

| 模态 | 核心原理 | 每关节3D朝向? | 外展? | 绝对位姿? | 力? | 漂移/迟滞 | 成本 | 量产一致性 | 原生输出 |
|---|---|---|---|---|---|---|---|---|---|
| **IMU 阵列**(基线) | 陀螺/加速/磁融合→每段朝向 | **是** | **是** | 朝向是; **位置否**(需外援) | 否 | 陀螺/yaw漂移; 磁需标定 | 低单件/**中系统** | 好(装配是变量) | **每关节四元数(骨架)** |
| **Flex 电阻(Spectra)** | 碳墨 R∝曲率 | 否 | 需额外传感 | 否 | 否 | **高**迟滞/漂移/老化 | **低** | **差**(逐件标定) | **标量弯曲/指** |
| **Flex(Bend Labs/Nitto)** | 软**电容**角位移 | 否(每传感角) | 2轴:部分 | 否 | 否 | **低**迟滞/漂移 | 中 | 好 | 标量**角**(1-2轴) |
| **电容拉伸(StretchSense)** | 硅胶电容 C∝应变 | 否(多通道标量) | **是** | 否(需 tracker) | 否(运动学手套) | 蠕变/迟滞(粘弹) 中 | **中高** | 中 | **多通道 curl+splay** |
| **液态金属(EGaIn/Galinstan)** | 微流道 R∝几何(应变) | 否 | 是(若布线) | 否 | **是**(压力几何) | 氧化层漂移; 泄漏/老化 | 研究级; 材料廉 | **差**(制造受限) | **标量应变(或压力)** |
| **磁-flex(Manus Quantum)** | 指尖磁体+磁强计解算 | 指尖位姿(非每关节quat) | **是** | 朝向靠IMU; **位置需tracker** | 否 | 无机械漂移; **金属畸变** | 中高 | 好(pro产品) | **指尖位置+flex/splay** |
| **EM 追踪(Polhemus/NDI)** | AC/脉冲DC场+线圈→6DoF | **是**(每传感) | 是(密集) | **是—全6DoF** | 否 | 无漂移; **金属畸变** | **高** | 精密(非消费) | **绝对6DoF/传感** |
| **压阻/压电力(FSR/PVDF/cap)** | R/C/电荷∝法向(±剪切)力 | **否**(非运动学) | 否 | 否 | **是**(要点) | FSR高; cap低; PVDF仅动态 | 低→高 | FSR/PVDF可量产; 阵列难 | **力/压力(±剪切),接触** |
| **sEMG(Meta/CTRL-labs)** | 肌肉MUAP→ML解码 | 仅推断 | 推断 | 否 | **是**(意图,含等长力) | 非平稳; 逐会话标定 | 中(数据=护城河) | HW一致; 模型负担 | **解码意图/控制(原始EMG)** |

**选型结论 (对 EchoGlove Lite/Pro)**:
- **Lite (flex+单IMU)**: 测得 `curl`(每指flex, MCP+PIP常被合并) + `root`朝向(单IMU 3-DoF, yaw漂移, 无位置); `skeleton`/`fingertip`/`splay`/`force` 为**模型推断或空** —— 印证 D10 "IK/ML 估计 21 关节" 的必要性。
- **Pro (eSkin+力)**: 更密 `curl`(+可能 `splay`) + **`contact_force` (差异化护城河)**; 绝对腕位置仍需外部(光学/EM/UWB)。
- **Bend Labs 现属 Nitto** (电容角传感, 低迟滞), 是 Lite flex 升级候选; **液态金属**兼具应变+压力但量产一致性差、gallium 腐蚀铝互连, 属 🔬 需研发验证; **磁感应/Hall** 适合拇指对掌高精度绝对角 (呼应 research_4 §柔性传感选型)。
- **PVDF 压电**只测动态不测静态, 做接触/滑移事件补充; **sEMG** 输出意图非几何, 不适合直接填几何格式, 格式先行策略下延后 (呼应 STRATEGY 传感器升级排序)。

## 数据可信度说明
所有数值来自官方产品页/SDK文档/GitHub README(2026-07-23 及 2026-07-26 抓取), 未公开项标注 待核实, 未编造。HaptX $5,000/LucidVR $60/SenseGlove €3,999-6,299/Rokoko ¥375,000 JPY/StretchSense $895/bHaptics ¥54,900为少数公开价格; Manus/Noitom/CyberGlove价格不透明, BP引用建议注明"询价/订阅制"。
