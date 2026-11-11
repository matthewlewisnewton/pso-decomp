# DHCP hostname declaration and legacy behavior

This is a distinct contract audit at branch `069d9beb5` and main `f8a71fae8`.
It does not retry the rejected allocation, queue-adjacency or private ABI probes.
The target is the C-linkage hostname setter `TLobby__sub_8042455C`, address
`0x8042455C`, size 0x80. Preserve the old code, bugs included.

## Source and native boundary

The producer TU defines and locally declares `s32(void *)`; the sole source
caller locally declares `s16(void *)` and passes a `char *` name. Scanning all
5,021 original split objects finds one zero-addend `R_PPC_REL24`: misc
`TLobby_801461EC.o`, offset `0x430`. Native call `0x8014661C` immediately
extends the low halfword with `extsh.` for the signed negative-status test.
The original DOL has that one direct call and no aligned absolute pointer word
to this target. This bounded scan does not exclude synthesized addresses or
external consumers and does not recover an original typedef.

The setter returns only literal zero/-1. Null input clears then sets the volatile
diagnostic to 1 and returns -1. Otherwise it computes the full string length
before checking `(u16)length < 0x20 && (u16)length != 0`. Accepted input calls
the option setter with ID 0x10 and `(u16)length`, ignores its result, and returns
zero. Rejected input sets diagnostic 1 without changing prior hostname storage.
The caller's empty-name bypass and all other caller operations stay intact.

Original option 0x10 is string kind 0, fixed size 32, targeting `dhcp_hostname`
at `0x805C3094`. Its configured storage is 44 bytes; reset clears 32 bytes, and
three DHCP builders later read it. The generic setter copies the table's full
32-byte extent, then inserts a terminator using the narrowed length. It does
not copy only `strlen` bytes or add a source/destination bound. Do not infer a
new capacity, ownership, lifetime or ingress-safety contract from these facts.

## Independent type and behavior controls

Nine isolated controls use the actual hostname body, `types.h`, volatile
diagnostic and dependent declarations, and actual native compiler commands:
GC/1.2.5n `-O4,p -inline off` for the producer; GC/2.6
`-O4,s -inline off -sdata2 4` for a full copy of the caller TU. Existing workspace
and exclusive capacity locks cover execution, with production inputs/outputs
unchanged. Four producer controls vary result width (`s32`/`s16`) and input
representation (`void *`/`char *`) independently. All reproduce the complete
128-byte function and relocation tuples with a 24-byte frame. Both short-result
caller controls reproduce its 308-byte function and relocations; word-result
controls retain size and relocations but change the signed status check.

An explicitly negative control replaces only the two 16-bit length checks with
full-width checks. It stays 128 bytes but changes native instructions. It is
never applied to production. Equal size is insufficient evidence of equivalence,
and the narrowing cannot be silently removed as cleanup or hardening.

Three original-free host tests extract the actual hostname setter, option setter
and option record. Fully allocated fixtures exercise null and lengths 0/32/
65,536/65,568 rejecting without clearing old storage; short names of length
1/31 still copying 32 bytes including data after the terminator; and lengths
65,537/65,567 accepting after low-16-bit narrowing. The latter copy 32 bytes
and terminate at offset 1/31. Bytes beyond the fixed destination extent remain
unchanged. These are host characterizations with stubbed memory/string helpers,
not native ABI, packet reachability, exploit or safety claims.

## Accepted bounded repair

Share one C `s16 TLobby__sub_8042455C(char *)` declaration in `DhcpClient.h`.
Remove both incompatible local forwards and change only the definition signature.
Retain its whole body, casts, full string-length evaluation, narrowed checks,
setter argument, fixed-copy behavior, diagnostics and caller. The mutable byte
pointer agrees with the current setter interface; no speculative const migration
or other API change is included. Symbols, configuration, compiler settings,
providers, force-active entries and layouts do not change.

The first candidate passes the capacity-gated native build and reproduces the
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,630
active compiled objects are **raw byte-identical**, including complete metadata,
code/data/debug sections and raw relocations; all 3,665 cached compiled-object
entries also retain their hashes. No normalization is used. Incremental checks
show zero metric, coverage or retention drift. Full sealed-main no-loss checks
pass: 3,598 exact linked units, 18,440 retention entries without drift, existing
+88 data bytes and no new function/code gain or loss. Ordered providers remain
3,598 source and 1,346 original fallbacks. All seventeen DHCP/modem host tests
pass. Independent source/native/control/harness review passes; exact committed
head review gates publication. Lease/router/domain repairs remain intact.

## Remaining holds and evidence that could reopen them

- **Locked allocator:** the prior combined typed migration changed instructions
  and local-symbol references and was restored. See
  [allocation evidence](pr303-packet-allocation-contracts.md). A new discriminating
  source/compiler or authentic declaration lead must explain the observed
  length-extension/register effects before another candidate; no compensating
  temporary, copy-expression, alias or compiler-setting variant is justified.
- **Queue adjacency:** the direct SDK queue probe changed instructions and
  relocations and was restored. See [receiver evidence](pr303-post-message-receiver.md).
  A truthful aggregate/array declaration or a newly recovered native indexed
  producer establishing that relationship would be useful; neighboring addresses
  and three independently valid SDK queues alone do not prove one aggregate.
- **Raw callback:** require a concrete registration store and target body/ABI.
  Dormant tables and classified neighboring aliases do not establish a live
  writer or callback signature.
- **Private thread creator/reset status:** isolated compiler controls explain
  previously observed differences but do not establish the historical private
  signature. Seek an authentic declaration for the pinned AVE version or a new
  distinguishing producer/caller/return-domain observation; retain the rejected
  shared-contract forms. The literal-zero init-family inventory does not resolve
  historical width and is not new reset evidence.
- **Metadata:** the old title/body update failed with no returned error payload.
  The original action error/approval diagnostic for call
  `exec-c61c1547-9e55-4353-bf50-dd0e3f3f5758` is still missing. Do not retry,
  change permissions or switch routes without that evidence. Technical progress
  comments are separately authorized.

Main and branch remained stable during this audit; no competing branch changes
were observed. No existing hold is lifted by the hostname repair. The scanner
remains lengthless and retains its characterized behavior. Keep draft.
