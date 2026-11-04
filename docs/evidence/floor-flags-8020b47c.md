# Floor flag import at 0x8020B47C

The 0x10C-byte routine receives the buffer beginning at offset 8 of the
6x6E sync packet. Its first helper swaps four 32-bit words in place. It then
uses the offsets at 0 and 8 to read consecutive signed 16-bit flags, swaps
each on the stack, and writes them at offset 2 in the saved object and enemy
rows for 18 floors.

## Interfaces and layout

The receiver is a buffer, not a `TLobby` object. The packet caller passes its
payload in r3 and a 16-bit length in r4; the wrapper does not use the length
or produce a consumed return value. The helper and wrapper are ordinary C++
free functions under address placeholders (`fn_8020B588` and `fn_8020BF68`);
their former `TLobby` member manglings are gone from source, the shared header
and `symbols.txt`. Only the symbol names changed: both functions keep their
exact machine code (0x44 and 0x20 bytes). The entry point remains the
unmangled `TLobby__sub_8020B47C` address placeholder it has on main.

`FloorFlagsBuffer` describes the four header words without inventing meanings
for the unused words at offsets 4 and 12. The enclosing buffer's ownership and
bounds remain unresolved. The two flag streams are read through const pointers;
only stack copies of their flags are swapped.

The shared saved-row and floor-table declarations are extracted unchanged
from `text_8020E08C.cpp`, which defines the table at 0x80513AD0. Each saved row
is 8 bytes, with flags at offset 2. Each 24-byte floor entry has object and
enemy counts at offsets 0 and 4 and row pointers at offsets 16 and 20.

## Matching constraint

Both loops test the table count before entering the positive-count branch.
Inside that branch, the row pointer is declared before the count snapshot.
The count remains fixed for the inner loop. There is no intervening call or
write between the guard and snapshot, so this preserves the original import
behavior.

Hoisting the count snapshot ahead of the guard gave a 99.62687% candidate:
five instructions swapped r29 and r30 in the second loop. The guard-first
form reproduces all 67 instructions with the stock GC/2.6 compiler and the
repository's existing flags. No compiler overrides or assembly are needed.

## Validation

Fork main acquired a separate exact implementation during this recovery, but
still linked the original object. This change preserves that match with shared
types and a simpler implementation, then selects the unit for source linkage.

Baseline: fork main `d952dc80e8614b6763f02cbe7b03f8c3a2014546`.
The stock-compiler object scores 100% for the complete 268-byte text section,
and the strict unit scan accepts its section layout, alignment and symbols.

A fresh build of that baseline passes the original DOL hash and retention
checks. Against its `ninja baseline` report, `ninja -j8 && python3
tools/check_pr.py --no-build` passes with no function, code or data
regressions. Linked units increase from 3,554 to 3,555 and complete code
increases from 3,445,516 to 3,445,784 bytes (+268). Two functions are renamed
to address placeholders. Matched functions, code and data stay at 27,297 /
4,142,212 / 1,441,403 because current main already contains the exact routine.
`link_units.py check` reports all 3,555 linked units exact, so the linked
input for this unit is `src/pso/unk/text_8020B47C.cpp`.

The packet caller, wrapper, four-word swap helper and table-owner objects stay
100%. The complete 5,233,088-byte DOL compares byte-for-byte with
`orig/GPOE8P/files/PsoV3.dol`; SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
