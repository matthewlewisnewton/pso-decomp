# Bridge and item-light constant ownership

Base: fork main `6d478092bf9791e1db79bb20a886173bb97e7021`.

The fallback unit `auto_11_805DBE20_sdata2` spans 40 bytes. Original
relocations assign its first seven floats to `TObjHashi.cpp`: the versus-2
constructor reads 120, the base constructor reads 400, 40, 0.15 and 30,
and the visibility method reads 0 and 640. The item-light constructor at
`0x801920D4` reads the final two floats, 0 and 30. A census of the fresh
configured original objects finds no other consumers of these nine symbols.
These references and the compiled layouts support assigning the data to the
two existing owners; they do not recover an original source filename.

## Compiler comparisons

Replacing the bridge externs with literals and removing its scoped CSE
pragma preserves instruction selection but emits the constants in the wrong
order: 120, 0, 640, 400, 40, 0.15, 30. This reproduces the previous source
comment's unresolved ordering problem. The item-light literals already
produce its exact eight-byte pool.

The late-definition arrangement documented in
[Dark Falz demo linkage](dfdemo0-native-linkage.md) resolves the bridge case.
Declare the seven named constants before the functions and define them
afterward in their original order. GC/2.6 emits exactly 28 bytes, without
extra pooled copies, while retaining all functions and native vtables.
The existing deferred compilation profile and scoped CSE setting are
retained; no new compiler exception is introduced.

The old symbol at `0x805DBE38` included four trailing zero bytes in its
reported size. The emitted scalar is four bytes. Correcting that symbol
and ending the bridge range at `0x805DBE3C` leaves ordinary alignment
padding before the item-light pool at `0x805DBE40`. The fresh split inventory
omits those four padding bytes, and the native linker recreates them.
No artificial array or explicit padding object is required. The item-light
literals are private after the full original/compiled consumer check;
the bridge's seven named definitions remain exported and gain their
corresponding generated retention entries.

## Validation

A fresh unchanged-main build and retention check passed before editing.
Both completed owners are entirely matched and source-linked:

| Owner | Functions | Code bytes | Data bytes |
| --- | ---: | ---: | ---: |
| `TObjHashi.cpp` | 24 | 2,756 | 820 |
| `TObjItemLight.cpp` | 3 | 484 | 60 |

All allocated section bytes match, allowing only the original trailing
zero alignment in the bridge's rodata/data sections. Section alignments
and all 200 bridge and 33 item-light relocation tuples match after resolving
local targets to section offsets and retaining external names and addends.

The full native build and `tools/check_pr.py` pass. Matched and linked data
both increase by 36 bytes; all function and code coverage is preserved.
The four-byte reduction in reported total data is identified as alignment
padding by the address-based regression check. The entire fallback pool
unit disappears from the configured inventory. Both existing source-linked
owners remain linked, so the linked-unit count stays at 3,625.
The rebuilt DOL retains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
