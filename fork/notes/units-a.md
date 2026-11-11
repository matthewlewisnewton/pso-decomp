# units-a notes

## pso/unk/TLobby_803BFE50.cpp
- Fork comment on publish_decode (now drain in 803C0238): the local declaration order
  (written, used, unused, then source/decoder) gives CodeWarrior the original saved
  registers and chunk slots.
- 803C0238 matched by taking the fork's prepare/publish/advance inlines (counter field
  mapping: fork decoded_samples/decoded_bytes/decode_position = upstream
  output_samples/consumed_bytes/decoded_samples). `int minimum`/`room` locals in the feed step and
  the `decoded_samples < remaining ? ... : ...` ternary in the skip step matter.
