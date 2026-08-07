# Episode Model

## 1. 目的

Episode Model 是 dataset / foundation-model interface。它将连续 observations、actions、任务上下文、事件和终止状态组织为可复现的 episode；它不是 Hand Token 的 streaming replacement。

## 2. 建议结构

```text
Dataset
  └── Episode
        ├── episode_metadata
        ├── observations[t]
        ├── actions[t] (optional)
        ├── events[t] (optional)
        ├── task / language context (optional)
        ├── masks / quality[t]
        └── provenance graph
```

每个 episode 应有稳定 ID、采集时间范围、source/session、采样率或 irregular-time 声明、参与的手/设备、任务上下文和终止原因。每个 step 必须可区分 observation time、action time 和 event time，不能假设三者天然同步。

## 3. Step 语义

- `observation`：人在某一时刻的观测状态；
- `action`：发送给机器人或环境的控制意图，必须与 human observation 分离；
- `event`：calibration、contact、grasp、operator marker 等离散事件；
- `mask`：字段缺失、不可用、被质量门控或 padding 的原因；
- `terminal` / `truncated`：任务自然结束与采集截断必须区分。

Episode 可以导出为 RLDS-like 或 LeRobot-compatible dataset projection，但这些 projection 不成为 V8 semantic source of truth。

## 4. 兼容性

| 生态 | Episode 对接方式 | 主要边界 |
|---|---|---|
| ROS2 | 录制 topic、tf、JointState、PoseStamped 后按 timestamp 组 episode | QoS、clock、topic schema 需记录 |
| LeRobot | 将 observation/action 映射为 time-series columns，保留 masks 与 metadata | 版本化 tensor/key layout 需实测 |
| MANO | episode step 可带 MANO parameter view 或 mesh reference | 参数回归、shape 和 license 独立 |
| FreeMoCap | 21-landmark tracks 作为 observation modality | 位置不恢复旋转，反向映射有歧义 |
| OpenXR | runtime hand frames 作为 source observation | runtime capture 不在当前实现范围 |
| Behavior FMs | 多模态 observation + action + language/task context | 需要大规模 benchmark、对齐和训练策略 |

## 5. 数据完整性

Episode writer 必须保存 schema/profile/provenance references、原始时间戳、有效性 mask、变换链和校验摘要。任何重采样、插值、降采样或窗口化都必须成为可追踪 transformation，而非覆盖原始 observation。

## 6. 状态

- Hand Token frame sequence 可作为 episode 的 raw transport evidence：✅；
- 统一 episode semantic schema：🟡 架构可行，尚未实现；
- LeRobot/RLDS projection：🟡 工程可行，需版本实测；
- 行为基础模型通用 episode contract：🌌 长期方向，需 research。
