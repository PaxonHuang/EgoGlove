"""
relay/hand_token.py — EchoGlove/EgoGlove V7 Hand Token v1 (Python 端)

与 firmware/shared/hand_token.{h,c} 逐字节兼容 (canonical 79B 帧, 小端,
float16, CRC-16/MODBUS)。relay 从任意传输 (USB-CDC / WS / UDP / BLE) 收到
Hand Token 后, 解析并**分叉**为双表示层 (STRATEGY.md D3):
  - to_mano()         → MANO Layer (Unity/Unreal/XR/数字人/手语)
  - to_robot_action() → Robot Action Layer (ROS2/机械臂/灵巧手/VLA/RL)

真实性 (docs/V7/ARCHITECTURE.md §8):
  - 协议 parse/serialize/CRC: ✅ (test_hand_token.py + firmware host 单测双向验证)
  - MANO θ/β 回归、Robot retarget 的**语义映射**: 🟡 (models/mano, models/robot 待实现)
    本模块的 to_mano/to_robot_action 目前是**结构化视图**, 不做真实回归/重定向。

作者/署名: PaxonHuang <quenchkidney@outlook.com>
"""
from __future__ import annotations

import struct
from dataclasses import dataclass, field
from typing import List

# ---- 协议常量 (对齐 hand_token.h) ----
MAGIC = b"HT"          # 0x48 0x54
VERSION = 1
FRAME_SIZE = 79

OFF_MAGIC, OFF_VERSION, OFF_DEVICE_ID, OFF_TIMESTAMP = 0, 2, 3, 4
OFF_FLEX, OFF_QUAT, OFF_WRIST = 8, 18, 26
OFF_VEL, OFF_ACC, OFF_CONTACT, OFF_FORCE, OFF_CRC = 50, 56, 62, 67, 77

PRODUCT_LITE, PRODUCT_PRO = 0, 1
HAND_LEFT, HAND_RIGHT = 0, 1


@dataclass
class HandToken:
    product: int = 0                                   # 0=Lite, 1=Pro
    hand: int = 0                                       # 0=Left, 1=Right
    serial: int = 0                                     # 0..63
    timestamp_us: int = 0
    flex: List[float] = field(default_factory=lambda: [0.0] * 5)
    quat: List[float] = field(default_factory=lambda: [0.0] * 4)
    wrist_6dof: List[float] = field(default_factory=lambda: [0.0] * 6)
    vel: List[float] = field(default_factory=lambda: [0.0] * 3)
    acc: List[float] = field(default_factory=lambda: [0.0] * 3)
    contact: List[int] = field(default_factory=lambda: [0] * 5)
    force: List[float] = field(default_factory=lambda: [0.0] * 5)


# ---- device_id 编解码 (对齐 C) ----
def make_device_id(product: int, hand: int, serial: int) -> int:
    return ((product & 1) << 7) | ((hand & 1) << 6) | (serial & 0x3F)


def split_device_id(dev_id: int):
    return (dev_id >> 7) & 1, (dev_id >> 6) & 1, dev_id & 0x3F


# ---- CRC-16/MODBUS (poly 0xA001, init 0xFFFF) ----
def crc16_modbus(buf: bytes) -> int:
    crc = 0xFFFF
    for byte in buf:
        crc ^= byte
        for _ in range(8):
            if crc & 1:
                crc = (crc >> 1) ^ 0xA001
            else:
                crc >>= 1
    return crc & 0xFFFF


# ---- 序列化 / 解析 ----
def serialize(t: HandToken) -> bytes:
    buf = bytearray(FRAME_SIZE)
    buf[OFF_MAGIC:OFF_MAGIC + 2] = MAGIC
    buf[OFF_VERSION] = VERSION
    buf[OFF_DEVICE_ID] = make_device_id(t.product, t.hand, t.serial)
    struct.pack_into("<I", buf, OFF_TIMESTAMP, t.timestamp_us & 0xFFFFFFFF)
    for i in range(5):
        struct.pack_into("<e", buf, OFF_FLEX + i * 2, t.flex[i])
    for i in range(4):
        struct.pack_into("<e", buf, OFF_QUAT + i * 2, t.quat[i])
    for i in range(6):
        struct.pack_into("<f", buf, OFF_WRIST + i * 4, t.wrist_6dof[i])
    for i in range(3):
        struct.pack_into("<e", buf, OFF_VEL + i * 2, t.vel[i])
    for i in range(3):
        struct.pack_into("<e", buf, OFF_ACC + i * 2, t.acc[i])
    for i in range(5):
        buf[OFF_CONTACT + i] = 1 if t.contact[i] else 0
    for i in range(5):
        struct.pack_into("<e", buf, OFF_FORCE + i * 2, t.force[i])
    struct.pack_into("<H", buf, OFF_CRC, crc16_modbus(bytes(buf[:OFF_CRC])))
    return bytes(buf)


def parse(frame: bytes) -> HandToken:
    """解析 79B 帧。非法 (长度/magic/version/CRC) 抛 ValueError。"""
    if len(frame) < FRAME_SIZE:
        raise ValueError(f"frame too short: {len(frame)} < {FRAME_SIZE}")
    if frame[OFF_MAGIC:OFF_MAGIC + 2] != MAGIC:
        raise ValueError("bad magic (expect 'HT')")
    if frame[OFF_VERSION] != VERSION:
        raise ValueError(f"unsupported version {frame[OFF_VERSION]}")
    want = struct.unpack_from("<H", frame, OFF_CRC)[0]
    have = crc16_modbus(bytes(frame[:OFF_CRC]))
    if want != have:
        raise ValueError(f"CRC mismatch: want {want:#06x} have {have:#06x}")

    product, hand, serial = split_device_id(frame[OFF_DEVICE_ID])
    t = HandToken(product=product, hand=hand, serial=serial)
    t.timestamp_us = struct.unpack_from("<I", frame, OFF_TIMESTAMP)[0]
    t.flex = [struct.unpack_from("<e", frame, OFF_FLEX + i * 2)[0] for i in range(5)]
    t.quat = [struct.unpack_from("<e", frame, OFF_QUAT + i * 2)[0] for i in range(4)]
    t.wrist_6dof = [struct.unpack_from("<f", frame, OFF_WRIST + i * 4)[0] for i in range(6)]
    t.vel = [struct.unpack_from("<e", frame, OFF_VEL + i * 2)[0] for i in range(3)]
    t.acc = [struct.unpack_from("<e", frame, OFF_ACC + i * 2)[0] for i in range(3)]
    t.contact = [1 if frame[OFF_CONTACT + i] else 0 for i in range(5)]
    t.force = [struct.unpack_from("<e", frame, OFF_FORCE + i * 2)[0] for i in range(5)]
    return t


# ---- 双表示层分叉 (D3) ----
def to_mano(t: HandToken) -> dict:
    """MANO Layer 结构化视图 (Unity/Unreal/XR/数字人/手语)。
    ⚠ 🟡 flex→MANO θ/β 的回归尚未实现 (models/mano/), 此处为结构视图。"""
    return {
        "representation": "mano",
        "hand": "R" if t.hand else "L",
        "flex": list(t.flex),          # 归一化关节角 (拇->小)
        "quat_wxyz": list(t.quat),     # 全局腕旋转
        "wrist_pose": list(t.wrist_6dof),
        "timestamp_us": t.timestamp_us,
        "_status": "🟡 结构视图; flex→MANO θ/β 回归待实现 (models/mano/)",
    }


def to_robot_action(t: HandToken) -> dict:
    """Robot Action Layer 结构化动作向量 (ROS2/机械臂/灵巧手/VLA/RL)。
    ⚠ 🟡 joint retarget 到目标灵巧手自由度尚未实现 (models/robot/)。"""
    return {
        "representation": "robot_action",
        "joint": list(t.flex),         # 归一化 flex 作关节角基, 待 retarget
        "wrist_6dof": list(t.wrist_6dof),
        "vel": list(t.vel),
        "acc": list(t.acc),
        "contact": list(t.contact),
        "force": list(t.force),        # 力控密集字段 (Pro), OpenX/DROID 主流缺此 → 差异化
        "timestamp_us": t.timestamp_us,
        "device": {
            "product": "Pro" if t.product else "Lite",
            "hand": "R" if t.hand else "L",
            "serial": t.serial,
        },
        "_status": "🟡 结构动作向量; joint retarget 待实现 (models/robot/)",
    }
