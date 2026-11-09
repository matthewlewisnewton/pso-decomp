# Quest-download cache-page rotation

`TQuestVmDownLoadServer__sub_803E95BC` (`0x803E95BC`, 424 original bytes)
rotates an encoded-name cache page, unlinks its indexed records, returns
their nodes to the existing free list, and invalidates cached IDs for the
selected page. This is a partial C++ recovery: **90.330185% in the standard
report, 428 compiled bytes**, adding no exact function or source-linked
coverage. The relocation-sensitive probe scores 90.18868%.

## Interface and real storage

The provisional interface is `void(void)`. All four original direct callers
discard its result: calls at `0x803E8998`, `0x803E8EE0`, `0x803E8F44`, and
`0x803E9508`. It reads no incoming argument and ends with the existing
`void clear_entries_by_id(s32)` call. This supports the boundary without
claiming to recover the original declaration or a class receiver.

| Global | Supported role |
| --- | --- |
| `lbl_805D786C` | `u8 *`, current page's exclusive end |
| `lbl_805D7870` | `u8 *`, current append cursor |
| `lbl_805D7874` | Existing `s32`, current page index |
| `lbl_805D7878` | `QuestDownloadCachedNameNode *`, free-list head |

The bytes remain the actual `lbl_80591EC8[0x2000]` object, divided into eight
`0x400`-byte pages. Heads and nodes remain the separate, already typed
`QuestDownloadCachedNameIndex lbl_80593EC8`. Source uses its real `heads`
members and borrows either a head lvalue or a real node's `next` lvalue.
No larger aggregate, node retyping, ownership change, or access past the
cache-byte array is introduced. Free-list insertion retains node lifetimes.

## Behavior and preconditions

The routine writes two zero terminator bytes at the old append cursor,
advances the signed page index with `(page + 1) % 8`, and resets the cursor
and page end. It walks little-endian length-prefixed records until a zero
length. Nonempty names select buckets from their first encoded byte:
`0xA0..0xEF` maps to buckets `0..79`; other bytes use bucket zero.

The index walk compares the indexed name using that node's byte length and
then checks the requested length. Shorter matching prefixes advance; equal
names/lengths or lexicographically greater names stop. The record-identity
guard prevents removing an equal-name node belonging to another record.
Unlinked nodes retain their record pointer and are pushed onto the free
chain. Final ID invalidation uses the newly selected page index.

Original code dereferences the stopping node unconditionally at
`0x803E96F8`. Source preserves this required non-null-stop precondition.
Sortedness alone does not prove it: cache/index consistency must supply a
stopping node for each processed nonempty key. Free-list-triggered callers
also assume rotation supplies a node and do not recheck the free head.

Valid initialized page indices, append space for the two-byte terminator,
bounded terminated record chains, and names shorter than the local 80-byte
buffer remain preconditions. Their satisfaction for every reachable caller
state is not established by this recovery or a finite test corpus. No
guard, rollback, new error return, or silent repair policy is invented.

## Code generation still open

Native code retains the cache-byte symbol as one base and reads the
adjacent head array at `+0x2000`. Source names the actual separate index
object, producing another symbol/base reference. Its stack frame,
name-buffer position and register choices also differ. No dummy storage,
pragma change or false enclosing object is used to imitate that layout.

Three honest link formulations were measured with
`functionRelocDiffs=data_value`. The pointer-to-pointer lvalue retained here
scores 90.18868% at 428 bytes in that probe. Direct conditional stores
score 80.896225% at 428 bytes; a reference lvalue scores 89.71698% at 424
bytes. All preserve the 159 exact functions and the DC20/F03B4 scores.
Equal extent does not establish exactness; these bounded results do not
establish that no exact source exists.

## Bounded behavior comparison

Original and selected candidate instructions were executed against a
separate graph-filter/free-chain model in 256 deterministic valid states.
All passed, including all eight page rotations and eight dense cases with
initially empty free lists, one for each rotation. The corpus covers prefix
keys, unrelated nodes, identity guards, empty-name records, two-byte record
lengths and 94 copies at the 79-byte name boundary. It returns 1,494 nodes
across the corpus.

Comparison checks complete nonstack data memory, normalized provider calls,
stack-pointer restoration and nonvolatile registers. String hooks implement
standard behavior; ID invalidation is an ABI-clobbering bounded stub.
Differing stack layouts are not equated. This is not full-provider,
malformed-state, exhaustive safety, exactness or linkage proof. Original
instructions, compiled objects, interpreter inputs and hashes remain local.

Final native/no-loss results accompany the published checkpoint. The unit
remains incomplete and unlinked; the separate search
[sentinel gate](quest-download-search-evidence.md) remains intact.

The later [native lifecycle sequences](quest-download-cache-lifecycle.md)
exercise the actual producers and document concrete limits to the invariant,
including uneven exhaustion and relocation onto the source page. They do not
turn the constructed-graph corpus above into a reachability proof.
