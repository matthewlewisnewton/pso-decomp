# Conversion-pool linker probe

Standalone fixtures for [issue #233](https://github.com/matthewlewisnewton/pso-decomp/issues/233).
The PSO build does not compile or link them. See also
[conversion-pool constants](../../../docs/evidence/conversion-pool-constants.md).

`signed-int-to-double.cpp` returns an `int` as a `double`. GC/2.6 then emits the
signed conversion bias `0x4330000080000000` as a local `.rodata` object.
`external-consumer.cpp` reads the external `const double synthetic_pool_export`.
`pool.lcf` defines that symbol as the `.rodata` section start (`_f_rodata`) and
keeps `signed_a` and `read_pool_export` with `FORCEACTIVE`.

## Commands

Compiler and linker: Metrowerks Embedded PowerPC version 2.4.7 build 107
(runtime built Jul 14 2003), the repo's GC/2.6 tools, through the wibo 1.0.3
wrapper. `configure.py` places them at:

- `build/tools/wibo`
- `build/compilers/GC/2.6/mwcceppc.exe`
- `build/compilers/GC/2.6/mwldeppc.exe`

SHA-256 of the binaries that produced the table below:

- `build/tools/wibo`: `7fdf620b151744296b9bb93318d8c4009d3d3e98e23718a6eda9fbec4cefbb2a`
- `build/compilers/GC/2.6/mwcceppc.exe`: `316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`
- `build/compilers/GC/2.6/mwldeppc.exe`: `37818faa6e510d3ab92629f0a6c4334cfca0ca943fba0a0d61626f7f9379077d`

Run from the repository root. The compiler flags are the PSO game flags in
`cflags_pso` (`configure.py`): `-O4,s`, `-inline off`, `-sdata2 4`, and the
other switches below. These sources include no headers. Adding that profile's
`-i` paths left `signed-int-to-double.o` byte-identical. The linker flags
`-fp hardware -nodefaults` are the project `ldflags`. `-m signed_a` selects the
entry. The linker default is `__start`, which this probe does not define, and
`-noentry` stops with `application has no main entry-point`. Repeating the link
with `-m read_pool_export` left the pool and alias symbols unchanged.

```sh
build/tools/wibo build/compilers/GC/2.6/mwcceppc.exe \
    -nodefaults -proc gekko -align powerpc -enum int -fp hardware \
    -Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath \
    -char signed -use_lmw_stmw on -O4,s -inline off -sdata2 4 \
    -c tools/probes/conversion_pool/signed-int-to-double.cpp \
    -o signed-int-to-double.o

build/tools/wibo build/compilers/GC/2.6/mwcceppc.exe \
    -nodefaults -proc gekko -align powerpc -enum int -fp hardware \
    -Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath \
    -char signed -use_lmw_stmw on -O4,s -inline off -sdata2 4 \
    -c tools/probes/conversion_pool/external-consumer.cpp \
    -o external-consumer.o

build/tools/wibo build/compilers/GC/2.6/mwldeppc.exe \
    -fp hardware -nodefaults -m signed_a \
    -lcf tools/probes/conversion_pool/pool.lcf \
    -o pool.elf \
    signed-int-to-double.o external-consumer.o

build/binutils/powerpc-eabi-readelf -s -W pool.elf
build/binutils/powerpc-eabi-objdump -d -s -j .text -j .rodata pool.elf
```

Link order is `signed-int-to-double.o` then `external-consumer.o`.

## Observed symbol table

`signed-int-to-double.o` has one `.rodata` symbol, `@6`: value 0, size 8, type
`OBJECT`, bind `LOCAL`, section `.rodata`. Its bytes are
`43 30 00 00 80 00 00 00`.

`pool.elf` places `.rodata` at `0x00010038`, size 8, alignment 8, with those
same bytes. `readelf -s -W pool.elf` reports:

| Symbol | Value | Size | Type | Bind | Section |
| --- | --- | --- | --- | --- | --- |
| `@6` | `0x00010038` | 8 | `OBJECT` | `LOCAL` | `.rodata` |
| `synthetic_pool_export` | `0x00010038` | 0 | `NOTYPE` | `GLOBAL` | `ABS` |
| `_f_rodata` | `0x00010038` | 0 | `NOTYPE` | `GLOBAL` | `ABS` |

`signed_a` is 44 bytes at `0x00010000`. Its pool load relocates against `@6`.
`read_pool_export` is 12 bytes at `0x0001002c`. Its load relocates against
`synthetic_pool_export`. Both resolved addresses are `0x00010038`. The
instruction words match the object files outside the `R_PPC_ADDR16_HA` and
`R_PPC_ADDR16_LO` fields.

The alias is the section-start symbol. It lands on the conversion pool when
that pool is the sole `.rodata` contribution, which is the case in these
fixtures: `external-consumer.cpp` contributes no `.rodata`, and
`signed-int-to-double.cpp` contributes only `@6`.

A separate check compiled one more translation unit,
`const double other_rodata = 1.0` with a function that returns it, using the
same compiler flags. That object’s `.rodata` was 16 bytes, the global and a
local pool, both `0x3ff0000000000000`. Linking it ahead of
`signed-int-to-double.o` and adding its function to `FORCEACTIVE` put
`synthetic_pool_export` at the section start `0x00010048` (the earlier double)
and left `@6` at `0x00010050` (the conversion bias). `read_pool_export` loaded
`0x00010048`; `signed_a` still loaded `@6`. With the extra function omitted from
`FORCEACTIVE`, the linker dropped that object and the sole-pool result
returned. That extra file is not part of this directory. Linking the conversion
object first, while still keeping the extra function, left the alias on `@6`
because the pool occupied the section start and the other double followed it.

## Verification

These commands were run on 2026-11-02. This worktree’s `build.ninja` points the
wrapper, compiler, linker, and binutils at
`/home/matt/workspace/pso-decomp/build/` (the shared toolchain passed to
`configure.py`). The `build/...` paths above are those binaries. The worktree
itself has no separate `build/compilers` directory. `readelf` and `objdump`
were `build/binutils/powerpc-eabi-readelf` and `powerpc-eabi-objdump` from that
same toolchain. The extra-object check used a temporary LCF and is not
reproduced by the commands above.
