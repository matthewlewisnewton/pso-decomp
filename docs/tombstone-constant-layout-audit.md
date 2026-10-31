# Tombstone constant-layout investigation — rejected WIP candidate

This branch preserves a bounded source experiment. It is not ready for merge or linking. The live PR113 and original worker checkout are unchanged. The starting head is `b11b468231936524f859d7c85a3440324c3dbc0f`; the earlier layout experiment is `34193d66b36bc7ca8174f52996251f29464c6fad`.

## Result

The source on this WIP branch uses compound assignment with the three named fade constants and named zero/one clamp bounds. It emits exactly the original 44 `.sdata2` bytes and 16 `.rodata` bytes, but `draw_name_labels` matches only 99.11504%. The other eight functions remain exact. Its `.sdata2` alignment is still 8 versus the original split's 4. It therefore loses one previously exact 904-byte function (2288 -> 1384 exact code bytes), so it fails the no-regression requirement and must remain an experiment.

The nine-function baseline was independently reproduced at 100% code, with 52 small-data bytes rather than 44. In the bounded probe corpus, natural placement without section declarations moves exported floats into `.sdata`; it does not preserve the original SDA relocation section. Naming the clamp bounds removes duplicate literals but changes fade FPR allocation. Explicit locals or reordered bound loads did not restore the exact code. These are finite observations, not a claim that no source solution exists.

## Original ownership and consumers

Read-only ELF relocation audit covered all 5067 original split objects available in the prepared worker tree. The complete 24 relevant relocations and definitions are in `experiments/tombstone-constant-layout/original-consumers.json`.

- `lbl_805D9170` is defined by the unassigned split `auto_11_805D9170_sdata2.o`, not by the tombstone object. Its only observed original callers are `TLobby::reset_tombstone_values` in `pso/unk/text_80074E48.o` and `TObjTombstone::is_other_tombstone_closer` in this unit. The existing split ownership plus shared uses do not establish which reconstructed source unit should own it. No split was extended over this preceding word.
- `TObjTombstone__data_804387B8` is owned by this tombstone split, but also referenced by `TObjTombstone__sub_80075DFC` in neighboring `TObjTombstone_80075DA8.o`, in addition to this unit's projection and name drawing. The compiled conversion pool has matching bytes but only a local compiler symbol. Localizing the original global would break the neighboring original consumer; a source-correct exported definition/coalescing strategy or justified larger unit reconstruction remains required.
- `lbl_804387C0` and the three fade scalars `lbl_805D9194`, `lbl_805D9198`, `lbl_805D919C` have only this unit's `draw_name_labels` as an observed original consumer. This evidence distinguishes their localizability from the shared signed-conversion constant; it does not fix alignment or FPR allocation.

## Validation and reproduction

Every retained source experiment is published as a patch against the immutable PR113 head in `experiments/tombstone-constant-layout/`; `results.json` records each function percentage, section size/alignment and natural compile/diff elapsed time. The branch's actual source is the `tombstone-probes-2-compound_named` experiment. Apply other patches to separate checkouts at the base, not cumulatively to this WIP head.

Probes used existing Wibo and GC/2.6 `mwcceppc.exe`, the unit's configured flags (`-O4,s -inline off -sdata2 4`, Gekko, PowerPC alignment, signed char, exceptions/RTTI off), isolated output directories and immutable original objects. Objdiff comparisons used `functionRelocDiffs=data_value`. All three compile batches acquired the reviewed capacity module's development-0 slot plus the shared legacy gate; queue waits were 0.001352, 0.000577 and 0.001012 seconds. Exact code/data and missing-export evidence is in `layout-evidence.json`.

No full build or `check_pr` was run: targeted evidence already proves a forbidden exact-function regression. No fallback DOL is presented as source correctness evidence. No checks, split ownership, shared definitions, original inputs, or live wrapper were changed. Full link/adoption validation and separate independent review are required only after a source candidate resolves these blockers.

## Precise remaining work

Recover fade instruction allocation without duplicate zero/one data; resolve the split's four-byte start against compiler eight-byte section alignment using actual ownership evidence rather than preceding padding; and preserve the signed-conversion constant's external export without duplicating its storage. There is no safe measured incremental adoption from this pass. Parent should keep PR113 draft/fallback and assign any broader shared ownership work explicitly.
