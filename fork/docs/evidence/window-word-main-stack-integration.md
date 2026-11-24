# Upstream Word renderer with preserved continuation contracts

This integrates main `59dfc7117a7e2cd251b65f1b435e66a9bf174618` and its merged
#407 recovery through focused head `0ac063a04cea85a639361faacc2196647965fac2`.
The continuation previously held the complete Word provider because its renderer
was missing. The combined original-byte, relocation, provider and full-build
qualification below supersedes that missing-body/provider hold. The native
constructor/destructor/table and broader raw-buffer interface holds are separate.

## Reconcile the existing contracts

The original reset at 803403F8 consumes raw destination storage in r3 and depth
in f1, overwrites r4 before using it, and fills eight 24-byte records. The
continuation's shared WindowVertexBufferAbi.h declaration remains authoritative
for this bounded recovered interface: raw storage, explicitly unused word and
float depth. The two new Word calls pass `(vertices, -1, depth)`, just like the
existing WS_String call. No TWindowDD object is constructed in that buffer, and
no semantic color argument or return value is inferred. The original five direct
callers and input/overwrite evidence remain in the earlier shared-contract note.

The upstream member reset and its Ffl catalog name are reconciled with the
continuation's existing Ff export, definition and callers at the same address.
The reset definition and WS_String source objects remain byte-identical to their
captured continuation objects. This is one shared interface, without a wrapper,
alternate-width function-pointer view, new export or inferred native buffer class.
The upstream 192-byte WordRowVertex array is retained. Other existing buffer/helper
casts remain qualified; this change does not establish those helpers as real
window methods or recover a complete portable rendering API.

The existing native TWindowDD_WS_Word::run_task and add_scroll_offset remain.
The status query still returns a word, not the older byte view. The actual
0x90-byte window adopts the upstream point_table_index at 0x64,
visible_row_count at 0x78 and scroll_offset at 0x88. Its established float at
0x84 is preserved rather than returning to opaque byte storage. Offset and size
assertions cover these fields. Native task accesses use the same field names,
without changing operations, order, local widths or float expressions.

The inherited renderer retains its scoped fp_contract on and the original fused
arithmetic, including eight fmadds and two fnmsubs. That mechanism is now accepted
upstream source, with direct instruction evidence. This integration introduces
no further control or scheduling variant. Historical local failed probes remain
historical; they are not a reason to reject a subsequently validated upstream
body. Original source spelling, runtime operand safety and unrelated interfaces
are not inferred from exact arithmetic alone.

## Exact objects and actual executable inputs

The combined Word object contains all 25 functions and 3412 original-exact text
bytes, including the 916-byte renderer. All 112 text relocation records match
original offsets, types, addends and resolved destinations; the eight-byte
conversion pool also matches. Every one of the preceding 24 function bodies and
its function-relative relocation destinations remains unchanged. In particular,
the native task is still 912 bytes and its offset helper is still 52 bytes.
Compiler-local literal names are resolved by section/address, not by colliding
anonymous names from other catalog units.

The complete prior ELF objects for DD (1244 compiled text bytes), WS_String draw
helper (844), Word constructor/table owner (664), ScrollBar owner (832), String
task/render owner (332), String constructor owner (460), and shared render-state
owner (896) remain byte-identical. The Word constructor owner's 88 data bytes and
four-byte .ctors registration therefore also remain unchanged.

The actual linker selects the complete Word source object exactly once and its
original text counterpart is absent. DD's independent incomplete 2736-byte unit
still selects its original provider once; its separate missing renderer is not
recovered by this change. Parts and all protected original data remainders and
the 1044-byte helper retain their independently checked providers and contents.

The generated retention correction replaces old DD-owned add_scroll_offset with
its established native Word symbol. There are 18465 retained names, with no
missing or stale entries. There is no data repartition, range shrink, new padding
claim or invented table.

## Complete-build qualification and remaining work

An isolated fresh-main build, the focused build, the combined continuation build
and its retention rebuild all run through the existing capacity gate and retain
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Fresh main has 3597 exact
linked units, focused 3598, and continuation 3599. Acceptance against preceding
continuation and refreshed focused/main reports passes. A separate raw interval
audit against the preceding continuation loses no data coverage, exact-data or
linked-data range, without invoking a padding exemption; no function address
vanishes. Port inventory and whitespace checks pass.

The +916 matched / +3412 linked code and eight linked data bytes relative to the
preceding continuation belong to upstream #407. The continuation's contribution
versus refreshed focused remains +492 linked code, +1604 matched and +1560 linked
data bytes, with the fourteen established window-gap qualifications. The earlier
inherited main BSS/sdata2 eight-byte historical qualification remains distinct.

The 148-byte legacy constructor, 116-byte deleting function, manual table and
factory remain unchanged. The earlier 156-byte native-constructor result still
needs evidence for shared descriptor/position/table address generation; the
renderer recovery does not supply that ownership arrangement. No exhausted
lifetime or DD-renderer probe is repeated. ComCard trailing-word, Parts exports,
Palette ownership/conversion, nameplate, callback, initialization and other
remaining holds stay explicit. Both replacements remain draft.
