# Network timer registry declarations

Audit at branch `deef13594` and main `f8a71fae8`. This is a distinct, concrete
timer registry, not a retry of the private thread-creator/reset or raw-IP
callback probes. Preserve the hostname narrowing/fixed-copy behavior, previous
evidence and every unresolved allocation, adjacency, private ABI and metadata hold.

## Closed observed call graph and native storage

`NetRegisterTimer` at `0x80419E64` (0x154 bytes) is defined as
`s32(s32 period, s16 locked, NetTimerCallback fn)`; `NetUnregisterTimer` at
`0x80419DDC` (0x88 bytes) is `s32(NetTimerCallback fn)`. The existing typedef is
`void (*NetTimerCallback)(void)`. Both return a native word, zero or -0x100.
The locked address-word wrappers at `0x80421844`/`0x804218AC` forward that word
and retain their additional -2 guards. No result width or provider body changes.

An inventory of all 5,021 original split objects finds ten registrations and ten
removals, all zero-addend `R_PPC_REL24`, with no other references to either
registry. An independent DOL scan finds the same ten direct calls each and no
aligned absolute pointer words to the registry entries. The two address-word
wrappers each have one observed original-object caller. This bounded graph does
not establish validity of arbitrary address words, synthesized or external calls.

The concrete callbacks are source-defined `void(void)`:

| Path | Callbacks |
|---|---|
| TCP | `TLobby__sub_8041A5B4`, `TLobby__sub_8041A3CC` |
| DHCP | `TLobby__sub_80423298` |
| EXI status | `TLobby::update_exi_status` |
| Misc | `TLobby__sub_804078B4`, `TLobby__sub_80411334`, `TLobby::tick_entry_timers`, `NetIPv6TickNeighborDiscovery`, `TLobby::update_timeout_entries` |
| Address-word wrapper | `TLobby::tick_connection_timeouts` |

Timer records begin at state +0x2C with stride 0x14. The original instructions
store the halfword lock selector at state-relative +0x2E (`0x80419F98`), the
callback word at +0x3C (`0x80419F9C`), then mark active at +0x2C (`0x80419FA0`).
The timer loop loads the callback at `0x80419D2C`, moves it to LR at
`0x80419D30` and invokes it at `0x80419D34`, without constructing arguments.
These correspond to the existing record's +2 lock field and +0x10 callback.
Layouts and invocation remain unchanged.

The wrapper's concrete provider is `tick_connection_timeouts__6TLobbyFv` at
`0x8040AF48`. Registration materializes its HA/LO at `0x8040A60C`/`0x8040A610`,
sets period 1000 at `0x8040A614` and calls the wrapper at `0x8040A618`. The
wrapper preserves the callback word, passes it in r5 and lock selector zero,
then calls the registry at `0x80421904`. Removal materializes the same provider
at `0x8040A3C4`/`0x8040A3D0`, calls the wrapper at `0x8040A3F0`, and reaches
registry removal at `0x8042187C` with the preserved word in r3.

## Declaration discrepancies and bounded controls

MessageTransport locally declares registration as `void(int, int, void(*)(void))`
and removal as `void(void *)`. Its results are discarded. The parser TU locally
declares registration as `s32(void *, int, void *)` and removal as `s32(void *)`.
Its wrappers are intentionally still native-word interfaces: preserve nonzero
callback guards, positive signed period check, lock/call/unlock ordering, -2
failures and forwarded word results.

Eight isolated whole-TU controls use the exact actual source and native commands:
GC/1.2.5n `-O4,p -inline off` for both MessageTransport and the parser. Four MessageTransport controls independently
vary ignored-result declaration (`void`/`s32`) and lock-selector width (`int`/`s16`)
with a truthful callback type/direct removal argument. Four parser controls vary
period representation (`void *`/`s32`) and callback representation (`void *`/
`NetTimerCallback`), using the existing short lock parameter. Typed callback
controls retain an explicit native-word conversion at the wrapper boundary.

All eight complete compiled objects are raw byte-identical to production,
including metadata and raw relocations. Existing workspace/exclusive capacity
locks cover execution; production inputs and outputs remain unchanged. The
controls do not distinguish unique historical typedef spellings. Definitions,
actual stored fields, invocation and concrete callers support the current shared
interface; controls establish that the proposed call forms retain native output.
Independent source/native/control review confirms that limited conclusion.

## One narrow shared-header candidate

Move only the existing typedef and two C API declarations into `NetworkTimer.h`.
Include it from `NetworkDispatch.h`, preserving its existing transitive API and
all structures/assertions. MessageTransport and the parser include the narrow
header instead of conflicting local declarations. The MessageTransport removal
passes its concrete callback directly. The parser passes the existing numeric
period and explicitly converts its native callback word to `NetTimerCallback`.
Existing correct declarations in TCP/misc are retained.

This separation avoids importing the parser's held reset declaration and state
overlay into this probe. No function definitions, callbacks, timer records,
initialization, locking, periods, scheduling, failures, symbols, configuration,
force-active entries or provider selection change. In particular no typed private
creator API, new thread callback convention, raw-IP registration contract or
validation of arbitrary function-address words is inferred.

The first production candidate passes its capacity-gated native build. All 3,630
active complete compiled objects and all 3,665 cached entries remain **raw
byte-identical**, including code/data/debug metadata and relocations, without
normalization. Original DOL SHA-1 stays
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental metrics/coverage/retention
have zero drift. Sealed-main no-loss checks pass with 3,598 exact linked units,
18,440 retention entries without drift, existing +88 data bytes and no new
function/code gain or loss. Ordered providers remain 3,598 source and 1,346
original fallbacks. All seventeen existing DHCP/modem host tests pass; the
hostname test's three extracted definitions retain their prior hashes. Inventory
regeneration changes only the shifted source-line reference, with no new
porting exceptions. Independent review passes; exact-head review gates publication.

Only these timer declarations are reconciled. The lease/router/domain/hostname
repairs remain intact. The [hostname audit](pr303-dhcp-hostname.md) records the
specific evidence needed to reopen each other hold; this audit clears none of
them. No rejected probe is retried or compensated. Keep draft.
