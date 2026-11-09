# LaunchDol's stranded epilogue

Investigation on source head `5de7fd190c109955b36aebabc6d47b428fa8fc7c`
narrows the ownership question for `0x8042E9FC..0x8042EA0F`. The restore is
already reproducible as the ordinary C++ LaunchDol's epilogue. Its isolated
function representation is the remaining bookkeeping boundary; a standalone
prologue-less C function is not established by these bytes.

## Ordinary compiler output

The [#284 fallback](launch-dol-cpp-recovery.md) was compiled independently,
keeping `__MWERKS__` defined but selecting only its C++ branch in an ignored
temporary source file. No production source, symbols or build inputs were
replaced. With GC/2.6 and the unit's existing
`-O4,p -use_lmw_stmw on -inline auto -opt nocse,nostrength,noprop` settings:

- The compiler emits one 332-byte (`0x14C`) LaunchDol function.
- Its first 296 bytes match the original LaunchDol prefix.
- Its last 20 bytes, at function offset `0x138`, exactly match the beginning
  of the adjacent original `text_8042E9FC` split.
- All ten `.text` relocation records match the original LaunchDol records;
  neither compared restore range contains a relocation. MWCC's separate
  metadata relocation section is not part of this comparison.
- Comparing that 332-byte C++ function with original LaunchDol plus the
  following restore leaves four differing instruction words, at offsets
  `0x128`, `0x12C`, `0x130` and `0x134`. These are the entry transfer already
  investigated in #284; no further tail-call spellings were tested here.

Thus the old 74.14% experiment's different restore register is not a current
obstacle. The current C++ frame already has the required r26-through-r31
save/restore and 0x20-byte stack allocation. This does not make the current
312-byte LaunchDol symbol or the separate pad function an exact C++ match.

## A second copy on the same disc

The disc's boot executable, `sys/main.dol`, contains the same complete
332-byte loader fingerprint at `0x80035558..0x800356A3`. Comparing this range
with `PsoV3.dol` at `0x8042E8C4..0x8042EA0F`, all 73 non-call instruction
words are identical. Only the ten relative-call displacement words differ;
all ten call sites remain relative branch-and-link instructions. The final
jump and all five restore words are identical, including their ordering.

| Executable | Loader start | Final jump begins | Restore begins | Next range |
|---|---|---|---|---|
| `files/PsoV3.dol` | `0x8042E8C4` | `0x8042E9EC` | `0x8042E9FC` | `0x8042EA10` |
| `sys/main.dol` | `0x80035558` | `0x80035680` | `0x80035690` | `0x800356A4` |

The boot DOL SHA-1 is `5f74659ed8968974ad3d334c4f22843800357dfe`, agreeing
with `config/GPOE8P/build.sha1`; the game DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The existing boot symbol inventory
also represents the loader as a 0x138-byte function followed by a 0x14-byte
function. Both executables are stripped, so those inferred symbol boundaries
are not independent original-source evidence.

A scan of every DOL text section found no direct unconditional or conditional
branch into either 20-byte restore range. This excludes direct branch entries,
not possible indirect transfers. Together with the identical frame and second
copy, it supports ownership by the preceding loader rather than by modem
parameter initialization. It does not recover an original source filename or
prove a compiler version for the boot executable independently.

As bounded controls, `switcher.dol`, `switcherD.dol`, `iwanaga.dol` and
`iwanagaD.dol` were checked too. None contains the same 332-byte loader
fingerprint. Each contains an `isync`/LR-transfer sequence using r31, followed
by exactly the same 20-byte restore as the separate SDK `Run` routine in
`PsoV3.dol`. The boot DOL has that SDK-shaped sequence as well as LaunchDol.

| Executable | SDK-shaped `isync` | Following 20-byte restore |
|---|---|---|
| `PsoV3.dol` | `0x80373958` | `0x80373964` |
| `main.dol` | `0x80012D80` | `0x80012D8C` |
| `iwanaga.dol` | `0x80226D48` | `0x80226D54` |
| `iwanagaD.dol` | `0x8023A2F0` | `0x8023A2FC` |
| `switcher.dol` | `0x806CB488` | `0x806CB494` |
| `switcherD.dol` | `0x80693510` | `0x8069351C` |

`libs/dolphin/src/os/OSReboot.c` keeps Run as its own generated assembly
routine. The game symbol inventory sizes Run at `0x80373938` to 0x40 bytes,
including its dead restore after the LR transfer; it does not invent a
separate function for that suffix. This is a useful same-project ownership
precedent. The SDK's configured compiler is GC/1.2.5n, versus the GC/2.6
LaunchDol probe, so these controls do not establish identical compiler
settings or original source between the two loaders.

## Reproducing the useful comparison

Use a fresh normal game build and compile the temporary fallback as described
in [the C++ reproduction](launch-dol-cpp-recovery.md). With its object saved
as `build/epilogue-probe/LaunchDolCpp.o`, compare sections without publishing
the original bytes:

```python
from pathlib import Path
import sys
sys.path.insert(0, "tools")
from link_units import elf_section_bytes

cpp = elf_section_bytes(Path("build/epilogue-probe/LaunchDolCpp.o"), ".text")
loader = elf_section_bytes(Path("build/GPOE8P/obj/pso/unk/text_8042E8C4.o"), ".text")
following = elf_section_bytes(Path("build/GPOE8P/obj/pso/unk/text_8042E9FC.o"), ".text")
assert len(cpp) == 0x14C and len(loader) == 0x138
assert cpp[:0x128] == loader[:0x128]
assert cpp[0x138:0x14C] == following[:0x14]
target = loader + following[:0x14]
assert [i for i in range(0, 0x14C, 4) if cpp[i:i+4] != target[i:i+4]] == [
    0x128, 0x12C, 0x130, 0x134,
]
```

For the second-copy comparison, extract only `sys/main.dol` from the local
disc into an ignored directory with `dtk vfs cp`; the container path syntax
is `<disc-image>:sys/main.dol`. Read each DOL's seven text ranges from its
header and compare the two addresses in the table. Ignore only relative-call
displacements at loader offsets `0x30`, `0x40`, `0x50`, `0x60`, `0x6C`,
`0xA4`, `0xB0`, `0xBC`, `0x108` and `0x114`; check that each is still a
relative branch-and-link. Retain the final jump and restore in the comparison.

## Consequences for recovery

The useful direction is one coordinated LaunchDol recovery with #284. Its
ordinary C++ frame already generates the restore; the unresolved transfer
precedes it. Searching for a separate C implementation of the five restore
words loses that owning-frame context.

A future ownership correction needs an explicit coverage-accounting plan.
Simply widening the existing symbol would remove the currently reported
function address at `0x8042E9FC` and fail the repository's address/no-loss gate;
it would not solve the four differing transfer instructions. No symbols,
splits, linkage selection, assembly exceptions or coverage rules were changed
for this investigation, and no new matching bytes are claimed.
