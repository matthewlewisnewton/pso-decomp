# Radar language linkage

This audit starts from scaled radar gate PR #150, commit
`bd1d0653d779a80217f177a70114da3fc3e90c0b`. It covers `RadarMapData.h`,
`TRaderMapCore.cpp`, `TRaderMapCore_801FB2B8.cpp` and `TObjRaderIcon.cpp`.
Compass descriptor work and further radar recovery have separate ownership.

## What can be removed locally

The three implementation files' broad `extern "C"` blocks enclosed nine existing
member definitions. Language linkage specifications do not change class members'
C++ linkage. Close the blocks after the imported declarations instead. Free
functions retain C linkage through their preceding declarations, including
`should_show_map__13TRaderMapCoreFv`, the radar task/destructor/constructor bridges,
and the icon factory/constructor declarations in the existing headers. This is
scope cleanup, not conversion of those bridges to native members.

Use the canonical declarations for these five imports:

| Import | Header | Contract |
| --- | --- | --- |
| `GXSetScissorBoxOffset` | `dolphin/gx/GXTransform.h` | `void(s32, s32)`; replaces incorrect `s32(int, int)` |
| `GXSetViewport` | `dolphin/gx/GXTransform.h` | Six `f32` arguments, `void` result |
| `GXSetScissor` | `dolphin/gx/GXCull.h` | Four `u32` arguments, `void` result |
| `memset` | `string.h` | `void *(void *, int, size_t)`; replaces incorrect `s32(void *, int, int)` |
| `sin_table_lookup` | `pso/math/AngleLookup.h` | `f32(s32)`, unchanged |

SDK and CRT declarations keep their genuine C ABI in the headers. The angle
helper's unmangled name remains the current recovery contract; its header is not
evidence that the original implementation was written in C.

All three scissor-offset calls ignore the result. On the pinned 32-bit Gekko
compiler, their signed `int` values convert exactly to signed `s32`. The sole
`memset` call clears the 0x30-byte local viewport record and ignores the returned
pointer; positive constant 0x30 converts exactly to `size_t`. No object ownership,
receiver, callback type, overload, memory access or argument evaluation changes.

Include the project `string.h` before Dolphin headers: Dolphin's incomplete
`libc/string.h` shares its guard and does not declare `memset`. The SDK's existing
`PSO_SDK_COMPACT_MATH` mode prevents unused static constants in inline `sqrt`/`sqrtf`
from adding 32 bytes of `.rodata`. It changes no called math implementation here;
the complete allocated sections and relocations must still compare equal. This
uses the same header mode as `AdxStreamRuntime.cpp` and `text_803D853C.cpp`.

## What remains provisional

The original-object scan covers 5,065 objects. `add_radar_scaled_gate` has precisely
three references, all direct calls from the icon unit, and no observed callback
registration. Its inputs use the mixed integer/floating Gekko calling convention;
it copies position/scalars into externally owned marker storage and returns 0/1.
There is no evidenced receiver argument justifying a nonstatic member. Ordinary
C++ free-function linkage would change its symbol name and every corresponding
relocation. A static member would also require supported class ownership and a
separately reviewed metadata rename. Keep the shared C declaration for now.

`TRaderMapCore__map_view_state` is a 120-byte original BSS object, referenced by
24 relocations in the radar and constructor units. The narrow header declares
three view records and does not define storage. CodeWarrior leaves simple global
variable names unmangled even with C++ linkage, so equal data-symbol names alone
cannot establish either necessary C linkage or compatible object types. Do not
move storage into a class or infer ownership from the recovery symbol spelling.

The factory `TObjRaderIcon__create` has 16 original data references in
`ObjectFactoryTables.o`. The radar task and destructor bridges each have an
original vtable data reference. These are real callback consumers, but their
hand-spelled bridge names do not prove original C language linkage. Replacing
those bridges with members requires factory/vtable type and lifetime evidence;
casting function pointers would not resolve the contract.

Other retained imports include provisional global/record views, explicitly
spelled member ABI names, matrix/render interfaces and camera/player helpers.
No blanket removal is justified by the fact that a declaration compiles. Existing
conflicts illustrate the risk: radar units disagree about the return and receiver
of `get_entity_id`, the pointer result of `get_player_by_client_id`, and the result
and receiver of `update_radar_auto_discovery`. The icon's local switch-query
prototype takes `u16`, while its canonical header and provider take `s32`.
Including that header would change argument truncation unless a separate semantic
analysis resolves the intended range. `fn_803D64F8` initializes a separate 0x28-byte
record; its use does not justify a `TRaderMapCore` object lifetime or receiver.

## Proposed follow-up ownership, in order

1. **Canonical SDK/CRT imports:** a separate cleanup owner can audit
   `RefCountedWorkBuffer.cpp` and `TObjEneRecon_8029E89C.cpp` without changing shared
   headers. The former repeats the incorrect `s32 memset` contract and encloses a
   `TLobby` member in a C block; the latter declares `GXSetScissor` with an `s32`
   result and signed arguments. Check ranges and complete objects independently.
2. **Angle imports:** the angle-contract owner can reconcile local declarations in
   `TEffIndirectCtrl_802A88AC.cpp` and `text_803369C8.cpp` against `AngleLookup.h`.
   The latter uses pointer-typed angles: canonicalizing it needs evidenced scalar
   conversions, not a function-pointer cast. Preserve the provider and shared
   angle header until all consumers are allocated and checked.
3. **Radar/player/switch boundaries:** allocate the player helper providers and
   their canonical headers to the player-contract owner; allocate `TSwitch.cpp`
   and `TSwitch.h` to the switch owner, with radar/icon callers coordinated.
   Resolve the conflicts above before moving declarations or narrowing types.
   The scan finds 971 original references to `get_player_by_client_id` and 85 to
   the switch query, so a local byte match cannot validate a shared change.
4. **Native radar interfaces and storage:** the radar class/storage owner must
   establish task/destructor/factory signatures, view-record identity and all
   consumers. A justified C++ function rename needs separate symbol-metadata
   review preserving original address, size, section and flags. Do not hide that
   dependency with aliases, assembly, casts, fabricated classes or exclusions.

These are proposed allocations, not claims on other workstreams. In particular,
compass PR #152 and the separate `copy_transform` receiver investigation remain
untouched.

## Validation boundary

Targeted baseline/candidate complete translation units were compiled with pinned
GC/2.6 production flags. All 51 existing defined functions, 577 allocated-section
relocations, allocated bytes, section sizes/alignment/flags and symbol
binding/visibility/type/extent compare equal. Compiler-local label numbers are
normalized by section and offset. Constructor and icon objects are byte-identical.
The radar object retains the 216-byte gate and its nine relocations; the unused
SDK constants described above are absent. Private dialect probes also confirm
C free-function naming, C++ member mangling inside a C block, and unmangled simple
global variables on this compiler.

This targeted result does not replace fresh full baseline/candidate builds,
original DOL reproduction, ordered source/fallback input checks, address/data/link
no-loss checks, independent review, or current-main queue acceptance.
