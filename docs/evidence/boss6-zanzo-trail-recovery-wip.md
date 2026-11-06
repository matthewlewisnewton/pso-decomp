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
renderer remains inexact: the scoped propagation setting gives 96.03% objdiff
similarity, not an exact match. Independent review found source holds in the
legacy owner constructors, the REL filename-size provider, and the ruler's
original static fan backing. The pragma is a compiler experiment, not proof of
source correctness.

The first donor comparison used a different checkout. A corrected targeted
comparison compiled 51 affected units from separate clean `3ba538f` and draft
`980b2f058` trees using copied GC/2.6 tools and identical per-unit commands.
All 50 non-target objects retained allocated-section bytes and normalized
relocation targets. This predates the Rico backing-data change below and does
not establish current configured graph identity. These targeted results do not
replace a full build, address-based no-loss check, real link-input audit, DOL
hash or independent review of the eventual head.

The original vtable at `0x804EC968..0x804EC980` has four relocations to the
native destructor, task, render and inherited shadow-render functions. The
compiler-emitted vtable has the same bytes and targets. The two conversion
constants emitted for the renderer match the original bytes at
`0x80476470..0x80476480`; original-reference inspection found no other unit
using either constant. The split records these ranges for the eventual link,
but generated graph and symbol-localization checks remain pending.

The Rico ring's static 3D fan now uses an actual four-element `Vec` array. The
native definitions cover the packed colors, positions, descriptor and 2D
positions at `0x804809D0..0x80480A40`, immediately before the existing vtable.
The original descriptor points to the position and color arrays, and the 2D
render parameters point to the following 2D array. A targeted compile retained
the original unit's complete code bytes; the added data bytes and two pointer
relocations match the original auto object, and the pre-existing vtable bytes
and four targets remain unchanged. The expanded split and real linked build
are not yet validated. A proposed native ruler data definition was not retained:
the original start is four-byte aligned, while the compiler emits an eight-byte
aligned data section. Its storage and linkage remain unresolved.

## Current-main merge (2026-11-05)

The branch now includes current `origin/main` (`ace1abf1a`) and drops the old
#289-only base. The merge keeps main's recovered `TBoss6Type1`/`TBoss6Type2`
layout and `TBoss6Zanzo::create`, and keeps this branch's typed trail frame,
`set_effect_points` receiver, REL buffer and drawing-descriptor interfaces.
Conflict resolution preserved the 98.77778% renderer source above.

A fresh full build from the merged tree verifies the original DOL SHA-1.
`check_pr.py` against a clean `ace1abf1a` baseline passes with zero exact,
matched-code, complete-code, linked-unit or source-link regressions, and adds
128 matched data bytes and 112 complete data bytes from the Rico backing data.
The renderer is still inexact and the `TBoss6Zanzo` unit still does not link, so
no function, code or link gain is claimed. Remaining holds: exact renderer
register allocation, the REL filename-size provider's `TScene` receiver, and
the ruler's original static fan backing.
