# Hard keyboard state helpers and composer forwarding

This follows PR #268 checkpoint `ac3722fcd5a7f0d0c3ab5324219d2eb8a94ba936`.
Two historical C helpers now define nonvirtual void members of their proven
`TWindowKeyBoardHard` owner. Their names describe the bounded operations below;
they do not establish a complete input-state or ownership model.

## Receivers and exact state operations

All-section original-object inspection finds six direct zero-addend calls to
the 24-byte helper at 8025EC04 and four to the 104-byte helper at 8025FF8C.
There is no address-taking or other-section reference to either helper.

`reset_input_state()` at 8025EC04 unconditionally clears word 0x68 and sets
word 0x60 mask 0x100. Two calls receive Control's field 0x24 and four receive
Chat's field 0x28, both populated by the recovered native Hard constructor.
The existing lack of a child-null guard at these callers remains unchanged.
The false Control C declaration and its duplicate wrapper header are removed.

`reset_composer_input_flags()` at 8025FF8C does nothing if borrowed composer
field 0x70 is null. Otherwise it sets word 0x60 mask 0x40, calls the composer's
native `set_input_flags_12()` (assigning word 0xB4 value 0x12), then assigns
Hard word 0x6C value 7 only for German, French or Spanish. Japanese, English
and unknown language values leave word 0x6C unchanged. The language read stays
after the composer call. One call receives Control's Hard child at 0x24; the
other three come from the existing Hard LED helpers on their own receiver.
The old void-pointer alias and duplicate wrapper header are removed.

Neither helper allocates, frees or changes a child pointer. Word access widths,
null behavior, call order and surrounding state transitions are retained. No
new meaning is assigned to the masks, language values or borrowed pointer.
The separate language-derived flag helper at 8025CC48, no-argument key query,
Soft interfaces and holder records remain unchanged and qualified.

## Complete-object and executable validation

The first ordinary native-owner probe preserves both recovered bodies at
24 and 104 bytes and all four complete texts:

| Unit | Text bytes |
| --- | ---: |
| TKeyBoardControl_8025EC04 | 5000 |
| TKeyBoardControl_80131C58 | 3284 |
| TWindowChat | 3808 |
| text_8025FF8C | 104 |

Every resolved text relocation target matches original. All allocated section
headers, flags, sizes, alignment, data/constants and resolved text/data targets
remain unchanged from ac372. Each source object is selected exactly once.
There is no layout, virtual slot, table/data provider, source selection, split,
compiler control, original remainder or ABI binding change.

The capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr` passes against published
ac372 with two catalog renames and zero metric or coverage delta, and against
separately built main `4bec40d6cca74a85e91c848ea2d9f25425a313ad` without
regression. Retention is clean at 17,895 and the port inventory passes.
Totals remain 27,406 exact functions, 3,587 exact linked units and 3,641
source-bearing units.

All Hard destruction/table, Soft, record, capacity, CMName, lifetime, constant
and ownership holds persist. Raw Base/Addition calls remain 22 across twelve
units and four bindings. The nameplate remains nonexact by 139 words with its
original provider selected; the protected original remainders are unchanged.
The PR remains draft, with no coverage or source-activation gain for this family.
