# DHCP lease output and status contract

Distinct audit from source head `ce710757b97ae8cef86e419559dd53a6fa1aab55`
on main `e65f11ce6ec99c006909422f81da1c0a46ac062e` (2026-11-11).
The three asynchronous reply-output slots already have their shared contract;
this investigation concerns the separate synchronous accessor at `0x8042474C`.

## Producer, destinations and native caller

The producer declares `s32(void *, void *, void *)`. It calls the generic option
getter for IDs 7, 8 and 9. The original option table independently gives each
entry kind 1 and size four, pointing to lease, renewal and rebinding words at
`0x805D7B64`, `0x805D7B68` and `0x805D7B6C`.

Scanning all 5,021 original split objects finds one reference: zero-addend
`R_PPC_REL24`, offset 0x4B0 in `TLobby_801461EC.o`. At native call `0x8014669C`,
the three arguments point to the caller's declared `s32` globals at
`0x805D56EC`, `0x805D56F0` and `0x805D56F4`. The caller declares a short
result and immediately executes `extsh. r0,r3` after the call. No historical
shared typedef or absence of unseen/dynamically constructed calls is inferred.

The producer returns only literal zero or -1. This differs from the previously
rejected reset wrapper, which forwards another function's word result. Preserve
the accessor's counterintuitive behavior: accepted DHCP states 3/4/5 return zero
even when getters fail and set diagnostic 0x11/0x12/0x13. Subsequent getter calls
still execute. The generic getter copies its table storage to a nonnull output
even when the option's presence flag makes its result report failure. Null
outputs remain permitted. Invalid states set diagnostic 2 and return -1.
No early exit, clearing, lifetime enforcement or bounds behavior is added.

## Discriminating compiler controls

Before editing production, compile eight isolated controls under the unchanged
workspace/legacy-exclusive capacity protocol. Vary return width (`s32`/`s16`)
and output type (`void *`/`s32 *`) independently. Producer controls retain its
actual body, both volatile globals, the existing getter declaration, and active
inline pragmas. Caller controls copy the complete actual TU and substitute only
this local prototype. Both use actual `types.h`, source basenames and resolved
Ninja compiler commands: GC/1.2.5n with `-O4,p -inline off` for the producer;
GC/2.6 with `-O4,s -inline off -sdata2 4` for the caller. Production source and
recorded native outputs remain untouched during these controls.

| Return / output type | Producer | Caller at the lease status check |
|---|---|---|
| `s32` / `void *` | 228 bytes, exact function/relocations | 308 bytes; full-word comparison differs |
| `s32` / `s32 *` | 228 bytes, exact function/relocations | 308 bytes; full-word comparison differs |
| `s16` / `void *` | 228 bytes, exact function/relocations | 308 bytes; exact function/relocations |
| `s16` / `s32 *` | 228 bytes, exact function/relocations | 308 bytes; exact function/relocations |

Every frame is 32 bytes. Both short-return caller controls retain `extsh.`;
the word-return controls use a full-word comparison instead. Pointer typing
alone causes no function or relocation drift in either role. This separates the
two factors and demonstrates why one new candidate is credible; it does not
establish a uniquely recoverable historical typedef or reopen the failed reset
and creator probes. Independent review confirms all eight results and hashes.

## Shared declaration candidate

Share `s16 TLobby__sub_8042474C(s32 *, s32 *, s32 *)` with C linkage in the
existing DHCP header. Change only the producer signature and remove the caller's
incompatible local opaque declaration. The body, generic getter declaration,
output globals, option table, volatile ordering, diagnostics, null handling,
copy behavior and returns remain unchanged. Signed destination types match the
observed owning declarations and preserve the copied native-word representation.

The first candidate passes native validation. Producer, caller and parser
complete objects are raw byte-identical, including metadata and relocations;
all 3,665 compiled-object hashes are unchanged, without normalization. Original
DOL SHA-1 remains `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental
metrics, coverage and retention have zero drift. Full sealed-main comparison
passes: 3,599 exact linked units, 18,428 retention entries without drift, existing
+88 data bytes and no new function/code gain or loss. Ordered providers remain
3,599 source inputs and 1,347 original fallbacks. All fourteen existing host
tests pass. Independent source/native review passes; exact-head review remains
the publication gate.

Only this lease-output/status declaration mismatch is repaired. Adjacent router,
hostname and init-result interfaces remain separate. The locked allocation,
adjacency, private creator/raw callback/reset and metadata holds remain. No
failed migration or compensating production variant is retried. Keep draft.
