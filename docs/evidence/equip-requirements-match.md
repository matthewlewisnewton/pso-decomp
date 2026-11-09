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

## Validation, 2026-11-09

Fresh separate build directories were generated from checked-in splits and
symbols for both main and the refreshed PR, using GC/2.6, dtk v1.8.4,
objdiff v3.6.1 and wibo 1.0.3. No generated objects were copied between builds.

- `check_equip_requirements`: 99.260086% to 100%, 892 bytes.
- All seven functions in the unit match, 2012/2012 code bytes; `.data` matches
  88/88 bytes with `functionRelocDiffs=data_value`.
- Both full builds reproduce original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `tools/check_pr.py --no-build --baseline <fresh-main-report>` passes:
  +1 exact function, +892 matched code bytes, +88 matched data bytes,
  no function, data or linked coverage regressions. Four zero padding bytes
  at `0x8049EF54` leave report coverage; the checker accepts this padding.
- All 3570 existing linked units remain exact; force-active metadata has no
  drift. The same checks also pass on unchanged main.
- `tools/list_port_exceptions.py --check` and `git diff --check` pass.

## Remaining link limit

The unit is **not source-linked**. Its sole scanner blocker is:

```
alignment .data:0x8049EEFC needs 8-byte alignment
```

The compiler-generated jump table occupies the original 88-byte range
`0x8049EEFC..0x8049EF54`, whose start is four modulo eight. Its compiled section
requests eight-byte alignment. A perfect objdiff score does not remove that
link constraint. `linked_units.txt` stays unchanged and the generated link
inputs still use `build/GPOE8P/obj/pso/unk/text_80104FCC.o`, the original split
object. There is no gain in source-linked code or data.

Two adjacent original factory tables are a possible ownership investigation:
`item_pro_create_fn_table` at `0x8049EED8` (16 bytes), followed by
`item_create_fn_table` at `0x8049EEE8` (20 bytes), then this jump table. The two
tables are used only by this unit's factory dispatch functions. Their original
relocations identify the armor/shield/unit factories and the weapon/equipment/
mag/tool/money factories. Owning and defining both tables could establish an
aligned start, but that has not been implemented or validated. Their existing
factory APIs use different pointer signatures, and the weapon factory wrapper
still has a provisional integer boundary. Do not claim the tables or introduce
function-pointer casts solely to bypass the alignment check.

No new assembly, steering pragmas, compiler overrides, link-check exceptions or
handwritten jump tables were added. Independent review of the final pushed
head remains required before merge.
