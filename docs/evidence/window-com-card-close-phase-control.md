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
