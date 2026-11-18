# Speech-balloon name plate and unit linkage

The baseline is fork main `cda82a7aad7de1bf9b86470002df3f68d1c8c039`.
`pso/misc/TWindowFukidasi.cpp` owns text at `0x8025010C`–`0x80252AE4`,
read-only data at `0x8044ED68`–`0x8044ED80`, switch tables at
`0x804CF0D0`–`0x804CF120`, and small constants at
`0x805DCD0C`–`0x805DCDC8`. Initially 31 of its 32 functions and 80 of
292 data bytes match; the unit is not source-linked.

## Recovered behavior and boundaries

The missing 800-byte function at `0x80251EC8` reads the balloon's name at
offset `0x78` and the shared draw context's opening tick at `0x30`. It skips
absent names and negative ticks, fades in over six ticks, draws the two
textured end caps and an optional stretched middle, then centers short names
and draws clipped small-font text. The background preserves the supplied RGB
bits, while the text uses the separately computed alpha with black RGB.

The implementation uses `TUnk_804CF0B8::name` and `TWindowDrawContext` fields.
The old `draw_name_plate__15TWindowFukidasiFv` external spelling is retained
at the existing boundary. This does not settle the original class name or
reconstruct the rest of the unit's legacy overlays and helper signatures.

The original wrapper at `0x800FC3E0` only calls `0x800FC400`. That leaf
overwrites `r3` with `localized_alphabet_list` before binding the texture list;
neither entry consumes an incoming argument. The former member declarations
with a pointer/integer argument introduced an unnecessary argument setup in
the recovered caller. Both entries are now shared no-argument free functions,
`begin_small_font_draw` and `bind_small_font_texture_list`, and their direct
callers use the same header. These names describe the observed operations.

## Matching iterations

The first complete C++ implementation compiled to 804 bytes and compared at
94.49%. A positive visibility guard reproduces the original exit branches.
Writing the RGB replacement with complementary masks allows the native
`rlwimi` form; the alpha remains available separately for the text call.

The optimizer experiments follow the repository's
[packed-word](pack-movie-frame-unit-flags.md) and
[symbol-chat](symbol-chat-parts-recovery-evidence.md) investigations. Scoped
propagation control raised the initial function to 99.225%, with the correct
800-byte size. Adding common-subexpression control gave 99.7%; lifetime
control as well gave 99.85%. A local left-edge value, used in both middle-quad
coordinates, resolved the remaining five floating-register fields. Scheduling
and peephole alternatives did not preserve the instruction sequence.
These controls describe observed GC/2.6 behavior, not original source pragmas.

Replacing the owned external floats with literals preserves the other
functions except four register/operand fields in `draw_body`. Expressing its
two texture-coordinate scales as division by `256.0f` restores those fields:
the backend folds division to multiplication by the exact reciprocal without
reversing the dividend's operand position. This follows the existing
[character-select UV evidence](chr-select-confirm-cell-store.md).

## Constant storage and alignment

Ordinary casts generate the unsigned and signed conversion biases in
`.rodata`. The angular conversion factor is a real intervening constant.
The name-plate height, zero, and clipping width likewise sit between emitted
float pools. Their definitions are interleaved with function definitions to
preserve object layout. Compatible pointer reads prevent the frontend from
also emitting anonymous copies of these four known initializers. Direct
reads of known initializers and simple reference forms produced duplicates;
keeping a pointer live across drawing calls changed register allocation.
This is the materialized-constant case described by
[conversion-pool evidence](conversion-pool-constants.md).

The 45 remaining pool names are localized only after the fresh active
original-object and compiled-object consumer inventory establishes that no
other unit references them. The three named floats and the angular factor
remain real source definitions. No pool-renaming hook, linker alias, asset
dump, handwritten switch table or assembly is introduced.

The final float at `0x805DCDC0` occupies four bytes. Its old eight-byte
symbol extent also covered four zero bytes before the next small-data owner,
which begins at `0x805DCDC8` with eight-byte alignment. The symbol size is
refined to four; the linker supplies the alignment tail. The compiled pool
has 184 bytes, and the original reported range has 188. The existing link
checker verifies this zero tail and its lack of an overlapping named object.
`cw_align: .sdata2=4` preserves the pool's actual four-byte-aligned start in
both ELF and the CodeWarrior comment record.

The unchanged baseline passes the full original-DOL build, address-based
no-loss checks, linked-unit checks, and retention freshness. The complete
unit adds one exact function and 800 matched code bytes, 212 matched data
bytes, and source linkage for 10,712 code bytes and 292 reported data bytes.

The final full build selects the compiled balloon object among 4,946 ordered
linker inputs and reproduces the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py --no-build`
passes against the clean baseline: no exact-function, code, data, coverage or
source-link losses; all 3,607 linked units remain exact. Retention changes add
27 names and remove none, and the regenerated retention check has no drift.
All 306 source-tool tests, portable behavior tests, sanitizer tests, the port
exception inventory check and changed-line whitespace checks pass.
