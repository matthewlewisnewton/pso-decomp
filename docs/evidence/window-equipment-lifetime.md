# Native equipment-list window lifetimes

This bounded follow-up starts at PR #268 checkpoint
`e48b2f66a589b3f34bf2921d21f13fafae722dd7`, including fork main
`fe6cdb14138b2413778c08f21fd1851170c22ab5`. It covers only
TWindowSubEquipKind and TWindowSubEquipList, two direct MenuIconLine descendants.

Both constructors now initialize MenuIconLine directly and both empty native
destructors use automatic base cleanup. Their factories use ordinary `new`.
Their task methods explicitly qualify the base task call, avoiding a virtual
self-call. EquipKind's render method uses the actual class members. No default
constructor, parent-image change, compiler flag or pragma is introduced.

## Client width and ownership

Both original constructor bodies explicitly sign-extend their incoming word
client at the MenuIconLine call. The native constructors therefore take
`(void *position, s32 client)` and narrow only in the base initializer.
EquipKind's old short factory declaration was misleading: the original factory
forwards the whole word unchanged, and its ten observed external calls use word clients. The factory declaration and definition now agree on that word
contract. Caller bodies do not change. EquipList's factory already uses words.
The existing C factory boundaries retain their integer-valued layout carrier;
this does not claim recovery of the wider window API.

EquipKind retains its 16-bit state at 0x88 and 16-bit timer at 0x8A, with size
0x8C and explicit offset assertions. EquipList adds no fields beyond its
0x88-byte MenuIconLine base. No scalar or pointer field is moved or widened.

The actual compiler-generated tables each contain five function slots:
destructor, task, render, inherited TObject shadow, and inherited MenuIconLine
vfunc_6. The source claims are `[804D15B8,804D15D4)` and
`[804D15D8,804D15F4)`, 28 bytes each. The old 32-byte catalog entries included
a separate zero tail, not another virtual function. No table is written by hand.

Three four-byte ranges leave report coverage: 804D15B4, 804D15D4 and
804D15F4. Each is zero in both original and rebuilt DOLs. They precede
EquipKind's table, EquipList's table, and the already linked GameEnd table,
respectively. All three following source data sections have natural eight-byte
alignment (sizes 28, 28 and 24), so normal linker alignment reproduces the
gaps. No source claim consumes them and no manual padding or alignment override
is introduced. The preceding switch-table claim still ends at 804D15B4.

## Qualification and bounded deferral

Complete original and compiled unrelocated text is identical:

| Unit | Bytes |
| --- | ---: |
| TWindowSubEquipKind | 412 |
| TWindowSubEquipList | 424 |
| text_80278E48 (Kind factory) | 96 |

All three are actual source link inputs; the original objects are not selected.
The complete DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr retains
all 27,384 exact functions and 3,585 exact linked units, with zero code or
non-padding coverage regression. Matched/linked data gains 56 bytes. The
porting inventory passes. Generated retention adds nine entries and removes
the old renamed initializer entry, remaining clean at 17,664 names.

Against fresh main fe6cdb141, the combined PR retains one additional exact
function, +600 matched code bytes, +728 linked code bytes and now +432
matched/linked data bytes. Its previous two qualified four-byte padding gaps
and these three new gaps account for 20 bytes outside report coverage.

The bounded raw ABI inventory drops from 83 calls in 43 source units to
79 in 41 units: the two constructors and two cleanup calls leave the interface.
Its four constructor and three destructor declarations remain needed elsewhere.

ShortCutList is deliberately deferred. Its window lifetime is coupled to a
separate 12-byte page-indicator allocation, whose current initializer is falsely
attributed to the much larger TWindowSubComCardList class. Its misleading
factory receiver is a layout pointer, and the selected index is actually a
signed word used for division/remainder by four. Coordinated recovery of that
auxiliary protocol is needed before changing this third descendant; neither
its source nor its callers are changed here.

No new ChoiceSetting 0x7C producer lead was found in this equipment family;
MenuIconLine's separate storage does not establish that unrelated field's
identity. ChoiceSetting's unknown producer, task word 805D5D94 and the broader
legacy interfaces keep the standing draft hold active.

The subsequent [ShortCut/page-indicator recovery](window-shortcut-page-lifetime.md)
resolves this specific deferral with a separate plain address-based type and
six genuine construction sites before recovering the window lifetime. It does
not identify ChoiceSetting's unrelated 0x7C producer.
