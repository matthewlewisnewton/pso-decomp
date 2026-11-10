# TWindowDD text measurement and word-select dispatcher boundaries

Investigated on PR #415 head `5b68b89c61227ae58032b46a2d204c558249af2a`,
against main `79768ce7da340723a8b6b559bca32fbdd705a5b2` (2026-11-10).
The executable has no original symbols. The reconstructed `Fv` and `FPv`
names are not evidence of parameter lists or class ownership.

## Text measurement: resolved

At `0x80246F8C`, the 36-byte helper loads the float at `0x805DCB70`
(1,000,000.0) into `f1`, calls `measure_message_text_width` at `0x8025A9C0`,
and returns. It does not replace `r3`. The latter function reads the entry's
flags at +0, its text pointer at +0x20, and writes width/height at +0x10/+0x14.
Its useful interface is `void measure_message_text_width(void *entry, f32 max_width)`.

The preview passes its entry in `r3` at `0x8026E4A8` before calling the
helper at `0x8026E4AC`. This is the same pointer used to set the text at
`0x8026E4A4` and to read the measured dimensions afterward. It is not the
shortcut window. Other callers pass text entries from unrelated windows.
In particular, `0x803412A0` calls `get_array_entry(0)`, preserves the returned
pointer in `r31`, and calls the helper with that same pointer still in `r3`.
The former no-argument static call depended on that unexpressed argument.

The source now declares and defines `extern "C" void measure_text_entry(void *)`
in a shared header and converts all 17 calls in 14 caller translation units.
The old no-argument static declaration is removed. The symbol at the same
address is renamed in `symbols.txt`; the DOL has no symbol table to preserve.
All original-object relocations are regenerated using that name. There is no
alias, assembler label, wrapper thunk or incompatible function-pointer call.
The opaque pointer leaves the full entry type unresolved without assigning it
to `TWindowDD`.

## Word-select formatting: unresolved matching constraint

At `0x8026E47C..0x8026E490`, the preview obtains the shared text buffer,
places it in `r4`, puts `shortcut + 4 bytes` in `r3`, narrows the local player
ID to 16 bits in `r5`, and calls `0x8034861C`. The dispatcher loads the global
language/mode into `r0`; it passes `r3`, `r4` and `r5` unchanged to a formatter:

| Mode | Address | Existing symbol |
|---|---|---|
| 0 | `0x803461CC` | `format_entry_text__9TWindowDDFPvPv` |
| 2 | `0x80344F54` | `format_german_message__9TWindowDDFPvPvUs` |
| 3 | `0x80344980` | `format_message_text__9TWindowDDFPvPvUs` |
| 4 | `0x80345608` | `TWindowDD__sub_80345608` |
| Other | `0x80345C64` | `format_english_message__9TWindowDDFPvPvUs` |

Those routines read `r3` as a compact word-select record: signed 16-bit
count at +0, type at +2, and IDs from +4. They write a byte string through
`r4`. The source's `DD_803461CC` is a 12-byte record with four ID slots,
not a window object. The localized routines preserve the third argument;
the gender lookup at `0x803472F8` explicitly narrows its own input to 16 bits
before calling `get_player_by_client_id`. The dispatcher also preserves the
formatter's integer result in `r3`; current callers discard it. A defensible
free interface is `s32 format_word_select_message(void *words, char *buffer,
s32 player)`, with a future shared record type. Signedness and the original
source's exact scalar typedef cannot be proved from these calls alone.

`0x80342788` (the existing `FPv` name) is a different function: it preserves
one window pointer in `r31`, checks input, and writes state 15 at +0xB4.
It is not a second signature or overload of the text formatter. Its bounded
interface takes one window pointer and returns no useful value. Whether that
pointer was implicit `this` or an explicit parameter is not recoverable from
these instructions alone. There is no reason to attach the compact formatting
record to the window class merely to retain the old `Fv` spelling.

Changing only the preview would leave every legacy reference to the old
symbol unresolved after a rename. The dispatcher definition, its downstream
formatter declarations/definitions, the player lookup boundary, and the
existing calls in `TWindowSubShortCutList`, `TWindowDD_803430BC`,
`TWindowDD_803471C0` and `TWindowDD_8034725C` need coordinated updates.
No such formatter changes are included in this commit.

## Natural-form probes

All probes used the unit's existing GC/2.6 settings. Symbol names were mapped
only in disposable comparison objects so objdiff compared the same addresses;
no binary patch or name alias is part of the build. Percentages below are
objdiff function similarity, not the number of exact functions.

| Probe | Result | Instruction difference |
|---|---|---|
| Explicit `u16 player` dispatcher and matching formatter declarations | Dispatcher 100% | No changes in dispatcher |
| Call that interface from existing `TWindowDD::open(s32, s32)` | `open` 96.47059% | Original `mr r5,r31` becomes `clrlwi r5,r31,16` |
| Give the opening helper a `u16` player parameter too | Opening helper 96.47059% | Its later call to `TWindowCtrl::open` gains `clrlwi r3,r31,16` instead of the original move |
| Full-width `s32` dispatcher but existing `u16` formatter declarations | Dispatcher 84.62963% | Four branches gain `clrlwi r5,r5,16`; branch displacements change |
| Full-width dispatcher and downstream declarations | Dispatcher and existing `open` 100% | No changes in either |
| Widen formatter definitions and player lookup declaration consistently, retaining explicit narrowing of computed player IDs | Japanese formatter 98.270775% | Same operations/length but changed saved-register allocation: initial zero goes from r27 to r31, record r28 to r26, buffer r29 to r27, player r26 to r28 |
| Full-width player lookup definition with its explicit `(u16)` conversion retained | Player lookup 100% | Same narrowing instruction inside the lookup |
| Use natural `u32` or `int` player types throughout that widened interface | Japanese formatter 98.270775% | Same allocation mismatch |
| Simplify Japanese zero initialization (`pos = 0`, empty output byte = 0) | Japanese formatter 98.09651% | Still differs |
| Const-correct the input records and input helper declarations in the full-width probe | Japanese 97.225204%, German 99.0676%, English 98.84393%, mode-0 97.402596% | Additional register-allocation differences |

The wider probes were not installed in the source tree. The unresolved
formatter is not presented as a mergeable fix. A further natural recovery or
Matt's explicit decision about a matching exception is needed; this change
does not add an exception or rely on one.

## Current-main integration and further probes (2026-11-10)

Merged fork main `00c484c57b38bc7f112016860e9faa628c7b49e9`. The
shortcut-list conflict keeps main's `PageIndicator::get_type()` call and
this PR's corrected text and symbol-preview interfaces. Regenerated the
porting inventory from the merged sources.

A further coordinated probe used a shared 12-byte word-select record and
free functions for the dispatcher, localized formatters and player-gender
lookup. The dispatcher, opening helper, German and English formatters,
Japanese formatter and gender lookup remained exact with full-width player
arguments. The French formatter at `0x80344980` scored 98.270775%: its
instruction count and operations remained the same, but saved registers
changed. (The earlier probe table called this the Japanese formatter;
mode 3 is French, as `Language.h` records.) The caller at `0x80347CC8`
scored 99.81132%, moving its incoming record through r6 instead of r5.

Natural count/index types, local scopes, independent zero initialization,
and explicit record/player/buffer locals did not restore both matches.
Scoped propagation, common-subexpression, scheduling, lifetime and dead-
assignment options also failed. These probes are not installed; no new
compiler exception or loss of exact functions is accepted by this change.
The remaining legacy formatter boundary still requires recovery or an
explicit maintainer decision before the PR is marked ready.

The retained integration passes `tools/check_pr.py` against a freshly built
baseline of the main commit above: +1 exact function, +1,044 matched code
bytes, +52 matched data bytes, +1 linked unit, no regressions. All six
shortcut-unit functions, 1,536 code bytes and 52 data bytes match. The DOL
is byte-identical to the original; retention and exception-inventory checks
also pass.
