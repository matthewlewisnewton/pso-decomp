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
existing MSL headers declare them. `strtoul.c` now uses those word-array
declarations and explicitly interprets the float bit patterns, following the
existing `ansi_fp.c` convention. It no longer declares the same objects as
`float[]`. No constant bytes or target arithmetic change.

## BML model accessor

An inventory found 142 `get_bml_model` declarations/definitions across 138
source files: 121 `s32`, 5 `int`, 7 `u8 *`, 6 `void *`, and 3 `NJS_OBJECT *`.
The definition and shared header returned `NJS_OBJECT *`, but local prototypes
kept conflicting return/parameter types for that same C-linkage function.

Callers now include `BmlResource.h` and use its single canonical declaration.
No local accessor prototype or incompatible accessor function-pointer cast
remains. Legacy integer resource/model words use explicit conversions at
their calls or storage boundaries; this does not invent new field types or
claim that those words can hold pointers on a 64-bit port. Other accessor
families are outside this change. No wrapper, alias, assembly, or compiler
override is used to conceal the conflicting declarations.

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
in the continuation result.
