# Action-palette source linkage

Continuation #403 qualification: the [combined-stack integration](window-palette-main-stack-integration.md)
retains this consolidated owner and compiler context while preserving its already
recovered Base-derived class, native constructor/task, free tag ABI and typed
texture-list storage pointers. The raw-construction/intermediate-Base statements
below describe the incoming main snapshot, not combined B. The raw destructor
and remaining callback/entry/helper qualifications stay explicit in that note.
The later [native destructor qualification](window-palette-native-destruction.md)
also resolves that raw deleting boundary on B while retaining the other holds.

Base: fork main `e65f11ce6ec99c006909422f81da1c0a46ac062e`.

The former `TWindowHelpItem_80243408`, `text_802437C4`, and
`TWindowActionPalette` fragments form one source unit at
`0x80243408–0x8024420C` with data at `0x804CDCA8–0x804CDFE8`.
The constructor passes the layout at `0x804CDF9C` to the window-base
constructor; that descriptor points to the records at `0x804CDE50`.
The same data range contains the class's six-word vtable and the icon
helper's eight-entry compiler-generated switch table. This is evidence
for consolidating the fragments, rather than assigning the vtable to an
unrelated data-only object.

## Layout and emission

The five pixel-coordinate tables contain 19, 17, 6, 3, and 8 UV pairs.
The icon helper uses one pooled address and offsets `0`, `0x98`, `0x120`,
`0x150`, and `0x168`. They remain separate C++ arrays: replacing them with
members of one aggregate made GC/2.6 calculate the addresses differently.
The symbol boundaries now describe those arrays rather than treating all
424 bytes as the first array.

`init_window_layout_entries` reads the two-word column/row header, then
walks type-6 sprite records in 0x30-byte steps and type-4 number records in
0x1C-byte steps. The recovered layout has five sprites and three number
labels. The sprite constructor at `0x8025B3D8` reads the position, size,
pixel UV, depth, color, texture-list pointer, texture index, and flags
from these records. Size checks cover both record types, the 332-byte
record collection, and the 20-byte window descriptor.

Immediate compilation reproduces the instructions but places the icon
switch table before the vtable. With `-inline off,deferred` and reversed
function definitions, GC/2.6 emits the vtable at data offset `0x308` and
the switch table at `0x320`, matching the original. The class's first
virtual declaration is its member-defined renderer, so the compiler emits
the table using the inherited `TObject` slot order. There is no handwritten
vtable. This follows the measured approach in
[compiler emission evidence](compiler-emission-evidence.md); it does not
establish the historical source definition order.

The existing constructor, destructor, base-window lifecycle, and
four-byte palette-entry accessors retain their bounded C ABI interfaces.
The native class declaration recovers the scene-node prefix and virtual
slots without adding implicit base construction or destruction to those
entry points. The intermediate window-class relationship and the entry
class's original name remain unresolved.

## Argument recovery

At `0x80243464`, the original forwards the incoming slot and client ID to
`get_palette_consumable_count`, looks up the returned item ID, and calls
`TItem::get_amount` through vtable offset `0x90`. The old no-argument
signature and function-pointer casts concealed those arguments. The free
function is now `get_palette_item_amount(u16, s32)` and uses the shared
`TItem` interface.

The icon group and label group are `int`, while the icon slot is `u16`.
The original masks the group inside the callee. Declaring that argument
as `u16` adds masks at the caller; declaring it as `s32` (CodeWarrior's
`long`, distinct from `int`) changes temporary lifetimes and register
assignment in `update_slot_sprites`. The private `update_slot_icon` slot
is likewise `u16`; its symbol now reflects that signature, so its call no
longer needs an incompatible function-pointer cast. These declarations
preserve all original instructions.

## Validation

The unchanged base passed the original-DOL hash and retention checks.
The consolidated object has 14 exact functions (3,588 bytes), an exact
832-byte data section, and matching allocated relocations. Source linkage
adds 956 code bytes and 832 data bytes; the other 2,632 code bytes were
already linked from the two neighboring fragments. Address-based coverage
and all existing matches are preserved. Unit counts fall by two for the
consolidation and linked-unit counts by one.

The complete source-linked build reproduces the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py` checks the
full report delta, linked units, and generated retention metadata. No
original objects, raw disassembly, or build artifacts are committed.
