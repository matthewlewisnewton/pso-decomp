# Mode selector writes versus window teardown

Evidence-only follow-up at d12613baeb2d3ea2c8d84a702609f30407fb2416.
No lifetime hold is discharged by this census.

## The value is not a Boolean

Original is_split_screen at 80019690 reads camera_split_screen_selector
(805D34B8) and computes value != 1. Its initial data word is 1. Zero therefore
selects the split branch too; it cannot be treated as a cleared/disabled mode.
The adjacent zero word in the original eight-byte data object is not a second
proven mode field.

Named original assembly references expose two store sites: 801A3B90 stores
incoming r3, and 801A3B98/9C writes 1. The former has two named direct callers
in enable_camera and free_sub_ctrls; the latter has a named direct call in
teardown_scene. This is a symbol-reference census, not exclusion of raw-address
writes, aliases, indirect calls, or initialization outside these units.

The current free_sub_ctrls member spelling is misleading as semantic evidence:
801A2FBC preserves incoming r3 in r31, 2FC0 forwards it to the selector store,
and 2FC4/2FC8 forwards the same value to the camera-count setter. In the concrete
local mode initializer 802C478C, phase 0xE and selected mode 1 lead to
802C6558 at 47C8 then free_sub_ctrls at 47CC with the returned r3 unchanged.
802C6558 counts four entries of data_804E0A48 whose values are not -1 and returns
that count (0..4). Thus this route passes an integer count, not an object pointer.
Mode 0 or a different main phase uses enable_camera, which explicitly writes 1;
other selected-mode values within phase 0xE perform neither branch. Availability
of the count route does not establish that every count is a reachable UI state.

## Concrete offline callback ordering

The original offline_game_scene_callbacks table at 804C1F68 contains eight-byte
init/cleanup pairs. Pair 0 is 802C478C / call_enable_camera; pair 9 is
reset wrapper 8024D838 / free_all_windows. run_load_callback_table at 800FD6F8
walks first words forward, eight bytes per pair, with an area-transfer-pending
abort before each callback. The offline setup call at 801A3A3C supplies size
0x180. If it reaches pair 9, the mode initializer has already run, then reset_all
runs. This is initialization ordering, not proof that an old window tree was
freed beforehand.

Reverse cleanup at 800FD6A0 loads the second word of each pair from the end,
steps backward eight bytes and skips null callbacks. The offline teardown call
at 801A35A8 supplies the same table and size. If callbacks return normally,
free_all_windows (pair 9) precedes the table's enable_camera (pair 0).

Crucially, teardown_scene itself has earlier explicit selector resets:
801A355C calls the write-1 routine and 801A3560 calls enable_camera, before
layer deletion at 801A3578 and the reverse callback walk at 801A35A8. Therefore
it is false that every selector change must wait for free_all_windows. These
are writes toward non-split mode, however; they do not demonstrate an existing
1P transition being retained while switching from value 1 to split mode.
Intervening calls and callbacks are not proved non-reentrant by this note.

## Pointer clearing is not destruction

reset_all at 8024D7C0 performs initialization calls, zeroes the published window
root/controllers/instance at 7F0..804, and initializes six viewport records. That
is not an explicit deletion of the previous tree. In contrast free_all_windows
saves the old root in r29 at 6A8 before clearing its published pointer at 6B0;
it invokes controller destructors, releases six viewport records at 740..750,
destroys the global instance, then invokes the retained root's destructor at
7A0 before keyboard cleanup. Neither pointer clearing nor a reset name alone
establishes callback retirement.

## What remains open

No supported local path preserving the known 1P transition across a 1-to-split
mode change is established here. Nor is its impossibility established. The
positive split writer is an initialization callback; tying it to a surviving
old object requires an actual caller lifecycle, abort/reentry behavior and
retained parent ancestry, not just mode-setter reachability. Dynamically resolved
writers and raw aliases remain outside this census. No protocol or TradeSession
caller bodies were analyzed. No production source, native build, checker,
readiness or merge state was changed.

Original assembly and current source were inspected. Retained original versus
compiled .text equality was separately checked for the two small setter/caller
units and TWindowCtrlMain; this is not a fresh native build or whole-program
validation.
