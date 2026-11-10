# Remaining MenuIconLine descendant lifetimes

This bounded follow-up starts at PR #268 checkpoint
`60d77e0f9ca4dce33b0d73234a5d1ce59bd6680c`, including main
`fe6cdb14138b2413778c08f21fd1851170c22ab5`. It covers SubItemList and the
existing address-named CheckBox window TUnk_804CE7E8, item-list window
TUnk_804D0948, and its existing derived TUnk_804EF4E0. It introduces no
new semantic class names, default constructors, compiler flags or pragmas.

## Constructor contracts and real owners

All four classes now use genuine constructors and automatic base cleanup.
Their factories use ordinary `new`. The two D0948 overloads initialize
MenuIconLine directly; EF4E0 initializes its real D0948 base. Render/task
functions and the D0948 destructor formerly attributed to SubStatusDisp now
belong to the actual address classes. Base task calls are explicitly qualified.

SubItemList and CheckBox constructors carry a word client and narrow at the
MenuIconLine initializer. CheckBox forwards its incoming word unchanged to its
name/client setup method; that method now accepts the word and narrows only
when storing the existing halfword at 0x20. Its whole-word forwarding and
halfword store are reproduced without a short-signature alias.

D0948's four-argument constructor takes position, heading word, count word and
alternate descriptor; it narrows the local client at the base call. Its other
constructor takes heading, count and client words, narrowing at the same
boundary. Both explicitly pass the heading to `sub_8026DE94(s32)`, which
passes it to `ensure_status_display`. The old no-argument declaration hid
a live-r4 dependency. EF4E0 supplies layout B0, count 0x40 and its existing
descriptor. The descriptor remains an original input, not newly claimed data.

SubItemList's selected-row reset and refresh belong to the 0x90-byte window,
not its 0x44-byte controller. The original reset's three direct callers are
window construction, controller task on LIST, and refresh. Both observed
external refresh calls use LIST. The controller's LIST field has one observed
positive producer: the SubItemList factory. These methods and declarations
move to SubItemList while their bodies retain exact instruction bytes. The
signed halfword at 0x88 is used without assigning meaning to 0x8A; the existing
opaque four-byte field and word at 0x8C remain unchanged. Offset/size assertions
cover the preserved layouts. Other historically mislabeled list helpers are
not silently represented as recovered by these two moves.

The closed SubItemList factory/caller pair now shares pointer-valued position,
extent and result types, plus the word client. The controller's existing word
handle remains unchanged. The other outer factory APIs retain existing word
carriers, including heading/text transport; this change does not claim complete
recovery or portability of those broader interfaces or the base's child protocol.

## Native tables and the bounded D0948 source claim

All four compiler-generated tables have five function slots (destructor, task,
render, TObject shadow, and MenuIconLine initialization or EF4E0's override):

| Class | Source-owned table | Bytes |
| --- | --- | ---: |
| TUnk_804CE7E8 | [804CE7E8,804CE804) | 28 |
| TUnk_804D0948 | [804D0948,804D0964) | 28 |
| TUnk_804EF4E0 | [804EF4E0,804EF4FC) | 28 |
| TWindowSubItemList | [804D1688,804D16A4) | 28 |

Each old 32-byte catalog range included an unrelocated zero tail. The D0948
tail remains outside its claim in the selected original
`auto_07_804D0964_data.o` input. Three other four-byte tails leave report
coverage: 804CE804, 804D16A4 and 804EF4FC. All are zero in original and
rebuilt DOLs. The following source data sections (ChoiceSetting, SubLog and
TAdEnterPPPPassGC) have natural eight-byte alignment, so normal linker
alignment reproduces them. No manual padding, table bytes, extra virtual
function or alignment override is introduced.

The previous D0948 project unit claimed text `[8026DFE8,8026E5E8)`, but its
source implemented only the first five functions through 8026E1D4. The separate
1,044-byte function `[8026E1D4,8026E5E8)` has no source implementation. Its
observed caller is ShortCut construction; its full ownership remains unresolved.
The source claim is now bounded to the naturally emitted 492-byte implemented
prefix plus the real table. This refines a project claim; it does not recover
or assert the original translation-unit boundary. Compiler settings and source
organization are not changed to force an emission result.

DTK selects `auto_03_8026E1D4_text.o` exactly once for the unimplemented
remainder, with no fake source file, stub or replacement body. Its unrelocated
text is byte-identical to the corresponding suffix of the fresh main original
object; the rebuilt DOL's resolved 1,044 bytes equal the original DOL. The
source prefix replaces its original input exactly once. Address coverage is
retained, and the whole DOL hash independently verifies the combined linkage.

## Qualification and remaining boundary

Complete original/compiled unrelocated text is identical, and all listed
objects are actual source link inputs:

| Unit | Bytes |
| --- | ---: |
| TWindowSubItemList | 504 |
| TWindowSubItem | 5,604 |
| TWindowCheckBox | 16 |
| TWindowSubStatusDisp_80248BE8 | 1,052 |
| text_80249004 | 84 |
| TWindowShop | 108 |
| TWindowSubStatusDisp_8026DFE8 (bounded prefix) | 492 |
| TShopJudgmentItemWindow_8026DF00 | 232 |
| text_80338F3C | 96 |
| TLobby_80338E9C | 160 |

The complete DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr retains
all 27,384 exact functions with zero matching/code/non-padding coverage loss.
The exact source prefix adds one linked unit (3,585 to 3,586), 492 linked code
bytes, and the four tables add 112 matched/linked data bytes. Retention is
clean at 17,677 entries (+11 additions, -2 stale renamed entries); the porting
inventory passes. Against fresh main fe6cdb141 the combined PR retains +600
matched code, +1,220 linked code and +572 matched/linked data bytes, with eight
qualified four-byte alignment gaps outside report coverage.

No raw MenuIconLine constructor/destructor calls remain. The three unused
MenuIconLine bindings and incidental header include leave WindowConstructorAbi.h.
It now contains only two constructor and two destructor declarations for Base
and Addition. Their 70 calls across 36 units remain a real lifetime boundary.
The unimplemented original remainder, wider helper/factory interfaces,
ChoiceSetting's unknown 0x7C producer and task word 805D5D94 remain held.
The PR stays draft and must not be marked ready or merged on this checkpoint.
