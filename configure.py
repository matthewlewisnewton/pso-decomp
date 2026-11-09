#!/usr/bin/env python3

###
# PSO Episode I & II Plus decompilation build configuration.
#
# Generates build.ninja, objdiff.json, and compile_commands.json
# using the standard dtk-template project generator (tools/project.py).
#
# Usage:
#   python3 configure.py                    # Generate build files
#   python3 configure.py --help             # Show all options
#
# After generating:
#   ninja                                   # Build & verify (default)
#   ninja all_source                        # Compile all source objects
#   ninja progress                          # Show progress after build
###

import argparse
import bisect
import re
import sys
from pathlib import Path
from typing import Any, Dict, List, Tuple
from tools.pso_assets import add_build_steps as add_data_build_steps

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# ===================================================================
# Units
# ===================================================================
# A unit is LINKED into the DOL from its compiled object when every function
# and data section in it matches. linked_units.txt is the only authority for
# that; tools/link_units.py maintains it.
_LINKED_UNITS_FILE = Path(__file__).resolve().parent / "config" / "GPOE8P" / "psov3" / "linked_units.txt"
_LINKED_UNITS = set()
if _LINKED_UNITS_FILE.exists():
    for _line in _LINKED_UNITS_FILE.read_text().splitlines():
        _line = _line.split("#", 1)[0].strip()
        if _line:
            _LINKED_UNITS.add(_line)


def Unit(name: str, **kwargs: Any) -> Object:
    """A translation unit (name == its splits.txt unit == its source path)."""
    return Object(name in _LINKED_UNITS, name, **kwargs)


def _units_from_splits(prefix: str) -> List[Tuple[str, int]]:
    """(unit, link address) of every `prefix` unit in splits.txt, in link order.
    A unit without .text takes the address of the last .text before it."""
    path = Path(__file__).resolve().parent / "config" / "GPOE8P" / "psov3" / "splits.txt"
    out: List[Tuple[str, int]] = []
    unit, addr = None, 0
    for line in path.read_text().splitlines() if path.exists() else []:
        if line and not line[0].isspace() and line.rstrip().endswith(":"):
            unit = line.rstrip()[:-1]
            if unit.startswith(prefix):
                out.append((unit, addr))
        m = re.match(r"\s+\.text\s+start:0x([0-9A-Fa-f]+)", line)
        if m:
            addr = int(m.group(1), 16)
            if out and out[-1][0] == unit:
                out[-1] = (unit, addr)
    return out


def _switch(flags: List[str], *switches: str, drop: Tuple[str, ...] = ()) -> List[str]:
    """`flags` with each of `switches` replacing the switch of the same name
    in place (`-O4,p` replaces `-O4,s`, `-inline auto` replaces `-inline off`)
    or appended, and the switches named in `drop` removed."""
    def name(f: str) -> str:
        return "-O" if re.match(r"-O\d", f) else f.split(" ", 1)[0]
    new = {name(s): s for s in switches}
    out = [new.pop(name(f), f) for f in flags if name(f) not in drop]
    return out + list(new.values())


# ===================================================================
# Version Configuration
# ===================================================================
DEFAULT_VERSION = "GPOE8P"
VERSIONS = [
    "GPOE8P",  # USA v1.02
]

# ===================================================================
# Argument Parsing
# ===================================================================
parser = argparse.ArgumentParser(
    description="PSO Episode I & II Plus decompilation build configuration"
)
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    nargs="?",
    help="script mode (default: configure)",
)
parser.add_argument(
    "-v", "--version",
    choices=VERSIONS,
    type=str,
    default=DEFAULT_VERSION,
    help=f"game version (default: {DEFAULT_VERSION})",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="build non-matching objects",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate linker map file(s)",
)
parser.add_argument(
    "--dtk",
    metavar="BINARY",
    type=Path,
    help="path to decomp-toolkit binary",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY",
    type=Path,
    help="path to objdiff-cli binary",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers directory",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine",
    )
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
parser.add_argument(
    "--target",
    choices=["psov3", "main"],
    default="psov3",
    help="DOL target to build (default: psov3 — the game binary)",
)
parser.add_argument("--data-replacements", type=Path, metavar="DIR",
                    help="verify exact runtime data replacements under DIR/files/")
args = parser.parse_args()

# ===================================================================
# Project Configuration
# ===================================================================
config = ProjectConfig()
config.version = str(args.version)
config.build_dir = args.build_dir
config.non_matching = args.non_matching
config.generate_map = args.map
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.compilers_path = args.compilers
config.binutils_path = args.binutils
config.sjiswrap_path = getattr(args, "sjiswrap", None)
config.progress = args.progress
if not is_windows():
    config.wrapper = getattr(args, "wrapper", None)

# Don't build asm overrides unless --non-matching
if not config.non_matching:
    config.asm_dir = None

# PSO uses `.rel` as a generic data-file extension. `movie.rel` is the only
# verified standard CodeWarrior REL module; it needs its own non-empty module
# config, symbols, splits, and source plan before enabling REL linking.
config.build_rels = False

# ---------------------------------------------------------------------------
# Tool versions (from dtk-template)
# ---------------------------------------------------------------------------
config.binutils_tag = "2.42-1"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.4"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# ---------------------------------------------------------------------------
# Paths — select DOL target
# ---------------------------------------------------------------------------
if args.target == "psov3":
    config.config_path = Path("config") / config.version / "psov3" / "config.yml"
    config.check_sha_path = Path("config") / config.version / "psov3" / "build.sha1"
else:
    config.config_path = Path("config") / config.version / "config.yml"
    config.check_sha_path = Path("config") / config.version / "build.sha1"
    # Separate output namespace (build/GPOE8P-main/) so switching targets
    # doesn't clobber the psov3 target's split/obj artifacts.
    config.version = f"{config.version}-main"

# ---------------------------------------------------------------------------
# Assembler flags
# ---------------------------------------------------------------------------
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
]

# ---------------------------------------------------------------------------
# Linker flags
# ---------------------------------------------------------------------------
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.map:
    config.ldflags.append("-mapunused")

# Linker version
config.linker_version = "GC/2.6"

# Shift JIS: disabled by default, enable per-object if needed
config.shift_jis = False

# ===================================================================
# Compiler Flags
# ===================================================================

# Base flags: CodeWarrior for GameCube, matching the original build.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-RTTI off",
    "-O4,p",
    "-inline auto",
    "-str reuse",
    "-maxerrors 1",
    "-nosyspath",
    # Generated headers only — per-group include paths live in
    # cflags_pso / cflags_dolphin / cflags_runtime below so SDK code
    # never sees game headers and vice versa.
    f"-i build/{config.version}/include",
]

# PSO main game code flags. Do not pass the base speed/auto-inline flags and
# then override them later; some MWCC/wibo rebuild paths are fragile with
# duplicate optimization switches. SDK/runtime still use cflags_base unchanged.
cflags_pso_base = [
    f for f in cflags_base
    if f not in ("-O4,p", "-inline auto")
]

cflags_pso = [
    *cflags_pso_base,
    "-i include",
    "-i src",
    "-i libs/dolphin/include",
    "-i libs/dolphin/include/dolphin",  # for "types.h" includes inside SDK headers
    "-char signed",
    "-use_lmw_stmw on",
    # Sega's game code was built optimize-for-SIZE, not speed: the original
    # uses stmw/lmw register save-restore and un-scheduled prologues. -O4,s
    # reproduces that (verified via locate_func masked scan, 2026-06-12).
    # SDK/runtime keep their own optimization via cflags_dolphin/runtime.
    "-O4,s",
    # ...and with auto-inlining OFF. The original keeps operator new/delete,
    # accessors, etc. as real out-of-line calls. Switching -inline auto ->
    # off took locate_func FOUND counts from 6->83 (TProtocol), 2->16
    # (TMainTask), 5->13 (TObject) with zero regressions (2026-06-12).
    "-inline off",
    # Target game code loads f64 constant-pool literals (int->float magic
    # 0x4330000080000000 etc.) from .rodata via lis/@l, never @sda21 — the
    # target's lfd@sda21 sites are all SDK-side units. mwcc's default
    # -sdata2 8 parks compiler-generated doubles in .sdata2, which is the
    # documented "magic-const @sda21-vs-rodata" stuck cluster. 4 keeps f32
    # consts (lfs @sda21, everywhere in target game code) small-data while
    # pushing 8-byte pool literals to .rodata like the original.
    "-sdata2 4",
]

# Dolphin SDK library flags
cflags_dolphin = [
    *cflags_base,
    "-i libs/dolphin/include",
    "-i libs/dolphin/include/dolphin",  # for "types.h" includes inside SDK headers
    "-i libs/dolphin/include/libc",
    "-i libs/dolphin/src",
    "-char unsigned",
    "-fp_contract off",
    "-D__GEKKO__",  # donor SDK sources guard asm functions with this
]

# odemuexi2/DebuggerDriver.o was built with deferred inlining: functions are
# emitted in reverse definition order and its small EXI helpers inline away.
cflags_dolphin_deferred = [
    "-inline auto,deferred" if f == "-inline auto" else f for f in cflags_dolphin
]

# Recovered SDK owners omit unused inline-math constants from their pools.
cflags_dolphin_recovered = [
    f for f in cflags_dolphin if f != "-char unsigned"
] + ["-char signed", "-DPSO_SDK_COMPACT_MATH"]

# PowerPC EABI runtime flags
cflags_runtime = [
    *cflags_base,
    # ac-donor MSL_C/ + libc/ headers first (the MSL sources are ac's
    # no-threads build, which is what PSO's MSL actually is). Do NOT mix in
    # libs/dolphin/include/libc here — its stdio.h shares the same include
    # guard but lacks the FILE typedef.
    "-i libs/PowerPC_EABI_Support/include",
    "-i libs/PowerPC_EABI_Support/include/libc",
    "-i libs/dolphin/include/dolphin",
    "-i libs/PowerPC_EABI_Support/Runtime/Inc",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-char signed",
    "-inline deferred,auto",
]

# MetroTRK debugger flags (mirrors ac-decomp's TRK_MINNOW_DOLPHIN lib)
cflags_trk = [
    *cflags_base,
    "-i libs",
    "-i libs/dolphin/include",
    "-i libs/dolphin/include/dolphin",
    "-i libs/dolphin/include/libc",
    "-i libs/PowerPC_EABI_Support/Runtime/Inc",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-sdata 0",
    "-sdata2 0",
    "-inline auto,deferred",
    "-rostr",
    "-char signed",
    "-use_lmw_stmw on",
]

# Native donor profiles verified against complete owning translation units.
cflags_native_recovered = [
    '-nodefaults',
    '-proc gekko',
    '-align powerpc',
    '-enum int',
    '-fp hardware',
    '-Cpp_exceptions off',
    '-RTTI off',
    '-O4,p',
    '-str reuse,pool,readonly',
    '-maxerrors 1',
    '-nosyspath',
    '-fp_contract off',
    '-char signed',
    '-use_lmw_stmw on',
    '-common off',
    '-D__GEKKO__',
    '-DDEBUG=0',
    '-DNDEBUG',
    '-DVERSION=0',
    '-inline deferred,auto',
    '-i libs',
    '-i libs/PowerPC_EABI_Support/include',
    '-i libs/PowerPC_EABI_Support/include/libc',
    '-i libs/dolphin/include',
    '-i libs/dolphin/include/dolphin',
    f'-i build/{config.version}/include',
]
cflags_native_recovered_auto = [
    "-inline auto" if f == "-inline deferred,auto" else f
    for f in cflags_native_recovered
]

# ===================================================================
# Compilers
# ===================================================================
# Sega built the game code with CodeWarrior GC/2.6 (GC/2.5 and GC/2.7 give the
# same code here; GC/2.0 does not) and cflags_pso. Everything else in
# PsoV3.dol is libraries linked prebuilt, each built with its own compiler:
# the Dolphin SDK, runtime and MetroTRK (helpers below), MusyX and the
# middleware after it (MIDDLEWARE).
GAME_COMPILER = "GC/2.6"

# Game files whose objects came from another compiler (an incremental build
# keeps an object until its source changes) or with other switches. Every
# entry is here because a function or data section matches only this way.
GAME_EXCEPTIONS: Dict[str, Dict[str, Any]] = {
    # Upstream #208: fused scale/corner arithmetic; deferred emission puts the
    # compiler vtable before the constructor switch table; class string is rodata.
    "pso/misc/TPlayerFootStamp.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on", "-inline off,deferred", "-str reuse,readonly")},
    # TObjPlayer__sub_8015434C fuses offset*sin+pos (fmadds at 0x80154408)
    # and offset*cos+pos (fmadds at 0x8015442C). The same flag leaves every
    # other function in this unit unchanged, including resolve_actor_sphere_contact's
    # (x*x)+(z*z) as fmuls+fadds. resolve_player_box_contact's fmadds at
    # 0x8015532C and 0x8015533C already come from that function's pragma.
    # Precedent: dtk-template's GC/Wii base flags use -fp_contract on
    # (https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209).
    "pso/player/TObjPlayer_801542CC.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on")},
    # Upstream #183: the Falz plot table TU is built with deferred inlining
    # (its state actions come out in reverse table order).
    "pso/boss/TBoss6PlotFalz_802B0228.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/boss/TBoss6EmptyWarp_802B0E2C.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly")},
    # Calendar month/day stores retain GC/1.3.2 scheduling; see calendar-conversion-evidence.md.
    "pso/misc/pso_date.cpp": {"mw_version": "GC/1.3.2"},
    # Curve and xz helpers fuse multiply-adds. The whole TU stays byte-exact
    # with -fp_contract on (all three tunnel units), so the flag belongs on the
    # unit rather than as per-function pragmas left over from the split units.
    "pso/boss/TObjBoss2Tunnel_8003B138.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on")},
    # Deferred, with definitions in reverse address order: the ctor's
    # function-local static and guard precede run_task's table guard in .sbss,
    # as in the original (docs/porting-exceptions.md section 5).
    # .sbss starts at 0x805D696C and .sdata2 at 0x805DECCC, both only 4-aligned.
    # mwld takes alignment from the CodeWarrior comment record, which GC/2.6
    # writes as 8, so the pool and every later sda21 offset shift by 4.
    # cw_align rewrites that record after compile. -sdata 4 does not.
    "pso/boss/TObjBoss2Tunnel_802F2070.cpp": {
        "cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on"),
        "cw_align": ".sbss=4 .sdata2=4",
    },
    # Upstream #185's -inline off,deferred, -pool off and -sdata 4; each is
    # needed (docs/porting-exceptions.md section 5).
    "pso/boss/TObjBoss2Tunnel.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-pool off", "-sdata 4", "-fp_contract on")},
    "pso/boss/TBoss4DarkFalz_8004C93C.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")},
    # Reverse definitions with deferred generation: the weak copies of TOTrap's
    # inline slots are generated first, so their 1.0/0.0 head .sdata2 as in the
    # original pool, and clamp_params_and_init inlines its clamp helpers.
    "pso/misc/TOTrapSeabed01.cpp": {"cflags": _switch(cflags_pso, "-inline deferred")},
    # Reverse definitions with deferred generation: the native TOTrapAncient02R
    # vtable is emitted before the switch table that follows it in .data, and
    # the .sdata2 pool keeps its original order. Unit -fp_contract on replaces
    # the per-function pragmas: the constructors, calc_trap_count and the R
    # vfunc_81 fuse multiply-adds.
    "pso/misc/TOTrapAncient02.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-fp_contract on")},
    # GC/2.0, like TOExplosiveMachine: play_sounds loads the three debris
    # positions before storing them (GC/2.6 interleaves them: 91.09%).
    # Reverse definitions and deferred generation place the native trap vtable
    # before its switch tables while preserving the original function order.
    # Contracted FP keeps the constructor and render exact (98.86% and
    # 97.66% without it). -opt nolifetimes keeps render exact (99.42% without
    # it). -pooldata=off keeps play_sounds' copy prologue (94.54% without it);
    # read-only strings keep the .rodata/.data/.sdata layout.
    "pso/misc/TOTrapAncient01.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on", "-str reuse,readonly", "-pooldata=off", "-opt nolifetimes")},
    # Upstream #180: the 8-byte zanzo motion list stays in .data (-sdata 4).
    "pso/object/TObjDFDemo1.cpp": {"cflags": _switch(cflags_pso, "-sdata 4")},
    "pso/enemy/TObjEneBalClawBody_80090178.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sdata 4")},
    # Deferred generation preserves the flower vtable before its dispatch table.
    "pso/enemy/TObjEneRe2Flower_800C3E14.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/enemy/TObjEneEpsilonGuard_8035F5C8.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # Gee native tables require deferred generation and reverse definitions.
    "pso/enemy/TObjEneMe1Gee.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # Upstream #190 commit 9c4e9ea1d: TObjEneDubchik is written from its last
    # function back. -inline off,deferred emits that order (the vtable lands
    # before the switch tables). -str reuse,readonly keeps the motion-name
    # pool in .rodata. These are upstream's own flags for this unit.
    "pso/enemy/TObjEneDubchik.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    # Native private header sections preserve initializer and helper emission order.
    "pso/enemy/TObjEnePanarms.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sdata 4", "-sym on")},
    "pso/enemy/TObjEneDelDepth.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TObjChip: render's colour template sits after draw_chips' in .rodata
    # while render comes first in .text, so the source runs backwards.
    "pso/object/TObjChip.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # One unit, written last-defined first: the vtable and the late helpers
    # precede the early ones in .text. -fp_contract on: draw_name_labels'
    # half-width nudge and the drop placement fuse multiply-adds.
    # -str reuse,readonly: the literals live in this unit's .rodata.
    "pso/object/TObjTombstone.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on", "-str reuse,readonly")},
    # Vol Opt scenery is one TU. Deferred emission puts TOBoss4Rock::run_task
    # first; -sdata 4 keeps the 8-byte motion-name array in .data.
    "pso/misc/TOBoss4.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on", "-str reuse,readonly", "-sdata 4", "-inline deferred")},
    # Dark Falz rocks are one TU, written last-defined first. -fp_contract on
    # fuses the fall and spin multiply-adds.
    "pso/boss/TBoss6Rock.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on", "-str reuse,readonly", "-inline off,deferred")},
    # GC/2.0: compiler-expanded struct copies take 2.0's registers.
    # The ending item handler table keeps 2.0's store/load scheduling for its
    # zero-initialized local member-function-pointer array.
    "pso/item/TItemSpecialEvent_803531FC.cpp": {
        "mw_version": "GC/2.0",
        # The split names the compiler's anonymous PMF initializer image at
        # 0x804F10C0; the source-built object references its first 12-byte
        # entry label. Map the target entry name to the object's image label.
        "symbol_mappings": {"@12": "...data.0"},
    },
    # GC/2.0: run_task's 36-byte PMF array initializer interleaves its copy
    # tail with actor_frame_tick (load, tail load, clrlwi., table load, tail
    # store). GC/2.5, 2.6 and 2.7 pack the tail pair and move the tick
    # relocation from +0xE4 to +0xEC; GC/2.0p1 and GC/1.3.2 drop the wave
    # helpers.
    # -inline off,deferred: the vtables come out in reverse order of their
    # key functions, and .data has TUnk_804DDF04's vtable before this
    # class's while TUnk_804DDF04's destructor comes first in .text.
    # -opt noprop: deform_indirect_texture_scroll keeps its s16 scroll offset
    # as a named local (extsh r28, after the coordinate masks in r30/r29).
    # With copy propagation the frontend replaces it with a hoisted temporary
    # that the allocator colours first (r30).
    # -fp_contract on: both texture-wave helpers fuse the wave offset into an
    # fmadds.
    # -str reuse,readonly: the two file names and the class name are in this
    # unit's .rodata. See docs/porting-exceptions.md section 5.
    "pso/effect/TEffIndirectCtrl.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred", "-opt noprop", "-fp_contract on", "-str reuse,readonly")},
    # pack_movie_frame: the original keeps every named local in one register
    # (no lifetime splitting), recomputes its pad and stride shifts instead of
    # sharing them, and leaves invariant hoisting to the backend. See
    # docs/porting-exceptions.md section 5.
    "pso/misc/TMovie_80143988.cpp": {"cflags": _switch(cflags_pso, "-opt nolifetimes,nocse,noprop,noloop")},
    "pso/boss/Boss5GryphonBehavior.cpp": {"mw_version": "GC/2.0"},
    "pso/enemy/TObjEneGyaranzo.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/misc/TOExplosiveMachine.cpp": {"mw_version": "GC/2.0"},
    "pso/enemy/TObjEneSlimeTailAttack.cpp": {"mw_version": "GC/2.0"},
    # -inline off,deferred: the real TBoss8Dragon constructor addresses
    # __vt__12TBoss8Dragon as addi r0, r31, 2348 from the .data anchor.
    # Plain -inline off emits lis/addi of the vtable symbol and the ctor
    # grows 0x554 -> 0x558. Deferred also emits the compiler vtable at
    # .data+0x92C, where the hand table was. Other functions are unchanged.
    # See docs/porting-exceptions.md section 5.
    "pso/boss/TBoss8Dragon.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred")},
    # GC/1.3.2: the container files 0x8018807C-0x8018D900, the CRC-32 pair
    # (`xoris/xori 0xFFFF`; 2.x always emits `li -1; xor`), and five others.
    # TObjCamera: 1.3.2 copies CameraSoundEvent member by member unscheduled.
    "pso/object/TObjCamera.cpp": {"mw_version": "GC/1.3.2"},
    "pso/object/TObjComputer.cpp": {"mw_version": "GC/1.3.2"},
    "pso/item/TObjContainerJung.cpp": {"mw_version": "GC/1.3.2"},
    # The two below also schedule the by-value DirectAttackPayload read of
    # their receive_direct_attack overrides only the way 1.3.2 does.
    "pso/item/TObjContainerItem.cpp": {"mw_version": "GC/1.3.2"},
    "pso/misc/TContainerAncient01.cpp": {"mw_version": "GC/1.3.2"},
    "pso/ui/TAdSinglePlyChrSelectGC_801FBF54.cpp": {"mw_version": "GC/1.3.2"},
    # Four depth/UV multiply-adds contract, so -fp_contract on replaces the old
    # per-function pragmas. -inline on inlines only clamped_active_slot
    # and mark_grid_cell_occupied; -inline auto also inlines eight unmarked
    # calls and those functions stop matching. See
    # docs/evidence/chr-select-slot-clamp-inline.md.
    # The eight compiler-pool globals before this unit's owned 0.53 / 1/256
    # literals are defined by TAdMultiPlyChrSelectGC_literals.s, including the
    # 16.0 conversion constant shared with the separately split ctor.
    "pso/ui/TAdChrSelPlyPlateGC.cpp": {
        "cflags": _switch(cflags_pso, "-fp_contract on", "-inline on"),
        "symbol_mappings": {
            "@102": "lbl_805DE580",
            "@175": "TAdMultiPlyChrSelectGC__data_805DE584",
        },
    },
    "pso/misc/TQuestVmDownLoadServer.cpp": {"mw_version": "GC/1.3.2", "cflags": _switch(cflags_pso, "-inline deferred")},
    "pso/misc/TCameraCtrl.cpp": {"mw_version": "GC/1.3.2"},
    "pso/misc/TKeyBoardControl_8025EC04.cpp": {"mw_version": "GC/1.3.2"},
    "pso/menu/TAdMultiOkGC.cpp": {"mw_version": "GC/1.3.2"},
    "pso/misc/TLobby_802A5120.cpp": {"mw_version": "GC/1.3.2"},
    "pso/unk/text_8032B318.cpp": {"mw_version": "GC/1.3.2"},
    # The player hit-vector snapshot needs 1.3.2's const-input copy scheduling.
    "pso/player/TObjPlayer_802D5B78.cpp": {"mw_version": "GC/1.3.2"},
    # GC/1.3: the compiler-generated TMenuList<> copy constructor.
    "pso/misc/TRegister.cpp": {"mw_version": "GC/1.3"},
    "pso/misc/TPlyGuildCardTag_801E0284.cpp": {"mw_version": "GC/1.3"},
    "pso/misc/TPlyStartGame.cpp": {"mw_version": "GC/1.3"},
    "pso/misc/TWindowShortListCtrl_8026E7DC.cpp": {"mw_version": "GC/1.3"},
    # Deferred inlining: functions come out in reverse source order and the
    # vtables before the switch tables in .data.
    "pso/misc/TMedicalCenterSequence.cpp": {"cflags": _switch(cflags_pso, "-inline deferred")},
    # Row-header copy is a 16-byte struct assignment. -inline off outlines it;
    # noauto,level=1 inlines that helper only. The rest of the unit stays out of line.
    "pso/misc/TWindowMainMenu_802AD538.cpp": {"cflags": _switch(cflags_pso, "-inline noauto,level=1")},
    # Soft-keyboard clip, scale, and layout fuse multiply-adds into fmadds/fnmsubs
    # (scale_point_about_pivot, apply_context_transform_to_rect,
    # apply_window_closing_stretch, clip_textured_quad, init_text_window_layout).
    # Unit -fp_contract on replaces the per-function pragmas. Precedent:
    # https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209
    "pso/misc/TWindowKeyBoardSoft_8024E68C.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on")},
    # Upstream #190: this file is written in reverse so deferred codegen emits
    # address order, and the readonly string pool places the constants.
    "pso/misc/TNpcPlayer.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    # get_technique_caster_flags' unsigned bias is lbl_8044D078, which TTecCtrl
    # loads from this split. MWCC emits the bias as a local pool object; the
    # post-process names that object as the split's global. Source cannot do
    # it without a second pool copy (docs/evidence/conversion-pool-constants.md).
    "pso/misc/TTecCtrl_8022C444.cpp": {"post_object": "tools/name_pool_symbols.py"},
    "pso/boss/TBoss7LaserLight.cpp": {"cflags": _switch(cflags_pso, "-inline deferred")},
    # Position jitter and the tentacle curve contract mul-add to fmadds, so
    # this unit is built with -fp_contract on. -inline off,deferred emits
    # functions and vtables in reverse source order: the Needle vtable then
    # the Tentacle vtable, with .text still in address order.
    # GC/2.0: the Needle constructor's const emitter copy. Before 2.5 a const
    # local whose address escapes stays out of the worst-case alias set, so
    # the three word loads of pos batch ahead of the stores; 2.6 interleaves.
    "pso/boss/TBoss7TentacleNeedle.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on")},
    # Photon bullet run_task contracts a mul-add. Deferred emission puts the
    # compiler vtables in address order while the definitions stay bottom-to-top.
    "pso/boss/TBoss7PhotonBullet_802EF26C.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on")},
    "pso/enemy/TObjEnemyCustom.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-pool off", "-str reuse,readonly")},
    "pso/boss/TBoss3VoloptCore.cpp": {"cflags": _switch(cflags_pso, "-inline deferred")},
    # -inline deferred is byte-identical to noauto,deferred,level=1 here
    # (.text/.data/.rodata/.sdata2 and relocs). off,deferred changes 21
    # functions (copy_transform, sub_802B96C0); noauto alone changes 86;
    # -fp_contract off changes 71 (draw_part_motions, sub_802B626C). The
    # multiply-adds are fmadds. dtk-template uses -inline auto and
    # -fp_contract on; Melee, TP, TWW and Pikmin 2 contract globally.
    "pso/boss/TBoss6Type1.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-fp_contract on")},
    "pso/boss/TBoss3VoloptP01.cpp": {"cflags": _switch(cflags_pso, "-inline deferred")},
    # Delbiter uses deferred code generation: reverse source definitions put
    # native vtables before the switch tables and functions in address order.
    "pso/enemy/TObjEneNanoDrago.cpp": {"cflags": _switch(cflags_pso, "-inline deferred")},
    "pso/enemy/TObjEneMe1GiGue.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/enemy/TObjEneRe7Berura.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/enemy/TObjEneDellBiter.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/enemy/TObjEneDellBiterEffects.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # The Vol Opt fade tasks: deferred like the units above, but nothing is
    # inlined (the inline TUnk_804999E8 destructor and TObject::queue_destruction
    # stay calls).
    "pso/boss/TUnk_804848A0.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TItem.cpp is written from its last function back (deferred code
    # generation; the data keeps source order) and built with GC/2.0, like the
    # struct-copy units above.
    # The dragonfly base and its cave subclass: vtables come out subclass first.
    "pso/misc/TOBiwaMushi.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on", "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODragonflyCave01.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on", "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODragonflyMachine01.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on", "-str reuse,readonly", "-sdata 4")},
    # Three fmadds in the original text, and nowhere else in the unit:
    # __ct__10TOMineTrap at 0x80170058 (fmadds f2,f3,f4,f2), follow_target at
    # 0x80170B9C (fmadds f0,f1,f0,f2), update_float_height at 0x80170D30
    # (fmadds f0,f3,f1,f0). No fmsubs. The same expressions are fmuls+fadds
    # when the flag is omitted. Every other function, including run_task, is
    # byte-identical with the flag off, and .rodata stays exact.
    # -inline on expands run_task's mode-4 strike helpers (strike_actor,
    # strike_player, strike_enemy); no other function in the unit changes.
    # See docs/porting-exceptions.md.
    "pso/misc/TOMineTrap_8016F6F8.cpp": {"cflags": _switch(cflags_pso, "-inline on", "-fp_contract on")},
    "pso/item/TItem.cpp": {"mw_version": "GC/2.0", "cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TItemProArmor.cpp, TItemProShield.cpp and TItemProUnit.cpp are written
    # from their last function back (deferred code generation, which also puts
    # each vtable before the switch tables).
    "pso/item/TItemProArmor.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TODoorBase's vtable precedes its switch tables: deferred, written from
    # its last function back.
    "pso/misc/TODoorBase.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TOBarrierEnergy01's vtable precedes its switch table too.
    "pso/misc/TOBarrierEnergy01.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/misc/TODoorAncient01.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/misc/TODoorAncient03.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/misc/TODoorAncient04.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    # TItemProArmorParticle.cpp is written from its last function back too:
    # its data (class names, particle table) keeps source order.
    "pso/item/TItemProArmorParticle.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TObjTreeLobby.cpp is written from its last function back: the
    # quest-damage task it also defines has its vtable after the tree's.
    "pso/object/TObjTreeLobby.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TObjLobbyMain.cpp too: its vtable precedes its two switch tables.
    "pso/object/TObjLobbyMain.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TObjParticleLobby.cpp too: its vtable precedes setup_emitter's jump table.
    "pso/object/TObjParticleLobby.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TItemMag's vtable precedes its switch tables: deferred, and written from
    # its last function back.
    "pso/item/TItemMag.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    # The bridges' vtables come out in the reverse of their .text order:
    # deferred, written from the unit's last function back. -fp_contract on:
    # TObjHashiBase::update_object_view_visibility fuses its multiply-adds.
    # The seabed tanks' vtables come out in .text order: deferred, written
    # from the unit's last function back.
    "pso/object/TObjSuisoChip.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/object/TObjHashi.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly", "-fp_contract on")},
    "pso/item/TItemProUnit.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TOKey's vtable precedes its switch tables: deferred, and written from
    # its last function back.
    "pso/misc/TOKey.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/item/TItemProShield.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TItemEffNeedle.cpp too: its three vtables come out in the order only
    # deferred code generation gives (TItemEffNeedlePos keeps the implicit
    # destructor).
    "pso/item/TItemEffNeedle.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # TItemEquipBase.cpp keeps its class-name string in .rodata.
    "pso/item/TItemEquipBase.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly")},
    # TObjMotion.cpp keeps its class-name string in .rodata too.
    "pso/object/TObjMotion.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly")},
    # The ancient doors keep their class-name and file-name strings in .rodata
    # (07's 8-byte model/motion name lists stay in .data: -sdata 4).
    "pso/misc/TODoorAncient05.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly")},
    "pso/misc/TODoorAncient06.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly")},
    "pso/misc/TODoorAncient07.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    # 08 and 09 are written from their last function back (each vtable
    # precedes its switch tables: deferred code generation).
    "pso/misc/TODoorAncient08.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorAncient09.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorCave01.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorCave02.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorMachine01.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorMachine02.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorVoShip.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorVS2Door01.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    "pso/misc/TODoorCave03.cpp": {"cflags": _switch(cflags_pso, "-str reuse,readonly", "-sdata 4")},
    # TItemMagSub.cpp (with TItemMagGrowEff) keeps its strings in .rodata, and
    # is written from its last function back: deferred code generation puts
    # the TItemMagGrowEff vtable first.
    "pso/item/TItemMagSub.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    # TItemObject's vtable precedes its switch table: deferred, and written
    # from its last function back.
    "pso/item/TItemObject.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # Two tool classes built the same way: the material's vtable precedes its
    # switch table, and TUnk_8049FED0's TU emits its helper task's vtable first.
    "pso/item/TUnk_8049FBC0.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/item/TUnk_8049FED0.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/item/TUnk_804F0D34.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # Vol Opt's second form also keeps eight-byte tables in .data, a six-byte
    # one in .bss and four-byte pointers in .sbss; its .rodata initializers run
    # from the last function back and its vtable precedes the switch tables.
    "pso/boss/TBoss3VoloptP02.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sdata 4")},
    # The character appearance tables keep eight-byte descriptors in .data
    # but four-byte pointer lists in .sdata.
    "pso/misc/CharacterAppearanceTables.cpp": {"cflags": _switch(cflags_pso, "-sdata 4")},
    # Vol Opt keeps its six-byte P01 order in .bss and its four-byte globals
    # in .sbss; its vtable precedes the switch tables in .data.
    "pso/boss/TBoss3Volopt.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sdata 4")},
    # Vol Opt's monitors keep their eight-byte texture lists in .data but the
    # four-byte class-name pointer in .sdata.
    "pso/boss/TBoss3VoloptMonitor.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sdata 4")},
    # The cave and machine map objects keep their eight-byte model-name lists
    # in .data but the four-byte motion-name list and class-name pointer in
    # .sdata.
    "pso/misc/TOAirconCave01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOAirconCave02.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOCapsuleAncient01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOFenceAncient01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOFenceAncient02.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOFenceAncient03.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOFenceAncient04.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOCapsuleMachine01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOCapsuleLabo.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOComputerMachine01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOMonumentAncient01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOCakeshopCave01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOHangerMachine01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOMonitorMachine01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TORainbowCave01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-fp_contract on")},
    "pso/misc/TORevlightCave01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOSignCave01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOSignCave02.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOSignCave03.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    "pso/misc/TOMonumentAncient02.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-fp_contract on")},
    # Kurage addresses each debug label on its own (no shared .rodata base).
    "pso/misc/TOKurage.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-fp_contract on", "-pool off")},
    "pso/misc/TOHealGeneral.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    # The key subclasses address each of their texture names on its own
    # (no shared .rodata base): built -pool off.
    "pso/misc/TOKeyAncient01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    "pso/misc/TOKeyAncient02.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    "pso/misc/TOKeyAncient03.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    "pso/misc/TOKeyCave01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    "pso/misc/TOKeyCol.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    "pso/misc/TOKeyMachine01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    # The sensor base: its vtable comes before its jump tables.
    "pso/misc/TOSensor.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/misc/TOSwitchItem.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-str reuse,readonly")},
    "pso/misc/TOSensorAncient01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    "pso/misc/TOSensorGeneral01.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly", "-pool off")},
    # Unlike the other keys it addresses its descriptors off one .data base.
    "pso/misc/TOKeyGenericSw.cpp": {"cflags": _switch(cflags_pso, "-sdata 4", "-str reuse,readonly")},
    # __vt__25TObjCityMainWarpChallenge at 0x804B6188 precedes
    # jumptable_804B61DC. Whole unit matches with nothing inlined.
    # See docs/evidence/city-main-warp-challenge-vtable.md.
    "pso/object/TObjCityMainWarpChallenge.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # Quest-collision deleting destructors share a TU. Deferred generation
    # emits the last definition first, which is the only order that puts each
    # vtable before the next class's (TObjQuestColA then TObjQuestCol;
    # TObjQuestColApcINW then TObjQuestColApcIN).
    "pso/object/TObjQuestColA_80196FE4.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    "pso/object/TObjQuestColApcINW_80196EDC.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred")},
    # The character creation camera: deferred with nothing inlined, and its
    # multiply-adds contracted into fmadds.
    "pso/camera/CreationCamera.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on")},
    # The lens-flare renderer contracts its attenuation and displacement
    # multiply-adds into fnmsubs/fmadds; the whole unit stays byte-exact with
    # -fp_contract on, so that is this translation unit's setting.
    "pso/effect/TEF_LensFlare.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on")},
    # The pad rumble and Ninja helper code contract multiply-adds into fmadds/fnmsubs.
    "pso/system/PadRumble.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on")},
    "pso/system/NinjaUtil.cpp": {"cflags": _switch(cflags_pso, "-fp_contract on")},
    # The render helpers (0x801412D0-0x80142770): GC/1.3.2, one .sdata2 pool. Only
    # 1.3.2 keeps approach_vector_fixed_distance's early-out copy unscheduled.
    "pso/render/render_util.cpp": {"mw_version": "GC/1.3.2", "cflags": [*_switch(cflags_pso, "-fp_contract on"), "-DPSO_SDK_COMPACT_MATH"]},
    "pso/render/render_util_head.cpp": {"mw_version": "GC/1.3.2", "cflags": [*_switch(cflags_pso, "-fp_contract on"), "-DPSO_SDK_COMPACT_MATH"]},
    "pso/render/render_util_tail.cpp": {"mw_version": "GC/1.3.2", "cflags": [*_switch(cflags_pso, "-fp_contract on"), "-DPSO_SDK_COMPACT_MATH"]},
    # Metrowerks' GCN_Mem_Alloc.c (runtime library code at -O4,p); belongs
    # in the runtime lib under its own name.
    "pso/unk/text_8039739C.cpp": {"cflags": _switch(cflags_pso, "-O4,p")},
    "pso/quest/QuestOpcodeHandlers.cpp": {"cflags": _switch(cflags_pso, "-inline on")},
    "pso/quest/TQuestThread.cpp": {"cflags": _switch(cflags_pso, "-inline on")},
    # init_from_id_lists (0x8002058C, size 0x30C) inlines its model and motion
    # walks. Default -inline off outlines them. auto leaves .text at 62.53% and
    # .data at 0%; auto,deferred leaves .text at 52.51% and .data at 0%. deferred
    # matched the previous extern "C" body, but on this C++ function it emits the
    # function at .text+0 instead of .text+0x1630, so the linked DOL does not
    # match. -inline on keeps the bytes and that order. Precedent: dtk-template
    # -inline auto https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203
    # and Brawl -inline on https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264
    "pso/misc/TLobby_8001EF5C.cpp": {"cflags": _switch(cflags_pso, "-inline on")},
    # TQuestListVM: deferred emission puts __vt__12TQuestListVM ahead of the
    # run_task switch table (written from the last function back). -pool off
    # keeps each title and window size its own reloc, and -str reuse,readonly
    # matches the read-only string objects. The whole unit stays byte-exact.
    # Precedent: dtk-template configure.py unit cflags, and this tree's
    # TObjBoss2Tunnel / TBoss6EmptyWarp unit flags.
    "pso/quest/TQuestListVM.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-pool off", "-str reuse,readonly")},
    # Status gauge: contracting the unit makes `0.299f * depth + ctx->depth`
    # the fmadds at 0x80257118. The bar multiply stays a separate fmuls
    # because the 7.5 scale is applied to the sum before the tick subtract.
    "pso/misc/TWindowSubStatusDisp_80256B94.cpp": {"cflags": _switch(cflags_pso, "-inline off,deferred", "-fp_contract on")},
    # Inventory walks read TItemList children through the class-body accessors
    # TItemList::link_down / link_next (typed_down in TObjPlayer_801D4CB8, whose
    # receiver is TObjPlayer). -inline noauto folds each call to the lwz of
    # m_down (+0x14) or m_next (+0xC). -inline off leaves a bl and grows the
    # walks (TObjPlayer__sub_801D4368 0x248 -> 0x278, and the TItemList walks
    # by the same 8-byte call). -inline auto also inlines the unmarked
    # TObjPlayer__sub_801D4730 into sort_by_key, so it is not this unit's flag.
    # With noauto the whole object matches -inline off on the old cast spelling,
    # including every function that does not call the accessor. Precedent:
    # https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203
    # (-inline auto) and TWindowMainMenu_802AD538.cpp (-inline noauto,level=1).
    "pso/unk/text_801D40D4.cpp": {"cflags": _switch(cflags_pso, "-inline noauto")},
    # Same -inline noauto as text_801D40D4.cpp. count_owned_items and the other
    # TItemList walks stay the lwz of m_down / m_next; -inline off grows each.
    "pso/player/TObjPlayer_801D5220.cpp": {"cflags": _switch(cflags_pso, "-inline noauto")},
    # Same -inline noauto as text_801D40D4.cpp. The three TPlyItem walks
    # (reduce_owner_matched_items, reduce_child_item_amounts,
    # collect_owner_fields_recursive) stay byte-identical to the cast spelling.
    "pso/player/TPlyItem.cpp": {"cflags": _switch(cflags_pso, "-inline noauto")},
    # Same -inline noauto as text_801D40D4.cpp. destroy_subobjects_recursive's
    # child load stays lwz r31,20(r3) and the sibling step stays lwz r31,12(r31).
    "pso/player/TObjPlayer_801D4CB8.cpp": {"cflags": _switch(cflags_pso, "-inline noauto")},
}

# MusyX (Factor 5). Its objects carry extab/extabindex for every non-leaf
# function: C++ with exceptions on reproduces them and leaves .text alone.
cflags_musyx = _switch(cflags_pso, "-O4,p", "-sdata2 8", "-Cpp_exceptions on") + ["-lang=c++"]

# Prebuilt middleware after MusyX, in link order: (name, first .text address,
# compiler, flags, per-file exceptions). Each library runs to the next one's
# address; the version strings in their data name them.
cflags_middleware = _switch(cflags_pso, "-O4,p", drop=("-sdata2",))
MIDDLEWARE: List[Tuple[str, int, str, List[str], Dict[str, Dict[str, Any]]]] = [
    # MusyX's synthesizer core, then its service, hardware and effect files.
    ("musyx", 0x803A3858, "GC/1.2.5n", _switch(cflags_musyx, "-opt nocse"), {}),
    ("musyx_hw", 0x803BAC70, "GC/1.2.5n", _switch(cflags_musyx, "-inline auto"), {}),
    # CRI ADX, LSC, SJ, MFCI and GCRNA ("Build:Jun 13 2002").
    ("cri", 0x803BFE50, "GC/2.6", cflags_middleware, {}),
    # Sega's Ginja model library.
    ("ginja", 0x803D6538, "GC/2.6", _switch(cflags_middleware, "-O3,p", "-opt nopeephole"), {
        # render_debug_text (0x803D85D8) saves r25-r31 with bl _savegpr_25 /
        # _restgpr_25, and its glyph quads are the inlined SDK FIFO writers
        # (sth/stw to 0xCC008000), not calls. -inline on inlines only functions
        # marked inline, so queue_debug_text stays a call from debug_printf_at.
        # The matrix helpers in text_803D8910.cpp match under the ginja defaults.
        "pso/unk/text_803D8098.cpp": {
            "cflags": _switch(cflags_middleware, "-O3,p", "-opt nopeephole", "-use_lmw_stmw off", "-inline on"),
        },
    }),
    # mcFsGc ("Ver 1.10.00 Build:Sep 17 2002") with ACCESS's file transfer.
    ("mcfs", 0x803E5668, "GC/1.2.5", cflags_middleware, {
        # Epilogue order (mtlr before the restores) only 1.2.5n produces.
        "pso/misc/TKeyBoardControl_803F0C50.cpp": {"mw_version": "GC/1.2.5n"},
        "pso/unk/text_803F1804.cpp": {"mw_version": "GC/1.2.5n"},
    }),
    # ntInf ("Ver 1.17.00 Build:Jul 9 2002").
    ("ntinf", 0x803F3CF4, "GC/2.6", cflags_middleware, {
        "pso/unk/text_803F4D84.cpp": {"cflags": _switch(cflags_middleware, "-O2", "-use_lmw_stmw off")},
    }),
    # ACCESS AVE-TCP ("avetcp.a Ver.1.16.1 Oct 23 2002"); its PPP files were
    # built without common subexpression elimination.
    ("avetcp", 0x803F7678, "GC/1.2.5n", cflags_middleware, {
        "pso/protocol/NetworkRuntime.cpp": {"cflags": _switch(cflags_middleware, "-opt nocse")},
        "pso/misc/TLobby_803FAEA0.cpp": {"cflags": _switch(cflags_middleware, "-opt nocse")},
        "pso/misc/TLobby_803FC178.cpp": {"cflags": _switch(cflags_middleware, "-opt nocse")},
        "pso/misc/TLobby_804048E8.cpp": {"cflags": _switch(cflags_middleware, "-opt nocse")},
        "pso/misc/TLobby_804050DC.cpp": {"cflags": _switch(cflags_middleware, "-opt nocse")},
    }),
    # The modem driver (AT command strings).
    ("modem", 0x8042BF48, "GC/1.2.5", cflags_middleware, {}),
    # ntUtl ("Ver 1.16.00 Build:Jul 8 2002"); the SDK's EXI library follows.
    ("ntutl", 0x8042E8C4, "GC/2.6", cflags_middleware, {}),
]
MIDDLEWARE_END = 0x8042F13C


def _game_and_middleware_libs() -> List[Dict[str, Any]]:
    """The pso/ and musyx/ units of splits.txt, sorted into the game lib and
    the MIDDLEWARE libs by link address."""
    game: List[Object] = []
    libs = [{"lib": name, "mw_version": mw, "cflags": flags, "progress_category": "game",
             "src_dir": "src", "objects": []} for name, _, mw, flags, _ in MIDDLEWARE]
    starts = [start for _, start, _, _, _ in MIDDLEWARE]
    for unit, addr in _units_from_splits(""):
        if not unit.startswith(("pso/", "musyx/")):
            continue
        i = bisect.bisect_right(starts, addr) - 1
        if i < 0 or addr >= MIDDLEWARE_END:
            game.append(Unit(unit, **GAME_EXCEPTIONS.get(unit, {})))
        else:
            libs[i]["objects"].append(Unit(unit, **MIDDLEWARE[i][4].get(unit, {})))
    return [{"lib": "psov3_main", "mw_version": GAME_COMPILER, "cflags": cflags_pso,
             "progress_category": "game", "src_dir": "src", "objects": game}, *libs]


# ===================================================================
# Library Helpers
# ===================================================================

def DolphinLib(lib_name: str, objects: list) -> dict:
    """A Dolphin SDK library. Use when registering SDK source files.

    The SDK copy embedded in PsoV3.dol was prebuilt by Nintendo with an
    older compiler than the game code — GC/1.2.5n matches its prologue
    style (mflr/stw/stwu, 0x8 frames), same as tp's DolphinLib.
    """
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_dolphin,
        "progress_category": "sdk",
        "src_dir": "libs/dolphin/src",
        "objects": objects,
    }


_msl_math = {
    "mw_version": "GC/1.3",
    "cflags": [f for f in cflags_runtime if f != "-fp_contract off"] + ["-fp_contract on"],
}


def RuntimeLib(lib_name: str, objects: list) -> dict:
    """A PowerPC EABI runtime / MSL library.

    Unit names carry the full PowerPC_EABI_Support/... prefix (same as tp)
    so src_dir is libs/.
    """
    return {
        "lib": lib_name,
        "mw_version": "GC/2.6",
        "cflags": cflags_runtime,
        "progress_category": "runtime",
        "src_dir": "libs",
        "objects": objects,
    }


def TRKLib(lib_name: str, objects: list) -> dict:
    """MetroTRK debugger library. Prebuilt like the SDK; flags and compiler
    follow ac-decomp's TRK_MINNOW_DOLPHIN settings (GC/1.3)."""
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3",
        "cflags": cflags_trk,
        "progress_category": "sdk",
        "src_dir": "libs",
        "objects": objects,
    }


# ===================================================================
# Library / Object Definitions
# ===================================================================
# PsoV3.dol's pso/ and musyx/ units are read from splits.txt: adding a unit
# there is all it takes. The SDK and runtime units are listed by hand so
# each one's compiler settings sit next to it.
# ===================================================================

if args.target == "psov3":
    config.reconfig_deps = [
        Path("config/GPOE8P/psov3/splits.txt"),
        _LINKED_UNITS_FILE.relative_to(Path(__file__).resolve().parent),
    ]
    config.libs = [
        *_game_and_middleware_libs(),
        DolphinLib(
            "recovered_sdk",
            [
                Unit('mtx/mtx.c', mw_version="GC/1.2.5"),
                Unit('mtx/mtxvec.c'),
                Unit('mtx/mtx44.c'),
                Unit('mtx/vec.c'),
                Unit('dvd/dvdlow.c'),
                Unit('dvd/dvdfs.c'),
                Unit('dvd/dvd.c'),
                Unit('vi/vi.c'),
                Unit('pad/Pad.c'),
                Unit('ai/ai.c'),
                Unit('ar/ar.c'),
                Unit('ar/arq.c'),
                Unit('dsp/dsp.c'),
                Unit('dsp/dsp_debug.c'),
                Unit('dsp/dsp_task.c'),
                Unit('card/CARDBios.c'),
                Unit('card/CARDUnlock.c'),
                Unit('card/CARDRdwr.c'),
                Unit('card/CARDBlock.c'),
                Unit('card/CARDDir.c'),
                Unit('card/CARDCheck.c'),
                Unit('card/CARDMount.c'),
                Unit('card/CARDFormat.c'),
                Unit('card/CARDOpen.c'),
                Unit('card/CARDCreate.c'),
                Unit('card/CARDRead.c'),
                Unit('card/CARDWrite.c'),
                Unit('card/CARDDelete.c'),
                Unit('card/CARDStat.c'),
                Unit('card/CARDRename.c'),
                Unit('card/CARDStatEx.c'),
                Unit('card/CARDNet.c'),
                Unit('gx/GXFifo.c'),
                Unit('gx/GXAttr.c'),
                Unit('gx/GXMisc.c'),
                Unit('gx/GXFrameBuf.c'),
                Unit('gx/GXLight.c'),
                Unit('gx/GXTexture.c'),
                Unit('gx/GXBump.c'),
                Unit('gx/GXPixel.c'),
                Unit("gx/GXStubs.c"),
                Unit('gx/GXDisplayList.c'),
                Unit('gx/GXTransform.c'),
                Unit('gx/GXPerf.c'),
            ],
        ) | {"cflags": cflags_dolphin_recovered},
        TRKLib(
            "recovered_trk",
            [
                Unit("TRK_MINNOW_DOLPHIN/support.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("TRK_MINNOW_DOLPHIN/notify.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("TRK_MINNOW_DOLPHIN/flush_cache.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("TRK_MINNOW_DOLPHIN/mem_TRK.c",
                            mw_version="GC/1.3", cflags=cflags_native_recovered_auto),
                Unit("TRK_MINNOW_DOLPHIN/targimpl.c",
                            mw_version="GC/2.6", cflags=[*cflags_native_recovered, "-sdata 0", "-sdata2 0"]),
                Unit("TRK_MINNOW_DOLPHIN/targsupp.s", src_dir=f"build/{config.version}/orig_asm"),
                Unit("TRK_MINNOW_DOLPHIN/exception.s", src_dir=f"build/{config.version}/orig_asm"),
                Unit("TRK_MINNOW_DOLPHIN/dolphin_trk.c",
                            mw_version="GC/2.6", cflags=[*cflags_native_recovered, "-sdata 0", "-sdata2 0"]),
            ],
        ),
        RuntimeLib(
            "recovered_runtime",
            [
                Unit("PowerPC_EABI_Support/Runtime/Src/CPlusLibPPC.cp",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/Runtime/Src/NMWException.cp",
                            mw_version="GC/1.3", cflags=cflags_native_recovered_auto),
                Unit("PowerPC_EABI_Support/Runtime/Src/ptmf.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/Runtime/Src/runtime.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/Runtime/Src/__init_cpp_exceptions.cpp",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/Runtime/Src/__mem.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/ansi_fp.c",
                            mw_version="GC/1.3", cflags=cflags_native_recovered_auto),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/printf.c",
                            mw_version="GC/1.3", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/rand.c",
                            mw_version="GC/1.3", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/scanf.c",
                            mw_version="GC/1.3", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/string.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/strtoul.c",
                            mw_version="GC/1.3", cflags=cflags_native_recovered),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/uart_console_io.c",
                            mw_version="GC/2.6", cflags=cflags_native_recovered),
            ],
        ),
        DolphinLib(
            "recovered_sdk_io",
            [
                Unit('exi/EXIBios.c', cflags=cflags_dolphin_recovered),
                Unit('exi/EXIUart.c', cflags=cflags_dolphin_recovered),
                Unit('si/SIBios.c', cflags=cflags_dolphin_recovered),
            ],
        ),
        # ------------------------------------------------------------------
        # PsoV3.dol — Embedded Dolphin SDK copy.
        # TU boundaries transferred from the tp and ac-decomp donors
        # (see WORKFLOW.md's SDK/runtime loop). Source lives in libs/dolphin/src.
        # ------------------------------------------------------------------
        DolphinLib(
            "base",
            [
                Unit("base/PPCArch.c"),
            ],
        ),
        DolphinLib(
            "db",
            [
                Unit("db/db.c"),
            ],
        ),
        DolphinLib(
            "os",
            [
                Unit("os/OS.c", cflags=cflags_dolphin_recovered),
                Unit("os/__start.c", cflags=cflags_dolphin_recovered),
                Unit("os/OSAlarm.c"),
                Unit("os/OSAlloc.c"),
                Unit("os/OSArena.c"),
                Unit("os/OSAudioSystem.c"),
                Unit("os/OSCache.c", cflags=cflags_dolphin_recovered),
                Unit("os/OSContext.c", cflags=cflags_dolphin_recovered),
                Unit("os/OSError.c", cflags=cflags_dolphin_recovered),
                Unit("os/OSFont.c"),
                Unit("os/OSInterrupt.c"),
                Unit("os/OSLink.c"),
                Unit("os/OSMessage.c"),
                Unit("os/OSMemory.c"),
                Unit("os/OSMutex.c"),
                Unit("os/OSReboot.c"),
                Unit("os/OSReset.c"),
                Unit("os/OSResetSW.c"),
                Unit("os/OSRtc.c"),
                Unit("os/OSSync.c"),
                Unit("os/OSThread.c"),
                Unit("os/OSTime.c"),
                Unit("os/__ppc_eabi_init.cpp"),
            ],
        ),
        DolphinLib(
            "dvd",
            [
                Unit("dvd/dvdqueue.c"),
                Unit("dvd/dvderror.c"),
                Unit("dvd/fstload.c", cflags=cflags_dolphin_recovered),
            ],
        ),
        DolphinLib(
            "gx",
            [
                Unit("gx/GXInit.c", cflags=cflags_dolphin_recovered),
                Unit("gx/GXGeometry.c"),
                Unit("gx/GXTev.c"),
            ],
        ),
        DolphinLib(
            "si",
            [
                Unit("si/SISamplingRate.c", cflags=cflags_dolphin_recovered),
            ],
        ),
        DolphinLib(
            "gba",
            [
                Unit("gba/GBA.c", cflags=cflags_dolphin_recovered),
                Unit("gba/GBAGetProcessStatus.c", cflags=cflags_dolphin_recovered),
                Unit("gba/GBAJoyBoot.c", cflags=cflags_dolphin_recovered),
                Unit("gba/GBARead.c", cflags=cflags_dolphin_recovered),
                Unit("gba/GBAWrite.c", cflags=cflags_dolphin_recovered),
                Unit("gba/GBAXfer.c", cflags=cflags_dolphin_recovered),
                Unit("gba/GBAKey.c", cflags=cflags_dolphin_recovered),
            ],
        ),
        DolphinLib(
            "amcstubs",
            [
                Unit("amcstubs/AmcExi2Stubs.c"),
            ],
        ),
        DolphinLib(
            "odenotstub",
            [
                Unit("odenotstub/odenotstub.c"),
            ],
        ),
        DolphinLib(
            "odemuexi2",
            [
                Unit("odemuexi2/DebuggerDriver.c", cflags=cflags_dolphin_deferred),
            ],
        ),
        TRKLib(
            "TRK_MINNOW_DOLPHIN",
            [
                Unit("TRK_MINNOW_DOLPHIN/mainloop.c"),
                Unit("TRK_MINNOW_DOLPHIN/nubevent.c"),
                Unit("TRK_MINNOW_DOLPHIN/nubinit.c"),
                Unit("TRK_MINNOW_DOLPHIN/msg.c"),
                Unit("TRK_MINNOW_DOLPHIN/msgbuf.c"),
                Unit("TRK_MINNOW_DOLPHIN/msghndlr.c"),
                Unit("TRK_MINNOW_DOLPHIN/serpoll.c"),
                Unit("TRK_MINNOW_DOLPHIN/usr_put.c"),
                Unit("TRK_MINNOW_DOLPHIN/dispatch.c"),
                Unit("TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
                Unit("TRK_MINNOW_DOLPHIN/main_TRK.c"),
                Unit("TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
                Unit("TRK_MINNOW_DOLPHIN/targcont.c"),
                Unit("TRK_MINNOW_DOLPHIN/target_options.c"),
                Unit("TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
                Unit("TRK_MINNOW_DOLPHIN/mslsupp.c"),
            ],
        ),
        RuntimeLib(
            "Runtime.PPCEABI.H",
            [
                Unit("PowerPC_EABI_Support/Runtime/Src/__va_arg.c"),
                Unit("PowerPC_EABI_Support/Runtime/Src/global_destructor_chain.c"),
                Unit("PowerPC_EABI_Support/Runtime/Src/Gecko_ExceptionPPC.cp"),
            ],
        ),
        RuntimeLib(
            "MSL_C.PPCEABI.bare.H",
            [
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/abort_exit.c"),
                # alloc.c: only GC/1.3 emits `li -5; and` where 1.3.2+ use rlwinm
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/alloc.c",
                            mw_version="GC/1.3"),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/ansi_files.c"),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/buffer_io.c"),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/direct_io.c"),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/FILE_POS.c"),
                # file_io.c: PSO's fclose keeps a real `bl fflush`; -inline
                # deferred would fold fflush into fclose and reverse the
                # emission order, so this TU drops deferred. extra_cflags
                # can't cancel it (deferred is sticky), hence full override.
                Unit(
                    "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/file_io.c",
                    cflags=[
                        f if f != "-inline deferred,auto" else "-inline auto"
                        for f in cflags_runtime
                    ],
                ),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/mbstring.c"),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/mem.c"),
                # mem_funcs.c: PSO's copy of these MSL copy loops predates the
                # rest of the runtime — GC/2.6 emits clrlwi/pipelined loops
                # that can't match; GC/1.3 with plain -inline auto is exact.
                Unit(
                    "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/mem_funcs.c",
                    mw_version="GC/1.3",
                    cflags=[
                        f if f != "-inline deferred,auto" else "-inline auto"
                        for f in cflags_runtime
                    ],
                ),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/misc_io.c"),
                Unit("PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/wchar_io.c"),
            ],
        ),
        # fdlibm + math_ppc (0x8039F7FC-0x803A2DA0): built like ac's MSL math,
        # GC/1.3 with -fp_contract on (e_acos needs fmadd; s_atan only matches
        # under 1.3).
        RuntimeLib(
            "MSL_C.PPCEABI.bare.H.math",
            [
                *[Unit(f"PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/{_n}.c", **_msl_math)
                  for _n in (
                      "e_acos", "e_asin", "e_atan2", "e_log", "e_pow", "e_rem_pio2", "k_cos",
                      "k_rem_pio2", "k_sin", "k_tan", "s_atan", "s_ceil", "s_copysign", "s_cos",
                      "s_floor", "s_frexp", "s_ldexp", "s_modf", "s_nextafter", "s_sin", "s_tan",
                      "w_acos", "w_asin", "w_atan2", "w_log", "w_pow",
                  )],
                Unit("PowerPC_EABI_Support/MSL/MSL_C/PPC_EABI/Src/math_ppc.c", **_msl_math),
            ],
        ),
    ]
else:
    # main.dol has no recovered source; it is rebuilt from its original objects.
    config.libs = []

# ===================================================================
# Progress Categories
# ===================================================================
config.progress_categories = [
    ProgressCategory("game", "PSO Game Code"),
    ProgressCategory("sdk", "Dolphin SDK"),
    ProgressCategory("runtime", "Runtime"),
]

# Progress report arguments for objdiff-cli
config.progress_report_args = [
    "--config", "functionRelocDiffs=data_value",
]

# ===================================================================
# Functions written in assembly
# ===================================================================
# The SDK, runtime and MetroTRK functions that Nintendo and Metrowerks wrote in
# assembly are not in this repository. Their bodies are
#     #include "orig_asm/<unit>/<function>.inc"
# and tools/orig_asm.py writes those files from decomp-toolkit's disassembly of
# the original, before anything is compiled. Units that are assembly from start
# to finish are written whole.
_ORIG_ASM = re.compile(r'^#include "(orig_asm/[\w/]+\.inc)"$', re.M)
_ORIG_ASM_UNITS = ["TRK_MINNOW_DOLPHIN/targsupp.s", "TRK_MINNOW_DOLPHIN/exception.s"]


def add_orig_asm_steps(config: ProjectConfig) -> None:
    outputs: List[Path] = []
    for root in (Path("libs"), Path("src")):
        for path in sorted(root.rglob("*")):
            if path.suffix in (".c", ".cp", ".cpp") and path.is_file():
                text = path.read_text(encoding="utf-8", errors="replace")
                if "orig_asm/" in text:
                    outputs += [config.out_path() / "include" / inc for inc in _ORIG_ASM.findall(text)]
    outputs += [config.out_path() / "orig_asm" / unit for unit in _ORIG_ASM_UNITS]
    symbols = Path("config") / config.version / "psov3" / "symbols.txt"
    config.custom_build_rules = [*(config.custom_build_rules or []), {
        "name": "orig_asm",
        "command": "$python tools/orig_asm.py $asm_dir $symbols $out",
        "description": "ORIG_ASM $asm_dir",
    }]
    steps = config.custom_build_steps = dict(config.custom_build_steps or {})
    steps["pre-compile"] = [*steps.get("pre-compile", []), {
        "outputs": outputs,
        "rule": "orig_asm",
        "inputs": [config.out_path() / "config.json"],
        "implicit": [Path("tools/orig_asm.py"), symbols],
        "variables": {"asm_dir": str(config.out_path() / "asm"), "symbols": str(symbols)},
    }]
    config.reconfig_deps = [*(config.reconfig_deps or []), Path("tools/orig_asm.py")]


# ===================================================================
# Main Dispatch
# ===================================================================
if args.target == "psov3":
    add_orig_asm_steps(config)
    # A disc image in orig/GPOE8P/, or the disc extracted there by wit.
    _disc_root = Path("orig/GPOE8P/P-GPOE")
    if not _disc_root.is_dir():
        _disc_root = Path("orig/GPOE8P")
    add_data_build_steps(config, _disc_root, replacements=args.data_replacements)

if args.mode == "configure":
    generate_build(config)
elif args.mode == "progress":
    calculate_progress(config)
else:
    sys.exit(f"Unknown mode: {args.mode}")
