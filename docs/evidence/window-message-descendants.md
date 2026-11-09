# Message descendant construction and the Log boundary

This follows PR #268 checkpoint
`9ef96cd1673fd908185cd272b8fe0e3a4af90328` on main
`9924ce113b5e6dff309a5ae94065265d3066fb24`.

Page, Quest, and Scroll now have genuine constructors and ordinary `new`
factories. Page initializes `Message(layout, (u32)capacity, client)` with the
same word carriers as its existing factory. Quest initializes
`Message(layout, 1, local_client_id)`, and Scroll initializes Quest directly.
No default constructor is introduced. Their existing native destructors and
compiler-owned table claims are retained.

The descendant-owned storage remains distinct: Page's word at `0x90` is its
message flags, Quest's word at `0x90` is its dispatch mode, Log's word at
`0x90` is an opaque scrollbar allocation handle, and Scroll adds a float speed
at `0x94` and completion pointer at `0x98`. Log's own `0x94` float is an
animation offset. None of this storage moves into Message. Existing size and
new first-owned-field offset assertions preserve these layouts.

Log's destructor is now native: it destroys its scrollbar allocation, clears
the controller registration, and automatically destroys Message. Its 24-byte
compiler-generated table is claimed to the destructor's owning
`TWindowMessageLog_8026AA38` unit at `[804D0760,804D0778)`. The controller
registration setter keeps its existing ordinary C identity; its declaration,
definition, and sole caller now consistently pass a `TWindowMessageLog *`.
The getter and clear helper remain unchanged.

Complete unrelocated text reproduces the original bytes:

| Source unit | Bytes |
| --- | ---: |
| `TWindowMessagePage` | 736 |
| `text_8026B260` (Quest constructor) | 84 |
| `TWindowMessageScroll` | 320 |
| `TLobby_8026B06C` (Quest factory) | 172 |
| `TLobby_8035D540` (Scroll factory) | 116 |
| `TWindowMessageLog_8026AA38` | 536 |
| `TWindowCtrl_8026AD44` | 72 |

## Historical Log limitation (resolved in the follow-up)

At this checkpoint, Log's initializer and factory remained their matching legacy functions. A real
Log constructor with `Message(layout, 30, client)` has the same 168-byte size
but differs in four instructions around the compiler's vptr installation:
the original prepares the call receiver before the store and uses a different
scratch register for the table address. Typed class-name/handle stores and a
consistent pointer-valued controller setter do not resolve that difference.
A genuine member interpretation of the registration helper also failed and
was discarded; no speculative member ownership or renamed helper is retained.
An isolated probe moving the native constructor outside the surrounding C
linkage block preserves the same mismatch; the validated source is unchanged.
A constructor-only unit also emits 168 bytes with the same mismatch, without
emitting a table. No speculative source split is activated by that probe.

This is a measurement of those source variants, not a proof that native Log
construction cannot match. No assembly, new pragma, compiler override, manual
table, alternate-width alias, or matching regression is accepted to bypass it.
Log remains the sole source-unit caller of the Message constructor binding in
`WindowConstructorAbi.h`, reduced from three. The interface still has five
constructor and three destructor declarations because Log needs that entry.
Its auxiliary 12-byte allocation helper and existing floating-register views
remain legacy interfaces; this change does not claim their ownership is unified.

The full build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Against checkpoint `9ef96cd16`,
all 27,369 exact functions and 3,575 exact linked units remain, with zero code,
data, function, or address-coverage regressions. Matched and linked data gain
24 bytes. Retention is clean at 17,587 entries. Against fresh main, the PR has
one additional exact function, 600 matched code bytes, 728 linked code bytes,
and 172 matched/linked data bytes. The standing draft hold remains.

## Native Log follow-up

The [Log and auxiliary-storage recovery](window-log-scroll-lifetime.md),
following checkpoint `034308446b77aba2c1df8808860a1ed81d64b4df`, resolves
the measured four-instruction difference. Direct access to actual members
removes the decompiler pointer alias; no compiler setting changes. Log now
initializes Message directly and its factory uses ordinary `new`. Its
auxiliary scrollbar construction also uses ordinary `new`. The sole Message
constructor binding leaves the ABI header, which now contains four constructor
and three destructor declarations. The broader raw-storage lifetime hold
remains. The earlier failed probes above describe history, not a current
constructor blocker.
