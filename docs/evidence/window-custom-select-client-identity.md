# CustomSelect: stored client identity and exit dispatch

This bounded follow-up to the [player lifecycle audit](window-custom-select-player-lifecycle.md)
and [original task controls](window-custom-select-task-controls.md) narrows the
identity question without changing game source or clearing the lifetime hold.
It inspects continuation parent `3ce0344d973e6be1df9c0db824e36d2a2b4cdc8e`
with accepted main `829806820f864516b12abff6bd439c4ad84392a1` integrated.

## Which player belongs to the menu?

The active WindowCtrl producer passes `local_client_id` to the single-screen
CtrlPlayer, or indices 0 through 3 for split-screen controllers. Original callers
forward the stored client word through CtrlPlayer offset0x24, MainMenu offset0x54
and the customize controller offset0x20 into CustomSelect's player lookup.
MainMenu1P/4P still have incomplete C-named constructor interfaces: this is
original register-forwarding evidence, not a recovered portable constructor ABI
or clearance of the width/interface qualifications.

The removal relevant to this hold must affect that stored menu-owning slot.
Removal of an arbitrary remote table entry is insufficient. A later comparison
against global `local_client_id` would also need proof that the global still
identifies the same client generation as the stored menu slot.
`is_locally_controlled()` tests `control_state == 1`; `setup_control_role` maps
roles into that state. A role predicate and slot identity are separate facts.

A complete current generated-object relocation census covers 4962 original and
3633 compiled objects, with 512552 relocation records. The six named constructor
targets have exactly eight original references: two WindowCtrl-to-CtrlPlayer
calls, one CtrlPlayer call to each MainMenu wrapper, the two wrappers' calls to
the common MainMenu initializer, MainMenu's customize-controller call and that
controller's CustomSelect call. All eight are zero-addend REL24 calls in the
inspected chain. Compiled references agree, with additional compiler catalog
metadata. This bounds named/address-resolved constructor references; it does not
exclude arbitrary raw storage, inlined construction or runtime address arithmetic.

## Exit packets and removal callbacks

The recovered command table binds 0x69 to `TProtocol::recv_exit_lobby` and 0x66
to `recv_exit_game`. Complete original `handle_command` bytes and resolved targets
qualify the binding; each original method-pointer descriptor separately has
zero receiver adjustment, nonvirtual selector -1 and the expected target.
The compiler's twelve-byte PMF constants are not asserted to be static sixteen-byte
command-table entries in the original data section.

Original receive code loads nullable callbacks at receiver offsets0xBC24 and
0xBC1C. It copies the eight-byte exit payload and forwards signed client/leader
bytes, plus disable-UDP for game exit. TLobby initialization installs
`retire_lobby_player` at 0xBC24 and `remove_player` at 0xBC1C. The initializer's
complete original body and resolved targets also match production.

In the inspected normal framing/dispatch chain there is no comparison excluding
`local_client_id` or the menu's stored client. `retire_lobby_player` looks up and
synchronously deletes the supplied slot's actor. `remove_player` removes the peer
and actor, clears its name/current dialog and resumes layers when quest download
is inactive. Closing that dialog is not proof of customize-menu teardown.
These leaf operations do not establish that a valid server/session can notify
this client of its own menu-owning player's exit while that menu is active.

Timing remains qualified: `parse_packet` defers non-ping packets through
`copy_packet` while `m_handle_pings_only` is set. This audit does not prove that
mode inactive during customization, exhaust every possible raw alias write, or
prove callback/task ordering through a valid removal transition. Absence of a
local-ID filter in normal dispatch is not absence of all temporal guards.

## Validation and the missing discriminator

Eighteen complete production function bodies and function-relative resolved
relocation targets match original: WindowCtrl, CtrlPlayer, common MainMenu and
both wrapper constructors; create_submenu, customize-controller and CustomSelect
constructors; player lookup, control-role setup and local-role predicate; TLobby
initializer and both removal callbacks; and the two exit decoders, handle_command
and parse_packet. This overlaps earlier lifecycle evidence and is not a claim of
eighteen additional distinct recovered functions. Private controls and receipts
are in `pr403-customselect-identity/`; original objects and instructions stay
private. No packet was fabricated or executed and no runtime session was tested.

The next discriminator is legitimate server/session self-exit versus other-client
notification semantics, combined with stored-slot generation and menu teardown or
packet-deferral ordering. Evidence must show either that the menu-owning player
cannot disappear before the next construction/use invocation, or the actual
applicable teardown/suspension path. This audit proves neither a reachable failure
nor universal safety. CustomSelect's nonzeroing allocator and partial-initialization
hold stays, as do Word, ComCard and all other standing technical holds. No source,
compiler profile, provider or behavior change follows from this investigation.
