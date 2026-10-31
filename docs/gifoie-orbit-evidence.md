# GiFoie orbit update recovery (WIP)

The missing `run_task__13TUnk_804CC800Fv` at `0x80230EA0` belongs to the
0x4C-byte orbit task constructed at `0x802312E4`, rather than the 0x13C-byte
`TTecGiFoie` receiver. The private `GiFoieOrbitTask` is a layout view of that
existing allocation, not a proposed new inheritance hierarchy or original class
name. Constructor and destructor interfaces remain provisional C boundaries.

## State and lifetime evidence

The constructor writes the emitter-array pointer at 0x1C, copies three float
coordinates to 0x20 and 0x2C, initializes the float radius at 0x38, signed word
phase at 0x3C, signed word tick counter at 0x40, and byte band/level/mode/single
fields at 0x44..0x47. Its caller allocates 0x4C bytes. The update additionally
reads a word axis angle at 0x48. The observed constructor does not initialize
that last word; this change deliberately adds no initialization or ownership
assumption about its dormant alternate mode.

The constructor allocates one pointer for the single-emitter path or four bytes
per profile entry otherwise. Both particle factories return emitter objects
subsequently passed to `TParticleCtrl::set_scale`. The destructor queues those
same emitters, frees their pointer array, and calls the original base destructor.
One typed pointer-array view now serves construction, update, and destruction.
No emitter is created, replaced, freed, or queued by the recovered update.

The profile is an eight-byte pointer/count record and its count is unsigned.
The update reads the band with `lbz`, the phase/tick values with `lwz`, and the
coordinate/radius values with `lfs`. The level byte is not read by this update.
The signed word phase and tick computations retain the original conversion
sequence; they are not narrowed to unsigned-short angles.

## Floating-point and callback order

The alternate mode performs a double-precision addition of 0.015, rounds back
to float, advances phase by 0x1C71, and evaluates cosine before sine. It pushes
the identity matrix, rotates Y then X, rotates the offset in place, and pops
one matrix before adding the origin.

The ordinary mode adds a float radial increment, converts the band-dependent
phase increment through float multiplication, then evaluates the vertical sine,
horizontal cosine, and horizontal sine in that order. The three final coordinate
expressions use the original fused multiply-add operations. The local
`fp_contract on` pragma is bounded to this update and reproduces those operations;
using separate multiply and add instructions changes the floating-point result.

For a single emitter, the update rotates the original forward vector on a balanced
matrix push/pop, zeros the three-word direction, and calls the established C++
`direction_to_rotation_xz` helper with its X and Z fields. Otherwise it computes
`atan2_float(dx, dz)`, scales in double precision, truncates to a signed word,
and forms the original X/zero-Y/0x4000-Z direction. Each emitter receives its
position callback followed by its direction callback. The array and band/count
are reloaded around callbacks, as in the original.

## Checkpoint limits

The GC/2.6 single-object comparison preserves all nine previously exact functions
and the eight owned data bytes. The new update is **not exact**: its native body
is 892 bytes versus 900 original bytes, with 98.26667% objdiff instruction
similarity. Remaining differences are the double-factor address materialization
and the adjacent emitter-loop zero/register setup. This is zero new exact code
bytes, and source linkage remains unchanged. No split, symbol owner, compiler
configuration, linked-unit list, shared header, or original input was changed.

Local probes covered expression/local order, native pointer and aggregate
access, loop-counter types/scope/reuse, and supported optimizer controls.
Changing to a literal also emitted extra data and was rejected. Removing
scheduling or peephole optimization moved many already-correct instructions;
those settings are not part of this checkpoint. No assembly, volatile effects,
manual register assignments, raw constant casts, or data-range reassignment were
used to force the remaining sequence.

Full build, `check_pr`, DOL hash verification, and source-link acceptance have
not been run for this inexact checkpoint. It remains draft work.
