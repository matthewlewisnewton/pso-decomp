# Socket protocol runtime

The comparison uses GPOE8P and fork main `83aec32b62`. The standard build compiles and links `pso/network/SocketProtocolRuntime.cpp`; it does not use the original socket object as a fallback. All 21 functions, all 10,388 text bytes, all 184 initialized data bytes and all 16 BSS bytes match the original object. The linked `PsoV3.dol` has the retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Against that main baseline, `tools/check_pr.py` reports 27,526 → 27,528 exact functions and 4,322,652 → 4,325,684 matched code bytes, with no regressions. Linking the unit adds 10,388 complete code bytes, 200 complete data bytes and one linked unit. All 3,631 linked units pass, and the retention list has zero additions or removals on the retention check.

## Retail SACK compaction bounds bug

The control block declares five SACK ranges at offsets `0x2F8..0x31F`. When a new range contains an existing range, retail `0x8041FED4` shifts the successors down one slot with `k < 5`. The last iteration reads `sack[5]`, one eight-byte range beyond the array:

- `0x320..0x323` contains `seg_top` and its two padding bytes;
- `0x324..0x327` contains `una`.

The loop copies those words into `sack[4]` and then clears `sack[4]`. It does not write either adjacent field. This is retail behavior, not a sixth active SACK range. The matching C++ deliberately retains the out-of-bounds read. A PowerPC read trace observes both adjacent words in the game and in the release and debug browsers on the disc.

Build selection is explicit in `TLobby__sub_8041FED4`:

- the normal CodeWarrior build (`__MWERKS__`) uses the retail `k < 5` loop;
- non-CodeWarrior port builds use `k < last`, which stops at source slot four and never reads beyond the array;
- defining `PSO_SOCKET_BOUNDED_SACK` selects the bounded loop for a diagnostic CodeWarrior build.

The retail and bounded forms produce the same final control block in the tested cases, but their adjacent-field read traces intentionally differ. `tools/probes/test_socket_runtime.py` expects retail reads by default and bounded behavior with `--bounded-sack`.

The receive-range routines at `0x8041F66C` and `0x8041F914` use unsigned endpoint subtraction before signed sequence comparisons. This preserves ordering across signed and unsigned sequence-number wrap. Their shared inline scope and range copies remain exact.

## Send acknowledgement

The send ring holds 65 16-byte `TcpSendRequest` records. A completion callback can reenter the socket and move the queue head, so `0x8041FFF8` reloads the head and ring descriptor after the callback and before reading the next request.

The scoped `opt_lifetimes off` setting, direct queue statements and native local declaration order reproduce the 1,048-byte routine exactly. The unreferenced eight-byte local area preserves the retail 96-byte frame and the FIFO destination descriptor at stack offset 20. Ports can remove that area and the optimizer settings while retaining the post-callback reload.

## Send gathering

`0x80420410` matches at 1,984 bytes. Its scoped `dont_inline on` and `opt_propagation off` settings, local declaration order and statement order reproduce the native register allocation. The integer address cursors preserve the original reverse and shift walks, including an unused final decrement before the array; conversions back to pointers occur only for guarded accesses. Ports should use bounded typed indices instead.

The partial-fragment tail at `0x80420B6C` is unreachable in retail. The FIFO path initializes the partial index to `-1`, and every path reaching the tail retains that value. The tail is nevertheless required for the original bytes and remains in the C++. Its 16-bit length temporaries reproduce the native stores without the former `s64` widening.

## Validation and reproduction

Run the normal build and repository gate:

```sh
python3 configure.py
ninja
python3 tools/check_pr.py
```

The socket unit is present in `config/GPOE8P/psov3/linked_units.txt`. `tools/link_units.py check` verifies that the linker uses the compiled unit, and `tools/link_units.py force-active --check` verifies its generated retention entries.

With Unicorn 2.1.4 available, compare behavior against the original DOL:

```sh
python3 tools/probes/test_socket_runtime.py \
    orig/GPOE8P/files/PsoV3.dol build/GPOE8P/psov3.dol
```

The retail probe checks the adjacent SACK reads, 21 SACK boundary cases, 786 reassembly comparisons, 12 out-of-order receive scenarios, 2,528 gathers and 1,600 ACKs with 1,766 completion events. ACK cases include callback reentry and queue-head movement.

For the bounded diagnostic, temporarily add `-DPSO_SOCKET_BOUNDED_SACK` to this unit's compiler flags, regenerate and link the DOL, then pass `--bounded-sack` to the same probe. Restore the normal flags and rebuild afterward. Both retail and bounded probes pass the same state and behavioral comparisons; only the expected SACK read trace differs. Pass `--browser-dir` with `iwanaga.dol` and `iwanagaD.dol` to reproduce the independent browser SACK traces.
