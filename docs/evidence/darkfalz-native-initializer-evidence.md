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

Historical native-object probes emitted a 1516-byte initializer identical to the
original instructions and 1288 matching data bytes with all 54 data relocations.
The local constant labels in symbols.txt come from those compiler outputs, not a
handwritten PMF representation. The three typed dispatchers preserve their
original instructions and resolved relocation targets. Corrected callback helper
calls pass the actual receiver explicitly, including the timer predicate and
8004D990; floating-point operations keep their original order.

The PR changes `configure.py` by adding exactly this `GAME_EXCEPTIONS` entry:

```python
    "pso/boss/TBoss4DarkFalz_8004C93C.cpp": {"cflags": _switch(cflags_pso, "-inline deferred", "-sym on")},
```

GC/2.6 and the game's `-O4,s` and `-sdata2 4` settings remain inherited. All other
entries, including main's calendar and player compiler overrides, are preserved.
PR190 added closed static-checker support for this exact unit/profile; that policy
support does not establish a current build result or native source linkage.

The matching source arrangement requires supported deferred generation and debug
source-file sections, as also used by the Panarms recovery. Ordinary definitions
are reversed, and the four final helpers live in a source-private header. In the
historical complete-object probe, the combined `-inline deferred -sym on` settings
emit two `.text` contributions: 5916 bytes for controller methods and the native
initializer, followed by 224 bytes for helpers. Deferred generation without
`-sym on`, or `-sym on` without deferred generation, retained a different function
order in the tested source forms. The combined profile is needed for the exact
whole-object layout, not merely for an initializer similarity score.

The definitions remain ordinary C++ functions with their existing linkage and
floating-point settings; no inline-only export or manual constructor registration
is introduced. This arrangement is an implementation choice and does not establish
historical filenames or compiler switches.

The independently reviewed private compile at source checkpoint
`8ce4517f7f0a3d90ddabdcfc3846f9bbea522c3b` reproduced all 56 original function
positions, sizes and instruction bytes, all 6,140 code bytes, all 1,308 owned data
bytes across `.ctors`, `.rodata`, `.data` and `.sdata2`, and all 272 resolved
relocations. The compiler accepted the switches/pragmas without diagnostics. The
three compiler constants are referenced only within this original unit; using
native literals and their compiler-local metadata removes unnecessary exports
without changing data addresses, extents or relocation targets.

The allocated helper repair now consistently declares the existing C helper at
8004B07C as `int (TBoss4DarkFalz *)`; it ignores the argument and still returns
zero. All five original callers explicitly forward the same controller receiver.
This removes the former no-argument/long-return declaration mismatch without
changing the C symbol, code, or receiver lifetime. The owned constant aliases and
38 PMF labels have also been prepared within their existing addresses/extents.

At adoption checkpoint `729f4c4ce0a286f9e4ba02669771f24b8b9b6e8b`, integrated with
main `36121c7635cf05d915cdc2f258c879b7a736e2a7`, all 44 class/helper-header
consumers produced byte-identical complete before/after objects for the bounded
helper repair under their then-configured flags. A separate check preserved
PR125's consumer at `2b64aa2015164259870d77ee72b006b63f296598`. Those are historical
input/output results; subsequent main and header changes are not covered by them.

The conflict repair against main `0ea667b2ae02f09c65cd9464314c0d5993618c6c`
retains the literal Dark Falz profile alongside main's overrides. It also preserves
main's resource tables, resource-descriptor definitions and vector corrections in
`TObjDFHorming.cpp`. Static configuration/source/consumer checks establish this
merge's input preservation, not a fresh compiler-output result. Unchanged
historical native-object evidence is not rebuilt or relabeled as current proof.

Source selection is unchanged. The actual current production compile must confirm
compiler-local alias names and the complete code/data/relocation layout. Final
merge validation still requires fresh split/report inputs, localization and
generated-retention checks, native source-link eligibility and ordered linker
provenance, original-DOL equality, and unfiltered code/data/function/link no-loss
checks. The merge process owns those acceptance gates; this document makes no
current native source-linkage or full-build claim.
