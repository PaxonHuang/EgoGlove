"""Boundary fixtures and validators for V8 Phase 1 (offline semantic fixtures).

Validates the frozen architecture boundary without touching transport::

    Hand Token v2  ->  Observation Layer  ->  (Episode Layer, later phase)

Each fixture reuses an existing offline Hand Token artifact (golden v2 skeleton,
golden v2 Lite, and an OpenXR-ingested frame) and wraps the decoded state in an
Observation plus its Coordinate Profile and Provenance record. See
docs/V8/06_SEMANTIC_FIXTURES.md.
"""
import copy

from hand_token import (
    V2_LITE_FRAME_SIZE,
    V2_SKELETON_FRAME_SIZE,
    parse_v2,
    serialize_v2,
)
from openxr_adapter import (
    OpenXRHandFrame,
    OpenXRJoint,
    OpenXRJointLocation,
    openxr_to_hand_token,
)
from test_hand_token import GOLDEN_V2_LITE_HEX, GOLDEN_V2_SKELETON_HEX

from semantic_fixtures import (
    FIELD_STATUSES,
    MOTION_FIELDS,
    CoordinateProfile,
    CoordinateTransform,
    ImplicitConversionError,
    ProvenanceRecord,
    Transformation,
    UnresolvedProfileError,
    assert_no_implicit_conversion,
    build_observation_from_token,
    digest_bytes,
    digest_payload,
    differing_conventions,
    make_frame_artifact,
    make_payload_artifact,
    observation_payload,
    provenance_lineage,
    validate_boundary,
    validate_coordinate_profile,
    validate_coordinate_transform,
    validate_observation,
    validate_provenance_record,
)

SEQUENCE_ID = "seq-0001"


def expect_error(error_type, fn, *args, **kwargs):
    try:
        fn(*args, **kwargs)
    except error_type:
        return
    raise AssertionError(f"expected {error_type.__name__}")


# ---------------------------------------------------------------------------
# Coordinate Profiles
# ---------------------------------------------------------------------------


def canonical_profile():
    """The V8 canonical semantic profile for decoded Hand Token (w-first)."""
    return CoordinateProfile(
        profile_id="egomotion.canonical",
        version="1.0.0",
        handedness="right",
        up_axis="+y",
        right_axis="+x",
        forward_axis="+z",
        length_unit="meter",
        angle_unit="radian",
        reference_frame="canonical_hand_frame",
        wrist_pose_scope="local",
        quaternion_order="wxyz",
        rotation_composition="parent_relative",
        clock_domain="device_monotonic_us",
        mirror_policy="none",
    )


def openxr_source_profile():
    """An OpenXR-style source profile (w-last, global, world frame, y-up)."""
    return CoordinateProfile(
        profile_id="openxr.runtime",
        version="1.0.0",
        handedness="right",
        up_axis="+y",
        right_axis="+x",
        forward_axis="-z",
        length_unit="meter",
        angle_unit="radian",
        reference_frame="world_frame",
        wrist_pose_scope="global",
        quaternion_order="xyzw",
        rotation_composition="global",
        clock_domain="openxr_display_time",
        mirror_policy="none",
    )


# ---------------------------------------------------------------------------
# Provenance assembly
# ---------------------------------------------------------------------------


def _validation_block():
    return {
        "checks": [
            "validate_coordinate_profile",
            "validate_observation",
            "validate_provenance_record",
            "validate_boundary",
        ],
        "metrics": {"fk21_ulp_tolerance": 24},
        "fixture_or_test_ref": "relay/test_semantic_fixtures.py",
        "status": "passed",
    }


def _policy_block():
    return {
        "license": "internal-fixture",
        "consent_class": "synthetic",
        "retention": "permanent",
        "permitted_use": "validation-only",
    }


def _decode_params():
    return digest_payload({"codec": "hand_token", "version": "2"})


def _fk_params(token):
    return digest_payload(
        {
            "method": "fk21",
            "index_map": "mediapipe-21",
            "rest_model_id": token.skeleton.model_id,
            "rest_revision": token.skeleton.revision,
        }
    )


def _decoded_state_payload(token):
    return {
        "canonical_20_rotation": [list(q) for q in token.skeleton.quat],
        "wrist_orientation_wxyz": list(token.base.quat),
        "rest_model_id": token.skeleton.model_id,
        "rest_revision": token.skeleton.revision,
    }


def build_provenance(record_id, source, observation, token, frame_bytes, upstream=None):
    """Assemble an immutable lineage: [upstream ->] frame -> decode -> derive -> observation."""
    artifacts = {}
    transformations = []

    if upstream is not None:
        source_art_id, source_payload, ingest_params = upstream
        artifacts[source_art_id] = make_payload_artifact(source_payload, source_art_id, "openxr.fixture")
        artifacts["artifact:frame"] = make_frame_artifact(frame_bytes, "artifact:frame", SEQUENCE_ID)
        transformations.append(
            Transformation(
                input_ref=source_art_id,
                operation="ingest_openxr",
                implementation_version="1",
                parameters_digest=digest_payload(ingest_params),
                output_ref="artifact:frame",
                deterministic=True,
            )
        )
    else:
        artifacts["artifact:frame"] = make_frame_artifact(frame_bytes, "artifact:frame", SEQUENCE_ID)

    artifacts["artifact:decoded_state"] = make_payload_artifact(
        _decoded_state_payload(token), "artifact:decoded_state", "hand_token.parse_v2"
    )
    transformations.append(
        Transformation(
            input_ref="artifact:frame",
            operation="decode",
            implementation_version="2",
            parameters_digest=_decode_params(),
            output_ref="artifact:decoded_state",
            deterministic=True,
        )
    )

    artifacts["artifact:observation"] = make_payload_artifact(
        observation_payload(observation), "artifact:observation", "semantic_fixtures.build_observation_from_token"
    )
    transformations.append(
        Transformation(
            input_ref="artifact:decoded_state",
            operation="derive_fk21",
            implementation_version="0.1.0",
            parameters_digest=_fk_params(token),
            output_ref="artifact:observation",
            deterministic=True,
        )
    )

    record = ProvenanceRecord(
        record_id=record_id,
        source=source,
        acquisition={
            "clock_domain": observation.clock_domain,
            "time_range": (observation.observed_at, observation.observed_at),
            "calibration_ref": "n/a",
        },
        artifacts=artifacts,
        transformations=tuple(transformations),
        validation=_validation_block(),
        policy=_policy_block(),
    )
    validate_provenance_record(record)
    return record


# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


def golden_skeleton_fixture():
    """Full Pro right-hand v2 skeleton frame -> Observation (all fields available)."""
    frame_bytes = bytes.fromhex(GOLDEN_V2_SKELETON_HEX)
    token = parse_v2(frame_bytes)
    profile = canonical_profile()
    observation = build_observation_from_token(
        token,
        frame_bytes,
        profile,
        provenance_ref="prov:golden_skeleton",
        observation_id="obs:golden_skeleton",
        sequence_id=SEQUENCE_ID,
        available_fields=MOTION_FIELDS,
        hand_scope="right",
        confidence=1.0,
    )
    source = {
        "origin": "fixture",
        "source_format": "hand_token_golden_hex",
        "source_version": "v2",
        "device": "pro_right",
        "operator_or_session": "golden_skeleton",
    }
    provenance = build_provenance("prov:golden_skeleton", source, observation, token, frame_bytes)
    return frame_bytes, token, profile, observation, provenance


def openxr_fixture():
    """OpenXR 26-joint frame -> ingest -> Hand Token -> Observation (masked fields)."""
    joints = {
        joint: OpenXRJointLocation(
            joint=joint,
            position=[0.05 * int(joint), 0.01 * (int(joint) % 4), 0.02 * (int(joint) % 3)],
            orientation=[0.0, 0.0, 0.0, 1.0],
        )
        for joint in OpenXRJoint
    }
    openxr_frame = OpenXRHandFrame(joints=joints, hand=1, product=1, serial=9, timestamp_us=42000)
    token = openxr_to_hand_token(openxr_frame)
    frame_bytes = serialize_v2(token)
    token = parse_v2(frame_bytes)

    profile = canonical_profile()
    available = ("canonical_20_rotation", "wrist_pose", "derived_landmarks_21")
    observation = build_observation_from_token(
        token,
        frame_bytes,
        profile,
        provenance_ref="prov:openxr",
        observation_id="obs:openxr",
        sequence_id=SEQUENCE_ID,
        available_fields=available,
        hand_scope="right",
        confidence=0.9,
    )
    source = {
        "origin": "openxr_runtime",
        "source_format": "xr_ext_hand_tracking",
        "source_version": "1",
        "device": "openxr_hmd",
        "operator_or_session": "openxr_fixture",
    }
    source_payload = {
        "joints": {
            joint.name: {
                "position": list(loc.position),
                "orientation_xyzw": list(loc.orientation),
            }
            for joint, loc in openxr_frame.joints.items()
        }
    }
    upstream = ("artifact:openxr_source", source_payload, {"adapter": "openxr_to_hand_token", "rest_model_id": 2})
    provenance = build_provenance("prov:openxr", source, observation, token, frame_bytes, upstream=upstream)
    return frame_bytes, token, profile, observation, provenance


def lite_fixture():
    """v2 Lite frame (no skeleton) -> Observation (skeleton fields masked out)."""
    frame_bytes = bytes.fromhex(GOLDEN_V2_LITE_HEX)
    token = parse_v2(frame_bytes)
    profile = canonical_profile()
    available = ("wrist_pose", "joint_angles", "velocity", "acceleration", "contact", "force")
    observation = build_observation_from_token(
        token,
        frame_bytes,
        profile,
        provenance_ref="prov:lite",
        observation_id="obs:lite",
        sequence_id=SEQUENCE_ID,
        available_fields=available,
        hand_scope="right",
        confidence=1.0,
    )
    source = {
        "origin": "fixture",
        "source_format": "hand_token_golden_hex",
        "source_version": "v2_lite",
        "device": "pro_right",
        "operator_or_session": "golden_lite",
    }
    # No skeleton, so the lineage is frame -> decode -> observation (no derive step).
    artifacts = {
        "artifact:frame": make_frame_artifact(frame_bytes, "artifact:frame", SEQUENCE_ID),
        "artifact:observation": make_payload_artifact(
            observation_payload(observation), "artifact:observation", "semantic_fixtures.build_observation_from_token"
        ),
    }
    transformations = (
        Transformation(
            input_ref="artifact:frame",
            operation="decode",
            implementation_version="2",
            parameters_digest=_decode_params(),
            output_ref="artifact:observation",
            deterministic=True,
        ),
    )
    provenance = ProvenanceRecord(
        record_id="prov:lite",
        source=source,
        acquisition={
            "clock_domain": observation.clock_domain,
            "time_range": (observation.observed_at, observation.observed_at),
            "calibration_ref": "n/a",
        },
        artifacts=artifacts,
        transformations=transformations,
        validation=_validation_block(),
        policy=_policy_block(),
    )
    validate_provenance_record(provenance)
    return frame_bytes, token, profile, observation, provenance


# ---------------------------------------------------------------------------
# Requirement 1: Hand Token remains the Motion Transport Layer
# ---------------------------------------------------------------------------


def test_transport_frame_round_trips_unmodified():
    for frame_hex, size in ((GOLDEN_V2_SKELETON_HEX, V2_SKELETON_FRAME_SIZE), (GOLDEN_V2_LITE_HEX, V2_LITE_FRAME_SIZE)):
        frame_bytes = bytes.fromhex(frame_hex)
        assert len(frame_bytes) == size
        assert serialize_v2(parse_v2(frame_bytes)) == frame_bytes


def test_observation_anchors_to_frame_without_mutating_token():
    frame_bytes, token, _, observation, _ = golden_skeleton_fixture()
    assert observation.raw_transport_ref.codec == "hand_token"
    assert observation.raw_transport_ref.codec_version == "2"
    assert observation.raw_transport_ref.frame_digest == digest_bytes(frame_bytes)
    # Building the observation must not perturb the transport token.
    assert serialize_v2(token) == frame_bytes


def test_semantic_metadata_never_enters_the_wire():
    frame_bytes, token, _, observation, _ = golden_skeleton_fixture()
    reserialized = serialize_v2(token)
    assert len(reserialized) == V2_SKELETON_FRAME_SIZE
    assert parse_v2(reserialized).caps == token.caps
    # The Observation/Profile/Provenance schema lives entirely off-wire.
    assert observation.coordinate_profile_id not in reserialized.hex()


def test_boundary_accepts_all_three_fixtures():
    for fixture in (golden_skeleton_fixture, openxr_fixture, lite_fixture):
        _, _, profile, observation, provenance = fixture()
        validate_boundary(observation, profile, provenance)


# ---------------------------------------------------------------------------
# Requirement 2: Observation remains the semantic layer
# ---------------------------------------------------------------------------


def test_fk21_landmarks_are_derived_with_full_metadata():
    _, _, _, observation, _ = golden_skeleton_fixture()
    provenance = observation.field_status["derived_landmarks_21"]
    assert provenance.status == "derived"
    derivation = provenance.derivation
    assert derivation["method"] == "fk21"
    assert derivation["topology"] == "canonical-20"
    assert derivation["index_map"] == "mediapipe-21"
    assert "rest_model_id" in derivation and "rest_revision" in derivation
    assert observation.availability_mask["derived_landmarks_21"] is True


def test_field_status_vocabulary_is_enforced():
    _, _, _, observation, _ = golden_skeleton_fixture()
    for field_provenance in observation.field_status.values():
        assert field_provenance.status in FIELD_STATUSES

    broken = copy.deepcopy(observation)
    broken.field_status["joint_angles"] = type(observation.field_status["joint_angles"])(status="invented")
    expect_error(ValueError, validate_observation, broken)


def test_landmarks_cannot_be_marked_measured():
    _, _, _, observation, _ = golden_skeleton_fixture()
    broken = copy.deepcopy(observation)
    field_type = type(observation.field_status["derived_landmarks_21"])
    broken.field_status["derived_landmarks_21"] = field_type(status="measured")
    expect_error(ValueError, validate_observation, broken)


def test_derived_value_requires_derivation_metadata():
    _, _, _, observation, _ = golden_skeleton_fixture()
    broken = copy.deepcopy(observation)
    field_type = type(observation.field_status["derived_landmarks_21"])
    broken.field_status["derived_landmarks_21"] = field_type(status="derived", derivation=None)
    expect_error(ValueError, validate_observation, broken)


def test_decoded_field_must_not_carry_derivation():
    _, _, _, observation, _ = golden_skeleton_fixture()
    broken = copy.deepcopy(observation)
    field_type = type(observation.field_status["joint_angles"])
    broken.field_status["joint_angles"] = field_type(status="decoded", derivation={"method": "fk21", "input_fields": ["x"]})
    expect_error(ValueError, validate_observation, broken)


def test_availability_mask_forbids_zero_masquerade():
    _, _, _, observation, _ = lite_fixture()
    # Lite has no skeleton: the skeleton fields are masked, not zero-filled.
    assert observation.motion.canonical_20_rotation is None
    assert observation.motion.derived_landmarks_21 is None
    assert observation.availability_mask["canonical_20_rotation"] is False
    assert observation.availability_mask["derived_landmarks_21"] is False
    assert observation.motion.joint_angles is not None

    _, _, _, full, _ = golden_skeleton_fixture()
    broken = copy.deepcopy(full)
    broken.availability_mask["joint_angles"] = False  # masked but still carries a value
    expect_error(ValueError, validate_observation, broken)


def test_openxr_observation_masks_unsourced_fields():
    _, _, _, observation, _ = openxr_fixture()
    # OpenXR sources rotations, not flex/force/contact: those stay masked.
    for name in ("joint_angles", "velocity", "acceleration", "contact", "force"):
        assert observation.availability_mask[name] is False
        assert getattr(observation.motion, name) is None
    assert observation.availability_mask["derived_landmarks_21"] is True


# ---------------------------------------------------------------------------
# Requirement 3: Coordinate Profile prevents implicit conversion
# ---------------------------------------------------------------------------


def test_profiles_are_complete_and_distinct():
    canonical = canonical_profile()
    openxr = openxr_source_profile()
    validate_coordinate_profile(canonical)
    validate_coordinate_profile(openxr)
    diff = differing_conventions(canonical, openxr)
    assert "quaternion_order" in diff  # w-first vs w-last
    assert "reference_frame" in diff


def test_incomplete_profile_is_rejected_not_guessed():
    canonical = canonical_profile()
    broken = copy.deepcopy(canonical)
    object.__setattr__(broken, "quaternion_order", "")
    expect_error(ValueError, validate_coordinate_profile, broken)
    object.__setattr__(broken, "quaternion_order", "w-first")  # not a controlled token
    expect_error(ValueError, validate_coordinate_profile, broken)


def test_implicit_cross_profile_conversion_is_blocked():
    canonical = canonical_profile()
    openxr = openxr_source_profile()
    # Same profile: no conversion needed, no error.
    assert_no_implicit_conversion(canonical, canonical)
    # Differing conventions with no declared transform: refused.
    expect_error(ImplicitConversionError, assert_no_implicit_conversion, canonical, openxr)


def test_explicit_transform_must_declare_every_difference():
    canonical = canonical_profile()
    openxr = openxr_source_profile()
    changes = differing_conventions(canonical, openxr)

    # A transform that only owns the quaternion reorder but ignores the rest is
    # rejected: partial conversion is still implicit conversion.
    partial = CoordinateTransform(
        source_profile_id=canonical.profile_id,
        target_profile_id=openxr.profile_id,
        parent_frame=canonical.reference_frame,
        child_frame=openxr.reference_frame,
        nature="static",
        convention_changes=frozenset({"quaternion_order"}),
        operation="quaternion_reorder_wxyz_to_xyzw",
        parameters_digest=digest_payload({"order": ["w", "x", "y", "z"]}),
        deterministic=True,
    )
    expect_error(ValueError, validate_coordinate_transform, partial, canonical, openxr)

    full = CoordinateTransform(
        source_profile_id=canonical.profile_id,
        target_profile_id=openxr.profile_id,
        parent_frame=canonical.reference_frame,
        child_frame=openxr.reference_frame,
        nature="static",
        convention_changes=changes,
        operation="reexpress_openxr_as_canonical",
        parameters_digest=digest_payload({"changes": sorted(changes)}),
        deterministic=True,
        calibration_ref="n/a",
    )
    validate_coordinate_transform(full, canonical, openxr)
    assert_no_implicit_conversion(canonical, openxr, full)


def test_unresolved_profile_cannot_claim_normalization():
    frame_bytes, token, profile, _, provenance = golden_skeleton_fixture()
    unresolved = build_observation_from_token(
        token,
        frame_bytes,
        profile,
        provenance_ref="prov:golden_skeleton",
        observation_id="obs:unresolved",
        sequence_id=SEQUENCE_ID,
        available_fields=MOTION_FIELDS,
        hand_scope="right",
        normalized=False,
    )
    expect_error(UnresolvedProfileError, validate_boundary, unresolved, profile, provenance)


def test_observation_clock_must_match_its_profile():
    frame_bytes, token, profile, observation, provenance = golden_skeleton_fixture()
    wrong_clock = copy.deepcopy(profile)
    object.__setattr__(wrong_clock, "clock_domain", "openxr_display_time")
    expect_error(ValueError, validate_boundary, observation, wrong_clock, provenance)


# ---------------------------------------------------------------------------
# Requirement 4: Provenance tracks source and transformation lineage
# ---------------------------------------------------------------------------


def test_provenance_lineage_is_ordered_and_connected():
    _, _, _, observation, provenance = golden_skeleton_fixture()
    lineage = provenance_lineage(provenance)
    assert lineage == ["artifact:frame", "artifact:decoded_state", "artifact:observation"]
    # The OpenXR fixture carries an upstream source ahead of the transport frame.
    _, _, _, openxr_obs, openxr_prov = openxr_fixture()
    assert provenance_lineage(openxr_prov)[0] == "artifact:openxr_source"
    assert "artifact:frame" in provenance_lineage(openxr_prov)


def test_provenance_records_transport_frame_identity():
    frame_bytes, _, _, observation, provenance = golden_skeleton_fixture()
    frame_artifact = provenance.artifacts["artifact:frame"]
    assert frame_artifact.schema_id == "hand_token"
    assert frame_artifact.schema_version == "2"
    assert frame_artifact.content_digest == digest_bytes(frame_bytes)


def test_unknown_transformation_endpoint_is_rejected():
    _, _, _, observation, provenance = golden_skeleton_fixture()
    bad = copy.deepcopy(provenance)
    object.__setattr__(
        bad,
        "transformations",
        provenance.transformations
        + (Transformation("artifact:ghost", "decode", "2", digest_payload({}), "artifact:observation", True),),
    )
    expect_error(ValueError, validate_provenance_record, bad)


def test_lineage_overwrite_is_rejected():
    _, _, _, observation, provenance = golden_skeleton_fixture()
    bad = copy.deepcopy(provenance)
    object.__setattr__(
        bad,
        "transformations",
        provenance.transformations
        + (Transformation("artifact:decoded_state", "recompute", "2", digest_payload({}), "artifact:observation", True),),
    )
    expect_error(ValueError, validate_provenance_record, bad)


def test_policy_requires_license_and_use():
    _, _, _, observation, provenance = golden_skeleton_fixture()
    bad = copy.deepcopy(provenance)
    policy = dict(provenance.policy)
    policy.pop("license")
    object.__setattr__(bad, "policy", policy)
    expect_error(ValueError, validate_provenance_record, bad)


def test_tampered_observation_breaks_terminal_digest():
    frame_bytes, token, profile, observation, provenance = golden_skeleton_fixture()
    validate_boundary(observation, profile, provenance)
    tampered = copy.deepcopy(observation)
    tampered.motion.derived_landmarks_21[0][0] += 0.5
    validate_observation(tampered)  # still structurally valid
    expect_error(ValueError, validate_boundary, tampered, profile, provenance)


def test_mismatched_reference_is_rejected():
    frame_bytes, token, profile, observation, provenance = golden_skeleton_fixture()
    wrong_profile = copy.deepcopy(profile)
    object.__setattr__(wrong_profile, "profile_id", "egomotion.other")
    expect_error(ValueError, validate_boundary, observation, wrong_profile, provenance)


if __name__ == "__main__":
    failures = 0
    for name, value in sorted(globals().items()):
        if name.startswith("test_") and callable(value):
            try:
                value()
                print(f"[ ok ] {name}")
            except Exception as exc:
                failures += 1
                print(f"[FAIL] {name}: {exc}")
    raise SystemExit(bool(failures))
