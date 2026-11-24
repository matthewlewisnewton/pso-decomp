# Recover native gameplay sound positions and request state

PR #392 is open at `dd1bb30ee0781a9038b19534e78fab4a2f035c3f` on upstream master `a519ac9af5fadfe3fee8555cbe4c6399dcbfcdae`. The review branch includes the 209 source files and two linker metadata files. [Upstream PR](https://github.com/zeroz41/pso-decomp/pull/392) · [Validation](2026-11-23-followups-on-latest-pr385-and-pr386.json)

## PR description

## Summary

Recover the C++ interfaces shared by the gameplay sound mixer, voice slots, and callers.

- Persistent sound requests carry source identity separately from world position. The mixer keeps the original slot reuse rules, and floor-dependent dispatch returns the original result.
- One-shot effects share a declaration and carry typed positions from actor, object, and technique callers to the mixer.
- Voice updates, reverb, and controller requests use the `SoundRequestVoice` and `SoundControlState` records. The gameplay sound packet handler reads the shared command and payload layout.

## Validation

- Matches the retail GPOE8P DOL byte for byte at SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 27,572 functions match and all 2,295 source units link. Coverage checks pass against upstream and fork main, and all 1,147 original data bytes remain accounted for.
- Probes exercise persistent slot handling, four dispatch routines on all 36 floors, voice reuse, distinct source identities, and full-pool rejection.
- Upstream's source-quality checker removes 269 findings and adds zero. The 12 function-label changes follow recovered signatures and owners. There are zero flagged labels and zero newly stale retention entries.

Validated on upstream master `a519ac9af5`.
