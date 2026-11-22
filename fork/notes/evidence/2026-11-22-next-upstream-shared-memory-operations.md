# Share the allocation, copy and release interfaces

The local review `great-merge/review/after-366/shared-memory-operations` is at `848e38d3679eb90d80c35f80e25f83bf3da4ad0c` above the sound review `a94738117b5df43522088adc726ffb98bd82644f`. Its single commit touches 227 paths. [Validation](2026-11-22-upstream-366-shared-memory-review-validation.json)

## Proposed PR description

Use the shared declarations for raw allocation, release, and byte and word copies. Move the nullable release helper out of character selection so game, scene, asset and window code can depend directly on the memory interface. The helper keeps its existing name and address, and the one linker-label change follows its new owner.

The build reproduces retail with all 27,572 functions exact, 2,447 units linked and all 1,147 starting data bytes accounted for. The retail and review probes cover overlapping copies, allocation results, null release, and ordered footprint texture teardown.
