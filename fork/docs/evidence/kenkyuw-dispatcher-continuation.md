# Needle contact interface and exact KenkyuW unit

## Current scope and provenance

The canonical interface is the single typed `TNeedleShoot` API from
[PR #453 at `5a260fbd6c189196c583278884b7f4d72cf10bf6`](https://github.com/matthewlewisnewton/pso-decomp/pull/453).
Its baseline is fork main `d6fc686573510cc9612beb6a2d71576ad685301c`.
Main already includes the exact, source-linked unit from
[#443](https://github.com/matthewlewisnewton/pso-decomp/pull/443): implementation
`b54ebadc4192bcaea393f799f39b43142dbb9fb2`, integrated head
`1ae049cb12e8393aac83b0d493379265de581824`, merge
`cb862cd99ef707159a73e33c302fdf753cdee5e1`.
This continuation claims no new matching or linkage credit above that main.

[PR #318's immutable call-site evidence at `2a4cebc570d9a216160c47fb2d736856eedf7a31`](https://github.com/matthewlewisnewton/pso-decomp/blob/2a4cebc570d9a216160c47fb2d736856eedf7a31/docs/evidence/kenkyuw-dispatcher-hit-test-scheduling.md)
records the two-input dispatcher and the reset's ignored receiver. Those
observations are preserved below. Its provisional free-function declarations
are not a second current API: the typed continuation already removes the
incompatible calls and false player receiver without retaining wrappers or
aliases. Do not merge the two heads mechanically or reintroduce either
`TObjPlayer__sub_802A445C(TNeedleShoot *, s32)` or the global
`clear_technique_contacts(TNeedleShoot *)` declaration.

The six definitions remain in `src/pso/npc/TObjNpcKenkyuW.cpp`; method
membership does not change the original split owner. Their names are descriptive
reconstructions or address placeholders, not recovered original debug symbols.
The reset and predicate ignore their incoming receiver. Their historical
free/static/nonstatic ownership is therefore unresolved. Current ordinary
nonvirtual members are supported by the actual `TNeedleShoot`-derived callers
and preserve the observed receiver and argument registers; exact instructions
corroborate behavior but do not establish original class ownership.

## Observed call contracts

| Entry | Current nonvirtual member | Original call and behavior |
| --- | --- | --- |
| `0x802A3D68` / 68 bytes | `void clear_technique_contacts()` | Calls at `0x802A3E10`, `0x802A4004`, and `0x802A41F4` pass the collector's projectile in `r3`. The body immediately overwrites that input, clears 16 actor pointers, 16 body pointers and count, and leaves the reserved word unchanged. No caller consumes a result. |
| `0x802A3DAC` / 60 bytes | `s32 is_hit_receivable_target(TechniqueContactActor *)` | Call at `0x802A44F8` passes projectile in `r3` and actor in `r4`. The callee ignores the receiver and returns integer 0/1. The caller uses `cmpwi r3,0`; changing the result to `bool` introduces narrowing. |
| `0x802A3DE8` / 500 bytes | `TechniqueContactList *fn_802A3DE8(void *)` | Default dispatcher call at `0x802A44C8` passes projectile in `r3` and its `+0x1c` source in `r4`. The collector reads projectile body/position/direction and can return null on obstruction. |
| `0x802A3FDC` / 496 bytes | `TechniqueContactList *fn_802A3FDC(void *)` | Mode 2 call at `0x802A44B4` uses the same receiver/source convention; preserve its distinct game-mode range and flag/source-ID filters. |
| `0x802A41CC` / 656 bytes | `TechniqueContactList *collect_technique_contacts(void *)` | Mode 1 call at `0x802A44A4` uses the same convention; preserve its source-entity-ID branch, player ranges and distinct flag filters. |
| `0x802A445C` / 228 bytes | `void check_actor_contacts(s32 ignored)` | Calls at `0x802A4CA0` (needle task) and `0x802CE410` (GiGue missile task) pass projectile in `r3` and `1` in `r4`; neither consumes a result. The callee ignores its second input and dispatches on stored `+0xb0`. |

Both dispatcher callers inherit `TNeedleShoot` and call its base constructor.
The collector offsets are projectile `+0x68` collision body, `+0x6c` position,
and `+0xa0` direction storage. The dispatcher destroys a projectile with no
body, selects one of the three collectors, invokes virtual slot `+0x18` for a
null list, and otherwise tests the first actor. It reloads that actor after the
predicate, stores its associated body at `+0x38`, and invokes virtual slot
`+0x24`. The unused integer's original purpose and spelling remain unknown.

The shared `TechniqueContactList` remains 0x88 bytes at `0x80540A38`.
`TechniqueContactBody *contact_body` names existing `+0x38` storage;
`TNeedleShoot` remains 0xbc bytes and both derived callers remain 0xc4 bytes.
Nonvirtual declarations do not alter virtual slot order. The opaque source,
actor/body interfaces and existing vector views over `m_6c`/`m_a0` are bounded
recovery, not a completed portable layout, lifetime or strict-aliasing audit.
No speculative mode names, collector unification or layout changes are implied.

Keep one symbol per original address. Relative to pinned main the five retained
helper entries are renamed to their `TNeedleShoot` member symbols; the dispatcher
was not retained and must not gain a redundant retention entry. Membership by
original address and the 18,663-entry retention count remain unchanged. There is
no split, linked-unit, native-flag or new compiler-exception change.

## Prior exact-head validation

The published #453 validation at `5a260fbd6c189196c583278884b7f4d72cf10bf6`
records a full gated build and `tools/check_pr.py --no-build` PASS against the
pinned main. All ten functions and 2,376 allocated bytes, plus 110 relocations
in allocated sections, equal the original split. Ten further relocations are
nonallocated `.mwcats.text` metadata: 120 total is not 120 allocated.
The actual 4,943-input ELF link selects the compiled KenkyuW source object and
excludes the original provider. All 3,612 linked units remain exact; retention
and porting-inventory checks pass. The DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

#318 independently records fresh full baseline/candidate builds, identical
complete caller objects (444- and 1,160-byte text sections), and no address-based
coverage loss. Its reset-only symbol mapping applies to #318, not this typed
API. Cross-head comparison here must map all six approved member renames.
The shared expected unit text SHA-256 is
`255926540faf1e27d9d8508822c7107d6cd128133969c29dcb77481fe007c101`.
Pinned-main totals are 27,447 exact functions, 4,243,592 matched code bytes,
1,477,731 matched data bytes and 3,612 exact linked units.

These immutable reports are provenance, not a substitute for validating a later
candidate. Recheck live heads, rebuild the exact candidate and fresh baseline,
verify complete affected objects, original DOL, retention and executed link
inputs, and independently review source and native evidence before acceptance.
The following experiments and #443 gains are historical; their 96.49123% or
unlinked snapshots are neither current holds nor compiler-impossibility proof.

## Historical compiler investigation

The initial reconstruction was 96.49123%, 228 bytes, with the other nine functions
exact. At the hit-test call the original emits `mr r3,r30` then `lwz r4,0(r31)`;
GC/2.6 schedules the load first. Relocations and function size agree.

| Experiment | Best result for the missing function |
| --- | --- |
| Local scheduling settings and volatile accesses | 96.49123% |
| Inline collector/contact/hit-test helpers | 96.49123% |
| Scoped optimizer options, with scheduling on/off | 96.49123% |
| Compatible GC 2.0, 2.0p1, 2.5, 2.6, 2.7 releases | 96.49123%; nine other functions exact |
| Earlier/later compiler releases | No improvement; existing exact functions lost or compilation failed |
| Early returns, loops, gotos and boolean/pointer switches | 96.49123% |
| Explicit source/receiver temporaries and propagation settings | 96.49123% |
| Separate contact temporaries and member-function pointers | 96.49123% |
| Inline contact setters returning the receiver | 96.49123% |

With scheduling and propagation disabled, explicitly loading the default
collector's source argument fixes that block's order. The remaining mismatch
moves to the virtual hit call: the contact store precedes the receiver copy,
while the original copies the receiver between loading and storing the body.
Comma expressions introducing the store into the call also change stack
allocation or instruction order. These are measured failures, not a proof that
no suitable C++ source exists.

The earlier investigation is in the preserved `decomp-tobjnpc-kenkyuw` branch,
`docs/evidence/kenkyuw-dispatcher-hit-test-scheduling.md`. Compiler research
reference: https://github.com/doldecomp/mweppc . No external source was copied.

## Matching solution retained from #443

The complete `.text` section is 2,376 bytes and all ten functions match. The
dispatcher uses scoped `scheduling off` and `global_optimizer off`; no assembly,
extra references, stores or no-op statements are introduced. Both settings are
limited to this function and are recorded in the porting exceptions register.

Disabling the global optimizer preserves the contact store within the virtual
call argument. Loading the contact into a local first gives the observed load,
receiver copy, store, and virtual dispatch order. The right operand of the comma
expression must be a value, `static_cast<void *>(actor)`: leaving it as the
lvalue `actor` produces an otherwise unnecessary stack store and a 32-byte
frame instead of the original 16-byte frame. Adding `register` alone does not
remove the store. The typed continuation uses
`static_cast<TechniqueContactActor *>(target)` for the same pointer-value
conversion without discarding its type. An explicit local for the default collector's source argument
also preserves its observed load before the receiver copy.

This was derived by reading the compiler's usage analysis:
[`checkexpression`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/COptimizer.c#L303)
marks a local referenced by `EOBJREF` as non-register, whereas a direct
`EINDIRECT(EOBJREF)` is a value use. The compiler's
[`call_function`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/FunctionCalls.c#L617)
then evaluates the register arguments before loading the virtual target. The
source explanation is an inference from that code; the exact instruction,
stack-frame and relocation results were measured with the pinned GC/2.6 binary.
No compiler source was copied into this repository.

The first 111 failed experiments and the subsequent global-optimizer, lvalue
conversion and register tests are retained under ignored
`build/experiments/kenkyuw-continuation/` for local reproduction. The failed
experiments above are historical measurements, not completion evidence.

## Historical #443 validation

The #443-era validation below used clean fork-main baseline
`08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`. Its gains and 3,611-unit total
are historical, not incremental claims for the current continuation.
Both that baseline and the source-linked candidate pass `tools/check_pr.py`.
The candidate has one new exact function (+228 matched code bytes), one new
linked unit (+2,376 complete code bytes), unchanged matched/complete data,
and no exact-function, data or linkage regressions. All 3,611 linked units
pass the linked-object check. The final DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, identical to the original.

The generated final Ninja link edge for `build/GPOE8P/psov3.elf` directly
includes `build/GPOE8P/src/pso/npc/TObjNpcKenkyuW.o` and excludes its original
split object. The report marks the unit complete with 10/10 functions and
2,376/2,376 code bytes. Its split owns no allocated data sections.

Generated retention adds five symbols from this unit and removes none.
Regeneration also sorts the existing DHCP `build_release` and `build_request`
entries into their normal alphabetical positions without changing membership.
Baseline and candidate logs and the direct link-input query are retained with
the ignored experiment artifacts.
