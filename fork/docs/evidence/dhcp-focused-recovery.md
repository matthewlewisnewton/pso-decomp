# Focused DHCP client recovery

Base: `224eb99838471c243b20c305eddac75e7ff76c8f` (fork main after #370).
Reference: the DHCP work in fork [#303](https://github.com/matthewlewisnewton/pso-decomp/pull/303),
head `46ee82d720db5f04c33b13ea4e767b285abaf22b`. This extracts only the three
missing bodies from that broader draft, preserving current main's symbols and
interfaces. It does not merge or replace the rest of #303.

Recover `TLobby__sub_80423298` (424 bytes, lease timer),
`TLobby__sub_80423E80` (940 bytes, request/renew/rebind step), and
`TLobby__sub_8042422C` (816 bytes, discovery/retry step). The existing unit at
`0x80421620..0x804245DC` now has all 42 functions exact. Move the already-exact
`set_thread_state_and_resume__6TLobbyFv` after `tcp_send` to reproduce its
original object order; function percentages alone did not prove linkability.

## Interfaces and inherited constraints

The common `NetworkReceiveCallback` signature takes an event and byte record.
The UDP opening helper, DHCP callback and existing `TUdpSocket` caller now use
that same signature through one shared header. The DHCP callback decodes the
byte record using its existing `Arg_804249F0` view (length at +2, output pointer
at +4). No callback is cast to an incompatible function type. Both complete
caller units, `NetworkPacketRuntime` and `TTcpSocket`, remain byte-identical.
The server ID at `0x805D7B24` is consistently a word in this unit; the existing
packet builders pass its address to `NetMemcpy`.

The imported request/discovery steps use #303's named `elapsed`, `wait`,
`server`, `client`, `any`, and `size` temporaries. They reproduce native stack
homes without unused padding arrays. This establishes matching behavior under
the pinned GC/1.2.5n compiler, not proof of the original source's variable names.
The already-exact release function's existing padding is outside this recovery.

Remaining native debt is explicit: provisional `TLobby` methods operate on raw
DHCP buffers; the reply buffer starts at +0x5DC and its cookie/options at
+0xEC; the UDP descriptor and callback storage carry 32-bit addresses; state and
reply flags use existing volatile views; and packet fields depend on the native
byte order. The recovered code preserves these established boundaries. A port
should consolidate the DHCP packet/buffer/state definitions, use free functions
or a real message type, pointer-sized addresses, explicit byte-order operations
and target-appropriate synchronization. Validate packet lengths before parsing.
The new callback header resolves the callback-type disagreement without claiming
to resolve these other representation issues.

No new pragma, assembly, intrinsic, hardware access, compiler override, split
boundary or symbol rename. The mechanical exception inventory changes only the
line number of its existing `0xC0000000` mask hit (an address-class mask, not a
hardware access). Section 7's upstream import scope is unchanged.

## Validation

Current-main build/baseline and retention passed before editing. Full build and
`tools/check_pr.py` pass with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; no exact function, code/data address,
linked range or padding is lost. All 42 functions and 4,800 data bytes match.
The scanner adds this one unit and eight retention names, removing none.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,386 | 27,389 | 3 |
| Exact code bytes | 4,189,632 | 4,191,812 | 2,180 |
| Exact data bytes | 1,470,159 | 1,470,159 | 0 |
| Linked code bytes | 3,673,564 | 3,685,784 | 12,220 |
| Linked data bytes | 1,179,243 | 1,184,043 | 4,800 |
| Linked units | 3,586 | 3,587 | 1 |

Actual ordered linker inputs: 3,587 source objects and 1,386 fallbacks;
SHA-256 `56ce7abf293fc14e4553bb649ed15e826830bff9468fc60d349550e25aeea882`.
