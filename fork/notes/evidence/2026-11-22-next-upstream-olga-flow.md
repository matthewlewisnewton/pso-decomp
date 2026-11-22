# Recover Olga Flow phase, Mag, and attack interfaces

The local review `great-merge/review/after-366/olga-flow` is at `315777bbb10acfa77a8defe55704d17f5f02b202` above the actor position and population review `0a8586d2fe82628319f89e4f1b1d2fba88520d90`. One commit combines the tested implementation of the two related phase and factory changes across 35 paths. [Validation](2026-11-22-upstream-366-olga-flow-review-validation.json)

## Proposed PR description

Recover the original types and class owners used through both phases of the Olga Flow encounter.

- Both phases use their native spawn and motion records. Mag owns its actions, emitters, hit reaction and lifetime.
- Mines, sword waves and other phase effects use their native setup and position inputs.
- Callers share the scrolling-strip contract and use the actor's four typed attack-credit slots.

The sixteen linker labels follow recovered signatures, native construction and the Mag class owner. The review reproduces retail with 27,572 exact functions, 2,447 source-linked units and all 1,147 historical data bytes accounted for. Eight runtime suites cover phase dispatch and factories, Mag lifetimes, attack credit, motion and camera, contact and attacks, and strip and particle ownership.
