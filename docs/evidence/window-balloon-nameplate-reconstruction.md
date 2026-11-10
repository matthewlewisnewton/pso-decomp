# Balloon name-plate reconstruction: exactness hold retained

This follows PR #268 checkpoint `408486a9dd82f700bf43cc79cb35663df63b9964`.
The formerly absent 800-byte name-plate renderer has a GameCube-derived source
implementation. The implementation is independently reviewed against the original
instructions, but it is not byte-exact and is not an executable source input.
All existing ABI, constant, destruction/table-order and ownership holds remain.

## Original owner and inputs

Original all-section references identify one direct call from balloon render,
passing the balloon in r3, draw context in r4 and packed color in r5. No
address-taking was found. The receiver is the established 0x98 TUnk_804CF0B8
image, with its existing owned char* name at 0x78. The context fields at 0/4,
0x30 and 0x38 agree with the established TWindowDrawContext definition and its
layout assertions. The new nonvirtual member is draw_name_plate(context, color);
the false no-argument Fukidasi label/prototype is removed. No field, object
layout, lifetime or ownership is invented by that receiver correction.

The renderer reads the existing name without acquiring/releasing it. It skips
all drawing when name is null or signed context open_tick is negative. Width
uses the original unsigned word-to-float conversion of get_name_text_width's
result. Alpha is 255 at ticks >=6; otherwise integer tick*255 is multiplied by
the observed 1/6 float and truncated before being shifted into the high byte.
Plate color retains the input RGB; text uses alpha-only black.

## Reconstructed drawing operations

The plate starts at context x-11/y-10, at depth -1/(context depth+0.0598).
It draws two 16x19 endcaps. The right cap starts at x+max(width,20)-4; the
middle strip is emitted only for width > 20. The three U ranges are 145..161,
177..193 and 161..177, divided by 256, and V spans 237/256..1. Every quad is
rebuilt before context transformation and drawing, preserving the original
stored-float boundary and operation order.

Text starts six pixels into the plate, centered for widths below 20, and three
pixels down. Its depth is -1/(context depth+0.07475), with the existing 100000
right limit and 1000000 draw-width input. The existing render-state helpers are
called in their original order; their historical names do not imply player
ownership. The no-argument render_forward call view remains a qualified legacy
boundary, not a recovered global helper interface.

The body was derived from the GameCube instructions and existing GC helper
implementations. No Dreamcast source or new compiler control is imported.

## Compilation result and arithmetic qualification

The initial compiling reconstruction was 796 bytes. A source-clarity refinement
uses the original positive guard and direct quad-field construction. A proposed
new scoped fp_contract pragma was rejected during independent review and removed.
No declaration/scheduling permutations, volatile storage, artificial liveness,
new intrinsic or alternate helper binding is added to force output.

The final function compiles to 800 bytes, but 139 instruction words differ from
original. Differences include register/color-expression allocation and the
separate multiply/add used for centering. Equal extent is not exact matching.
There is no evidence-backed type correction currently explaining those remaining
instruction differences, so the exactness hold is explicit.

For the centering arithmetic specifically, width is converted from an unsigned
integer and width < 20 restricts it to exact integers 0..19. Therefore 20-width and
its product with 0.5 are exact; separating that product from the final addition
introduces no intermediate-rounding difference from the original fused operation.
Independent review confirms this bounded argument and the observed guards,
geometry, colors, ordering and helper operands. It does not establish complete
renderer byte/relocation equivalence or resolve the legacy render-state interface.

## Regression and selected-provider proof

The compiled unit now has 10,712 text bytes. All 31 previously compiled functions
and all 9,912 prior text bytes are unchanged, including every function-relative
resolved text target. All prior allocated data/constants, headers, flags and
resolved data/constant targets remain unchanged. Its 80-byte render/task jump data
and resolved destinations still match original. The new body has the same 13 call
targets in the same order as original, with conditional drawing preserved.

The unchanged original provider contains 10,712 text bytes, 24 rodata bytes,
188 sdata2 bytes and 80 jump-data bytes, and remains selected once. Compiled
Fukidasi source remains absent from executable inputs. Compiled rodata remains
16 bytes versus original 24, and compiled sdata2 remains 36 versus original 188. External constant references and ownership remain qualified;
completing text extent is not a constant or source-link claim.
The separate constructor 132, deleting wrapper 144 and producer 2356 text/targets
remain original-exact source inputs. The original 84-byte prefix/class-table
provider is unchanged and selected once. No native destruction or table claim,
new gap, split, padding or source activation is introduced.

The shared-capacity full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr against 4084
and comparison against separately built main 1d44 both pass. Before final main
integration below, metrics remained unchanged: 27,405 exact functions, 3,586 exact
linked units and 3,641 source-bearing units. Retention was clean at 17,886. Port
inventory passes after refreshing only line locations of four existing intrinsic entries; no exception/control is added.
Snapshot, WS_Word and protected-original checks pass again, including the 1,044-byte
helper and Word's original 3,412-byte provider/missing 916-byte renderer.

## Remaining work

Exact GC instruction/relocation matching still requires an evidenced source/type
or interface correction; register differences alone do not justify output steering.
Canonical constant ownership and complete linked validation are also required
before replacing the original provider. The prior short/word initializer ABI,
destruction/table-order, record/capacity, CMName, Parts, ChoiceSetting, task-global
and wider ownership holds persist. Raw Base/Addition calls remain 22 across 12
units and four shared bindings. The PR stays draft. No history rewrite or split
is part of this checkpoint.


## Final current-main integration

Main `4bec40d6cca74a85e91c848ea2d9f25425a313ad` is integrated by merge
`5b17fbc5ecb248c30e844ca91f982bff4cdb62f6`. The download-graph recovery merges
without conflict; its own compiler/port qualifications are preserved separately
from this renderer, which introduces no new control.

Fresh main and integrated full builds both preserve the original DOL hash.
Renderer/provider, constructor/deleting/producer, original table, Snapshot,
WS_Word and protected-original checks pass again. Retention is clean at 17,739
on fresh main and 17,895 on the branch; current port inventory passes. Incremental
and fresh-main check_pr both pass.

Main contributes +380 matched code, +1992 linked code and +136 matched/linked
data bytes, one exact function and one linked unit. Those gains belong to main;
the renderer reconstruction itself remains zero metric delta and non-exact.
Current totals are 27,406 exact functions, 3,587 exact linked units and 3,641
source-bearing units. Combined PR deltas versus fresh main remain +600 matched
code, +1220 linked code, +1496 matched data and +1452 linked data bytes. All
fourteen qualified alignment gaps and remaining technical holds are unchanged.


The later [shared state/reset recovery](window-render-state-reset-contracts.md) establishes consistent no-argument begin/forward state helpers across the active callers. It supersedes that input-contract qualification only; historical ownership, the other state helpers, all 139 differing words and the original provider remain held.
