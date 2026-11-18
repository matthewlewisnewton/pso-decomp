# Item-drop packet and payload contracts

This is a source-contract follow-up to merged #253 (`f8824976c724e9266a61ae57bbd5e5d22f625fe0`,
original head `a451711eb4f78e90b646ff9f0e2ea9a7189db994`), based on fork main
`e258b1e91233fb9ddcbf72c9c168784a346153ff`. It retains the original recovery,
source selection and binary evidence. It claims no new recovered code or data.

## Lifetimes and direct interfaces

The two adjacent drop handlers at `8011AA68` and `8011AB64` now create genuine
`TItemData` locals. All three send sites declare a native
`G_DropItem_PC_V3_BB_6x5F` only after item validation and encoding, at the old
initializer call. Its first member is the native DC packet, whose constructor
constructs its `FloorItem` member once. Both contain a real `G_ClientIDHeader` at
zero. The PC suffix remains four opaque bytes. There is no extra early clear,
placement allocation, wrapper entrypoint or invented owning class.

The receive view has the same real header and `TItemData` payload. Size/offset
guards preserve incoming extent 0x28, outgoing extent 0x2C, record +4 and payload
+0x14. The existing packet swap at `8011B0FC` is an explicit byte interface for a
complete aligned packet with that live header. Its record leaf at `80104200`
accepts an aligned 0x24-byte encoded representation, including the two existing
sync-buffer uses; it does not claim a `FloorItem` lifetime for those buffers.
No sync parsing or bounds behavior changes.

The initializer at `8010E344` now defines `TItemData::init` with real members,
keeping the original byte/store order. The enemy selector at `8010663C` and
restrictions at `80105EA4` operate on the real item. The enemy selector's +0x10
field is `data2.data_u32`, not the item ID at +0x0C. All restriction declarations
and direct callers agree. The byte-2 range guard retains its signed character
representation read before unsigned comparison to reproduce the original
load/conversion sequence; it does not cast the item to an unrelated object.
The remaining generator scalar carriers and byte views keep their established
ABI. No manager, rule, rarity, or class-hierarchy migration is included.

## Symbol reconciliation

Only these identities change; their addresses, sizes, allocated bytes and
relocation destinations remain fixed:

| Address | Previous symbol | Current symbol |
| --- | --- | --- |
| 8011AB64 | `process_enemy_drop_request__FScsisiff` | `process_enemy_drop_request__Flsisiff` |
| 8011B0C8 | `send_item_packet__6TLobbyFv` | `send__24G_DropItem_PC_V3_BB_6x5FFv` |
| 8011B130 | `init_header_packet__6TLobbyFv` | `__ct__24G_DropItem_PC_V3_BB_6x5FFv` |
| 8011B188 | `init_header__6TLobbyFv` | `__ct__18G_DropItem_DC_6x5FFv` |

The area parameter is a 32-bit carrier: `8011ABFC` forwards it without byte
narrowing to the 32-bit generator at `8011C39C`. Both direct callers already
produce sign-extended area values, and their instructions remain unchanged.
Retention replaces the old area-helper and DC-initializer names with their
corresponding current names; the other two original #253 roots remain unchanged.
The link set is unchanged.

## Validation

Targeted comparison preserves all allocated sections and 1,102 relocations
across the six changed source units against the fresh baseline, with only the
four explicit identity mappings above. The focal unit retains all 15 exact
functions, 2,192 code bytes and 74 allocated relocations. The four packet/caller
units match the original fully. The two item-provider units retain their
baseline data reconstruction limitations; their allocated bytes and relocations
are unchanged. The scheduled development build completed through the repository capacity
wrapper in legacy/exclusive mode, with the pinned Ninja executable. The full
build and `tools/check_pr.py --no-build` pass: zero changes in matched functions,
matched code/data, linked code/data, address coverage, or linked-unit counts.
All 3,553 linked units and 16,678 retention entries pass. Four identities are
renamed at fixed addresses; no no-loss exception or new coverage credit is used.
The actual linker response was captured during this build and all its ordered
inputs were fingerprinted. The focal compiled source input occurs once and its
original fallback is absent.

`cmp` confirms the output equals the original DOL; both have SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The original #253 checkout and
proof remain retained separately. Independent final review binds the repaired
commit and these records before publication.
