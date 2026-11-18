# Earlier compiler candidates for the runtime and libraries

Investigation at `08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`, with the nine
GC/2.0-to-GC/1.3.2 game migrations already present in the working tree.
No production sources or compiler assignments were changed by this investigation.

## The proposed GC/2.6 moves do not require GC/2.6

All **42 GC/1.3 library/runtime units** that the earlier audit proposed moving
to GC/2.6 also reproduce the existing object under **GC/1.3.2 without source
or flag changes**. Fresh compilation of all 42 with both GC/1.3 and
GC/1.3.2 confirmed equivalent allocated section contents, sizes and ELF
alignment, defined external/weak symbol layout, and normalized relocation
positions, types and targets. Comparison against the original split objects
found no lost exact functions in these 42 candidates.

The 43rd proposed GC/2.6 move, `pso/misc/QuestDownloadBuffers.cpp`, also
reproduces its existing GC/1.2.5 object under both GC/1.2.5n and GC/1.3.2.
Both alternatives were freshly compiled and checked by the same object
comparison. That unit therefore need not move to the game compiler either.

These were proposed migrations, not already applied migrations. GC/2.6 was
preferred by the earlier audit when several versions gave equivalent output;
the preference did not identify a technical requirement for that compiler.
GC/1.3.2 is a reasonable alternative default for this runtime group regardless
of whether the main-game default remains GC/2.6 or becomes GC/2.0.

GC/1.2.5n is a different candidate: only one of those 42 runtime units
(`TRK_MINNOW_DOLPHIN/target_options.c`) reproduced the existing object in the
earlier unchanged-source sweep. This investigation did not attempt to rewrite
the other 41 runtime units for GC/1.2.5n. The SDK/MusyX/network profile and the
GC/1.3 runtime profile should not be treated as interchangeable solely because
both are older than the main-game compiler.

## What still blocks retiring GC/1.3

Of the **53 GC/1.3 library/runtime C/C++ units**, **45** reproduce their
existing objects under GC/1.3.2 unchanged. In addition to the 42 above, these
are `NMWException.cp`, `printf.c` and `scanf.c`; all three were freshly
compiled under both versions. The four GC/1.3 game units and two generated
assembly entries are outside this library count.

The remaining eight units lose 18 currently exact functions under an unchanged
GC/1.3.2 compile. All eight are currently source-linked. Fresh GC/1.3 and
GC/1.3.2 compiles, and comparisons to the original split objects, reproduced
the prior audit's losses:

| Unit | Exact functions lost | Observed difference / investigation |
| --- | ---: | --- |
| `TRK_MINNOW_DOLPHIN/mem_TRK.c` | 1 | Trailing `length &= 3` becomes one mask instruction instead of load-immediate plus register AND. |
| `TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c` | 1 | `TRKReadUARTPoll` changes buffer-address formation and register assignment. |
| `MSL_Common/Src/strtoul.c` | 2 | Decimal digit-store registers and 64-bit multiplication scheduling differ. |
| `MSL_Common/Src/mem_funcs.c` | 4 | Each copy helper's trailing `n &= 3` loses the separate load-immediate instruction. |
| `MSL_Common_Embedded/Math/Double_precision/s_atan.c` | 1 | Array-address formation introduces extra address instructions; 512-byte function becomes 536 bytes. |
| `MSL_Common_Embedded/Math/Double_precision/e_pow.c` | 1 | Existing candidate is 91.41%; no source repair attempted in this bounded pass. |
| `MSL_Common/Src/alloc.c` | 4 | Existing candidate changes `free`, fixed-pool deallocation, `SubBlock_merge_next` and `Block_link`; no source repair attempted in this pass. |
| `MSL_Common/Src/ansi_fp.c` | 4 | Five function outputs change, including internal helper emission; four were exact before. No source repair attempted in this pass. |

Paths beginning `MSL_Common` or `MSL_Common_Embedded` are relative to
`PowerPC_EABI_Support/MSL/MSL_C/`.

## Bounded source experiments

The five smaller cases above received **42 exploratory source variants** and
nine accepted flag variations. None produced an equivalent complete object.
The results establish a remaining repair burden, not impossibility:

- Eight mask/remainder expressions each for `mem_TRK.c` and `mem_funcs.c`
  included a named mask, a constant named mask, `sizeof(unsigned long)`,
  modulo, complement, signed masking and subtracting the complete-word
  portion. The straightforward expressions still fold to the newer mask
  instruction. Subtraction formulations alter other instructions. Disabling
  propagation or strength reduction did not repair the difference; disabling
  peephole optimization changed much more code.
- Ten UART index/pointer formulations included separate index updates, named
  pointers, separate byte loads, unsigned indices and equivalent pointer
  expressions. The best score was 98%, versus 97.75% unchanged, but the
  original instructions were not recovered.
- Six 64-bit multiplication expressions and eight decimal digit-store
  expressions in `strtoul.c` did not restore either differing function.
- Grouping `atan`'s existing constant tables into a structure or one array
  did not recover the original addressing. Pooling and propagation flags
  also failed. These grouping experiments preserved the existing source
  constants; no values were extracted from the original binary.

Three additional diagnostic flag probes were rejected by the compiler's
option parser: `-opt noexpressions` on the two memory units and
`-opt noaddressmode` on `s_atan.c`. They are excluded from the nine accepted
flag variations. The compiler returned success despite the usage warnings,
so unchanged output from those probes is not evidence about an optimization.

There is no successful source patch to integrate from this pass. The 45
unchanged-source runtime candidates are substantially more straightforward
than the eight repairs; the five closely inspected mismatches are backend
code-generation differences that did not yield to the tested ordinary source
expressions. GC/1.3 retirement should remain a separate measured task rather
than being inferred from the ease of the 45 assignments.

## Validation and reproduction

Artifacts are isolated under `/tmp/pso-older-library-compiler/`:

- `probe_fresh.py` and `fresh-results.json`: both compilers on all 42 proposed
  GC/2.6 library moves.
- `verify.py`, `verification-results.json` and `original-verification.json`:
  fresh compiles of the eight remaining runtime units and original-object
  comparisons for those eight plus the 42 candidates. This 50-unit subset
  has 143 exact baseline functions and 18 losses, all in the eight blockers.
- `final_validation.py` and `final-validation.json`: the three additional
  GC/1.3.2 runtime candidates and the shared quest-download buffer unit.
- `probe_sources.py`, `probe_more.py`, `probe_strtold.py` and their result JSON:
  64 diagnostic compiles comprising ten baseline/unchanged compiles, 42 source
  variants, nine accepted flag variants and three rejected-option probes.
- Per-unit directories contain source variants, complete command arguments,
  compiler diagnostics, objects and objdiff reports.

The scripts reuse the comparison helper from
`/tmp/pso-compiler-consolidation-20261113/normalize.py`. It resolves anonymous
local relocation targets to section/offset, while preserving external symbol
identity. Original comparison inputs are the verified original-DOL split from
that audit. Tools, compiler executables and generated headers are read-only
inputs from `/home/matt/workspace/pso-decomp/build/`. Compilation was serial
within this investigation and used private output paths.

These are object-level feasibility results. CodeWarrior comment metadata,
the integrated linker, final DOL hash, source-link retention and all
`tools/check_pr.py` checks still require validation before applying a library
migration. No full-library migration or integrated validation was performed
by this investigation. Neither equivalent output nor a compiler mismatch
establishes Sega's original compiler or source spelling.
