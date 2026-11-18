# Socket protocol runtime recovery

The unit owns text `0x8041ED8C..0x80421620`, data
`0x804FD890..0x804FD948`, and BSS `0x805C1DF0..0x805C1E00`.
The data boundary includes the four compiler-generated switch tables in emitted
order; the last 88 bytes previously belonged to the following automatic split.
No table is written by hand.

## Bounded C++ candidate for PR 457

The candidate based on `b85d436d3e` builds and links. Eighteen of the 21
functions match. The data and BSS match. The linked DOL differs from the
original at 23 instruction words, all in the three functions below. The
project checksum gate therefore fails.

| Function | Size | Differing linked words | Source change |
| --- | ---: | ---: | --- |
| SACK update, `0x8041FED4` | 292 | 1 | Shift from the next valid range and clear the last slot. |
| ACK, `0x8041FFF8` | 1,048 | 12 | Complete the request, reload the head after the callback, and seek the cursor using the entry size. |
| Send gatherer, `0x80420410` | 1,984 | 10 | Index the two fragments in each swap and shift. Prepend from the end of the consumed prefix. |

**SACK bounds.** With `last_reasm = 0`, a new range of `[100,160)` and an
existing range of `[110,120)`, the original PowerPC instructions at
`0x8041FF9C` and `0x8041FFA4` load TCB offsets `0x320` and `0x324`.
A memory-access trace in Unicorn 2.1.4 observed both loads, a copy to
the fifth slot, and the subsequent clear. The candidate skips that copy
and produces identical final contents for all `0x544` bytes of the TCB.
Only the immediate at `0x8041FFBC` changes, from 5 to 4. Upstream's TCP
initializer clears five ranges, then writes `seg_top = -1` separately.
Its send scoreboard also uses `una` independently. The initialization
and the send-side operations support the five-entry layout.
[Upstream TCP source](https://github.com/zeroz41/pso-decomp/blob/c09673abce55daff9907737bf705005921db0ec1/src/pso/network/NetTcp.c)

Bounded source-index and destination-index loops, a one-past pointer, a
counted move, a guarded final assignment, and clearing through the final
iterator all produced different code. lwIP's SACK code also compacts valid
entries and clears the trailing entries. I compiled two earlier versions of the full unit with 20 installed GC compiler
releases. GC/1.2.5n preserved 18 exact functions in each, the most of any
release tested. With that compiler the bounded loop compares the index to 4.
[lwIP SACK implementation](https://github.com/lwip-tcpip/lwip/blob/master/src/core/tcp_in.c)

**ACK frame.** The two operations at a completion boundary must stay ordered.
The callback can change the ring head. The candidate snapshots the new head
before copying the ring descriptor and uses that index to find the entry.
The compiler allocates the original 96-byte frame with ordinary live buffers.
Six instruction words use stack offset `0x24` for the FIFO destination where
the original uses `0x14`. Two comparisons with zero use the unsigned head
type, and two pairs of instructions set up the same call arguments in a
different order. A diagnostic grouping the socket handle and a snapshot of
the ring index in a local record matched all 1,048 bytes. I found no
independent consumer or shared type for that pair. The candidate retains
separate operations. The fork's PPP implementation provided the precedent
for testing consumed inline results and buffer lifetimes.
[PPP frame recovery](https://github.com/matthewlewisnewton/pso-decomp/commit/f777b125078ab4f027eedb8936f12d2693384108)

**Gatherer.** Upstream's gatherer reproduced the original 1,984 bytes using
both C and C++ with GC/1.2.5n. Its prepend loop decrements its pointer before
testing whether the prefix is empty, and again after consuming element zero.
The candidate reads `source_end[-1]` only while an element remains. It then
decrements `source_end` to that valid element. All ten differences are in
that loop at `0x804209FC..0x80420A4C`. The other fragment walks and the final
signed halfword addition match. Offset and length are unsigned byte counts
as in upstream. The fork's sole caller in `TcpProtocol.cpp` rebuilt to the
same object bytes as the clean main baseline.
[Upstream gatherer](https://github.com/zeroz41/pso-decomp/pull/305)

**Checks.** The original and rebuilt PowerPC DOLs produced the same results in
2,400 gather cases and 1,600 ACK cases. The gather comparison covered return
values, all output packet and TCB bytes, and the request ring. The ACK comparison
also covered data buffers and completion events, including callbacks changing
the head. The emulator used the game buffer routines and intercepted the two
completion notifications for the ACK comparison. Focused host cases passed
with address, undefined-behavior and bounds sanitizers, including 200,000
full-TCB SACK comparisons. The candidate DOL SHA-1 is
`4fe6f3a8b8f49ed9b7d82d7e915f8316f66cc9ba`. The original is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

## Published integration at b85d436d3e

The local integration on fork main `9ab744a4ec` keeps main's upstream-derived
out-of-order receive queue and uses its shared `TcpTcb` layout for the three
new socket bodies. All three current TCP callers of the ACK routine use its
shared signature. The partial send length is a `u16` because the output field
stores its low halfword and the total adds that halfword interpreted as signed.
Declaring it before the total preserves the generated registers and instruction
schedule without a wider integer. The send-thread resume call uses the
provider's signed 32-bit handle, also with identical emission.

The integrated object matches all 21 functions, 10,388 code bytes and 200
data bytes. A native rebuild reproduces the original DOL SHA-1 and
`tools/check_pr.py --no-build` passes against a clean build of `9ab744a4ec`.
It adds three exact functions, 4,160 matched code bytes and 88 matched data
bytes. The linked-unit count is 3,621. The retention block gains six entries
and loses none. The actual linker selects the compiled socket and TCP
objects. The rebuilt TCP and callback-provider objects are byte-identical
to their current-main counterparts.

The source now keeps five SACK ranges and copies from the enclosing control
block's byte representation. The last copy reads bytes `0x320..0x327`
containing `seg_top`, its padding and `una`, then immediately clears the
destination. The intrinsic expands to the native two-word copy. Separate
destination-index and byte-offset updates reproduce the induction registers.
An explicit byte cursor differed in 20 instruction words; a numeric byte
offset reduced the difference to four; giving the destination its own index
preserved the native order of those four instructions. The final function's
73 instructions and the entire compiled socket object are unchanged.
The portable copy passed 200,000 deterministic cases under address,
undefined-behavior and bounds sanitizers, with whole-block comparison against
a bounded reference, including wrapped sequence numbers and randomized
adjacent state.

Native ACK frame offsets are `0x14` for the destination, `0x1C` for the
request reference, `0x2C` for the cursor, `0x34` for the request and `0x4C`
for the saved registers. No native instruction refers to the eight bytes
at `0x24..0x2B`. Removing that space changes 22 words, all frame setup,
restore or stack offsets for the cursor, request and saved registers.
An older matching reconstruction, upstream `82cb898ff1`, also had a reserved
eight-byte local, and `7f406a2a68` dropped that match. The later upstream C
implementation still reserves that space. This branch classifies it as
CodeWarrior frame space and excludes it from portable builds, following
the checked-in TCP output frame precedent in [TCP protocol
unit](tcp-protocol-unit.md). The original reason for the gap remains unknown.
A host harness with buffer adapters passed focused ACK cases covering ring
index wrap, partial request writeback, ordered completion callbacks, FIFO
wrap and insufficient space under the same sanitizers.

All three recovered socket entry points now share declarations with their
callers. In particular the segmentation signature uses signed offset and
length, in agreement with its definition and the caller's `int` locals.
The entire TCP caller object remains byte-identical to current main.
Receive completion and SACK expiration also use the shared control block
directly; expiration retains its native symbol without a `TLobby` pointer
cast or a competing declaration.

The input caller supplies an active table entry and a halfword payload skip
derived from the network and TCP header lengths. The output caller starts
with an empty fragment list and passes signed offset and length. It handles
a negative segmentation return by clearing the output count and total.
Focused host receive cases checked skipped bytes, FIFO wrap, partial request
completion, synchronous callback reentry and closed receive. Focused
segmentation cases checked FIFO and queued ring wrap, pending-fragment splits,
fragment offsets and an out-of-range offset. The harnesses used buffer and
callback adapters and mapped native address cursors to host-width integers.
The native call census finds the receive-resume symbol only in the TCP and
socket runtime objects. Both source callers use a signed halfword handle.
The provider truncated its handle before both table lookup and callback, so
the shared interface now declares the halfword directly. Widening the
caller changed the receive routine. Narrowing the provider instead and
keeping its word promotions distinct under scoped `opt_common_subs off`
preserves all 56 native instructions and the complete provider object.
The targeted host checks do not exhaust the caller domain. The recorded
native ACK frame space remains a point for source review.

## Checkpoints and current status

Historical validation below belongs to published head
`7817d00f0f525a2324a9fb225eb29d2418dac9cd`, based on fork main
`1e8cf6d437b6ac2216d5cf41f3c296950f6d819e`. Its original starting baseline
was `ead31005e05c515068799f79935dca70ea241206`. These receipts do not validate
later integration or source changes.

The narrow intermediate production-source checkpoint is
`664b2d2c4e96dc48a555d4f0917b69a39ae7b63f`: published head `7817d00`
merged with pinned fork main `5146327538ef67c0077c30664309f9cd48fabc86`,
plus removal of one unused conflicting ACK declaration. This lineage retains
the published `sack[6]` representation as an **unresolved source hold**. It does
not include the later byte-copy repair. Its declaration cleanup and main merge
have source-scoped review. Fresh validation of descendant
`c597ac3356934e15a99af39eb5cbc34ea9c9bcd9` is recorded below; final scoped
review is still required before intermediate publication. This is not a
readiness claim.

The separate research checkpoint
`80985201fd2bfc3fa72b718149f41b75338acafe` includes the five-range/adjacent-field
byte-copy repair from `9f2f2350`. Its fresh native build failed the original DOL
checksum. `0x8041FED4` changed from a 292-byte leaf function to 332 bytes with
a `memcpy` call, stack frame and saved registers. The other twenty socket
functions remained exact. A 160-case host test against an instruction-level
original-function oracle passed with undefined-behavior/bounds sanitizers, but
that limited behavior evidence does not establish exact native emission or the
four main bodies' complete caller/domain behavior. The failed native root and
receipts remain preserved; this repair is excluded from the intermediate line.
No truthful matching replacement is established.

Open source holds include the unsupported sixth SACK subobject, unused
eight-byte ACK frame local, segmentation's emission-only `s64` widening, and
complete caller/domain and behavioral closure. The earlier capacity-rule
incompatibility has a separately reviewed checkout-local wrapper at
`57d92a7493b90020020c6d409d91aa42c1cb3ece`; it permits only the pinned profile
through fresh exclusive preparation, exact graph review and `--legacy-frozen`
execution. This tooling result does not clear any socket source hold. Native
DOL, no-loss, complete-object/provider/relocation and retention results must be
attributed to their actual source, baseline and external gate checkpoints.

At historical head `7817d00`, the report recorded 21 matching functions,
10,388 code bytes and 200 data bytes, compared with 17 functions, 5,064 code
bytes and 112 data bytes before recovery. The four recovered bodies were:

| Address | Bytes | Behavior |
|---|---:|---|
| `0x8041F204` | 1,128 | Consume receive fragments into the waiting read or receive FIFO. |
| `0x8041F914` | 1,164 | Insert received sequence ranges, merge overlaps, and update SACK state. |
| `0x8041FFF8` | 1,048 | Retire acknowledged send bytes and finish queued send callbacks. |
| `0x80420410` | 1,984 | Construct outgoing fragments from the send FIFO and queued requests. |

## Layout and ABI boundaries

`TcpControlBlock.h` replaces the overlapping TCP prefix views used by this unit.
Its `0x544` allocation stride, packet offsets, range table, callback fields and
capacity offsets are checked against the accesses and indexed walks in this
unit and `TcpProtocol.cpp`. Sequence numbers and range endpoints use unsigned
32-bit subtraction followed by a signed comparison, preserving TCP wraparound.

Five SACK ranges are active. Native `0x8041FED4` also reads the adjacent eight
bytes at `0x320..0x327` on the last compaction iteration before clearing range
four. Other native TCP helpers use a signed-halfword index at `0x320` and
separate word state at `0x324`; the read does not establish a sixth range
subobject. This intermediate lineage retains the published `TcpSackRange
sack[6]` view unchanged and explicitly unresolved. It must not be described as
a verified or truthful shared layout. The separate bounded byte-copy proposal
avoids that subobject claim but did not reproduce native code, as documented
above. No aliasing cast, guessed union or compiler steering replaces it here.

The send-request callback is shared with its actual provider in
`text_80421620.cpp`: signed 16-bit handle and status, and a typed 16-byte request.
The provider retains a signed 32-bit local handle. Historical head `7817d00`
reported all 42 provider functions exact. `TcpProtocol.cpp` calls `0x8041FFF8`
with the control-block pointer instead of integer arguments. Its compiled source
object was unlinked: the historical linker selected the original TCP object.
DOL equality therefore does not validate that source change; complete compiled
object and reference comparison remains required.

Other boundaries remain provisional: the global TCP runtime is only a pointer
and count prefix here, while older providers retain different partial views.
The slot/thread resume helpers still have legacy handle-width declarations;
consolidating those providers changed native bytes in the bounded probes.
UDP prefix and packet views, explicit legacy ABI symbol names, and provisional
`TLobby` wrappers are inherited. Source linkage does not establish their
original class ownership or make these interfaces portable.

## Historical compiler constraints and unresolved source evidence

The following describes the reconstruction at historical head `7817d00`,
retained in intermediate source checkpoint `664b2d2`. Matching emission does not establish
that its frame/type/optimizer constructs reflect original source. In particular,
the unused ACK local and `s64` widening remain source-truth blockers.

Historical builds used GC/1.2.5n with the existing AVE-TCP profile and unit override `-inline on`.
The range-removal helper must inline. Its caller-owned eight-byte range value
preserves the reassembly function's native frame; no separate helper body is
emitted. Scoped `dont_inline` controls preserve the other native call boundaries.

`0x8041FFF8` uses scoped `opt_lifetimes off`, an unsigned read-index record, and
an unreferenced eight-byte local area. The area preserves the native 96-byte
frame and other local offsets; it is reconstruction debt, not proof of an
original local variable. The callback's formal 16-bit handle and its provider's
32-bit local are both needed for the original register allocation.

`0x80420410` uses scoped `opt_propagation off` because the executable retains
an otherwise unreachable partial-fragment branch with an index set to -1.
The fragment phase locals are deliberately distinct and their declaration order
preserves native register allocation. The shift counter is a named local and
is decremented before the address cursors. The packet-clear path exits the outer
scan loop and reaches its common return, rather than returning from the inner
branch.

The final partial length widens a signed 32-bit difference to `s64`. Its input
range fits signed 32 bits; the widening changes no arithmetic result. It keeps
the halfword store separate from the signed 16-bit extension in CodeWarrior.
An ordinary 32-bit local shares the extension with the store and differs in five
instruction rows. This is an emission constraint, not evidence for an original
64-bit local. The initial wrapped FIFO length uses a corresponding unsigned
halfword store to avoid an extra sign extension.

Reverse and prepend loops use unsigned 32-bit address cursors. Their final
unused decrement can precede the array; doing that with a C++ pointer would be
undefined even without dereferencing it. Only guarded valid element accesses
convert the integer addresses back to pointers. A port should use indices or
an appropriate guest-address representation, and remove optimizer/frame/type
steering while retaining the explicit halfword conversions and sequence math.

## Historical validation and required current checks

Historical receipts for head
`7817d00f0f525a2324a9fb225eb29d2418dac9cd` against base
`1e8cf6d437b6ac2216d5cf41f3c296950f6d819e` recorded full-build and
`tools/check_pr.py` PASS. Comparisons against that base and the original
starting baseline reported no loss of exact functions or matched/linked code
and data. The recorded incremental result was four new exact functions,
+5,324 matched code bytes, +88 matched data bytes, +10,388 linked code bytes,
+200 linked data bytes and one linked unit. The receipts recorded 3,619 linked
units and 18,838 retention names passing, with six retention additions and no
removals. They are historical measurements, not current checkpoint results.

Historical ordered linker inputs selected the compiled socket runtime object
and omitted its original fallback. Recorded common provider hashes were equal;
the replacement was limited to the socket object and adjacent data-gap object.
The original `TcpProtocol.o` remained the actual provider despite changed TCP
source. Historical linker logs also contain ignored `FORCEACTIVE` warnings;
current validation must compare unchanged baseline and candidate retention and
warnings rather than infer correctness from a matching DOL.

Current validation must independently establish complete affected object
sections, relocations, symbols and references, ordered source providers,
strict address-based no-loss coverage, retention, caller/domain closure and
behavioral/sanitizer results against authenticated unchanged baselines.
Function scores and raw byte equality alone do not resolve the source-truth
blockers. The original DOL SHA-1 requirement remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No
source-completion claim is made for this intermediate. Fresh native results
belong to exact descendant `c597ac33`, as recorded below.


## Fresh narrow-intermediate validation

Validated source/evidence head:
`c597ac3356934e15a99af39eb5cbc34ea9c9bcd9`.
Unchanged native baseline:
`5146327538ef67c0077c30664309f9cd48fabc86`.
External checkout-local gate:
`57d92a7493b90020020c6d409d91aa42c1cb3ece`, wrapper SHA-256
`7d68cc7603872846335f61abcbdc04c659ffa65ff7fb7169e3e10b5c371513d4`,
profile SHA-256
`9de9e5ae77e9f1601871109fbdec91b6f6772f75237ccf97d4474a97ba1c72c9`.
Both roots received fresh exclusive preparation and independent exact-graph
review before serial `--mode legacy --legacy-frozen --lane acceptance` builds.
The baseline graph SHA-256 was
`991b5249c7123a27b99172cddb4aea8eb6782e045ed7b838ec828bc73927c2c7`;
the intermediate graph SHA-256 was
`dcdf6b00b0e6d8cfe7ae8bf55135e3bb261b2a6681c674108683c2d3d95022fe`.
No live wrapper, marker or compiler-output script was changed.

The full native builds passed the original DOL SHA-1 check. The intermediate's
fresh `tools/check_pr.py --no-build` passed against the freshly built baseline:
four new exact functions, +5,324 matched code bytes, +88 matched data bytes,
+10,388 linked code bytes, +200 linked data bytes and one linked unit, with no
regressions. Current comparison denominators stayed at 27,572 functions,
4,353,092 code bytes and 1,761,176 data bytes. All 3,623 linked units were
exact; retention listed 19,183 names with six additions, no removals and no
metadata drift. The same 26 ignored `FORCEACTIVE` warning symbols occurred in
baseline and intermediate logs; passing retention metadata does not erase them.

The fresh socket source object is byte-identical to the authenticated object
from published `7817d00`. The complete compiled `TcpProtocol.o`, callback
provider `text_80421620.o` and declaration-cleanup `TLobby_804050DC.o` are
byte-identical to unchanged main, including every section, symbol and
relocation. The TCP source object's existing native mismatch remains: 40 of 45
functions and 9,756 of 19,380 code bytes match. It remains unlinked, and no
additional TCP recovery is claimed.

Ordered provider manifests reconstructed with Ninja `compdb -x link` from each
preserved executed frozen graph show 4,945 common input paths with identical
hashes. Only the socket original/source provider and adjacent data-gap provider
change. The original TCP object remains selected. These are graph-bound ordered
link-input records, not retained physical linker response files.

Address-based comparisons also passed against the authenticated historical
`1e8cf6d` and original `ead31005` reports. Their data denominators differ from
current main by 31 and 35 bytes respectively, reported as padding coverage:
file-backed intervals contain original zero bytes; other intervals lie in the
original DOL's BSS span. These differences predate this intermediate update;
there is no denominator change against current main. They are disclosed rather
than counted as recovered source data.

Fresh host/tooling tests at `c597ac33`: 346 passed. The existing portable
ASan/UBSan suite also passed with unchanged sanitizer settings. Neither suite
establishes complete behavior/domain closure for the four socket bodies. The
initial default-sandbox Wibo SIGSYS failure and LeakSanitizer ptrace failure
were retained as environment failures; successful runs used normal reviewed
escalation, without disabling checks. The separate 160-case byte-copy helper
test belongs to failed `80985201`, not to this intermediate implementation.

This evidence-only descendant changes no production source, compiler/tool code,
configuration or test inputs from validated `c597ac33`; that equality must be
bound in the final scoped review. No second native build is implied. The SACK
view, ACK frame local, segmentation widening and broader source/behavior holds
remain open, as do all five original PR303 network holds. This is a bounded
draft update, not a complete or ready reconstruction.
