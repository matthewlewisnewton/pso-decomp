# Third-party code

Code adapted from these projects keeps its original notices in the source files.

| Project | Used for | License |
| --- | --- | --- |
| [ac-decomp](https://github.com/ACreTeam/ac-decomp), [Twilight Princess](https://github.com/zeldaret/tp), [doldecomp](https://github.com/doldecomp) | Dolphin SDK, MSL and runtime sources | CC0 |
| [dtk-template](https://github.com/encounter/dtk-template) | `configure.py` and the build scripts in `tools/` | CC0 |
| [Ninja](https://github.com/ninja-build/ninja) | `tools/ninja_syntax.py` | [Apache 2.0](LICENSES/ninja-Apache-2.0.txt) |
| [newserv](https://github.com/fuzziqersoftware/newserv) | protocol structure layouts | [MIT](LICENSES/newserv-MIT.txt) |
| [fdlibm](https://www.netlib.org/fdlibm/) | math functions | [Sun notice](LICENSES/fdlibm-SunPro.txt) |
| [pso-decomp](https://github.com/zeroz41/pso-decomp) | quadrilateral overlap adapted from [upstream #309](https://github.com/zeroz41/pso-decomp/pull/309) and sphere-contact candidate adapted from [upstream #311](https://github.com/zeroz41/pso-decomp/pull/311); TCP control-block layouts and TCP recovery adapted from `NetTcp.c` / `NetTcpState.h` at `b0b44cbda23b206e1e5457a0e3711e0c0dd48bb8`; TCP out-of-order receive queue from `SocketProtocolRuntime.c` at `be4a012306441b91fe0e30083800a8589bccf518` ([upstream #285](https://github.com/zeroz41/pso-decomp/pull/285)); TCP receive delivery, send acknowledgement, send gathering and their callers from [SocketProtocolRuntime.c at 256e5a7](https://github.com/zeroz41/pso-decomp/blob/256e5a7d353d47f899c22c0ec148a75064d96079/src/pso/network/SocketProtocolRuntime.c); Dark Falz type 1 state table, native class and position generator ([commits and adaptation details](../docs/evidence/boss4-type1-unit.md)) | [MIT](LICENSES/pso-decomp-MIT.txt) |

The CRI LSC initialization split and build-banner declaration follow upstream
[matchpass 18](https://github.com/zeroz41/pso-decomp/commit/b0b44cbda23b206e1e5457a0e3711e0c0dd48bb8)
under the [upstream MIT license](LICENSES/pso-decomp-MIT.txt).

The reverse-tech scene hook layout and initializer follow upstream
[matchpass 19](https://github.com/zeroz41/pso-decomp/commit/1542ec2fe0a1f110cad6b88fca8d53a246d2585e)
under the [upstream MIT license](LICENSES/pso-decomp-MIT.txt).
