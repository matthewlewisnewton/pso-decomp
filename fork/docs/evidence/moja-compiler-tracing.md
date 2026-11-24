# Moja compiler tracing and Dreamcast-informed forms

Date: 2026-11-10. Follow-up to the
[first index investigation](moja-constructor-index-investigation.md), using the
same immutable PR 394 head `2484bc5ae9d6042a06d935a27663696d7d2bb99e`, fresh
original-object split, CodeWarrior GC/2.6, and isolated investigation worktree.
The investigation sections below record the original experiments. The subsequent
integration checkpoint records the byte-offset candidate's complete linked
validation. PR #418 retains these findings only; production source keeps the
approved scaled-offset lookup and its existing porting-exceptions entry.

## Byte-offset candidate integration checkpoint

The candidate tested in commit
`58b8f6356d6379238e0d4fa0d7b0c572bd7b29e2` applied the minimal byte-offset form,
retaining the existing clamps and compiler flags. The independent field-clamp
and inline-helper candidates were not included in that change.

That validation used baseline code at
`1a18b4bd7577af4ee367317064e020d1f91ce5a8`; the documentation-only base
`79768ce7da340723a8b6b559bca32fbdd705a5b2` has identical build inputs. Both the
unchanged baseline and replacement passed `python3 tools/check_pr.py`, using
fresh split objects/configuration and the pinned toolchain:

- Rebuilt DOL SHA-1: `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- All 3,590 linked units remain exact; force-active additions/removals: 0/0.
- Exact functions: 27,416 → 27,416; matched code: 4,213,640 → 4,213,640 bytes;
  matched data: 1,472,575 → 1,472,575 bytes.
- Linked code: 3,737,624 → 3,737,624 bytes; linked data:
  1,190,727 → 1,190,727 bytes. No coverage or denominator changes.
- Moja's owned section bytes, allocated sizes/alignment, function order,
  defined globals, and resolved relocations equal the baseline.
- `python3 tools/list_port_exceptions.py --check` and `git diff --check` pass.

These are historical results for the candidate, not a new validation run or
approval of its source form. [Review of PR #418](https://github.com/matthewlewisnewton/pso-decomp/pull/418#pullrequestreview-5847939484)
identified byte-address traversal as a different register-allocation workaround,
with no coverage gain, which the candidate's exception entry did not record.
The PR therefore restores the approved scaled-offset source and exception entry
unchanged from base `79768ce7da340723a8b6b559bca32fbdd705a5b2`. Only this evidence
document changes relative to that base; byte-address traversal remains an
experimental candidate requiring explicit approval and a complete register
entry before production use.

## Findings and recommendation

There is a **complete-unit matching candidate for the multiply/divide
round trip**: compute the byte offset once and actually use it as a byte offset.
It needs no compiler-flag change, but still uses low-level pointer casts and the
existing CSE pragma to preserve register allocation. Matching output does not
establish that the original source used byte addressing or justify replacing
the approved workaround with this form.

The compiler traces explain both obstacles to ordinary indexing. The shared
offset's virtual-register identity controls the r7/r8 result. Named clamp bounds
and literal bounds enter different frontend and constant-emission paths. The
strongest route to removing both workarounds remains recovery of the earlier
Moja functions and their shared literal pool.

An independent cleanup also matches: compare the probability fields directly
instead of copying them into two `chance` locals. The research round prepared
candidate patches under ignored `build/` and did not change production source,
configuration, splits, or a PR. It stopped at object comparisons; the subsequent
full-game integration check is recorded above.

## What the original compiler actually does

Five runs of the original compiler under retrowin32/GDB captured frontend AST,
backend PCode, and allocation logs. Four additional full-unit instrumented runs
observed constant rewriting, allocation, reuse, and emission. Hooks only read
compiler state. The four complete traced outputs match normal-wibo compilation
of the same sources in all allocated section bytes. The five register traces
stop at the constructor's code-generation end; complete objects were validated
separately with normal compilation.

### Integer registers

The approved source becomes `variant_offset = kind << 2` and two masked uses of
that local in the frontend AST. The initial backend emits the masks, then the
first peephole pass removes them. There is no runtime division. The named
offset retains its early virtual-register identity.

Ordinary indexing with the pragma creates two backend shift temporaries. A
backend CSE pass merges them, but their later identity survives. Immediately
before allocation, the operations and schedule are equivalent; the allocation
log records the difference:

| Form | Shared byte offset | Base-stat table pointer |
|---|---|---|
| Approved round trip | virtual r36 (`variant_offset`) → r8 | virtual r57 → r7 |
| Ordinary indexing, CSE off | virtual r57 → r7 | virtual r56 → r8 |
| Ordinary indexing, CSE on | virtual r40 (frontend temporary) → r8 | virtual r68 → r7 |
| Real byte-offset lookup | virtual r36 (`variant_offset`) → r8 | virtual r57 → r7 |

In these graphs, the later-created of the two interfering values gets colored
first and takes r7, leaving r8 for the other. This explains the four changed
instruction words. It also explains why enabling CSE repairs the table loads:
the frontend introduces a shared offset temporary before backend code generation.
The pragma does not disable every backend common-subexpression pass.

### Float registers and constants

With named bounds and CSE enabled, the frontend creates four float temporaries
for the bound loads before the backend creates the offset/parameter/sum
temporaries. Allocation puts the lower bound in f2, offset in f1, and
parameter/sum in f0. Literal bounds stay float-constant expressions in the AST;
their backend temporaries arise later, producing the desired lower bound f0,
offset f2, and parameter/sum f1. This accounts for seven changed instructions
per clamp, fourteen total, in the named-bound/CSE-on control.

The constant-emission trace establishes why substituting literals still fails
the complete-object comparison:

- Named 0.3f and 0.6f definitions emit before deferred function generation.
- In the current partial unit, literal zero/one are first generated in the
  constructor, at `.sdata2+8/+12`. Eight literal requests allocate two objects
  and reuse them six times.
- Ordinary named definitions are absent from that generated-float cache. The
  approved source and named-bound/CSE-on control make no literal-cache requests.
- Defining bounds before use lets the frontend substitute their values, but
  still emits the named storage and additional anonymous literal objects.
- The generated cache is shared across functions: in that visible-definition
  diagnostic, `run_task` introduces one, `load_resources` introduces zero, and
  the constructor reuses both.

One trace-guided probe also changes the offsets to ordinary 0.3f/0.6f literals,
uses direct indexing, and removes the pragma. All 2,204 raw instruction bytes
still match. The resulting pool is `[0.3, 0, 1, 0.6]`, however, and the named
offset exports disappear. This is not a usable replacement in the current split.

The mechanism supports recovering earlier functions that naturally introduce
zero then one, followed by the remaining pool and finally the constructor's
offsets. The proposed original-unit boundary remains unproven. Adding named
definitions or assigning the shared pool to the tail alone cannot recover this
emission sequence.

## Dreamcast-informed experiments

The pinned [Dreamcast v2 constructor draft](https://github.com/finalbillybong/pso_ver2_dc_decomp/blob/ff6f8e088f4040d38d9b674147789f49a2d48aef/nonmatching/objects/TObjEneMoja_ctor_8c038104.cpp)
suggested shared byte offsets, direct field clamps, comparison orientation, and
parameter-first addition. It is explicitly a nonmatching, generator-derived
draft with unproven equivalence; its byte arithmetic may itself be a decompiler
artifact. No source was transplanted. These are independently written variants
of this repository's constructor.

The source-form lane compiled 118 complete-unit probes, all warning-free:
64 direct-index/clamp/constant combinations, 12 byte-offset diagnostics,
32 inline-clamp combinations, six minimal byte-offset replacements, two typed
accessors, and two isolated field-clamp cleanups. Direct-index forms still fail
the constant references/layout or register match. Parameter-first additions and
top-level-const inline parameters provided no improvement.

The minimal exact replacement retains the existing clamps and uses:

```cpp
const size_t variant_offset = variant * sizeof(*lbl_805D50C8);
bind_enemy_combat_stats(
    reinterpret_cast<u8*>(*reinterpret_cast<BattleBaseStats**>(
        reinterpret_cast<u8*>(lbl_805D50C8) + variant_offset)),
    reinterpret_cast<u8*>(lbl_805D50CC[attack + variant * 3]),
    reinterpret_cast<u8*>(*reinterpret_cast<ActorParamBlock**>(
        reinterpret_cast<u8*>(lbl_805D50D0) + variant_offset)));
```

This removes the divide-back operation by giving the offset a real purpose.
Prefer `sizeof` over the also-exact `<< 2` diagnostic. The scope remains two
pointer-entry tables; it does not establish a general byte-buffer interface.

A typed `entry_at_byte_offset<T>(T** table, size_t offset)` helper containing
the same casts also matches with `-inline on,deferred`. It emits no extra helper
body. Its unrelated local switch-table label is renumbered, but resolves to the
same address. This improves readability at the cost of changing the unit's
explicit-inlining setting; it is not preferable merely for hiding the casts.

The byte-offset candidate, helper, and field-only cleanup were independently
checked against the already-matching PR source object: owned section bytes,
allocated sizes/alignment, function order, defined globals, and resolved
relocations all agree. All six functions match the fresh original target;
`.text` is 2,204 bytes, `.data` 776, and `.sdata2` 8. The minimal candidate was
also independently replayed with the recorded production compiler command.
These research checks preceded the complete linked validation recorded above.

## Reproducing the method

Build the recorded base with the pinned toolchain and a locally owned original
disc, following [CONTRIBUTING.md](../../CONTRIBUTING.md). Save its report and
compiled Moja object before changing a scratch copy. Use the exact base's split
configuration to generate the original comparison object; a neighboring build
directory's object is not sufficient provenance.

1. Capture the Moja compile command with
   `ninja -t commands build/GPOE8P/src/pso/enemy/TObjEneMoja.o`. Keep its flags;
   redirect the source and output to scratch paths. Compare the approved form,
   direct indexing with the pragma, direct indexing without the pragma, direct
   indexing with literal bounds, and the real byte-offset form shown above.
2. Compare each complete unit with objdiff's `functionRelocDiffs=data_value`.
   Also compare actual section sizes/alignment, raw bytes, defined globals,
   function order, and relocation targets/addends. A percentage alone misses
   extra constants and removed exports.
3. Run [mwcc-debugger](https://github.com/cadmic/mwcc-debugger) with the original
   GC/2.6 executable under retrowin32/GDB. This investigation used debugger base
   `bad9cea2423bed957188c930086f9dabe669d30c` with its GDB endpoint changed from
   `localhost:9001` to `[::1]:9001` for the local emulator. Supply
   the captured compiler command without the wibo/dependency-wrapper prefixes
   to `-a`, and select `__ct__11TObjEneMojaFP7TObjectPv`. Keep the production
   flags, including the absence of `-sym on`. Compare the final AST, initial
   PCode, peephole/CSE passes, and GPR/FPR assignment dumps as described above.
4. For the constant trace, log the following original-executable breakpoints
   without modifying compiler memory. Let compilation finish and compare its
   output with normal wibo compilation of the identical source. Count requests,
   allocation/reuse events, and section offsets, not just equal numeric values.

| GC/2.6 address | Observation |
|---|---|
| `0x433492` / `0x4340B1` | Function generation start/end |
| `0x547A10` / `0x547A75` | Named-constant rewrite eligibility / actual rewrite |
| `0x4E0700` | Generated float request and cache contents |
| `0x4E078D` / `0x4E0852` | Reused / newly allocated float object |
| `0x4B3BE5` | Generated float emission and section offset |
| `0x4B5380` | Named read-only definition emission |
| `0x5E9EFC` | Generated-float list head |

These addresses apply to the compiler executable with SHA-256
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.
The [mweppc source](https://github.com/doldecomp/mweppc/tree/919828d97d33d236da675824d43c5d57332afe74)
(`backend/Coloring.c`, `backend/TOC.c`, `frontend/CExpr.c` under `src/compiler`)
helped identify the implementation and addresses; observations above came from
the original executable. The register debugger stops after the selected
function, whereas the custom constant hooks let all six functions finish.

After integrating a candidate, run the full `tools/check_pr.py` gate against a
built current-main baseline. This final link step is distinct from investigation
of one object's matching behavior.

## Local reproduction artifacts

All extracted objects and compiler dumps remain ignored under
`build/moja-index-investigation/` in the investigation worktree. They are not
distributed with this repository; the paths below identify that local archive.

- GPR trace analysis: `compiler_trace_registers/FINDINGS_GPR.md`.
- FPR trace analysis: `compiler_trace_registers/FINDINGS_FPR.md`.
- Constant runtime report: `compiler_trace_constants/REPORT.md`.
- 118 source-form results and report: `dreamcast_forms/FINDINGS.md`.
- Independent object verification: `followup_verification.json`.
- Minimal byte-offset patch:
  `dreamcast_forms/byteoffset_unchanged_clamps_size_t_sizeof/candidate.patch`.
- Independent field-clamp cleanup patch:
  `dreamcast_forms/field_clamp_only_unscoped/candidate.patch`.

These replay commands require that local archive:

```sh
python3 build/moja-index-investigation/replay.py dreamcast_forms/byteoffset_unchanged_clamps_size_t_sizeof/TObjEneMoja.cpp
python3 build/moja-index-investigation/verify_followup.py
```

Trace runners, original command lines, source hashes, and tool hashes are saved
with each lane. Runtime tracing uses the local debugger/emulator installations
and serial access to port 9001. Wibo and debugger execution in this environment
require the approved host execution path described in the first report.
