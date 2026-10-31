# Window effect light recovery (work in progress)

At 0x802AD040, the original calls the alpha and scale methods, selects texture 2, and draws left and right quads around the position at offsets 0x1c and 0x20. It draws a center quad only when the width argument exceeds the constant at 0x805DE0F4. The implementation retains placeholder names for constants and the helper; its geometry is inferred from those operations, not original source names.

Targeted comparison against the original object at base beaa7f52af2a7360e18deafc771648f51b709531 reports the helper at 96.87%, with the other eight existing functions still exact. This is an intermediate candidate, not a complete or linkable unit. Full-build validation remains pending. The original vtable at 0x804DE390 and constants beginning at 0x805DE0E0 are outside the current unit's split; ownership and the existing inherited provisional interfaces require further investigation before claiming whole-unit linkage.
