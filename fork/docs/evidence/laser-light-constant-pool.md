# Laser-light constant pool

At fork main `37eab6e173f40350e82c51ea91babc0507fe0317`,
`pso/boss/TBoss2LaserLight.cpp` already links its eight functions (976 code
bytes), two native vtables (48 data bytes), and the first 16 bytes of its
constant pool. The adjacent 16-byte `auto_11_805D84A8_sdata2` unit still
comes from the original object inventory.

The original `run_task` at `0x800372F0` reads `40.0f` at `0x805D84A8`
when updating field `+0x3C`. The constructor at `0x80037500` reads `1.0f`,
`0.2f`, and `2.0f` at `0x805D84AC`, `0x805D84B0`, and `0x805D84B4`,
respectively. These initialize fields `+0x28`/`+0x2C`, `+0x30`, and `+0x34`.
A fresh census of the configured original objects and compiled consumers
finds no other unit referencing these four symbols. Together with native
emission, this supports extending the existing unit's `.sdata2` range from
`0x805D8498` through `0x805D84B8`, absorbing the entire fallback unit.
It does not establish the original source filename or complete class ownership.

## Compiler comparison

Defining the four existing externs as initialized `const f32` objects in
this source emits a 48-byte `.sdata2` section: the named definitions are
followed by compiler-generated copies. Instruction matching alone does not
establish a linkable object with the original data layout.

Following the literal-pool cases in
[conversion-pool constants](conversion-pool-constants.md), ordinary literals
instead produce the exact 32-byte pool in order: `5`, `0`, `3`, `60`, `40`,
`1`, `0.2`, `2`. The existing deferred-codegen arrangement also preserves
all eight functions and both compiler-generated vtables; no new compiler
steering is needed. The four private split symbols become `scope:local`
after the consumer check. `lbl_805D8498` stays exported because
`TBoss2Joint` reads that `5.0f` value.

## Validation

The baseline was rebuilt from the immutable main commit above with fresh
split objects and configuration. Its retention check passes unchanged.
The completed unit matches every function and owned data section, and the
source-link checker accepts its sizes, alignment, order, globals and layout.
The linker selects the compiled source object for the expanded range.

`tools/check_pr.py` passes: matched and linked data both increase by 16
bytes, with no function, code, data or source-link regression. Matched code
remains 4,266,936 bytes (27,470 functions), and linked code remains
3,961,248 bytes. The original-data fallback unit disappears; the number of
linked source units remains 3,619. The rebuilt DOL retains SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, and retention metadata is unchanged.
