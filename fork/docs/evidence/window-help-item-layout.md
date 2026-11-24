# HelpItem native lifetime and mixed-receiver boundaries

This follows PR #268 checkpoint
`f110ad682a4cb35cd0f2d41fabed1905631aa693`. The prerequisite checkpoint separated mixed receivers. The direct-member
constructor follow-up now establishes matching Base inheritance and native
HelpItem lifetime; callback and wider interface boundaries remain qualified.

## Separate the actual window image from entry receivers

HelpItem is 0xBC bytes and now derives from TWindowBase. Name, position,
page pointer at 0x64 and callback words at 0xB0 retain size/offset assertions.
The real constructor contract (void*, u16) is unchanged; its initializer
explicitly narrows the client to the recovered Base s16 contract. Native
destruction releases the page with the existing flag-1 protocol before automatic
Base cleanup. Allocation uses the inherited TObject allocator.

The old header also exposed float position at 8, color at 10 and an owned
string at 18 as though those were HelpItem window fields. They are entry
receivers used by historical helper methods. The header no longer offers
those overlapping aliases. TWindowHelpItem_8025A12C uses its existing local
entry prefix for color, animation, owned text and values at 10/14/18/1C/20.
Its string field is no longer called a vtable, and its word value at 20 is
not mapped onto the actual window's client halfword.

The summary/value placement helper at 80243408 and the notification constructor
at 80341334 write entry position at 8 explicitly. The depth-reset helper in
TWindowSubStatusDisp_8025A9B4 uses its existing text-entry prefix at 1C. These
operations are not mapped onto TObject tree members or Base frame bytes.
Historical exported helper owners and broader entry APIs remain qualified;
this does not claim their complete semantic class identities or portable
member-call contracts.

## Concrete page ownership and opaque callback boundary

Field 64 is the proved PageIndicator_8026CB44 pointer, created by the existing
ordinary-new producer. Draw/input/decay and flag-1 release preserve the observed
protocol. The field is no longer an integer, but no different release policy
or native-delete wrapper is added. Other tail words remain unchanged.

The callback field remains the existing 12-byte CallbackWords representation.
Its null initialization, reset, serialized callback records and invocation
machinery are unchanged. No callback signature, new native member-pointer type
or derived-class ownership is invented. Original inspection found no descendant
and 14 constructor calls; the existing two ordinary-new callers and 12 legacy
allocation/constructor calls preserve their established widths.

The constructor now explicitly forwards its actual 30/34 two-float position
prefix to the existing copy entry. It does not pretend a complete PartsSet
object lives at that field. The helper's historical exported name remains a
qualified legacy ABI boundary.

## Correct descriptor identity, not a vtable

The 20 bytes at 804CF6E0 are extent 228/184, order 38900, literal null entries
and flags 3. The source uses the existing provisional WindowLayoutDescriptor
schema under window_help_item_parameters. The misleading __vt__15TWindowHelpItem
name and 0x134-byte catalog extent are corrected to that 20-byte descriptor;
adjacent callback tables are not absorbed into it. All 1832 bytes of the owning
data section remain byte-identical, including callback records.

The actual object table at 804CF8B0 is now compiler-owned
__vt__15TWindowHelpItem, exactly 24 bytes. Its four relocations are the native
destructor, task, render and inherited TObject shadow slots. Only that range is
claimed by TWindowHelpItem_80255AB4; the separate descriptor and adjacent callback
tables retain their original owners. No new padding or table slot is introduced.
Fresh retention adds the four newly named native symbols; no unrelated cleanup
is included.

## Resolving the constructor difference

Earlier native probes retained a decompiler self alias and optionally cached
the position address. Both produced the same two-instruction scheduling
difference. The source-correct follow-up uses direct members throughout:
m_name, &m_30, save_position(), page creation and the existing tail initialization.
It uses neither the alias nor a cached position pointer. The complete 832-byte
text section now matches, including constructor 252, destructor 104, task 208
and render 116 bytes. No manual vptr store, Base default constructor, unrelated
work in Base arguments, compiler control or post-processing is needed.

All 34 text relocation records agree with the current-main original after
resolving both catalogs to target addresses, including descriptor versus actual
vtable identity, the existing page constructor and qualified release boundary.
The native table's 24 raw bytes and all four data relocations match the regenerated
original split. The compiled HelpItem object is the actual linked input once.

## Parts constant follow-up and standing holds

Before this family, the existing [conversion-pool](conversion-pool-constants.md) and
[Boss6 constant evidence](tboss6type1-sdata2-constants.md)
was reviewed for the Parts 32.0f blocker. It already covers ordinary external,
unnamed-namespace, C-linkage and class-static placement forms. It supplies no
new source-correct placement fix and does not authorize treating a four-byte
float as a conversion-bias export. The prior rejected probes are not repeated,
and Parts' matching extern implementation/source-link hold remains.

Callback/signature, entry-owner, raw lifetime, ChoiceSetting, task-global,
Snapshot, ChallengeResult, CustomSelect, status cleanup asymmetry and other
standing holds remain. The protected original remainders are unchanged.
PR remains draft. This establishes HelpItem lifetime only, without lifting the
Parts constant, callback, broader interface or unrelated ownership holds.

## Validation and current main

The complete serialized build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against the published
`bf3b2680e8573dbad56482fa690cbe3347910446` checkpoint passes without code,
function, coverage or linked-address regression. This follow-up adds 24 matched
and linked data bytes; existing exact text was already source-linked.

Totals remain 27,395 exact functions and 3,588 exact linked units. Retention is
clean at 17,836 names. Port inventory passes unchanged; no construct or scope is added. Twenty-one complete affected/helper/
constructor-caller text sections are identical to main originals. Twenty are
selected source inputs once; the already-held TWindowHelpItem_80243408 unit
keeps its original input because of unrelated existing data blockers.
The descriptor/callback owner's full 1832-byte data section remains identical.

Selected-input and range checks preserve Parts' original provider/source-link
hold, the protected 1044-byte setup helper and every retained original remainder,
prefix and suffix. No additional alignment gap is introduced. Combined deltas
versus fresh main are +600 matched code, +1220 linked code, +1332 matched data
and +1288 linked data. Source raw Base/Addition use drops to 36 calls across 18 units after removing
this window's construction/cleanup pair; the remaining legacy callers keep
their ABI holds.

Integrated main is `12cc95ca737a3a8757c17f45df06a9af4821d872`, whose README-only
change follows the separately validated `7e25e5b529718a679cc65a028ea6d46952c74f36`
source baseline. Publication checks current remote main again.
