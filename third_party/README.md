# Third-party code

Code adapted from these projects keeps its original notices in the source files.

| Project | Used for | License |
| --- | --- | --- |
| [ac-decomp](https://github.com/ACreTeam/ac-decomp), [Twilight Princess](https://github.com/zeldaret/tp), [doldecomp](https://github.com/doldecomp) | Dolphin SDK, MSL and runtime sources | CC0 |
| [dtk-template](https://github.com/encounter/dtk-template) | `configure.py` and the build scripts in `tools/` | CC0 |
| [Ninja](https://github.com/ninja-build/ninja) | `tools/ninja_syntax.py` | [Apache 2.0](LICENSES/ninja-Apache-2.0.txt) |
| [newserv](https://github.com/fuzziqersoftware/newserv) | protocol structure layouts | [MIT](LICENSES/newserv-MIT.txt) |
| [fdlibm](https://www.netlib.org/fdlibm/) | math functions | [Sun notice](LICENSES/fdlibm-SunPro.txt) |
| [pso-decomp](https://github.com/zeroz41/pso-decomp) | TCP control-block layouts and TCP recovery adapted from `NetTcp.c` / `NetTcpState.h` at `b0b44cbda23b206e1e5457a0e3711e0c0dd48bb8`; TCP out-of-order receive queue from `SocketProtocolRuntime.c` at `be4a012306441b91fe0e30083800a8589bccf518` ([upstream #285](https://github.com/zeroz41/pso-decomp/pull/285)); Dark Falz type 1 state table, native class and position generator ([commits and adaptation details](../docs/evidence/boss4-type1-unit.md)) | [MIT](LICENSES/pso-decomp-MIT.txt) |
