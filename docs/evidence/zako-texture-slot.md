# Zako texture-list slot contract

This narrow follow-up to PR #303 shares the existing runtime texture-list
pointer declaration between the Zako initializer and draw reader. The initializer
was already repaired in PR #440. Its body, including the explicit native-word to
pointer conversion, is unchanged. The reader no longer redeclares that pointer
as `s32` and casts it back at the texture API call.

## Storage and native references

At the inspected main pin d6fc686573510cc9612beb6a2d71576ad685301c,
`falz_zako_texture_list` is one four-byte object at 0x805D6A68 in the original
fallback `.sbss` provider `auto_10_805D6A00_sbss`. This change does not define or
move that storage. It gives both source consumers one C-linkage declaration in
`pso/boss/TBoss4ZakoTexture.h`.

The complete 4,943-original-object inventory has exactly two relocations into
that slot, both SDA21 with zero addend:

- The initializer stores the texture getter's result at 0x8030AD70.
- The draw reader loads it at 0x8030AB88 and passes it unchanged to
  `set_current_texture_list` at 0x8030AB8C.

There are no data relocations or aligned original-DOL data words pointing into
this slot. This is static reference evidence, not a claim excluding arbitrary
runtime-computed aliases. The initializer's sole original caller is
`TBoss4DarkFalz::load_resources`; the draw reader's sole original caller is
`TCameraCtrl__sub_8030ABF4`.

## Why this slot is a pointer, without retyping the archive

The evidence is the actual producer-to-consumer dataflow, not the recovered
symbol name alone:

1. `load_resources` constructs the BML resource with kind 5 and a null arena,
   stores the resource pointer, and calls the initializer when it is nonnull.
   `kind & 0x1` selects the synchronous constructor path. This does not guarantee
   successful file loading or allocation.
2. `TBoss4Uro::get_instance_count` returns that resource pointer.
   `TObjFish__sub_8001EDB0` loads the entry array at resource offset 0x42C,
   indexes by 16 bytes, and returns the word at entry offset 0xC. Zako uses
   index 8. The initializer stores that returned value unchanged.
3. The BML constructor and `bind_bml_model` initialize the entry's texture word
   to zero. For the NJTL tag, the binder writes the allocation loader's return
   value into offset 0xC. With a null arena, the loader allocates/copies the
   chunk, applies the designated POF0 fixups, and returns the allocation
   address. Unknown chunks or allocation failure may yield zero. The value
   at this boundary is not an undecoded archive offset or texture index.
4. `set_current_texture_list` stores its argument at render-context offset
   0x20 and returns 1. The downstream texture-number code dereferences that
   value as a list, loads its entry-array pointer, and indexes 12-byte native
   entries. The existing `GinjaTextureList *` API describes that route.

The BML getter still returns a native `s32` word. BML entry words, packed archive
fields, offsets and loader interfaces are not retyped here. The initializer's
explicit conversion marks the existing boundary. The 209 original references
to the getter and 600 to the setter are otherwise untouched; this is not a
renderer-wide interface repair or general 64-bit archive-portability claim.

## Behavior and limits preserved

The slot is a borrowed cache. Its assignment still occurs before model lookup
and child-model processing, including when the child-model branch is not taken.
The reader forwards null just as before. Cleanup deletes the BML resource but
does not clear this slot; no new cleanup, lifetime, ownership, nonnull or
post-cleanup safety guarantee is introduced.

The chunk-model reader, buffers, shadow/material helper, full-unit fold and
compiler-profile migration remain outside this change. In particular, the
held material-helper transaction is not repaired by a texture pointer type.
The raw model handle and other existing renderer boundaries remain. Both units
already linked from source, so this repair claims no new matching or linking
gain. Original scope and attribution remain traceable to PR #303 at
3ed9b21ae3d8b887e18642e3e561063fb1eb2c98.

## Original-free characterization

Run `python3 -m unittest tools.tests.test_zako_texture_slot -v`.
Set `PSO_TEST_SANITIZERS=1` for fatal AddressSanitizer/UBSan checks.

The test extracts the actual reader expression and compiles it using the real
shared slot and setter headers, with separate fixture storage. Three cases
exercise an allocated nonzero pointer, null, and repeated replacement, each
10,000 times. The test-only opaque objects do not reproduce Ginja layouts or
BML allocation. It checks pointer identity and one setter call per read, not
the rest of the draw function, resource loading, or native layout. The existing
initializer test retains its explicit zero-handle host limitation.

Native acceptance still requires exact DOL/linked-ELF validation, full object
sections/symbols/relocations, the affected header/source dependency closure,
provider/retention checks, and address-based no-loss checks against an
authenticated base. Source typing and host characterization alone do not prove
native matching.
