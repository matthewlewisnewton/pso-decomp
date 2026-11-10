# Canonical read-only download-token view

The finder, slot and search now borrow one existing four-byte
`QuestDownloadMatchToken` format through `const` pointers. The private duplicate
`Ent_803E9DE0` record is removed. This improves source-type consistency and
prevents writes through these borrows; it adds no matching or linkage coverage.

## Observed producer-to-consumer chain

A named-reference census of all 4,958 active original objects finds the entry
and index tables only in the finder (two relocations each). Its sole direct
caller is retained `sub_803EA9E8` (one call relocation). The census excludes
42 stale physical objects; its private SHA-256 is
`f1373f4b1bf4ea463c3d32f25304ed8e32ce935178456025d65c01a34edd9797`.
Native data-flow review additionally follows the returned address and slot
member, rather than treating named relocations as a complete alias proof.

The finder indexes records with stride four and returns the actual selected
record address. At `0x803EAA54..0x803EAA6C`, `A9E8` rejects all ones, writes the
length byte at slot+0x18, then stores the accepted record pointer or NULL at
slot+0. Search reads that record's bytes at offsets 0, 1, 2 and 3 as `a`, `b`,
pattern offset and signed backward-link count. Reset/init still store the named
unavailable pointer. NULL, unavailable and a valid record pointer remain distinct.

The original-hash DOL and symbol extents provide these bounded metadata checks:

| Check | Observation |
|---|---|
| Entry-table extent | 0x5FC bytes, 383 four-byte records |
| Index-table extent | 0xC0 bytes, 96 signed-halfword endpoints |
| Endpoints | Monotonic, minimum 1 and maximum 383; 34 empty groups |
| Nonzero record links | 317; all decrease the record index and remain within the table |
| Pattern map | 244 bytes; referenced offsets and lengths stay within it |

For bytes `0xA0..0xFE`, the finder uses index pairs within those 96 endpoints.
Lower bytes return before indexing. Byte `0xFF` would require endpoint 96,
outside the observed index object. This unchecked-input limitation is retained:
no guard or alternative native behavior is invented, and no shipped reachability
claim is made.

## Narrow source change

`const` flows coherently through the unsized extern table declaration, finder
return/local, slot's token pointer, search local and typed unavailable sentinel.
The finder uses that same sentinel name on its existing failure path. The
manually preserved link name, argument types and count are unchanged.

No table definition, extent, storage, class owner, allocation or interface is
invented. `A9E8` remains original code. This canonicalizes the recovered format
and read-only access path; it does not prove original C++ type identity or
recover the retained dictionary's source ownership and lifetime. Other pointer
views and the byte-input producer storage hold remain separate.

Full native build and main/previous-head no-loss checks pass. All 168 compiled
provider bodies, all 16 frontend bodies, all 173 provider report entries and
complete provider/frontend/buffer object bytes are unchanged. Slot offsets,
80-slot owner extent, allocated data and relocations are preserved. Original
DOL SHA-1 remains `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Independent exact-head review accompanies publication. No new runtime execution
is claimed for unchanged executable objects.

## Fresh byte-input investigation: rejected adapters

Both exact keyword/fallback helpers mask lookup words to their low-byte keys;
they do not modify or retain the local prefix. A new bounded investigation
therefore tested preparing only those keys in the real `u16 words[4]`, while
leaving every live attribute-bearing mapping read and post-output reread intact.
The sole lookup path reaches this array with two, three or four words.

| Prefix preparation | Strict consumer match | Compiled bytes |
|---|---:|---:|
| Retained full-word copy | 62.267857% | 1,000 |
| Low-byte keys, ordinary loop | 44.20982% | 1,180 |
| Low-byte keys, explicit two-to-four-word adapter | 55.808037% | 1,032 |

Both measurements preserve the other 167 compiled provider functions but regress
the consumer, so neither is adopted or advanced to runtime validation. These
are distinct from earlier probes that decoded full words or changed live
classification reads. The lead stops here; no pragma, compiler switch, dummy
initialization or owner change is used to force a result.

The exact frontend still writes through a signed-halfword view of the actual
byte-owned scratch buffer. A credible repair needs a justified storage/lifetime
form that preserves the native halfword store at `0x803E6524` and all 16 exact
frontend functions. Earlier byte-store/copy/array-placement forms regress that
body. Shared byte/halfword/ID phase bounds, retained views and callbacks remain
held; this dictionary-token improvement does not supply those proofs.

The unit remains 159/173 exact, five undefined and nine partial, unlinked.
See the [byte-input evidence](quest-download-byte-conversion.md) for the existing
bounded native corpus and unresolved storage/lifecycle boundaries.
