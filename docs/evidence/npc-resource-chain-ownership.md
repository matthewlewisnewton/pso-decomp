# NPC resource ownership and boundaries

Base: fork main `8aaabc087559d217358101920f7cefae081ad884`, including
merged HFW01/NFW01 recovery and the GC/2.0 compiler default.

Eleven resource cleanup/load pairs occupied the ends of neighboring class units.
Move each complete pair to the beginning of its named class's existing unit,
preserving original function order. Four GVM pairs move 576 code bytes; seven BML
pairs move 952. No class, vtable, constructor or factory is reconstructed.
The original code addresses and resource-reference graph support these boundaries;
this does not claim historical source-file provenance.

| Resource family | Boundary corrections | New data |
|---|---|---:|
| GVM | GovernorBase → HFW00; Moja → NFM00 → NFM01 → NFW00 | 64 bytes |
| BML | FemaleBase → Child → Dwarf → Fat → Macho → Old → Tall; MaleDwarf → MaleFat | 528 bytes |

The GVM units now own each class-name string alongside its existing two filenames.
The 160 filename bytes transfer ownership without being counted as new coverage.
The BML group owns nine complete model-filename/archive-filename/class-name pools:
FemaleBase through FemaleTall at `0x8043F830–0x8043F9C8`, and MaleDwarf/MaleFat
at `0x8043FBE0–0x8043FC58`. The total gain is 31 new ordinary const arrays,
545 literal bytes including terminators and 47 natural alignment bytes: **592 bytes**.
No asset payloads, source padding, section attributes or compiler settings are added.

A fresh census of all 5,061 original objects audits 77 relevant labels and 122
references. Each model filename leads through its original model-name array and
resource descriptor to the matching class loader; each archive filename points
through the same descriptor; each class-name pointer is read by that constructor.
The GVM filenames are referenced only within their moved loader methods.
Existing descriptor payloads and model/motion arrays remain external, including
legacy descriptor views whose full type recovery is outside this change.

## Shared resource declarations

The existing class headers give each moved resource global one consistent type.
GVM model pointers use the existing constructor's first-word `s32*` representation;
texture handles use the canonical `GinjaTextureList*` returned by the shared loader.
The archive factory's existing integer interface remains a bounded conversion.
BML resources use `BmlResource*` in loaders and constructors. Loader temporaries
and assignment now preserve that pointer type instead of converting to an integer
and storing through an alias. Existing constructor byte-offset reads remain
unchanged. No field layout, allocation, cleanup behavior or vtable changes.

The unusually named `FemaleMacho::close_dialog_window`,
`FemaleOld::destroy_static_instance` and `FemaleTall::destroy_instance` are the
existing resource cleanup methods; their names and bodies are retained.

## Validation

Native head `5ed0d060795a6447d0c2af8ab34a089a8b252a90` reproduces original
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Full PR, source-link,
retention, both exception inventories and strict original-address no-loss checks
including padding pass. Matched data increases 1,505,752 → 1,506,344; source-linked
data increases 1,503,856 → 1,504,448. All 3,614 linked units remain exact.
Functions, code, coverage denominators and generated retention are unchanged.

Across all 15 affected source units, 7,180 text bytes and all 508 runtime
relocation sites and resolved targets are identical at their original addresses,
before/after and against the original objects. Allocated data, alignment and
natural zero tails match. All 3,605 other compiled source objects, including the
consumers of the changed headers, are byte-identical to fresh main.

## Deferred extents and other cases

Four GVM class-name pointer symbols are recorded as eight-byte objects, while
ordinary pointer definitions emit four bytes. The original executable still
matched, but the strict linked-unit checks correctly rejected the named tails.
Those 32 bytes remain original-owned. No symbol extent is shrunk, second pointer
invented, or checker relaxed to count them. Corresponding class-name strings are
independently supported and included.

The existing BML name-pointer/motion arrays and opaque resource descriptors remain
external. Further recovery must establish their complete types and extents.
The prior fog diagnostic placement failures, adjacent shop overlap with #562,
network/player section-order cycles and RoomId pointer-versus-room-ID debug
interface are still deferred; this batch does not claim those cases solved.
