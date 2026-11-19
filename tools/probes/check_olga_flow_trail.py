"""Exercise the Olga Flow afterimage history and its emitted quads on GPOE8P."""
import argparse
from pathlib import Path
import struct

from unicorn.ppc_const import UC_PPC_REG_FPR1, UC_PPC_REG_FPR2, UC_PPC_REG_FPR3, UC_PPC_REG_MSR

from gpoe8p_image import GameImage


PARENT = 0x81110000
OBJECT = 0x81110200
POSITIONS = 0x81110400
COLORS = 0x81110600
HEAP = 0x81111000


def verify(dol, num_points, num_frames):
    game = GameImage(dol)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)

    def read(address, fmt):
        layout = struct.Struct(">" + fmt)
        return layout.unpack(cpu.mem_read(address, layout.size))

    # Unicorn implements the scalar floating-point saves and restores in this
    # function. Skip their paired-single counterparts in the emulator copy.
    start = game.symbols["draw_trail__11TBoss6ZanzoFv"]
    for i in range(5):
        slot = 0x118 - 16 * i
        reg = (31 - i) << 21
        for base, opcode in ((0x10, 0xf0010000), (0x294, 0xe0010000)):
            address = start + base + 8 * i
            assert read(address, "I") == (opcode | reg | slot,)
            cpu.mem_write(address, struct.pack(">I", 0x60000000))

    addresses = []
    sizes = []

    def allocate(size, *_):
        address = HEAP + sum(sizes)
        sizes.append(size)
        addresses.append(address)
        cpu.mem_write(address, b"\xa5" * size)
        return address

    game.hook("__nw__7TObjectFUl", lambda size, *_: OBJECT if size == 0x2c else 0)
    game.hook("__ct__7TObjectFP7TObject", lambda obj, parent, _: obj)
    game.hook("__nwa__FUl", allocate)
    game.hook("__nw__FUl", allocate)
    assert game.call("create__11TBoss6ZanzoFP7TObjectll", PARENT, num_points, num_frames) == OBJECT
    assert game.calls["__ct__7TObjectFP7TObject"][0][:2] == (OBJECT, PARENT)
    point_count, frame_count = max(2, num_points), max(2, num_frames)
    frames, current, n, m = read(OBJECT + 0x1c, "4I")
    assert (n, m) == (point_count, frame_count)
    assert sizes == [8 * m] + [16 * n] * m + [8, 16 * n]
    assert frames == addresses[0] and current == addresses[-2]
    for i in range(m):
        assert read(frames + i * 8, "2I") == (0, addresses[i + 1])
    assert read(current, "2I") == (0, addresses[-1])

    demo = 0
    game.hook("check_demo_mode__Fv", lambda *_: demo)
    history = [None] * m
    draw_calls = []

    def draw(fan, count, flags):
        pos, col, uv, stored_count = read(fan, "4I")
        assert (count, flags, uv, stored_count) == (4, 7, 0, 4)
        draw_calls.append([(read(pos + i * 12, "3f"), read(col + i * 4, "I")[0]) for i in range(4)])

    game.hook("draw_tri_fan_3d__FP13NJS_POINT3COLlUl", draw)
    for tick in range(m + 5):
        sample = None
        if tick != 3:
            sample = [((float(tick), float(i), float(tick - i)), 0x123400c0 + (i << 8))
                      for i in range(n)]
            cpu.mem_write(POSITIONS, b"".join(struct.pack(">3f", *pos) for pos, _ in sample))
            cpu.mem_write(COLORS, b"".join(struct.pack(">I", color) for _, color in sample))
            game.call("set_effect_points__11TBoss6ZanzoFPC3VecPCUl", OBJECT, POSITIONS, COLORS)
            assert read(current, "I") == (1,)
            assert cpu.mem_read(addresses[-1], n * 16) == b"".join(
                struct.pack(">I3f", color, *pos) for pos, color in sample)
        if tick == 2:
            demo = 1
            before = cpu.mem_read(HEAP, sum(sizes))
            game.call("run_task__11TBoss6ZanzoFv", OBJECT)
            assert cpu.mem_read(HEAP, sum(sizes)) == before
            demo = 0
        game.call("run_task__11TBoss6ZanzoFv", OBJECT)
        history = [sample] + history[:-1]
        assert read(current, "I") == (0,)
        for i, entry in enumerate(history):
            assert read(frames + i * 8, "I") == (int(entry is not None),)
            if entry:
                assert cpu.mem_read(addresses[i + 1], 16 * n) == b"".join(
                    struct.pack(">I3f", color, *pos) for pos, color in entry)

        draw_calls.clear()
        game.call("draw_trail__11TBoss6ZanzoFv", OBJECT, instruction_limit=200000)
        expected = []
        # PowerPC rounds each subtraction of the per-frame fade to single precision.
        def single(value):
            return struct.unpack(">f", struct.pack(">f", value))[0]

        fades = [1.0]
        for _ in range(1, m):
            fades.append(single(fades[-1] - single(1.0 / m)))
        for i in range(1, m):
            if history[i - 1] is None or history[i] is None:
                continue
            front = fades[i - 1] if i >= 2 and history[i - 2] is not None else 0
            back = fades[i] if i + 1 < m and history[i + 1] is not None else 0
            for j in range(n - 1):
                quad = []
                for row, point, fade in ((i - 1, j, front), (i - 1, j + 1, front),
                                         (i, j + 1, back), (i, j, back)):
                    pos, color = history[row][point]
                    quad.append((pos, (color & 0xffffff00) | int(single(fade * (color & 255)))))
                expected.append(quad)
        assert draw_calls == expected, (tick, n, m)

    freed = []
    game.hook("__dla__FPv", lambda ptr, *_: freed.append(ptr))
    game.hook("__dl__FPv", lambda ptr, *_: freed.append(ptr))
    game.hook("__dt__7TObjectFv", lambda *_: None)
    game.call("__dt__11TBoss6ZanzoFv", OBJECT, 0)
    assert freed == [addresses[-1], current, *addresses[1:1 + m], frames]


def verify_triangle_fan(dol):
    game = GameImage(dol)
    cpu = game.cpu
    cpu.reg_write(UC_PPC_REG_MSR, cpu.reg_read(UC_PPC_REG_MSR) | 0x2000)
    uv_address = HEAP
    positions = [(3.0, -2.0, 0.0), (-1.5, 0.25, 17.0), (10.0, 2.0, -4.0)]
    colors = [0xff302010, 0x8123abce, 0x55555555]
    uvs = [(0, 255), (-255, 0), (510, -510)]
    cpu.mem_write(POSITIONS, b"".join(struct.pack(">3f", *pos) for pos in positions))
    cpu.mem_write(COLORS, struct.pack(">3I", *colors))
    cpu.mem_write(uv_address, b"".join(struct.pack(">2h", *uv) for uv in uvs))
    events = []

    def floating(reg):
        return struct.unpack(">d", struct.pack(">Q", cpu.reg_read(reg)))[0]

    def hook(name, capture):
        def record(a, b, c):
            events.append(capture(a, b, c))
        game.hook(name, record)

    for name in ("load_camera_view_matrix__Fv", "setup_blended_textured_draw__Fv",
                 "setup_render__10TObjPlayerFv", "load_context_texture_obj__Fv",
                 "TObjPlayer__sub_803E21DC", "setup_opaque_color_draw__Fv",
                 "TObjEneRe4Sorcerer__sub_801E3F20", "TObjPlayer__sub_803E2248"):
        hook(name, lambda *_, name=name: name)
    hook("GXBegin", lambda prim, fmt, count: ("begin", prim, fmt, count))
    hook("TObjPlayer__sub_801E3F30", lambda *_: ("point", floating(UC_PPC_REG_FPR1),
         floating(UC_PPC_REG_FPR2), floating(UC_PPC_REG_FPR3)))
    hook("TObjPlayer__sub_801E3F24", lambda color, *_: ("color", color))
    hook("fn_801E3F44", lambda *_: ("uv", floating(UC_PPC_REG_FPR1), floating(UC_PPC_REG_FPR2)))

    for count in (0, len(positions)):
        for flags, setup in ((0, "setup_opaque_color_draw__Fv"), (7, "TObjPlayer__sub_803E21DC"),
                             (8, "setup_render__10TObjPlayerFv"), (14, "setup_blended_textured_draw__Fv")):
            cpu.mem_write(OBJECT, struct.pack(">4I", POSITIONS, COLORS, uv_address if flags & 8 else 0, count))
            events.clear()
            game.call("draw_tri_fan_3d__FP13NJS_POINT3COLlUl", OBJECT, count, flags)
            expected = ["load_camera_view_matrix__Fv", setup]
            if flags & 8:
                expected.append("load_context_texture_obj__Fv")
            expected.append(("begin", 0xa0, 4, count))
            for i in range(count):
                expected.extend((("point", *positions[i]), ("color", colors[i])))
                if flags & 8:
                    expected.append(("uv", uvs[i][0] / 255.0, uvs[i][1] / 255.0))
            expected.extend(("TObjEneRe4Sorcerer__sub_801E3F20", "TObjPlayer__sub_803E2248"))
            assert events == expected, (count, flags, events)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dol", type=Path)
    dol = parser.parse_args().dol.read_bytes()
    verify_triangle_fan(dol)
    for dimensions in ((-1, 0), (3, 4), (7, 15)):
        verify(dol, *dimensions)
    print("Afterimage creation, active history, demo pause, quad colors and release passed.")
