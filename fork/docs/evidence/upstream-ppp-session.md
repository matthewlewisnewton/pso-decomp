# PPP/session control recovery

Original recovery baseline: fork main `224eb99838471c243b20c305eddac75e7ff76c8f`.
PR rebased and revalidated on `387621104107ed1ff8c650bf2f50ef00c6859ba4` after DHCP #371 merged.
Reference: upstream #213/#215 session code at
`9eb8da7276b625b67c1854e7ea3372b0d944f456`,
`src/pso/network/TLobby_803FAEA0.c`.

Recover link-status retrieval at `0x803FB358` (340 bytes) and the connection,
PPP setup and authentication routine at `0x803FB7A4` (2,452 bytes). The existing
unit now contains all 16 exact functions and links its 4,824 code bytes and
536 BSS bytes. Move the already-exact `get_remaining` after the connection
routine to reproduce native object order; no split or symbol changes.

## Interfaces

The new `NetSessionLayout.h` gives the connection routine a bounded 0xD0-byte
session view, including its 0x60-byte modem configuration and request at +0x88.
Size and offset assertions check the native layout. These are views of the
existing storage, not a claim that every network caller now shares one type.
`SessionModemConfig` deliberately describes the complete configuration; the
existing modem-script header's shorter `ModemConfig` is a separate partial view.

The upstream routine declares several status helpers with returns that differ
from their definitions. This recovery makes the definitions and declarations
consistently return signed 16-bit status for `TLobby__sub_80403D28`,
`TLobby__sub_80403DA8`, `TLobby__sub_80403C60`, `TLobby__sub_80403BA8`,
`TLobby__sub_80403B04`, `TLobby__sub_80403864`,
`wait_for_connection__6TLobbyFPv`, `TLobby__sub_803FAEDC`, and
`TLobby::map_state_to_mode_id`. Their return paths use bounded status codes.
The forwarding wrapper's local result is also `s16`. All previously exact
callers/callees remain exact. New call arguments agree with the existing helper
definitions, including pointer types and the 16-bit mode. No function-pointer
cast conceals an incompatible new call. Existing unrelated local declarations
elsewhere in the network stack remain outside this change.

## Native constraints and port guidance

The status routine preserves upstream's address temporaries, including the
otherwise-unused assignment to `new_var`. Removing that assignment and
simplifying the redundant base initialization changes its base register from
r5 to r4 and scores 99.882355%; this is compiler steering, not meaningful runtime
state. The connection routine retains repeated notification/abort macros and
its `goto` to the wait phase. The packet records carry native-endian fields and
32-bit pointer values. Status retrieval still reads raw protocol offsets;
callbacks release and reacquire the existing mutex around notification.

Ports should use one coherent session/protocol layout, pointer-sized fields,
explicit byte order, platform synchronization and typed callback interfaces.
Remove unused matching temporaries and simplify the repeated control flow
without changing the notification timing. The old provisional TLobby/TUdpSocket
static wrappers and explicit mangled free entry points remain native boundary
debt. No assembly, intrinsic, hardware access, pragma or compiler override is
introduced. The unit's 36 existing effective pragma lines and GC/1.2.5n
`-opt nocse` setting are retained; many old pragma blocks surround declarations
only. Section 4 records this scope; section 7's historical import scope remains
unchanged.

## Validation

Current-main build, baseline and retention passed before editing. Full build
and `tools/check_pr.py` pass with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; no exact function, code/data address,
linked range or padding is lost. The scanner adds one unit and four retention
names, removing none. Exception inventories remain current.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,386 | 27,388 | 2 |
| Exact code bytes | 4,189,632 | 4,192,424 | 2,792 |
| Exact data bytes | 1,470,159 | 1,470,159 | 0 |
| Linked code bytes | 3,673,564 | 3,678,388 | 4,824 |
| Linked data bytes | 1,179,243 | 1,179,779 | 536 |
| Linked units | 3,586 | 3,587 | 1 |

Actual ordered linker inputs: 3,587 source objects and 1,386 fallbacks;
SHA-256 `f19ab893b06998cd0987517f3def08681f5c6685b537d3289c1e7a1a4a87c194`.

The table and input digest above describe the original recovery baseline.
Revalidation against main `387621104` retains the same incremental gains and
all DHCP coverage. The rebase only combines the generated retention additions
and exception-register sections; recovered source is unchanged. Full build,
original DOL hash, address/link no-loss and inventory checks pass on the combined
base, as does comparison against the original `224eb9983` baseline.
