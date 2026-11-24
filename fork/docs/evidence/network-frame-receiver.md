# Frame receiver at 80426448

This investigation starts from main
`08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`, after the independent #303
extractions were merged. It addresses the receiver of `post_send_message`,
not the held locked-allocator signature or temporary representation.

## Caller and callee evidence

The original GPOE8P DOL has SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Scanning its text for direct
branches to 80426448 finds exactly eight calls:

| Calling function | Call addresses | Frame argument |
|---|---|---|
| 80427378 | 80427460, 804274B8, 804274DC, 8042755C | slot + 0x23A |
| 804275B0 | 804276B0, 804277BC | slot + 0x23A |
| 80427F48 | 80428070 | incoming second argument, preserved in r31 |
| 80428094 | 8042818C | slot + 0x23A |

The seven slot calls load the unsigned length at +0x824. Existing source layout
assertions place the 0x5EA-byte frame at +0x23A and its length at +0x824 in the
0xE14-byte PPPoE record. The remaining caller builds the frame through its
existing `u8 *frame` argument. All eight source calls agree with these native
dataflows; their casts to `TLobby *` do not describe a class object.

At 80426448/0x8C, incoming r3 is saved in r29 and used only as the source of
`NetMemcpy`. There is no class-member access. The low 16 bits of incoming r4
feed allocation, copy length and the descriptor's +4 queued-length write.
Allocation failure returns -1. All other paths return zero, including descriptor
lookup failure and queue-send failure. These observations support a byte-frame
pointer and the existing `u16` length, without a claim about historical API
spelling, buffer capacity or ownership transfer.

The direct-call scan (including conditional branches) and aligned initialized-word
scan find no other static references. Scanning all 4,944 active original split
objects on both pinned main and the candidate finds the same eight zero-addend
`R_PPC_REL24` references, all in `TLobby_80426CAC.o`, and one definition of size
0x8C. These inventories do not exclude dynamically constructed calls, unaligned
encodings or external consumers.

## Bounded recovery

Replace the fictitious member with shared C declaration
`s16 post_send_message(u8 *frame, u16 arg1)` and pass the existing frame buffers
directly. The export spelling changes at the same native address and size.
Keep the original signed-word local conversion, allocator declaration and call,
temporary types, copy expression, descriptor operations, queue flags and returns.
No bounds check, rollback, release or failure repair is added.

The previous combined allocator migration changed the result temporary and
count/copy expressions, and changed native output. This receiver-only recovery
does not retry that migration. The locked allocator, queue adjacency, private
creator/reset and raw callback contracts remain unresolved. Existing behavior,
including bugs and PPC32 pointer-to-word boundaries, is preserved.

## Validation against pinned main

The independent unchanged-main build was authenticated at the exact base above:
clean tracked source, all active objects, 229 tool hashes, original inputs and
successful native-build/no-loss/link/retention receipts. The candidate used a
separate worktree and the shared serialized capacity gate with local tools.

- Both built DOLs reproduce the original SHA-1 above.
- Of 3,632 active compiled objects, 3,630 are raw byte-identical. The complete
  caller and callee objects agree after the single export-name mapping, including
  section/symbol ordering, code/data/debug payloads and raw relocation records.
  Only the name and consequent string offsets/file placement differ.
- Of 4,944 active original objects, 4,942 are raw-identical. The same two agree
  under that mapping and regenerated string-table ordering; string multiplicities,
  symbol order and all other payloads/relocations remain exact.
- Ordered linker providers remain 3,610 source objects and 1,334 original fallbacks.
  Address-based no-loss and source-link checks pass. Retention has 18,650 entries
  with zero drift. Matched functions/code/data remain 27,444 / 4,241,872 bytes /
  1,477,679 bytes: one rename, no coverage gain or loss.
- All 330 Python tool tests, portable behavior targets, ASan/UBSan targets,
  Python syntax, generated port-exception inventory and whitespace checks pass.

The whole caller and callee are validated, rather than just the recovered helper.
No split range, source-provider selection, compiler flag, pragma or held allocator
expression changes.
