# Crush-rock render and physics unit

Base: fork main `34742a01fa18f1df3b4d838871297333cc8d1c76`.

`pso/boss/TBoss6CrushRock_80359FEC.cpp` already source-linked its two
functions, totaling 352 code bytes. Its four physics constants were still
in the original-only `auto_11_805E00B8_sdata2` object. This recovery absorbs
that entire 16-byte range into the existing unit; it does not change the
separate constructor/destructor unit or establish an original filename.

## Layout and behavior

The constructor at `0x8035A1A4` writes a model pointer at `+0x1C`, texture
list at `+0x20`, position at `+0x24`, velocity at `+0x30`, three integer
angles at `+0x3C`, and angular velocity at `+0x48`. Its factory allocates
`0x54` bytes. The render/update assembly independently reads those same
fields. The shared class now records that layout with size/offset checks;
the model remains opaque at this interface.

`run_task` at `0x8035A064` queues destruction when the existing boss-alive
predicate fails. Otherwise it advances angles, adds `-0.25f` to vertical
velocity, and adds velocity to position. Below the zero-height floor it
clamps height, scales horizontal velocity by `0.25f`, scales vertical
velocity by `-0.25f`, and queues destruction when `vector_length` returns
less than `0.1f`. The existing approximate length helper is unchanged.
The existing predicate name is retained rather than assigning it a new
owner or meaning.

## Compiler comparisons

Both a C-compatible record implementation and the typed C++ member
implementation emit the same 352 instruction bytes and a 16-byte literal
pool ordered `-0.25`, `0`, `0.25`, `0.1`. Against the old code-only split,
render scores 100% and update 99.56896%; the only remaining differences
are the five SDA21 references into the newly emitted pool.

After that comparison, the
[laser-light pool](laser-light-constant-pool.md),
[vertex-color cache pool](chunk-vertex-color-cache-pool.md), and
[conversion-pool investigation](conversion-pool-constants.md) supplied
comparable ownership and emission cases. Additional probes found:

- Removing the inherited `opt_common_subs off` region preserves all
  allocated bytes and relocations of the literal implementation.
- Initializing the old named constants before their uses folds them into
  literals, but changes floating-point register choices in the old raw
  access implementation.
- Defining the old named constants after their uses keeps a 100% code
  score but emits their 16 bytes in `.sdata`, rather than `.sdata2`.

Ordinary literals without a pragma are the final source form. A fresh
inventory of 8,559 configured original/compiled objects finds only this
unit referring to the four old split symbols. Together with native pool
emission, that supports claiming exactly `0x805E00B8..0x805E00C8` and
marking the four symbols local through `localize_split_globals.py`.

## Validation

The unchanged base was rebuilt with fresh split objects and its generated
retention check passed before edits. The completed object has exact
`.text` (352 bytes, alignment 4) and `.sdata2` (16 bytes, alignment 8).
Its 19 allocated relocation tuples agree after normalizing defined local
symbols to section offsets. The actual linker input selects the compiled
rock object, and the original-only constant object disappears.

The native rebuild retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py` passes
against the clean base: matched and linked data each increase by 16 bytes,
with no exact-function, code, data-coverage or linked-unit loss. Both
functions remain exact; the gain is data ownership and source linkage.
Generated retention metadata is unchanged. The porting inventory records
removal of the now-unnecessary pragma; no new compiler exception is added.
