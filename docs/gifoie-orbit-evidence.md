# GiFoie orbit update recovery

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

## Exact update source and compiler setting

The final emitter loop uses a fresh signed word counter instead of reusing the
motion-path amplitude index. Its direction-field reset reads a non-const named
word initialized to zero. The existing pragma push/pop now also bounds
`opt_propagation off` to this update. These three choices together reproduce the
original separate direction/count/stride zero definitions and the two-step
angle-scale address load. The callback order, fresh array and band/count reads,
FP evaluation, types, and ownership remain the same. No raw byte cursor or
additional memory effect is needed.

Paired minimal probes with the pinned GC/2.6 compiler distinguish the cause:
non-const named zero with propagation on emits 200 bytes; const named zero with
propagation off also emits 200; non-const named zero with propagation off emits
208 and preserves the separate address and zero lifetimes. In the real function,
reusing the outer counter still emits 896 bytes; the fresh loop-local counter
produces the exact 900-byte body. Keep the named zero non-const and retain the
local compiler setting unless a replacement passes the complete object checks.
This is a function-local setting, with no build-profile or shared-header change.

The existing local `doldecomp/mweppc` reference at commit
`19365baddf770e61fce8a2909419d844c5eef29d` supplied the hypothesis: its
`ValueNumbering.c:isCSEop` treats named locals and compiler temporaries differently
for literal loads, and `Peephole.c:ADDI_L_S` forbids the address fold when the
source register is overwritten before the load. This explanation is consistent
with the measured paired outputs; that reference does not establish the
implementation of the installed compiler binary or the original game source.

## Targeted validation and remaining gates

Against the frozen native-repair prerequisite
`faf702cd14096119915547de4f8e3b1d419bc7c9`, the update changes from 892/900 bytes
and 98.26667% instruction similarity to an exact 900-byte body. All nine prior
exact functions remain exact. The complete 3,412-byte `.text` section is
byte-identical to the original split, with the original function order, sizes,
offsets and alignment 4. All 131 text relocations match after identifying the
already-localized conversion-bias symbol with its compiler-generated local name.
The eight-byte bias and 24-byte native vtable retain their bytes, alignment 8,
and original relocations. The compiled object's import/export names are
unchanged from the prerequisite; the update introduces no new consumer boundary.

These are local targeted-object and original-data checks. The original unit is
still retained by the linked-unit selection. Actual split/report regeneration,
refreshed checks against final development inputs, scheduled full development,
normal `check_pr`, original DOL hash, ordered linker inputs and source-link proof
remain required before the owner can select or accept this unit from source.
The targeted exact result is not a claim that those integration gates ran.

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
substitute for those gates. Select the whole unit from source only after those scheduled integration
gates confirm eligibility.
