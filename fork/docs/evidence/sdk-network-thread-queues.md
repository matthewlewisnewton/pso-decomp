# SDK network thread and queue interfaces

This independent extraction is based on main
`cda82a7aad7de1bf9b86470002df3f68d1c8c039`. It carries only the SDK boundary
repairs from #303 checkpoints `c0e5064f778f515a7ce098911a10c840fa49a34f`
(entry adapter), `ab6a5b4bfa1bdf7e9306c1565284615d2075af47` (handle/query),
`6d361cf2177eda08ea2780ec770b29b7e919a468` (queue records), and
`0cc69ab17ffe090f5d888084802dea26e1346ff0` (explicit queue receiver).
These identify prior evidence and authorship, not prerequisites. Packet #431
and DHCP #434 are not dependencies; no parser, receive-record or allocator
contract is imported.

## Thread boundaries

The supplied SDK declares `OSCreateThread` with entry `void *(*)(void *)`.
Its implementation supplies the parameter and uses `OSExitThread` for return.
The creator passes null. The adapter ignores that incoming argument, obtains
the current thread, searches the existing records, calls the existing private
`e->fn(e)` and returns null. Give the adapter the actual SDK signature and remove
the incompatible function-pointer cast. Its address/size stay `803F9C78`/`0x7C`;
only the signature-driven export spelling changes from
`run_current_thread_callback__6TLobbyFv` to
`run_current_thread_callback__6TLobbyFPv`.

The creator stores the embedded `OSThread` address as a native word only on
success. Five callers provide existing storage: the transport record at +4,
two globals and two dispatcher fields. `NetThreadHandle` uses the existing
`u32` type, preserving those PPC32 address words. The transport view retains
size 0x10 with a checked +4 handle member. Dispatcher fields already use this
representation. No private creator signature, callback, status check, output
timing or cancellation/resume contract changes.

The SDK declares `OSIsThreadSuspended(OSThread *)` and reads `thread->suspend`.
The two game calls pass a cached handle at native addresses 803F7C90/803F7D28.
Use the SDK header and explicit `OSThread *` conversion at these calls, retaining
the signed local word, read before locking, `== 1` checks and later global resume
reads. No null check or reload is added. This is a target address boundary, not
a claim that native address-word storage is portable to a wider host.

## SDK queue records and receiver

The SDK supplies a void initializer and BOOL send/receive functions, with
`OSMessageQueue *` and `OSMessage *` parameters. Native initialization and uses
establish three separate records:

| Address / symbol | Record size | Message slots |
|---|---:|---:|
| 805CF240 / `lbl_805CF240` | 0xA0 | 32 |
| 805CF2E0 / `TLobby__pppoe_message_queue` | 0xA0 | 32 |
| 805CF380 / `lbl_805CF380` | 0x48 | 10 |

Each has the 0x20-byte SDK queue followed by four-byte message slots. Compile-time
assertions check message width, record sizes and queue/slot offsets. Keep symbol
names, definition order and linkage. Receive through SDK message locals and
retain byte/record views only where the existing payload fields are consumed.
Five other units contain only unused duplicate byte-array declarations, removed
without changing their bodies. No queue capacity, flag, pending counter,
callback, +4/+8 payload operation or message-zero behavior changes.

The helper at 80425C70/0x8C never dereferences its alleged TLobby receiver; it
forwards it to `OSSendMessage`. Exactly three original REL24 calls from the
Ethernet dispatcher (object offsets 0x41C/0x494/0x588) supply the same native SDK
queue address. Recover owner-local C function
`post_network_queue_message(OSMessageQueue *, s32, s32, s32)`, retaining both
lookup selectors, the descriptor length write, send flag zero, success `== 1`
test and all returns. Null lookup still avoids the write/send. Send failure
still leaves the write in place; no retry, release or rollback is introduced.
Observed callers do not prove a historical shared API or exclude constructed
calls. The selector-zero path remains even though these three use selector one.

All three callers retain the original `mq + 0xA0` byte-address expression and
argument words. The separate globals are not combined into an assumed aggregate.
The previously rejected direct queue-address replacement is not retried. The
two exported names and corresponding retention references change at identical
addresses/sizes; split boundaries and source-provider selection stay fixed.

## Validation and limits

The serialized build uses the authenticated exact-main baseline and its 229
tool hashes. It preserves original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Of 3,632 active compiled objects,
3,630 are raw-identical. NetworkRuntime and NetworkMessageTransport match as
complete ELFs after only the two documented export-name mappings and consequent
symbol-string offsets/file placement. All section/symbol ordering and semantic
metadata, code/data/debug payloads and raw relocation bytes agree.

Of 4,946 active original objects, the same two additionally reorder their string
tables during regeneration. They are not claimed raw-identical: mapped string
multisets/counts and symbol-record order remain exact, as do all other payloads
and raw relocations. Ordered providers remain 3,606 source and 1,340 fallback.

Address-based no-loss, source-link and retention checks pass with 18,575 entries
and zero drift. Matched functions/code/data remain 27,438 / 4,237,032 bytes /
1,477,195 bytes, with only two reported function renames. Current Python and
portable/sanitizer tests, syntax, generated inventory and whitespace checks pass.
No new coverage is claimed.

The private creator/callback and reset ABI, raw callback registration, locked
allocator and cross-object queue adjacency holds remain. Original failure paths
and bugs are preserved. No compiler trick, flag, pragma or artificial reference
is added. Original #303 remains frozen.
