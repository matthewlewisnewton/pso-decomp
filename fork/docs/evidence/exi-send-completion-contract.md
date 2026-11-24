# EXI send completion registration

Source base: `d6fc686573510cc9612beb6a2d71576ad685301c`. Its only change from
native baseline `cb862cd99ef707159a73e33c302fdf753cdee5e1` is README progress
text. This is a separate callback path from the dormant raw-IP tables.

## Producer, slot and consumer

The message thread at 80425CFC passes `TLobby__sub_80425D88` to
`TLobby::start_exi_send` (8042B334/0x3C). The registration stores its third
argument into the four-byte slot 805D7C54 at 8042B358. The target's sole
address-taking reference is the thread's HA/LO pair; the registrar has one
original REL24 caller. All 4,943 active original objects have exactly three
relocations to the slot: registration store, completion load and completion
clear. Direct original-DOL SDA accesses agree, using SDA base 805DA600.

The slot is initially zero within the startup BSS clear range
805D49A0..805D7CFC. The registration overwrites it without testing an earlier
value, then starts the existing DMA path. The known caller waits on the
completion queue before continuing its send loop. These facts do not establish
exclusive slot ownership, synchronization or a general one-outstanding-send
guarantee, and no such check is added.

The original-backed consumer is `TLobby__sub_80429B8C`, not 80429648. It loads
the callback at 8042AA74, clears the slot at 8042AA80, and calls it at 8042AA88.
The call is gated by completion state in r29, **not by a null-pointer test**.
The two completion paths load unsigned status bytes at 8042A5E0 and 8042A844;
their values reach the callback in r3. The slot is cleared before the call, so
the callback's invocation does not retain that registration. No cancellation,
failure cleanup, retry or null handling is inferred or introduced.

The known target at 80425D88/0x40 explicitly retains the low eight bits of its
argument, increments the pending count and sends the byte as a message to
805CF380 with flags zero. The source already declares and defines it as
`void(u8)`. The consumer does not inspect the callback result, but its epilogue
leaves r3 live. Its two observed entry-registration routes resolve that limit:
it registers itself with `EXILock(0, 2, self)` at 80429BB8, and initialization
passes it to `EXISetExiCallback(2, self)` at 8042B304. The SDK interrupt handler
calls it at 80430058 and overwrites r3 at 8043005C; the unlock-queue handler
calls it at 80430624 and overwrites r3 at 80430628 before returning literal one.
Neither path consumes its incidental result. Eight other original references
are nonzero-addend internal jump-table labels, not entry registrations; no
direct branches or aligned literal pointers to the entry were found.

The message thread waits for the completion queue, ignores the message value
and decrements the count. These facts support the observed `void(u8)` callback
contract; they do not recover a historical typedef or assign meaning to the
status bits.

The reference closure is bounded to the inspected source, original object
relocations and native accesses. It does not prove absence of dynamically
constructed addresses, arbitrary memory writes or external consumers.

## Minimal interface and validation limits

Share `ExiSendCompletionCallback`, use it for the registrar's third parameter
and existing slot declaration, and pass the known callback directly. Keep the
other parameters, local declarations, store order, DMA call, callback body,
queue/counter behavior and all failures unchanged. The registrar's source
signature determines its changed export spelling at the same address and size.
No new global definition or source provider is introduced.

The EXI owner unit is **not source-linked**. Before this change, 16 of its 19
functions match: 3,772 of 10,672 code bytes, with all 4,736 data bytes matched.
The source omits 80429648 (844 bytes), consumer 80429B8C (3,860 bytes) and
8042AAA0 (2,196 bytes). The consumer has no definition in the compiled object.
Those pre-existing gaps remain; the original-backed consumer is not recovered
or claimed source-validated by this change.

A DOL match alone cannot validate the changed registration source in that unit.
Acceptance separately requires the entire compiled owner and caller objects to
agree with the unchanged source baseline under the one export rename, and the
registration function's resolved instructions and relocations to agree with the
original. The compiler places SDA21 relocation records on the low halfword;
the original splitter places them on the instruction word. This existing
representation difference must be explained when comparing to original code,
while candidate-versus-source-baseline raw relocations must remain unchanged.

Raw-IP callbacks, private creator/reset, locked allocation, queue adjacency and
the original #303 metadata holds remain separate and unresolved. Original
behavior, including possible bugs, stays intact.

## Validation of the single candidate

Independent source review approved the minimal contract before compilation.
The candidate used the authenticated cb862cd9 native baseline, with the
README-only d6fc6865 source-base difference checked separately. Full build via
the shared capacity gate reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

All 3,632 compiled objects were compared: 3,630 are byte-identical, and the
complete EXI owner and message-transport objects agree under only
`start_exi_send__6TLobbyFllPFUc_v` → `start_exi_send__6TLobbyFlll`, including
sections, symbol metadata and relocations. All 4,943 split original objects
were also compared: 4,941 are byte-identical; the same two agree under that
rename and splitter string-table order. The complete 60-byte compiled
registrar resolves exactly to original instructions at 8042B334. Candidate
versus unchanged-source relocation records are identical. The existing
compiled/original SDA21 offset convention is accounted for explicitly.

The 3,860-byte original consumer and its relocations remain unchanged; it
still has no compiled source definition. The owner's 16/19 exact functions
and three unrecovered functions above are unchanged. There is no new
source-link, function-match or coverage gain. Ordered providers remain 3,612
source and 1,331 fallback; retention remains 18,663 with zero drift. Address
and data no-loss checks pass, with 27,447 matched functions, 4,243,592 matched
code bytes and 1,477,731 matched data bytes unchanged.

All 330 tool tests, four portable and sanitizer targets, syntax and port
inventory checks pass. The bounded slot/reference audit still finds the same
three slot accesses and sole concrete registered target. Native equality
supplements the source and call-chain evidence; it does not establish a
general alias, lifetime or concurrency guarantee.
