# Quest download buffer import and pending type recovery

This draft preserves the deferred source from upstream
[`6e52d78f641e37d66845e683e8fc3f013f3c2662`](https://github.com/zeroz41/pso-decomp/commit/6e52d78f641e37d66845e683e8fc3f013f3c2662)
(#168, author zeroz). The initial import contains the exact
`QuestDownloadBuffers.cpp` blob, without replaying that commit's unrelated or
already integrated changes. Upstream #167 changes a player function and is not
a dependency of this buffer import.

The baseline is fork main `0ea667b2ae02f09c65cd9464314c0d5993618c6c`.
Fork #226 deliberately deferred these definitions. This checkpoint has **zero
new matched or source-linked bytes**: the source has no split entry and is not
in `linked_units.txt`. The existing extraction and linker selection remain
unchanged. The imported declarations are a starting point, not qualified types.
Later commits add two bounded cache layouts and express the filename and
name-index extents as character and four-byte-row arrays. Their consumers and
complete ownership are still pending as described below.

## Storage census

The symbol metadata describes ten contiguous extents totaling 34,912 bytes.
It establishes addresses and sizes, not historical translation-unit ownership
or the C++ lifetime of objects accessed through those addresses.

| Symbol | Address | Bytes | Contract still needed |
| --- | --- | ---: | --- |
| `quest_vm_download_server_file_info` | `8058DE08` | 68 | Filename and cache interfaces |
| `quest_download_slot_table` | `8058DE4C` | 11,384 | 128 entries and ten cache pages |
| `quest_name_index_table` | `80590AC4` | 4,096 | Consistent four-byte name records and DMA view |
| `lbl_80591AC4` | `80591AC4` | 1,028 | ASK header and remaining four bytes |
| `lbl_80591EC8` | `80591EC8` | 8,192 | Cached byte data and bounded variable records |
| `lbl_80593EC8` | `80593EC8` | 4,416 | Bucket heads and cache-node lifetimes |
| `lbl_80595008` | `80595008` | 2,448 | Actual uses, extent and owner |
| `quest_download_slot_chain_table` | `80595998` | 2,240 | #203's 80 real 28-byte slot records |
| `lbl_80596258` | `80596258` | 12 | Header and accesses through the following payload |
| `quest_download_text_buffer` | `80596264` | 1,028 | Shared byte, wide-code and ID lifetimes |

The reviewed 40,000-byte node pool begins at `80596668`, after this range.
The separate 39-record input table starts at `805A0498`. Neither repair
establishes ownership or lifetime of these ten objects.

## Cache layouts recovered after the import

`QuestDownloadCacheTypes.h` gives the slot-cache extent 128 real eight-byte
entries followed by ten real 0x40C-byte pages. The entry fields are a byte
reference count, a byte value, an unsigned halfword page index, and two signed
halfword offsets/IDs. Acquisition and release update the reference count;
`803E779C` returns the other fields with the corresponding native load widths.
The page has two words (page index and state), a next pointer, and 1,024 data
bytes. Native `init_page_cache` initializes the ten page headers, terminates the
last next pointer, and clears the reference byte in all 128 entries.

The name index is **80 node pointers followed by 512 eight-byte nodes**, not
1,104 unrelated `void *` objects. Native `__VIRetraceHandler` clears the heads at
cached-data offsets +0x2000 through +0x213C and chains nodes from +0x2140 through
+0x3138. Each node has a byte-record pointer and a next pointer. Native
`803E8DA0` writes the record pointer and splices the node into a bucket;
`803E95BC` returns it to the free list by updating that same next member. There
is no evidence here of another active node variant requiring a union.

Two admitted development compiler probes, using the original imported source
and the typed definitions, produced identical allocated data sections: all ten
symbol offsets/extents/bindings, 34,912 zero BSS bytes, alignment 8, and no
relocations. All layout assertions passed without diagnostics. These are
targeted definition-layout checks, not consumer, full-build or source-link proof.
The two cache definitions now use these types. At the independently reviewed
`e2988a01c` checkpoint no shared consumer had been edited; the provider follow-up
below is a separate step.

## Released provider access repair

The inactive layout scope at `e2988a01c` passed
[independent review](https://github.com/matthewlewisnewton/pso-decomp/pull/238#issuecomment-6569146152)
without repairs. The buffer definitions and cache type header remain unchanged
from that reviewed commit.

After the Quest owner released the precise provider hunks, a separate follow-up
replaced duplicate cache-entry/page views with the reviewed field types and
filename accesses with the actual character array. The two cached-name readers
now use the actual 80 bucket heads and read encoded name bytes at offsets 2/3,
without treating the name as a one-element array. The exact-match output carries
a byte pointer. At the `57cff1c8` checkpoint the prefix-match output retained its
legacy pointer boundary. That bounded access rewrite passed
[independent review](https://github.com/matthewlewisnewton/pso-decomp/pull/238#issuecomment-6569570341);
complete source integration and storage lifetime remained on hold.

A retained-original census covers all static references to the two cache globals
and 30 identified encoded-record producer/consumer interfaces across 5,067
original objects. It identifies loaders, insertion/eviction, page modification,
record-pointer return paths, variant readers and both query aggregators. Mutable
record validity, callback safety and complete owner provenance remain open.

The final provider object is byte-for-byte identical to the retained baseline
object, including all 153 emitted function records and allocated data, with no
diagnostics. The unchanged baseline object retains 149 exact native functions;
this follow-up adds no exact functions. A private composition with the reviewed
`3dd6c6ea` explicit ID-pointer/count API is also whole-object identical. The
public API declaration is left for coordinated adoption of that owner's patch;
its old member spelling is not declared correct here.

A second private composition applies these released hunks to the exact #203
candidate `32befa8160d39b4cda09d14149171191102d796b` and composes the same reviewed
ID API. Its complete provider object is byte-for-byte identical to #203's
retained object, preserving all four of its recovered functions. Only copied,
pinned headers and an isolated source snapshot were used; the other worker's
files were not edited. This is composition evidence for that immutable candidate,
not adoption of #203 or current-main acceptance.

The next released follow-up repairs the two query callers. `803F0268` now gives
the cached-name lookup an actual `Out_803E8B1C` local and reads its `id` and byte
pointer fields; it no longer passes an unrelated `Info_803F0138` through a cast.
`803F0500` reads the encoded prefix at byte offsets 2/3, and the prefix output
now carries a byte pointer. Signatures, failure branches and acquisition
arguments are preserved. Both lookup misses initialize their offset/ID sentinel;
record pointers are read only on success. A separate existing concern remains:
the primary lookup does not initialize `i1.id` on failure, yet a cached-only
success passes it to slot acquisition. This follow-up does not initialize it or
claim that branch's source contract is valid.

Two fresh development provider compiles checked this follow-up. The first is
whole-object identical to the retained 153-function baseline. The second
composes the released edits with published #203
`1602f9b5732df211bdf63e6bf907ca8d1c4d8d82` and the frozen reviewed ID API; it is
whole-object identical to #203's retained provider object, including its four
recovered functions. All actual baseline compile inputs were independently
rebound to that published head and its main base
`909d120b21f7e875e71a5c1d0d3a7799a08078e9`. The complete private composition is
prepared for later validation; neither the API overlay nor #203 is adopted by
this checkpoint, and no duplicate full build was launched.

Two common-base experiments remain failed diagnostics. Directly naming the
separate cache/header objects loses the existing exact matches for
`init_page_cache` and `read_ask_header`; defining separate objects in the same
translation unit also leaves the cache initializer at 540 rather than 536 bytes.
Those changes are excluded from the published patch. The legacy common-base
views remain visibly provisional, using the reviewed cache member types where
possible. No larger storage owner was inferred to recover the matches.

## Follow-up boundaries

The file/cache repair must reconcile every consumer, rather than replace only
the imported definition. `init_page_cache` currently casts the 68-byte file-info
symbol to `Cache_803E840C`, which spans 0x2CBC bytes. Its 128 eight-byte entries
and ten 0x40C-byte pages occupy the next symbol's entire 0x2C78-byte extent.
`read_ask_header` separately casts the same file-info symbol to a padded view
whose header is at +0x3CBC. A candidate repair can use the actual separate
filename, cache and header objects, but must preserve native symbol/addend
relocations and all consumers; physical adjacency does not prove a larger
filename or aggregate object.

The retained original object makes the relocation problem concrete:
`init_page_cache` loads the file-info symbol and derives the page start at
+0x444 and entries at +0x44; `read_ask_header` loads that same symbol and derives
the header at +0x3CBC. Neither function relocates directly against the cache or
header symbol. A separate-object source spelling may therefore alter exact
instructions/relocations. A complete owner spanning these ranges is a candidate
for investigation, not a conclusion from the available evidence.

The filename extent is now a 68-character array. The observed native route is
`803F09A4` -> request 0x20 -> dispatch table entry 31 -> `803E5B94` ->
`poll_download_status` -> `803F08E4` -> `set_file_info_name`. It copies one
five-character literal plus its terminator through the 128-byte staging buffer
into this extent. The retained original relocation census found no other
static callers or staging writers. This bounds the observed executable route;
it does not establish a general 67-character check or validate arbitrary
external callers of the exported dispatcher/setter.

The name-index extent is now 1,024 rows of four bytes. Read-only inspection of
the shipped ASK dictionary gives a search high bound of 657, sorted data rows,
a minimum nonempty first key and a zero sentinel at row 657. With the native
low bound of zero, the binary search reads rows 0..656, and the next-row reader
reaches at most row 657. An empty key may return -1, but `803F0500` checks the
next row and returns before using that result in the current-row reader.
Subsequent key shortening retains a nonempty key. These facts qualify this
shipped asset and observed route only; replacement dictionaries and opaque
callers remain outside the proof. The asset and disassembly stay private.

One additional admitted compiler probe checked these two array changes against
the retained baseline, without rebuilding the baseline. Complete allocated
data, including every symbol offset, extent, binding, alignment and relocation,
remains identical to the original automatic BSS object. The comparison receipt
records an initial tuple-versus-JSON-list representation mismatch and the
successful canonical comparison of the same objects; no compiler rerun or
comparison field was omitted.

The 2,448-byte symbol at `80595008` also cannot be qualified by a source-only
reference search: its missing native consumers `803EA428` and `803EA9E8` use
that base plus +0x990 for the following slot table. `803EA428` passes +0x8C0 to
the item-query producers and reads halfwords at +0x8C0/+0x8C8 and a word at
+0x8C4. This identifies a result workspace in the final 0xD0 bytes, but does
not establish the first 0x8C0 bytes' object type or a complete aggregate owner.

A further native relocation census and straight-line argument analysis found
15 constant request IDs among the dispatcher's callers. None selects the
primary-dictionary mutation commands 30/31 or command 24, the only observed
route to `EE580`. The shipped primary records have at most 15 distinct query
key pairs. These findings narrow the earlier hypothetical query-list overflow;
they do not demonstrate a reachable original-binary defect. They are bounded
static-route evidence, not a general API guarantee or proof against raw-address
entry, corruption, replacement assets or callbacks. Complete producer and
storage contracts remain required.

The slot-table definition must adopt #203's canonical record header together
with its reviewed consumers and allocator interfaces. The four exact functions
in #203 must survive the combination. The buffer work must not introduce an
alternative record model or replace the current #203 repair wholesale.

The text buffer is also the storage used by the pending EE580 recovery and the
DF64 caller. The frontend's 512 signed halfwords cover 1,024 bytes, not the
complete 1,028-byte symbol. Other paths use byte dictionaries, a text record
prefix and ID cells. A new union or larger integer array alone would not prove
lifetime transitions, retained values, variable-tail bounds or a 257-ID bound.
The header-plus-12 callers belong to this same audit. C284 and DF64 function/API
repairs remain separate dependencies and must be coordinated before their
frontend hunks change.

## Activation and acceptance

The subsequent six-access repair removes the name-index and cached-byte scalar
wrappers. The three name readers now index the actual four-byte rows, the index
DMA receives the actual array, and the two cached-byte helpers use the actual
8,192-byte buffer. The earlier filename repair and all function signatures are
preserved. This is a declaration/access repair; existing receiver casts, signed
offset domains and runtime bounds remain separate obligations.

Two admitted candidate compilations reused their immutable baselines: the
public `f7975109d537b6592d117fd2d807e326f00bb3b4` continuation and the private
composition with published #203 at
`1602f9b5732df211bdf63e6bf907ca8d1c4d8d82` plus the reviewed explicit ID API.
Both complete provider objects and empty diagnostics are unchanged, including
every emitted function, allocated data section and symbolic relocation. The
public object SHA-256 remains
`da74517bd1d1b40261ceb9a923e11a55f36f5a00a2ecd86da1f2bb75bafff1a6`;
the private composed object remains
`a891a64c3d2eaaecd4a5546781956b72cb439f27cb449c2e78afe3f55c20cfa0`.
This follow-up adopts no buffer fold, slot definition, split or link activation
and claims no new exact functions or source-linked bytes.

Type and consumer repairs belong in later commits, separately from the upstream
import. Once their source contracts pass independent review, qualify emitted
code/data, alignment, symbol bindings and relocations using admitted development
capacity. Reuse prior immutable evidence only when its actual inputs agree.
Then establish the data-owner boundary, regenerate the graph and retention data,
check actual native source selection, and run the original-DOL and address-based
no-loss checks against both the dependency base and current fork main.

The initial import performed source-provenance, symbol-extent and unchanged-
build-input checks only. The cache-type commit adds the two targeted compiler layout probes above;
the filename/index follow-up adds one candidate probe against the retained
baseline. The provider follow-up adds the retained-baseline and private composition
comparisons described above. No checkpoint ran a game link, full build or
`check_pr.py`, and none claims review-ready status. Keep the PR draft until the complete contracts and
these validation gates pass. Final current-main acceptance belongs
to the merge process.
