# SymbolChatParts compiled native lifetime; source-link hold retained

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
