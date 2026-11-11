# Socket protocol runtime recovery

The unit owns text `0x8041ED8C..0x80421620`, data
`0x804FD890..0x804FD948`, and BSS `0x805C1DF0..0x805C1E00`.
The data boundary includes the four compiler-generated switch tables in emitted
order; the last 88 bytes previously belonged to the following automatic split.
No table is written by hand.

The original starting baseline is `ead31005e05c515068799f79935dca70ea241206`.
The final fork-main prerequisite is `1e8cf6d437b6ac2216d5cf41f3c296950f6d819e`;
its unchanged full build, source-link and retention checks pass.
Before recovery, 17 of 21 functions matched: 5,064 of 10,388 code bytes and
112 data bytes. The complete reconstruction matches 21 functions, 10,388 code
bytes, and 200 data bytes. Newly recovered bodies are:

| Address | Bytes | Behavior |
|---|---:|---|
| `0x8041F204` | 1,128 | Consume receive fragments into the waiting read or receive FIFO. |
| `0x8041F914` | 1,164 | Insert received sequence ranges, merge overlaps, and update SACK state. |
| `0x8041FFF8` | 1,048 | Retire acknowledged send bytes and finish queued send callbacks. |
| `0x80420410` | 1,984 | Construct outgoing fragments from the send FIFO and queued requests. |

## Layout and ABI boundaries

`TcpControlBlock.h` replaces the overlapping TCP prefix views used by this unit.
Its `0x544` allocation stride, packet offsets, range table, callback fields and
capacity offsets are checked against the accesses and indexed walks in this
unit and `TcpProtocol.cpp`. Sequence numbers and range endpoints use unsigned
32-bit subtraction followed by a signed comparison, preserving TCP wraparound.

Five SACK ranges are active. `0x8041FED4` also reads the pair immediately after
range four while compacting, before clearing range four. The storage therefore
includes that sixth lookahead pair at `0x320`; this does not establish a sixth
active SACK range or the original declaration.

The send-request callback is shared with its actual provider in
`text_80421620.cpp`: signed 16-bit handle and status, and a typed 16-byte request.
The provider retains a signed 32-bit local handle; all 42 provider functions
remain exact. `TcpProtocol.cpp` now calls `0x8041FFF8` with the actual control
block pointer instead of integer arguments; its existing matches are preserved.

Other boundaries remain provisional: the global TCP runtime is only a pointer
and count prefix here, while older providers retain different partial views.
The slot/thread resume helpers still have legacy handle-width declarations;
consolidating those providers changed native bytes in the bounded probes.
UDP prefix and packet views, explicit legacy ABI symbol names, and provisional
`TLobby` wrappers are inherited. Source linkage does not establish their
original class ownership or make these interfaces portable.

## Native compiler constraints

Use GC/1.2.5n with the existing AVE-TCP profile and unit override `-inline on`.
The range-removal helper must inline. Its caller-owned eight-byte range value
preserves the reassembly function's native frame; no separate helper body is
emitted. Scoped `dont_inline` controls preserve the other native call boundaries.

`0x8041FFF8` uses scoped `opt_lifetimes off`, an unsigned read-index record, and
an unreferenced eight-byte local area. The area preserves the native 96-byte
frame and other local offsets; it is reconstruction debt, not proof of an
original local variable. The callback's formal 16-bit handle and its provider's
32-bit local are both needed for the original register allocation.

`0x80420410` uses scoped `opt_propagation off` because the executable retains
an otherwise unreachable partial-fragment branch with an index set to -1.
The fragment phase locals are deliberately distinct and their declaration order
preserves native register allocation. The shift counter is a named local and
is decremented before the address cursors. The packet-clear path exits the outer
scan loop and reaches its common return, rather than returning from the inner
branch.

The final partial length widens a signed 32-bit difference to `s64`. Its input
range fits signed 32 bits; the widening changes no arithmetic result. It keeps
the halfword store separate from the signed 16-bit extension in CodeWarrior.
An ordinary 32-bit local shares the extension with the store and differs in five
instruction rows. This is an emission constraint, not evidence for an original
64-bit local. The initial wrapped FIFO length uses a corresponding unsigned
halfword store to avoid an extra sign extension.

Reverse and prepend loops use unsigned 32-bit address cursors. Their final
unused decrement can precede the array; doing that with a C++ pointer would be
undefined even without dereferencing it. Only guarded valid element accesses
convert the integer addresses back to pointers. A port should use indices or
an appropriate guest-address representation, and remove optimizer/frame/type
steering while retaining the explicit halfword conversions and sequence math.

## Validation

Function, section, alignment, emitted symbol and ordered linker-input checks
are separate from the function scores. Rebuild the configured source link and
run `tools/check_pr.py` against the immutable baseline report. The original DOL
SHA-1 must remain `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Both the incremental comparison against the fork-main prerequisite and the
overall comparison against the original starting baseline pass without losing
an exact function, matched/linked code or data range. The final incremental
result is four new exact functions, +5,324 matched code bytes, +88 matched data
bytes, +10,388 linked code bytes, +200 linked data bytes, and one linked unit.
All 3,619 linked units and 18,838 retention names pass; the unit adds six
retention names and removes none. No symbol localization is required.

The actual ordered `psov3.elf.rsp` inputs must select the compiled socket
runtime object once and omit its original fallback. The private validation
receipt records the ordered input hashes, original DOL, pinned tools,
configuration, report and both immutable baselines. The declaration, layout,
function and data checks also pass after integration with the fork's newer
DHCP and receive-prefix changes in the shared callback provider.
