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

## Word-select formatting: resolved

At `0x8026E47C..0x8026E490`, the preview obtains the shared text buffer,
places it in `r4`, puts `shortcut + 4 bytes` in `r3`, extracts the local
player ID's low 16 bits into `r5`, and calls `0x8034861C`. The dispatcher
loads the global language/mode into `r0` and forwards its arguments:

| Mode | Address | Recovered free function |
|---|---|---|
| 0 (Japanese) | `0x803461CC` | `format_word_select_japanese` |
| 2 (German) | `0x80344F54` | `format_word_select_german` |
| 3 (French) | `0x80344980` | `format_word_select_french` |
| 4 (Spanish) | `0x80345608` | `format_word_select_spanish` |
| Other (English) | `0x80345C64` | `format_word_select_english` |

The language IDs agree with `include/pso/ui/Language.h`. The input is a
compact record: signed 16-bit count at +0, type at +2, and four word IDs at
+4. `WordSelectMessage.h` shares that 12-byte layout and the formatter
signatures. The destination is a character buffer. Japanese uses only the
first two arguments; the other modes also take the player ID. The dispatcher
returns the formatter's integer result, which current callers discard.
The Spanish formatter remains original-object code; its declaration and
symbol are renamed with the dispatcher reference.

The dispatcher and localized interfaces take a full-width `s32` player
argument because their original calls forward `r5` without narrowing it.
`show_word_select_message` at `0x803471C0` likewise forwards its player
argument to the formatter and then to `TWindowCtrl::open`. Its only source
caller supplies a record at packet +4 and a player ID loaded from packet +2.
This helper is now a free function with a typed record pointer instead of
`TWindowDD::open(s32, s32)`.

`word_select_player_gender` at `0x803472F8` explicitly extracts the low
16 bits before `get_player_by_client_id`, then returns 0 or 2 from the
player's male/female class flags (or 0 if no player exists). That is unrelated
to window state or battle flags. Signedness of the original player typedef
is not recoverable from these calls; `s32` preserves the observed forwarding.

All five dispatcher call sites, three localized recursive calls, formatter
definitions, display helper, and gender lookup now use shared declarations.
The old no-argument `TWindowDD::update_state` and hand-mangled formatter
stand-ins are removed. `0x80342788` (`update_state__9TWindowDDFPv`) is a
different function that checks a window's input and writes state 15 at +0xB4;
it is unchanged. The remaining downstream word/string helpers retain their
existing interfaces; this change recovers the formatter boundary rather than
claiming to reconstruct every word-select window method.

## Why the earlier full-width probes lost exact matches

A direct full-width migration initially scored 98.270775% for the French
formatter and 99.81132% for the caller at `0x80347CC8`, with unchanged
operations and instruction counts but different register choices. A `u16`
dispatcher instead adds narrowing instructions in `show_word_select_message`;
its unchanged incoming argument must remain full-width.

Traces of GC/2.6 with the unit's normal flags identify the first backend
change in the French formatter's computed-player call. The old narrow
callee argument emits:

    rlwinm r3, r99, 0, 16, 31

With a full-width callee and `(u16)(word_id - 0x68C)`, the initial backend
representation instead emits:

    rlwinm r100, r99, 0, 16, 31
    mr r3, r100

The allocator coalesces the move, but the extra virtual register changes its
interference graph and the saved-register ordering. Ordinary local-variable
and compiler-option probes did not solve that difference.

The source now expresses the required low-16-bit extraction as
`(word_id - 0x68C) & 0xFFFF`, producing the mask directly in the argument
register. The window preview and constructor calls similarly use
`local_client_id & 0xFFFF`. These expressions perform the same unsigned
16-bit extraction as the original caller instructions. The formatter's
incoming player is forwarded unchanged; it is not masked speculatively.
The shortcut preview retains its existing `u16` local and still matches.

With these boundaries, the French, German, English and Japanese formatters,
dispatcher, display helper, gender lookup and all previously exact callers
are exact again. No new pragma, intrinsic, function-pointer cast, assembly,
symbol alias or temporary matching regression is needed for this recovery.
