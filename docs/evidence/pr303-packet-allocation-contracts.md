# Packet allocation declarations

Audit against source head `80850ea411ac9ceecf90a2f6754f1027f63015f8` and main
`e65f11ce6ec99c006909422f81da1c0a46ac062e` (2026-11-11). Both implementations
in `NetworkPacketRuntime.cpp` return `u8 *` for a `u32` size. Their result is
the descriptor's packet-data pointer at +8, not the descriptor itself.

| Helper | Native size | Synchronization | Original split references |
|---|---:|---|---|
| `0x8042558C` | 0xB4 | Mutex around scan | Two `R_PPC_REL24` calls |
| `0x80425640` | 0x78 | No mutex | One `R_PPC_REL24` call |

Both reject unsigned sizes above 0x600, permit zero, and scan 32 descriptors in
order. The first entry with `in_use == 0` is marked in use and its existing data
pointer returned. Exhaustion returns null. Allocation does not initialize the
queued-length word, clear packet bytes or add rollback. No new nonnull/data
initialization invariant is assumed. The locked helper enters its mutex before
the size test and unlocks on its existing paths; the unlocked helper remains
unlocked.

## Native callers

Scanning all 5,021 original split objects finds exactly these three references,
all zero-addend `R_PPC_REL24` calls:

| Helper | Caller | Object / relocation offset | Input and result |
|---|---|---|---|
| Locked | `post_send_message` | MessageTransport / 0x8FC | `u16` count; result used as buffer and lookup address |
| Locked | `send_ethernet_frame` | TLobby_804050DC / 0x3CD4 | Constant 0x5EA; result stored in existing `u8 *` field |
| Unlocked | `TLobby__sub_80426AAC` | MessageTransport / 0xFEC | Guarded positive length at most 0x5EE; result returned as a native word |

The misc caller already declares the locked helper as `u8 *(u32)`. Message
transport declares it as `s32(void *)`, and declares the unlocked helper as
`s32(s32)`. The mode-dependent wrapper also returns another provider's word in
its mode-1 branch. One pointer-producing branch does not establish a pointer
return contract for the whole wrapper; preserve its `s32` interface and guards.
This is bounded source/relocation evidence, not a historical shared API or
ownership proof for unseen or dynamically constructed calls.

## Combined probe rejected and restored

One source-reviewed probe shared both producer declarations, migrated the locked
caller's pointer-only temporary to `u8 *`, removed the copy-count pointer
round-trip, and made the unlocked branch's pointer-to-word boundary explicit.
The misc caller used the shared header instead of its duplicate declaration.
Local order, existing padding, producers, bounds, lock timing, selection, copy
and lookup sequence, writes, sends, null handling and cleanup were retained.

Native validation rejects that combined probe. `post_send_message` grows from
140 to 144 bytes, with changed register allocation and length-extension code.
The misc object also changes generated local-symbol reference targets. No
normalization or compensating source forms are accepted. Exactly those two
objects change among 3,665, and the DOL SHA-1 becomes
`75d524554ba2dcc732f67f960daa52558917433d`.

Restore all three source inputs exactly and rebuild through the capacity gate.
All 3,665 compiled objects and the original DOL return to their prior bytes.
The locked migration and misc-header change remain restored and held. No
alternative local type, lifetime, copy expression, alias or compiler setting is
tested to compensate for this failure.

## Independently matching unlocked subset

The preserved combined-probe object provides discriminating evidence for the
separate unlocked interface: its 220-byte `TLobby__sub_80426AAC` function and all
four relocation tuples are identical to the baseline. Independent review
confirms that this can justify an unlocked-only probe, not acceptance of the
combined change or a replacement form for the locked caller.

Share only `u8 *TLobby__sub_80425640(u32)` with C linkage in the already-used
`NetworkPacketPool.h`. Remove its wrong local declaration and convert only the
allocator branch explicitly to the wrapper's existing native-word result:
`ret = (s32)TLobby__sub_80425640((u32)len)`. Keep every guard, other branch and
producer operation unchanged. The locked helper, caller temporary/copy expression,
misc declaration, adjacency and other private interfaces remain untouched.

This separable probe passes. Owner, provider and runtime complete objects are
raw byte-identical; all 3,665 compiled-object hashes are unchanged, without
normalization. The original DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental metrics, coverage and
retention have zero drift. Full sealed-main no-loss checks pass: 3,599 exact
linked units, 18,428 retention entries without drift, existing +88 data bytes and
no new function/code gain or loss. Ordered providers remain 3,599 source inputs
and 1,347 original fallbacks. All fourteen host tests pass. Independent source
and native review passes; final exact-head review gates publication.

Only the unlocked allocator declaration is repaired. The locked migration,
adjacency, other output-pointer questions, private creator/raw callback/reset
ABI and metadata holds remain. Keep draft.
