# Radial particle update and owned constants

## Sources and boundary

This recovers `TUnk_8048E7A8::run_task` at `0x8008B590` (1,384 bytes),
adapting the typed implementation in upstream [#244](https://github.com/zeroz41/pso-decomp/pull/244),
commit `8c507b2dacae5428291a823c3868ca486419660c`. Its earlier matched body came
from [#243](https://github.com/zeroz41/pso-decomp/pull/243), commit
`23795dfa1d27576b0cd4034d2fb37c47583969ab`. The fork baseline is
`f0f05f3afe56fd2b71e9dc1fe946e2fa03c84b86`; paths remain the fork's paths.

The original update loads the emitter record at `this+0x20`, advances toward
`origin` using speed at `+0x68`, stores the resulting step at `+0x3C`, ages and
fades the particle, updates the sprite frame, follows the entity identified at
`+0x26` through `find_entity_by_id` / its real `get_center` virtual, and advances
the `NJS_MOTION` at `+0xB8`. The derived `+0xC0` word is a floating-point motion
frame step, not a byte buffer.

`TUnk_8048E728.h` now declares the actual vectors, scalar state, parameter
record used by that code. The parameter
record is still a bounded partial record: unknown fields remain unknown.
The texture table's declaration remains exactly the owner's `void *[0x6C]`
from `TParticleCtrl_801E5330.cpp`. Its entries are converted to the existing
`TUnk_804C57F0` quad-sprite base; that class's declared `void *m_28` is then
converted to `ParticleDefinition *`. The already-defined complete
`ParticleDefinition` was moved unchanged from the owner source into a shared
header. All 0x6C slots hold sprite objects; rendering can choose an alternate
bank at index +0x36. There is no competing typed array object declaration or
invented queue bank. The existing `void *` definition field remains an explicit
legacy boundary. The two native constructors use the same frame-count access
instead of pointer arithmetic off a synthetic scalar.

Existing Ballistic and Orbit member accesses are updated to the actual stored
fields. No compatibility unions alias scalar/vector storage. Existing legacy
constructor and rendering boundaries are otherwise preserved; this change is
not a claim that all particle APIs or constructor ownership are recovered.
In particular, raw constructor/destructor views, explicit legacy vptr writes
and other provisional rendering interfaces remain. The two touched
motion-drawing calls use the actual shared `ModelDrawContext` declaration;
only their existing integer model handle is converted to its pointer argument.
The age/fade pair and three colour-channel locals carry meaningful values,
but their array spelling is not proof of the original source declarations.

## Floating-point semantics

The ordinary MWCC GC/2.6 unit command is `-O4,s -inline off -sdata2 4`, with no
unit `fp_contract` override. The existing two constructor scopes already use
`fp_contract on`. The newly recovered update uses a separate push/on/pop
scope, leaving every other routine's compiler state unchanged.

The original has twelve `fmadds` for `color_rate[channel] * age + base[channel]`,
at `0x8008B6D0`, `0x8008B704`, `0x8008B738`, `0x8008B770`, `0x8008B7A4`,
`0x8008B7D8`, `0x8008B820`, `0x8008B84C`, `0x8008B878`, `0x8008B8A8`,
`0x8008B8D4`, and `0x8008B900`. These cover all three channels in each of the
four additive/nonadditive and per-particle/emitter-base paths. This is direct
arithmetic evidence, not a scheduling or register-allocation preference.

With only this new scope's `on` removed, the update is 94.10405%: the compiler
emits separate multiply/add operations and additional instructions. With the
scope it is exactly 1,384 bytes. All eight pre-existing functions remain exact
in both probes. The source cannot establish the precise original spelling of
the compiler setting; it establishes the single-rounded arithmetic required
by the executable. Independent source-quality review is required before
publication of this new compiler-control use.

For a port, use single-precision fused interpolation, such as `fmaf(rate, age,
base)`, where native rounding must be preserved. Separate multiplication and
addition can change the value at clamp/conversion boundaries. Floating-point
exception, denormal and conversion behavior still needs the target platform's
normal compatibility treatment.

## Colour representation

The native routine stores alpha/red/green/blue as four bytes then loads one
32-bit word. The source writes the object representation of a live `u32`
through `u8 *` (`unsigned char *`), which is legal byte aliasing. It does not
read an inactive union member. GameCube's big-endian representation gives the
packed value `0xAARRGGBB`.

A little-endian port should keep the same channel conversions and form the
word explicitly: `(u32(a) << 24) | (u32(r) << 16) | (u32(g) << 8) | u32(b)`.
The byte-write spelling is target-specific; merely removing compiler pragmas
is not sufficient to preserve packed colour on a little-endian host.

## Data ownership and validation

The unit owns `.rodata` `0x80439540..0x80439568`: the zero angle triple with
alignment padding, signed and unsigned integer-conversion doubles, and the
radians-to-angle factor. Its existing `.sdata2` `0x805D9558..0x805D9570` is
emitted by ordinary literals. This accounts for 64 exact data bytes, up from
8 on the fork baseline, rather than borrowing a neighbouring unit's pool.

The direct object comparison is all nine functions / 4,220 code bytes and
both data sections / 64 bytes exact. The new totals are +1 exact function,
+1,384 exact code bytes and +56 exact data bytes.

The seven other affected compiled objects (`TParticleCtrl_801E5330`, `TParticleCtrl`,
`TParticleCtrl_80085EE4`, `TParticleCtrl_800866F8`, `TBoss4Type2_800874F4`,
`ParticleBallistic`, and `ParticleOrbit`) retain identical allocated section
bytes, sizes and alignment, global symbols, and relocation destinations versus
the fresh baseline objects. Local compiler-generated literal labels may be
renumbered; their section, offset, relocation type and addend are unchanged.

Validation uses pinned dtk 1.8.4, objdiff 3.6.1, wibo 1.0.3 and MWCC GC/2.6,
freshly split original inputs, and original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Original binaries and built artifacts
are not part of the change.

### Source-link admission

The unused `clear_active_flag__13TParticleCtrlFv` definition was removed from
this file: its owned address is `0x80088000`, outside the radial text range.
It had added 16 duplicate bytes and a foreign global to this object. Removing
that duplicate does not remove the owning unit's implementation.

The ten radial literal symbols were made local only after the repository's
localizer checked the current generated split inventory and compiled objects.
A separate census of all 8,586 current split/source consumer objects finds no
other consumer of those symbols. The scanner then admits only this new unit.
Its generated retention delta adds three names and removes none:
`check_radial_particle_retire`, `construct_radial_particle`, and
`TParticleCtrl::init_random_particle` (under their full mangled names).

Final validation against the immutable fork baseline:

- Full locked `ninja -j2`: original and rebuilt DOL hashes both equal the SHA-1
  above, including after this unit is linked from source.
- `tools/check_pr.py --no-build --baseline <fresh-f0-report>`: PASS after that
  full build; no exact function, linked unit, address coverage or data loss.
- `link_units.py check`: all 3,590 linked units exact.
- `link_units.py force-active --check`: 17,823 names; no addition or removal.
- Generated exception inventory and whitespace checks: PASS.
- Link input is `build/GPOE8P/src/pso/misc/ParticleRadial.o`, not the split
  original object. Final `.text` is 4,220 bytes, with no duplicate helper;
  `.rodata` is 40 bytes and `.sdata2` is 24 bytes, all exact.

Overall delta: +1 exact function, +1,384 exact code bytes, +56 exact data bytes,
+1 source-linked unit, +4,220 linked code bytes and +64 linked data bytes.
No original or private build artifact is included in the commit.
