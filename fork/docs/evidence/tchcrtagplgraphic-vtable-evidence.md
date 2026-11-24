# TChCrTagPlGraphic vtable emission exception

`pso/misc/TChCrTagPlGraphic.cpp` owns `__vt__17TChCrTagPlGraphic`, an 8-entry
(0x20-byte) table at 0x804DCC78 whose last word is zero; the next owner starts
at 0x804DCC98. [CONTRIBUTING.md](../../CONTRIBUTING.md) says not to write vtables
by hand. This note records why the unit keeps a hand-written table and what was
measured instead, so the arrangement is a documented exception rather than a
precedent anyone has to re-derive.

The unit's vtable has five real entries: the destructor, `run_task`, `render`,
the inherited `TObject::render_shadows`, and the recovered slot-6 selection
predicate (`TChCrTagPlGraphic__vt4`, "is this tag the selected one"). The
original extent is eight words; word 7 is zero.

Measured with the project's GC/2.6 compiler (the standard build flags) on this
unit:

1. Declaring the slot-6 selection predicate as a class virtual — any member
   name — makes the compiler take over vtable emission in this unit. Left
   undefined, the link fails with `undefined:
   'TChCrTagPlGraphic::is_selected()'` referenced from the emitted
   `TChCrTagPlGraphic::__vt`.
2. Defined as a member, the compiler emits a 0x1c-byte (seven-entry) table.
   The linked DOL is still original-identical, but the object's `.data` is
   0x1c bytes against the unit's claimed 0x20-byte extent: objdiff marks the
   0x804DCC78 range non-exact and `link_units.py check` refuses the unit
   (`size .data:32!=28`), so `tools/check_pr.py` fails. The eighth zero word
   cannot be reproduced after a compiler-emitted vtable: MWCC emits user data
   before compiler vtables, so no trailing source object can follow the
   table, and file-scope `asm { }` is not accepted in C++ mode.
3. A member-defined first-declared virtual triggers the same takeover on its
   own. With the phantom `render_shadows` override removed, the empty member
   destructor became the first declared virtual and the compiler emitted its
   six-entry table next to the hand-written one. The destructor therefore
   uses the recovered free-function form (as `TChCrTagPlBack` already does),
   which keeps emission suppressed and reproduces the original 0x58-byte
   body at 0x802A33FC.

The hand-written table preserves the recovered symbol names and the original
five relocation targets; all eight functions and the table stay byte-identical
at their original addresses and the DOL hash is unchanged.

This is a bounded exception for this unit. If a supported compiler arrangement
reproduces the 0x20-byte extent — including the trailing word — from declared
class virtuals, replace the table with compiler emission and update this note.
