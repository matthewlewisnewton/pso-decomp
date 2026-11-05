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

## Flag

The clamp is `static inline clamped_slot_802C5F1C` (placeholder; it has no
symbol). Under `-inline on` the clamp locals are temporaries created before
the hoisted row, so the row stays in `r8` and the cell in `r7`. The helper
is not emitted out of line.

The cell stores are written directly. `a` is the slot scale, used for `v0`
and again in the `v1` sum. Both products are divisions by `256.0f`:

```
v0 = a / 256.0f;
v1 = (lbl_805DE588 + a) / 256.0f;
```

`TAdMultiPlyChrSelectGC__data_805DE584` is exactly `1/256` (`0x3b800000`).
Division is not commutative, so MWCC does not swap the operands, and the
backend folds `/ 256.0f` into `fmuls` by that pooled reciprocal with the
dividend still on the left (`fmuls f2,f0,f3` for `v0`, `fmuls f0,f0,f3` for
`v1`). Objdiff scores the function 100% (236 bytes).

A multiply by the named scale does not. `optimizecomm` swaps a commutative
operator when the left tree costs more than the right. The sum is an add
(cost 2) and the scale is a load (cost 1), so `(lbl + a) * scale` is parsed
as `scale * sum` and emits `fmuls f0,f3,f0` (99.830505%). Writing
`scale * (lbl + a)`, `+scale`, `(0.f, scale)`, or `scale + 0.f` does the
same. A named sum (`b = lbl + a; v1 = b * scale`) costs 1 on the left and
matches, including `fmuls f0,f0,f3`, but that name is used once, so it is
not in the source. Reusing `a` for the sum keeps the sum on the left and
moves every prologue load (11 mismatched instructions).

The literals this file already uses (`0.5f`, `255.0f`, `-206.0f`, then the
zero, `0.54f`, `1/6`, `1.0f`, `16.0f`, and `0.53f` that the other functions
load) are emitted in that order, and the reciprocal is appended. That is
the DOL's `.sdata2` from `0x805DE560` through `0x805DE588`, so the split
covers that range. The zero tables defined in this file run from
`0x804E0A48` through `0x804E0B00`; the `.data` split covers them. With both
ranges claimed, every compiled function in the unit is exact and both
sections match. Claiming only the old 12-byte `.sdata2` leaves the new
pool outside the original object, and the float relocs no longer match.

The unit's `configure.py` entry replaces `-inline off` with `-inline on`.
Retested on this source:

| Flag | `sub_802C5F1C` | Other functions that were already exact | Kept |
|---|---|---|---|
| `-inline off` | real call, 332 bytes, 42.79518% | the extra `clamped_slot_802C5F1C` symbol is emitted | no |
| `-inline auto` | 99.830505% (236) on the multiply form; not retested after the division | `update` 108→572, `update_option_cursor` 476→700, `handle_dpad_input` 564→788 | no |
| `-inline on` | 100% (236) | the other compiled functions stay exact | yes |

`-inline all`, `-inline deferred`, `-inline noauto`, and `-inline auto,deferred`
were measured on the previous body. `all` and `auto,deferred` inline the same
extra functions as `auto`. `deferred` reverses emission order. `noauto`
matched `-inline on`. They are not used on this source.

`-inline auto` is the smaller request in other projects. On this source it
leaves the commuted `fmuls` and inlines functions that are not marked
`inline`. `-inline on` inlines only the helper. Nothing else in this file
is marked `inline`. Precedent for that switch:
<https://github.com/doldecomp/brawl/blob/5efd9ce/configure.py#L264>.
The `auto` spelling that was tried first:
<https://github.com/encounter/dtk-template/blob/d366876/configure.py#L203>.

## Return value

The function's last instruction is `addi r1, r1, 0x10` / `blr`. It never
writes `r3`. The callers do not read `r3`, so the return type is `void`.
Both compiled callers still pass the old `f1C` in `r4`. The body does not
read that argument. `TAdMultiPlyChrSelectGC` stays `0xA0` bytes, and
`get_or_create` is `new TAdMultiPlyChrSelectGC`, which is `li r3, 160` /
`bl __nw__7TObjectFUl`. The grid this function fills is `S_802C6008`, the
same view `update_option_cursor` already uses; `S_802C61E4` is that view
under `handle_dpad_input`'s name. The quads sit in what was padding between
`f1C` and `sel`, so those callers' offsets are unchanged.
