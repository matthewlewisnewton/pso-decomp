# CustomSelect: socket shutdown and conditional scene-exit ordering

This follow-up starts at continuation `4e45e551bbf28cbc54c06683e76bb37b53167eda`
on tested main `d6fc686573510cc9612beb6a2d71576ad685301c`. It extends the
[session-deferral controls](window-custom-select-session-deferral.md) with the
actual scene-dispatch edge and a bounded socket-field repair. It does not assume
a server can deliver an own-client exit while customization remains active.

## Identify shutdown rather than buffer readiness

`TLobby__sub_801384E4` and `update_state` preserve their existing guarded bytewise
OR1 at protocol offset `0x2A`. This is `TSocket::m_is_invalid_packet`;
`m_buffer_cleared` is the distinct byte at `0x2B`. The real producer is TProtocol,
which derives through TTcpSocket from TSocket. Native offset assertions distinguish
both bytes. Original protocol-task loads and the original transition load/OR/store
sequences independently qualify the field identity.

The two raw accesses now use the existing socket field. Including its canonical
header exposed an incompatible local `s32 memcpy(void *, void *, int)`
declaration. That declaration is removed; the unit uses the standard header's
actual return/source/size contract. The original calling behavior is preserved.
No replacement prefix structure, helper body, new flag, zeroing or additional
null/ownership guard is introduced.

The protocol task checks the invalid byte first and closes/reset its connection
state on that branch. The buffer-cleared byte governs the other receive-processing
branch. Positive TCP notification clears the latter; nonpositive notification
marks the former. Thus the observed transition store is a shutdown trigger, not
proof of a persistent receive pause. This is also distinct from the word at
`0x191C` controlling ping-only packet deferral.

`send_logout` sends command `0x05` and clears the connected state; it does not
itself close the socket or delete a player in its inspected body. `recv_logout`
closes/resets then invokes its registered callback. TLobby registers the callback
that queues its lobby controller for destruction. These direct operations do not
make packet66/69 actor-removal callbacks equivalent to a complete scene exit.
Transitive network/callback effects remain qualified.

## The conditional phase-dispatch edge

Original `main_phase_table` has twelve-byte init/update/exit rows. Row 15's
zero-addend ADDR32 relocations at table offsets `0xB4/0xB8/0xBC` target:

1. `run_online_lobby_scene`;
2. `TLobby::update_camera_state`;
3. `cleanup_online_lobby_scene`.

The table's original provider remains selected once. The original dispatcher
calls initialization, repeatedly invokes the update while result is zero, and
calls the current phase's exit callback after that loop ends. It then handles
results 1/2/3 by assigning the next phase. In particular, exit dispatch precedes
that phase assignment; it is not merely an unused cleanup function nearby.

Both inspected character-selection request wrappers pass 18 to the native phase
setter. The setter writes the next-phase word at `+4`, then result 1 at `+0x10`.
Consequently, when the phase 15 update returns and this loop ends, the dispatcher
invokes the registered lobby cleanup before entering the next phase. The request
call alone does not synchronously execute cleanup, and intervening work or raw
writes to global phase state are not exhaustively excluded.

The cleanup's original direct order is full `delete_layer_children`, layer
resume, deletion of `tl_su` children, a render-tick wait, later cleanup callbacks,
then reset of `local_client_id`. It contains no direct main-task update call.
Earlier task controls establish that full deletion processes the tl_00/tl_01
controller layers before the player layer. The separately rooted popup-storage
ownership qualification remains. This gives a concrete old-controller-before-
player teardown route for that returned phase transition, not a guarantee for
all notification/removal paths.

The frame routines run normal tasks earlier and may request disconnect or phase
change later. Cleanup is not immediate at those calls. Legitimate own-client
notification semantics, pre-return helper/callback effects and the stored menu's
client generation still require evidence. No reachable failure or universal
safety claim follows from this conditional dispatcher result.

## Exact production qualification

Twenty-two complete production function bodies and function-relative resolved
targets match original: protocol send/receive logout, parser/task; socket receive,
notification, close and construction; two lobby shutdown setters, lobby logout,
queued-controller callback and initialization; character-selection request
wrappers, scene cleanup/frame dispatch; phase setter, disconnect wrapper and main.
The original phase-table triple, request arguments, byte offsets and store/receiver
controls are separately checked. These audits overlap prior evidence and are not
additive recovered-function counts. No runtime session or fabricated packet is
executed. Private controls are in `pr403-customselect-exit/`.

The gated native build passes in 17.68 seconds and reproduces the original DOL.
The complete affected ELF differs only in one `.strtab` byte: local anonymous
data symbol `@1922` becomes `@1920`. Binding, section, offset 212 and size 108 stay
unchanged; after only that unique local-name normalization every ELF byte equals
the preceding production object, including all headers and raw relocation records.
Raw whole-ELF identity is not claimed. Report, ordered Ninja graph and DOL hashes
remain byte-identical, with no match, coverage or provider gain/loss.

Acceptance, 3612 exact linked units, 18837 retention names without drift, inventory,
whitespace and independent source review pass. The initial header compile exposed
the single conflicting memory declaration; correcting that actual contract is
qualified above. No optimizer, scheduling, section, layout or ABI-width variant
is used. All CustomSelect partial-initialization/nonzeroing-allocation, Word,
ComCard, ownership, original-provider and interface holds remain. Only the bounded
socket-field clarity and returned phase-exit ordering are established here.
