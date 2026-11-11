# Technique-contact call boundaries after exact dispatcher recovery

PR #443 recovered and source-linked the complete `TObjNpcKenkyuW.cpp` unit.
This follow-up retains that exact implementation and repairs two provisional
call boundaries. It does not claim another newly matched function or linked
unit on top of current main.

Pinned base: fork main `d6fc686573510cc9612beb6a2d71576ad685301c`.
The prerequisite implementation is `b54ebadc4192bcaea393f799f39b43142dbb9fb2`,
integrated as `1ae049cb12e8393aac83b0d493379265de581824` and merged by
`cb862cd99ef707159a73e33c302fdf753cdee5e1` ([#443](https://github.com/matthewlewisnewton/pso-decomp/pull/443)).
The matching solution and existing compiler exceptions are documented in
[the continuation evidence](kenkyuw-dispatcher-continuation.md).

## Dispatcher at `0x802A445C`

The original direct calls at `0x802A4CA0` (needle task) and `0x802CE410`
(GiGue missile task) both pass the projectile in `r3` and `1` in `r4`.
Both callers are `TNeedleShoot`-derived and ignore the result. The dispatcher
never reads its incoming second argument, and neither caller consumes its
return register.

`TNeedleShoot.h` now shares
`void TObjPlayer__sub_802A445C(TNeedleShoot *, s32)` with both callers and
the definition. This preserves the observed unused input while removing the
inconsistent local `s32 (void *, s32)` / `s32 (void *, int)` declarations.
It does not identify the original name or purpose of that second input.

The matching implementation, typed `m_38` contact-body pointer, scoped
`scheduling off` / `global_optimizer off`, and value conversion in its virtual
call come from main and remain intact. No new compiler exception or unit
boundary is introduced by these call-boundary repairs.

## Reset at `0x802A3D68`

The original calls at `0x802A3E10`, `0x802A4004`, and `0x802A41F4` pass the
collector's projectile in `r3`. The reset immediately overwrites that incoming
register and clears the shared actors, bodies and count.

Main declared a zero-argument free function and cast its address to a different
function-pointer type at each call to supply that projectile. This follow-up
uses ordinary calls through the shared provisional declaration
`void clear_technique_contacts(TNeedleShoot *)` in `TechniqueContact.h`.
The definition explicitly ignores that parameter. Its symbol is renamed at the
same original address; stale zero-argument declarations are removed from the
NPC header. Generated retention replaces only the old reset name with the
new one, keeping the entry count unchanged.

This is a neutral operational boundary, not evidence that the original used
a free function, static member, or particular class owner. Existing private
receiver-layout views and the player-class collector declaration remain
provisional; the change does not broaden those ownership claims.

## Validation

The acceptance checks compare the complete linked unit and both caller units
against a separate clean build of the pinned main, then compare address-based
function/code/data coverage and actual link inputs. The complete 2,376-byte
unit must stay exact and source-linked, both caller text sections must remain
byte-identical, and relocations must agree after mapping only the reset label.
Fresh separate baseline and candidate builds pass with DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All ten functions remain 100%
exact; the dispatcher is 228 bytes and the complete unit is 2,376 bytes.
All allocated contents and all 120 relocations agree with pinned main after
mapping only the reset label. Complete unit text SHA-256:
`255926540faf1e27d9d8508822c7107d6cd128133969c29dcb77481fe007c101`.
Both caller objects' allocated contents and relocations also agree with main;
their text sections are 444 and 1,160 bytes respectively.

The real ordered 4,943-input ELF link command includes the compiled
`src/pso/npc/TObjNpcKenkyuW.o` and excludes the original split provider in
both builds. The candidate input path/object-hash digest is
`5bf3d305f0ee827b15c2b49f2ba693a87ccadbc3ae862ef477c6ec198e22cb67`;
the clean baseline digest is
`d67a70a276228c6158cb4c12bf912ad9c5ef2faf8fcc30f0bd751c81c23f118f`.

`check_pr.py --no-build` passes against pinned main: 27,447 exact functions,
4,243,592 matched code bytes, 1,477,731 matched data bytes, and 3,612 linked
units are unchanged. No address coverage, complete code/data or exact function
is lost. Retention has 18,663 entries; only the reset label changes. The
porting inventory and changed-line whitespace checks pass.

The overall comparison against earlier main
`08c178922fb8da57f44c2d9fc4efb5ebdecf05b4` also passes: three additional
exact functions, +1,720 matched code bytes, +52 matched data bytes,
+5,112 linked code bytes, +68 linked data bytes, and two additional linked
units, with zero regressions. Those gains come from prerequisite main work
(the dispatcher and TWindowDD), not from these ABI repairs.

## Historical investigation

The pre-match investigation and its standalone compiler controls are preserved
at immutable commit
[`de82ec68d9901f6a429dc27e7b1a69b27271f9ad`](https://github.com/matthewlewisnewton/pso-decomp/blob/de82ec68d9901f6a429dc27e7b1a69b27271f9ad/docs/evidence/kenkyuw-dispatcher-hit-test-scheduling.md).
Its 96.49123% scores and unlinked status describe that historical snapshot.
The later exact solution in #443 supersedes those matching holds; the failed
experiments are not proof that the original source or compiler settings were
impossible to reconstruct. No game binaries or object dumps are published.
