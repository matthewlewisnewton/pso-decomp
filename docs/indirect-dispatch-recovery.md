# Indirect controller dispatcher recovery

`TEffIndirectCtrl::run_task` at 0x802A88B0 is native C++, and the translation
unit around it is linked. `pso/effect/TEffIndirectCtrl.cpp` is the original
unit for `.text` 0x802A8140-0x802A9588: the seven earlier split files
(`TScene_802A8140`, `text_802A8210`, `TObjPlayer_802A8368`,
`TEffIndirectCtrl_802A88AC`, `TEffIndirectCtrl_802A9284`, `TEffIndirectCtrl`,
`text_802A9568`) are one file again. It also owns this range's `.rodata`, `.data`,
`.bss`, `.sdata`, `.sbss` and `.sdata2`. All 34 functions and every section are
byte-exact.

- **Compiler.** GC/2.0. Its block-copy scheduler interleaves the 36-byte
  snapshot tail with `actor_frame_tick`. GC/2.6 packs the tail and leaves the
  tick relocation four bytes later.
- **Snapshot.** `run_task` initializes a local
  `void (TEffIndirectCtrl::*)()` array with the three handlers. The compiler
  emits the 0x24 zero template in `.rodata` (`lbl_8046FBE8`) and the 3×12-byte
  pool in `.data` (`eff_indirect_task_table`), both `scope:local`, the same
  way as `TItemSpecialEvent_803531FC.cpp`.
- **Vtables.** The other vtable in front of `__vt__16TEffIndirectCtrl` is
  `__vt__13TUnk_804DDF04`. It belongs to the scene object that
  `fn_802A8210` constructs. It is in the same unit, which is why the
  standalone controller file could not own its `.data`.
- **Emission order.** MWCC emits vtables in reverse order of their key
  functions, and the `TUnk_804DDF04` vtable comes first although its
  destructor is earlier in `.text`. The unit is built with
  `-inline off,deferred`, and the source is written last-defined first.
- **Strings.** `-str reuse,readonly` keeps the two file names and the class
  name in `.rodata`.
- **Wave helpers.** The two wave helpers fuse one multiply-add each. The
  unit-wide `-fp_contract on` replaces the scoped pragmas they had before.
- **Scroll helper.** `-opt noprop` (#291) keeps the scroll offset as a
  named local.

The reasons and evidence for each switch are in
[porting-exceptions.md](porting-exceptions.md) section 5.

The sections below are the history of the search before the files were merged.
They describe earlier objects, not the current one.

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

The stack snapshot uses native `void (TEffIndirectCtrl::*)()` values, written as
an array initializer. The compiler copies the zero template at `lbl_8046FBE8`
and then the registrations from `eff_indirect_task_table`. No PMF words are
encoded in source.
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

## Review follow-up: typed recipe fields and linkage audit

The controller's 0x20 field is now a pointer to the real eight-byte
`TEffIndirectRecipe` layout (dispatch mode byte at 0x0, signed recipe bytes at
0x1-0x5, padding at 0x6, source-id byte at 0x7) instead of an integer indexed
through `((u8 *)m_20)[n]` casts. The constructor's recipe accesses use the same
type, and `get_indirect_recipe` is declared with that pointer (identical layout
and the same unmangled extern "C" symbol as its definition). This removes the
raw offset casts without changing any instruction under GC/2.6: the dispatcher
stayed at 95.61% and every other function in the unit and in all five consumer
units stayed exact. Building the same source with GC/2.0, which is what matches
the copy tail, makes `run_task` exact as well. The extern "C" audit below is
unchanged.

The names in the added extern "C" block were checked against
`config/GPOE8P/psov3/symbols.txt`: `eff_indirect_task_table`, `lbl_8046FBE8`,
`actor_frame_tick` and `lbl_805DE028` are plain original symbols, so the block
does not declare any C++-mangled name with C linkage.
