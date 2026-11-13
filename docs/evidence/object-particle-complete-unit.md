# Complete object-particle unit

Recovery base: fork `main` `9ac38ed9b5cbeb366c900b5f77967b7d79226787`.
`pso/object/TObjParticle.cpp` owns the five functions at
`0x8019527C..0x80195674` (1,016 bytes). They already matched and linked;
this recovery replaces the provisional constructor and brings the remaining
40 data bytes into the source unit.

## Native object and set record

The constructor at `0x80195400` calls `TObjBase(TObject *)`, installs the
`TObjParticle` vtable and name, and copies the set position, rotation, three
float parameters, and three integer parameters into the shared base fields.
The set record's first 12 bytes are not read here and remain opaque. Rotation
is copied as three words with `copy_xyz`; the shared `CameraAngles` represents
those words without pretending they are floating-point coordinates.

The value stored at object offset `0x90` is the result of the shared particle
factories. Task update passes it to `TParticleCtrl::set_position` and
`set_direction`, and destruction queues it before clearing it. It is now a
`TParticleCtrl *emitter`. Offset `0x94` receives the integer conversion of the
set's first float parameter, also used as the particle-table ID; it is retained
as `particle_id`. Size and offset assertions guard the object and the read
portion of the set record.

The native constructor and ordinary `new` replace the free constructor's
manual vtable store and allocation scaffolding. The factory retains its
existing C-linkage symbol and byte-pointer boundary. Camera distance uses the
shared camera's verified `position` member at `0x178`. The render function's
apparently empty checks are retained because the original still performs both
the parent-state call and the emitter comparison.

## Compile, compare, research, refine

The initial native reconstruction preserved render, destructor and factory at
100%. Task update was 99.7% because its three literals still targeted a
separate fallback pool. The constructor was 96.20301% and 12 bytes too long:
using `u16 flags` with the shared `int` particle-spawn API added an unconditional
`clrlwi` at each of its first three calls. The old unit-local prototype had
instead declared that API's last argument as `u16`.

The [keyboard client-argument case](keyboard-constructor-abi-evidence.md) and
[projectile entity-ID case](pr100-projectile-id.md) explain why the register
carrier and the point of narrowing must be checked separately. The shared
spawn implementation forwards its full argument to the particle controller;
this unit uses its existing shared declaration rather than changing that ABI.
A full-width flag local with `u16` casts at composition improved the constructor
to 97.21805%, but introduced a temporary move and narrowed the base too early.
Full-width base/flag locals with explicit low-16-bit masks improved it to
98.45865%; only the final call's narrowing schedule and the zero-literal target
remained. Using the same full-width carrier and mask expression for the
continuous flags reproduced the original instruction order. These masks retain
the original 16-bit composition boundaries; they do not establish the original
source spelling. No compiler flag or pragma was added.

The [Gryphon shockwave](gryphon-shockwave-constants.md) and
[conversion-pool](conversion-pool-constants.md) cases explain the remaining
literal relocations. The default compiler emits these values in order:

| Address | Value | Consumer |
| --- | ---: | --- |
| `0x805DBEE0` | `2250000.0f` | task distance threshold |
| `0x805DBEE4` | `160000.0f` | task distance threshold |
| `0x805DBEE8` | `100000000.0f` | task distance threshold |
| `0x805DBEEC` | `0.0f` | constructor mode comparison |

Assigning `0x805DBEE0..0x805DBEF0` to the unit makes all four relocations exact.
The localization tool checked the active original and compiled consumers before
marking those four labels local. The adjacent zero at `0x805DBEF0` is outside
this pool and remains with the following fallback data.

## Complete data and validation

The name pointer at `0x805D33D8` targets the `TObjParticle` string at
`0x80445E30`. Source now defines both. The pointer's symbol extent is four
bytes; the eight-byte split retains its four-byte trailing alignment. The
13-byte string similarly occupies a 16-byte split. The compiler/linker provide
those zero tails, with no explicit padding objects. The preceding four-byte
`motorcycle_class_name` at `0x805D33D4` remains in an explicitly described
original fallback fragment: it was part of the old generated fragment and is
not particle data or padding.

All five functions, the native 52-byte vtable, name storage and 16-byte float
pool compare at 100%. Original/compiled allocated section alignments agree
(text four, other sections eight), and all 46 runtime relocations have equal
section offsets, types and resolved target addresses. Expanded linker inputs
select the compiled particle object. The existing linkset entry remains valid;
retention changes are limited to its native constructor, name string and name
pointer.

The full original-DOL SHA-1 remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The address-based report comparison
gains 40 matched and source-linked data bytes with unchanged function, code and
data denominators. All 3,616 linked units remain exact, and the generated
retention check passes. The complete unit supplies 1,016 code bytes and 92 data
bytes, including its linker-provided alignment tails.
