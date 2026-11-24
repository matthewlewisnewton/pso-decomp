# Native Palette destruction in the consolidated owner

Following the [current-main integration](window-palette-main-stack-integration.md)
at `6249cfec18bbc43a1dae1aab9f0bc1bd67fc87cf`, Palette's deleting wrapper is
now its actual C++ destructor. The body calls the existing array-runtime cleanup
once for `resources`, stride 4/count 3. The compiler supplies the vptr update,
automatic Base destruction, null guard and hidden deleting-flag protocol. Manual
Base cleanup, delete handling and the unused raw ABI declarations are removed.
No tag class, extra cleanup or default construction is invented.

## New evidence and one bounded test

The earlier [native destructor probe](window-action-palette-construction.md)
matched its 116 bytes but separated the vtable from the icon's jump-table owner,
losing an exact function. Main's accepted consolidation, reconciled with this
continuation's native Base chain, supplies a new coherent owner. The destructor
can now be tested without extracting either table or changing compiler context.

An active original census of 4964 objects and 249768 relocations finds one named
reference to the 116-byte destructor: its own vtable's zero-addend ADDR32 entry.
No direct caller, interior reference or descendant constructor is inferred.
Virtual destruction retains the original entrypoint, slot and target ABI.

One candidate replaces only the raw wrapper with the native body and removes
its unused constructor-ABI include and delete forward declaration. Profile,
function organization, key declaration, fields, constructor, callbacks and
array-runtime protocol stay fixed. There is no scheduling, table, layout,
return-type or compiler-option variant.

## Complete owner qualification

All 3588 text bytes, 832 data bytes, 14 function bodies/offsets/sizes, allocated
section headers and 198 resolved relocations remain original-exact. The 24-byte
compiler vtable at data+0x308 and following 32-byte icon switch table retain all
four/eight resolved targets. The native 260-byte constructor, 584-byte ordinary-new
producer unit and all 3630 other active compiled objects remain unchanged.

Complete ELF byte identity is **false**. The compiler renames the local anonymous
jump-table symbol from `@236` to `@234`, changing one byte in `.strtab`. Its local
binding, data offset 800, size 32 and every relocation destination stay the same.
Replacing only that spelling in the prior ELF reproduces the entire candidate;
all other ELF bytes, including raw relocation records and global symbols, are
identical. Independent review confirms this unobservable local-label change.
No original-byte, coverage, relocation or source-link gate is waived.

The earlier private `local-symbol-qualification.json` records this comparison
at the scratch stage, before production activation. Its phase flag describes
that earlier checkpoint. Subsequent production compilation reproduces the
scratch candidate ELF exactly and is qualified separately below.

## Full validation and remaining holds

The capacity-gated full production build passes in 4.10 seconds and reproduces
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The report and
complete Ninja graph remain byte-identical to the published integration.
Address-based acceptance, all 3600 exact linked units, 18596-name retention and
port inventory pass with zero metric change. The complete source owner remains
selected once, with its original object and retired fragments absent. Prior
fresh-main/focused comparisons, protected providers/remainders and all strict
coverage qualifications remain intact; no new main build is claimed here.

Raw Base/Addition calls fall from 16 across 9 units to 15 across 8 units, with the
same three bindings still needed elsewhere. Only Palette's raw deleting-wrapper
hold is resolved. Callback signatures and tag storage/lifetime, negative cleanup
flags, the first-record reset repeated three times, unchecked icon indices,
external icon argument views and light/helper arity remain qualified. No existing
asymmetry is silently repaired. Word placement, ComCard trailing-word, Parts
profile/export, numeric-input return and every other hold remain unchanged.

Private fixed-source command/receipt, original-reference census, ELF comparison,
local-symbol qualification, production build and acceptance/proof are in
`pr403-palette-native-dtor/`. No original object, binary or raw disassembly is
published. Independent source and frozen-head review remain publication gates.
The PR stays draft; this change does not claim global interface portability.
