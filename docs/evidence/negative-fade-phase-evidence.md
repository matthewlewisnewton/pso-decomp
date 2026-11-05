# Negative fade phase

The helper at `0x800A0554` operates on `TUnk_80490470`. It invokes the
`set_rate_from_divisor` virtual slot with 10, sets `phase` to minus 20 times
the resulting rate, and clears the four inherited color components. The new
member is nonvirtual; the call to the rate setter remains virtual.

All six original callers still use hand-mangled compatibility declarations
with `void *` arguments; five declare an integer return. Their surrounding
fade storage remains represented by raw overlays in places. Recovering the
member does not establish those declarations or overlays as type-safe.
