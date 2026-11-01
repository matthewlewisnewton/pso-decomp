# GiFoie orbit update recovery (WIP)

The missing `run_task__13TUnk_804CC800Fv` at `0x80230EA0` belongs to the
0x4C-byte orbit task constructed at `0x802312E4`, rather than the 0x13C-byte
`TTecGiFoie` receiver. The private `TUnk_804CC800` declaration derives from the established `TObject` base.
Its member update retains the receiver and method name established by the
original symbol; `GiFoieOrbitTask` is an alias used by the existing factory ABI.
Its constructor and virtual destructor now use native C++ lifetime handling.

## State and lifetime evidence

The constructor writes the emitter-array pointer at 0x1C, copies three float
coordinates to 0x20 and 0x2C, initializes the float radius at 0x38, signed word
phase at 0x3C, signed word tick counter at 0x40, and byte band/level/mode/single
fields at 0x44..0x47. Its caller allocates 0x4C bytes. The update additionally
reads a word axis angle at 0x48. The observed constructor does not initialize
that last word; this change deliberately adds no initialization or ownership
assumption about its dormant alternate mode.

The native constructor allocates one pointer for the single-emitter path or four bytes
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

Full build, `check_pr`, DOL hash verification, and source-link acceptance remain
pending. The update stays inexact and the whole unit stays on fallback.

A separate read-only object audit found no extra allocated sections/globals,
section-alignment changes, function-order changes, or global-layout changes.
The outstanding export is `lbl_8044D350`, the compiler-generated integer-conversion
bias. No undefined references to that name were found in 8,776 historical original
and compiled objects. Localization remains a proposal until the scan is refreshed
against the final full development inputs.

Further valid source forms show the original 900-byte update size and two-step
angle-constant address load are reachable under the same compiler. Those forms
still differ in induction state/registers. Failed variants exclude only themselves;
there is no impossibility or assembly-origin conclusion.

## Allocated native orbit lifetime closure

The orbit class can use the established `TObject` base, a native constructor,
virtual destructor, update method, and inherited allocation functions. The
original base calls, 0x4C allocation, 0x18 vptr offset, and six-entry vtable
constrain that relationship. No shared header needs changing.

The original caller passes the band as a word loaded with `lha`. A byte-typed
native constructor argument adds an extra caller truncation absent in the
original; a signed word parameter followed by the observed byte field store
preserves both caller and constructor. The old hand-mangled factory name
attributed this allocation to TTecGiFoie and advertised a byte argument. The
proposal gives the constructor the orbit receiver name and its consistent word
parameter contract at the same original address 0x802312E4.

A diagnostic symbol-only mapping preserves every original allocated byte and
compares all nine pre-existing functions exactly against the native class form.
Its emitted vtable has the original 24-byte layout and four original relocation
targets: the orbit destructor/update and inherited TObject render/shadow methods.
The proposed .data ownership is only 0x804CC800..0x804CC818. Neighboring vtables,
particle tables, vectors, strings, and constants retain their current owners.

The reviewed constructor/vtable names, 24-byte data extent, and bias localization
are adopted on the private continuation. Actual split regeneration, refreshed
all-input localization checks, scheduled development gates, and independent
exact-head review remain necessary. The symbol-mapped diagnostic is not a
substitute for those gates. Do not select the whole unit from source while its
update differs.
