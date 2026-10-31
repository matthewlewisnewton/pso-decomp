# Lens-flare renderer recovery

`render__13TEF_LensFlareFv` owns 0x800812D0..0x800818D8 in
`pso/effect/TEF_LensFlare.cpp`. This is a partial native reconstruction: the
function remains nonexact and the unit remains on fallback. No newly exact code
or source linkage is claimed.

The renderer returns when the render pass is zero or the camera is absent. It
initializes a local sprite scratch, selects additive blending, and optionally
rejects the light using `(10 * scale.x)^2` and the existing proximity helper.
That rejection precedes `begin_effect_render`; do not add a matching end call
there. After beginning the effect, it normalizes the camera-to-light vector
when its squared length is nonzero. The normalizer at 0x803D97B4 writes
three float components and returns its approximate length in f1; its local
declaration therefore uses an f32 result. The caller ignores that result. An identity matrix, camera y rotation,
camera x rotation, and the constant forward vector establish the facing dot
product. A nonpositive dot skips drawing but still ends the effect.

For positive facing, depth/alpha state is saved by the existing state helper
before projecting the object's position. The projection helper at 0x803D8D1C
writes only output offsets 0 and 4, proving the two-float screen buffer extent. The original has no extra x/y screen
clipping test or alpha clamp. The glare path uses sprite definition 15 when
facing exceeds 0.99. The central path always uses definition 9. Both build
axis-aligned quads with full 0..1 UVs at depth 0.5. Each draw pairs
`begin_screen_draw(1)` with the existing screen-state restoration helper named
`TWindowSubStatusDisp::get_player`. The particle effect ends after depth/alpha
restoration.

At 0x8008172C..0x80081870 the reflected-element pointer advances by 0x18.
Offsets 0,4,8,C,10 hold a signed texture selector and four floats: displacement,
scale, attenuation, and alpha. Offset 14 is not consumed here. The exported
0xF0-byte table contains ten such records, but the postincremented loop starting
at one consumes only the first nine. It selects definition `9 + texture` and
moves from the projected point towards/beyond screen center (320,240). The
attenuation expression preserves the original fused negative multiply-subtract;
the displacement expressions preserve fused multiply-add ordering. Negative
sizes clamp to zero. Alpha follows signed `fctiwz`, then byte storage; the
explicit intermediate signed conversion preserves low-byte wrapping rather
than introducing a clamp or relying on an out-of-range float-to-byte conversion.

The sprite definition stride is 0x28. Existing particle-atlas initialization and
sprite renderers establish the texture-list/texture fields at 4/8 and dimensions
at 14/18. Lens-flare loads from definition 9 at 0x16C/0x170/0x17C/0x180 and
from definition 15 at 0x25C/0x260/0x26C/0x270 agree with that layout. The private
0x2C sprite scratch follows the node layout already consumed by the adjacent
quad-sprite renderers: link, position, offset, scales, color, flags, type, angle.
The link/type are not used here and remain untouched. Only the position
subobject reaches `VecCopy`; quad submission receives an actual float array.
Color byte/word views use the target compiler's native union representation.

The class's offset-90 field is now a descriptor pointer. The existing constructor
stores the descriptor table's address there. Its size remains 0x94, and the sole
other source consumer (`TWindowKeyBoardBase_8008102C.cpp`) compiles identically
with the previous and refined headers. No camera, math, graphics, or particle
shared header is changed. The legacy constructor representation remains bounded
and is not broadened by this recovery.

Targeted GC/2.6 probes preserve all five existing exact functions, including the
constructor. Remaining differences involve register allocation and local
instruction scheduling. Aggregate quad initialization introduced a constant
copy loop and extra data and was rejected; scalar quad construction is retained.
A higher-similarity direct float-to-byte variant was rejected in favor of the
explicit signed alpha conversion above. Full build, address-loss, data/export,
linker-input, and original-DOL gates remain outstanding until an exact candidate
justifies development-lane admission.
