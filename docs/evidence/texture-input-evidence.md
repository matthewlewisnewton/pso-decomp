# Texture input and runtime surface

The helper at `0x803DA204` initializes a texture input descriptor. It writes
input data at `+0`, format/options at `+4`, width at `+0x10`, and height at
`+0x14`. The name `GinjaTextureInput` describes this role; the original source
name is not established. Persistent descriptors use a `0x24` stride. Existing
capture locals were represented as `0x20` byte buffers; their original stack
frames accommodate the full descriptor.

This input is distinct from the loaded surface: the loader reads the input and
attaches separately allocated runtime state. For menu fonts, the pixel pointer
is reached via texture-list entry `+8`, texture `+0xc`, then surface `+0x20`.
`GinjaSurfaceState` now includes that pointer, but remains a prefix: runtime
surfaces also have a reference field at `+0x24` and use a `0x28` pool stride.
The font list and its runtime chain retain their existing local declarations;
reconciling the list definition with the shared types remains separate work.

Some surrounding owners still store a descriptor address as `void *` or a byte
buffer. Their actual allocation and enclosing class layouts remain separate
work; this change does not establish all of those owners' C++ lifetimes.
