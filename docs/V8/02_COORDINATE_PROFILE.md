# Coordinate Profile

## 1. 目的

Coordinate Profile 是所有空间语义的显式 normalization boundary。它解决 source-specific frame、单位、handedness、轴向、旋转表示和 local/global pose 的差异；它不改变 Hand Token v2 的 canonical-20 或 wire contract。

## 2. Profile 内容

每个 profile 至少声明：

- `profile_id` 与版本；
- handedness（right/left-handed）；
- up/right/forward axis；
- length unit 与 angle unit；
- origin/reference frame 和 frame tree；
- wrist pose 是 global、local 还是 session-relative；
- quaternion component order（w-first 或 w-last）；
- rotation composition convention；
- timestamp/clock domain；
- mirror policy 与 left/right hand semantics。

禁止根据字段名或数值范围隐式猜测 profile。缺失 profile 时，observation 只能标记为 unresolved，不能宣称已归一化。

## 3. 转换边界

```text
source profile
    ↓ explicit transform + validation
canonical semantic profile
    ↓ optional projection
MANO / FreeMoCap / OpenXR / ROS2 / LeRobot profile
```

Hand Token v2 已冻结的 canonical 约定继续作为 transport decode 的既定语义。V8 只要求 decoded observation 携带 profile reference，并让上下游转换可审计、可复现。

## 4. 典型生态差异

- OpenXR 常见 global pose、米制、右手坐标和 `x,y,z,w` quaternion；
- Hand Token canonical 使用父相对旋转，内部约定为 `w,x,y,z`；
- ROS2 `geometry_msgs/Quaternion` 使用 `x,y,z,w`，而 `JointState` 主要是 named scalar DOF；
- FreeMoCap/MediaPipe 主要是 21-point position view，不等价于旋转骨架；
- MANO 使用 parent-relative axis-angle pose，需要明确 root、pose convention 与 hand side。

上述规则只能作为 profile 实例的候选描述；具体 adapter 必须以其权威 schema 和测试为准。

## 5. 验证要求

Profile validator 应检查：有限值、单位、轴变换、quaternion norm、父子拓扑、时间单调性、镜像一致性和 round-trip tolerance。任何 transform 都应记录 source profile、target profile、版本和误差预算。

## 6. 状态

- Hand Token canonical coordinate semantics：✅ 已冻结并有 codec/FK/golden evidence；
- Profile metadata abstraction：🟡 工程可实现；
- 跨 OpenXR/MANO/FreeMoCap/ROS2 的统一 round-trip tolerance：🔬 需研究验证；
- 自动 profile inference：🌌 长期方向，默认不启用。
