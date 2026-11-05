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

## Summary (regenerated on this branch after merging main `1e1b3cddc`, 2026-11-04)

Counts below match [porting-exceptions-generated.md](porting-exceptions-generated.md)
after merging main `1e1b3cddc` (2026-11-04). Assembly is counted as functions;
the generated file counts each `asm` line and its `orig_asm` include separately.

| Category | Hits | Files / units |
|---|---:|---:|
| Assembly (`asm` + `orig_asm` include) | 7 functions (13 source lines) | 4 |
| MWCC intrinsics | 83 | 54 |
| Direct hardware access (GX FIFO `0xCC008000` etc.) | 71 | 13 |
| CodeWarrior pragmas (excluding push/pop) | 5,836 | 879 |
| Per-unit compiler overrides in `configure.py` | 156 | 156 |
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

5,836 pragmas in 879 files; per-file table in the generated file. Main kinds:
`dont_inline` 1151, `inline_depth` 1043, `fp_contract` 915, `auto_inline` 842,
`opt_common_subs` 619, `scheduling` 260, `opt_propagation` 241,
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

### Approved: `TObjBoss2Tunnel__sub_8007D1D0` ([#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/boss/TObjBoss2Tunnel.cpp` | `TObjBoss2Tunnel__sub_8007D1D0` (`0x8007D1D0`, size `0x658`) | one `#pragma opt_propagation off` | Approved by Matt 2026-11-04 4:38 PM PT (per-function `opt_propagation off` for #290). It replaces upstream #185's unit switch `-opt nopropagation`; every other function in the unit is 100% without it. The original tests `lbz r3, boss2_tunnel_state_flag` / `cmplwi r3, 0` and computes the copy-filter flag (`clrlwi r3, r3, 31; xori r28, r3, 1`) before `bl TObjBoss2Tunnel__sub_8036EF44`. With propagation on, the load stays live in r30 across the calls, `clrlwi`/`xori` move after `TObjBoss2Tunnel__sub_8036EF44` and `set_display_copy_filter__Fi`, and each early exit branches to a shorter epilogue (`b 0x1210` instead of `b 0x1224`): 92.25%. | Drop the pragma. The flag is `!(boss2_tunnel_state_flag & 1)`; a port does not need MWCC's propagation schedule. |

### Approved: `TUnk_804E4B3C::update_spawn_timer` ([#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/boss/TObjBoss2Tunnel_802F2070.cpp` | `TUnk_804E4B3C::update_spawn_timer` (`0x802F2664`) | one `#pragma opt_common_subs off` | Approved by Matt 2026-11-04 4:38 PM PT. The original prologue is `lfs f0, lbl_805DECB4` then `lfs f2, 0x58(r3)` / `lfs f1, 0x5c(r3)` / `fadds f1, f2, f1` (threshold in f0, then `m_58` and `m_5c`). Without the pragma, common-subexpression elimination sinks that load: the same 44 instructions come out with the threshold in f2 and the add in f1/f0 (8 words differ) whether the threshold is a local, a compound assignment, or the direct compare. A unit `-opt nocse` keeps the timer and breaks `spawn_segment_row_a`, `spawn_segment_row_b`, and `advance_effect_timer`. The constructor `TObjBoss2Tunnel__sub_802F2A2C` does not use this pragma. | Drop the pragma. The value is `m_58 += m_5c`, then subtract `lbl_805DECB4` on wrap; a port does not need MWCC's load schedule. |

### Approved: `TWindowKeyBoardSoft::set_open_tick` ([#219](https://github.com/matthewlewisnewton/pso-decomp/pull/219))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp` | `TWindowKeyBoardSoft::set_open_tick` @ `0x8024E7B8` (size `0x80`) | one `#pragma opt_common_subs off` | Approved by Matt on 2026-11-04 4:38 PM PT. Without it, common-subexpression elimination swaps the two SDA21 constant loads at `set_open_tick+0x3c` / `+0x44`: matched order is `lfs f2, lbl_805DCC88@sda21` then `lfs f3, lbl_805DCC84@sda21` (`0x8024E7F4` / `0x8024E7FC`); with CSE on those loads swap (`f2`/`f3` renumbered) so the function is the same length and not the same bytes. The float math (`(lbl_805DCC88 + (f32)tick) / lbl_805DCC88` then `* lbl_805DCC84`) is otherwise identical. Unit `-fp_contract on` is separate (section 5) and does not fix this load order. | Drop the pragma. A port does not need MWCC's CSE schedule for these two loads. |

### Approved: `TLobby__sub_803FCF44` ([#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TLobby_803FC178.cpp` | `TLobby__sub_803FCF44` @ `0x803FCF44` (size `0x148`) | one scoped `#pragma opt_common_subs on` | Approved by Matt 2026-11-04 6:14 PM PT. This avetcp unit is compiled `-opt nocse`, so common-subexpression elimination is off for the file. The original reuses common subexpressions in this one function: two direct `lis`/`addi` of `lbl_805C02D0` (`0x803FD034` and `0x803FD058`) and a length clamp of `lhz` / `extsh` / `addi r0,r4,0` (`0x803FD03C`–`0x803FD04C`), frame 32. Without the pragma those reads become one hoisted `...bss.0` base (frame 32→40, saves r29) and the clamp folds to `lha`. The function is then 83.24% (objdiff instruction match 82.65%). `#pragma opt_propagation off` does not change that. `-inline` (`auto`, `deferred`, `auto,deferred`, `noauto`, `on`, `off`, `all`) and `-fp_contract on`/`off` leave the builder at 82.65%, and the auto modes regress other exact functions. Unit-wide `-opt commonsubs` drops other functions in the file. | Drop the pragma. The value is the clamped copy into the challenge buffer; a port does not need MWCC's addressing. |

## 5. Per-unit compiler overrides (`configure.py`)

156 units override the default `GAME_COMPILER = "GC/2.6"`/`cflags_pso` in
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

`TObjBoss2Tunnel.cpp`, `TObjBoss2Tunnel_8003B138.cpp`, and `TObjBoss2Tunnel_802F2070.cpp` set `-fp_contract on` because the curve and tunnel helpers fuse multiply-adds. Each unit stays byte-exact, which is why the flag is on the unit rather than a per-function `fp_contract` pragma. Precedent: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) and Melee, TP, TWW, and Pikmin 2, which contract globally.

### `TAdMultiPlyChrSelectGC_802C50EC.cpp` ([#294](https://github.com/matthewlewisnewton/pso-decomp/pull/294))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp` | `TAdMultiPlyChrSelectGC__sub_802C5F1C` | unit `-inline on` instead of the game default `-inline off` | The slot clamp is a `static inline` helper with no symbol of its own. Under `-inline off` the helper is a real call and the function is 332 bytes (42.79518%). Under `-inline on` the row stays in `r8` and the cell in `r7`, and the function is 236 bytes. `v0` and `v1` are `a / 256.0f` and `(lbl_805DE588 + a) / 256.0f`. MWCC folds that into `fmuls` by the pooled reciprocal at `805DE584` (exactly 1/256) with the dividend on the left, and the function is exact. `-inline auto` inlines other functions (`update` 108→572, `update_option_cursor` 476→700, `handle_dpad_input` 564→788). The other compiled functions and the data sections stay exact under `-inline on`. Evidence: [chr-select-slot-clamp-inline.md](evidence/chr-select-slot-clamp-inline.md). Precedent: [Brawl `-inline on`](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) (only functions marked `inline`); [`-inline auto` in dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) was tried and does not keep this unit identical. | Drop the flag. The value is `min(slot, 3)` applied to each cell's texture row. A port does not need MWCC's inline-local numbering. |

`pso/effect/TEF_LensFlare.cpp` (this change) sets `-fp_contract on` because the
recovered renderer contracts its attenuation and displacement multiply-adds
into `fnmsubs`/`fmadds`. The same unit places `lbl_80438E40` with
`__declspec(section ".rodata")` so the original `{0,0,-1}` vector symbol stays
in `.rodata`. Port: keep FMA or accept small float differences; a normal
`const` is enough for the vector.

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

### `TObjBoss2Tunnel_802F2070.cpp` and `TObjBoss2Tunnel.cpp`: `-inline off,deferred` and upstream #185's switches ([#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290))

| Unit | Functions | What | Why | Port should |
|---|---|---|---|---|
| `pso/boss/TObjBoss2Tunnel_802F2070.cpp` | all 27 functions (`0x802F2070`-`0x802F2C84`), written in reverse address order | unit switch `-inline off,deferred` | Data order. The original `.sbss` holds the ctor's function-local static `constructed$35` (+0) and its guard `init$36` (+4) before `run_task`'s handler-table guard `init$59` (+5), although `run_task` (`0x802F28E0`) comes before the ctor `TObjBoss2Tunnel__sub_802F2A2C` in `.text`. Target asm: `lbz r0,init$59` at `0x802F2900` and `stb r0,init$59` at `0x802F295C`; `lbz r0,init$36` at `0x802F2BA0`, then `li r0,1; stw r0,constructed$35; stb r0,init$36` at `0x802F2BAC`-`0x802F2BB4`. MWCC creates function-local statics in parse order and, with `deferred`, emits code in reverse definition order ([compiler-emission-evidence.md](evidence/compiler-emission-evidence.md)); only that combination gives both orders. Without the switch the guard was emulated with two hand-written globals set in the ctor. With it the ctor has a real `static s32 constructed = 1;`, `.sbss` goes from 66.67% to 100%, `.data` gets real symbol sizes (`@56`-`@58`, `handlers$55`, `boss2_tunnel_effect_tail`), and `.text`, `.rodata` and `.sdata2` stay identical (27/27 functions 100%). check_pr: 0 regressions. The sibling `TObjBoss2Tunnel.cpp` and `TBoss6PlotFalz_802B0228.cpp` (upstream #183) use the same switch, as do `TObjEneRe2Flower_800C3E14.cpp` and `TObjEneEpsilonGuard_8035F5C8.cpp`. Precedent: per-object `-inline` settings in [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) and [brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264). | Drop the switch; definition order does not matter to a port. |
| `pso/boss/TObjBoss2Tunnel.cpp` | the unit (all functions; upstream [#185](https://github.com/zeroz41/pso-decomp/pull/185)'s `configure.py` entry) | unit switches `-inline off,deferred -pool off -sdata 4` | Copied from upstream zeroz41 [#185](https://github.com/zeroz41/pso-decomp/pull/185) with the code. Upstream's fourth switch, `-opt nopropagation`, is replaced by the approved per-function `opt_propagation off` on `TObjBoss2Tunnel__sub_8007D1D0` (section 4). Measured by dropping one switch at a time: without `-pool off`, `run_confirm_message_loop` is 90.25%; without `-sdata 4`, `draw_snapshot_capture_overlay` 78.35%, `TObjBoss2Tunnel__sub_8007DB80` 85.33%, `reset_state` 93.33%, `show_message_and_wait` 96.50%, `run_confirm_message_loop` 97.15%, `TObjBoss2Tunnel__sub_8007D1D0` 99.61%; without `deferred`, the function order flips and most functions drop to 99.2-99.9%. With all three and the pragma, every section of the unit is 100%. `-pool off` and `-sdata 4` are already used by `TOKurage.cpp`, the `TOKey*`/`TOSensor*` units and `TObjEnemyCustom.cpp`. | Drop the switches. |

### `-opt nolifetimes,nocse,noprop,noloop`: `TMovie_80143988.cpp` ([#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167))

| Unit | Function | What | Why | Port should |
|---|---|---|---|---|
| `pso/misc/TMovie_80143988.cpp` | `pack_movie_frame` (`0x80143988`, 564 bytes; the only function in the unit) | unit switch `-opt nolifetimes,nocse,noprop,noloop` | The original keeps each named local in one register for the whole function: the packed word is built in place in `r25`, and `mr r24, r25` copies it for the second scanline before every luma insert (`0x80143A4C`, `0x80143A70`, ... eight times). The cache-touch offset is the single `li r0, 0x20` hoisted to the entry (`0x8014398C`) and reused by both `dcbt r31, r0` / `dcbt r9, r0` (`0x80143A30`, `0x80143ADC`). The pad scales are recomputed late in the entry (`slwi r5, r25, 2` ... `slwi r3, r24, 2`, `0x80143A18`–`0x80143A20`). Without `nolifetimes` the unit is 53.40% (568 bytes, `stmw r21`). Without `noprop`, `touch` is propagated as a constant: 70.50%, 596 bytes. Without `nocse` or `noloop` the shared stride and pad shifts become frontend temps coloured in the wrong order: 93.06%, 564 bytes. With the switch, `.text` (564 bytes), relocations and symbols match the target object. The source is plain C++ (no `__rlwinm`/`__rlwimi`); only `__dcbt` (section 2) remains. Precedent: Petari uses these keywords per object: [`-opt nolifetimes,nocse,noprop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L3735), [`-opt nolifetimes,noloop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L2974), [`-opt noloop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L1532). SFA uses [`-opt nolifetimes`](https://github.com/zcanann/SFA-Decomp/blob/f561e933ecc7356259bccdd6a7ce9a4462a950a0/configure.py#L1586). This repo already has `-opt noprop` and `-opt nocse` units. Evidence: [pack-movie-frame-unit-flags.md](evidence/pack-movie-frame-unit-flags.md). | Drop the switch. The source is plain C++; drop the cache touch too. |

### `-inline noauto`: inventory child links ([#304](https://github.com/matthewlewisnewton/pso-decomp/pull/304))

| Unit | Function | What | Why | Port should |
|---|---|---|---|---|
| `pso/unk/text_801D40D4.cpp`, `pso/player/TObjPlayer_801D5220.cpp`, `pso/player/TPlyItem.cpp`, `pso/player/TObjPlayer_801D4CB8.cpp` | inventory walks (`TObjPlayer__sub_801D4368`, the `TItemList` walks, `destroy_subobjects_recursive`) | unit switch `-inline noauto` | `m_down` / `m_next` are `TObject *`. The slots are `TItemList`. `TItemList::link_down` / `link_next` are class-body inline and hold the one downcast. `-inline noauto` folds each call to `lwz` of `+0x14` / `+0xC`, the same bytes as the old cast. `-inline off` leaves a `bl` and grows the walks (`TObjPlayer__sub_801D4368` `0x248` → `0x278`). `-inline auto` also inlines unmarked `TObjPlayer__sub_801D4730` into `sort_by_key`, so it is not used. Every other function in these objects is unchanged versus `-inline off`. Precedent: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) (`-inline auto`); this repo's `TWindowMainMenu_802AD538.cpp` (`-inline noauto,level=1`). | Drop the switch and the accessors; a downcast at the walk is the portable spelling. |

## 6. Approved regressions

None on main.

## 7. Upstream catch-up (rewrite later)

Matt, 2026-11-04 6:55 PM PT: "Yes, allow the one-time upstream asm exception with
those guardrails." Code taken unchanged from upstream zeroz41/pso-decomp #167-#191
may keep upstream's asm and other patterns the fork otherwise bans, so the fork can
catch up quickly. Each instance gets one row here; the C++ rewrite comes later.
Guardrails: the code is upstream's own (cite the upstream PR), check_pr passes with
0 matched/linked regressions, and new fork code still follows the full rules.

Matt, 2026-11-04 ~8:17 PM PT, on [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298): "Allow #298's as upstream catch-up with
register rows." The rows below are the instances kept under that decision.

Columns (all required; `tools/list_port_exceptions.py --check` validates them):
function/symbol; unit; file (repo path); upstream PR (#167-#191); cheat type (`asm`,
`raw offset cast`, `extern "C" mangled name`, `steering pragma`, `shadow struct`,
or `other: <what>`); the fork PR that brought it in; and the tag
`upstream catch-up, rewrite later`. List and count them with
`python3 tools/list_port_exceptions.py --upstream-catchup`; check_pr prints the count.

| Function/symbol | Unit | File | Upstream PR | Cheat type | Fork PR | Tag |
|---|---|---|---|---|---|---|
| `TObjBoss2Tunnel__sub_8007D1D0` (`0x8007D1D0`): snapshot cursor `flags = (u32 *)p`, `levels = (u32 *)(p + 0x30)`, `name = (char *)(p + 0x60)` | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | raw offset cast | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `TObjBoss2Tunnel__sub_8007D1D0`: `((TLobby *)p)->move_data(...)` on the snapshot buffer | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: receiver cast | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `is_on_current_screen__11TCameraCtrlFv` (declared `extern "C"` with a wide `(ControllerInputContext *, s32)` signature; called by `TObjBoss2Tunnel__sub_8007D1D0`) | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | extern "C" mangled name | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `TObjBoss2Tunnel::eval_piecewise_curve` (`0x8007DE80`): `f32 r = 0.0f; if (farg0 < r) { r = r; }` | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: no-op self-assignment | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `load_data_buffers`: `((TScene *)screen_binary_filename)->update_lobby_scene()` | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: receiver cast | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `TObjBoss2Tunnel__sub_8007CAE8`: `((TWindowSubSymbolChatPartsSet *)(&stack.sp10))->copy_vec2((void *)arg0)` | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: receiver cast | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `TObjBoss2Tunnel::transform_vec_by_camera`: `(u32)TCameraCtrl::get_view_matrix()` for the `TCameraCtrl::concat_matrix(u32, u32)` header signature (upstream called `get_view_matrix__11TCameraCtrlFv`) | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: pointer-to-int cast | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `TObjBoss2Tunnel__sub_8007D1D0`: `((TLobby *)lbl_8048DF34)->tmp_buf_release()`; `save_screen_snapshot`: `((TAdSinglePlyChrSelectGC *)1)->load_player_slot((int)..., (int)...)`; `show_message_and_wait` and `run_confirm_message_loop`: `((TLobby *)win)->send_and_handle(...)` / `set_field_1c(...)` (6 calls). The fork headers declare these as non-static `TLobby`/`TAdSinglePlyChrSelectGC` members, and their other callers across the repo use the same casts | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: receiver cast | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `load_data_buffers`: `memmove(..., (void *)temp_r30, ...)` on the `s32` address from `TLobby::set_stream_and_load_file`; `TObjBoss2Tunnel::load_snapshot`: `memcpy((void *)buf, (void *)(stack.sp60 + 8), ...)` on `s32` addresses; `show_message_and_wait` and `run_confirm_message_loop`: `TLobby::create_message_window((s32)window_pos, (s32)window_size, ...)` for the `(s32, s32, u32, s16)` header signature | `pso/boss/TObjBoss2Tunnel.cpp` | `src/pso/boss/TObjBoss2Tunnel.cpp` | [#185](https://github.com/zeroz41/pso-decomp/pull/185) | other: int/pointer casts | [#290](https://github.com/matthewlewisnewton/pso-decomp/pull/290) | upstream catch-up, rewrite later |
| `update_connection_state__6TLobbyFP13Self_803FD74C` (extern "C" declaration) | `pso/misc/TLobby_803FAEA0.cpp` | `src/pso/misc/TLobby_803FAEA0.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | extern "C" mangled name | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby__sub_803FB6A0`: call `update_connection_state__6TLobbyFP13Self_803FD74C(state, &lbl_805BFF68)` | `pso/misc/TLobby_803FAEA0.cpp` | `src/pso/misc/TLobby_803FAEA0.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | extern "C" mangled name | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby::dispatch_received_packet`: `(Self_803FD74C *)((u8 *)temp_r30_4 + 0xA0)` | `pso/misc/TLobby_803FC178.cpp` | `src/pso/misc/TLobby_803FC178.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | raw offset cast | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby__sub_803FC728`: `(Self_803FD74C *)(sub + 0xA0)` (first call) | `pso/misc/TLobby_803FC178.cpp` | `src/pso/misc/TLobby_803FC178.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | raw offset cast | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby__sub_803FC728`: `(Self_803FD74C *)(sub + 0xA0)` (second call) | `pso/misc/TLobby_803FC178.cpp` | `src/pso/misc/TLobby_803FC178.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | raw offset cast | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby__sub_80402CE0`: `*(u8 *)((u8 *)g + 0x15A)` | `pso/misc/TLobby_803FC178.cpp` | `src/pso/misc/TLobby_803FC178.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | raw offset cast | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby__sub_80402CE0`: `*(u8 *)((u8 *)g + 0x15B)` | `pso/misc/TLobby_803FC178.cpp` | `src/pso/misc/TLobby_803FC178.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | raw offset cast | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |
| `TLobby__sub_80402CE0`: `*(u16 *)((u8 *)g + 0x15C)` | `pso/misc/TLobby_803FC178.cpp` | `src/pso/misc/TLobby_803FC178.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | raw offset cast | [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | upstream catch-up, rewrite later |

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
