# Word metadata pooling: observed compiler eligibility and timing

This follows continuation `418d4b0111a4f7b98efd34f75bd1aea9c6151f35`
and the [destructor/table isolation](window-word-destructor-isolation.md).
It observes the two already-frozen source snapshots; it introduces no new
initializer, layout, declaration-order or compiler-option candidate.

## Controlled observation

The normal build uses GC/2.6 with `-O4,s -inline off -sdata2 4` and the existing
remaining target flags. Its compiler executable SHA-256 is
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
The wibo SHA-256 is
`7fdf620b151744296b9bb93318d8c4009d3d3e98e23718a6eda9fbec4cefbb2a`.
The public [compiler reconstruction](https://github.com/doldecomp/mweppc/tree/919828d97d33d236da675824d43c5d57332afe74)
identifies the relevant structures and addresses. Runtime observations come
from the pinned original executable, rather than executing the reconstruction.

Two runs observe pool decisions, and a third observes final data-definition
ordering in the identical compiler-table candidate. Execution-only hardware
breakpoints read objects, symbols, section links and groups. They do not patch
compiler code/data, invoke compiler helpers, alter optimization state or modify
source during compilation. Runs hold the existing legacy capacity gate and
shared debugger lock. Each traced run has a separate, identical-command normal
control, retaining production code-generation options. Only source/include/output
paths and dependency-file output handling are redirected to private scratch.

All three complete traced ELF objects equal their normal controls byte for byte.
The manual-table control also equals the captured published 664-byte owner ELF;
the compiler-table control equals the captured failed 672-byte candidate ELF.
Thus the observations reproduce the previously qualified pair, including their
relocations, symbol attributes and metadata, rather than just similar assembly.
No original-game object, binary or raw disassembly is published with this note.

## What the initializer actually sees

In `TWindowDD__sub_803422F0`, the manual-table snapshot references:

| Object | Defined data offset | Bytes | Pool eligibility at function generation |
| --- | ---: | ---: | --- |
| Descriptor `lbl_804EFC7C` | 0x2C | 20 | Existing `.data` root |
| Position `lbl_804EFC74` | 0x24 | 8 | Same root |
| Manual table `lbl_804EFC90` | 0x40 | 24 | Same root |

The observed group's initial limit is three distinct objects. Adding the third
reference marks the group full and introduces its shared base; subsequent
snapshots record count three, full one and virtual register 37. This agrees
with `add_anchor_reference` in the pinned compiler reconstruction. It explains
the shared address base in this initializer; it is not a universal threshold
for every section, group or compiler setting.

In the frozen compiler-table candidate, descriptor and position still have the
same data offsets and root, but the C declaration of
`__vt__17TWindowDD_WS_Word` resolves to an undefined symbol during initializer
code generation: size zero, no defined section and no section pool link.
`GetDataPoolRoot` returns null. The two eligible metadata references leave the
observed group at count two, full zero and register zero. Repeated uses of those
same two objects do not add a third distinct object.

This is not a weak-symbol exclusion: the observed C table object has qualifier
zero. The actual compiler-generated table object, used by the native destructor,
is a separate frontend object with a 24-byte type and const qualifier; it too
has an undefined symbol and no section pool link at that point. Both eventually
refer to the same emitted table symbol, but neither has a defined data-pool root
during these immediate function compilations. Final ELF adjacency alone cannot
supply the missing eligibility retroactively.

## Table definition occurs after immediate function generation

The timing run observes all seven function-generation starts, including the
native destructor and retained initializer. Only afterward does
`CParser_GlobalCleanup(TRUE)` run Word's class action and
`CInit_DeclareData` for the actual 24-byte compiler table.
The [parser implementation](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CParser.c)
runs class actions in final cleanup; the
[class implementation](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CClass.c)
declares the table there. This directly explains its unavailable section root
in the earlier observations under the current immediate-compilation profile.
It does not recover the original game's source organization or compiler options.

The observation narrows the earlier address-sharing uncertainty: this frozen
pair differs before register allocation because the real table is defined too
late for the initializer's data-pool membership. Later register choices are a
consequence, not evidence for another member-local or scheduling spelling.

## Reproduction and boundary

Capture the normal compiler command for the owner using the pinned Ninja
`-t commands` operation. Keep its production options. Replay the already-frozen
manual-table and destructor/table-isolation sources with their own matching Word
headers in private output directories. For this exact compiler, read-only
hardware execution breakpoints are:

| Address | Observation |
| --- | --- |
| 0x004D1247 | `GetDataPoolRoot` eligibility, resolved symbol/section/group |
| 0x004D12B3 / 0x004D12BD | Successful/null pool-root return |
| 0x004E09E0 | Addition of a distinct anchor reference |
| 0x00433492 | Function generation start |
| 0x004E4A60 | Global cleanup and its class-action argument |
| 0x0052CC60 | Class action |
| 0x0050A460 | Actual data declaration |

Use at most four hardware breakpoints per run. Do not substitute software
breakpoints, helper calls, `-sym on` or debugger-modified compiler data. Validate
complete traced/control ELF identity before interpreting the records.

Private reproduction artifacts are `pr403-word-pool-observation/observe.py`,
`observe-timing.py`, per-lane `trace.json`, `receipt.json`, normal/traced objects
and logs. The source snapshots reproduce the previous published/failed ELF
pair exactly. Independent read-only review confirms the output controls and
bounded interpretation. This is compiler-mechanism evidence, not another full
linked candidate test; the earlier failed-candidate DOL result and restoration
remain the applicable whole-program results.

Further activation needs independently justified source/class organization or
compiler-profile evidence that makes the actual table eligible at function
generation while preserving all functions, objects, relocation targets, providers
and original DOL. No deferred-generation flag, reordering, synthetic third
reference, manual replacement table or new lifetime mechanism is authorized by
these observations. The native Word constructor/destructor/table and raw lifetime
holds remain; the matched renderer and shared helper recoveries are unchanged.

The subsequent [native-table context control](window-word-native-table-context.md)
finds and independently replays an already-recorded genuine class precedent. The
Fish/Falz production profile defines its real table before function generation;
the same-source immediate control defines it afterward and loses the three-object
pool. This corroborates the mechanism without establishing Word's own original
profile or authorizing a flag/source change.
