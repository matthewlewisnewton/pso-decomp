# Porting exceptions register

Every place where the source is not plain portable C/C++ because matching the
GameCube binary needs it: assembly, CodeWarrior-only intrinsics and pragmas,
direct hardware access, per-unit compiler overrides, and approved regressions.
A port to another platform must rewrite or neutralize every entry here.

The mechanical inventory (each line and file) is generated into
[porting-exceptions-generated.md](porting-exceptions-generated.md):

    python3 tools/list_port_exceptions.py           # regenerate
    python3 tools/list_port_exceptions.py --check   # fail if stale
    python3 tools/list_port_exceptions.py --pr N    # list exceptions added by open PR N

Reasons are cited only where a file, PR or approval records one; otherwise the
entry says *reason not recorded*.

## Summary (regenerated on this branch after merging main `f6dedd375`, 2026-11-04)

Counts below match [porting-exceptions-generated.md](porting-exceptions-generated.md)
after merging main `f6dedd375` (2026-11-04). Assembly is counted as functions;
the generated file counts each `asm` line and its `orig_asm` include separately.

| Category | Hits | Files / units |
|---|---:|---:|
| Assembly (`asm` + `orig_asm` include) | 7 functions (13 source lines) | 4 |
| MWCC intrinsics | 83 | 54 |
| Direct hardware access (GX FIFO `0xCC008000` etc.) | 71 | 13 |
| CodeWarrior pragmas (excluding push/pop) | 5,852 | 884 |
| Per-unit compiler overrides in `configure.py` | 148 | 148 |
| Approved regressions | 0 | 0 |

## Rule for assembly

If assembly is approved, a scalar C/C++ equivalent ships next to it (Matt,
2026-11-04). The asm is guarded for the GameCube/MWCC build (`#ifdef __MWERKS__`)
and the scalar version is the compiled fallback, so a port builds the C. Approved
asm always has an entry in this register.

## 1. Assembly

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/musyx/runtime/Chorus/chorus_fx.c` | `do_src1`, `do_src2` | `asm` body from `orig_asm` include under `#ifdef __MWERKS__`; scalar C in the `#else` | Vendor MusyX hand-written assembly. Matt approved keeping it on 2026-11-04 with a scalar fallback ([#316](https://github.com/matthewlewisnewton/pso-decomp/pull/316)). Evidence: [musyx-asm-fallbacks.md](evidence/musyx-asm-fallbacks.md). | Compile the scalar C fallback. |
| `src/musyx/runtime/StdReverb/reverb.c` | `DoCrossTalk`, `HandleReverb` | Same: MWCC assembly, scalar C fallback | Same approval and evidence as the chorus pair ([#316](https://github.com/matthewlewisnewton/pso-decomp/pull/316)). | Compile the scalar C fallback. |
| `src/pso/math/MatrixVector.cpp` | `vector_length`, `matrix_identity` | `asm` body from `orig_asm` include under `#ifdef __MWERKS__`; scalar C++ in the `#else` | Hand-written Gekko kernels (`frsqrte`+`fres` estimates at 0x803D8BD8; paired-single `ps_sub`/`ps_merge01`/`psq_st` at 0x803D8CA8) that CW 2.6 cannot emit. Matt approved them on 2026-11-04 with a scalar fallback ([#356](https://github.com/matthewlewisnewton/pso-decomp/pull/356)). Evidence: [matrixvector-asm-kernels-evidence.md](evidence/matrixvector-asm-kernels-evidence.md). | Compile the scalar C++ fallback. |
| `src/pso/unk/text_803E2D70.cpp` | `transform_chunk_vertices_pos_normal` | hand-written `asm void` under `#ifdef __MWERKS__` | One-time asm exception approved by Matt on 2026-11-04 ([#281](https://github.com/matthewlewisnewton/pso-decomp/pull/281)): SDK `PSMTXROMultVecArray`-style paired-single code (`psq_l`/`ps_madds*`/`psq_stu`) that MWCC cannot emit from C; other GameCube decomps keep it as asm. Evidence: [docs/evidence/paired-single-sdk-asm.md](evidence/paired-single-sdk-asm.md). | Use the scalar C++ `#else` fallback that ships with it. |

## 2. MWCC intrinsics

`__cntlzw` (55), `__frsqrte` (11), `__fabsf` (6), `__fabs` (4), `__rlwinm` (4),
`__abs` (1), `__builtin_va_info` (1); full list in the generated file. Reason: they
reproduce single PowerPC instructions the original compiled code used; no
per-site reason is recorded.

Port should: `__fabsf`/`__fabs` → `fabsf`/`fabs`; `__abs` → `abs`; `__cntlzw` →
a count-leading-zeros helper (`__builtin_clz` with a zero check, returns 32 for 0);
`__frsqrte` → `1.0 / sqrt(x)` (the Newton refinement loops around it then become
redundant but harmless); `__rlwinm` → shift/rotate + mask; `__builtin_va_info` →
standard `va_start`.

## 3. Direct hardware access

13 files write the GX write-gather pipe at `0xCC008000` directly (inlined
`GXPosition*`/`GXColor*` style emission), e.g. `TObjPlayer_803E21B8.cpp`,
`TObjLight_803DF220.cpp`, `text_803E2D70.cpp` (32 hits), `ChunkMaterialState.cpp`.
Reason not recorded per site; it mirrors the SDK's inline GX macros. Port should:
route through the GX abstraction of the target renderer (call `GXPosition3f32`
etc. or their port equivalents) instead of the fixed address.

## 4. CodeWarrior pragmas

5,852 pragmas in 884 files; per-file table in the generated file. Main kinds:
`dont_inline` 1151, `inline_depth` 1043, `fp_contract` 924, `auto_inline` 842,
`opt_common_subs` 624, `scheduling` 262, `opt_propagation` 240,
`readonly_strings` 203, `peephole` 104, `optimization_level` 88, `bool` 56,
`defer_codegen` 50, `pack` 46. Reason: reproduce the original code generation
and emission order; individual pragmas generally carry no recorded reason.

Port should: drop optimization/scheduling/inlining pragmas (they only steer
MWCC). **Keep the semantics** of `pack` (use the target's packing attribute and
check struct layout), `bool`, and `fp_contract` where float results must match
bit-for-bit (`fp_contract on` means fused multiply-add was used; a port may see
small float differences without FMA).

### Approved: `TBoss6Type2::sub_802BEC28` ([#312](https://github.com/matthewlewisnewton/pso-decomp/pull/312))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/boss/TBoss6Type2_802BE588.cpp` | `TBoss6Type2::sub_802BEC28` | one `#pragma opt_common_subs off` | Approved by Matt on 2026-11-04. Without it, common-subexpression elimination hoists the load of `lbl_805DE4E0` (0.0f) from `.text+0x6ec` to `.text+0x6c8` and renumbers the int-to-float temps, so the function is the same length and not the same bytes. Writing the ratio as `1.0f - (float)m_460 / (float)unk_45C` clamped to [0, 1] reproduces the instructions, but MWCC pools those literals as new local `.sdata2` instead of `R_PPC_EMB_SDA21` to `lbl_805DE4E4` / `lbl_805DE4E0` (the unclaimed blob `0x805DE4D8..0x805DE4F8`). `fp_contract on` is not part of this exception: removing it leaves the object identical. | Drop the pragma. The value is that clamped ratio; a port does not need MWCC's load schedule. |

### Approved: `TEF_LensFlare::render` ([#272](https://github.com/matthewlewisnewton/pso-decomp/pull/272))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/effect/TEF_LensFlare.cpp` | `TEF_LensFlare::render` | one scoped `#pragma opt_propagation off` | MWCC propagation needed for the exact receiver/descriptor cursor codegen. Approved by Matt 2026-11-04. | Drop it. |

### Approved: `TWindowKeyBoardSoft::set_open_tick` ([#219](https://github.com/matthewlewisnewton/pso-decomp/pull/219))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp` | `TWindowKeyBoardSoft::set_open_tick` @ `0x8024E7B8` (size `0x80`) | one `#pragma opt_common_subs off` | Approved by Matt on 2026-11-04 4:38 PM PT. Without it, common-subexpression elimination swaps the two SDA21 constant loads at `set_open_tick+0x3c` / `+0x44`: matched order is `lfs f2, lbl_805DCC88@sda21` then `lfs f3, lbl_805DCC84@sda21` (`0x8024E7F4` / `0x8024E7FC`); with CSE on those loads swap (`f2`/`f3` renumbered) so the function is the same length and not the same bytes. The float math (`(lbl_805DCC88 + (f32)tick) / lbl_805DCC88` then `* lbl_805DCC84`) is otherwise identical. Unit `-fp_contract on` is separate (section 5) and does not fix this load order. | Drop the pragma. A port does not need MWCC's CSE schedule for these two loads. |

## 5. Per-unit compiler overrides (`configure.py`)

148 units override the default `GAME_COMPILER = "GC/2.6"`/`cflags_pso` in
`GAME_EXCEPTIONS` or the `MIDDLEWARE` table: other MWCC versions (GC/1.2.5,
1.2.5n, 1.3, 1.3.2, 2.0) and switches (`-inline deferred`, `-fp_contract on`,
`-str reuse,readonly`, `-sdata 4`, `-opt nocse`, `-use_lmw_stmw off`, ...). The
`configure.py` comment above each entry is its recorded reason (e.g.
`pso_date.cpp`: GC/1.3.2 scheduling, see
[calendar-conversion-evidence.md](evidence/calendar-conversion-evidence.md);
`TObjTombstone.cpp`: `-fp_contract on` because two calculations fuse
multiply-adds). The generated table copies each comment; 93 entries have no
comment of their own (several share a comment with the entry above). Library
groups (SDK, runtime, TRK, MusyX, CRI, Ginja, mcFs, ntInf, avetcp, modem, ntUtl)
use their own compiler versions as recorded there.

Port should: build everything with one modern compiler. Only `-fp_contract on`
(float results) and deferred emission order (no semantic effect) need thought;
nothing else changes behaviour.

`pso/effect/TEF_LensFlare.cpp` (this change) sets `-fp_contract on` because the
recovered renderer contracts its attenuation and displacement multiply-adds
into `fnmsubs`/`fmadds`. The same unit places `lbl_80438E40` with
`__declspec(section ".rodata")` so the original `{0,0,-1}` vector symbol stays
in `.rodata`. Port: keep FMA or accept small float differences; a normal
`const` is enough for the vector.

### `pso/misc/TOMineTrap_8016F6F8.cpp`: `-inline on`, `-fp_contract on` ([#321](https://github.com/matthewlewisnewton/pso-decomp/pull/321))

Allowed by Matt on 2026-11-04: unit-wide switches in `configure.py`. No
function pragma.

| Unit | Functions | What | Why | Port should |
|---|---|---|---|---|
| `pso/misc/TOMineTrap_8016F6F8.cpp` | `TOMineTrap::run_task` (`0x8016F90C`, 952 bytes); no other function changes | unit switch `-inline on`, which expands the inline members `strike_actor(TObjChara *, TObjPlayer *)`, `strike_player(TObjChara *)` and `strike_enemy(TObjChara *, TObjPlayer *)` into mode 4's loop | The original keeps `this` in r29, the owner in r31, `i` in r30, the entity id in r28 and the actor in r27 (`mr r29, r3` at `0x8016F91C`, `mr. r27, r3` at `0x8016F9F4`, `mr r28, r3` at `0x8016FA48`). With the actor as a named local in `run_task` it is virtual r34, degree 30, and every temp it could lose a neighbour to is numbered above it. MWCC's simplify pass only pushes a node whose degree is already below 29 when the ascending sweep reaches it, so the actor is coloured before the id and gets r29 (`this` r28, id r27; 98.49%). Copy propagation cannot remove the named copy because the actor is passed to calls (`mr r3, actor`). When `get_player_data(i)` is the argument of an inline call, the actor is the inline's argument temp: it is numbered above the two room loads that the frontend CSE pass shares, so the sweep sees degree 28 and gives it the last callee-saved register. The player and enemy branches are their own inlines: nested inlines are expanded one pass later in statement order. That keeps the two `DirectAttackPayload` argument copies in the original stack slots (`0x10(r1)` for the player hit at `0x8016FB10`, `0x8(r1)` for the enemy hit at `0x8016FBE4`). With one inline for the whole body the slots swap (99.97%). With the switch, `run_task` is 100% and every other function, `.rodata` and the symbol table are byte-identical to the object built without it from the previous source (`-inline off` and `-inline on` give identical objects for that source). Without the switch, the new source keeps the three helpers out of line as weak functions and `run_task` is 33.82%. Other keywords tested: `noauto` gives the same object as `on`. `deferred` matches `run_task` but writes the functions in reverse order. `auto`, `auto,deferred` and `all` also auto-inline small members: `run_task` falls to 95.95% (76.70% with `auto,deferred`), and six other functions drop, for example `check_trigger`/`can_trigger` to 39.48% and `receive_direct_attack` to 60.34%. Precedent: [brawl `configure.py`](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) (`-inline on`), [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) per-group `-inline`, and this repo's `-inline on` units `QuestOpcodeHandlers.cpp` and `TQuestThread.cpp`. | Drop the switch. The helpers are plain inline members. |

#### `-fp_contract on`

The original text has three `fmadds` and no `fmsubs`.

| Function | Instruction | Address | Expression |
|---|---|---|---|
| `TOMineTrap::TOMineTrap` | `fmadds f2,f3,f4,f2` | `0x80170058` | damage product `lbl_805DB878 * (float)level + lbl_805DB874`, then two `fmuls` |
| `TOMine::follow_target` | `fmadds f0,f1,f0,f2` | `0x80170B9C` | `lbl_805DB884 * ((lbl_805DB888 + target_y) - held_y) + held_y` |
| `TOMine::update_float_height` | `fmadds f0,f3,f1,f0` | `0x80170D30` | `lbl_805DB884 * ((lbl_805DB888 + home_y) - height) + constant`, then `fadds` the old height |

Objdiff of the whole unit (`GC/2.6`, `-O4,s -inline on -sdata2 4`), flag on
versus flag omitted: `run_task` is byte-identical either way (100%, 952
bytes). Every other function that is exact without the flag stays exact with
it. `.rodata` (`lbl_804421F8`, 8 bytes) is exact either way. The three
functions above change, from 98.73% (1076 bytes) / 97.81% (296) / 95.60%
(172) without the flag to 99.91% (1072 bytes) / 100% / 100% with it. Those
multiply-adds compile as `fmuls`+`fadds` when `-fp_contract` is omitted and
`fmadds` when it is on.

The constructor's remaining gap is the clamp at `0x80170068`: the original is
`lfs f1, 0x358(r28); lfs f0, lbl_805DB85C; fcmpo f1, f0` then `stfs f0`, and
this source swaps `f0`/`f1`. `lbl_805DB85C` is `0.0f` in the shared `.sdata2`
pool (`0x805DB840`-`0x805DB890`), which `text_8016F1C0.cpp`, this unit and
`TOMine.cpp` all read. As an `extern const` global, its load is shared by the
frontend CSE pass, and that temp is numbered below the reload of the field, so
the reload gets `f0`. Written as the literal `0.0f`, the clamp compiles to the
original registers. The only difference left is that the relocation then
points at a pool entry of this unit's own (`.sdata2`) instead of
`lbl_805DB85C`. Matching it honestly needs that pool to belong to one unit
spanning those splits; this PR leaves the unit boundaries alone.

`follow_target` and `update_float_height` are exact on main through
function-local `fp_contract` pragmas. This PR removes those pragmas; the unit
flag is what keeps their `fmadds`.

Port should: fuse those three multiply-adds, or accept the float difference.

### `pso/effect/TEffIndirectCtrl.cpp`: GC/2.0, `-inline off,deferred`, `-fp_contract on`, `-str reuse,readonly` ([#161](https://github.com/matthewlewisnewton/pso-decomp/pull/161))

#161 merges the seven split files between `0x802A8140` and `0x802A9588`
(`TScene_802A8140`, `text_802A8210`, `TObjPlayer_802A8368`,
`TEffIndirectCtrl_802A88AC`, `TEffIndirectCtrl_802A9284`, `TEffIndirectCtrl`,
`text_802A9568`) back into the one translation unit that owns `.text`, `.rodata`,
`.data`, `.bss`, `.sdata`, `.sbss` and `.sdata2` for that range. The unit is linked
and all 34 functions and every section are byte-exact.

| Unit | Functions | What | Why | Port should |
|---|---|---|---|---|
| `pso/effect/TEffIndirectCtrl.cpp` | `TEffIndirectCtrl::run_task` (`0x802A88B0`); the whole unit is built with it | `mw_version` GC/2.0 | `run_task`'s 36-byte local array of member-function pointers interleaves its copy tail with `actor_frame_tick` (load, tail load, `clrlwi.`, table load, tail store). GC/2.6 packs the tail pair and moves the tick relocation from +0xE4 to +0xEC. GC/2.5 and GC/2.7 match 2.6. GC/2.0p1 and GC/1.3.2 drop the wave helpers. The initializer also produces the original data: a 0x24 zero template in `.rodata` (`lbl_8046FBE8`) and the 3×12-byte pool in `.data` (`eff_indirect_task_table`), as in `TItemSpecialEvent_803531FC.cpp`. Precedent: `TObjEneGyaranzo.cpp` (GC/2.0 with `-inline off,deferred`). | Build with the port compiler. |
| `pso/effect/TEffIndirectCtrl.cpp` | unit layout: `TUnk_804DDF04::~TUnk_804DDF04` (`0x802A81B8`), `TEffIndirectCtrl::~TEffIndirectCtrl` (`0x802A8AD4`), and the order of every function | unit switch `-inline off,deferred`; the source is written last-defined first | MWCC emits vtables in reverse order of their key functions. In the DOL the `TUnk_804DDF04` destructor comes first in `.text`, but its vtable (`0x804DDF04`) is before `__vt__16TEffIndirectCtrl` (`0x804DDF1C`) in `.data`. With the source in `.text` order and no deferred code generation, the `.text` order is right but the vtables come out swapped (`__vt__16TEffIndirectCtrl` at `.data+0x24`, `TUnk_804DDF04`'s at `+0x3C`). Deferred code generation emits functions last-defined first. With the definitions reversed, both `.text` and `.data` come out in the original order, and so do the float pool and the local array templates. Precedent: the per-group `-inline` settings in [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) and [brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264), and this repo's `-inline off,deferred` units (`TObjChip.cpp`, `TObjTombstone.cpp`, `TBoss6PlotFalz_802B0228.cpp`, ...). | Drop the switch. Emission order has no semantic effect. |
| `pso/effect/TEffIndirectCtrl.cpp` | `deform_indirect_texture_wave` (`0x802A8CC0`), `update_indirect_texture_wave` (`0x802A8E4C`) | unit switch `-fp_contract on`; replaces the two scoped `#pragma fp_contract on` blocks that came over from `TEffIndirectCtrl_802A88AC.cpp` | Each helper fuses the wave offset into one `fmadds f0,f2,f1,f0` (`+0xC8C`, `+0xE18`). Without contraction both drop to 98.38%: each fused multiply-add becomes an `fmuls` and an `fadds`, and `.text` grows from 5192 to 5200 bytes. No other function in the unit contracts. With the unit switch the object is identical to the one the pragmas produced. Precedent: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`), and the same pragma-to-unit-switch change for `TWindowKeyBoardSoft_8024E68C.cpp` (#219, below). | Keep fused multiply-add, or accept small float differences. |
| `pso/effect/TEffIndirectCtrl.cpp` | `load_indirect_dat`, `load_indirect_info`, `TEffIndirectCtrl__name` (data) | unit switch `-str reuse,readonly` | `"indirect.dat"`, `"indinfo.dat"` and `"TEffIndirectCtrl"` are in this unit's `.rodata` (`0x8046FBB8`, `0x8046FBC8`, `0x8046FBD4`), with `.sdata` pointers to them. Without the switch MWCC puts the three literals in `.data`: `.rodata` shrinks from 160 to 112 bytes, `.data` grows from 84 to 132, and `.data` falls to 57%. Same switch and reason as `TObjTombstone.cpp`; the same pair of switches as `TBoss6PlotFalz_802B0228.cpp`. | Drop the switch. |

### `TWindowKeyBoardSoft_8024E68C.cpp`: `-fp_contract on` ([#219](https://github.com/matthewlewisnewton/pso-decomp/pull/219))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp` | `scale_point_about_pivot`, `apply_context_transform_to_rect`, `apply_window_closing_stretch`, `clip_textured_quad`, `init_text_window_layout` | unit `configure.py` override `-fp_contract on` | These five functions emit contracted multiplies. In the matched object: `fmadds` at `scale_point_about_pivot`+0x1c/+0x40, `apply_context_transform_to_rect`+0x1c/+0x34/+0x58/+0x70, `apply_window_closing_stretch`+0x40, `clip_textured_quad`+0x80/+0xa8, and `fnmsubs` at `clip_textured_quad`+0xd0/+0xf8; `init_text_window_layout` has four `fmadds` and four `fnmsubs`. Turning contraction off drops the unit from 2156/2156 (17/17) to 1652/2156 (14/17): the transform 79.35% of 124, the stretch 92% of 100, the clip 87.86% of 280. The unit-level flag matches every section of the object that the old per-function `#pragma fp_contract on` produced (`.text` 2156 bytes, `.rodata` 8, `.mwcats.text`, `.comment`). Precedent: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`), and the same switch already used here for `PadRumble.cpp` and `CreationCamera.cpp`. | Keep fused multiply-add, or accept the float differences. |

### `-opt noprop`: `TEffIndirectCtrl.cpp` ([#291](https://github.com/matthewlewisnewton/pso-decomp/pull/291))

#291 approved this for `TEffIndirectCtrl_802A88AC.cpp`, which #161 merged into
`pso/effect/TEffIndirectCtrl.cpp`. The switch now covers the merged unit. Two
functions from the other old splits were written around propagation and now use
plain source: `free_all` (no copied loop-counter alias) and
`setup_indirect_tev_alternate` (no `u8` copy of the argument).

| Unit | Function | What | Why | Port should |
|---|---|---|---|---|
| `pso/effect/TEffIndirectCtrl.cpp` (was `TEffIndirectCtrl_802A88AC.cpp`) | `deform_indirect_texture_scroll` (`0x802A8FD8`) | unit switch `-opt noprop`, the unit-wide form of `opt_propagation off` (approved for `TEF_LensFlare::render`, #272) | The original keeps the scroll offset as a named `s16` local: `clrlwi r30,r21,26; clrlwi r29,r20,26; extsh r28,r4` at `0x802A90E4`, then `add r5,r5,r28` at `0x802A9158`. With propagation, the frontend replaces the single `off16 = offset` with a hoisted temp, which is coloured before the masks: `clrlwi r29; clrlwi r28; extsh r30`, six operands, 99.79%. Main matched only with a cancelling `off16++; off16--;`, removed here. No `-inline` or `-fp_contract` setting moves it. With the switch, the object is identical to main's in every section, relocation, and symbol. Every other function in the unit is unchanged. Precedent: per-object switches in [brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) (`-opt peephole -opt schedule` on `nt_etc_so.cpp`, L723), and this repo's `-opt nocse` / `-opt nopeephole` units. The precedent is weak: brawl uses `-opt peephole/schedule`, not `noprop`; no other decomp found using `-opt noprop`. Accepted by Matt 2026-11-04 4:34 PM PT. Evidence: [indirect-scroll-offset-propagation.md](evidence/indirect-scroll-offset-propagation.md). | Drop the switch. The source is plain C++. |

### `-opt nolifetimes,nocse,noprop,noloop`: `TMovie_80143988.cpp` ([#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167))

| Unit | Function | What | Why | Port should |
|---|---|---|---|---|
| `pso/misc/TMovie_80143988.cpp` | `pack_movie_frame` (`0x80143988`, 564 bytes; the only function in the unit) | unit switch `-opt nolifetimes,nocse,noprop,noloop` | The original keeps each named local in one register for the whole function: the packed word is built in place in `r25`, and `mr r24, r25` copies it for the second scanline before every luma insert (`0x80143A4C`, `0x80143A70`, ... eight times). The cache-touch offset is the single `li r0, 0x20` hoisted to the entry (`0x8014398C`) and reused by both `dcbt r31, r0` / `dcbt r9, r0` (`0x80143A30`, `0x80143ADC`). The pad scales are recomputed late in the entry (`slwi r5, r25, 2` ... `slwi r3, r24, 2`, `0x80143A18`–`0x80143A20`). Without `nolifetimes` the unit is 53.40% (568 bytes, `stmw r21`). Without `noprop`, `touch` is propagated as a constant: 70.50%, 596 bytes. Without `nocse` or `noloop` the shared stride and pad shifts become frontend temps coloured in the wrong order: 93.06%, 564 bytes. With the switch, `.text` (564 bytes), relocations and symbols match the target object. The source is plain C++ (no `__rlwinm`/`__rlwimi`); only `__dcbt` (section 2) remains. Precedent: Petari uses these keywords per object: [`-opt nolifetimes,nocse,noprop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L3735), [`-opt nolifetimes,noloop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L2974), [`-opt noloop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L1532). SFA uses [`-opt nolifetimes`](https://github.com/zcanann/SFA-Decomp/blob/f561e933ecc7356259bccdd6a7ce9a4462a950a0/configure.py#L1586). This repo already has `-opt noprop` and `-opt nocse` units. Evidence: [pack-movie-frame-unit-flags.md](evidence/pack-movie-frame-unit-flags.md). | Drop the switch. The source is plain C++; drop the cache touch too. |

## 6. Approved regressions

None on main.

## Pending in open PRs

Found by `tools/list_port_exceptions.py --pr N` on 2026-11-04. Add or remove the
entry when the PR merges.

| PR | Exception | Status / reason |
|---|---|---|
| [#285](https://github.com/matthewlewisnewton/pso-decomp/pull/285) | `static asm void pad_03_8042E9FC_text` via `orig_asm` include (`src/pso/unk/text_8042E9FC.cpp`) | PR body: 5-word stranded epilogue; 0/60 C probes across 20 compilers reach it. **No approval recorded and no scalar fallback**; it needs one under the rule above. |
| [#296](https://github.com/matthewlewisnewton/pso-decomp/pull/296) | `scheduling` ×5, `peephole`, `optimize_for_size` pragmas | Reason not recorded. Drop in a port. |
| [#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250) | `fp_contract` ×3 | Reason not recorded. |
| [#303](https://github.com/matthewlewisnewton/pso-decomp/pull/303), [#295](https://github.com/matthewlewisnewton/pso-decomp/pull/295), [#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289), [#225](https://github.com/matthewlewisnewton/pso-decomp/pull/225), [#222](https://github.com/matthewlewisnewton/pso-decomp/pull/222), [#215](https://github.com/matthewlewisnewton/pso-decomp/pull/215), [#128](https://github.com/matthewlewisnewton/pso-decomp/pull/128) | 1 to 4 inlining/optimization pragmas each | Reason not recorded. Drop in a port. |
| [#240](https://github.com/matthewlewisnewton/pso-decomp/pull/240) | Not scanned | Diff exceeds GitHub's 300-file limit; scan locally after it merges. |
| [#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167) | Unit switch `-opt nolifetimes,nocse,noprop,noloop` on `TMovie_80143988.cpp` (section 5); the pre-existing `__dcbt` in `pack_movie_frame` | `pack_movie_frame` matches 100% in plain C++. The earlier `__rlwinm` / `__rlwimi` calls are gone. `__dcbt` is the original data-cache touch (`dcbt r31, r0` / `dcbt r9, r0`). Port: drop the switch and the cache touch. |

The scan covers source lines only; `configure.py` overrides added by PRs show up
in the generated table once merged.
