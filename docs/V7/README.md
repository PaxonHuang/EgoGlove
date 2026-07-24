# EchoGlove V7.0 — 设计文档包

> **Date**: 2026-07-24
> **Supersedes**: V6.0 (Beta 仓库 `docs/V6/`)
> **Key Changes**:
> - **战略**: 单产品线 → Lite + Pro 双产品线 (D6)
> - **数据标准**: 11-dim 特征分类 → **双表示层** Hand Token (MANO + Robot Action, D3)
> - **视觉**: 无 → Pro 预留 EGO Camera 接口 (D7)，双生态通信 (D9)
> - **仓库**: EchoGlove-SLR-MOCAP-Beta → EgoGlove monorepo

> **Implementation status**: 本包为 **V7 设计目标**。当前真实落地能力见 `ARCHITECTURE.md` §8 真实性总表（✅/🟡/🔬/🌌 四级标注，不写想象中的能力）。

## Document Index

| # | File | Content |
|---|------|---------|
| 0a | `STRATEGY.md` | **战略冻结书** — D1–D9 全部冻结决策，所有材料唯一真相源 |
| 0b | `ARCHITECTURE.md` | **系统架构** — 双表示层数据流 + 双产品线硬件 + 真实性总表 |
| 1 | `01_architecture_diagrams.md` | 双产品线系统架构图、数据流、通信栈、三级推理 |
| 2 | `02_BOM_table.md` | Lite/Pro BOM、V6→V7 成本对比、供应商 |
| 3 | `03_wiring_diagram.md` | Lite (ESP32-S3) + Pro (ESP32-P4) 接线、传感器、双生态接口 |
| 4 | `04_SOP-SPEC-PLAN_V7.md` | **主规格书** — 系统总览/硬件/固件/通信/relay/前端/数据/路线图 |
| 5 | `05_claude_code_prompts.md` | V7 实现阶段 paste-ready Claude Code 提示词 |
| 6 | `06_decision_summary.md` | V6→V7 决策记录、真实性分级、风险评估、兼容矩阵 |
| 7 | `07_dual_rep_layer.md` | **双表示层详解** — Hand Token 规范、MANO/Robot Action 对齐、SDK 接口 |

## Quick Reference

- **主线**: 视觉主导 + 可穿戴增强 (D1)，具身智能遥操作优先 (D2)
- **核心壁垒**: 双表示层 (D3) — Hand Token 分叉为 MANO Layer + Robot Action Layer
- **Lite**: ESP32-S3 + Flex + IMU + BLE/WiFi, <¥500 BOM
- **Pro**: ESP32-P4 + 柔性 eSkin + 力接口 + EGO Camera 接口 + 双生态通信 (D9)
- **真实性**: ✅ flex-ADC / S3-ESP-NOW / P4-UART+USBCDC / P4-mock；🟡 IMU驱动 / 有线UART / ROS2 / 双表示层；🔬 连续手语benchmark / eSkin / Force；🌌 EGO融合 / Foundation Model

## 跨会话恢复上下文

先读 `STRATEGY.md` + `ARCHITECTURE.md` 即可恢复战略与架构上下文，勿重读全文。

## 历史版本

| Version | Location | Status |
|---------|----------|--------|
| V6.0 | `EchoGlove-SLR-MOCAP-Beta/docs/V6/` (archive 仓库) | Superseded by V7 |
| V5/V5.2 | `EchoGlove-SLR-MOCAP-Beta/docs/superpowers/` | Archive |
| V3 | `EchoGlove-SLR-MOCAP-Beta/docs/archive/v3/` | Archive |
