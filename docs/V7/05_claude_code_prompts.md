# EchoGlove V7.0 — Claude Code 实现提示词

> **Version**: V7.0
> **Date**: 2026-07-24
> **用途**: V7 各实现阶段的 paste-ready 提示词，配合本仓库 CLAUDE.md 使用

每个提示词假设已在 EgoGlove monorepo 根目录，且已读 `docs/V7/STRATEGY.md` + `ARCHITECTURE.md`。

---

## Phase V7-α: Lite IMU 驱动 + Hand Token 规范 (🟡→✅)

```
在 firmware/lite/ 实现 LSM6DSV16X IMU 驱动 (本地库 firmware/lite/lib/Sensors/LSM6DSV16X/)。
要求:
1. I²C @0x6A (SA0=GND), GPIO8 SDA / GPIO9 SCL, 400kHz, CS 必须硬件拉高 3.3V
2. 用 ST 官方 esp32 兼容驱动或手写寄存器, 启用 SFLP embedded fusion
3. 输出 euler[3] + gyro[3] 填入 11-dim 特征向量 (替代当前 0 填充)
4. 接入 SensorManager.h, FreeRTOS Task_SensorRead 100Hz
5. 不引入 PlatformIO registry 依赖, 本地库
6. pio run 必须通过
参考: docs/V7/03_wiring_diagram.md §1.1, 历史 V6 docs/V6/07_internal_adc_migration.md (ADC 部分已落地可参考结构)
真实性约束: 实现后标 ✅, 不得宣称已实现未验证部分
```

## Phase V7-α: Hand Token 规范定稿 + 协议头

```
在 firmware/shared/ 定义 Hand Token 二进制协议:
1. 参照 docs/V7/07_dual_rep_layer.md 字段表 (flex5 + IMU4 + 6DoF6 + vel6 + contact5 + force5)
2. hand_token.h: 结构体 + 序列化/反序列化 + CRC-16
3. 兼容 Lite (force=0 填充) 与 Pro (force 有效)
4. 在 relay/ 加 Hand Token 解析, 分叉为 MANO dict + Robot Action dict
5. 单元测试 firmware/shared/test/
真实性: 当前 🟡, 实现后标 ✅
```

## Phase V7-β: 双表示层 SDK

```
在 sdk/python/ 实现 HandTokenSDK:
1. parse_hand_token(bytes) -> HandToken
2. to_mano(token) -> MANO params (兼容 ms-MANO)
3. to_robot_action(token) -> {joint, wrist_6dof, vel, contact, force}
4. to_ros2_msg(token) -> sensor_msgs/JointState + geometry_msgs/PoseStamped
5. 与 MediaPipe hand landmark 融合接口 (vision_world_state + glove_hand_state -> human_intent)
6. pytest 覆盖
参考: docs/V7/07_dual_rep_layer.md, STRATEGY.md D1/D3
真实性: 🟡→✅
```

## Phase V7-β: 连续手语 benchmark

```
在 data/open/slr_benchmark/ 建连续手语评测集:
1. 采集脚本 ( relay/scripts/record_benchmark.py )
2. 指标: 端到端延迟 / 字词错误率 WER / 连续准确率
3. 50 句日常表达, 每句 3 次 × 5 人
4. 评测脚本 compute_metrics.py
5. 数据入 data/open/ (Open Core), 标注 4 级真实性
诚实约束: 这是 🔬→🟡, BP 当前 "亚秒级连续手语" 仍为未证明, 用本 benchmark 给出真实数字
```

## Phase V7-RC: Pro 原型 eSkin/Force 驱动

```
在 firmware/pro/ 实现:
1. eSkin ×5 驱动 (ADC1 或外置 ADC, 待选型)
2. Force ×5 驱动
3. 双生态通信: USB-C (CDC) + Ethernet (RMII) 起通
4. ROS2 bridge 骨架 (base_station/ 或 sdk/ros2/)
参考: docs/V7/02_BOM_table.md §2, 03_wiring_diagram.md §2
真实性: 🔬→🟡, Pro BOM 为目标测算
```

---

## 通用约束 (所有阶段)

- git 身份: PaxonHuang <quenchkidney@outlook.com>, 无 AI co-author 署名
- 不编造: 引用前核实, 待核对项标 "待人工核对"
- 4 级真实性: ✅/🟡/🔬/🌌, 实现后更新 ARCHITECTURE.md §8
- 遇决策/重大 bug: 停下让用户决策
- 每阶段完成: 更新 memory + commit + (内容落地后) graphify update .
