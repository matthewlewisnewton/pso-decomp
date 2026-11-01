# Indirect controller dispatcher recovery (partial)

`TEffIndirectCtrl::run_task` at 0x802A88B0 is reconstructed as native C++.
The current 484-byte candidate is **not exact**: targeted objdiff similarity is
95.61%. No new exact-function or source-linkage gain is claimed. All ten existing
functions in its unit remain exact in the targeted object comparison. Full
baseline/candidate builds and check_pr have not been run for this partial candidate.

## Receiver, state and lifetime evidence

The original dispatch passes the current controller in r3 and no explicit
arguments to `__ptmf_scall`. The three registrations at `eff_indirect_task_table`
are `update_scroll_mode__16TEffIndirectCtrlFv`,
`eff_indirect_update_and_flush__FP16TEffIndirectCtrl`, and
`update_eff_indirect__FP16TEffIndirectCtrl`, in that order. Each registration has
zero receiver adjustment and the native direct-member-call discriminator. Their
original bodies consistently access the same controller layout. The two currently
free-function declarations take precisely that controller pointer; this patch does
not rename or redefine those handlers or the registration storage.

The stack snapshot uses native `void (TEffIndirectCtrl::*)()` values. The existing
36-byte zero template at `lbl_8046FBE8` initializes the snapshot, which is then
populated from the original registration table. No PMF words are encoded in source.
The recipe's unsigned mode byte admits indices 0 through 2; other values skip the
callback. The post-callback recipe reload and source-id byte store are retained,
followed by the original `sub_802A955C` call. There is no allocation, destruction or
new receiver conversion in this dispatcher.

The original guard reads the halfword at 0x46; demo mode bypasses that guard.
Recipe bytes 4 and 5 are sign-extended before 32-bit wrapping phase addition;
bytes 1 and 2 are converted as signed values to f32. The random update occurs every
32 frames, and retains the original single-precision multiplication order:
normalization times rand first, then signed recipe byte 3.

## Proposed shared-header correction

Two existing four-byte padding arrays become f32 fields at 0x48 and 0x50. Original
`run_task` stores with `stfs` at both offsets; the existing constructor initializes
both with a floating zero, and the existing scroll callback loads 0x48 with `lfs`.
The class retains size 0x54, all field offsets and its virtual slots.

This is a narrowly scoped header proposal for coordinator review. The four other
translation units that include this header were compiled with the original and
proposed header; all four complete ELF objects are byte-identical. No movement,
camera or quest contract header is changed.

## Remaining matching work

The external-template/explicit-native-PMF-copy candidate preserves existing code
and data matches. Remaining instruction differences are around the zero-template
copy tail, the frame-counter load/test, and the first registration loads.
Tested alternatives include explicit null array elements, empty/dynamic array
initialization, aggregate assignment with supported scoped inline pragmas, standard
memcpy, a bounded copy loop, earlier frame sampling, equivalent guard/cadence
expressions and declaration placement. These did not produce exact code. Literal
array initialization additionally introduces an owned zero template and shifts the
existing constant targets, so it is not the checkpoint candidate.

Further source scheduling work needs a new supported hypothesis; no volatile
qualifiers, fake effects, assembly or raw PMF construction were used. Whole-unit
linkage remains separate work: the inventory has only 4/20 owned data bytes exact.

## Follow-up: allocated field prerequisite and conversion-pool identity

The independently reviewed two-field correction is isolated as prerequisite
`d1c7d7fad4a180723cef46f03f5a910e82a67c02`, based on fork main
`54e6746b86fea52d2b949a8750492a43355655f9`. All five complete consumer objects,
including the unit without this partial body, are byte-identical before and after
that header-only change. This continuation depends on that prerequisite; PR149
remains a separate frozen draft.

The original and candidate conversion pools contain the same two eight-byte
objects at the same `.rodata` offsets (0 and 8). The original names
`TEffIndirectCtrl__data_8046FC48` and `TEffIndirectCtrl__data_8046FC50` correspond
to compiler-local pool entries at those offsets. All four signed-conversion
relocations in the dispatcher resolve to offset 0 in both objects; the other
existing conversion references resolve to the same native pool objects too.
The original assembly reference census finds these pool names only in this unit.
This proves pool byte/address identity; it does not resolve exported-symbol
requirements for future source linkage. No symbol scope, ownership or split is
changed here.

After resolving those local pool identities, only the frame-counter relocation
position differs in the dispatcher: original offset 0xe4, candidate 0xec.
The four instruction-word differences remain. A new hypothesis pass tested the
signed modulo cadence, a single-case switch, the compiler's native memory-copy
operation for initialization and assignment, and generated aggregate assignment
under its supported always_inline pragma. None reached exact code; the checkpoint
continues to use the clearer explicit native PMF assignments.

## Source-link closure in progress

The scroll helper now expresses the same owned angle scale as the other wave
helpers: the single-precision literal `182.04445f`. This removes an undefined
self-reference to `TEffIndirectCtrl__data_805DE02C` that would otherwise survive
when the unit is selected from source. The complete targeted object still retains
all ten existing exact functions and the same 16 bytes of `.rodata` and four bytes
of `.sdata2`. The dispatcher now uses the runtime's canonical `int rand(void)`
declaration from `<stdlib.h>` instead of a provisional long-return declaration;
the complete emitted object is unchanged by that interface correction.

A census of 7,414 existing original/compiled objects, substituting the candidate
for this unit's compiled object, finds no undefined references to the two pooled
conversion-bias names or the owned angle-scale name. The original assembly census
also finds their references only inside this unit. This supports a future narrow
`scope:local` proposal for those three split-artifact names once matching and all
link guards are satisfied. No such symbol-scope changes are included yet.

The latest probes record exact source, compiler, launcher and object hashes plus
the complete command and diagnostics. Size/performance modes, optimization levels,
single-pass/disabled scheduling, peephole control, adjacent installed compiler
patch releases, native record/array copying, deferred generation, and genuine
inline copy operators have not produced an exact dispatcher yet. These results
rule out those specific variants only. One failed alignment-declaration syntax
produced no object; the repository's supported alignment syntax compiled and
produced the unchanged best object. No impossibility or assembly-origin claim is
made. The owner continues with source-form and export/layout closure.
