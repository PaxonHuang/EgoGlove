# Provenance Model

## 1. 目的

Provenance Model 记录 observation/episode 的来源、处理链、工具版本、质量证据和信任边界。它回答“数据从哪里来、经过了什么变换、哪些结论可以相信”，但不把元数据塞入 Hand Token motion payload。

## 2. 建议结构

```text
ProvenanceRecord {
  record_id
  source {
    device / runtime / dataset
    source_format
    source_version
    operator_or_session (optional)
  }
  acquisition {
    time_range
    clock_domain
    calibration_ref
    environment_ref (optional)
  }
  transformations[] {
    input_ref
    operation
    implementation_version
    parameters_digest
    output_ref
  }
  validation {
    checks
    metrics
    fixture_or_test_ref
    status
  }
  policy {
    license
    consent / privacy class
    retention
    permitted_use
  }
}
```

## 3. Provenance graph

Provenance 应表达不可变的 lineage：`source → ingest → decode → normalize → derive → export`。每个节点有 content/schema/tool identity，每条边说明操作及参数摘要。重新处理产生新 output node，不覆盖旧记录。

对于 Hand Token，应记录 frame/sequence 的 hash、codec version 和 validation result；但不得把 source vendor、license 或实验注释强行加入 frozen wire contract。

## 4. Trust 与质量

Provenance 的 trust 不是单一分数。至少区分：

- authenticity：是否能确认来源和完整性；
- calibration validity：采集时标定是否有效；
- semantic validity：拓扑、坐标和单位是否已验证；
- measurement quality：噪声、缺失、遮挡和延迟证据；
- transformation confidence：派生/估计步骤的模型和误差；
- usage authority：license、consent、商业使用边界。

未经验证的外部 schema 必须标注 `research_required` 或 `unverified`，不得因为成功解析就宣称语义等价。

## 5. 生态兼容

- MANO：记录模型版本、β/θ 生成方式与 license；
- FreeMoCap：记录 tracker/backend、相机或 session 信息及 AGPL 相关边界；
- OpenXR：记录 runtime、extension/version、base space 与 frame time；
- ROS2：记录 bag、topic、QoS、ROS distribution 与 clock source；
- LeRobot：记录 dataset revision、feature schema、转换脚本和 split；
- Behavior Foundation Models：记录数据许可、consent、去标识化、过滤与 train/eval split，支持 reproducible dataset cards。

## 6. 状态

- 现有 codec/golden tests 提供部分实现证据：✅；
- sequence-level lineage 与 trust schema：🟡 工程可实现；
- 跨源 uncertainty calibration、consent automation：🔬；
- 可验证数据供应链与 foundation-model data governance：🌌。
