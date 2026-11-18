# Composer flag forwarding through Control and Chat

This follows PR #268 checkpoint `e56ab605d4b75352052cd711af52b571e9d4feb1`.
Five existing flag functions now have their evidenced composer, Control or Chat
owner. Their old free/update/icon names implied operations the bodies do not
perform. This recovery changes neither lifetime nor allocation behavior.

## Original references and owner evidence

An all-section scan of the original objects finds only direct zero-addend text
calls to these functions, with no address-taking or other-section references:

| Address | Native member | Original calls |
| --- | --- | --- |
| 801F64F4 | Control::clear_keyboard_flag60_bit1() | 10 |
| 801F6520 | Composer::clear_flag60_bit1() | 1 |
| 80247D2C | Composer::set_flag62_bit4() | 2 |
| 80265410 | Control::set_keyboard_flag62_bit4() | 4 |
| 80246FF0 | Chat::set_keyboard_flag62_bit4() | 1 |

Control is TKeyBoardControl and composer is TWindowKeyBoardBase. All Control
receivers trace to the established 0x2C producers. The ten clear calls cover
Quest, serial/password/PPP, ShortMail and SubComCard. The four set calls cover
serial, ShortMail, MakeTeam and SymbolChat. Their field 0x20 is the proven 0xB8
composer. Existing callers use the operations as void calls.

The separate 80246FF0 wrapper was falsely declared as SubShortCut::free_icon.
Its sole caller passes field 0x38 immediately after constructing TWindowChat
with ordinary new. Chat's field 0x20 is its own composer. The call now uses the
actual Chat member rather than a SubShortCut receiver view. The Control and Chat
wrappers remain separate original functions even though their bodies are equal.

All fourteen Control calls and the one Chat call now use their native members.
The free_menu_object/update_chat_window declarations and obsolete local C leaf
prototypes are removed after migrating their complete reference sets. No alternate
ABI binding, alias wrapper, function-pointer cast or extra virtual slot is added.

## Flag semantics and preserved boundaries

The 801F6520 leaf clears mask 0x0001 in composer halfword 0x60. The 80247D2C leaf
sets mask 0x0004 in composer halfword 0x62. Native members use the existing u16
fields and preserve both original access widths and masks. The three forwarding
wrappers retain their child-null guards. They neither allocate nor release an
object or buffer, and no freeing/reopening/cancellation semantics are inferred
from the old names or observed state transitions.

Quest's two early-return paths retain their original deletion/flag-call order.
No owning field, queued destruction, pointer retention or callback behavior changes.
Existing word-valued child fields remain qualified as before. No new validation,
null guard, flag reset, initialization or compiler/output control is introduced.

The adjacent historical SubShortCut close/reopen method remains unchanged at
64 bytes, including its broader receiver/implicit argument qualifications. The
separate Soft-window word-0x60 setter fn_80247ED8 remains unchanged at 16 bytes;
it is not made a composer halfword operation. Control show/hide's complete
196-byte unit is unchanged and remains selected once. Those wider interfaces,
complete Soft identity and native lifetimes retain their holds.

## Complete-object and link validation

The five bodies independently match original at 44/16/16/44/44 bytes. Initial
native probes preserve complete Chat3808, menu-owner6068 and shortcut-helper108
text; the completed full build also preserves Quest7064 and all caller objects.
Thirteen changed source objects have complete original text bytes and resolved
text relocation targets: those four, PPP1724, password1940, serial4452,
serial-detail1512, ShortMail5828, MakeTeam1188, SymbolChat8084, SubComCard13404
and SubShortCut1880. Every one is selected once as source.

Allocated headers, flags, sizes, alignment, data/constants and resolved text/data
relocation targets remain unchanged from e56 across all thirteen objects. No new
data provider, split, table, original remainder or source activation is claimed.
The existing retention entry for fn_801F6520 follows its native symbol rename;
there is no new retention or port exception.

The shared-capacity full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr passes against published
e56 with zero metric/coverage/address regressions and five catalog renames, and
against separately built main `25b4001837b8bdc46666d2ad736a7148a411f978`.
Retention is clean at 17,882 and port inventory passes unchanged. Totals remain
27,404 exact functions, 3,585 exact linked units and 3,641 source-bearing units.

Prior copy, text, position/depth, Snapshot, WS_Word and protected-original checks
pass again. CMName remains original-selected with its existing constant/code
holds. The original 1,044-byte helper and WS_Word's full original3,412 provider,
including its missing916 renderer, remain intact. Combined deltas versus main
remain +600 matched code, +1220 linked code, +1496 matched data and +1452 linked
data bytes; fourteen qualified four-byte alignment ranges are unchanged.

Raw Base/Addition calls remain 22 across 12 units and four shared bindings.
Record identity/capacity/storage aliasing, CMName activation, remaining lifetimes,
Parts constants, ChoiceSetting producer, task-global word and wider callback,
renderer/depth and ownership interfaces retain their holds. PR stays draft.


## Later Chat close/reopen qualification

The [Chat follow-up](window-chat-reopen-contract.md) establishes the two remaining
historical SubShortCut helper receivers and genuine void close/open forwarding.
Their 64/16-byte bodies and complete objects remain exact. The child-lifetime
and wider interface holds inside Chat's unchanged callees remain active.
