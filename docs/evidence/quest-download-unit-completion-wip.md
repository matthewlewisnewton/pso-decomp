# Quest-download unit completion investigation (in progress)

The claimed unit is `pso/misc/TQuestVmDownLoadServer_803E6970.cpp`, based on
fork main `554d21699c873ccf9be1b2268eba37cd3a32e48b`. All 173 native functions
now have C++ bodies, but only 167 match exactly. **This unit remains unlinked
and is not ready for a completion PR.** The exact display milestone is
recorded in [display recovery](quest-download-display-recovery.md).

## Assembly reconstruction and iteration

Initial bodies were compiled for all five missing routines. Candidate building
(`803EA428`) classifies input runs, appends synthetic or dictionary item chains,
and searches decreasing candidate lengths. Its run-emission block is shared by
several branches, including backward branches. Restoring that position and a
signed minimum count improves the relocation-sensitive comparison from roughly
74% to 94.19162%, with the original 1,336-byte extent.

Selection (`803EA9E8`) initializes tokens, constructs item/entry chains, selects
lengths, releases discarded entries, and consolidates groups. Keeping the
selection cases nested and advancing the consolidation cursor in its consuming
expression reproduces the original 1,004-byte extent. Declaration-order probes
reach 96.88844%. This is not an exactness claim.

Request accumulation (`803EE2F4`) and emission (`803EE580`) retain their native
fallbacks, name/text conversion and ID-list traversal. Their initial bodies
remain partial. The latter preserves the original unsigned-halfword comparison
with integer minus one; it is not silently normalized to `0xFFFF`.

The repository precedents studied include the earlier quest investigations,
[inline entry merge](quest-download-pr295-sol61.md),
[movie-frame allocation](pack-movie-frame-unit-flags.md),
[shape blending](creation-shape-blending.md), and
[copy propagation](indirect-scroll-offset-propagation.md). Local compiler
backend research also used the `doldecomp/mweppc` coloring implementation.
Reduced C and C++ probes, readonly-reference helper inputs, declaration orders,
address-expression forms, explicit header temporaries and supported scoped
optimization switches were compiled and compared. Adjacent compiler releases
provided no new exact functions; the pinned compiler/profile remains unchanged.
Ineffective experimental helper and optimization scopes were removed.

## Shared types and scratch lifetime

`QuestDownloadQueryTypes.h` gives the provider and data unit one definition of
the six-byte query entries, 32-entry result, and 0x990-byte workspace. Layout
assertions cover the 0x8C0 result offset, 14-byte entry offset and complete
extents. The following slot array remains a separate actual object. Native-only
address adapters retain the observed workspace-relative addressing; their
non-MWCC branches use the actual slot array directly.

`QuestDownloadScratch.h` gives the frontend, provider and data owner consistent
scratch, string-buffer and display-prefix declarations. The display prefix is
still its actual 12-character object. Two native routines retain its address
when reaching the following scratch allocation; the portable adapter names
that separate byte array directly. No encompassing aggregate is fabricated.

The existing aligned `u8[0x404]` provides storage for complete trivial scratch
objects. Before the conversion producer writes words, tagged placement
construction begins `QuestDownloadScratchWords` with 514 signed halfwords.
The producer writes at most 512, preserving the four trailing bytes. The
consumer borrows the corresponding unsigned-halfword view. Before request
emission writes IDs, placement construction begins the complete 257-word ID
array. Construction performs no initialization stores. These phases reuse
storage rather than declaring incompatible external arrays over one symbol.

The conversion borrows its input only during the synchronous call. Keyword and
fallback lookups return readonly table pointers, not input pointers. The ID
consumers synchronously walk the supplied list and do not retain that pointer.
These changes do not establish reentrant or concurrent use of this global
scratch, arbitrary malformed-input bounds, or new ownership for the remaining
opaque variable-record interfaces. Existing engine preconditions remain.

The selector return declaration is a full signed word, matching its native
sign-extended returns and caller use. Its function remains exact.

## Current comparison and validation

Direct comparisons use `functionRelocDiffs=data_value` with the unchanged
GC/1.2.5 profile. Remaining functions are:

| Native suffix/name | Match % | Compiled/original bytes |
| --- | ---: | ---: |
| `803E8DA0` | 95.051544 | 780/776 |
| `803EA9E8` | 96.88844 | 1004/1004 |
| `803EDC20` | 94.41237 | 388/388 |
| `803EDF64` | 96.98214 | 888/896 |
| `803EE2F4` | 95.74847 | 644/652 |
| `803F03B4` | 99.75903 | 332/332 |

The latest full build and `tools/check_pr.py` pass against the starting-main
baseline: +8 exact functions, +5,260 matched code bytes, no exact-function,
matched-data or source-linkage losses; all 3,626 linked units remain exact.
The built DOL retains its original SHA-1. The new scoped placement inlining
and native address boundaries are registered in `porting-exceptions.md`;
the generated inventory is refreshed.

A private PPC differential harness loads the verified executable, relocates
only the recovered conversion routine to another address, and calls the actual
original mapping and lookup helpers. The 134,296-case run passes all
single low bytes, all 65,536 low-byte pairs in both modes, 2,000 longer
random inputs, 200 inputs of 512 words, and keyword-derived inputs with all
case combinations and four attribute patterns. Return-site observations
confirm all six keyword rows are hit on both sides. The comparison includes
the meaningful result, output bytes/count, readonly input representation and
stack/nonvolatile restoration. This bounded execution evidence does not prove
exact code or whole-unit linkage. Original binaries, table contents and
extracted instructions remain private and are not committed.

Completion still requires all nine function differences, full allocated
section layout and relocations, source-link eligibility, and fresh complete
link/no-loss verification. No incomplete unit is added to `linked_units.txt`.

## Cache initializer exact recovery

The follow-up initializer now matches all 628 native bytes. An MWCC-only
integer address adapter reaches the actual index immediately after the actual
8,192-byte cache, without claiming an enclosing C++ object. Other compilers name
the actual index directly. The existing canonical index layout supplies the
80 bucket heads and 512 nodes. A scoped `opt_common_subs off` preserves the
native independent node-end calculation. Unsigned bucket indexing reproduces
the straight unrolled stores. After clearing the eight pages, the page cursor
is rewound to the first page's end before publishing the append bound; this
preserves its native register handoff without dummy storage or extra writes.

This iteration also tested natural inlined cache-search boundaries and parser
header/body splits; they did not improve exactness and were discarded. A private
read-only trace of the pinned compiler under retrowin32/GDB exposes the parser's
remaining four-word header difference: the offset addition reuses the output
cursor's virtual register, whereas the target needs a separate intermediate.
No compiler state or generated instructions are patched.

The same address adapter and separately scoped CSE setting improve replacement
to 95.051544%, reload to 95.281815%, and rotation to 97.5566%. Rotation uses a
bounded name-search helper that returns the stopping node and its link. It now
has the native 424-byte extent, with stack offsets and registers still differing.
The checked native initializer is an exact milestone, not whole-unit completion.

## Primary-record remover exact recovery

`803EF208` now matches all 816 bytes. The record/end declaration order restores
their native registers. Whole-record removal names its actual negative
displacement and borrows it through a readonly reference. Its destination uses
a documented MWCC integer-address expression to preserve the native operand
order; other compilers use ordinary byte-pointer addition. Partial-message
removal forwards through its own depth-two inline boundary to the existing
byte shifter. This accounts for the native name-buffer offset without padding,
extra storage or an alignment attribute.

The whole-record helper is deliberately specific to a tail after a nonempty
record. The caller reaches it only for a record before the terminated page end;
its positive record size puts `source = record + size` strictly after the
backing array's first byte. Both terminator bytes belong to the same page.
Consequently, even the helper's generic backward branch can decrement its
cursor to `source - 1` without forming a before-array pointer. The actual call
uses `-size`, hence the forward branch. This is a narrower, caller-supported
interface than the earlier general array-start copy helper; it does not claim
to accept arbitrary `source == array_begin` inputs. The existing partial-message
helper and its other exact callers retain their previous code and contracts.

The integrated remover passes the fresh full no-loss check: all 3,626 linked
units remain exact and the original DOL SHA-1 passes. Together with the display
and cache initializer, this branch adds three exact functions and 2,148 matched
code bytes. A host C++98 extraction of the exact portable record-tail helper
also passes 91,455 comparisons with `memmove` under AddressSanitizer and
UndefinedBehaviorSanitizer, including empty spans and both overlap directions,
with the documented strictly-after-array-start source condition.

## Shared cache lookup and accumulator control flow

Copying and terminating the record name in the caller, then inlining the
sorted lookup, reproduces rotation's native 0x88-byte frame and name offset
0x14. The helper returns the stopping node and publishes its link; it does not
introduce a fabricated result object or unused padding. Rotation is now
99.43396%, with only the length and bucket registers swapped. Reusing this
boundary in the persisted-page rebuild reaches 97.82727%, 444/440 bytes.
Its extra base-pointer copy and stack/register differences remain unresolved.

The accumulator's empty-cache-name branch returns to the earlier shared
emit/increment/continue block, as the native backward branch does. Its request
length is explicitly narrowed to an unsigned halfword before the existing
signed-halfword field store. Direct use of the actual global buffers for the
first conversion and append-name scan reproduces more of the native pointer
handoffs; the first terminator store also names the actual global buffer.
This reaches 95.74847%, 644/652 bytes. Missing pointer spills and remaining
register assignments are still partial work, not exact coverage.

The full repository check passes after these changes: all 162 exact functions
in this unit are retained, all 3,626 linked units remain exact, the original DOL
hash passes, and force-active retention has zero additions or removals. The
branch's exact gain remains three functions and 2,148 code bytes. These partial
improvements do not make the unit eligible for source linkage or a completion PR.

## Cache page rotation exact recovery

`803E95BC` now matches all 424 bytes. A readonly trace of the unmodified pinned
compiler showed that the helper's mutable input-length parameter received a
virtual register before the bucket and node locals. That made the length and
bucket occupy the opposite saved registers from the original.

The helper now distinguishes the input name length from each indexed record's
length. It declares the wanted length, bucket, node, predecessor, then the
per-record length in that order. Their actual lifetimes reproduce the native
allocation; the caller's input length and the loop's record length reuse the
same physical register without being the same C++ variable. No dummy reads,
padding, compiler patch, new option or instruction editing is involved.

The rebuilt owning object retains all previous exact functions and now has
163/173 exact. Its shared lookup also raises the persisted-page rebuild to
98.37273%, still 444/440 bytes with a base-copy and stack-layout difference.
The full repository check passes with four added exact functions and 2,572
matched code bytes, all 3,626 existing linked units exact, an identical DOL,
and unchanged force-active retention. Ten functions and complete unit linkage
remain outstanding.

## Persisted cache rebuild exact recovery

`803E93DC` now matches all 440 bytes. The ARAM read and initial page cursor
name the actual cache array directly; retaining a second pointer alias had
emitted an extra saved-register copy. A fixed-image read helper forwards to a
byte-count adapter under a scoped inline depth of two. Both use the existing
ARAM boundary and its unchanged byte count. Their inline temporary lifetimes
place the real name buffer at the native 0x18 stack offset, with the native
0x90-byte frame. The outer adapter retains its explicit signed-word return
cast: removing that otherwise redundant cast shifts the inline temporary and
name-buffer offset by four bytes (99.96364%). There is no padding object, dummy
parameter or alignment trick.

The complete object retains exact rotation and all earlier exact functions:
164/173 now match. Full checks pass with five added exact functions and 3,012
matched bytes, all 3,626 linked units exact, the original DOL hash unchanged,
and zero retention drift. Nine function differences and full source-link
eligibility remain before the requested completion PR.

## Keyword-conversion block layout

The native `803EDF64` places fallback mapping and output emission inside the
keyword-scan loop, before the scan-advance block. Keeping that block after the
loop had preserved behavior but moved a large range of instructions. The two
existing entry paths now join labels at the native position. Exhausting input
breaks to the common zero return after the loop. The lookahead byte is declared
before the conversion state, and byte comparisons retain unsigned constants.
These changes improve the comparison from 78.625% to 96.98214%, still 888/896
bytes; the lookahead load/copy sequence remains different. Exact coverage stays
164/173 functions.

The freshly compiled candidate was compared with the original PPC instructions
in Unicorn using the original classifier, keyword table, and mapping helpers.
All 134,296 cases agreed on return value, output bytes and count, unchanged input,
and preserved registers. Cases cover every one- and two-byte low-byte combination
under both mapping modes with nonzero input attributes, randomized longer input,
and all six keyword rows with case/attribute variants. This is behavioral
validation of the partial candidate, not a claim of an exact match.

## Exact cached-record move (`803E8924`)

The 504-byte move now matches exactly with the pinned compiler. A borrowed
`CachedRecordView` exposes only the existing record pointer, little-endian
length, name length and name pointer. Its constructor copies a pointer; it
neither owns nor extends the underlying cache allocation. Inlining the byte
accessor through the length accessor at depth two reproduces the native
0x90-byte frame and name buffer at stack offset 0x20 without padding.

The source cursor and saved original pointer use chained initialization.
The identity check compares against the still-unadvanced source cursor; after
the copy loop, the saved original pointer clears the old record's name length.
Separate initialization generated `mr r27,r30` instead of the native
`addi r27,r30,0`; comparing against the saved pointer changed the comparison's
register operand. Both pointers designate the same record at that check.

This iteration used the GC/1.2.5 implementation in
[rayanht/mwcc](https://github.com/rayanht/mwcc) and the chained-assignment notes in
[Sunshine's matching guide](https://github.com/doldecomp/sms/blob/main/docs/AGENT_MATCHING_TIPS.md).
Compiler tracing was read-only; no compiler or generated binary was patched.
Direct relocation-sensitive comparison confirms all 126 instructions, with
165 of 173 functions now exact and the other eight unchanged.

## Glyph-table relocation and symbol recovery

The 0x6A8-byte read-only range at `8047EA28` contains the already defined
`glyph_bits[0x3E0]`, `glyph_rows[0x72]` and `glyph_col[0x100]` arrays used by
`803E7390`. Their boundaries are `8047EA28`, `8047EE08`, and `8047EFD0`.
The consumer reads byte bits, four-byte row pairs and byte column indices;
none of these arrays contains pointers. The packed words at `8047EB44` and
`8047EC64` happen to equal code addresses, so the splitter had incorrectly
created two `R_PPC_ADDR32` relocations there. Both sources are now explicitly
blocked, following the existing font-data precedent in `config.yml`.

The current generated split/report census supplied 8,594 split and compiled
objects for the undefined-symbol audit. None refers externally to the old
combined `lbl_8047EA28` label. The symbol inventory now identifies the three
actual static arrays, matching their source linkage and extents. No asset
bytes were added to source. The whole `.rodata` range now reports 100%, and
the regenerated DOL retains the original SHA-1. The switch tables still have
two internal alignment gaps to recover; function emission order also remains
a separate whole-object requirement.

## Candidate-builder control flow and lifetimes (`803EA428`)

The candidate builder now compares at 99.74551%, with all 334 instructions,
the original 1,336-byte extent, and the original 0x48-byte frame. Exact unit
coverage remains 165/173; this is still a partial function.

An explicit zero switch case restores the native decision tree. The bounded
text scan compares its accumulated length against the original input bound,
which recovers the unsigned count-loop exit. Input bound and computed candidate
length are separate locals: frontend lifetime splitting had otherwise given
the latter an anonymous value with a different allocation priority.

The append helper preserves the native list-tail handoffs, and a saved pointer
to the slot's item head is shared across candidate lengths. A signed-byte span
return passes through the word-sized store helper, retaining the native sign
extension. The borrowed workspace-address value has no padding or ownership
claim; its constructor preserves the native temporary lifetime. The result
uses its real offset within the workspace. The native-only run store expresses
the member displacement before indexing by the slot byte stride, recovering
`add` plus displacement `stb` instead of an indexed store. Ports continue to
use the actual, separately declared slot array.

Read-only traces of the unchanged GC/1.2.5 compiler guided these changes.
The remaining 15 instruction differences are register arguments: six scan
pointer uses, three command-table address uses, and six uses of promoted loop
values. C language-mode probes for the separate `803F03B4` parser and additional
pointer/reference, scope, and promotion probes produced no new exact functions.
No compiler, generated instruction, or physical register assignment was patched.

The improved builder was executed against the original PPC routine in Unicorn
for 10,168 cases. All 334 instructions were reached on both sides. Cases include
all initial byte values, empty and bounded runs, download-command continuation,
mode-dependent early returns, seeded existing item lists, allocation failures,
and randomized mixed input. Native classification helpers execute unchanged;
dictionary lookups, allocation, release, and item-list construction use identical
deterministic boundary stubs. Return values, complete workspace/slot and item
memory, unchanged input, boundary call traces, and preserved registers agree.
This checks the recovered routine's behavior, not the implementations of those
stubbed external operations or whole-game runtime behavior.

## Exact candidate builder (`803EA428`)

The follow-up recovers all 1,336 bytes, including every register operand.
The temporary used for the native slot displacement is reused for the input
address inside either character scan. It is represented as `size_t`, and each
branch initializes its value before reading it. The lookup scan has its own
byte cursor. Scoped `opt_lifetimes off` preserves that reuse. The non-MWCC
slot adapter still addresses the actual separate array; no encompassing owner
or synthetic pointer object is introduced.

Inside synthetic-item creation, `s8 maximum = end + 1` precedes the item field
writes and passes to the existing word-sized span store. Moving the conversion
outside this block or obtaining it through a narrow-return helper produces the
same behavior but different allocation order. The local form restores both the
three loop-invariant registers and the command-table base register. The unused
narrow-return helper was removed. All other previously exact functions remain
exact: the unit is now 166/173, with seven function matches and full object
layout/linkage still outstanding.

The cleaned exact object also passes the 10,168-case native comparison described
above, with all 334 original and candidate instructions reached. This iteration
consulted [the MWCC allocator research](https://github.com/stephenjayakar/melee-mwcc-register-skill/blob/main/references/allocator-rules.md)
and [Pikmin's inline-boundary evidence](https://github.com/projectPiki/pikmin/wiki/MWCC-Decomp-Permutation-Notes).
They were research references; no code was copied into the unit and no raw
register constraints or assembly were introduced.

## Exact request emitter (`803EE580`)

The emitter now matches all 408 original bytes. A structural search found that
separating the final request-field writes from the storage view changes the
constant-zero lifetime and restores the native call-argument registers. Keeping
the request view before the ID cursor restores their r30/r29 allocation. The
borrowed view's constructor removes the extra global-address copy. The retained
source uses the existing `inline_depth(1)` region; no new option, padding,
assembly, or physical-register constraint is needed.

`QuestDownloadRequestView` holds only a pointer to the actual 40-byte allocation.
The later `completed` pointer names its real leading `Req_803EEF2C` subobject.
Neither view changes ownership, storage lifetime, or request layout. The
placement construction of the existing scratch ID array remains unchanged.
The unit now has 167 exact functions; six function matches and complete object
layout/linkage remain outstanding.

A native PPC differential run passes 3,600 cases with matching memory, boundary
calls, and preserved registers. Half are ordinary ABI cases covering null and
all-ones entry lists, absent item sources, duplicate IDs, all-ones IDs, varying
16-bit text IDs, and randomized lists. The other half explicitly force the
comparison operand to signed -1 to exercise the retained custom-request path:
the original unsigned halfword load cannot naturally produce this value.
This supplemental injection is confined to the test harness. Together the runs
reach all 102 instructions in both implementations. Native `strncpy` executes;
word conversion, byte conversion, and submission use deterministic stubs that
also clobber caller-saved registers. This does not test those external routines
or claim whole-game runtime coverage.

The full native build still reproduces the original DOL hash, and no previously
exact or source-linked function or data range is lost. A separate private
function-order candidate preserves all matches; its cleanup and the two data
alignment boundaries remain part of completing the whole claimed span.
