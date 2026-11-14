# Controller-driven menu reopen: receiver and conditional retirement order

Evidence-only follow-up at `13d6ced7b9e35fe7c7afa7138c15ea6b21520fc9`.
That remote head was clean and its exact-head hosted source checks passed. Literal
main was `1712bd56c8bc24956dc6279019c0dda0fc577f8c`. No integration or build attempt.

## Concrete receiver chain

In the non-split constructor path, TWindowCtrlPlayer allocates a 1P menu, passes
itself as parent at 8024E34C, invokes its constructor at 8024E350 and stores the
result at controller +0x28 (8024E358). Allocation success and an unchanged slot
are preconditions for this receiver identification. Split-screen uses the 4P
menu and is not included in this transition proof.

`update_main_menu_request` loads that slot and the receiver's table at +0x18.
Its open dispatch at 8024DE38 loads table slot +0x18, whose original 1P table
entry is vfunc_6. The close dispatches at 8024DD54 and 8024DDD4 instead load slot
+0x20, the 1P vfunc_8. Placeholder source names m4/m6 are not evidence of the
actual target identity; the original table and load offsets establish it.

The open path requires a non-null menu and player, passes the preceding input,
visibility and activity gates, observes get_active_menu zero, and has key==0x1F.
get_active_menu queries the menu's +0x4C mask 0x1. vfunc_6 itself repeats the closed
bit test and player lookup before opening and creating a transition.
The function-key path calls try_open_battle_menu instead and is excluded here.

Both close branches jump directly to the request-method epilogue after their
virtual call. Therefore this one invocation does not close and then fall through
to the open dispatch. This is local control-flow exclusivity, not a ban on a
separate/reentrant invocation during the same engine frame.

## Conditional normal-cycle ordering

CtrlPlayer::run_task (8024E188) invokes run_all_updates; that routine calls
update_main_menu_request at 8024E0C0. The controller task precedes the normal
TObject recursion into its descendants. Menu close queues/clears its active
submenu; it does not synchronously destroy it or remove the menu itself.

For a close followed by the *next ordinary controller task*, if normal descent
into the same menu child chain occurs between those requests, the old transition
remains in that chain, destruction is enabled, and no intervening reentrant
publication/mutation occurs, the queued transition is deleted during that
intervening descent. Its global clear then precedes the next open's publication.
This excludes old-generation late clearing on this specific normal cycle.

It is not the same ordering argument as the AreaMap child-task return: this
request executes in an ancestor task, and the useful retirement interval is
between request invocations. The explicit intervening-descent condition cannot
be dropped merely because there are two input events or two nominal frames.
Suspended/paused menu ancestry, removal/reparenting, disabled destruction,
reentrant/direct invocation and alternative publication paths remain outside the
proof. The disabled-destruction queue-consuming behavior remains as documented
in the AreaMap note; no later deletion is guaranteed in that case.

## Tests, limits and next discriminator

Retained complete .text equality against original split objects passes for
CtrlPlayer (584 bytes), Ctrl_8024D960 (2084) and MainMenu_8024E3CC (104).
This is not a fresh build or relocation/current-main integration check.
The separate reopen-order model passes its ordinary case and demonstrates that
skipped descent or disabled destruction defeats the claimed retirement ordering.
It is a conditional ordering model, not a full task interpreter or game test.

No production change is justified by this bounded proof; no global callback
lifetime/table hold is cleared. Next check should target actual mutations of
menu/ancestor update flags or additional callers of update_main_menu_request,
not repeat the already established constructor/table mapping. Establishing that
ordinary menu descendants are always visited between relevant requests would
remove a stated assumption; without it this remains path-specific evidence.

A named `bl update_main_menu_request` search across the available original split
assembly finds only run_all_updates at 8024E0C0. This is a direct-symbol search,
not exclusion of indirect, raw-address or other-runtime calls. The retained
executable remains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Independent read-only review passed the original receiver/slot mapping, close
branch exits, conditional traversal argument and all three model cases. No
source-quality hold was lifted.
