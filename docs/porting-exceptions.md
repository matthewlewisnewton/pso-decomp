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

## Summary (regenerated after merging main `4ae351128`, 2026-11-09)

Counts below match [porting-exceptions-generated.md](porting-exceptions-generated.md)
after merging main `4ae351128` (2026-11-09). Assembly is counted as source lines;
the generated file counts each `asm` line and its `orig_asm` include separately.

| Category | Hits | Files / units |
|---|---:|---:|
| Assembly (`asm` + `orig_asm` include) | 44 source lines | 11 |
| MWCC intrinsics | 83 | 54 |
| Direct hardware access (GX FIFO `0xCC008000` etc.) | 69 | 13 |
| CodeWarrior pragmas (excluding push/pop) | 5,774 | 877 |
| Per-unit compiler overrides in `configure.py` | 184 | 184 |
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
| `src/pso/unk/text_803D8910.cpp` | `vec3_add_to` | hand-written `asm void` under `#ifdef __MWERKS__`; scalar add in the `#else` | In-place paired-single add (`psq_l`/`ps_add`/`psq_st`, z with W=1) at 0x803D8910 that CW 2.6 cannot emit from C. Matt confirmed this exception in the [#128 approval](#approval-for-the-ginja-vector-kernels). Evidence: [vec3-add-to-paired-single.md](evidence/vec3-add-to-paired-single.md). | Compile the scalar add fallback. |
| `src/pso/unk/text_803D8910.cpp`, `src/pso/unk/text_803D96A8.cpp` | `vec3_dot`, `vec3_cross`, `normalize_vector` | standard `orig_asm` body from the disc under `#ifdef __MWERKS__`; scalar C/C++ in the `#else` | GC/2.6 did not reproduce the register allocation and load order of `vec3_dot` (0x803D89C0). The typed intrinsics also insert an extra rounding step when reproducing the estimate sequence in `vec3_cross` (0x803D8A18) and `normalize_vector` (0x803D97B4). Matt approved these three disc-generated bodies in the [#128 approval](#approval-for-the-ginja-vector-kernels). Evidence: [vec3-add-to-paired-single.md](evidence/vec3-add-to-paired-single.md). | Compile the scalar C/C++ fallback. |
| `src/pso/unk/text_803E2D70.cpp` | `transform_chunk_vertices_pos_normal` | hand-written `asm void` under `#ifdef __MWERKS__` | One-time asm exception approved by Matt on 2026-11-04 ([#281](https://github.com/matthewlewisnewton/pso-decomp/pull/281)): SDK `PSMTXROMultVecArray`-style paired-single code (`psq_l`/`ps_madds*`/`psq_stu`) that MWCC cannot emit from C; other GameCube decomps keep it as asm. Evidence: [docs/evidence/paired-single-sdk-asm.md](evidence/paired-single-sdk-asm.md). | Use the scalar C++ `#else` fallback that ships with it. |

### Approval for the Ginja vector kernels

On 2026-11-09, Matt approved merging
[PR #128](https://github.com/matthewlewisnewton/pso-decomp/pull/128) with
the hand-written paired-single `vec3_add_to` body and the disc-generated
`vec3_dot`, `vec3_cross` and `normalize_vector` bodies. The approval covers
their scalar C++ fallbacks and the `ports/` layout in that PR. See the
[merge review](https://github.com/matthewlewisnewton/pso-decomp/pull/128#pullrequestreview-5820919265)
for the decision it resolves and [#356](https://github.com/matthewlewisnewton/pso-decomp/pull/356)
for the earlier `vector_length` precedent.

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

5,773 pragmas in 877 files; per-file table in the generated file. Main kinds:
`dont_inline` 1146, `inline_depth` 1038, `fp_contract` 877, `auto_inline` 837,
`opt_common_subs` 609, `scheduling` 261, `opt_propagation` 237,
`readonly_strings` 205, `peephole` 103, `optimization_level` 88, `bool` 56,
`defer_codegen` 53, `pack` 46, `opt_dead_assignments` 41. Reason: reproduce the original code generation
and emission order; individual pragmas generally carry no recorded reason.

Port should: drop optimization/scheduling/inlining pragmas (they only steer
MWCC). **Keep the semantics** of `pack` (use the target's packing attribute and
check struct layout), `bool`, and `fp_contract` where float results must match
bit-for-bit (`fp_contract on` means fused multiply-add was used; a port may see
small float differences without FMA).

### Dark Falz demo 4

| File | Scope | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/object/TObjDFDemo4.cpp` | Translation unit | `readonly_strings on` and `defer_codegen on` | Places the class name in `.rodata` and emits the seven functions in reverse definition order. Deferred generation also places the camera initializers before the signed conversion constant. | Use ordinary string and function definitions. |
| `src/pso/object/TObjDFDemo4.cpp` | Constructor at `0x8004F6AC` | Weak linkage for the strip-node table | With strong linkage CodeWarrior pools the strip table and both camera initializers under a shared `.rodata` base. Weak linkage preserves the original direct relocations and keeps the shared `.data` base for the motion tables and vtable. | Use the same const table with ordinary linkage. |
| `configure.py` | `pso/object/TObjDFDemo4.cpp` | `-sdata 4` | The two eight-byte afterimage index tables use normal data addressing. The class-name pointer still uses small data. | Use ordinary arrays and a string pointer. |

### `request_network_info_load` frame and instruction ordering

`src/pso/network/NetworkInfoRequests.cpp` uses scoped `scheduling off` and
`peephole off` pragmas and an MWCC-only 32-byte alignment attribute on its
first parameter. The pragmas reproduce the original instruction order and
switch lowering; the attribute reproduces its aligned frame. This is a
code-generation device, not evidence that the channel value requires alignment
or that the original source used an aligned parameter. The original and the
compiled function both pass the channel in the same register and do not access
an aligned stack object. A port should ignore these settings and use the plain
`s32` parameter and function body. See
[the comparison](evidence/network-info-request-frame.md).

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

### Network runtime recovered from upstream #213/#215

| File | Functions / scope | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/protocol/NetworkRuntime.cpp` | `TLobby__sub_803F8E9C` (`0x803F8E9C`) | One new scoped `pool_data on`; pooled cross-array queue addresses, word views, pointer-valued 32-bit handles, explicit initialization order and unused upstream temporaries | Exact native BSS references, register schedule and stack frame. Typed alternatives range from 74.49% to 99.95%; concrete offsets and probes are in [the evidence](evidence/upstream-network-runtime.md). | Use the actual typed slot arrays and native handle types; remove unused locals and optimizer steering. Do not preserve cross-array pointer arithmetic. |
| `src/pso/protocol/NetworkRuntime.cpp` | `TLobby__sub_803FABDC` (`0x803FABDC`) | Redundant second null test/allocation branch and `goto`, `A_803FADA0` option-block view, explicit allocator ABI name | These reproduce the original control flow and existing protocol ABI. The callback signature itself is corrected consistently. | Remove redundant control flow and consolidate the packet/option/allocator interfaces. |
| `src/pso/protocol/NetworkRuntime.cpp` | Previously exact code now linked | Existing 32 pragmas, `-opt nocse`, raw protocol views and mangled names, provisional class wrappers, direct bus-clock reads | Existing native matching debt becomes source-linked with this unit; no new hardware access, asm, intrinsic or compiler override. See [the bounded inventory and port guidance](evidence/upstream-network-runtime.md). | Replace clock/OS operations with target services and consolidate protocol interfaces; remove optimizer-only pragmas/overrides. |

### PPPoE discovery recovered from upstream #213/#215

| File | Function / scope | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TLobby_80426CAC.cpp` | `TLobby__sub_804275B0` (`0x804275B0`) | Unused upstream `pad[2]` and `spare[2]` locals | Preserve the original MWCC stack frame/slot offsets; removing them scores 99.90–99.97%. Typed fields and consistent helper signatures retain 100%; see [the evidence](evidence/upstream-pppoe.md). | Remove unused locals; use typed buffers and explicit byte-order/length handling. |
| `src/pso/misc/TLobby_80426CAC.cpp` | Previously exact code now linked | 12 existing pragma lines, opaque/overlapping table views, 32-bit address tokens, raw packet/tag accesses, redundant expressions and provisional class wrappers | Existing native matching debt becomes source-linked; no new pragma or compiler override. [The evidence](evidence/upstream-pppoe.md) records its limits. | Use one typed table, explicit buffer/free-function interfaces and portable pointer/token types; validate lengths and remove optimizer-only steering. |

### Focused DHCP recovery from fork #303

| File | Scope | What remains | Port should |
|---|---|---|---|
| `src/pso/unk/text_80421620.cpp` | DHCP timer/request/discovery and previously exact code now linked | Provisional class wrappers on packet buffers, fixed reply/options offsets, 32-bit pointer/callback words, native byte-order and volatile-state assumptions; existing optimizer steering and release-frame padding. The new callback header makes callback declarations consistent. See [evidence](evidence/dhcp-focused-recovery.md). | Use shared typed packet/state definitions, explicit byte order and length checks, pointer-sized handles and appropriate synchronization; remove optimizer-only constraints. |

### PPP/session control recovered from upstream #213/#215

| File | Function / scope | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TLobby_803FAEA0.cpp` | `TLobby__sub_803FB358` | Redundant base initialization and otherwise-unused `new_var` assignment | Simplifying the native temporary pattern changes the base register (99.882355%); [evidence](evidence/upstream-ppp-session.md). | Use a typed protocol/status copy and remove matching-only temporaries. |
| `src/pso/misc/TLobby_803FAEA0.cpp` | Connection routine and previously exact code now linked | Bounded session views, raw status offsets, native-endian words, 32-bit addresses, notification macros/goto and 36 existing pragma lines | Existing native representation/emission constraints; new status helper declarations and definitions are consistent. No new pragma or compiler override. | Consolidate layouts and signatures, use portable handles and explicit byte order, preserve callback timing and remove optimizer steering. |

### Keyboard control recovered from upstream #208

| File | Function / scope | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TKeyBoardControl.cpp` | Keyboard glyph/tab and key-frame drawing | Existing scoped `pool_data off` and `fp_contract` pragmas, provisional receiver/layout views and explicit mangled helper names | Native table references, floating-point instructions and class boundaries; see [the evidence](evidence/upstream-keyboard-control.md). The existing `opt_loop_invariants off` is removed. | Drop optimizer steering, preserve required floating-point semantics, and consolidate keyboard/rendering types. |
| `src/pso/misc/TWindowSubStatusDisp_8024FBA8.cpp` | Font-code mapper declaration | Existing wide input declaration remains `s32`, while the shared mapper interface takes `u16`; return type is corrected to `u16` | Narrowing the caller declaration changes original instruction selection. The new glyph-drawing signature is consistent in all callers, but this neighboring legacy boundary remains unresolved. | Use the shared narrow mapper interface and explicit character decoding; do not preserve the declaration discrepancy. |

### Dispatcher extraction using upstream #213/#215 boundaries

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/network/NetworkDispatcher.cpp` | All 12 dispatcher functions | Four existing pragma lines (`opt_common_subs on` x3, `pool_data off` x1), inherited `-opt nocse`, 32-bit handles and provisional `TLobby`/`TUdpSocket` wrappers; reset status and thread-creation callback/return declarations remain inconsistent across units | Extracts the fork's already-exact dispatcher and its 248-byte BSS so it can link. The follow-up replaces reset/shutdown/handler overlays with the shared state and names both thread handles without changing native objects. The reset callee now explicitly returns `s32`, but the incompatible DHCP caller is retained after a type-correct probe changed its frame and result copy; this is not a completed ABI repair. See [upstream-dispatcher.md](evidence/upstream-dispatcher.md). | Remove compiler-only steering and recover explicit dispatcher/OS contracts with portable handle types, validating callers and callees together. |
| `src/pso/network/TcpProtocol.cpp` | Extracted TCP range; still unlinked | Inherited `-opt nocse`; 24 moved pragma lines plus explicit `dont_inline off` and `inline_depth(4)` that previously carried into this range from earlier source | Without the ambient settings, timer callbacks `8041A3CC` / `8041A5B4` have different stack frames and `8041D584` no longer inlines its segment-removal helper. Scores are 99.78432%, 99.916664% and 65.69705%; restoring the settings retains all 40 previously exact TCP functions. Existing raw views, local ABI redeclarations and provisional members remain unresolved. | Remove compiler steering; unify TCP layouts and callback/status interfaces. This extraction does not claim the five still-unmatched TCP functions as recovered. |

## 5. Per-unit compiler overrides (`configure.py`)

169 units override the default `GAME_COMPILER = "GC/2.6"`/`cflags_pso` in
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

### `pso/ui/TAdDialingGC_80328B20.cpp` with GC/1.3.2

GC/1.3.2 preserves the 59-instruction sequence of `draw_dialing_rectangle`
at `0x80328B24`. With the same source, GC/2.6 reuses coordinate loads and
sums across the vertex writes and emits 49 instructions. The older compiler
also matches the other three functions with the default game flags.

The four coordinate pairs at `0x804767A8..0x804767C8` stay in the existing
original read-only data contribution. Assigning them to this split would
reverse its order relative to the dialing constructor's string and create a
link-order cycle. The single referenced float at `0x805DF6F8` belongs to this
split. The following zero word has no reference and stays with the original
data.

A port can use its regular compiler. Bind the legacy
`draw_tri_fan_2d__14TObjCMHairMenuFllf` entry to the renderer that takes a
`ColorLineList`, and supply the four coordinate pairs as typed constants.

### `pso/ui/TAdSelectGameModeGC_802C4748.cpp` with GC/1.3.2 and `-fp_contract on`

`draw_selection_plate` at `0x802C4B64` uses the caller's position and the two
floats at plate offsets `0x21C` and `0x220` to build a four-vertex fan. The
character-select, serial-entry, and password-entry callers pass the same
four-byte color by value. GC/1.3.2 preserves the coordinate load schedule,
as in the dialing rectangle. Assigning the vertex pointer before the color
pointer reproduces the original register allocation. The depth expression
fuses the index adjustment and base depth in the `fmadds` at `0x802C4C84`.
The unsigned conversion bias and two float literals supply the new
`.rodata` and `.sdata2` contributions.

A port can use its regular compiler and call the renderer through a
`ColorLineList` interface. Preserve the fused depth calculation if the port
requires identical rounding.

### `pso/unk/text_80049FD8.cpp` and the Vol Opt debris initializer

GC/2.0 interleaves the BML resource and model-table loads with the final
load and store of the initializer copy. It loads all three
position components before storing them. GC/2.6 groups the copy tail and
interleaves the position loads and stores. The same GC/2.0 aggregate pattern
is used for debris in `TOExplosiveMachine.cpp` and `TOTrapAncient01.cpp`.

The local initializer emits the 76-byte template at `0x80436748`. The
original relocations to this template come from `fn_80049FD8`, and the split
maps it to the compiler's local `@13` symbol. Ports can use the default
compiler.
### `pso/misc/TLobby_8001EF5C.cpp`: `-inline on`

`init_from_id_lists` at `0x8002058C` (size `0x30C`) contains the
model-count walk, the motion-count walk, and the flag `& 2` download walk in
its body. The project default `-inline off` outlines those `static inline`
walks, so the function is not the original bytes. Measured with objdiff
(`functionRelocDiffs=data_value`):

| Flag | Result |
|---|---|
| `-inline auto` | `.text` 62.53%, `.data` 0% |
| `-inline auto,deferred` | `.text` 52.51%, `.data` 0% |
| `-inline deferred` | Per-function match on the previous `extern "C"` body. On this C++ function it emits `init_from_id_lists` at `.text+0` instead of `.text+0x1630`, so the linked DOL does not match. |
| `-inline on` | Every function 100%, `.text` and `.data` 100%, function at `.text+0x1630`. The unit links. |

`-inline on` is the least invasive flag that keeps the whole unit identical,
including section order. Precedent for this family of unit-level inline switches:
[dtk-template `-inline auto`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203)
and [Brawl `-inline on`](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264).

The current source walks each id list with a pointer and a caller-born index
(`load_model_list`, `load_motion_list`, and the flag `& 2` model request).
Objdiff of that body is 100% (780 bytes, at `.text+0x1630`). The unit links.
The typed file API recovery is recorded in
[pr308-typed-file-apis.md](evidence/pr308-typed-file-apis.md).

### `pso/quest/QuestOpcodeHandlers.cpp`: `-inline on`

This existing unit switch also inlines the scalar accessor on the VM's per-slot
`QuestVmArgument` union. String-push writes the pointer alternative directly;
the GBA disk opcode reads that same alternative, and saved contexts use the
same slot type. Whole-unit objdiff after the typed recovery: `.text` 51,176
bytes, `.data` 88 bytes, and `.bss` 1,392 bytes, all 100%; the linked DOL has
the original SHA-1. Direct numeric member reads keep the four affected handlers
exact without any added optimization pragma. Evidence and iteration details:
[pr308-typed-file-apis.md](evidence/pr308-typed-file-apis.md).

| Unit | Flags | What needs the fused multiply-adds | Original asm | Rest of the unit |
|---|---|---|---|---|
| `pso/player/TObjPlayer_801542CC.cpp` | `-fp_contract on` | `TObjPlayer__sub_8015434C` only. `body->center.x = body->offset.x * sine + pos.x` and `body->center.z = body->offset.z * cosine + pos.z`. | `fmadds f0, f1, f30, f0` at `0x80154408` (offset.x * sin + pos.x); `fadds f0, f1, f0` at `0x8015441C` (pos.y + offset.y, not fused); `fmadds f0, f1, f31, f0` at `0x8015442C` (offset.z * cos + pos.z). No `fmsubs` in this function. | Objdiff of the whole unit with the flag versus without it: the other 55 functions stay at the score they had without the flag (all exact), and `.bss`, `.data`, and `.sdata2` stay 100%. `resolve_actor_sphere_contact`'s `(x * x) + (z * z)` stays `fmuls` + `fadds`. The `fmadds` at `0x8015532C` and `0x8015533C` are in `resolve_player_box_contact`, from that function's existing `#pragma fp_contract on` (already on main), not from this override. Precedent: GC/Wii projects put `-fp_contract on` in the base flags ([dtk-template configure.py](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209)). `cflags_pso` omits it, so this one unit opts back in, the same kind of override as `TObjTombstone.cpp`. |
`TObjBoss2Tunnel.cpp`, `TObjBoss2Tunnel_8003B138.cpp`, and `TObjBoss2Tunnel_802F2070.cpp` set `-fp_contract on` because the curve and tunnel helpers fuse multiply-adds. Each unit stays byte-exact, which is why the flag is on the unit rather than a per-function `fp_contract` pragma. Precedent: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) and Melee, TP, TWW, and Pikmin 2, which contract globally.

### `TAdChrSelPlyPlateGC.cpp` ([#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/ui/TAdChrSelPlyPlateGC.cpp` | `TAdMultiPlyChrSelectGC__sub_802C5F1C`; also `mark_grid_cell_occupied` inlined into `sub_802C5688` and `sub_802C6660` | unit `-inline on,deferred` together with the `-fp_contract on` row below | The slot clamp is a `static inline` helper with no symbol of its own. Under `-inline off` the helper is a real call and the function is 332 bytes (42.79518%). Under `-inline on` the row stays in `r8` and the cell in `r7`, and the function is 236 bytes. `v0` and `v1` are `a / 256.0f` and `(lbl_805DE588 + a) / 256.0f`. MWCC folds that into `fmuls` by the pooled reciprocal at `805DE584` (exactly 1/256) with the dividend on the left. The same flag inlines `mark_grid_cell_occupied(row, col)`. `802C6660` passes `row + 1, col + 1` (its `row`/`col` are the 0-based quad indices); the inlined arguments are the `addi` before `mulli 0x14` and `stwx` at `0x802C67xx`. `802C5688` already holds grid coordinates and stays 700/700. `-inline auto` inlines other functions (`update` 108→572, `update_option_cursor` 476→700, `handle_dpad_input` 564→788). The original 36-function split matched with `-inline on` and `-fp_contract on`. The complete unit also uses deferred emission for the constructor. Evidence: [chr-select-slot-clamp-inline.md](evidence/chr-select-slot-clamp-inline.md), [chr-select-confirm-cell-store.md](evidence/chr-select-confirm-cell-store.md). Precedent: [Brawl `-inline on`](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) (only functions marked `inline`); [`-inline auto` in dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) was tried and does not keep this unit identical. | Drop the flag. The value is `min(slot, 3)` applied to each cell's texture row, and the occupied-cell store is `grid[row][col] = -1`. A port does not need MWCC's inline-local numbering. |
| `src/pso/ui/TAdChrSelPlyPlateGC.cpp` | Constructor at `0x802C6DD4` and whole-unit layout | deferred emission with definitions in reverse address order | The constructor shares the `.data` base at `0x804E0A48` for the native vtable at +0xC8 and the ready-tag arrays at +0x98 and +0xA8. Immediate emission addresses all three separately. Deferred emission with reversed definitions restores the instruction, relocation and pool order. See [plate constructor evidence](evidence/chr-select-confirm-cell-store.md#constructor-and-factory). | Use an ordinary C++ constructor and compiler-generated vtable. Function order and shared relocation bases are CodeWarrior layout details. |

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


### `text_8034A090.cpp`: `-fp_contract on`

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/unk/text_8034A090.cpp` | `TAdLoadQuestPrtTxtGC::TAdLoadQuestPrtTxtGC` (`0x8034A254`, 892 bytes) | unit `configure.py` override `-fp_contract on` | The constructor's three particle layouts contract `scale * index + base` into `fmadds` (case 0 at ctor+0x120, `ec 1d d8 3a`; the same form in cases 1 and 2). With the flag the unit is 1452/1452 code, 4/4 functions, `.rodata` 8 and `.data` 36. Without it those three functions and both data sections stay 100%, and the constructor falls to 93.32% and grows from 892 to 908 bytes (separate `fmul`/`fadd`). No `-inline` change was needed. Precedent: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) (`-fp_contract on`). | Keep fused multiply-add, or accept the float differences. |

### `TCheckMemoryCard.cpp` section placement

The native static initializer at `0x8033C69C` computes the card-menu position and layout
height, then initializes four pairs of `TCheckMemoryCard` member callbacks. CodeWarrior
emits the eight member-pointer templates between the menu position and the callback
table. The card vtable follows at `0x804EF9A0`. The initializer's text follows the card
methods and character-select factory, so a separate initializer unit would impose
opposite object orders in `.data` and `.text`. The combined unit preserves both orders,
as in the [calendar conversion fold](evidence/calendar-conversion-evidence.md).

- `-sdata 4` keeps the eight-byte menu position in `.data`, ahead of the callback
  templates, and retains the four-byte height in `.sbss`. With the default threshold,
  the menu position goes into `.sdata` and the initializer uses different offsets.
- `cw_align: .rodata=4` preserves the start of the two float pairs at `0x80477DB4`.
  CodeWarrior otherwise declares eight-byte section alignment. The existing
  `cw_comment_align.py` rule adjusts the ELF and CodeWarrior alignment metadata.

A port can use the C++ initializers and its normal section layout.

### `TOTrapAncient01.cpp` unit overrides ([#221](https://github.com/matthewlewisnewton/pso-decomp/pull/221))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TOTrapAncient01.cpp` | whole unit; `TOTrapAncient01::TOTrapAncient01`, `render`, `play_sounds` | `configure.py`: `mw_version` `GC/2.0`, `-inline off,deferred`, `-fp_contract on`, `-str reuse,readonly`, `-pooldata=off`, `-opt nolifetimes` | Every section of the object is byte-identical with all six settings; each row below is the score with only that setting removed. `GC/2.0`: `play_sounds` (`0x801794CC`, size `0x2B8`) builds three `const TObjChipParams` records from a `.rodata` template and `position`. The original loads `x`/`y`/`z` into `f2`/`f1`/`f0` before the template's tail `stw r0,4(r5)` (`lfs f2,0x38(r31)` at `+0x48`, `stw` at `+0x4C`, `lfs f1`/`lfs f0` at `+0x50`/`+0x54`, then three `stfs`). GC/2.6 stores the tail first and alternates `lfs`/`stfs`, which leaves the length unchanged but changes the bytes of all three records: `play_sounds` 91.09%, `.text` 98.32%. The sibling trap `TOExplosiveMachine.cpp` builds its debris records the same way and is GC/2.0 for the same reason. Precedent for a per-unit compiler version: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L257) (`GC/1.2.5n` and `GC/1.3.2` objects under a different linker version). `-fp_contract on`: the constructor's `0.5f * scale.x + 30.0f` is an `fmadds`. Without contraction, `TOTrapAncient01::TOTrapAncient01` is 98.86% and `render` 97.66%. Precedent: [dtk-template `configure.py`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209) and the same switch on `TWindowKeyBoardSoft_8024E68C.cpp`. `-inline off,deferred`: deferred emission keeps the vtable ahead of the switch tables and preserves the original function order. Without it, `.rodata` is 42.21%, `.data` 63.58%, and `.sdata2` 56.25%. Precedent for a unit `-inline` switch: [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) (`-inline auto`) and [brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264) (`-inline on`). `-opt nolifetimes`: `render` is 99.42% without it. Precedent for a unit `-opt nolifetimes`: [Petari `configure.py`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L2137). `-pooldata=off`: without it, `play_sounds` is 94.54% (the copy prologue becomes `stmw` instead of the original `stwu`/`stw r31`) and `.data` is 63.58%. Precedent for a unit `-pooldata off`: [FFCC-Decomp `configure.py`](https://github.com/zcanann/FFCC-Decomp/blob/48eec39b00014bac8ef9e585d2beb55f5ab6c68d/configure.py#L594) and [marioparty6 `configure.py`](https://github.com/iirg4x/marioparty6/blob/3be3802ab7c1c79e7060500f2aca0e85ad9962dd/configure.py#L1089). `-str reuse,readonly` drops the default `,pool`, so the strings stay in the read-only layout. Without it, `.rodata` is 75%, `.data` 61.97%, and `.sdata` 75%. Precedent: [FFCC-Decomp `configure.py`](https://github.com/zcanann/FFCC-Decomp/blob/48eec39b00014bac8ef9e585d2beb55f5ab6c68d/configure.py#L600) builds a unit with `-pooldata off` and `-str reuse,readonly`; [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L237) uses `-str reuse,pool,readonly` for its runtime libraries. `-opt nopropagation` is not set. | Build with the default compiler: keep contraction for the constructor's float result. The other settings change only scheduling and layout. |

### `TOTrapSeabed01.cpp` unit override ([#221](https://github.com/matthewlewisnewton/pso-decomp/pull/221))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TOTrapSeabed01.cpp` | whole unit | `configure.py`: `-inline deferred` in place of the default `-inline off`; definitions in reverse order | Every section of the object is byte-identical. The native `TOTrapSeabed01` vtable references TOTrap's inline slots 20, 21, 23 and 24, so this object emits weak copies of them. The linker keeps `TOTrap.o`'s copies. The original `.sdata2` at `0x805DE640` is `1.0, 0.0, 0.5, 15, 0.1, 10, 30`: the copies' `1.0f`/`0.0f` come first, then the unit's literals in function order. Deferred generation emits the copies first, and the reversed definitions in the original `.text` order. With the default `-inline off`, the copies are generated last: `.sdata2` is 71.43%, `.rodata` 50% (the two conversion constants swap), and `clamp_params_and_init` 69.32% because its clamp helpers are not inlined. `-inline off,deferred` fixes the pools but still leaves `clamp_params_and_init` at 69.32%. `-inline auto` loses `draw_object_tree` and `create` entirely (0%). The unit matches without its former per-function `fp_contract`, `opt_common_subs`, `inline_depth` and `dont_inline` pragmas, so they are removed. Precedent: the same switch on `TQuestVmDownLoadServer.cpp`, `TMedicalCenterSequence.cpp` and `TBoss7LaserLight.cpp`, and unit `-inline` switches in [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) and [brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264). | Ignore it: generation order has no semantic effect. |

### `TOTrapAncient02.cpp` unit override ([#221](https://github.com/matthewlewisnewton/pso-decomp/pull/221))

| File | Functions | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/misc/TOTrapAncient02.cpp` | whole unit | `configure.py`: `-inline deferred` in place of the default `-inline off`, and `-fp_contract on`; definitions in reverse order | Every section of the object is byte-identical. The unit defines `~TOTrapAncient02` and `~TOTrapAncient02R`, so it emits both native vtables in place of the former hand-written `s32[90]` table, its `extern "C"` alias for `vfunc_87__6TOTrapFf` and the C-named `__dt__15TOTrapAncient02Fv` with its raw vptr store. It also owns the ten `TOTrapAncient02R` methods at `0x8017B878`..`0x8017B9AC`, formerly split into `pso_const_ids7.cpp` and `text_8017B8A0.cpp`, and its `.sdata2` pool at `0x805DBA78` (`1.0, 2.0, 0.0, 7, 10.15, 0.00001, 240, 20, 1.8, 30, 0.5, 400`) as literals. The original `.data` is the three resource records and the collision body, the `TOTrapAncient02R` vtable at `0x804B4B4C`, `TOTrapAncient02::vfunc_84`'s switch table at `0x804B4CB4`, then the `TOTrapAncient02` vtable at `0x804B4D10`. The `TOTrapAncient02` vtable references TOTrap's inline slots 20, 21, 23 and 24, so this object emits weak copies of them, and the linker keeps `TOTrap.o`'s copies. Deferred generation emits the `TOTrapAncient02R` vtable before any function, so before the switch table, and the reversed definitions keep the original `.text` order. With the default `-inline off`, `.data` is 90.09%, `.sdata2` 70.83%, and `vfunc_84` 99.79% because its switch-table relocation moves, along with most other functions at about 99.8%. Unit `-fp_contract on` replaces the seven per-function `fp_contract on` pragmas from main: without it `.text` is 99.5% (`calc_trap_count` 94.74%, `TOTrapAncient02R::vfunc_81` 99.38%, both constructors about 98%) because their multiply-adds stay unfused; no function in the unit needs it off. Precedent: the `TOTrapSeabed01.cpp` entry above, the same switch on `TQuestVmDownLoadServer.cpp`, `TMedicalCenterSequence.cpp` and `TBoss7LaserLight.cpp`, unit `-inline` switches in [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) and [brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264), and unit `-fp_contract on` on `TWindowKeyBoardSoft_8024E68C.cpp` and in [dtk-template](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L209). | Ignore them: generation order has no semantic effect, and the unit's fused multiply-adds are the ones its pragmas already selected. |

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

Linking `TObjBoss2Tunnel_802F2070.cpp` also needs `cw_align` (`.sbss=4 .sdata2=4` in `configure.py`, applied by `tools/cw_comment_align.py`). mwld places small data using the alignment stored in the CodeWarrior `.comment` record. GC/2.6 writes 8 there, and `-sdata 4` does not change it, so `.sbss` (original start `0x805D696C`) and `.sdata2` (original start `0x805DECCC`) were each inserted 4 bytes late. That one pad shifted the rest of `.sdata2` and every `sda21` offset that follows. The script rewrites the comment record and `sh_addralign` after compile; the section bytes are unchanged. Objdiff stays at 100% either way, because it matches relocations symbolically.

### `-opt nolifetimes,nocse,noprop,noloop`: `TMovie_80143988.cpp` ([#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167))

| Unit | Function | What | Why | Port should |
|---|---|---|---|---|
| `pso/misc/TMovie_80143988.cpp` | `pack_movie_frame` (`0x80143988`, 564 bytes; the only function in the unit) | unit switch `-opt nolifetimes,nocse,noprop,noloop` | The original keeps each named local in one register for the whole function: the packed word is built in place in `r25`, and `mr r24, r25` copies it for the second scanline before every luma insert (`0x80143A4C`, `0x80143A70`, ... eight times). The cache-touch offset is the single `li r0, 0x20` hoisted to the entry (`0x8014398C`) and reused by both `dcbt r31, r0` / `dcbt r9, r0` (`0x80143A30`, `0x80143ADC`). The pad scales are recomputed late in the entry (`slwi r5, r25, 2` ... `slwi r3, r24, 2`, `0x80143A18`–`0x80143A20`). Without `nolifetimes` the unit is 53.40% (568 bytes, `stmw r21`). Without `noprop`, `touch` is propagated as a constant: 70.50%, 596 bytes. Without `nocse` or `noloop` the shared stride and pad shifts become frontend temps coloured in the wrong order: 93.06%, 564 bytes. With the switch, `.text` (564 bytes), relocations and symbols match the target object. The source is plain C++ (no `__rlwinm`/`__rlwimi`); only `__dcbt` (section 2) remains. Precedent: Petari uses these keywords per object: [`-opt nolifetimes,nocse,noprop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L3735), [`-opt nolifetimes,noloop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L2974), [`-opt noloop`](https://github.com/SMGCommunity/Petari/blob/50c1eae28478c8b1b1c8708ab8ce9a3b845ee6c6/configure.py#L1532). SFA uses [`-opt nolifetimes`](https://github.com/zcanann/SFA-Decomp/blob/f561e933ecc7356259bccdd6a7ce9a4462a950a0/configure.py#L1586). This repo already has `-opt noprop` and `-opt nocse` units. Evidence: [pack-movie-frame-unit-flags.md](evidence/pack-movie-frame-unit-flags.md). | Drop the switch. The source is plain C++; drop the cache touch too. |

### `TObjEneMoja.cpp`: `-inline off,deferred`

The loader at `0x800AF56C` uses a shared `.data` base for the two BML descriptors, action table and collision body. With a single external struct view, CodeWarrior folds two subobject offsets into their loads and emits a 680-byte function. Defining the individual tables in the same translation unit restores the two address instructions and the original 688 bytes.

The Moja vtable at `0x804919BC` lies between those tables and the `run_task` switch table at `0x80491B08`. Moving only the resource tables into the loader creates a cycle because the code for `run_task` precedes the loader while its switch table follows the resource tables. The consolidated unit owns both tables and generates the vtable from the real destructor. Immediate compilation puts the switch table before the vtable. Reverse definitions with `-inline off,deferred` preserve both the function order and the original data order.

Ports can drop the compiler switch. The render and target-acquisition bodies in `TObjPlayer_800ACA60.cpp` are ordinary `TObjEneMoja` members (`render`, and `vfunc_28` — the `TObjChara` override name for acquire_target).

### `TBoss8Dragon.cpp`: `-inline off,deferred` ([#302](https://github.com/matthewlewisnewton/pso-decomp/pull/302))

| Unit | Functions | What | Why | Port should |
|---|---|---|---|---|
| `pso/boss/TBoss8Dragon.cpp` | `TBoss8Dragon::TBoss8Dragon` (`__ct__12TBoss8DragonFP7TObjectPv`, `0x802FD47C`, 0x554) and the compiler vtable `__vt__12TBoss8Dragon` (`0x804E5534`) | unit switch `-inline off,deferred` | The constructor stores the vptr with `addi r0, r31, 2348` off the `.data` anchor (`TBoss8Dragon__camera_offset_index_table` at `0x804E4C08`). Under plain `-inline off` that store is `lis`/`addi` of `__vt__12TBoss8Dragon` and the function is 0x558. Deferred code generation restores the anchor form and places the 107-slot compiler vtable at `.data+0x92C`. The destructor, `create`, and the other functions keep the same instructions; only their order in the object follows deferred emission. Precedent: [dtk-template `-inline auto`](https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203) was not needed; this is the `-inline off,deferred` form already used for `TObjEneGyaranzo.cpp` and [the per-group inline settings in brawl](https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264). `-inline auto,deferred` was tried in an earlier pass and rewrote 56 functions. | Drop the switch. Emission order has no semantic effect. |

### `TAdChrSelPlyPlateGC.cpp`: `-fp_contract on` ([#214](https://github.com/matthewlewisnewton/pso-decomp/pull/214), folded by [#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250))

| File | Function | What | Why | Port should |
|---|---|---|---|---|
| `src/pso/ui/TAdChrSelPlyPlateGC.cpp` | `sub_802C50EC` (`fmadds` at `0x802C5148`), `sub_802C522C` (`0x802C5274`), `sub_802C5688` (`0x802C58AC`), `sub_802C6660` (`0x802C676C`) | unit `-fp_contract on`, together with the `-inline on,deferred` rows above | The original unit has one `fmadds` in each of those four functions, so the whole unit was built with contraction on. Main had `#pragma fp_contract on` around the first two only; the unit flag replaces that pragma. Without contraction, `sub_802C50EC` drops to 97.81%, `sub_802C522C` to 96.98%, `sub_802C5688` to 98.03%, and `sub_802C6660` to 93.89%. With both unit flags, every function and section matches. Precedent: [#219](https://github.com/matthewlewisnewton/pso-decomp/pull/219) (`TWindowKeyBoardSoft_8024E68C.cpp`, above) and `TObjTombstone.cpp`, both unit `-fp_contract on`. | Keep fused multiply-add, or accept small float differences. |

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

### Technique controller recovered from upstream #208

| Unit / scope | What | Why | Port should |
|---|---|---|---|
| `pso/misc/TTecCtrl.cpp` | `-fp_contract on`, `-inline on,deferred`; existing scoped `opt_propagation off` in the folded charge-light function | Fused parameter scaling, inline global-load order and vtable/switch-table emission order reproduce the native object. [Evidence](evidence/upstream-technique-control.md). | Drop optimizer steering; retain fused arithmetic if identical floating-point results are needed. |
| Parameter calculator and folded native interfaces | Provisional `pad_*` parameter fields, TTecAnti receiver cast over parameter storage, explicit mangled names, legacy actor/light function-pointer casts and raw offset views | Existing interface/layout assumptions from upstream and the fork remain bounded native recovery debt. | Use typed parameter copy/free functions, consolidate actor/light signatures and recover field meanings. |

The former `TTecCtrl_8022C444.cpp` conversion-pool post-process is retired.
Folding its readers into one object allows the compiler to emit local biases
without symbol rewriting. The old hand-written TTecCtrl vtable is also removed;
the class destructor emits it. [Historical evidence](evidence/conversion-pool-constants.md).

### Footprint unit recovered from upstream #208

| Unit | Compiler settings | Reason and port action |
|---|---|---|
| `pso/misc/TPlayerFootStamp.cpp` | `-fp_contract on`, `-inline off,deferred`, `-str reuse,readonly` | Adapted from upstream [#208](https://github.com/zeroz41/pso-decomp/pull/208), `ae797d392`. Removing fusion drops the constructor to 90.710144%; removing deferred emission changes function/vtable/switch/constant order (`.data` 33.333332%, `.sdata2` 14.285715%); writable strings move the class name (`.rodata` 95.38461%, `.sdata` 50%). All settings together give an exact, linked unit. A port can drop the flags, retaining explicit fused arithmetic if its results are required. [Evidence and remaining API boundaries](evidence/upstream-footstamp.md). |

### Sprite frame draw recovered from upstream #208

| Unit | Compiler settings | Reason and port action |
|---|---|---|
| `pso/misc/TLobby_80228154.cpp` | `mw_version` GC/1.3.2 | Adapted from upstream [#208](https://github.com/zeroz41/pso-decomp/pull/208), `ae797d392`, which links the unit exact under GC/1.3.2. `TLobby__sub_80228154` (`0x80228154`, sprite frame draw) is plain C++: no asm, casts or pragmas. Under GC/2.6 the unit's `.text` is 1720 bytes instead of 1732 (the sprite draw's frame and flag tests come out shorter); under GC/1.3.2 every section and relocation is identical to upstream's linked object. The unit's other functions are unchanged fork code. Build with the port compiler. |

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

Matt, 2026-11-05 10:17 AM PT, on [#302](https://github.com/matthewlewisnewton/pso-decomp/pull/302): register the named
`__ct__17AccelerationCurveFv` calls and the hand table `lbl_80481280` on `TBoss1Dragon__ct`, and stop trying to
replace those sites with a real constructor. A real `TBoss1Dragon` constructor matches the `addi`/`bl` only with
`-inline off,deferred`, which reverses emission order in that linked unit. The named calls are this PR's rename of
`reset_coords_pass`, not unchanged upstream text. The compiler-vtable / real-destructor alternative does not match
the DOL homes (`mr. r31, r3` / `mr r30, r4`; a real `~T()` is `mr. r30, r3` / `mr r31, r4`). This approval is only
those sites. It does not cover any other function, cast, or hand table. The two rows below record that decision in
this table; their upstream column is [#191](https://github.com/zeroz41/pso-decomp/pull/191) because that is the
catch-up this branch integrates, not because those lines appear unchanged in #191.


Matt, 2026-11-09, authorized this carrier after the #207 exception-scope limitation
was identified: "Skip the license change (or don’t, the two are equivalent) and merge
the rest." He also requested documentation of outstanding inherited cheats. This
adds only the #207 sites below to the catch-up scope; it does not grant a blanket
exception to #193–#228. Some listed constructs already existed in these three fork
units before this carrier; they are included because the units now link from source.
The #207 source uses the fork's existing include paths and symbol names. The explicit
BmlResource constructor symbol is the fork spelling of upstream's
`load_resource_from_descriptor`; real `StripBufferPair` construction replaces the
old `TLobby::alloc_tables` calls. Reasons, measured alternatives, port guidance, and
deferred upstream work are in [the carrier audit](evidence/upstream-catchup-207.md).

Columns (all required; `tools/list_port_exceptions.py --check` validates them):
function/symbol; unit; file (repo path); upstream PR (#167-#192 or the specifically authorized #207 sites); cheat type (`asm`,
`raw offset cast`, `extern "C" mangled name`, `steering pragma`, `shadow struct`,
or `other: <what>`); the fork PR that brought it in; and the tag
`upstream catch-up, rewrite later`. List and count them with
`python3 tools/list_port_exceptions.py --upstream-catchup`; check_pr prints the count.

| Function/symbol | Unit | File | Upstream PR | Cheat type | Fork PR | Tag |
|---|---|---|---|---|---|---|
| `subtract_vector` | `pso/math/MatrixTransforms.cpp` | `src/pso/math/MatrixTransforms.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `matrix_apply_translation` | `pso/unk/text_803D9650.cpp` | `src/pso/unk/text_803D9650.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `transform_point_by_current_matrix` | `pso/unk/text_803D96A8.cpp` | `src/pso/unk/text_803D96A8.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `rotate_vector_by_current_matrix` | `pso/unk/text_803D96A8.cpp` | `src/pso/unk/text_803D96A8.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `rotate_matrix_by_node_angles` | `pso/unk/text_803D96A8.cpp` | `src/pso/unk/text_803D96A8.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `push_matrix` | `pso/unk/text_803D96A8.cpp` | `src/pso/unk/text_803D96A8.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `scale_current_matrix` | `pso/unk/text_803D96A8.cpp` | `src/pso/unk/text_803D96A8.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `post_translate_matrix` | `pso/unk/text_803D96A8.cpp` | `src/pso/unk/text_803D96A8.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `sin_table_lookup` | `pso/unk/text_803D647C.cpp` | `src/pso/unk/text_803D647C.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `cos_table_lookup` | `pso/unk/text_803D647C.cpp` | `src/pso/unk/text_803D647C.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `convert_color_f32_to_u8` | `pso/misc/TCameraCtrl_803D749C.cpp` | `src/pso/misc/TCameraCtrl_803D749C.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `convert_color_u8_to_f32` | `pso/misc/TCameraCtrl_803D749C.cpp` | `src/pso/misc/TCameraCtrl_803D749C.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | asm | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TCameraCtrl::update_projection_params` `#pragma use_lmw_stmw off` | `pso/misc/TCameraCtrl_803D66DC.cpp` | `src/pso/misc/TCameraCtrl_803D66DC.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TCameraCtrl::update_projection_params` `#pragma opt_common_subs off` | `pso/misc/TCameraCtrl_803D66DC.cpp` | `src/pso/misc/TCameraCtrl_803D66DC.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `set_perspective_projection_from_fov` `#pragma use_lmw_stmw off` | `pso/misc/TCameraCtrl_803D676C.cpp` | `src/pso/misc/TCameraCtrl_803D676C.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `sample_camera_motion` `#pragma use_lmw_stmw off` | `pso/misc/TCameraCtrl_803D6960.cpp` | `src/pso/misc/TCameraCtrl_803D6960.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `interpolate_motion_vector_keys` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6960.cpp` | `src/pso/misc/TCameraCtrl_803D6960.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `interpolate_motion_vector_keys_xy` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6960.cpp` | `src/pso/misc/TCameraCtrl_803D6960.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TObjPlayer::interpolate_motion_key` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6960.cpp` | `src/pso/misc/TCameraCtrl_803D6960.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `sample_motion_angle_keys` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6960.cpp` | `src/pso/misc/TCameraCtrl_803D6960.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `sample_motion_angle_keys_s16` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6960.cpp` | `src/pso/misc/TCameraCtrl_803D6960.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TCameraCtrl::translate_view_negated` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6538.cpp` | `src/pso/misc/TCameraCtrl_803D6538.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `set_camera_look_at` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6538.cpp` | `src/pso/misc/TCameraCtrl_803D6538.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TCameraCtrl::set_clamped_offsets` `#pragma opt_common_subs off` | `pso/misc/TCameraCtrl_803D6538.cpp` | `src/pso/misc/TCameraCtrl_803D6538.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TCameraCtrl::set_clamped_offsets` `#pragma scheduling off` | `pso/misc/TCameraCtrl_803D6538.cpp` | `src/pso/misc/TCameraCtrl_803D6538.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `multi_chg_game_mode_window_extent` | `pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp` | `src/pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | other: __declspec(section ".data") | [#351](https://github.com/matthewlewisnewton/pso-decomp/pull/351) | upstream catch-up, rewrite later |
| `lbl_804F3A18` | `pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp` | `src/pso/ui/TAdMultiChgGameModeGC_8036DE10.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | other: __declspec(section ".data") | [#351](https://github.com/matthewlewisnewton/pso-decomp/pull/351) | upstream catch-up, rewrite later |
| `TObjDFDemo1.cpp:149` `#pragma defer_codegen on` | `pso/object/TObjDFDemo1.cpp` | `src/pso/object/TObjDFDemo1.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#351](https://github.com/matthewlewisnewton/pso-decomp/pull/351) | upstream catch-up, rewrite later |
| `TObjDFDemo1.cpp:204` `#pragma fp_contract on` | `pso/object/TObjDFDemo1.cpp` | `src/pso/object/TObjDFDemo1.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#351](https://github.com/matthewlewisnewton/pso-decomp/pull/351) | upstream catch-up, rewrite later |
| `configure.py:440` `-sdata 4` | `pso/object/TObjDFDemo1.cpp` | `configure.py` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | other: per-unit cflags override | [#351](https://github.com/matthewlewisnewton/pso-decomp/pull/351) | upstream catch-up, rewrite later |
| TObjEneDubchik.cpp | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | other: unit flags -inline off,deferred and -str reuse,readonly | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik.cpp:166 inline_depth | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik.cpp:167 auto_inline | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik.cpp:168 dont_inline | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA82C:547 opt_common_subs | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA82C:548 opt_propagation | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::render:707 opt_common_subs | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Vec_800A9C38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VBase_800AA704 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VObj_800AA704 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VBase_18_fe09eb | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VObj_18_fe09eb | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Mdl_800AA82C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Res_800AA82C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Node_800AA82C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Desc_800AA82C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Base_Sub | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| V_Sub | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Obj_800AA528 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Obj_800A8A7C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Vec_800A8C4C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VBase_14_fddec9 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VObj_14_fddec9 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VBase_18_ca64a0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VObj_18_ca64a0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Self_800AA334 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Ids_800AA82C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Vec_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Pair_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VB_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| VO_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Params_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| Ene_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| T_800AAF98 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| O_800AAF98 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| PADV/PADV4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | other: hand-padded virtual stubs | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AAF98 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| queue_destruction__7TObjectFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| __ct__13TUnk_80491460FPvlll | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| render_anim_model_at_pos__15TObjEnemyCustomFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| __nw__7TObjectFUl | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| __dt__11BmlResourceFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| __ct__11BmlResourceFlP21BmlResourceDescriptorllPv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A4294 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA82C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8E04 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AB7A0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA330 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| obj_testFlags30__14TObjCollidableFUl | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AAFF0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A93E4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| defer_render__7TObjectFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| random_ratio__9TObjCharaFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| find_target_in_range__15TObjEnemyCustomFf | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| sub_8004292C__15TObjEnemyCustomFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| update_shock_clock__9TObjCharaFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| update_movement_status__9TObjCharaFv | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AB068:437 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AB068:437 0x44 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AB068:437 0x40 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AB068:437 0x4C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AB068:439 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer::set_invuln_flags:449 0x18 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer::clear_flag_04000000:457 0x18 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer::clear_flag_04000000:461 0x8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AAF78:493 0x3C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AAF78:494 0x3E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AAF78:523 0xA | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA82C:566 0x1C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA82C:572 0x18 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800AA82C:577 0x18 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::run_task:671 0x338 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::render:727 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::render:732 0x34 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AA10C:785 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AA10C:792 0x354 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AA10C:795 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AA10C:803 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800AA10C:803 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:823 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:827 0x388 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:829 0x380 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:831 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:834 0x368 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:836 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:838 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:840 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:842 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:843 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:845 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:846 0x29C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:846 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:846 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:851 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:853 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:856 0x368 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:858 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:860 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:865 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:870 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:871 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:872 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:875 0x368 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:878 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:878 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:881 0x3A4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9E9C:882 0x308 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:896 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:899 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:901 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:902 0x60 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:903 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:904 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:905 0x3CC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:907 0x30 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:911 0x3CC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:915 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:916 0x308 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:917 0x310 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:921 0x308 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:921 0x310 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:924 0x308 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:925 0x310 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:926 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:927 0x308 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:927 0x310 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:928 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:936 0xC0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:939 0xB4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:940 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:944 0x384 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:945 0x384 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:946 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:952 0x388 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:953 0x33E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A9C38:953 0x32C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A93E4:1116 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1171 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1173 0x39C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1175 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1178 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1178 0x354 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1179 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1180 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1184 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1187 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1190 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1192 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1195 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1197 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1199 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1200 0x29C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1200 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1200 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1201 0x350 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1208 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1209 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1212 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1217 0x410 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1218 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1218 0x410 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1219 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1220 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1224 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1225 0x29C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1225 0x2A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1225 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1226 0x350 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1232 0x410 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1233 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1234 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1234 0x410 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1236 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1238 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1241 0x410 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1241 0x60 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1243 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1244 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1245 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1246 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1248 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1256 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1257 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1263 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1264 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1266 0xB4 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1267 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1268 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1275 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1276 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1277 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1284 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1285 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1286 0x38E | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1287 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1290 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1295 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1296 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8FB4:1297 0x3A8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer::update_timed_state:1324 0x33A | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8E04:1336 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8E04:1337 0x3B0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8E04:1340 0x3B0 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1355 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1360 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1363 0x368 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1365 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1367 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1369 0x29C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1369 0x50 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1370 0x37C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1377 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1380 0x368 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1382 0x290 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1382 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1383 0x290 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1383 0x29C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1384 0x308 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1386 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1386 0x50 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1387 0xB8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer__sub_800A8C4C:1389 0x388 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_start_dying:1397 0x388 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8B8C:1405 0x318 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8B8C:1405 0x392 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8A7C:1418 0x68 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8A7C:1420 0x68 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8A7C:1423 0x78 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8A7C:1425 0x78 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8A7C:1428 0xA8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjEneDubchik::sub_800A8A7C:1430 0xA8 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TObjPlayer::set_flag_start_effect:1469 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1476 0x33C | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1481 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1485 0x38 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1487 0x24 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1487 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1487 0x60 | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| dubchik_update_dying:1490 0x2FC | pso/enemy/TObjEneDubchik.cpp | src/pso/enemy/TObjEneDubchik.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TLobby__sub_80146314 `(char *)&lbl_8050CCE8 + 0x7C` | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TLobby__sub_80146314 `(char *)&lbl_8050CCE8 + 0xFC` | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | raw offset cast | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TLobby__sub_80146314 `send_and_handle__6TLobbyFv` | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TLobby__sub_8014734C `send_and_handle__6TLobbyFv` | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TLobby__sub_80146314 `func_801A5E54__Fv` | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TLobby__sub_8014734C `func_801A5E54__Fv` | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | extern "C" mangled name | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| AccountEntry, NetConnectCfg, NetLinkStatus, ModemDialConfig | pso/misc/TLobby_801461EC.cpp | src/pso/misc/TLobby_801461EC.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | shadow struct | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| `TNpcPlayer.cpp` | `pso/misc/TNpcPlayer.cpp` | `configure.py` | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | `other: per-unit cflags override` | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| `is_small_obstacle` | `pso/misc/TNpcPlayer.cpp` | `src/pso/misc/TNpcPlayer.cpp` | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | `other: dead function for sdata2 pool order` | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| `is_hp_low` | `pso/misc/TNpcPlayer.cpp` | `src/pso/misc/TNpcPlayer.cpp` | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | `other: dead function for sdata2 pool order` | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:2410 fp_contract (calc_follow_goal) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:2582 opt_common_subs (deliver_partner_action) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:2805 fp_contract (partner_observe_surroundings) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:2865 fp_contract (select_path_waypoint__10TNpcPlayerFv) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3001 opt_common_subs (needs_movement__10TNpcPlayerFPvPvi) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3002 opt_propagation (needs_movement__10TNpcPlayerFPvPvi) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3038 fp_contract (check_movement_progress) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3260 fp_contract (refresh_npc_view_actor_lost) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3463 fp_contract (partner_route_around_wall) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3464 opt_common_subs (partner_route_around_wall) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3522 fp_contract (partner_compute_stalled_detour) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3568 fp_contract (route_around_object__10TNpcPlayerFv) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| TNpcPlayer.cpp:3769 fp_contract (partner_clip_path_point) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | steering pragma | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| `refresh_npc_view_actor_lost` (TNpcPlayer.cpp:3268 `__cntlzw`) | pso/misc/TNpcPlayer.cpp | src/pso/misc/TNpcPlayer.cpp | [#190](https://github.com/zeroz41/pso-decomp/pull/190) | other: compiler intrinsic | [#354](https://github.com/matthewlewisnewton/pso-decomp/pull/354) | upstream catch-up, rewrite later |
| `advance_rng__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `advance_rng__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8023F754` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_2a4__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_2a4__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_0x280__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_0x280__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_menu_index__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_menu_index__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_mode__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_mode__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_clamped_field27c__6TLobbyFPvf` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_clamped_field27c__6TLobbyFPvf` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8023F880` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8023F880` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: reused local | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `fade_out_sound_slot` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `fade_out_sound_slot` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_sound_slot_pitch` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `alloc_looping_sound_slot` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `alloc_one_shot_sound_slot` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `resolve_sound_effect_bank` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `resolve_sound_effect_bank` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `is_ready__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `is_ready__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8023FCC0` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `reset_sound_group_fade__6TLobbyFv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `fade_voice_channels__6TLobbyFi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `fade_voice_channels__6TLobbyFi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8023FFB8` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8023FFB8` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update_sound_frame` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: absolute address | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `reset_sound_state__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `reset_sound_state__6TLobbyFPv` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_sound_aux_effects` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_sound_aux_effects` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_sound_aux_effects` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: pointer-to-int cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `pop_sound_groups__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `pop_sound_groups__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `pop_sound_groups__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `validate_and_set_selection__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `validate_and_set_selection__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `validate_and_set_selection__6TLobbyFPvi` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_80240808` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `reset_sound_owner_state` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update_crc16_ccitt__6TLobbyFUsUc` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Range_8023FBBC` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Owner_8023FBBC` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Ent_8023FCC0` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Obj_8023FCC0` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Slot_802405B0` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Mgr_802405B0` | `pso/misc/TLobby_8023F734.cpp` | `src/pso/misc/TLobby_8023F734.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_field0__6TLobbyFPvi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_field0__6TLobbyFPvi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `clamp_field9c__6TLobbyFPvf` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `clamp_field9c__6TLobbyFPvf` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_802409E4` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `set_voice_pitch_slide` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `tick_sound_voice` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update_random_flip_flag__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update_random_flip_flag__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `update_random_flip_flag__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_80241798` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `send_voice_controller_updates` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `clamp_params__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `clamp_params__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_sound_voice__6TLobbyFPviiii` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_sound_voice__6TLobbyFPviiii` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_sound_voice__6TLobbyFPviiii` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `__dt__17SoundRequestVoiceFv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `__ct__17SoundRequestVoiceFv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_308__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_308__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_field_308__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `forward_8024273C__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `forward_8024273C__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `send_find_user_self_tag__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `send_find_user_self_tag__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `send_find_user_self_tag__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `load_selected_guild_card_record` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_802422EC` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `find_and_load_com_card__6TLobbyFUi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `find_and_load_com_card__6TLobbyFUi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `find_and_load_com_card__6TLobbyFUi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `copy_com_card_entry__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `copy_com_card_entry__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_com_card_entry__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_com_card_entry__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `parse_csv_token__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `parse_csv_token__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `skip_to_comma_field__6TLobbyFPvii` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `skip_to_comma_field__6TLobbyFPvii` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `build_text_from_comma_list__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `build_text_from_comma_list__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8024259C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | steering pragma | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8024259C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_player_entry__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_player_entry__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_player_entry__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `init_player_entry__6TLobbyFPvPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `remove_com_card_entry__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `remove_com_card_entry__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `remove_com_card_entry__6TLobbyFi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_8024273C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `remove_com_card_by_id__6TLobbyFUi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `remove_com_card_by_id__6TLobbyFUi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: function-pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `remove_com_card_by_id__6TLobbyFUi` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: receiver cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `reset_state_805D63DC__6TLobbyFv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `reset_state__6TLobbyFPv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `construct_entry_arrays__6TLobbyFv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_802428C4` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby__sub_802428F8` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | raw offset cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `get_com_card_data__6TLobbyFv` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | extern "C" mangled name | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Entry_8024220C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Src_8024220C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Voice_80241FD8` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Ctl_80240B64` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Params_80240B64` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Owner_80241798` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Sound_80241798` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Tag_802421C4` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Pair_80242380` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Ext_80242380` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `Entry_80242380` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `RecoveredGlobal_8024259C_TLobby__data_8050AAAC` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `RecoveredGlobal_802426E8_lbl_80517F9C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `RecoveredGlobal_8024287C_lbl_80517EE0` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `RecoveredGlobal_8024287C_lbl_80517F9C` | `pso/misc/TLobby_802409AC.cpp` | `src/pso/misc/TLobby_802409AC.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | shadow struct | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `TLobby::set_read_params` | `pso/misc/TLobby_800F8AA8.cpp` | `src/pso/misc/TLobby_800F8AA8.cpp` | [#188](https://github.com/zeroz41/pso-decomp/pull/188) | other: pointer cast | [#355](https://github.com/matthewlewisnewton/pso-decomp/pull/355) | upstream catch-up, rewrite later |
| `clear_sound_listener_position` | `pso/misc/TLobby_802268F4.cpp` | `src/pso/misc/TLobby_802268F4.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | other: dead-stripped function | [#352](https://github.com/matthewlewisnewton/pso-decomp/pull/352) | upstream catch-up, rewrite later |
| `__vt__25TObjCityMainWarpChallenge` | `pso/object/TObjCityMainWarpChallenge.cpp` | `src/pso/object/TObjCityMainWarpChallenge.cpp` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | other: hand-written vtable | [#352](https://github.com/matthewlewisnewton/pso-decomp/pull/352) | upstream catch-up, rewrite later |
| `TObjCityMainWarpChallenge.cpp` | `pso/object/TObjCityMainWarpChallenge.cpp` | `configure.py` | [#183](https://github.com/zeroz41/pso-decomp/pull/183) | other: per-unit cflags override | [#352](https://github.com/matthewlewisnewton/pso-decomp/pull/352) | upstream catch-up, rewrite later |
| TLobby_80228818.cpp:391 opt_propagation (`render__14TUnk_804CC048Fv`) | pso/misc/TLobby_80228818.cpp | src/pso/misc/TLobby_80228818.cpp | [#192](https://github.com/zeroz41/pso-decomp/pull/192) | steering pragma | [#360](https://github.com/matthewlewisnewton/pso-decomp/pull/360) | upstream catch-up, rewrite later |
| `TObjPlayer::apply_status_effect` | `TObjPlayer_801542CC` | `src/pso/player/TObjPlayer_801542CC.cpp` | [#171](https://github.com/zeroz41/pso-decomp/pull/171) | other: s32-to-pointer cast | #305 | upstream catch-up, rewrite later |
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
| `TBoss1Dragon__ct` (`0x80029DE4`): `extern "C" void __ct__17AccelerationCurveFv` and the two calls `(AccelerationCurve *)(arg0 + 0x5F4)` and `(arg0 + 0x618)`. Matt, 2026-11-05 10:17 AM PT: do not replace these with a real constructor. It matches only under `-inline off,deferred`, which reverses this linked unit. The calls are this PR's rename of `reset_coords_pass` | `pso/boss/TBoss1Dragon.cpp` | `src/pso/boss/TBoss1Dragon.cpp` | [#191](https://github.com/zeroz41/pso-decomp/pull/191) | extern "C" mangled name | [#302](https://github.com/matthewlewisnewton/pso-decomp/pull/302) | upstream catch-up, rewrite later |
| `lbl_80481280` (`.data` `0x80481280`, 107 pointers) and its stores in `TBoss1Dragon__ct` (`+0x18`) and `destroy__12TBoss1DragonFPvs`. Matt, 2026-11-05 10:17 AM PT: a compiler vtable and real destructor do not match the DOL r31/r30 homes. Only this table | `pso/boss/TBoss1Dragon.cpp` | `src/pso/boss/TBoss1Dragon.cpp` | [#191](https://github.com/zeroz41/pso-decomp/pull/191) | other: hand-written vtable | [#302](https://github.com/matthewlewisnewton/pso-decomp/pull/302) | upstream catch-up, rewrite later |
| `TBoss6Rock::run_task` | `pso/boss/TBoss6Rock.cpp` | `src/pso/boss/TBoss6Rock.cpp` | [#181](https://github.com/zeroz41/pso-decomp/pull/181) | `other: u64 pointer widen` | [#313](https://github.com/matthewlewisnewton/pso-decomp/pull/313) | upstream catch-up, rewrite later |
| `LaunchDol` | `pso/unk/text_8042E8C4.cpp` | `src/pso/unk/text_8042E8C4.cpp` | [#172](https://github.com/zeroz41/pso-decomp/pull/172) | asm | [#350](https://github.com/matthewlewisnewton/pso-decomp/pull/350) | upstream catch-up, rewrite later |
| `TEffStarLight2D` `#pragma defer_codegen on` | `pso/effect/TEffStarLight2D_Base.cpp` | `src/pso/effect/TEffStarLight2D_Base.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `TObjDFDemo5` `#pragma defer_codegen on` | `pso/object/TObjDFDemo5.cpp` | `src/pso/object/TObjDFDemo5.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | steering pragma | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |
| `__ct__20TAdLoadQuestPrtTxtGCFP7TObjectl` | `pso/unk/text_8034A090.cpp` | `src/pso/unk/text_8034A090.cpp` | [#180](https://github.com/zeroz41/pso-decomp/pull/180) | extern "C" mangled name | [#361](https://github.com/matthewlewisnewton/pso-decomp/pull/361) | upstream catch-up, rewrite later |


| `RecoveredGlobal_8001B3BC_lbl_804F5800` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `RecoveredGlobal_8001B3EC_lbl_804F5800` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `RecoveredGlobal_8001B3D4_lbl_804F5800` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `RecoveredGlobal_8001B404_lbl_804F5800` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Pos_8001AD8C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Box_8001AD8C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Self_8001AD8C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Pos_8001AF80` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Box_8001AF80` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Self_8001AF80` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Box_8001B190` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Self_8001B190` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText.cpp:137 #pragma readonly_strings on` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | steering pragma | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText__ending_font_texture_list` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".data") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText.cpp:311 #pragma fp_contract on` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | steering pragma | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_804347B0` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".rodata") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_804347C0` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".rodata") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7DF0` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7DF4` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText__data_805D7DF8` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7DFC` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E00` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E04` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E08` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E0C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E10` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E14` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E18` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E1C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E20` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E24` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E28` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E2C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E30` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E34` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E38` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E3C` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `lbl_805D7E40` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: __declspec(section ".sdata2") | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `Obj_80185160` | `pso/unk/text_80184C2C.cpp` | `src/pso/unk/text_80184C2C.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `VBase_802A2A00` | `pso/unk/text_802A2A00.cpp` | `src/pso/unk/text_802A2A00.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TChCrTag_802A2A00` | `pso/unk/text_802A2A00.cpp` | `src/pso/unk/text_802A2A00.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | shadow struct | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `text_802A2A00.cpp:17 #pragma fp_contract on` | `pso/unk/text_802A2A00.cpp` | `src/pso/unk/text_802A2A00.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | steering pragma | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `render__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | extern "C" mangled name | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `run_task__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | extern "C" mangled name | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `__ct__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | extern "C" mangled name | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `__ct__7TObjectFP7TObject` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | extern "C" mangled name | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `__vt__10TAdEndText assignment in __ct__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: explicit compiler-vtable pointer assignment | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `render__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `run_task__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `__ct__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText__sub_8001B3BC` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText__sub_8001B3D4` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText__sub_8001B3EC` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText__sub_8001B404` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText::free_resources` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: pointer stored in 32-bit integer ABI | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText::load_ending_font` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: pointer stored in 32-bit integer ABI | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `__cvt_fp2unsigned in render__10TAdEndTextFv` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: CodeWarrior conversion runtime helper | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TAdEndText::~TAdEndText placement` | `pso/menu/TAdEndText.cpp` | `src/pso/menu/TAdEndText.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: source ordering for compiler vtable emission | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TLobby__sub_80184DF4` | `pso/unk/text_80184C2C.cpp` | `src/pso/unk/text_80184C2C.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `TObjLaboMapWarp::slot4C` | `pso/unk/text_80184C2C.cpp` | `src/pso/unk/text_80184C2C.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `__ct__11BmlResourceFlP21BmlResourceDescriptorllPv in TLobby__sub_80184DF4` | `pso/unk/text_80184C2C.cpp` | `src/pso/unk/text_80184C2C.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | extern "C" mangled name | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `clear_global_array__6TLobbyFPv in TLobby__sub_80184DF4` | `pso/unk/text_80184C2C.cpp` | `src/pso/unk/text_80184C2C.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | extern "C" mangled name | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `fn_802A2A00` | `pso/unk/text_802A2A00.cpp` | `src/pso/unk/text_802A2A00.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | raw offset cast | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |
| `fn_802A2A00 self-assignment, identical branches and goto` | `pso/unk/text_802A2A00.cpp` | `src/pso/unk/text_802A2A00.cpp` | [#207](https://github.com/zeroz41/pso-decomp/pull/207) | other: matching-oriented source control flow | [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) | upstream catch-up, rewrite later |

## Pending in open PRs

Found by `tools/list_port_exceptions.py --pr N` on 2026-11-04. Add or remove the
entry when the PR merges.

| PR | Exception | Status / reason |
|---|---|---|
| [#285](https://github.com/matthewlewisnewton/pso-decomp/pull/285) | `static asm void pad_03_8042E9FC_text` via `orig_asm` include (`src/pso/unk/text_8042E9FC.cpp`) | PR body: 5-word stranded epilogue; 0/60 C probes across 20 compilers reach it. **No approval recorded and no scalar fallback**; it needs one under the rule above. |
| [#296](https://github.com/matthewlewisnewton/pso-decomp/pull/296) | `scheduling` ×5, `peephole`, `optimize_for_size` pragmas | Reason not recorded. Drop in a port. |
| [#250](https://github.com/matthewlewisnewton/pso-decomp/pull/250) | `fp_contract` ×3 | Reason not recorded. |
| [#295](https://github.com/matthewlewisnewton/pso-decomp/pull/295) | `inline_depth(2)` (main's existing region uses depth 1) on `src/pso/misc/TQuestVmDownLoadServer_803E6970.cpp` | The nested `flags & 1` group walk only inlines at depth 2, which is required for both page-fit expansions in `sub_803EC284` to match. A port can drop the pragma and keep the scalar loop. |
| [#303](https://github.com/matthewlewisnewton/pso-decomp/pull/303), [#289](https://github.com/matthewlewisnewton/pso-decomp/pull/289), [#225](https://github.com/matthewlewisnewton/pso-decomp/pull/225), [#222](https://github.com/matthewlewisnewton/pso-decomp/pull/222), [#215](https://github.com/matthewlewisnewton/pso-decomp/pull/215), [#128](https://github.com/matthewlewisnewton/pso-decomp/pull/128) | 1 to 4 inlining/optimization pragmas each | Reason not recorded. Drop in a port. |
| [#240](https://github.com/matthewlewisnewton/pso-decomp/pull/240) | Not scanned | Diff exceeds GitHub's 300-file limit; scan locally after it merges. |
| [#313](https://github.com/matthewlewisnewton/pso-decomp/pull/313) | `configure.py`: `TBoss6Rock.cpp` `-fp_contract on`, `-str reuse,readonly`, `-inline off,deferred`; `TOBoss4.cpp` `-fp_contract on`, `-str reuse,readonly`, `-sdata 4`, `-inline deferred` | One TU each, written last-defined first. Deferred emission puts the late helpers and vtables in address order. `-fp_contract on` fuses the fall and spin multiply-adds (and TOBoss4's). `-str reuse,readonly` keeps the literals in the unit's rodata. `-sdata 4` keeps TOBoss4's 8-byte motion-name array in `.data`. |
| [#167](https://github.com/matthewlewisnewton/pso-decomp/pull/167) | Unit switch `-opt nolifetimes,nocse,noprop,noloop` on `TMovie_80143988.cpp` (section 5); the pre-existing `__dcbt` in `pack_movie_frame` | `pack_movie_frame` matches 100% in plain C++. The earlier `__rlwinm` / `__rlwimi` calls are gone. `__dcbt` is the original data-cache touch (`dcbt r31, r0` / `dcbt r9, r0`). Port: drop the switch and the cache touch. |

The scan covers source lines only; `configure.py` overrides added by PRs show up
in the generated table once merged.


## 8. Native item factory callback ABI

| File | Boundary | Why | Port should |
|---|---|---|---|
| `src/pso/unk/text_80104FCC.cpp`, `include/pso/item/ItemCreateFunction.h` | `item_create_fn_table[4]` stores `TItemMoney::create(TItemData*)` in the byte-buffer callback type and the MWCC branch invokes that type | The original relocation targets the typed money factory, while the dispatcher makes the same indirect call for all five item categories. Native PPC passes either record pointer in `r3`; this is an ABI dependency, not portable C++ call compatibility. The complete 124-byte data section and 2012-byte code section match and link. [Evidence](evidence/equip-requirements-match.md). | Compile the non-MWCC `invoke_item_factory` path, which converts the stored money callback back to its actual function type before calling it. Keep the typed money declaration; do not erase it globally. `ports/tests/item_factory_callbacks.cpp` exercises this fallback. |

This callback boundary is documented for review; it does not add assembly,
steering pragmas, per-unit compiler switches or link-check exceptions. The
mechanical inventory does not currently enumerate function-pointer conversions.
