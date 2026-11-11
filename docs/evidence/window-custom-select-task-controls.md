# CustomSelect task-root and teardown controls

This continues the [player-lifecycle audit](window-custom-select-player-lifecycle.md)
at continuation `31a6b55de75b3f061265974fa7bfc0441fb5d84e`, on main
`5bba9c44adebc1cfa019def85e1f39f6da340ef0`. Current refs and the isolated
worktree were unchanged when this investigation began. No game source,
constructor, allocator, compiler setting or behavior is changed.

## Two scheduling paths, resolved from original calls

The active WindowCtrl's observed constructor caller loads `tl_00` into the
parent register immediately before construction. The original callee forwards
that register unchanged to TObject construction. The customize controller is
under this WindowCtrl / CtrlPlayer / MainMenu tree.

CustomSelect's native Base chain instead selects the per-viewport window root
through the existing CDB0 / CDD0 helpers. Main window-control construction creates
that subtree beneath a root with no TObject parent. Its explicit traversal is
called by `TWindowCtrlSub::run_task`, whose producer passes `tl_01` as parent.
Thus the controller and popup use distinct traversal paths; neither is proved
suspended merely by changing the `tl_window` task layer.

This is original register/load/call evidence, not a newly inferred portable ABI
for the remaining raw constructors, viewport views or callback interfaces.

## Contrasting real helper scopes

The controls compare original routines and their actual receiver loads, rather
than simulate an invented game state:

| Original routine | Observed scope/order | What it establishes |
| --- | --- | --- |
| `delete_layer_children` | Calls deletion on tl_00, tl_camera and tl_01 before tl_03 | Full layer cleanup removes the controller/subcontroller layers before the player layer; this is one ordered teardown path |
| `toggle_pause_layers` | Includes both tl_00 and tl_01 | This routine reaches the relevant controller roots |
| `toggle_pause_game_layers` | Includes tl_03 and tl_window, excludes tl_00 and tl_01 | Calling the narrower helper does not itself change either controller-root pause bit |
| `resume_game_layers` | Likewise excludes tl_00 and tl_01 | Its name is not proof of the state of those roots |

A toggle can pause or resume depending on the prior flag. The original TObject
traversal also has a child-queue cleanup branch that invokes a node's task before
checking its suspend/pause bits. These routines' names or mere invocation cannot
substitute for the actual flags and path at the removal boundary. No universal
pause guarantee follows from the table.

## The post-rebuild callback is not teardown

`TLobby__sub_801B09A4` destroys and recreates saved player slots synchronously,
then calls `TLobby__sub_8024AC20` for the recreated client. The latter's original
12-byte member-pointer record at 804CEA58 has zero receiver adjustment,
nonvirtual selector -1 and target 8024C6FC. The dispatcher obtains the active
controller's client slot, then invokes that leaf.

The leaf clears mask 0x2 in the halfword at receiver offset 0x1C. It does not
write TObject's task flags at offset 4, delete children or call a pause/destruction
helper. The callback therefore does not establish that MainMenu or the pending
customize controller was suspended or torn down. This identifies the observed
operation without inventing a semantic name or clearing the existing PMF/type
qualification.

## Removal and fade paths are not failure demonstrations

The existing same-slot registration path deletes an old player and assigns its
replacement within one synchronous operation. The saved-slot rebuild similarly
attempts recreation of each previously present slot before returning. These
transient null intervals are not by themselves task-interleaving counterexamples.
The recreation source dereferences its allocation result; allocation failure is
not evidence of a clean return with an absent local player.

`apply_char_to_players` can skip recreation when selection/data is absent, but
the inspected `reload_offline_area` path calls full layer cleanup before any
explicit subsequent normal-task traversal. Its original direct-call sequence
has no main-task/run-tasks call between player rebuilding and that cleanup.
Nested helper effects are not exhaustively established. This path is not cited
as a reachable CustomSelect failure.

The inspected battle fade-entry paths install callbacks that invoke the saved-
slot rebuild. Fade setup and callback execution only establish fade state and
callback invocation. The inspected preceding cleanup targets map/effect layers
and floor items, not tl_00/tl_01. Indirect quest, audio and other phase effects
remain unproved. Visual fade alone is therefore not a suspension invariant;
neither does this bounded trace prove the menu remains runnable in that phase.

## Verification and remaining proof

Twenty-two additional individual production functions compare exactly with
original body bytes and function-relative resolved targets. The original-object
controls additionally verify receiver loads/call order for the layer helpers,
parent-register forwarding, the explicit popup traversal, and the PMF record,
relocation and 16-byte leaf operation. Earlier nineteen-function evidence is
retained separately. Private controls/receipts are in
`pr403-customselect-scheduling/`; original objects and raw instructions are not
published. These are static controls, not game execution or emulation.

Only evidence documentation changes. The validated production report, Ninja graph
and original DOL remain byte-identical; no new full-build result is claimed.
Independent review and whitespace checks qualify publication.

The hold remains: prove that a menu-owning local/split-screen client cannot lose
its valid player before the controller's next construction/use invocation, or
prove the relevant tl_00/tl_01/root teardown/suspension ordering at every applicable
removal path. Arbitrary remote-player removal is not enough to establish a local
UI failure. Current evidence proves neither a reachable failure nor universal
safety. Presumed zeroed heap, visual fade, the post-rebuild callback and the wrong
layer's pause bit do not fill the gap. Word, ComCard, balloon, Parts provenance,
opaque ownership and all other standing holds remain intact.
