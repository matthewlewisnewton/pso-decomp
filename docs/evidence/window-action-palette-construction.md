# ActionPalette construction and tag receivers

This follows PR #268 checkpoint
`507a83dc28c5a7a77d197981e80da073c7d9d3fd`. ActionPalette now has a genuine
Base-initializing constructor, ordinary-new producer and supported Base-derived
0x78-byte image. Native task/render definitions use that actual receiver. The
original deleting wrapper and table provider remain; native destruction/table
integration is held on the layout/matching issue below.

## Window and tag storage are separate receivers

The original constructor takes a word client, narrows it for Base, and stores
the low halfword at 0x20. Its sole producer allocates 0x78. The native word-valued
constructor and producer reproduce all 260/584 bytes. Direct task members reproduce
its 640-byte body; the renderer's entry-list pointer is the actual Base prefix
at 0x24. Resource/state/scale offsets remain 0x60/0x6C/0x70 and total size 0x78.

The three four-byte records at 0x60 retain the existing init_gc_tag and
TPlyDispConfig::free_if_valid array-runtime protocol: stride four, count three,
and negative cleanup flags. The initializer clears four bytes. The cleanup
callback only deletes storage for a positive flag, so negative cleanup does not
release embedded storage. No owned resource or nontrivial native tag class is
inferred from the historical resource-field name.

The reset loop intentionally calls both setters on the first record on all
three iterations. The original loop does not advance to the next record; this
checkpoint preserves that asymmetry and all callback relocation targets.

The old set_slot/set_mode window methods actually write bytes 1/0 of a tag.
Their same historical exports now take void* tag storage and a byte value in
ActionPaletteTagAbi.h. Properly scoped callers use that interface instead of
casting tag/player storage to a complete palette window. The false byte-one
window field and member setter declarations are removed. No wrapper body or
replacement ABI binding is introduced.

Three unchanged units retain one-argument/integer-return views of those exports:
MainCursor_8013E624, MainCursor_8013E7B8 and TObjPlayer. Their missing value and
return contracts are not inferred. The new header is scoped to the migrated
callers and setter owner, so these incompatible legacy views remain explicit
holds. Wider entry, raw-record callback and player/helper ownership is also
qualified. This is not a global portable tag-interface recovery.

## Original deleting wrapper and icon jump-table hold

A native destructor probe reproduced all 116 bytes, and its compiler table
reproduced 24 bytes with the four correct slot targets. The complete linked DOL
still matched. However, extracting that table from the preceding held HelpItem
object made the icon renderer's 32-byte anonymous jump table external to its
original text object. Objdiff then stopped counting the 404-byte
`draw_action_palette_icon` at 80243630 as exact, despite unchanged raw instructions
and executable bytes. check_pr correctly rejected the lost exact function.

That probe is not activated. The complete original 832-byte HelpItem data provider
is restored, including the original Palette table and icon jump table. The
original Palette deleting wrapper and its Base cleanup binding are retained.
No compiler table is emitted, and no data range is reclassified or lost.
Construction recovery does not resolve destruction or compiler-table integration.
A future source arrangement must preserve icon jump-table matching and section
order without losing existing matches or inventing a table/control.

## Validation and current limits

The serialized full build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against 507a83dc28 passes
with zero metric delta: 27,395 exact functions, 3,588 exact linked units and no
code/data/coverage or linked-address regression. Retention remains clean at 17,850
and port inventory passes unchanged.

All nine relevant complete compiled text sections and their resolved targets
are unchanged from captured 507a objects: eight setter caller/owner units plus
the producer. All raw text also matches main originals. Eight objects are actual
source inputs once; the already-held TObjPlayer_801C7430 keeps its original
provider because of pre-existing constant relocation differences. Every setter
call offset/type/resolved target matches the original across all eight units.
The held player's source bytes and relocations remain unchanged and unactivated.

Palette's whole 2288-byte text covers constructor 260, retained deleting wrapper 116,
task 640 and render 84; all callback targets agree. The original HelpItem object
retains its full 832 data bytes and all resolved text/data relocations, selected
once. Its 956 compiled text bytes and 456 compiled data bytes remain unchanged.
The original Palette table's four slots retain their resolved targets, with no
competing compiler table, new gap or padding. The icon function's exact match is
restored. All protected providers/ranges retain their prior verification.

Only the raw constructor boundary is removed: 26 Base/Addition calls remain
across 13 source units, with the same four shared bindings. Balloon, ScrollBar,
Parts, ChoiceSetting/global ownership and all wider interface holds remain.
PR stays draft. Integrated main remains
`12cc95ca737a3a8757c17f45df06a9af4821d872`; combined deltas remain +600 matched
code, +1220 linked code, +1472 matched data and +1428 linked data bytes. The
fourteen qualified four-byte alignment gaps are unchanged.

## Bounded contiguous-owner probe on continuation #403

At continuation checkpoint `e0c0e8f51d688c0300e6659a8b8dd895781264fe`, a new
read-only ownership audit distinguished the earlier table-only extraction from
a contiguous source organization. The icon at 80243630 (404 bytes), adjacent
palette slot-light helper (344 bytes), and existing Palette unit (2288 bytes)
form a contiguous 3036-byte text range ending at 8024420C. Co-locating them could
keep the anonymous jump table with its generating icon code. This organization
would not establish an original translation-unit boundary or a new native owner
for the light helper.

One bounded candidate tested that organization with a genuine Palette destructor
and automatic Base cleanup. The original-selected prefix retained all 552 text
and 776 data bytes, including the serialized entry records and descriptor. The
five existing mutable UV banks (19/17/6/3/8 pairs) were represented by one
424-byte aggregate with size/offset assertions and kept in that prefix's source;
the moved icon referenced it externally. No raw replacement blob, extra virtual
slot, padding object, compiler control or alignment override was introduced.

The same candidate tested one shared raw icon-helper contract: callers transport
words and the callee explicitly consumes their low 16 bits. All eight direct
calls in five caller units discard the result; there is no evidenced external
address-taking. The original's eight local jump-table relocations target its
own icon body. This evidence supports the observed transport and consumption,
but does not uniquely recover original parameter signedness or source types.
The old function-pointer call view was removed only in the candidate. The light
helper's existing one-argument caller qualification was not changed.

The first compile rejected this candidate. The icon grew from 404 to 428 bytes,
making the combined text 3060 rather than 3036 bytes. Its generated code loaded
the external UV aggregate within individual cases rather than retaining the
original common local-data base. The word contract also changed two complete
caller objects: text_8027C13C stayed 240 bytes but changed instructions, and
CustomSelect changed from 2488 to 2480 bytes. The HelpItem_802531A0 and
CustomEquip_80275D9C complete caller texts stayed identical. The compiler emitted
56 data bytes naturally, but the changed text prevents qualification of their
jump targets or the complete object. The rebuilt DOL failed its original hash.

All candidate implementation, header and configuration changes were restored;
the failed probe is retained privately. No declaration/order variant, explicit
base-hoisting device, new control or coverage waiver was tried. The native
destructor/table hold and the existing helper views remain active. Further work
needs independent evidence for a common UV/table/jump source owner and the
caller conversion contract. Recovering the actual serialized entry schema could
support a larger coherent owner; merely moving or spelling declarations to
recover the original load schedule would not.

The restored capacity-gated full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All seven affected complete source
objects and their seven original counterparts are byte-identical to the frozen
published checkpoint. check_pr passes with zero metric, function, provider or
address-coverage delta; all 3590 linked units remain exact and retention is clean
at 17968 entries. Comparisons against refreshed focused #402 and main b3062dc640
also pass. Port inventory and independent read-only review pass. Only these
evidence notes and the current blocker index are published from this probe.

The later [serialized-layout recovery](window-action-palette-layout.md) derives
the 332-byte record schema from the actual dispatcher and initializers and
recovers it with the following 20-byte descriptor. Their bytes and six pointer
relocations match without changing existing function matches or providers.
The common-owner and caller-conversion holds above remain; no contiguous-owner
or width-contract probe is repeated by that data-only recovery.
