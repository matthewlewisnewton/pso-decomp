# Sonic Team GameCube toolchain comparisons

Research date: 2026-11-16. These comparisons guide hypotheses for PSO's
compiler consolidation; they do not authenticate Sega's original build
configuration. No production settings are changed by this note.

## Chronology from Sega and developers

Sega's official chronology places the Japanese Dreamcast Sonic Adventure 2
release on 2001-06-23 and Sonic Adventure 2 Battle for GameCube on
2001-12-20. These are release dates, not executable compilation timestamps.
[SEGA 2001 chronology](https://sonic.sega.jp/SonicChannelOld/chara/history/2001/index.html)

In a developer roundtable originally published in Nintendo DREAM's
November 2016 issue, Takashi Iizuka recalls requesting GameCube development
hardware from Nintendo of America immediately after finishing Adventure 2.
Jun Senoue describes the June Dreamcast release followed by December's
GameCube release. Iizuka also describes working through platform-specific
libraries. This is first-person retrospective evidence for the porting
sequence and library boundaries, but names no compiler or SDK revision.
[Nintendo DREAM publisher's Japanese interview, page 2](https://www.ndw.jp/sonic25th-interview01/2/)

Sega dates Sonic Adventure DX's GameCube releases to June 2003, with Japan
on 2003-06-19. Its PC edition is listed separately in December; those
platform releases must not be conflated.
[SEGA 2003 chronology](https://sonic.sega.jp/SonicChannelOld/chara/history/2003/index.html)

## What the matching projects actually configure

These are directly inspected repository configurations, not claims that
all selected code has already been matched or that a selected linker is
historically unique. Branch URLs were read on the research date.

| Project | Game / engine profile | Runtime and debugger | Dolphin SDK | Linker |
|---|---|---|---|---|
| SA2B (`GSNE8P`) | GC/1.2.5 for ordinary RELs and Ninja; GC/1.2.5n for Chao | GC/1.2.5 runtime/MSL; GC/1.1p1 MetroTRK | GC/1.2.5, with GC/1.2.5n for selected libraries | GC/1.3.2 |
| SADX | REL helper inherits GC/2.0 | GC/1.3 runtime/MSL; GC/1.3.2 MetroTRK | GC/1.2.5n | GC/2.0 |

Sources: [SA2B configure.py](https://raw.githubusercontent.com/roeming/SA2B/main/configure.py),
[SADX configure.py](https://raw.githubusercontent.com/doldecomp/sadx/master/configure.py).

The SA2B configuration marks numerous SDK and some game objects matching,
but its README still describes the generic project scaffold; no complete
SA2B reproduction was performed here. SADX explicitly has unfinished game
flags and disables rebuilding RELs. Most listed SADX runtime and MetroTRK
objects are marked nonmatching. Its configuration therefore supplies a
useful candidate grouping, with limited evidential weight for exact
historical compiler identity.

SADX's inspected commit-history page identifies latest listed commit
`4c2b833be9b4b63d57d761beb647cb8d9acbedb6` (2024-08-01). Fetching that immutable
file through the research browser failed, so this note cites the successfully
read branch file rather than falsely claiming a verified immutable snapshot.
The SA2B browser pages did not expose a reliable commit hash.
[SADX commit history](https://github.com/doldecomp/sadx/commits/master/)

## Implications for PSO

The locally queried compiler banners are documented in
[the compiler distribution/version note](compiler-consolidation-gc20.md).
They date GC/1.2.5[n]'s compiler to April 2001, GC/1.3 to January 2002,
GC/1.3.2 to May 2002, GC/2.0 to September 2002 and GC/2.6 to July 2003.
These are dates embedded in our compiler executables, not independently
verified public release dates of the corresponding development kits.

Several conclusions follow, with distinct confidence levels:

- **Strong chronological constraint:** the initial December 2001 Japanese
  SA2B release predates our GC/1.3.2 compiler, and the initial June 2003
  GameCube SADX releases predate our GC/2.6 compiler. Those specific later
  compiler builds cannot have produced those earlier initial releases if
  their recorded dates are accurate. Later game revisions require their
  own analysis.
- **Important limitation:** SA2B's configured linker is GC/1.3.2 despite the
  earlier first release. The inspected target is the US edition, and its
  exact executable revision/date was not authenticated here. Regardless,
  this is a warning against reading a modern matching project's linker
  selection as proof of its original development environment. The local
  banner table dates compilers; it does not independently date each linker.
- **Useful candidate family:** SADX independently suggests GC/2.0 for
  game/linking, GC/1.3 for runtime/MSL, GC/1.3.2 for debugging support, and
  GC/1.2.5n for SDK code. This gives GC/1.3 a specific nearby-project
  precedent; it should not be silently relabeled GC/1.3.2 just because the
  latter is our consolidation preference.
- **Plausible grouping, unproven count:** both projects distinguish engine,
  runtime/debugger and SDK compilation profiles. Neither establishes an
  exact three-compiler rule: each inspected configuration names four
  distinct versions when the linker is included. A two- or three-version
  PSO reconstruction may still be achievable through output equivalence.

Dreamcast ancestry identifies source and engine heritage, not an executable
object archive that can be linked unchanged into the GameCube port. The
relevant retained versions here are PowerPC compiler profiles. The useful
historical model is successive GameCube game builds plus separately built
PowerPC runtime, SDK and middleware components.

For our later PSO Plus target, SADX chronology alone cannot exclude a
2003 compiler. The PSO-specific timeline and binary clues must decide which
versions were available for that exact edition. No Sega build manifest,
original project file, authenticated tool log or unique compiler fingerprint
for PSO was recovered in this comparison. Historical clues should prioritize
experiments, while full object and DOL validation decide which profiles the
reconstruction can safely use.
