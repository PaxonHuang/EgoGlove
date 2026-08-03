"""Byte-compatible Hand Token v1 and v2 codecs."""
from __future__ import annotations

import math
import struct
from dataclasses import dataclass, field
from typing import List

MAGIC = b"HT"
VERSION = 1
VERSION_V2 = 2
FRAME_SIZE = 79
V2_LITE_FRAME_SIZE = 82
V2_SKELETON_FRAME_SIZE = 405
V2_MAX_FRAME_SIZE = 1024

OFF_MAGIC, OFF_VERSION, OFF_DEVICE_ID, OFF_TIMESTAMP = 0, 2, 3, 4
OFF_FLEX, OFF_QUAT, OFF_WRIST = 8, 18, 26
OFF_VEL, OFF_ACC, OFF_CONTACT, OFF_FORCE, OFF_CRC = 50, 56, 62, 67, 77
V2_OFF_CAPS, V2_OFF_TOTAL_LEN, V2_OFF_BASE, V2_OFF_TLV = 8, 9, 11, 80

PRODUCT_LITE, PRODUCT_PRO = 0, 1
HAND_LEFT, HAND_RIGHT = 0, 1
HAND_TOKEN_CAP_HAS_SKELETON = 0x01
HAND_TOKEN_CAP_HAS_FORCE = 0x02
HAND_TOKEN_CAP_HAS_VEL_ACC = 0x04
HAND_TOKEN_CAP_GLOBAL_WRIST = 0x08
HAND_TOKEN_CAP_QUAT_WLAST = 0x10
HAND_TOKEN_CAP_HANDEDNESS_AXIS = 0x20
HAND_TOKEN_CAP_SKEL_SMALLEST3 = 0x40
HAND_TOKEN_CAP_RESERVED = 0x80
HAND_TOKEN_TLV_SKELETON_QUAT20 = 0x01
HAND_TOKEN_TLV_REST_OFFSETS = 0x02
HAND_TOKEN_TLV_REST_MODEL_ID = 0x08

_PARENT = (-1, 0, 1, 2, 0, 4, 5, 6, 0, 8, 9, 10, 0, 12, 13, 14, 0, 16, 17, 18)
_MEDIAPIPE_JOINTS = (0, 1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 18, 19)
_TIP_PARENTS = (3, 7, 11, 15, 19)
_MEDIAPIPE_GROUPS = ((0, 1, 2, 3), (5, 6, 7), (9, 10, 11), (13, 14, 15), (17, 18, 19))


class UnsupportedRestModelError(ValueError):
    """Raised when FK requires an unimplemented rest-model adapter."""


@dataclass
class HandToken:
    product: int = 0
    hand: int = 0
    serial: int = 0
    timestamp_us: int = 0
    flex: List[float] = field(default_factory=lambda: [0.0] * 5)
    quat: List[float] = field(default_factory=lambda: [0.0] * 4)
    wrist_6dof: List[float] = field(default_factory=lambda: [0.0] * 6)
    vel: List[float] = field(default_factory=lambda: [0.0] * 3)
    acc: List[float] = field(default_factory=lambda: [0.0] * 3)
    contact: List[int] = field(default_factory=lambda: [0] * 5)
    force: List[float] = field(default_factory=lambda: [0.0] * 5)


@dataclass
class HandSkeleton:
    quat: List[List[float]] = field(default_factory=lambda: [[0.0] * 4 for _ in range(20)])
    offsets: List[List[float]] = field(default_factory=lambda: [[0.0] * 3 for _ in range(25)])
    model_id: int = 0
    revision: int = 0


@dataclass
class HandTokenV2:
    base: HandToken = field(default_factory=HandToken)
    caps: int = 0
    has_skeleton: bool = False
    skeleton: HandSkeleton = field(default_factory=HandSkeleton)


def make_device_id(product: int, hand: int, serial: int) -> int:
    return ((product & 1) << 7) | ((hand & 1) << 6) | (serial & 0x3F)


def split_device_id(dev_id: int):
    return (dev_id >> 7) & 1, (dev_id >> 6) & 1, dev_id & 0x3F


def crc16_modbus(buf: bytes) -> int:
    crc = 0xFFFF
    for byte in buf:
        crc ^= byte
        for _ in range(8):
            crc = ((crc >> 1) ^ 0xA001) if crc & 1 else crc >> 1
    return crc & 0xFFFF


def _f32(value: float) -> float:
    """Narrow a Python float to the C model's IEEE-754 binary32 value."""
    return struct.unpack("<f", struct.pack("<f", value))[0]


def _f16_bits(value: float) -> int:
    """C-compatible float32 -> IEEE-754 binary16 RN-even conversion."""
    bits = struct.unpack("<I", struct.pack("<f", value))[0]
    sign = (bits >> 16) & 0x8000
    exponent = (bits >> 23) & 0xFF
    mantissa = bits & 0x7FFFFF

    if exponent == 0xFF:
        # Match hand_token_f32_to_f16(): preserve the sign and canonicalize
        # every NaN payload to the quiet half-NaN bit 0x0200.
        return sign | 0x7C00 | (0x0200 if mantissa else 0)

    half_exponent = exponent - 127 + 15
    if half_exponent >= 0x1F:
        return sign | 0x7C00
    if half_exponent <= 0:
        if half_exponent < -10:
            return sign
        mantissa |= 0x800000
        shift = 14 - half_exponent
        half = mantissa >> shift
        remainder = mantissa & ((1 << shift) - 1)
        halfway = 1 << (shift - 1)
        if remainder > halfway or (remainder == halfway and half & 1):
            half += 1
        return sign | half

    half = sign | (half_exponent << 10) | (mantissa >> 13)
    remainder = mantissa & 0x1FFF
    if remainder > 0x1000 or (remainder == 0x1000 and half & 1):
        half += 1
    return half


def _f16(bits: int) -> float:
    return struct.unpack("<e", struct.pack("<H", bits))[0]


def _normalise(quat: List[float]) -> List[float]:
    values = [_f32(value) for value in quat]
    norm2 = _f32(0.0)
    for value in values:
        norm2 = _f32(norm2 + _f32(value * value))
    if not all(math.isfinite(value) for value in values) or not math.isfinite(norm2) or norm2 <= 0:
        raise ValueError("quaternion must be finite and non-zero")
    inv = _f32(1.0 / math.sqrt(norm2))
    return [_f32(value * inv) for value in values]


def _pack_f16(buf: bytearray, offset: int, value: float) -> None:
    struct.pack_into("<H", buf, offset, _f16_bits(value))


def _canonical_quat(quat: List[float]) -> List[float]:
    candidate = [_f16(_f16_bits(value)) for value in _normalise(list(quat))]
    bits = [_f16_bits(value) for value in candidate]
    for _ in range(32):
        normalized = _normalise(candidate)
        next_bits = [_f16_bits(value) for value in normalized]
        candidate = [_f16(value) for value in next_bits]
        if not all(math.isfinite(value) for value in candidate):
            raise ValueError("non-finite f16 quaternion")
        if next_bits == bits:
            return candidate
        bits = next_bits
    raise ValueError("f16 quaternion canonicalization did not converge")


def _write_base(buf: bytearray, offset: int, token: HandToken, w_last: bool, canonical: bool) -> None:
    for i in range(5): _pack_f16(buf, offset + i * 2, token.flex[i])
    quat = _canonical_quat(token.quat) if canonical else token.quat
    wire_quat = [quat[1], quat[2], quat[3], quat[0]] if w_last else quat
    for i, value in enumerate(wire_quat): _pack_f16(buf, offset + 10 + i * 2, value)
    for i in range(6): struct.pack_into("<f", buf, offset + 18 + i * 4, token.wrist_6dof[i])
    for i in range(3): _pack_f16(buf, offset + 42 + i * 2, token.vel[i])
    for i in range(3): _pack_f16(buf, offset + 48 + i * 2, token.acc[i])
    for i in range(5): buf[offset + 54 + i] = 1 if token.contact[i] else 0
    for i in range(5): _pack_f16(buf, offset + 59 + i * 2, token.force[i])


def _read_base(frame: bytes, offset: int, w_last: bool, normalise_quat: bool) -> HandToken:
    token = HandToken()
    token.flex = [struct.unpack_from("<e", frame, offset + i * 2)[0] for i in range(5)]
    wire_quat = [struct.unpack_from("<e", frame, offset + 10 + i * 2)[0] for i in range(4)]
    token.quat = [wire_quat[3], wire_quat[0], wire_quat[1], wire_quat[2]] if w_last else wire_quat
    if normalise_quat: token.quat = _normalise(token.quat)
    token.wrist_6dof = [struct.unpack_from("<f", frame, offset + 18 + i * 4)[0] for i in range(6)]
    token.vel = [struct.unpack_from("<e", frame, offset + 42 + i * 2)[0] for i in range(3)]
    token.acc = [struct.unpack_from("<e", frame, offset + 48 + i * 2)[0] for i in range(3)]
    token.contact = [1 if frame[offset + 54 + i] else 0 for i in range(5)]
    token.force = [struct.unpack_from("<e", frame, offset + 59 + i * 2)[0] for i in range(5)]
    return token


def serialize(token: HandToken) -> bytes:
    buf = bytearray(FRAME_SIZE)
    buf[:2], buf[2], buf[3] = MAGIC, VERSION, make_device_id(token.product, token.hand, token.serial)
    struct.pack_into("<I", buf, OFF_TIMESTAMP, token.timestamp_us & 0xFFFFFFFF)
    _write_base(buf, OFF_FLEX, token, False, False)
    struct.pack_into("<H", buf, OFF_CRC, crc16_modbus(bytes(buf[:OFF_CRC])))
    return bytes(buf)


def parse(frame: bytes) -> HandToken:
    if len(frame) != FRAME_SIZE: raise ValueError("v1 frame must be exactly 79 bytes")
    if frame[:2] != MAGIC: raise ValueError("bad magic (expect 'HT')")
    if frame[2] != VERSION: raise ValueError(f"unsupported version {frame[2]}")
    if struct.unpack_from("<H", frame, OFF_CRC)[0] != crc16_modbus(frame[:OFF_CRC]): raise ValueError("CRC mismatch")
    token = _read_base(frame, OFF_FLEX, False, False)
    token.product, token.hand, token.serial = split_device_id(frame[3])
    token.timestamp_us = struct.unpack_from("<I", frame, 4)[0]
    return token


def _validate_skeleton(skeleton: HandSkeleton) -> None:
    if skeleton.revision == 0: raise ValueError("rest-model revision must be nonzero")
    if len(skeleton.quat) != 20 or len(skeleton.offsets) != 25: raise ValueError("invalid skeleton dimensions")
    if skeleton.offsets[0] != [0.0, 0.0, 0.0]: raise ValueError("wrist offset must be zero")
    for quat in skeleton.quat: _normalise(quat)
    for offset in skeleton.offsets:
        if len(offset) != 3 or not all(math.isfinite(_f16(_f16_bits(value))) for value in offset):
            raise ValueError("offset must be finite f16")


def serialize_v2(token: HandTokenV2) -> bytes:
    if token.caps & (HAND_TOKEN_CAP_GLOBAL_WRIST | HAND_TOKEN_CAP_SKEL_SMALLEST3 | HAND_TOKEN_CAP_RESERVED):
        raise ValueError("unsupported v2 capability")
    has_skeleton = bool(token.caps & HAND_TOKEN_CAP_HAS_SKELETON)
    if has_skeleton != token.has_skeleton: raise ValueError("HAS_SKELETON mismatch")
    if has_skeleton: _validate_skeleton(token.skeleton)
    length = V2_SKELETON_FRAME_SIZE if has_skeleton else V2_LITE_FRAME_SIZE
    buf = bytearray(length)
    buf[:2], buf[2], buf[3], buf[8] = MAGIC, VERSION_V2, make_device_id(token.base.product, token.base.hand, token.base.serial), token.caps
    struct.pack_into("<I", buf, 4, token.base.timestamp_us & 0xFFFFFFFF)
    struct.pack_into("<H", buf, 9, length)
    w_last = bool(token.caps & HAND_TOKEN_CAP_QUAT_WLAST)
    _write_base(buf, V2_OFF_BASE, token.base, w_last, True)
    if has_skeleton:
        cursor = V2_OFF_TLV
        buf[cursor:cursor + 3] = bytes((1, 160, 0)); cursor += 3
        for quat in token.skeleton.quat:
            q = _canonical_quat(quat); q = [q[1], q[2], q[3], q[0]] if w_last else q
            for i, value in enumerate(q): _pack_f16(buf, cursor + i * 2, value)
            cursor += 8
        buf[cursor:cursor + 3] = bytes((2, 150, 0)); cursor += 3
        for offset in token.skeleton.offsets:
            for i, value in enumerate(offset): _pack_f16(buf, cursor + i * 2, value)
            cursor += 6
        buf[cursor:cursor + 3] = bytes((8, 4, 0)); cursor += 3
        struct.pack_into("<HH", buf, cursor, token.skeleton.model_id, token.skeleton.revision)
    struct.pack_into("<H", buf, length - 2, crc16_modbus(bytes(buf[:-2])))
    return bytes(buf)


def parse_v2(frame: bytes) -> HandTokenV2:
    if len(frame) < V2_LITE_FRAME_SIZE or frame[:2] != MAGIC or frame[2] != VERSION_V2: raise ValueError("not a v2 frame")
    total = struct.unpack_from("<H", frame, 9)[0]
    if total != len(frame) or total > V2_MAX_FRAME_SIZE: raise ValueError("bad v2 total length")
    caps = frame[8]
    if caps & (HAND_TOKEN_CAP_GLOBAL_WRIST | HAND_TOKEN_CAP_SKEL_SMALLEST3 | HAND_TOKEN_CAP_RESERVED): raise ValueError("unsupported v2 capability")
    if struct.unpack_from("<H", frame, len(frame) - 2)[0] != crc16_modbus(frame[:-2]): raise ValueError("CRC mismatch")
    has_skeleton = bool(caps & HAND_TOKEN_CAP_HAS_SKELETON)
    if not has_skeleton and len(frame) != V2_LITE_FRAME_SIZE: raise ValueError("Lite v2 has TLVs")
    if has_skeleton and len(frame) > V2_MAX_FRAME_SIZE: raise ValueError("v2 frame too large")
    w_last = bool(caps & HAND_TOKEN_CAP_QUAT_WLAST)
    base = _read_base(frame, V2_OFF_BASE, w_last, True)
    base.product, base.hand, base.serial = split_device_id(frame[3])
    base.timestamp_us = struct.unpack_from("<I", frame, 4)[0]
    skeleton, seen, cursor, crc = HandSkeleton(), 0, V2_OFF_TLV, len(frame) - 2
    while cursor < crc:
        if crc - cursor < 3: raise ValueError("truncated TLV header")
        kind, length = frame[cursor], struct.unpack_from("<H", frame, cursor + 1)[0]; cursor += 3
        if length > crc - cursor: raise ValueError("truncated TLV value")
        value_end = cursor + length
        if kind == 1:
            if seen & 1 or length != 160: raise ValueError("invalid quaternion TLV")
            seen |= 1
            for joint in range(20):
                values = [struct.unpack_from("<e", frame, cursor + joint * 8 + i * 2)[0] for i in range(4)]
                skeleton.quat[joint] = _normalise([values[3], values[0], values[1], values[2]] if w_last else values)
        elif kind == 2:
            if seen & 2 or length != 150: raise ValueError("invalid offsets TLV")
            seen |= 2
            skeleton.offsets = [[struct.unpack_from("<e", frame, cursor + index * 6 + i * 2)[0] for i in range(3)] for index in range(25)]
        elif kind == 8:
            if seen & 4 or length != 4: raise ValueError("invalid rest-model TLV")
            seen |= 4
            skeleton.model_id, skeleton.revision = struct.unpack_from("<HH", frame, cursor)
        cursor = value_end
    if cursor != crc: raise ValueError("TLV bounds error")
    if has_skeleton:
        if seen != 7: raise ValueError("missing required skeleton TLV")
        _validate_skeleton(skeleton)
    elif seen: raise ValueError("TLVs require HAS_SKELETON")
    return HandTokenV2(base=base, caps=caps, has_skeleton=has_skeleton, skeleton=skeleton)


def parse_any(frame: bytes):
    if len(frame) < 3 or frame[:2] != MAGIC: raise ValueError("bad magic")
    if frame[2] == VERSION: return parse(frame)
    if frame[2] == VERSION_V2: return parse_v2(frame)
    raise ValueError(f"unsupported version {frame[2]}")


def _quat_mul(left: List[float], right: List[float]) -> List[float]:
    a, b, c, d = left; e, f, g, h = right
    return [_f32(a*e-b*f-c*g-d*h), _f32(a*f+b*e+c*h-d*g),
            _f32(a*g-b*h+c*e+d*f), _f32(a*h+b*g-c*f+d*e)]


def _rotate(quat: List[float], vector: List[float]) -> List[float]:
    """Rotate with the same cross-product operation graph as C quat_rotate()."""
    q = [_f32(value) for value in quat]
    v = [_f32(value) for value in vector]
    u = q[1:]
    uv = [
        _f32(u[1] * v[2] - u[2] * v[1]),
        _f32(u[2] * v[0] - u[0] * v[2]),
        _f32(u[0] * v[1] - u[1] * v[0]),
    ]
    uuv = [
        _f32(u[1] * uv[2] - u[2] * uv[1]),
        _f32(u[2] * uv[0] - u[0] * uv[2]),
        _f32(u[0] * uv[1] - u[1] * uv[0]),
    ]
    result = []
    for i in range(3):
        w_uv = _f32(q[0] * uv[i])
        sum_term = _f32(w_uv + uuv[i])
        scaled = _f32(_f32(2.0) * sum_term)
        result.append(_f32(v[i] + scaled))
    return result


def fk21(skeleton: HandSkeleton) -> List[List[float]]:
    if skeleton.model_id not in (0, 1, 2): raise UnsupportedRestModelError(f"unsupported rest model {skeleton.model_id}")
    _validate_skeleton(skeleton)
    positions, rotations = [[0.0, 0.0, 0.0] for _ in range(20)], [[1.0, 0.0, 0.0, 0.0] for _ in range(20)]
    for joint, parent in enumerate(_PARENT):
        rotations[joint] = _normalise(skeleton.quat[joint]) if parent < 0 else _quat_mul(rotations[parent], _normalise(skeleton.quat[joint]))
        if parent >= 0:
            offset = _rotate(rotations[parent], skeleton.offsets[joint])
            positions[joint] = [_f32(positions[parent][axis] + offset[axis]) for axis in range(3)]
    landmarks = [list(positions[0])]
    for joints, parent, offset_index in zip(
        ((1, 2, 3), (5, 6, 7), (9, 10, 11), (13, 14, 15), (17, 18, 19)),
        _TIP_PARENTS,
        range(20, 25),
    ):
        landmarks.extend(list(positions[joint]) for joint in joints)
        offset = _rotate(rotations[parent], skeleton.offsets[offset_index])
        landmarks.append([_f32(positions[parent][axis] + offset[axis]) for axis in range(3)])
    return landmarks


def to_mano(t: HandToken) -> dict:
    return {"representation": "mano", "hand": "R" if t.hand else "L", "flex": list(t.flex), "quat_wxyz": list(t.quat), "wrist_pose": list(t.wrist_6dof), "timestamp_us": t.timestamp_us, "_status": "🟡 结构视图; flex→MANO θ/β 回归待实现 (models/mano/)"}


def to_robot_action(t: HandToken) -> dict:
    return {"representation": "robot_action", "joint": list(t.flex), "wrist_6dof": list(t.wrist_6dof), "vel": list(t.vel), "acc": list(t.acc), "contact": list(t.contact), "force": list(t.force), "timestamp_us": t.timestamp_us, "device": {"product": "Pro" if t.product else "Lite", "hand": "R" if t.hand else "L", "serial": t.serial}, "_status": "🟡 结构动作向量; joint retarget 待实现 (models/robot/)"}
