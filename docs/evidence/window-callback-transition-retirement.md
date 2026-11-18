# Character-transition callback retirement and replacement ordering

Read-only follow-up to `649f2d33584ca76177004c1b508330b0c6a704e9`.
This traces an actual callback owner/close origin rather than assuming that
calling Base close synchronously destroys a callback window. No behavior changes.

## Concrete owner replacement path

The 0x50-byte TUnk_804E0B28 transition task stores its callback window at +0x4C.
Its native constructor publishes itself to lbl_805D67E8 before creating the
status window and callback window. The callback target reloads that global,
returns when null and otherwise invokes the transition operation. It does not
capture a task pointer in the callback field.

A census of 5,061 available original split objects finds three named relocations
to this global: the constructor store, destructor clear and callback load. The
transition constructor has one direct caller, create_char_select_slot at
80264124. This helper first calls destroy_submenu, sets a float ordering field,
allocates 0x50 bytes and constructs/publishes the new transition when allocation
succeeds. destroy_submenu at 802640E4 queues its existing +0x20 task for destruction
and clears the slot; it does not invoke that task's destructor synchronously.
The ordering-field helper is a single float-field write, not a retirement wait.

The two named direct callers are MainMenu1P's vfunc_6 and vfunc_9. The former
requires the menu-open bit to be clear and a player to exist; the latter calls
the factory when close_active_submenu succeeds. That helper itself queues the
existing submenu and uses the saved menu-entry state to choose its return.
Neither inspected call site contains a direct wait for callback-window retirement.
This does not establish that a previous transition task, rather than some other
submenu kind, legitimately occupies +0x20 on every such call.

## Actual teardown and callback phase advancement

The transition destructor closes the stored callback (+0x4C), clears its slot,
closes/clears the status window (+0x48), unconditionally clears lbl_805D67E8, then
performs TObject cleanup and conditional deallocation. It does not compare the
global with its own address before clearing it.

The callback window is separately registered through Base's client-root producer,
not constructed as a TObject child of the transition task. Its task calls DD's
initialize_subwindow wrapper, which forwards to update_open_close, then updates
fade. Base close requests the closing phase and sets the auto-destruction flag.
In the inspected closing phase, the counter reaching five disallows ordinary
rendering and queues destruction. A later destruction-enabled TObject task visit
deletes a queued node rather than invoking its task. This is not a guarantee of
five elapsed frames: opening state, pause, root traversal and destruction-disable
state affect when those operations run.

Ordinary rendering checks the separate object DISALLOW_RENDER bit; deferred
rendering checks DEFER_RENDER and does not independently test DISALLOW_RENDER.
CallBack render invokes a non-null callback without checking the Base close flag.
Thus even the phase endpoint's ordinary-render disable is not by itself proof
that an already-deferred callback cannot run before deletion. This audit does
not establish that this window actually acquires a pending deferred-render bit.

## What is now constrained, and what is not

After the destructor's explicit global clear, provided no publication or mutation
occurs between that clear and the callback's global load, the null branch excludes
dereferencing the retired transition through this global even if its separately
registered window remains. Intervening TObject child cleanup is not assumed free
of reentrant publication.
This is a bounded no-republication result, not a captured-task ownership claim.

Replacement order remains material. Under the explicit condition that an old
transition is pending destruction when a new one publishes its pointer, the old
transition's later unconditional destructor clear would erase the new pointer.
Conversely, an old callback dispatched after new publication but before that clear
would use the new global, not its historical producer. Those consequences follow
from the inspected operations; no normal-game reachable failure, allocator reuse,
freed access or required change is claimed. In particular, this does not justify
adding an identity guard, synchronous delete, callback reset or extra render test.

The missing discriminator is now concrete: establish the old submenu's dynamic
type and the actual menu/task ordering at the two caller gates, including whether
it is retired before a new transition can publish, and whether a pending deferred
render can survive that ordering. The previously audited full-layer teardown is
not a substitute for this ordinary replacement path. All wider lifetime and
source-quality holds remain.

## Validation scope

Nine complete current compiled text sections match their original split text
bytes: MainMenu_80263B70 (2404), SubEquip_80263AB0 (192), UserSort (648),
ChrSelSlot (2332), MultiPlyChrSelect_802C6F88 (292), CallBack (572), DD_8024662C
(288), SubComCard_80244774 (7864) and TObject (6096). Original assembly establishes
the named call and store order used above. This is an overlapping audit cohort,
not nine newly recovered units. No fresh whole-object relocation equivalence or
new native build is claimed here. Source/configuration remain unchanged, and the
retained executable has original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

Independent review passes with the no-publication interval explicitly starting
at the global clear, not merely at destructor return. No lifetime hold is lifted.
