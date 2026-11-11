# Controller shutdown callback ordering

This read-only follow-up starts at continuation
`8b58a2a7ed0cbaf75f4c0194f7cb107b53cce85a`, including main
`d6fc686573510cc9612beb6a2d71576ad685301c`. It investigates a distinct
possible origin for the [conditional follower timing scenario](window-com-card-close-phase-control.md),
without treating that scenario as a demonstrated game failure.

## A shutdown helper is not its calling context

The original 60-byte `TWindowCtrl::shutdown()` queues the active controller if
present, clears the active global, frees chat-log resources and calls an empty
menu helper. It does not directly release the viewport roots. Taken alone,
this body could not establish whether a status close was accompanied by root
teardown.

The historical name `TWindowCtrl::close()` is also misleading for this audit:
its 44-byte body calls an empty menu helper, initializes the chat heap and
clears the active controller global. It is the paired initialization callback,
not evidence of another status-destruction operation. The names and source
contracts are unchanged.

## Original table entries give a bounded ordering control

A scan of all 4,960 configured original objects finds exactly two references
to each helper, all zero-addend ADDR32 data relocations. They are the following
scene-table entries; no original direct call to either helper is found:

| Original table | Controller initialization / shutdown | Preceding row's root release |
| --- | --- | --- |
| offline_game_scene_callbacks, size 0x180 | +0x50 / +0x54 | +0x4C |
| online_lobby_scene_callback_table, size 0x158 | +0x40 / +0x44 | +0x3C |

Each table uses eight-byte load/unload pairs. The preceding row's load callback
is the window-manager reset helper and its unload callback is
`TWindowCtrlMain::free_all_windows`. The original 88-byte reverse iterator
walks rows backward and invokes their second word. Normal completion therefore
calls controller shutdown, then root release on its next iteration, with no
intervening table row. The separate 108-byte forward iterator invokes first
words and checks area-transfer state between rows; its behavior is not a
guarantee of complete initialization on every interrupted load.

The original offline `TLobby::teardown_scene` and online
`cleanup_online_lobby_scene` both call full layer deletion before unloading
their respective tables. Thus these two known entries do not establish a
standalone controller shutdown without root teardown. This adds a concrete
callback edge to the earlier full-layer/root-manager control; it does not
make every possible controller retirement equivalent to those scene exits.

## Limits and qualification

The census does not exclude computed calls, runtime table mutation, raw aliases
or alternate controller-removal paths. Adjacent callback rows do not exclude
reentrant task dispatch inside a callback or prove successful completion of
the entire teardown. Phase/session constraints and interrupted initialization
still need independent evidence where a broader claim depends on them.

The earlier destructor-slot qualification also remains: releasing all sibling
windows does not prove that the status destructor's stored icon pointers are
valid when it calls `close()` through them. No invalid access is executed or
claimed reachable here. No cleanup order, pointer clearing, ownership, guard
or default initialization is changed.

The expanded original comparison covers 54 overlapping function bodies and
their relative relocation targets across 26 units, including the prior
46-function cohort, both controller callbacks, chat cleanup, the two empty
menu helpers, forward/reverse iteration and offline scene teardown. These are
audit controls, not newly recovered functions. Each inspected source provider
occurs once with its original counterpart absent; the original data provider
containing both scene tables is retained once. No table is moved or localized.
The existing executable retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Independent review confirms the original table adjacency and bounded caller
order. This is documentation-only evidence, with no new native build, behavior
change, coverage gain or hold clearance. Further progress needs a distinct
controller-removal/alias path or concrete callback/slot-validity evidence;
repeating the earlier scalar timing cases would not supply it.
