# SymbolChatParts compiled native lifetime; source-link hold retained

Later follow-up: the [#243 provenance and propagation control](window-symbol-parts-propagation-control.md)
qualifies a newer upstream source separately from the historical checks below.
One fixed typed/native literal-plus-control scratch case matches all 20 bodies and
198 resolved relocations, without upstream's explicit 8.0f placement. The control's
original-context provenance remains unproved; no scope/provider change follows.

This follows PR #268 checkpoint
`4980c356083cd3a47c9666ff5da779dbb13b3d54`.

## What this checkpoint establishes

The native constructor, destructor, render and task methods compile to the
original complete 4620-byte SymbolChatParts text. Its sole producer now uses
ordinary new and its complete 8084-byte source unit also matches. The window
has a genuine Addition initializer, borrowed word pointers at 0x7C/0x80,
an opaque owned heading at 0x88 and the known Scroll producer at 0x8C.
The shared size/offset assertions preserve its 0x90-byte image. Signed count
at 0x76 is supported by repeated original lha loads. Other fields/padding in
0x70..0x87 are preserved; no speculative initialization is added.

Original reference inspection finds one zero-addend constructor call, from
SubSymbolChat::create_parts, allocating 0x90 and supplying position 0x7D and
addresses of globals 805D6498/649C. Those inputs and the dereferencing consumers
support the two borrowed s32* fields. Existing outer controller word/result
transport remains qualified. No descendant was found.

The constructor creates the opaque heading from global-new 0x24 storage and
the existing message-0x33 type-1 protocol. It then creates the known plain
12-byte Scroll_8026D790 from a zero float pair. Destruction retains erased
flag-1 Scroll release, then opaque heading release, followed by automatic
Addition cleanup. This does not broaden the generic release helper's unknown
ChoiceSetting producer claim, invent a complete heading class or replace its
protocol with an unsupported typed delete. Native render/task use the actual
receiver and Base/Addition fields rather than the old window prefix replica.

## Actual executable input remains original for this unit

This is compiled-source progress, not newly source-linked executable lifetime
recovery. The original SymbolChatParts object is still selected; the compiled
source object is not. The actual producer unit remains source-linked. No
linked-unit count or executable code/data gain is claimed for this family.

The unit remains blocked by 18 missing .sdata2 exports 805DD7C8..805DD80C.
Original reference audit finds no external original-object references. However,
the repository localization tool correctly detects a compiled-source reference
to its own extern label 805DD7F8, the 32.0f row extent in fn_802857C4. Localizing
that name would leave a real undefined reference when the original object is
removed, so no localization is applied and the tool's guard is not bypassed.

Three bounded source-correct probes do not close that blocker:

- A direct 32.0f literal preserves section sizes and pool bytes but changes
  floating-register allocation in fn_802857C4.
- A normal exported constant definition preserves text but adds an unowned
  four-byte .sdata section. It is not activated.
- Recovering that helper as an address-named member with actual window/context
  fields and the literal adds an instruction and changes registers. Its one
  original caller is Parts render, and its context offsets are supported by
  TWindowDrawContext, but exact matching is not established. It is not activated.

The matching extern implementation is retained. No section pragma, duplicate
symbol, artificial reference, padding, alternate linker binding or other
matching control is introduced to force constant placement. Complete source
linkage remains a concrete hold; the later full checks must preserve it.

## Descriptor/table claim and original range refinement

The matching compiled data is 44 bytes: provisional WindowLayoutDescriptor
at [804D2DD8,804D2DEC), extent 178/188, order 50050, entries lbl_804D2D40,
flags 0xC3, then the compiler's normal four-function 24-byte table through
804D2E04. The old 28-byte catalog size is corrected rather than inventing a
slot. Raw data and normalized/full-link references match. This is a split
claim supported by compiled source; its selected provider remains the original
SymbolChatParts object. It is not 44 newly source-linked data bytes or proof
of original translation-unit boundaries.

The earlier Help checkpoint's 204-byte original suffix at 804D2D3C is refined
into a 156-byte original prefix through 804D2DD8, the 44-byte claim above, and
four zero bytes [804D2E04,804D2E08). The original prefix and original target
object remain selected once. The tail is separately qualified as natural
alignment before the existing PartsSet source .data at 804D2E08; it is excluded
from source claims and report coverage, not defined as source padding. Original
and rebuilt resolved words/ranges remain unchanged. The former whole-204-byte
original-input claim no longer describes the refined linkset.

The protected 1044-byte setup helper and all other original unknown remainders,
prefixes and suffixes remain unchanged. Existing ChoiceSetting, task-global,
Snapshot, ChallengeResult, CustomSelect, callback, status cleanup asymmetry
and wider interface holds remain open. PR stays draft.

## Validation checkpoint

Before integrating newer main, full DOL SHA-1 remains
0d85744b51d7379efb025a943d0cd5aaae2191a3. check_pr against the published
checkpoint passes: +44 matched data, zero linked-code/data gain, unchanged
27,390 exact functions and 3,589 exact linked units. The one additional
four-byte alignment gap is separately reported. Retention remains clean at
17,792 names. Final publication additionally requires current-main integration,
fresh-baseline comparison, selected-input provenance and immutable-head review.

## Final current-main integration and verification

Current main `65b21c210ae980e9d2fe4aef1a3314ed84df1ddd` is merged. Its
keyboard recovery deleted the old soft-keyboard unit after folding the code
into TKeyBoardControl. The merge retains that deletion and carries this PR's
two explicit Base ABI corrections into the new owner. Its entire 9096-byte
text matches the current-main original and remains source input once. Existing
main types and compiler qualifications are preserved.

Both the separate fresh-main baseline and integrated branch reproduce the
original DOL hash. Address-based check_pr passes against the prior published
checkpoint, retaining main's three new exact functions and linked code/data
gains. Current totals are 27,393 exact functions and 3,587 exact linked units;
unit-count reduction comes from main's folding, with no linked-address loss.
Retention passes at 17,827 names and the port inventory is current.

This family alone adds 44 matched data bytes and no linked code/data bytes.
The original Parts object is selected once, the native compiled object is
absent from the actual executable inputs, and its still-undefined 32.0f label
is supplied by that original provider. Compiled text 4620, rodata 8, sdata2 72
and descriptor/table 44 bytes match their original ranges. The producer's
8084-byte text remains identical and source-linked once. No constant scope
localization or linked-unit addition is applied.

Actual linker input and raw/resolved range checks preserve the new 156-byte
original Help prefix, selected original target data, protected 1044-byte setup
helper and all other retained original pieces exactly once. The following
PartsSet source .data is 24 bytes, alignment eight; the new 2E04..2E08 gap is
zero in original and rebuilt DOLs. A scan of 4968 active current-main original
objects/249768 relocations finds no catalog-addressed target into that gap,
and no symbol starts there. Against current main there are now 14 qualified
four-byte gaps/56 bytes for the combined PR; main's own new sdata2 gap is
shared by the baseline and is not charged to this family.

Compared with fresh main, combined PR deltas are +600 matched code, +1220
linked code, +1308 matched data and +1264 linked data bytes. Source raw
Base/Addition binding use falls to 38 calls across 19 units (16 Base and three
Addition pairs), while the four shared bindings remain. Those source counts
do not imply that Parts is now taken from compiled source. The constant link
blocker and every prior ownership/interface hold remain active.

## Controlled entry-field follow-up

After native HelpItem checkpoint `36c7adffe9b13c125922bd3dbf56b6a7f06f86fe`,
the Parts draw helper uses this unit's existing Part_80285314 view for entry
x/y at 0x08/0x0C instead of indexing a float pointer. The C helper receiver,
context, count and argument contracts are retained. With the extern constant
as control, every compiled section byte and all text/data/sdata2/rodata
relocation records are unchanged from the published matching object.

A second, isolated probe substituted the 32.0f literal after this field-only
control passed. Its helper remains 484 bytes and the unit 4620 text bytes,
but eleven instruction words differ through floating-point register allocation.
The constant pool size remains unchanged. The type reconstruction therefore
does not resolve the constant export/source-link blocker. The literal probe is
not activated; the extern reference and selected original provider remain.
No constant-placement permutations or compiler scheduling controls are added.

The matching field clarification passes the full DOL hash, check_pr against
36c7adffe9 (zero metric delta), unchanged port/retention checks, selected-input
and protected-remainder provenance. Native HelpItem's separate 24-byte data
gain remains intact. Current main remains 12cc95ca737a3a8757c17f45df06a9af4821d872.
Parts and all unrelated ownership/interface holds remain; PR remains draft.

## Upstream #196/#198 ownership check

Following continuation checkpoint `0f17a7a216751f820458e06c890d389861463700`,
the independent data-worker report was reconciled with exact upstream revisions
before considering any source activation. It confirms the same eighteen missing
float exports, not a new function, size or alignment recovery opportunity.

[Upstream #196](https://github.com/zeroz41/pso-decomp/pull/196), inspected at
`90435282423e1e8011e74b7cb6a33c79e9eef561`, moves the Parts source and its
include paths from misc to ui/chat. Its split-unit name changes, but text, rodata
and sdata2 ranges do not. It adds no definition for the named 32.0f export and
does not change any of the eighteen float symbol scopes.

[Upstream #198](https://github.com/zeroz41/pso-decomp/pull/198), inspected at
`77dfb3c5b82b070cf5a8fbcee15a7a4f05f2594d`, retains the identical Parts source
blob `8d86b3211f372526659c1c9ccafd2d5fa48fafa2`. Its adjacent PartsSet folding
does not move or claim this unit's constants. Both heads retain
`extern const f32 lbl_805DD7F8` and the corresponding helper load; the 18 floats
at [805DD7C8,805DD810) remain exported four-byte objects. The conversion-bias
range is unchanged as well. This supplies no new local-pool or exported-object
ownership evidence.

The current compiled Parts object still has an undefined lbl_805DD7F8. Matching
local section bytes and twenty matching functions do not define that symbol.
The earlier absence of external original-object references does not erase this
real compiled-source dependency. Source linkage needs a source-correct named
definition/export, or independently supported local ownership that removes the
dependency while preserving every affected section, instruction and relocation.
Neither upstream revision provides that mechanism.

Independent read-only review confirms this assessment. No constant-placement
probe is repeated, no float is localized, no symbol scope or linked-unit list is
changed, and the selected original provider remains intact. This check adds no
coverage or readiness claim and leaves every lifetime/interface/constant hold in
place. The preceding gated DOL, no-loss and provider qualification is unchanged.
