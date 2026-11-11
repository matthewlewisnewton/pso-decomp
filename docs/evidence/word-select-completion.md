# Word-select formatter completion and table grouping

The selected recovery span is `0x803430BC..0x80346A84`: 25 functions and
14,792 bytes of code. Before recovery, 24 functions (13,164 bytes) matched;
the 1,628-byte Spanish formatter at `0x80345608` was absent. This change
completes that formatter and covers the entire selected span from source.
The implementation uses the existing payload and full-width player interfaces
in `WordSelectMessage.h`; these remain bounded interfaces, not a reconstruction
of every word-select method or the complete payload's trailing parameters.

## Spanish formatting

The original uses six message types, including recursive conversion of type 3,
opening punctuation for word IDs `0x685`/`0x686`, player-gender-dependent forms,
and per-word prefix categories loaded from the Spanish archive header at +0x20.
The archive loader and consumers now share that category pointer's byte type.
The original's word IDs, range checks, table selections and final terminator
(included in the returned count) are preserved.

The recursive scratch record retains the extra storage already used by the
other localized formatters: the shared 12-byte payload view does not describe
all trailing fields copied by the conversion helper. This change does not
claim recovery of that larger wire/storage record.

GC/2.6's normal flags plus scoped `dont_inline off` and `inline_depth(1)`
inline `append_spanish_word_form`. The helper keeps the selected word live
across separator formatting. A flat implementation differed in three
instructions only: it used r27 where the original uses r30 for the second word
of type 4. The helper and the shared counter/form temporary reproduce the
complete original function. Removing the depth setting produces a 1,536-byte
function instead of 1,628 bytes, so it is not a decorative pragma.
Ports may remove these controls and keep the ordinary C++ helper.

## Data grouping and provisional boundary

The original's first compiler-generated table occupies
`0x804EFD68..0x804EFDBC` (84 bytes). Its five later tables occupy
`0x804EFDC0..0x804EFF1C` (348 bytes). There are no references or named objects
in the intervening four zero bytes. Compiling the old combined source places
the later tables at offset 0x54 rather than 0x58: every function can match
while the data layout remains wrong.

Separating the window/controller prefix from the lookup/formatter helpers at
`0x8034435C` gives two normal GC/2.6 objects. Their `.text` sizes are 4,768 and
10,024 bytes; their `.data` sizes are 84 and 348 bytes, both with the compiler's
ordinary eight-byte section alignment. The linker therefore recreates the
four-byte gap before the second group. The split introduces no padding object,
manual jump table, assembly or per-unit compiler override.

This is an evidence-backed grouping that reproduces code and data layout.
It does not establish an original filename or prove that `0x8034435C` was the
original source-file boundary. The address coverage check explicitly recognizes
`0x804EFDBC..0x804EFDC0` as zero alignment padding; the data denominator drops
by four bytes while all 432 table bytes become exact and source-linked.

## Validation

Initial recovery base: `5bba9c44adebc1cfa019def85e1f39f6da340ef0`.
Publication base: `08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`.
The unchanged publication base passes its full build and retention check.
The initial recovery passed the address-based no-loss check before rebasing.
Final checks compare the publication base and the saved complete pre-rebase
candidate by original address, including function, code/data and source-link
coverage. Both generated objects compare identically against
fresh original splits for complete allocated bytes, section alignment and
normalized relocation targets. All 759 normalized relocations match. The actual linker inputs select both
compiled source objects. The full linked build reproduces original DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

`tools/check_pr.py --no-build` passes after the full native linked build; all
3,612 linked units pass. The generated retention change adds four word-select
symbols and removes none. Both selected groups are 100% exact and linked.
