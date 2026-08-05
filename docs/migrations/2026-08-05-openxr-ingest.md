# OpenXR Ingest Adapter Milestone

## Scope

OpenXR is an adapter input ecosystem, not the source of Hand Token topology. The implemented boundary is:

```text
OpenXR 26-joint global poses
        -> OpenXRJointLocation / OpenXRHandFrame
        -> openxr_to_hand_token()
        -> canonical-20 HandTokenV2 skeleton
```

The adapter is schema-neutral and offline. It does not depend on an OpenXR runtime or binding, open a device stream, or provide WebSocket/FastAPI transport.

## Implemented Boundary

`relay/openxr_adapter.py` provides:

- `OpenXRJoint`, an explicit 26-joint identifier set;
- `OpenXRJointLocation`, including position, source `x,y,z,w` orientation, validity flags, optional confidence, and radius;
- `OpenXRHandFrame`, including the complete joint map and Hand Token metadata;
- `validate_openxr_frame()`, which rejects missing, invalid, malformed, non-finite, or out-of-range input;
- `openxr_to_hand_token()`, which returns the existing `HandTokenV2` type.

The conversion maps OpenXR `WRIST` plus 19 articulated joints into the frozen canonical-20 order. `PALM` and the five OpenXR fingertip records are not added as rotation joints; their positions are used for the self-contained rest-offset table.

Global OpenXR poses are converted to parent-relative canonical quaternions using internal `w,x,y,z` order. The output uses rest model id `2`, revision `1`, and the existing `HAS_SKELETON` capability. It does not add capabilities or TLVs.

## Compatibility Evidence

The adapter is covered by dependency-free synthetic tests in `relay/test_openxr_adapter.py`:

- complete 26-joint fixture and validation failures;
- canonical mapping and metadata preservation;
- global w-last to parent-relative w-first quaternion conversion;
- all 20 parent offsets plus five distal-to-tip offsets;
- existing 405-byte v2 skeleton serialization and parse round trip;
- FK21 reconstruction of source landmarks before and after f16 serialization.

The existing `relay/test_hand_token.py` regression suite remains the authority for v1 79-byte compatibility, v2 Lite/skeleton goldens, malformed frames, quaternion canonicalization, and C/Python FK parity. The OpenXR milestone did not modify `relay/hand_token.py`, the v2 wire layout, `firmware/shared/`, or the frozen golden frames.

## Current Roadmap Checkpoint

- **P0:** Hand Token v1/v2 codec, canonical-20 skeleton, FK21, C/Python wire parity, and goldens: completed in the preceding protocol milestone.
- **P1:** OpenXR offline ingest adapter: implemented and verified.
- **P1 remaining:** FreeMoCap 21-position ingest requires an explicit IK/ambiguity boundary; MANO, ROS2, Unity XR, and robot exporters remain separate work.
- **P2:** Physical Hi5/Manus/mHand streams: not started; external schemas and device integration remain outside this milestone.
- **P3:** Pro hardware expansion: roadmap only.

The next engineering phase should be selected from the remaining P1 adapter/exporter work after an independent scope review. Do not begin EgoMotion branding, repository renaming, or GitHub migration as part of this protocol milestone.
