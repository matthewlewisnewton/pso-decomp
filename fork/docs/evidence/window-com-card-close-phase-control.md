# ComCard follower close-phase and task-order control

This bounded read-only follow-up uses continuation head
`af0be3dd63f740bcd0191ca6d98af8f38522ecd2`, including main
`d6fc686573510cc9612beb6a2d71576ad685301c`. It tests the limit of the
[conditional five-slot closure result](window-com-card-follower-lifetime.md).
No source variant, cleanup change or provider replacement is activated.

## Original ordering and two different counters

The icon producer sets the chain follower's sort key to the borrowed status
window's key plus 1.0, and each status-effect follower to that key plus 2.0
plus its effect index. The original float constants are 1.0 and 2.0. Window
sorting compares `get_scale()`, which reads offset 0x1C, and places the higher
key first. Under the inspected stable shared-root routing, this places those
followers before their status window. The separate depth-order value at 0x54
is not the compared key.

TObject traversal caches the next sibling before invoking the current task.
A queued, destruction-enabled node is deleted on its next traversal visit
without invoking that task. Neither this rule nor sorting establishes an
unconditional lifetime guarantee when a sibling borrows a pointer.

The follower descriptor has flags 0x82B: open and transition masks 1/2 both
start set. Base initializes its opening tick and closing counter to zero.
Closing during this opening transition sets pending-close mask 4. Progress
first waits for the opening tick to reach 7.5, then clears open/pending-close
masks and returns without incrementing the closing counter. A later task
increments that counter at 0x22; it queues destruction when the integer count
reaches five (the original comparison is against 4.5).

An already-open status window can begin this five-update closing phase
immediately. Equal opening tick increments, including the increment of two
used below, do not synchronize these different phases.

## Discriminating scalar controls and their limits

The controls assume follower-before-parent visits once per pass, destruction
enabled, a settled-open parent that receives `close()`, initially zero closing
counters, and equal opening increments of two. They exclude reopen, reparent,
pause/suspension, root teardown and intervening helper mutations. On its first
task the parent refresh closes and clears its follower pointer. These are
explicit scalar-model assumptions, not a claim that an external game event
reaches the paired states with all those conditions intact.

With a newly opening follower starting at tick zero, the model gives:

| Pass | Follower visit before parent | Parent visit |
| --- | --- | --- |
| 1 | Opening tick 2; borrowed read while parent exists | Refresh requests follower close; closing count 1 |
| 2 | Opening tick 4, close pending | Closing count 2 |
| 3 | Opening tick 6, close pending | Closing count 3 |
| 4 | Opening tick 8; switches to closing without incrementing its closing count | Closing count 4 |
| 5 | Closing count 1; borrowed read while parent exists | Closing count 5 queues parent |
| 6 | Closing count 2; borrowed read while parent exists | Queued parent is deleted without a task |
| 7 | Another borrowed read would need a still-valid parent | Parent is already absent in this model |

The same simplified schedule with an already-open follower instead queues
the follower during pass 6, before the parent is deleted later in that pass.
Its next visit deletes it without running its borrowed read. The contrast
identifies a necessary missing premise: five close requests do not by
themselves prove close-phase alignment or prevent later borrowed reads.

This is a scalar transition control, not an emulator or execution of a freed
read. It establishes neither a legitimate-session failure nor allocator reuse,
and does not exclude another teardown mechanism preventing pass 7. A safe
recovery still needs original evidence for the paired phase states, actual
close origin and scheduling, or an independent teardown rule that prevents
the unprotected visit. No guard, extended cleanup loop or new ownership is
inferred. All lifetime holds remain.

## Original-code qualification

The expanded control checks 36 compiled bodies and their function-relative
relocation targets against originals across 17 units. This includes the prior
34-function closure cohort plus the actual sort-key accessor and the client
opening-rate helper. All inspected source providers occur once and original
counterparts are absent. The prior complete-original reference census still
finds exactly two direct follower-constructor calls in icon refresh.

The inspected executable retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No source, configuration,
executable or coverage change is claimed, and no new native build is required
for this read-only control. Independent review confirms the timing contrast
and its conditional scope. The ComCard trailing-word and conversion-pool,
Word, CustomSelect and other previously documented holds remain unchanged.

## Actual close origins and the bounded full-teardown route

A subsequent read-only control starts at
`8797b57725f78855ad661ab1c38685b28048a3ba` on the same main. It identifies
two concrete controller-owned origins for a status close request:

- TWindowCtrlPlayer's destructor closes its status pointer at 0x30, then clears
  that pointer. This is the pointer populated by `create_status_window`.
- TWindowCtrl's destructor closes its three party windows at 0x78 through
  0x80, clears those pointers and queues tracked player controllers before
  its TObject child cleanup. Its constructor populates those party slots.

This identifies real original call sites rather than assuming an arbitrary
external close. It is not an exhaustive receiver/alias census of every close
or deletion operation.

Full `TMainTask::delete_layer_children` processes tl_00 first, tl_01 third and
tl_fadeafter last. TWindowCtrlMain's original constructor registers its TObject
under tl_fadeafter; the original vtable's destructor entry at table +8 resolves
to its actual destructor. That destructor saves the window root, clears its
global, deletes the subcontrollers, releases all six viewport-root pointers
and the shared instance, then deletes the saved root. TObject root destruction
recursively deletes registered windows synchronously; it does not wait for
their open/close counters.

Consequently, under normal destruction-enabled registration and no reentrant
task dispatch, this full-layer chain reaches the separately registered window
storage before a subsequent ordinary task traversal. When it completes
normally, the modeled seventh-pass follower task is excluded on this route.
The four inspected reload routes and returned phase-15 scene cleanup invoke
this full-layer helper. The original direct call order reaches deletion before
later explicit main-task updates; scene cleanup has no direct main-task update.
This extends the earlier controller-layer evidence to its actual window-root
manager. It does not prove every controller removal follows that route or
exclude transitive callback/reentrant processing within other helpers.

There is a separate destructor-access limit. Sorting can put a follower before
the status window during root deletion, while the status destructor still
calls `close()` through its first four nonnull icon pointers. The follower's
raw destructor does not visibly clear those owner slots. Destroying all siblings
therefore does not establish slot validity, safe destructor accesses or normal
completion of teardown. Excluding a later task visit is narrower than proving
the entire teardown safe. No reachable invalid access is asserted here, and
this observation does not authorize changing cleanup order or ownership.

The constructor's replacement guard is weaker: TWindowCtrl queues the previous
active controller if present, but does not itself delete the viewport roots.
A complete original-reference scan finds one direct TWindowCtrl-constructor
call, in `TLobby::create_tasks`, which constructs TWindowCtrlMain before it.
The manager has five direct constructor callers, including four other scene
initializers; it is not restricted to this game-task helper. Neither the
replacement guard nor that local construction sequence proves that every
replacement follows full teardown. The nearby `cleanup_game_objects` call
performs game-object/item setup and is not a substitute for window-root deletion.
Computed calls and all scene-table/session constraints are not excluded by
this relocation census.

The expanded original comparison now covers 46 bodies and their relative
relocation targets across 20 units, including both controller cleanup paths,
manager construction, full-layer deletion, task creation, the four reloads,
scene cleanup and the game-object helper. The 4,960-original-object reference
census separately checks the constructors and original manager destructor
table entry. All inspected source providers occur once with originals absent;
the DOL hash remains the one above. Independent review confirms the bounded
chain and the separate destructor-access caveat. This is documentation-only
evidence, with no new native build or hold clearance.

The subsequent [controller callback-order audit](window-controller-callback-order.md)
traces the separate shutdown helper to its two original scene-table entries.
Both pair shutdown with adjacent reverse-order root release, and both inspected
scene teardown callers first delete full layers. That bounded evidence does
not establish standalone shutdown, reentrant-callback safety or destructor-slot
validity.
