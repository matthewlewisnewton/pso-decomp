# WS_String native lifetime

This follows PR #268 checkpoint
`2e83236557ff45f1f4754225b0d1f49bd2c23ae9`. WS_String's existing Base-derived
0x74-byte image now has a genuine constructor/destructor pair, its recovered
task override, and its compiler-owned 24-byte table. The existing local factory
uses ordinary new. No additional raw lifetime binding is introduced.

## Ownership and constructor contracts

The original table at 804EFC38 has exactly four function slots: destructor,
task, WS_String render and inherited TObject shadow. Original active-reference
inspection finds the task at 803411A8 only in this table, without other table
references or direct calls. The misleading TWindowDD::init_window owner is
recovered as TWindowDD_WS_String::run_task in its existing source unit. The
obsolete DD declaration is removed; no compatibility wrapper is invented.

The sole constructor call is the local 0x74-byte allocation. The constructor
accepts two pointer arguments for position/size and the existing word-valued
text/mode arguments. The Base initializer forwards position with client four.
Fields at 60/64/6C are mode and two two-float pairs; their offsets and total
size are asserted. Copies use the already-observed two-float helper boundary,
without pretending complete PartsSet objects live in those fields.

The destructor has no descendant-owned resource to release; compiler-emitted
Base cleanup and deleting behavior reproduce the original 88 bytes. The
constructor's 224 bytes and factory's 112 bytes are also identical. The entry
lookup, text update, position writes, qualified depth helper and refresh call
retain their original order. In modes one/three, the original post-lookup
entry+24 write remains unconditional even when the lookup returned null. No
new null handling or behavioral fix is claimed.

## Descriptor and table placement

The existing 20-byte descriptor at 804EFC24 initially has zero extent/order,
entry reference 804EFC00 and flags three. It is declared with the provisional
WindowLayoutDescriptor schema. The factory still sets the two extents; static
initialization still sets order and the entry prefix's existing word. No
initializer value is substituted for those runtime updates.

Only the compiler table at [804EFC38,804EFC50) is claimed by the constructor
unit. The entry prefix36 and descriptor20 remain in the original 56-byte
provider at 804EFC00, selected exactly once. This avoids forcing an eight-byte
aligned combined section to the descriptor's four-modulo-eight address.
The table starts naturally aligned; no gap or source padding is introduced.
Its 24 bytes and all four relocation targets match the regenerated original
split. Compiler-generated tables are not written by hand.

## Validation and boundaries

Serialized native builds use the shared capacity gate. The full linked DOL
retains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against
2e83236557 passes: +24 matched/linked data bytes, zero code/function/unit or
linked-address regression. Totals remain 27,395 exact functions and 3,588 exact
linked units. Retention is clean at 17,838 entries: three related native names
are added and the obsolete constructor retention name is replaced. Port
inventory passes unchanged; no compiler control or exception is introduced.

Four complete source-selected text sections and all their text relocation
targets match main originals: constructor owner460, task/render owner832,
draw helper owner844 and factory caller3288 bytes. The other factory caller
unit TWindowDD_803430BC is already held: its compiled 13,164-byte text and
relocations remain unchanged from fresh main compiled source, while its
14,792-byte original remains selected once. Its four existing factory calls
and broader historical float/register declarations are not retyped or claimed
portable. The remaining exact caller supplies the fifth factory reference.

The original prefix, all protected remainders and the 1,044-byte setup helper
are preserved. HelpItem and Parts validation/provenance remain intact. The
Parts constant/source-link blocker, entry/helper attribution, renderer implicit
register interfaces, callback signatures and all other ownership holds remain.
This family removes two raw Base calls, leaving 34 Base/Addition calls across
17 source units and the four shared ABI bindings. PR remains draft.

Integrated main is `12cc95ca737a3a8757c17f45df06a9af4821d872`. Combined PR deltas
versus its separately validated source baseline are +600 matched code,
+1220 linked code, +1356 matched data and +1312 linked data bytes. The fourteen
previously qualified four-byte alignment gaps are unchanged.
