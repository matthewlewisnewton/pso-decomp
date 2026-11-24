# Keyboard Control text copies and queries

This follows PR #268 checkpoint `c99491924e90c06f1711e75b0e560f4cde35aa64`.
The remaining three helpers in the historical SubComCard wrapper unit now have
their evidenced Control receiver. Composer text sizing/export also use their
actual native owner. Record identity, capacity/storage aliasing, broader Soft
interfaces and CMName activation retain their existing qualifications.

## Original references and actual receivers

All-section relocation inspection of the original objects establishes these
zero-addend direct text calls, with no address-taking or other-section references:

| Existing address | Recovered member | Original calls |
| --- | --- | --- |
| 80131BC4 | Control::allocate_text_copy() | 17 |
| 80131C10 | Control::is_keyboard_active() | 10 |
| 80131C34 | Control::is_key_active() | 17 |
| 8025C974 | Composer::export_text(char*) | 2 |
| 8025CA70 | Composer::get_text_buffer_size() | 1 |

Control means TKeyBoardControl and composer means TWindowKeyBoardBase. The
outer receivers come from the proven 0x2C Control producers in MakeTeam,
SubComCard, ShortMail, InformationBoard, SymbolChat, Quest, JoinLobby, CMName
and serial/password/PPP paths. The latter shared keyboard variable is populated
by serial's create_keyboard_control modes 2/3. Control field 0x20 supplies the
established 0xB8 composer. Chat's separate direct export uses its own proven
composer and existing caller-provided output buffer.

All 44 outer source calls now use those actual Control members, and Chat uses
the native composer export. Obsolete local C prototypes and the ShortMail copy
function-pointer cast are removed. Queries still return normalized int conditions:
the existing composer halfword queries test masks 0x20 and 0x1 respectively.
Neither wrapper updates state. No cancellation/confirmation meaning is inferred
beyond the observed caller branches and underlying bits.

## Fresh allocation and preserved export behavior

The historical realloc_buffer name did not resize existing storage. Its 76-byte
body calls global operator new[] with the composer's size result, exports into
that allocation and returns it. allocate_text_copy returns char* explicitly.
Existing word-valued consumers keep emission-free s32 pointer views where their
broader interfaces remain qualified; existing char* consumers use the pointer
directly. No downstream getter or protocol signature is guessed.

Original consumers treat the result as an owned address. MakeTeam replaces its
retained name/comment allocations; the other observed paths use temporary copies
and pair them with operator delete[], including early returns. No deletion,
retained-field assignment or ownership transfer is changed. Export still runs
after allocation without a new null guard, preserving existing failure behavior.

The native composer export and size methods retain their existing
Base_8025C974 prefix view, 0x6C text buffer and 0xB4 flags, along with the existing
embedded-record measure_char_overflow receiver protocol. This does not establish
a complete nontrivial record class, portable aliasing contract or new capacity
invariant. The historical signed 32-bit size return view is retained; no uniquely
original signedness is claimed.

Sizing counts the terminator and reserves two language-prefix bytes whenever
flag 0x10 is clear. Export emits that prefix only for nonempty text. Empty text
therefore retains its harmless extra allocation. Language selection, encoded
high-byte emission, font/overflow calls, truncation/termination, pointer reloads
and all buffer assumptions remain unchanged. No artificial scheduling variables,
volatile accesses, extra guards, compiler controls or placement changes are added.

## Exact objects and held source

The first native owner probe matches complete wrapper148 and helper4788 text.
All five bodies independently match original at 76/36/36/252/148 bytes.
Fourteen selected source objects retain their entire original text and resolved
text relocation targets: wrappers148, composer helper4788, Chat3808, Quest7064,
PPP1724, serial4452, password1940, text_8032AACC456, InformationBoard1064,
ShortMail5828, MakeTeam1188, SymbolChat8084, SubComCard13404 and JoinLobby23052.
Each is selected once. Across all fifteen changed compiled objects, allocated
section headers/flags/sizes/alignment/data/constants and resolved text/data
relocations remain unchanged from c994. Existing JoinLobby writable-rodata
representation is unchanged. No new table or data provider is emitted.

CMName remains separate: compiled15504 text, all relocations and allocated
sections are unchanged; its original17988 provider remains selected once and
compiled source stays absent from executable inputs. The changed run_task556
instruction bytes and all call targets match original. Its eight pre-existing
SDA21 constant-target differences and unrecovered code remain held. No complete
CMName equivalence, constant ownership or source activation is claimed.

## Validation and remaining holds

The capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against c994 passes with
zero metric/coverage/address regressions and five catalog renames. Comparison
against separately built main `25b4001837b8bdc46666d2ad736a7148a411f978` also
passes. Retention is clean at 17,882 and port inventory passes unchanged.
Current totals remain 27,404 exact functions, 3,585 exact linked units and 3,641
source-bearing units. This family changes no source activation or match metric.

Earlier text, position/depth, Snapshot, WS_Word and protected-original checks pass
again. The original 1,044-byte helper and WS_Word's full original3,412 provider,
including its missing916 renderer, remain intact. Combined deltas versus main
remain +600 matched code, +1220 linked code, +1496 matched data and +1452 linked
data bytes; the fourteen qualified four-byte alignment ranges are unchanged.

Raw Base/Addition calls remain 22 across 12 units and four shared bindings.
Record identity/capacity/storage aliasing, wider Soft and callback/renderer/depth
interfaces, remaining lifetimes, Parts constants, ChoiceSetting producer,
task-global word, CMName activation and protected original remainders retain
their documented holds. PR stays draft.
