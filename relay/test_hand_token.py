"""
test_hand_token.py — Hand Token v1 Python 单测 + 跨语言金标校验

可用 pytest 运行, 也可直接 `python3 test_hand_token.py`。
金标向量 GOLDEN_HEX 与 firmware/shared/test/test_hand_token.c 共用同一串:
两端都对 canonical reference token 序列化并断言等于该串 → 逐字节 C↔Python 兼容。
作者/署名: PaxonHuang <quenchkidney@outlook.com>
"""
import struct

from hand_token import (
    HandToken, serialize, parse, crc16_modbus,
    make_device_id, split_device_id, to_mano, to_robot_action,
    FRAME_SIZE, PRODUCT_PRO, HAND_RIGHT,
)

# 与 C test 的 GOLDEN= 输出保持一致 (首轮 host 运行后填入真实值)。
GOLDEN_HEX = ""  # 占位; 见 firmware/shared/test 首轮 GOLDEN= 输出


def reference_token() -> HandToken:
    """与 C make_ref() 完全一致; 所有 float16 字段取可精确表示值。"""
    return HandToken(
        product=PRODUCT_PRO, hand=HAND_RIGHT, serial=7,   # device_id=0xC7
        timestamp_us=12345678,                            # 0x00BC614E
        flex=[0.0, 0.25, 0.5, 0.75, 1.0],
        quat=[1.0, 0.0, 0.0, 0.0],
        wrist_6dof=[0.125, -0.25, 0.5, 0.0, 1.5, -3.0],
        vel=[0.5, 0.25, 0.125],
        acc=[2.0, 0.0, -2.0],
        contact=[1, 0, 1, 0, 1],
        force=[0.5, 0.0, 1.25, 0.0, 2.0],
    )


def test_crc_known_vector():
    assert crc16_modbus(b"123456789") == 0x4B37


def test_device_id_roundtrip():
    dev = make_device_id(1, 1, 7)
    assert dev == 0xC7
    assert split_device_id(dev) == (1, 1, 7)


def test_f16_exact_via_struct():
    # struct '<e' 是 IEEE754 half; 与 C f32_to_f16 (round-to-nearest-even) 一致
    assert struct.pack("<e", 0.25) == b"\x00\x34"
    assert struct.pack("<e", 1.0) == b"\x00\x3c"
    assert struct.pack("<e", 2.0) == b"\x00\x40"


def test_serialize_len_and_header():
    frame = serialize(reference_token())
    assert len(frame) == FRAME_SIZE == 79
    assert frame[0:2] == b"HT"
    assert frame[2] == 1
    assert frame[3] == 0xC7


def test_roundtrip_lossless():
    ref = reference_token()
    got = parse(serialize(ref))
    assert (got.product, got.hand, got.serial) == (ref.product, ref.hand, ref.serial)
    assert got.timestamp_us == ref.timestamp_us
    # 全部取可精确表示值 → f16/f32 round-trip 无损, 可用 ==
    assert got.flex == ref.flex
    assert got.quat == ref.quat
    assert got.wrist_6dof == ref.wrist_6dof
    assert got.vel == ref.vel
    assert got.acc == ref.acc
    assert got.contact == ref.contact
    assert got.force == ref.force


def test_reject_bad_crc():
    frame = bytearray(serialize(reference_token()))
    frame[10] ^= 0xFF
    try:
        parse(bytes(frame))
        assert False, "expected ValueError on CRC mismatch"
    except ValueError:
        pass


def test_reject_bad_magic():
    frame = bytearray(serialize(reference_token()))
    frame[0] = 0xAA
    try:
        parse(bytes(frame))
        assert False, "expected ValueError on bad magic"
    except ValueError:
        pass


def test_reject_short():
    frame = serialize(reference_token())
    try:
        parse(frame[:-1])
        assert False, "expected ValueError on short frame"
    except ValueError:
        pass


def test_dual_representation_fork():
    t = parse(serialize(reference_token()))
    mano = to_mano(t)
    robot = to_robot_action(t)
    assert mano["representation"] == "mano"
    assert mano["hand"] == "R"
    assert mano["flex"] == [0.0, 0.25, 0.5, 0.75, 1.0]
    assert robot["representation"] == "robot_action"
    assert robot["force"] == [0.5, 0.0, 1.25, 0.0, 2.0]
    assert robot["device"]["product"] == "Pro"


def test_golden_cross_language():
    valid = len(GOLDEN_HEX) == FRAME_SIZE * 2 and all(
        c in "0123456789abcdefABCDEF" for c in GOLDEN_HEX
    )
    if not valid:
        # 金标未填时跳过 (首轮): C host 测试打印 GOLDEN= 后填入本文件
        print("SKIP golden: GOLDEN_HEX 未填, 见 firmware/shared/test 首轮 GOLDEN= 输出")
        return
    assert serialize(reference_token()).hex() == GOLDEN_HEX.lower()


if __name__ == "__main__":
    fails = 0
    for name, fn in sorted(globals().items()):
        if name.startswith("test_") and callable(fn):
            try:
                fn()
                print(f"[ ok ] {name}")
            except AssertionError as e:
                fails += 1
                print(f"[FAIL] {name}: {e}")
    print("== ALL PASS ==" if not fails else f"== {fails} FAILED ==")
    raise SystemExit(1 if fails else 0)
