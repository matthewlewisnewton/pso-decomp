# Native Snapshot window lifetime

This follows the capture boundary checkpoint
`e944bae257d23e8b2dd061fba00c6db51dc8cfe7`. TWindowSnapShot now has genuine
Base construction/destruction, its actual renderer/task and a compiler-owned
24-byte table. OptionCtrl's sole 0x64-byte window producer uses ordinary new.
The separate opaque 0x40-byte capture allocation is not a window-owned resource.

## Supported window lifetime

The native position-pointer constructor initializes Base with the existing
descriptor and client four, assigns the existing name, clears byte 0x60 and
preserves the checksum-result flag update. Entry one receives the same localized
text through the existing entry helper. No null/error behavior is changed.
The original constructor has only the OptionCtrl allocation reference; no
descendant constructor or other producer was found in original relocation scans.

The destructor has no descendant resource to release: automatic Base cleanup
and native deleting behavior reproduce the original 88 bytes. In particular it
does not free the shared capture allocation or its buffer. Global startup/transfer
code manages that separate opaque storage under the retained raw protocol.

The renderer now explicitly forwards its actual window receiver to the existing
default-entry helper, frame and entry-list drawing. Its flag/text/icon behavior
is unchanged. Constructor160, destructor88, render176 and existing task152 all
remain exact inside the complete 868-byte source unit. OptionCtrl's complete
160-byte source text also remains exact, including its separate SoundBalance
producer. No live-register constructor argument or raw Base alias is needed for
this window. Wider entry/render-context interfaces remain qualified.

## Compiler table and original prefix

Only [804DDEC8,804DDEE0) is claimed for the compiler table. It is naturally
eight-byte aligned and contains exactly four targets: deleting destructor, task,
renderer and inherited TObject shadow. All 24 bytes and four resolved relocations
match the regenerated original split. No hand-written table, extra slot,
alignment override, padding or gap is introduced.

The original auto_07_804DDBF0_data provider previously held 752 bytes. Its first
728 bytes, including the 20-byte descriptor at 804DDEB4 and all adjoining unknown
data, remain original input once with identical bytes and resolved targets.
The source uses the established descriptor schema but does not claim its data.
The separate original capture table16 at 804DD098 also remains unchanged and
selected once. Native capture identity/destructor ABI, dispatch-at3C and historical
word-valued address interfaces are not recovered by this window change.

## Validation and remaining holds

The full shared-gate build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr against da05
passes with +24 matched/linked data bytes and zero code/function/unit/address
or meaningful-data loss. All seven affected complete text sections and resolved
text relocations match main originals and captured preceding source objects:
868/1364/116/1312/1520/200/160 bytes. All seven source objects are selected once;
their original text counterparts are absent. The five capture consumer/owner
units retain their allocated-section inventories; the only new allocated section
is the window's compiler-owned table24. No source boundary or original-TU claim
is inferred from these object counts.

Retention adds exactly the native destructor/table/render/task names, with no
removal, and passes at 17,856. Port inventory passes unchanged. The previous
protected-original checks pass, including the original 1044-byte setup helper
and WS_Word's complete original3412 provider with its missing916-byte renderer.
No compiler control or additional technical exception is introduced.

Fork main remains `4e784e247d991f1fb25766fc80923242a9ba469a`. Fresh-main check_pr
passes with combined +600 matched code, +1220 linked code, +1496 matched data
and +1452 linked data bytes. Totals remain 27,395 exact functions, 3,589 exact
linked units and 3,653 source-bearing units. The fourteen previously qualified
four-byte alignment ranges are unchanged. Raw Base/Addition calls fall to 22
across 12 units. Capture lifetime, WS_Word, ownership/interface/constant and all
other standing holds remain; PR stays draft.
