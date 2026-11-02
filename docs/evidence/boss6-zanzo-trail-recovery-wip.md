# Boss 6 trail recovery (in progress)

The function at `0x803204B8` writes through the frame pointer at offset `0x20`
and iterates the point count at `0x24`. The factory at `0x80320AE0` constructs
`TBoss6Zanzo`, and the original callers store its result in the fields later
passed to that function. The former `TBoss6Type1` receiver was therefore not
supported. The frame contains an active word and a point-array pointer; a point
contains four color bytes and a three-float position. Placement construction
starts the lifetimes of the trivially initialized arrays returned by `mem_alloc`.

The drawing routine at `0x801E3784` reads three pointers from a descriptor, not
from a player. Its original callers supply a descriptor whose first fields are
position, packed color and texture-coordinate pointers. Likewise `0x80257720`
copies four color bytes, without using an effect object. The two functions and
their source callers now use those contracts; the old player and effect-class
method declarations did not describe their receivers. Two global fan descriptors
remain in original data; the local 20-byte ruler wrapper records its extra word.

The eight-byte function at `0x803204B0` is a REL image getter used by the
adjacent module loader. A typed buffer and native allocation establish its
receiver and pointer lifetime. This function remains in its existing split.

In private targeted GC/2.6 comparisons, the original functions outside the new
trail renderer retained their instruction bytes after the symbol renames. The
new renderer is still inexact: objdiff reports 94.81% similarity, not an exact
match. The 45 other direct consumers of the changed class headers and the 15
separately checked helper and caller objects retained their allocated-section
bytes and relocation targets after normalizing the named symbol migrations.
These targeted results do not replace a configured graph, full build,
address-based no-loss check, real link-input audit, DOL hash or independent
review.

The original vtable at `0x804EC968..0x804EC980` has four relocations to the
native destructor, task, render and inherited shadow-render functions. The
compiler-emitted vtable has the same bytes and targets. The two conversion
constants emitted for the renderer match the original bytes at
`0x80476470..0x80476480`; original-reference inspection found no other unit
using either constant. The split records these ranges for the eventual link,
but generated graph and symbol-localization checks remain pending.
