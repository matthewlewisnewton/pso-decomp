# Distinct Hard keyboard and composer flag receivers

This follows PR #268 checkpoint `10bc3e84d64084fb9ea0b51d8f6257ec98be0e16`.
Five flag helpers now use their supported Hard keyboard or composer owner.
Their bytes, access widths and caller contracts remain exact. No construction,
destruction, compiler table or wider wrapper interface is activated by this
owner correction.

## Word and halfword operations name different images

The word at 0x60 belongs to the 0x74-byte Hard keyboard for these three helpers:
set_flag60_bit200, clear_flag60_bit200 and is_key_held (mask 0x100). Control's
field 0x24 is populated by the existing Hard producer. Chat's hardKeyboard field
has its separately verified Hard producer. Their calls now name that receiver.

The apparent ShortMail field-0x24 calls also reach Hard: their outer helpers
receive the w5C keyboard controller, created through TKeyBoardControl__ct, whose
field 0x24 is the Hard child. They do not use the unrelated mail-selection field
at the same offset. The legacy outer helper declarations are unchanged; only
the proven child receiver is corrected here.

is_key_active tests mask 0x1 in a halfword at 0x60, and set_flag62_bit8 writes a
halfword at 0x62. Their supported owner is the 0xB8-byte TWindowKeyBoardBase
composer. Callers include Control's freshly allocated field 0x20, Hard's borrowed
field 0x70, Soft's borrowed field 0x6C, Chat's composer and the existing keyboard
wrapper's field 0x20. The actual composer declaration already represents those
two halfwords. Reads and writes now use those members directly. Result types
remain int; neither a new boolean narrowing nor a word-sized field alias is used.

Original object inspection found direct zero-addend references for the migrated
helpers, with no mixed receiver or address-taking reference. Constructor chains
and all known source consumers agree with the receiver split. No ownership of
either keyboard child or borrowed composer changes, and no null/flag behavior is
altered. Original whole instructions and all call targets independently agree.

## Adjacent interfaces remain qualified

The existing is_active halfword query retains its Chat/SubComCard caller views.
The adjacent set_flag62_bit2 setter retains its MakeTeam forwarding wrapper's
legacy integer-return view. Their bodies, declarations and calls are unchanged;
their complete receiver/return contracts need separate qualification. They are
referenced helpers, not dead code. No cast or replacement wrapper is added to
conceal the mismatch.

The existing outer ShortMail/SubComCard/Soft views, raw composer/reset/card
helpers, control-key member-pointer table and Hard deleting/table integration
remain held. This correction establishes only the five shared flag receivers.

## Validation and current main

Implementation `fdbdcc62efd00259dd913732b3b2624decd9148c` passes check_pr against 10bc with zero metric delta.
Its shared-gate full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Retention changes exactly one setter
name, preserving the count of 17,862 before main integration. Port inventory
passes unchanged. No compiler control or technical exception is introduced.

All six complete compiled text sections match captured 10bc source and main
originals: owner3284, Chat3808, ShortMail helper196, SubComCard helper148, Hard440
and Soft owner9096 bytes. All resolved text/data targets and allocated sections
are unchanged. Each source object is selected once in actual executable inputs,
with its original text counterpart absent. The five individual helper bodies
remain exact at 16/16/12/12/16 bytes. The two held adjacent helpers remain exact
and untouched. Existing data, including control/member-pointer/jump tables,
retains the same providers. The original Hard table28 stays selected once with
all four resolved targets unchanged; no new table or data section is emitted.

Fork main's Dark Falz demo update `6c35e6fa976ec49bb095710abef8717d7912a40d` is integrated by merge
`0a721dc2130b0f59d6f0d9cbf79e1f9959d1459f`. Both isolated builds retain the
original DOL hash. check_pr against published 10bc and freshly built main6c
passes. Main contributes +512 matched/linked code bytes, +232 matched/linked
data bytes and one exact function; its source fold reduces the source-bearing
inventory by four and linked-unit inventory by three. Its two four-byte sdata
alignment ranges are shared with the fresh baseline and are not flag-family
coverage changes.

Current totals are 27,398 exact functions, 3,584 exact linked units and 3,645
source-bearing units, with clean retention at 17,869 and unchanged port inventory.
Combined PR deltas versus fresh main remain +600 matched code, +1220 linked code,
+1496 matched data and +1452 linked data bytes. Hard input, Snapshot, WS_Word and
protected-original provenance pass again, including the original 1044-byte helper
and WS_Word's original3412 provider/916-byte rendering body. Raw Base/Addition
calls remain 22 across 12 units. All remaining ownership, lifetime, renderer,
constant and interface holds remain; PR stays draft.

## Later status/setter qualification

The [status protocol follow-up](window-keyboard-status-protocol.md) supplies the
additional receiver and return-use evidence for the two adjacent helpers above.
It recovers their composer owner and the actual Control setter wrapper's observed
void protocol. This supersedes only those adjacent query/setter holds; the other
legacy wrappers, float-forwarding, table, lifetime and wider interface holds stay.
