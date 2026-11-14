# Base close request and keyboard Control flag receivers

This follows PR #268 checkpoint `fc54d7b66e1d40dc4b5c18f338622e0d86013de2`,
with main `4bec40d6cca74a85e91c848ea2d9f25425a313ad` integrated. It corrects
three helper owners and their observed calls without changing executable bytes
or claiming another native lifetime.

## Base helper and receiver evidence

The 140-byte helper at 80244A4C operates on Base's word 0x2C and conditionally
plays sound 0x53704. It now defines nonvirtual `TWindowBase::request_close()`
instead of a LockOn member. Base's existing 56-byte `close()` delegates directly
to it and then sets mask 0x10, removing the false downcast to LockOn.
The original mask tests, sound condition and state updates are unchanged.

All-section original-object inspection finds twenty direct zero-addend calls,
with no address-taking or other-section references. Their receiver audit covers:

- Global controller BreakIn, Timer and Area children; player controller
  MessageInformation, Status and ActionPalette children; and party-status rows.
- MainMenu's MenuMainMenu child, Trade's menu/confirmation children and the
  SubComCard menu child, all established Base descendants.
- SubMag's HelpItem and the shared button-toggle helper's HelpItem/Message
  receivers. SubMag's separate message/effect cache is distinct from HelpItem.
- The Equip controller's Message child and keyboard Control's Soft child, for
  which the recovered initializer establishes the Base prefix only.
- Base's own close delegation and the keyboard flag helper below.

None of these calls requires LockOn's dynamic type. Existing raw storage fields
are retained; this change makes only the supported Base receiver claim.
ChoiceSetting's separate 100-byte `TUnk_804D0658::request_close()` at 80268794
and the unrelated HunterGuild callback remain untouched.

## Control mask 4 protocol

The 92-byte helper at 80131998 now defines
`TKeyBoardControl::set_flag1c_bit4()`; the 104-byte helper at 801319F4 defines
`clear_flag1c_bit4()`. Their old ShortMail C/member views are removed, including
the obsolete duplicate wrapper header. Exactly three original calls to each
helper pass proven Control objects from SubComCard and ShortMail keyboard
producers. All six calls now use the actual nonvirtual void members.

Both methods use Control's halfword 0x1C. Setting mask 4 only when absent forwards
first to Hard field 0x24's mask-0x200 setter, then to Soft field 0x28's Base close
request. Clearing only when present forwards first to Hard's mask-0x200 clearer,
then requests Soft show only if the reloaded Control halfword has mask 1 clear.
The reload after the Hard call, child-null guards and call order are preserved.
No freeing, cancellation, complete Soft identity or native child lifetime is
inferred from these operations.

## Complete-object and link validation

The first ordinary native-owner probe matches the complete owner texts at 7,864
and 196 bytes. The full build preserves all eleven affected complete texts,
their resolved original text relocation targets and their previous allocated
section headers, flags, sizes, alignment, data/constants and resolved text/data
relocations. The selected source objects occur exactly once:

| Unit | Text bytes |
| --- | ---: |
| TWindowSubComCard_80244774 | 7864 |
| TWindowSubTradeMain_80330A84 | 5828 |
| TKeyBoardControl_80131C58 | 3284 |
| TWindowMainMenu | 1468 |
| TWindowSubComCard_80271E7C | 13404 |
| TWindowSubMag | 3716 |
| TWindowSubShortMail_80131998 | 196 |
| TWindowCtrl_8024B7D4 | 2020 |
| TWindowCtrl_8024D960 | 2084 |
| text_80263A20 | 144 |
| TWindowSubShortMail_8027E620 | 5828 |

The four relevant bodies independently match original at 140, 56, 92 and 104
bytes. The capacity-gated full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr` passes against the
published fc54 baseline with three catalog renames and zero metric or coverage
delta, and against the separately built main4bec baseline with no regression.
Retention is clean at 17,895 and the port inventory passes.

No class layout, virtual slot, compiler control, source selection, split,
data/table provider, original remainder or ABI binding changes. Totals remain
27,406 exact functions, 3,587 exact linked units and 3,641 source-bearing units.
Raw Base/Addition calls remain 22 across twelve units and four bindings.
All remaining lifetime, record, capacity, CMName, constant and ownership holds
remain. The nameplate's 800-byte reconstruction still has 139 differing words
and retains its original provider. The PR remains draft.
