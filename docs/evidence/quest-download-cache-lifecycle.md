# Quest-download cache lifecycle (partial)

`sub_803E93DC` reloads the eight cache pages and reconstructs their sorted
name index. The existing `__VIRetraceHandler` symbol at `0x803E97B0` initializes
that index and handles a failed reload. Both are partial C++ recoveries; the
symbol spelling does not establish an SDK owner or retrace-handler role.
The standard report scores reload 88.67273% and initializer 82.47771%.
Neither recovery adds an exact function or source-linked coverage.

## Actual objects and provider boundary

Both routines use the real `lbl_80591EC8[0x2000]` byte array and the separate
`QuestDownloadCachedNameIndex lbl_80593EC8`: 80 head pointers followed by 512
eight-byte nodes. No enclosing owner, extra storage or retyping is introduced.
The initializer chains the existing nodes, clears the heads and calls reload.
It does not initialize unused nodes' record pointers. Failed seek or a read
other than `0x2000` bytes takes its fallback: zero each page's two-byte record
terminator, select page zero and reset its cursor/end. It clears the dirty
byte on either outcome, retaining the other bytes.

The sole native caller of `aram_read_thunk` is reload at `0x803E9418`. The
thunk forwards its three argument words without accessing a server object.
Its former nonstatic member declaration fabricated a receiver. The recovery
uses the existing native link name as a provisional `extern "C"` free function:

```cpp
u32 aram_read_thunk__22TQuestVmDownLoadServerFUli(
    void *handle, void *dst, s32 size);
```

The wrapper remains byte-identical. The scalar file-handle word is converted
at the existing opaque provider boundary; no pointed-to ownership is inferred.
The other provider interfaces and class layout remain unchanged. This repair
does not authorize the separate search pointer sentinel.

Reload seeks to `0x1400`, reads the complete byte image, walks each page's
little-endian length-prefixed records, and inserts every nonempty name into
its bucket. Equal keys are inserted, not replaced. Visiting the selected page
restores its append cursor and exclusive end. The persisted page word loaded
from header `+0x30/+0x31` has no local range validation. Page range, bounded
terminated chains and names shorter than the local 80-byte buffer are unchecked
preconditions, not properties established by this implementation.

The loader now borrows the actual byte-array base before seeking and uses that
same base for the read destination and subsequent page walk. This matches the
native base lifetime without assuming an owner spanning the cache and index.
Its read result is interpreted as a signed native I/O-status word locally. For
this positive `0x2000`-byte request, the actual reader bounds the count to
`0..0x2000`; timeout returns all-ones. The native conversion therefore preserves
the existing complete-read versus failure test. The unsigned thunk/provider ABI
is unchanged, and this ordinary integer status is unrelated to the held pointer
sentinel. Neither stable record contents nor valid predecessor links across a
nested rotation are inferred from the stable array address.

The initializer also borrows the fixed cache-array base before building the
free list and preserves it across reload for its existing failure path. Both
initialization loops, store order and fallback cursor assignments are unchanged.
This follows the native cache-base lifetime while retaining the separate typed
index object; it supplies no new callback or lifecycle invariant.

## Mutator audit

A named-reference census of all 4,970 original objects at the initial lifecycle
checkpoint confines direct references to the cache, index and cursor/free-list globals to this unit. This
is not proof against every possible alias-derived write.

| Routine | Observed transition |
| --- | --- |
| `97B0` | Resets free links/heads; reloads or initializes empty pages. |
| `93DC` | Loads cache bytes, inserts nonempty records and restores append bounds. |
| `8DA0` | For an equal key, clears its old name length before unlinking/freeing its node; invalidates the cached ID. Reserves a new node, rotates for space, writes the replacement and recomputes its insertion position. |
| `8924` | May rotate, then reserves append space. For the indexed source, redirects its node before copying, clears the old name length and invalidates its ID. |
| `95BC` | Evicts the next page's indexed records and returns their nodes to the free list. |
| `EF958`, `EF8E0` | Change payload/version or flag bytes through resolved records; observed writes preserve lengths, name keys and links. Their callers mark dirty state. |
| `read_ask_header`, `8150`, `9764` | Read the selected-page word and prepare header/cache write attempts; the write hook returns minus one without writing. |

Both `8DA0` and `8924` also require a non-null sorted-search stopping node;
`8DA0` dereferences it at `0x803E8E64`, and `8924` at `0x803E8A64`. During a
capacity rotation inside `8DA0`, one node has already been reserved: bucket
nodes plus free nodes account for 511 cells until insertion completes.

## Continuous native/candidate sequences

The private instruction harness executes the actual native initializer,
loader, replacement caller, relocation caller, rotation, text helpers and ID
invalidators. On the candidate side, undefined callers retain their native
instructions and call the recovered routines. Strings use standard hooks;
seek/read use bounded provider hooks. Indexes are built by the initializer
and loader, rather than manufactured for each operation.

The 73 cases include 32 empty-image/seek/short-read/read-failure initialization
cases across all selected pages; 16 mixed sequences with 640 replacement,
relocation and rotation operations; eight streams of 160 replacements each
(1,280 total) causing 160 capacity rotations; and eight reloads of snapshots
produced by those streams, followed by another replacement. The continuous
replacement streams cover all starting pages and more than two reuse cycles.
They observe the reserved-node state and compare complete nonstack data memory,
normalized provider traces, meaningful return values and restored stack/nonvolatile
registers. Stable-boundary checks independently reconstruct live records,
validate sorted buckets and partition all 512 node cells.

The current page's live prefix ends at the append cursor. Bytes beyond that
cursor are already evicted storage; treating them all as live records gives a
false invariant. Other closed pages terminate at their stored zero length.
Unused cache and node bytes are deliberately nonzero in initialization tests.
The ordinary cases seed valid prior page/cursor metadata; a separate cold-start
case tests oversized reconstruction before a zero cursor has been restored.

## Counterexamples bound the claims

The remaining nine cases include paired native/candidate witnesses. Both
sides agree on nonstack data and provider traces up to a detected null access.
The harness stops at effective addresses zero/four; it does not model console
low-memory vector contents or claim a particular hardware exception.

- Loading equal `A` keys on pages zero and one, then rotating from seven to
  zero, stops at the other equal-key node and leaves the deeper page-zero node
  indexed. Thus arbitrary duplicate-key persisted images do not preserve
  index/live-record equality.
- A bounded image with 512 unique names, 128 on each of pages zero through
  three, selects empty page four. Appending a new key with a non-null search
  stop rotates into empty page five and still has no free node. The native
  caller dereferences effective address four at `0x803E8EE8`. Merely having a
  consistent index and at most 512 names does not establish next-page availability.
- With valid prior cursor metadata, a 513-name image triggers reload's nested
  rotation into that same empty page; its unchecked free-node read reaches
  effective address four at `0x803E9510`. With a cold zero cursor instead,
  nested rotation first stores to effective address zero at `0x803E95E8`,
  before reload has restored the selected page's append bounds.
  Reload computes the predecessor/link before this callback. This witness does
  not justify those borrows across arbitrary reentrant rotations.
- With two 500-byte records on pages zero and one and page zero selected,
  relocating page one's first record rotates onto its source page. Native code
  reserves 500 bytes, then its post-rotation source-page check skips copying.
  The reserved prefix retains a now-unindexed name. Eight further rotations
  reach rotation's null-node read at `0x803E96F8`.
- Empty-bucket and beyond-tail replacement searches reach the unchecked node
  read at `0x803E8E64`. Successful reloads with selected-page words eight and
  `0xFFFF` retain those unchecked values.

These bounded images pass the hooked read; the 513-name case stops during
reconstruction. The witnesses do not establish that shipped producers or
callers reach those states. They do
show that the simple initialized/sorted/unique-record premises are insufficient
for a universal lifecycle proof. No null guard, validation policy, rollback or
other behavioral repair is added to imitate such a proof.

## Later direct-reload validation

The current 528-case run retains the [456-case lifecycle/removal corpus](quest-download-primary-removal.md)
and adds 72 direct loader cases. Every selected page is exercised with read
results `-1`, zero, one, two, 127, 128, 8,191 and 8,192, plus seek failure.
Calling reload directly prevents initializer fallback from masking its effects.

Before these reads, the old cache bytes have a nonzero pattern. A failed or
short read is checked against an independent complete nonstack snapshot with
only the provider's returned prefix replaced. Thus the 8,191-byte case tests
retention of a distinct final byte. These failure cases do not parse the old
pattern or establish its validity as a record image. Complete reads replace it
with a valid image and check the selected-page cursor/end and index invariants.
The actual dirty byte is seeded nonzero, with distinct adjacent bytes; both
the byte and entire word must remain unchanged. Seek failure also preserves
its full snapshot and makes no read call.

Native/candidate meaningful returns, complete nonstack data, normalized provider
traces and restored stack/nonvolatile registers agree. The actual read thunk
executes, while seek/read/string operations retain their bounded hooks. No DMA
quiescence, arbitrary-image, callback-lifetime or shipped-reachability proof is
added. All earlier precondition witnesses remain in the retained corpus.

The model script SHA-256 is
`433f38840a9da1bdcb556691421074ac3440761553dbf1865a3a968a089d989c`;
its compiled candidate SHA-256 is
`f4b7f1f419cc4ba56fc0bfd43e7833b51d3c80169844309e58869bfb7434b25b`.

## Matching and remaining work

Relocation-sensitive probes (`functionRelocDiffs=data_value`) score reload
88.09091% (448 compiled bytes versus 440 original), improved from 85.59091%
at 444 bytes. The initializer improves from 55.254776% at 640 bytes to
57.057323% at 648 bytes, versus 628 original. Its whole-project report improves
from 80.99363% to 82.47771%; the direct object comparison remains less matched.
The initializer lifetime change is a modest matching gain with eight additional
compiled bytes. Pointer-range clearing, library fill, nonempty-loop and
failure-page cursor variants all regressed and were left out; the retained
variant preserves both existing loops. Neither refinement is exact completion.
At the initializer checkpoint, all 167 other provider bodies, eight other partial scores, 159 exact functions
and 16 frontend functions are preserved. Provider noncode data, object layout
and relocations are unchanged; all frontend allocated bytes/layout and normalized
relocations are preserved.
Native code commonly retains the cache byte symbol as
one base and reaches the adjacent index from it; honest source names the two
actual objects. Register/stack and loop-lowering differences remain. No false
owner, dummy padding, new pragma or compiler override is introduced.

Native/no-loss results and independent review accompany the published checkpoint.
Original instructions, objects and interpreter inputs remain private; the note
publishes provenance summaries and hashes.
The unit remains incomplete and unlinked. Full provider behavior, every reachable
producer transition, malformed-image safety and exactness remain unproved. The
[search sentinel gate](quest-download-search-evidence.md) remains in force.

The later [relocation and entry-gate audit](quest-download-cache-relocation.md)
recovers `8924` and bounds these lower-level witnesses against the observed
dispatcher, disabled mode flag and fixed dictionary image. Snapshot round trips
here use the test provider; the native write stub does not establish persistence.
