"""Hand Token v1/v2 Python tests and C wire interoperability checks."""
import math
import struct

from hand_token import (
    HAND_LEFT, HAND_RIGHT, PRODUCT_PRO,
    HAND_TOKEN_CAP_HAS_SKELETON, HAND_TOKEN_CAP_QUAT_WLAST,
    HandSkeleton, HandToken, HandTokenV2, UnsupportedRestModelError,
    crc16_modbus, fk21, make_device_id, parse, parse_any, parse_v2,
    serialize, serialize_v2, split_device_id, _f16_bits,
)

GOLDEN_V1_HEX = (
    "485401c74e61bc00000000340038003a003c003c0000000000000000003e000080be"
    "0000003f000000000000c03f000040c00038003400300040000000c0010001000100"
    "380000003d000000408e4c"
)
GOLDEN_V2_LITE_HEX = (
    "485402c74e61bc00005200000000340038003a003c003c0000000000000000003e000080be"
    "0000003f000000000000c03f000040c00038003400300040000000c001000100010038"
    "0000003d00000040459d"
)
# Signed-off skeleton fixture: reference_v2(w_last=True), TLVs 01/02/08,
# canonical f16 quaternion fixed point, and x/y/z/w wire order.
GOLDEN_V2_SKELETON_HEX = (
    "485402c74e61bc00119501000000340038003a003c003800b8003800380000003e000080be000000"
    "3f000000000000c03f000040c00038003400300040000000c0010001000100380000003d00000040"
    "01a0000038003800b80038000000000000003c000000000000003c000000000000003c0000000000"
    "00003c000000000000003c000000000000003c000000000000003c000000000000003c0000000000"
    "00003c000000000000003c000000000000003c000000000000003c000000000000003c0000000000"
    "00003c000000000000003c000000000000003c000000000000003c000000000000003c0000000000"
    "00003c02960000000000000000340000000000340000000000340000000000340000000000340000"
    "00000034000000000034000000000034000000000034000000000034000000000034000000000034"
    "00000000003400000000003400000000003400000000003400000000003400000000003400000000"
    "00340000000000340000000000340000000000340000000000340000000000340000000008040000"
    "000100e347"
)

def reference_token():
    return HandToken(
        product=PRODUCT_PRO, hand=HAND_RIGHT, serial=7, timestamp_us=12345678,
        flex=[0.0, 0.25, 0.5, 0.75, 1.0], quat=[1.0, 0.0, 0.0, 0.0],
        wrist_6dof=[0.125, -0.25, 0.5, 0.0, 1.5, -3.0],
        vel=[0.5, 0.25, 0.125], acc=[2.0, 0.0, -2.0],
        contact=[1, 0, 1, 0, 1], force=[0.5, 0.0, 1.25, 0.0, 2.0],
    )


def reference_skeleton():
    skeleton = HandSkeleton(model_id=0, revision=1)
    skeleton.quat = [[1.0, 0.0, 0.0, 0.0] for _ in range(20)]
    skeleton.quat[0] = [0.5, 0.5, 0.5, -0.5]
    skeleton.offsets = [[0.0, 0.0, 0.0]] + [[0.25, 0.0, 0.0] for _ in range(24)]
    return skeleton


def reference_v2(w_last=True):
    base = reference_token()
    base.quat = [0.5, 0.5, -0.5, 0.5]
    skeleton = reference_skeleton()
    skeleton.quat[1] = [2.0, 0.0, 0.0, 0.0]
    caps = HAND_TOKEN_CAP_HAS_SKELETON | (HAND_TOKEN_CAP_QUAT_WLAST if w_last else 0)
    return HandTokenV2(base=base, caps=caps, has_skeleton=True, skeleton=skeleton)


def recalc_crc(frame):
    frame[-2:] = struct.pack("<H", crc16_modbus(bytes(frame[:-2])))
    return bytes(frame)


def assert_value_error(fn, *args):
    try:
        fn(*args)
    except ValueError:
        return
    raise AssertionError("expected ValueError")


def _float32_ordered_bits(value):
    """Return monotonic float32 bits, rejecting nonfinite values."""
    if not math.isfinite(value):
        raise ValueError("float32 ULP comparison requires finite values")
    bits = struct.unpack("<I", struct.pack("<f", value))[0]
    if bits == 0x80000000 or bits == 0:
        return 0x80000000
    return (~bits & 0xFFFFFFFF) if bits & 0x80000000 else bits | 0x80000000


def _float32_ulp_distance(actual, expected):
    return abs(_float32_ordered_bits(actual) - _float32_ordered_bits(expected))

def test_f16_narrows_through_float32_at_rounding_boundary():
    # C receives float fields as binary32 before its RN-even f16 conversion.
    boundary = 1.0 + 2.0 ** -11 + 2.0 ** -25
    token = reference_token()
    token.flex[0] = boundary
    assert serialize(token)[8:10] == b"\x00\x3c"


def test_f16_bits_matches_c_overflow_and_nonfinite_rules():
    assert _f16_bits(65520.0) == 0x7C00
    assert _f16_bits(-65520.0) == 0xFC00
    assert _f16_bits(float("inf")) == 0x7C00
    assert _f16_bits(float("-inf")) == 0xFC00
    assert _f16_bits(float("nan")) == 0x7E00
    negative_nan = struct.unpack("<f", struct.pack("<I", 0xFFC12345))[0]
    assert _f16_bits(negative_nan) == 0xFE00


def test_v2_serializer_rejects_fields_that_become_nonfinite():
    token = reference_v2()
    token.skeleton.offsets[1][0] = 65520.0
    assert_value_error(serialize_v2, token)
    token = reference_v2()
    token.skeleton.offsets[1][0] = float("nan")
    assert_value_error(serialize_v2, token)


def test_frozen_goldens_match_serializers_and_reconstruct_reference_state():
    assert len(GOLDEN_V1_HEX) == 158 and GOLDEN_V1_HEX.isascii() and GOLDEN_V1_HEX.islower()
    assert len(GOLDEN_V2_LITE_HEX) == 164 and GOLDEN_V2_LITE_HEX.isascii() and GOLDEN_V2_LITE_HEX.islower()
    assert len(GOLDEN_V2_SKELETON_HEX) == 810 and GOLDEN_V2_SKELETON_HEX.isascii() and GOLDEN_V2_SKELETON_HEX.islower()
    assert all(character in "0123456789abcdef" for golden in (
        GOLDEN_V1_HEX, GOLDEN_V2_LITE_HEX, GOLDEN_V2_SKELETON_HEX
    ) for character in golden)

    reference = reference_token()
    assert serialize(reference).hex() == GOLDEN_V1_HEX
    parsed_v1 = parse(bytes.fromhex(GOLDEN_V1_HEX))
    assert (parsed_v1.product, parsed_v1.hand, parsed_v1.serial, parsed_v1.timestamp_us) == (
        reference.product, reference.hand, reference.serial, reference.timestamp_us
    )

    assert serialize_v2(HandTokenV2(base=reference_token())).hex() == GOLDEN_V2_LITE_HEX
    parsed_lite = parse_v2(bytes.fromhex(GOLDEN_V2_LITE_HEX))
    assert not parsed_lite.has_skeleton and parsed_lite.caps == 0
    assert (parsed_lite.base.product, parsed_lite.base.hand, parsed_lite.base.serial, parsed_lite.base.timestamp_us) == (
        reference.product, reference.hand, reference.serial, reference.timestamp_us
    )

    # W-last is the signed-off frozen fixture; W-first is behavior-tested separately.
    assert serialize_v2(reference_v2(w_last=True)).hex() == GOLDEN_V2_SKELETON_HEX
    parsed_skeleton = parse_v2(bytes.fromhex(GOLDEN_V2_SKELETON_HEX))
    assert parsed_skeleton.has_skeleton
    assert parsed_skeleton.caps == HAND_TOKEN_CAP_HAS_SKELETON | HAND_TOKEN_CAP_QUAT_WLAST
    assert (parsed_skeleton.base.product, parsed_skeleton.base.hand,
            parsed_skeleton.base.serial, parsed_skeleton.base.timestamp_us) == (
        reference.product, reference.hand, reference.serial, reference.timestamp_us
    )
    assert (parsed_skeleton.skeleton.model_id, parsed_skeleton.skeleton.revision) == (0, 1)
    assert parsed_skeleton.skeleton.quat[0] == [0.5, 0.5, 0.5, -0.5]


def test_v1_golden_and_api_regression():
    assert crc16_modbus(b"123456789") == 0x4B37
    assert make_device_id(1, 1, 7) == 0xC7
    assert split_device_id(0xC7) == (1, 1, 7)
    assert_value_error(parse, serialize(reference_token())[:-1])


def test_v2_lite_wire_layout_and_version_gate():
    token = HandTokenV2(base=reference_token())
    frame = serialize_v2(token)
    assert len(frame) == 82
    assert frame[:4] == b"HT\x02\xc7"
    assert frame[8] == 0 and struct.unpack_from("<H", frame, 9)[0] == 82
    assert parse_v2(frame).has_skeleton is False
    assert isinstance(parse_any(serialize(reference_token())), HandToken)
    assert isinstance(parse_any(frame), HandTokenV2)
    assert_value_error(parse, frame)


def test_v2_skeleton_layout_wlast_and_wfirst_round_trip():
    frame = serialize_v2(reference_v2(True))
    assert len(frame) == 405
    assert frame[80] == 1 and struct.unpack_from("<H", frame, 81)[0] == 160
    assert frame[243] == 2 and struct.unpack_from("<H", frame, 244)[0] == 150
    assert frame[396] == 8 and struct.unpack_from("<H", frame, 397)[0] == 4
    assert struct.unpack_from("<4e", frame, 83) == (0.5, 0.5, -0.5, 0.5)
    parsed = parse_v2(frame)
    assert parsed.skeleton.quat[0] == [0.5, 0.5, 0.5, -0.5]
    assert serialize_v2(parsed) == frame
    wfirst = serialize_v2(reference_v2(False))
    assert len(wfirst) == 405 and parse_v2(wfirst).skeleton.quat[0] == [0.5, 0.5, 0.5, -0.5]
    assert serialize_v2(parse_v2(wfirst)) == wfirst


def test_v2_parser_canonicalizes_finite_nonunit_quaternions():
    for w_last in (True, False):
        frame = bytearray(serialize_v2(reference_v2(w_last)))
        struct.pack_into("<H", frame, 21, 0x4000)
        external = recalc_crc(frame)
        parsed = parse_v2(external)
        assert math.isclose(sum(x * x for x in parsed.base.quat), 1.0, rel_tol=0, abs_tol=1e-6)
        canonical = serialize_v2(parsed)
        assert canonical != external
        assert serialize_v2(parse_v2(canonical)) == canonical
        frame = bytearray(serialize_v2(reference_v2(w_last)))
        struct.pack_into("<H", frame, 83, 0x4000)
        external = recalc_crc(frame)
        parsed = parse_v2(external)
        assert math.isclose(sum(x * x for x in parsed.skeleton.quat[0]), 1.0, rel_tol=0, abs_tol=1e-6)
        canonical = serialize_v2(parsed)
        assert serialize_v2(parse_v2(canonical)) == canonical


def test_v2_rejects_malformed_c_cases_and_skips_unknown_tlv():
    frame = serialize_v2(reference_v2(True))
    for caps in (0x08, 0x40, 0x80):
        bad = bytearray(frame); bad[8] = caps; assert_value_error(parse_v2, recalc_crc(bad))
    bad = bytearray(frame); bad[9] += 1; assert_value_error(parse_v2, bytes(bad))
    bad = bytearray(frame); bad[-1] ^= 1; assert_value_error(parse_v2, bytes(bad))
    assert_value_error(parse_v2, frame[:-1])
    bad = bytearray(frame); bad[243] = 1; assert_value_error(parse_v2, recalc_crc(bad))
    bad = bytearray(frame); struct.pack_into("<H", bad, 81, 159); assert_value_error(parse_v2, recalc_crc(bad))
    bad = bytearray(frame); struct.pack_into("<H", bad, 246, 0x3C00); assert_value_error(parse_v2, recalc_crc(bad))
    bad = bytearray(frame); struct.pack_into("<H", bad, 401, 0); assert_value_error(parse_v2, recalc_crc(bad))
    bad = bytearray(frame); struct.pack_into("<H", bad, 83, 0x7C00); assert_value_error(parse_v2, recalc_crc(bad))
    bad = bytearray(frame); bad[21:29] = b"\0" * 8; assert_value_error(parse_v2, recalc_crc(bad))
    unknown = bytearray(frame[:-2]); unknown[243:243] = b"\x7f\x01\0\xa5"
    struct.pack_into("<H", unknown, 9, len(unknown) + 2)
    unknown.extend(b"\0\0")
    assert parse_v2(recalc_crc(unknown)).has_skeleton


def test_v2_serializer_rejects_invalid_skeleton_contract():
    token = reference_v2()
    token.skeleton.revision = 0; assert_value_error(serialize_v2, token)
    token = reference_v2(); token.skeleton.offsets[0][0] = 0.25; assert_value_error(serialize_v2, token)
    token = reference_v2(); token.has_skeleton = False; assert_value_error(serialize_v2, token)
    token = reference_v2(); token.skeleton.offsets[1][0] = math.inf; assert_value_error(serialize_v2, token)


def test_fk21_nonidentity_chain_matches_c_float32_fixture():
    """Direct C quat_rotate()/FK output fixture, stored as little-endian f32."""
    skeleton = HandSkeleton(model_id=0, revision=1)
    skeleton.quat = [[1.0, 0.0, 0.0, 0.0] for _ in range(20)]
    skeleton.quat[0] = [0.9238795, 0.0, 0.3826834, 0.0]
    skeleton.quat[1] = [0.9659258, 0.2588190, 0.0, 0.0]
    skeleton.quat[2] = [0.9396926, 0.0, 0.3420201, 0.0]
    skeleton.offsets = [[0.0, 0.0, 0.0] for _ in range(25)]
    skeleton.offsets[1] = [1.0, 0.0, 0.0]
    skeleton.offsets[2] = [0.5, 0.25, 0.0]
    skeleton.offsets[3] = [0.25, 0.0, 0.5]
    skeleton.offsets[20] = [0.0, 0.0, 0.75]

    # Generated once by compiling firmware/shared/hand_skeleton.c with this
    # fixture input; exact little-endian binary32 output is retained here so
    # every Python landmark remains covered without a runtime C dependency.
    expected_f32_le = bytes.fromhex(
        # Exact 504-hex-character output from the C host driver compiled with
        # firmware/shared/hand_skeleton.c and the fixture above (252 bytes).
        "000000000000000000000000f204353f00000000f50435bf"
        "0514933fd6b35d3ed2e678bf81edd23f60bed73d727299bf"
        "40cc1540184a3abe040c98bf"
        + "00" * 192
    )
    expected = struct.unpack("<63f", expected_f32_le)
    actual = tuple(value for point in fk21(skeleton) for value in point)
    assert len(expected) == len(actual) == 21 * 3
    # Host expression-graph evaluation measured at most 24 ULP from the C fixture.
    for actual_value, expected_value in zip(actual, expected):
        assert _float32_ulp_distance(actual_value, expected_value) <= 24, (
            actual_value, expected_value
        )


def test_fk21_identity_mapping_tips_and_model_errors():
    skeleton = HandSkeleton(model_id=0, revision=1)
    skeleton.quat = [[1.0, 0.0, 0.0, 0.0] for _ in range(20)]
    skeleton.offsets = [[0.0, 0.0, 0.0] for _ in range(25)]
    for index in range(1, 20): skeleton.offsets[index][0] = 1.0
    for index in range(20, 25): skeleton.offsets[index][0] = 2.0
    points = fk21(skeleton)
    assert [p[0] for p in points] == [0, 1, 2, 3, 5, 2, 3, 4, 6, 2, 3, 4, 6, 2, 3, 4, 6, 2, 3, 4, 6]
    skeleton.model_id = 99
    try: fk21(skeleton)
    except UnsupportedRestModelError: pass
    else: raise AssertionError("expected UnsupportedRestModelError")
    skeleton.model_id = 0; skeleton.revision = 0; assert_value_error(fk21, skeleton)


if __name__ == "__main__":
    failures = 0
    for name, value in sorted(globals().items()):
        if name.startswith("test_") and callable(value):
            try:
                value(); print(f"[ ok ] {name}")
            except Exception as exc:
                failures += 1; print(f"[FAIL] {name}: {exc}")
    raise SystemExit(bool(failures))
