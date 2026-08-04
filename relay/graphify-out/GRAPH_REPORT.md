# Graph Report - relay  (2026-08-03)

## Corpus Check
- 2 files · ~2,983 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 55 nodes · 175 edges · 9 communities (8 shown, 1 thin omitted)
- Extraction: 97% EXTRACTED · 3% INFERRED · 0% AMBIGUOUS · INFERRED: 5 edges (avg confidence: 0.8)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `a2808526`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- hand_token.py
- parse
- fk21
- parse_v2
- serialize_v2
- test_hand_token.py
- test_fk21_nonidentity_chain_matches_c_float32_fixture
- test_v2_rejects_malformed_c_cases_and_skips_unknown_tlv
- UnsupportedRestModelError

## God Nodes (most connected - your core abstractions)
1. `serialize_v2()` - 16 edges
2. `parse_v2()` - 15 edges
3. `fk21()` - 11 edges
4. `HandToken` - 10 edges
5. `parse()` - 10 edges
6. `test_v2_lite_wire_layout_and_version_gate()` - 10 edges
7. `serialize()` - 9 edges
8. `_validate_skeleton()` - 9 edges
9. `reference_v2()` - 9 edges
10. `HandSkeleton` - 8 edges

## Surprising Connections (you probably didn't know these)
- `test_v2_lite_wire_layout_and_version_gate()` --indirect_call--> `HandToken`  [INFERRED]
  test_hand_token.py → hand_token.py
- `test_v2_serializer_rejects_fields_that_become_nonfinite()` --indirect_call--> `serialize_v2()`  [INFERRED]
  test_hand_token.py → hand_token.py
- `reference_token()` --calls--> `HandToken`  [EXTRACTED]
  test_hand_token.py → hand_token.py
- `reference_skeleton()` --calls--> `HandSkeleton`  [EXTRACTED]
  test_hand_token.py → hand_token.py
- `test_fk21_identity_mapping_tips_and_model_errors()` --calls--> `HandSkeleton`  [EXTRACTED]
  test_hand_token.py → hand_token.py

## Import Cycles
- None detected.

## Communities (9 total, 1 thin omitted)

### Community 0 - "hand_token.py"
Cohesion: 0.29
Nodes (11): _canonical_quat(), _f16(), _f16_bits(), HandToken, _pack_f16(), Byte-compatible Hand Token v1 and v2 codecs., C-compatible float32 -> IEEE-754 binary16 RN-even conversion., to_mano() (+3 more)

### Community 1 - "parse"
Cohesion: 0.38
Nodes (10): crc16_modbus(), make_device_id(), parse(), parse_any(), serialize(), split_device_id(), reference_token(), test_f16_narrows_through_float32_at_rounding_boundary() (+2 more)

### Community 2 - "fk21"
Cohesion: 0.47
Nodes (6): _f32(), fk21(), _quat_mul(), Rotate with the same cross-product operation graph as C quat_rotate()., Narrow a Python float to the C model's IEEE-754 binary32 value., _rotate()

### Community 3 - "parse_v2"
Cohesion: 0.67
Nodes (6): HandSkeleton, _normalise(), parse_v2(), _read_base(), _validate_skeleton(), ValueError

### Community 4 - "serialize_v2"
Cohesion: 0.47
Nodes (6): HandTokenV2, serialize_v2(), reference_skeleton(), reference_v2(), test_v2_serializer_rejects_invalid_skeleton_contract(), test_v2_skeleton_layout_wlast_and_wfirst_round_trip()

### Community 5 - "test_hand_token.py"
Cohesion: 0.60
Nodes (4): assert_value_error(), Hand Token v1/v2 Python tests and C wire interoperability checks., test_fk21_identity_mapping_tips_and_model_errors(), test_v2_serializer_rejects_fields_that_become_nonfinite()

### Community 6 - "test_fk21_nonidentity_chain_matches_c_float32_fixture"
Cohesion: 0.40
Nodes (5): _float32_ordered_bits(), _float32_ulp_distance(), Direct C quat_rotate()/FK output fixture, stored as little-endian f32., Return monotonic float32 bits, rejecting nonfinite values., test_fk21_nonidentity_chain_matches_c_float32_fixture()

### Community 7 - "test_v2_rejects_malformed_c_cases_and_skips_unknown_tlv"
Cohesion: 0.67
Nodes (3): recalc_crc(), test_v2_parser_canonicalizes_finite_nonunit_quaternions(), test_v2_rejects_malformed_c_cases_and_skips_unknown_tlv()

## Knowledge Gaps
- **1 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `fk21()` connect `fk21` to `hand_token.py`, `parse_v2`, `test_hand_token.py`, `test_fk21_nonidentity_chain_matches_c_float32_fixture`, `UnsupportedRestModelError`?**
  _High betweenness centrality (0.059) - this node is a cross-community bridge._
- **Why does `serialize_v2()` connect `serialize_v2` to `hand_token.py`, `parse`, `parse_v2`, `test_hand_token.py`, `test_v2_rejects_malformed_c_cases_and_skips_unknown_tlv`?**
  _High betweenness centrality (0.059) - this node is a cross-community bridge._
- **Why does `_f16_bits()` connect `hand_token.py` to `parse_v2`, `test_hand_token.py`?**
  _High betweenness centrality (0.048) - this node is a cross-community bridge._
- **Are the 2 inferred relationships involving `serialize_v2()` (e.g. with `test_v2_serializer_rejects_fields_that_become_nonfinite()` and `test_v2_serializer_rejects_invalid_skeleton_contract()`) actually correct?**
  _`serialize_v2()` has 2 INFERRED edges - model-reasoned connections that need verification._