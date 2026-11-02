# GuildWarning recovery checkpoint — WIP, do not merge

This preserves the unfinished THunterGuildWarning class recovery and its unit at
0x80211718–0x802119F0. The class has explicit warning mode, timer and four Message
window pointers, with typed construction, destruction and task dispatch. It is an
unfinished source checkpoint, not a source-correctness or readiness claim.

Base: fork commit `f3441bb8ac8ded6b73c02bd13622105638abacfe`.
No new linked-unit, split, symbol/export or retention changes are included.
The broader controller/HUD and render-context experiments remain private to avoid
publishing a partially composed shared-provider migration.

## Known blockers

- The renderer retains provisional two-float pair and factory declarations.
  Canonical array-backed pair, Message factory, CDF/common-base construction,
  position/close/show contracts, descriptor storage, vtables and exports must be
  composed with their existing owners. The matching private owner-header variants
  are not included or approved by this checkpoint.
- The shared text getter, archive scalar storage, borrowed-text bounds and retention,
  message-entry storage and drain/teardown contracts need final qualification.
- HUD initialization can publish zero or partially converted texture entries after
  a returned resource/allocation failure, then execute thirteen unguarded setters.
  No dominating success/termination invariant or defined byte-identical failure
  model has been established. This is conditional native-path evidence, not an
  observed game crash. Normal successful archive evidence does not close it.
- The HUD loader needs a genuine u32 zero/ID/address carrier, actual record/surface
  construction, storage ownership/alignment, matching allocator and byte-copy APIs,
  and consumer closure. Earlier pointer-only HUD experiments are not adopted here.
- Current-root source compilation, complete native code/data/symbol/relocation
  comparisons, original-DOL equality, check_pr, unfiltered no-loss checks and actual
  ordered linker-input selection remain required before activation or readiness.

## Evidence limits and resume

Earlier private targeted probes reproduced 728 renderer instruction bytes, 40 data
bytes and 29 relocations under explicitly proposed contracts. Later private context
and loader probes preserved complete paired objects in their recorded scopes.
Those measurements do not validate this published head or its current dependencies.
No configured full build or check_pr was run for this save-only checkpoint.

Next: compose the independently qualified Message/base/pair and loader declarations,
resolve the first-setter pointer-state and lifetime obligations, then obtain exact-head
independent source review and scheduled development validation. Keep this PR draft.
Original assets, objects, disassembly, proprietary tools and private evidence are not
included. This checkpoint does not request or convey any previously denied peer message.
