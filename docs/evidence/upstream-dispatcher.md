# Link the network dispatcher independently

Base: validated fork main `12cc95ca737a3a8757c17f45df06a9af4821d872`, including
DHCP #371, keyboard #372, technique #373 and PPP/session #374. Previous validated
bases include `387621104107ed1ff8c650bf2f50ef00c6859ba4`,
`f892b2e3ac77834f6250df75066d82c420197e44` and
`65b21c210ae980e9d2fe4aef1a3314ed84df1ddd`, following the original
`224eb99838471c243b20c305eddac75e7ff76c8f` baseline.
Reference: upstream's network split in [#213](https://github.com/zeroz41/pso-decomp/pull/213)
and typed follow-up [#215](https://github.com/zeroz41/pso-decomp/pull/215),
checked at upstream `dd7a1a2d6e200a69462fff12172ff35aaa460c93`.
Its `NetDispatcher.c` and `NetTcp.c` own the same code and BSS ranges below.
This change extracts the fork's existing C++ bodies and shared interfaces;
it does not import upstream's C rewrite or recover additional functions. The
follow-up below improves the dispatcher's state accesses while preserving its
complete native object.

## Boundaries and source ownership

The fork's combined `pso/misc/TLobby_804050DC.cpp` contained 338 functions,
295 exact. Its 12 dispatcher functions were exact but could not link independently
of the incomplete surrounding code. Split the two consecutive subsystems at
the upstream boundaries:

| Unit | Code range (end exclusive) | Data range (end exclusive) |
|---|---|---|
| Existing prefix | `804050DC–80419A00` | `.data 804FD80C–804FD890`, `.bss 805C1AD8–805C1C50` |
| `network/NetworkDispatcher.cpp` | `80419A00–8041A1D8` | `.bss 805C1C50–805C1D48` |
| `network/TcpProtocol.cpp` | `8041A1D8–8041ED8C` | `.bss 805C1D48–805C1DF0` |

The dispatcher owns `network_dispatch_state`, the protocol-handler table,
timer table, message queue, and dispatch loops. Its existing shared
`NetworkDispatch.h` has field offsets and size assertions. The TCP range owns
`tcp_protocol_state`; moving that range to a separate file keeps each source
file contiguous in the split map. BSS is zero-initialized program state.
No assets, synthetic references, manual tables or object-rewriting hooks are added.

Preserve the existing function definition order. Move the two TCP definitions
previously interspersed among dispatcher definitions with the rest of TCP.
Keep `TLobby__sub_80406F0C`, formerly defined after the TCP functions, in the
prefix that owns its address. The prefix remains at 243/281 exact functions;
TCP remains at 40/45; the dispatcher is 12/12 and fully linkable. All three
units' data sections match. The unmatched prefix/TCP code remains on original
object fallback and is not represented as new recovery.

## Compiler settings and remaining debt

All three ranges retain the existing AVE-TCP GC/1.2.5n compiler and
`-opt nocse` switch. The two new configure entries preserve that setting;
they do not change optimization policy. TCP additionally spells out
`dont_inline off` and `inline_depth(4)`, already active at its old position.
An extraction without those settings loses three prior matches:

| Function | Score without ambient settings | Difference |
|---|---:|---|
| `TLobby__sub_8041A3CC` | 99.78432% | Stack frame grows from 0x18 to 0x20 |
| `TLobby__sub_8041A5B4` | 99.916664% | Stack frame grows from 0x20 to 0x28 |
| `TLobby__sub_8041D584` | 65.69705% | Segment-removal helper becomes an out-of-line call |

Restoring the settings preserves every previously exact function. TCP has 24
moved pragma lines plus those two explicit lines; the dispatcher has four
moved pragma lines (`opt_common_subs` x3, `pool_data` x1). The generated
inventory after integrating keyboard main is 5,773 pragma lines in 877 files
and 178 unit overrides.
No assembly, intrinsic or hardware access is added. The historical section 7
upstream catch-up register stays at 521 entries.

Remaining inherited constraints are recorded in section 4 of the
[porting exceptions register](../porting-exceptions.md):

- Dispatcher reset/shutdown and handler release now use the shared state and
  named fields. Handles and payloads remain 32-bit, and the final four state bytes
  remain unresolved. Use target-appropriate handle/payload types in a port.
- Existing `TLobby` / `TUdpSocket` wrappers do not establish actual class ownership.
  The block-local `NetResumeThread(s32)` redeclaration is removed in favor of the
  shared runtime declaration. The legacy mangled handler-registration name and
  the thread creator's callback/return-type mismatch remain unresolved.
- The reset definition now explicitly returns the runtime's `s32` status, but
  DHCP's legacy `s16(int)` caller declaration remains incompatible. The follow-up
  below records why this is not a completed ABI repair.
- TCP still contains overlapping record views, raw packet offsets, provisional
  member calls, local signed/unsigned status declarations, pointer/integer casts,
  and optimizer-only locals. Preserve the original native ABI for this split;
  a future typed recovery should consolidate callers and callees together.
- Timer wraparound and synchronization behavior remain the original implementation.
  Native byte matching is not a portable runtime/concurrency validation.

## Typed dispatcher follow-up (2026-11-10)

The initial check found fork main `387621104107ed1ff8c650bf2f50ef00c6859ba4`
already included in the original PR head `205d83303ed37d03efba67768825b867c4c77b2e`.
Main then advanced through keyboard commit
`f892b2e3ac77834f6250df75066d82c420197e44` to technique/progress commit
`65b21c210ae980e9d2fe4aef1a3314ed84df1ddd`, followed by PPP/session main
`12cc95ca737a3a8757c17f45df06a9af4821d872`; all are merged into this branch. The dispatcher is already fully exact and
linked, so this follow-up improves source quality rather than claiming new
recovered bytes.

- Replace the reset/shutdown per-function state views and the handler-release
  overlay with `NetworkDispatchState` and its existing handler records. Remove
  the unused duplicate views and lifecycle declarations from the old prefix.
- Name the protocol and timer thread handles at offsets `0x08` and `0x0C`.
  Their creation callbacks, shutdown order and yield checks establish these roles;
  upstream #215 uses the same two slots. Offset assertions pin both fields.
  Keep them unsigned, as the old yield check's `u32 *` view and the runtime's
  `u32 *` output/`u32` resume argument require. A signed-field probe changed the
  yield function's two unsigned comparisons and was rejected.
- Preserve the reset range through `offsetof(NetworkDispatchState, unknown_F4)`
  with a new offset assertion. Both reset functions still clear only `0xF4` bytes,
  not the whole `0xF8`-byte object. The trailing four bytes stay untouched.
- Use the shared `NetResumeThread(u32)` declaration. The thread creator's output
  declaration is now `u32 *`, matching its definition; its inherited callback and
  narrow return declaration are not claimed as a unified runtime contract.

### Reset status boundary remains unresolved

`TLobby__sub_80419A34` calls `TLobby__sub_803F8E9C`, whose definition returns
`s32` success/failure. The dispatcher now explicitly forwards that result and
its canonical header declares `s32(void)`, as upstream #215 does. That callee
change is byte-identical. DHCP's `TLobby::init_network_stack` still declares it
as `s16(int)`, passes an unused count, and consumes the result as signed 16-bit
status. The older `void(void)` definition did not describe this behavior.

A probe with one shared `s32(void)` declaration, a no-argument call and the
existing `s16` status local was rejected: `init_network_stack` fell to
97.608696%, its frame grew from `0x10` to `0x18`, and the result copy gained
sign extension. The caller is retained unchanged, with an explanatory comment.
This partial callee correction does **not** repair the cross-unit mismatch.

A later #303 audit proved the runtime reset returns only -1 or 0 and has one
signed-16 consumer. A separate bounded shared `s16(void)` contract probe was
semantically sound, but also rejected: the wrapper gained a sign extension and
the caller's frame grew from 0x10 to 0x18. It failed original-DOL validation and
was fully restored, with all four complete network objects byte-identical.
No compensating return-type, counter-lifetime, padding or compiler-steering
variant was added. See [the #303 audit](pr303-source-contracts.md).
Consolidating that boundary requires a separate caller/callee recovery that
preserves both complete objects; no frame padding or compiler steering is added.

The final dispatcher, DHCP, prefix and TCP source objects are each byte-identical
to their pre-cleanup objects, including object metadata and relocations. Raw
objdiff with `functionRelocDiffs=data_value` confirms dispatcher 12/12 and DHCP
42/42 functions exact and their code/BSS sections at 100%. Full build and
`tools/check_pr.py` pass against both current main and the original PR head.
No exact function, data, linked range, padding coverage or retention entry is lost.
The cleanup adds no linked bytes beyond the extraction totals below and changes
no compiler exception counts or link inputs.

## Current-main integration

Built unchanged main `12cc95ca737a3a8757c17f45df06a9af4821d872` in the separate
baseline worktree, retaining the earlier keyboard/technique baseline reports.
The native build, retention check, original-DOL hash, exception inventory and
`tools/check_pr.py` pass. Merged that main into the dispatcher branch. The only
conflict was the exception-register summary; both the new PPP/session section
and the existing keyboard, technique and dispatcher entries are retained, with
the inventory regenerated. No dispatcher or DHCP source change was needed.

Reconfigured with fresh split objects and built the combined tree. Full native
build and no-loss checks pass against both validated main and the original PR head.
The actual final linker edge contains 3,587 source objects and 1,383 fallbacks:
dispatcher, DHCP and PPP/session are source inputs; the incomplete prefix and TCP
remain fallback inputs. README stays on merged-main coverage. All four complete
network source objects validated above remain byte-identical after this merge,
including the documented, unresolved DHCP/dispatcher ABI boundary.

The comparison to the original PR head inherits main's four-byte alignment-padding
coverage reduction at `.sdata2 0x805DC7EC`, documented with the technique conversion
pool recovery. `report_delta.py --check` accepts it as zero-filled alignment padding;
no exact function, data object or linked range is lost. The dispatcher-only
comparison to validated main has no padding loss.

## Validation

Built unchanged base and saved its report; retention passed before editing.
Full build and `tools/check_pr.py` pass against that immutable baseline,
including original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`,
address-aware exact-function/data coverage, linked coverage and retention checks.
Raw objdiff uses `functionRelocDiffs=data_value`. The dispatcher has all
12 functions, 2,008 code bytes and 248 BSS bytes exact; the source object is
an actual linker input.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,394 | 27,394 | 0 |
| Exact code bytes | 4,202,324 | 4,202,324 | 0 |
| Exact data bytes | 1,470,367 | 1,470,367 | 0 |
| Linked code bytes | 3,704,816 | 3,706,824 | 2,008 |
| Linked data bytes | 1,185,687 | 1,185,935 | 248 |
| Linked units | 3,586 | 3,587 | 1 |

Total functions, code and data are unchanged; the unit count increases from
4,968 to 4,970. There are no lost exact or linked functions/data ranges and
no alignment-padding loss. The scanner adds only the dispatcher and two
retention entries (`NetRunProtocolDispatchLoop`, `NetRunTimerDispatchLoop`),
removing none. README coverage remains tied to merged main.
