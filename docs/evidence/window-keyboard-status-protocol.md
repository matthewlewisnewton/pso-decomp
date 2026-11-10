# Composer status and the void Control setter protocol

This follows PR #268 checkpoint `b56690de6194d026a9036afd52a59ecaad659895`.
The remaining adjacent is_active query and set_flag62_bit2 setter now have their
supported TWindowKeyBoardBase composer owner. Their forwarding setter belongs to
the actual TKeyBoardControl and uses the observed void protocol. The unrelated
float-forwarding helper and all lifetime/table/renderer holds remain unchanged.

## Receiver and result-use evidence

The original is_active helper has two direct callers: Chat passes its proven
composer, and the existing SubComCard-named query wrapper passes Control's field
0x20. That field is populated by the native 0xB8-byte composer producer. The query
reads mask 0x20 in the halfword at 0x60 and returns a normalized word result. Its
declaration, definition and both calls now use the actual composer. The outer
query wrapper's legacy owner is not changed by this correction.

The setter writes mask 0x2 in the composer's halfword at 0x62. Its only original
caller is the MakeTeam-named forwarding function at 80131A5C, which forwards its
field 0x20. All five original callers of that forwarding function allocate 0x2C
bytes and call TKeyBoardControl__ct. They are the ShortMail, two SubComCard,
InformationBoard and SubSymbolChat keyboard producers, so the wrapper's actual
receiver is Control. No address-taking or other reference was found for this
wrapper in the original object inventory.

Every original wrapper call immediately overwrites r3 with the saved controller
pointer before further use. No observed caller consumes a result. This supports
a void setter and void Control wrapper for the closed observed protocol; it does
not prove unique original source return-type spelling. All five calls now use
that contract, and the old integer-return C view of the setter is removed.
No replacement wrapper body or alternate export is added. Receiver and field
argument positions remain unchanged.

The corrected wrapper forwards Control's composer directly through the actual
member declaration. Original null and allocation-failure behavior is preserved,
and there is no new object or ownership transfer. The adjacent 36-byte
get_lobby_field_20 helper and its historical float/live-argument view remain
untouched. Raw composer/reset/card, outer wrapper, control-key member-pointer,
Soft, capture and window lifetime interfaces still need their own qualification.

## Exact code and unchanged data

The query12, setter16 and forwarding wrapper36 independently match original
instructions. All eight complete text sections and every resolved relocation
match captured b566 source and main originals: owner3284, Chat3808, query wrapper148,
setter wrapper owner72, ShortMail5828, SubComCard13404, InformationBoard408 and
SubSymbolChat8084 bytes. All five setter call offsets/types/targets agree.
Existing allocated sections and text/data/constant targets are unchanged. Each
source object is selected once in the executable inputs, with its original text
counterpart absent. The former five flag helper bodies also remain independently
exact under their previously recovered owners.

There is no data claim, split, alignment change or compiler table emission. The
original Hard table28 and all four targets remain original input once. Native
control/composer lifetime recovery is not claimed by these member definitions.
Raw Base/Addition calls remain 22 across 12 units. No compiler control or new
technical exception is introduced.

## Validation and main integration

Implementation `4e41ccea0a1e0b29fe576ee159cbac67d3878cb0` passes check_pr against b566 with zero metric delta,
three catalog renames and unchanged retention at 17,869. The full shared-gate
build reproduces DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`; the port
inventory passes unchanged.

Main `6dfba15dc7d0ad790d70c90c535473363703ca23` is integrated by merge
`838e673f374f5a5898d9665f27155a8eaa75fc36`. Both isolated builds match the
original DOL. check_pr against published b566 and freshly built main6df passes.
Main contributes +536 matched code, +672 linked code, +248 matched/linked data
bytes and two exact functions. Its source fold removes two source-bearing units;
the linked-unit count is unchanged. Those changes are attributed to main, not
this zero-delta status family.

Current totals are 27,400 exact functions, 3,584 exact linked units and 3,643
source-bearing units. Retention is clean at 17,870; the one added name belongs
to main. Combined PR deltas versus fresh main remain +600 matched code, +1220
linked code, +1496 matched data and +1452 linked data bytes. Hard input, previous
flag-body refinements, Snapshot, WS_Word and protected-original provenance pass
again, including the original1044 helper and WS_Word's original3412 provider with
its missing916-byte renderer. All other documented holds remain; PR stays draft.
