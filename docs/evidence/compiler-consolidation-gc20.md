# Consolidating the GC/2.0 compiler profile

The starting configuration at `08c178922f` assigns twelve game units to
GC/2.0. The initial consolidation target retained GC/2.6 as the game default and
linker, with GC/1.3.2 available for older game output. A compiler that
reproduces an object is a matching implementation choice, not proof of the
compiler Sega used.

A later [reverse sweep](compiler-default-gc20-impact.md) tests GC/2.0 as the
primary compiler instead of assuming GC/2.6 must remain. The
[older-library investigation](compiler-consolidation-older-libraries.md)
and [Slime source repair](compiler-consolidation-gc132-slime.md) also revisit
compiler-only failures using source changes. The initial retirement plan
below is conditional on its retained compiler set, not a settled choice.

## Compiler-only migrations

The following nine units move from GC/2.0 to GC/1.3.2 with their sources,
flags, symbol mappings and unit boundaries unchanged:

- `pso/unk/text_80049FD8.cpp`
- `pso/enemy/TObjEneGyaranzo.cpp`
- `pso/item/TItem.cpp`
- `pso/misc/TOExplosiveMachine.cpp`
- `pso/misc/TOTrapAncient01.cpp`
- `pso/effect/TEffIndirectCtrl.cpp`
- `pso/boss/TBoss7TentacleNeedle.cpp`
- `pso/unk/text_8031EF14.cpp`
- `pso/item/TItemSpecialEvent_803531FC.cpp`

Fresh compilations preserve allocated section contents, sizes, ELF
alignment, symbol layout and relocations. In particular, the current
`TEffIndirectCtrl.cpp` source retains its wave helpers under GC/1.3.2;
the earlier configuration comment about losing those helpers does not
apply to this source and its current flags.

A clean baseline build and an isolated candidate build containing these
nine configuration changes both reproduce `PsoV3.dol` SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The full repository checks pass:

- 27,444 exact functions and 4,241,872 matched code bytes, unchanged.
- 1,477,679 matched data bytes, unchanged.
- All 3,610 source-linked units remain exact.
- No address-coverage, code, data or source-link regressions.
- The 18,650-entry `force_active` inventory has no additions or removals.

Validation used the repository's configured compilers and toolchain, with
fresh baseline outputs. The candidate reused a private copy of those
outputs and rebuilt all nine changed compilation edges before linking and
generating its report. The original inputs and shared tools were read-only.

## Remaining GC/2.0 units

Three independent investigations tested natural source forms and supported
settings without finding a replacement that preserves existing matches:

| Unit | Exact functions lost under default GC/2.6 | Investigation |
|---|---:|---|
| `Boss5GryphonBehavior.cpp` | 3 | [Aggregate-copy scheduling and allocation](compiler-consolidation-gryphon.md) |
| `TObjEneSlimeTailAttack.cpp` | 1 | [By-value payload and prologue scheduling](compiler-consolidation-slime.md) |
| `TBoss8Dragon.cpp` | 2 | [Aggregate-copy aliasing and global loads](compiler-consolidation-dragon.md) |

These three units retain their GC/2.0 profiles and unchanged source. The
Dragon unit is not source-linked, but its existing exact functions must
still be preserved. The failed candidates were confined to scratch files.
The nine validated migrations do not retire GC/2.0; work on the next
compiler should wait for these remaining matching constraints to be resolved.

## Distribution labels and reported defaults

The `GC/...` directory labels are not the version numbers printed by the
compiler executables. Direct `-version` queries of the configured binaries
give:

| Toolchain label | Embedded PowerPC compiler | Reported runtime build date |
|---|---|---|
| GC/1.2.5 | 2.3.3 build 163 | 2001-04-23 |
| GC/1.2.5n | 2.3.3 build 163 | 2001-04-23 |
| GC/1.3 | 2.4.2 build 53 | 2002-01-10 |
| GC/1.3.2 | 2.4.2 build 81 | 2002-05-07 |
| GC/2.0 | 2.4.7 build 92 | 2002-09-16 |
| GC/2.6 | 2.4.7 build 107 | 2003-07-14 |

Thus six configured labels span three reported version numbers and five
version/build combinations. The executables still have six distinct
SHA-256 identities. In particular, GC/1.2.5 and GC/1.2.5n print the same
banner but produce different output in the consolidation audit. A banner
does not establish binary equivalence or historical Sega provenance.

The complete GC/2.0 and GC/2.6 help, including compatibility, obsolete,
deprecated, ignored and meaningless options, is identical except for the
version/build-date banner. Actual compilation with identical Dragon
production flags and `-opt display` appended after all existing options
also reports identical active settings: global optimizer level 4,
optimize-for-size, no extra global optimizations, peephole optimization on,
and scheduling for GEKKO. `-O4,s` has the same documented expansion.

These measurements find no exposed default-option difference that can be
corrected simply by spelling out the old settings. They do not prove that
all hidden state is equal. The version-conditioned alias implementations
described in [the Dragon investigation](compiler-consolidation-dragon.md)
change algorithms behind the same settings; the tested broader optimizer
switches do not restore the old output without other regressions.

The exact option-help query, after a normal tool installation, is:

```sh
for version in 2.0 2.6; do
    build/tools/wibo "build/compilers/GC/$version/mwcceppc.exe" \
        -help all,normal,obsolete,deprecated,ignored,meaningless,compatible
done
```

The local active-profile replay is
`python3 /tmp/pso-gc20-dragon/defaults.py`. It loads each original full
command from
`/tmp/pso-compiler-consolidation-20261113/objects/pso__boss__TBoss8Dragon.cpp/GC_{2.0,2.6}.argv.json`,
inserts `-opt display` immediately before `-c` (after `-O4,s`), and redirects
the object output to its scratch directory. Diagnostics and banners are
under `/tmp/pso-gc20-dragon/defaults/`; `compiler_versions.py` in the parent
directory replays all six banner queries. These commands do not change
the project's compiler assignments.
