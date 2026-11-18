# TCP send queues and SACK compaction

The comparison uses GPOE8P and fork main `4959835fff`, which includes the exact receive delivery from [#606](https://github.com/matthewlewisnewton/pso-decomp/pull/606). Of the unit's 21 functions, 18 match exactly. All 184 initialized data bytes and all 16 BSS bytes match. Each function retains its original size and address in a diagnostic link of the complete C++ unit.

| Routine | Native size | Differing instruction words in the linked game |
| --- | ---: | ---: |
| SACK compaction, `0x8041FED4` | 292 | 1 |
| Send acknowledgement, `0x8041FFF8` | 1,048 | 6 |
| Send gathering, `0x80420410` | 1,984 | 43 |

Across the complete DOL, only these 50 words change. The diagnostic game has SHA-1 `ce9186a07392d2841bc927e715f65e7e769fbaa3`. Its code and data include the shared callback provider and the callers of ACK and send gathering.

## SACK and receive reassembly

The control block holds five SACK ranges at offsets `0x2F8..0x31F`. When inserting a new range that contains an existing range, the game copies that existing range's successors down one slot. Its loop goes one copy beyond the table, reads the words at `0x320` and `0x324`, and clears the destination. Those words hold the scoreboard's top index with its alignment bytes, and its unacknowledged sequence number. The bounded loop copies through source slot four and clears slot four. Compaction and expiration derive their limits from the array declaration. The compaction bound changes the compare immediate at `0x8041FFBC` from five to four.

A PowerPC read trace observes both adjacent words in the game, the release browser and the debug browser shipped on the same disc. The bounded game produces the same final control block with zero reads from those words. A byte-identical routine given that same state would perform the original reads. Main currently counts the original five-iteration bound as an exact match.

The receive-range routines at `0x8041F66C` and `0x8041F914` use the same unsigned endpoint subtraction to count the bytes removed from the reassembly queue. This calculation works across both signed and unsigned sequence-number wrap. Eliminating the former routine's unused eight-byte array leaves all 680 bytes of that routine and all 1,164 bytes of the latter routine exact. Insertion at
`0x8041FDA0` and overlap handling at `0x8041F914` now subtract in the
unsigned sequence space before interpreting a difference as signed.
This removes signed overflow from receive-range insertion and merging
while preserving the compiled socket object.

## Send acknowledgement

The send ring holds 65 records. Each 16-byte record contains a buffer reference, a signed halfword length, a signed halfword offset and a completion callback. A callback can reenter and move the queue head. The routine takes its next index after the callback and before copying the ring descriptor. The debug browser also takes the index in this order. The last six differing instructions all address the same FIFO destination descriptor at stack offset 36. Retail places it at 20. The frame size, call targets and other instructions match.

The debug build initializes an additional descriptor kind byte at `0x8016B0E8`. It never subsequently addresses that slot. This gives evidence for a fourth initialization in that build, but does not establish a purpose for a fourth C++ object. Passing the live request and packet by reference, changing the completion snapshot's lifetime, sharing buffer cursors, and grouping the actual queue operations into inline helpers did not recover the retail FIFO stack slot.

## Send gathering

The gatherer works with the packet's 12 fragment descriptors directly. It reverses the consumed prefix using an index relative to its end. The partial-fragment branch uses the selected fragment's buffer and length, as in the debug browser at `0x8016B03C..0x8016B044`. Both four-byte descriptor copies explicitly copy the value word. Indexing and byte counts stay at their native widths. Gathering uses the translation unit's ordinary compiler options.

All 43 differing words lie between `0x8042098C` and `0x80420A4C`, in the forward scan of the fragment prefix and the reverse copy. The instructions for the subsequent partial-fragment tail match. A direct backward cursor under scoped propagation settings produced a candidate four bytes longer than retail. Comparing pointer walks, counted loops, end-relative indexing and increment order yielded the equal-size build above. A subsequent trial of 144 loops using source and destination bounds gave a best equal-size result of 44 differing words. The public upstream C recovery and the compiler's loop and stack implementations informed the trials. [Upstream recovery](https://github.com/zeroz41/pso-decomp/pull/305) · [MWCC loop strength reduction](https://github.com/rayanht/mwcc/blob/main/src/optimizer/StrengthReduction.c) · [MWCC EABI frame allocation](https://github.com/rayanht/mwcc/blob/main/src/backend/StackFrameEABI.c)

The partial-fragment tail at `0x80420B6C` is unreachable in the retail GPOE8P routine. The retail FIFO path initializes the callee-saved register `r29` to `-1` at `0x804206F0`. Its direct branch at `0x80420804` enters the queued-prefix scan, which preserves `r29`. The later branch into the tail at `0x80420A60` requires `r29 >= 0`. The other path, which finds a partial first fragment, returns before the scan. In the C++ candidate, the same paths leave `partial_fragment == -1` whenever the final tail test runs. The emitted debug-browser instructions identify the descriptor that this tail would use.

A scratch build removed that tail, started the queued-prefix scan at index zero and reversed the prefix through slot zero. It passed all 2,528 gather comparisons against the diagnostic C++ build. An instruction hook recorded zero entries to the tail in those runs. The scratch routine shrank from 1,984 to 1,888 bytes, shifting later symbols in the full link.

## Matching build and port behavior

The matching GameCube build must preserve the original executable bytes,
including the SACK loop. The socket unit stays out of the source-link list,
so that build links the original object split from the user's disc. The
bounded C++ routine is for source builds. It shifts entries within the five-slot
SACK table and clears the final slot.

The diagnostic build below links the full C++ unit for behavioral testing.
The match report compares that compiled source with the original object.

## Reproducing the comparisons

The standard build keeps main's link set. It reproduces the retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,630 source-linked units pass and the retention list has zero additions or removals. Against the stated baseline, `tools/check_pr.py` reports 27,526 → 27,525 exact functions and 4,322,652 → 4,322,360 matched code bytes. The 292-byte SACK routine is the only exact-function regression. Matched data and linked code and data are unchanged.

For the diagnostic build, use a separate checkout with the normal project tools, original input files and a completed standard build. Add `pso/network/SocketProtocolRuntime.cpp` to the sorted list in `config/GPOE8P/psov3/linked_units.txt`. Then run the following with the same configure options as the standard build and Unicorn 2.1.4 available to Python.

```sh
python3 tools/link_units.py force-active --write
python3 configure.py
ninja build/GPOE8P/psov3.dol
python3 tools/probes/test_socket_runtime.py orig/GPOE8P/files/PsoV3.dol build/GPOE8P/psov3.dol
```

Pass `--browser-dir` with a directory containing the disc's `iwanaga.dol` and `iwanagaD.dol` to reproduce the independent SACK traces. The probe verifies the SHA-1 of each reference executable. It checks the SACK state and adjacent-field accesses in the original trace, and exercises 21 more SACK cases on the bounded routines, including every possible compaction position in a full table. It also checks 786 reassembly cases, 12 out-of-order receive scenarios with overlapping data, 2,528 gathers, and 1,600 ACKs with 1,766 completion events. Cases include both sequence wraps, all 32 reassembly slots, all 12 packet fragments, queue wrap and partial consumption. The ACK checks intercept completions, record their arguments and exercise queue-head changes during a callback.
