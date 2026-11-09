# Ports

Host builds of the decompiled code. The matching GameCube build stays on
MWCC, the MSL/Dolphin headers and the original object layout; nothing here is
compiled into `PsoV3.dol`.

The layout follows the Super Mario Sunshine PC port and the Twilight Princess
port: a host compatibility header, a platform math include, and a test layer
that exercises the same scalar code the game units build on a port. A full
port would extend this with a Dolphin SDK header overlay
(`ports/include/dolphin`), host OS/GX/MTX implementations, and patches for the
GameCube-only layout asserts.

## Contents

| Path | Purpose |
| --- | --- |
| `include/pso/port/PortCompat.h` | Host C/C++ library include for the port layer. |
| `include/pso/port/VectorMathFallbacks.h` | Scalar `vec3_dot`, `vec3_cross` and `normalize_vector`; the same bodies the game units' non-MWERKS branches call. |
| `tests/vector_math_fallbacks.cpp` | Behavior tests for those fallbacks. |
| `tests/item_factory_callbacks.cpp` | Tests the typed item-factory callback path, including restoring the money factory's function type. |
| `tests/Makefile` | Builds and runs the tests. |

## Running

On x86_64:

```sh
make -C ports/tests run
make -C ports/tests sanitize
```

On an ARM target such as the Anbernic RG34XXSP (Allwinner H700, Cortex-A53),
cross-compile with the target compiler:

```sh
make -C ports/tests clean
make -C ports/tests CXX=aarch64-linux-gnu-g++ all
```

Run the resulting binaries on the device, or under `qemu-aarch64` when the host
has it.

The fallbacks use only the standard C++ library and `std::sqrt`, with no x86
or ARM intrinsics. `-ffp-contract=off` is the default in the test Makefile so
x86 and ARM hosts produce the same results; a port that enables hardware FMA
may round differently where the scalar code contains `a * b + c`.

## What this does not do yet

The full matching units still need a host SDK overlay and a force-included
compatibility header, as in the SMS and TP ports, before they can compile on
x86 or ARM. The GameCube layout asserts (`sizeof(TCameraCtrl) == 0x1D4`,
`sizeof(NJS_OBJECT) == 0x38`, etc.) and the `libc`/`dolphin` headers are
matching-build-only.
