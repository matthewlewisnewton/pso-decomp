# Link the network dispatcher independently

Base: fork `387621104107ed1ff8c650bf2f50ef00c6859ba4`, including DHCP #371.
Revalidated after main advanced from the original `224eb99838471c243b20c305eddac75e7ff76c8f` baseline.
Reference: upstream's network split in [#213](https://github.com/zeroz41/pso-decomp/pull/213)
and typed follow-up [#215](https://github.com/zeroz41/pso-decomp/pull/215),
checked at upstream `dd7a1a2d6e200a69462fff12172ff35aaa460c93`.
Its `NetDispatcher.c` and `NetTcp.c` own the same code and BSS ranges below.
This change extracts the fork's existing C++ bodies and shared interfaces;
it does not import upstream's C rewrite or recover additional functions.

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
inventory becomes 5,774 pragma lines in 878 files and 178 unit overrides.
No assembly, intrinsic or hardware access is added. The historical section 7
upstream catch-up register stays at 521 entries.

Remaining inherited constraints are recorded in section 4 of the
[porting exceptions register](../porting-exceptions.md):

- Dispatcher reset/shutdown and handler-release functions still use overlapping
  provisional struct views and raw offsets. The thread fields are still accessed
  through `unknown_08`; handles and payloads are 32-bit. Replace these with one
  typed state and target-appropriate handle/payload types in a port.
- Existing `TLobby` / `TUdpSocket` wrappers do not establish actual class ownership.
  The block-local `NetResumeThread(s32)` declaration and legacy mangled handler
  registration name remain as on main. Consolidate these with the runtime API.
- TCP still contains overlapping record views, raw packet offsets, provisional
  member calls, local signed/unsigned status declarations, pointer/integer casts,
  and optimizer-only locals. Preserve the original native ABI for this split;
  a future typed recovery should consolidate callers and callees together.
- Timer wraparound and synchronization behavior remain the original implementation.
  Native byte matching is not a portable runtime/concurrency validation.

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
| Exact functions | 27,389 | 27,389 | 0 |
| Exact code bytes | 4,191,812 | 4,191,812 | 0 |
| Exact data bytes | 1,470,159 | 1,470,159 | 0 |
| Linked code bytes | 3,685,784 | 3,687,792 | 2,008 |
| Linked data bytes | 1,184,043 | 1,184,291 | 248 |
| Linked units | 3,587 | 3,588 | 1 |

Total functions, code and data are unchanged; the unit count increases from
4,973 to 4,975. There are no lost exact or linked functions/data ranges and
no alignment-padding loss. The scanner adds only the dispatcher and two
retention entries (`NetRunProtocolDispatchLoop`, `NetRunTimerDispatchLoop`),
removing none. README coverage remains tied to merged main.
