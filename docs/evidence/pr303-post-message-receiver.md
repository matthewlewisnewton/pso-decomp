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
