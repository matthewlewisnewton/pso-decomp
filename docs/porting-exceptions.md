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

## Summary (regenerated on this branch after merging main `39136ddd5`, 2026-11-04)

| Category | Hits | Files / units |
|---|---:|---:|
| Assembly (`asm` + `orig_asm` include) | 5 functions | 3 |
| MWCC intrinsics | 83 | 54 |
| Direct hardware access (GX FIFO `0xCC008000` etc.) | 71 | 13 |
| CodeWarrior pragmas (excluding push/pop) | 5,864 | 885 |
| Per-unit compiler overrides in `configure.py` | 144 | 144 |
| Approved regressions | 0 on main, 1 pending (#291) | |

## Rule for assembly

If assembly is approved, a scalar C/C++ equivalent ships next to it (Matt,
2026-11-04). The asm is guarded for the GameCube/MWCC build (`#ifdef __MWERKS__`)
and the scalar version is the compiled fallback, so a port builds the C. Approved
asm always has an entry in this register.

## 1. Assembly

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/musyx/runtime/Chorus/chorus_fx.c` | `do_src1`, `do_src2` | `asm` body from `orig_asm` include | Library code shipped as assembly; covered by the CONTRIBUTING `orig_asm` rule for vendor assembly. No specific evidence doc. | Write scalar C fallback (none exists yet); MusyX upstream C sources are a reference. |
| `src/musyx/runtime/StdReverb/reverb.c` | `DoCrossTalk`, `HandleReverb` | `asm` body from `orig_asm` include | Same as above. | Same: scalar C fallback needed (none exists yet). |
| `src/pso/unk/text_803E2D70.cpp` | `transform_chunk_vertices_pos_normal` | hand-written `asm void` under `#ifdef __MWERKS__` | One-time asm exception approved by Matt on 2026-11-04 ([#281](https://github.com/matthewlewisnewton/pso-decomp/pull/281)): SDK `PSMTXROMultVecArray`-style paired-single code (`psq_l`/`ps_madds*`/`psq_stu`) that MWCC cannot emit from C; other GameCube decomps keep it as asm. Evidence: [docs/evidence/paired-single-sdk-asm.md](evidence/paired-single-sdk-asm.md). | Use the scalar C++ `#else` fallback that ships with it. |

The four MusyX entries predate the scalar-fallback rule and have **no C fallback**; `transform_chunk_vertices_pos_normal` has one.

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

5,864 pragmas in 885 files; per-file table in the generated file. Main kinds:
`dont_inline` 1153, `inline_depth` 1045, `fp_contract` 931, `auto_inline` 844,
`opt_common_subs` 624, `scheduling` 262, `opt_propagation` 239,
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

## 5. Per-unit compiler overrides (`configure.py`)

144 units override the default `GAME_COMPILER = "GC/2.6"`/`cflags_pso` in
`GAME_EXCEPTIONS` or the `MIDDLEWARE` table: other MWCC versions (GC/1.2.5,
1.2.5n, 1.3, 1.3.2, 2.0) and switches (`-inline deferred`, `-fp_contract on`,
`-str reuse,readonly`, `-sdata 4`, `-opt nocse`, `-use_lmw_stmw off`, ...). The
`configure.py` comment above each entry is its recorded reason (e.g.
`pso_date.cpp`: GC/1.3.2 scheduling, see
[calendar-conversion-evidence.md](evidence/calendar-conversion-evidence.md);
`TObjTombstone.cpp`: `-fp_contract on` because two calculations fuse
multiply-adds). The generated table copies each comment; 92 entries have no
comment of their own (several share a comment with the entry above). Library
groups (SDK, runtime, TRK, MusyX, CRI, Ginja, mcFs, ntInf, avetcp, modem, ntUtl)
use their own compiler versions as recorded there.

Port should: build everything with one modern compiler. Only `-fp_contract on`
(float results) and deferred emission order (no semantic effect) need thought;
nothing else changes behaviour.

### `TBoss6Type1.cpp` ([#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289))

| Flag | Why | Evidence |
|---|---|---|
| `-inline deferred` | Least inline mode that keeps this unit's object identical. | Against `-inline noauto,deferred,level=1` (the previous profile): `.text`, `.data`, `.rodata`, `.sdata2` and relocations are byte-identical, so `noauto` and `level=1` do nothing here. `-inline off,deferred` changes 21 functions, including `copy_transform` and `TBoss6Type1__sub_802B96C0`. `-inline noauto` changes 86, including `draw_model` and `render`. `-inline auto`, `on`, and `all` inline callers and change the same set. |
| `-fp_contract on` | The unit's multiply-adds are `fmadds`. | `-fp_contract off` changes 71 functions, including `draw_part_motions`, `run_task`, `render_shadows`, and `TBoss6Type1__sub_802B626C`. |

Precedent: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) (`-inline auto`) and [#L209](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`); Melee, TP, TWW and Pikmin 2 contract globally; [Brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) uses `-inline on`.

Neither flag replaces the two per-function pragmas. With those pragmas deleted, every allowed inline mode left `TBoss6Type1__ct` and `TBoss6Type1__sub_802B8A70` off (the modes that preserved the other functions leave them at the same 98.5% / 97.8% as deleting the pragmas under the old profile). Those pragmas stay pending; they are not approved.

## 6. Approved regressions

None on main.

## Pending in open PRs

Found by `tools/list_port_exceptions.py --pr N` on 2026-11-04. Add or remove the
entry when the PR merges.

| PR | Exception | Status / reason |
|---|---|---|
| [#291](https://github.com/matthewlewisnewton/pso-decomp/pull/291) | Allowed regression: `deform_indirect_texture_scroll` 100% → 99.79% | Approved by Matt on 2026-11-04 so the `off16 = offset` steering (still on main in `TEffIndirectCtrl_802A88AC.cpp`) could be removed. Port: nothing; the PR version is the portable one. |
| [#285](https://github.com/matthewlewisnewton/pso-decomp/pull/285) | `static asm void pad_03_8042E9FC_text` via `orig_asm` include (`src/pso/unk/text_8042E9FC.cpp`) | PR body: 5-word stranded epilogue; 0/60 C probes across 20 compilers reach it. **No approval recorded and no scalar fallback**; it needs one under the rule above. |
| [#296](https://github.com/matthewlewisnewton/pso-decomp/pull/296) | `scheduling` ×5, `peephole`, `optimize_for_size` pragmas | Reason not recorded. Drop in a port. |
| [#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250) | `fp_contract` ×3 | Reason not recorded. |
| [#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289) | `TBoss6Type1__ct`: `#pragma opt_common_subs off`. `TBoss6Type1__sub_802B8A70`: `#pragma opt_lifetimes off`. | Not approved. No allowed unit inline or `fp_contract` flag reproduces them (section 5). `opt_common_subs off` keeps `lbl_80470EAC` from being CSE'd (98.5% without it). `opt_lifetimes off` keeps the `fctiwz` reload in r30 (97.8% without it). Drop both in a port. |
| [#303](https://github.com/matthewlewisnewton/pso-decomp/pull/303), [#295](https://github.com/matthewlewisnewton/pso-decomp/pull/295), [#272](https://github.com/matthewlewisnewton/pso-decomp/pull/272), [#225](https://github.com/matthewlewisnewton/pso-decomp/pull/225), [#222](https://github.com/matthewlewisnewton/pso-decomp/pull/222), [#215](https://github.com/matthewlewisnewton/pso-decomp/pull/215), [#187](https://github.com/matthewlewisnewton/pso-decomp/pull/187), [#128](https://github.com/matthewlewisnewton/pso-decomp/pull/128) | 1 to 4 inlining/optimization pragmas each | Reason not recorded. Drop in a port. |
| [#240](https://github.com/matthewlewisnewton/pso-decomp/pull/240) | Not scanned | Diff exceeds GitHub's 300-file limit; scan locally after it merges. |

The scan covers source lines only; `configure.py` overrides added by PRs show up
in the generated table once merged.
