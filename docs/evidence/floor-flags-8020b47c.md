# Floor flag import at 0x8020B47C

The 0x10C-byte routine receives the buffer beginning at offset 8 of the
6x6E sync packet. Its first helper swaps four 32-bit words in place. It then
uses the offsets at 0 and 8 to read consecutive signed 16-bit flags, swaps
each on the stack, and writes them at offset 2 in the saved object and enemy
rows for 18 floors.

## Interfaces and layout

The receiver is a buffer, not a `TLobby` object. The packet caller passes its
payload in r3 and a 16-bit length in r4; the wrapper does not use the length
or produce a consumed return value. The helper and wrapper retain their
existing linker names through C-linkage free functions. Removing their
incorrect `TLobby` member declarations does not change their machine code.

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

Baseline: fork main `f3441bb8ac8ded6b73c02bd13622105638abacfe`.
The stock-compiler object scores 100% for the complete 268-byte text section,
and the strict unit scan accepts its section layout, alignment and symbols.

A fresh build of the baseline passes the original DOL hash and retention
checks. Against its `ninja baseline` report, the final
`tools/check_pr.py --no-build --baseline /tmp/pso-floor-baseline-current/build/GPOE8P/baseline.json`
passes with no function, code or data regressions. Linked units increase from
3,555 to 3,556 and linked code increases by 268 bytes. Matched function/code/data
counts stay unchanged because the rebased main already contains the exact routine.

The packet caller, wrapper, four-word swap helper and table-owner objects are
byte-identical to the baseline. A final `ninja -d keeprsp` relink retains
`build/GPOE8P/psov3.elf.rsp`, which names
`build/GPOE8P/src/pso/unk/text_8020B47C.o` rather than its original split object.
The complete 5,233,088-byte DOL compares byte-for-byte with
`orig/GPOE8P/files/PsoV3.dol`; SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
