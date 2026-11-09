# Native SymbolChatHelp lifetime and borrowed state

This follows PR #268 checkpoint
`e9ffe7079e339f9a5337a175ece4730d4fb2c834`, including main
`18207f98696bab4911ca2cecac1c19381e2ea506`. Snapshot remains deferred;
its real window and separately allocated capture object need a separate
ownership audit.

## Actual owner and allocation producers

TWindowSubSymbolChatHelp has size 0x74: Base, a flag byte at 0x60 and
four pointer words at 0x64..0x70. Its original destructor only cleans up
Base and conditionally releases the object. It neither releases nor owns
the pointed-to state. No descendant was found.

All four original constructor references are zero-addend REL24 calls from
TWindowSubSymbolChat_80281814. Each allocates 0x74, passes the address of
byte-selection global 805D6494 and word-mode global 805D64A0, then stores
the Help object in controller handle m_54. All four sites now use ordinary
new TWindowSubSymbolChatHelp with the shared `(s8 *, s32 *)` declaration.
The outer controller handle remains word-valued; its broader handle protocol
is not silently retyped.

Native construction explicitly initializes Base with the existing Help
descriptor, client 4 and position lookup 0x7E. It sets the class name and
flag byte, stores the two borrowed pointers, and clears the two optional
toggle targets. Native empty destruction expresses automatic Base cleanup.
Render now explicitly forwards its receiver through the shared draw-context
entry point. No default Base lifetime, child release or virtual slot is added.

## Borrowed fields and coordinated helper receivers

The original consumers establish the pointer accesses:

| Offset | Observed access |
| --- | --- |
| 0x64 | Signed byte selection, incremented and wrapped at eight |
| 0x68 | Word mode, tested by Help drawing |
| 0x6C/0x70 | Nullable word toggle targets, read/written under flag bit 4 |

The three original pointer-setter calls pass addresses of globals 805D6498
and 805D649C. These are borrowed toggle targets, not owned allocations.
Typed fields replace integer storage and duplicate receiver-prefix views;
input and drawing access the actual fields. Size and pointer-offset assertions
preserve the class image.

Six helpers were attributed to the smaller TWindowSubSymbolChat controller,
although all original calls use its m_54 Help object. Independent original
reference inspection found only the following calls, all in the same
controller unit, without address-taken references:

| Helper | Calls |
| --- | ---: |
| Set flag bit 1 | 2 |
| Set flag bit 2 | 3 |
| Clear flag bit 2 | 1 |
| Clear flag bit 4 | 1 |
| Install toggle pointers and enable bit 4 | 3 |
| C helper clearing bit 1 | 2 |

The four bit methods now belong to Help. The pointer setter is the
address-named Help member sub_8028392C(s32 *, s32 *); its old position name
and integer arguments are removed. The C helper becomes the ordinary
address-named fn_80283944(Help *), returning void as required by its body
and all observed ignored-result calls. It does not claim an original C++
member identity. Shared declarations, definitions, callers and catalog
symbols change together; no alternate mangled alias is added. Other
historically misattributed controller methods remain outside this recovery.

The flag byte uses s8 as a consistent reconstruction. The original C helper
used a signed-byte view; the other five helpers retain their existing
explicit unsigned-byte mask conversions. Every observed write produces
0..7 and consumers test only bits 1/2/4, so this preserves all observed
behavior and exact instructions. It does not uniquely establish the original
signedness or behavior for hypothetical high-bit flag values. No compiler
control is added to obtain the match.

## Descriptor, compiler table and preserved original suffix

The constructor input at [804D2D10,804D2D24) has extent 242/116, order
50050, flags 3 and a literal null entry pointer without relocation. The
existing provisional WindowLayoutDescriptor schema represents these fields.
The native key function emits the four-function 24-byte table at
[804D2D24,804D2D3C). The catalog size is corrected from 28 to 24 bytes;
no extra slot is invented.

The compiler naturally emits descriptor plus table as 44 data bytes,
alignment eight, table offset 0x14. That exact range is claimed and raw data
is identical. The following zero word [804D2D3C,804D2D40) stays original
input. The opaque data at 804D2D40 is not a proven naturally eight-byte-aligned
source section, so this change does not call that word removable padding.

The actual selected original object auto_07_804D2D3C_data.o contains the
204-byte suffix, including that word. Its unrelocated data equals the suffix
at offset 296 of main's original 500-byte auto_07_804D2C14_data.o. It is
selected exactly once, and all 204 resolved DOL bytes remain unchanged.
There is no coverage loss from this recovery. No opaque entry data, manual
table, padding definition or alignment override is introduced.

## Verification and standing holds

Complete original/compiled unrelocated text is identical in all four changed
units, each selected as actual source link input exactly once:

| Unit | Bytes |
| --- | ---: |
| TWindowSubSymbolChatHelp | 2,408 |
| TWindowSubSymbolChat_80281814 | 8,084 |
| TWindowSubSymbolChat_802838C4 | 144 |
| TWindowSubSymbolChat_80283954 | 108 |

Help's complete 44-byte data, eight-byte rodata and 60-byte sdata2
sections also match.
The full DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes:
all 27,386 exact functions and 3,587 exact linked units retained, no
function/code/data/coverage loss and 44 additional matched/linked data
bytes. Retention is clean at 17,722 names (+5, no removals), and the porting
inventory passes. Against fresh main 18207f986, the PR retains +600 matched
code, +1,220 linked code and +776 matched/linked data bytes. The ten previously
qualified four-byte alignment gaps are unchanged.

The raw Base/Addition interface now has 58 calls across 30 source units:
25 Base pairs and four Addition pairs. Its four bindings remain. The separate
original 1,044-byte text remainder [8026E1D4,8026E5E8) is still selected
exactly once, with unchanged unrelocated and resolved bytes. ChoiceSetting's
unknown 0x7C producer, task-global word 805D5D94 and broader ownership/interface
holds remain. The PR stays draft and must not be marked ready or merged.
