# HelpItem layout and mixed-receiver prerequisites

This follows PR #268 checkpoint
`f110ad682a4cb35cd0f2d41fabed1905631aa693`. It publishes matching layout and
interface prerequisites; genuine Base inheritance and native HelpItem lifetime
activation remain held on the measured constructor difference below.

## Separate the actual window image from entry receivers

HelpItem is 0xBC bytes. Its window name, legacy vptr at 0x18, client, entry
container, position pair at 0x30, frame state, page pointer at 0x64 and callback
words at 0xB0 have size/offset assertions. The unused TObject-prefix bytes
remain opaque. This remains a legacy Base image, not a claimed C++ Base
subobject. The existing real constructor contract (void*, u16), static object
allocator and raw Base construction/cleanup are retained.

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

The actual original object table at 804CF8B0 remains TWindowHelpItem__object_vtable,
24 bytes, and retains its existing provider. No compiler vtable, table rename,
new data claim, padding or source-link gain is activated. Fresh reference
analysis adds the existing callback lbl_804CF6F4 to retention after the corrected
descriptor boundary; no unrelated retention normalization is included.

## Measured native activation hold

A coordinated native probe used Base inheritance, genuine destructor/render/
run_task, the page/callback tail and a compiler-owned table. Destruction (104
bytes), task update (208) and direct-receiver render (116) reproduced the original.
The 252-byte constructor differed only at relative offsets 38/3C: the target
computes the 30-byte position address before storing the derived vptr, while
the native constructor stores the vptr first. The instructions are otherwise
the same, but exact matching is not established.

Forwarding the real Base field to the copy entry and an ordinary cached position
pointer did not resolve that scheduling difference. No Base default constructor,
manual duplicate vptr write, unrelated work in Base arguments, new compiler
control or post-processing is introduced. The native probe is not activated;
the matching legacy lifetime/render/task and all exact objects are retained.

## Parts constant follow-up and standing holds

Before this family, the existing conversion-pool and Boss6 constant evidence
was reviewed for the Parts 32.0f blocker. It already covers ordinary external,
unnamed-namespace, C-linkage and class-static placement forms. It supplies no
new source-correct placement fix and does not authorize treating a four-byte
float as a conversion-bias export. The prior rejected probes are not repeated,
and Parts' matching extern implementation/source-link hold remains.

Callback/signature, entry-owner, raw lifetime, ChoiceSetting, task-global,
Snapshot, ChallengeResult, CustomSelect, status cleanup asymmetry and other
standing holds remain. The protected original remainders are unchanged.
PR remains draft; no native HelpItem completion is claimed.
