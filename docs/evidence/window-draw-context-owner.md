# Draw-context ownership separated from Soft keyboard labels

This follows continuation `1e029e97038b7c828d9a1e8dcb318c6a8cd99ef7` on
main `d6fc686573510cc9612beb6a2d71576ad685301c`. The inspected client notification
paths still do not establish valid-server own-client exit semantics. No additional
notification guard or authentic-session evidence justifies revisiting that hold.
This separate bounded lane corrects ownership of existing context operations.

## Three storage domains stay distinct

The singleton in owner `TWindowKeyBoardSoft_8024E68C` allocates exactly 0x4C bytes.
Its initializer writes the existing `TWindowDrawContext` layout through the final
clip coordinate at 0x48. Menu-frame setup and the main-menu content frame consume
that returned layout. These operations do not use a TObject/window prefix.

Actual Soft windows have separate 0x70-byte producers, Base initialization and a
borrowed composer word at 0x6C. The composer itself is 0xB8 bytes, with independent
text records and flags. Neither allocation is the singleton. The nine moved
functions were project-labelled Soft keyboard methods; their new source owner
follows observed allocation/field/caller evidence, not recovered debug names.

The existing `TWindowDrawContext` now declares and defines:

| Operations | Preserved original body sizes |
| --- | --- |
| Scale a point about the pivot; set open tick | 76 / 128 bytes |
| Set clipping bounds; shrink right clip; animate layout | 20 / 32 / 44 bytes |
| Open existing singleton; get or allocate; free; initialize | 88 / 76 / 84 / 96 bytes |

Both actual opening callers receive `TWindowDrawContext *`. Their static calls
and the controller allocation/release calls name the actual context owner.
The Base setup now calls `window->animate_scale()` explicitly; the old no-argument
C alias relied on the context return remaining live in r3. No return value is
invented or consumed.

Allocation size, initialization order, null/failure behavior, native word returns
for get/free/init, signed cleanup argument and global clearing stay unchanged.
The global's existing word transport/name and eight-byte catalog extent are
preserved. No ownership of its second catalog word, native constructor, default
lifetime, new/delete pairing or global-array layout is inferred.

## Closed reference cohort and complete objects

The initial complete generated-original census finds 21 references to the nine
targets, all zero-addend direct REL24 calls in six source units. The current census
checks 4960 original and 3632 active compiled objects, 512644 relocation records;
there are no undefined old export names. All observed references in this cohort are direct calls, with no address-taking;
arbitrary computed runtime addresses are not excluded by the relocation census.

| Source unit | Complete text bytes preserved |
| --- | ---: |
| TWindowKeyBoardSoft_8024E68C | 2156 |
| TWindowSubComCard_80244774 | 7864 |
| TWindowMainMenu_802AD538 | 4600 |
| TWindowCtrlMain | 1528 |
| TWindowCtrlMain_8024EEF8 | 68 |
| TKeyBoardControl | 9096 |

Every non-name payload byte agrees with the preceding six complete ELFs,
including allocated data/constants, compiler metadata and raw relocation records.
Symbol record ordering, binding, section, offsets and sizes agree after only the
nine documented export-name mappings. String-table lengths, consequent symbol-
name/file offsets and zero alignment padding account for the serialization
changes; raw whole-ELF identity is not claimed. There is no anonymous-symbol,
function-placement or body normalization. All nine component bodies and resolved
function-relative targets separately match original.

All 3626 other active compiled objects remain raw-identical. Each of the six
source providers remains selected once with its original fallback absent.
The entire Ninja graph and ordered inputs remain byte-identical, as does the DOL.
The catalog/retention changes describe real source-owner renames at unchanged
addresses, not new code/data coverage or recovered original translation units.

## Validation and remaining scope

The one fixed-source cohort passes the capacity-gated native build in 36.28 seconds,
reproducing original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Address-based acceptance has zero function/code/data/coverage delta, nine reported
renames, 3612 exact linked units and 18837 retention names without drift.
Port inventory and whitespace checks pass; no compiler option, pragma, section,
allocation or layout variant is introduced. Private complete-object, original,
reference/provider and build controls are in `pr403-draw-context-owner/`.
Independent review agrees with the bounded ownership correction.

The generic Soft header still contains legacy overlay inheritance and mixed
window/composer/context parameter views. In particular, keyboard render and
line-drawing helpers still label some context arguments with the Soft type.
Those are not made truthful by inherited method resolution alone. Raw split-
position/viewport helpers and text-record reset operations remain separate;
no actual Soft-window construction/destruction or portable context lifetime is
recovered here. All CustomSelect valid-session/lifetime, Word, ComCard, data,
ownership and interface holds remain. The continuation stays draft.
