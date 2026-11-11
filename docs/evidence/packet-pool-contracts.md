# Packet lookup and unlocked allocator contracts

This independent extraction is based on main
`e9b77fcfdcc2335c9a5a92886826022c80505e67`. It carries only the packet lookup
repair from `80850ea411ac9ceecf90a2f6754f1027f63015f8` and unlocked allocator
repair from `ce710757b97ae8cef86e419559dd53a6fa1aab55`, previously validated
on the composite #303 branch. Neither earlier commit is a prerequisite.

## Contracts and native callers

The unchanged implementations in `NetworkPacketRuntime.cpp` define these C
interfaces. `NetworkPacketPool.h` now shares them with their callers:

| Helper | Producer contract | Original MessageTransport call relocations |
|---|---|---|
| `TLobby__sub_804256B8` | `NetworkPacketBufferDescriptor *(u32 address)` | `0x138`, `0x924`, `0xBE8` |
| `TLobby__sub_80425640` | `u8 *(u32 size)` | `0xFEC` |

An inventory of all 4,948 current original objects finds exactly these four
references, each `R_PPC_REL24` with zero addend. Source references agree.
This inventory does not prove the absence of dynamically constructed calls.

Lookup locks the existing mutex, searches active descriptors by unsigned
packet-address range, unlocks, and returns the descriptor or null. A descriptor
contains `in_use`, `queued_length` and `data` at offsets 0, 4 and 8. The three
callers retain their byte views of the **descriptor**, including the existing
queued-length writes. They do not substitute its packet-data pointer. Explicit
`u32` conversions preserve their existing native address words.

The unlocked allocator rejects unsigned sizes above `0x600`, accepts zero,
scans 32 descriptors in order, marks the first unused entry active and returns
its existing packet-data pointer. Exhaustion returns null. It does not lock,
clear packet bytes, initialize queued length or add rollback.

Its sole caller, `TLobby__sub_80426AAC`, already admits positive lengths no
greater than `0x5EE`. The wrapper retains its `s32` return because another mode
returns another provider's word. Only the allocator branch becomes
`ret = (s32)TLobby__sub_80425640((u32)len)`. These are explicit PPC32 native-word
boundaries, not a claim that pointer-to-word conversion is portable to a wider
host. Every guard, mode, failure path and producer operation remains unchanged.

## Validation against the pinned main

The unchanged-main baseline was authenticated by commit, clean tracked inputs,
configuration/build graph, tools, original objects and successful build/check
receipts. The extraction was built through the serialized capacity gate, with
fresh compilation of MessageTransport, PacketRuntime and NetworkRuntime.

- All 3,632 active compiled objects are raw byte-identical to main, including
  their full sections, symbol tables and relocation records; no normalization.
- All 4,948 original objects and ordered providers are unchanged: 3,603 source
  inputs and 1,345 original fallbacks.
- The rebuilt DOL has original SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `check_pr.py` passes address-based no-loss and source-link checks; 18,441
  retention entries have zero drift. Matched functions remain 27,434, matched
  code 4,232,424 bytes and matched data 1,477,099 bytes. No coverage gain claimed.
- All 306 current Python tool tests, portable behavior tests, ASan/UBSan tests,
  Python syntax, port-exception inventory and changed-line whitespace checks pass.

The locked allocator `TLobby__sub_8042558C`, its caller's legacy declaration and
copy expression are deliberately unchanged. Its prior combined typed migration
changed native output. Queue ownership/adjacency, private creator, raw callback,
reset-status and other unresolved contracts remain separate. This extraction
adds no compiler setting, pragma, source-provider change or behavior repair;
original behavior, including existing bugs, is preserved.
