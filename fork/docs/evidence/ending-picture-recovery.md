# Ending-picture native layout and data ownership

Validated against fork main `6d478092bf9791e1db79bb20a886173bb97e7021`.
The old `TEndingPic.cpp` already matched its instructions, but accessed every
field through offsets, represented the constructor as a C function, and read
its name, state and floating-point constants from fallback objects.

## Layout and constructor

The constructor at `0x80352F6C` forwards its second argument to
`TObject(TObject *)`. Its caller in `TEnding::TEnding` allocates `0xF0` bytes
and supplies `tl_01` in that argument. `TEndingPic(TObject *)` and
`new TEndingPic(tl_01)` reproduce both functions exactly. The old `Fv` split
name incorrectly omitted the parent parameter; the corrected symbol is
`__ct__10TEndingPicFP7TObject`.

The task and drawing functions establish the elapsed-tick counter at `0x1C`,
next picture at `0x24`, picture pair at `0x28`, six eight-float quad records
at `0x2C`, and timing rate at `0xEC`. Quad records contain four screen edges
and four texture coordinates; the draw calls pass the records at `0xAC`
and `0xCC`. These descriptive member names are inferred from their uses.
The word at `0x20` is only initialized to `0xFF` here and remains `field_20`.
The header checks the quad offset, timing offset and complete object size.
The state machine retains the original `3 * rate - rate` and
`14 * rate - rate` threshold expressions and the final picture-pair clamp.

The constructor loads the pointer at `0x805D4378`, which refers to the
`TEndingPic` string at `0x804790F0`. An explicit const character array emits
that string in `.rodata`; a direct string-literal pointer initializer instead
emitted it in `.data` with the existing compiler settings, moving the native
vtable. The const-array form needs no new compiler override or pragma.
The vtable remains compiler-generated.

## Ending-picture and item boundaries

The ending-picture code ends after the texture-list getter at `0x80353018`.
The following event-item helpers through `0x803531FC` use the item owner and
are the targets of the use-effect dispatcher's member-function-pointer table.
They now live immediately before that dispatcher in
`TItemSpecialEvent_803531FC.cpp`; its existing filename still identifies the
dispatcher entry point.

The ending-picture literal pool at `0x805DFEF0` contains the drawing depth
and 14 geometry constants, including zero at `0x805DFEF8`. The item helper
uses a separate zero at `0x805DFF30`, followed by `10000.0f`. Moving the
helpers lets each source file emit its own ordinary literal pool and matches
both complete objects under their existing GC/2.6 and GC/2.0 settings.
This supports the recovered boundary; it does not establish original source
filenames or source spelling. The inherited event-item name remains the
explicit inference documented in its [group evidence](titem-special-event-group-evidence.md).

The investigation used the const-array definitions and late-constant/local-label
handling described by [window effect light recovery](window-effect-light-recovery-evidence.md),
[conversion pools](conversion-pool-constants.md), and the warning to compare
relocations as well as instructions in [compiler emission evidence](compiler-emission-evidence.md).
The initial native constructor and member implementation preserved all function
matches. Const string placement, separating the two pools, correcting two symbol
extents, and localizing the anonymous pool labels resolved the data differences.
The repository localization tool checked compiled and original active objects
and found no foreign users of the 17 literal labels before marking them local.

## Sections and validation

The complete ending-picture unit now covers 8 exact functions (1,120 code bytes)
and 120 data bytes: `.rodata` 16, `.data` 24, `.sdata` 8, `.sbss` 8 and
`.sdata2` 64. Its animation state and current texture-list pointer are source
definitions. The separate item's 11 functions (872 code bytes) and 404 data
bytes also match and link. The ending controller's four functions remain exact.
The shared wall-texture-list storage remains a 32-bit integer interface in its
owning unit; the local getter preserves that boundary.

The class-name pointer and final float are four-byte objects, rather than the
old eight-byte extents that included alignment padding. The native linker
recreates the original zero tails after the name string, pointer and float pool.
The split also retires four unowned zero alignment bytes at
`0x805D4374`–`0x805D4378` from the report denominator; no data object is removed,
and the linked DOL reproduces those bytes.

Full `tools/check_pr.py` passes: original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, no function or code losses,
104 additional matched and source-linked data bytes, and a four-byte alignment
padding denominator reduction. Every linked unit passes the link check.
The regenerated retention block adds 12 entries and removes none; its freshness
check passes. The actual linker inputs select both compiled source objects and
neither original fallback object. The source-only tool suite (346 tests), portable
behavior tests, and address/undefined sanitizer tests pass.
