"""V8 offline semantic fixtures and validators (Phase 1).

Offline, dependency-free scaffolding that exercises the frozen architecture
boundary::

    Hand Token v2 (Motion Transport Layer)
        -> decode
    Observation Layer (semantic state container)
        -> Coordinate Profile + Provenance Model

This module only *reads* already-decoded Hand Token state and wraps it in
semantic metadata for validation. It does NOT modify Hand Token v2, add TLV
fields, touch firmware, integrate LeRobot, add runtime services, install ML
dependencies, or build dataset pipelines. See docs/V8/06_SEMANTIC_FIXTURES.md
and the layer contracts under docs/V8/.
"""
from __future__ import annotations

import hashlib
import json
import math
from dataclasses import dataclass
from typing import Dict, List, Mapping, Optional, Sequence, Tuple

from hand_token import HandTokenV2, fk21

SCHEMA_ID = "egomotion.observation"
SCHEMA_VERSION = "0.1.0"
HAND_TOKEN_CODEC_ID = "hand_token"
HAND_TOKEN_CODEC_VERSION = "2"
HAND_TOKEN_FRAME_MEDIA_TYPE = "application/x-hand-token-frame"

# --- Field-status vocabulary (docs/V8/01_OBSERVATION_LAYER.md §1, §3a) ---
STATUS_DECODED = "decoded"
STATUS_MEASURED = "measured"
STATUS_DERIVED = "derived"
STATUS_ESTIMATED = "estimated"
STATUS_FUSED = "fused"
FIELD_STATUSES = frozenset(
    {STATUS_DECODED, STATUS_MEASURED, STATUS_DERIVED, STATUS_ESTIMATED, STATUS_FUSED}
)
# Statuses that must carry explicit derivation metadata; decoded/measured must not.
DERIVED_STATUSES = frozenset({STATUS_DERIVED, STATUS_ESTIMATED, STATUS_FUSED})

HAND_SCOPES = frozenset({"left", "right", "bimanual"})

# Motion field names, in canonical Observation order (docs/V8/01 §2).
MOTION_FIELDS = (
    "canonical_20_rotation",
    "wrist_pose",
    "derived_landmarks_21",
    "joint_angles",
    "velocity",
    "acceleration",
    "contact",
    "force",
)

# Coordinate Profile frame taxonomy (docs/V8/02_COORDINATE_PROFILE.md §4).
FRAME_SOURCE = "source_frame"
FRAME_CANONICAL_HAND = "canonical_hand_frame"
FRAME_CANONICAL_WRIST = "canonical_wrist_frame"
FRAME_SESSION = "session_frame"
FRAME_WORLD = "world_frame"
FRAME_CAMERA_OPTICAL = "camera_optical_frame"
FRAME_ROBOT_BASE = "robot_base_frame"
FRAME_ROBOT_TOOL = "robot_tool_frame"

_HANDEDNESS = frozenset({"right", "left"})
_AXES = frozenset({"+x", "-x", "+y", "-y", "+z", "-z"})
_LENGTH_UNITS = frozenset({"meter", "centimeter", "millimeter"})
_ANGLE_UNITS = frozenset({"radian", "degree"})
_QUAT_ORDERS = frozenset({"wxyz", "xyzw"})
_WRIST_SCOPES = frozenset({"global", "local", "session_relative"})
_ROTATION_COMPOSITIONS = frozenset({"parent_relative", "global"})
_MIRROR_POLICIES = frozenset({"none", "mirror_x", "mirror_y", "mirror_z"})
_TRANSFORM_NATURES = frozenset({"static", "dynamic", "estimated"})
_VALIDITY_STATES = frozenset({"valid", "invalid", "unchecked"})
_VALIDATION_STATUSES = frozenset({"passed", "failed", "research_required", "unverified"})


class ImplicitConversionError(ValueError):
    """Raised when a cross-profile reinterpretation lacks an explicit transform."""


class UnresolvedProfileError(ValueError):
    """Raised when an Observation claims normalization without a resolvable profile."""


def _is_finite_vector(values: Sequence[float]) -> bool:
    return all(isinstance(v, (int, float)) and math.isfinite(v) for v in values)


def _canonical_json(payload) -> bytes:
    return json.dumps(payload, sort_keys=True, separators=(",", ":")).encode("utf-8")


def digest_bytes(data: bytes) -> str:
    """Content digest of a raw transport artifact (e.g. a Hand Token frame)."""
    return "sha256:" + hashlib.sha256(data).hexdigest()


def digest_payload(payload) -> str:
    """Content digest of a semantic payload's canonical JSON form."""
    return "sha256:" + hashlib.sha256(_canonical_json(payload)).hexdigest()


# ---------------------------------------------------------------------------
# Coordinate Profile (docs/V8/02_COORDINATE_PROFILE.md)
# ---------------------------------------------------------------------------


@dataclass(frozen=True)
class CoordinateProfile:
    """Explicit frame/convention boundary. Never inferred from values."""

    profile_id: str
    version: str
    handedness: str
    up_axis: str
    right_axis: str
    forward_axis: str
    length_unit: str
    angle_unit: str
    reference_frame: str
    wrist_pose_scope: str
    quaternion_order: str
    rotation_composition: str
    clock_domain: str
    mirror_policy: str = "none"

    def convention_signature(self) -> Dict[str, str]:
        """Every convention that distinguishes this profile from another."""
        return {
            "handedness": self.handedness,
            "up_axis": self.up_axis,
            "right_axis": self.right_axis,
            "forward_axis": self.forward_axis,
            "length_unit": self.length_unit,
            "angle_unit": self.angle_unit,
            "reference_frame": self.reference_frame,
            "wrist_pose_scope": self.wrist_pose_scope,
            "quaternion_order": self.quaternion_order,
            "rotation_composition": self.rotation_composition,
            "clock_domain": self.clock_domain,
            "mirror_policy": self.mirror_policy,
        }


def validate_coordinate_profile(profile: CoordinateProfile) -> None:
    """Reject an incomplete or malformed profile; never guess the gaps."""
    if not isinstance(profile, CoordinateProfile):
        raise TypeError("profile must be a CoordinateProfile")
    if not profile.profile_id or not profile.version:
        raise ValueError("profile_id and version are required")
    if profile.handedness not in _HANDEDNESS:
        raise ValueError(f"handedness must be one of {sorted(_HANDEDNESS)}")
    axes = (profile.up_axis, profile.right_axis, profile.forward_axis)
    if any(axis not in _AXES for axis in axes):
        raise ValueError("up/right/forward axes must be signed axis tokens")
    if len({axis[-1] for axis in axes}) != 3:
        raise ValueError("up/right/forward axes must be mutually distinct")
    if profile.length_unit not in _LENGTH_UNITS:
        raise ValueError(f"length_unit must be one of {sorted(_LENGTH_UNITS)}")
    if profile.angle_unit not in _ANGLE_UNITS:
        raise ValueError("angle_unit must be radian or degree")
    if not profile.reference_frame:
        raise ValueError("reference_frame is required (frame taxonomy)")
    if profile.wrist_pose_scope not in _WRIST_SCOPES:
        raise ValueError(f"wrist_pose_scope must be one of {sorted(_WRIST_SCOPES)}")
    if profile.quaternion_order not in _QUAT_ORDERS:
        raise ValueError("quaternion_order must be wxyz (w-first) or xyzw (w-last)")
    if profile.rotation_composition not in _ROTATION_COMPOSITIONS:
        raise ValueError("rotation_composition must be parent_relative or global")
    if not profile.clock_domain:
        raise ValueError("clock_domain is required")
    if profile.mirror_policy not in _MIRROR_POLICIES:
        raise ValueError(f"mirror_policy must be one of {sorted(_MIRROR_POLICIES)}")


def differing_conventions(source: CoordinateProfile, target: CoordinateProfile) -> frozenset:
    """Convention fields on which two profiles disagree (empty == none needed)."""
    source_sig, target_sig = source.convention_signature(), target.convention_signature()
    return frozenset(key for key in source_sig if source_sig[key] != target_sig[key])


@dataclass(frozen=True)
class CoordinateTransform:
    """Explicit, auditable conversion between two profiles (docs/V8/02 §4)."""

    source_profile_id: str
    target_profile_id: str
    parent_frame: str
    child_frame: str
    nature: str  # static | dynamic | estimated
    convention_changes: frozenset
    operation: str
    parameters_digest: str
    deterministic: bool
    validity_interval: Optional[Tuple[int, int]] = None
    calibration_ref: Optional[str] = None
    uncertainty: Optional[float] = None


def validate_coordinate_transform(
    transform: CoordinateTransform, source: CoordinateProfile, target: CoordinateProfile
) -> None:
    """A transform must declare exactly the conventions that actually differ."""
    if not isinstance(transform, CoordinateTransform):
        raise TypeError("transform must be a CoordinateTransform")
    if transform.source_profile_id != source.profile_id:
        raise ValueError("transform source_profile_id does not match source profile")
    if transform.target_profile_id != target.profile_id:
        raise ValueError("transform target_profile_id does not match target profile")
    if transform.nature not in _TRANSFORM_NATURES:
        raise ValueError(f"nature must be one of {sorted(_TRANSFORM_NATURES)}")
    if not isinstance(transform.deterministic, bool):
        raise ValueError("deterministic flag must be a bool")
    if not transform.operation or not transform.parameters_digest:
        raise ValueError("transform operation and parameters_digest are required")
    if not transform.parent_frame or not transform.child_frame:
        raise ValueError("transform must declare parent_frame and child_frame")
    actual = differing_conventions(source, target)
    declared = frozenset(transform.convention_changes)
    if declared != actual:
        raise ValueError(
            f"transform declares {sorted(declared)} but profiles actually differ in {sorted(actual)}"
        )
    if transform.uncertainty is not None and not math.isfinite(transform.uncertainty):
        raise ValueError("transform uncertainty must be finite when supplied")


def assert_no_implicit_conversion(
    source: CoordinateProfile,
    target: CoordinateProfile,
    transform: Optional[CoordinateTransform] = None,
) -> None:
    """Block silent reinterpretation across profiles (docs/V8/02 §2, §4).

    Identical conventions need no transform. Any difference requires an explicit,
    fully-declared CoordinateTransform; otherwise the read is refused.
    """
    diff = differing_conventions(source, target)
    if not diff:
        return
    if transform is None:
        raise ImplicitConversionError(
            f"profiles differ in {sorted(diff)}; an explicit CoordinateTransform is required"
        )
    validate_coordinate_transform(transform, source, target)


# ---------------------------------------------------------------------------
# Provenance Model (docs/V8/04_PROVENANCE_MODEL.md)
# ---------------------------------------------------------------------------


@dataclass(frozen=True)
class ArtifactIdentity:
    """Minimal reproducible artifact identity (docs/V8/04 §3)."""

    artifact_id: str
    content_digest: str
    media_type: str
    schema_id: str
    schema_version: str
    producer: str
    producer_version: str
    source_commit: Optional[str] = None


@dataclass(frozen=True)
class Transformation:
    """One immutable lineage edge: input artifact -> operation -> output artifact."""

    input_ref: str
    operation: str
    implementation_version: str
    parameters_digest: str
    output_ref: str
    deterministic: bool


@dataclass(frozen=True)
class ProvenanceRecord:
    record_id: str
    source: Mapping[str, str]
    acquisition: Mapping[str, object]
    artifacts: Mapping[str, ArtifactIdentity]
    transformations: Tuple[Transformation, ...]
    validation: Mapping[str, object]
    policy: Mapping[str, str]


def make_frame_artifact(frame_bytes: bytes, artifact_id: str, sequence_id: str) -> ArtifactIdentity:
    """Artifact identity for a raw Hand Token frame (Motion Transport Layer)."""
    return ArtifactIdentity(
        artifact_id=artifact_id,
        content_digest=digest_bytes(frame_bytes),
        media_type=HAND_TOKEN_FRAME_MEDIA_TYPE,
        schema_id=HAND_TOKEN_CODEC_ID,
        schema_version=HAND_TOKEN_CODEC_VERSION,
        producer="hand_token.codec",
        producer_version=HAND_TOKEN_CODEC_VERSION,
    )


def make_payload_artifact(payload, artifact_id: str, producer: str) -> ArtifactIdentity:
    """Artifact identity for a semantic payload (Observation / derived view)."""
    return ArtifactIdentity(
        artifact_id=artifact_id,
        content_digest=digest_payload(payload),
        media_type="application/json",
        schema_id=SCHEMA_ID,
        schema_version=SCHEMA_VERSION,
        producer=producer,
        producer_version=SCHEMA_VERSION,
    )


def validate_provenance_record(record: ProvenanceRecord) -> None:
    """Enforce source + transformation lineage integrity (docs/V8/04 §2-§4)."""
    if not isinstance(record, ProvenanceRecord):
        raise TypeError("record must be a ProvenanceRecord")
    if not record.record_id:
        raise ValueError("record_id is required")

    source = record.source
    if not source.get("origin") or not source.get("source_format") or not source.get("source_version"):
        raise ValueError("source requires origin, source_format and source_version")

    acquisition = record.acquisition
    if not acquisition.get("clock_domain") or "time_range" not in acquisition:
        raise ValueError("acquisition requires clock_domain and time_range")

    for artifact in record.artifacts.values():
        if not artifact.content_digest.startswith("sha256:"):
            raise ValueError("artifact content_digest must be a sha256 digest")
        if not artifact.schema_id or not artifact.schema_version:
            raise ValueError("artifact requires schema_id and schema_version")
        if not artifact.producer or not artifact.producer_version:
            raise ValueError("artifact requires producer and producer_version")

    # Lineage must reference known artifacts, form a connected acyclic chain, and
    # never overwrite: each artifact is the output of at most one transformation.
    inputs, outputs = set(), set()
    for transformation in record.transformations:
        if transformation.input_ref not in record.artifacts:
            raise ValueError(f"unknown transformation input {transformation.input_ref}")
        if transformation.output_ref not in record.artifacts:
            raise ValueError(f"unknown transformation output {transformation.output_ref}")
        if not transformation.operation or not transformation.implementation_version:
            raise ValueError("transformation requires operation and implementation_version")
        if not transformation.parameters_digest:
            raise ValueError("transformation requires a parameters_digest")
        if not isinstance(transformation.deterministic, bool):
            raise ValueError("transformation deterministic flag must be a bool")
        if transformation.output_ref in outputs:
            raise ValueError("lineage overwrite: an artifact is produced more than once")
        inputs.add(transformation.input_ref)
        outputs.add(transformation.output_ref)

    if record.transformations:
        roots = [a for a in record.artifacts if a not in outputs]
        sinks = [a for a in record.artifacts if a not in inputs]
        if len(roots) != 1 or len(sinks) != 1:
            raise ValueError("lineage must have exactly one source root and one terminal sink")
        # Connectivity: following edges from the root must reach the sink.
        edges = {t.input_ref: t.output_ref for t in record.transformations}
        seen, cursor = set(), roots[0]
        while cursor in edges and cursor not in seen:
            seen.add(cursor)
            cursor = edges[cursor]
        if cursor != sinks[0]:
            raise ValueError("lineage is not a connected acyclic path from source to terminal")

    validation = record.validation
    if not validation.get("checks") or validation.get("status") not in _VALIDATION_STATUSES:
        raise ValueError("validation requires non-empty checks and a known status")

    policy = record.policy
    if not policy.get("license") or not policy.get("permitted_use"):
        raise ValueError("policy requires license and permitted_use")


def provenance_lineage(record: ProvenanceRecord) -> List[str]:
    """Return the ordered artifact lineage from source root to terminal sink."""
    validate_provenance_record(record)
    outputs = {t.output_ref for t in record.transformations}
    cursor = next(a for a in record.artifacts if a not in outputs)
    edges = {t.input_ref: t.output_ref for t in record.transformations}
    lineage = [cursor]
    while cursor in edges:
        cursor = edges[cursor]
        lineage.append(cursor)
    return lineage


# ---------------------------------------------------------------------------
# Observation Layer (docs/V8/01_OBSERVATION_LAYER.md)
# ---------------------------------------------------------------------------


@dataclass(frozen=True)
class FieldProvenance:
    """Per-field status plus derivation metadata when the value is not decoded."""

    status: str
    derivation: Optional[Mapping[str, object]] = None


@dataclass(frozen=True)
class Quality:
    """Orthogonal quality axes (docs/V8/01 §4). Per-field availability is the mask."""

    validity: str = "unchecked"
    confidence: Optional[float] = None
    uncertainty: Optional[float] = None


@dataclass(frozen=True)
class RawTransportRef:
    """Anchor back to the Motion Transport Layer frame that decoded this state."""

    codec: str
    codec_version: str
    frame_digest: str
    sequence_id: str
    device: Mapping[str, object]


@dataclass
class MotionState:
    """Semantic motion payload; absent fields stay None, never zero-masqueraded."""

    canonical_20_rotation: Optional[List[List[float]]] = None
    wrist_pose: Optional[Mapping[str, List[float]]] = None
    derived_landmarks_21: Optional[List[List[float]]] = None
    joint_angles: Optional[List[float]] = None
    velocity: Optional[List[float]] = None
    acceleration: Optional[List[float]] = None
    contact: Optional[List[int]] = None
    force: Optional[List[float]] = None


@dataclass
class Observation:
    observation_id: str
    sequence_id: str
    observed_at: int
    clock_domain: str
    hand_scope: str
    motion: MotionState
    field_status: Dict[str, FieldProvenance]
    availability_mask: Dict[str, bool]
    quality: Quality
    coordinate_profile_id: str
    provenance_ref: str
    raw_transport_ref: RawTransportRef
    normalized: bool = False


def _validate_derivation_metadata(field_name: str, derivation: Mapping[str, object]) -> None:
    if not derivation.get("method"):
        raise ValueError(f"{field_name}: derivation requires a method")
    if not derivation.get("input_fields"):
        raise ValueError(f"{field_name}: derivation requires input_fields")


def validate_observation(observation: Observation) -> None:
    """Enforce the semantic-layer rules (docs/V8/01 §1-§4, §3a)."""
    if not isinstance(observation, Observation):
        raise TypeError("observation must be an Observation")
    if observation.hand_scope not in HAND_SCOPES:
        raise ValueError(f"hand_scope must be one of {sorted(HAND_SCOPES)}")
    if not observation.observation_id or not observation.sequence_id:
        raise ValueError("observation_id and sequence_id are required")
    if not observation.clock_domain:
        raise ValueError("clock_domain is required (timestamps name a clock domain)")

    if set(observation.availability_mask) != set(MOTION_FIELDS):
        raise ValueError("availability_mask must cover exactly the motion fields")
    available = {name for name in MOTION_FIELDS if observation.availability_mask[name]}
    if set(observation.field_status) != available:
        raise ValueError("field_status must be present for exactly the available fields")

    for name in MOTION_FIELDS:
        value = getattr(observation.motion, name)
        if observation.availability_mask[name]:
            if value is None:
                raise ValueError(f"{name} is marked available but carries no value")
        else:
            if value is not None:
                raise ValueError(f"{name} is unavailable but carries a value (zero-masquerade)")

        if value is None:
            continue
        provenance = observation.field_status[name]
        if provenance.status not in FIELD_STATUSES:
            raise ValueError(f"{name}: unknown field status {provenance.status}")
        if provenance.status in DERIVED_STATUSES:
            if provenance.derivation is None:
                raise ValueError(f"{name}: {provenance.status} value requires derivation metadata")
            _validate_derivation_metadata(name, provenance.derivation)
        elif provenance.derivation is not None:
            raise ValueError(f"{name}: {provenance.status} value must not carry derivation metadata")

    # FK21 is only ever a derived positional view, and only with full metadata.
    landmarks = observation.motion.derived_landmarks_21
    if landmarks is not None:
        provenance = observation.field_status["derived_landmarks_21"]
        if provenance.status != STATUS_DERIVED:
            raise ValueError("derived_landmarks_21 must be marked derived, never measured/decoded")
        derivation = provenance.derivation or {}
        for required in ("method", "input_fields", "topology", "index_map", "rest_model_id", "rest_revision"):
            if required not in derivation:
                raise ValueError(f"derived_landmarks_21 derivation missing {required}")
        if len(landmarks) != 21 or not all(_is_finite_vector(p) and len(p) == 3 for p in landmarks):
            raise ValueError("derived_landmarks_21 must be 21 finite 3-vectors")

    rotations = observation.motion.canonical_20_rotation
    if rotations is not None:
        if len(rotations) != 20 or not all(_is_finite_vector(q) and len(q) == 4 for q in rotations):
            raise ValueError("canonical_20_rotation must be 20 finite quaternions")

    quality = observation.quality
    if quality.validity not in _VALIDITY_STATES:
        raise ValueError(f"quality.validity must be one of {sorted(_VALIDITY_STATES)}")
    if quality.confidence is not None and not (0.0 <= quality.confidence <= 1.0):
        raise ValueError("quality.confidence must lie in [0, 1]")
    if quality.uncertainty is not None and not math.isfinite(quality.uncertainty):
        raise ValueError("quality.uncertainty must be finite")

    if not observation.coordinate_profile_id:
        raise ValueError("coordinate_profile_id is required")
    if not observation.provenance_ref:
        raise ValueError("provenance_ref is required")
    transport = observation.raw_transport_ref
    if transport.codec != HAND_TOKEN_CODEC_ID or not transport.frame_digest.startswith("sha256:"):
        raise ValueError("raw_transport_ref must anchor to a Hand Token frame digest")


def observation_payload(observation: Observation) -> Dict[str, object]:
    """Canonical semantic payload used for content digests (derived state only)."""
    return {
        "schema": f"{SCHEMA_ID}@{SCHEMA_VERSION}",
        "observation_id": observation.observation_id,
        "sequence_id": observation.sequence_id,
        "observed_at": observation.observed_at,
        "clock_domain": observation.clock_domain,
        "hand_scope": observation.hand_scope,
        "coordinate_profile_id": observation.coordinate_profile_id,
        "motion": {
            name: getattr(observation.motion, name)
            for name in MOTION_FIELDS
            if getattr(observation.motion, name) is not None
        },
        "field_status": {
            name: {"status": fp.status, "derivation": fp.derivation}
            for name, fp in observation.field_status.items()
        },
        "raw_transport_ref": {
            "codec": observation.raw_transport_ref.codec,
            "codec_version": observation.raw_transport_ref.codec_version,
            "frame_digest": observation.raw_transport_ref.frame_digest,
            "sequence_id": observation.raw_transport_ref.sequence_id,
        },
    }


def build_observation_from_token(
    token: HandTokenV2,
    frame_bytes: bytes,
    profile: CoordinateProfile,
    provenance_ref: str,
    observation_id: str,
    sequence_id: str,
    available_fields: Sequence[str],
    hand_scope: str,
    normalized: bool = True,
    confidence: Optional[float] = None,
) -> Observation:
    """Wrap decoded Hand Token v2 state in an Observation (semantic layer).

    ``available_fields`` declares which motion fields the *source* genuinely
    provides; availability is never inferred from zero values (docs/V8/01 §1).
    Decoded fields are marked ``decoded``; FK21 landmarks are computed here and
    marked ``derived`` with full derivation metadata.
    """
    if not isinstance(token, HandTokenV2):
        raise TypeError("token must be a HandTokenV2")
    available = frozenset(available_fields)
    unknown = available - frozenset(MOTION_FIELDS)
    if unknown:
        raise ValueError(f"unknown motion fields requested: {sorted(unknown)}")
    if ("canonical_20_rotation" in available or "derived_landmarks_21" in available) and not token.has_skeleton:
        raise ValueError("canonical_20_rotation/derived_landmarks_21 require a skeleton token")

    base = token.base
    device = {"product": base.product, "hand": base.hand, "serial": base.serial}
    motion = MotionState()
    field_status: Dict[str, FieldProvenance] = {}

    def _decoded(name: str, value) -> None:
        setattr(motion, name, value)
        field_status[name] = FieldProvenance(status=STATUS_DECODED)

    if "canonical_20_rotation" in available:
        _decoded("canonical_20_rotation", [list(q) for q in token.skeleton.quat])
    if "wrist_pose" in available:
        _decoded(
            "wrist_pose",
            {
                "position": list(base.wrist_6dof[:3]),
                "orientation_wxyz": list(base.quat),
            },
        )
    if "joint_angles" in available:
        _decoded("joint_angles", list(base.flex))
    if "velocity" in available:
        _decoded("velocity", list(base.vel))
    if "acceleration" in available:
        _decoded("acceleration", list(base.acc))
    if "contact" in available:
        _decoded("contact", list(base.contact))
    if "force" in available:
        _decoded("force", list(base.force))

    if "derived_landmarks_21" in available:
        landmarks = fk21(token.skeleton)
        motion.derived_landmarks_21 = [list(p) for p in landmarks]
        field_status["derived_landmarks_21"] = FieldProvenance(
            status=STATUS_DERIVED,
            derivation={
                "method": "fk21",
                "input_fields": ["canonical_20_rotation", "rest_offsets"],
                "topology": "canonical-20",
                "index_map": "mediapipe-21",
                "rest_model_id": token.skeleton.model_id,
                "rest_revision": token.skeleton.revision,
                "coordinate_profile_id": profile.profile_id,
            },
        )

    availability_mask = {name: name in available for name in MOTION_FIELDS}
    frame_digest = digest_bytes(frame_bytes)
    observation = Observation(
        observation_id=observation_id,
        sequence_id=sequence_id,
        observed_at=base.timestamp_us,
        clock_domain=profile.clock_domain,
        hand_scope=hand_scope,
        motion=motion,
        field_status=field_status,
        availability_mask=availability_mask,
        quality=Quality(validity="valid", confidence=confidence),
        coordinate_profile_id=profile.profile_id,
        provenance_ref=provenance_ref,
        raw_transport_ref=RawTransportRef(
            codec=HAND_TOKEN_CODEC_ID,
            codec_version=HAND_TOKEN_CODEC_VERSION,
            frame_digest=frame_digest,
            sequence_id=sequence_id,
            device=device,
        ),
        normalized=normalized,
    )
    validate_observation(observation)
    return observation


def validate_boundary(
    observation: Observation,
    profile: CoordinateProfile,
    provenance: ProvenanceRecord,
) -> None:
    """Tie the three layers together and prove the boundary holds.

    1. Hand Token remains the Motion Transport Layer: the observation anchors to
       a real frame digest, and that decoded-from frame appears as a node in the
       provenance lineage (it need not be the root — an upstream source such as
       OpenXR may feed it through an ingest transformation).
    2. Observation remains the semantic layer: schema rules hold and the profile
       reference resolves.
    3. Coordinate Profile: the observation references a valid, complete profile
       whose clock domain matches the observation.
    4. Provenance tracks lineage: the terminal artifact digest matches this
       observation's derived payload.
    """
    validate_observation(observation)
    validate_coordinate_profile(profile)
    validate_provenance_record(provenance)

    if observation.coordinate_profile_id != profile.profile_id:
        raise ValueError("observation references a different Coordinate Profile")
    if observation.provenance_ref != provenance.record_id:
        raise ValueError("observation references a different Provenance record")
    if observation.clock_domain != profile.clock_domain:
        raise ValueError("observation clock domain does not match its Coordinate Profile")
    if observation.normalized is False:
        raise UnresolvedProfileError("observation is unresolved and cannot claim normalization")

    lineage = provenance_lineage(provenance)
    frame_digest = observation.raw_transport_ref.frame_digest
    anchor = None
    for artifact_id in lineage:
        artifact = provenance.artifacts[artifact_id]
        if artifact.content_digest == frame_digest and artifact.media_type == HAND_TOKEN_FRAME_MEDIA_TYPE:
            anchor = artifact_id
            break
    if anchor is None:
        raise ValueError("provenance lineage does not contain the observation's Hand Token transport frame")
    terminal = provenance.artifacts[lineage[-1]]
    if terminal.content_digest != digest_payload(observation_payload(observation)):
        raise ValueError("provenance terminal artifact does not match the observation payload")


__all__ = [
    "ArtifactIdentity",
    "CoordinateProfile",
    "CoordinateTransform",
    "FieldProvenance",
    "ImplicitConversionError",
    "MotionState",
    "Observation",
    "ProvenanceRecord",
    "Quality",
    "RawTransportRef",
    "Transformation",
    "UnresolvedProfileError",
    "assert_no_implicit_conversion",
    "build_observation_from_token",
    "digest_bytes",
    "digest_payload",
    "differing_conventions",
    "make_frame_artifact",
    "make_payload_artifact",
    "observation_payload",
    "provenance_lineage",
    "validate_boundary",
    "validate_coordinate_profile",
    "validate_coordinate_transform",
    "validate_observation",
    "validate_provenance_record",
    "FIELD_STATUSES",
    "DERIVED_STATUSES",
    "HAND_SCOPES",
    "MOTION_FIELDS",
    "SCHEMA_ID",
    "SCHEMA_VERSION",
    "HAND_TOKEN_CODEC_ID",
    "HAND_TOKEN_CODEC_VERSION",
    "HAND_TOKEN_FRAME_MEDIA_TYPE",
]
