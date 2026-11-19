"""Check the contact pool, native result constructors and radial hit selection."""
from pathlib import Path
import struct
import sys

from unicorn.ppc_const import UC_PPC_REG_6, UC_PPC_REG_MSR
from gpoe8p_image import GameImage


def check(path):
    game = GameImage(path.read_bytes())
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    pool = game.symbols["lbl_804FF9C0"]
    basic = game.symbols["lbl_80500140"]
    radial = game.symbols["csn_query_map_object"]
    group_buffer = game.symbols["lbl_804FFD40"]
    guard = b"\xa5" * 8

    cpu.mem_write(pool - 8, guard + b"\xa5" * (0x380 + 0x400 + 8 + 16) + guard)
    game.call("__sinit_CsnQuery_cpp")
    assert cpu.mem_read(pool - 8, 8) == guard
    assert cpu.mem_read(pool, 32 * 0x1C) == bytes(32 * 0x1C)
    assert cpu.mem_read(group_buffer, 0x400) == b"\xa5" * 0x400
    assert cpu.mem_read(basic, 8) == struct.pack(">II", 0, pool)
    assert cpu.mem_read(radial, 16) == struct.pack(">IIif", 0, pool, -1, -1.0)
    assert cpu.mem_read(radial + 16, 8) == guard

    local = 0x81110020
    for name, payload in [
        ("__ct__10CsnContactFv", bytes(0x1C)),
        ("__ct__6CsnHitFv", struct.pack(">II", 0, pool)),
        ("__ct__13WallRayResultFv", struct.pack(">IIif", 0, pool, -1, -1.0)),
    ]:
        cpu.mem_write(local - 8, guard + b"\xcc" * len(payload) + guard)
        assert game.call(name, local) == local
        assert cpu.mem_read(local - 8, 16 + len(payload)) == guard + payload + guard

    query = 0x81110100
    rays = 0x81110200
    origin = (7.0, 2.0, -1.0)
    mask = 0x1181
    depths = []
    visited = []

    def hit_segment(start, end, actual_mask):
        index = len(visited)
        contact = cpu.reg_read(UC_PPC_REG_6)
        assert contact == pool + index * 0x1C
        assert start == query + 12 and actual_mask == mask
        endpoint = struct.unpack(">3f", cpu.mem_read(end, 12))
        assert endpoint == (origin[0] + index, origin[1], origin[2])
        visited.append(contact)
        depth = depths[index]
        if depth is None:
            return 0
        cpu.mem_write(contact, struct.pack(">6fI", endpoint[0] - depth, endpoint[1], endpoint[2],
                                           1.0, 0.0, 0.0, mask))
        return 1

    game.hook("query_wall_segment__FP3VecP3VecUlP10CsnContact", hit_segment)
    for values, expected in [
        ([], -1), ([None, None, None], -1), ([0.0], 0),
        ([2.0, 5.0, 5.0], 1), ([None, -6.0, 3.0], 1),
        ([None] * 31 + [8.0], 31),
    ]:
        depths = values
        visited.clear()
        cpu.mem_write(query, struct.pack(">ifI3fI", len(values), 32.0, mask, *origin, rays))
        for i in range(len(values)):
            cpu.mem_write(rays + 12 * i, struct.pack(">3f", float(i), 0.0, 0.0))
        got = game.call("select_deepest_wall_ray", query, radial)
        flag, contacts, index, depth = struct.unpack(">IIif", cpu.mem_read(radial, 16))
        assert len(visited) == len(values)
        assert (got, flag, contacts, index) == (int(expected >= 0), int(expected >= 0), pool, expected)
        assert depth == (-1.0 if expected < 0 else abs(values[expected]))
    print(f"{path}: startup, 32 contacts, three constructors, six radial selection cases passed")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise SystemExit(f"usage: {sys.argv[0]} PsoV3.dol [rebuilt.dol ...]")
    for image in sys.argv[1:]:
        check(Path(image))
