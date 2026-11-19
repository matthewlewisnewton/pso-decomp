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


def check_ground_queries(path):
    game = GameImage(path.read_bytes())
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    base = 0x81118000
    source, separate_dest, separate_normal = (base + n for n in (16, 48, 80))
    contact, groups = base + 128, base + 192
    result = game.symbols["lbl_80500140"]
    group_buffer = game.symbols["lbl_804FFD40"]
    point = struct.pack(">3f", 12.5, -6.0, 3.25)
    normal_vector = struct.pack(">3f", 0.0, 1.0, 0.0)
    origin = struct.pack(">3f", -7.5, 8.0, 4.0)
    raised = struct.pack(">3f", -7.5, 28.0, 4.0)
    select = "select_ground_query_groups__FP9CsnVectorUl"
    triangles = "evaluate_ground_triangles__FP3VecUlPP8CsnGroup"
    game.hook(select, lambda *_: groups if has_group else 0)
    game.hook(triangles, lambda *_: int(has_triangle))
    cases = 0
    for has_group, has_triangle in ((False, False), (True, False), (True, True)):
        for mask in (0, 0x16EF, 0x80000001):
            cpu.mem_write(source, origin)
            value = game.call("csnVecterUnder", source, mask)
            assert value == (result if has_triangle else 0)
            assert game.calls[select][0][:2] == (source, mask)
            if has_group:
                assert game.calls[triangles] == [(source, mask, group_buffer)]
            else:
                assert triangles not in game.calls
            assert cpu.mem_read(source, 12) == origin
            cases += 1

    def sample(destination, mask, unused):
        assert destination == dest and mask == 0x16EF
        assert cpu.mem_read(destination, 12) == raised
        return result if hit else 0

    game.hook("csnVecterUnder", sample)
    cpu.mem_write(contact, point + normal_vector + struct.pack(">I", 0x4000))
    cpu.mem_write(result, struct.pack(">II", 1, contact))
    for function in ("adjust_point_to_ground", "adjust_point_to_ground_with_normal"):
        with_normal = function.endswith("_with_normal")
        for hit in (False, True):
            for dest in (source, separate_dest):
                for normal in (tuple(dict.fromkeys((source, dest, separate_normal))) if with_normal else (separate_normal,)):
                    state = bytearray(b"\xa5" * 112)
                    state[source - base:source - base + 12] = origin
                    cpu.mem_write(base, bytes(state))
                    assert game.call(function, source, dest, normal) == int(hit)
                    assert len(game.calls["csnVecterUnder"]) == 1
                    state[dest - base:dest - base + 12] = point if hit else (raised if dest == source else origin)
                    if hit and with_normal:
                        state[normal - base:normal - base + 12] = normal_vector
                    assert cpu.mem_read(base, len(state)) == state
                    cases += 1
    effect_game = GameImage(path.read_bytes())
    effect_cpu = effect_game.cpu
    effect_cpu.reg_write(UC_PPC_REG_MSR, effect_cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)

    def place(position, destination, unused):
        assert position == source and destination != position
        assert effect_cpu.mem_read(position, 12) == origin
        effect_cpu.mem_write(destination, point if hit else origin)
        return int(hit)

    def emit(destination, actual_id, attributes):
        assert actual_id == effect_id and attributes == 0
        assert effect_cpu.reg_read(UC_PPC_REG_6) == lifetime & 0xFFFFFFFF
        assert effect_cpu.mem_read(destination, 12) == (point if hit else origin)
        return 0

    effect_game.hook("adjust_point_to_ground", place)
    effect_game.hook("create_timed_particle_emitter", emit)
    effect_cpu.mem_write(source, origin)
    for name, effect_id in (("spawn_ground_effect", 0xE5), ("spawn_effect_at_ground", 0xE4)):
        for hit in (True, False):
            for lifetime in (-1, 0, 35, 120):
                effect_game.call(name, source, lifetime)
                assert list(effect_game.calls) == ["adjust_point_to_ground", "create_timed_particle_emitter"]
                assert effect_cpu.mem_read(source, 12) == origin
                cases += 1
    return cases


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise SystemExit(f"usage: {sys.argv[0]} PsoV3.dol [rebuilt.dol ...]")
    for image in sys.argv[1:]:
        check(Path(image))
        print(f"{image}: {check_ground_queries(Path(image))} ground query and effect cases passed")
