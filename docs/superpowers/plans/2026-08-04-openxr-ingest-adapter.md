# OpenXR Ingest Adapter Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a typed, schema-neutral offline OpenXR 26-joint global-pose adapter that emits the existing canonical-20 `HandTokenV2` without changing the frozen Hand Token wire format or topology.

**Architecture:** Add a focused `relay/openxr_adapter.py` boundary containing OpenXR-shaped dataclasses and a pure conversion function. The adapter validates a complete frame, maps OpenXR joints into the existing canonical-20 order, converts global w-last poses to canonical parent-relative w-first quaternions, derives all 25 rest offsets, and returns a skeleton-bearing `HandTokenV2` using existing model id 2. Existing `serialize_v2()`, `parse_v2()`, and `fk21()` remain the only wire/FK boundaries.

**Tech Stack:** Dependency-free Python standard library (`dataclasses`, `enum`, `math`), existing `relay/hand_token.py`, repository-style dependency-free tests in `relay/test_openxr_adapter.py`.

## Global Constraints

- Do not add an OpenXR runtime dependency, streaming, WebSocket, FastAPI, or device integration.
- Do not modify Hand Token v1/v2 wire format, canonical-20 topology, existing TLVs, or frozen golden behavior.
- OpenXR input uses 26 global poses, meter positions, and source quaternion order `x,y,z,w`.
- Internal output quaternions are finite, normalized, parent-relative `w,x,y,z`.
- OpenXR `PALM` and five `TIP` joints are not canonical rotation joints; their positions are used only to derive offsets.
- Invalid or unavailable required joint data must fail explicitly; do not silently fabricate poses.
- Keep changes limited to the adapter, focused tests, and a narrowly scoped architecture/status documentation update.
- Before commit, verify `PaxonHuang <quenchkidney@outlook.com>`, run `git diff --check`, run tests, and run `graphify update .` as required by `CLAUDE.md`.

---

### Task 1: Define the typed OpenXR input boundary and failing fixtures

**Files:**
- Create: `relay/openxr_adapter.py`
- Create: `relay/test_openxr_adapter.py`

**Interfaces:**
- Produces `OpenXRJointLocation`, `OpenXRHandFrame`, `OpenXRJoint` identifiers, and the public function signature `openxr_to_hand_token(frame: OpenXRHandFrame) -> HandTokenV2`.
- Consumes existing `HandToken`, `HandSkeleton`, and `HandTokenV2` from `relay/hand_token.py`.

- [ ] **Step 1: Define the OpenXR joint identifiers and dataclasses in the new module.**

Use a stable integer-backed enum for all 26 OpenXR identifiers in spec order: `PALM`, `WRIST`, thumb `METACARPAL/PROXIMAL/DISTAL/TIP`, and index/middle/ring/little `METACARPAL/PROXIMAL/INTERMEDIATE/DISTAL/TIP`.

Define:

```python
@dataclass(frozen=True)
class OpenXRJointLocation:
    joint: OpenXRJoint
    position: List[float]
    orientation: List[float]  # source order x, y, z, w
    location_valid: bool = True
    orientation_valid: bool = True
    confidence: Optional[float] = None
    radius: Optional[float] = None
```

and:

```python
@dataclass(frozen=True)
class OpenXRHandFrame:
    joints: Mapping[OpenXRJoint, OpenXRJointLocation]
    hand: int = HAND_LEFT
    product: int = PRODUCT_PRO
    serial: int = 0
    timestamp_us: int = 0
```

Export the public names through `__all__`. Keep the input schema independent of any Khronos/runtime package.

- [ ] **Step 2: Add synthetic 26-joint fixture helpers and tests that describe the contract.**

Create a fixture with every joint present, valid, finite, and identity-oriented. Give each canonical parent-child joint a deterministic global position and give each discarded tip a distinct position. Add tests for:

```python
def test_openxr_fixture_contains_all_26_joints(): ...
def test_openxr_missing_or_invalid_required_joint_is_rejected(): ...
def test_openxr_bad_vector_lengths_nonfinite_and_confidence_are_rejected(): ...
```

Require confidence, when supplied, to be finite and in `[0.0, 1.0]`; treat `None` as “not provided” rather than inventing a value. Require all 26 records, valid position/orientation flags, 3-position and 4-quaternion shapes, and finite values.

- [ ] **Step 3: Run the new test file and confirm the tests fail for missing conversion behavior.**

Run:

```bash
cd /home/EchoGloveHugeProjects/EgoGlove
python3 relay/test_openxr_adapter.py
```

Expected: the module imports, but conversion/mapping tests fail until Task 2 is implemented. Do not install pytest or other dependencies.

- [ ] **Step 4: Commit the typed boundary and contract tests.**

```bash
git add relay/openxr_adapter.py relay/test_openxr_adapter.py
git commit -m "test(relay): define OpenXR ingest boundary"
```

---

### Task 2: Implement global-pose conversion to canonical Hand Token v2

**Files:**
- Modify: `relay/openxr_adapter.py`
- Modify: `relay/test_openxr_adapter.py`

**Interfaces:**
- Consumes `OpenXRHandFrame`.
- Produces `HandTokenV2(base=HandToken(...), caps=HAND_TOKEN_CAP_HAS_SKELETON, has_skeleton=True, skeleton=HandSkeleton(...))`.

- [ ] **Step 1: Add mapping constants matching the frozen canonical topology.**

Define explicit canonical-index mappings for wrist and the 19 articulated OpenXR joints, plus the five canonical distal parents and five OpenXR tip joints. Do not derive the mapping from enum ordering implicitly. The mapping must be:

```text
canonical 0  <- WRIST
t 1..3      <- THUMB METACARPAL, PROXIMAL, DISTAL
canonical 4..7 <- INDEX METACARPAL, PROXIMAL, INTERMEDIATE, DISTAL
canonical 8..11 <- MIDDLE METACARPAL, PROXIMAL, INTERMEDIATE, DISTAL
canonical 12..15 <- RING METACARPAL, PROXIMAL, INTERMEDIATE, DISTAL
canonical 16..19 <- LITTLE METACARPAL, PROXIMAL, INTERMEDIATE, DISTAL
```

Use the existing `_PARENT` relationship from `hand_token.py` conceptually, but keep adapter-local maps explicit and avoid changing private codec topology constants.

- [ ] **Step 2: Add quaternion helpers with the existing float32 arithmetic conventions.**

Implement local helpers for source `xyzw` → internal `wxyz`, conjugate/inverse of normalized global quaternions, and parent-relative composition:

```python
local = normalize(conjugate(parent_global) * child_global)
```

Use existing `_normalise`, `_quat_mul`, and `_f32` from `hand_token.py` where importing private helpers is consistent with the current module style; otherwise wrap them in small adapter helpers without introducing a second wire implementation. Validate that all resulting quaternions are finite and nonzero.

- [ ] **Step 3: Derive the 20 canonical parent offsets and five tip offsets.**

For each canonical joint, calculate its parent-to-child vector from global positions and express it in the parent’s global rotation frame:

```python
offset = rotate(conjugate(parent_global), child_global_position - parent_global_position)
```

Set `offsets[0]` to `[0.0, 0.0, 0.0]`. Store canonical offsets at indices `1..19`; store distal-to-tip offsets at indices `20..24` in thumb/index/middle/ring/little order. Use the source global pose positions and global orientations—not arbitrary rest constants—because the adapter’s self-contained frame must reproduce the source geometry through `fk21()`.

- [ ] **Step 4: Construct the v2 object without changing codec behavior.**

Return a `HandTokenV2` with:

```python
base = HandToken(
    product=frame.product,
    hand=frame.hand,
    serial=frame.serial,
    timestamp_us=frame.timestamp_us,
    quat=source_wrist_orientation_wxyz,
)
skeleton = HandSkeleton(
    quat=canonical_parent_relative_quaternions,
    offsets=derived_25_offsets,
    model_id=2,
    revision=1,
)
return HandTokenV2(
    base=base,
    caps=HAND_TOKEN_CAP_HAS_SKELETON,
    has_skeleton=True,
    skeleton=skeleton,
)
```

Do not set `HAND_TOKEN_CAP_QUAT_WLAST`: it describes emitted wire order, while adapter output is canonical internal w-first. Do not add provenance or new TLVs.

- [ ] **Step 5: Add conversion tests for mapping, quaternion math, and offsets.**

Add tests with a non-identity synthetic frame that assert:

```python
def test_openxr_mapping_preserves_canonical_joint_order(): ...
def test_openxr_global_wlast_rotations_become_parent_relative_wfirst(): ...
def test_openxr_derives_20_joint_and_5_tip_offsets(): ...
```

Use a simple parent chain with known rotations (for example a wrist rotation and a child rotation) so the expected local quaternion can be checked numerically. Check all 25 offset slots, including the wrist zero and five tip offsets. Assert metadata and `model_id == 2`, `revision == 1`.

- [ ] **Step 6: Run focused tests and confirm conversion behavior passes.**

Run:

```bash
cd /home/EchoGloveHugeProjects/EgoGlove
python3 relay/test_openxr_adapter.py
```

Expected: all adapter tests pass. If numeric comparisons are needed, use explicit tolerances appropriate to float32 arithmetic; do not loosen validation to hide a mapping error.

- [ ] **Step 7: Commit the conversion implementation.**

```bash
git add relay/openxr_adapter.py relay/test_openxr_adapter.py
git commit -m "feat(relay): add OpenXR canonical ingest adapter"
```

---

### Task 3: Verify v2 serialization and FK21 compatibility

**Files:**
- Modify: `relay/test_openxr_adapter.py`
- Do not modify: `relay/hand_token.py` or firmware wire implementation

**Interfaces:**
- Consumes `openxr_to_hand_token()`.
- Verifies compatibility with existing `serialize_v2()`, `parse_v2()`, and `fk21()`.

- [ ] **Step 1: Add serialization round-trip tests.**

Add:

```python
def test_openxr_output_serializes_as_existing_v2_skeleton_frame(): ...
def test_openxr_output_round_trips_without_wire_changes(): ...
```

Assert the output has length `V2_SKELETON_FRAME_SIZE` (405 bytes), serializes successfully, parses as `HandTokenV2`, retains skeleton/model metadata, and satisfies the existing canonical stability invariant:

```python
assert serialize_v2(parse_v2(serialize_v2(token))) == serialize_v2(token)
```

Do not add or alter golden constants; this is compatibility coverage, not a new protocol format.

- [ ] **Step 2: Add FK21 source-position validation.**

Call `fk21(token.skeleton)` and compare its 21 landmarks against the synthetic OpenXR source positions in MediaPipe order: wrist, thumb four points, index four, middle four, ring four, little four. Because serialization is f16, test the pre-serialization adapter output with a tight float32 tolerance and the parsed/serialized output with a documented f16 tolerance.

- [ ] **Step 3: Run both adapter and existing Hand Token tests.**

Run:

```bash
cd /home/EchoGloveHugeProjects/EgoGlove
python3 relay/test_openxr_adapter.py
python3 relay/test_hand_token.py
```

Expected: all adapter tests and all existing dependency-free Hand Token tests pass; frozen v1/v2 goldens remain unchanged.

- [ ] **Step 4: Commit verification coverage.**

```bash
git add relay/test_openxr_adapter.py
git commit -m "test(relay): verify OpenXR v2 and FK compatibility"
```

---

### Task 4: Update narrowly scoped architecture/status documentation

**Files:**
- Modify: `docs/V7/ARCHITECTURE.md` (OpenXR adapter status section only)
- Modify: `docs/V7/README.md` or the nearest existing adapter index section, only if it already contains the adapter inventory

**Interfaces:**
- Documents the implemented offline adapter and its boundaries; does not define a new protocol contract.

- [ ] **Step 1: Locate the existing adapter/integration status text and update only the relevant OpenXR entry.**

State that OpenXR is an implemented (`✅`) schema-neutral offline ingest layer accepting 26 global joint poses and emitting canonical-20 `HandTokenV2`; explicitly state that runtime capture, streaming, and device integration are not implemented. Preserve the project’s realism labels and do not mark FreeMoCap IK, MANO regression, ROS2, Unity, Hi5, Manus, or mHand as implemented by this change.

- [ ] **Step 2: Review the documentation diff for scope and truthfulness.**

Run:

```bash
git diff -- docs/V7/ARCHITECTURE.md docs/V7/README.md
```

Expected: only the OpenXR adapter status/boundary is changed, with no strategic or wire-format rewrite.

- [ ] **Step 3: Commit the documentation update.**

```bash
git add docs/V7/ARCHITECTURE.md docs/V7/README.md
git commit -m "docs: record OpenXR ingest adapter boundary"
```

---

### Task 5: Final verification, graph update, and milestone commit/push

**Files:**
- Modify only generated graph outputs from `graphify update .` as required.

- [ ] **Step 1: Inspect identity and working tree.**

Run:

```bash
cd /home/EchoGloveHugeProjects/EgoGlove
git config user.name
git config user.email
git status --short
git diff --check
```

Expected identity: `PaxonHuang` and `quenchkidney@outlook.com`. Do not clean unrelated generated files (`firmware/shared/test/test_hand_token` or existing `relay/graphify-out/`).

- [ ] **Step 2: Run the full dependency-free regression set.**

Run:

```bash
python3 relay/test_openxr_adapter.py
python3 relay/test_hand_token.py
```

Expected: both runners pass with zero failures. Do not install pytest merely to satisfy the check.

- [ ] **Step 3: Update the knowledge graph.**

Run:

```bash
graphify update .
```

Review the resulting graph diff/status and ensure no unrelated source changes were introduced.

- [ ] **Step 4: Review the complete milestone diff and history.**

Run:

```bash
git status --short
git diff --check
git log --oneline -5
git diff HEAD~4..HEAD --stat
```

Confirm the commits contain only the adapter, focused tests, scoped docs, and graph update artifacts.

- [ ] **Step 5: Create the milestone commit if any final uncommitted implementation/docs/graph changes remain.**

```bash
git add relay/openxr_adapter.py relay/test_openxr_adapter.py docs/V7/ARCHITECTURE.md docs/V7/README.md graphify-out
git commit -m "feat(relay): complete OpenXR ingest milestone"
```

If the task commits already contain all intended changes, do not create an empty commit.

- [ ] **Step 6: Push only after the requested verification succeeds.**

```bash
git push origin feature/handtoken-v2-open-hand-infra
```

Report the exact commit(s), test commands/results, graphify result, and any pre-existing unrelated working-tree artifacts. Do not claim pytest success because pytest is not installed.
