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

### Isolating reassociation and lifetime splitting

A further passive trace reads the control's IRO expression graph in 53
snapshots at existing phase boundaries. It does not enable the internal dump
option or invoke compiler routines from the debugger. A second observation
brackets the relevant original calls directly. Both complete objects remain
byte-identical to the saved 332-byte control and ordinary stock/emulator
outputs; sources, options and compiler state are unchanged.

The first selected address changes occur at the existing
`MoveInvarianceInAddressExpr` checkpoints. The direct observation isolates
them across `0x4A5CEF` (call to `0x4A4E20`) and its return at `0x4A5CF4`:

| Invocation | Before | After |
|---|---|---|
| First loop | `(image + field) + (i << 2)` for `0x48`, `0x90` | `(image + (i << 2)) + field` |
| Second loop | Same form for `0x64`, `0xAC` | Same constants-last form |

The same routine is also called at `0x4A630F`, returning at `0x4A6314`; those
calls do not further change the selected shapes. Observer labels such as
"vector" and "motion" are aliases, not authenticated stock function names.
The conclusion rests on the call boundaries and actual expression changes.

At every bracket, loop-invariant optimization is one, strength reduction zero
and frontend common-subexpression optimization zero. Thus the observed
reassociation runs with the latter two options already disabled. This agrees
with the public reconstruction's [loop-address rewriter](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/IroLoop.c#L2391),
which places constant addends last. That reference supports interpretation;
the stock observations establish the change in this input.

A separate bracket, from entry at `0x45DC70` to return at `0x42E39F`, isolates
the second loop's index changing from shared temporary `@26` to `@42`. Its
address-expression association stays unchanged across that call. These are
distinct frontend transformations, preceding register allocation and frame
construction. The reader bounds list/tree traversal, handles operand nodes
as original ENode leaves, and compares expression shapes rather than mutable
node indices. Its first broad trace selected only shifts; the focused trace
also captures the initial multiplication by four, avoiding an inference from
an empty selection before shift lowering.

This identifies where this control acquires the prefix structure missing
from the assembly candidate. It does not justify manually reproducing the
optimizer's arithmetic, adding liveness or changing its flags. A genuine
source solution must retain the nonlinking transfer's behavior and pass the
same ownership and address-accounting checks.

### Bounded code-reference ownership check

A separate read-only scan of the authenticated original game examines its
two populated text sections: 1,088,320 aligned words, including 215,460 raw
direct-branch encodings. No decoded direct `b`/`bc` target enters
`[0x8042E9FC, 0x8042EA10)`. Among 4,633 exactly adjacent `lis` plus `addi` or
`ori` address constructions, none constructs an address in that range.
No exactly adjacent linking branch-to-next, `mflr`, `addi` construction was
found.
Original-free positive and negative decoder controls include signed and
absolute branches, both address-construction forms and `addi`'s special r0
base behavior.

This scans raw section words, not a recovered control-flow graph, and is
separate from the earlier initialized-data pointer scan. It does not exclude
nonadjacent constructions, general arithmetic, relative/SDA tables, runtime
writes or other indirect transfers. It supplies no original source boundary
or ownership proof. The follow-up below extends this check to bounded local
constant tracking, retaining unknown values at calls and control boundaries.

### Conservative LR/CTR constant tracking

[The standalone audit](../../tools/audit_loader_indirect_targets.py) reads the
authenticated original DOL and a native report used only for declared block
boundaries. It requires the existing 312-, 20- and 196-byte function extents;
those declarations are reset points, not authenticated ownership evidence.
Run from the repository root with a fresh output directory:

```sh
python3 -m unittest tools.tests.test_loader_indirect_targets
python3 tools/audit_loader_indirect_targets.py --report build/GPOE8P/report.json
```

The default output is ignored `build/loader-indirect-targets`. `result.json`
records input/tool hashes, counts and scope; `events.json` records metadata
for SPR assignments and indirect-branch encodings. No binary is generated.

All register facts start unknown at declared function starts/ends, direct
branch targets and control-flow fallthrough boundaries. Every call/control
boundary clears all facts; no predecessor facts are joined and no return
address is assumed. Only a small explicit 32-bit instruction whitelist
propagates constants. Memory loads produce unknowns, updating forms invalidate
their base, and unsupported instructions clear every fact. Provenance beyond
32 contributing instructions becomes unknown. Newly resolved text targets
become reset points and require recomputation, discarding preliminary claims.
No newly discovered reset point was needed in this run.

The decoder follows the [PowerPC instruction reference](https://www.nxp.com/docs/en/user-guide/MPCFPE_AD_R1.pdf)
for LR/CTR targets, split SPR fields and register effects. It reads the
pre-instruction target, masks its low two bits, rejects unsupported reserved
branch fields and rejects CTR-decrement branch-to-CTR forms. Twenty-three
original-free tests cover known nonadjacent constructions, register aliases,
r0 semantics, signed arithmetic, loads/updates, unsupported barriers,
control boundaries, leader refinement, linking branches and provenance limits.
Independent review found and corrected the reserved-field check before the
final evidence run; that run and its complete metadata were independently
recomputed without changing the game or compiler.

The same 1,088,320 text words produce 29,949 LR-branch and 5,498 CTR-branch
encodings. One local constant target resolves: the linking transfer at
`0x8000C0CC` to `InitMetroTRK` at `0x80395930`. This is a syntactic target,
not proof of execution. The other **35,446 indirect transfers remain
unresolved**. The 1,012 known SPR assignments include CTR loop counts; they
must not all be interpreted as function addresses. No resolved assignment
value or indirect-branch target enters the 20-byte restore range.

| Held transfer | Last local LR assignment | Source of its unknown value |
|---|---|---|
| Loader jump at `0x8042E9F8` | `0x8042E9F4` | r0 loaded at `0x8042E9EC`, from memory offset `0xE0` through r26 |
| Restore return at `0x8042EA0C` | `0x8042EA04` | r0 loaded at `0x8042EA00`, from stack offset `0x24` |

Last-writer locations are metadata, never invented values. The remaining
unknowns include memory/table values, unsupported operations and unmodeled
indirect entries into the middle of a syntactic region. Raw words may be
unreachable or noncode. This is not a complete CFG or an indirect-entry
exclusion proof. The restore remains consistent with the preceding saved
frame, but this analysis does not authenticate ownership or a new source
handoff and authorizes no symbol, provider or accounting change.

## Payload provenance and intervening writes

The next investigation follows the memory word loaded at `0x8042E9EC`,
without substituting a guessed value into the indirect-target analysis.
The pinned original DOL contains these four direct branch-and-link encodings:

| Call site | Target |
|---|---|
| `0x8007F8BC` | `launch_switcher_dol` at `0x8007F970` |
| `0x8007FA08` | `fn_8042EBA4` at `0x8042EBA4` |
| `0x8007FA7C` | `launch_switcher_dol` at `0x8007F970` |
| `0x8042EBF8` | `LaunchDol` at `0x8042E8C4` |

Scanning the original text encodings finds no other direct branches to these
three entry addresses; aligned initialized-data words contain none of them.
This does not exclude indirect callers, computed addresses, interior entries
or unreachable encodings. The report marks the two forwarding functions,
the read wrapper, `TGStream::read_whole_file`, `read_sectors_sync` and
`find_gsl_entry` as exact and source-linked. Source names and report boundaries
alone do not establish an original interface or complete call graph.

The exact [caller](../../src/pso/unk/text_8007F8D0.cpp) queries the size of
`lbl_80438D20`, reads it into `resource_decompress_buffer`, then forwards that
buffer and the queried size. Reading the original literal authenticates this
filename as **`switcher.dol`**. Its argument string is a separate launch
argument. The [forwarding helper](../../src/pso/unk/text_8042EAD4.cpp) writes
the buffer into context field `0x104`, the queried size into `0x100`, and
`0x8000` into `payload_size`. Its copied path literal at `lbl_80480404` is
**`iwanaga.dol`**, not the filename just read. Neither forwarding function
checks a DOL header or the read result. The `SEGA` check elsewhere in the
context setup concerns launch-record data, not validation of the image's
entry word. No production declaration or behavior is changed by this audit.

The authorized disc's `files/switcher.dol` was extracted privately without
decompression. The same disc's `files/PsoV3.dol` equals the pinned game DOL.
Only bounded metadata is recorded here:

| Retail payload property | Observed value |
|---|---|
| File length | 204,480 bytes (`0x31EC0`) |
| SHA-1 | `4b386d2c190b42b5bc3a0c42ec4d3bff08f6d048` |
| SHA-256 | `b8febb6f6f0bf6fdb181d4b4c0506510cc0ce74ff83faaff39dded8d42b0156f` |
| Header entry word | `0x806C5040`, inside its own first text range |
| Active text sections | 2; first destination `0x806C5000` |
| Active data sections | 6 |
| BSS | `[0x806F6920, 0x806FDAA4)` |

All eight populated file extents are in bounds. Their destination ranges
and the BSS range avoid the held restore `[0x8042E9FC, 0x8042EA10)`.
The loader stops each section loop at its first zero file offset; this
payload has no populated slot after that terminator. BSS overlaps some
initialized-data ranges, so the clear-before-copy ordering still matters.
The helper's fixed `0x8000` field produces a launch-record copy of `0x8120`
bytes to `[0x80003100, 0x8000B220)`; it is not the DOL file length.
These are expected writes from an intact header, not a runtime alias proof:
the entry is read after the record copy, reset call, BSS clear and section
moves, and the runtime source-buffer address remains unknown.

Several concrete predicates prevent treating the retail entry as a constant:

- [The resource path](../../src/pso/system/TGStream.cpp) consults the active
  GSL table by name before the disc-file fallback. A matching archive entry
  can select a different source and metadata size. This establishes a possible
  path, not that a retail archive actually shadows `switcher.dol`.
- `read_whole_file` rejects a nonpositive size but performs no DOL header,
  entry, section or destination check. The caller ignores its return value.
  Its sector waits run `TLobby::run_frame`, which runs tasks and renders nodes.
- [Startup](../../src/pso/misc/TKeyBoardControl_8000F764.cpp) allocates the
  shared `0x80000` buffer and passes the same pointer to
  `TObjPlayer__sub_803E492C`. That
  [setter](../../src/pso/unk/text_803E2D70.cpp) installs it as
  `chunk_vertex_cache_buffer`. Depending on flags and model/cache state,
  `draw_chunk_vertices_cached` can copy or generate vertices into that alias.
  This is an intervening-write candidate, not evidence that this particular
  launch executes a clobber or reaches the restore.
- For this file, the read performs 99 full sectors followed by a 1,728-byte
  remainder. The remainder-sector wait can run callbacks after the initial
  header-bearing read; the final remainder copy does not refresh that header.
  The caller blacks the display and waits for `GXDrawDone` after the read.

The new read-only [payload audit](../../tools/audit_loader_payload_provenance.py)
pins both input hashes, reproduces the file-header and direct-reference
metadata, and emits no original bytes. Its range checks are analyst checks;
they are not checks performed by the game. Seven original-free controls cover
an entry in text, a watched-range entry, section-loop termination at a hole,
range endpoints, malformed extents/wraps, address alignment, output preservation
and direct versus indirect branches. Existing outputs and symlinks are rejected.
The payload metadata and original call references were independently
recomputed. Reproduce locally with private inputs and an ignored output:

```sh
python3 -m unittest tools.tests.test_loader_payload_provenance
python3 tools/audit_loader_payload_provenance.py --dol PRIVATE/PsoV3.dol --payload PRIVATE/switcher.dol --output build/payload-provenance.json
```

The retail entry discriminates the straightforward intact-disc path: it
targets the payload's own text, not the held restore. It neither authenticates
the restore's ownership nor resolves all runtime handoffs. A useful next
experiment must establish the selected GSL/disc source and the buffer/cache
state across the two read waits, or observe an authorized runtime trace of
those predicates. A retail file hash alone cannot discharge them. No memory
fact is seeded into the tracker and all unresolved indirect entries remain
unknown.

## Controlled read-boundary execution

The next discriminator tests the read/callback predicates against original
machine code, with synthetic data and explicit external-call models. The
[read-boundary probe](../../tools/probe_loader_read_boundaries.py) uses
Unicorn 2.1.4 in 32-bit big-endian PPC mode. Both the original DOL hash and
the checked symbol-inventory hash are pinned. It executes only an explicit
allowlist of 17 original function ranges and stops at the entry to
`fn_8042EBA4`; it never executes LaunchDol, seeds its indirect target or
executes the held restore. An unknown code boundary or instruction bound
fails the probe. Original input bytes remain private and unchanged.

The executed ranges include the caller, size/read/open/lookup functions,
pending-read setters/resetters, the cache-buffer setter and
`draw_chunk_vertices_cached`. The latter two functions are individually
exact in their current report but their combined unit remains original-
provided; this investigation does not activate it. Device operations,
standard memory/string helpers, display calls and the launch-argument helper
are modeled boundaries. The full frame callback is replaced by a chosen
invocation of the original cache-drawing function. No live task tree, device,
allocator state or selected resource is reconstructed.
Boundary returns clobber volatile GPRs while retaining CR/CTR/FPR state;
this is a limited call model, not full ABI emulation. SDA bases come from the
checked native linked ELF. Controls verify that the original size getter
and cache setter access their intended fixture globals at those bases.

The original sector-read object confirms this order: start the read; publish
the pending handle/count/destination; poll for status **equal to 3**; call
`TLobby::run_frame` for every other status; reset pending state after 3.
The read-start return value is not inspected. The reconstructed source's
one-argument declaration of `read_checked_align` omits its count/destination
parameters; the original call retains both in r4/r5. The probe captures those
actual PPC registers and introduces no production interface correction or
assumption about a host compiler's calling convention.

The caller captures the resource-buffer pointer in r30 and the initial size
in r31 before `read_disc_file`; it forwards those saved values afterwards.
The stream separately captures its selected handle in its local prefix.
The pending-read fields and cache pointer/flags remain global. Consequently,
rebinding the resource-buffer global alone would not redirect the pointer
already captured by this caller; preservation of the pointed-to header and
the selected handle's lifetime still require evidence. The source's
`TLobby::flush_pending` can resubmit the recorded read when its retry flag
is set, and then checks other registered reads. Those retry paths are not
emulated by the controlled frame callback and remain additional state to
establish for a real execution.

Nine controls use synthetic 4,864-byte disc and 6,912-byte GSL images with
distinct synthetic entry words. They produce these bounded results:

| Chosen boundary conditions | Observed original-code behavior |
|---|---|
| Successful disc read, no frame callback | Forwards disc fixture's buffer and queried size |
| Active matching GSL entry | Uses archive fixture and its size; no disc open |
| Active GSL table without the name | Uses disc fallback |
| Initial size query succeeds, read's later size query fails to open | Issues no sector read; still forwards the original queried size and stale buffer |
| One callback during the remainder wait, cache replay aliases payload | Original cache function copies the synthetic replacement header; remainder copy leaves that word changed |
| Same callback, `chunk_render_flags & 4` | Cache write is skipped; disc fixture's header remains |
| Same callback, zero cached byte count | No cache copy; disc fixture's header remains |
| Same callback, cache buffer points elsewhere | Alternate buffer changes; payload fixture's header remains |
| Read-start returns failure and status stays noncomplete | Eight modeled frame calls, then a harness stop on the ninth status poll; no forwarding |

The bounded-wait result is a harness stop, not a timeout or error branch in
the game. The modeled status sequence is not asserted to occur on hardware.
For the callback cases, the first full-sector transfer completes before the
remainder wait and the callback occurs before its completion; these are
chosen scheduling conditions. The actual frame machinery's ability to reach
that cache operation during this launch remains unproved. The guard, empty
cache and separate-buffer controls demonstrate why that state matters.
The failure control also distinguishes the queried record size from a
successful payload read; forwarding that size does not authenticate a header.

All nine controls pass. The ordinary 30 original-free analysis tests remain
separate: these nine cases additionally require the authorized private DOL
and pinned emulator dependency. Reproduce in an ignored environment with
`unicorn==2.1.4` installed:

```sh
python3 tools/probe_loader_read_boundaries.py --dol PRIVATE/PsoV3.dol --output build/read-boundaries.json
```

This provides reproducible counterexamples to assuming that file metadata,
the read call or a frame wait alone preserves the header. It does not prove
any chosen external outcome, an actual clobber, arbitrary indirect entry or
restore ownership. The remaining discriminator is the **actual callback/task
tree, cache pointer/flags/count and I/O outcomes at this launch**. An
authenticated call-site state or authorized runtime observation could settle
those predicates; the current controlled runs cannot. All original providers,
function extents and strict accounting holds remain in place.

## Launch attachments and the read-wait scene roots

The next bounded trace distinguishes the main task tree from the restricted
traversal in `TLobby::run_frame`. The exact
[main-task initializer](../../src/pso/object/TObject.cpp) creates the layer
roots with `new TObject(this)`: they are siblings under the main task, not
ancestors implied by the macro grouping names. The exact
[read-wait frame](../../src/pso/misc/TLobby_800F9DA0.cpp) selects:

| Traversal | Directly selected roots |
|---|---|
| Task updates | `tl_su`, `tl_camera`, `tl_07`, `tl_particle` |
| Rendering | `tl_su`, `tl_07`, `tl_particle` |
| Conditional updates/rendering | `tl_fade`, when its controller pointer is nonzero and its ancestry is not queued for destruction |

It does not directly traverse `tl_00`, `tl_01`, `tl_03`, `tl_04`,
`tl_particlemodel` or `tl_clipout`. This narrows the previous callback model;
it does not establish the contents of any selected root at a retail launch.
Platform/deferred-work calls around these traversals can also affect state.

Known launch attachments are consistent with this separation:

- The [mode-selection launch task](../../src/pso/misc/TWindowShortListCtrl_801A4FC0.cpp),
  `TUnk_804C2298`, attaches to `tl_00`. Its
  [state-8 task path](../../src/pso/unk/text_801A4D30.cpp) calls the selection
  helper before advancing state and requesting the scene change. Its original
  vtable at `0x804C2298` points to that task and an empty render method.
- The [mode-scene factory](../../src/pso/ui/TAdMultiChgGameModeGC_8023EAC4.cpp)
  passes `tl_01` to the trial-check constructor in case 22. The
  [logo path](../../src/pso/misc/TLogo.cpp) passes its logo object as parent;
  the inspected logo construction sites pass `tl_01` to that logo constructor.
  Original constructor code forwards incoming r4 through the trial/warning
  chain, and through the logo constructor, to the original TObject constructor.
  Several reconstructed declarations omit that parameter, so these are
  object/register-flow observations, not authentication of a new C++ interface.

Thus these known construction paths do not place the launch task directly
under a selected read-wait root. This helps exclude straightforward recursive
redispatch of that same task through those attachments. It does not exclude
other callers, reparenting, other children or arbitrary indirect entries.

There is nevertheless a concrete compatible cache-writer path in the
selected layers: [TEffect's constructor](../../src/pso/effect/TEffect.cpp)
attaches to `tl_particle`; `TEffClitical` derives through that constructor.
Its original vtable at `0x8048E2E8` selects the exact
[`TEffClitical::render`](../../src/pso/effect/TEffClitical.cpp) at `0x80082308`,
which calls `draw_chunk_object`. The
[chunk traversal](../../src/pso/unk/text_803E2D70.cpp) supplies
`draw_chunk_vertices_cached` as its model callback. This is a source/object
path admitted by the selected root, conditional on a live effect node,
render flags, resources and traversal conditions. No such node is observed
at the modem launch. Cleanup routines exist, including deletion of layer
children; their existence alone does not prove they dominate every launch or
that callbacks cannot populate a selected layer afterwards.
In particular, `delete_layer_children` clears `tl_07` and `tl_particle` but
does not clear the selected persistent `tl_su` root. That one cleanup call
therefore cannot by itself establish an empty set of read-wait tasks.

The original traversal also exposes a useful flag distinction.
`TObject::render_nodes` checks each **child's** `DISALLOW_RENDER` bit before
dispatching that child and descending. It does not check the receiver root's
own bit. Likewise `run_tasks` checks child update flags rather than the
directly selected root's flags. Consequently, a root disabled in a normal
main-tree pass is not by that fact excluded when `run_frame` calls its
traversal directly. A child render-disable flag does prune its descendants.
The separately checked fade-controller ancestry remains a real gate.

The [scene-root probe](../../tools/probe_loader_scene_roots.py) executes the
original frame, TObject constructors, traversals, empty virtual methods and
fade gate over a deliberately synthetic TObject-only tree. Six independently
checkable cases cover ordinary selection, root suspend/render flags, child
render blocking, child update suspension, a present fade controller and a
queued controller ancestor. The roots and children are attached by the
original constructor, and virtual calls use its original TObject vtable.
The controls assert the complete ordered update/render receiver lists.
In particular, root flags `0x14` leave direct child dispatch unchanged,
whereas child `0x10` removes rendering of that child and its grandchild.
Inherited setup runs the prior size-getter/cache-setter binding controls;
the scene phase then replaces the allowlist with its ten scene ranges and
eight explicit platform boundaries. It performs no effect rendering or cache
write during that phase. Its platform calls
are explicit zero-return models, with the prior probe's stated ABI limits;
they do not reconstruct a retail task tree or hardware behavior.

With the same pinned private DOL and emulator dependency, reproduce with:

```sh
python3 tools/probe_loader_scene_roots.py --dol PRIVATE/PsoV3.dol --output build/scene-roots.json
```

The narrowed conclusion is that the known launcher attachments are outside
the direct wait-frame traversal, while `tl_particle` admits a genuine
cache-writing class path and root flags alone do not exclude it. Missing
evidence is the selected layers' live children, child flags and resource/cache
state at each launch, including effects of surrounding callbacks and cleanup.
A useful next source trace is to test cleanup dominance, persistent `tl_su`
tasks and constructors that can repopulate selected roots between scene entry
and the read.
The runtime header word and all restore-ownership holds remain unresolved.

## Cleanup scope, phase dispatch and repopulation

The cleanup trace adds an entry route beyond the preceding object-attachment
analysis. The pinned original `main_phase_table` at `0x804805E0` contains
22 records of three function pointers, ordered init/update/exit. **Phase 19
directly selects `check_modem_result` as its update callback.** Its entry is
the audio-stop wrapper at `0x803354E8`, its update is `0x803354A8`, and its
exit at `0x803354A4` is an empty return. A trial-check object need not be
redispatched through the task tree for this route to reach the modem helper.
That observation does not establish which phase actually precedes a launch.

The exact [main dispatcher](../../src/pso/player/TObjPlayer_80011014.cpp)
calls the current init, caches its update pointer, loops while the result
field is zero, then calls an exit before applying the normal next-phase
assignment. It reloads the current-phase field for lookups: calling this the
"old phase exit" assumes callbacks leave that field unchanged until the
normal transition. Menu phases 2, 4, 6, 7, 9, 10, 11 and 13 share
`fn_8023F3F8` as update and `TLobby::release_scene_resources` as exit.
The original table selects offline teardown for phase 14 and online lobby
cleanup for phase 15. Source names alone were not used to identify these
original pointer values.

There are several different cleanup scopes; they cannot be conflated:

| Operation | Explicit tree/state effect in the inspected body |
|---|---|
| `TMainTask::delete_layer_children` | Deletes children of the listed layers, including camera, `tl_07` and `tl_particle`; does not delete `tl_su` children |
| [Menu release](../../src/pso/unk/text_8023F1B8.cpp) | Calls that layer cleanup, reverse resource callbacks, particle-heap cleanup and resource-task cleanup; no direct `tl_su` deletion |
| [Offline teardown](../../src/pso/unk/text_801A3014.cpp) | Additionally deletes `tl_su` children, followed by area/resource callbacks |
| [Online lobby cleanup](../../src/pso/misc/TLobby_801A3C48.cpp) | Additionally deletes `tl_su` children, followed by other cleanup/callback work |
| [`clear_resource_load_tasks`](../../src/pso/unk/text_800F9B84.cpp) | Deletes children of the separate resource-load root at `0x8050113C` |
| [`TLoadCtrl::cleanup_scene`](../../src/pso/misc/TLoadCtrl.cpp) | Queues the current controller for destruction and clears its global instance, then performs mode/camera cleanup |

"Persistent `tl_su`" therefore means surviving the **layer-only** cleanup,
not surviving every teardown. Conversely, absence of a direct deletion in
menu release does not prove that all its callback bodies preserve that root.
Neither resource-task cleanup nor deletion of some named layer proves that
every read-wait task has gone away.

Ordering also limits cleanup-dominance claims. The known
[`TUnk_804C2298` state-8 path](../../src/pso/unk/text_801A4D30.cpp) calls the
launch-selection helper before setting state 9 and requesting the scene
change. The same outer dispatcher's later phase exit cannot itself precede
that nested launch. Another independently invoked cleanup remains possible.
Within a menu phase, [the mode-frame update](../../src/pso/unk/text_8023F3F8.cpp)
queues the old mode object and later invokes the mode factory; it does not
call the full phase-release routine for each mode replacement.

Selected roots can be repopulated after a cleanup. Both the inspected logo
entry and [menu-scene entry](../../src/pso/unk/text_8023F1B8.cpp) create a
camera and invoke
[`TParticleCtrl::create_quad_sprites`](../../src/pso/misc/TParticleCtrl_801E5330.cpp)
before later UI launch paths. The original definition table has 108 records
of size `0x28`; the selector at `+0x24` is type 3 in 70 records and type 4 in
38. The factory attempts allocations and constructs `TQuadSpriteSclCol` or
`TQuadSpriteSclColRot` under `tl_particle`. Allocation success and continued
liveness are separate predicates. These are quad-sprite classes, not
`TEffClitical`; their presence does not establish the earlier cache-writing
effect path or a payload clobber.

There is also a conditional persistent-task route to new selected-layer
children. `TLoadCtrl::start_loading` attaches a controller to `tl_su`.
With the **global instance nonzero**, when that receiver's tick reaches two,
mode 0 can construct `TNowLoading`. Its
[loading indicators](../../src/pso/misc/TNowLoading.cpp), including
[`TLoadingCur`](../../src/pso/misc/TLoadingCur.cpp), call
[`fn_80086FE0`](../../src/pso/unk/text_80086FE0.cpp); the corresponding
[`initialize_with_direction`](../../src/pso/boss/TBoss4Type2_800874F4.cpp)
constructs particle objects under `tl_07`. This depends on controller flags,
mode/tick, particle bounds and successful allocations. The global guard is
nonzero, not equality between receiver and instance. Clearing it suppresses
that task body's work; queuing the controller is a distinct traversal gate.
A no-op parent task alone would not exclude descendants, since `run_tasks`
can recurse into them. No active loading controller is observed at launch.

The [phase-dispatch probe](../../tools/probe_loader_phase_cleanup.py) pins the
original table and executes the original main dispatcher and phase-19
callbacks over explicit synthetic phase/root state. Five cases cover direct
phase-19 entry, chosen menu/offline/online predecessors, and a result flag
that suppresses the update. Predecessor callback bodies are intercepted:
the controls verify **table-selected callback order**, not cleanup effects.
For the modeled predecessors, exit selection precedes phase-19 entry.
With null fixture root globals, the original phase-19 update still reaches
the modem-selection helper, where the probe stops. The negative control
skips that update, executes the empty exit and reaches a modeled shutdown.
No modem helper body, file read, loader or restore executes. Inherited setup
and ABI limitations remain those of the earlier probes.

```sh
python3 tools/probe_loader_phase_cleanup.py --dol PRIVATE/PsoV3.dol --output build/phase-cleanup.json
```

These results replace a blanket clean-scene assumption with route-specific
conditions. What remains missing is the actual predecessor/phase-request path,
the effects of its release callbacks, and loading/quest/network task state
after cleanup and any restart. A useful next bounded trace is the callers
that request phase 19 and the resource callbacks on their exact predecessor
paths, especially whether they discharge or recreate active `tl_su` work.
Possible repopulation is not an observed retail callback, runtime header
value or restore-ownership proof. Providers and address accounting remain
unchanged.

## Phase-19 request survival and release callbacks

The next trace follows request sites, rather than assuming that writing 19
guarantees the next phase. In the inspected source, the PPP-entry constructor
requests 19 when its account predicate fails; the external-network confirmation
constructor does so under its outer flag predicates and failed account check.
The known mode factory constructs those classes in modes 25 and 21. The
title object's `open_keyboard` action, associated with the mode-0 title class,
also requests 19. These are known construction/request paths, not observations
of which path a retail launch takes or an exhaustive list of indirect calls.

The original setter at `0x8000F9CC` writes only the pending phase at state
`+0x04` and result flag 1 at `+0x10`; it leaves the current phase unchanged.
The [bounded request audit](../../tools/audit_loader_phase_requests.py) finds
43 direct branch encodings to that setter in the pinned original text. Two
have an immediately preceding `li r3,19`, in the PPP and external-network
constructors. The title action's setup is nonadjacent and is not silently
counted by that deliberately narrow pattern. Even an adjacent instruction
does not prove the register value on every possible entry path.

The exact [normal menu update](../../src/pso/unk/text_8023F3F8.cpp) continues
after the factory and task dispatch. When `TAdPlayerLoadGC::get_instance()`
returns zero, a later predicate can invoke `fn_8000F92C`, which replaces the
pending phase from state `+0x0C` and sets result 3. The following quest-readiness
predicate can then call the setter with **0**. An earlier request for 19 can
therefore be superseded in the same update. The getter's
[actual implementation](../../src/pso/ui/TAdPlayerLoadGC_80076BBC.cpp) returns
`card_load_sequence_state`; this is distinct from `TLoadCtrl__instance`.
Names must not be used to equate those two guards.

The [request-survival probe](../../tools/probe_loader_request_survival.py)
executes the original main dispatcher, menu update, title action, request
setter, queued-phase setter and card-state getter. At an explicitly modeled
factory boundary it invokes the original title action with a synthetic
receiver. This chooses request timing; it does not claim that the factory's
real constructor performs that action or authenticate its input conditions.
Main-task work, predecessor init/release bodies, platform calls and account/
quest predicates remain explicit models. Four controls assert request order,
phase/result snapshots, exit count and the eventual boundary:

| Chosen predicates after the request | Controlled outcome |
|---|---|
| Card state zero; neither later override | Phase 19 update reaches the modem-helper boundary |
| Card state zero; quest readiness true | Original setter sequence `[19, 0]`; menu exit then modeled shutdown |
| Card state nonzero | Later override predicates are skipped; request 19 survives |
| Card state zero; queued-phase override true, queued destination explicitly zero | Original queued setter changes result to 3 and next to 0; menu exit then modeled shutdown |

All four controls pass and are independently replayable. They establish
conditional survival/replacement in the selected original instructions, not
real menu input, a particular predecessor, cleanup effects or a runtime header
value. They stop before the modem helper or shutdown body. Earlier read,
scene and phase controls remain separate fixtures rather than a claimed
single retail execution.

The release audit reads the actual callback pairs and records the 30 release
pointers in the order used by menu release: the seven-entry table at
`0x804CCE60` backwards, then the 23-entry table at `0x804CCDA8` backwards.
It follows declared direct targets for at most four edges: 90 entries are
visited, 88 of them have supported declarations, with no direct route to
the loading-controller constructor/destructor/start/cleanup entries at that
depth. This is a syntactic graph with a cutoff, not a complete call graph.
Indirect-transfer encodings include possible returns and unresolved calls;
they are not invented edges. Declarations do not authenticate ownership.

The handled **integer D-form store encodings** using canonical r13 produce
three syntactic writes overlapping `TLoadCtrl__instance`, attributed to its
destructor, `cleanup_scene` and `start_loading`. Floating/paired-single,
indexed, aliased and runtime writes are outside this scan. Absence of such
an encoding in a callback does not prove its memory effects. Six new
original-free controls exercise the pattern limits, partial-store overlap,
conflicting declarations, indirect encodings and graph cutoff.

Independent source inspection likewise finds no explicit loading-controller
clear/restart/instance assignment in the 30 release callback bodies. The
nested title-release table at `0x804EE58C` has four release functions that
are original one-instruction returns. Window cleanup virtually deletes several
global controllers and releases viewport slots. The chat-log cleanup calls
fixed `THeap` methods directly; the resource-file destructor is also fixed.
Their allocation and lifetime contracts still matter. Secondary save-data cleanup
uses an array-destruction helper with fixed callback `0x801FC8B4`, for seven
elements of size `0x2798`, then optionally deletes storage. That immediate
callback target is known; its destructor/allocator effects still need tracing.
The remaining dynamic targets, aliases and state must be established before
claiming that loading work survives, is cleared or is restarted.

```sh
python3 -m unittest tools.tests.test_loader_phase_requests
python3 tools/audit_loader_phase_requests.py --dol PRIVATE/PsoV3.dol --output build/phase-requests.json
python3 tools/probe_loader_request_survival.py --dol PRIVATE/PsoV3.dol --output build/request-survival.json
```

This narrows the predecessor claim to known menu-request paths **whose pending
request survives the rest of the update**. Actual predecessor and loading
state remain unknown. A useful next bounded investigation is the dynamic
targets and lifetime/alias contracts of those specific release operations,
together with code that completes or restarts `TLoadCtrl` during the relevant
resource callbacks. No production interface, provider, function extent,
indirect target or coverage rule changes here.

## Release target and loading-lifetime contracts

Further original-object checks resolve several immediate targets in that
release inventory. In particular, the earlier description of chat-log heap
dispatch as virtual was incorrect: original `fn_8026AC50` has direct
`R_PPC_REL24` references to `heap_free__5THeapFPv` at offsets `0x34` and `0x58`,
and a direct `THeap` destructor call at `0x6C`. The current header and exact
implementation likewise have no virtual heap method.

| Release lane | Resolved immediate operation | Remaining contract |
|---|---|---|
| [Chat log](../../src/pso/unk/text_8026AC50.cpp) | Free nonnull line/last-line blocks through its `THeap`, destroy heap and clear globals | Live heap, valid owned blocks/free-list and underlying allocator effects |
| [Item resource](../../src/pso/item/TItemLoad_8010FDF0.cpp) | Nonvirtual `RelocatedFile` destructor deletes `buffer`; deleting form also deletes the object | Valid object/buffer lifetime and allocator ownership; relocated root is not traversed here |
| Save data | Fixed seven-element character-array destruction followed by optional storage deletion | Valid array storage and allocator effects, rather than callback targets derived from element values |
| [Window roots](../../src/pso/misc/TWindowCtrlMain.cpp) | Virtual deletion, with immediate types constrained by the inspected constructors | Actual live types, aliases, descendants and reentrancy/rebinding history |

The character-array lane can be narrowed further. Original `__destroy_arr`
passes **-1** as each callback's second argument. The fixed chain is seven
character callbacks, each destroying its display configuration; two inner
configuration ranges each destroy two arrays of four leaves. This reaches
**112** `TPlyDispConfig::free_if_valid` callbacks through 29 array-helper
entries. The original leaf only calls delete for a positive second argument;
on this path it returns without reading a stored element value. This excludes
an element-selected callback target on that specific path. Outer buffer
deletion still occurs, so the whole release is not a no-op.

The [release-contract probe](../../tools/probe_loader_release_contracts.py)
executes the original release/heap/array instructions with explicit disjoint
storage fixtures and logical allocator boundaries. Poisoned, unmapped values
inside the character slots do not get dereferenced. Keep-storage, null-array
and positive-leaf-delete controls distinguish the argument gate from a stubbed
no-op. Resource-file controls observe the buffer and object deletion boundaries,
the null guard and repeated cleanup. Populated/empty chat-heap controls execute
the original constructor, allocator and free-list coalescing, checking the
single restored free block before the modeled `xfree`. A second cleanup does
not issue another free. These are chosen valid storage/ownership fixtures;
the allocator hooks do not prove effects of actual game allocations or aliases.

For windows, the inspected `TWindowCtrlMain` constructor creates a detached
generic TObject root. Its misleadingly named `TWindowCtrlMain__instance` and
the six viewport nodes are also allocated as **TObject**, not as loading
controllers. The other globals are constructed as `TWindowCtrlScreen`,
`TWindowCtrlSub` and `TWindowCtrlClipOut`. Under that construction and valid
lifetime contract, their immediate destructor entries are constrained:

| Constructor-established type | Original destructor entry |
|---|---|
| TObject | `0x8022AA70` |
| TWindowCtrlScreen | `0x8024CAD0` |
| TWindowCtrlSub | `0x8024C9B8` |
| TWindowCtrlClipOut | `0x8024C8E8` |

The probe checks the four original vtable slots, not runtime objects.
TObject destruction can still dispatch descendant destructors. Pointer
rebinding, stale aliases, descendants and effects of releasing storage are
not excluded by the immediate-type table. The inspected loading constructor
normally attaches to `tl_su`; that fact alone is not a program-wide proof
that it can never become reachable through another subtree.

A separate lifetime constraint affects a possible restart. Original
`TLoadCtrl::cleanup_scene` queues its current controller and clears the
global instance immediately. The destructor later queues **whichever fade
pointer is globally current**, clears that slot, and clears any nonzero
instance without comparing it to the object being destroyed. The TObject
constructor appends siblings; `run_tasks` saves the next sibling before
deleting a queued node. Therefore ordering matters if a new controller is
published before that old queued node is drained.

Three controlled sequences execute original constructors, cleanup, queue
traversal, destructor and task body:

| Chosen ordering | Observed fixture state |
|---|---|
| Queue/clear A, then drain A without restart | A is deleted; no current controller remains |
| Queue/clear A, construct/publish B and a new fade, then drain A | A's destructor clears B's global gate and queues B's fade; B remains a live sibling but its task body leaves its tick at zero |
| Queue/clear and drain A, then construct/publish B | B's global gate/fade remain and its first task call increments its tick to one |

This is a chosen sequential ordering constraint, not an observed retail bug.
The probe publishes an actually constructed B at a chosen restart point;
it does not execute the full `start_loading` call and its resource callbacks.
The new fade uses an explicit base-node-only constructor model. Camera/audio/
platform helpers and frees are modeled boundaries. Tick one stops before
the child-spawn threshold of two, so it does not demonstrate repopulation.
Clearing the global suppresses the task body; the separate possibility of
existing descendants remains. Eleven release/lifetime controls independently
pass, in addition to the existing original-free analysis tests.

```sh
python3 tools/probe_loader_release_contracts.py --dol PRIVATE/PsoV3.dol --output build/release-contracts.json
```

The immediate heap, resource and array targets are now substantially more
specific. A surviving phase-19 request still does not establish their live
arguments or the order of controller completion/restart. The next useful
bounded trace is the window subtrees' construction/reparenting and the calls
that serialize queued-controller destruction with a later `start_loading`.
No retail state, source-correct handoff or restore ownership is inferred;
all original providers, function extents and accounting gates remain intact.

## Window descendants and the queued-controller drain boundary

The next trace distinguishes the detached window tree from its update driver
and the manager that owns its cleanup. The inspected constructors attach the
viewport/instance nodes under a detached `TObject(NULL)` root. A
`TWindowCtrlSub` under `tl_01` drives that root's updates. Removing that driver
alone therefore does not destroy the detached tree. However, the **complete**
`TMainTask::delete_layer_children` also deletes `tl_fadeafter` children, including
the normally attached `TWindowCtrlMain`. Its destructor deletes the detached
tree and clears the window globals before the later `free_all_windows` release
callback. These two cleanup scopes must not be confused.

Known attachment helpers are more specific than their names suggest:

- `TWindowDD::construct_base` obtains a viewport root through the split-aware
  `TWindowCtrlMain__sub_8024CDB0`/`8024CDD0` getter before calling the base
  `TObject` constructor. [Source](../../src/pso/misc/TWindowDD_8024662C.cpp).
- `TWindowSubComCard::reparent_to_main_ctrl` at `0x80244888` calls getter
  `0x8024CE24`, then `TObject::set_parent`. The getter returns the object at
  `viewport_states + 0x8C`: **viewport slot five**, not the global instance.
  Its inspected callers include card-dialog/window cleanup operations.
  [Helper](../../src/pso/misc/TWindowSubComCard_80244774.cpp),
  [dialog example](../../src/pso/misc/TWindowSubComCard_8033BDB0.cpp).
- Other descendants can be attached through the global instance, for example
  `TFontSmallHelp`. Their actual presence, descendants and lifetime are not
  established by that constructor. [Source](../../src/pso/misc/TFontSmallHelp.cpp).

The [window-teardown probe](../../tools/probe_loader_window_teardown.py)
executes the original main dispatcher, chosen request action, menu update,
menu exit, reverse release-table loop, layer cleanup, window constructors and
destructors. Five controlled trees reach the original modem-helper boundary:

| Chosen fixture | State at the helper boundary |
|---|---|
| Loading controller remains under `tl_su` | Window tree deleted; controller remains, no loading destructor called |
| Controller deliberately reparented into viewport five | Window-tree destruction calls its loading destructor and clears the instance |
| Menu task boundary queues controller through original `cleanup_scene`, without draining SU | Instance zero; queued SU controller remains undestroyed |
| Same cleanup with a chosen direct SU drain | Controller already destroyed |
| A base-node window fixture is moved into viewport five, then moved back out to SU | Escaped node survives window cleanup; the separate loading controller also survives |

All five execute the thirty release-table callbacks in the original table
order. Twenty-nine callback bodies are explicit no-effect models; only the
window callback executes here. Snapshots show that the manager destructor has
already completed tree deletion during layer cleanup before that callback
starts. Eleven constructor allocations and each expected logical free are
checked. The viewport-five helper runs over a base-node-only compatibility
fixture. Reparenting a loading controller is a **generic countermodel**, not
an authenticated source call or evidence that this attachment occurs in the
game. Unknown actual descendants and aliases still prevent a preservation or
destruction claim about the retail transition.

The cleanup/restart question also has a distinct traversal gate. The original
`TMainTask::run_task` applies `update_flags` to its child layers when they differ
from `old_update_flags`, then calls `TObject::run_tasks` on the main parent.
That traversal tests each child layer's flags before recursing. In contrast,
the read-wait frame calls `tl_su->run_tasks()` **directly**; `run_tasks` tests
its children, not its receiver's flags. Thus an explicit main-task tick after
cleanup is a drain opportunity, rather than unconditional proof that queued
SU descendants were destroyed.

Three separate post-request controls execute the original main-task and
traversal instructions. With SU as the first child and chosen `update_flags=1`,
the main tick sets its pause flag `0x8` and leaves queued controller A alive.
Calling the paused SU's `run_tasks` directly then destroys A while leaving
the SU pause flag unchanged. A fresh queued controller is destroyed by the
main traversal after `update_flags=0` resumes SU. These isolate receiver versus
child gating; they are not a continued execution of the modem helper or proof
that the chosen pause state is reachable during retail launch. The harness
enables the emulated FPU so original window float-initializer instructions
execute; it does not replace those instructions.

The accompanying pinned original-text inventory finds seven direct branch
encodings to `start_loading`, three to `poll_default`, twelve to
`cleanup_scene`, and one to the loading constructor, all linked branches.
These declarations belong to the loading wrapper and the inspected gameplay/
lobby loading owners, rather than to the menu update/release bodies. The
inventory retains declared owners and does not resolve indirect calls or
branch conditions. Source inspection finds explicit cleanup followed by
`main_task.run_task` on the normal paths in those owners. Two transfer-pending
early returns and the online-lobby nonzero-handle branch do not contain an
immediate drain after their cleanup call. `begin_frame` is empty. Intervening
resource callbacks, layer flags and later paths must still be traced; no
universal serialization or restart exclusion follows from this inventory.

These controls retain synthetic factory, predicate and task effects, logical
frees and platform/resource boundary models. Full `start_loading`, real
allocations, arbitrary descendant classes and runtime callbacks are not
executed. The useful next discriminator is how the relevant paths establish
SU flags and queued-controller state before the first read wait, including
the early-return paths and any callback that can publish a new controller.
The original-provider and restore-ownership holds remain unchanged.

```sh
python3 tools/probe_loader_window_teardown.py --dol PRIVATE/PsoV3.dol --output build/window-teardown.json
```

## Known indicator references in the first read-wait frame

The stronger positive discriminator after the teardown trace is whether the
known indicator references are drained before a read-wait frame renders.
An absence of recognized writes to an update-mask global would not establish
its retail value or exclude aliases. The indicator destructor chain instead
provides explicit operations and a frame-order predicate that can be tested.

The [indicator-drain probe](../../tools/probe_loader_indicator_drain.py) runs
the original loading constructor in mode zero and calls its original task
body twice. Tick one allocates no indicator. Tick two constructs
`TNowLoading`, its network indicator and cursor, and their particle controllers
through the original factory and particle initializer. Original `VecCopy`
instructions also execute. The fixture checks the resulting tree links,
allocation order and reference identities: the network indicator stores five
nonnull references, the cursor one, while `TNowLoading`'s own four reference
fields remain zero. All six particle controllers attach under `tl_07` and
have their own address in the initializer's owner field. Their original
vtable render slot is the no-op `TObject::render`; their task body can generate
other objects and must not be confused with that render slot.

Original `cleanup_scene` queues the loader and clears the instance. During
the original `run_frame`, SU traversal precedes camera, TL07 and particle
updates, and all those updates precede rendering. Deleting the queued loader
recursively deletes its indicator children. The original network destructor
queues its five referenced controllers and the cursor destructor queues its
one reference. TL07 traversal can therefore destroy those six later in the
same frame, before even the SU render traversal starts.

Four independently replayed controls distinguish the required contracts:

| Chosen fixture after construction/cleanup | Known controllers destroyed before rendering |
|---|---|
| Valid references, destruction enabled | Six; loader and three indicator nodes also deleted |
| Loader has `DISALLOW_DESTRUCTION` (`0x20`) | Zero; queue bit clears, loader/descendants survive, and the still-current fade remains eligible for the frame's fade passes |
| One referenced particle controller has `DISALLOW_DESTRUCTION` | Five; that controller survives with its queue bit cleared |
| One additional controller has no indicator reference | All six known references drain; the unrelated controller survives |

The controls execute the original constructors, reference queues, destructor
chain, frame and tree traversals. Logical frees are counted and checked for
duplicates. Surviving task/render bodies are explicit boundary markers rather
than simulated effect generators. In particular, the ordinary queued-loader
case reaches no such surviving body. The protected-loader case retains six
particle-task boundaries and the cursor-render boundary; the unrelated case
retains its one particle-task boundary. The protected-particle case retains
that node without invoking its task body in this first queue-processing pass.
This is narrower than a claim that protected objects always stop updating.

This experiment uses synthetic zero particle descriptors, a chosen pool limit
and valid disjoint allocations. Rotation math uses chosen zero output angles;
the fade is a base-node-only constructor model. Platform/resource helpers and
surviving task/render effects remain modeled; logical frees do not reproduce
allocator reuse. It directly invokes two loading ticks, not the full
`start_loading` resource path or a retail menu history. Earlier-generated
objects, changed ownership, stale aliases, different live types and unrelated
cache writers remain outside the result. Nothing establishes the word later
loaded at `0x8042E9EC` or original restore ownership.

The missing discriminating evidence is now more specific: actual loader,
descendant and controller flags/references when the first read wait begins,
or an authenticated predecessor/callback trace that establishes them. For
effects already generated before cleanup, the selected particle definitions
and generator/parent-lifetime contracts must also be established. These
cannot be replaced by the fixture's synthetic descriptors or a retail file
entry address. Original providers, extents and accounting remain unchanged.

```sh
python3 tools/probe_loader_indicator_drain.py --dol PRIVATE/PsoV3.dol --output build/indicator-drain.json
```

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
