# GcrnaStream static storage

This extracts only the Gcrna storage part of
[`1370dcf359541a5e6d0a3cc218513559a7431b6d`](https://github.com/matthewlewisnewton/pso-decomp/commit/1370dcf359541a5e6d0a3cc218513559a7431b6d),
authored by matthewlewisnewton with Cursor coauthor credit, as preserved in
[`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98`](https://github.com/matthewlewisnewton/pso-decomp/commit/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98).
Existing source notices and attribution remain unchanged.

## Ownership and layout

`pso/audio/GcrnaStream.cpp` already links. Seven existing external declarations
become zero-initialized definitions in original address order: `gcrna_init_count`,
`gcrna_audio_buffer_count`, `lbl_805D7688`, `gcrna_audio_allocation`,
`gcrna_uses_caller_buffer`, `lbl_805D7694` and `gcrna_aligned_audio_storage`.
Each occupies four native bytes at offsets 0, 4, 8, 12, 16, 20 and 24 in the
`.sbss` range starting at `0x805D7680`. The two unresolved labels retain their
existing names; no new interpretation of their roles is claimed.

The owned range ends at `0x805D76A0`: 28 bytes of storage plus four bytes of
alignment padding. `gcrna_aligned_audio_storage` is the existing 32-bit address
word used by allocation/alignment and buffer indexing; its symbol extent is
corrected from eight bytes to four, excluding padding at `0x805D769C`.
No extra storage field is invented to fill that tail. All function bodies,
compiler settings, string directives and original behavior remain unchanged.

## Validation

The comparison base is `cda82a7aad7de1bf9b86470002df3f68d1c8c039`.

- Serialized native builds reproduce original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr.py` passes with no
  function, code, data, linked or address-coverage loss.
- Matched and linked data each gain the 32-byte owned range, including padding.
  Matched functions remain 27,438, matched code 4,237,032 bytes, source-linked
  code 3,862,972 bytes and linked units 3,606. There is no new function or unit.
- All 3,631 other active compiled objects are raw-identical. GcrnaStream's five
  existing allocated sections and all 148 relocations are unchanged, without
  normalization. The new `.sbss` is 28 bytes of NOBITS storage at alignment 8,
  with no relocations; all seven symbols match the original offsets and sizes.
- The original split's `.sbss` is 32 bytes. Its only symbol in the four-byte
  tail is the generated gap marker, not a real object. The repository's
  alignment-padding check accepts the tail, and the final DOL proves that the
  linker reproduces the original address layout. Existing `.rodata` tail
  padding is unchanged and is not a new claim of this extraction.
- Ordered linker paths and counts stay unchanged (3,606 source and 1,340
  fallback inputs). The automatic original `.sbss` object at `0x805D7658`
  shrinks by 32 bytes while the existing Gcrna source object owns this range.
- Regenerating retention from fresh candidate split objects adds exactly the
  seven new definitions, changing 18,575 entries to 18,582, with no removals.
  Generated port-exception inventory is unchanged; no new exception is added.
- All 306 original-free host tests pass. Portable `make -C ports/tests run`
  and `make -C ports/tests sanitize` pass with AddressSanitizer and UBSan enabled.

Original binaries, proprietary tools and private validation artifacts stay local.
