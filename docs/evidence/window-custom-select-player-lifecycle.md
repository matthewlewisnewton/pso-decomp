# CustomSelect player lifecycle: a narrowed, unresolved precondition

This bounded investigation starts at continuation
`4011a74909c618b1bedba71df05e5d71e3cf1154` and is qualified on main
`5bba9c44adebc1cfa019def85e1f39f6da340ef0`. It changes no constructor,
allocator, task, guard or original behavior. The partial-initialization hold in
[the native-code checkpoint](window-custom-select-native-code.md) remains.

## The transition spans task invocations

In `TUnk_804D1160::run_task`, state 2 reads CustomEquip's cursor and updates
help, then reads its selection bit. Selection sets state 3 and the switch
breaks. The next invocation performs `new TWindowSubCustomSelect(client)`;
there is no positive player recheck before construction. State 3 immediately
falls through to state 4, which asks the new window for its current action.
The skipped table/grid fields matter before eventual child destruction too.

`TWindowSubCustomEquip::handle_decide` sets the selection bit without checking
player presence. Its task handles input without a dominating positive-player
check. Palette-refresh functions and the controller's help update can return
when the player is absent, but those returns do not veto the controller's
selection transition. Opening MainMenu originally checks for a player; that is
not by itself a lifetime guarantee through a later task invocation.

The lookup at 801BA74C rejects invalid indices and otherwise reads
`player_slot_table`. The player destructor calls `unregister`, whose body calls
collision/entity cleanup and clears its slot. This is an observed invalidation
path, not proof that removal is reachable while this menu transition is active.

## The window tree is not the player's descendant tree

The inspected allocation/parent arguments form this observed TObject chain:

| Owner/producer | Created child and parent argument |
| --- | --- |
| Active WindowCtrl constructor | CtrlPlayer, parent is the WindowCtrl receiver |
| CtrlPlayer constructor | MainMenu1P or MainMenu4P, parent is CtrlPlayer |
| MainMenu submenu producer | Customize controller, parent is MainMenu |
| Customize controller state 3 | CustomSelect through its native window construction |

The first three links do not parent the menu under `TObjPlayer`. Player
TObject destruction therefore does not automatically establish teardown of this
menu tree. Its `clear_links` forwards to collision-body cleanup; the inspected
unregister path does not directly close MainMenu. Other player cleanup helpers
are not assumed to have no indirect global effects: a complete cross-root
lifecycle proof is still missing.

CtrlPlayer's update path invokes `update_main_menu_request`. That routine
returns if the player lookup fails; the inspected branch does not close or
queue MainMenu. Other null-player branches close status/Palette/short-list
children, which does not prove closure of the MainMenu/customize subtree.
Generic TObject task traversal and queued destruction alone do not establish
the required ordering across the player and window roots.

## Nonzeroing allocation is not a substitute invariant

TObject new calls `heap_alloc`, not the separate `heap_zalloc` wrapper.
Allocation updates the free-list headers without clearing returned payload;
`heap_zalloc` separately calls memset. Initial heap-pool clearing supplies no
per-allocation reuse guarantee. CustomSelect's null-player return still occurs
before its child slots and grid/table state are initialized. No zeroing,
synthesized default child, allocator change or destructor guard is added.

## Bounded verification and stop condition

Nineteen individual production functions were compared to their current
original bodies and function-relative resolved targets: CustomSelect's 388-byte
constructor/116-byte destructor, customize controller and producer, CustomEquip
selection/task, window-root and CtrlPlayer construction/task, menu-request
update, player lookup/unregister/collision-link helper/destructor/entity-unregister
wrapper, TObject allocation/traversal and heap allocation/zero-allocation.
All nineteen bodies and targets agree. This is not a claim that the large
player translation unit as a whole is exact. The separate full build and
protected-provider checks qualify the combined branch.

Private source/original-function evidence is in `pr403-customselect-lifecycle/`.
Original objects and raw disassembly are not published. Independent review
agrees that no local dominating valid-player guarantee was found.

The exact missing evidence is a global window-root teardown or update-suspension
invariant before player-slot removal, covering the state-2-to-next-invocation-3
gap and subsequent window use. The observed code does not yet prove that
invariant, and this audit does not construct a reachable runtime failure.
Neither presumed zeroed storage nor byte equality clears the hold. Word,
ComCard, opaque heading/Scroll ownership and other interface holds remain.
