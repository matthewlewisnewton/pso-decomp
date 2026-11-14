# Menu replacement gate discriminator

Read-only source follow-up at `cf4e153ecb108cace713a37f78ed9a9f1cca8438`.
This is a separate bounded evidence checkpoint, not clearance of the callback
lifetime hold or a new native build.

## Fresh integration check

A literal remote query and fetch found main at
`1bb11b184a5c70c03062b4cfa26d7863b4ce1cec` and the PR branch at the head above.
`git merge-tree --write-tree HEAD FETCH_HEAD` returned successfully, without
conflict entries, with tree `b5abfa529a616147072ac048390f207c34b716f8`.
No working tree/index integration was made. This establishes textual mergeability
for those pins only, not source compatibility or build correctness. In particular,
no rejected current-main compiler graph route was retried.

## Stronger distinction between menu states

`TWindowMainMenu::handle_menu_selection` runs only with the open bit set, the
submenu-active bit clear, and a non-null menu. A selected terminal entry calls
`create_submenu(id)` after closing the description and updating the menu.
`create_submenu` sets the submenu-active bit, queues and clears the old +0x20
object, and creates the selected submenu. Its listed constructors are distinct
from the transition constructor. Unsupported selectors leave the slot cleared.
The transition factory is therefore not the only writer of this slot, and when +0x20 contains the transition, a supported terminal-selection path queues
it and, on successful allocation, installs a different submenu type.

`MainMenu1P::vfunc_9` calls `close_active_submenu`, which queues/clears +0x20
before testing saved menu state. Only its nonzero result creates a new transition.
This does NOT yet prove that every virtual call to this gate comes from an active
non-transition submenu. Its entry does not itself test the old dynamic type.
`vfunc_6` requires the open bit clear and a player present, then opens the menu and
creates a transition. Its entry similarly does not establish that no older queued
transition remains elsewhere in the child chain.

Thus proving the typical state cycle alone is insufficient: the required
invariant concerns every path reaching these gates, including calls during a
child's task and close/reopen intervals, not just what occupies +0x20 now.

## Scheduler fact and remaining discriminator

`TObject::run_tasks` caches a child's next pointer before invoking its task. On
the normal allowed-update branch it calls that node's task and then its child
traversal. A queue request is consumed on a later applicable visit to the queued
node; it is not a synchronous destructor call. `MainMenu1P::run_task` executes
selection handling before returning to that enclosing traversal. These facts make
the location of the virtual gate call within traversal essential: a parent-task
replacement and a child-task return must not be modeled as interchangeable.

`TWindowCtrlSub::run_task` traverses the window-task root. Screen rendering
separately traverses the global window instance and selected viewport root.
The inspected `TMainTask::render_objects` deferred pass starts at tl_03 and tl_04,
not a direct named window root. This does not prove that a callback is unreachable
from all deferred traversals: root ancestry, reparenting and other callers still
need evidence. The prior conditional deferred-render concern remains conditional.

Next discriminating step: enumerate the virtual slot callers corresponding to
MainMenu1P::vfunc_9 and the menu reopen gate, establish their receiver/parent types
and whether they execute before or inside the submenu child traversal, then carry
the queued-transition generation through that order. A negative direct-symbol
search is insufficient because these are virtual calls. If all supported paths
retire the previous transition before publication, that can retire the specific
replacement-overlap scenario without introducing a behavior-changing guard.
Otherwise preserve the observed original behavior and document its reachable
preconditions; do not invent a repair in this matching branch.

No production source, build metadata, readiness state, or lifetime hold changed.

## Inspection anchors and review

Original split assembly anchors: handle_menu_selection 802647CC (terminal
create_submenu call at 802648A0), create_submenu 8026417C, MainMenu1P vfunc_9
802883EC, vfunc_6 80288490, TObject::run_tasks 8022A8DC. Matching source paths
are MainMenu.cpp, MainMenu_80263B70.cpp, UserSort.cpp and object/TObject.cpp.
The scheduler/root observations additionally use MainMenu1P.cpp and
TWindowCtrlMain_8024C820.cpp. These are inspection anchors, not a fresh
whole-object equivalence claim. Independent read-only review passed after
qualifying the terminal-selection statement by incoming type and allocation
success. The retained executable SHA-1 remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; no new build was run.
