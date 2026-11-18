# Typed keyboard depth forwarding

This follows PR #268 checkpoint `f854351d1fac8b5b54daa29cae0a7acde7860792`.
The former get_lobby_field_20 helper is now the evidenced Control member
set_keyboard_depth(f32), returning void and forwarding to its composer through
the established Base set_depth(f32) declaration. This removes this helper's
false no-argument/integer-return view without expanding the wider setter scope.

## Receiver, float and result contract

Original all-section relocation inspection finds exactly two direct calls to
80131A80, with no observed address-taking. Both occur in MakeTeam's keyboard
setup paths. Each receiver comes from a 0x2C allocation initialized by
TKeyBoardControl__ct, and field 0x20 contains the previously constructed composer.
The helper's actual owner is Control rather than the surrounding MakeTeam object.

Both original calls load lbl_805DD144 into f1 immediately before the call and
overwrite r3 afterward. The observed protocol is a receiver plus a float input
with no consumed result. The shared Base definition/declaration is already
void set_depth(f32): it writes the float at 0x1C and reorders the window. The
typed wrapper now forwards its declared float directly to that existing method
on the composer. Both caller declarations/calls agree with the actual member.
No unexplained live float argument remains in this wrapper. Unique original
source spelling or return-type spelling is not inferred from the matching code.

The original setup sequence and null/allocation-failure behavior are unchanged.
The neighboring void flag wrapper is unchanged. No resource or lifetime moves to
Control, and no compatibility body or alternate ABI export is introduced. Other
legacy set_depth views, outer keyboard wrappers and broader renderer interfaces
remain qualified; the shared Base implementation is not modified here.

## Complete object and link verification

The forwarder's 36 bytes and the preceding flag wrapper's 36 bytes independently
match their original bodies. The complete 72-byte owner and 1188-byte caller texts
match captured f854 source and fresh main originals, including every resolved
text/data target. Both source objects remain actual executable inputs once, with
their original text counterparts absent. Allocated-section inventories are
unchanged. The caller's entire 48-byte anonymous jump table and all its targets
remain exact. There is no table emission, data/range/split/padding change or new
compiler control/technical exception.

The shared-gate full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against f854 passes with
zero metric delta and one catalog rename. Retention stays clean at 17,870 with
no generated changes, and the port inventory passes unchanged.

Main `4618606af4bec0db175a176d9fadabd098936a04` is integrated by merge
`c198b6170024ca45b3441e7508ae338ed71cc1a9`. It changes only the progress README
relative to the separately built/validated 6dfba15dc7 baseline; all compiler and
link inputs are identical. Both isolated builds and hashes pass after the update.
Fresh-main check_pr passes with combined +600 matched code, +1220 linked code,
+1496 matched data and +1452 linked data bytes. Totals remain 27,400 exact
functions, 3,584 exact linked units and 3,643 source-bearing units.

The previous status/flag bodies remain exact under their recovered names.
Snapshot, WS_Word and protected-original provenance pass again, including the
original1044 helper and WS_Word's original3412 provider/missing916 rendering body.
Raw Base/Addition calls remain 22 across 12 units. Other constructor/destructor,
table, capture, constant, renderer and interface holds remain; PR stays draft.
