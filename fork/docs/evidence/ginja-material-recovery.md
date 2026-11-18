# Ginja material unit recovery

Initial recovery base: fork `main` `e65f11ce6ec99c006909422f81da1c0a46ac062e`.
Final integration base: `0a85a72c1c09598512363e6d375616ebd1d1b63e`, built
unchanged in this worktree before rebasing the recovery.
Unit: `pso/system/GinjaMaterial.cpp`, `.text` at
`0x803DB470..0x803DC82C` (5,052 bytes). The missing function was
`apply_ginja_material_params` at `0x803DBE1C..0x803DC3BC` (1,440 bytes).
The other 23 functions were already exact.

## Dispatcher and interfaces

The dispatcher walks eight-byte `GinjaParameter` records, updates the cached
value/dirty mask, and calls the parameter-kind table only when the combined
change mask is nonzero. It then selects blending, depth and alpha-test state,
including the primary/secondary draw-list rejection bit. Its original
returns carry no result. The declaration is now `void`, and the record's
previously opaque parameter pointer uses the existing `GinjaParameter` type.
The record layout and all table entries retain their original sizes and order.

The eleven-entry callback table at `0x804FC540` contains ten functions and a
null slot at kind 3. Kind 1 takes one signed word, kind 2 takes two signed
words, and the other populated entries take one unsigned word. The native
indirect call always supplies value/changed in r3/r4. The MWCC branch preserves
that heterogeneous ABI; it is not a portable compatible-function-type call.
On other compilers `GinjaParameterHandler.h` stores erased function pointers
and restores the entry's actual signature before invocation. The host test
covers all ten populated slots with ordinary and negative signed values.
It checks the callback boundary, not GameCube structure layouts or GX behavior.
Input kind validation and the null slot retain the original caller contract.

`draw_ginja_model_lists` no longer invents integer results from void material
and vertex-array calls. Its shared `ModelDrawCallback` interface still returns
an integer: the original normal path sets zero, while the draw-flags bit-2
path leaves the return register unspecified. Ginja callers discard it; other
users of the shared callback interface can consume their own targets' results
(see [the callback evidence](motion-draw-callback-evidence.md)). The native
fallthrough preserves those bytes; ports return zero. The pre-existing
`load_ginja_model_matrices` non-void fallthrough also has a portable zero return.
This does not claim a fully recovered common draw-callback interface.

## Matching the final register difference

The unit retains its GC/2.6 middleware flags (`-O3,p`, `-inline off`,
`-opt nopeephole`) and existing scheduling setting. A scoped
`use_lmw_stmw off` on the new dispatcher selects the original `_savegpr_26` /
`_restgpr_26` prologue and epilogue.

After recovering the control flow and prologue, the C++ had all 360
instructions in order, but
exchanged r26/r27 at eight operands in the parameter loop. A named surface
pointer was allocated after the hoisted callback-table address. A passive
trace of the stock compiler's register allocation showed the table taking
r27 before the surface forced allocation of r26. The parameter cursor then
took r26. The original instead uses table r26, cursor r27 and count r28.

The final source binds `const u32 &format` directly to the selected surface's
format field. This keeps the surface address across `GXSetZCompLoc(0)` and
reads the format afterward, exactly as the original does. The compiler's
address expression now has the temporary lifetime needed for the original
allocation. No extra loads, stores, arithmetic, or instructions are emitted.
A plain surface pointer leaves eight register differences; a reference to the
texture's *surface-pointer field* fixes the loop but incorrectly postpones
the surface load until after the GX call. The format-field reference preserves
both the load timing and every register operand.

The investigation followed the repository's
[expression/lifetime example](information-str-recovery.md),
[allocation analysis](cast-technique-6x47-register-allocation.md), and
[optimizer-switch investigation](pack-movie-frame-unit-flags.md).
The allocator was inspected in
[doldecomp/mweppc](https://github.com/doldecomp/mweppc), `Coloring.c`;
no code from that project was incorporated. Declaration permutations,
C-compatible forms, equivalent masks, inline helpers, and stock compiler
versions were measured before selecting the field reference. The shipped
compiler is unmodified and the unit has no new compiler-command override.

## Constant ownership

The four-byte RGBA fallback at `0x805E0F68` is `(0, 0, 0, 127)` and is read
by `set_ginja_material_color` in this unit. Its previously unclaimed range is
now owned by the unit. It must precede the float pool so `.sdata2` starts at
the original eight-byte-aligned address. A guarded MWCC section attribute
places this aggregate in `.sdata2` instead of `.sdata`. Its definition follows
the material-color function (preserving the named load) and precedes the
dispatcher (preserving literal-pool order). Defining it at the end of the file
preserves size and alignment but puts it after the four floats and fails data
and relocation comparison. The final section is 20 bytes at
`0x805E0F68..0x805E0F7C`; `.data` contains 296 bytes.

The unit's four scalar literals at `0x805E0F6C`, `0x805E0F70`, `0x805E0F74`,
and `0x805E0F78` are 1.0, 0.0, -0.5 and 0.5. They become local compiler-pool
symbols. A consumer census over the fresh active build inventory (8,579
objects) found no external undefined reference to any of those four names.
The last scalar owns four bytes; the following four zero bytes at
`0x805E0F7C..0x805E0F80` are alignment before the next unit's eight-byte-aligned
constants, not part of the 0.5 scalar. The split ends at `0x805E0F7C`.
No game asset data or synthetic padding was added to source.

The unit still contains previously recovered raw GX declarations, bounded
layout views, legacy callback casts and optimizer pragmas. Source linking does
not resolve those older interfaces; porting work should consolidate them
against the target GX implementation. The new native callback exception,
format-field lifetime, and portable return handling are recorded in the
[porting register](../porting-exceptions.md).

## Final validation

The unchanged integration base and the completed branch both rebuild the
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` with the pinned
native toolchain. The link edge for `build/GPOE8P/psov3.elf` takes
`build/GPOE8P/src/pso/system/GinjaMaterial.o`. The complete unit has 24/24
exact functions, 5,052/5,052 code bytes and 316/316 data bytes.

`python3 tools/check_pr.py` passes against the locally built integration base:

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,433 | 27,434 | 1 |
| Matched code bytes | 4,230,364 | 4,231,804 | 1,440 |
| Matched data bytes | 1,476,979 | 1,476,999 | 20 |
| Source-linked code bytes | 3,834,576 | 3,839,628 | 5,052 |
| Source-linked data bytes | 1,199,511 | 1,199,827 | 316 |

All 3,602 linked units remain exact. The retention update adds 27 names and
removes none; the final force-active check has zero additions/removals.
The only lost coverage is the four verified zero alignment bytes described
above. `make -C ports/tests run`, `make -C ports/tests sanitize`, the generated
exceptions-inventory check and `git diff --check` pass. The merged host suite
includes the existing vector, item-factory and loader tests as well as the new
Ginja callback test.
