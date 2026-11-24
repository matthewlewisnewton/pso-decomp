# Native SimpleStatus, Status and PartyStatus lifetimes

This follows PR #268 checkpoint
`08978811ebb444eabb920142a6c168b7d7419ba3`, including current main
`387621104107ed1ff8c650bf2f50ef00c6859ba4`.

## Coordinated constructor and destructor chains

SimpleStatus is a 0x78-byte Base-derived window. Status and PartyStatus
inherit it without additional fields. Original reference inspection finds
three SimpleStatus constructor calls: its factory and both derived chains.
Each derived constructor has one factory caller. No additional descendant
was found. Recovering all three together avoids introducing another raw
base-lifetime binding.

SimpleStatus now takes position pointer, word client and descriptor pointer,
explicitly narrows at Base initialization, retains the existing client
halfword assignment, sets its name/counter/scale and zeros five child slots.
Status genuinely forwards that complete contract through its base initializer;
its old one-argument declaration hid the position/client/descriptor live
arguments. PartyStatus takes a slot word and descriptor, builds SimpleStatus
with position lookup 0xAB and the local client, then narrows the supplied slot
into its halfword. Main's Base client type is unchanged.

The former SimpleStatus member factory actually received position as its
receiver. It is now static create(position, client), using ordinary new. The
status factory's split-screen branch calls it through the shared declaration;
the full-screen branch uses ordinary new Status with all three real inputs.
PartyStatus's factory also uses ordinary new and preserves its word-valued
slot calculation and existing opt_propagation-off scope. Derived destructors
express automatic SimpleStatus cleanup, which then automatically cleans Base.
No default Base lifetime or new raw constructor/destructor alias is added.

SimpleStatus and PartyStatus render are genuine native methods, explicitly
passing their receiver to shared TWindowDD::draw_default_entry before actual
background and entry drawing. Status's existing native rendering and task/
helper interfaces remain qualified where not otherwise recovered here.

## Five managed icon slots and preserved four-slot destructor

The five pointers at 0x64 through 0x74 are actual optional Base-derived icon
windows. The existing icon helper creates the chain icon in slot 0 and four
status-effect icons in slots 1 through 4, each from a 0x74-byte allocation
and the existing ComCard initializer. Its hidden/invalid cleanup loop closes
all five. Constructor zeroing and all field offsets support the shared
Base-window pointer array; the fifth slot is neither unused nor always zero.

The original SimpleStatus destructor, however, closes only slots 0 through 3.
Native cleanup deliberately retains that four-iteration loop and clears each
closed pointer. It does not silently extend cleanup to slot 4. This observed
asymmetry remains a hold: this checkpoint does not establish complete fifth-
child teardown or assert why the executable omitted it. No immediate delete,
new ownership policy or unrequested bug fix is introduced. The existing icon
helper's entire 3640-byte text section remains unchanged.

## Compiler tables and supported descriptor ownership

Each native key-function unit owns a 20-byte provisional WindowLayoutDescriptor
followed naturally by its 24-byte, four-function compiler table:

- SimpleStatus: [804D0CB0,804D0CDC), extent 153/50, order 50100, entries
  lbl_804D0B58, flags 0xB28.
- Status: [804D0F78,804D0FA4), extent 228/76, order 70050, entries
  lbl_804D0D98, flags 0xB28.
- PartyStatus: [804E7808,804E7834), extent 114/46, order 70100, entries
  lbl_804E7750, flags 0xB28.

All three old table sizes change from 28 to 24; no fictitious virtual slot
is introduced. Each natural .data section is 44 bytes, alignment eight and
table offset 0x14. Their raw data and resolved ranges match. This organization
does not prove original translation-unit boundaries. No manual table/padding,
alignment override, new pragma, intrinsic or assembly is introduced. The
existing Status FP-contract and PartyStatus string controls remain unchanged.

## Exact original-data refinement and alignment qualifications

SimpleStatus preserves original 344-byte [804D0B58,804D0CB0) and 140-byte
[804D0CDC,804D0D68) inputs around its claim. PartyStatus preserves the original
264-byte [804E7700,804E7808) prefix. Each is selected once and equals the
corresponding current-main original slice.

The earlier SoundBalance checkpoint retained all 532 bytes at
[804D0D94,804D0FA8) as one original input. This recovery refines only the
proved Status descriptor/table: 484 original bytes [804D0D94,804D0F78),
44 source-owned bytes, then four zero bytes [804D0FA4,804D0FA8). The remaining
484-byte original prefix is selected once; the old whole-532-byte original-
input preservation claim no longer applies. All resolved bytes across that
entire former range remain identical.

The isolated zero tails [804D0FA4,804D0FA8) and [804E7834,804E7838) leave
report coverage. They are excluded from the source claims and reproduced by
natural alignment before the existing source-owned SubAreaMap .data (24 bytes,
alignment eight) and TAdChrSelASlotGC .data (528 bytes, alignment eight).
No original tail object is selected and no source padding is defined. Original
and rebuilt words are zero; no symbol starts there, and scanning 4973 active
current-main original objects/249768 relocations finds no catalog-addressed
incoming target into either range. Full DOL equality corroborates the resolved
bytes. These are two additional qualified gaps, making 13 gaps/52 bytes for
the combined PR, not loss of meaningful data.

The protected 1044-byte original text setup helper, Help/CustomEquip data
remainders and all other previously retained original prefixes/suffixes remain
selected exactly once and byte-identical. No unrecovered original body or
opaque entry data is synthesized.

## Validation and remaining holds

Six complete source text sections match original objects and are selected
once with no original text fallback: SimpleStatus 564, Status 1260,
PartyStatus 688, status factory 124, party factory 92 and icon helper 3640
bytes. The three native data sections add 132 matched/source-linked bytes.
All native constructor/destructor chains, both factories and actual linker
inputs retain exact bytes and relocations through the full link.

Full builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against the published
checkpoint passes: no function/code/meaningful-data or linked-unit regression,
27,390 exact functions and 3,589 exact linked units. Retention is clean at
17,792 names and port inventory passes. Against fresh current main the combined
PR has +600 matched code, +1220 linked code and +1264 matched/linked data bytes.

Raw Base/Addition ABI usage is reduced to 40 calls across 20 units (16 Base
and four Addition construction/cleanup pairs), with four shared bindings
retained. The fifth-child cleanup asymmetry and broader status/task/helper
attribution remain held, along with the original setup helper, mixed callback
signatures, ChoiceSetting, task-global, Snapshot, ChallengeResult, CustomSelect,
AreaMap interface and other standing holds. PR remains draft; portable or
complete lifetime recovery is not claimed.
