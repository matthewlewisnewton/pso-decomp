# Viewport/scissor interface contract

## Scope

This is an interface-only extraction from the remaining Zako work in #303.
The implementation stays in `pso/misc/TLobby_801E2F94.cpp`, and the Zako caller
stays in `pso/boss/TBoss4ZakoDraw_8030A96C.cpp`. Neither Zako unit is folded.
No buffer, global layout, material-state transaction, compiler profile, pragma,
symbol metadata, split or linker-provider change is part of this repair.

The shared interface is:

    static void TCameraCtrl::set_viewport_scissor(int mode, void *rect);

The definition uses the existing private `Rect_801E317C` view of the pointer.
The pointer remains opaque at the shared boundary. This does not assert a new
canonical type for the camera's complete global state, narrow ownership, change
constness, or introduce a receiver or wrapper.

The previous declarations disagreed about both result and input types. Zako
passed the rectangle address through an int; the camera private header and
Zako declared an integer result that no caller used. The provider used a local
rectangle-pointer type and s32 mode, while other declarations used int/void*.
Here s32 is signed long, so int and s32 are distinct source types even though
both are 32-bit under the native compiler.

## Original caller and callee evidence

The 348-byte provider at `801E317C` compares incoming r3 with 2. Mode 2 reads four
floats at offsets 0, 4, 8 and 12 through r4 and computes the arguments to
GXSetScissor. Other modes do not read the rectangle and request 0,0,640,480.
There is no instance-object access or consumed hidden receiver.

The complete original reference audit found one provider and three text-section
REL24 references with addend zero, agreeing with an independent original-DOL
direct/conditional branch scan:

- `80068518`, post_update_view__13TUnk_80488A28Fv: mode 2, address of
  TCameraCtrl__data_804FF634 plus 0x30.
- `8006958C`, reset_viewport_scissor__11TCameraCtrlFv: mode 0, address of its
  existing four-word stack copy. That initialization is preserved even though
  the mode-0 provider does not read it.
- `8030AC40`, TCameraCtrl__sub_8030ABF4: mode 2, address of
  TCameraCtrl__data_804FF634 plus 0x30, on the existing non-split-screen path.

None consumes a result. The first two enter their epilogues; Zako makes its next
call without reading a result. There are no other symbol relocations, external
branches into the provider's interior, or aligned data pointers into its extent.
This is static reference closure, not proof about arbitrary runtime-generated
addresses or the exact lost historical prototype.

The name ending FiPv was introduced by recovered-name commit `be75fdde6a`.
Its preservation is metadata consistency, not original source proof by itself.
The input roles, existing camera callers, absence of a receiver and provider's
existing void definition support the chosen shared static interface. Use int,
not the repository's long typedef, so its native symbol identity remains
`set_viewport_scissor__11TCameraCtrlFiPv` without a manual mangled-name alias.

## Preserved behavior and limits

Every arithmetic operation, condition and call in the provider is retained.
The only added local is the pointer conversion to its existing private view.
All three callers keep the same mode, address and surrounding state changes.
The mode-0 stack setup is retained. No null guard, clamping correction, ownership
change or return-value synthesis is added.

There is an existing defect: `adj` is uninitialized when the computed vertical
offset is negative or unordered/NaN. In the original instructions, incoming f31
is used without assignment on that path. This repair deliberately does not
initialize it or convert that inherited register dependence into a fake argument.
Out-of-range or non-finite float-to-u32 conversions are also outside the defined
host characterization. An interface repair does not make those paths portable.

The original-free host test extracts the actual shared declaration, private
rectangle view and provider body. It tests non-2 modes with a null rectangle,
basic mode-2 routing, clamps, positive offsets, representable fractional
conversions and 10,000 bounded states. It also checks all three source call sites
use the shared interface. Mode-2 test inputs are finite, initialize adj and keep
conversions representable. Sanitizer builds make UBSan failures fatal. The GPU
is a recording stub; this is not native ABI, native matching or GPU proof.

## Validation boundary and provenance

The source pin is `d6fc686573510cc9612beb6a2d71576ad685301c`, whose only delta
from parent `cb862cd99ef707159a73e33c302fdf753cdee5e1` is README.md. Native
baseline inputs and results must be authenticated independently. The earlier
read-only scope audit used 08c1789/345ac; it is source evidence rather than a
substitute for current-pin build validation.

The camera header had 174 compiled consumers in that scope audit, with Zako
adding one. Recompute and validate the complete dependency set at the candidate,
plus all active native objects, relocations, DOL bytes, address no-loss,
providers and retention. Do not count these already-linked functions as new
matching or source-link gains.

The static declaration was proposed in Matthew Newton's #303 work, which records
Cursor co-authorship. This extraction completes the provider/caller contract
rather than copying the original whole renderer fold. The #440 constructor and
resource work and the existing BML types are already baseline and not repeated.
The shadow material-helper mismatch, full typed renderer/fold and compiler-profile
migration remain explicitly held. The shadow body is unchanged by this repair.
