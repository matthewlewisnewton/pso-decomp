# CustomSelect native code with preserved initialization hold

This follows PR #268 checkpoint `3cafc19119bce9d39e3f90133c5ecac20e5b8d1e`.
CustomSelect now has native Addition construction/destruction and an ordinary-new
producer. Its compiler table adds 24 matched and linked data bytes. This recovers
the exact native code graph while preserving the unresolved partial-initialization
safety limitation; it does not establish safe destruction on every return path.

## Constructor and conditional initialization

The sole original constructor caller allocates 0x84 bytes in the customize
controller's state 3. It now uses `new TWindowSubCustomSelect(client)` with the
same word-valued client input. Original inspection finds one direct zero-addend
constructor call, with no address-taking or other-section reference.

The native constructor at 80277AEC initializes Addition with the existing
descriptor, short client view and layout 0x10. It preserves name/client stores,
the player lookup and both existing early returns. No derived member initializer,
zeroing, default child construction or extra guard is added.

On the positive path it selects the same organic/android action table, initializes
the same grid bytes and timer, and counts records to the existing sentinel. It
allocates the opaque 0x24-byte heading through the same constructor protocol,
then constructs the existing 12-byte Scroll object from the same stack pair.
The existing floating-point pragmas, including the duplicate directive, remain
unchanged. No new compiler control or intrinsic is introduced.

The 388-byte constructor reproduces all original instructions and resolved
targets. The native destructor reproduces all 116 bytes: Scroll cleanup at
field 0x80 with release flag 1, opaque heading cleanup at 0x7C with flag 1,
then automatic Addition destruction and the compiler's deleting protocol.
The child cleanup functions remain type-erased; their complete identities and
ownership contracts are not widened. Render now defines the actual member with
its unchanged body; the task already did so.

## Partial-initialization safety remains unresolved

The null-player return occurs before fields 0x78, 0x7C and 0x80 and the grid
state are initialized. The destructor later reads the two child slots. The sole
producer's preceding CustomEquip selection flag is not a dominating positive
player check. No complete producer guarantee excludes that return path.

The second return follows address formation of an embedded player prefix; it
does not establish a separately nullable allocation. Both branches are retained.
Scalar members remain uninitialized on those paths, as in the original code.
Spare storage, allocator behavior or a presumed zeroed heap is not used as proof.
Native code exactness does not resolve this lifetime-safety hold.

## Table and original providers

The compiler emits exactly the existing 24-byte table at [804D1550,804D1568),
with the four original destructor/task/render/TObject-shadow targets. No extra
slot, hand-written table or data-placement control is used. The descriptor and
action records retain their original providers.

The previous 204-byte original data span is fully accounted for:

| Range | Bytes | Provider |
| --- | ---: | --- |
| 804D14B4..804D1550 | 156 | Original prefix, including descriptor/records |
| 804D1550..804D1568 | 24 | Native compiler table |
| 804D1568..804D1580 | 24 | Original suffix |

Both original objects remain selected exactly once with unchanged raw bytes and
resolved targets. There is no new gap, padding classification or coverage loss.

## Complete objects and validation

The first ordinary native probe preserves the complete 2488-byte owner text,
its 16-byte conversion pool and all resolved targets. The producer's complete
1212-byte folded text and 32-byte jump data remain unchanged from 3caf. The
existing Menu/List provenance check also compares that fold against both original
text slices and every relocation target. Both source objects are selected once.

The full capacity-gated build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental `check_pr` passes
with +24 matched/linked data bytes and no code, function, total-data coverage or
linked-address regression. The comparison against separately built main
`4bec40d6cca74a85e91c848ea2d9f25425a313ad` also passes. Retention is clean at
17,904 and the port inventory passes.

The now-unused raw Addition constructor declaration leaves WindowConstructorAbi.h.
Raw Base/Addition calls fall from 20 across eleven units to 18 across ten; three
bindings remain: Base construction, Base destruction and Addition destruction.
The remaining raw Addition cleanup is Balloon's held destructor boundary.
Totals remain 27,406 exact functions, 3,587 exact linked units and 3,641
source-bearing units. Combined PR deltas versus fresh main are +600 matched code,
+1220 linked code, +1564 matched data and +1520 linked data bytes.

Partial initialization, opaque headings/Scroll release, callbacks, ChoiceSetting,
task-global ownership, remaining lifetimes/constants, Word/nameplate original
providers and protected remainders keep their standing qualifications. The PR
remains draft; this change does not claim 100% completion or portable lifetime
safety for the unresolved paths.
