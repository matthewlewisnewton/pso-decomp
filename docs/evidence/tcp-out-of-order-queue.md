# TCP out-of-order receive queue

The implementation of `TLobby__sub_8041F914` at `0x8041F914` (size `0x48C`)
comes from [upstream #285](https://github.com/zeroz41/pso-decomp/pull/285),
immutable commit `be4a012306441b91fe0e30083800a8589bccf518`. The fork did not
previously define this function, so the adaptation brings in its complete
body and inline range-removal helper, rather than only the upstream diff.
The existing split assigns it to `pso/network/SocketProtocolRuntime.cpp`.
The upstream MIT notice is retained under `third_party/LICENSES/` and the
source is attributed in `third_party/README.md`.

The function rejects closed receive paths, nonpositive sequence displacements
and segments outside the available receive window. It skips the packet prefix,
copies fragments into the receive ring at their sequence displacement, inserts
or extends the reassembly range, removes covered ranges and refreshes the SACK
list. Comparisons between sequence ranges retain signed differences. Field
names whose meaning is unresolved remain unchanged.

The implementation uses the fork's existing `NetPacket`, `NetBufferRef`,
`TcpHdr` and `TcpTcb` declarations. The insert and SACK-refresh helpers now
take that same `TcpTcb`, replacing their private partial views without casts.
Their existing instruction matches must remain exact.

The shared declaration takes the upstream `u16` packet offset. The fork's
previous caller declaration took `u32`; merely narrowing its prototype lets
GC/1.2.5n omit the caller's native `clrlwi` instruction, because the callee
already truncates the argument. Instead, the call explicitly masks
`(len + total) & 0xffff` in the argument expression. This preserves both the
16-bit offset and the original instruction scheduling. Performing that mask
in an intermediate local schedules it earlier and loses the caller's exact
match. Both translation units now share one compatible declaration.

The scoped inline controls, declaration order, separate `n` and empty branch
are inherited matching constraints, documented in the
[porting exceptions register](../porting-exceptions.md). Upstream reports
99.62% without the empty branch. This is compiler-allocation evidence, not a
claim about how the original source was written.

Validation against fork `main` at
`1bb11b184a5c70c03062b4cfa26d7863b4ce1cec` passes `tools/check_pr.py`:
the original DOL SHA-1 is unchanged, matched code increases from 4,299,004
to 4,300,168 bytes, and exact functions increase from 27,505 to 27,506.
There are no function or data regressions. All 3,618 linked units remain
exact and generated retention metadata has no drift. The caller and both
retargeted helpers retain their exact matches. This unit still has three
unimplemented functions, so it remains outside the source linkset.
