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

The native constructor emits the original 500-byte instruction sequence.
This is not yet a reported exact gain: its native constructor symbol must be
mapped to the original address and the sole caller updated consistently.
The existing raw constructor name is a legacy annotation. The proposed native
allocation at the caller preserves its instructions and relocation types,
with only that constructor symbol changed.

The compiler also emits an unsigned conversion double. The original double
at `0x80476640` is currently in an automatic data unit; both original and
compiled values are the native `2^52` conversion bias. Original-object and
compiled-object reference scans found no other consumer of this constant.
Claiming its eight bytes for this unit and making the symbol local is a
bounded ownership correction, pending coordinated integration. No original
assets, data ranges, symbols, caller source, or linked-unit selection have
been modified by this checkpoint.

Targeted compilation preserves all three existing exact functions. Both other
header consumers (`TBoss6Kakusan.cpp` and `TBoss6GravBall_80323134.cpp`) only
include this header; their compiled allocated sections and relocations must
remain identical. Whole-program validation and source-link eligibility remain
pending; a matching fallback DOL alone will not prove source linkage.
