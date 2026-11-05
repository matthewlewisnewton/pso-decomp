# DHCP step frames: dead homes for named locals

Units: `pso/unk/text_80421620.cpp` (`TLobby__sub_80423C04` release,
`TLobby__sub_80423E80` request, `TLobby__sub_8042422C` discover), GC/1.2.5n
`-O4,p -inline off`.

The original frames are larger than the address-taken objects need: 12 bytes
below `src` in release and request, 16 in discover, and 4 more between the send
buffer and the next object in request and discover. No instruction reads or
writes those bytes.

## What MWCC does

Measured in scratch functions with the unit's compiler and flags:

- Address-taken locals are placed bottom-up in reverse declaration order.
  Locals in nested blocks go below the function-scope ones. The frame is
  `align8(end of locals) + align8(saved GPRs)`.
- A local with one definition that MWCC forwards into its use keeps a 4-byte
  home at its declaration position, and nothing touches it. This happens when
  the use is a store or a compare: `v = g; d[1] = v;`, `v = 5;`, a `?:` result,
  `elapsed = now - t; if (elapsed >= k)`.
- No home is left for call results (`rc = f(); if (rc < 0)`), for locals with
  two definitions (if/else, `len = f(); len = clamp(len)`), for values live
  across a call or branch, or for values only passed as call arguments.
- `-inline off` does not inline anything here, so helper parameters are not
  the source.

So the dead words are the homes of named single-assignment values in the
original source. Unused arrays reproduce the size but not the reason.

## Locals that reproduce the frames

| Function | Below `src` | Between buffer and next object |
|---|---|---|
| release | `elapsed` (300 ms resend gap), `server` (broadcast), `size` (padded length) | none |
| request | `elapsed` (3 s retry), `wait` x2 (RFC 2131 4.4.5: half the time left to T2 / lease end) | `size` |
| discover | `elapsed` (3 s retry), `server` (broadcast), `client` (0.0.0.0), `any` (socket peer 0.0.0.0) | `size` |

Each function is byte-identical with these (frames -112, -88, -184). Rejected
forms: `server` as a ternary in request swaps r5/r6; reading `dhcp_socket`
after the clamp changes the send sequence; a `retries` local in discover
matches but needs the global re-read the original does, so the peer address
was used instead.
