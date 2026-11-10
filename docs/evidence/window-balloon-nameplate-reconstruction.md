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
middle strip is emitted only for width>20. The three U ranges are 145..161,
177..193 and 161..177, divided by256, and V spans237/256..1. Every quad is
rebuilt before context transformation and drawing, preserving the original
stored-float boundary and operation order.

Text starts six pixels into the plate, centered for widths below20, and three
pixels down. Its depth is -1/(context depth+0.07475), with the existing100000
right limit and1000000 draw-width input. The existing render-state helpers are
called in their original order; their historical names do not imply player
ownership. The no-argument render_forward call view remains a qualified legacy
boundary, not a recovered global helper interface.

The body was derived from the GameCube instructions and existing GC helper
implementations. No Dreamcast source or new compiler control is imported.

## Compilation result and arithmetic qualification

The initial compiling reconstruction was796 bytes. A source-clarity refinement
uses the original positive guard and direct quad-field construction. A proposed
new scoped fp_contract pragma was rejected during independent review and removed.
No declaration/scheduling permutations, volatile storage, artificial liveness,
new intrinsic or alternate helper binding is added to force output.

The final function compiles to800 bytes, but139 instruction words differ from
original. Differences include register/color-expression allocation and the
separate multiply/add used for centering. Equal extent is not exact matching.
There is no evidence-backed type correction currently explaining those remaining
instruction differences, so the exactness hold is explicit.

For the centering arithmetic specifically, width is converted from an unsigned
integer and width<20 restricts it to exact integers0..19. Therefore20-width and
its product with0.5 are exact; separating that product from the final addition
introduces no intermediate-rounding difference from the original fused operation.
Independent review confirms this bounded argument and the observed guards,
geometry, colors, ordering and helper operands. It does not establish complete
renderer byte/relocation equivalence or resolve the legacy render-state interface.

## Regression and selected-provider proof

The compiled unit now has10712 text bytes. All31 previously compiled functions
and all9912 prior text bytes are unchanged, including every function-relative
resolved text target. All prior allocated data/constants, headers, flags and
resolved data/constant targets remain unchanged. Its80-byte render/task jump data
and resolved destinations still match original. The new body has the same13 call
targets in the same order as original, with conditional drawing preserved.

The full original10712 text,24 rodata,188 sdata2 and80 jump-data provider remains
unchanged and selected once. Compiled Fukidasi source remains absent from the
executable inputs. Its constant sections still have external ownership/interface
qualifications; completing text extent is not a constant or source-link claim.
The separate constructor132, deleting wrapper144 and producer2356 text/targets
remain original-exact source inputs. The original84-byte prefix/class-table
provider is unchanged and selected once. No native destruction or table claim,
new gap, split, padding or source activation is introduced.

The shared-capacity full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr against4084
and comparison against separately built main1d44 both pass. Metrics remain
unchanged:27405 exact functions,3586 exact linked units and3641 source-bearing
units. Retention is clean at17886. Port inventory passes after refreshing only
line locations of four existing intrinsic entries; no exception/control is added.
Snapshot, WS_Word and protected-original checks pass again, including the1044
helper and Word's original3412 provider/missing916 renderer.

## Remaining work

Exact GC instruction/relocation matching still requires an evidenced source/type
or interface correction; register differences alone do not justify output steering.
Canonical constant ownership and complete linked validation are also required
before replacing the original provider. The prior short/word initializer ABI,
destruction/table-order, record/capacity, CMName, Parts, ChoiceSetting, task-global
and wider ownership holds persist. Raw Base/Addition calls remain22 across12
units and four shared bindings. The PR stays draft. No history rewrite or split
is part of this checkpoint.
