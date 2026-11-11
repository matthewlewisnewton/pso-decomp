# OSMemory reset registration data

This extracts only OSMemory's reset record from
[`1370dcf359541a5e6d0a3cc218513559a7431b6d`](https://github.com/matthewlewisnewton/pso-decomp/commit/1370dcf359541a5e6d0a3cc218513559a7431b6d),
authored by matthewlewisnewton with Cursor coauthor credit, as preserved in
[`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98`](https://github.com/matthewlewisnewton/pso-decomp/commit/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98).
Existing SDK notices and third-party attribution remain unchanged.

## Ownership and behavior

`os/OSMemory.c` already links on base
`5bba9c44adebc1cfa019def85e1f39f6da340ef0`. Its initialization passes
`&ResetFunctionInfo` to `OSRegisterResetFunction`. The SDK's existing
`OSResetFunctionInfo` declaration contains a callback, a 32-bit priority and two
links. The record at `0x804F4458` has the `OnReset` callback, priority 127 and
zero-initialized links. The split now assigns its 16-byte `.data` range,
`0x804F4458..0x804F4468`, to OSMemory.

Both `OnReset` at `0x8037340C` and `ResetFunctionInfo` were already named local
symbols in base metadata. Source now uses those local definitions rather than
external address-suffixed aliases. No callback body, compiler setting, symbol
metadata or linkset membership changes. This is data ownership, not a new
function match or a newly linked unit.

## Validation against the base

- Fresh serialized native builds of base and candidate reproduce original DOL
  SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `check_pr.py` passes: matched and source-linked data each gain 16 bytes;
  matched functions, matched code and source-linked code are unchanged. All
  3,608 linked units remain exact, with no address-coverage loss.
- Of 3,632 active compiled objects, 3,631 are raw-identical to base. OSMemory's
  complete existing allocated `.text` section is byte-identical. Its existing
  relocations are identical after mapping the two removed address-suffixed
  aliases to their already-established names. The added `.data` section matches
  the original in all 16 bytes, alignment 8 and its single `R_PPC_ADDR32`
  relocation to `OnReset` at offset 0.
- OSMemory's full compiled `.text` also includes pre-existing discarded SDK
  functions. The owned 736-byte `.text` range remains exact; no extra function
  coverage is claimed for those discarded contributions.
- The only linker-input change is removal of the original 16-byte automatic
  data object now owned by OSMemory: 3,608 compiled-source and 1,337 original
  fallback objects remain, in their original relative order. Retention was regenerated from fresh candidate split objects
  and config: all 18,602 entries remain unchanged. Port-exception inventory is
  unchanged; this extraction introduces no exception.
- All 306 original-free host tests pass. Portable `make -C ports/tests run`
  and `make -C ports/tests sanitize` pass with AddressSanitizer and UBSan enabled.

Validation records and original-derived build products remain local. The source
and this ownership explanation contain no copied game assets.
