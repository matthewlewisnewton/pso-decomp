# Ancient trap continuation

This sits on the Ancient base in #221. Ancient01 stays on the original object.
Nothing here selects the unit for source linkage.

`play_sounds` copies each rodata debris template, then stores this actor's
position. Y is also the floor field. The records are `TObjChipParams`. On
GC/2.6 with the unit's `-inline off,deferred` profile, `play_sounds` is
91.086205% of its 696 bytes, not exact. Copying X and Z through locals and
reading `position.y` for both Y uses scored 95.13793%. Const aggregates under
GC/2.0 scored 100%, including the constructor, but only with
`#pragma opt_propagation off` and extra clamp temporaries. GC/2.0 is not the
unit compiler: the original `.sdata2` flags are 2, and that object emits
flags 3. Those schedules are not kept. The constructor stays on the GC/2.6
source that is already exact (612 bytes, 100%).

The eleven `.sdata2` floats at `0x805DBA48` are defined in address order.
That section is 44/44 bytes at 100%. The compiled section flags are still 3
against the original 2, so the bytes are not a link. `.data` 696, `.rodata`
400, `.sdata` 8, and `.sbss` 8 stay 100%. Seventeen functions are exact,
including `vfunc_81` (540 bytes).

`#pragma pool_data off` and `#pragma opt_lifetimes off` around `play_sounds`
come from the parent. Removing them makes the previously exact 92-byte
`.data` range at `0x804B4A1C` inexact and drops `play_sounds` to 85.52873%.
They stay so that range does not regress.
