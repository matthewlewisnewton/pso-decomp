# Socket protocol runtime recovery

The unit owns text `0x8041ED8C..0x80421620`, data
`0x804FD890..0x804FD948`, and BSS `0x805C1DF0..0x805C1E00`.
The data boundary includes the four compiler-generated switch tables in emitted
order; the last 88 bytes previously belonged to the following automatic split.
No table is written by hand.

## Bounded C++ candidate for PR 457

The candidate based on `b85d436d3e` builds and links. Eighteen of the 21
functions match. The data and BSS match. The linked DOL differs from the
original at 17 instruction words, all in the three functions below. Objdiff
scores the text at 99.8325%. The project checksum gate therefore fails.

| Function | Size | Differing linked words | Source change |
| --- | ---: | ---: | --- |
| SACK update, `0x8041FED4` | 292 | 1 | Shift from the next valid range and clear the last slot. |
| ACK, `0x8041FFF8` | 1,048 | 6 | Complete the request, reload the head after the callback, and seek the cursor using the entry size. |
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
entries and clears the trailing entries. Compiling the bounded checkpoint
`f1b968a945` with 20 installed GC compiler releases produced no better code
for these three functions. GC/1.2.5n preserved 18 exact functions, the most
of any release tested. With that compiler the bounded loop compares the index
to 4.
[lwIP SACK implementation](https://github.com/lwip-tcpip/lwip/blob/master/src/core/tcp_in.c)

**ACK frame.** The two operations at a completion boundary must stay ordered.
The callback can change the ring head. The candidate snapshots the new head
before copying the ring descriptor and uses that index to find the entry.
The compiler allocates the original 96-byte frame with ordinary live buffers.
The browser debug build below uses a signed queue index in both lookups. The
candidate reads that index after the first descriptor copy and before the
post-callback copy. Both lookups advance by `sizeof(TcpSendRequest)`. The two
zero comparisons and the call arguments now match. The only six differing
instructions address the FIFO destination at stack offset `0x24` where the
original uses `0x14`. A diagnostic grouping the socket handle and a snapshot
of the ring index in a local record matched all 1,048 bytes. I found no
independent consumer or shared type for that pair. The candidate retains
separate operations. The fork's PPP implementation provided the precedent
for testing consumed inline results and buffer lifetimes.
[PPP frame recovery](https://github.com/matthewlewisnewton/pso-decomp/commit/f777b125078ab4f027eedb8936f12d2693384108)

**Gatherer.** Upstream's gatherer reproduced the original 1,984 bytes using
both C and C++ with GC/1.2.5n. Its prepend loop decrements its pointer before
testing whether the prefix is empty, and again after consuming element zero.
The candidate reads `source_end[-1]` only while an element remains. It then
decrements `source_end` to that valid element. All ten differences are in
that loop at `0x804209FC..0x80420A4C`. Reusing the request and partial
indices across both branches, as in the browser debug build, left the
compiled function unchanged. The other fragment walks and the final
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
full-TCB SACK comparisons. A separate symbolic check of the changed PowerPC
compaction loop for initial indices 1 through 4 found identical final values
for every TCB word and every register live at the common exit. It models the
TCB as ordinary RAM. Both DOLs are 5,233,088 bytes. The candidate SHA-1 is
`d03a4023b996c22630fc45048ae69ce8098016f0`. The original is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

## Comparison with the browser's AVE-TCP debug build

The same GPOE8P Rev 2 disc contains two NetFront browser executables. Both
the game and release browser identify their middleware as AVE-TCPv6.0 for GC
1.16.1, built on October 23, 2002 at 17:47:54. The debug browser identifies
`avetcpD.a` 1.16.1, built at 17:47:26 that day. All three name SDK
`12Dec2001Patch3`. ACCESS also identifies Episode III as a consumer of the
same middleware family. The measurements below use only the owned I & II Plus
disc. [ACCESS announcement](https://www.access-company.com/news_event/archives/20030613-2/)

| Executable and SHA-1 | SACK entry (bytes) | ACK entry (bytes) | Gather entry (bytes) |
| --- | --- | --- | --- |
| `PsoV3.dol` · `0d85744b51d7379efb025a943d0cd5aaae2191a3` | `0x8041FED4` (292) | `0x8041FFF8` (1048) | `0x80420410` (1984) |
| `iwanaga.dol` · `4fbc45e48519f07b9b161debf0078db24c5aa24c` | `0x80152994` (292) | `0x80152AB8` (1048) | `0x80152ED0` (1984) |
| `iwanagaD.dol` · `0fc3904718e56689b248ade22ba8ee1327b0a0e2` | `0x8016B4EC` (448) | `0x8016B07C` (1136) | `0x8016A738` (2372) |

The release browser contains the game SACK function byte for byte. Its ACK
differs at 16 relative calls and two words materializing the protocol-state
address. Its gatherer differs at 42 relative calls. The debug browser has
different code and function order. The five-entry table, the 65-position
request ring, the 12-byte fragment stride and the ordering of callbacks and
buffer operations identify the three debug routines.

**Receive.** The release browser's 1,128-byte receive routine at
`0x80151CC4` matches the game routine at `0x8041F204` after normalizing
direct calls and the address loads for protocol state and the two switch
tables. The debug routine at `0x8016C080` takes a packet, a 16-bit unsigned
skip and a control block. At `0x8016C1AC..0x8016C1D0` it compares the
pending read capacity with the remaining fragment length as unsigned
counts. The taken paths recalculate the selected count into the same
register, at `0x8016C1E4` and `0x8016C27C`. The C++ uses that one transfer
count for the copy and for the cursor updates. It reproduces all 1,128
retail bytes in the full translation unit. The linked DOL has the same
SHA-1 as the 17-word candidate above. Host fixtures exercised header skip,
FIFO wrap, completion, callback reentry and a closed receive under address,
bounds and undefined-behavior sanitizers.

The receive completion provider at `0x80422368` takes a signed halfword
slot index and passes a public socket handle to its callback. The two use
different representations for UDP and the same value for TCP. In the
debug build, the UDP callback record receives tag `0x400` at `0x8016F038`.
The UDP socket constructor returns a handle with that tag at `0x8016F208`.
The shared event dispatcher applies the other socket tags and validates the
unchanged TCP index at `0x8016DDE4..0x8016DE08`. The TCP completion path
sign-extends the index for the table at `0x8016EA4C` and prepares a separate
signed callback handle at `0x8016EA70..0x8016EA84`. Using the same tag
encoder for TCP and UDP gives all 56 release instructions with the unit's
standard settings. The whole callback-provider object, including its
relocations, remains byte-identical at SHA-1
`e0f85ba99db49669350a054ee8db7da8ee27053c`.

**SACK bounds.** The debug routine calculates the source at index `k+1`
and the destination at index `k`, both from `TCB+0x2F8` with stride 8.
It compares the signed loop index with 5 at `0x8016B658`, then clears slot
four. Its neighboring SACK expiration routine uses the same pair of indexed
addresses and compares the shift index with **4** at `0x8016B74C`. This
distinction survives two compiler configurations and supports a source-level
off-by-one in the update. With the range pair documented above, Unicorn
observed the reads at `TCB+0x320` and `+0x324` in both browser builds. The
debug PCs are `0x8016B640` and `0x8016B644`. All three disc executables and
the bounded candidate produced the same complete control block. The candidate
made zero reads from those two fields.

**ACK locals.** The debug frame is 112 bytes. The request is at stack +48,
its buffer reference at +24, the ring cursor at +40 and the FIFO destination
at +16. The queued path initializes three kind bytes at +44, +36 and +28.
The store to +36 at `0x8016B0E8` is the only direct access to the +32..+39
slot, and its address is never passed. The spacing and three equal kind
values support an extra buffer-reference initialization in the original.
The clean candidate needs only the live descriptors. The debug code keeps
the signed 16-bit socket handle and ring-head snapshot in separate registers.
It snapshots the ring head **after** the initial descriptor copy at
`0x8016B124`, then **before** the descriptor copy following the callback at
`0x8016B1D4`. Both local zero tests use signed compares, while the unsigned
field is compared to 64 for ring wrap. These observations give a source
hypothesis for a signed local index. The original local declarations remain
unknown.

**Gatherer.** One debug register holds the index initialized to -1 at
`0x8016AAA4` and assigned the first request index in the other branch at
`0x8016AC18`. The gatherer uses this value to calculate its shift indices,
start the scan at the index plus one (`0x8016ADA4`), test the reverse loop
(`0x8016AE7C`), and select the trailing buffer (`0x8016AE98`). The debug
cursor steps back 12 bytes before checking for an empty prefix at
`0x8016AE10` and again after each copy at `0x8016AE74`. The port candidate
keeps its cursor within the array. At `0x8016AE58..0x8016AE60` the debug
routine stores the fragment length as a halfword, sign-extends it and adds
it to the packet total. The debug partial-fragment branch reads
`fragments[partial_fragment].length` at `0x8016B03C..0x8016B044`. Applying
that expression and both debug loop bounds to the bounded source produced
1,988 bytes, with 38 differing instruction words in aligned object
comparison. The 1,984-byte candidate retains the retail load at offset
`0x2C` in this unreachable branch.

The same 2,400 gather and 1,600 ACK cases described above also agreed
between the game and debug browser. The ACK comparison included 1,717
callback events with the same simulated reentry. These comparisons used
the debug executable's own buffer helpers, its registry at `0x804E6A28`
and completion dispatchers at `0x8016EDF4` and `0x8016E50C`.

**Reproduction.** Set `disc` to the Rev 2 disc image, and make the project's
`dtk` and `powerpc-eabi-objdump` available on the shell path. With Unicorn
2.1.4 available to Python, the checker verifies the input hashes, traces
the adjacent reads and checks all `0x544` final bytes against the expected
result. Omit `--candidate` to run the disc-only comparison.

```sh
dol_dir=$(mktemp -d)
for name in PsoV3 iwanaga iwanagaD
do
    dtk vfs cp "$disc:files/$name.dol" "$dol_dir/$name.dol"
done
python3 tools/probe_socket_sack.py "$dol_dir" --candidate build/GPOE8P/psov3.dol
powerpc-eabi-objdump -D -b binary -m powerpc:common -EB --adjust-vma=0x8000d760 \
    --start-address=0x8016a738 --stop-address=0x8016b788 "$dol_dir/iwanagaD.dol"
```

The debug DOL's second text section starts at file offset `0x25A0` and
virtual address `0x8000FD00`, giving the address adjustment used above.

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
