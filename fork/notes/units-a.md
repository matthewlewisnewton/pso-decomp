# units-a notes

## pso/unk/TLobby_803BFE50.cpp
- Fork comment on publish_decode (now drain in 803C0238): the local declaration order
  (written, used, unused, then source/decoder) gives CodeWarrior the original saved
  registers and chunk slots.
- 803C0238 matched by taking the fork's prepare/publish/advance inlines (counter field
  mapping: fork decoded_samples/decoded_bytes/decode_position = upstream
  output_samples/consumed_bytes/decoded_samples). `int minimum`/`room` locals in the feed step and
  the `decoded_samples < remaining ? ... : ...` ternary in the skip step matter.

## pso/unk/TLobby_803C1A58.cpp
- 803C2388 (AIFF header walk): needs `#pragma opt_propagation off` and
  `#pragma opt_common_subs off`, `s32 form_size` and a local `chunk_bytes`-free form
  (`end = p + (form_size - 4)`), plus READ_LE32/SWAP32 with the high byte shifted as unsigned
  (`(int)((u32)(b)[3] << 24)`, `(u32)(x) << 8`) keeping the native int result.
- 803C3570: needs `opt_common_subs off`, `opt_lifetimes off`, `opt_propagation off`; the
  fork's local declaration order and its `AdxBlockTransferView` layout view (replaces
  Strm_803C1A8C for this function only; Strm_803C1A8C still serves 803C2A00 and others).
  Fork comment: "Keep the high-byte shift unsigned while retaining the native int result."
