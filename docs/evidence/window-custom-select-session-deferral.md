# CustomSelect: session replacement and packet deferral

This follow-up qualifies the [stored-client audit](window-custom-select-client-identity.md)
on continuation `264bee15256513aaed94d37170d2f8e93e7b2ecf`, with tested main
`08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`. It identifies a real transition
mechanism behind the parser's ping-only branch. No game source, compiler setting,
provider, allocator or behavior changes, and no lifetime hold is cleared.

## A bounded deferral mechanism

The parser's word at TProtocol offset `0x191C` is the existing
`m_handle_pings_only` field. Original construction initializes it to zero.
Two original free functions access that same word through the
`TLobby__protocol_instance` global:

| Phase | Original operation and significance |
| --- | --- |
| `reset_state_flags` | Reset the deferred buffer, store word 1 at `+0x191C`, and mark player setup pending. |
| `parse_packet` while the word is nonzero | Dispatch command `0x1D`; copy other completed packets into the deferred buffer. |
| `process_deferred_player_setup` | Perform the selected setup case; if protocol exists, store word 0 at `+0x191C` before calling drain. |
| `drain_deferred_packets` | Iterate buffered records and call `handle_command` directly. |

Original receiver-load relocations, store values and the parser load establish
this connection; it is not inferred from the function names alone. Across all
3609 original text objects in the current generated inventory, a syntactic scan
for immediate `0x191C` finds exactly those four instructions: constructor store,
parser load and the two free-function stores. This is a bounded literal-access
census, not proof that no computed/indexed address or raw alias can touch the word.

Setup is conditional. States 1/2 call `construct_lobby_players`, states 3/4 call
`make_players`, and state 5 calls the retained legacy helper. Other states do not
thereby create a player. The wrapper's completion is not proof of a positive
lookup for every menu-owning client. Neither this audit nor the existing source
establishes that ping-only mode surrounds ordinary customization.

The buffer is reset before collection. Copying respects the existing 64KiB limit;
records that do not fit are not appended. Drain resets its read cursor, stops at
a zero command or the end bound, obtains each stored size and dispatches through
the current protocol. There is no client-ID/menu check in this replay loop, and
it does not consult the ping-only flag again. These are original operations,
not a claim of arbitrary-input safety or a reason to change its bounds behavior.

## Positive transition controls and their limits

Four original reload routes have the following direct call order:

`reset_state_flags` → `delete_layer_children` → main-task execution →
`process_deferred_player_setup` (including conditional drain).

The routes are `reload_lobby_floor_scene`, `reload_floor_scene`,
`start_quest_mission` and `change_floor_reload_area`. The earlier
[task-root controls](window-custom-select-task-controls.md) establish that full
layer deletion deletes tl_00 and tl_01 children before the player layer. Thus these
routes supply concrete deletion-before-replay evidence for the old controller
layers. The separately rooted popup storage retains its ownership qualifications.
This is stronger than treating a fade or a pause toggle as teardown.

Some routes preserve players by temporarily reparenting them, rebuild tasks and
restore them before completion. Explicit main-task execution occurs before the
final setup/drain call. The direct sequence does not prove no indirect processing
inside intervening helpers, no newly created menu, no later task invocation, or
that every removal path traverses one of these four routes. It is not a universal
suspension or stored-client-generation invariant.

## Session replacement is a different control

Both game-join and lobby-enter handlers invoke `destroy_all_objects` before
rewriting `local_client_id`. Despite its broad name, that helper consists of
twelve guarded queue-destruction/global-clear pairs for tracked lobby UI objects.
It does not directly delete/suspend the active WindowCtrl or its
MainMenu/customize tree. Its name cannot substitute for the full layer-deletion
control above, and the global rewrite alone cannot rebind a stored menu client.

The lobby-add and game-add callbacks explicitly reject an entry matching the
current local client before deleting/replacing an actor. The exit callbacks do
not contain that test. This original-code contrast is discriminating evidence
about the client; it is not a protocol guarantee that a valid server sends, or
never sends, an own-client exit while a menu is active. Arbitrarily injecting
such a packet would not establish a valid-session counterexample.

## Verification and remaining evidence

Seventeen complete production bodies and function-relative resolved relocation
targets match original: protocol constructor/parser/task; reset and deferred-setup
wrappers; buffer reset/copy/drain; the four reload routes; tracked-UI cleanup;
and game/lobby join and add callbacks. The individual sizes and original direct
call/field controls are retained privately in `pr403-customselect-session/`.
These functions overlap earlier audits and are not additive recovered-function
counts. Independent review agrees with the bounded interpretation. No original
object or instruction listing is published, and no runtime session is executed.

Only evidence/index documentation changes. Production report, Ninja graph and
DOL hashes remain unchanged from the validated current branch; no new full build
or coverage gain is claimed. Original DOL and protected-provider qualifications
remain those of the pinned current-main build. Whitespace, inventory and frozen
review checks qualify publication.

The missing discriminator remains legitimate session notification semantics and
teardown/deferral ordering for the menu's stored client generation. The four
reload controls identify where the old controller layers are already deleted; they do not
establish ordinary active-menu safety after replay or validate self-exit delivery.
CustomSelect's partial-initialization/nonzeroing-allocation hold, Word, ComCard,
original-provider, ownership and interface holds remain. No reachable failure or
universal safety result follows.


The subsequent [DD/main integration](window-dd-main-integration.md) preserves all
seventeen session controls on main `d6fc686573510cc9612beb6a2d71576ad685301c`.
Its separate full-build/provider qualification changes the report and graph;
the earlier documentation-only hash-identity statement applies to the pinned
`94a4045114` checkpoint. No session/lifetime hold is lifted by the renderer work.
