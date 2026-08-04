# Graph Report - EgoGlove  (2026-08-04)

## Corpus Check
- 39 files · ~164,192 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 1207 nodes · 1514 edges · 49 communities
- Extraction: 98% EXTRACTED · 2% INFERRED · 0% AMBIGUOUS · INFERRED: 34 edges (avg confidence: 0.7)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `757f3ccd`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- lsm6dsv16x.md
- test_hand_token.py
- Chapter 4
- hand_token.c
- EchoGlove 产业级商业计划书 V2.0
- 竞品研究 (5/5) — 手部数据/骨架格式与流协议互操作
- 任务2: 连续手语识别(SLR) SOTA
- Hand Token v2 — Skeleton Layer 互操作协议设计 (Design Spec)
- 寿命终止开发板
- ESP32-S3-LCD-EV-Board
- 寿命终止开发板
- ESP32-S3-DevKitC-1
- ESP32-S3-USB-OTG
- EchoGlove V7.0 — 双表示层详解 (D3 核心壁垒)
- EchoGlove V7.0 — 主规格书 (SOP-SPEC-PLAN)
- ESP32-P4X-Function-EV-Board
- ESP32-P4X-EYE
- gen_docx.py
- Claude Code Configuration Consolidation Design
- EchoGlove V7 — 系统架构 (ARCHITECTURE)
- EchoGlove V7 — 战略决策冻结书 (STRATEGY)
- Disabled-Then-Archived Plugin Candidates
- EchoGlove V7.0 — 接线图
- gen_figures.py
- 三、EchoGlove定位小结
- File Map
- EgoGlove — Claude Code 项目指南
- esp-dev-kits-zh_CN-master-esp32p4.md
- EchoGlove V7.0 — System Architecture Diagrams
- EgoGlove
- EchoGlove V7.0 — 决策记录与真实性分级
- hand_skeleton_fk21
- E C H O G L O V E
- 六、竞争分析
- 竞品研究 (1/5) — 数据手套/MOCAP手套竞品
- 竞品研究 (2/5) — 视觉手部追踪方案 (纯 CV 路线)
- Global Constraints
- Global Constraints
- EchoGlove V7.0 — Claude Code 实现提示词
- EchoGlove V7.0 — BOM 表
- 三、产品体系与技术架构
- 四、核心竞争力与壁垒
- EchoGlove V7.0 — 设计文档包
- 二、市场机会与行业趋势
- 五、商业模式与收入结构
- 八、融资需求与产业合作价值
- 十、风险分析与应对策略
- 七、研发路线图与里程碑
- 九、团队与组织

## God Nodes (most connected - your core abstractions)
1. `Chapter 4` - 35 edges
2. `寿命终止开发板` - 26 edges
3. `ESP32-S3-LCD-EV-Board` - 24 edges
4. `寿命终止开发板` - 22 edges
5. `serialize_v2()` - 21 edges
6. `parse_v2()` - 20 edges
7. `ESP32-S3-DevKitC-1` - 20 edges
8. `ESP32-S3-USB-OTG` - 20 edges
9. `main()` - 19 edges
10. `openxr_to_hand_token()` - 18 edges

## Surprising Connections (you probably didn't know these)
- `main()` --calls--> `hand_skeleton_fk21()`  [INFERRED]
  firmware/shared/test/test_hand_token.c → firmware/shared/hand_skeleton.c
- `main()` --calls--> `hand_token_make_device_id()`  [INFERRED]
  firmware/shared/test/test_hand_token.c → firmware/shared/hand_token.c
- `main()` --calls--> `hand_token_split_device_id()`  [INFERRED]
  firmware/shared/test/test_hand_token.c → firmware/shared/hand_token.c
- `main()` --calls--> `hand_token_crc16()`  [INFERRED]
  firmware/shared/test/test_hand_token.c → firmware/shared/hand_token.c
- `refresh_v2_crc()` --calls--> `hand_token_crc16()`  [INFERRED]
  firmware/shared/test/test_hand_token.c → firmware/shared/hand_token.c

## Import Cycles
- None detected.

## Communities (49 total, 0 thin omitted)

### Community 0 - "lsm6dsv16x.md"
Cohesion: 0.00
Nodes (422): 11.11, 11.12 SPI2_CTRL1_OIS (70h), 11.13, 11.14, 11.1 SPI2_WHO_AM_I (0Fh), 11.2 SPI2_STATUS_REG_OIS (1Eh), 11.4, 11 SPI2 register description (+414 more)

### Community 1 - "test_hand_token.py"
Cohesion: 0.08
Nodes (87): IntEnum, _canonical_quat(), crc16_modbus(), _f16(), _f16_bits(), _f32(), fk21(), HandSkeleton (+79 more)

### Community 2 - "Chapter 4"
Cohesion: 0.04
Nodes (45): 3. 通过 电池供电, 3. 通过 电池供电, 4.1.1 入门指南, 4.1.2 硬件参考, 4.1.3 硬件版本, 4.1.4 相关文档, 4.1 ESP-VoCat v1.2, 5.1.1 入门指南 (+37 more)

### Community 3 - "hand_token.c"
Cohesion: 0.13
Nodes (41): hand_skeleton_t, hand_token_t, finite_f16(), get_f16(), get_f32(), get_u16(), get_u32(), hand_token_crc16() (+33 more)

### Community 4 - "EchoGlove 产业级商业计划书 V2.0"
Cohesion: 0.05
Nodes (38): 2.1 Physical AI 成为下一阶段AI基础设施, 2.2 "手"是具身智能关键入口, 2.3 三大目标市场, 2.4 竞争空白(详见第6章), 3.1 双产品线, 3.2 双表示层 (核心壁垒, D3), 3.3 Pro视觉接口 (D9 双生态兼容), 3.4 硬件资产复用判断 (+30 more)

### Community 5 - "竞品研究 (5/5) — 手部数据/骨架格式与流协议互操作"
Cohesion: 0.06
Nodes (32): 0. 贯穿性事实 — 四元数分量顺序不通用 (最高频静默损坏点), 1. BVH (Biovision Hierarchy) — 动捕通用语 【高】, 2. FBX / glTF 2.0 / VRM humanoid, 3. MANO / SMPL-X hand 【高】, 4. OpenXR hand tracking + SteamVR Skeletal Input 【高】, 5.1 Rokoko Studio Live 【高】 (核对官方 `Rokoko/rokoko-studio-live-blender` 源), 5.2 Manus Core / MANUS SDK 【高】 (核对 `ManusSDKTypes.h` + `etaoxing/manus_glove/_enums.py`; 类型经社区镜像, enum 值为 Manus canonical), 5.3 Noitom Axis Studio / Hi5 SDK 【高】 (核对官方 `pnmocap/MocapApi.h`) (+24 more)

### Community 6 - "任务2: 连续手语识别(SLR) SOTA"
Cohesion: 0.06
Nodes (30): 1.1 MANO (MPI-IS), 1.2 SMPL-X (MPI-IS), 1.3 smplx仓库 (vchoutas/smplx), 1.4 MS-MANO (CVPR 2024), 1.5 manopth (hassony2/manopth), 2.1 CorrNet (CVPR 2023), 2.2 CorrNet+ (hulianyuyy/CorrNet_Plus), 2.3 DSTA-SLR (hulianyuyy, COLING 2024) (+22 more)

### Community 7 - "Hand Token v2 — Skeleton Layer 互操作协议设计 (Design Spec)"
Cohesion: 0.07
Nodes (26): 10. 签核清单 (P0), 1. 动机与背景, 2.1 目标（本 spec 范围内）, 2.2 非目标（本 spec 明确不做，YAGNI）, 2. 目标与非目标, 3.1 关节集 + 层级 (parent → child), 3.2 为何选 20（研究结论，research_5 §A）, 3.3 旋转约定（逐项明确声明，避免歧义） (+18 more)

### Community 8 - "寿命终止开发板"
Cohesion: 0.08
Nodes (26): 1.54 INCH LCD:, 3.1.1 ESP32-P4-Function-EV-Board v1.5.2, 3.1 ESP32-P4-Function-EV-Board, 3.2.1 ESP32-P4-EYE, 3.2 ESP32-P4-EYE, ESP32-P4-Function-EV-Board v1.4, J1, J1 (+18 more)

### Community 9 - "ESP32-S3-LCD-EV-Board"
Cohesion: 0.08
Nodes (24): 3.1.1 开发板概述, 3.1.2 应用程序开发, 3.1.3 硬件参考, 3.1.4 硬件版本, 3.1.5 样品获取, 3.1.6 相关文档, 3.1 ESP32-S3-LCD-EV-Board v1.5, AEC 电路 (+16 more)

### Community 10 - "寿命终止开发板"
Cohesion: 0.09
Nodes (22): 6.1.1 ESP32-S3-DevKitM-1, 6.1 ESP32-S3-DevKitM-1, 6.2.1 ESP32-S3-USB-Bridge, 6.2 ESP32-S3-USB-Bridge, 供电说明, 入门指南, 内含组件和包装, 备注: (+14 more)

### Community 11 - "ESP32-S3-DevKitC-1"
Cohesion: 0.10
Nodes (20): 1.1.1 入门指南, 1.1.2 硬件参考, 1.1.3 硬件版本, 1.1.4 相关文档, 1.1 ESP32-S3-DevKitC-1 v1.1, ESP32-S3-DevKitC-1, 内含组件和包装, 内含组件和包装 (+12 more)

### Community 12 - "ESP32-S3-USB-OTG"
Cohesion: 0.10
Nodes (20): 2.1.1 快速入门, 2.1.2 硬件参考, 2.1.3 相关文档, 2.1 ESP32-S3-USB-OTG, • 500 mA 限流电路, ESP32-S3-USB-OTG, GPIO 分配, LCD 接口 (+12 more)

### Community 13 - "EchoGlove V7.0 — 双表示层详解 (D3 核心壁垒)"
Cohesion: 0.10
Nodes (19): 1.1 字段表 (数据可用性视角), 1.2 二进制帧 (Hand Token v1 · 定长 79 字节 · 小端), 1. Hand Token 规范, 1b.1 canonical 骨架 = 20 旋转关节 (D11), 1b.2 v2 二进制帧 (capability-flagged TLV 变长, version 0x02, 待实现), 1b.3 双向映射 (ingest / export), 1b. Hand Token v2 — Skeleton Layer 互操作层 (D11 冻结, 代码待实现 🟡), 2. MANO Layer 映射 (+11 more)

### Community 14 - "EchoGlove V7.0 — 主规格书 (SOP-SPEC-PLAN)"
Cohesion: 0.11
Nodes (18): 10. 风险, 11. 兼容矩阵, 1. 系统总览, 2.1 Lite, 2.2 Pro, 2. 硬件规格, 3.1 共享 (`firmware/shared/`), 3.2 Lite (`firmware/lite/`, PlatformIO) (+10 more)

### Community 15 - "ESP32-P4X-Function-EV-Board"
Cohesion: 0.12
Nodes (17): 1.1.1 入门指南, 1.1.2 硬件参考, 1.1.3 硬件版本, 1.1.4 相关文档, 1.1 ESP32-P4X-Function-EV-Board, ESP32-P4X-Function-EV-Board, J1, Strip (+9 more)

### Community 16 - "ESP32-P4X-EYE"
Cohesion: 0.12
Nodes (17): 1.54 INCH LCD:, 2.1.1 入门指南, 2.1.2 硬件参考, 2.1.3 硬件版本, 2.1.4 相关文档, 2.1 ESP32-P4X-EYE, ESP32-P4X-EYE, USB HighSpeed & Power in: (+9 more)

### Community 17 - "gen_docx.py"
Cohesion: 0.31
Nodes (15): add_header_footer(), add_heading(), add_image(), add_page_break(), add_para(), add_table(), add_toc(), build_body() (+7 more)

### Community 18 - "Claude Code Configuration Consolidation Design"
Cohesion: 0.12
Nodes (15): Candidates to disable from the enabled default plugin set, Claude Code Configuration Consolidation Design, In scope, Instruction consolidation, Memory consolidation, Objective, Out of scope, Release gates (+7 more)

### Community 19 - "EchoGlove V7 — 系统架构 (ARCHITECTURE)"
Cohesion: 0.12
Nodes (15): 1. 设计原则, 2.1 EchoGlove Lite（消费 / 教育 / XR / 手语入口）, 2.2 EchoGlove Pro（具身智能数据入口）, 2. 双产品线硬件架构, 3. 双表示层数据流（核心，D3）, 4.1 Lite（BLE/WiFi 为主）, 4.2 Pro（双生态，D9）, 4.3 历史通信栈（V6，archive 参考） (+7 more)

### Community 20 - "EchoGlove V7 — 战略决策冻结书 (STRATEGY)"
Cohesion: 0.13
Nodes (14): 0. 公司主航道, 1. 冻结决策 D1–D12, 2. 核心壁垒：双表示层架构 (D3), 3. 五层壁垒体系, 4. 双产品线 (D6), 5. 数据战略 (D5)：Open Core + Commercial Data Asset, 6. GPT5.6 精华（认可并保留）, 7. GPT5.6 糟粕 / 代码现实修正（GPT 没读代码导致） (+6 more)

### Community 21 - "Disabled-Then-Archived Plugin Candidates"
Cohesion: 0.15
Nodes (12): Claude Configuration Consolidation Implementation Plan, Disabled-Then-Archived Plugin Candidates, File Map, Global Constraints, Retained Enabled Plugins, Task 1: Create the reversible archive and baseline manifest, Task 2: Disable unused plugins while retaining V7 capability baseline, Task 3: Consolidate instruction layers and historical V6 entry point (+4 more)

### Community 22 - "EchoGlove V7.0 — 接线图"
Cohesion: 0.15
Nodes (12): 1.1 IMU: LSM6DSV16X (breakout, I²C) 🟡, 1.2 Flex: 5× 内部 ADC1 ✅, 1.3 通信, 1. EchoGlove Lite 接线 (ESP32-S3), 2.1 传感器, 2.2 双生态通信 (D9), 2.3 EGO Camera 接口 (预留, D7) 🌌, 2. EchoGlove Pro 接线 (ESP32-P4) 🟡/🔬 (+4 more)

### Community 23 - "gen_figures.py"
Cohesion: 0.38
Nodes (10): fig_bom_cost(), fig_competitive_radar(), fig_dual_rep_layer(), fig_force_gap_matrix(), fig_funding_use(), fig_market_size(), fig_price_band(), fig_roadmap_gantt() (+2 more)

### Community 24 - "三、EchoGlove定位小结"
Cohesion: 0.18
Nodes (10): BP用一句话定位, D12 生态桥接 — dex-retargeting/AnyTeleop = 下游 retarget 目标 (非竞品), 一、遥操作/数据采集平台横向对比, 三、EchoGlove定位小结, 二、算法栈(主流遥操作/VLA范式), 关键交叉发现, 来源, 相比UMI/ALOHA的优势 (+2 more)

### Community 25 - "File Map"
Cohesion: 0.18
Nodes (10): File Map, Global Constraints, Hand Token v2 P0 Protocol Implementation Plan, Self-Review, Task 1: Canonical Skeleton Contract and FK, Task 2: C v2 Lite Codec and Version Gate, Task 3: C Skeleton TLV Codec and Validation, Task 4: Python v2 Mirror and FK (+2 more)

### Community 26 - "EgoGlove — Claude Code 项目指南"
Cohesion: 0.20
Nodes (9): EgoGlove — Claude Code 项目指南, 仓库结构, 分支与提交, 历史与记忆, 唯一真相源, 工作纪律, 开发与验证, 真实性与技术约束 (+1 more)

### Community 27 - "esp-dev-kits-zh_CN-master-esp32p4.md"
Cohesion: 0.20
Nodes (9): 4.1 开发者社区, 4.2 产品, 4.3 联系我们, Chapter 3, Chapter 4, Chapter 5, Table of contents, 免责声明和版权公告 (+1 more)

### Community 28 - "EchoGlove V7.0 — System Architecture Diagrams"
Cohesion: 0.20
Nodes (9): 1. System Architecture Overview — 双产品线, 2. Dual-Representation Data Flow (核心, D3), 3.1 Lite, 3.2 Pro, 3.3 历史栈 (V6, archive 参考), 3. Communication Stack (双生态, D9), 4. Three-Tier Inference (诚实分工), 5. Repository Layout (+1 more)

### Community 29 - "EgoGlove"
Cohesion: 0.20
Nodes (9): EgoGlove, License, 仓库结构, 分支策略, 历史仓库迁移, 双产品线, 文档, 核心壁垒：双表示层架构 (+1 more)

### Community 30 - "EchoGlove V7.0 — 决策记录与真实性分级"
Cohesion: 0.22
Nodes (8): 1. V6 → V7 决策记录, 2. 真实性分级定义, 3. 真实性总表 (与 ARCHITECTURE.md §8 同步), 4. 风险评估, 5. 兼容矩阵 (V7 对外), 6. GPT5.6 对话修正点 (糟粕→修正), 7. 审批状态, EchoGlove V7.0 — 决策记录与真实性分级

### Community 31 - "hand_skeleton_fk21"
Cohesion: 0.36
Nodes (8): hand_skeleton_t, hand_skeleton_fk21(), normalize_quat(), quat_mul(), quat_rotate(), supported_model(), zero_vec3(), hand_skeleton_status_t

### Community 32 - "E C H O G L O V E"
Cohesion: 0.25
Nodes (7): E C H O G L O V E, 一、项目执行摘要, 产业级商业计划书 V2.1, 战略冻结点索引, 目录, 附录: 真实性分级说明, 面向具身智能时代 · 人体手部数据采集与人机交互基础设施

### Community 33 - "六、竞争分析"
Cohesion: 0.25
Nodes (8): 6.1 竞争格局总览, 6.2 专业数据手套 (商用), 6.3 视觉手部追踪 (纯CV), 6.4 机器人数据采集平台 (EchoGlove主航道竞争区), 6.5 竞争空白综合判断 (EchoGlove切入逻辑), 6.6 学术对标 (BP技术章节可引SOTA), 6.7 EchoGlove 一句话定位, 六、竞争分析

### Community 34 - "竞品研究 (1/5) — 数据手套/MOCAP手套竞品"
Cohesion: 0.25
Nodes (7): 一、商用数据手套/MOCAP手套矩阵, 三、EchoGlove相对空白点小结, 二、GitHub开源手套项目矩阵, 五、传感原理横向对比 (非惯性 vs IMU) (2026-07-26), 四、惯性/混合/磁传感手套深度矩阵 (2026-07-26 深度研究), 数据可信度说明, 竞品研究 (1/5) — 数据手套/MOCAP手套竞品

### Community 35 - "竞品研究 (2/5) — 视觉手部追踪方案 (纯 CV 路线)"
Cohesion: 0.25
Nodes (7): 6.1 商业/平台级视觉手部追踪方案, 6.2 标准/接口层, 6.3 学术/开源融合方案, 6.4 纯CV方案普遍局限小结 (EchoGlove glove+vision融合切入逻辑), 关键来源, 投资人注意事项, 竞品研究 (2/5) — 视觉手部追踪方案 (纯 CV 路线)

### Community 36 - "Global Constraints"
Cohesion: 0.25
Nodes (7): Configuration Reduction Implementation Plan, Global Constraints, Task 1: Replace duplicated project instructions with an indexed contract, Task 2: Reduce default plugin and tool loading, Task 3: Replace accumulated project-local permissions with a minimal reversible allowlist, Task 4: Deduplicate project memory while preserving current operational state, Task 5: Run final configuration verification and document rollback

### Community 37 - "Global Constraints"
Cohesion: 0.25
Nodes (7): Global Constraints, OpenXR Ingest Adapter Implementation Plan, Task 1: Define the typed OpenXR input boundary and failing fixtures, Task 2: Implement global-pose conversion to canonical Hand Token v2, Task 3: Verify v2 serialization and FK21 compatibility, Task 4: Update narrowly scoped architecture/status documentation, Task 5: Final verification, graph update, and milestone commit/push

### Community 38 - "EchoGlove V7.0 — Claude Code 实现提示词"
Cohesion: 0.25
Nodes (7): EchoGlove V7.0 — Claude Code 实现提示词, Phase V7-RC: Pro 原型 eSkin/Force 驱动, Phase V7-α: Hand Token 规范定稿 + 协议头, Phase V7-α: Lite IMU 驱动 + Hand Token 规范 (🟡→✅), Phase V7-β: 双表示层 SDK, Phase V7-β: 连续手语 benchmark, 通用约束 (所有阶段)

### Community 39 - "EchoGlove V7.0 — BOM 表"
Cohesion: 0.29
Nodes (6): 1. EchoGlove Lite BOM（单手，<¥500 目标）, 2. EchoGlove Pro BOM（单手，企业级，目标测算 🔬）, 3. V6 → V7 成本对比, 4. 供应商与采购要点, 5. 风险, EchoGlove V7.0 — BOM 表

### Community 40 - "三、产品体系与技术架构"
Cohesion: 0.33
Nodes (6): 3.1 V6 核心硬件架构与双产品线, 3.2 双表示层架构: MANO 与 Robot 双生态原生兼容, 3.3 三级推理热切换架构, 3.4 多模态融合与V7演进方向, 3.5 硬件资产复用判断, 三、产品体系与技术架构

### Community 41 - "四、核心竞争力与壁垒"
Cohesion: 0.33
Nodes (6): 4.1 第一层: 低成本多模态硬件壁垒, 4.2 第二层: 双表示层数据标准壁垒, 4.3 第三层: 数据飞轮壁垒, 4.4 第四层: 开放生态壁垒, 4.5 第五层: 人类操作数据资产壁垒, 四、核心竞争力与壁垒

### Community 42 - "EchoGlove V7.0 — 设计文档包"
Cohesion: 0.33
Nodes (5): Document Index, EchoGlove V7.0 — 设计文档包, Quick Reference, 历史版本, 跨会话恢复上下文

### Community 43 - "二、市场机会与行业趋势"
Cohesion: 0.40
Nodes (5): 2.1 具身智能产业爆发与数据瓶颈, 2.2 目标市场规模估算, 2.3 三大目标市场, 2.4 产业趋势与技术窗口, 二、市场机会与行业趋势

### Community 44 - "五、商业模式与收入结构"
Cohesion: 0.40
Nodes (5): 5.1 四层收入架构, 5.2 Open Core + Commercial Data Asset 双轨策略, 5.3 数据飞轮, 5.4 战略边界 (不做什么), 五、商业模式与收入结构

### Community 45 - "八、融资需求与产业合作价值"
Cohesion: 0.40
Nodes (5): 8.1 融资规模与用途分配, 8.2 产业合作诉求 (面向中关村/WRC/京东), 8.3 对合作方价值, 8.4 风险(诚实披露), 八、融资需求与产业合作价值

### Community 46 - "十、风险分析与应对策略"
Cohesion: 0.50
Nodes (4): 10.1 技术风险, 10.2 市场与竞争风险, 10.3 数据合规与隐私风险, 十、风险分析与应对策略

### Community 47 - "七、研发路线图与里程碑"
Cohesion: 0.50
Nodes (4): 7.1 三年演进路线, 7.2 关键里程碑与验收标准, 7.3 传感器升级路线与必补指标, 七、研发路线图与里程碑

### Community 48 - "九、团队与组织"
Cohesion: 0.67
Nodes (3): 9.1 核心团队, 9.2 组织规划与人才缺口, 九、团队与组织

## Knowledge Gaps
- **924 isolated node(s):** `项目定位`, `唯一真相源`, `仓库结构`, `分支与提交`, `真实性与技术约束` (+919 more)
  These have ≤1 connection - possible missing edges or undocumented components.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `寿命终止开发板` connect `寿命终止开发板` to `esp-dev-kits-zh_CN-master-esp32p4.md`?**
  _High betweenness centrality (0.004) - this node is a cross-community bridge._
- **Why does `寿命终止开发板` connect `寿命终止开发板` to `Chapter 4`?**
  _High betweenness centrality (0.002) - this node is a cross-community bridge._
- **Are the 2 inferred relationships involving `serialize_v2()` (e.g. with `test_v2_serializer_rejects_fields_that_become_nonfinite()` and `test_v2_serializer_rejects_invalid_skeleton_contract()`) actually correct?**
  _`serialize_v2()` has 2 INFERRED edges - model-reasoned connections that need verification._
- **What connects `项目定位`, `唯一真相源`, `仓库结构` to the rest of the system?**
  _924 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `lsm6dsv16x.md` be split into smaller, more focused modules?**
  _Cohesion score 0.004728132387706856 - nodes in this community are weakly interconnected._
- **Should `test_hand_token.py` be split into smaller, more focused modules?**
  _Cohesion score 0.0757020757020757 - nodes in this community are weakly interconnected._
- **Should `Chapter 4` be split into smaller, more focused modules?**
  _Cohesion score 0.043478260869565216 - nodes in this community are weakly interconnected._