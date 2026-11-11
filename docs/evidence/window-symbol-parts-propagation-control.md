# Parts float exports: provenance audit and bounded propagation control

This follows the [native lifetime/export hold](window-symbol-parts-lifetime.md)
and the new upstream lead recorded in the
[Word control note](window-word-native-vptr-control.md). The verified clean stack
was main `e65f11ce6ec99c006909422f81da1c0a46ac062e`, focused
`37ed8308f9df0e8ff4426bcc187f378f337a2cbc` and continuation
`e0dfa3c92f12a756a753a4418ca5bf9284273486`. No competing head update or Parts PR
was observed in the targeted open-PR check. Production source, symbol scopes,
providers and all technical holds remain unchanged.

## What changed upstream

The pinned upstream source at
[`8c507b2dacae5428291a823c3868ca486419660c`](https://github.com/zeroz41/pso-decomp/commit/8c507b2dacae5428291a823c3868ca486419660c)
has Parts blob `40811abe0cb49deba7bd12ea7f9f3d0b92d20855`. Local Git history
identifies its source change as
[`23795dfa1d27576b0cd4034d2fb37c47583969ab`](https://github.com/zeroz41/pso-decomp/commit/23795dfa1d27576b0cd4034d2fb37c47583969ab),
merged [upstream #243](https://github.com/zeroz41/pso-decomp/pull/243).
Elias's recovery adds scoped `opt_propagation off` to both row helpers, replaces
the named32.0f load in `fn_802857C4` with a literal and reconstructs
`fn_802855C4` with an explicit 8.0f `.sdata2` definition just before it.
The same commit localizes seventeen floats in [805DD7C8,805DD810), keeps
`lbl_805DD808` exported and adds Parts to its linked-unit list. Its split range
does not move. Earlier #196/#198 findings remain valid for their pinned heads.

The commit and PR explicitly motivate the 8.0f definition's location by pool
order. Their CI reports a matching DOL, but no Word/Parts retail build profile or
independent original-source provenance for these controls is supplied. The
8.0f value/read is behaviorally supported; a matching output does not justify its
chosen definition location or the propagation setting. This is reconstructed
source evidence, not authorization to import its matching controls or scope edits.

The compiler reference describes `opt_propagation` as controlling copy and
constant propagation. Existing repository uses demonstrate availability, not the
original setting for Parts. No upstream source or explicit constant definition
is imported into the production unit here.

## Current ownership and reference census

The current generated split configuration and report supply 4,966 original and
3,633 compiled consumer objects. All are present; retired split files are excluded.
A census of 512,252 relocations resolves catalog names plus addends, defined
section-relative targets and absolute symbols. It finds 100 references into
[805DD7C8,805DD810), all within original/compiled Parts. None is external to the
unit. The published compiled Parts object alone has an undefined pool label,
`lbl_805DD7F8`. The other floats have no named compiled-source dependency.

Thus the eighteen exports remain a concrete current link gate, rather than
eighteen independently evidenced external API objects. Absence of external
resolved references does not itself establish original linkage, exclude computed
runtime addresses, validate source freshness or permit localization. The active
configuration/report census and unchanged production-source checkpoint qualify
this observation; no scope change is applied.

## Discriminating four-case control

The fixed source is the current typed/native Parts unit. Only `fn_802857C4`
varies along two axes: its existing extern 32.0f load versus literal 32.0f, and
inherited propagation versus scoped `opt_propagation off`. The extern declaration
is removed only in literal cases. Every other function, field, expression,
definition order and option remains fixed. In particular, the already-matching
typed `fn_802855C4` remains unchanged. No explicit 8.0f definition, section control,
data reorder, local-variable permutation or upstream helper replacement is tried.

The four successful scratch compilations use the pinned production GC/2.6 and
wrapper under the shared legacy-exclusive capacity gate. Baseline source SHA-256:
`fd73641595c8227c426e2e76530d883ee12f5f915cf30557239127e6106c41e6`.
Literal/off source SHA-256:
`47f47e4744fd2ada4839b37fb549eca5f291f4363f358763d0fadaf25d03b454`.
The compiler SHA-256 remains
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.

| Scratch source | Exact bodies and relative resolved targets | Undefined pool label | All 198 owned resolved relocations exact |
| --- | ---: | --- | --- |
| Extern / inherited | 20/20 | 805DD7F8 | Yes |
| Literal / inherited | 19/20 | None | No |
| Extern / off | 20/20 | 805DD7F8 | Yes |
| Literal / off | 20/20 | None | Yes |

Extern/inherited reproduces the published complete ELF. Extern/off is also
byte-identical to it. Literal/inherited changes eleven instruction words in the
484-byte helper and its relocation use, reproducing the earlier bounded literal
failure. Literal/off restores all 20 original function bodies in original order,
all 4620 text bytes and all 198 resolved relocation records. No native symbol
identity remapping is needed against the current original split.

All four cases retain original 44 data, 8 rodata and 72 pool bytes, their sizes and
alignments. The existing `.sdata2` flags difference remains: original 2 versus
compiled 3, shared by the published baseline and every control. Complete allocated
headers therefore are not claimed original-equal. Literal/off has neither an
undefined pool label nor a named exported definition of any of the eighteen
floats; its internal references resolve to the original pool addresses.

Two runner failures are isolated privately: an initial sandbox-stopped invocation
produced no object, and an incorrect scratch-source insertion was rejected as
syntax before the affected helper could compile. Correcting the runner produced
the intended fourth case; the first three completed controls were retained without
recompiling them. Neither failure evaluated another source hypothesis.

## Result and stop condition

The control isolates propagation as sufficient to restore this literal helper's
matching output. Upstream's explicit 8.0f definition and second helper rewrite are
unnecessary for this fixed typed/native scratch source. That result is specific
to this source/context and does not invalidate another reconstruction's needs.
It does not establish a source-correct reason to disable propagation in retail
Parts. Adopting the setting solely because it matches would cross the existing
no-steering hold.

No production literal, pragma, symbol localization or source-provider activation
follows. There is no full-game candidate build or candidate DOL-pass claim.
The selected original Parts object remains the sole executable provider; its
native producer remains source-linked. All protected original units/remainders,
Word's actual order/destination hold and other ownership/interface holds stay.

The next useful evidence is independently justified original source/compilation
context for this control, or a source-correct explanation preserving the load's
value lifetime under the established profile. Another constant placement,
declaration-order or optimizer sweep is not justified. Any later activation needs
current complete-reference/freshness qualification, exact owned sections and
actual relocations, retention/provider/no-loss gates, full original-DOL build and
independent review.

Private reproducible source controls, receipts and proofs are in
`pr403-parts-control/`: `compile.py`, `compile-receipt.json`, `audit.py`,
`object-comparison.json`, `reference-census.json` and pinned upstream files.
Original objects, binaries and raw disassembly are not published. Independent
read-only review confirms the bounded comparison and its limitations. Evidence
publication changes no production source/profile, provider or coverage metric.
