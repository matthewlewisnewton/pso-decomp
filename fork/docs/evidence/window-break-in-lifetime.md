# Native BreakIn window lifetime

This bounded follow-up starts at PR #268 checkpoint
`19e455b404f6fd3055ffa1f34ec9d6f3a81d5fb9`, including main
`18207f98696bab4911ca2cecac1c19381e2ea506`.

## Ownership and allocation

TWindowBreakIn is exactly the 0x60-byte Base image, with no additional
fields. The original destructor only installs the derived table, cleans
up Base and conditionally releases the object. No own child cleanup or
descendant was found. The native empty destructor now expresses automatic
Base cleanup and compiler deletion behavior.

The only original constructor reference is the Ctrl initializer in
TWindowCtrl_8024C160: allocate 0x60, construct, store in f2C. This site now
uses ordinary new TWindowBreakIn and the shared class declaration. The
constructor genuinely takes no arguments; it initializes Base explicitly
with the existing descriptor, client 4 and layout-position lookup 0xAA,
then sets the class-name pointer. It does not invoke a default Base lifetime.
The C initializer and duplicated raw destructor declarations are removed;
the catalog uses the actual compiler constructor symbol.

Render now passes its receiver explicitly through the shared
TWindowDD::draw_default_entry declaration. The existing task behavior is
unchanged. The historically attributed update_entry_visibility helper and
broader entry/position protocols remain bounded legacy interfaces; this
recovery does not assert their complete class ownership.

## Descriptor, table and natural alignment

The constructor's descriptor at [804CE1B8,804CE1CC) has extent 112/30,
order 50000, flags 0x823 and an entry-table relocation to lbl_804CE030.
The existing provisional WindowLayoutDescriptor schema represents these
layout fields. The referenced entry table remains opaque original input.
No asset data is copied into source.

The four-function compiler table occupies [804CE1CC,804CE1E4): destructor,
task, render and TObject shadow. The old 28-byte catalog size included a
zero tail without relocation; it is corrected to 24 bytes. No fifth virtual
slot is invented.

The descriptor precedes the table in the natural compiler data section:
44 bytes, alignment eight, table offset 0x14. Source claims only
[804CE1B8,804CE1E4). All unrelocated data bytes match and the complete link
verifies pointer targets. The separate four-byte tail [804CE1E4,804CE1E8)
is zero in both original and rebuilt DOLs, and stays outside the source
claim. The following ChallengeResult object's complete data section is
232 bytes with natural alignment eight in both source and original inputs;
ordinary linker alignment reproduces the gap. No padding definition,
alignment override, manual table or new compiler control is introduced.

## Validation and remaining holds

BreakIn's complete 312-byte text and 44-byte data equal the original
unrelocated sections. Its unchanged class-name string and pointer emit
15 rodata bytes and four sdata bytes; their existing split spans are 16
and eight bytes, respectively. The emitted prefixes match, and the remaining
original/rebuilt bytes are zero linker padding. These existing spans stay
covered. The complete
976-byte Ctrl caller text also matches. Both units are actual source link
inputs exactly once, with their original objects absent from the link.

The full DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes:
27,386 exact functions and 3,587 exact linked units retained; matched and
linked data increase 44 bytes with no code/function/non-padding coverage
loss. Retention is clean at 17,717 names (+5, no removals), and the porting
inventory passes. Against fresh main 18207f986, the combined PR retains
+600 matched code, +1,220 linked code and +732 matched/linked data bytes.
Ten qualified four-byte alignment gaps are outside report coverage.

One more Base construction/cleanup pair leaves the raw interface, reducing
it to 60 calls across 31 source units: 26 Base pairs and four Addition
pairs. The two constructor and two destructor bindings remain.

The original 1,044-byte remainder [8026E1D4,8026E5E8) remains original
input exactly once, with unchanged unrelocated suffix and resolved DOL
bytes. ChoiceSetting's unknown 0x7C producer, task-global word 805D5D94
and broader ownership/interface holds remain. Snapshot is deferred: its
0x64-byte Base window and separate global 0x40-byte capture object share
historical false attribution and require their own ownership audit. The
PR stays draft and must not be marked ready or merged.
