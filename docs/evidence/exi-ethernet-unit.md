# EXI Ethernet driver completion

Base: fork `main` at `1e8cf6d437b6ac2216d5cf41f3c296950f6d819e`.
Unit: `pso/misc/TLobby_80429598.cpp`, text `80429598..8042BF48`.
The existing avetcp profile remains GC/1.2.5n, `-O4,p`, `-inline off`.
No compiler override or assembly is added.

The legacy TLobby exports remain for ABI compatibility. Their spelling does
not establish a TLobby class relationship or an original filename. The three
previously absent bodies keep their address names.

| Function | Bytes | Observed role |
| --- | ---: | --- |
| `TLobby__sub_80429648` | 844 | Receive descriptor/ring traversal, ethertype filtering and DMA submission |
| `TLobby__sub_80429B8C` | 3,860 | EXI interrupt cause dispatch, counters, challenge response and completion callback |
| `TLobby__sub_8042AAA0` | 2,196 | Adapter identification, reset, MAC/configuration reads and callback installation |

## Recovery and provenance

The initial receiver was written from the original instructions and compiled
before researching the differences. Its first C++ object scored 87.89% fuzzy.
Subsequent trials compared C/C++ lowering, scalar/aggregate snapshots, helper
boundaries, integer expression types, optimizer options and scheduling models.
Those trials are investigation steps, not claims about the original source.

The EXI helpers, interrupt and initialization bodies adapt the same project's
upstream [driver recovery by Elias](https://github.com/zeroz41/pso-decomp/commit/d45158801364648741c00de15f78f5553079f414),
from `src/pso/network/TLobby_80429598.c`. The project's MIT contributor notice
is retained. The receiver was completed against this executable's control
flow rather than importing upstream's unmatched storage arrangement.

Relevant prior cases were the [audio/ADX recovery](audio-formats-and-adx-transfer.md),
[pack_movie_frame investigation](pack-movie-frame-unit-flags.md),
[Moja temporary-identity traces](moja-compiler-tracing.md), and the byte-lane
extraction in `TWindowSnapShot_802A5B2C.cpp`. The reconstructed
[compiler intrinsic definitions](https://github.com/PrimeDecomp/mwcc-tools/blob/3570fd49e67947c2e14dc9a677318a8858190305/src/backend/Intrinsics.c)
confirmed the native primitives and their types. Auxiliary GC/1.1 debugger
traces helped explain temporary ordering; they are not acceptance evidence.
Every final match and build uses the unmodified GC/1.2.5n compiler.

The receiver's read-command mask uses `__rlwinm` in the MWCC branch. The
scalar expression produced the same logical operation but introduced a
different temporary: the descriptor address occupied r5, delaying the EXI
frequency argument. The intrinsic with an inline flag setter reached 99.88%;
removing that setter's early temporary made all 844 bytes exact. Keep the
native mask directly in the macro expansion; moving it into another inline
wrapper needs a fresh complete-object comparison.

## Native storage and ABI boundaries

The receiver retains the observed 0x50-byte frame using MWCC-only unused local
slots. They represent compiler storage, not recovered packet fields, and are
neither read nor initialized. The separate volatile 32/16-bit snapshot and
volatile accesses preserve the observed six-byte descriptor publication order.
They do not provide host thread synchronization. A port omits the guarded
slots and implements callback synchronization in its EXI/OS backend.

The six-byte descriptor view covers next-page, length and status/reserved
bytes. Its original metadata still has separate labels at `805D7C5C` and
`805D7C60`, and at `805D7C6C` and `805D7C70`. This is a bounded native view;
it does not establish the ownership of the surrounding original globals.
The callback/table words remain at their existing PPC32 ABI boundary. The
queue uses the shared eight-byte `OSThreadQueue` declaration and MAC storage
uses its six-byte extent. Layout assertions cover the local descriptor and
128-byte adapter state.

The send-DMA callback has no consumed result in either its direct caller or
EXI callback path. Its declaration now returns void without changing the
native export name or instructions. The free DMA completion callback uses the
shared `OSContext*` type. Other legacy ignored-argument callback signatures
are retained at the existing boundary.

The original receiver calls the allocation callback when no ethertype
whitelist is installed. A positive whitelist count restricts it to a matching
entry. This differs from the upstream draft's nested callback condition and
must be preserved. Ring wrap arithmetic, interrupt priority, callback order,
error returns and lock-transfer behavior also retain the original behavior;
this change adds no validation or error-path repair.

## Data ownership and source linkage

The unit now owns `.data` `804FD9D8..804FDA1D`: the compiler-generated
eight-entry interrupt switch table (32 bytes) and two diagnostic strings
(12 and 25 bytes). No switch table is written by hand. The original table is
already local in symbol metadata. Named arrays preserve the exported string
symbols; their contents and positions match.

The three zero alignment bytes at `804FDA1D..804FDA20` leave reported data
coverage. The report delta identifies this as padding, and the linked DOL
reproduces those bytes. There is no loss of an exact function or non-padding
data range. The unit's existing 4,736 BSS bytes remain exact.

`link_units.py scan --write` adds only this unit. Its generated retention
change adds 15 unit exports with no removals; regeneration also sorts two
unchanged Needle export entries into their normal positions. Unchanged main
passed retention before the change, and the final list has zero drift.

## Validation

Fresh original split objects/configuration and the pinned tools were used in
the isolated worktree. Both baseline and candidate DOLs reproduce SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

| Measure | Before | After |
| --- | ---: | ---: |
| Exact unit functions | 16/19 | 19/19 |
| Exact unit code | 3,772 | 10,672 |
| Exact unit data, including BSS | 4,736 | 4,805 |
| Unit code linked from source | 0 | 10,672 |
| Unit data linked from source | 0 | 4,805 |

All three allocated sections score 100%. The source-link scanner checks
complete-object sizes, layout, alignment and symbols. Ninja's actual link
edge selects `src/pso/misc/TLobby_80429598.o`, with no original fallback for
this unit. Full original-DOL validation checks the resolved placement.

`tools/check_pr.py` passes: +3 exact functions, +6,900 exact code bytes,
+69 exact data bytes, +10,672 linked code bytes and +4,805 linked data bytes;
3,618 linked units become 3,619. No regression is reported. The three zero
padding bytes above account for the data denominator change.

The non-MWERKS branch uses the scalar operations in
`ports/include/pso/port/ExiEthernetFallbacks.h`. `make -C ports/tests run` and
`make -C ports/tests sanitize` pass, including all 65,536 byte-swap/register
inputs, upper-register-bit truncation, zero and all 32 leading-bit boundaries.
These tests cover the scalar primitives, not a full host Ethernet driver.
A complete port still supplies the SDK overlay, guest SI register view,
EXI/OS services and PPC32 callback/address translation described in the
[porting register](../porting-exceptions.md).
