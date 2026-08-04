"""Contract tests for the schema-neutral OpenXR input boundary."""
import math

from hand_token import (
    HAND_TOKEN_CAP_HAS_SKELETON,
    HAND_TOKEN_CAP_QUAT_WLAST,
    HAND_RIGHT,
    PRODUCT_PRO,
    HandTokenV2,
)

from openxr_adapter import (
    OpenXRHandFrame,
    OpenXRJoint,
    OpenXRJointLocation,
    openxr_to_hand_token,
    validate_openxr_frame,
)


CANONICAL_OPENXR_JOINTS = (
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
CANONICAL_PARENT = (-1, 0, 1, 2, 0, 4, 5, 6, 0, 8, 9, 10, 0, 12, 13, 14, 0, 16, 17, 18)
TIP_OPENXR_JOINTS = (
    OpenXRJoint.THUMB_TIP,
    OpenXRJoint.INDEX_TIP,
    OpenXRJoint.MIDDLE_TIP,
    OpenXRJoint.RING_TIP,
    OpenXRJoint.LITTLE_TIP,
)
TIP_PARENT = (3, 7, 11, 15, 19)


def assert_close(actual, expected, tol=1e-5):
    assert len(actual) == len(expected)
    for axis, (left, right) in enumerate(zip(actual, expected)):
        assert abs(left - right) <= tol, f"axis {axis}: {actual} != {expected}"


def z_quat_wxyz(angle: float):
    return [math.cos(angle / 2.0), 0.0, 0.0, math.sin(angle / 2.0)]


def z_quat_xyzw(angle: float):
    quat = z_quat_wxyz(angle)
    return [quat[1], quat[2], quat[3], quat[0]]


def rotate_z(angle: float, vector):
    cos_a = math.cos(angle)
    sin_a = math.sin(angle)
    x, y, z = vector
    return [cos_a * x - sin_a * y, sin_a * x + cos_a * y, z]


def add_vectors(left, right):
    return [left[axis] + right[axis] for axis in range(3)]


def nonidentity_openxr_fixture():
    global_angles = [0.25] + [0.0] * 19
    local_angles = [0.25] + [0.017 * (index + 1) for index in range(1, 20)]
    canonical_offsets = [[0.0, 0.0, 0.0]] + [
        [0.01 * index, -0.004 * (index % 5), 0.03 + 0.002 * (index % 4)] for index in range(1, 20)
    ]
    tip_offsets = [[0.025 + 0.003 * index, 0.006 * (index + 1), -0.004 * index] for index in range(5)]
    canonical_positions = [[1.0, -2.0, 0.5]] + [[0.0, 0.0, 0.0] for _ in range(19)]

    for index in range(1, 20):
        parent = CANONICAL_PARENT[index]
        global_angles[index] = global_angles[parent] + local_angles[index]
        canonical_positions[index] = add_vectors(
            canonical_positions[parent],
            rotate_z(global_angles[parent], canonical_offsets[index]),
        )

    joints = {
        OpenXRJoint.PALM: OpenXRJointLocation(
            OpenXRJoint.PALM,
            [0.9, -2.1, 0.55],
            z_quat_xyzw(-0.1),
        )
    }
    for index, joint in enumerate(CANONICAL_OPENXR_JOINTS):
        joints[joint] = OpenXRJointLocation(joint, canonical_positions[index], z_quat_xyzw(global_angles[index]))
    for tip_index, joint in enumerate(TIP_OPENXR_JOINTS):
        parent = TIP_PARENT[tip_index]
        joints[joint] = OpenXRJointLocation(
            joint,
            add_vectors(canonical_positions[parent], rotate_z(global_angles[parent], tip_offsets[tip_index])),
            z_quat_xyzw(global_angles[parent] + 0.5),
        )

    frame = OpenXRHandFrame(
        joints=joints,
        hand=HAND_RIGHT,
        product=PRODUCT_PRO,
        serial=23,
        timestamp_us=987654,
    )
    return frame, local_angles, canonical_offsets, tip_offsets


def openxr_fixture() -> OpenXRHandFrame:
    joints = {}
    for joint in OpenXRJoint:
        joints[joint] = OpenXRJointLocation(
            joint=joint,
            position=[float(joint), float(joint % 3), float(joint // 3)],
            orientation=[0.0, 0.0, 0.0, 1.0],
        )
    return OpenXRHandFrame(joints=joints)


def test_openxr_conversion_contract_produces_skeleton_token():
    token = openxr_to_hand_token(openxr_fixture())
    assert isinstance(token, HandTokenV2)
    assert token.has_skeleton
    assert token.caps & HAND_TOKEN_CAP_HAS_SKELETON
    assert token.skeleton.model_id == 2
    assert token.skeleton.revision == 1


def test_openxr_mapping_preserves_canonical_joint_order():
    frame, local_angles, _, _ = nonidentity_openxr_fixture()
    token = openxr_to_hand_token(frame)

    assert token.base.product == frame.product
    assert token.base.hand == frame.hand
    assert token.base.serial == frame.serial
    assert token.base.timestamp_us == frame.timestamp_us
    assert token.skeleton.model_id == 2
    assert token.skeleton.revision == 1
    for index, expected_angle in enumerate(local_angles):
        assert_close(token.skeleton.quat[index], z_quat_wxyz(expected_angle))


def test_openxr_global_wlast_rotations_become_parent_relative_wfirst():
    frame, local_angles, _, _ = nonidentity_openxr_fixture()
    token = openxr_to_hand_token(frame)

    assert token.caps & HAND_TOKEN_CAP_HAS_SKELETON
    assert not token.caps & HAND_TOKEN_CAP_QUAT_WLAST
    assert_close(token.base.quat, z_quat_wxyz(local_angles[0]))
    assert_close(token.skeleton.quat[0], z_quat_wxyz(local_angles[0]))
    assert_close(token.skeleton.quat[5], z_quat_wxyz(local_angles[5]))
    assert_close(token.skeleton.quat[19], z_quat_wxyz(local_angles[19]))


def test_openxr_derives_20_joint_and_5_tip_offsets():
    frame, _, canonical_offsets, tip_offsets = nonidentity_openxr_fixture()
    token = openxr_to_hand_token(frame)

    assert len(token.skeleton.offsets) == 25
    assert_close(token.skeleton.offsets[0], [0.0, 0.0, 0.0])
    for index in range(1, 20):
        assert_close(token.skeleton.offsets[index], canonical_offsets[index])
    for tip_index, offset in enumerate(tip_offsets):
        assert_close(token.skeleton.offsets[20 + tip_index], offset)


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
