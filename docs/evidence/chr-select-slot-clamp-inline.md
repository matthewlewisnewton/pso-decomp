# Character-select slot clamp (`sub_802C5F1C`)

`TAdMultiPlyChrSelectGC::sub_802C5F1C` (`0x802C5F1C`, 236 bytes) fills a 4×3
grid of selection quads and clamps the active player slot
(`TAdMultiPlyChrSelectGC__data_805D67D8`) to 3. The original inner loop keeps
the hoisted row (`self + i*96`) in `r8` and the cell in `r7`:

```
add   r8, r3, r4
lwz   r0, TAdMultiPlyChrSelectGC__data_805D67D8
li    r7, 3
cmpwi r0, 4
bge   ...
mr    r7, r0
xoris r0, r7, 32768
add   r7, r8, r5
```

A straight loop in the caller is the same 59 instructions with `r7` and `r8`
swapped (objdiff 99.15254%, nine argument mismatches). MWCC numbers named
locals below its own temporaries and colours the hoisted row first, so the
row takes `r7`.

## Flag that matches

The clamp is `static inline clamped_slot_802C5F1C` (placeholder; it has no
symbol). `idx` is declared before `cnt`, and the caller reads the home float
before the call. Under `-inline on` those locals are temporaries created
before the hoist, so the row lands in `r8`. The helper is not emitted
out of line. `.text` stays 6100 bytes of compiled code against the original
7288 (the two unmatched slot routines are still not in this TU).

The unit's `configure.py` entry replaces `-inline off` with `-inline on`.
Checked against the original object, instruction by instruction, and against
the data sections:

| Flag | `sub_802C5F1C` | Other functions that were already exact | Kept |
|---|---|---|---|
| `-inline off` | real call, 332 bytes | unchanged | no |
| `-inline auto` | exact | seven grow (`update` 108→572, `update_option_cursor` 476→700, `handle_dpad_input` 564→788, `sub_802C65C0` 160→212, `reset_slot_selections` 88→132, `find_active_slot` 96→148, `update_selection` 668→1300) | no |
| `-inline auto,deferred` | exact | thirteen change, including the seven above | no |
| `-inline all` (`on` + `auto`) | exact | same seven as `auto` | no |
| `-inline deferred` | each body exact | function order reversed (`update_selection` emitted first) | no |
| `-inline noauto` | exact | unchanged; object identical to `-inline on` | same result as `on` |
| `-inline on` | exact | all 32 unchanged; `.data` / `.rodata` / `.sdata2` unchanged | yes |

`-inline auto` is the smaller request in other projects, and it does make
this function exact, but it does not leave the rest of the unit identical.
`-inline on` inlines only functions marked `inline`. Nothing else in this
file is marked `inline`. Precedent for that switch:
<https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264>.
The `auto` spelling that was tried first:
<https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203>.

## Return value and the grid members

The function's last instruction is `addi r1, r1, 0x10` / `blr`. It never
writes `r3`. The three callers (`update_option_cursor` at `0x802C6028`,
`handle_dpad_input` at `0x802C6204`, and the unmatched plate constructor at
`0x802C6E6C`) do not read `r3` afterwards, so the return type is `void`.
The two compiled callers increment `m_1c` and then call. That increment is
`lwz r4, 0x1c(r3)` / `addi` / `stw` whether or not the old value is passed
as an argument, so the parameter is not part of the matched code. The
unmatched plate constructor at `0x802C6E6C` still passes the slot global in
`r4`; this body does not read it. The function takes no parameter.

The quad array and the integer fields `m_24`..`m_9c` are the same bytes at
`0x24`. `initialize_selection_state` stores integers there (`stw` to `m_34`
and the rest) and this function stores the cell texture floats (`stfs`).
Both are members of one union, and each function uses the member of the
type it stores. `cursor` is at `0x324`, `sel` at `0x4AC`, `f4DC` at `0x4DC`,
`f4EC` at `0x4EC`, `f4F8` at `0x4F8`. `update_option_cursor` and
`handle_dpad_input` use those members on `this`. The function is a member;
its symbol is `sub_802C5F1C__22TAdMultiPlyChrSelectGCFv`.

`get_or_create` still executes `li r3, 160` / `bl __nw__7TObjectFUl`. The
class is `0x530` bytes once the grid is a member, so that call passes the
literal `0xA0` and constructs with placement new. That placement
`operator new` is `inline`. `TAdMultiPlyChrSelectGC.cpp` needs `-inline on`
for the same reason as this unit: `-inline off` outlines it (`get_or_create`
26→31 instructions) and `-inline auto` also inlines `__ct` (27→62). With
`-inline on`, all 15 functions in that unit match the original object.
