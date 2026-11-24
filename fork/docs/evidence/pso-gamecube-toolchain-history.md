# Historical constraints on PSO's GameCube toolchains

Research date: 2026-11-16. This note separates release chronology, metadata
in the verified original executable, and hypotheses about compiler selection.
It does not identify an authenticated Sega project file or compiler manifest.
The matching-build experiments are recorded separately in
[the GC/2.0 adoption note](compiler-default-gc20-adoption.md).

## What history supports

A small set of GameCube compiler generations is plausible: a main game build,
older PowerPC runtime or retained game objects, and independently supplied SDK
and middleware libraries. The original executable itself carries library
build dates spanning December 2001 through October 2002. That supports
preserving library generations independently of the main game's compiler.
It does not establish exactly two or three compiler executables.

The Dreamcast origin establishes source ancestry, not a third GameCube binary
compiler by itself. Dreamcast SH-4 machine code cannot be linked as native
GameCube PowerPC code. Any retained game object in the GameCube DOL would
already have been built for GameCube. Shared source, assets and algorithms
could carry over; a claim about preserved PowerPC objects from early port
builds needs evidence from those builds.

## Development and release chronology

| Date | Evidence | Constraint |
|---|---|---|
| Early 2001 | In a June 28, 2001 account reproducing Yuji Naka's interview with Core Magazine, Naka described two months of GameCube R&D early that year, followed by porting PSO for an E3 demonstration. | The GameCube port predates the later 2002 compiler builds. This is a contemporary developer statement carried by a second publication, not a preserved build log. |
| 2002-09-12 | Nintendo's Japanese release archive lists the original GameCube Episode I & II on this date. | A compiler executable genuinely built after this date cannot have produced that first retail build. |
| 2003-11-27 | Sega's own CEDEC 2006 developer presentation lists Japanese Episode I & II Plus on this date. Contemporary Sonic Team news also announces Plus for this date. | Plus is a later revision; 2003 tools are chronologically possible for Plus even when impossible for the first 2002 release. |
| September 2004 | Contemporary US release coverage lists Plus in the week of September 13. The repository targets US Plus v1.02, not the first Japanese 2002 binary. | The first game's release date alone cannot date our target executable or exclude a 2003 compiler. |

Sources: [Naka interview excerpt, June 2001](https://www.nintendoworldreport.com/news/6160/phantasy-star-online-details),
[Nintendo's original Japanese release listing](https://www.nintendo.co.jp/ngc/before/02_0009.html),
[Sega developers Satoshi Sakai and Akio Setsumasa, CEDEC 2006, slide 4](https://cedec.cesa.or.jp/2006/archive/pdfXYZMMMM08087/r15.pdf),
[archived Sonic Team news, September 2 and November 14, 2003](https://backup.segakore.fr/sonicteam/pso/news/news_old_00.html),
[contemporary US release-week coverage](https://www.gamedeveloper.com/game-platforms/game-releases---week-of-september-13th-2004).
The Sonic Team site is preserved by a third-party mirror; the Nintendo and
CEDEC documents remain on their publishers' domains. US coverage is
contemporary reporting, not a Sega build record. No exact US release-day
claim is needed for the compiler comparison.

A January 2001 interview with Metrowerks' Brian Gildon independently confirms
CodeWarrior was already used by licensed GameCube developers and Nintendo's
OS work, and discusses the PowerPC/Gekko target. It establishes the tool
family's availability during the port's early development, but provides no
PSO-specific version number. [Direct Metrowerks interview](https://www.gamespot.com/articles/metrowerks-provides-codewarrior-for-the-gamecube/1100-2678095/)

## Compiler builds versus chronology

The following are the **locally queried compiler runtime build dates**, not
verified retail availability dates for the SDK distributions. Their banners
were recorded in [the compiler inventory](compiler-consolidation-gc20.md#distribution-labels-and-reported-defaults).

| Local label | Compiler banner | Build date | Historical interpretation |
|---|---|---|---|
| GC/1.2.5 and GC/1.2.5n | Embedded PowerPC 2.3.3 build 163 | 2001-04-23 | Fits early GameCube development and later prebuilt libraries. Identical banners do not identify which distinct executable supplied a library. |
| GC/1.3 | Embedded PowerPC 2.4.2 build 53 | 2002-01-10 | Fits development before the first GameCube PSO release. |
| GC/1.3.2 | Embedded PowerPC 2.4.2 build 81 | 2002-05-07 | Also fits that development period; chronology cannot choose it over GC/1.3. |
| GC/2.0 | Embedded PowerPC 2.4.7 build 92 | 2002-09-16 | Four days after the first Japanese GC release; plausible for subsequent revisions and Plus, but not literally that first retail build if the reported build date is accurate. |
| GC/2.6 | Embedded PowerPC 2.4.7 build 107 | 2003-07-14 | Too late for the original 2002 releases, but available chronologically before Japanese Plus. History alone does not exclude it from our target. |

These directory labels must not be equated with Sega project version names,
Nintendo SDK dates, or the version string printed by MWCC. The six
historical labels examined cover only three reported compiler version families;
several distinct builds within a family can generate the same instructions.
A matching function cannot uniquely distinguish those executables.

## Direct evidence inside the target executable

A read-only scan independently verified original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3` before inspecting metadata.
These are the executable's self-reported library dates, not an external
estimate of when the complete game was linked:

| Component | Recorded date/version | Original DOL file offset |
|---|---|---|
| Dolphin DSP | Build date 2001-12-17 | `0x4E8BF8` |
| Dolphin OS | Revision 54, kernel build 2002-06-05 02:09:12 | revision at `0x4E7B71`, date at `0x4E7BA8` |
| CRI ADX/CVFS/LSC/SJ and related components | 2002-06-13 builds, several component versions | e.g. ADXT at `0x4706A9`, CVFS at `0x471031` |
| ntUtl | 1.16.00, 2002-07-08 | `0x474341` |
| ntInf | 1.17.00, 2002-07-09 | `0x4F0F39` |
| mcFsGc | 1.10.00, 2002-09-17 | `0x473DD9` |
| ACCESS AVE-TCP | 1.16.1, 2002-10-23; SDK marker `12Dec2001Patch3` | `0x474011`, repeated library build at `0x4741F0` |

The OS and DSP dates also appear in the reconstructed
`libs/dolphin/src/os/OS.c` and `libs/dolphin/src/dsp/dsp.c`; the original-DOL
scan is the independent evidence. The ACCESS marker is an SDK identifier,
not a CodeWarrior version. A later library build against an older SDK is
visible directly here. Build strings can be retained or copied, so they
provide strong component provenance clues without proving every instruction
was compiled on the stated date.

Reproducer and metadata inventory:
`/tmp/pso-toolchain-history-20261116/inspect_dates.py` and `metadata.json`.
The scan reads the existing authorized original and does not modify or
redistribute the executable. No game assets or executable byte arrays are
included in this note.

## How this should guide consolidation

The proposed **GC/2.0 + GC/1.3.2 + GC/1.2.5n** set is historically coherent
as a *working hypothesis*: a later main GameCube build, an early-2002
PowerPC generation, and older SDK/middleware output. Object-level and full
link evidence should decide whether it is sufficient. Historical chronology
does not prove that Sega used exactly these three executables, or that every
runtime object belongs to one generation.

In particular, there is no historical reason here to force GC/1.3 output
onto GC/1.3.2 if that requires artificial source changes. Both are plausible
2002 builds. Nor does the identical GC/1.2.5/1.2.5n banner justify discarding
one without preserving its library output. The practical three-version
plan remains conditional on those remaining repairs.

The most useful next historical comparisons are earlier Japanese GC PSO
releases and the network trial: compare the same recovered functions and
SDK/middleware metadata across releases, then test only date-compatible
compiler builds. A function unchanged from a pre-September-2002 retail
binary would show that later compilers merely reproduce its code, rather
than prove they originally compiled it. Shared-library fingerprints in
Sonic Adventure 2 Battle can provide another independent comparison, but
matching teams or source ancestry alone cannot transfer its compiler choice
to PSO Plus. No authenticated Sega compiler project manifest was found in
this bounded search.
