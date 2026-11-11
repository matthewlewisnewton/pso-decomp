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
| `include/pso/port/LoaderTransfer.h` | Guest-state/backend interface for scalar loader handoff and restore handlers in the actual game units. |
| `tests/loader_transfer.cpp` | Complete transfer, wraparound, preservation and fault propagation checks; stream interface for original-code differential validation. |
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

## Loader machine boundary

Compile `src/pso/unk/text_8042E8C4.cpp` and `text_8042E9FC.cpp` with
`-Iports/include` and without `__MWERKS__`. These units expose
`pso::port::step_loader_boundary` through `LoaderTransfer.h`. A portable PPC
execution backend supplies numeric big-endian guest word reads and instruction
synchronization. Copy its GPR/LR/CTR/CR/XER/PC state into `LoaderState`, execute a
step, copy the state back, and dispatch the resulting guest PC. Preserve all
other backend state. Do not convert the LR transfer into a returning host call.

The handlers support each of the four handoff and five restore instruction
entries, including interior entries. Unknown PCs return false without effects.
A source-based port must retain enough guest state to honor this contract or
route this boundary through a PPC backend. The preceding relocation/reset body
and a complete host SDK remain port work. Fault delivery, cache behavior and
concurrent execution belong to that backend; these handlers specify completed
instruction behavior. See [contract and original-code differential tests](
../docs/evidence/loader-restore-retention.md#portable-integration-contract).
