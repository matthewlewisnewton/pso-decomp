# Boss7 tentacle bank prerequisite

This change isolates the three genuine mutable banks at
`0x80541528..0x80541918`: 14 runtime nodes (784 bytes), 14 segment positions
(168 bytes), and 14 angle words (56 bytes). It preserves Scott Lowry's scoped
ownership work from `1eadd7feea746a6f5bd1c4d905ff7700e6b724b1` and the three
array definitions from `c5e453d76e407c851294cd61442585d8336f9ae6`, with attribution
in the preceding commits. The unrelated equipment table and the upstream
builder implementation are excluded.

`Boss7TentacleBanks.cpp` is an explicit storage-only link contribution of the
same Boss7 tentacle owner, not a claim about the original filename or a separate
original translation unit. The original compiler's shared bank base remains
evidence that the original code and banks were compiled together. This source
organization permits independent qualification of the exact existing storage
while the original code remains selected from fallback. There is one definition
of each bank, in address order. No padding object, dummy reference, generated
code, or checker exception is introduced.

The shared header declares real `DragonModelNode[14]`, `Vec[14]`, and `u32[14]`
objects with asserted sizes and field offsets. Needle's unlinked source uses
these same declarations; its only access changes are the corresponding member
names. The original code has not been recovered or promoted by this change.

These destination objects do not assert a live typed source resource. The
original helper's extra four-byte read beyond the terminal serialized node is
pre-existing behavior, and its source contract remains a separate hold in
PR239. Defining the zero-initialized destination bank neither introduces that
read nor resolves it. Adjacent motion-state storage at `0x80541918..0x80541928`
remains original fallback.

Native qualification is pending. Required checks are exact BSS size, alignment,
symbol offsets and unique ownership; unchanged original code and all affected
consumer relocations; preservation of the adjacent fallback range; actual
selection of the data object's compiled source; and original-DOL/no-loss checks.
The normal data-only-unit rules and all ordinary linkage gates remain in force.
Until those checks pass, this draft claims no new matched or source-linked
bytes, no exact functions, and no readiness to merge.
