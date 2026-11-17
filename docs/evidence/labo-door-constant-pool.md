# Laboratory and seabed door constant ownership

Base: fork main `15aca194b7f696a7505d149da1c0fd20f2d549dc`.

The generated unit `auto_11_805DDDB8_sdata2` holds three floats and a
four-byte alignment tail, covering `0x805DDDB8..0x805DDDC8`. All ten
original loads belong to `pso/misc/TODoorLabo.cpp`:

| Constant | Value | Original reads |
|---|---:|---|
| `0x805DDDB8` | `1.0f` | `0x8029F878`, `0x8029FB7C`, `0x8029FE10`, `0x802A0108` |
| `0x805DDDBC` | `0.5f` | `0x8029F880`, `0x8029FB84`, `0x8029FE18`, `0x802A0110` |
| `0x805DDDC0` | `50.0f` | `0x8029F8E0`, `0x8029FBEC` |

The first value is subtracted from the motion frame count; the second
initializes the adjacent animation field. The last initializes field
`0xC4` in the laboratory door constructors. These observations support
literal-pool ownership, without assigning new names to unresolved fields
or changing the existing provisional constructor interfaces.

Replacing the external loads with literals under the existing GC/2.6
settings emits the three floats in original order. The source split now
owns the complete 16-byte range. The old eight-byte symbol extent at
`0x805DDDC0` included four zero padding bytes: its two consumers use `lfs`,
and the next pool begins at the eight-byte-aligned address `0x805DDDC8`.
The corrected symbol size is four bytes; compiler/linker alignment
recreates the tail without a source padding object. No compiler override
or new steering pragma is needed.

After rebuilding the exact splits, the repository localization tool
verified that the three labels have no outside references. A separate
current-inventory audit checked every original and compiled object.
The labels are local, allowing the compiler-generated constants to supply
the bytes. The generated fallback unit disappears from the active split
inventory; the existing linked-unit entry continues to select the compiled
`TODoorLabo` object. No linkset or retention-list change is required.

Validation retains all 24 exact functions (2,652 code bytes), the 68-byte
resource descriptor section and the eight-byte conversion bias. The new
pool adds 16 matched and source-linked data bytes, including alignment,
for 92 exact data bytes in the complete source unit. No code, function,
data coverage or existing source linkage is lost. The full build retains
the original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`;
`tools/check_pr.py` passes, including linked-unit and retention checks.
