# Ancient trap recovery (work in progress)

Base: `beaa7f52af2a7360e18deafc771648f51b709531` (fork PR #100). This is an unvalidated intermediate, not a completed or linked recovery.

At `0x80179970`, the update adds the field at `0x34c` to scale Y; while positive it dispatches area-specific positional sounds. On reaching zero it changes the halfword at `0x326`, updates flags and emits two effects, then selects the nearest player, adjusts a distance by body information and conditionally sends a hold. The state and field names remain provisional. The jump table at `0x804B4A78` maps cave, mine, ruins and VR spaceship area ranges to the four sounds in the implementation.

`play_sounds` creates three chip objects using independently initialized 0x4c parameter records, spawns a particle, and chooses a sound by floor area. Its original template records are at `0x80442D80`, `0x80442DCC`, and `0x80442E18`; its switch table is at `0x804B49D8`, followed by the existing update and movement switch tables at `0x804B4A1C` and `0x804B4A78`. The expanded split claims those contiguous ranges in this unit. The compiler-emitted records reproduce the complete expanded `.rodata` in the direct comparison; the data switch tables are not yet exact. These claims require full report-delta and link-input validation before acceptance.

A target compile with GC/2.6 succeeds. Direct objdiff against the split original using `functionRelocDiffs=data_value` reports `play_sounds` at 91.086205%, `vfunc_81` at 94.703705%, all 16 previously exact functions at 100%, `.rodata` at 100%, and `.sdata2` at 13.333334%. The `.data` section is not exact. This comparison is not a full build or a linkage check. The source's provisional overlays and return types require further review.

The existing `find_nearest_visible_player` declaration in `include/pso/player/TObjPlayer_80011014.h` takes `TObjEnemy *`, but this trap is not a `TObjEnemy`; the local `void *` boundary records the observed call at `0x80179AB8` until the shared interface is reconciled. No full build, `check_pr`, link scan, or independent review has been performed on this WIP.
