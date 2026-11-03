# Conversion-pool constants and split exports

Follow-up to [issue #233](https://github.com/matthewlewisnewton/pso-decomp/issues/233).
This change strengthens localization diagnostics. It does not recover original
pool ownership, change symbols or relocations, or promote a linked unit.

## What a value does and does not establish

The double bit patterns `0x4330000000000000` and `0x4330000080000000`
are used in unsigned and signed integer conversion sequences. Finding those
bytes alone does not establish compiler-generated provenance: a named ordinary
object can contain the same value. Inspect the original and compiled section,
alignment, symbol binding/type/offset and the relocation consumers. Distinguish
an MWCC local `@...` pool object used by a conversion sequence from an exported
source definition, and retain uncertainty about the original source arrangement.

The issue's scratch experiments describe particular compiler/source combinations.
They do not prove that every supported source/compiler arrangement is impossible,
or that the original used IPA, interfile pooling or linker constant folding.
Those remain hypotheses pending a reproducible positive result or toolchain
provenance. In particular, matching unrelocated bytes cannot establish a correct
relocation target or retained exported definition.

## Retained-object inventory

The initial read-only inventory used reference checkout commit
`7db2c3273` and patch base `909d120b21f7e875e71a5c1d0d3a7799a08078e9`.
The five source files below were byte-identical between those checkouts.
The reference graph selected GC/2.6 `mwcceppc.exe`, Wibo, `-O4,s`,
`-inline off`, and `-sdata2 4` for the examples. The local inventory records
the complete per-unit command, compiler/wrapper hashes, source/object hashes,
section/symbol/relocation listings and report/configuration hashes. These are
**retained objects**, not a fresh compile of the patch base. Their configured
compiler profile does not establish which compiler invocation produced them.
Raw evidence and proprietary inputs remain local.

| Unit | Observed shape | Constraint |
| --- | --- | --- |
| `TObjBoss2Tunnel_8007C5C0` | Both objects have 16-byte `.rodata`, alignment 8; signed bias at offset 8. The compiled copy is local `@51`. | Original export `TObjBoss2Tunnel__data_80438A90` is undefined in the `TObjBoss2Tunnel_8007CF0C` split. Retain a real provider. |
| `TTecCtrl_8022C444` | Both objects have 8-byte `.rodata`, alignment 8, containing the unsigned bias. | Original export `lbl_8044D078` is undefined in the `TTecCtrl` split. Retain a real provider. |
| `TWindowSubSymbolChatParts` | Both have 8-byte `.rodata` and 72-byte `.sdata2`; 19 original globals are absent from the compiled object. | Its own compiled object still has undefined `lbl_805DD7F8`. The unit cannot be localized as a group until that reference is resolved. |
| `TObjPlayer_8008DCF0` | `lbl_805D9620` is a **4-byte `.sdata2` float**, not an 8-byte conversion bias. | Original and compiled consumers reference it, including the owner. Do not classify all missing data as conversion constants. |
| `TObjFish_8033CCC8` | Original `.rodata` is 8 bytes, alignment 8; compiled `.rodata` is 16 bytes, alignment 8. Compiled local `@26` at offset 0 and global `lbl_80477F08` at offset 8 contain the signed bias. | Data scores 100%, but size differs. Text and `.sdata2` also differ. The named definition is not a valid duplicate-pool recipe. |

A read-only audit of reference report sections scored 100% found Fish as the
only oversized `.rodata`/`.sdata2` section with more aligned copies of one of
the two biases than its original. That census is bounded to this retained
report and these two patterns; it is not a claim that all duplicate data has
been found. Size, alignment and final native-link checks remain required.

## Fail-closed localization

`tools/localize_split_globals.py` now reads every split object from the current
DTK `build/GPOE8P/config.json`, including generated and split-only units. It
also reads every compiled object identified by the report's source metadata,
since a later scan can promote such a unit. The report and split census must
agree. Retired files in the build directories are excluded.

Previously, a missing consumer file was silently skipped. Generated units with
no extension also produced the wrong path (`.o`), which was then skipped.
Either omission could hide a reference. A missing, malformed, unsupported or
inconsistent current object now rejects the whole plan before any symbol write.
GLOBAL and WEAK undefined symbols both count, including the owner's compiled
object; the owner's original split is excluded because it is replaced when linked.
Refused units print the actual consumer paths.

The tool rechecks each cached missing-only candidate against the report and
current link/layout guards. It fingerprints inspected report, split configuration,
symbol/split inventories and objects, then rejects detected changes during the
scan. This detects replacement during inspection; it does **not** prove that a
previously built object matches the current source, flags, headers or compiler.
Do not edit inputs concurrently with a scan. Rebuild from the intended revision
before running it. A successful plan alone does not authorize re-homing a symbol
or editing another object's relocation.

For an isolated checkout with a fresh complete build:

```sh
python tools/link_units.py scan
python tools/localize_split_globals.py <unit>
# Inspect the plan and the complete consumer inventory before --write.
python tools/localize_split_globals.py --write <unit>
# Rebuild; check original bytes, size, alignment, relocations and native link.
python tools/check_pr.py
```

`#232`'s existing localization needs no reimplementation. A referenced-elsewhere
case must keep its exported provider until a separate repair proves every
affected consumer and the final native link. A duplicate named constant must
not be accepted by weakening section-size or relocation checks. Any eventual
source repair needs fresh exact compiler/flags evidence, incremental and overall
no-loss checks, link-input provenance and the original DOL hash.

Portable regression tests require neither game data nor MWCC:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest tools.tests.test_localize_split_globals
```
