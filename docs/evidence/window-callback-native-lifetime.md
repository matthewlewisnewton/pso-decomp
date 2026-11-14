# CallBack native lifetime and retained callback boundary

This follows PR #268 checkpoint `f79fc8e17fb2ae3ab41a8b891c4545ee8b9e6748`.
The 0x64-byte CallBack window now uses one Base-derived declaration, a native
constructor/destructor and an ordinary-new factory. Its descriptor and compiler
table add 44 matched and linked data bytes. Mixed callback signatures remain a
separate hold.

## Native construction and actual producer

The conflicting flat local class is removed. The shared class retains Base's
0x60-byte image and the existing four-byte callback field. Its constructor takes
the observed two byte pointers and signed-word callback transport. It initializes
Base with the existing descriptor and client 4, sets the name, copies the second
input into fields 0x38/0x3C, saves position, then calls the unchanged word setter
at 802ACDA8. The copy helper's historical receiver view remains qualified.

The constructor at 802ACE84 is byte-exact at 128 bytes. The empty native
destructor automatically calls Base cleanup and reproduces all 88 original bytes,
including the compiler's deleting protocol. The 52-byte task now defines the
actual native member. The 72-byte render body is unchanged.

All-section original inspection finds one direct constructor caller: the
88-byte factory at 802ACF04, which allocates 0x64 bytes. It now uses ordinary
`new TWindowCallBack`; complete instructions, allocation guard, argument order
and result behavior remain exact. There are six direct factory calls from
SubSymbolChat, Agreement, Ep3Exist, SerialAccess, its 8032AD30 unit and PlyStatus.
There is no constructor/factory address-taking or other-section reference.
The factory's existing three-void-pointer interface and all six outer calls
remain unchanged.

## Callback qualification is preserved

The field's existing local invocation view,
`void (*)(TWindowCallBack *, s32)`, moves unchanged into the shared declaration.
It is explicitly documented as a legacy view. The existing setter and factory
still transport the callback as a word; no new conversion, adapter or common
portable callback interface is introduced.

The producers include no-argument functions, differing-argument views and a
dynamic callback path. This change does not prove their complete compatibility.
Render retains its pointer-null test and existing call with window/context.
The initial probe's newly introduced integer field changed that comparison;
preserving the prior pointer field type avoids that unnecessary source change.
Native window lifetime is recovered independently of the unresolved invocation
boundary. No ownership is assigned to the borrowed callback.

## Descriptor, table and unknown original word

The existing WindowLayoutDescriptor view represents exactly the observed
20 bytes: two zero floats, order 50045.0f, a null entry pointer and flags 0x23.
Defining it adjacent to the native class naturally emits the descriptor followed
by the 24-byte compiler table, at offset 20 within a 44-byte data section.
There is no placement control, hand-written table, extra virtual slot or padding.
All four table targets match original: destructor, task, render and TObject's
shadow method.

The old catalog's 28-byte table included an additional zero word at 804DE38C,
without a function relocation. The native claim stops at that address. That word
is retained as raw original data under an address-based label and explicit
original-only range [804DE38C,804DE390). It has no source definition, class owner
or asserted original translation-unit identity. The split tool otherwise omits
the zero auto-gap; this explicit range preserves it rather than treating it as
padding. No coverage waiver is used.

The old 384-byte original provider is accounted for completely:

| Range | Bytes | Provider |
| --- | ---: | --- |
| 804DE210..804DE360 | 336 | Original Boss table prefix |
| 804DE360..804DE38C | 44 | Native descriptor and compiler table |
| 804DE38C..804DE390 | 4 | Explicit original unknown-word remainder |

Both original ranges are selected exactly once with unchanged bytes and resolved
targets; the unknown word links at 804DE38C. The original name-pointer provider
at 805D3E58 is also retained once. No neighboring data range is absorbed.

## Whole objects and executable validation

The complete 572-byte owner text and 88-byte factory text match original bytes
and every resolved relocation target. Each source object is selected once.
The new data's full 44 bytes and all four slot targets match the original slice.
The native constructor catalog uses its actual `s32`/signed-long mangling;
no parameter type is changed to influence output.

The capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr` passes against published
f79 with +44 matched/linked data bytes, one catalog rename and no lost function,
code, data, total coverage or linked address. The comparison against separately
built main `4bec40d6cca74a85e91c848ea2d9f25425a313ad` also passes. No new gap
is added. Retention is clean at 17,900 and port inventory passes.

Raw Base/Addition calls fall from 22 across twelve units to 20 across eleven,
with the same four shared bindings. Totals remain 27,406 exact functions,
3,587 exact linked units and 3,641 source-bearing units. Combined PR deltas
against fresh main are +600 matched code, +1220 linked code, +1540 matched data
and +1496 linked data bytes. Callback/copy interfaces, remaining lifetimes,
ChoiceSetting/global ownership, constants, Word/nameplate original-provider
holds and protected remainders persist. The PR remains draft.

## Dynamic wrapper result correction (52dba159 follow-up)

The callback producer at 802ACF5C previously had a `void` source return despite
forwarding the factory result unchanged in r3. The original wrapper saves its
incoming callback word, obtains both zero vectors, calls the existing factory,
then restores only r30/r31, link register and stack. Its epilogue does not alter
r3. The source now explicitly returns the factory's existing `void*` result;
the signed-word callback parameter and exported mangling remain unchanged.

Two inspected producer chains consume this result as a window handle:

- Character-select transition construction stores r3 at +0x4C immediately after
  the call at 802C72F4. Its destructor reads that slot, calls Base close and
  clears it before closing the status window and clearing lbl_805D67E8.
- SubSymbolChat construction stores the result at +0x5C. Its destructor closes
  that stored window, clears the slot and then clears the singleton.

The registered transition callback at 802C6FB0 obtains its receiver from
lbl_805D67E8, not the callback window argument. The SubSymbolChat callback at
80281814 similarly obtains its receiver from TWindowSubSymbolChat__instance.
Both test their global for null. This establishes two concrete global-mediated
borrowed callback chains, not a guarantee of every reentrant destruction order
or a common portable callback signature. The existing outer caller declarations
and invocation contracts remain held and are not rewritten by this correction.

Independent source review confirmed the original return and both stored-handle
uses. The capacity-gated native full build passed, retaining DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The complete rebuilt wrapper object is
byte-identical to its captured 52dba159 object, including relocations and symbol
metadata. No table, data range, ownership, callback arguments or lifetime order
changes. This is a source-return correction with no match gain, not clearance
of the wider callback or keyboard holds. A native rebuild of the prior-head sources provided a fresh comparison baseline;
all 3,655 source-object files have identical SHA-256 inventories after restoring
the correction. The 347-test suite and linked-unit exactness check pass.
No fresh-main delta result is claimed for this pass.

## Explicit borrowed frame arguments (aa2d396773 follow-up)

Three already-two-argument callback implementations previously called a raw
`draw_window_frame` declaration with missing arguments: serial draw_screen at
803212F8 and password callback 8032AC9C supplied neither argument, while player
status callback 8033F3D8 supplied only the receiver. Their original first frame
calls at 8032130C, 8032ACB0 and 8033F3F4 preserve incoming r3/r4. Saving r4 to r31
in the serial/password prologues does not consume or replace the live r4 value.
The frame implementation at 80245F98 uses both the Base window and the second
argument's rectangle/color fields. These were real source-contract omissions,
not an instruction-byte difference.

Each call now uses the existing `TWindowBase::draw_window_frame(void*)` member,
with arg0 as receiver and arg1 as the borrowed frame context. The callback
window is Base-derived; render at 802ACDA8 loads its callback, passes the window
in r3 and draw_default_entry's result in r4. The three existing registrations
and all callback entry signatures remain unchanged. This does not change frame
context ownership, callback storage or deletion order, nor establish a portable
common callback signature. In particular, Agreement's no-argument callback and
other mixed producer declarations are outside this correction and remain held.

The native capacity-gated full build preserves the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,655 source-object SHA-256 entries
are identical to the captured aa2d396773 inventory, including the complete three
changed units and their symbol/relocation records. No original-provider,
compiler-profile, layout, coverage or ownership change is introduced.
Independent original-assembly review confirms the three incoming-register paths,
the callee's use of both values and the factory registrations. Address-based
check_pr against the captured aa2d396773 report passes with zero regression.

The 347-test repository suite also passes. Broader holds remain unchanged.

## Agreement entry and registration contract (e778094702 follow-up)

Agreement's callback at 803296E8 was separately traced rather than assumed to
share the preceding three source contracts. Its prologue saves floating-point
and nonvolatile registers without replacing incoming r3/r4, then calls the
frame member at 80329718. That callee reads both its window receiver and frame
context. The existing no-argument callback and no-argument raw frame declaration
therefore omitted values actually consumed by the original execution path.

A scan of 5,061 available original split objects found only the callback's
zero-addend HA/LO address references, both in Agreement's own registration at
80329808/80329818. The registration passes this address as the third factory
argument at 8032981C; the existing factory stores it in the Base-derived callback
window. Its renderer passes that window in r3 and draw_default_entry's result
in r4. No alternate direct reference appeared in this original-object census;
computed callers, external aliases and future registrations are not excluded.

The genuine static member now explicitly accepts window/context pointers and
calls the existing Base frame member with them. Its native mangling is recorded
in the symbol catalog and retention entry; no adapter, asm alias, forced slot,
new parameter width, callback dispatch change or assumed source-name provenance
is introduced. Registration still uses the member's address. The callback's
body, frame behavior and text-rendering order are unchanged. Its static class
placement is retained, not presented as original-source identity evidence.

The capacity-gated native full build passes with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Only the Agreement object changes in
the 3,655-file compiled-source inventory. Its complete non-string sections,
relocation records and ordered symbol metadata agree after normalizing the one
native export rename; ELF string offsets/file positions are not claimed raw
identical. All other 3,654 source objects are raw-identical. The qualified common
callback field type, no-argument global-mediated callbacks, remaining interface
and lifetime holds remain outside this narrow entry-contract correction.
Independent original-assembly/source review passes. check_pr against the captured
e778094702 report passes with zero metric loss and the single catalog rename;
the 347-test repository suite passes. This is not a ready-for-review claim.

## Ep3 callback receiver correction (0e9dee826 follow-up)

The Ep3 entry at 8036EFBC was modeled as a nonstatic TAdEp3Exist member taking
a signed word, registered through a hand-mangled no-argument C declaration.
Its actual factory registration supplies an ordinary callback address, and the
callback renderer supplies its own Base-derived window in r3, not an Ep3 task.
The entry's prologue leaves r3/r4 unchanged for the frame call at 8036EFD0; no
Ep3 task field is read. This distinct wrong-receiver contract was checked
independently of Agreement's previously omitted parameters.

The census of 5,061 available original objects finds only the zero-addend HA/LO
references in the Ep3 factory registration. No alternate direct reference was
found; computed callers or externally supplied aliases are not ruled out.
The source now uses a genuine static member accepting window/context pointers,
passes them to the existing Base frame member and registers its native address.
The old hand-mangled external declaration is removed; catalog and retention use
the real resulting FPvPv export. No adapter, forced symbol spelling, allocation,
class size, dispatch, lifetime order or common callback-field type is changed.
Static class placement remains recovered organization, not proof of original
source naming. The larger mixed callback invocation ABI remains qualified.

Native capacity-gated full build preserves original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,654 other compiled-source
objects are byte-identical; the Ep3 object's full non-string sections, raw
relocation records and ordered symbol metadata match after normalizing its one
native export rename. String/file offsets are not claimed raw-identical.
Independent original-assembly/source review passes. check_pr against the captured
0e9dee826 report passes with zero metric loss and one catalog rename. All 347
repository tests pass. This does not change the PR's substantive draft holds.
