# DHCP message, receive and parser contracts

## Scope and provenance

This is the remaining DHCP source-contract family from frozen PR #303 head
`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98`. It is explicitly stacked on
PR #434, `309836d175006800bf2a5d221649f6910cb9598d`, which in turn starts at
fork main `cda82a7aad7de1bf9b86470002df3f68d1c8c039`. `DhcpAccessors.h` and
its setter, hostname, lease, router and domain contracts remain the unchanged
prerequisite. `DhcpClient.h` includes that header rather than redeclaring them.

Original message/header work is by Matthew Lewis Newton, with the retained
`Co-authored-by: Cursor <cursoragent@cursor.com>` attribution in commits
`2f90b2977176ad4a692d31c578352c0a8d4f0375` and
`891d16a8f20ebeb0062411582efdf9fc23aeaa7a`. Shared-layout and later contract
work is from Codex commits `3a74db95a`, `ab7da74eb`, `460ce612d`, `4f029010a`,
`adc1a464e` and `ac0a1995b`. The actual-source characterization tests come
unchanged from the frozen head. This extraction claims no newly recovered
function, code/data bytes, or source-linked unit: all native bodies already
match and link on the baseline.

## Packet ownership and receive records

`BootpPacket` names the RFC 951 fields at their observed offsets, with the
DHCP cookie at 0xEC and total header size 0xF0. `DhcpMessage` owns 1500 bytes,
and its release/request/discover builders operate on that message rather
than pretending the storage is a TLobby. Three adjacent message regions are
outgoing, accepted reply and receive scratch, at offsets 0, 0x5DC and 0xBB8;
the buffer object is 0x1194 bytes. Header/region offsets and extents are checked
at compile time. Existing expressions, options and control paths are retained.

Raw IPv4, raw IPv6 and UDP event producers at 0x80421938, 0x80421AD8 and
0x80421F10 use the same eight-byte prefix: signed halfword flags at +0,
signed halfword length at +2, and a native pointer at +4. Their distinct
address/port tails stay separate and have offset/size checks. Dispatcher
0x80421FB8 and DHCP callback 0x804249F0 share only this record prefix. The
inherited local raw callback signature and cast remain provisional and
unchanged; a shared record does not prove its callback return/argument ABI.

DHCP state, step and reply words use shared volatile declarations. The step
word has 32 original relocation references, confined to the two DHCP units.
Volatile preserves the observed accesses; it does not establish atomicity,
thread synchronization or lifetime ownership.

## Parser and request interfaces

The lease routine at 0x804245E4 immediately interprets its argument as cookie
and option bytes. Its two callers, configuration parsing at 0x80423440 and
the renewal/rebinding step at 0x80423E80, supply that storage. It is now the
C-linkage `dhcp_parse_lease_times(u8 *)`, not a false TLobby method. The three
message builders likewise receive real `DhcpMessage` objects.

All 13 original references to the option scanner at 0x80424830 are in these
two units. The shared return is s32, matching its callers' word consumption;
its byte-loaded result is always 0..255. Zero remains ambiguous between no
match and a matched zero-length option. No scanner algorithm changes.

The borrowed output slots at 0x805D7B40/44/48 each hold one native pointer.
The sole upstream caller supplies an address word, a subnet word pointer and
a local broadcast word. Configuration parsing writes through each optional
pointer and then clears it. The shared request declarations use s32 pointers
for these outputs. Blocking request 0x80424D58 returns s16, consistent with
its sole caller's `extsh.` at 0x80146664 and results {-1, 0, 1}. Registration
0x80424DCC retains s32, consistent with its sole caller's word comparison at
0x80424D6C. Failures retain the borrowed pointers until reset, just as before.
Unused opaque arguments stay opaque. This does not claim unique recovery of
original typedefs.

## Original behavior deliberately retained

Event 0 provides scratch without capping the signed received length. The
dispatcher permits a callback reduction and copies fragments, but this is not
DHCP bounds validation. ACK states 2/4/5 copy exactly the event length into
the persistent reply and keep only the bytes plus a flag. There is no stored
accepted-reply extent and no tail clear. Subsequent parsers receive pointers
without lengths. The scanner's signed base-minus-cursor test is not a forward
bound. Header reads, fixed option-table copies, stale output pointers/bytes,
short-receipt stale options and original error/state transitions are preserved.
The prerequisite's low-16-bit hostname acceptance is unchanged.

The seven scanner/setter cases and five ACK-chain cases compile actual source
function definitions, not rewritten algorithms. The ACK fixture compiles six
actual functions with synthetic services and storage. Tests exercise stale
reply/lease behavior for states 2/4/5 and a complete synthetic receipt. Every
executed access has allocated storage. Event-0 exceptional lengths are never
passed to event 1. These are host characterization, not native ABI, wire
endianness, ingress reachability, exploit, or safety proofs.

## Validation and remaining boundaries

The capacity-gated native build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Full PR checks against both
immutable baselines have zero change to 27,438 matched functions, 4,237,032
matched code bytes, 1,477,195 matched data bytes, 3,862,972 complete code
bytes and 1,354,111 complete data bytes. All 3,606 linked units are exact;
18,575 retention entries have no missing/stale entry. Splits and linkset are
unchanged. Ordered linker providers remain 3,606 compiled and 1,340 original.

All 3,632 active source objects and 4,946 active original objects are compared
completely against both bases. Incrementally only two source objects differ,
with unchanged complete code/data, symbol order, metadata and raw relocations
after mapping the 16 explicitly address-preserving DHCP names: three builders,
the lease parser and twelve state/lease globals. Original regenerated objects
also allow only symbol string-table entry order, retaining every mapped string,
symbol record and relocation. Combined comparison additionally includes #434's
single domain-function rename. No arbitrary relocation or section normalization
is used. The original reference closure has one provider per audited symbol,
13 scanner calls, two lease-parser calls, and one caller each of configuration
parsing, blocking request and registration.

NetworkPacketRuntime remains 24/24 functions, text_80421620 42/42, and the
upstream lobby caller 40/40, each exact in code/data and source-linked. All
321 host tests, four existing portable suites, and ASan/UBSan runs of both
the 15 DHCP cases (including prerequisite hostname tests) and portable suites
pass. Initial sandbox-only Wibo/LeakSanitizer execution failures were resolved
by permitted native execution; no source workaround or disabled check was used.
Generated exception inventory changes only an existing expression's line number.

Timer-registry repairs, SDK thread/queue work and packet allocator contracts
remain separate. This patch preserves queue declarations for that owner. The
locked allocator, failed queue-adjacency probe, private creator/reset ABI and
unresolved raw-IP callback contract stay held. No new pragma, assembly,
compiler override, fallback provider or bug hardening is introduced.
