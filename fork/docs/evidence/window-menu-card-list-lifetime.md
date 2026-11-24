# Menu and SubComCardList native lifetime chain

This follows PR #268 checkpoint
`e99494222ff334dfed588ff80feea573a1b7c36f`. Menu now constructs its Addition
base and destroys it automatically. SubComCardList's two constructors initialize
Menu, and its destructor releases the page indicator before automatic Menu
cleanup. The three source allocation producers use ordinary new. No replacement
raw lifetime binding is introduced.

## Ownership and argument contracts

Original references establish three Menu constructor calls: its local 0x8C
producer and the two List base initializers. List is the only known descendant;
each List constructor has one 0xA0 producer. Native render/task/destructor table
ownership agrees with those classes. No other direct destructor call surfaced.

Menu retains a word count and word client, narrowing the client explicitly for
Addition and the stored halfword. Allocation remains count times eight bytes,
followed by the original explicit two-word zeroing loop. The destructor retains
the existing release order: the known 12-byte Scroll at 0x84, opaque heading at 0x88,
row buffer at 0x80, then Addition cleanup. The same release helpers/flags and
operator delete[] are used. Heading identity and wider entry/row helper APIs
remain qualified; no complete heading class or new delete policy is inferred.

Both List constructors use Menu count seven/client four and the supplied
position. Page count still divides by seven, rounds away from zero, clamps to
at least one, then narrows through the established signed-byte page constructor.
The page at 0x8C is separately allocated and released with the existing flag-one
protocol. List's remaining initialization and flag/layout calls retain their
original order. Word-shaped fields at 0x80/84/88/8C retain their existing target
representation; the native chains do not imply a wider portable interface.

The extended List mode is deliberately a word parameter with an explicit byte
store at 0x9C. The original factory saves and forwards the entire incoming word
without extsb; the original constructor only narrows when storing the byte.
The old local s8 constructor declaration was not evidence for narrowing the
caller. Existing record/count word transports and the outer factory signature
are retained. The signed page-count boundary is separate and unchanged.

## Separate the existing controller from List

The old List source unit also contained three TUnk_804D1160 controller methods.
Those bodies are moved unchanged into the adjacent source unit that already
contains that same controller's initializer and cleanup. The project source
boundary now follows the evidenced class ownership; it does not establish an
original translation-unit boundary.

List text is now [8027553C,802758C8), 908 bytes. The controller unit covers
[802758C8,80275D84), 1212 bytes: the old List's 836-byte controller suffix plus
the existing 376-byte controller initializer/cleanup. Its switch jump table
moves with those methods, retaining all 32 original bytes at 0x804D1178. No native
controller constructor/destructor or compiler table is added, and its existing
raw TObject/interface holds remain. No compiler control is introduced; the
copied string pragma is not added to the controller unit.

## Compiler tables and original providers

Menu's native table is exactly 24 bytes at 0x804D05E0; List's is exactly 24 at 0x804D1148.
Each has four function relocations matching the corresponding original table.
Both begin naturally aligned, and no descriptor, unknown entry table or padding
is absorbed into their claims.

The existing 112-byte original provider at 0x804D05A8 becomes an original 56-byte
prefix, the 24-byte Menu source table, and an original 32-byte suffix. The prefix
retains the descriptor and preceding opaque data. The former 48-byte provider
at 0x804D1148 is refined into the 24-byte List source table and the original 24-byte
controller table at 0x804D1160. Original providers are actual linker inputs once;
no new alignment gap or synthetic padding is introduced.

## Validation and limits

The serialized full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against e99494222f passes:
+48 matched/linked data bytes and no exact function, code, unit, data coverage
or linked-address regression. Totals remain 27,395 exact functions and 3,588 exact
linked units. Retention is clean at 17,846 names; ports pass unchanged.

Menu's full 6068-byte text, List 908, folded controller 1212 and the 104/80-byte
allocation producers match the original address ranges. Every changed text
relocation is compared by offset, type and resolved target, including section
locals and folded switch targets. The outer caller's full 13,404-byte text also
matches. All six compiled objects are selected once. Both compiler tables and
the relocated jump table match raw bytes and resolved relocation targets. List's
existing string/constant sections match fresh-main compiled source, including
the pre-existing natural constant-pool padding qualification.

ChatSymbol, WS_String, HelpItem, Parts and every protected remainder/provider
retain their prior validation. The protected 1,044-byte helper remains original
and byte-identical. No new callback, heading, ChoiceSetting, task-global or
renderer/helper interface claim is made. ScrollBar's measured constructor hold
and Parts' constant/source-link blocker remain. PR stays draft.

This removes another raw Addition pair: 30 Base/Addition calls remain across 15
source units, with the same four shared ABI bindings. Integrated main is
`12cc95ca737a3a8757c17f45df06a9af4821d872`. Combined PR deltas versus its
separately validated source baseline are +600 matched code, +1220 linked code,
+1448 matched data and +1404 linked data bytes. The fourteen previously
qualified four-byte alignment gaps are unchanged.
