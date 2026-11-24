# Link the network OS runtime and IPv6CP helpers

Base: fork `fe6cdb14138b2413778c08f21fd1851170c22ab5`. Reference:
upstream [#213](https://github.com/zeroz41/pso-decomp/pull/213),
`76d99c974ba4897eca428c505be1af4d4f6ec124`, with the typed follow-up
[#215](https://github.com/zeroz41/pso-decomp/pull/215),
`9eb8da7276b625b67c1854e7ea3372b0d944f456`.

The fork already contained 51 exact functions in
`pso/protocol/NetworkRuntime.cpp`. Recovering its two missing bodies makes the
existing complete unit linkable; this change neither replaces the network stack
with upstream's C files nor changes split boundaries. The fork's unit spans
upstream's `NetworkRuntime.c` and `NetworkThreadRuntime.c`.

## Recovered functions and interfaces

- `TLobby__sub_803F8E9C`, `0x803F8E9C`, 820 bytes: resets thread, alarm,
  mutex, message-queue and buffer slots, then initializes the buffer/packet pools
  and PPPoE state. A thread handle is the address of its embedded `OSThread`;
  mutex and queue handles similarly address their embedded OS objects.
- `TLobby__sub_803FABDC`, `0x803FABDC`, 252 bytes: allocates an IPv6CP
  configure packet and appends enabled options using the existing option-length
  table and `TLobby__sub_803FADA0`. The callback takes one state pointer and
  returns a packet pointer. Correct both its declaration and protocol-table
  callback field; do not cast a three-argument callback to conceal the mismatch.

The initializer's three result tests use signed halfword results. Update
`TLobby::init_buffer_pool`, `initialize_network_packet_pool` and
`TLobby__sub_80428360` consistently to `s16` in declarations and definitions.
Their implementations return only 0 or -1 and remain exact. The last call passes
zero in r3; retain that argument as an unnamed `s32`, since its meaning is not
established. No incompatible local return-type redeclarations are imported.
The three helpers have no other source call sites in this baseline.

The 12-byte `NetworkBufferSlot` view is deliberately bounded to the existing
buffer-slot allocation at `lbl_805D7A64`. `TLobby_803F8794.cpp` allocates and
walks it with stride 12, clears its first word, and writes the size and buffer
address in the other two words (`Ent_803F8D84` / `Ent_803F8DBC`). This patch only
uses `active`; consolidating those older duplicate views remains follow-up work.
Compile-time assertions verify the buffer/thread strides and OS slot sizes and
handle-target offsets.

## Outstanding inherited matching constraints

These are recorded in section 4 of the [exception register](../porting-exceptions.md).
They are native ABI/compiler constraints, not evidence of portable source.

1. The initializer adds one scoped `pool_data on`. Its code uses the three
   contiguous source-defined BSS arrays as one address base. The exact layout is:

   | Object | Address | Size | Offset from alarm table |
   |---|---|---:|---:|
   | 64 alarm slots | `0x805BE070` | `0x1600` | `0` |
   | 8 mutex slots | `0x805BF670` | `0x100` | `0x1600` |
   | message queue 0 | `0x805BF770` | `0x3A8` | `0x1700` |
   | message queue 1 | `0x805BFB18` | `0x3A8` | `0x1AA8` |
   | existing IPv6CP state | `0x805BFEC0` | `0xA8` | `0x1E50` |

   The two queue addresses are formed beyond the alarm array, and the initializer
   retains word views of mutex/queue records plus 32-bit pointer-valued handles.
   This relies on the verified native layout, not standard C++ array bounds or
   aliasing guarantees. A port should use `network_message_queue_slot_table[0/1]`,
   typed `active`/`handle` fields and an appropriate pointer/handle representation.
   The explicit mutex initialization order, unused upstream locals and unused
   assignment remain because simpler expressions change MWCC's schedule/frame.
   This is documented technical debt, not a claim about the original source text.
2. The IPv6CP callback retains the redundant second null test and its `goto done`.
   The original code actually contains the second conditional branch and fallback
   allocation. It also retains the existing `A_803FADA0` view of the option block
   starting at `h1C` and the explicit `init_net_buffer_entry__6TLobbyFUs` ABI name.
   A port can remove the redundant branch and consolidate the packet/option types
   and allocator declarations across the protocol library.
3. Linking the unit activates its previously present debt: 32 existing pragmas
   (`dont_inline`, `inline_depth`, common-subexpression/data-pooling controls,
   propagation/lifetime/dead-assignment settings and `bool`), its existing
   `-opt nocse` override, the bus-clock reads at `0x800000F8`, raw packet/option
   views, explicit mangled ABI names and several provisional `TLobby`/`TUdpSocket`
   wrappers. This patch does not claim to resolve those boundaries. Ports should
   use target OS timing/thread/queue/mutex services, shared protocol types and
   ordinary free-function interfaces, and remove optimizer-only steering.

No new assembly, intrinsic, hardware access or per-unit override is introduced.
The generated inventory rises by one pragma (5,771 to 5,772); section 7's narrow
upstream catch-up scope remains unchanged at 521 entries on this baseline.

## Bounded cleanup probes

With the pinned GC/1.2.5n compiler, compare the source object against the original
split with `build/tools/objdiff-cli diff -1 build/GPOE8P/obj/pso/protocol/NetworkRuntime.o
-2 build/GPOE8P/src/pso/protocol/NetworkRuntime.o -o diff.json`.
The following probes changed only initializer expressions; the remaining functions
stayed exact. Scores are for `TLobby__sub_803F8E9C`, not the whole unit.

| Alternative | Match |
|---|---:|
| Straight typed loops and explicit result truncation | 74.49268% |
| Typed slots with staged mutex pointers and consistent `s16` interfaces | 95.74146% |
| Remove the remaining unused initializer locals | 99.94634% |
| Use actual queue-array addresses at their initialization sites | 97.439026% |
| Replace the remaining mutex word views with typed fields | 97.53658% |
| Remove the unused first-mutex assignment | 96.8% |
| Retained constraints with typed thread/alarm access, actual mutex-array addresses, and redundant mask removed | 100% |

One unused scalar was removed without changing the object. The thread and alarm
accesses now use their existing fields, and mutex addresses use their actual array
instead of upstream's offsets across the alarm array. Further cleanup is welcome
but must preserve the native build or be confined to a nonmatching port.

## Validation and gain

Built current main with the pinned compiler and original inputs, saved the report,
and verified clean retention before editing. Full build, original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, address-aware no-loss comparison,
all linked units and generated retention checks pass. Python syntax checks and
all 268 source-tool tests also pass.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,383 | 27,385 | 2 |
| Exact code bytes | 4,187,972 | 4,189,044 | 1,072 |
| Exact data bytes | 1,470,159 | 1,470,159 | 0 |
| Linked code bytes | 3,659,388 | 3,667,732 | 8,344 |
| Linked data bytes | 1,167,699 | 1,175,627 | 7,928 |
| Linked units | 3,584 | 3,585 | 1 |

All 53 functions and the complete BSS section match. The existing BSS becomes
source-linked; it is zero-initialized program state, not extracted asset bytes.
The scanner adds exactly this unit and 20 generated retention entries, removing
none. Total function, code, data and unit counts do not change. No old match,
linked range, or alignment padding is lost. The dispatcher and other network,
keyboard and technique gaps remain separate follow-up work.

Actual ordered linker inputs agree with the report: 3,585 source objects and
1,388 original fallbacks (4,973 total). The ordered-input SHA-256 is
`505a2e0e9e345d7de14b21923024a9445968ca999228df88874db758749afe19`.
