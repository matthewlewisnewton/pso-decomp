# Modem command-path recovery

Base: fork main `f0f05f3afe56fd2b71e9dc1fe946e2fa03c84b86`.
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

The remaining eight missing bodies, the four frame mismatches, the undefined
22-entry command-prefix table and inherited raw state views are follow-up work.
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
