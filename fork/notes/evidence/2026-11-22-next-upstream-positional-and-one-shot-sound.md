# Recover native positional and one-shot sound interfaces

The local review `great-merge/review/after-366/positional-and-one-shot-sound` is at `a94738117b5df43522088adc726ffb98bd82644f` above the saves, quests and asset-loading review `773c658eccd69066f6592db2bc4cfc6add2fbb02`. Its four commits touch 166 paths. [Validation and component records](2026-11-22-upstream-366-sound-review-validation.json)

## Proposed PR description

Recover the sound request contracts shared by the lobby mixer, sound slots, actor effects and option window.

- Persistent sound requests keep the source identity and native position while the mixer updates or reuses a slot. The floor-dependent dispatch passes through the original return value.
- One-shot callers share the declaration and pass their actual position. Olga Flow uses its native position in five calls.
- Sound balance uses the shared window draw context and passes the actual label to both text-width calls.

The three linker label changes follow the corrected signatures. All 27,572 functions match retail, 2,447 units link from source, and all 1,147 original data bytes are accounted for. The probes cover four dispatch routines on all 36 floors, voice allocation and reuse, eight one-shot cases, and sound-balance drawing and text. The 195 direct persistent-sound calls and 1,198 direct one-shot calls retain their addresses.
