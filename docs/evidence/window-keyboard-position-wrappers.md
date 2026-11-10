# Keyboard Control position wrapper contracts

This follows PR #268 checkpoint `79e89ce7345edcc1bf7472675c68fb569f347802`.
Four position helpers now have their evidenced TKeyBoardControl owner and native
Base position-saving calls. The two composer variants remain distinct, the
separate legacy text getter stays qualified, and no child lifetime or data
ownership is inferred from this recovery.

## Four distinct operations and their callers

Original all-section relocation inspection finds direct zero-addend references
and no address-taking for these four helpers. Producer chains allocate 0x2C and
initialize TKeyBoardControl; fields 0x20/0x24/0x28 hold composer/Hard/Soft children.
The corrected contracts preserve those actual receivers and borrowed input pairs:

- set_position at 80131AA4 has six calls on the SubComCard/ShortMail controller
  paths. It writes composer x/y with the original -4/-10 adjustments and stores
  word 0x50=3. It does not save position. No further meaning is assigned to that
  word by this recovery.
- set_soft_keyboard_position at 80131ADC has two calls, Quest and CMName. It
  forwards the input x/y to the Soft child's known Base prefix and saves position.
  This does not establish the complete Soft class or its native lifetime.
- set_hard_keyboard_position at 80131B18 has two calls, Quest and JoinLobby.
  It writes the Hard child's x/y and saves position. Both original callers ignore
  the result, so its void interface replaces JoinLobby's old integer-return view.
- set_composer_position at 80131B54 has eleven calls across the keyboard producers.
  It retains the same -4/-10 adjustments and immediately saves position. It is
  deliberately separate from the word-0x50 variant above.

All 21 known source calls now use those actual members. The obsolete free-function
header is removed after migrating every include/call. Base save_position already
has a void, receiver-only contract and copies 0x30..0x3C to 0x40..0x4C. The native
composer call replaces its old phantom integer/float arguments without changing
instructions. No artificial scratch arguments, cached scheduling variables or
compiler controls are introduced.

Input access order, child reloads, margins, word/float widths and original null/
allocation-failure behavior remain unchanged. No input pair or child is acquired
or released. The adjacent 36-byte get_keyboard_field_6c helper and its broader
text/return views remain untouched and held. Other outer wrapper, callback,
renderer and lifetime interfaces are outside this claim.

## Exact objects and held CMName source

The owner's entire 288-byte text and eight-byte local float pool match original
and captured 79e89 objects. The four bodies independently match at 56/60/60/76
bytes; the separate getter's 36 bytes are unchanged. No table is emitted.

Nine actual source inputs are selected once. Whole text bytes and resolved text
targets match preceding source and main originals: owner288, Quest7064, serial1512, ShortMail5828,
SubComCard13404, MakeTeam1188, InformationBoard408, SubSymbolChat8084 and
JoinLobby23052. Allocated flags, data, constants and anonymous jump layouts are
unchanged from preceding source, including JoinLobby's pre-existing writable-rodata
representation. Resolved data/constant targets also remain unchanged.

CMName remains a held source unit. Its complete compiled15504 text, all compiled
relocations and allocated sections are unchanged from captured source; its
original17988 provider stays selected once and compiled source is absent from
executable inputs. The changed run_task's 556 instruction bytes and all call
relocations, including the two position calls, match original. Eight pre-existing
SDA21 constant-target differences remain, alongside unrecovered code. No source
activation, constant ownership or complete object equivalence is claimed there.

## Validation and current main integration

Implementation `9559332e264b58665ff1f9b9e23e4e684daafa46` passes incremental check_pr against 79e89 with zero
metric delta and four catalog renames. The shared-gate full build retains DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Retention remains clean at
17,870 before main integration and port inventory passes unchanged. No data claim,
split, alignment, padding, source activation or technical exception is introduced.

Main `4ae3511286473eb94ba91236c37e94f7b0475109` is integrated by merge
`52e732433987268618cef48dee5d8a16e4612378`. Four addition-only retention conflicts
are resolved by preserving both this branch's recovered window symbols and main's
new character-plate symbols. Fresh-object retention verification passes afterward:
main17726 and branch17882. No branch-specific retention removal or unrelated
normalization is added.

Both isolated builds preserve the original DOL hash. check_pr against published
79e89 and freshly built main4ae passes. Main contributes +724 matched code, +836
linked code, +52 matched/linked data bytes and three exact functions. Its source
inventory decreases by one while linked units increase by one. Those gains/folds
are attributed to main; this position family remains zero delta.

Current totals are 27,403 exact functions, 3,585 exact linked units and 3,642
source-bearing units. Combined PR deltas versus fresh main remain +600 matched
code, +1220 linked code, +1496 matched data and +1452 linked data bytes. Prior
depth/status, Snapshot, WS_Word and protected-original checks pass again, including
the original1044 helper and WS_Word's original3412 provider/missing916 renderer.
Raw Base/Addition calls remain 22 across 12 units. All remaining documented holds
remain; PR stays draft.
