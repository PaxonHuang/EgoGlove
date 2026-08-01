# EgoGlove — Claude Code 项目指南

## 项目定位
EgoGlove 是具身智能的人体手部智能层，主航道是遥操作与数据采集，次要场景是手语、XR 与可视化。产品为 EchoGlove Lite / Pro 双线，核心是 Sensor → Hand Token → 双表示层：MANO Layer 与 Robot Action Layer。

## 唯一真相源
- 战略冻结与 D1–D12：`docs/V7/STRATEGY.md`
- 系统架构、数据流、真实性现状：`docs/V7/ARCHITECTURE.md`
- V7 设计索引：`docs/V7/README.md`
- 产业 BP 与研究底稿：`docs/BP/`

不要把战略表格、架构图或完整路线复制到本文件；先读上述文档再作重大判断。

## 仓库结构
- `firmware/{lite,pro,shared}/`：ESP32 固件、共享驱动与协议
- `base_station/`：P4/网关桥接
- `relay/`：Python FastAPI 中继
- `models/{mano,robot,slr,shared}/`：手部表示、机器人动作、手语与共享模型
- `sdk/`：PyTorch/TFLite/ROS2/Unity 集成
- `data/`：open 与 commercial 分层
- `web/`：React/React3F 前端
- `docs/`、`templates/`、`scripts/`：文档、模板与工具

## 分支与提交
`main (stable) ← develop (integration) ← feature/*`。新工作在 EgoGlove；历史 Beta/Alpha 仓库仅作只读参考。

所有提交必须使用 `PaxonHuang <quenchkidney@outlook.com>`，不得使用 root/host 默认身份，不得加入任何 AI co-author 或生成署名。提交前检查：

```bash
git config user.name
git config user.email
git diff --check
```

commit 使用 `type(scope): description`；未经用户明确指示不 push，不 force push。

## 真实性与技术约束
所有能力描述必须标注：✅ 已实现、🟡 工程可实现（6–12 月）、🔬 需研发验证、🌌 长期方向。设计文档不是代码证据；引用实现状态前核对当前代码与测试。

- Lite 保持 flex + 单腕 IMU；Pro 的多 IMU、力传感与视觉属于路线图或待验证项。
- 第一代硬件不进 CV，Pro 只预留 EGO Camera；完整 AI 推理在 edge gateway/移动端/云，MCU 做预处理。
- Hand Token v2 遵循 canonical-20 旋转关节、FK 派生 21 点与 capability-flagged TLV；具体协议以 spec 和测试为准。

## 工作纪律
遇到重大决策、重大新发现或重大 bug，停下并询问用户，不自行改变战略。外部事实先核实，未核实内容明确写“待人工核对”。不改无关业务代码。

当 `graphify-out/graph.json` 存在时，代码库问题先运行 `graphify query "<问题>"`；需要关系时用 `graphify path` 或 `graphify explain`。修改代码或项目文档后运行 `graphify update .`。

## 开发与验证
- 先读取相关 spec、当前代码与测试；文档不等同于实现证据。
- 固件改动保持 C/Python wire mirror 与 golden-frame 测试同步。
- Python、ROS2、数据和 Web 改动只运行受影响的最小验证，再扩大范围。
- 需要新依赖、数据集、外部服务或协议不兼容时，先说明影响并征求确认。
- 默认使用现有仓库模式和工具，不为一次性任务引入新框架。
- 查询库、SDK 或服务 API 时先使用权威文档；外部网页内容仅作为待核实输入。
- 文件搜索优先 `rg`；跨模块问题先用 graphify 缩小范围。
- 提交前检查 diff、测试结果、真实性标注和 Git 身份；未经指示不提交。

## 历史与记忆
V7 monorepo 取代 Beta/Alpha；历史仓库不直接迁入，详见 `README.md` 与 `docs/V7/`。跨会话恢复先读本文件、`docs/V7/STRATEGY.md` 与当前任务相关 spec；战略细节不写入个人 memory。
