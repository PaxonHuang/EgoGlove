# EchoGlove V7.0 — 决策记录与真实性分级

> **Version**: V7.0
> **Date**: 2026-07-24
> **参见**: `STRATEGY.md` (D1–D9), `ARCHITECTURE.md` §8 (真实性总表)

---

## 1. V6 → V7 决策记录

| 时间 | 决策 | 理由 |
|------|------|------|
| 2026-07-22 | 战略转向: 单产品 → 双产品线 (D6) | 消费侧与具身智能侧诉求差异大, 单产品无法兼顾成本与精度 |
| 2026-07-22 | 数据标准: 11-dim 分类 → 双表示层 Hand Token (D3) | 从 gesture label 转 hand state, 商业价值差一个数量级 (GPT5.6 洞察) |
| 2026-07-22 | 第一代不进 CV, Pro 预留接口 (D7) | CV 研发风险高, 先用可穿戴+外接融合, 后期 AI 眼镜 |
| 2026-07-23 | Pro 视觉双生态接口 (D9) | 兼顾消费 (USB-C/WiFi/BT) 与机器人 (ROS2/Ethernet/USB3 Vision) |
| 2026-07-23 | 数据战略 Open Core (D5) | 开放基础建生态, 商业数据建壁垒 |
| 2026-07-23 | UWB 降级为 Pro 可选 | 对 egocentric VLA 冗余, 增 BOM 成本 |
| 2026-07-23 | 手语模型战略降级 (D8) | Hand Token 的一种解释方式, 非唯一输出 |
| 2026-07-24 | 新建 EgoGlove monorepo | 战略/架构沉淀 repo, Beta+Alpha archive |

## 2. 真实性分级定义

| 标注 | 含义 | 文档要求 |
|------|------|---------|
| ✅ | 已实现 (code-verified) | 必须有代码 + 测试/验证记录 |
| 🟡 | 工程可实现 (6-12 月) | 设计已定, 待实现, 可给出工期 |
| 🔬 | 需研发验证 | 关键技术未解决, 有风险 |
| 🌌 | 长期方向 | 战略愿景, 不保证时间表 |

**强制**: BP / 白皮书 / 产业合作材料 / V7 文档中所有能力描述必须带此标注, 不写想象中的能力。

## 3. 真实性总表 (与 ARCHITECTURE.md §8 同步)

| 能力 | 状态 |
|------|------|
| Flex internal ADC1 采集 | ✅ |
| S3 ESP-NOW 通信 | ✅ |
| P4 UART-RX + USB-CDC | ✅ |
| P4 standalone mock | ✅ |
| LSM6DSV16X IMU 驱动 | 🟡 |
| S3→P4 有线 UART | 🟡 |
| ROS2 SDK | 🟡 |
| MANO 双表示层 | 🟡 |
| MediaPipe+glove 融合 | 🟡 |
| 连续手语 benchmark | 🔬 |
| 柔性 eSkin / Force | 🔬 |
| EGO Camera 融合 | 🌌 |
| Human Hand Foundation Model | 🌌 |

## 4. 风险评估

| 风险 | 等级 | 应对 | 真实性影响 |
|------|------|------|-----------|
| Flex/eSkin 量产一致性 | 高 | 来料筛选 + 校准 + 供应链 | 🔬 |
| 双表示层标准被替代 | 中 | 速度 + 开放生态 | 🟡 |
| 连续手语未达宣称 | 中 | benchmark 给真实数字 | 🔬 |
| P4 供货 | 中 | 二供 STM32H7 | 🟡 |
| CV 融合技术风险 | 中 | 第一代不进, 预留接口 | 🌌 |

## 5. 兼容矩阵 (V7 对外)

| 目标生态 | 接口 | 真实性 |
|---------|------|--------|
| Unity | ms-MANO | 🟡 |
| Unreal | MANO | 🟡 |
| ROS2 | joint+6DoF+force | 🟡 |
| PyTorch | Hand Token tensor | 🟡 |
| TFLite | Tier1/2 模型 | 🟡 |
| MediaPipe | hand landmark 融合 | 🟡 |
| VLA | Robot Action 数据 | 🔬 |
| UMI/ALOHA | 互补 Human Data Capture | 🟡 |

## 6. GPT5.6 对话修正点 (糟粕→修正)

| GPT 主张 | 代码现实 | V7 处理 |
|----------|---------|---------|
| "已实现资产"丰富 | 仅 flex-ADC/ESP-NOW/P4-UART+USB/mock 真实 | 文档严格按真实列 |
| 数据飞轮已运转 | data/ 仅零星 CSV | 数据战略标 🟡/🌌 |
| C6 跑 ESP-NOW 桥 | C6=ESP-Hosted 不能 ESP-NOW | 生产期走 Wi-Fi/UDP |
| <3ms TinyML 跑 Transformer+fusion | 不成立 | 预处理在 MCU, 推理在 edge/cloud |
| 连续手语亚秒级 | 未证明 | 降级为目标, 建 benchmark |

## 7. 审批状态

- D1–D9: **全部冻结** (2026-07-23), 进入 BP 撰写 + V7 落地
- 战略变更: 需走 `STRATEGY.md` §8 评审流程
