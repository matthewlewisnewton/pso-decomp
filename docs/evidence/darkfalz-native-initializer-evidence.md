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

The source-link continuation uses the compiler's supported deferred generation
and debug source-file sections (`-inline deferred -sym on`), as already used by
the Panarms recovery. Ordinary definitions are reversed, and the four final
helpers live in a source-private header. The resulting two `.text` contributions
concatenate to the original layout: controller methods, native initializer, then
helpers. Their definitions remain ordinary C++ functions, with their existing
linkage and floating-point settings; no inline-only export or manual constructor
registration is introduced. This arrangement is an implementation choice and
does not establish historical filenames or compiler switches.

A successful private production compile reproduces all 56 original function
positions, sizes and instruction bytes, all 6,140 code bytes, all 1,308 owned data
bytes across `.ctors`, `.rodata`, `.data` and `.sdata2`, and all 272 resolved
relocations. The compiler accepts the switches/pragmas without diagnostics. The
three compiler constants are referenced only within this original unit; using
native literals and their compiler-local metadata removes unnecessary exports
without changing data addresses, extents or relocation targets.

Shared adoption of the bounded compiler exception and private-constant metadata
is pending coordination. The existing 8004B07C declaration/definition mismatch
also has a separately probed, instruction-preserving parameter correction awaiting
allocation. Full development, source-selection, original-DOL and independent
review gates remain required before this continuation can claim source linkage.
