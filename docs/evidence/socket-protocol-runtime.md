# Socket protocol runtime recovery

The unit owns text `0x8041ED8C..0x80421620`, data
`0x804FD890..0x804FD948`, and BSS `0x805C1DF0..0x805C1E00`.
The data boundary includes the four compiler-generated switch tables in emitted
order; the last 88 bytes previously belonged to the following automatic split.
No table is written by hand.

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
have source-scoped review; fresh exact-descendant native gates are required
before any intermediate publication. This is not a readiness claim.

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
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No current PASS or completion
claim is made here for the intermediate source checkpoint `664b2d2` integrated
with pinned main `51463275`; its actual descendant needs fresh native gates.
