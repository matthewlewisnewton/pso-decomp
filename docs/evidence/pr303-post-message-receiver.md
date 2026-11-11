# Message-post receiver ownership

Read-only audit at PR #303 head
`6d361cf2177eda08ea2780ec770b29b7e919a468`, with main
`e65f11ce6ec99c006909422f81da1c0a46ac062e` (2026-11-11).
The recovered name `post_message__6TLobbyFlll` identifies native address
`0x80425C70`, size 0x8C. Its configured class/mangled name is not evidence of
historical `TLobby` ownership.

## Reference closure and arguments

Scanning all 5,021 original split ELF objects finds exactly three relocations
to this helper, all `R_PPC_REL24`, all in `NetworkMessageTransport.o`, and all
inside `dispatch_received_ethernet_frame` (`0x80425DC8`, size 0x348). A separate
direct-branch scan of the original DOL's text sections finds those same three
calls. No aligned absolute address word to the helper appears in initialized
DOL sections. Source contains these three calls and one member declaration.

| Native call | Original object offset | Selected delivery path | Receiver in r3 |
|---|---:|---|---|
| `0x80425F8C` | 0x41C | Broadcast, mode 2 | `r29 + 0xA0` |
| `0x80426004` | 0x494 | Accepted multicast, mode 2 | `r29 + 0xA0` |
| `0x804260F8` | 0x588 | Accepted local unicast, mode 2 | `r29 + 0xA0` |

The original object's HA/LO relocations at 0x28A/0x28E identify r29's base as
`lbl_805CF240`. The resolved DOL instructions independently establish that base
as `0x805CF240`; all three receivers therefore equal `0x805CF2E0`.
Each call also passes the frame address in r4, the existing extent word minus
four in r5, and selector 1 in r6. Results are discarded. This does not prove the
frame extent is valid or authorize removing the selector-zero path.

## Queue ownership

`0x805CF2E0` is the start of `TLobby__pppoe_message_queue`, the middle of three
adjacent SDK queue records. The native initializer independently passes this
address to `OSInitMessageQueue` at `0x804263AC`, with message storage
`0x805CF300` and capacity 32. The SDK queue occupies 0x20 bytes; its 32 four-byte
message slots fill the remaining 0x80 bytes of the 0xA0-byte record. The typed
SDK repair retains these exact extents and addresses.

Queue producers are the three delivery paths above. Consumers are
`recv_pppoe_message` and the drain routine at `0x80426574`, both using nonblocking
SDK receive. The former reads the queued descriptor's length/address words at
+4/+8; the drain routine reads +8 and calls the existing entry-clear helper.
This audit does not
reclassify packet-buffer ownership, add rollback, or prove end-to-end lifetime
safety.

The posting helper saves incoming r3 unchanged in r30. It does not dereference
that receiver. Its only operational use is forwarding the same word to
`OSSendMessage` at `0x80425CC4`, with flag zero. The payload pointer is separate:
the selected descriptor is returned by one of the two existing lookup paths,
and argument 2 is written at descriptor offset four before the send.

On null lookup there is no write or send and the helper returns -1. On SDK send
failure the offset-four write remains; no rollback occurs in this helper.
Success requires the SDK result to equal 1 and returns zero; other results
return -1. Preserve these original operations and failure behavior. In
particular, a receiver recovery must not add queue checks, retry, entry release,
or result handling in the three callers.

## Scope of the finding

The observed receivers are SDK message queues, rather than `TLobby` objects or
the payload descriptors. That supports considering a separate explicit
`OSMessageQueue *` parameter while retaining every existing branch and argument.
It does not establish a historical shared declaration, a singleton-only helper,
or the absence of dynamically synthesized/external callers. The original
selector-zero branch must remain even though the three observed calls select
the other branch.

No API or native source change is made by this audit. Receiver and adjacency
holds remain, alongside private creator/raw callback/reset and metadata holds.
A separate recovery would need independent source-contract review, complete
native code/relocation comparison and normal original-DOL/no-loss validation;
the current receiver interpretation alone is not acceptance of that change.
Do not compensate for any mismatch with parameter, lifetime, register or compiler
steering.

The source/native traces and reference scans were independently reviewed. The
original DOL SHA-1 remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; all prior SDK queue validations
remain applicable because the audit changes documentation only. No new matching
function, code or data gain is attributed to it. Keep draft.

## Explicit queue-parameter probe

After the audit, test one separately source-reviewed recovery: the owner-local
C-linkage helper `post_network_queue_message(OSMessageQueue *, s32, s32, s32)`.
Replace the implicit receiver with an explicit SDK queue parameter, remove the
nonvirtual `TLobby` declaration, and rename only the configured export and its
force-active entry. The address and size remain `0x80425C70` / 0x8C. The new name
describes this recovery; it is not asserted to be a historical shared API.

The body retains both lookup paths, all locals, the descriptor offset-four write,
SDK send flag zero, result comparison and every return. All three calls retain
the original `mq + 0xA0` byte-address expression and all three existing argument
words, converting the queue address explicitly to `OSMessageQueue *`. No singleton
specialization, selector removal, queue check, retry or rollback is introduced.
No callback, allocator or private status contract changes.

The first probe reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The complete **compiled owner** ELF
equals its saved reference after exactly one audited helper-name mapping. Section
and symbol order/properties, all code/data/debug payloads and raw relocation
bytes remain equal; only the renamed symbol's string offsets/length and necessary
physical ELF placement differ. No instruction or relocation payload is normalized.
The other 3,664 compiled objects are raw byte-identical.

The regenerated **original-reference split object** is a separate comparison:
its string table mechanically moves the renamed helper from string ordinal 27
to 39. Its mapped symbol records/order and raw relocations agree, but its string
order does not satisfy the strict complete-object comparison. Do not claim whole
original-reference equality or broaden the compiled-owner normalization to hide
this distinction. That reference object is not the selected compiled provider.

Incremental report comparison has zero metric, coverage or retention drift, with
only the helper rename. Full sealed-main comparison passes with 3,599 exact linked
units, 18,428 retention entries without drift, existing +88 data bytes and no new
function/code gain or loss. The ordered provider list remains 3,599 source inputs
and 1,347 original fallbacks. All fourteen DHCP/modem host tests, inventory and
whitespace checks pass. Independent source and complete-object review finds no
remaining objection to the bounded receiver recovery, subject to final exact-head
review.

This repairs the fake receiver for this owner-local helper and its three observed
calls. Cross-object adjacency, historical shared-declaration uncertainty, private
creator/raw callback/reset ABI restrictions and the metadata hold remain. Keep
draft; no other hold is cleared by this probe.

## Direct queue-reference control

Test one natural adjacency repair after the explicit-parameter checkpoint:
replace the dispatcher byte view with `OSMessageQueue *mq =
&TLobby__pppoe_message_queue.queue`, and pass `mq` directly at the same three
calls. Direct SDK references in the accepted initializer make this a credible
compiler control, without assuming an aggregate owner for separate globals.
All other arguments, branches, fields and helper behavior remain unchanged.

Native validation rejects this one form. The dispatcher grows from 0x348 to
0x34C bytes. Its queue HA/LO relocation target changes from `lbl_805CF240` to
`TLobby__pppoe_message_queue`, with receiver/register setup changes and shifted
subsequent relocations. Only the owner changes among 3,665 compiled objects;
the DOL SHA-1 becomes `e1602266e859a1875dd307031c612d45b94cb0c0`.
Independent review confirms the failure. Restore the saved source exactly and
rebuild; all 3,665 objects and the original DOL return to their prior bytes.
No alternate lifetime, aggregate, alias, pragma or compensating expression is
tested. The adjacency hold remains. The rejected source is not published.

## Shared descriptor lookup declaration

A separate producer/caller audit finds a narrower contract mismatch:
`TLobby__sub_804256B8` is defined as
`NetworkPacketBufferDescriptor *(u32 address)`, while message transport locally
declares `u8 *(s32)`. The producer locks, searches the 32 active descriptors by
unsigned address range, unlocks, and returns either the descriptor or null.
Existing native size/field assertions establish its 12-byte record, with the
queued-length word at +4 and the actual packet-data pointer at +8.

Original split objects contain exactly three references, all zero-addend
`R_PPC_REL24` calls in message transport, at object offsets 0x138, 0x924 and
0xBE8. These correspond to the posting helper's selector-zero path,
`post_send_message`, and `queue_timeout_message`. Share the producer's existing
declaration, with C linkage only for that function, in `NetworkPacketPool.h`.
Include that header in the caller and remove the incompatible local declaration.
Convert signed address words explicitly to `u32`, retaining their native bits,
and expose the returned descriptor as a `u8 *` byte view at the existing byte
accesses. This view is descriptor storage, not the packet data at its +8 field.

No implementation, lookup range, lock timing, null behavior, descriptor write,
allocation API, callback or source configuration changes. The other allocator
declarations and `find_entry_by_address` remain separate interfaces. No bounds
or ownership invariant is invented, and the adjacency control is fully restored.

The first lookup-declaration probe passes. Owner, provider and runtime complete
objects are raw byte-identical to saved references, without normalization; all
3,665 compiled-object hashes are unchanged. The DOL retains original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental comparison has zero
metric/coverage/retention drift. Full sealed-main no-loss comparison passes with
3,599 exact linked units, 18,428 retention entries without drift, existing +88
data bytes and no new function/code gain or loss. Ordered providers remain
3,599 source inputs and 1,347 original fallbacks. All fourteen host tests pass.
Independent source and native review passes; final exact-head review remains
the publication gate. Only this lookup declaration mismatch is repaired.
Adjacency, other allocator/output-pointer questions, private ABI and metadata
holds remain. Keep draft.
