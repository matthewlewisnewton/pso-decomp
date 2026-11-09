# LaunchDol C++ recovery

PR #284 remains relevant as recovery of the DOL section-table view and a C++
loader implementation. It is not a completed C++ match. The main integration baseline
`224eb99838471c243b20c305eddac75e7ff76c8f` already has the exact, linked
`LaunchDol` assembly implementation, so retaining that implementation adds no
matched code, functions or linked units against this main.

## Header view

`ModemLaunchContext::field_104` points to the loaded DOL header. The original
section loops read the seven text and eleven data file offsets at `0x00` and
`0x1C`, destination arrays at `0x48` and `0x64`, and size arrays at `0x90` and
`0xAC`. BSS address/size are at `0xD8`/`0xDC`; the entry pointer is at `0xE0`.
`DolImageHeader` is a descriptive view, not a recovered original type name.
It ends after the entry at `0xE4` and omits the remaining header padding.
Compile-time assertions verify its section offsets, BSS/entry offsets and size.

## C++ result reproduced on 2026-11-09

The native `__MWERKS__` branch is still main's generated `orig_asm` body. To
measure C++ independently, copy `text_8042E8C4.cpp` into an ignored temporary
file, keep the includes and declarations above `#ifdef __MWERKS__`, and replace
that conditional with only its `#else` branch. Do not undefine `__MWERKS__` for
this probe: its types and intrinsic handling must remain those of the target
compiler. Compile with the normal ntutl GC/2.6 flags and the unit override
`-inline auto -opt nocse,nostrength,noprop`, then compare the resulting
`LaunchDol` with the freshly split original object using objdiff.

The independent temporary compile reproduces **93.39744%**. Its first 296 bytes
(`0x000..0x127`, 74 instructions) and all 10 relocations within that prefix are
identical to the target. The compiled C++ function is 332 bytes; the target
symbol is 312 bytes. The section loops and setup are recovered, but the complete
functions are not byte-identical. This is a fuzzy result, not 312 recovered
matching bytes. The final 20 bytes of the 332-byte C++ output also equal the
stranded epilogue in the next original split. Across the combined span, only
the words at offsets `0x128`, `0x130` and `0x134` differ. That suffix equality
does not create a standalone matched symbol or linkable unit for PR #285.

## Remaining boundary

The target's final jump begins at `0x8042E9EC` and ends before `0x8042E9FC`.
The C++ source loads the actual typed entry pointer before synchronization,
as the target does. GC/2.6 then emits a CTR indirect call and a normal frame
restore. This ordering improves the result from 91.02564% to 93.39744%; it
does not change the entry type or introduce a forced register or qualifier. The original transfers control
through LR without restoring the frame. Earlier PR experiments tested other
MWCC versions and spellings; none established an ordinary C++ match for that
transfer. This evidence does not prove impossibility for every compiler or
source form.

The following 20 bytes at `0x8042E9FC..0x8042EA0F` are the stranded epilogue
tracked by stacked PR #285; `init_modem_check_params` begins at `0x8042EA10`.
This PR does not widen the LaunchDol symbol or remove that covered address.

A host port must supply loader and cache-operation equivalents; the fallback's
MWCC `__isync` call and console addresses do not establish host portability.
No host build or execution of the DOL loader is claimed. Keep the draft status
until the remaining C++/assembly boundary has an accepted resolution and the
final head receives independent review.
