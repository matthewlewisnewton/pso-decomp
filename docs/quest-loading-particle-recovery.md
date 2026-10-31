# Quest-loading particle recovery

The constructor at `0x80322F20` receives the allocated `0x158`-byte object
in r3 and its `TAdLoadQuestGC` parent in r4. It forwards both to the native
`TObject` constructor and returns the same receiver. The sole call site at
`0x80309788` checks allocation before constructing the child.

Four controller pointers start at `0x1c`; the destructor at `0x80322E90`
queues each non-null controller and clears its slot. The constructor passes
persistent per-controller positions (`0x2c`, stride `0xc`) and angle words
(`0x5c`, stride `0xc`) to `create_particle_controller_with_angles`. Signed
angle increments start at `0x8c`. The task adds increments to unsigned word
accumulators, preserving their wrap. Constructor color records begin at
`0xc8`, stride `0x24`; only the first four float fields are established.
Remaining fields retain opaque storage and are not initialized here.

The apparent member `get_abs()` at `0x80323114` is a scalar wrapper:
its callers pass a signed stick sample in r3, and `ansi_fp_abs` accepts
an integer. Giving this boundary its scalar signature preserves the existing
32-byte implementation without fabricating a receiver.

The native constructor is mapped to `0x80322F20`, and the sole caller uses
native allocation with its verified `TAdLoadQuestGC` parent. Fresh original
split objects generated from these repository mappings compare exactly with
targeted compiler output: 500 constructor bytes and 13 relocations, plus all
three caller functions (196, 4, and 4 bytes). No comparison aliases are needed.

The compiler emits an unsigned conversion double. Its original eight-byte
range `0x80476640..0x80476648` is assigned to this unit and localized; both
original and compiled values are the native `2^52` bias with alignment 8.
Original-object and compiled-object reference scans found no other consumer.
Neighboring tables, strings, and signed conversion data retain their ownership.

Targeted compilation preserves all three existing exact functions. Both other
header consumers (`TBoss6Kakusan.cpp` and `TBoss6GravBall_80323134.cpp`) retain
byte-identical complete objects. The task body remains unrecovered in this
checkpoint. Whole-program validation is pending, and source-link selection is
unchanged.
