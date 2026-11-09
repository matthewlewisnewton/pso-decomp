# PR #303 shared source contracts

The source audit of candidate `95d2c2bf37644746979e4bcc52c2092e12352322`
found declaration inconsistencies despite byte-identical target output. This
continuation reconciles those contracts. The earlier candidate is preserved
on a local branch; no publication is part of these changes.

## DHCP packet storage and reply flag

`pso/network/DhcpClient.h` supplies one definition of `BootpPacket`,
`DhcpMessage`, `DhcpClientBuffers`, and the shared volatile state/reply flag.
Previously the timer unit defined the storage as `DhcpClientBuffers`, while
the callback unit declared the same object through unrelated `G_804249F0`.
Their reply flag declarations also disagreed about `volatile`.

The storage consists of three 1,500-byte regions. The builders use the first
region, the callback at `0x804249F0` hands the UDP receiver the third region,
and its reply handler at `0x80424A48` copies accepted packets from the third
to the second. Compile-time checks cover header size/field offsets, message
size, region offsets `0`, `0x5DC`, `0xBB8`, and total size `0x1194`.
The callback uses the same header members as the builders. Both units take
their flag qualifiers from the shared header. This establishes consistent
declarations; it does not claim that `volatile` provides thread synchronization.

## Floating constants

The newly supplied MSL `float.c` defines `unsigned long` word arrays, as the
existing MSL headers declare them. Both `strtoul.c` and `render_util_tail.cpp`
now use those word-array declarations and explicitly interpret the float bit
patterns, following the existing `ansi_fp.c` convention. No reader declares
these objects as `float[]` or `const f32[]`. No constant bytes or target
arithmetic change.

## BML model accessor

The definition and shared header returned `NJS_OBJECT *`, but callers used
conflicting integer, void, byte-pointer and local node-pointer prototypes for
that same C-linkage function. Macros and function-pointer casts also hid
incompatible declarations, including one fabricated six-argument call.

All 179 source files referencing the accessor now directly include
`BmlResource.h` and compile against its single canonical declaration.
No local accessor prototype or incompatible accessor function-pointer cast
remains. Legacy integer resource/model words use explicit conversions at
their calls or storage boundaries; this does not invent new field types or
claim that those words can hold pointers on a 64-bit port. Other accessor
families are outside this change. No wrapper, alias, assembly, or compiler
override is used to conceal the conflicting declarations.

The dolphin loader at `0x802C2958` now copies the real `NpcAnimationBinding`
object, replaces its motions pointer with `BmlResource::motions`, and supplies
that local binding to `register_animated_chunk`. This produces the original
four-word copy followed by its first-word overwrite. The old six-argument
accessor cast merely forced the copy temporaries into registers `r5`–`r8`;
those registers are not model-accessor arguments. The real two-argument call
and native binding copy retain the exact 184-byte function with no compiler
override or steering helper. The other Pigeon and Rafoie accessor casts/macros
are also ordinary shared-header calls now.

Two one-argument prototypes had hidden model-index arguments:

- At `0x800A3230`, the DarkGunner helper receives its index in `r4`, saves it
  across the model call, and reuses it for the texture call. Its caller at
  `0x800A305C` supplies 1. The model call now passes `(s32)a1` explicitly.
  The existing outer `void *` parameter remains a bounded legacy interface.
  The resource initialization's accessor function-pointer casts also become
  ordinary shared-header calls; node reads use the shared `NJS_OBJECT` fields.
- The radar constructor's three calls at `0x801FB4D4`, `0x801FB4E4`, and
  `0x801FB4F4` pass `&core->m_90` and indices 2, 0, 1, then store the returned
  model pointers in its three frame-model words. The helper at `0x801FB9A4`
  ignores the context, loads the resource into `r3`, forwards incoming `r4`
  to the accessor, and returns its result. It now has the shared static
  declaration `NJS_OBJECT *init_map_ptr(const s32 *, s32)`; a nonstatic
  receiver would incorrectly treat an interior word as a `TRaderMapCore`.
  The old `Fv` symbol was metadata, not evidence of a no-argument source
  signature. The metadata now uses the compiler-emitted `FPCll` signature,
  and the constructor calls the shared declaration instead of declaring a
  mangled symbol by hand. The existing helper name remains provisional.

## Validation before current-main integration

The shared DHCP/float repair and complete accessor migration both reproduce
the original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Against the preserved candidate report, exact functions, matched/complete
code/data, coverage, and linked units are unchanged; the radar signature is
the only function rename. The pinned compiler also emits the exact original
radar helper, its constructor calls, the DarkGunner helper and its caller.
Fresh full validation after integrating current main is recorded separately
below.

## Current-main integration

Merged main `560addd4270d97c8f14fbb1025d07ec3f5f751d2`, preserving the
three new units and inherited exception records from its #207 carrier. The
only conflicts were the two exception documents. Their merged inventory
contains 5,765 pragmas in 871 files and 175 unit overrides; this continuation
introduces no new pragma or override.

A separately built main baseline passes the original DOL hash, source-linkage
and retention checks. The merged continuation also builds to the original
DOL hash and passes `check_pr.py --no-build` against that fresh baseline:

| Measure | Current main | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,367 | 27,370 | +3 |
| Matched code bytes | 4,182,748 | 4,184,928 | +2,180 |
| Matched data bytes | 1,469,283 | 1,469,371 | +88 |
| Complete code bytes | 3,641,308 | 3,653,528 | +12,220 |
| Complete data bytes | 1,166,551 | 1,171,439 | +4,888 |
| Linked units | 3,573 | 3,573 | 0 |

There are no address-level regressions or coverage losses against current
main. Retention contains 17,591 names, with no missing or stale entry. All
3,573 linked units are exact. The three new matches are the same DHCP functions
as the initial PR; the declaration repairs deliberately add no match count.
The DarkGunner unit remains 43/43 with exact code/data; the radar constructor
unit remains 4/4 and its helper unit 3/3. Their original compiled source inputs
remain on the DOL's link edge. The porting-exception inventory check passes.

Against the preserved pre-contract candidate, the additional functions/data
and three additional linked units all come from current main. Its 4-byte
total-data decrease is main's dropped zero alignment padding, already
documented by the #207 carrier; the address-level delta check passes.

The four audited contract conflicts are reconciled. Other legacy accessor
families, integer storage fields, the character-select no-argument function
cast/receiver-as-index convention, and the opaque DHCP lease-parser/cookie
interfaces remain bounded inherited work. This continuation does not claim
complete original-source type recovery or host-pointer portability. Keep
the PR draft pending review and the separate publication authorization.
