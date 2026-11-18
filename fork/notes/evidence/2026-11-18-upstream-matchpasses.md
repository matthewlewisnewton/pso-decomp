# Upstream matchpasses

## Front-end scenes

`great-merge/frontend-scenes` starts at upstream master `92a266f5eb`. Head `6a32eddbc2` contains five commits across 43 files (+449/−482). Most callers change only how they create the menu line controller. The eight-byte ending checkpoint is included in this branch.

| Commit | Review focus |
| --- | --- |
| `544c351c4f` | The ending fade and wall texture list have shared declarations across their writers and consumers. |
| `3db59f8252` | The ending scene constructor uses the class name from the scene setup unit. |
| `34e3191db7` | The drawing controller owns the relocated resource. Its tasks animate lines, start the next line by key and serve the title and selection screens. Four previously separate source-linked units become one. |
| `69d60d75a2` | The title sprites share their frame table. The menu font loader and upload task agree on the palette pointer type. |
| `6a32eddbc2` | Character selection owns its memory-card callbacks and load state. The adjacent four-byte keyboard channel mask belongs to the input polling unit. |

Against a fresh upstream build, the full GPOE8P check passed. The original DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 27,572 functions and 2,538 source-linked units are exact. Matched and linked data both increase by 64 bytes with zero address regressions. Six original inventory ranges contribute 60 bytes. The keyboard mask at 0x805D793C contributes the other four. Applying the exported patch to the pinned upstream tree reproduces the branch tree exactly.

## Network runtime

`great-merge/network-runtime` starts independently at `92a266f5eb`. The six commits through `7dfa6e1757` cover 18 files (+901/−577). Read the TCP queue and callback commits first, then the modem initializer, PPP buffers and broadband adapter helpers. Fork PR 457 is included. Upstream's matching check passes with the original DOL, all 27,572 functions exact, all 2,541 linked units exact and eight newly linked inventory bytes. The exported patch reproduces the review branch exactly. Git merged this branch and the front-end scenes branch cleanly in a tree-only check.

The [socket integration evidence](../../docs/evidence/socket-protocol-runtime.md) records both the exact and bounded builds. The adapter helpers passed the full 16-bit input sweep normally and under address and undefined-behavior sanitizers.

## Review queue

Use the subsystem and the question a reviewer can answer to set the boundary. Include the owning types, their callers, linker changes and relevant checks in the same PR. Keep independent steps visible as commits. Recent upstream examples covered 33 files and 57 files respectively. [Matchpass 22](https://github.com/zeroz41/pso-decomp/pull/301) and [Matchpass 21](https://github.com/zeroz41/pso-decomp/pull/300).

| Review family | Starting inventory bytes | Scope and dependency |
| --- | ---: | --- |
| Front-end scenes | 60 | Prepared and validated above. |
| Window lifecycles and results | 396 | Group the list, help, choice, keyboard and status windows with their shared window helpers and callers. Include the challenge and duel result screens and their page indicator. Refresh the base after PR 320 lands. |
| Already proposed in PR 320 | 176 | Six window recoveries have an existing upstream review. The constructor prerequisite also belongs there. Check the landed tree before cutting the windows branch. [Upstream PR 320](https://github.com/zeroz41/pso-decomp/pull/320) |
| Player, enemy and effect behavior | 272 | Group player combat pools and enemy or boss lifecycle and effect changes by shared behavior. The Gifoie and Photon Blast recoveries include their task lifetimes. The Photon Blast class-name recovery depends on a compiler alignment change. |
| Scene resources and rendering | 64 | Group the event archive names with scene resource loading. Group default lighting and rotation constants with the renderer, geometry and BML changes that use them. |
| Network runtime | 8 | Prepared and validated above. The PPP scratch buffers occupy 0x805D7A70–0x805D7A78. |
| Audio | 4 | Carry the area-music fade settings with the music sequencer work. |
| Original alignment padding | 4 | The Dark Falz range includes four verified padding bytes at 0x805D8A2C. |
| Already covered at the upstream baseline or outside its measured deficit | 163 | The ledger records the disposition by address. |
| **Total** | **1,147** | |

The rows account for the inventory. They also identify dependencies for packaging the broader integration branch. Resource interfaces and their game callers can travel together. Standalone build and progress tooling can travel with its fixtures and portability checks. The later review branches still require a current upstream base and independent validation. Refresh the queue as upstream accepts work. Keep the range ledger and LLM notes under `fork/` on the fork.
