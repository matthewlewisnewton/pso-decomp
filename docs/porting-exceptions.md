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

## Summary (main at 7ccb07696, 2026-11-04)

| Category | Hits | Files / units |
|---|---:|---:|
| Assembly (`asm` + `orig_asm` include) | 4 functions | 2 |
| MWCC intrinsics | 83 | 54 |
| Direct hardware access (GX FIFO `0xCC008000` etc.) | 71 | 13 |
| CodeWarrior pragmas (excluding push/pop) | 5,871 | 886 |
| Per-unit compiler overrides in `configure.py` | 141 | 141 |
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

These four predate the scalar-fallback rule and have **no C fallback**.

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

5,871 pragmas in 886 files; per-file table in the generated file. Main kinds:
`dont_inline` 1153, `inline_depth` 1045, `fp_contract` 931, `auto_inline` 844,
`opt_common_subs` 624, `scheduling` 267, `opt_propagation` 239,
`readonly_strings` 203, `peephole` 105, `optimization_level` 88, `bool` 56,
`defer_codegen` 50, `pack` 46. Reason: reproduce the original code generation
and emission order; individual pragmas generally carry no recorded reason.

Port should: drop optimization/scheduling/inlining pragmas (they only steer
MWCC). **Keep the semantics** of `pack` (use the target's packing attribute and
check struct layout), `bool`, and `fp_contract` where float results must match
bit-for-bit (`fp_contract on` means fused multiply-add was used; a port may see
small float differences without FMA).

## 5. Per-unit compiler overrides (`configure.py`)

141 units override the default `GAME_COMPILER = "GC/2.6"`/`cflags_pso` in
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

## 6. Approved regressions

None on main.

## Pending in open PRs

Found by `tools/list_port_exceptions.py --pr N` on 2026-11-04. Add or remove the
entry when the PR merges.

| PR | Exception | Status / reason |
|---|---|---|
| [#281](https://github.com/matthewlewisnewton/pso-decomp/pull/281) | `transform_chunk_vertices_pos_normal` (`src/pso/unk/text_803E2D70.cpp`) as `asm void` | One-time asm exception approved by Matt on 2026-11-04: SDK `PSMTXROMultVecArray`-style paired-single code that every other GameCube decomp keeps as asm. Guarded for MWCC with a scalar C++ fallback. Evidence: `docs/evidence/paired-single-sdk-asm.md` on that branch. Port: use the C++ fallback. |
| [#291](https://github.com/matthewlewisnewton/pso-decomp/pull/291) | Allowed regression: `deform_indirect_texture_scroll` 100% → 99.79% | Approved by Matt on 2026-11-04 so the `off16 = offset` steering (still on main in `TEffIndirectCtrl_802A88AC.cpp`) could be removed. Port: nothing; the PR version is the portable one. |
| [#285](https://github.com/matthewlewisnewton/pso-decomp/pull/285) | `static asm void pad_03_8042E9FC_text` via `orig_asm` include (`src/pso/unk/text_8042E9FC.cpp`) | PR body: 5-word stranded epilogue; 0/60 C probes across 20 compilers reach it. **No approval recorded and no scalar fallback**; it needs one under the rule above. |
| [#296](https://github.com/matthewlewisnewton/pso-decomp/pull/296) | `scheduling` ×5, `peephole`, `optimize_for_size` pragmas | Reason not recorded. Drop in a port. |
| [#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250) | `fp_contract` ×3 | Reason not recorded. |
| [#303](https://github.com/matthewlewisnewton/pso-decomp/pull/303), [#295](https://github.com/matthewlewisnewton/pso-decomp/pull/295), [#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289), [#272](https://github.com/matthewlewisnewton/pso-decomp/pull/272), [#225](https://github.com/matthewlewisnewton/pso-decomp/pull/225), [#222](https://github.com/matthewlewisnewton/pso-decomp/pull/222), [#215](https://github.com/matthewlewisnewton/pso-decomp/pull/215), [#187](https://github.com/matthewlewisnewton/pso-decomp/pull/187), [#128](https://github.com/matthewlewisnewton/pso-decomp/pull/128) | 1 to 4 inlining/optimization pragmas each | Reason not recorded. Drop in a port. |
| [#240](https://github.com/matthewlewisnewton/pso-decomp/pull/240) | Not scanned | Diff exceeds GitHub's 300-file limit; scan locally after it merges. |
| [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | Fake linkage: `extern "C" void handle_request_timeout__6TLobbyFv(void)`, stored into the one-word timer callback in `TLobby__sub_80402CE0` (`src/pso/misc/TLobby_803FC178.cpp`, compiled as the tail TU) | **Not approved.** The binary relocates that slot to `handle_request_timeout__6TLobbyFv`. On MWCC GC/1.2.5n a pointer to a non-static member is 12 bytes for a class with no bases and no virtuals (`this_delta`, `v_offset`, function address), so class shape does not make it a 4-byte address. `__ptmf_cast` is not a builtin here. The real non-static `TLobby::handle_request_timeout` stays; it is already byte-exact and reads `this`. Port: on a compiler whose pointer-to-member is a single address, store `&TLobby::handle_request_timeout`. |
| [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | Per-unit `-opt nocse` on `pso/misc/TLobby_803FD08C.cpp` | The remainder of the avetcp PPP object after the CHAP builder was split out. Same profile as `TLobby_803FC178.cpp` and the other PPP files (configure.py: those files were built without CSE). The builder itself (`TLobby_803FCF44.cpp`) uses the avetcp default, CSE on. |
| [#298](https://github.com/matthewlewisnewton/pso-decomp/pull/298) | `__declspec(section ".sdata2")` on `lbl_805E1158` in `TLobby_803FCF44.cpp` | The seven-byte `"avetcp"` object is a global `.sdata2` symbol. A plain C++ `const` is local, so the unit cannot be linked; `extern` without the section attribute emits `.sdata` and the loads use r13. Same attribute as `TObjFish_8033CCC8.cpp` on main. Port: an ordinary global const in the small read-only data section. |

The scan covers source lines only; `configure.py` overrides added by PRs show up
in the generated table once merged.
