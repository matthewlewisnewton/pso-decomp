# Soft keyboard native destruction and table ownership

This checkpoint follows native construction at `0c4900191c351e81d36e628a115817a8341e27b4`.
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

## Validation scope

The complete-object proof checks unchanged prior allocated payloads, other symbol records and existing
relocation targets, apart from the new table definition and its four relocation
records, exact original function bodies and resolved targets, exact table
bytes/targets, and original suffix preservation. The other 3,635 compiled objects
remain raw-identical; both keyboard PMF cohorts are unchanged. The DOL is
raw-identical, with the sole ordered-provider replacement being the original
84-byte provider by its original 60-byte suffix. ELF table/symbol serialization
changes are expected; raw identity of the changed object is not claimed.

Post-retention-repair native build, all 346 tool tests, host behavior tests and
ASan/UBSan runs passed. A fresh continuation check against the preceding head
passes: zero function/code loss, +24 matched data and +24 linked data, 3,626 exact
linked units, and 19,454 retention names with no drift. Independent source review
found no blocker in the scoped four-file implementation.

## Remaining holds

This establishes native Soft destruction and compiler table ownership, not
portable borrowed-composer ownership, legacy callback/PMF lifetime, original
translation-unit filenames, or unknown-word semantics. Word, ComCard, other
window-family source-quality and compiler-provenance holds remain. No readiness
or merge claim follows from the matching gain.
