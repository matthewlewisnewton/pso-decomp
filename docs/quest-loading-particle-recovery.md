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

## Whole-unit continuation

The continuation reconstructs the task's input/tint control flow and keeps
integer truncation inside each per-axis expression. Doubled angles double the
signed integer before converting to float. Word accumulators retain unsigned
wrap; signed divisions truncate toward zero. The native compiler reuses repeated
conversion terms without handwritten arithmetic or instruction injection.

The retained task has 828 bytes and 99.4686% targeted similarity. Its remaining
instruction differences exchange f4 and f5 for the signed-conversion bias and
angular factor. The constructor's instruction bytes and previously exact helper
bodies are preserved. This continuation is not exact or source-linked yet; its
additional data mappings remain a separate coordinated proposal.

Native definitions now reproduce all 109 bytes of the unit's data: the six tint
presets, fixed-size class name and descriptor, compiler-generated vtable,
conversion constants, local static scale/guard, and floating constants. Direct
comparison against original DOL ranges, resolving only native ADDR32 data
relocations through the symbol map, verifies bytes, offsets and alignment. The
remaining three bytes after the local static guard are not claimed. No metadata
or source-link selection is changed by the continuation checkpoint.
