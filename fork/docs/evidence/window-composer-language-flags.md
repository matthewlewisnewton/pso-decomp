# Composer language-derived input flags

At checkpoint f91022962d, helper 8025CC48 still carried a Hard-keyboard C alias
and byte-offset accesses. Its two original direct calls pass the borrowed
composer, not Hard: release_keyboard forwards m_composer after a null check,
and run_task forwards that same field within its existing non-null branch.
An all-original-object relocation census finds exactly these two zero-addend
calls and no other relocation reference. This is not an absence proof for
computed calls, but no such exposure was found in the inspected source.

The helper is now TWindowKeyBoardBase::reset_input_flags_for_language. It uses
the actual composer m_b4 word and inherited signed m_20 halfword. Japanese
behavior still clears m_b4 then tests saved-client masks 16, 32, 64, 128 in order,
setting bits 1, 2, 4, 8. English/German/French/Spanish assign 6; other language values
leave the word unchanged. Signed client promotion, call order, repeated reads,
word stores and caller null behavior are unchanged. No allocation, deletion,
borrowing-duration or original member spelling is inferred.

The three complete objects preserve allocated bytes/headers, symbol metadata
and order, and resolved relocation targets after only the recovered export
rename. The other 3,629 active compiled objects and original DOL are raw-identical.
Capacity-gated native build and aggregate no-loss checks pass; retention remains
19,489 names, all 3,622 linked units exact. No layout, provider, table, compiler
control or source-selection change is made. Hard destructor/table, no-argument
query receiver, other window-family and borrowed-lifetime holds remain.
