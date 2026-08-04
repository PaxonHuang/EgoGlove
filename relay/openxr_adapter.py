"""Schema-neutral OpenXR hand input boundary.

The boundary deliberately uses only Python data types so callers do not need
to depend on a particular OpenXR binding or runtime package.
"""
from __future__ import annotations

import math
from dataclasses import dataclass
from enum import IntEnum
from typing import List, Mapping, Optional

from hand_token import HAND_LEFT, PRODUCT_PRO, HandTokenV2


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
    """Convert a validated OpenXR frame to Hand Token v2.

    Joint mapping and skeleton construction are intentionally implemented by
    the next adapter task; this boundary reserves the stable public signature.
    """
    validate_openxr_frame(frame)
    raise NotImplementedError("OpenXR to Hand Token conversion is implemented in Task 2")


__all__ = [
    "OpenXRJoint",
    "OpenXRJointLocation",
    "OpenXRHandFrame",
    "openxr_to_hand_token",
    "validate_openxr_frame",
]
