# Native SoundBalance window lifetime

This follows PR #268 checkpoint
`a578d1161d6af0c28bb70a486e86f93656acea0e`, including current main
`224eb99838471c243b20c305eddac75e7ff76c8f`.

## Actual lifetime and allocation producer

TWindowSoundBalance is 0x68 bytes: Base followed by a flag byte, signed
selection byte, two gain halfwords and trailing padding. Its original
destructor only installs its table, cleans up Base and conditionally releases
the object. No own child release or descendant was found.

The native constructor explicitly initializes Base with its descriptor,
client 4 and supplied position. It sets the class name, flags, selection and
gain sentinels, positions its existing entries, then applies either zero gains
or the saved settings. The empty native destructor expresses automatic Base
cleanup. No default Base lifetime or additional allocation is introduced.

Original reference inspection found one zero-addend constructor call and no
address-taken constructor references. OptionCtrl allocates 0x68 and supplies
option entry 0xCF as position. That producer now uses ordinary new through
the shared void* position constructor, retaining its established word-valued
factory result. The adjacent Snapshot producer is unchanged and remains
subject to its separate window/capture-object ownership hold.

Existing size and new field-offset assertions preserve selection at 0x61,
music gain at 0x62 and sound-effect gain at 0x64.

## Explicit entry/text forwarding and borrowed settings

The old constructor's no-argument entry-field and text-width declarations
relied on live argument registers. It now passes each actual Base entry
pointer explicitly to the existing getter at 8024477C, then passes the
returned text carrier to shared calc_text_width(char*). The getter's existing
s32 return is preserved: its implementation reads the word at receiver+0x20.
The cast to char* expresses the observed text use of that carrier, rather
than claiming a complete SubComCard object at the entry address.

This is a qualified legacy entry-word boundary. Its historical exported
mangled name and broader widget ownership are not recovered here. No new
wrapper, alias body or alternative mangled signature is added. Both entry
chains retain exact instructions and explicit argument dataflow.

The global-state call uses the actual shared static declaration returning
u8*, not a local declaration changing its return type. It returns the
system_save_payload pointer. The existing SoundBalanceSettings prefix view
reads a signed music halfword at offset 4 and signed effects byte at offset 6;
new assertions check those offsets. This is borrowed save-payload access,
not an allocation, ownership claim or assertion of the complete payload type.
The original null test, sentinel initialization and gain-update order remain.

## Actual draw-context view and existing compiler controls

Render now views the draw-context result as TWindowDrawContext, rather than
its unrelated KeyBoardSoft-derived image. All accesses use the existing
inner_x/inner_w fields of the verified context prefix. Selection-bar drawing
already accepts that actual context type. Instructions are unchanged.

The pre-existing scoped opt_common_subs off around render and fp_contract on
around construction remain. This recovery adds no pragma, intrinsic, assembly,
hardware access or compiler override; it does not approve or remove the
remaining portability qualifications of those existing controls and interfaces.

## Descriptor, compiler table and original suffix

The constructor input at [804D0D68,804D0D7C) has extent 470/60, order
50100, flags 3 and an entry relocation to lbl_804D0CE0. The existing
provisional WindowLayoutDescriptor schema represents these layout fields.
The referenced entry table remains opaque original input.

The native key function emits a four-function 24-byte table at
[804D0D7C,804D0D94). The catalog size is corrected from 28 to 24; the
trailing zero word is not an invented virtual slot. Descriptor and table
naturally form 44 bytes, alignment eight, with table offset 0x14. Both raw
data and fully linked targets match, without a manual table or alignment
override.

The following word at 804D0D94 remains original input with the following
opaque data. The selected auto_07_804D0D94_data.o contains 532 bytes, identical
to offset 572 onward in main's original 1,104-byte auto_07_804D0B58_data.o.
The preceding original entry-data prefix remains 528 bytes of that same
baseline object. Both original pieces are selected exactly once; the
532-byte suffix's resolved DOL bytes are unchanged. No trailing-word padding
or ownership claim is made, and no coverage leaves the report.

## Verification and standing holds

Complete original/compiled unrelocated text is identical in both changed
units, each selected as actual source link input once:

| Unit | Bytes |
| --- | ---: |
| TWindowSoundBalance | 1,996 |
| TWindowOptionCtrl_8026B828 | 160 |

SoundBalance's complete 44-byte data and 16-byte rodata also match.
The full DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes:
all 27,387 exact functions and 3,588 exact linked units retained, no code,
function, data or coverage loss, and 44 additional matched/linked data bytes.
Retention is clean at 17,746 names (+5, no removals); the porting inventory
passes. Against fresh main 224eb9983, the combined PR retains +600 matched
code, +1,220 linked code and +868 matched/linked data bytes. The ten previously
qualified alignment gaps are unchanged.

One more Base construction/cleanup pair leaves the raw interface. It now
has 54 calls across 28 source units: 23 Base pairs and four Addition pairs.
Its four bindings remain.

The original Help data suffix of 204 bytes and separate 1,044-byte text
remainder [8026E1D4,8026E5E8) remain original inputs once, with unchanged
unrelocated and resolved bytes. ChoiceSetting's unknown 0x7C producer,
task-global word 805D5D94, Snapshot separation and broader ownership/interface
holds remain. SubStatusDisp's adjoining 16-byte data at 804D2B20 is not
speculatively assigned to enable its native table. The PR stays draft and
must not be marked ready or merged.
