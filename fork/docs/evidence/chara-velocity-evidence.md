# Character movement vector

`TObjChara` stores three consecutive float components at offsets `0x308`,
`0x30C`, and `0x310`. Movement code reads and updates them as a vector, and
other callers use the same storage for temporary directions. The member is
therefore represented as a `Vec` named `movement_velocity` at `0x308`; the
existing `velocity()` accessor returns that actual object.

The name describes the common movement use, not a claim that the original
source used this spelling or that every caller treats the vector as velocity.
