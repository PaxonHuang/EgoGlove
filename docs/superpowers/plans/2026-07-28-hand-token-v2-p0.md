# Hand Token v2 P0 Protocol Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 实现 Hand Token v2.0 capability-flagged TLV codec、self-contained canonical-20 skeleton、25-offset FK 派生 MediaPipe-21，并以 C/Python 三组跨语言金标证明与 v1 79B 永久兼容。

**Architecture:** 保留现有 v1 struct、codec 与 Python API 不变；新增 focused skeleton 模块和独立 v2 codec。v2 wire quaternion 可 w-first/w-last，解析边界统一为内存态 w-first；version-gate 只负责分流。Skeleton frame 固定包含 quaternion-20、offset-25、rest model 三件套。

**Tech Stack:** C11 (`gcc`, `make`, `-Wall -Wextra -Werror`)、Python 3 dataclasses/`struct`、pytest、CRC-16/MODBUS、IEEE-754 binary16。

## Global Constraints

- 真相源：`docs/superpowers/specs/2026-07-27-hand-token-v2-design.md`，P0 于 2026-07-28 签核。
- v1 永久保持 `version=0x01`、79B、字节布局、CRC 和现有公开 API 不变。
- v2 固定 `version=0x02`；header 11B、base 69B、TLV、CRC 2B；`total_len` 含 CRC。
- v2.0 拒绝 `SKEL_SMALLEST3=1`；smallest-three 延后 v2.1。
- 内存态 quaternion 固定 `w,x,y,z`；`QUAT_WLAST` 仅描述 wire，codec 在边界 swap。
- `REST_OFFSETS` = 25×vec3 f16：`0..19` parent-offset，Wrist 为零；`20..24` 为五指 Distal→Tip。
- `REST_MODEL_ID` = `{u16 model_id, u16 revision}` LE；0/1/2 = canonical-human/MANO-aligned/OpenXR-aligned；revision 从 1 起。
- `HAS_SKELETON` 时 `SKELETON_QUAT20`、`REST_OFFSETS`、`REST_MODEL_ID` 必须各一次。
- 未知 model 可结构解析，但 FK 返回 unsupported；未知 TLV 按 len 跳过。
- 三个不可跳过金标：v1 79B、v2 Lite 82B、v2 skeleton 405B。
- 不实现 MANO 回归、robot retarget、厂商 adapter 或硬件改动。

## File Map

- Modify `firmware/shared/hand_token.h`: 保留 v1；声明共享 base 类型、version-gate 与 v2 API。
- Modify `firmware/shared/hand_token.c`: 复用 CRC/f16/base 字段 codec；实现 v1/v2 分流和 v2 TLV codec。
- Create `firmware/shared/hand_skeleton.h`: canonical 索引、parent 表、rest model、FK 状态与 API。
- Create `firmware/shared/hand_skeleton.c`: quaternion math 与 canonical-20 → MediaPipe-21 FK。
- Modify `firmware/shared/test/test_hand_token.c`: v1 回归、v2 wire、负例和三金标。
- Modify `firmware/shared/test/Makefile`: 编译 skeleton 模块。
- Modify `relay/hand_token.py`: 保留 v1 API，新增 mirror v2 dataclasses/codec/version-gate/FK。
- Modify `relay/test_hand_token.py`: Python mirror、三金标和错误矩阵。

---

### Task 1: Canonical Skeleton Contract and FK

**Files:**
- Create: `firmware/shared/hand_skeleton.h`
- Create: `firmware/shared/hand_skeleton.c`
- Modify: `firmware/shared/test/test_hand_token.c`
- Modify: `firmware/shared/test/Makefile`

**Interfaces:**
- Produces: `hand_skeleton_t { float quat[20][4]; float offsets[25][3]; uint16_t model_id; uint16_t revision; }`.
- Produces: `hand_skeleton_status_t hand_skeleton_fk21(const hand_skeleton_t *, float out[21][3])`.
- Status values: `OK`, `INVALID_ARGUMENT`, `INVALID_WRIST_OFFSET`, `UNSUPPORTED_MODEL`, `INVALID_REVISION`.

- [ ] **Step 1: Write failing C tests**

Add tests that assert the exact parent table `{-1,0,1,2,0,4,5,6,0,8,9,10,0,12,13,14,0,16,17,18}`, identity quaternion FK chain accumulation, frozen MediaPipe output mapping (`4/8/12/16` excluded but present in each parent chain), and tips using offsets 20..24. Add negative tests for nonzero wrist offset, model 99, and revision 0.

- [ ] **Step 2: Run red test**

Run: `make -C firmware/shared/test clean all`
Expected: compile FAIL because `hand_skeleton.h` and `hand_skeleton_fk21` do not exist.

- [ ] **Step 3: Implement minimal skeleton module**

Implement quaternion normalization, Hamilton multiplication, vector rotation, and parent-chain global transforms. Freeze the derived MediaPipe mapping as `0`; `1,2,3,tip20`; `5,6,7,tip21`; `9,10,11,tip22`; `13,14,15,tip23`; `17,18,19,tip24`. Canonical metacarpals `4/8/12/16` participate in FK parent chains but are excluded from output; canonical Proximal `5/9/13/17` maps to MediaPipe MCP. Reject unsupported model before FK; no tip extrapolation.

- [ ] **Step 4: Run green test**

Run: `make -C firmware/shared/test clean all`
Expected: exit 0 and all skeleton/FK assertions pass.

- [ ] **Step 5: Commit**

```bash
git add firmware/shared/hand_skeleton.h firmware/shared/hand_skeleton.c firmware/shared/test/test_hand_token.c firmware/shared/test/Makefile
git commit -m "feat(protocol): add canonical hand skeleton FK"
```

### Task 2: C v2 Lite Codec and Version Gate

**Files:**
- Modify: `firmware/shared/hand_token.h`
- Modify: `firmware/shared/hand_token.c`
- Modify: `firmware/shared/test/test_hand_token.c`

**Interfaces:**
- Produces: `hand_token_v2_t { hand_token_t base; uint8_t caps; bool has_skeleton; hand_skeleton_t skeleton; }`.
- Produces: `size_t hand_token_v2_serialize(const hand_token_v2_t *, uint8_t *, size_t)`.
- Produces: `bool hand_token_v2_parse(const uint8_t *, size_t, hand_token_v2_t *)`.
- Produces: `hand_token_wire_version_t hand_token_detect_version(const uint8_t *, size_t)`.
- Keeps: existing v1 symbols and 79B output byte-identical.

- [ ] **Step 1: Write failing Lite/version tests**

Assert v1 golden remains exactly the existing 158-char hex; v2 Lite is exactly 82B with header offsets `caps=8`, `total_len=9`, base begins at 11, CRC at 80; detect_version returns V1/V2/INVALID. Assert v1 parser rejects v2 and v2 parser accepts v1 through an explicit compatibility helper only, not by misreading layout.

- [ ] **Step 2: Run red test**

Run: `make -C firmware/shared/test clean all`
Expected: compile FAIL on missing v2 types/functions.

- [ ] **Step 3: Refactor shared base codec and implement Lite v2**

Extract private `serialize_base69()` / `parse_base69()` so v1 `[8,77)` and v2 `[11,80)` share code. Do not change v1 offsets/functions. Validate exact `total_len`, reserved caps bit7=0, smallest-three=0, CRC over `[0,total_len-2)`.

- [ ] **Step 4: Run green and v1 regression**

Run: `make -C firmware/shared/test clean all`
Expected: exit 0; v1 golden unchanged; v2 Lite tests pass.

- [ ] **Step 5: Commit**

```bash
git add firmware/shared/hand_token.h firmware/shared/hand_token.c firmware/shared/test/test_hand_token.c
git commit -m "feat(protocol): add Hand Token v2 Lite codec"
```

### Task 3: C Skeleton TLV Codec and Validation

**Files:**
- Modify: `firmware/shared/hand_token.h`
- Modify: `firmware/shared/hand_token.c`
- Modify: `firmware/shared/test/test_hand_token.c`

**Interfaces:**
- TLV constants: `0x01 SKELETON_QUAT20`, `0x02 REST_OFFSETS`, `0x08 REST_MODEL_ID`.
- Produces valid skeleton frame length 405B and normalized in-memory w-first quaternions.

- [ ] **Step 1: Write failing TLV tests**

Build a deterministic reference skeleton with exact f16 values. Test 405B length, TLV order 01/02/08, round-trip, `QUAT_WLAST` wire swap, unknown TLV skip, and rejection of missing/duplicate trio members, wrong lengths, truncated TLV, `HAS_SKELETON` mismatch, smallest-three, nonzero wrist offset, and revision 0.

- [ ] **Step 2: Run red test**

Run: `make -C firmware/shared/test clean all`
Expected: tests FAIL because skeleton TLVs are not emitted/parsed.

- [ ] **Step 3: Implement bounded TLV writer/parser**

Use cursor/end bounds before every TLV header/value access. Emit known TLVs in ascending type order for deterministic goldens. Track seen bits to reject duplicates. Convert all wire quaternions according to `QUAT_WLAST`; validate quartet norms are finite and nonzero before normalization.

- [ ] **Step 4: Run green test**

Run: `make -C firmware/shared/test clean all`
Expected: exit 0 and all malformed-frame tests pass.

- [ ] **Step 5: Commit**

```bash
git add firmware/shared/hand_token.h firmware/shared/hand_token.c firmware/shared/test/test_hand_token.c
git commit -m "feat(protocol): add self-contained skeleton TLVs"
```

### Task 4: Python v2 Mirror and FK

**Status: required next task — not implemented in `relay/hand_token.py` as of the C fixed-point milestone.**

**Files:**
- Modify: `relay/hand_token.py`
- Modify: `relay/test_hand_token.py`

**Interfaces:**
- Produces: `HandSkeleton`, `HandTokenV2`, `serialize_v2()`, `parse_v2()`, `parse_any()`, `fk21()`.
- `parse_any(frame)` returns existing `HandToken` for v1 and `HandTokenV2` for v2.
- Error contract: malformed wire raises `ValueError`; unsupported rest model in `fk21()` raises `UnsupportedRestModelError`.

- [ ] **Step 1: Write failing Python mirror tests**

Mirror every C positive/negative case, including v1 golden, 82B Lite, 405B skeleton, w-last normalization, trio validation, unknown TLV skip, and exact identity-rotation FK outputs.

- [ ] **Step 2: Run red test**

Run: `python3 -m pytest relay/test_hand_token.py -q`
Expected: collection/import FAIL for missing v2 symbols.

- [ ] **Step 3: Implement minimal Python mirror**

Keep `serialize()`/`parse()` unchanged for v1. Use `struct.pack_into/unpack_from`, explicit cursor bounds, dataclass default factories, tuple parent table, quaternion helpers, and the same deterministic TLV order as C. Implement the identical bounded 32-iteration `f16(normalize(...))` fixed-point selection for the v2 base wrist and all skeleton quaternions; normalize parsed finite/non-zero wire values without rejecting non-unit external input.

- [ ] **Step 4: Run green test**

Run: `python3 -m pytest relay/test_hand_token.py -q`
Expected: all tests pass, no skipped golden.

- [ ] **Step 5: Commit**

```bash
git add relay/hand_token.py relay/test_hand_token.py
git commit -m "feat(relay): mirror Hand Token v2 codec and FK"
```

### Task 5: Cross-Language Golden Contract

**Files:**
- Modify: `firmware/shared/test/test_hand_token.c`
- Modify: `relay/test_hand_token.py`

**Interfaces:**
- Constants in both tests: `GOLDEN_V1_HEX`, `GOLDEN_V2_LITE_HEX`, `GOLDEN_V2_SKELETON_HEX`.

- [ ] **Step 1: Generate candidate bytes independently**

After the Python mirror implements the identical quaternion fixed-point algorithm, generate candidate bytes independently for C and Python. Compare v1 plus v2 Lite and skeleton outputs before freezing constants.

- [ ] **Step 2: Compare before freezing**

The comparison must include non-unit finite ingest, canonical-frame `serialize(parse(frame))` stability, base and all skeleton quaternions, and both w-first/w-last ordering. Expected: exact C/Python bytes; otherwise stop and fix the codec, never choose one side as authority.

- [ ] **Step 3: Freeze nonempty constants and remove skips**

Replace old optional `GOLDEN_HEX=""` behavior. Each test must assert hex syntax, exact length, serialized bytes equal constant, and parsing the constant reconstructs the reference object.

- [ ] **Step 4: Run both suites**

Run: `make -C firmware/shared/test clean all && python3 -m pytest relay/test_hand_token.py -q`
Expected: both exit 0; zero skips; all three goldens pass.

- [ ] **Step 5: Commit**

```bash
git add firmware/shared/test/test_hand_token.c relay/test_hand_token.py
git commit -m "test(protocol): freeze v1 and v2 cross-language goldens"
```

### Task 6: Final Compatibility and Documentation Gate

**Files:**
- Modify: `docs/V7/07_dual_rep_layer.md`
- Modify: `docs/V7/ARCHITECTURE.md`
- Modify: `docs/superpowers/specs/2026-07-27-hand-token-v2-design.md`

**Interfaces:**
- Documents only code-verified behavior as ✅; adapters/exporters remain 🟡/🔬.

- [ ] **Step 1: Run clean verification matrix**

Run:
```bash
make -C firmware/shared/test clean all
python3 -m pytest relay/test_hand_token.py -q
git diff --check
```
Expected: all exit 0; no skipped tests.

- [ ] **Step 2: Run sanitizer host test**

Run:
```bash
make -C firmware/shared/test clean all CFLAGS='-std=c11 -Wall -Wextra -Werror -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```
Expected: exit 0, no ASan/UBSan report.

- [ ] **Step 3: Update implementation truth labels**

Record v2 C/Python codec, version-gate, FK, and goldens as ✅ only after Steps 1-2. Keep MANO fitting, retargeting, third-party adapters, and physical hardware integration at existing 🟡/🔬 levels. Update spec status to implemented with commit references only after commits exist.

- [ ] **Step 4: Update graph and inspect scope**

Run: `graphify update . && git diff --check && git status --short`
Expected: graph update succeeds; tracked changes are only planned source/test/docs files. Do not stage untracked `graphify-out/` unless repository policy is separately changed.

- [ ] **Step 5: Commit final docs**

```bash
git add docs/V7/07_dual_rep_layer.md docs/V7/ARCHITECTURE.md docs/superpowers/specs/2026-07-27-hand-token-v2-design.md
git commit -m "docs(protocol): mark Hand Token v2 P0 verified"
```

## Self-Review

- Spec coverage: canonical indices/FK, caps, TLV, rest model, 25 offsets, version gate, CRC, malformed input, unknown TLV, three goldens, v1 compatibility all mapped to Tasks 1-6.
- Explicitly excluded: smallest-three encoding, adapters/exporters, MANO/robot semantic models, hardware.
- Placeholder scan: no unresolved placeholder markers or unspecified test step remains.
- Type consistency: C and Python types/functions are defined once above and reused verbatim.
