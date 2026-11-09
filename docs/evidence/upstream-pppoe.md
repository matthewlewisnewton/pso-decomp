# Link the PPPoE discovery unit

Base: fork `18207f98696bab4911ca2cecac1c19381e2ea506`, after the network
runtime recovery in [#369](https://github.com/matthewlewisnewton/pso-decomp/pull/369).
Reference: upstream [#213](https://github.com/zeroz41/pso-decomp/pull/213),
`76d99c974ba4897eca428c505be1af4d4f6ec124`, and its typed follow-up
[#215](https://github.com/zeroz41/pso-decomp/pull/215),
`9eb8da7276b625b67c1854e7ea3372b0d944f456`,
`src/pso/network/TLobby_80426CAC.c`.

The fork's existing `pso/misc/TLobby_80426CAC.cpp` had 19 of 20 functions
exact. Recovering `TLobby__sub_804275B0` at `0x804275B0` adds the missing
588-byte discovery receive handler. It handles PADO (`7`), PADS (`0x65`) and
PADT (`0xA7`), updating the existing session state, saving the offer frame,
processing tags, sending the next discovery frame and restarting the retry timer.
The fork's function names, C++ interfaces and split boundaries are retained.

## Interfaces and layout

The original uses signed halfword results. Make the existing declarations and
definitions agree for `TLobby::post_send_message`, `TLobby__sub_8042787C`
and `TLobby__sub_80427F48`. The first returns only 0/-1, the second 1/-1,
and the third returns -1 or the first helper's result. The existing caller in
`NetworkTransport.cpp` already declares the third helper as `s16`.
All affected pre-existing functions remain exact, including the complete
`NetworkMessageTransport.cpp` object. No incompatible local redeclaration is used.

Extend the existing session view with `rx_frame` and `rx_frame_len` instead of
importing upstream's raw field casts. Compile-time assertions establish the
`0xE14` session stride, transmit buffer at `0x23A`, transmit length at `0x824`,
receive buffer at `0x826`, and receive length at `0xE10`. The session lookup now
returns this same view; its duplicate partial struct and caller cast are removed.
The handler names its header's length field `payload_len` rather than upstream's
`id`, and uses the named receive buffer, length, peer-address and retry fields.

Two pairs of already-exact functions were in the wrong source order:
`parse_tlv_records` / `TLobby__sub_8042787C` and
`TLobby__sub_80427B6C` / `TLobby__sub_80427C6C`. Restoring their original
address order makes the entire object linkable. Individual function matches alone
did not establish that; the scanner correctly rejected the first attempt for order.

## Outstanding inherited constraints

These are also recorded in section 4 of the [exception register](../porting-exceptions.md).

- The recovered handler retains upstream's unused `s32 pad[2]` and `u8 spare[2]`.
  With the pinned GC/1.2.5n compiler, removing both scores 99.89796%, removing
  only `pad` scores 99.96599%, and removing only `spare` scores 99.93198%.
  These probes use the corrected interfaces and typed fields; the retained version
  scores 100%. The differences are stack frame/slot offsets, not missing logic.
  A port should delete these optimizer-only locals.
- Linking activates the unit's 12 existing non-push/pop pragma lines:
  `dont_inline` x4, `inline_depth` x3, `opt_propagation` x2,
  `opt_common_subs` x2 and `auto_inline` x1. Some occur in empty scopes or around
  a typedef. Their presence is inventoried, not a claim that every line is needed.
  A port should remove compiler-only steering and unused temporaries.
- Existing debt includes an opaque `lobby_pppoe_slot_table` viewed through
  multiple structs, accesses beyond the one session to the trailing address
  storage, 32-bit integer/pointer conversions, raw tag reads and host-endian
  halfword copies, a pointer/timestamp host-unique token, redundant comma/mask
  expressions, and provisional `TLobby` member wrappers called on frame buffers.
  This patch does not establish real class ownership. A port should use one typed
  session/table definition, explicit buffer parameters and byte-order helpers,
  pointer-sized types and a suitable opaque host-unique token. Validate frame/tag
  lengths against their buffers before parsing or copying; the native handler
  preserves the original's unchecked behavior.

No new pragma, per-unit compiler override, hardware access, assembly or intrinsic
is introduced. The generated exception inventory remains 5,772 pragmas in 876
files and 176 compiler overrides. Section 7's upstream catch-up scope remains
unchanged at 521 entries; this is a bounded port, not a blanket import of #213.

## Validation and gain

Built current main with the pinned tools and original inputs, saved its baseline,
and verified retention before editing. Full build, original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, address-aware no-loss comparison,
linked-unit and generated retention checks pass.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,385 | 27,386 | 1 |
| Exact code bytes | 4,189,044 | 4,189,632 | 588 |
| Exact data bytes | 1,470,159 | 1,470,159 | 0 |
| Linked code bytes | 3,667,732 | 3,673,564 | 5,832 |
| Linked data bytes | 1,175,627 | 1,179,243 | 3,616 |
| Linked units | 3,585 | 3,586 | 1 |

All 20 functions and the complete BSS section match. The BSS is zero-initialized
program state, not extracted assets. The scanner adds this one unit and 14
retention entries, removing none. Total code, data, function and unit counts do
not change. No prior exact or linked range or alignment padding is lost.
