# LaunchDol's stranded epilogue

This records bounded ownership evidence for `0x8042E9FC..0x8042EA0F`.
The range remains unmatched, with its address and ownership hold preserved.
Narrowed #284 at `d70369041672d5c881d895dc0a27b96f612e4b0c` contains the
DOL header view and caller conversion; it removes the experimental C++
loader and its per-unit compiler override. This document does not restore
either one. The active LaunchDol provider and compiler settings remain those
of main.

## Separate source linkage for the modem initializer

The existing `init_modem_check_params` function at `0x8042EA10` starts after
the preceding frame restore. It has its own entry, prologue and return,
and its 196-byte C++ implementation was already exact. Previously the build
selected the original object for both functions because their combined
216-byte unit included the unmatched restore.

The split now keeps `text_8042E9FC.cpp` as an original-only 20-byte range
and moves the unchanged initializer body to `text_8042EA10.cpp`, selected
from source. This is a provisional extraction at an existing function
boundary, not a claim to have recovered an original translation unit.
Neither function's symbol, address or size changes. The LaunchDol provider,
its 312-byte extent and `skip_cfa_ranges` remain unchanged. No source body
or assembly is supplied for the restore.

The fresh initializer object has one allocated section, `.text`, of 196
bytes with alignment four. Its complete text, function extent, global
definitions and all 18 text relocations match the fresh original split.
They also agree with the previous original object after subtracting the
20-byte leading offset. The original-only split retains those first 20
bytes unchanged. Compiler metadata sections are not claimed byte-identical.
The initializer inherits the existing ntUtl compiler profile without an
override, pragma, new interface or source-body change.

This activation adds 196 source-linked code bytes and one linked unit;
it adds no newly matched function or code byte. Both original function
addresses and full extents remain in strict coverage. Across the same
216-byte span, 196 bytes are matched and source-linked, and 20 remain
unmatched and original-provided. This is partial progress, not completion
of the epilogue or transfer recovery.

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

## Synthetic DTK control

[The standalone generator](../../tools/repro_dtk_bclr_restore.py) reproduces
an orphaned restore using only constructed PowerPC instructions and DOL
metadata. It requires no game input, compiler, emulator or target execution:

```sh
python3 tools/repro_dtk_bclr_restore.py --dtk /path/to/dtk-1.8.4
```

Use a fresh output directory, or select one with `--out-dir`. The default is
ignored `build/dtk-bclr-repro`; it contains the two synthetic images, analyzer
logs and `result.json`. The script checks the DTK version/revision and records
its executable hash. No generated binary is committed.

Both fixtures have the same saved frame, an LR handoff, a 20-byte restore and
a trailing leaf function. Their sole difference is the branch link bit at
file offset `0x51F`, XOR one. With DTK 1.8.4 at the revision above:

| Handoff | `dol info` result | Following restore |
|---|---|---|
| Nonlinking `blr` | Exit 1, unpaired epilogue at `0x81001028` | Analyzed separately at `0x81001020..0x81001034` |
| Linking `blrl` | Exit 0 | Reached through the modeled call fallthrough |

Both emit the same warning about missing SDA bases, which the fixture does
not need. The single-bit control isolates branch treatment from frame bytes,
section layout and metadata.

The pinned [VM implementation](https://github.com/encounter/decomp-toolkit/blob/a0c455e46cab58e1d2e0885623f85089ff0499db/src/analysis/vm.rs#L402-L457)
classifies a branch through LR as a return target. An unconditional nonlinking
case becomes a jump to that target, whereas a linking case also models a
return-site path. The [slice analyzer](https://github.com/encounter/decomp-toolkit/blob/a0c455e46cab58e1d2e0885623f85089ff0499db/src/analysis/slices.rs#L360-L362)
ends the return block immediately after the branch. Its later
[frame-pairing check](https://github.com/encounter/decomp-toolkit/blob/a0c455e46cab58e1d2e0885623f85089ff0499db/src/analysis/slices.rs#L588-L595)
rejects the separately encountered restore without a prologue.

This establishes a mechanism for the tool diagnostic, not PSO's original
function extent, translation unit or compiler provenance. The linking control
changes runtime semantics and is not a candidate handoff replacement. No game
symbol, split, provider, address, coverage rule or `skip_cfa_ranges` entry is
changed on the strength of this reproduction.

## Stock-compiler phase comparison

A bounded comparison of the historical 332-byte C++ call control and a
320-byte named-operand inline-assembly handoff localizes their first prefix
divergence to frontend optimization. Both use the same frozen GC/2.6 compiler
and historical flags; no compiler state, register assignment, liveness or
production build input was changed. The compiler executable's SHA-256 is
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`.

For each input, ordinary Wibo compilation, untraced retrowin32 compilation and
passive debugger observation produced byte-identical complete objects. Their
allocated sections, function sizes, globals and text relocations also agree
with the saved candidate. The call-control debugger reported a closed remote
connection after its final continuation; the compiler nevertheless exited
successfully and emitted the complete object, authenticated separately. The
assembly-candidate observer handled that EOF and completed normally. These
checks authenticate the observed outputs, not the original game's source.

- Initial frontend ASTs agree throughout the prefix; only the expected call
  versus assembly tail differs.
- After frontend optimization, the array-address expression associations and
  second-loop lifetime splits differ. Initial backend code already uses
  offset addition plus indexed loads for the call control, versus
  base-plus-index addresses and displacement loads for the assembly candidate.
- Backend common-subexpression elimination shares that base. The two loops
  lose one and two instructions respectively, accounting for the 12-byte
  prefix shortening before register allocation or scheduling.
- Register dependencies then differ, while both candidates retain the same
  0x20-byte frame and r26–r31 save/restore. Changing the frame or assigning a
  different register would not address the first divergence.

One distinct source-based test moved the target-specific assembly statement
into an ordinary C++ inline helper, rather than the previously tested
function-level assembly helper. With unchanged flags, Wibo and retrowin32
produced identical complete objects, and its full 320-byte text was identical
to the direct named-operand assembly candidate. This encapsulation did not
improve the emitted result and is not a replacement implementation. No helper
phase trace was collected, so identical internal decisions are not claimed.

This initial comparison alone did not identify the assembly effect causing
the gate. The follow-up below isolates that stock-compiler decision; neither
comparison recovers an original interface or authorizes expression/register
steering. No experimental source, private compiler dump or binary is added
here. The exact original provider, symbol extents and strict accounting remain
in force.

### Isolating the frontend assembly gate

A second passive observation of the same two frozen inputs follows the stock
executable's assembly-effect checks and optimizer gates. The executable,
sources and flags are unchanged. Both observations ran to compiler exit zero;
for each input, the complete stock, untraced-emulator and debugger-observed
objects are byte-identical and agree with the saved candidate's allocated
output. A transient occupied debugger port stopped the initial combined job
before its second observation; that input completed in a separate gated job.

Both inputs have optimization level four and the assembly-aware optimization
option already enabled. In the named-operand candidate:

| Observed statement | Effect barrier byte | Unmodeled-flow byte | Disable gate after statement |
|---|---:|---:|---:|
| `mtlr entry` | 0 | 0 | 0 |
| Nonlinking `blr` | 0 | 1 | 1 |

The stock executable tests the option at `0x46D51C`, obtains the effect header,
and tests bytes zero and three at `0x46D531` and `0x46D537`. The `blr` takes
the effect-triggered store at `0x46D53E`, setting byte `0x5EB394` to one.
The option-disabled path at `0x46D547` is not taken. This distinguishes a
specific branch effect from a blanket prohibition of assembly optimization.

At the main optimizer gate (`0x42E041`), that byte remains one for the
assembly candidate and zero for the call control. The control enters the
main optimization region, reaches lifetime splitting (`0x42E39A`) and enters
expression regeneration (`0x42E3E1`); the assembly candidate skips all three.
Its prefix AST already differs immediately after the IRO optimizer returns,
before the later simple cleanup. The public reconstruction's
`DisableDueToAsm` description is therefore consistent with an observed stock
decision, rather than being the sole basis for the diagnosis.

The nonlinking indirect transfer is an actual control-flow boundary. Clearing
the gate, supplying false label/call effects or replacing it with a linking
transfer would not establish an equivalent source solution. No such change
was tested or adopted. These observations explain this candidate's optimizer
path; even the call control's exact prefix does not authenticate the original
game's source, flags or pass sequence. A source recovery still needs a
semantically justified representation and the unchanged ownership/accounting
checks.

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
it would not solve the historical probe's three differing transfer words. The
initializer extraction above preserves both symbol starts and extents while
changing only the split boundary and source selection for its existing body.
It does not correct ownership of the restore or change assembly exceptions
or coverage rules. No new matching bytes are claimed.
