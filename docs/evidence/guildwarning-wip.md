# GuildWarning recovery checkpoint — WIP, do not merge

This preserves the unfinished THunterGuildWarning class recovery and its unit at
0x80211718–0x802119F0. The class has an explicit warning mode, timer and four Message
window pointers, with typed construction, destruction and task dispatch. It is an
unfinished source checkpoint, not a source-correctness or readiness claim.

Base: main `7dc29c361014d08d901c826c28e85d73d613ee61` (PR branch merged onto it).
No linked-unit, split, symbol/export or retention changes are included.

## Current measured state

On this head every touched unit compiles byte-exactly under objdiff:

- `THunterGuildWarning_80211718`: `close_windows`, `sub_80211774` (600 bytes) and
  `sub_802119CC` at 100%.
- `THunterGuildWarning` (constructor), `THunterGuildWarning_80211648`,
  `_80211690`, `_802116EC`, `_80211700`, `_8021170C` and
  `psov3/pso/player/THunterGuildWarning` at 100%.

`ninja && check_pr.py --no-build` reports one new exact function
(`THunterGuildWarning__sub_80211774`, 0x600 code bytes), zero regressions and
PASS, with all 3553 previously linked units still exact. The renderer's constant
pair now refers to the split-owned `lbl_8044BC7C`/`lbl_8044BC84` objects instead
of re-defining them, so the unit no longer emits an unowned `.rodata` section.

## Known blockers

- The recovered renderer still uses placeholder pair/factory declarations.
  Canonical Message factory, CDF/common-base construction, position/close/show
  contracts, descriptor storage and exports must be composed with their existing
  owners. Byte-exact codegen does not by itself prove these declarations are the
  original ones.
- The shared text getter, archive scalar storage, borrowed-text bounds and
  retention, message-entry storage and drain/teardown contracts need final
  qualification.
- HUD initialization can publish zero or partially converted texture entries after
  a returned resource/allocation failure, then execute thirteen unguarded setters.
  No dominating success/termination invariant or defined byte-identical failure
  model has been established. That private experiment is not published here.
- Linking `THunterGuildWarning_80211718` has not been attempted; it is now an exact
  candidate but this checkpoint deliberately leaves `linked_units.txt` untouched.

## Evidence limits and resume

This conversion was checked with the configured full build and `check_pr.py` on
the merged head, but no original-DOL equality claim is made for a newly linked
unit because none was added. Next: compose the independently qualified
Message/base/pair and loader declarations, then obtain exact-head independent
source review and scheduled development validation. Keep this PR draft.
Original assets, objects, disassembly, proprietary tools and private evidence are not
included. This checkpoint does not request or convey any previously denied peer message.
