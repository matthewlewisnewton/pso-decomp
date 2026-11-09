# Quest-download cache replacement (partial)

`sub_803E8DA0` (`0x803E8DA0`, 776 original bytes) is now defined as partial
C++: **84.08247% in the standard report**, 83.92783% in the relocation-sensitive
probe (`functionRelocDiffs=data_value`), and 768 compiled bytes. It adds no exact
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

The private 234-case run executes recovered replacement on the candidate side,
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

Native code retains the cache-byte base and reaches the adjacent heads at
`+0x2000`; honest source addresses the separate index object. Register/stack
allocation, scheduling and code extent also differ. Existing 159 exact functions
and six previous partial scores are preserved. The 166 modeled compiled
functions bind to the native build checkpoint; noncode layout, objects and
relocations are checked separately. Native/no-loss results and independent
exact-head review accompany publication.

The unit remains 159/173 exact, seven undefined and seven partial, unlinked.
The [observed entry gates and fixed-image caveats](quest-download-cache-relocation.md)
still apply: no enabled shipped mutation route was demonstrated. Lower-level
counterexamples are not claims of shipped failures. The search pointer-sentinel
sign-off remains unresolved.
