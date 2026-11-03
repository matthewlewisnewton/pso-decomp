# Effect parameter storage and copy

This extracts the bounded parameter-storage part of the Dragon work. It changes
one 44-byte copier, its seven callers, and the direct template-copy storage in
the same three translation units. It does not change geometry algorithms,
actor construction, virtual slots, data ownership, compiler profiles, or source
selection. It claims no new matched bytes or linked unit.

`EffectGeometryParameters` is one complete twenty-byte record. The copier and
geometry boundary use the actual float members at offsets 4 and 8. Local copies
now contain those members instead of treating a scalar prefix or a byte buffer
as a different complete record. The first eight bytes and final eight bytes
are copied through character views of the complete objects; the float at 8 is
assigned as a float. The scoped scheduling pragma preserves the native order.

The prior private review used an opaque prefix/suffix record. Current main has
since recovered two templates as constant `DragonAttackParams` aggregates. This
extraction retains their initializer values, const qualification, data placement,
and existing scalar representations at the other offsets in the shared record.
Those other fields keep provisional names and receive no new semantic meaning.
The other existing Dragon attack templates keep their separate original type.
The eight external templates keep their names and storage owners. No generated
alias or replacement data allocation is introduced.

The extracted source contract passed independent review at
`5096f459ef2b03b5f0103a9ddfaeb7bdcc2768a2`. The follow-up is composed on fork
main `909d120b21f7e875e71a5c1d0d3a7799a08078e9`, which includes the genuine
Lightning construction merged from #243 at `9be3f5e6c`. Both include additions in
Gryphon are retained. The three actual dependency contexts were rebuilt with main's changed
`TBoss4DarkFalz.h`; the old per-object receipts are kept as historical evidence.

Fresh paired full builds preserve all 462 existing function bodies, allocated
section bytes and metadata, symbol records, and 7,192 physical relocations
across Dragon1, Dragon8, and Gryphon. Dragon8 and Gryphon objects are raw-file
identical. Dragon1 has 45 compiler-local label renumberings; each correspondence
has the same binding, section, offset, size, type, backing bytes, and relocation
identity. The copier still matches all 44 native bytes.

Both builds reproduce the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, and their linked ELF allocated
bytes/layout agree. All 5,013 ordered linker inputs are identical. Among 3,692
active source objects, only Dragon1's local-label strings differ. The full
`tools/check_pr.py` gate passes with zero function/code/data/link losses and
zero matching or linkage gain; all 3,551 source-linked units remain exact.

The baseline includes the canonical Dark Falz symbol attributes. G2 introduces
no symbol address, extent, export, split, selection, or retention delta.

The allocated storage/copy repair preserves the surrounding legacy code.
Existing return-type, receiver, actor-lifetime, and curve obligations remain
separately allocated. The user's merge process owns final integration acceptance.
