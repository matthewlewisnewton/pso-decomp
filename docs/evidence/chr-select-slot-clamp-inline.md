# Character-select slot clamp (`sub_802C5F1C`)

`TAdMultiPlyChrSelectGC__sub_802C5F1C` (`0x802C5F1C`, 236 bytes) fills a 4×3
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
