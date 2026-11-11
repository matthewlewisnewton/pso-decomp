# Share the concrete network timer registry contract

This declaration-only change is extracted from the Codex-authored commit
[`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98`](https://github.com/matthewlewisnewton/pso-decomp/commit/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98)
in [PR #303](https://github.com/matthewlewisnewton/pso-decomp/pull/303), with
include placement adapted to independent main base
`e9b77fcfdcc2335c9a5a92886826022c80505e67`.
The [original timer audit](https://github.com/matthewlewisnewton/pso-decomp/blob/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98/docs/evidence/pr303-network-timer-contract.md)
records the source, native call-graph and whole-translation-unit control evidence.
No other #303 source changes are prerequisites or included here.

## Existing provider and observed callers

Main already defines `NetRegisterTimer` at `0x80419E64` as
`s32(s32 period, s16 locked, NetTimerCallback fn)` and `NetUnregisterTimer` at
`0x80419DDC` as `s32(NetTimerCallback fn)`. `NetTimerCallback` is
`void (*)(void)`. Both providers in `NetworkDispatcher.cpp` are unchanged from
main and from the extraction source. Their zero and -0x100 results are native
words, and the timer loop calls the stored callback without arguments.

A fresh scan of all 4,948 original objects in main's generated
`build/GPOE8P/config.json` finds ten references to each registry function.
Every reference is a zero-addend `R_PPC_REL24` call. A separate direct-branch
scan of the original DOL finds the same ten registrations and ten removals,
and no aligned absolute words naming either registry entry in its initialized
sections. These are bounded observations, not proof about arbitrary function
address words, synthesized targets or external callers.

The concrete callback definitions have `void(void)` signatures:

- TCP: `TLobby__sub_8041A5B4` and `TLobby__sub_8041A3CC`.
- DHCP: `TLobby__sub_80423298`.
- EXI: `TLobby::update_exi_status`.
- Miscellaneous timers: `TLobby__sub_804078B4`, `TLobby__sub_80411334`,
  `TLobby::tick_entry_timers`, `NetIPv6TickNeighborDiscovery` and
  `TLobby::update_timeout_entries`.
- The native address-word wrappers: `TLobby::tick_connection_timeouts`.

Timer records start at dispatcher state +0x2C, with stride 0x14. The original
registration stores the halfword lock selector at state-relative +0x2E
(`0x80419F98`), the callback word at +0x3C (`0x80419F9C`) and the active
halfword at +0x2C (`0x80419FA0`). The loop loads the callback at `0x80419D2C`,
moves it to LR at `0x80419D30` and calls it at `0x80419D34` without constructing
arguments. These agree with the existing record's +2 lock and +0x10 callback.

The wrapper's observed provider is `tick_connection_timeouts__6TLobbyFv`
at `0x8040AF48`. Registration constructs that address at
`0x8040A60C`/`0x8040A610`, passes period 1000 and calls the registration
wrapper at `0x8040A618`. Removal constructs the same address at
`0x8040A3C4`/`0x8040A3D0` and calls the removal wrapper at `0x8040A3F0`.
The wrappers pass the preserved native word to the registries at
`0x80421904` and `0x8042187C`, respectively.

## Narrow source change

`NetworkTimer.h` now owns the existing callback typedef and two C-linkage
declarations. `NetworkDispatch.h` includes it, preserving its transitive API,
record definitions and layout assertions. MessageTransport and the parser
include only the narrow header, avoiding the parser's unresolved dispatcher
reset declaration and local state overlay.

MessageTransport previously declared a discarded `void` result, an `int`
lock selector and a `void *` removal argument. It now uses the existing
provider's declarations and passes its concrete callback directly. The parser
previously declared its period and callback as `void *`; it now passes the
numeric period and explicitly converts the existing native address word to
`NetTimerCallback` at each wrapper boundary.

The wrappers retain the zero-callback and positive-signed-period guards,
lock/call/unlock order, -2 failures and forwarded word results. No provider or
callback body, timer layout, initialization, scheduling or failure behavior
changes. Correct duplicate declarations in TCP/misc remain as they were.
No private thread-creator/reset ABI, raw-IP callback contract, message queue,
allocator, state adjacency or metadata hold is resolved. Existing main bugs
remain intact; the DHCP and other repairs in #303 are not part of this change.
There are no new compiler controls, intrinsics, pragmas or exceptions.

## Independent-main validation

Validation uses isolated main and candidate checkouts and the existing
pinned local tools. Current main is refreshed from authenticated previous
validation outputs: regenerate current split objects and rebuild all changed
inputs through the serialized native capacity gate. The main report, complete
active object hashes and linker-input provenance are sealed before that
checkout changes. The candidate independently rebuilds its changed inputs
through the same gate, and every active object is compared with the current
main seal. Original #303 outputs do not supply the baseline.

The original and built DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,632 active compiled objects
are raw byte-identical between main and the candidate, including code, data,
symbols, metadata and relocations, with no normalization. Ordered linker
inputs remain 3,603 source objects and 1,345 original-object fallbacks.

The gated native build and `tools/check_pr.py --no-build` pass against the
fresh main report. Address-based coverage has no losses, all 3,603 linked
units remain exact, and all 18,441 retention entries have zero drift.
Matched functions remain 27,434, matched code 4,232,424 bytes and matched
data 1,477,099 bytes, each with delta zero. This is a declaration correction,
not a matching or linking gain. The generated porting inventory changes only
one existing source-line reference. All 306 existing `tools/tests` unit tests
pass, including the modem state/order tests and address-coverage/retention
validation tests. Host tests do not establish native ABI compatibility; the
complete native object comparison provides that bounded check. Python syntax
and both `make -C ports/tests run` and `make -C ports/tests sanitize` also pass,
including the portable loader targets inherited from current main.
