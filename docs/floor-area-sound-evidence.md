# Floor-area sound wrappers

The original entries at `0x800D8830` and `0x800D88E4` select persistent and one-shot sound requests from the
current floor area. The persistent entry forwards the owner and position. The one-shot entry leaves the sound
request result in the return register on its sound-producing paths and the floor-area value on the other path;
GibonU consumes that full-register result. The signed return spelling is a carrier for the observed register,
not proof of the original source type.

The named request constants preserve the original packed values. The underlying sound APIs have their own
position-lifetime and reuse rules; these wrappers do not establish shorter lifetimes. The position and owner
types describe the observed call boundaries, not complete ownership of the sound subsystem.
