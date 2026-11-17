# HFW01 and NFW01 resource boundaries

Base: fork main `f9b6cf76d9171b3dce5082b1484a85f4579855cd`.

The last two functions in each former `00` unit are the neighboring `01` class's
named resource cleanup and loader methods. Their references target the filename
pool immediately following that `01` class's name literal. Move each contiguous
144-byte function tail into `01` and extend its existing readonly range:

| Pair | New 00 text | New 01 text | New 01 rodata |
|---|---|---|---|
| HFW | 8014ADF4–8014AF38 | 8014AF38–8014B10C | 8043FA60–8043FA98 |
| NFW | 8014CD24–8014CE68 | 8014CE68–8014D03C | 8043FDB8–8043FDF0 |

The free/load entries are `8014AF38/8014AF8C` and `8014CE68/8014CEBC`.
The moved pair precedes the unchanged `01` destructor/constructor/factory;
the `00` destructor/constructor/factory sequence is unchanged. This fixes the
previous text-versus-rodata ordering cycle without consolidating whole units.
The boundary is supported by class method names, resource use and emitted layout;
it is a reconstruction, not independent historical build-system provenance.

The four filenames are `npc_g01_data.rel`, `n_g01_e_body.gvm`,
`npc_i01_data.rel` and `n_i01_e_body.gvm`. Each contains 16 visible characters
plus its terminator. Each pair occupies 40 original bytes: 34 literal bytes
and six zero bytes from natural compiler/linker alignment.
Definitions use inferred bounds and external linkage with the original names.
No source padding, section attributes, new flags or asset payloads are added.
The existing readonly-string pragma is retained.

## Shared declarations

The existing `01` headers declare the resource-node `s32*` and the canonical
`GinjaTextureList*` under C linkage. Previously the loader used integer words
while the constructor used pointers for the same globals. The resource pointer
keeps the constructor's existing first-word dereference; the loader's existing
address conversion now produces that pointer. The texture loader already returns
the shared texture-list pointer type. Four-byte native storage and cleanup logic
remain unchanged. This does not recover the legacy integer-argument/result
`create_named_object` interface or the classes' raw construction and vtable code.

## Validation

A fresh complete census of 5,065 active original objects before this correction
finds each filename referenced only from its transferred `01` loader.
The full native build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. PR, retention, actual source-link,
strict original-address no-loss checks (including padding), and both exception
inventory gates pass. The four units stay exact and source-linked. Matched and
source-linked data each gain 80 bytes; no function/code count, linked unit or
coverage denominator changes. Retention adds exactly four filename symbols and
removes none. The moved code and relocation targets are checked by original
address, rather than by unchanged object-relative offsets. All 1,584 text bytes
and 102 allocated relocation records/targets match before/after and the original
objects, including both class-name pointers. The two other source objects using
the changed headers are byte-identical. Native compiler metadata relocations
are excluded from this runtime relocation count.

## Deferred research

FogCollisionSwitch's six diagnostic strings were tested with the existing shared
const-format API. Both inline definitions and ordinary definitions after the
functions emit the 96-byte string pool before the existing eight-byte conversion
constant; the original requires that constant first at `0x80440088`. Both trials
fail the original DOL hash and change code bytes. The readonly section remains
104 bytes/alignment 8, so this is ordering/emission work, not a missing extent.
Keep this recovery deferred; no compiler flags, attributes or padding were added
to force it. The failed source and object experiments are excluded from this PR.
TTecCtrl's texture descriptor uses an opaque surrogate instead of the shared
texture-list contract. Mutable/integer archive-loading APIs and title texture
filename fields also need interface work before defining const pools. None is
included in this boundary correction.
