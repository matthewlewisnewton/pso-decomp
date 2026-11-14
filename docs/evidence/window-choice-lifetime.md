# Native ChoiceSetting lifetime and unresolved auxiliary ownership

This follows published PR #268 checkpoint
`546eb00fc1c6b5f6c1465048675fc5585a89d7c2`, including main
`fe6cdb14138b2413778c08f21fd1851170c22ab5`.

## Native constructor and cleanup chain

The existing address-named `TUnk_804D0658` owns the 0x80-byte Addition-derived
window. Its constructor at 80269004 takes a position pointer and word-valued
entry count, initializes Addition with client 4 and the existing descriptor,
then initializes its entries. The old `TWindowMenuInfomation__ct` routine at
80268B34 is that entry initialization method, not a separately constructed
base object. No empty default or extra TObject construction is introduced.

`TWindowChoiceSetting` adds 16-bit state at 0x80 with preserved padding and
has size 0x84. Its constructor
forwards both position and count to the real base constructor, then sets its
name and state. Its formerly one-argument C declaration depended on live r4/r5
without declaring them. Both factories now use ordinary `new`. Extent/count
setup has one canonical pointer/word declaration; its wrapper forwards both
arguments explicitly, replacing another implicit live-register dependency.
The two-float extent input stays opaque; no original vector type is asserted.

The base destructor releases its observed children and automatically destroys
Addition. The derived destructor is empty and automatically destroys the real
base. Both use the compiler's native cleanup/deleting protocol. Render/task
methods are attached to the actual owners, replacing SubStatusDisp labels.
Both compiler-generated 24-byte tables have destructor/task/render/inherited
TObject shadow slots, with no extra virtual function. Their claims are
`[804D0658,804D0670)` and `[804CE808,804CE820)`. The mutable descriptor and
neighboring entry data remain outside these claims. No table, padding or
alignment is written by hand.

Direct access to actual members removes the decompiler receiver aliases that
changed register homes in the initial native methods. Array entry lookup uses
Base's real int-index declaration; close/draw/task checks use actual member
receivers, and the entry-flag helper receives its observed entry pointer
explicitly. No borrowed function-pointer view is added to make these match.
All existing field types and descendant layouts remain; additional offset
assertions cover 0x7C and 0x80.

## Auxiliary producer remains unknown

The common initialization method clears fields 0x78 and 0x7C. Both examined
constructor paths invoke it; the derived constructor only adds its state at
0x80. The setup helper allocates a 0x24-byte heading at 0x78 and sets flag
0x40. It does not allocate a scrollbar or write 0x7C. No positive producer for
0x7C was found on these construction/setup paths.

The nullable 0x7C field's consumers pass it to scroll clamping, drawing, the
counter and release protocol. This supports the observed prefix operations,
not full class identity or a claim that the field is always zero. Its positive
producer may be in an unrecovered/computed path. The bytes remain opaque and
release stays type-erased; no Scroll pointer type or native destructor is
assigned to this field. The separate 0x78 heading lifetime is unchanged.

The [expanded task-global relocation audit](window-task-owner.md) also finds
no relocation target at 805D5D94, including signed offsets from neighboring
symbols. That result does not prove padding or exclude runtime-computed
accesses. Its catalog range and absent source claim remain unchanged.

## Qualification

Complete unrelocated original/compiled text is identical:

| Source unit | Bytes |
| --- | ---: |
| TWindowChoiceSetting | 2,160 |
| TWindowChoiceSetting_80249240 | 956 |
| text_80269004 | 96 |
| TWindowSubComCard_80249120 | 288 |

The complete linked DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr preserves
all 27,384 exact functions and 3,585 exact linked units, with no code or
address-coverage loss. The two tables add 48 matched/linked data bytes. The
porting inventory passes and retention is clean at 17,656 entries (+6, -0).
Against fresh main fe6cdb141 the combined PR retains +600 matched code,
+728 linked code and now +376 matched/linked data bytes. The two previously
qualified four-byte linker-padding coverage changes are unchanged. The
remaining ABI header still has four constructor and three destructor bindings;
its source calls fall from 85 to 83 across 43 units (Addition 4 construction /
4 cleanup). The unknown auxiliary producer, global word and broader legacy
interfaces keep the standing draft hold active.
