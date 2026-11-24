# Equipment requirement match and link limit

PR #319 recovers `check_equip_requirements` at `0x80104FCC` in
`pso/unk/text_80104FCC.cpp`. It remains relevant: fork main
`6daa19a11db97b1b8222fd2665eba485ed3a74a4` does not match this function.

## Permission argument and meseta interpretation

The weapon, armor and mag cases load their ItemPMT class permission as a
halfword and sign-extend it at the call boundary. Declare
`check_class_equip_permission`'s permission argument as `s16` consistently in
the shared header, definition and remaining local declarations, rather than
casting three individual arguments to `s16` before passing them to an `s32`
parameter. The callee still tests the same low permission bits. The compiler
emits identical instructions for the callee and existing callers, but changes
the requirement check's register allocation to the original player/item homes.

`TItemData::data2.meseta` is a signed `s32` view of the same four bytes already
available as `data_u32`. The original requirement check uses a signed compare;
`TItemMoney::amount` also stores this value as `s32`. The enum cap retains the
original cap-left comparison without converting the item amount to an enum.

This patch recovers the previously unpublished change in
`d5ce402f22ac4190ebb5c0dc6b10202d562f3db3`, after merging current fork main.
That earlier worktree withheld publication because it was behind main; those
older-base losses are absent in this refreshed validation.

## Factory ownership and alignment

The original unit's factory dispatchers are `construct_item` at `0x8010542C`
and `TLobby__sub_801054E0` at `0x801054E0`. Repository-wide references to
`item_create_fn_table` and `item_pro_create_fn_table` occur only in those
functions. The original relocation inventory places these objects consecutively:

| Address | Object | Size | Relocation targets |
|---|---|---:|---|
| `0x8049EED8` | `item_pro_create_fn_table` | 16 | null, armor, shield, unit factories |
| `0x8049EEE8` | `item_create_fn_table` | 20 | weapon, equipment, mag, tool, money factories |
| `0x8049EEFC` | generated restriction switch table | 88 | labels inside `check_equip_requirements` |

The factory target order comes from the original `.rela.data` entries, not
inferred item names. The source arrays use the existing factory declarations
and named function addresses; the restriction table is still compiler-generated.

Defining the two factory arrays before the requirement function reproduces
`.data` at offsets `0`, `0x10` and `0x24`, with total size `0x7C`. The expanded
split starts at `0x8049EED8`, which satisfies the compiled section's eight-byte
alignment. Both code and all 124 data bytes/relocations match. This replaces the
previous unlinked 88-byte slice starting four modulo eight at `0x8049EEFC`.
No synthetic prefix, handwritten jump table, alignment override or scanner
exception is used. Adjacency, exclusive users and the reproduced native layout
support this ownership; the original object-file boundaries themselves are not
available from the linked executable.

## Factory interface recovery

`ItemCreateFunction.h` shares a pointer-returning byte-buffer factory type.
The equipment dispatcher reads byte 1 of the complete item record. The weapon
wrapper now passes the item record explicitly to `get_weapon_factory_for_item`
and returns `TItem*`; its previous local declaration omitted the getter's
argument and represented both pointers as `s32`. Getter definitions and callers
now use the same shared declarations. Default weapon and tool factories return
`TItem*`, avoiding return-type function-pointer coercions. All affected compiled
units remain exact.

One native ABI boundary remains explicit: `TItemMoney::create` takes
`TItemData*`, as its original mangled name records, while the original five-entry
factory table dispatches through a byte-buffer callback. Its table initializer
therefore converts that function pointer to the common storage type. Native
MWCC/PPC invokes it with the same record address in `r3` and receives the item
pointer in `r3`. This is a target ABI dependency, not an assertion that different
C++ function types are portable call-compatible.

The non-MWCC path uses `invoke_item_factory` to convert entry 4 back to its
actual function type before calling it. The C++98 function-pointer round trip
restores the original type, so that path does not call the money function through
an incompatible signature. The shared money declaration is unchanged. This
boundary is recorded in the porting exceptions register. The port callback test
checks all four byte-buffer paths, the money path, record identity, return
identity and call counts with opaque test types; it does not claim a host build
of the complete game's native layouts.

## Validation, 2026-11-09

Main baseline: `6daa19a11db97b1b8222fd2665eba485ed3a74a4`.
Prior published PR baseline: `15802875b9d64dc36961cdc066e8faab5948549c`.
Separate build directories use the checked-in splits and symbols, GC/2.6,
dtk v1.8.4, objdiff v3.6.1 and wibo 1.0.3. No generated objects were copied
between builds.

- `check_equip_requirements`: 99.260086% to 100%, 892 bytes.
- All seven functions in the unit match, 2012/2012 code bytes; expanded `.data`
  matches 124/124 bytes with `functionRelocDiffs=data_value`.
- The source-linked build reproduces original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- Against current main: +1 exact function, +892 matched code bytes, +124 matched
  data bytes, +2012 source-linked code bytes, +124 source-linked data bytes.
- `check_pr.py` passes against both fresh baselines. Against the prior published
  PR head, matched code/functions are unchanged, matched data increases 36
  bytes, and source-linked code/data increase 2012/124 bytes; no regressions.
- All 3571 linked units are exact; force-active metadata has no drift. The three
  new retention entries are `TLobby__sub_801054E0`, `item_create_fn_table` and
  `item_pro_create_fn_table`, as generated by the link scanner.
- Four zero padding bytes at `0x8049EF54` leave report coverage; the checker
  accepts this padding. No function, data or linked coverage regresses.
- `make -C ports/tests run` and `make -C ports/tests sanitize` pass, including
  address and undefined-behavior sanitization of the callback test.
- `list_port_exceptions.py --check` and `git diff --check` pass. The mechanical
  exception inventory remains unchanged; the callback ABI has a manual entry.

The target unit is now source-linked: generated link inputs use
`build/GPOE8P/src/pso/unk/text_80104FCC.o`, not its original split object.
Independent review of the final pushed head remains required before merge.
