# Quest display-prefix prerequisite

This separate inactive checkpoint follows the canonical slot definition at
`50ad77435cf35a69136678f3c62cd001cc2ee31e`. Neither checkpoint changes PR #238's
six-object selection. The original upstream import remains in their dependency
history; this definition uses the original symbol and extent rather than
introducing a renamed or enlarged object.

`QuestDownloadDisplayPrefix.cpp` defines the actual 12-byte encoded character
array at `80596258..80596264`. Both existing source consumers declare this symbol
as `u8[]`; the definition keeps that element type and C linkage. Static zero
initialization supplies the backing array before the frontend initializes it.
No structure overlay, union-member transition or node lifetime is needed for
this character storage. The remaining 1,028-byte scratch object is separate.

The original-reference census identifies four direct users. Frontend 5B94
initializes the prefix with `strcpy` from the constant at `8047E68C`. That constant
terminates at offset 10, so the copy uses 11 bytes within the 12-byte object.
Native B4D4 writes display-count bytes at offsets 5, 6 and 7, then passes the
prefix to C95C. BEFC and C460 use its address only as an anchor for the next
object at `+12`; they do not establish a larger prefix array.

C95C reads encoded characters until NUL, advancing by one or two bytes. Its
retained compiled body and symbolic relocations equal the original. A finite
read-only check of the retained prefix, all 256 possibilities for the first
count byte and the ten decimal possibilities for each remaining count byte
covered 25,600 cases: termination was at offset 5 or 10 and the maximum read
offset was 10. This is a bound for that prefix reader and the native count-write
domain, not a proof about arbitrary corruptions or other scratch writers.
No original string or asset bytes are included in this document or source.

The actual validated #238 linker input selects the frontend source object and
the original provider object. The frontend's prefix declaration is compatible
with this definition; its prefix-address relocations and copy call are unchanged.
The fallback provider retains the original BEFC/C460 `+12` address calculations.
Defining this separate data object therefore does not require changing the
provider source or recovering all sixteen missing provider functions. Recovering
those two consumers later still requires proper separate-object scratch access;
this definition does not bless their provisional source pointer arithmetic.

The definition is absent from the split and linked-unit lists. Original fallback
still owns all four deferred objects, so the checkpoint claims zero new linked
bytes. Before selection, independently review this narrow ownership boundary,
target-compile the new object, and qualify its size, alignment and symbols. The
proposed source range ends four modulo eight; actual generated scratch fallback
alignment and consumed linker inputs must preserve `80596264` without added
padding. Existing selected 12-byte BSS sections show that such extents are
supported, but do not qualify this new split.

Only after actual-graph review and development admission should native linkage,
original-DOL equality and all raw no-loss checks establish a gain. The 2,448-byte
workspace and 1,028-byte scratch remain held for their own type, producer-bound
and phase-lifetime work. No shared header, function body, scanner, retention or
build-selection change is part of this checkpoint.
