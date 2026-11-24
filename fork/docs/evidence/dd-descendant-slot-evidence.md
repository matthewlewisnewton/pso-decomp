# DD descendant virtual slot

The original DD base table has no common callable implementation at the
position `+0x1a0`. Direct subclasses use that position for different methods:
Nest has a receiver-only initialization method, Boss 2 Joint has a
receiver-only initialization method, and Boss 2 Mine handles a signed action
argument. DD_ST instead introduces its own float-argument target-selection
method there. Boss 7 Joint's corresponding word is zero.

The old pure `TObjEneDD::vfunc_104(f32)` assigned the DD_ST contract to the
base and caused direct descendants' subsequent virtual calls to be placed at
incorrect offsets. This change relies on the native Nest implementation in
its preceding commits and declares the real Joint and Mine methods before their
later virtuals. The method names describe observed behavior; original source
names are not established. The surrounding legacy Joint and Mine helpers and
raw table declarations remain outside this change.
