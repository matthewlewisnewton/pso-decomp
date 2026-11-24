# Dead-spot effect wrapper

The helper at `0x800D907C` forwards its position pointer, particle lifetime and
floating-point radius to the dead-spot factory, inserting effect ID `0xE4`.
The factory passes the position and lifetime to the timed particle emitter and
passes the position, emitter and radius to the dead-spot initializer. The
original wrapper leaves its floating-point argument in `f1` for the factory;
the typed declaration makes that argument explicit. The emitter stores the lifetime separately from its zero delay. The dead spot
uses the radius for radial offsets. The wrapper exposes no meaningful return.

The existing Nest caller uses a local three-float overlay cast to `Vec *`; its
C++ object lifetime is separate from the machine-level pointer contract.
The downstream factory still exposes integer addresses at its source boundary.
