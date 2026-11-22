# Recover actor positions, population and encounter setup

The local review `great-merge/review/after-366/actor-positions-and-population` is at `0a8586d2fe82628319f89e4f1b1d2fba88520d90` above the camera and scene review `a3cd2e2647cfa0885abc15cf9d7be86a6929e9ea`. Its six commits touch 107 paths. [Validation](2026-11-22-upstream-366-actor-positions-review-validation.json)

## Proposed PR description

Carry the native actor records from population and spawn through movement, attack selection and resource release.

- Actor position initialization and copies use their shared character owner. Movement and contact routines receive their original destinations.
- NPC population uses its native records and the typed REL loader. Enemy battle setup uses typed stats, motion and attack inputs.
- Sharks use native construction and resource ownership. Fly, Flower and Recon use their original factory, attack and encounter records.

The review matches retail with 27,572 exact functions, 2,447 source-linked units and all 1,147 original data bytes accounted for. Runtime probes cover 384 battle table entries, 32 complete loads, 56 NPC archive lifecycle cases, Shark constructors and lifetimes, flight and ground movement, and Flower and Recobox behavior.
