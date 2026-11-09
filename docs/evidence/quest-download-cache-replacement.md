# Quest-download cache replacement (partial)

`sub_803E8DA0` (`0x803E8DA0`, 776 original bytes) is now defined as partial
C++: **90.71134% in the standard report**, 90.5567% in the relocation-sensitive
probe (`functionRelocDiffs=data_value`), and 772 compiled bytes. It adds no exact
function or source-linked coverage. The existing provisional interface remains
`s32(char *key, Req_803EEF2C *request, s32 value)`.

## Boundary and mutation order

The existing 16-byte native request view supplies a stored-name pointer at zero,
signed halfword length at `+4`, kind byte at `+7`, optional byte at `+8`, and
text pointer at `+0xC`. Both lookup/hash passes use the separate first argument;
name bytes are copied from the request pointer. Known callers prepare a separate
terminated local lookup buffer, so those pointers must not be silently unified.
No class ownership or new request layout is inferred.

The routine sets the dirty byte before reading its arguments. For an equal key,
it clears the old record's name length, unlinks its existing node, invalidates
the encoded cache ID, and returns that node to the real free list. It rotates
if no node is available, then pops/reserves a node before checking byte capacity.
A capacity rotation therefore occurs with one node reserved outside both lists.

It appends a little-endian length, name length, `strncpy`-copied name, kind byte,
the low byte of the third argument, an optional byte, and encoded text. The
length is `3 + request.len + 2-or-3 + encoded text width`. The optional byte is
present when `request.x8 != 0 || request.x7 >= 0x2D`, including a zero byte for
kind `0x2D` and above. That decision is re-evaluated separately for sizing and
writing, with native field rereads retained.

The existing text helpers treat `0x80..0x9F` and `0xE0..0xFC` as leads and copy
the following pair; other bytes become `0xFF, byte`. They perform no trail
validation and copy no trailing NUL. The append cursor has a separate two-byte
zero next-record marker. After encoding, the routine recomputes its lookup
position against the current index and links the reserved node, returning zero.
It does not reuse a borrowed link from before rotation.

Only the actual byte cache, typed bucket/node arrays and their existing free
list are used. Native non-null lookup-stop and post-rotation node-availability
requirements remain unchecked. Nonempty bounded names, complete terminated text
units, page-sized records and valid stable backing storage remain preconditions.
No null guard, repair, new pragma, padding or fabricated enclosing object is added.
General alias behavior for request/input storage inside an invalidated record or
append destination is not established.

## Native/candidate and independent packet checks

The original private 234-case checkpoint executed recovered replacement on the candidate side,
as well as the already recovered relocation/loader/initializer/rotation. It
retains the earlier 79 continuous lifecycle, guard and expected-precondition
cases; it does not repair indexes between operations. Complete nonstack data
memory and normalized provider traces agree. Meaningful return values and
stack/nonvolatile restoration are checked on successful returns; paired stops
check native fault kinds/sites and pre-stop data/trace agreement.

The 155 additions include:

- 144 packet cases: kinds `0x2C/0x2D`, optional byte zero/nonzero, four text forms,
  name lengths one/two/79, and three wide signed values. Lookup and stored-name
  buffers are distinct. An independent encoder checks every output record byte,
  the two-byte next marker and matching cached-ID invalidation.
- Ten more packet cases: `strncpy` NUL padding; a single-node, same-bucket
  mismatched-name diagnostic; insertion before/between keys and after a shorter
  prefix; exact capacity equality and one byte beyond; a 1,022-byte record;
  same-key replacement and new-key insertion with initially empty free lists.
- A direct null-key witness: both bodies first set dirty, then reach the native
  low-address read at `0x803E8DC8`. The harness stops there rather than modeling
  console low-memory vector contents or inventing a source error return.

Thus 154 cases check independent full packet bytes. The text corpus includes
empty/ASCII text, boundary leads with complete trails, and high nonlead bytes.
The capacity tests use complete independently encoded input records, not manually
repaired cursors. The maximum record retains exactly two bytes for its marker.
The same-key empty-free-list case releases/reuses its node without rotation;
the new-key case rotates into a populated page and obtains a free node.

The mismatched-name diagnostic does not establish general rename support:
bucket selection and insertion position still follow the lookup argument.
String and seek/read providers are bounded hooks. These tests are not a complete
provider, malformed-input safety, exhaustive alias or reachability proof.

## Remaining differences and gates

The refinement retains the actual byte-cache base across lookup for the encoded
ID calculation, writes the three-byte record prefix through an advancing byte
cursor, and extends the optional-prefix length into the complete record length.
The request length is still read after the text-width call and reread for the
header, name copy and cursor advance. The optional-byte predicates remain
separate for sizing and writing. These source data flows improve the standard
score from 84.08247% (768 compiled bytes), without changing the request boundary,
lookup key, reservation order or post-rotation index lookup.

The current private 528-case run re-executes this candidate, including the 154
independent packet encodings above, continuous mutation sequences, primary-page
removal, name-index boundaries and 72 direct reload/seek/read boundary cases.
The [cache lifecycle continuation](quest-download-cache-lifecycle.md) records the bounded
provider and reachability limitations. The candidate object SHA-256 is
`3d4f4f03a68bf40037aedc8eba301a70e0785230a5b2756973dbd28f90fbdf02`.
All 168 modeled compiled provider functions bind to the native build; the other
167 provider functions, all 16 frontend functions, all 159 exact functions and
the eight other partial scores are preserved. Noncode bytes, layout, objects
and relocations are checked separately. Native/no-loss results and independent
exact-head review accompany publication.

Native code also reaches the adjacent heads at `+0x2000`; honest source still
addresses the separate index object. Register/stack allocation, scheduling and
code extent remain different. The cache-base borrow does not establish a shared
enclosing owner or clear the request/input alias preconditions.

The unit remains 159/173 exact, five undefined and nine partial, unlinked.
The [observed entry gates and fixed-image caveats](quest-download-cache-relocation.md)
still apply: no enabled shipped mutation route was demonstrated. Lower-level
counterexamples are not claims of shipped failures. The search pointer-sentinel
sign-off remains unresolved.

The [primary-page remover continuation](quest-download-primary-removal.md)
shares the existing request type with its real frontend producer. Former local
request/message names are aliases; this does not widen or retype byte buffers.
