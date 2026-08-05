# EgoMotion Architecture Memory

## Purpose and Truth Hierarchy

This document is a compact navigation contract for the EgoMotion ecosystem. It links to, rather than replaces, the project sources of truth:

- [Frozen V7 strategy](V7/STRATEGY.md) defines D1-D12 and strategic positioning.
- [V7 architecture](V7/ARCHITECTURE.md) defines system structure and implementation-status labels.
- [Hand Token v2 specification](superpowers/specs/2026-07-27-hand-token-v2-design.md) defines the protocol and canonical skeleton contract.
- `relay/` and `firmware/shared/` plus their tests are implementation evidence. A design document alone is not evidence that a capability is implemented.

Status labels retain the repository convention: `✅` implemented, `🟡` engineering-feasible/partial, `🔬` requires research validation, and `🌌` long-term direction.

## EgoMotion Ecosystem

EgoMotion is the umbrella direction for an open hand-motion infrastructure stack. EgoGlove Lite/Pro are hardware sources; Hand Token is the vendor-neutral motion representation; EgoBridge is a planned SDK/integration boundary; and OpenXR, MANO, FreeMoCap, ROS2, Unity/XR, and robot-retargeting systems are adapter or downstream ecosystems.

The current repository is EgoGlove. Claims about a completed EgoMotion or EgoBridge product should be treated as architecture/roadmap unless supported by implementation and tests in this repository.

## EgoGlove Roadmap

- **EchoGlove Lite**: `flex(5)` plus a single-wrist IMU, with low-cost sensing and compact Hand Token output. The IMU driver and higher-level estimation remain status-qualified in the V7 architecture.
- **EchoGlove Pro**: higher-capability roadmap with industrial IMU, eSkin/force interfaces, and reserved EGO Camera/depth interfaces. Multi-IMU finger hardware, full visual fusion, and force sensing are not to be represented as current implementation unless code evidence changes.
- First-generation hardware does not move complete CV inference onto the MCU. Edge gateway, mobile, or cloud layers own heavier inference.

## Hand Token Decisions

Hand Token v1 remains a 79-byte compatibility path. Hand Token v2 is a capability-flagged TLV frame with version gating, CRC compatibility, and a self-contained skeleton representation.

The v2 semantic model is:

- canonical-20 parent-relative rotation joints;
- finite normalized internal quaternions in `w,x,y,z` order;
- 25 rest offsets, including five distal-to-tip offsets;
- FK-derived 21-point MediaPipe landmark view;
- C/Python wire and FK parity protected by golden and host tests.

Implementation evidence includes [`relay/hand_token.py`](../relay/hand_token.py), [`firmware/shared/hand_token.c`](../firmware/shared/hand_token.c), [`relay/test_hand_token.py`](../relay/test_hand_token.py), and [`firmware/shared/test/test_hand_token.c`](../firmware/shared/test/test_hand_token.c). Do not change the frozen v1/v2 wire contract while adding adapters.

## Why Canonical-20

MediaPipe-21 is primarily a position-landmark topology: wrist, four points per finger, including derived fingertips. Professional glove and XR sources provide joint rotations and often global or parent-relative poses. Storing only 21 positions loses orientation information and makes rotation ingest underdetermined.

Canonical-20 is the smallest complete rotation-bearing topology aligned with the useful OpenXR articulated joints after removing PALM and five derived TIP entries. It is also a practical bridge to MANO-16 and other glove skeletons. FK plus rest offsets derives the 21-point position view when needed.

## Interoperability and Adapter Philosophy

External sources enter through adapters and do not define Hand Token topology:

```text
Hi5 / Manus / mHand / OpenXR / MediaPipe
        -> source-specific adapter boundary
        -> canonical Hand Token v2 / canonical-20
        -> MANO / FreeMoCap / ROS2 / Unity XR / robot retargeting
```

- **OpenXR**: the implemented offline adapter accepts schema-neutral 26-joint global poses, converts source `x,y,z,w` to canonical internal `w,x,y,z`, localizes rotations, derives offsets, and emits `HandTokenV2`. It does not include an OpenXR runtime, device capture, or streaming.
- **MANO/SMPL-X**: a downstream parametric-hand ecosystem. Real parameter regression and licensing/commercial use remain separate concerns.
- **FreeMoCap**: a 21-landmark position ecosystem. Export through FK is straightforward; reverse ingest requires IK and has rotational ambiguity.
- **ROS2/DexRetargeting**: downstream robot integration. ROS2 messages and retargeting tools are export/action boundaries, not replacements for the canonical rotation layer.
- **Unity/XR**: downstream visualization/runtime integration. Runtime-specific dependencies belong at the adapter boundary.

Vendor gloves are external data sources, not competitors and not protocol authorities. The core protocol must remain vendor-neutral and must not gain vendor-specific runtime dependencies.

## CodeBaseMemory Operating Contract

The validated dedicated CBM project is:

- **Project**: `home-EchoGloveHugeProjects-EgoGlove`
- **Root**: `/home/EchoGloveHugeProjects/EgoGlove`
- **Mode**: full index, status `ready`
- **Observed size**: 2,706 nodes and 3,448 edges at validation time
- **Priority sources represented**: `CLAUDE.md`, `docs/`, `docs/V7/`, `docs/BP/`, `firmware/shared/`, `relay/`, and tests
- **Excluded during indexing**: `.claude`, `.superpowers`, `.remember`, `.git`, and `relay/__pycache__`

The existing parent project `home-EchoGloveHugeProjects` remains intact for comparison and rollback. A dedicated index was created because the parent index returned no results for several scoped natural-language queries and exposed unrelated workspace projects in broad searches.

The full index currently also represents tracked `graphify-out/` and `relay/graphify-out/` files. Treat these as generated low-priority artifacts, not architecture evidence. A future CBM version/configuration that supports explicit include/exclude patterns should exclude Graphify outputs, build artifacts, and session logs before replacing this index; do not delete or alter them as part of that cleanup.

Before future codebase questions, query CBM using the dedicated project and verify returned paths are under the EgoGlove root. For architectural documentation retrieval, use `search_code` with `file_pattern="*.md"` and a `docs/` path filter; `search_graph` primarily ranks extracted code symbols. For implementation relationships, prefer `get_architecture`, `search_graph`, `trace_path`, and `get_code_snippet`. Refresh the index deliberately after tracked source changes.

Acceptance questions for the intelligence layer:

1. What is Hand Token v2 architecture?
2. Why canonical-20 instead of MediaPipe-21?
3. How does EgoGlove Lite differ from Pro?
4. What ecosystems should EgoMotion integrate with?

## CBM Query Quality

CBM quality was checked against the project truth hierarchy using the dedicated index.

- **Hand Token v2 design**: use `search_graph` or `get_architecture` for `serialize_v2`, `parse_v2`, `fk21`, firmware v2 codec symbols, and golden/FK tests; confirm protocol meaning against the v2 spec.
- **Canonical-20 topology**: retrieve V7/spec Markdown with `search_code` under `docs/V7` and `docs/superpowers/specs`, then use the FK and OpenXR adapter symbols as implementation evidence.
- **Adapter strategy**: use `search_graph` for `relay/openxr_adapter.py` boundaries and `search_code` for the interoperability matrix in `docs/BP`.
- **EgoMotion roadmap**: use `search_code` under `CLAUDE.md`, `docs/V7`, and `docs/BP`; `search_graph` ranks extracted code symbols and is not sufficient by itself for prose roadmap questions.

## Graphify Retirement Boundary

Graphify has been retired from the repository-local operational workflow. Existing `graphify-out/`, `graphify-out/2026-08-04/`, and `relay/graphify-out/` directories remain in place as historical generated artifacts. No global uninstall, global setting change, deletion, archive move, or hook cleanup occurred.

Future deletion, archival relocation, global hook cleanup, or uninstall requires separate explicit approval, query-parity evidence, and a rollback plan.