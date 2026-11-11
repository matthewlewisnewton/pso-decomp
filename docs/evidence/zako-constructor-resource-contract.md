# Zako constructor and resource initialization

## Scope and dependency

This bounded extraction from PR #303 at
`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98` is stacked on BML PR #436,
`ee2d8660d3719234fb3cbd34b05757f550a7f717`, whose fork-main base is
`cda82a7aad7de1bf9b86470002df3f68d1c8c039`. It depends on that PR's canonical
`get_bml_model(BmlResource *, s32) -> NJS_OBJECT *` contract. Do not describe the
combined stack as an independent main-based Zako change.

This change recovers the constructor and resource initializer only. The proposed
full unit fold remains held for the material-call contract described below. Both
existing Zako fragments, their split ranges, linker providers and compiler
profiles remain in place. Networking, character-load and runtime/data work from
#303 is excluded.

## Constructor and caller

The factory at `0x8030A83C` allocates `0x1C` bytes using `TObject::operator new`,
tests the allocation result, then invokes the constructor at `0x8030A96C` with
`this` in r3 and the original parent in r4. The `new TBoss4ZakoDraw(parent)`
expression retains those 72 bytes, including the null-allocation branch.

The constructor is `TBoss4ZakoDraw(TObject *parent) : TObject(parent)`. Its 68
bytes call the real base constructor, set the compiler-generated vtable and copy
the class-name pointer to the inherited name member. This replaces the old
hand-written vtable/offset writes and the misleading `Fv` export spelling. The
metadata rename is limited to
`__ct__14TBoss4ZakoDrawFv -> __ct__14TBoss4ZakoDrawFP7TObject` at the same address.
The existing class virtual-slot order is unchanged.

`TOBJECT_OUT_OF_LINE_HELPERS` selects the repository's existing out-of-line
helper declarations before including the class header. It does not change
compiler flags or add a pragma. No new assembly, compiler profile, or porting
exception is introduced.

## Resource fields and preserved behavior

The 100-byte initializer at `0x8030AD58` takes BML model index 8, follows the
`NJS_OBJECT::child` field at native offset `0x2C`, clears bit 1 of its `evalflags`
and reads its `model` field at offset 4. The shared Ninja declaration expresses
those existing loads and stores without integer/pointer offset overlays.

The texture getter still returns `s32`; its explicit conversion to
`GinjaTextureList *` is a retained 32-bit native boundary, not a portable getter
contract. This change does not claim that all external model and texture globals
have canonical declarations. The child must exist. No new null check is added.
If the child's model is null, the previous chunk-model pointer and rotation phase
remain unchanged and the buffer-reset function is not called. The texture list
is still assigned and the child's flag bit is still cleared in that case.

The original-free host test extracts the checked-in initializer body and checks
both model-present and null-model cases with allocated fixture objects. It uses
only a zero texture handle and stubs the buffer-reset call. It tests control flow
and field updates, not native offsets, constructor ABI, renderer behavior,
invalid-resource handling, or a 64-bit port of the integer texture getter.

## Why the full fold is held

The frozen #303 fold changes the shadow renderer's incompatible function-pointer
cast into a direct six-argument declaration/call of
`set_chunk_material_override_pair`. The actual definition in
`ChunkMaterialState.cpp` and its shared header accept only two `s32` arguments,
which become the AND and OR masks. The additional four values in the proposed
call force outgoing register allocation; the callee does not consume them.

A private reproduction of the full fold passed native DOL and no-loss checks.
Changing only this declaration/call to the evidence-backed two-argument contract
kept the shadow function at 408 bytes but changed r5/r6/r7 assignments and reduced
its objdiff score to 99.65686%; the DOL checksum failed. This does not justify an
invented prototype, further casts, compensating source forms or new compiler
steering. The full fold and its migration from scoped `fp_contract` pragmas to a
unit override are therefore deferred. This narrower change leaves the existing
renderer body and pragmas byte-for-byte unchanged and makes no claim to resolve
that pre-existing source defect.

## Provenance

The constructor/resource work was authored by Matthew Newton with Cursor
co-authorship in #303, including `dca8232aa48915cc8837398272cc0b244745051d` and
`d116a606e614be50d1b62714a197891508a13889` (Falz model typing), and is adapted here without the coupled network
changes or held fold. The BML prerequisite preserves the separate canonical-call
work and its attribution. Existing notices remain intact.

## Validation boundary

The immutable BML base and its cda82a7a main baseline are authenticated by their
clean commits, original input hashes, pinned tool hashes and complete active
source/original-object inventories. The candidate is built in a separate checkout
through the shared native build-capacity gate. Compare both the incremental Zako
change and the combined BML/Zako tree by original address and complete object
sections/relocations, not merely by final DOL checksum. Exact-head results and any
subsequent base refresh are recorded in the PR description.
