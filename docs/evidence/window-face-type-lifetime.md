# Native SymbolChat FaceType lifetime

This follows PR #268 checkpoint
`4dea8719cf6755a48adde660e1fff3ab28a6b6e7`, including current main
`224eb99838471c243b20c305eddac75e7ff76c8f`.

## Window lifetime and actual producer

TWindowSubSymbolChatFaceType is 0x6C bytes: Base, three flag/selection
bytes, a borrowed selection pointer at 0x64, and owned opaque heading
storage at 0x68. Existing size and new pointer-offset assertions preserve
the image. No descendant or additional constructor reference was found.

The sole original producer is SubSymbolChat state 8. It allocates 0x6C,
passes position lookup 0x7D and the address of selection byte 805D6494,
and stores the result in controller handle m_48. This becomes ordinary
new TWindowSubSymbolChatFaceType with shared `(void *, s8 *)` arguments.
The outer handle retains its existing word-valued transport boundary.

The genuine constructor initializes Base with the evidenced descriptor,
client 4 and supplied position, then sets the name, three bytes, selection
pointer and heading. Native destruction releases that heading through its
existing protocol and automatically cleans up Base. No default Base
lifetime or borrowed-selection release is introduced.

Render/task become actual native methods, with explicit draw-context receiver
forwarding. Selection drawing uses the real pointer field instead of a
parallel prefix view. The close handler calls its actual is_open member
rather than relying on an incoming register through a no-argument C
prototype. These changes preserve every original text byte.

## Opaque owned heading and unchanged child protocol

The original constructor separately allocates 0x24 bytes with global new,
then calls the existing type-1 heading initializer with message 0x33 and
client. Its returned storage goes into 0x68. The destructor calls the
existing nullable release with flag 1; that protocol performs its legacy
cleanup and global deletion.

The constructor now explicitly forwards storage, text carrier and client
through that existing initializer, with its observed pointer result. Shared
message lookup supplies the same text carrier. Field 0x68 remains void*,
rather than inventing a complete heading class, C++ child constructor,
virtual destructor or native delete expression.

The child's concrete class and broader entry-helper ownership remain
unresolved. Historical SubStatusDisp names in the initializer, render/task
helpers and release protocol are retained as qualified legacy interfaces;
this does not assert a full SubStatusDisp object in 0x24 bytes. FaceType
owns this allocation and releases it once, while field 0x64 remains borrowed.

## Descriptor/key-function organization and compiler table

The original descriptor at [804D2CE0,804D2CF4) has extent 178/188,
order 50050, flags 0x43 and an entry relocation to lbl_804D2C18. The
existing provisional WindowLayoutDescriptor schema represents these fields.
The opaque entry data stays original.

The descriptor is defined with the native destructor/key function in the
existing class unit, TWindowSubSymbolChatFaceType.cpp. The constructor
remains in its existing text_802841FC unit and references that class-associated
input. Both text claims and unit identities are retained. This source
organization follows the actual class ownership and relocation; it neither
creates an artificial unit nor proves an original translation-unit boundary.

The key function naturally emits a four-function 24-byte table at
[804D2CF4,804D2D0C): destructor, task, render and TObject shadow. The
catalog size is corrected from 28 to 24 bytes. Descriptor and table form
44 bytes, alignment eight and table offset 0x14; original/compiled raw data
and fully linked targets match. No extra virtual slot, manual table, padding
definition or alignment override is added.

The separate tail [804D2D0C,804D2D10) is zero in both original and rebuilt
DOLs. It is outside the claim and report coverage. No original tail object
is selected: the following already source-owned Help data has size 44 and
natural alignment eight, reproducing the word by ordinary linker alignment.
The checker qualifies this four-byte gap; no meaningful data is lost.

The preceding original auto_07_804D2C14_data.o now has 204 bytes, equal to
the prefix of main's original 500-byte object. It remains selected once and
its resolved bytes are unchanged. Entry-array ownership is not fabricated.

## Verification and standing holds

Complete original/compiled unrelocated text is identical in the five changed
units and one header-dependent unit, each actual source link input once:

| Unit | Bytes |
| --- | ---: |
| TWindowSubSymbolChatFaceType | 104 |
| text_802841FC | 160 |
| TWindowSubSymbolChatFaceType_80283A70 | 1,828 |
| TWindowSubSymbolChat_802839C0 | 176 |
| TWindowSubSymbolChat_80281814 | 8,084 |
| TWindowSubSymbolChat_80283954 | 108 |

The class's 44-byte data and render unit's eight-byte rodata and 56-byte
sdata2 sections also match. The full DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes:
all 27,387 exact functions and 3,588 exact linked units retained, no
code/function/non-padding coverage loss, and 44 additional matched/linked
data bytes. Retention is clean at 17,747 names (+1, no removals); the porting
inventory passes. Against fresh main 224eb9983, the combined PR retains
+600 matched code, +1,220 linked code and +912 matched/linked data bytes.
Eleven qualified four-byte alignment gaps now lie outside report coverage.
No new compiler control is introduced.

One more Base construction/cleanup pair leaves the raw interface. It now
has 52 calls across 26 source units: 22 Base pairs and four Addition pairs.
The four bindings remain.

The original Help suffix of 204 bytes, SoundBalance suffix of 532 bytes
and separate 1,044-byte text remainder [8026E1D4,8026E5E8) remain original
inputs exactly once, with unchanged unrelocated and resolved bytes.
ChoiceSetting's unknown 0x7C producer, task-global word 805D5D94, Snapshot
separation and broader child/interface/ownership holds remain. The PR stays
draft and must not be marked ready or merged.
