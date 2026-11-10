# CVFS file query and open recovery

The independent base is fork main `1a18b4bd7577af4ee367317064e020d1f91ce5a8`.
The existing `pso/unk/text_803CE568.cpp` text and BSS boundaries are retained.
This work does not authenticate a different original translation-unit boundary.

## Live routines and call boundary

| Address | Recovered routine | Text bytes |
| --- | --- | ---: |
| `0x803CE568` | `cvFsGetFileSizeEx` | 1,196 |
| `0x803CEA14` | `cvFsGetFileSize` | 1,188 |
| `0x803CF2F4` | `cvFsOpen` | 1,636 |

The routines split a device prefix from a path, resolve the default or named
registered device, optionally restore the `DEV:path` form, and invoke the device
interface. Open allocates one of forty handles and releases its slot on failure.
The two device-open words and the extended-query word retain their existing
32-bit boundary; this change does not infer additional pointer or enum types.

The names are corroborated by the routines' own diagnostic strings. Shared
prototypes now pass the path and query word explicitly. The stream-file layer's
existing integer handle storage remains a bounded legacy interface, with an
explicit conversion from the returned `CvFsHandle *`.

Error registration and forwarding now share one three-argument callback type.
The adapter consumes its message argument and explicitly accepts the ignored
third word. Forwarding replaces the first word with the registered context and
preserves the other two arguments. The former no-argument declarations depended
on register carry-over; no incompatible function-pointer call is introduced.
The setter, forwarder and ADX stream runtime retain their complete text bytes
relative to the current-main build.

The remaining legacy `TLobby` wrappers and `SIGetTypeAsync` name are not claimed
as recovered class ownership or cleaned interfaces. No missing initialization
routine is invented.

## Native diagnostic data

The complete catalog is 86 ordinary named constant character arrays, including
the version banner. Diagnostics belonging to stripped APIs remain data, without
fabricated function bodies to force their emission. CodeWarrior places these
arrays at the original four-byte-spaced offsets.

The added section ranges are:

- `.rodata`: `[0x8047CF30, 0x8047DAB4)`, 2,948 bytes.
- `.sdata2`: `[0x805E0DA0, 0x805E0DAC)`, 12 bytes.

The four zero bytes at `[0x8047DAB4, 0x8047DAB8)` remain in the neighboring
original provider. No address coverage is removed. The small-data range contains
the version pointer and `%s:%s`. Its format storage is explicitly null-padded to
eight bytes, representing the six-byte terminated format and its two original
zero tail bytes. No adjacent named object is consumed.

The old aggregate catalog labels are refined to actual terminated-string
extents where a live named literal is defined. The intervening catalog spans
retain local labels. Localization followed a census of every active original
object, including unlinked objects, rather than source text alone. Before the
fold, only this code unit and its original version-pointer provider referred to
the catalog. After the fold, the 4,950-object inventory contains no other-object
reference into the claimed catalog, small-data constants or handle storage.
The latter census examined 249,573 other-object relocations.

## Matching constraints and attribution

The path/device helpers and three live bodies adapt zeroz's upstream
[Matchpass 15 source](https://github.com/zeroz41/pso-decomp/blob/ae797d392bb93d5bf7164341870f78f864da23b0/src/pso/unk/text_803CE568.cpp),
commit `ae797d392bb93d5bf7164341870f78f864da23b0` (#208), under this project's
existing MIT license. Its stripped-API stubs and reconstructed initialization
routine are not imported.

A separate output cursor in the path-copy loop reproduces the original pointer
and counter update order while retaining a const input path. A read-once byte
local and a shared scan/output index did not reproduce that schedule. The
original instructions establish the separate update roles. The public
[RE4 CVFS listing](https://github.com/adonis-singh/re4/blob/9b76ff003081d6ece8b838453fb8310743a972c7/src/lib/cri_cvfs.c)
is corroborating research only, not an imported body or a source-license grant.
Its register-pinning assembly is not used. No assembly, intrinsic, dummy frame
local, scheduling override or additional per-unit compiler setting is added.
The existing inline-helper controls are described in the porting register.

An external catalog-base pointer reproduced all body instructions but reversed
the two pool-base materializations. Defining the actual catalog in source lets
the compiler emit its native readonly pool, removing that mismatch without an
artificial reference or source-only padding function.

## Validation

The current-main baseline report and its sealed source, tools, generated graph
and active object inventory were independently rehashed before reuse. The
candidate generates fresh split objects from its own checked-in split/symbol
configuration and local original inputs.

Against that base:

- Exact functions: 27,416 to 27,419, a gain of three.
- Matched code: 4,213,640 to 4,217,660, a gain of 4,020 bytes.
- Matched data: 1,472,575 to 1,475,535, a gain of 2,960 bytes.
- Source-linked code: 3,737,624 to 3,744,024, a gain of 6,400 bytes.
- Source-linked data: 1,190,727 to 1,194,831, a gain of 4,104 bytes.
- Linked units: 3,590 to 3,591. Every linked unit remains exact.
- Total code, data and function counts are unchanged. There are no regressions.

All thirteen functions and all four allocated sections score 100%. An independent
ELF comparison checks every allocated payload, section size and alignment,
seventeen required public definitions and all 195 normalized relocations. Ninja's
actual ELF input list selects the compiled CVFS object rather than its original
fallback. Only this unit is added to the linkset; the generated retention delta
adds its four existing BSS exports.

There is one disclosed ELF representation difference: the DTK split marks
`.sdata2` allocated/read-only (`A`), while the native compiler emits allocated/
writable (`WA`). A census of the sealed current main finds the same difference
in 540 already-linked units, including `TAdADXlogo` and `TBoss2Tentacle`.
Changing the version pointer's volatile spelling does not change it. No compiler
control or object patch is added to force ELF flags. This is not whole-ELF byte
identity; payloads, relocations, final addresses and DOL bytes are the checks.

Capacity-gated native source-link builds reproduce the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py`, the linked-unit
and force-active checks, the porting inventory check and changed-line whitespace
checks pass. Publication remains subject to independent final-head review and
separate authorization for a new PR.
