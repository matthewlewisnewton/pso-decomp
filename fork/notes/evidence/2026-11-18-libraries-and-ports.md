# Fork library and portability changes

This audit compares fork `23aa26cec0` with integration `e4ce5613d1` on upstream `92a266f5eb`. The file list comes from the fork’s changes since the common ancestor, `fba9382235`. It covers all 15 paths under `libs/` and all 12 under `ports/` that the fork changed.

## Libraries

| Fork change | Resolution on integration |
|---|---|
| MSL `ansi_fp.c`, `printf.c`, `scanf.c` and Dolphin `dvdfs.c` | The four files have identical Git blobs on the fork, upstream and integration. |
| Dolphin `include/libc/ctype.h` and `src/mtx/mtxvec.c` | Integration carries the fork contents byte for byte. |
| MSL `ctype.c` and `include/MSL_C/ctype.h` | Upstream already defines the character tables and `islower`. The implementation differs from the fork by one comment. Its header declares `islower` weak alongside the other character classifiers. The selected object matches all 96 code bytes and 768 data bytes. |
| MSL `locale.c` | Upstream defines the C locale data with ordinary string literals, `CHAR_MAX` and a dead-stripped `setlocale`. The selected object matches all 64 data bytes. |
| MSL `strtoul.c` | Integration uses the shared fdlibm and locale declarations for the floating constants and locale table. The fork’s anonymous-symbol aliases are gone. The selected object matches all 6,396 code bytes and 216 data bytes. |
| Runtime `NMWException.cp` | Both branches destroy arrays through `::operator delete[]`. Their only file difference is a blank line. |
| Runtime `ptmf.c` | Upstream defines the three-word null member-function pointer. The compiled object exports the 12-byte `__ptmf_null` at offset zero in `.rodata`; the help window copies three words. The fork dropped the definition and described a 16-byte range in its symbol map. |
| Dolphin `include/dolphin/mtx.h` and `src/mtx/vec.c` | The SDK declaration and definition of `PSVECDistance` both accept const vector inputs. The lobby calls that shared declaration. The selected vector object matches 204 code bytes and eight data bytes. |
| Dolphin `include/dolphin/types.h` | Upstream’s C fallback for `nullptr` also tests whether the macro already exists. Both versions leave C++ to supply its own definition. |

## Portable host code

Eight paths have identical contents on the fork and integration. They are the `LoaderTransfer.h` and `PortCompat.h` headers, the host test directory’s `.gitignore`, and all five test sources. These are the other four paths.

| Fork path | Integration |
|---|---|
| `ports/include/pso/port/VectorMathFallbacks.h` | The only change is the comment identifying the current native source unit. Both named units include this header. |
| `ports/include/pso/port/ExiEthernetFallbacks.h` | The same byte-swap, read-command and leading-zero helpers serve the upstream C caller and the fork’s C++ tests. |
| `ports/tests/Makefile` | The loader test links the combined upstream translation unit. All five test programs pass in a clean export via both `make -C ports/tests run` and `make -C ports/tests sanitize`. |
| `ports/README.md` | The fork’s porting guide lives under [fork/ports](../../ports/README.md). |

The fork’s older conversion-pool symbol rewriting hook has no active build caller. The fork’s own [conversion-pool investigation](../../docs/evidence/conversion-pool-constants.md) records the translation-unit merge that retired it. The integration linker tools still identify conversion pools, and the native build reproduces the original executable without the hook.
