# Scale-15 dead-spot position

The wrapper at `0x800D9398` forwards its first input unchanged to the dead-spot factory, supplies selector 2 and the `lbl_805DA3CC` scale, and forwards its second input as the delay. The downstream constructor at `0x800D8314` copies the incoming three-component point to a local vector before its ground query. The `const Vec *` wrapper argument reflects that observed read-only use; the original source spelling is not established. The wrapper has no observed return value.

This function is distinct from the E4 particle-backed factory at `0x800D907C`. The underlying factory and constructor still use legacy integer or raw pointer declarations, and some callers use existing local vector overlays. This change does not recover their full object types or establish ownership for other effect interfaces.
