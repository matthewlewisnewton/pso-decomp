# Ancient trap recovery (work in progress)

Base: `beaa7f52af2a7360e18deafc771648f51b709531` (fork PR #100). This is an unvalidated intermediate, not a completed or linked recovery.

At `0x80179970`, the update adds the field at `0x34c` to scale Y; while positive it dispatches area-specific positional sounds. On reaching zero it changes the halfword at `0x326`, updates flags and emits two effects, then selects the nearest player, adjusts a distance by body information and conditionally sends a hold. The state and field names remain provisional. The jump table at `0x804B4A78` maps cave, mine, ruins and VR spaceship area ranges to the four sounds in the implementation.

A target compile with GC/2.6 succeeds. Direct objdiff against the split original reports the new function at 89.85185%; the pre-existing constructor has regressed from 100% to 99.8366% and must be restored before this can be accepted. This comparison is not a full build or a linkage check. `play_sounds` is still absent. Its three chip parameter templates and switch table are currently outside the unit's claimed data ranges, and the source's provisional overlays and return types require further review. The original split warns that `.data` begins at `0x804B4A1C` despite an expected 8-byte alignment. No full build, `check_pr`, link scan, or independent review has been performed on this WIP.
