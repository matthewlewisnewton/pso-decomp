# Network-info request frame and switch

`request_network_info_load` at `0x803F3DD4` accepts a card channel and a
caller-owned buffer. Mode 0 returns -1, mode 1 starts a load if no request is
active, and other modes return -5. A busy request returns -4. On success it
sets the card channel, records request kind 2, phase 3, the buffer and result
200. Its caller passes the channel in `r3` and the buffer in `r4`.

The original has a dynamically 32-byte-aligned 64-byte frame, but its body
does not access stack locals. With the configured GC/2.6 compiler and middleware
flags, a plain scalar parameter produces an ordinary 32-byte frame. An unused
aligned local is eliminated; an addressed aligned local adds stack accesses
absent from the original. An alignment attribute on the first parameter instead
produces the original frame and leaves the two arguments in their original
registers. This is a matching device, not evidence about the original source
or a semantic alignment requirement on the channel. It is guarded for MWCC;
the public declaration and port fallback use an ordinary `s32`.

With scheduling disabled, the remaining switch differs by one instruction:
peephole optimization replaces the original compare-against-4 and unconditional
branch with an extra unconditional branch. Disabling peephole optimization for
this function reproduces the original sequence. Both pragmas are scoped to the
function. With them and the frame attribute, both functions in the unit and
their relocations match; the existing result-taking function remains unchanged.
The caller's original and compiled object also remain exact after sharing the
declaration.
