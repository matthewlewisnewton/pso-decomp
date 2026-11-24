# Deferred-pass ancestry for the transition callback window

Evidence-only follow-up at `74ae24db073cb45ae5a38cd540a941e6d266447b`.
This constrains the earlier conditional deferred-render concern using actual
registration, rather than assuming every flagged TObject is globally scanned.

## Constructor-established callback tree

The transition owner creates its callback through the previously traced factory.
The callback is not a child of that owner: CallBack constructs Base with client 4,
and Base obtains its TObject parent from sub_8024CDB0/sub_8024CDD0. The selector
returns viewport root 0 outside split screen and the client-indexed root (4 here)
in split screen. The six viewport records use stride 0x1C and store root at +0.

TWindowCtrlMain creates window_task_root as a separate TObject with NULL parent
(original 8024D56C–8024D570). It creates each viewport root with that window root
as parent (8024D5D4–8024D5D8), then stores each record's root at 8024D5E4. The
ordinary global window instance is another child of this window root. These
statements require successful allocations and the constructor-established root
identities; an existing nonzero global root is not freshly reconstructed.

The screen controller attaches under tl_window; the task subcontroller attaches
under tl_01. Their explicit calls into the detached window tree establish work
and render dispatch, not a TObject parent-child link from those controller
objects to the detached roots. The main TWindowCtrlMain object itself attaches
under tl_fadeafter, also distinct from the separately allocated root.

## What the inspected deferred pass actually traverses

TMainTask initialization creates layer objects, including tl_03/tl_04, as its
children. The named deferred pass at 80229A00 and 80229A08 invokes
render_deferred_nodes on those two layer roots. That routine iterates children,
conditionally renders flagged children, and recursively visits their children.
It neither follows each node's parent link nor globally scans every allocated
object. Setting DEFER_RENDER changes a flag, not parent registration.

For the constructor-established, unchanged tree above, the callback window is
not a descendant of tl_03 or tl_04. Thus merely retaining a pending deferred flag
on that callback cannot make this static descendant traversal visit it. This is
a narrower, positive exclusion than the earlier statement that the routine does
not independently check DISALLOW_RENDER. The flag-check observation remains
true, but it alone is not evidence that this callback participates in that pass.

## Explicit exclusions

This does not prove absence of reparenting, root/global replacement or aliases,
raw child-link mutation, direct/indirect invocation of callback render, a virtual
render implementation that dispatches into another tree, or other runtime entry
points. It does not settle ordinary window rendering, lifetime between close and
deletion, later singleton publication, or all transition-owner ancestry. No
whole-program reachability or lifetime hold is cleared. Neither extra guards nor
a change to deferred rendering is justified by this finding.

Next discriminator, if pursued, should seek a concrete setter/reparenting or
cross-tree render dispatcher with the callback or window root as its receiver.
A negative function-name search is not a substitute for that receiver evidence.
No protocol callers or protocol content were examined in this pass.

## Validation

Retained original/compiled full .text equality passes for CtrlMain (1528 bytes),
CtrlMain_8024C820 (2888), CallBack (572), DD_8024662C (288), TObject (6096).
This is not a fresh build, complete relocation comparison or current-main
integration check. The separate static ancestry model passes non-split and
split-client paths and a sensitivity case showing reparenting defeats the result.
It is not a game execution or render-interleaving model. Production files and
existing source-quality holds remain unchanged.

Independent read-only review passed the original constructor/root selection,
controller dispatch distinction, conditional graph exclusion and all three model
checks. The retained executable still has original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No lifetime hold was lifted.
