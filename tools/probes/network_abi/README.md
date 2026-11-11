# Network ABI compiler controls

These standalone fixtures explain two instruction changes in PR #303's rejected
shared thread-creator contract. The game build never compiles or links them.
They characterize compiler lowering, not the historical ABI. No original assets
are needed, and no game source, provider, compiler setting or behavior changes.

## Reproduction settings

Measured on 2026-11-11 at game-source head
`cdbcdf92bdcbd1a13a38113e828a7879c9bf3ae5`, using the actual resolved Ninja
commands for `NetworkTransport`, `NetworkDispatcher` and `NetworkRuntime`.
The wrapper is `build/tools/wibo`; the compiler is
`build/compilers/GC/1.2.5n/mwcceppc.exe`. Their SHA-256 hashes are:

- Wibo: `7fdf620b151744296b9bb93318d8c4009d3d3e98e23718a6eda9fbec4cefbb2a`
- Compiler: `ccf4b465cec73b5aae9c5c5543dcf8cda8a62aba246f89e2e0b200d742f2e55c`

The fixtures include the supplied `types.h`: native `s32/u32` are long-based,
not locally substituted `int` typedefs. The callback control also retains the
runtime's active `pool_data off` pragma. Dispatcher/runtime use `-opt nocse`;
transport does not. No other flags vary within a profile.

The compiler command below shows the dispatcher word-result/explicit-short
case. Use a private output directory and coordinate the operation through the
[existing capacity protocol](../../local_build_capacity/PROTOCOL.md). The
measurements used its unchanged workspace and legacy-exclusive acquisition for
one bounded ten-command operation; no shared tools or lock identifiers changed.

```sh
build/tools/wibo build/compilers/GC/1.2.5n/mwcceppc.exe \
  -nodefaults -proc gekko -align powerpc -enum int -fp hardware \
  -Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath \
  -i build/GPOE8P/include -i include -i src -i libs/dolphin/include \
  -i libs/dolphin/include/dolphin -char signed -use_lmw_stmw on \
  -O4,p -inline off -opt nocse -lang=c++ \
  -DCREATOR_SHORT=0 -DCAST_SHORT=1 \
  -c tools/probes/network_abi/status.cpp -o build/private-control-output
```

Compile all four `(CREATOR_SHORT, CAST_SHORT)` pairs `(1,0)`, `(0,0)`,
`(0,1)`, `(1,1)` with and without `-opt nocse`. For callback controls use the
runtime profile, `callback.cpp`, and `-DNO_ARGUMENT=0` or `1` instead of the
two status defines. The callee is unknown and external in every status case;
no visible definition permits a result-domain optimization. Linkage, argument
types, source basename and function names stay constant between alternatives.

## Status result

Both profiles produce this table. The initializer retains the original two
preceding short-result checks, two creator calls, cleanup branches, handle
lifetimes, and 0xF8-byte same-TU BSS state. Extension counts for the initializer
include those two preceding checks. Every minimal function has an 8-byte frame;
every initializer has a 24-byte frame.

| External declaration | Explicit caller conversion | Minimal bytes / extensions | Initializer bytes / extensions |
|---|---|---:|---:|
| `s16` | none | 72 / 1 | 260 / 4 |
| `s32` | none | 72 / 0 | 260 / 2 |
| `s32` | `s16` | 76 / 2 | 268 / 6 |
| `s16` | `s16` | 72 / 1 | 260 / 4 |

The short declaration produces `extsh. r0,r3`. Explicit conversion of the word
result produces `extsh r0,r3` followed by `extsh. r0,r0`. Thus the extra extension
is reproducible in a minimal function, and does not depend on surrounding game
code or callback storage. The faithful initializer reproduces the accepted
260-byte and rejected 268-byte functions byte for byte, with all 18 function
relocation tuples equal after explicitly mapping synthetic external names to
their corresponding game names. This is function-level comparison, not complete
object equality. The fixture's named state uses the same local BSS-section target.

This demonstrates the compiler mechanism. It does not establish that the
original creator returned `s16`; its observed return constants fit both widths.
Changing the producer type or compensating for the extra instruction is not
authorized by this experiment.

## Callback result

Both slot views retain stride 0x328 and callback offset 0x318, with compile-time
assertions. Lookup, pointer-view expression, search, and null return are identical.
Each variant is 124 bytes with an 8-byte frame. Only callback type/invocation
changes. At offsets 0x54/0x58/0x5C:

| Context argument | No argument |
|---|---|
| `mulli r0,r7,0x328` | `mulli r3,r7,0x328` |
| `add r3,r6,r0` | `addi r0,r3,0x318` |
| `lwz r12,0x318(r3)` | `lwzx r12,r6,r0` |

The context call requires the slot address live in r3 at the indirect call.
The no-argument call permits an indexed field load instead. Each control's
complete function bytes equal its corresponding accepted/rejected runtime
function, and all three relocations equal after mapping the three synthetic
external names (`current_thread`, `slot_count`, `slots`). No instruction bytes
are normalized. Neither result proves the historical provider parameter type;
the observed providers ignore incoming r3. An expression-shape workaround was
not tested or proposed for production.

All ten commands succeed. Independently re-extracted code, relocation, extension
and hash checks confirm these results. All 6,679 recorded production-input hashes
and five native-output hashes remain unchanged, including the original DOL and
four complete network objects. The private shared creator/raw callback/reset
ABI restrictions remain. These controls explain why the earlier repair failed;
they do not clear it for publication.
