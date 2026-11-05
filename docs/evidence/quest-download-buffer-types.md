# Quest download buffer types and data-only recovery boundary

The initial commit preserves the exact `QuestDownloadBuffers.cpp` source blob
from upstream [6e52d78f641e37d66845e683e8fc3f013f3c2662](https://github.com/zeroz41/pso-decomp/commit/6e52d78f641e37d66845e683e8fc3f013f3c2662)
(#168, author zeroz). It is a scoped extraction: that commit's unrelated and
already integrated changes were not replayed. Upstream #167 changes a player
function and is not a dependency. The subsequent commits recover types and
consumer accesses separately, preserving the import and attribution in history.

Fork #226 deferred this 34,912-byte range. The first recovery defined and selected
a narrower **six-object, 29,184-byte data-only unit**, from `8058DE08` to
`80595008`, and left the remaining 5,728 bytes in the automatic BSS fallback.
`QuestDownloadBuffers.cpp` now owns the whole `8058DE08..80596668` range.
`docs/evidence/quest-download-deferred-storage.md` records why that tail stays
in this unit.

The provider's complete text range and its own BSS remain unchanged: that BSS
still starts at the pool. Extending this data unit up to that address follows
the object order and that compiler signal. It is not a claim about the
historical source filename. The data unit is selected in `linked_units.txt`.
The historical native validation below proves 29,184 newly matched and
source-linked data bytes, with no new exact functions.

The tested composition includes `e258b1e91233fb9ddcbf72c9c168784a346153ff`,
which contains #203. It preserves #203's canonical records and four recovered
functions. The public ID API remains main's existing API; the independently
reviewed explicit ID-pointer/count API is still a private composition input.

## Objects and types

| Source object | Address | Bytes | Representation |
| --- | --- | ---: | --- |
| `quest_vm_download_server_file_info` | `8058DE08` | 68 | Character filename array |
| `quest_download_slot_table` | `8058DE4C` | 11,384 | 128 cache entries and ten pages |
| `quest_name_index_table` | `80590AC4` | 4,096 | 1,024 four-byte name-index rows |
| `lbl_80591AC4` | `80591AC4` | 1,028 | ASK header byte buffer, full native extent |
| `lbl_80591EC8` | `80591EC8` | 8,192 | Encoded cached-record bytes |
| `lbl_80593EC8` | `80593EC8` | 4,416 | 80 bucket pointers and 512 nodes |

`QuestDownloadCacheTypes.h` expresses the field widths used by the native
producers and consumers, with target layout assertions. An eight-byte cache
entry contains byte reference/value fields, a halfword page index, and signed
halfword offset/ID fields. A 0x40C-byte page contains page/state words, a next
pointer, and 1,024 data bytes. Native `init_page_cache` initializes ten page
headers, terminates their chain, and clears all 128 entry reference bytes.

The cached-name index has 80 node pointers followed by 512 eight-byte nodes.
Native `__VIRetraceHandler` clears the heads at cached-data offsets +0x2000
through +0x213C and chains nodes at +0x2140 through +0x3138. Native `803E8DA0`
writes a byte-record pointer and splices a node into a bucket; `803E95BC`
returns nodes through the same next-pointer field. No alternate active node
variant or larger enclosing storage object is invented.

The four objects that follow the six cache buffers are `lbl_80595008` (2,448
bytes), `quest_download_slot_chain_table` (2,240 bytes), `lbl_80596258` (12
bytes), and `quest_download_text_buffer` (1,028 bytes). They are defined in this
unit as the existing symbol extents. The slot array uses the canonical
`QuestDownloadSlot[80]`. `lbl_80595008` is `QuestDownloadWorkspace`: the last
`0xD0` bytes are the 32-entry query result read by `803EA428`, and the leading
`0x8C0` bytes have no load or store through this symbol. `lbl_80596258` is the
12-character display prefix copied from `lbl_8047E68C` and overwritten at
offsets 5..7 by `803EB4D4`. `quest_download_text_buffer` stays an opaque
`u8[0x404]`; its readers disagree on the element type. The native 40,000-byte
allocator pool begins at `80596668` and belongs to
`TQuestVmDownLoadServer_803E6970`, not to this data unit.

## Validation and review boundaries

The inactive ten-object layout at `e2988a01c` passed
[independent review](https://github.com/matthewlewisnewton/pso-decomp/pull/238#issuecomment-6569146152).
The 21 released provider access repairs at `57cff1c8` passed
[independent review](https://github.com/matthewlewisnewton/pso-decomp/pull/238#issuecomment-6569570341),
and the query-boundary repair at `f7975109` passed
[independent review](https://github.com/matthewlewisnewton/pso-decomp/pull/238#issuecomment-6569762964).
These are bounded source reviews, not overall activation approval.

The later six-access repair uses the actual four-byte rows for three name
readers and DMA, and the actual 8,192-byte buffer for two cached-byte helpers.
It preserves the earlier filename repair and all signatures. Both the public
153-function baseline and private #203/API 157-function composition remained
whole-object identical, including allocated data and symbolic relocations,
with empty diagnostics. A fresh compile of the current-main merge likewise
preserves the complete 157-function provider object, SHA-256
`a891a64c3d2eaaecd4a5546781956b72cb439f27cb449c2e78afe3f55c20cfa0`.

A fresh original-DOL split and the actual generated GC 1.2.5 compiler command
verified the six-object data-only candidate. It has no functions or initialized
data, 29,184 BSS bytes aligned to eight bytes, and exactly the six native global
objects with matching offsets, extents and bindings. Allocated bytes and
relocations match the fresh original object. The real single-unit objdiff
report scores BSS at 100%; the unchanged repository `unit_is_exact` check passes
all extra/missing symbol, section, size, alignment, layout and order guards.
This single-unit report is not a full-project no-loss report.

The repository already supports exact nonempty data-only units. Its ordinary
split and link graph can independently select the data object while retaining
the complete original provider object. Recovery of all 16 missing provider
functions is therefore required only for selecting the mixed provider object
from source, not for this bounded data milestone. No checker, score, compiler
unit-completeness flag, or fallback implementation is altered. The selected
frontend's direct reference to `lbl_80591AC4` is a compatible byte-array access.

## Separate consumer and remaining-storage work

The provider remains on original text fallback. Its inherited filename-based
cache/header views are not declared valid C++ owners by this data split.
A separately reviewed construction using real separate objects reproduces both
setup routines (888 instruction bytes) and all ten buffer extents. That resolves
the bounded common-base construction question; complete provider folding and
its allocator adjustment are separate from the data-only milestone.

Released query repairs give `803F0268` an actual cached-result local and make
`803F0500` read encoded name bytes at offsets 2/3. The primary lookup still
leaves its ID uninitialized on failure, which matters for a cached-only success.
The observed shipped route's initially empty cache narrows that concern but
does not establish a general source contract. The old ID member API also
remains a coordinated follow-up; receiver casts are not justified by byte match.

Retained-original analysis covers static cache references and 30 encoded-record
interfaces across 5,067 objects. The observed filename route copies a fixed
five-character literal and terminator. Shipped name-index bounds reach at most
row 657 of 1,024. Primary-record analysis found at most 15 distinct query pairs;
15 identified dispatcher request IDs exclude the primary mutation commands
30/31 and the observed EE580 command 24. These are finite native-route and
shipped-asset findings, not arbitrary-caller guarantees. They do not prove a
reachable original overflow or establish that either 1,028-byte buffer's final
four bytes are unused padding.

The workspace's final 0xD0 bytes are the 32-entry query result. The first
0x8C0 bytes still have no direct reference, so they stay an untyped leading
array inside that one object. The slot array uses #203's canonical
80-record definition. Shared text has byte, halfword and ID views; a larger
array or union alone does not establish their lifetime changes, retained
values or EE580 bounds. Callback quiescence after DMA timeout also remains
unproved. Those holds still bar a typed query object. They do not keep the
named BSS extents out of this data unit.

## Historical native activation validation

The normal development builds compared baseline
`e258b1e91233fb9ddcbf72c9c168784a346153ff` with selected candidate
`6607f3d2c0406f794e3d187fede3c6756ac51f4f`. Both completed successfully and
produced genuine complete reports (5,013 and 5,014 units). Both built DOLs are
byte-identical to their original input, SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

| Measure | Baseline | Candidate | Change |
| --- | ---: | ---: | ---: |
| Matched data bytes | 1,404,127 | 1,433,311 | +29,184 |
| Source-linked data bytes | 1,009,911 | 1,039,095 | +29,184 |
| Source-selected units | 3,553 | 3,554 | +1 |
| Exact functions | 27,288 | 27,288 | 0 |

Live linker response files establish the sole added source selection as
`QuestDownloadBuffers.o`. Replacing its source input and adjacent 5,728-byte
original remainder with the former combined original input restores the entire
baseline input order. All 5,012 other selected objects are byte-identical.
The compiled data object has SHA-256
`b72e7f08b622cd4de11effeb137b9deb4c75098b2815e6e6c509a0feb1b3c4e0`;
all six final ELF symbols retain their original addresses, sizes and bindings.

Both ordinary `check_pr.py --no-build` runs passed against the authentic
baseline report after the admitted native builds. The unchanged raw loss guard
reported zero loss in all nine combinations of code/data/function coverage,
exactness and source linkage, without filtering padding losses. Retention
remains 16,678 entries with no additions or removals. Scanner preview found no
further exact units to add and no regressions; no global scanner write was used.

These results are historical development evidence for the exact commits above.
Later documentation-only updates do not change those tested source/configuration
bytes. Fresh applicability and final acceptance against the merge queue's
current `main` remain separate requirements. The original provider and deferred
5,728 bytes remain excluded from this activation. Original artifacts,
disassembly, private diagnostics and proprietary tools stay local.
