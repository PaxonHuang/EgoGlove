"""Contract tests for the schema-neutral OpenXR input boundary."""
import math

from openxr_adapter import (
    OpenXRHandFrame,
    OpenXRJoint,
    OpenXRJointLocation,
    validate_openxr_frame,
)


def openxr_fixture() -> OpenXRHandFrame:
    joints = {}
    for joint in OpenXRJoint:
        joints[joint] = OpenXRJointLocation(
            joint=joint,
            position=[float(joint), float(joint % 3), float(joint // 3)],
            orientation=[0.0, 0.0, 0.0, 1.0],
        )
    return OpenXRHandFrame(joints=joints)


def test_openxr_fixture_contains_all_26_joints():
    frame = openxr_fixture()
    assert len(frame.joints) == 26
    assert set(frame.joints) == set(OpenXRJoint)
    assert len({tuple(frame.joints[joint].position) for joint in OpenXRJoint}) == 26
    validate_openxr_frame(frame)


def test_openxr_missing_or_invalid_required_joint_is_rejected():
    frame = openxr_fixture()
    missing = dict(frame.joints)
    del missing[OpenXRJoint.WRIST]
    try:
        validate_openxr_frame(OpenXRHandFrame(joints=missing))
    except ValueError:
        pass
    else:
        raise AssertionError("expected missing joint rejection")

    invalid = dict(frame.joints)
    invalid[OpenXRJoint.PALM] = OpenXRJointLocation(
        OpenXRJoint.PALM, [0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 1.0], location_valid=False
    )
    try:
        validate_openxr_frame(OpenXRHandFrame(joints=invalid))
    except ValueError:
        pass
    else:
        raise AssertionError("expected invalid joint rejection")


def test_openxr_bad_vector_lengths_nonfinite_and_confidence_are_rejected():
    cases = (
        (OpenXRJoint.PALM, OpenXRJointLocation(OpenXRJoint.PALM, [0.0, 0.0], [0.0] * 4)),
        (OpenXRJoint.WRIST, OpenXRJointLocation(OpenXRJoint.WRIST, [math.inf, 0.0, 0.0], [0.0] * 4)),
        (OpenXRJoint.THUMB_TIP, OpenXRJointLocation(OpenXRJoint.THUMB_TIP, [0.0] * 3, [0.0] * 4, confidence=-0.01)),
        (OpenXRJoint.INDEX_TIP, OpenXRJointLocation(OpenXRJoint.INDEX_TIP, [0.0] * 3, [0.0] * 4, confidence=1.01)),
        (OpenXRJoint.MIDDLE_TIP, OpenXRJointLocation(OpenXRJoint.MIDDLE_TIP, [0.0] * 3, [0.0] * 4, confidence=math.nan)),
    )
    for joint, location in cases:
        joints = dict(openxr_fixture().joints)
        joints[joint] = location
        try:
            validate_openxr_frame(OpenXRHandFrame(joints=joints))
        except ValueError:
            continue
        raise AssertionError(f"expected rejection for {joint.name}")


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
