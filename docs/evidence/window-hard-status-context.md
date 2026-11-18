# Hard keyboard status context and composer flags

This checkpoint follows `47475a3c41a2cce7e655d478672f6ffe3e4c0e8a`.
Hard's status renderer now receives the established `TWindowDrawContext` returned
through the existing draw-default-entry boundary. It reads inner_x/inner_y at
0x10/0x14 and depth at 0x38 directly. The old local overlay called the last field
“scale”; the division and floating-point evaluation order are unchanged.

The renderer's duplicate window/composer overlays are removed. It uses the
already evidenced borrowed m_composer and its m_b4 flags, preserving the null
and language guards and all branch tests. Hard run_task also uses the typed
composer flag field to clear bit 0x40 in the same order. No new initialization,
null guard, ownership transfer, cleanup or bug fix is introduced.

The complete status object preserves allocated payloads, section headers,
symbol metadata/order and all 35 resolved relocation targets after the single
pointer-parameter export rename. All other 3,635 active compiled objects,
including Hard's run_task/constructor/destructor owner, remain raw-identical.
The capacity-gated full build reproduces the original DOL byte for byte.
Independent source review found no blocker in this scoped repair. Fresh
aggregate checks, all 346 tool tests and portable behavior tests pass. Generated
retention changes only the renderer name and retains 19,454 entries without drift.

Existing pragmas are unchanged; their provenance is not newly established.
The integer-based draw-default/text-parameter interfaces, raw key query and
other callback/borrowed-lifetime qualifications remain. Hard's deleting wrapper
and original table are untouched. This is source-quality recovery with no
claimed matching gain or PR-readiness conclusion.
