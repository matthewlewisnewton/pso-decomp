# Modem command data ownership

Initially based on fork main `f9b6cf76d9171b3dce5082b1484a85f4579855cd`;
refreshed against `8aaabc087559d217358101920f7cefae081ad884`, including
the merged ownership work and GC/2.0 default compiler.

`ModemRuntime.cpp` owns the 22-entry command filter table at `.data
0x804FDA78–0x804FDAD0` and its adjacent command strings/buffers at `.sdata
0x805D48B8–0x805D4940`. These extend existing ranges by 88 and 136 bytes.
The decoder explicitly iterates 22 pointers and compares each string with the
input command after its `AT` prefix. A census of all 5,061 current original
objects finds both table references in this unit, exactly 22 table relocations
with zero addends, and each filter string referenced only through that table.
The six accompanying AT strings also have only this unit's original consumers.

The 28 ordinary `char` arrays retain their original names and mutability.
`TAdSinglePlyChrSelectGC__sub_8042D49C` uppercases its argument in place;
the `AT&P0` and `AT&P2` buffers pass through it. No const-discarding interface
is introduced. Every explicit array bound equals the literal length including
its terminator and the original symbol extent. The old `AT` declaration's
four-byte bound is corrected to its actual three bytes; its only consumer
compares two bytes.

Exact bounds are visible before MWCC chooses small-data addressing. An initial
inferred-bound trial put the 22 filter strings and `AT` into `.data` and changed
one instruction. Complete literal-sized array types reproduce ordinary `.sdata`
emission without a pragma, compiler override, inflated bound or source padding.
Function bodies, pointer-table element types and compiler settings are unchanged.

## Validation

The native build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. PR, retention, actual source-link,
both port-exception inventories and strict original-address no-loss checks,
including padding, pass. Matched and source-linked data each gain 224 bytes;
function/code counts, linked units and coverage denominators are unchanged.
Retention adds the 29 newly defined names with no removals.

All 10,620 existing code bytes and 548 existing runtime relocation sites/targets
are unchanged. The complete object matches original allocated bytes and alignment,
with its one-byte small-data alignment tail and pre-existing four-byte BSS tail.
All 570 runtime relocations, including the 22 table entries, resolve to original
addresses. The comparison normalizes MWCC's immediate-halfword and DTK's
instruction offsets for SDA21 relocations. All 3,619 other compiled source
objects are byte-identical to the freshly built baseline.

## Deferred related work

The later modem-name pointer tables and string pool remain separate. That pool
contains a named four-byte empty-string extent, which a one-byte empty literal
does not establish. No oversized array or padding surrogate is added to claim it.
