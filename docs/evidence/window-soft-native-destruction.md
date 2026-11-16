# Soft keyboard native destruction and table ownership

This backports the Soft lifetime subset of `3a915a93c29dafb81cb749c96c00c5b1f70b86f2`
onto #562 (`68da9c9a0e`).
`TWindowKeyBoardSoft::~TWindowKeyBoardSoft() {}` replaces the hand-mangled raw
deleting wrapper. Soft is a genuine Base-derived class with scalar added fields;
normal Base destruction and inherited deletion emit the original 88-byte body.
No compiler-control changes, ordering probes or artificial virtual slots are used.

The compiler naturally appends its 24-byte table after the unchanged 548-byte
owned data prefix. The four targets are the Soft destructor, run_task, render,
and inherited TObject render_shadows. The old 84-byte original provider becomes
24 source-owned bytes plus a 60-byte original suffix at `0x804D001C`. That suffix
retains the unknown four-byte word and following 56-byte descriptor. The word
is **not** classified as padding or a virtual slot.

## Draw-context prerequisite

The 0x4C singleton allocated at `0x8024EDF8` is a `TWindowDrawContext`, not
an actual Soft window. Its nine context operations move to that existing type,
with their callers and symbols, so Soft can have the genuine 0x70 Base-derived
layout. The split-position helper receives borrowed x/y storage through
`WindowViewport.h`; its effect caller forwards that storage directly.
Keyboard glyph/outline/grid, key-frame, composer text and Word rendering use
context pointers for their existing context accesses. Soft flag accessors now
name the actual field at 0x60. The two Soft allocation producers use ordinary
`new`, forwarding their existing composer and client values.

The composer input-mode, Hard keyboard, Chat predicates/fields, Base rectangle
and String drawing contracts from #563 are outside this backport. Legacy
composer/text-record method labels and borrowed word transport remain qualified.
No compiler flag, pragma, alignment override, byte-offset cast, hand-written
table or substitute function is introduced.

## Validation scope

A fresh build on #562 matches the Soft destructor (88 bytes), constructor
(152 bytes), `TKeyBoardControl__ct` and `TWindowChat::open_next_input_window`
at 100%. All functions and allocated sections in the twelve touched source
units match at 100%, including the complete 9,096-byte TKeyBoardControl text
and its compiler-owned table. The split retains all 60 suffix bytes as original
input. Full build and address-based no-loss checks use the original DOL and
the prescribed main baseline; this is not a claim of raw compiler-ELF identity
with #563 or recovery of original translation-unit filenames.

## Remaining holds

This establishes native Soft destruction and compiler table ownership, not
portable borrowed-composer ownership, legacy callback/PMF lifetime, original
translation-unit filenames, or unknown-word semantics. Word, ComCard, other
window-family source-quality and compiler-provenance holds remain. No readiness
or merge claim follows from the matching gain.
