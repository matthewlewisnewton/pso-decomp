# ComCard follower registration and cleanup boundary

This read-only control follows continuation head
`efbf147af1948037ed7f468facb536a609999cf9`, including main
`d6fc686573510cc9612beb6a2d71576ad685301c`. It narrows the
[SimpleStatus five-slot qualification](window-status-family-lifetime.md)
without changing construction, cleanup, providers or behavior.

## Task parent versus borrowed window

The original follower constructor at 80249ED8 forwards its client argument to
Base. Both original allocation sites are in SimpleStatus's icon refresh and
pass that window's stored client. Base obtains its TObject parent through
TWindowCtrlMain__sub_8024CDB0 / TWindowCtrlMain__sub_8024CDD0: the selected
viewport root, or the common first root outside split screen. SimpleStatus's
own Base construction uses this same root-selection contract.

The follower then stores the supplied SimpleStatus pointer at 0x60. This is
distinct from TObject's parent at 0x10. Its task reads the borrowed window's
saved y position through that pointer before its ordinary open/close update.
The inspected construction and depth-sorting paths do not replace the task
parent with the borrowed window; sorting rearranges siblings within the
existing parent's list. Thus these construction paths register the windows as
siblings, rather than making the follower a SimpleStatus descendant.

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

A source-correct next step needs concrete original lifecycle evidence that
orders all relevant root deletion, later reparenting or explicit follower
closure before the borrowed SimpleStatus ceases to be valid. A demonstrated
problem would still require a separately justified behavior change; this
audit does not authorize extending the original loop. The follower's separate
native-constructor conversion-pool mismatch and the basic ComCard trailing-word
ownership/coverage hold remain unchanged. No prior constructor variant is
repeated or activated.
