# Vector helper contracts

`normalize_vector_checked` at `0x8007E9EC` takes a pointer to an XYZ vector,
normalizes it in place, and returns an approximate original length. The
underlying routine uses hardware reciprocal-square-root and reciprocal
estimates. If the squared length is zero, or if the returned length is
non-finite, it clears all three components and returns zero. Its former
`TObjBoss2Tunnel::update_scale` name treated the vector as an object receiver.

`transform_point_to_view` at `0x800B9F04` forwards a source and destination
vector to the camera transform. That transform concatenates the selected
camera view matrix with the current matrix and transforms the point, including
translation, into the destination. Its former `TObjEneDD::get_camera_ctrl`
name obscured both vector arguments. No return value or general aliasing
guarantee is established by this interface.

The native helper declarations describe these boundaries. Some older callers
still use hand-written compatibility declarations with integer-held pointers,
ignored returns or extra arguments; those declarations are not made type-safe
by the symbol renames. The underlying camera transform still takes integer
addresses at its current source boundary. Some converted normalization calls
cast local arrays or other structures to `Vec *`; those casts do not establish
the lifetime of a `Vec` object, and the caller storage needs further recovery.
