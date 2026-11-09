# Upstream catch-up through 00cda35c8

Fork [#367](https://github.com/matthewlewisnewton/pso-decomp/pull/367) folds upstream history through `00cda35c8f04b9089a26b46a5cc2df017f669198`
with an `ours` merge, then ports three units from upstream
[#207](https://github.com/zeroz41/pso-decomp/pull/207), squash
`bf460d72b531f011798c6928f4dff86be7eebfcf`. Its fork baseline is
`6daa19a11db97b1b8222fd2665eba485ed3a74a4`. Matt authorized the history fold on
2026-11-09 after its consequences and the exception-register limitation were stated,
and explicitly requested documentation of outstanding inherited cheats.

The fold commit is `95ca83321f022ff73229606634b5d415a8658cf3`; its tree equals the
baseline tree. The fork's LICENSE is retained, as permitted by the request.
Integration must preserve this merge ancestry; squash merging the carrier would
lose the history relationship.

## Source actually imported

| Fork unit | Original text interval | Newly linked code | Newly linked data |
|---|---|---:|---:|
| `pso/menu/TAdEndText.cpp` | `0x8001A988`–`0x8001B424` | 2,716 | 784 |
| `pso/unk/text_80184C2C.cpp` | `0x80184C2C`–`0x80185248` | 1,564 | 0 |
| `pso/unk/text_802A2A00.cpp` | `0x802A2A00`–`0x802A2BD8` | 472 | 36 |

The source uses the existing fork paths and declarations. Existing calls to
`set_current_texture_list` in the ending renderer remain intact; the newly recovered
font-drawing function calls the distinct `set_texlist` helper from upstream.
The fork's real `StripBufferPair` constructor replaces upstream's misowned
`TLobby::alloc_tables` calls. Existing `BmlResource` destruction is preserved.
The 42 new retention entries are generated from fresh original split objects;
there are no retention removals or unrelated normalization changes.

## Outstanding inherited cheats

The [section 7 register](../porting-exceptions.md#7-upstream-catch-up-rewrite-later)
adds 64 site/category rows for these three units. This is an audit of their remaining
matching constraints, including legacy constructs already present in the baseline;
it is not a claim that all 64 were introduced by this patch. The upstream column
identifies the carrier's source version (#207), not the first historical introduction
of every legacy line. The existing 429 catch-up rows remain, giving 493 total rows.
The generated inventory scans compiler/hardware constructs across the whole tree;
it does not automatically identify every raw-offset cast or shadow type.

| Remaining construct | Why retained / evidence | Rewrite or port action |
|---|---|---|
| `TAdEndText`'s `Self_*`, `Box_*`, `Pos_*`, and four `RecoveredGlobal_*` structures | Upstream's layout views reproduce the existing accesses; class ownership and shared global typing remain provisional. | Consolidate evidence-backed members and global declarations; remove padded shadow views only with complete object validation. |
| Mangled ending-task render/run/constructor definitions, explicit `TObject` constructor call, and `__vt__10TAdEndText` assignment | Existing upstream ABI form retained while making the whole unit link. The vtable itself is compiler-emitted, not a hand-written table. | Use real class members/construction and compiler-managed vptr initialization once their code and relocation layout match. |
| Ending-task raw accesses, pointer/integer resource handles, and `__cvt_fp2unsigned` call | Existing upstream representation; no claim that it is a portable class interface. | Use shared types and pointer-sized handles; replace the compiler runtime helper with a defined numeric conversion after checking its range semantics. |
| `#pragma readonly_strings on` and 24 section-placement declarations in `TAdEndText` | Upstream's arrangement emits the claimed `.rodata`, `.data`, and `.sdata2` objects byte-exactly, including the font metrics and texture descriptors. Individual alternatives have not been exhaustively tested. | Use ordinary const data on a port; matching cleanup must preserve sizes, addresses, alignment and relocations. |
| `#pragma fp_contract on` in the ending task and `fn_802A2A00` | Upstream requests fused arithmetic; the resulting full objects match. The ending-task pragma predates this carrier. | Drop the compiler-specific pragma on a port and explicitly choose the required fused-arithmetic behavior. |
| Placement of `TAdEndText::~TAdEndText` after `run_task` | #207 moves it to obtain the required function/vtable emission order. | Preserve matching order while recovering the class; ordinary source organization is sufficient when porting away from binary matching. |
| `TLobby__sub_80184DF4` raw resource/model offsets and integer handles | Upstream's recovered seasonal-model setup remains layout-based. | Replace offset casts with verified `BmlResource`, model, and descriptor fields incrementally. |
| Four calls to `__ct__11BmlResourceFlP21BmlResourceDescriptorllPv` | This is the fork spelling of upstream's `load_resource_from_descriptor`. A trial using ordinary `new BmlResource(...)` changed descriptor indexing and register allocation, scoring 97.39269% for the function. Restoring the upstream call form makes it 100%. | Recover a real constructor expression with identical code; a nonmatching port can use normal construction immediately. The raw ABI declaration is intentionally registered, not presented as the public C++ API. |
| `clear_global_array__6TLobbyFPv()` without its declared pointer argument | Upstream directly calls the mangled function; its current body clears global state and does not consume that argument. | Recover a consistent signature/call boundary without adding an unmatched argument setup instruction. |
| `Obj_80185160` and the raw cast in `TObjLaboMapWarp::slot4C` | Existing baseline shadow view in the newly linked lobby unit. | Replace with the verified class member layout. |
| `VBase_802A2A00`, `TChCrTag_802A2A00`, and raw self/position casts | Upstream models a virtual call and object fields without recovering the owning class. | Recover the actual tag class, virtual slot and shared types; avoid invented class ownership. |
| Self-assignment, identical branches and `goto` in `fn_802A2A00` | Upstream explicitly records these as preserving code shape. This carrier validates that source, not the necessity of each construct in isolation. | Simplify in a portable implementation; prove any matching cleanup against the whole object. |

No assembly, intrinsic, hardware access, or per-unit compiler override is added by
this carrier. The generated totals remain 22 assembly/include lines, 83 intrinsic
hits, 69 hardware hits and 174 unit overrides. Pragmas increase from 5,766 to 5,768
across 872 files: one `readonly_strings` and one `fp_contract` site are new.
The checker admits #207 in addition to its existing #167–#192 set; intermediate
#193–#206 and later PRs do not gain an exception merely through history folding.

## Upstream content still requiring explicit ports

An ancestry fold does not import the omitted patches. Future merges start after the
folded tip and will not automatically restore these earlier changes. Existing fork
implementations may already cover individual functions; each follow-up must compare
original addresses and linker inputs before claiming additional coverage.

| Upstream source | Deferred work |
|---|---|
| #196, `fc62998f4` | Matchpass 13's path reorganization, folds, code and data additions. Keep the fork's present layout until each affected unit is reconciled. |
| #198, `721e0b3ea` | Matchpass 14's unit folds and data/code additions, including UI/window and keyboard changes. |
| #208, `ae797d392` | Matchpass 15's code/data and split changes, including ADX/audio, technique, player, enemy, UI and networking work. This commit is an ancestor of #207, despite its higher PR number. |
| #213, `76d99c974` | C network-stack rewrite and its headers, unit boundaries, symbols and compiler settings. Reconcile with the fork's existing network recovery. |
| #207, `bf460d72b` | `TBoss4Type2__sub_80054FC0` at `0x80054FC0` and `__VIRetraceHandler` at `0x803E97B0` remain unmatched on the baseline and are not ported by this three-unit carrier. |
| Naming waves and follow-up corrections through `00cda35c8` | Upstream symbol/string names are recorded in ancestry but not applied by this carrier. Audit their evidence and reconcile them with fork names in follow-ups. Zero new linked bytes does not mean no semantic value. |

The other #207 changes at `0x800E1774`, `0x801CD550`, `0x80279178`,
`0x802D9644`, `0x802D9824`, and `0x803EC71C` are already exact in the baseline
under the fork's names/types. The equipment-list unit is already linked. Those
implementations are retained; this carrier does not replace them with upstream text.
The two LICENSE commits are history-only, retaining the fork's existing notice.

## Validation

Built the untouched baseline in an isolated clone with the pinned tools and the
local original disc inputs; generated all split objects afresh. Baseline retention:
17,528 entries, zero additions/removals needed. After importing and linking:

- `tools/check_pr.py`: PASS; original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- Exact functions: 27,364 → 27,367; exact code: 4,180,388 → 4,182,748 (+2,360).
- Linked code: 3,636,556 → 3,641,308 (+4,752); linked data: 1,165,731 → 1,166,551 (+820).
- Linked units: 3,570 → 3,573; zero function, linked-code or linked-data regressions.
- All sections of the three new units match; linkage and retention checks pass.
- Four zero padding bytes at `.sdata2:0x805DDEA4` leave aggregate split coverage when the new constant pool is split out. The address-aware checker reports this allowed padding change; it is not a data-object regression.

The exception register and generated inventory are checked separately with
`python3 tools/list_port_exceptions.py --upstream-catchup --check` and
`python3 tools/list_port_exceptions.py --check`.
