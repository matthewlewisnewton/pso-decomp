# Dark Falz native state initializer

The controller constructed in the `TObjDFHorming` translation unit installs the
`TBoss4DarkFalz` vtable. Its task dispatchers at 8004B084 and 8004B0F8 select a
0x34-byte state record using the receiver's field at 37C, then invoke its update
or tick member pointer on that same object. `change_state` at 8004B20C checks the
signed 0..15 bounds and old-state -1 sentinel, calls leave, changes the state,
and calls enter. No extra callback argument is supplied.

The shared record therefore uses `void (TBoss4DarkFalz::*)()`, with a name pointer
and four native 12-byte member pointers at offsets 04, 10, 1C and 28. The former
unrelated receiver overlay and union word reconstruction are removed. Twenty
callback definitions now receive `this` through their class interface. The
separate function at 8004CF6C retains an address placeholder because the existing
`update_parts()` name identifies 8004CAF4.

Native aggregate initialization emits the 38 compiler-owned member-pointer
constants at 80484F40–80485108, followed by the sixteen state records at
80485108–80485448. The initializer fills the callback fields before any controller
is created; name pointers are static relocations. The compiler also emits the
existing constructor-list entry at 80433F34. The preceding vtable, following
vectors, and original name strings retain their ranges and owners.

The complete production object emits a 1516-byte initializer identical to the
original instructions and 1288 matching data bytes with all 54 data relocations.
The local constant labels in symbols.txt come from that production compile, not a
handwritten PMF representation. The three typed dispatchers preserve their
original instructions and resolved relocation targets. Corrected callback helper
calls pass the actual receiver explicitly, including the timer predicate and
8004D990; floating-point operations keep their original order.

This checkpoint is still work in progress. The existing 8004B07C declaration and
definition disagree about an unused receiver parameter; their bounded correction
requires coordinated adoption. The compiler places the generated initializer
after four existing helpers rather than before them, so whole-object function
order does not yet qualify this unit for source linkage. No source-selection or
compiler-setting change is made. Exact function/data progress must be confirmed
by the normal full report and zero-loss gates; fallback DOL equality alone would
not establish native unit linkage.
