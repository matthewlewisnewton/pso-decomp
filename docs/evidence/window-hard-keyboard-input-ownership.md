# Hard keyboard input helper ownership

This follows PR #268 checkpoint `733f83605a6e754e3a3884173cf8bef6da6b1c70`.
Five input helpers now belong to the evidenced TWindowKeyBoardHard receiver.
Their complete text, data and relocation targets remain exact. This is an owner
and interface correction with zero match/coverage gain; it does not activate
Hard destruction or compiler-table ownership.

## Receiver and caller evidence

TKeyBoardControl is 0x2C bytes. The three enable_*_led helpers read flags at 0x60
and a borrowed composer pointer at 0x70. Original relocation inspection finds
one caller for each, in Control's constructor, passing field 0x24, whose producer
allocates the 0x74-byte Hard keyboard. These accesses fit that keyboard's
existing declaration. The helpers and all three callers now use that owner.

get_input_mode reads Hard's flags at 0x60 and has one original caller, the Hard
accent-processing method. translate_key_char likewise has one original caller,
Hard's process_key_input. It uses Hard's flags and reads the borrowed composer's
word at 0xB4, which is represented by the existing TWindowKeyBoardBase image.
All five incoming references found are direct zero-addend calls; no address-taking
or mixed receiver reference was found in the original object inventory.

Translation's old static (receiver,key,output) interface becomes a genuine Hard
member (key,output), preserving receiver/key/output ABI positions and the byte key
and halfword output types. It names the actual Hard fields and calls its existing
lookup member. The three LED helpers preserve their composer-null tests, state
flags, reset calls and subsequent update order. They do not release or acquire
ownership of the composer.

get_input_mode retains its unusual receiver-word return for unrecognized language
values. No new fallback, range validation or sentinel is substituted. Character
map decisions, result values, output writes and all call targets remain unchanged.
The generic printable-key utility and raw composer/reset/card boundaries keep
their existing contracts. The control-key member-pointer table still uses its
historical Soft view; this correction does not establish that wider dynamic type
or the remaining keyboard interfaces.

## Validation and retained tables

The complete owner5000 and Control caller3284 texts are byte-identical to captured
733f source and fresh main originals. All resolved text and data relocation
targets agree. The five helper bodies are independently exact at
1128/96/80/80/80 bytes. Existing owner data756 and caller data24, including the
descriptor, member-pointer and anonymous jump-table layout, are unchanged.
Allocated-section inventories agree with preceding source objects. Both objects
remain actual source inputs once, with their original text counterparts absent.

The original 28-byte Hard table provider remains selected once with all four
resolved targets unchanged. No compiler table is emitted by this family, and the
existing deleting wrapper, constructor and producer lifetime qualification stays
as described in the construction evidence. No split, data range, padding,
alignment override, compiler control or technical exception is introduced.

The shared-gate full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr against 733f
passes with zero metric delta and five catalog renames. Retention replaces exactly
the two get_input_mode/translate_key_char names and stays clean at 17,862 entries;
the port inventory passes unchanged. Hard construction, Snapshot, WS_Word and
protected-original provenance pass again, including the retained original
1044-byte helper and WS_Word's original3412 provider/916-byte rendering body.

Fork main remains `b2a90ff1eabedf275aaed6cc16acbbd3e8b4a36c`. Fresh-main check_pr
passes with combined +600 matched code, +1220 linked code, +1496 matched data
and +1452 linked data bytes. Totals remain 27,397 exact functions, 3,587 exact
linked units and 3,649 source-bearing units. Raw Base/Addition calls remain 22
across 12 units. All destruction/table, capture, renderer, ownership, constant
and wider interface holds remain; PR stays draft.
