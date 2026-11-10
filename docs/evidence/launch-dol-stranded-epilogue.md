# LaunchDol's stranded epilogue

This records bounded ownership evidence for `0x8042E9FC..0x8042EA0F`.
The range remains unmatched, with its address and ownership hold preserved.
Narrowed #284 at `d70369041672d5c881d895dc0a27b96f612e4b0c` contains the
DOL header view and caller conversion; it removes the experimental C++
loader and its per-unit compiler override. This document does not restore
either one. The active provider and compiler settings remain those of main.

The earlier investigation at `5de7fd190c109955b36aebabc6d47b428fa8fc7c`,
refreshed at `5b639174d431c7bcbe1c1d007f9998a0a60ec09f`, compared an
experimental C++ frame with this restore. Matching suffix bytes do not
recover an independently callable function or establish behavior equivalence.

## Historical experimental compiler output

The historical candidate remains inspectable at immutable commit
[`a9eab37139ef10f53e3e9baf4f8d2dd1ade395aa`](https://github.com/matthewlewisnewton/pso-decomp/blob/a9eab37139ef10f53e3e9baf4f8d2dd1ade395aa/src/pso/unk/text_8042E8C4.cpp).
Only its C++ branch was selected in an ignored temporary source, retaining
`__MWERKS__` for target types and intrinsics. The experiment used GC/2.6 with
`-O4,p -use_lmw_stmw on -inline auto -opt nocse,nostrength,noprop`.
Those are historical experiment settings, not an active per-unit override.

- The compiler emitted one 332-byte (`0x14C`) LaunchDol function.
- Its first 296 bytes matched the original LaunchDol prefix.
- Its last 20 bytes, at function offset `0x138`, exactly matched the beginning
  of the adjacent original `text_8042E9FC` split.
- All ten `.text` relocation records matched the original LaunchDol records;
  neither compared restore range contained a relocation. MWCC's separate
  metadata relocation section was not part of this comparison.
- Comparing that 332-byte C++ function with original LaunchDol plus the
  following restore left three differing instruction words, at offsets
  `0x128`, `0x130` and `0x134`. These are the entry transfer already
  investigated in #284; no further tail-call spellings were tested here.
  The initial probe also differed at `0x12C`; #284's reviewed change to load
  the entry before `__isync()` removed that difference. The 332-byte
  output, prefix, suffix and relocation comparisons were reproduced against
  the historical base named above.

Thus the older 74.14% experiment's different restore register did not remain
an obstacle in the later experiment. Its frame had the required
r26-through-r31 save/restore and 0x20-byte stack allocation. This was a
93.39744% experimental comparison, not an exact 312-byte LaunchDol function,
working host fallback, behavior-equivalence proof or independent pad recovery.

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

## Original metadata and stored-address checks

The original exception index does not supply the missing ownership boundary.
Both pinned DOLs have a null-terminated exception registration record with
the following half-open ranges. These values were read from the original
inputs, not from a reconstructed ELF or compiler probe.

| Executable | Registration record | Exception index | Records | Registered code range |
|---|---|---|---|---|
| `PsoV3.dol` | `0x8000F704` | `0x8000EC60..0x8000F704` | 227 | `0x8039667C..0x803BFE50` |
| `main.dol` | `0x8000E75C` | `0x8000E660..0x8000E75C` | 21 | `0x8000E780..0x8002BB8C` |

Every index record has a positive function size, is ordered by function
address, stays within its registration's code range and points into its
original exception-table section. Neither registration nor any index record
overlaps the corresponding loader/restore range in the earlier table.
Consequently, this metadata cannot distinguish the current 312-byte loader
boundary from a 332-byte owning-frame interpretation. Absence of an exception
entry does not establish that either extent is the original source function.

A separate scan found no four-byte-aligned, big-endian address word in any
initialized DOL data section pointing anywhere into the loader/restore span:
219,888 words checked in the game and 7,984 in the boot executable. This
narrows the search for a stored absolute entry address, including an entry
into the restore. It does not exclude computed or relative addresses,
unaligned storage, addresses constructed by instructions, runtime writes or
indirect entry. It is not an additional proof that the restore is unreachable.

To reproduce these bounded checks, first verify the two SHA-1s above. Map
virtual addresses to file offsets using the DOL header's seven text and
eleven data offset/address/size entries. At each registration address, read
four big-endian words as index start, index end, code start and code size;
the following four words are zero. Walk the index in 12-byte records
containing function start, function size and exception-table address. Check
the ranges and ordering before testing overlap. Then walk only populated
data sections at virtual addresses divisible by four and test each unsigned
word against the corresponding half-open loader/restore range. Do not scan
file padding or invent contents for uninitialized storage.

DTK 1.8.4 (`a0c455e46cab58e1d2e0885623f85089ff0499db`)'s unconfigured
`dol info` analysis also rejects both originals
as an unpaired epilogue, at `0x8042EA04` and `0x80035698` respectively. This is
a limitation of inferred function slicing, not original boundary metadata or
a reason to remove `skip_cfa_ranges`. The configured exact build remains the
validation path.

## Comparison record and reproduction limits

The historical comparison procedure is preserved at immutable commit
[`7bb5e50e5e3a36dcee05c71bb802be5f45c12168`](https://github.com/matthewlewisnewton/pso-decomp/blob/7bb5e50e5e3a36dcee05c71bb802be5f45c12168/docs/evidence/launch-dol-stranded-epilogue.md).
The current checkout has no experimental C++ loader branch or unit override
to select. Its acceptance build uses the unchanged exact provider. Historical
probe instructions do not authorize restoring that implementation or flags;
future source experiments require a distinct evidenced transfer facility or
authentic original-toolchain evidence as described in the
[narrowed recovery follow-up](launch-dol-cpp-recovery.md).

For the second-copy comparison, extract only `sys/main.dol` from the local
disc into an ignored directory with `dtk vfs cp`; the container path syntax
is `<disc-image>:sys/main.dol`. Read each DOL's seven text ranges from its
header and compare the two addresses in the table. Ignore only relative-call
displacements at loader offsets `0x30`, `0x40`, `0x50`, `0x60`, `0x6C`,
`0xA4`, `0xB0`, `0xBC`, `0x108` and `0x114`; check that each is still a
relative branch-and-link. Retain the final jump and restore in the comparison.

## Consequences for recovery

The evidence supports investigating the restore in the preceding loader's
owning-frame context, rather than searching for an unrelated standalone C
function. The historical frame comparison did not solve the preceding
transfer. Narrowed #284 is a header-view change, not a completed loader
implementation; subsequent transfer work remains a separate held follow-up.

A future ownership correction needs an explicit coverage-accounting plan.
Simply widening the existing symbol would remove the currently reported
function address at `0x8042E9FC` and fail the repository's address/no-loss gate;
it would not solve the historical probe's three differing transfer words. No symbols,
splits, linkage selection, assembly exceptions or coverage rules were changed
for this investigation, and no new matching bytes are claimed.
