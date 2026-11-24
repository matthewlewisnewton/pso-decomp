# ComCard follower registration and cleanup boundary

The registration control follows continuation head
`efbf147af1948037ed7f468facb536a609999cf9`; the subsequent scheduled-close
control follows `87482aae0ba0372b7076c1a6a4dda687af173063`. Both include main
`d6fc686573510cc9612beb6a2d71576ad685301c`. It narrows the
[SimpleStatus five-slot qualification](window-status-family-lifetime.md)
without changing construction, cleanup, providers or behavior.

## Task parent versus borrowed window

The original follower constructor at 80249ED8 forwards its client argument to
Base. Both original allocation sites are in SimpleStatus's icon refresh and
pass that window's stored client. Base obtains its TObject parent through
TWindowCtrlMain__sub_8024CDB0 / TWindowCtrlMain__sub_8024CDD0: the selected
viewport root, or the common first root outside split screen. SimpleStatus's
own Base construction uses this same root-selection contract. PartyStatus
requires a qualification: it constructs Base using `local_client_id`, then
replaces its stored client halfword with the remote slot that its followers
receive. Its inspected controller producer runs only in the non-split branch,
where both selectors return the common first root. Shared-root equivalence
therefore relies on that stable routing, not identical client arguments for
every descendant or an assumption about later runtime mode changes.

The follower then stores the supplied SimpleStatus pointer at 0x60. This is
distinct from TObject's parent at 0x10. Its task reads the borrowed window's
saved y position through that pointer before its ordinary open/close update.
The inspected construction and depth-sorting paths do not replace the task
parent with the borrowed window; sorting rearranges siblings within the
existing parent's list. Thus the inspected, consistently routed construction
paths register the windows as siblings, rather than making the follower a
SimpleStatus descendant.

TObject destruction deletes its `m_down` children and removes the object from
its parent. That recursive mechanism therefore does not explain the fifth
follower's omission from SimpleStatus's four-slot destructor. Base's cleanup
destroys entry storage and adjusts window depth order; it does not traverse
the five icon pointers. `close()` requests the window transition and sets the
later-destruction flag; it is not immediate deletion. The existing refresh
path can populate slot 4 and has separate paths that close all five slots.

Full viewport-root release is a different operation that can destroy registered
siblings. Establishing its existence does not establish its timing relative to
every ordinary SimpleStatus removal or a follower task invocation. Likewise,
this bounded construction inspection does not exclude every later reparenting
path or prove a reachable dangling access. The original four-iteration cleanup
is preserved. No extra close, null guard, default initialization or new
ownership is inferred.

## Conditional ordinary scheduled closure

All three original task bodies, SimpleStatus (116 bytes), Status (108) and
PartyStatus (116), call icon refresh before `initialize_subwindow`, which
forwards to the open/close progression. A subsequent task that reaches refresh
with its `close()` state intact takes the refresh helper's all-five cleanup
branch. The original window-flag predicates give a bounded explanation:

| State seen by request_close | Effect relevant to icon availability |
| --- | --- |
| Mask 1 absent | It remains absent; mask 4 is cleared |
| Masks 1 and 2 present | Mask 4 is set |
| Mask 1 present, mask 2 absent | Mask 1 is cleared and mask 2 set |

`close()` also sets mask 0x10. The availability predicate returns false when
mask 1 is absent or mask 4 is present. Consequently every row reaches the
five-slot close-and-null branch before this task advances its own deletion
state, provided nothing reopens or otherwise changes the window first. A
bounded algebra control checks all 64 low-six-bit inputs; high bits do not
change this implication. These are window flags at 0x2C, distinct from
TObject's scheduling/deletion flags at offset 4.

This establishes a conditional explicit closure path for the fifth slot. It
does not establish synchronous follower destruction: the follower's own task
reads the borrowed window before advancing its closing state. Relative task
order, close-phase alignment and queued deletion therefore still matter.
Direct deletion, already queued deletion or suspension can also bypass a
normal parent task invocation. No unconditional lifetime safety, reachable
failure or cleanup-loop change follows from this control.

## Controls and remaining evidence

Twenty-five compiled functions across nine units reproduce their original
bodies and function-relative relocation targets: follower construction/task/
cleanup, SimpleStatus construction/cleanup/icon refresh, Base construction/
cleanup/layout initialization/position/depth/close progression, viewport-root
selection/release, controller cleanup and TObject construction/destruction/
traversal. A separate scan of all 4,960 currently configured original objects
and 249,768 relocations finds exactly the two direct, zero-addend REL24 calls
to the follower constructor, both in icon refresh. This relocation scan does
not exclude runtime-computed calls or subsequent task reparenting.

Each of the nine inspected source providers is selected once with its original
counterpart absent. The existing DOL retains SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. This is a read-only check of the
already validated executable, not a new native build or coverage gain.
Independent source review confirms the sibling/borrowed-pointer distinction
and these limits.

The scheduled-close follow-up extends the original-body/relative-target checks
to 34 functions across 15 units, adding all three status tasks, the two flag
predicates, PartyStatus's constructor/factory/controller routing and the player
controller destructor. All 15 source providers are selected once with original
counterparts absent. This follow-up remains read-only, retains the same DOL,
and has separate independent review; it changes no executable or provider.

A source-correct next step needs concrete original lifecycle evidence that
orders follower destruction, or otherwise prevents its borrowed reads, before
SimpleStatus ceases to be valid. That includes relative task order and close
phase alignment for ordinary scheduled closure, and root deletion, later
reparenting or explicit teardown for bypass paths. A demonstrated
problem would still require a separately justified behavior change; this
audit does not authorize extending the original loop. The follower's separate
native-constructor conversion-pool mismatch and the basic ComCard trailing-word
ownership/coverage hold remain unchanged. No prior constructor variant is
repeated or activated.

The subsequent [task-order and close-phase control](window-com-card-close-phase-control.md)
compares opening and already-open followers under explicit scalar scheduling
assumptions. It shows why five close requests alone are insufficient to prove
borrowed-parent lifetime, without claiming a reachable game failure.
Its subsequent actual-origin audit identifies controller destructor close sites
and the full-layer window-root teardown chain, while separately preserving
replacement, reentrant-dispatch and destructor-slot-validity qualifications.
