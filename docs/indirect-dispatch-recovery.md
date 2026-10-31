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
