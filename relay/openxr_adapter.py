"""Schema-neutral OpenXR hand input boundary.

The boundary deliberately uses only Python data types so callers do not need
to depend on a particular OpenXR binding or runtime package.
"""
from __future__ import annotations

import math
from dataclasses import dataclass
from enum import IntEnum
from typing import List, Mapping, Optional, Sequence

from hand_token import (
    HAND_LEFT,
    HAND_TOKEN_CAP_HAS_SKELETON,
    PRODUCT_PRO,
    HandSkeleton,
    HandToken,
    HandTokenV2,
    _f32,
    _normalise,
    _quat_mul,
    _rotate,
)


class OpenXRJoint(IntEnum):
    """The 26 joints from XR_EXT_hand_tracking, in specification order."""

    PALM = 0
    WRIST = 1
    THUMB_METACARPAL = 2
    THUMB_PROXIMAL = 3
    THUMB_DISTAL = 4
    THUMB_TIP = 5
    INDEX_METACARPAL = 6
    INDEX_PROXIMAL = 7
    INDEX_INTERMEDIATE = 8
    INDEX_DISTAL = 9
    INDEX_TIP = 10
    MIDDLE_METACARPAL = 11
    MIDDLE_PROXIMAL = 12
    MIDDLE_INTERMEDIATE = 13
    MIDDLE_DISTAL = 14
    MIDDLE_TIP = 15
    RING_METACARPAL = 16
    RING_PROXIMAL = 17
    RING_INTERMEDIATE = 18
    RING_DISTAL = 19
    RING_TIP = 20
    LITTLE_METACARPAL = 21
    LITTLE_PROXIMAL = 22
    LITTLE_INTERMEDIATE = 23
    LITTLE_DISTAL = 24
    LITTLE_TIP = 25


@dataclass(frozen=True)
class OpenXRJointLocation:
    joint: OpenXRJoint
    position: List[float]
    orientation: List[float]  # source order x, y, z, w
    location_valid: bool = True
    orientation_valid: bool = True
    confidence: Optional[float] = None
    radius: Optional[float] = None


@dataclass(frozen=True)
class OpenXRHandFrame:
    joints: Mapping[OpenXRJoint, OpenXRJointLocation]
    hand: int = HAND_LEFT
    product: int = PRODUCT_PRO
    serial: int = 0
    timestamp_us: int = 0

# Frozen Hand Token canonical topology, deliberately independent of enum order.
_CANONICAL_OPENXR_JOINTS = (
    OpenXRJoint.WRIST,
    OpenXRJoint.THUMB_METACARPAL,
    OpenXRJoint.THUMB_PROXIMAL,
    OpenXRJoint.THUMB_DISTAL,
    OpenXRJoint.INDEX_METACARPAL,
    OpenXRJoint.INDEX_PROXIMAL,
    OpenXRJoint.INDEX_INTERMEDIATE,
    OpenXRJoint.INDEX_DISTAL,
    OpenXRJoint.MIDDLE_METACARPAL,
    OpenXRJoint.MIDDLE_PROXIMAL,
    OpenXRJoint.MIDDLE_INTERMEDIATE,
    OpenXRJoint.MIDDLE_DISTAL,
    OpenXRJoint.RING_METACARPAL,
    OpenXRJoint.RING_PROXIMAL,
    OpenXRJoint.RING_INTERMEDIATE,
    OpenXRJoint.RING_DISTAL,
    OpenXRJoint.LITTLE_METACARPAL,
    OpenXRJoint.LITTLE_PROXIMAL,
    OpenXRJoint.LITTLE_INTERMEDIATE,
    OpenXRJoint.LITTLE_DISTAL,
)
_CANONICAL_PARENTS = (-1, 0, 1, 2, 0, 4, 5, 6, 0, 8, 9, 10, 0, 12, 13, 14, 0, 16, 17, 18)
_TIP_OPENXR_JOINTS = (
    OpenXRJoint.THUMB_TIP,
    OpenXRJoint.INDEX_TIP,
    OpenXRJoint.MIDDLE_TIP,
    OpenXRJoint.RING_TIP,
    OpenXRJoint.LITTLE_TIP,
)
_TIP_PARENTS = (3, 7, 11, 15, 19)


def _xyzw_to_wxyz(quaternion: Sequence[float]) -> List[float]:
    return _normalise([quaternion[3], quaternion[0], quaternion[1], quaternion[2]])


def _conjugate(quaternion: Sequence[float]) -> List[float]:
    return [_f32(quaternion[0]), _f32(-quaternion[1]), _f32(-quaternion[2]), _f32(-quaternion[3])]


def _parent_relative(parent_global: Sequence[float], child_global: Sequence[float]) -> List[float]:
    return _normalise(_quat_mul(_conjugate(parent_global), list(child_global)))


def _parent_offset(
    parent_global: Sequence[float], parent_position: Sequence[float], child_position: Sequence[float]
) -> List[float]:
    delta = [_f32(child_position[axis] - parent_position[axis]) for axis in range(3)]
    return _rotate(_conjugate(parent_global), delta)


def validate_openxr_frame(frame: OpenXRHandFrame) -> None:
    """Validate the complete source frame before conversion."""
    if not isinstance(frame, OpenXRHandFrame):
        raise TypeError("frame must be an OpenXRHandFrame")
    if set(frame.joints) != set(OpenXRJoint):
        raise ValueError("frame must contain all 26 OpenXR joints")
    for joint in OpenXRJoint:
        location = frame.joints[joint]
        if not isinstance(location, OpenXRJointLocation) or location.joint != joint:
            raise ValueError("joint mapping contains an inconsistent location")
        if not location.location_valid or not location.orientation_valid:
            raise ValueError("required joint location and orientation must be valid")
        if len(location.position) != 3 or len(location.orientation) != 4:
            raise ValueError("joint vectors must have 3-position and 4-quaternion shapes")
        values = list(location.position) + list(location.orientation)
        if not all(isinstance(value, (int, float)) and math.isfinite(value) for value in values):
            raise ValueError("joint vectors must contain finite values")
        if location.confidence is not None and (
            not isinstance(location.confidence, (int, float))
            or not math.isfinite(location.confidence)
            or not 0.0 <= location.confidence <= 1.0
        ):
            raise ValueError("confidence must be finite and in [0.0, 1.0]")
        if location.radius is not None and (
            not isinstance(location.radius, (int, float))
            or not math.isfinite(location.radius)
        ):
            raise ValueError("radius must be finite when supplied")


def openxr_to_hand_token(frame: OpenXRHandFrame) -> HandTokenV2:
    """Convert a validated OpenXR frame to canonical Hand Token v2."""
    validate_openxr_frame(frame)
    locations = frame.joints
    global_quats = [_xyzw_to_wxyz(locations[joint].orientation) for joint in _CANONICAL_OPENXR_JOINTS]
    local_quats = [
        global_quat if parent < 0 else _parent_relative(global_quats[parent], global_quat)
        for global_quat, parent in zip(global_quats, _CANONICAL_PARENTS)
    ]
    positions = [locations[joint].position for joint in _CANONICAL_OPENXR_JOINTS]
    offsets = [[0.0, 0.0, 0.0]]
    for index in range(1, len(_CANONICAL_OPENXR_JOINTS)):
        parent = _CANONICAL_PARENTS[index]
        offsets.append(_parent_offset(global_quats[parent], positions[parent], positions[index]))
    for tip_joint, parent in zip(_TIP_OPENXR_JOINTS, _TIP_PARENTS):
        offsets.append(_parent_offset(global_quats[parent], positions[parent], locations[tip_joint].position))

    skeleton = HandSkeleton(quat=local_quats, offsets=offsets, model_id=2, revision=1)
    base = HandToken(
        product=frame.product,
        hand=frame.hand,
        serial=frame.serial,
        timestamp_us=frame.timestamp_us,
        quat=global_quats[0],
    )
    return HandTokenV2(
        base=base,
        caps=HAND_TOKEN_CAP_HAS_SKELETON,
        has_skeleton=True,
        skeleton=skeleton,
    )


__all__ = [
    "OpenXRJoint",
    "OpenXRJointLocation",
    "OpenXRHandFrame",
    "openxr_to_hand_token",
    "validate_openxr_frame",
]
