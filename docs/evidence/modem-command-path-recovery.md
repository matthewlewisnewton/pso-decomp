# Modem command-path recovery

Current validation base: `59dfc7117a7e2cd251b65f1b435e66a9bf174618`.
The unit has 25 recovered bodies, 14 exact functions, and remains unlinked.
The PR is reviewed as partial source recovery. Complete native matching and
source linking remain follow-up work; the historical draft checkpoints below
record the limits at each earlier validation base.

Initial base: fork main `f0f05f3afe56fd2b71e9dc1fe946e2fa03c84b86`.
Reference: upstream `8c507b2dacae5428291a823c3868ca486419660c`, including
network C recovery #213 (`76d99c974ba4897eca428c505be1af4d4f6ec124`) and
modem initializer recovery #243 (`23795dfa1d27576b0cd4034d2fb37c47583969ab`).
Upstream #241 is a BBA-driver follow-up, and #244 is Matchpass 17. Neither is
an independent modem command-path implementation.

## Scope and evidence

Recover five missing bodies in the existing `pso/network/ModemRuntime.cpp`
unit without changing its compiler profile, pragmas, split boundaries, launch
context provider or source-link status. The original split object is the
instruction and relocation oracle. Upstream bodies are references, not proof of
source correctness or authority to import their matching devices.

- `0x8042CD64`, 404 bytes: poll modem register 5 for a FIFO byte count, yield
  while empty, read command `0x23`, append received bytes to the existing
  response buffer, and recognize `OK` / `ERROR` with the original state machine.
- `0x8042D49C`, 360 bytes: validate a CR-terminated AT command, uppercase it,
  reject the existing 22 prefix-table entries, acquire EXI, transmit, wait for
  the response, and unlock. This body is exact.
- `0x8042D6A4`, 316 bytes: wait for FIFO space using register 4, send command
  `0x63` with the byte count, and transmit up to four bytes per immediate
  transfer while advancing the command pointer and remaining length by four.
- `0x8042E320`, 360 bytes: validate the dial mode and connection state, publish
  the result callback, build the selected dial command, set connecting state,
  acquire EXI, transmit, and unlock. The two setup-command statuses are ignored
  by the original; this source does not reserve an unused result local.
- `0x8042E488`, 244 bytes: retain the low byte in the existing register-0x13
  shadow, acquire EXI, write the register, and unlock. Its input remains full
  width, consistent with its caller and the original byte store.

The original EXI calls establish channel 0, device 2, frequency 4, two-byte
register commands, one-byte register data, and four-byte FIFO commands. The
ordinary inline helpers describe those transactions. No unused `selected`
variables, dummy arrays, frame-alignment attributes, new intrinsics or new
optimizer controls are imported to reproduce stack slots.

The address-based placeholder C function names remain provisional. They do not
establish that these routines were methods of the character-select class. The
existing actual C++ members remain actual members.

## Shared API corrections

Use the SDK declarations from `dolphin/exi.h`, `os/OSInterrupt.h` and
`os/OSThread.h`, rather than incompatible local declarations. The thread queue
at `lbl_805D7CA0` is an `OSThreadQueue`, as required by both sleep and wake calls.
The existing hangup command literal is a six-byte character array according to
its original symbol extent, not an integer converted to a string address.

`libs/dolphin/src/exi/EXIBios.c` invokes callbacks with `(chan, context)` in
both the immediate and DMA completion paths and when a queued lock is granted.
The existing native static member `wake_load_thread` therefore takes
`(s32, OSContext *)`; it ignores both inputs. Its declaration, definition and
compiler-emitted symbol identity are updated together. There is no extra thunk
or hand-mangled declaration. The existing C callback at `0x8042DDE4` uses the
same SDK signature, and both packet/message transport consumers now include its
shared header instead of repeating `(int, int)` declarations.

The reset callback is `BOOL (*)(BOOL)` in `os/OSReset.h`. Give the existing
native `send_modem_hangup` member that signature and remove its callback cast.
Its body remains exact. `map_state_to_code` now receives the dial string as a
`const char *`, and forwards an ordinary `void (*)(s32)` result callback rather
than a `void *`. The direct session caller supplies the existing byte-string
buffer through the explicit byte-string/character-string boundary. Symbol
metadata follows the changed native member signatures at the same addresses.
These changes describe their observed call interfaces, not authenticated
original class ownership or original source spelling.

The command-list adapter `TLobby__sub_803F7E50` retains its inherited native
address-word parameter. Its new shared declaration makes that debt explicit,
and it converts to a character pointer only at the now correctly declared
command validator. Converting the whole cursor to a pointer made GC/1.2.5
commute the operands of one existing add; even spelling the sum in the original
source order did not preserve its bytes. No pointer-to-integer expression was
introduced to steer that instruction. The existing address-word adapter is not
claimed as a recovered original interface. This boundary should be revisited
with the rest of the transport's address-word storage.

## Matching status and holds

| Address | Original bytes | Result |
| --- | ---: | --- |
| `0x8042CD64` | 404 | 99.91089% fuzzy; stack layout differs |
| `0x8042D49C` | 360 | 100% exact |
| `0x8042D6A4` | 316 | 99.81013% fuzzy; stack layout differs |
| `0x8042E320` | 360 | 99.933334% fuzzy; command-buffer stack offset differs |
| `0x8042E488` | 244 | 99.81967% fuzzy; stack layout differs |

All five have the original instruction count, control flow and call targets.
For the four non-exact bodies, objdiff identifies only stack-frame/stack-slot
immediate differences. Upstream obtains its slots with unused helper status
locals or an unused dial result local. They are not imported here. This is a
bounded comparison, not proof that no clean source organization can match.
The unit stays unlinked and incomplete. A passing DOL hash does not score these
unlinked candidate bodies: their runtime bytes still come from the original.

The remaining modem bodies, frame mismatches, unit-local data layout and
inherited raw state views are follow-up work. The 22-entry command-prefix table
is external data at `0x804FDA78`, immediately beyond this unit's owned
`[0x804FDA20, 0x804FDA78)` data range. Its external reference is not a missing
unit-local definition or a reason to extend this unit's ownership.
The original modem initializer independently clears a 0x2C-byte send record at
`0x805D1DD0` and a 0x40-byte receive record at `0x805D1DFC`; that supports later
typed transfer-state recovery. The existing initializer's padding devices and
interrupt handler's explicit leading-zero intrinsic are not imported by this
change.

## Validation

Fresh fork-main and candidate native builds use the pinned project tools and
checkout-local original inputs under the shared capacity gate, with Ninja
`-j2`. The first compiler invocation needed sandbox escalation for Wibo. One
unchanged baseline retry recovered from a transient compiler PE-image mapping
failure. The successful baseline and candidate both reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

`tools/check_pr.py --no-build` passes against the fresh main baseline:

| Measure | Main | Candidate | Change |
| --- | ---: | ---: | ---: |
| Exact functions | 27,414 | 27,415 | +1 |
| Exact code bytes | 4,212,112 | 4,212,472 | +360 |
| Exact data bytes | 1,472,559 | 1,472,559 | 0 |
| Source-linked code bytes | 3,730,376 | 3,730,376 | 0 |
| Source-linked data bytes | 1,188,215 | 1,188,215 | 0 |
| Linked units | 3,589 | 3,589 | 0 |

There are zero lost exact functions or live code/data/link ranges. All existing
12 exact modem functions remain exact; the unit becomes 13/25 exact functions.
The three renamed native member symbols keep their original addresses and
extents. Linked-unit and generated retention checks pass with no drift. The
porting-exception inventory and changed-line whitespace checks pass; all 268
source-tool tests pass. No new exception is introduced.


## Transmit-state continuation

The next increment recovers `0x8042DE20` (300 bytes, exact),
`0x8042DF4C` (568 bytes, 99.92254% fuzzy) and `0x8042E184` (412 bytes,
99.85437% fuzzy). The latter two retain only stack-immediate differences. The
first increment's four frame mismatches remain unchanged. Five other modem
bodies remain absent; the complete unit is still unlinked and incomplete.

The first 0x2C bytes of the existing `modem_exi_state` allocation are now a
`ModemSendState`: busy flag, current data pointer, remaining and total lengths,
immediate head and tail pointers/counts, DMA body pointer/count, and completion
callback. Original `0x8042DD70`, `0x8042DE20` and `0x8042DF4C` accesses and the
initializer's independent 0x2C-byte clear constrain those fields. Size and
callback-offset assertions verify the native record view.

`0x8042DD70` now uses those actual fields rather than writing outside
`modem_connection_info` through casts. Its shared API takes a buffer pointer,
length and `void (*)(s32)` callback. The transport retains its existing
address-word queue field, converted once at this explicit buffer boundary;
there is no callback-to-integer conversion. All 116 bytes of this previously
exact routine remain exact, as does its source-linked transport caller.

`0x8042DE20` limits a transfer to the remaining modem FIFO space, updates the
remaining count, separates immediate head/tail bytes from complete 32-byte DMA
cache lines, stores the body cache range, and sends command `0x68`. Ordinary
address-width `size_t` expressions express the alignment operations. Introducing
inline helper functions for these expressions was a 96.26667% candidate with
different frame/register allocation; the direct expressions match without any
padding, alignment attribute, dummy local or optimizer change. The alignment
calculation uses the native DMA/cache contract, not an arbitrary object-address
transformation. A port must use its target's DMA/cache facilities.

The completion callback drains immediate head bytes, starts DMA and returns for
its second phase, drains the tail, deselects, updates the interrupt mask and
unlocks EXI. Head/tail counters decrease by four, even for a shorter last
transfer. It clears busy/data and the saved callback before calling the client
with the original total length. The callback-active flag is set only around
that call. It does not assert lock ownership: EXI is already unlocked, and the
client may reenter the modem API. `0x8042E184` deliberately returns zero when
the transport may start a send; its original signed/unsigned comparisons and
callback-context lock suppression are preserved.

`EXIImm` copies immediate write bytes into the hardware data register before
returning, as shown by `libs/dolphin/src/exi/EXIBios.c`; the asynchronous
completion therefore does not retain the stack command's address.

### Preserved storage and ownership hold

Only the proven transmit prefix is typed in this increment. The existing
0x70-byte `modem_exi_state` allocation and symbol extent remain unchanged; its
remaining 0x44 bytes are explicitly opaque inherited storage. This is a
provisional binary interface, not authentication of an original combined
source object or discovery of another field.

The original initializer separately clears a 0x40-byte receive region at
`0x805D1DFC`, ending at `0x805D1E3C`. The next linked SDK `Ecb` allocation starts
at `0x805D1E40` and its original and compiled `.bss` sections both require
eight-byte alignment. That is strong evidence for a four-byte alignment tail.
It does not by itself resolve the existing allocation's source ownership.
Replacing it with two independent records would reduce the report's original
BSS extent by four bytes under the current extraction and strict no-loss
accounting. No special suffix field, standalone padding object, artificial unit,
new alignment directive or weaker guard is introduced to hide that uncertainty.
Full storage/source-link readiness remains held pending a justified ownership
and accounting resolution.

### Continued validation

The continuation's fresh capacity-gated native build reproduces the original
DOL. Relative to main, exact functions are 27,414 -> 27,416 and exact code bytes
are 4,212,112 -> 4,212,772 (+660); relative to the first published checkpoint,
the increment adds one exact function and 300 bytes. All data, source-linked
coverage and unit counts are unchanged. ModemRuntime is 14/25 exact functions
and its original 0x120-byte BSS coverage is unchanged. The complete current-main
comparison and the incremental comparison both retain every byte in all nine
strict coverage/exactness/link categories. This remains partial progress.


## Pinned-main integration validation

The branch integrates pinned main
`1a18b4bd7577af4ee367317064e020d1f91ce5a8` through merge
`f2ff3e6efa` after the transmit increment `b3b48349b6`. The merge is clean;
main's rope and ADX recovery, shared declarations and generated metadata are
preserved. The same modem code and storage remain under review.

The sealed shared main baseline is authenticated by its exact commit/tree,
tracked-source manifest, active object inputs, toolchain and generated build
artifacts before its report is reused. No redundant main build is run. The
candidate receives its own capacity-gated native build with fresh split objects.
It reproduces the original DOL SHA-1. `check_pr.py`, all nine strict no-loss
categories, linked-unit/retention and exception-inventory checks pass against
that exact main baseline.

| Measure | Pinned main | Candidate | Change |
| --- | ---: | ---: | ---: |
| Exact functions | 27,416 | 27,418 | +2 |
| Exact code bytes | 4,213,640 | 4,214,300 | +660 |
| Exact data bytes | 1,472,575 | 1,472,575 | 0 |
| Source-linked code bytes | 3,737,624 | 3,737,624 | 0 |
| Source-linked data bytes | 1,190,727 | 1,190,727 | 0 |
| Linked units | 3,590 | 3,590 | 0 |

Relative to the earlier published branch, main itself removes four unallocated
`.sdata2` padding bytes at `[0x805DAA54, 0x805DAA58)`. This inherited main
accounting change is disclosed separately; the fresh pinned-main comparison
loses no original coverage, exactness or source-linked interval. All 268
source-tool tests and changed-line whitespace checks pass. Modem's full
BSS extent and existing exact functions remain unchanged throughout.

Actual ELF linker inputs still select the original modem fallback and the
source transport/session objects. ModemRuntime remains 14/25 exact functions,
with six recovered non-exact bodies and five missing bodies. A passing full
DOL is not evidence that those held bodies are source-linked. The branch stays
draft; neither callback cleanup nor matching gains resolves its storage,
remaining data-layout or frame-recovery holds.

## Receive preparation and completion

The next increment reconstructs `0x8042BF6C` (440 original bytes) and
`0x8042C124` (448 original bytes). It refines the already allocated receive
region after the transmit prefix using its original 0x40-byte clear and all
original accesses, including the callback at receive+0x3C. The unknown f10,
f14, f34 and f38 flags retain provisional names. Assertions constrain the
receive size, offset within the unchanged allocation and callback offset.
The final four already allocated bytes remain unclassified inherited storage;
no new padding object, alignment directive or ownership assertion is added.

The preparer sets the transfer length, clears the old immediate/DMA slices,
partitions the receive buffer into immediate head/tail and complete 32-byte DMA
lines, sends modem command 0x28 and drains the immediate head. It starts a DMA
with the correctly typed completion callback when a body exists, otherwise
calls that callback directly with zero/null SDK arguments. It does not
pre-invalidate the receive body or import upstream's unused EXISelect status
local.

The completion drains the tail in at most four-byte immediate reads, decrementing
its counter by four, invalidates a completed DMA body and clears body_length,
then advances received count and the buffer by the transfer length. It
preserves deselect, interrupt-mask restore and EXI unlock before handling the
client callback. In contrast to the send callback, it clears the accumulated
received count **after** the client callback returns. This original ordering
is preserved, including its reentrancy implications.

The clean preparer is 98.281815% fuzzy and 444 emitted bytes versus 440
original bytes. Besides its frame difference it materializes one additional
receive-buffer field address and allocates registers differently. The
completion is 99.90179% fuzzy at the original 448-byte length, with only stack
immediates different. A bounded alternative that captures the receive buffer
as a real local value emitted 440 bytes but scored 96.09091%; it was discarded.
No unused local, raw offset alias, pragma or layout attribute is added to force
these bodies exact. The two existing new exact routines and all earlier exact
functions remain unchanged.

A public [Dolphin modem implementation](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/HW/EXI/EXI_DeviceModem.cpp)
corroborates the command/packet FIFO and register protocol. Its
[header](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/HW/EXI/EXI_DeviceModem.h)
explicitly derives register names from PSO reverse engineering. It therefore
does not authenticate an original helper or dead-local/frame organization.
No Dolphin code is copied or adapted here. The six earlier stack-layout holds
remain unresolved; a bounded public-source search did not supply independent
original-source evidence that would justify the rejected unused locals.


## Synchronous receive and current validation

The same receive increment adds `0x8042D7E0`, 1,424 original bytes, with a
shared byte-buffer declaration and one explicit conversion at the transport's
existing generic buffer boundary. It retains the early busy/no-data returns,
first-entry flag clears before locking, register setup order and the clearing
of f38 after lock acquisition. It does not change unrelated register shadows.
An empty modem FIFO only unlocks and returns zero. For data, it uses immediate
head/tail reads and synchronous DMA with a null completion callback followed by
`EXISync`. It invalidates only the completed DMA body after all reads, then
deselects, restores the interrupt mask, unlocks and returns the original length.
It neither calls the asynchronous completion nor updates asynchronous receive
progress. No bounds check or callback-context lock suppression absent from the
original is introduced.

The synchronous body is 99.9073% fuzzy at the original 1,424-byte length.
All 33 differing instruction operands are stack immediates; control flow and
call targets agree. This is a ninth recovered non-exact body, not a new exact
match. The initial two new exact routines and all pre-existing exact routines
remain exact. The only absent bodies are the modem interrupt dispatcher at
`0x8042C2E4` and initializer at `0x8042CEF8`.

`tools/tests/test_modem_receive.py` compiles the actual current receive bodies
and record declarations with synthetic device stubs. Eight scenarios cover
async head/DMA/tail completion, callback-visible state mutation and post-callback
reset, immediate-only completion,
early busy/no-data exits, empty FIFO, first-entry register ordering and shadow
preservation, and synchronous DMA/cache ordering, including mixed immediate/DMA reads,
without async-state changes.
The fixture uses 32-bit scalar types with host pointers: it checks semantics
and call ordering, not target record layout, native frame matching or real
hardware. The test is explicitly skipped if no host C++ compiler is available;
it executes and passes in this validation environment. No original game inputs
or copied emulator code are needed for this test.

The branch merges exact current main
`fffd67d0c35e1fdaf17880c563739750e7c35813` after independently authenticating
the shared baseline's clean tracked sources, tool/compiler hashes, generated
configuration and ordered input list. The candidate has its own capacity-gated
native build; no duplicate main build is used. The native DOL, `check_pr.py`,
all nine strict interval categories, linked units, retention and exception
inventory checks pass against that baseline.

| Measure | Current main | Candidate | Change |
| --- | ---: | ---: | ---: |
| Exact functions | 27,420 | 27,422 | +2 |
| Exact code bytes | 4,217,568 | 4,218,228 | +660 |
| Exact data bytes | 1,472,639 | 1,472,639 | 0 |
| Source-linked code bytes | 3,802,084 | 3,802,084 | 0 |
| Source-linked data bytes | 1,193,991 | 1,193,991 | 0 |
| Linked units | 3,594 | 3,594 | 0 |

The new receive bodies add no exact or source-linked bytes yet. All modem
storage extents remain unchanged. Separately, the main update after 1a18
removes four bytes at `[0x8051857C, 0x80518580)` from the spatial-audio unit's
reported BSS range. Those bytes were counted exact in the earlier report;
this inherited main accounting change is not attributed to modem recovery.
The exact-current-main comparison loses no coverage or exactness.

Readiness remains held on the nine non-exact recovered bodies, two absent
bodies, incomplete unit-local data layout and unresolved storage/interface
ownership. No dummy locals, newly invented padding ownership, raw offset
aliases, new intrinsic, compiler profile or optimizer changes are introduced.

All 269 source-tool tests pass in this environment, including the eight-scenario
receive semantics fixture. The native layout and matching holds remain separate.


## Interrupt dispatch and initialization

The next increment reconstructs both remaining absent bodies, without adding
an intrinsic or importing upstream's dummy stack locals. All 25 bodies now
have source, but only 14 are exact; this is still a partial, unlinked recovery.

The interrupt dispatcher at `0x8042C2E4` reads register 2 under an EXI lock,
intersects it with the existing shadow mask and handles only the highest set
bit. An ordinary bounded scan on the already nonzero byte expresses that
priority without `__cntlzw`. The four handled bits are 0x10 (transmit), 0x20
(receive availability), 0x40 (receive length) and 0x02 (AT response). It does
not process every pending bit. The original edge behavior is retained: an
unsupported highest bit returns after disabling the hardware interrupt mask,
without unlocking. The zero-masked-status path unlocks without disabling the
mask. Transmit and active receive branches transfer the lock to their existing
completion paths rather than unlocking early.

The AT-response branch drains the actual FIFO count in chunks up to four,
parses the response, restores the mask and unlocks before delivering a result.
It clears done before the client callback, sets the callback-active flag around
the call and retains the response callback pointer, unlike the one-shot send
and receive callbacks. No new append bounds clamp is introduced. The portable
priority scan changes the dispatch instructions and register allocation. The
dispatcher emits 1,572 bytes versus 1,524 original bytes and is 95.91863% fuzzy.
This is not an exact-match gain.

The initializer at `0x8042CEF8` acquires EXI before initializing the shadow
registers and thread queue. It separately clears the proven 0x1C connection,
0x40 receive and 0x2C send records. It resets only done and length in the
response record, preserving its callback, result, FIFO count and buffer. The
four inherited unclassified bytes and the unused shadow bytes remain untouched.
Typed field assignments replace upstream's cross-field pointer-update aliases.

It probes the device at frequency zero and preserves the initialized connection
state on an ID mismatch, unlocking and returning -1. A matching 0x02020000 ID
allows the 0x8000 reset command at frequency four, followed by the original
register writes and five AT-command/wait pairs. All five wait results remain
ignored. Mask enable follows the final wait, followed by SDK-typed callback
registration on channel 2, reset-hook registration and EXI unlock. Channel 2
for the callback is the original behavior, despite data transfers on channel
0/device 2. The shared initializer declaration replaces the direct caller's
local duplicate without changing its C ABI.

Its real used command buffer retains the upstream reference's 0x88 capacity
as an explicitly provisional choice. The original stack buffer accesses do
not authenticate that declaration or capacity. The capacity is not adjusted
to reproduce a frame. No dummy array, unused result, alignment attribute,
compiler setting or padding object is added. The body emits the original
1,444-byte extent and is 99.869804% fuzzy in the project report;
stack offsets still differ. The direct object comparison also exposes literal
bank relocation associations at the same 0x40/0x4C offsets.

Ordinary emission of its two used command literals restores the first 86
bytes of the owned 88-byte `.data` bank with the original bytes and reset-hook
relocation. Both sections retain eight-byte alignment. The compiled bank ends
at 86 bytes while the split bank includes two further zero bytes. Those bytes
remain an honest data-layout hold; no invented tail object or enlarged string
array is added to claim them. Thus the report gains no exact-data bytes yet.
The setup prefix strings at 0x805D489C, 0x805D48A4 and 0x805D48B0 remain external
and their symbol extents are not pulled into this unit.

The extracted-source host control fixture exhausts all 65,536 status/mask
pairs and checks lock failure, unsupported priorities, receive delegation and
capacity clamping, AT FIFO chunking and callback retention. Initializer tests
cover device-ID failure, original state preservation, ignored wait failures
and cross-group setup/command/mask/hook ordering. Like the receive fixture,
these synthetic stubs check semantics and ordering, not target ABI, actual
hardware or native frame matching.

The candidate's capacity-gated native build still reproduces the original DOL
hash against authenticated main `fffd67d0c35e1fdaf17880c563739750e7c35813`.
`check_pr.py`, all nine strict no-loss categories against both main and the
previous receive checkpoint, linked-unit/retention, exception inventory and
whitespace checks pass. The 270 source-tool tests include both host fixtures.
No existing exact function is lost; the total gain remains two functions and
660 exact code bytes, with no exact-data or source-link gain. The original
modem fallback is still the actual linker input.

Readiness is now held on 11 non-exact bodies, the original helper/frame and
buffer declaration evidence, the final two data-bank bytes, unresolved storage
and interface ownership, and whole-unit source linking. Having all bodies
present is not equivalent to a matched or ready unit.


## Pinned 12a main integration

The branch cleanly integrates newer main
`12a3368673103f37dfd3710886ce24a4e19c6783` after the reviewed control-path
checkpoint. Main's status-display recovery, PageIndicator declarations, split
ownership, linked-unit entry and retention changes are preserved. The modem
production bodies and both host fixtures are byte-identical across the merge.

The shared baseline is independently authenticated against its exact clean
commit, all 7,202 tracked Git blobs, 137 tool/compiler hashes, generated graph
snapshots, original/native DOL hashes and 4,950 ordered linker inputs. It has
3,595 source inputs and 1,355 original fallback inputs. Only this candidate
receives another capacity-gated native build; the shared baseline is not
rebuilt. The candidate reproduces the original DOL SHA-1.

| Measure | Pinned 12a main | Candidate | Change |
| --- | ---: | ---: | ---: |
| Exact functions | 27,421 | 27,423 | +2 |
| Exact code bytes | 4,218,916 | 4,219,576 | +660 |
| Exact data bytes | 1,472,639 | 1,472,639 | 0 |
| Source-linked code bytes | 3,807,220 | 3,807,220 | 0 |
| Source-linked data bytes | 1,193,999 | 1,193,999 | 0 |
| Linked units | 3,595 | 3,595 | 0 |

The complete modem recovery remains 14/25 exact functions. All 25 bodies are
present, but the 11 mismatches and the previously documented capacity,
layout/ownership and source-linking holds are unchanged. This integration
does not turn host semantic tests or an original-fallback DOL into native
matching credit.


The integration's `check_pr`, strict nine-category no-loss comparisons against
both pinned main and the published control checkpoint, all 3,595 linked units,
18,288 retention entries, exception inventory and whitespace checks pass.
All 270 source-tool tests pass. The rebuilt modem object comparison is unchanged
from the reviewed control checkpoint; no gain is attributed to merging main.

## Review preparation against current main

Merge `4ba4f3118b8513109ce3fa94c9bb09a4e287337f` integrates fork main
`59dfc7117a7e2cd251b65f1b435e66a9bf174618` without conflicts. Main's radial
particle and word-select recovery, source-link entries, shared declarations and
retention changes are preserved. The only production-source edit in this review pass explains the modem
dispatcher's intentional lock retention for transfer branches and unsupported
highest status bits; it changes no behavior.

GitHub contained no inline review comments or submitted reviews at this pass.
The previous progress comment's matching, data-layout and ownership limits
remain valid. They constrain whole-unit matching and source linking, rather
than being claimed as resolved by this recovery PR. The 11 non-exact bodies,
provisional initializer buffer capacity, final two data-bank bytes and four
unclassified storage bytes remain explicit follow-up work. The unit is still
excluded from `linked_units.txt`.

Both the exact archived main tree and the integrated candidate receive fresh
native builds using checkout-local original inputs and the pinned tools under
the shared exclusive capacity gate, with Ninja `-j2`. Both reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The candidate then passes the full
`tools/check_pr.py`, including its Ninja step, against that fresh main report.

| Measure | Current main | Candidate | Change |
| --- | ---: | ---: | ---: |
| Exact functions | 27,423 | 27,425 | +2 |
| Exact code bytes | 4,221,216 | 4,221,876 | +660 |
| Exact data bytes | 1,472,695 | 1,472,695 | 0 |
| Source-linked code bytes | 3,814,852 | 3,814,852 | 0 |
| Source-linked data bytes | 1,194,071 | 1,194,071 | 0 |
| Linked units | 3,597 | 3,597 | 0 |

Unfiltered original-address comparison preserves all nine code/data/function
coverage, exactness and source-link categories. All 3,597 linked units and
18,296 generated retention entries pass. All 270 source-tool tests, Python syntax,
porting-exception inventory and changed-line whitespace checks pass. No new
porting exception is introduced.

The receive/control fixtures again pass eight receive scenarios and all
65,536 raw status/mask pairs. A separate extracted-source transmit spot check
passes 512 cases across all 32 buffer alignments and 16 lengths, covering
immediate/DMA byte order, multiple FIFO windows, deferred lock acquisition,
busy/disconnected returns, readiness thresholds and callback delivery after
unlock and one-shot state clearing. The same spot check passes AddressSanitizer
and UndefinedBehaviorSanitizer with leak detection disabled because this
environment's tracer prevents LeakSanitizer operation. These synthetic checks
do not authenticate native ABI, frame matching or real hardware behavior.

Direct object comparison still reports 14/25 exact functions. The actual ELF
inputs select the original modem object and the compiled transport/session
callers. Review readiness applies to the bounded source recovery and its two
exact-function gains; it does not claim that the modem unit can now link from
source.
