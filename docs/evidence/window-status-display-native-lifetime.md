# Status display native lifetime and borrowed text table

This follows PR #268 checkpoint `1d267065d081613d7cfe521ebd485601b29f5aa5`,
with main `4bec40d6cca74a85e91c848ea2d9f25425a313ad` integrated.
It recovers the 0x74-byte TWindowSubStatusDisp lifetime and its two producers,
removing two raw Base calls and adding 40 matched and linked data bytes.
This is distinct from the SimpleStatus/Status/PartyStatus family.

## Constructor, cleanup and producers

The existing Base-derived declaration has halfwords at 0x60/0x62, a retained
word at 0x64, the PageIndicator storage word at 0x68 and scales at 0x6C/0x70.
The native constructor at 80281760 takes a word client, narrows at the Base
initializer and retains the original halfword client assignment. It uses the
same descriptor and layout-position lookup 0x19, writes the name, clears the
two counters, initializes the scales, constructs the existing 12-byte
PageIndicator with (0, 3, client), then dispatches page initialization.
Field 0x64 is not given a new initializer.

The native destructor at 802816F8 retains the existing PageIndicator release
protocol with flag 1. Automatic Base destruction and the compiler's deleting
protocol reproduce the original cleanup. The PageIndicator field remains a
word and its release helper remains type-erased; this change does not widen
their interface claims.

Original constructor reference inspection identifies two direct callers:
the status-category controller at 8027FCE4 and character-selection transition
constructor at 802C7250. Both allocate 0x74 bytes and forward a word client. They now use
ordinary new through the shared class declaration, preserving allocation
failure and subsequent stores. The latter's opaque StatusWindow pointer is
replaced by the actual TWindowSubStatusDisp pointer. Surrounding controller
lifetime and callback protocols remain qualified.

## Four borrowed pointers and native table

The formerly unclaimed 16 bytes at [804D2B20,804D2B30) contain four original
ADDR32 relocations to 805DD6F8/6FC/700/704. Those original string prefixes are
empty, B, A and S. The original consumer at 8027FD88 has two indexed table
loads, at unit text offsets 0x460..0x478 and 0x62C..0x644, feeding
set_text_entry_string. This supports a borrowed text-pointer array. Its
address-based name and raw external string payload declarations are retained;
no original semantic name or translation-unit identity is claimed.

The ordinary mutable pointer array naturally emits after the existing 4152
bytes of data, followed by the compiler's 24-byte four-function vtable at
[804D2B30,804D2B48). All eight relocations match the original offsets, types,
addends and resolved targets. The original table has destructor, task, render
and TObject shadow targets. No manual vtable, speculative slot, placement
control, padding object, new pragma or source-order search is used.

The complete old 72-byte original span is accounted for:

| Range | Bytes | Provider |
| --- | ---: | --- |
| 804D2B20..804D2B30 | 16 | Borrowed text-pointer array |
| 804D2B30..804D2B48 | 24 | Native compiler vtable |
| 804D2B48..804D2B68 | 32 | Unchanged original suffix |

The suffix includes the following data symbol and SubSymbolChat table. It
remains selected exactly once with identical bytes and resolved targets.
The string payloads retain their original providers. No bytes are classified
as padding and no coverage is discarded.

## Validation and remaining holds

The first coherent native probe preserves all 1660 owner text bytes, including
the 180-byte constructor and 104-byte destructor. The complete producer texts,
164 and 2332 bytes, remain original-exact. All resolved text relocation targets,
old 4152-byte data prefix and producer allocated sections remain unchanged.
The 4192-byte owner data matches the original prefix plus the natural 40-byte
suffix. All three recovered source objects are selected exactly once.

The incomplete consumer's compiled 3788 bytes and all prior targets remain
unchanged. Its full 5136-byte original object remains selected once, with
compiled source absent from the link. This table recovery does not recover
its missing functions or establish their source interfaces.

Independent read-only review confirmed source lifetime/ABI consistency and
all new data bytes/relocations. The capacity-gated full build preserves DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes
with +40 matched/linked data bytes and no code, function, total-data coverage
or linked-address regression. Comparison against separately built main also
passes. Retention is clean at 17,908 and the port inventory passes unchanged.

Raw Base/Addition calls fall from 18 across ten units to 16 across nine;
the three shared ABI bindings remain. Totals stay at 27,406 exact functions,
3,587 exact linked units and 3,641 source-bearing units. Combined PR deltas
versus main are +600 matched code, +1220 linked code, +1604 matched data and
+1560 linked data bytes. Existing qualified alignment tails are unchanged.

The incomplete consumer, remaining lifetime/ownership/callback/constant and
initialization holds, DD/Word/nameplate original providers and protected
remainders remain. The PR stays draft; no split or history rewrite is made.

The subsequent [bounded blocker audit](window-status-page-com-card-blocker-audit.md)
records one reconstruction of the missing 1348-byte consumer page. Its 1344-byte
result preserves prior functions and call order but is not activated. The full
original consumer and the unchecked rank-index qualification remain intact.
