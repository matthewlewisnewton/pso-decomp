# Native main-menu window lifetime and client contract

This follows PR #268 checkpoint
`6af0917225a86909a6520b5d973ed8fbb126a237`, including main `6e880491f`.

The recovered object is `TWindowMenuMainMenu`, the Base-derived menu window.
It is distinct from its TObject-derived `TWindowMainMenu` controller. The
window now has a genuine constructor and empty destructor with automatic
Base cleanup. Its existing render/task methods and embedded entry/slot layouts
are unchanged. No default constructor is added for the window or its bases.

The constructor accepts a position pointer and word-valued client, narrowing
only at the Base initializer. The original instruction sequence performs
that sign extension; the earlier short-valued native probe omitted it and
shortened the unit by four bytes. The controller's factory and both callers
now use one real static declaration with a word client, replacing the old
pointer-valued client declaration and local mangled prototype. The factory
uses ordinary `new`.

The remaining constructor register-home difference disappeared when its body
used the actual members directly instead of a decompiler pointer alias. No
register constraint, pragma, compiler option, or assembly is introduced.
Complete unrelocated text compares identically:

| Unit | Original and native bytes |
| --- | ---: |
| `TWindowMenuMainMenu` | 504 |
| `TWindowMainMenu_802AE928` | 80 |
| `TWindowMainMenu` | 1,468 |

The existing 20-byte descriptor has an extent pair, order, null layout-entry
pointer, and flags. It uses the observed `WindowLayoutDescriptor` schema.
The compiler naturally emits descriptor then its 24-byte table, at offset
`0x14` with eight-byte section alignment. The source claim is
`[804DE3C8,804DE3F4)`. The actual table `[804DE3DC,804DE3F4)` has four slots:
destructor, task, render, and inherited shadow rendering. The old 28-byte
catalog entry included a zero tail, not another virtual function.

The preceding four-byte `pad_07_804DE3C4_data` and trailing zero word
`[804DE3F4,804DE3F8)` remain outside the claim. The preceding padding leaves
report coverage and is reproduced by normal linker alignment; following
callback data is unchanged. No padding or alignment override is written.

The complete linked build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Checks against the published
checkpoint retain all 27,370 exact functions and 3,576 exact linked units,
with zero non-padding regressions. Matched and linked data increase by 44
bytes; retention is clean at 17,612 entries. The refreshed porting inventory
passes. The standing draft hold remains for the remaining lifetime interfaces.
