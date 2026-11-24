# WAV header parser at 0x803C1780

Base: personal-fork main `5c77f59730e69b01ff66e9c1f83ac97cc9f15e28`.
No prerequisite PRs or split-boundary changes are needed.

## Ownership and file layout

`pso/unk/text_803C1780.cpp` owns `0x803C1780–0x803C1A58`: four
functions totaling 728 code bytes and no allocated data. The previously missing
600-byte function scans for the four-byte `fmt ` and `data` tags. Its existing
external pointers at `0x805D4650` and `0x805D4654` refer to those strings at
`0x805E0CA0` and `0x805E0CA8`; they remain owned by their existing data units.
The placeholder symbol is retained because the `TLobby` prefix does not establish
ownership of this middleware parser.

The format chunk reads little-endian fields at offsets 8 (format), 10 (channels),
12 (sample rate), 20 (block alignment), and 22 (bits per sample). Its layout is
0x18 bytes; the data chunk is an eight-byte tag/size header. Source layout guards
check these sizes and offsets. Endian expressions use unsigned 32-bit inputs;
the decoded data size becomes signed only for the original signed divisions.

The direct caller at `0x803C1668` now includes the shared declaration. Its output
fields at 0xC/0xD are signed bytes, and the two-byte encoding field at 0xAA is a
signed halfword. These declarations preserve the existing byte layout and emitted
caller object. Its legacy integer input address is converted at this boundary.

## Matching constraints and behavior

The default middleware settings are GC/2.6, `-O4,p`, `-inline off`. The parser
scopes `opt_propagation off`: propagation otherwise folds the explicit data-chunk
address into an indexed load and changes register allocation. Explicit 32-bit
address addition at the two header-view boundaries preserves the original add
operand order. The views do not write the input buffer. These arrangements
reproduce the emitted object; they do not identify the original source spelling.

The endian macros are local to this function and undefined immediately afterward.
They receive side-effect-free field reads or unsigned casts. Explicit inline
helpers with inlining enabled were also compiled, but changed the emitted code.
The signed 16-bit payload-offset local preserves the original output width and
register assignment.

This recovery preserves the executable's parsing behavior, including its limits:

- Searches advance one byte at a time and compare four bytes before the next
  cursor bound check. The function does not fully validate a supplied buffer.
- Only the format-chunk offset is checked for four-byte alignment.
- The format field is compared as a signed halfword and rejected only above 1.
- Divisions precede the later zero/block-alignment/channel checks.
- The 4-bit case changes block alignment to twice the channel count, codec to 4,
  sample count to half the data size divided by channels, output width to 16,
  and encoding to 2. The 16/8-bit cases use encodings 0/1, respectively.

## Validation

The full base build reproduces the pinned original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The completed unit changes from
3/4 exact functions (128/728 code bytes) to 4/4 (728/728 bytes). Source linkage
adds all 728 bytes; no data gain is claimed. The linked-unit scanner accepts the
compiled object's sections, symbols, sizes, alignment, and relocations without
localizing globals or changing force-active retention metadata. Final validation
also requires the complete linked DOL build, address-based report regression
check, native link-input selection, and independent review of the immutable head.
