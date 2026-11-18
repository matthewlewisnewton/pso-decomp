# Context arguments in keyboard and scanline rendering

This follows the [context-owner repair](window-draw-context-owner.md), starting at
continuation `5404ec95c70b93556277aeee8e320157ede52d34` on main
`d6fc686573510cc9612beb6a2d71576ad685301c`. It corrects a bounded set of context
arguments without claiming actual Soft-window lifetime or clearing the separate
CustomSelect valid-session guarantee.

## Original transport and actual argument domain

Soft render obtains its context from the established draw-default helper, then
passes it to grid, outline and glyph/icon rendering. Those three helpers access
context geometry, depth, color and transforms. Their second parameter now names
`TWindowDrawContext *` instead of the false Soft-window pointer view. The first
keyboard/window receiver is unchanged and retains its wider layout qualifications.

The static key-frame helper likewise receives the whole context. It uses x/y and
context transforms, not merely a two-float position. Its second parameter becomes
`TWindowDrawContext *`, with direct x/y members and the two existing callers
forwarding their context without a float-array cast. The one resulting native
export rename describes that actual pointer parameter at the same address.
The Soft namespace for this static keyboard helper does not establish a native
Soft class layout or an implicit object receiver.

The ComCard scanline helper's third parameter supplies the same context geometry,
depth and pivot scaling. Its definition/declaration and sole call now use the
actual context type. The enclosing scanline wrapper keeps its existing raw-byte
entry interface; the typed call does not qualify that broader ABI automatically.

Finally, Soft render uses the existing shared
`TWindowDD::draw_default_entry((s32)this)` declaration instead of a no-argument
local alias. The actual helper already takes that native window word. Its result
is kept as a context pointer and forwarded explicitly in the same helper order.
The native word/pointer boundary is preserved, without a widened return or new
lifetime/ownership contract. Existing null/failure preconditions remain.

## Complete reference and object controls

A generated-original census finds six zero-addend REL24 references to the five
helpers, all in two units. There are no named address-taking/interior references
in that cohort. The current census covers 4960 original and 3632 active compiled
objects, 512644 relocation records, with no undefined old export name. Computed
runtime address arithmetic is outside that bound.

Six complete individual bodies and function-relative resolved targets match
original:

| Routine | Bytes |
| --- | ---: |
| Glyph/icon helper | 1820 |
| Keyboard outline | 608 |
| Grid/page selector | 856 |
| Key frame | 580 |
| Soft render | 88 |
| ComCard scanline helper | 436 |

The complete 9096-byte text and all other payloads in TKeyBoardControl preserve
the preceding production object. Symbol record order, binding, section, offset
and size agree after only the single documented key-frame export rename;
string-table length, consequent symbol/file offsets and zero alignment padding
account for serialization differences. Every other payload byte, compiler
metadata and raw relocation record agrees. Raw ELF identity for that owner is
not claimed, and no anonymous-symbol or body/address normalization is used.

The entire 7864-byte-text ComCard owner remains raw byte-identical as a complete
ELF. 3631 of the 3632 active compiled objects are raw-identical, including that
ComCard owner. Both source providers remain selected once, their original
fallbacks absent. DOL, complete Ninja graph and ordered linker inputs remain
byte-identical. No code/data coverage or object/table ownership is added.

## Validation and retained limits

The fixed source candidate passes the capacity-gated native build in 14.03 seconds.
Initial acceptance correctly rejects the stale retention spelling for the one
renamed export. Standard `force-active --write` changes exactly that old/new name,
retaining 18837 entries; the subsequent full gated rebuild passes in 84.46 seconds
with original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Complete-object/original/census checks are replayed against that rebuilt state.
Final address-based acceptance preserves all function/code/data/coverage metrics,
reports one rename, retains 3612 exact linked units and has no retention drift.
Inventory and whitespace checks pass. No compiler flag, pragma, substitute helper body,
allocation, initializer, type-width variant or original-provider change is used.

Private receipts and exact controls are in `pr403-context-arguments/`.
Independent source/proof review supports the typed context argument cohort.
The first Soft/composer receiver views, raw clipping/transform and scanline entry
interfaces, generic overlay inheritance and singleton word/lifetime protocol
remain qualified. Actual Soft construction/destruction, CustomSelect valid-session
lifetime, Word, ComCard trailing-word/table and every other standing ownership,
initialization and interface hold remain. The continuation stays draft.
