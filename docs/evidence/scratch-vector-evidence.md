# Shared scratch vector storage

`scratch_vec` and `lbl_8050BF00` are shared scratch symbols defined by the
render utility. Each occupies 0x20 bytes in the original object. Callers use
the first three floats as a three-component vector; the remaining 0x14 bytes
are retained as opaque storage because their original structure is unknown.
`ScratchVectorStorage` expresses that layout with a `Vec` at offset zero.

This describes the observed storage and common vector access, not the
original source-level names or a general-purpose vector workspace API.
