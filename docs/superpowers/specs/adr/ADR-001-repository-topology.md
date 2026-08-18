# ADR-001: Repository Topology — EgoMotion Umbrella + EgoGlove Implementation

> 日期：2026-08-17
> 状态：Approved / Frozen（用户签核）
> 关联 spec：`docs/superpowers/specs/2026-08-17-egomotion-architecture-upgrade-design.md` §2

## Context

EgoMotion 生态需要区分 **platform / ecosystem 概念** 与 **具体实现资产**。此前方案曾提议把 EgoGlove 仓库 GitHub rename 为 EgoMotion 以统一品牌，但审查发现：

1. GitHub `PaxonHuang/EgoMotion` 已作为独立 umbrella repository 存在（只有 README+LICENSE）。
2. EgoGlove 仓库已包含大量真实实现：firmware（lite/pro/shared）、relay（Hand Token v2 codec、OpenXR adapter、semantic_fixtures）、tests、V8 docs、canonical-20、FK21、OpenXR adapter。
3. 为品牌统一而 rename/migrate 会破坏：Git history、现有相对文档链接（`docs/V8` → `relay/*.py`）、本地路径、codebase-memory 索引（`home-EchoGloveHugeProjects-EgoGlove` 按路径 hash 派生）、scripts、tests、现有引用。
4. 让 implementation repo 也叫 EgoMotion 会与已存在的 umbrella repo 命名碰撞。

## Decision

正式冻结：

- **`PaxonHuang/EgoMotion`** = Umbrella / Platform / Architecture repository
- **`PaxonHuang/EgoGlove`** = Glove Implementation repository

两者均保持现有 GitHub repo 名称。

## Repository Responsibilities

### EgoMotion（Umbrella / Platform）

负责：
- 产品/生态定位
- Architecture
- Strategy
- Roadmap
- Cross-repository specifications
- ADR
- Data Standard
- Integration contracts
- Repository navigation
- 产品线关系
- 跨仓库依赖关系
- 对外项目说明

EgoMotion 是"地图"和"架构中枢"，**不是**未来所有代码的 monorepo。禁止因这一定位提前建 firmware/hardware/algorithms/models/simulation/web/data 等空目录（YAGNI）。

### EgoGlove（Implementation）

负责现阶段已存在及未来逐步进入的：
- glove firmware
- sensor acquisition
- relay
- Hand Token v2
- canonical-20
- FK21
- OpenXR adapter
- V8 semantic implementation
- future glove-side tactile integration
- glove hardware implementation
- SDK implementation（仅在真正进入实现阶段时）
- 对应测试

## Local Path Policy

本地路径全部保持不变：

- `/home/EchoGloveHugeProjects/EgoMotion`
- `/home/EchoGloveHugeProjects/EgoGlove`
- 父目录 `/home/EchoGloveHugeProjects`

禁止（除非未来单独批准）：GitHub rename、本地目录 rename、parent directory rename、remote URL 修改、submodule 引入。

## Git History Policy

不为了命名统一而迁移/重写历史。EgoGlove 的现有 commit 历史保持原样。

## Dependency Policy

当前优先使用：
- documentation links
- explicit version contracts
- Git references / releases（真正需要时）

暂不使用 submodule。

## Future Repository Split Criteria

未来只有当某一模块满足以下条件之一时才创建独立 repo：
- 独立生命周期
- 独立 CI/CD
- 独立版本
- 独立依赖
- 独立贡献者/团队
- 仓库规模真正需要拆分

候选未来仓库：EgoTouch（tactile subsystem）、EgoData（dataset infrastructure）、EgoTeleop（robotics/teleop）、EgoCal（calibration）。**现在不预建**。

## Consequences

**优点**：
- 保留 Git history、文档回链、CBM 索引、scripts、tests、现有引用。
- 平台与实现职责清晰分离。
- 仓库名作为工程资产名，产品品牌名对外统一（EgoMotion Glove），二者解耦。
- 增量演进，符合"选择性兼容升级、不重写全部代码"原则。

**代价**：
- 两个仓库名（EgoMotion + EgoGlove）需在文档中说明关系。
- 跨仓库导航依赖文档链接而非代码依赖，需维护文档准确性。

## Core Principle

**Repository name ≠ Product brand name.**

EgoMotion 是生态/平台概念；EgoGlove 是具体实现资产。产品线对外统一叫 EgoMotion Glove Lite/Pro/X，但实现仓库保留 EgoGlove 名。不再通过 rename repository 强行统一概念。
