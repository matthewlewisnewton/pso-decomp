# TCP queues and network integration

Fork main `3342e42983` contains the socket runtime from fork PR 457. Its C++ implementation adapted the upstream C network stack. The integration keeps the C library, the existing TCP control-block layout and upstream's native symbols. [Fork PR 457](https://github.com/matthewlewisnewton/pso-decomp/pull/457)

| Integration commit | Source evidence |
| --- | --- |
| `b332dc4f9a` | The queue, socket API and completion callback share the 16-byte send request. Receive and completion callbacks carry their native status and handle types. |
| `db0bd68721` | TCP reassembly and selective acknowledgements share unsigned sequence ranges. The receive-room clamp and range-length helper reproduce the native instructions. |
| `8a221ccb53` | Send acknowledgement reloads the queue head after a callback. The send gatherer preserves the order of ring and pending fragments. The portable path walks the prefix by index. |
| `7d7f185846` | The modem initializer locks EXI, initializes the two state blocks, writes the configuration registers, runs its setup commands and installs its callback. The source object owns both 12-byte command rows. |
| `3e83afaa84` | The modem dispatcher uses its native leading-zero instruction on GameCube and the fork’s portable implementation on the host. Host fixtures exercise both initialization outcomes, all 65,536 interrupt status and mask pairs, eight receive scenarios and Ethernet frame forwarding. |

The integration build and the standalone network matchpass both reproduce the original GPOE8P executable, SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Each passes the project check against upstream and preserves all 27,572 exact functions. The integration build has 2,539 exact source-linked units, and the standalone matchpass has 2,541.

The queue probe compared the original executable with the matching build and separately linked builds with both portable bounds options enabled. Each run passed 786 reassembly comparisons, 12 out-of-order receives, 2,528 gathers and 1,600 acknowledgements with 1,766 completion events. The receive cases cover the signed boundary and the 32-bit sequence wrap. The send cases include callback reentry. The broadband adapter helper checks exhaust the 16-bit values and run with address and undefined-behavior sanitizers.

The public receive API, receive queue entry point, and completion functions share declarations. The intermediate legacy C helper at 0x8041DBD4 retains its differing caller and callee integer widths. The checks cover GPOE8P and emulated queue operations. Live modem and broadband hardware remain outside the validation performed here.
