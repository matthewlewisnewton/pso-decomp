# Ordinary render receiver forwarding and mode compatibility

Evidence-only follow-up at `3d478780f5e09d2ff99029e67c5f434e30006e3f`.

## Actual receivers, not the placeholder declarations

Original ClipOut::render at 8024C8A4 first tests is_window_display_enabled. After
render-state setup it calls selector 8024CE34 at 8024C8C8, immediately followed
by render_nodes at 8024C8CC. The selector loads the root pointer from
viewport_states+0x70 into r3; no instruction replaces that returned r3 between
the calls. With record stride 0x1C this is slot 4. The no-argument C alias in
current source does not describe the native receiver: it is the selected root,
not the ClipOut object's this pointer.

Screen::render similarly tests display enablement, renders the global window
instance, obtains a viewport player index and calls selector 8024CDD0 at
8024CAAC followed immediately by render_nodes at 8024CAB0. Again returned r3 is
the root receiver. Unlike the fixed ClipOut selector, CDD0 chooses slot 0 outside
split screen and the supplied player index in split screen. Equality with slot 4
in split screen depends on that actual index; it is not established by an array
size or by the camera-index loop alone.

## Construction and activation conditions

CtrlMain constructs the screen controller under tl_window and ClipOut under
tl_clipout when their global instances are null and allocations succeed. There
is no split-screen guard around those construction blocks. Their existence is
therefore not proof of a shared callback receiver in a particular mode.
TMainTask::render_ui explicitly allows/traverses tl_window;
render_clipout_and_fade allows/traverses tl_clipout. Descendant DISALLOW_RENDER
and the controllers' display-enabled check still apply. This establishes named
ordinary dispatch paths, not a guaranteed pair of invocations in every frame.

The known transition producer has an important extra condition. CtrlPlayer
constructs MainMenu1P in the non-split branch; split mode constructs MainMenu4P.
The previously traced transition factory's named callers are MainMenu1P methods.
Its callback constructor passes client 4 into Base's mode-sensitive root selector.
For that constructor-established 1P lifecycle with unchanged non-split mode,
client 4 still selects root 0. Screen selects root 0 in that mode too, whereas
ClipOut selects root 4. Thus the known transition callback has an ordinary Screen
root path, but shared ClipOut slot-4 dispatch is not proved for that lifecycle.

A callback actually constructed in split mode selects root 4 and is in ClipOut's
constructor-established tree, subject to ordinary render/activation conditions.
That conditional is not proof that this particular transition is constructed in
split mode. Mode changes across construction, alternate producers, root aliases,
reparenting and retained objects across reinitialization remain separate evidence
gaps. Changing mode also does not by itself reparent an existing callback.

## Consequence and limits

This supplies an ordinary-render path missing from a purely deferred-root audit,
without reviving a global deferred scan assumption. It does not establish duplicate
rendering, a reachable lifetime defect, all phase interleavings, or readiness.
The no-argument forwarding boundary is real source-ABI debt, but changing it
requires receiver-aware source recovery and full approved validation; no production
change is made from this register observation alone.

The useful next discriminator is a non-protocol mode-transition or alternate
callback producer that establishes the mode at creation and subsequent root
identity. Without that positive evidence, do not infer shared-mode reachability
from client 4 and fixed root 4 alone. No protocol caller was inspected here.

## Validation scope

Original/retained compiled full .text sections remain equal for CtrlMain (1528
bytes), CtrlMain_8024C820 (2888), CtrlPlayer (584), and TObject (6096). The native
instruction anchors above establish forwarding; equality is not a new native
build, relocation comparison, runtime render test or integrated-main validation.
Production source, callback ABI and all readiness holds are unchanged.

Independent read-only review passed native r3 forwarding, construction/layer
paths and the non-split lifecycle qualification. No source-quality hold lifted.
