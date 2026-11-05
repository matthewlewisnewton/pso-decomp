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

## Summary (regenerated on this branch after merging main `73c22f96f`, 2026-11-05)

Counts below match [porting-exceptions-generated.md](porting-exceptions-generated.md)
after merging main `73c22f96f` (2026-11-05). Assembly is counted as functions;
the generated file counts each `asm` line and its `orig_asm` include separately.

| Category | Hits | Files / units |
|---|---:|---:|
| Assembly (`asm` + `orig_asm` include) | 7 functions (13 source lines) | 4 |
| MWCC intrinsics | 83 | 54 |
| Direct hardware access (GX FIFO `0xCC008000` etc.) | 69 | 13 |
| CodeWarrior pragmas (excluding push/pop) | 5,794 | 875 |
| Per-unit compiler overrides in `configure.py` | 164 | 164 |
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

5,794 pragmas in 875 files; per-file table in the generated file. Main kinds:
`dont_inline` 1148, `inline_depth` 1040, `fp_contract` 894, `auto_inline` 840,
`opt_common_subs` 611, `scheduling` 260, `opt_propagation` 238,
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

### Approved: `TLobby__sub_8020DC78` ([#357](https://github.com/matthewlewisnewton/pso-decomp/pull/357))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TSetManager_8020D918.cpp` | `TLobby__sub_8020DC78` | one scoped `#pragma opt_propagation off` | Approved by Matt 2026-11-05, t250s1179. Propagation merged the separate null locals into one register, leaving six callee-saved register rows different at 99.77419%. Disabling it preserves the distinct object-pool and enemy-row null locals: the target is 100% (620/620 bytes), the whole unit `.text` is 100% (1728/1728), and every sibling stays exact. Precedents: `TObjBoss2Tunnel__sub_8007D1D0` and `TEF_LensFlare::render`. | Drop the pragma. A port does not need MWCC's propagation schedule. |

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

164 units override the default `GAME_COMPILER = "GC/2.6"`/`cflags_pso` in
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

### `TAdChrSelPlyPlateGC.cpp` ([#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/ui/TAdChrSelPlyPlateGC.cpp` | `TAdMultiPlyChrSelectGC__sub_802C5F1C`; also `mark_grid_cell_occupied` inlined into `sub_802C5688` and `sub_802C6660` | unit `-inline on` instead of the game default `-inline off`, together with the `-fp_contract on` row below | The slot clamp is a `static inline` helper with no symbol of its own. Under `-inline off` the helper is a real call and the function is 332 bytes (42.79518%). Under `-inline on` the row stays in `r8` and the cell in `r7`, and the function is 236 bytes. `v0` and `v1` are `a / 256.0f` and `(lbl_805DE588 + a) / 256.0f`. MWCC folds that into `fmuls` by the pooled reciprocal at `805DE584` (exactly 1/256) with the dividend on the left. The same flag inlines `mark_grid_cell_occupied(row, col)`. `802C6660` passes `row + 1, col + 1` (its `row`/`col` are the 0-based quad indices); the inlined arguments are the `addi` before `mulli 0x14` and `stwx` at `0x802C67xx`. `802C5688` already holds grid coordinates and stays 700/700. `-inline auto` inlines other functions (`update` 108→572, `update_option_cursor` 476→700, `handle_dpad_input` 564→788). `-inline deferred` emits the unit backwards. With `-inline on` and `-fp_contract on` together, every function and section of this object matches (36/36, `.text` 7400 including the folded destructor; `.rodata` 0x80471A88–0x80471D08 and owned `.sdata2` 0x805DE580–0x805DE588). Evidence: [chr-select-slot-clamp-inline.md](evidence/chr-select-slot-clamp-inline.md), [chr-select-confirm-cell-store.md](evidence/chr-select-confirm-cell-store.md). Precedent: [Brawl `-inline on`](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) (only functions marked `inline`); [`-inline auto` in dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) was tried and does not keep this unit identical. | Drop the flag. The value is `min(slot, 3)` applied to each cell's texture row, and the occupied-cell store is `grid[row][col] = -1`. A port does not need MWCC's inline-local numbering. |

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
functions above change, from 98.82% (1076 bytes) / 97.81% (296) / 95.60%
(172) without the flag to 100% (1072 bytes) / 100% / 100% with it. `run_task`
is byte-identical either way. Those multiply-adds compile as `fmuls`+`fadds`
when `-fp_contract` is omitted and `fmadds` when it is on.

The constructor clamp (`0x80170068`) is written `attack.power < 0.0f`.
`lbl_805DB85C` is that `0.0f`. Loaded by name, it is an `extern const`, so
the frontend CSE pass puts it in a temp numbered below the reload of
`attack.power` and the compare swaps `f0`/`f1` (99.91%). A literal is not
shared, so the reload is `f1` and the constant is `f0`, which is the
original. That literal is the unit's only `.sdata2` entry. The split claims
`0x805DB85C`-`0x805DB860` (`align:4`), the address of `lbl_805DB85C`. The
other uses in this file still name the symbol, and both relocations resolve
there. Defining `lbl_805DB85C = 0.0f` in the file does not do this: MWCC
inlines the const, so every use becomes a second pool slot 4 bytes after
the exported symbol, and `receive_physical_attack` and
`receive_weapon_special_attack` leave exact. The compiled `.sdata2` section
is 8-aligned and `0x805DB85C` is not, and the pool symbol is the compiler's
`@252` rather than `lbl_805DB85C`, which `text_8016F1C0.cpp` and `TOMine.cpp`
still reference. The unit therefore matches (38/38 functions, `.text`,
`.rodata` and `.sdata2`) and is not linked.

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

#322 (split from #240) builds `pso/misc/TWindowSubStatusDisp_80256B94.cpp`
with `-fp_contract on` and `-inline off,deferred` (unit-level flags allowed
under Matt's 2026-11-04 2:37 PM PT policy).

`-fp_contract on`: the original fuses the depth term of
`render__13TUnk_804CF930FP18TWindowDrawContext` into one `fmadds` at
`0x80257118` (`0.299f * depth + ctx->depth`, then `-1.0f / ...`); MWCC only
emits that from plain C with contraction on. Only that function's code
changes when contraction is turned off. The bar is `sum *= 7.5f; bar =
(tick - sum) * 17.0f;`, which stays `fmuls` / `fsubs` / `fmuls`. The other
functions and `.sdata2` stay byte-identical with contraction off.

`-inline off,deferred`: the two vtables `__vt__13TUnk_804CF918` (`.data`
`0x804CF918`) and `__vt__13TUnk_804CF930` (`0x804CF930`) are emitted by the
virtual destructors. With `-inline off` and the functions defined in address
order, MWCC puts the derived table at the lower address. Defining the
derived functions first and compiling `-inline off` puts the base table
first but emits the derived functions first in `.text`. `-inline off,deferred`
emits that reversed source in address order and still puts
`__vt__13TUnk_804CF918` ahead of `__vt__13TUnk_804CF930`. Each table is
`0x18` bytes (top offset 0, RTTI 0, then the four virtuals; the base
`calc_bar_width` slot is the pure-virtual zero). The whole unit, including
`.text` `0x7e8`, `.rodata` 8, `.data` `0x30` and `.sdata2` `0x78`, matches
with the flag. Without deferred the same source does not. Precedent:
[dtk-template configure.py#L203](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203)
(`-inline auto`) and #L209 (`-fp_contract on`), and this tree's
`TQuestListVM.cpp` / `TObjTombstone.cpp` deferred units. Functions affected:
the whole translation unit. The destructors are `__dt__13TUnk_804CF918Fv`
and `__dt__13TUnk_804CF930Fv`; the other virtuals are
`update__13TUnk_804CF918Fv`, `render__13TUnk_804CF918FP18TWindowDrawContext`,
`calc_bar_width__13TUnk_804CF930Fv`, `update__13TUnk_804CF930Fv`, and
`render__13TUnk_804CF930FP18TWindowDrawContext`.
The signed `open_tick` cast's `0x4330000080000000` bias is
`lbl_8044EE40`. That object was an unclaimed 8-byte `.rodata` gap; the only
relocation to it is the `lis`/`lfd` in `render__13TUnk_804CF930FP18TWindowDrawContext`,
so the range `0x8044EE40..0x8044EE48` belongs to this unit. It is
`scope:local` for the same reason as the other unreferenced compiler pools
(`TObjFish_8033CCC8`'s `lbl_80477F08`): the compiler names the pool `@N`, and
nothing else loads the export. With the bytes in the unit, objdiff's
`functionRelocDiffs=data_value` treats `@N` and `lbl_8044EE40` as the same
load, and `render__13TUnk_804CF930FP18TWindowDrawContext` is byte-identical. The unit's `.sdata2` floats
`lbl_805DCE58` through `lbl_805DCECC` are the same kind of unreferenced pool
(`0.0f` and the other literals, including `lbl_805DCECC` = 2.0f) and are
`scope:local` too, which is what makes the whole unit linkable. Port: drop the flag;
`0.299f * depth + ctx->depth` may become a separate multiply and add. The
cast stays a cast.

### `TWindowKeyBoardSoft_8024E68C.cpp`: `-fp_contract on` ([#219](https://github.com/matthewlewisnewton/pso-decomp/pull/219))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TWindowKeyBoardSoft_8024E68C.cpp` | `scale_point_about_pivot`, `apply_context_transform_to_rect`, `apply_window_closing_stretch`, `clip_textured_quad`, `init_text_window_layout` | unit `configure.py` override `-fp_contract on` | These five functions emit contracted multiplies. In the matched object: `fmadds` at `scale_point_about_pivot`+0x1c/+0x40, `apply_context_transform_to_rect`+0x1c/+0x34/+0x58/+0x70, `apply_window_closing_stretch`+0x40, `clip_textured_quad`+0x80/+0xa8, and `fnmsubs` at `clip_textured_quad`+0xd0/+0xf8; `init_text_window_layout` has four `fmadds` and four `fnmsubs`. Turning contraction off drops the unit from 2156/2156 (17/17) to 1652/2156 (14/17): the transform 79.35% of 124, the stretch 92% of 100, the clip 87.86% of 280. The unit-level flag matches every section of the object that the old per-function `#pragma fp_contract on` produced (`.text` 2156 bytes, `.rodata` 8, `.mwcats.text`, `.comment`). Precedent: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`), and the same switch already used here for `PadRumble.cpp` and `CreationCamera.cpp`. | Keep fused multiply-add, or accept the float differences. |
### `TBoss7TentacleNeedle.cpp`: GC/2.0, `-inline off,deferred`, `-fp_contract on` ([#299](https://github.com/matthewlewisnewton/pso-decomp/pull/299))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/boss/TBoss7TentacleNeedle.cpp` | `__ct__20TBoss7TentacleNeedleFP7TObjectP3Vec` (`0x802EFD08`, GC/2.0); `TBoss7Tentacle__sub_802F0608` and the constructor (`-fp_contract on`); `TObjPlayer__sub_802F0D30` and the unit's `.rodata`/`.sdata2` (`-inline off,deferred`) | unit `configure.py` override `mw_version: GC/2.0` with `-inline off,deferred -fp_contract on` | The constructor passes `create_particle_emitter` a stack copy of `pos`, written as `const Vec emitter_position = *pos;`. The original loads all three words before storing any: `lwz r6,0(r31); lwz r5,4(r31); lwz r0,8(r31); stw r6,8(r1); stw r5,0xc(r1); stw r0,0x10(r1)` at `0x802EFE38`. MWCC before 2.5 leaves a `const` local whose address escapes out of the worst-case alias set, so the scheduler may move the third load above the stores; GC/2.6 adds it and interleaves them (`lwz r5; lwz r0; stw r5; stw r0; lwz r0; stw r0`). Under GC/2.6 the constructor is 97.88% and the unit 40/41; under GC/2.0 every one of the 41 functions and every section matches, and no other function changes between the two compilers. Without `-fp_contract on` the unit drops to 39/41 (`TBoss7Tentacle__sub_802F0608` 91.13%, constructor 96.92%): the tentacle curve and the position jitter fuse to `fmadds`. Without deferred inlining `TObjPlayer__sub_802F0D30` falls to 69.59% and `.rodata`/`.sdata2` are emitted out of order (the vtables also come out tentacle first). No pragmas, no asm, no casts in the copy. Precedent: per-object `mw_version` in [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L257), and this repo's GC/2.0 units for compiler-expanded struct copies (`TItemSpecialEvent_803531FC.cpp`, `Boss5GryphonBehavior.cpp`, `TBoss8Dragon.cpp`, ...). | Drop the overrides; the C++ is the behavior. |

### `TBoss7PhotonBullet_802EF26C.cpp`: `-inline off,deferred`, `-fp_contract on` ([#299](https://github.com/matthewlewisnewton/pso-decomp/pull/299))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/boss/TBoss7PhotonBullet_802EF26C.cpp` | `run_task__18TBoss7PhotonBulletFv` (`0x802EF2AC`); unit vtable order | unit `configure.py` override `-inline off,deferred -fp_contract on` | `run_task` contracts `2.0f * aim + travel` into `fmadds`; with `-fp_contract off` the function grows by `0x10`. Deferred emission, with the definitions written bottom to top, places `__vt__18TBoss7PhotonBullet` then `__vt__15TBoss7PhotonPad` while `.text` stays in address order; without it the compiler emits the pad vtable first. Both vtables are the compiler's own (virtual destructor, `run_task`, `render`); `TOBJECT_OUT_OF_LINE_HELPERS` keeps `queue_destruction` as the external call. With the flags the unit matches every section (`.text` 1428, `.data` 116, `.sdata2` 28, 8/8 functions). Precedent: `-fp_contract on` in [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209), and `-inline off,deferred` on `TObjTombstone.cpp` and other units here. | Drop the flags; the C++ is the behavior. |


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

### `TAdChrSelPlyPlateGC.cpp`: `-fp_contract on` ([#214](https://github.com/matthewlewisnewton/pso-decomp/pull/214), folded by [#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/ui/TAdChrSelPlyPlateGC.cpp` | `sub_802C50EC` (`fmadds` at `0x802C5148`), `sub_802C522C` (`0x802C5274`), `sub_802C5688` (`0x802C58AC`), `sub_802C6660` (`0x802C676C`) | unit `-fp_contract on`, together with the `-inline on` row above | The original unit has one `fmadds` in each of those four functions, so the whole unit was built with contraction on. Main had `#pragma fp_contract on` around the first two only; the unit flag replaces that pragma. Without contraction, `sub_802C50EC` drops to 97.81%, `sub_802C522C` to 96.98%, `sub_802C5688` to 98.03%, and `sub_802C6660` to 93.89%. With both unit flags, every function and section matches. Precedent: [#219](https://github.com/matthewlewisnewton/pso-decomp/pull/219) (`TWindowKeyBoardSoft_8024E68C.cpp`, above) and `TObjTombstone.cpp`, both unit `-fp_contract on`. | Keep fused multiply-add, or accept small float differences. |

### `TBoss6Type1.cpp` ([#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289))

| Flag | Why | Evidence |
|---|---|---|
| `-inline deferred` | Least inline mode that keeps this unit's object identical. | Against `-inline noauto,deferred,level=1` (the previous profile): every section and relocation is byte-identical, so `noauto` and `level=1` do nothing here. `-inline off,deferred` changes 3 functions (`Boss6Anim::copy_transform`, `copy_block` and `TBoss6Type1__sub_802B96C0`). `-inline noauto` changes 2 (`load_params_from_table` and `TBoss6Type1__sub_802B6C30`). `-inline auto` changes 20, including `draw_model`, `run_task` and the constructor. Measured on the source with every function exact. |
| `-fp_contract on` | The unit's multiply-adds are `fmadds`. | `-fp_contract off` changes 16 functions, including `fire_at_all_players`, `spawn_grav_ball`, `update_sway` and `TBoss6Type1__sub_802B626C`. |

Precedent: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) (`-inline auto`) and [#L209](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`); Melee, TP, TWW and Pikmin 2 contract globally; [Brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) uses `-inline on`.

The unit has no per-function pragmas.

Source construct MWCC accepts and standard C++ does not:

| File | What | Why | Port should |
|---|---|---|---|
| `src/pso/boss/TBoss6Type1.cpp` | Seven `s32` constants (`boss6_type1_particle_slot_count`, `boss6_type1_sway_speed_min`/`_range`, `boss6_type1_sway_hold_min`/`_range`, `boss6_type1_anim_count`, `boss6_type1_main_anim`) are declared `extern const` near the top and defined `static const` at the end of the file. | The original reads them with `lwz` from `.sdata2` (`0x805DE2D4`, `0x805DE3A8`..`0x805DE3B4`, `0x805DE3C4`/`0x805DE3C8`), each placed at its first reader in deferred generation order. MWCC folds a `const` scalar read after its definition, and writes an external-linkage one at parse time (offset 0, ahead of every literal). Only an internal-linkage definition after its readers gives both the loads and the positions. Before, the values were externs, `.sdata2` was 95.73% and `0x805DE2C8`..`0x805DE2D0` / `0x805DE3C4`..`0x805DE3F0` were unowned; now the split owns `0x805DE2C8`..`0x805DE3F0`, the section is 296/296 bytes and the unit links. Evidence: [tboss6type1-sdata2-constants.md](evidence/tboss6type1-sdata2-constants.md). | Drop the `extern` declarations and define the constants (`static const` or `constexpr`) above their first use. |

### `-inline noauto`: inventory child links ([#304](https://github.com/matthewlewisnewton/pso-decomp/pull/304))

| Unit | Function | What | Why | Port should |
|---|---|---|---|---|
| `pso/unk/text_801D40D4.cpp`, `pso/player/TObjPlayer_801D5220.cpp`, `pso/player/TPlyItem.cpp`, `pso/player/TObjPlayer_801D4CB8.cpp` | inventory walks (`TObjPlayer__sub_801D4368`, the `TItemList` walks, `destroy_subobjects_recursive`) | unit switch `-inline noauto` | `m_down` / `m_next` are `TObject *`. The slots are `TItemList`. `TItemList::link_down` / `link_next` are class-body inline and hold the one downcast. `-inline noauto` folds each call to `lwz` of `+0x14` / `+0xC`, the same bytes as the old cast. `-inline off` leaves a `bl` and grows the walks (`TObjPlayer__sub_801D4368` `0x248` → `0x278`). `-inline auto` also inlines unmarked `TObjPlayer__sub_801D4730` into `sort_by_key`, so it is not used. Every other function in these objects is unchanged versus `-inline off`. Precedent: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) (`-inline auto`); this repo's `TWindowMainMenu_802AD538.cpp` (`-inline noauto,level=1`). | Drop the switch and the accessors; a downcast at the walk is the portable spelling. |

### `TBoss4ZakoDraw.cpp`: `-fp_contract on` ([#303](https://github.com/matthewlewisnewton/pso-decomp/pull/303))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/boss/TBoss4ZakoDraw.cpp` | `TObjPlayer__sub_8030A9B0` | unit `configure.py` override `-fp_contract on` | The Falz shadow draw contracts `t*(t*t)` to `fnmsubs` and the tint to `fmadds`. Without the switch those are separate mul/add and the function is not the original bytes. The other eight functions in the unit stay byte-identical with the switch (9/9 linked). Not a per-function pragma. Precedent: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`); Melee, TP, TWW, and Pikmin 2 contract floats globally. | Keep fused multiply-add, or accept the float differences. |

`dhcp_state` is `volatile s32`. The timer callback `TLobby__sub_80423298` (`0x80423298`) and `dhcp_handle_reply` (`0x80424A48`) write it, and `TLobby__sub_80424CF4` stores 6 then reloads it before any call (`lwz` at `0x80424D1C` while r3 still holds 6). A port declares that object `volatile` and does not cache it across those calls. This is portable C++; it is not an MWCC pragma or a `*(volatile s32 *)&` pun.

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
| [#295](https://github.com/matthewlewisnewton/pso-decomp/pull/295), [#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289), [#225](https://github.com/matthewlewisnewton/pso-decomp/pull/225), [#222](https://github.com/matthewlewisnewton/pso-decomp/pull/222), [#215](https://github.com/matthewlewisnewton/pso-decomp/pull/215), [#128](https://github.com/matthewlewisnewton/pso-decomp/pull/128) | 1 to 4 inlining/optimization pragmas each | Reason not recorded. Drop in a port. |
| [#240](https://github.com/matthewlewisnewton/pso-decomp/pull/240) | Not scanned | Diff exceeds GitHub's 300-file limit; scan locally after it merges. |
| [#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167) | Unit switch `-opt nolifetimes,nocse,noprop,noloop` on `TMovie_80143988.cpp` (section 5); the pre-existing `__dcbt` in `pack_movie_frame` | `pack_movie_frame` matches 100% in plain C++. The earlier `__rlwinm` / `__rlwimi` calls are gone. `__dcbt` is the original data-cache touch (`dcbt r31, r0` / `dcbt r9, r0`). Port: drop the switch and the cache touch. |

The scan covers source lines only; `configure.py` overrides added by PRs show up
in the generated table once merged.
