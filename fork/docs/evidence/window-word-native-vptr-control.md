# Word native-construction control: exact bodies, unresolved placement

This follows the [raw-initializer timing control](window-word-specific-context-control.md).
The clean stack was focused `37ed8308f9df0e8ff4426bcc187f378f337a2cbc`,
continuation `039efcef6ad0ac1d70b906cab6333e6ad238c1c8` and main
`e65f11ce6ec99c006909422f81da1c0a46ac062e`. No competing head update was
observed. This investigation changes evidence only. Production source, profiles,
providers, coverage qualifications and all technical holds remain unchanged.

## Selecting the bounded lane

Sixteen raw Base/Addition calls remain across nine units and three shared
bindings. The factory/lifetime families still require producer, callback,
initialization or ownership evidence; their count is not reduced by this probe.
ComCard still lacks ownership of `[804CE914,804CE918)`. Its previously rejected
four-byte loss is not waived or retested. Parts still lacks eighteen exported
floats `lbl_805DD7C8` through `lbl_805DD80C` in the current compiled object.

Word offers a distinct source question: the preceding timing control retained a
C initializer with explicit table-symbol transport. It did not test the vptr
store emitted for a genuine constructor. One fixed native construction candidate,
in two compilation contexts, can distinguish that boundary without a source-order,
layout, local-variable or optimizer-option sweep.

## Source and caller boundary

The private candidate uses the existing 0x90-byte Base-derived Word class, an
ordinary two-word constructor, ordinary `new` in the existing factory and a native
destructor. The constructor initializes Base with the existing descriptor and
position, then performs the observed name, count, index, scroll and tail stores
and calls the retained reset/loader helpers. The observed list-id word at0x70 is
named and its offset asserted without changing size. The destructor conditionally
deletes the existing buffer and clears it; Base destruction and the deleting
protocol are compiler generated. Manual table/vptr stores and the fake destructor
receiver are removed. Existing metadata and definition order stay unchanged.

This does not establish the entire helper graph's source types. Reset retains
its qualified raw two-word ABI, including an observed unused second word. The
loader retains its existing explicit raw receiver ABI. Mixed mapper declarations,
raw-storage lifetime, buffer ownership interfaces and the global name's catalogued
second word remain qualified. No default constructor, extra field/padding,
aggregate or new constant is invented.

A census of4,949 unique active original objects from the fresh-main configuration
examines249,768 relocations. The raw constructor has one named reference, a
zero-addend REL24 in its own factory. The deleting body has one named reference,
a zero-addend ADDR32 in its own table. No other named calls/address takers occur.
This does not exclude arbitrary alias arithmetic or prove every original type.

## One source, two contexts

Both contexts use identical private source and headers. Source SHA-256:
`37926adae30637a4965ea16625cef072bcc78be2da7ad00be3ab69a14ed01845`.
Only the value after `-inline` changes: `off` versus `off,deferred`.
There is no definition reordering, declaration variant or modified production
configuration. The pinned GC/2.6 compiler SHA-256 is
`316e2a98236c23f3fc902243b157eaebf8ef2ad6edb88cfd632a15b6676fa9a8`;
the wrapper SHA-256 is
`7fdf620b151744296b9bb93318d8c4009d3d3e98e23718a6eda9fbec4cefbb2a`.

Each run holds the legacy capacity gate and common debugger lock. Four read-only
hardware breakpoints observe data declaration, function generation, pool state
and anchor addition. No compiler memory or code is changed. Each complete traced
ELF equals its own separate normal control byte for byte.

| Measurement | Original | Immediate | Deferred |
| --- | ---: | ---: | ---: |
| Genuine constructor / original initializer bytes | 148 | 156 | 148 |
| Owner text bytes | 664 | 672 | 664 |
| Owned data bytes | 88 | 88 | 88 |
| .ctors record bytes | 4 | 4 | 4 |
| Constructor text relocation records | 7 | 11 | 7 |

Immediate generation again emits the real table after all seven functions.
Deferred generation declares it before all seven, pools it with descriptor and
position, and reaches a full three-object group with virtual register36. The
genuine constructor now uses the retained shared address base for its automatic
vptr store. All seven deferred function bodies and their normalized,
function-relative relocation offsets, types and resolved targets including
addends match original after the documented native constructor/destructor symbol
normalization.
This includes the116-byte deleting destructor and92-byte factory.

The complete88 data bytes and all five normalized data relocation identities
match, including the24-byte compiler table's four function targets. The four
.ctors raw bytes and normalized function identity match. Owned section types,
flags and alignments remain unchanged: text4, data8 and ctors4.

## Whole-owner failure remains

Exact component bodies and equal text size do not qualify the owner. Deferred
generation reverses the unchanged definition order:

| Function | Original text offset | Deferred text offset |
| --- | ---: | ---: |
| First query | 0 | 644 |
| Second query | 20 | 624 |
| Deleting destructor | 40 | 508 |
| Constructor | 156 | 360 |
| Factory | 304 | 268 |
| Startup stores | 396 | 196 |
| Following helper | 468 | 0 |

Consequently actual table and startup destinations do not reproduce original
linked addresses. Symbol normalization cannot repair placement. There is no
full-game candidate build or DOL-pass claim: this candidate already fails its
required order/address gate. No lifetime/profile activation follows, and deferred
compilation is not established as the original retail profile.

This bounded result distinguishes genuine construction from the previous raw
initializer: it resolves that component's four-byte mismatch under the diagnostic
context. It does not justify rearranging definitions solely to obtain offsets.
The investigation stops after the two fixed-source contexts. Further work needs
independently supported native source/compilation organization, complete actual
placement/relocation/link qualification and the retained helper-interface audit.

Private replay, receipts, traces, comparisons and reference census are in
`pr403-word-native-vptr/` (`observe.py`, `verify.py`, `reference-audit.py`,
`summary.json`, `reference-audit.json`). Original objects, binaries and raw
disassembly are not published. Independent read-only review confirms the bounded
result and the failed placement boundary. The published Word owner/renderer,
original DOL and prior coverage certificates remain unchanged.

## Separate new Parts lead

The pinned upstream
[Parts source](https://github.com/zeroz41/pso-decomp/blob/8c507b2dacae5428291a823c3868ca486419660c/src/pso/ui/chat/TWindowSubSymbolChatParts.cpp),
blob `40811abe0cb49deba7bd12ea7f9f3d0b92d20855`, differs from the older
#196/#198 source previously audited. It uses literal32.0f with scoped
`opt_propagation off` in two helpers and an explicit8.0f `.sdata2` definition.
This is a new reconstructed-source lead, not proof of export completeness,
original ownership, safe localization or justified compiler controls. Historical
findings remain valid for their pinned older heads. No Parts source is imported
or compiled here. A future audit must establish complete sections/relocations,
external references and control provenance before any provider change.
