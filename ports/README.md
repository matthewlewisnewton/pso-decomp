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
| `tests/ginja_parameter_callbacks.cpp` | Tests the one- and two-argument material parameter callbacks through their actual function types. |
| `include/pso/port/ExiEthernetFallbacks.h` | Scalar byte-swap, register-command and leading-zero operations used by the EXI Ethernet driver. |
| `tests/exi_ethernet_fallbacks.cpp` | Exhaustive 16-bit command/byte-swap checks and interrupt-priority boundary checks. |
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

## Socket send queue and selective acknowledgments

The port build compiles the three bounded SACK, ACK and send-gather routines directly
from `src/pso/network/SocketProtocolRuntime.cpp`. To use them in another target,
compile that file with `-DPSO_SOCKET_QUEUE_PORT -Iports/include -iquote include`.
The backend supplies the operations declared in `pso/port/SocketQueue.h`, the TCP
state and the completion dispatcher. The socket records use host byte order.
A backend importing GameCube state must also decode the queue-mode bit into
`f204_b7` because bit-field ordering depends on the target ABI.
Buffers and callbacks in stored game records use four-byte identifiers.
The host backend resolves them and copies each 16-byte ring entry into a typed
local request. It can keep native pointers for that request and the TCB array.
This interface covers the three routines. The rest of the socket stack still
needs platform implementations.

To build and run the Linux ARM64 fixture from the repo root with GCC and QEMU:

```sh
aarch64-linux-gnu-g++ -std=c++98 -O2 -static -DPSO_SOCKET_QUEUE_PORT \
    -Iports/include -iquote include ports/tests/socket_queue.cpp \
    src/pso/network/SocketProtocolRuntime.cpp -o /tmp/pso-socket-queue-arm64
qemu-aarch64 /tmp/pso-socket-queue-arm64
```

The standalone run checks the entire connection record in 200,000 SACK cases
and exercises a completion callback that moves the queue head. To compare
the same executable with the original game, install Unicorn 2.1.4 for Python
and provide a local dump of the US Rev 2 executable:

```sh
python3 tools/probe_socket_queue_port.py --dol orig/GPOE8P/files/PsoV3.dol \
    -- qemu-aarch64 /tmp/pso-socket-queue-arm64
```

The differential runner exercises the queued-request and FIFO modes. It compares
return values, packets, connection records, request rings, data buffers and
completion events across architectures.

With GCC 13.3 on x86-64 and AArch64 Linux under QEMU 8.2.2, each binary
agreed with the retail DOL in 2,400 gather, 1,600 ACK and 1,024 SACK cases,
including 1,717 completion events. The ARM64 run also passed with undefined-
behavior and bounds instrumentation enabled.

The debug AVE-TCP gatherer uses the selected fragment index to delimit the
prepend loop and reads the selected fragment's length in its trailing branch.
The port uses those expressions directly. Checkpoint `7ae77309ec` documents
the closest native build and the CodeWarrior differences for this form.
[Debug-build comparison](../docs/evidence/socket-protocol-runtime.md#comparison-with-the-browsers-ave-tcp-debug-build)

GCC 13.3 also compiles the complete 21-function GameCube source as a
freestanding AArch64 ILP32 object. This build uses four-byte native pointers.
It still requires the game's buffer, socket, callback and thread providers
to link. The Linux executable tested above uses the usual eight-byte pointers.

```sh
aarch64-linux-gnu-g++ -mabi=ilp32 -std=gnu++98 -ffreestanding -fno-exceptions \
    -fno-rtti -O2 -Iinclude -Ilibs/dolphin/include -Ilibs/dolphin/include/dolphin \
    -c src/pso/network/SocketProtocolRuntime.cpp -o /tmp/pso-socket-ilp32.o
```
