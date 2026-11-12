# Quest-download unit completion investigation (in progress)

The claimed unit is `pso/misc/TQuestVmDownLoadServer_803E6970.cpp`, based on
fork main `554d21699c873ccf9be1b2268eba37cd3a32e48b`. All 173 native functions
now have C++ bodies, and 172 match exactly. **This unit remains unlinked
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
| `803EA9E8` | 100 | 1004/1004 |
| `803EE2F4` | 99.81595 | 652/652 |

The latest full build and `tools/check_pr.py` pass against main `5146327538`:
+12 exact functions, +7,652 matched code bytes and +1,744 matched data bytes,
with no exact-function, matched-data or source-linkage losses. All 3,622 linked
units remain exact and the built DOL retains its original SHA-1. The chosen
unit has 172 of 173 functions exact; final source-link admission remains pending.
The scoped compiler exceptions are registered in `porting-exceptions.md` and
the generated inventory is current.

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

Completion still requires the remaining accumulator difference, full allocated
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

## Converter lookahead follow-up

The converter at `0x803EDF64` now retains the decoded low byte separately from
its halfword lookahead state and reuses it for the repeated-character and x/X
checks. With the existing compiler settings this improves the candidate from
96.98214% to 99.24107% (892 candidate bytes versus 896 native bytes). A redundant native byte mask
and register assignments remain unresolved, so this does not add an exact
function or source-link coverage.

A private PowerPC differential run compared this candidate with the original
routine on 134,296 cases: both mode settings, every one-byte and two-byte
low-byte combination, randomized longer inputs, all keyword rows with case
and high-byte variants, and long inputs. Return values, output bytes and count,
read-only input, and preserved registers agreed; both implementations reached
all six keyword rows using the actual native helpers.

## Shared character interfaces

The character conversion chain now shares halfword inputs, a halfword Shift-JIS
conversion result, and byte encoder/lookup results. The two classification
predicates return integers, as their native callers expect. Their two-byte local
output arrays accommodate both encoder outcomes; the former single-byte locals
were too small for the two-byte case. Scoped `bool off` preserves the native
integer predicate instructions.

The neighboring routine at `803E5D20` now passes the conversion result explicitly
to the encoder through the shared header. Its old parameterless declaration
relied on the prior call leaving its result in r3. All 16 neighboring functions
remain exact, as do the same 167 functions in the claimed unit. The corrected
interfaces slightly improve the still-partial input parser to 94.46392%; no
additional function or source linkage is claimed in this step.

## Fresh split-object layout experiment

A private three-object grouping was rechecked against fresh original objects
produced by the pinned `dtk dol split --no-update`, using this branch's original
inputs and a private copy of the split configuration. The text boundaries are
`803E6970..803E9A24`, `803E9A24..803ED0CC`, and `803ED0CC..803F0C50`.
These cover the same 173 functions; the checked-in split and linkset remain
unchanged while the six functions are still partial.

The groups emit 156, 1,044, and 36 bytes of compiler-generated switch tables,
all with normal eight-byte alignment. This reproduces the four-byte gaps at
`804FC8F4..804FC8F8` and `804FCD0C..804FCD10`. The first group owns the glyph
and signature constants; its 1,738 emitted bytes plus six trailing alignment
bytes cover the original 1,744-byte read-only range. The pool belongs with the
second group's initializer (40,000 BSS bytes); the final group owns the remaining
9,336 BSS bytes. All these sections compare at 100% against the fresh splits.

The function counts are 58/59, 58/59, and 51/55 exact, retaining all 167 exact
functions. Comparing the second group to the old combined original object had
shown a false candidate-builder difference from a synthetic `R_PPC_NONE`
retention relocation; the freshly extracted second-group object resolves it.
This is a layout experiment, not proof of original filenames or a completed
source-link change. Source organization and complete linked validation remain
required before publication.

## Current-main integration checkpoint

Unchanged fork main `5146327538` was built in an isolated checkout with fresh
split objects and compiled sources. Its full check passed, including original
DOL SHA-1, 3,622 exact linked units, and all 19,177 retention entries. The lower
unit count reflects upstream consolidation, not lost address coverage.

Merge `e729b18b4c` incorporates that base. The integrated branch passes the full
check against the saved main report: eight additional exact functions, 5,260
additional matched code bytes, and 1,744 additional matched data bytes. A second
address-based comparison against the complete pre-integration branch report
also reports no regressions. The claimed unit still has six partial functions
and remains unlinked; publication awaits their exact matches and integration
of the validated data grouping.


## Exact lookahead conversion

`803EDF64` now matches all 896 bytes under the unchanged GC/1.2.5 profile.
The next input word is retained as `u16 raw`; its low byte initializes the
byte lookahead, while the comparison assigns the decoded value to the
halfword `next`. The first input byte is also an unsigned byte. This retains
the two native masks and the dependency that schedules the halfword copy
before the comparison. Ordering the byte, first-byte, next and state locals
then reproduces the remaining register allocation. An overwritten preliminary
assignment to `next` was removed and exactness rechecked. No new optimization
pragma or target-specific source operation is required.

The complete native instruction sequence was reached before declaration-order
refinement; the earlier candidate's higher aggregate score concealed a missing
mask. Read-only compiler traces distinguished that missing dependency from a
register-allocation difference. The private differential run passes the same
134,296 cases described above, including all six keyword rows, actual native
helpers, outputs, input preservation and nonvolatile registers. Both the tested
candidate and the version without the overwritten assignment are byte exact.

The complete build and `tools/check_pr.py` pass against independently validated
main `5146327538`: nine new exact functions and 6,156 additional matched code
bytes, with no losses. All 3,622 previously linked units remain exact and the
DOL hash passes. This brings the claimed unit to 168/173 exact functions; the
five remaining routines and eventual complete source linkage remain in scope.


## Shared-header layout check

The three provisional objects were rebuilt with one shared internal header and
separate ordinary C++ definition files, rather than three copies of the full
source. Against fresh original splits, the groups preserve 58/59, 58/59 and
52/55 exact functions: all 168 existing exact functions, including `803EDF64`.
Every allocated data section remains exact. The claim still covers all 173
functions and the complete original address span; the checked-in split and
linkset have not changed during this private organization trial.

The third group's BSS definitions must follow its function definitions under
the current compiler profile. Placing those definitions first lets the compiler
combine several named addresses through a common BSS base. That changes
`803EE580`, `803EE718` and `803EE828`, even though the data bytes stay correct.
Moving the actual definitions back after the functions preserves their native
address loads and all three exact matches. No synthetic padding or invented
aggregate is needed. The source organization still needs a final cleanup and
full linkage validation after the five remaining functions match.


A separate private link-only probe substitutes these three recovered objects
for the combined original object in the normal linker input list. The stock
linker succeeds; its diagnostics are identical to an unchanged control link.
The resulting ELF contains all 173 native function symbols and the expected
eight BSS objects and sizes, including the 40,000-byte pool and 8,288-byte DMA
buffer. This checks symbol resolution and retention only. The five partial
functions prevent an exact executable, and the accepted linkset and verified
build output remain unchanged. Final admission still requires the fresh
split/config retention workflow and complete original-DOL comparison.


## Accumulator scalar lifetime checkpoint

The `803EE2F4` candidate now compiles to the native 652-byte size and 104-byte
stack frame, improving from 95.74847% to 98.65031%. Its instruction sequence
agrees after register operands are abstracted; pointer-copy routing and register
assignment still differ, so this is not an exact-function gain. All 168 existing
exact functions remain exact. The name pointer is borrowed as a scalar value,
the encoded string gets a separate character-pointer handoff for its length
query, and the replacement length remains live through conversion and emission.
The second conversion uses the shared wide-buffer address directly. Only the
required depth-one inline and propagation controls remain in its scope.

A private PowerPC differential run passed 3,000 randomized multi-entry cases.
The native and recovered bodies both execute native `strlen` and `strncpy`;
controlled callbacks model the six list/conversion/emission boundaries and log
their arguments. Cases vary mode/state, selected slots, replacement versus
append paths, embedded terminators, entry lengths, item metadata and initial
name/encoded contents. Callback traces, emitted request contents, the name,
encoded, wide and input buffers, stack pointer and nonvolatile registers agree.
This is controlled-boundary behavioral evidence, not a full game execution or
proof of exact code.

Alternative measurements include 720 scalar declaration orders, const/register
qualifiers on the older aggregate view, temporary-view value conversions, and
borrowed header-offset/pointer and in-place-cursor forms for `803F03B4`. None
produced another exact function. The aggregate view's higher fuzzy score still
has an extra stack home; it is not the retained candidate. The compiler traces
and the repo's `kenkyuw-dispatcher-continuation.md` temporary-lifetime case guided
these checks. The whole-unit claim remains 168/173 exact and awaits the same five
remaining matches and final source-link integration.


## Header parser exact cursor update

`803F03B4` now matches all 332 bytes. The input pointer itself advances to the
first record using `cursor = cursor + cursor[2] + 3`, after computing the end
pointer from the two-byte length. This replaces a separate local cursor and
preserves the same pointer arithmetic and record traversal. No signature type,
layout, compiler option, or helper behavior changes.

The explicit addition assignment reproduces the native header temporary reuse;
its compound-assignment counterpart did not. Probes of borrowed header values,
separate offset helpers and cursor phases had retained the four differing
register operands. Comparing those data-flow differences led to reusing the
input parameter. All 168 previously exact functions remain exact. The full
repository check passes with no linkage or coverage losses; four functions
remain before complete-unit admission.


## Input decoder exact state lifetime

`803EDC20` now matches all 388 bytes, including its stack frame and register
operands. The inlined scan reads the current entry limit and returns both that
pointer and the encoded-byte count. A small decoder state holds the real
pending lead byte; its constructor sets that byte to zero. Depth-one inlining
and scoped propagation control preserve the native initialization copy and the
ASCII-path reset. This changes no external signature, storage layout or call.

The compiler trace of the scalar candidate showed that the scan's pointer
handoff changed interference with the entry count. Moving state loads alone
failed to resolve it. Making the pending byte an initialized state value fixed
the native zero handoff; declaring entry, code cursor and count in that order,
and ordering the independent ASCII-path increments as encoded count, code
cursor, entry cursor, then entry count completed the match. The same order
preserves the original per-character writes and bounds checks.

The direct full-object comparison retains all 169 previous exact functions and
adds the decoder. Three functions remain: cache replacement, group selection
and name accumulation. Complete-unit source-link admission is still pending.

The full repository check passes: +11 exact functions and +6,876 matched code
bytes versus main, no coverage or source-linkage loss, unchanged retention,
and the original DOL hash. All 3,622 currently linked units remain exact.


## Three-function continuation and refreshed full source link

The private three-group build now retains all 170 exact functions (58, 58 and
54 in the three groups). Every grouped data and BSS section still compares at
100%. A fresh stock-linker run includes all 173 function symbols and all eight
owned BSS symbols, whose extents agree with the original object. Its diagnostics
are byte-identical to the unchanged control link. This remains a private link
experiment, not admission to the accepted linkset or an exact-DOL claim.

For cache replacement, an inlined bucket value plus separate replacement and
insertion link locals now gives a private 776-byte candidate at 99.948456%.
Both scans, the write cursor, instruction ordering and stack frame agree; two
arithmetic register operands still differ. The clean size helper keeps metadata
width and the complete record size as separate, used values. Typed prefix
reads, constructor/reference forms, caller versus inline arithmetic boundaries,
integer types and optimizer controls have not yet closed those last operands.
The shared lookup used by exact rebuild functions must remain unchanged when
this candidate is integrated; its replacement lookup is separate.

The accumulator's separate wide-buffer reassignment improves its private score
to 98.895706% at the native size and frame. It passes the same 3,000-case
controlled-boundary PowerPC differential harness. A selector cursor object
increased fuzzy similarity but enlarged the frame, so it is not a better
retained candidate. Bound-reference, const-contract and borrowed-cursor probes
have not improved the native-frame selector. These experiments followed the
[TWW register-allocation guidance](https://github.com/zeldaret/tww/blob/main/docs/regalloc.md)
and compiler allocation/propagation traces; no instruction patch, physical
register pin, extra linked object or changed shared ABI was introduced.

## Cache replacement complete

`803E8DA0` now matches all 776 native bytes. Separate replacement and insertion
search helpers preserve their different temporary lifetimes. A bucket value
constructor supplies the first search index; the insertion helper retains an
ordinary scalar bucket. A distinct insertion-link result prevents the first
lookup's reference from extending into insertion.

The record length keeps its actual metadata count, encoded width and prefix
sum. Discarding the prefix assignment's expression value with a `void` cast in
the comma expression retains the native temporary handoff. Ordinary sequential
assignments differed in two register operands. No instruction bytes or physical
register selections are embedded in the source.

Six caller declarations from the direct reconstruction become unused after
inlining the search, size and writer helpers. They are explicitly retained for
the native 104-byte frame. Removing them produces the same instructions and
registers with an 80-byte frame (99.97423%). Sixty-four combinations passing the
actual scratch variables by reference did not preserve the exact allocation.
The retained declarations are documented matching debt, following the existing
NetworkRuntime and PPPoE frame precedents, not a claim about original source.
A port can remove them. The integrated comparison retains all previously exact
functions; group selection and request accumulation remain partial.

The integrated cache checkpoint passes `tools/check_pr.py`: original DOL SHA-1,
all 3,622 linked units, unchanged 19,177-entry retention list and no match losses.
Relative to current main it adds 12 exact functions and 7,652 matched code bytes.

## Accumulator pointer lifetimes and complete first group

The accumulator now reaches 99.386505% with all 652 native instruction bytes'
layout and its 104-byte stack frame retained. Directly initializing the name
pointer and borrowing the pointer at the replacement-copy call changes which
value the compiler preserves across calls. An explicit current-group index
then preserves the slot-selection/emission lifetime. The wide conversion
buffer is reassigned at the append handoff. The remaining differences are
register operands; this is still a partial function.

Compiler-stage traces showed the earlier borrowed initialization splitting the
main name-buffer value before register allocation. Follow-up experiments covered
borrowed call-site views, actual byte/string pointer types, complete copy and
request-emission helpers, standard register hints, constant pointer bases,
equivalent loops, and supported optimizer passes. The selector experiments also
covered real phase storage, cursor/bound value objects, local references and a
token-initialization helper. Higher scores with a wrong frame were not adopted.

The integrated accumulator passes 3,000 native PPC differential cases, including
buffer contents, callback arguments and preserved registers. `tools/check_pr.py`
passes against unchanged main `5146327538`, with 171 of 173 functions exact and
no loss of matches or source linkage. The source layout experiment is now 59/59,
58/59 and 54/55 exact functions across the three native groups. Group zero's
12,468 text bytes, 1,744 rodata bytes and 156 data bytes all match exactly; every
other data/BSS section also remains exact. A fresh stock-linker run using all
three source objects succeeds with diagnostics identical to the original-object
control. Final linked-unit admission awaits the selector and accumulator.

## Selector consolidation lifetime improvement

The selector now reaches 99.28287% with the native 1,004-byte extent and
80-byte frame. The input limit is used directly; an explicit token-input
pointer supplies the dictionary lookup. The consolidation cursor
initialization assigns the lookup result to `walk` and then `slot`, while a
separate `groupEnd` supplies the leading-entry count. Together these reproduce
the formerly different consolidation copy/load sequence. Register operands
still differ. Removing the bound wrapper also restores native prologue
scheduling; this selector refinement needs no additional compiler pragmas.
Declaring `first` before `selectedEnd` further improves register allocation.

The token-input temporary survives cleanup from an assignment expression to
an ordinary assignment followed by the consuming call. A search result that
hoisted slot lookup out of its loop was rejected as behaviorally invalid;
statement reordering was disabled for subsequent searches. Small arithmetic
helpers, cursor getters, equivalent address expressions and boundary wrappers
were tested without another improvement.

A private native PPC differential harness compares 3,000 selector scenarios.
It controls eleven external operations consistently on both sides, varies
initial token and node availability, selection modes and spans, early-return
and allocation failures, and group consolidation. Callback arguments, all
slot/entry/allocation storage, the shared selection mode and preserved
registers agree. Every controlled operation is reached. This validates the
refinement under those modeled callback behaviors; it does not replace the
remaining exact assembly comparison or complete-unit source-link admission.

## Follow-up allocation experiments

The retained selector is 99.28287%, with the native instruction sequence,
1,004-byte extent and 80-byte frame. Its 3,000-case native differential check
and the complete repository checks pass. A minimal standalone C translation
and a minimal C++ translation both reproduce that same score and extent, so
neither language mode nor unrelated declarations explain the remaining swaps.

Private compiler-state captures and a replay of the simplify/select algorithm
reproduce every current selector register assignment and the full 93-node
selection order. Searches over named-local declaration orders alone did not
improve this graph. A model that also permits reordering compiler-created
values can reach the native assignment; that model result is a diagnostic,
not a source match. The corresponding source-level lifetime reconstruction
remains unfinished.

The follow-up research used the existing
[TWW register-allocation guide](https://github.com/zeldaret/tww/blob/main/docs/regalloc.md)
and [GC/1.2.5 allocation observations](https://github.com/MarkMcCaskey/decomp-scripts/blob/main/mwcc-compiler-notes.md).
Trials covered declaration initializers, separate phase cursors, scoped
optimizer settings, actual inline operations, dependency-safe initialization
orders, and equivalent integer and pointer expressions. Aggregate variants
that changed the native frame were rejected. The accumulator's character
buffer and cast-spelling trials did not improve its retained 99.386505%.
No shared helper ABI or buffer declaration was changed for these experiments.

The next trials covered real token-install and slot-cleanup helpers, argument
snapshots, phase-local aggregates, following-entry preparation, equivalent loop
forms and a whole-selection inline driver. Scheduler, peephole, pointer-analysis
and dead-assignment controls did not improve the retained bodies. Accumulator
copy/validation helpers and explicit buffer-role locals also did not improve
99.386505%. These remain private experiments, not additional production
compiler controls or recovered exact functions.

An indexed token loop (`slot = first + tokenOffset`) compiles to the native
instruction sequence and 80-byte frame at 99.203186%. Its 3,000-case native PPC
comparison passes, including callback arguments, slot and node state, selection
mode and preserved registers. It supplies a different valid search seed; the
higher-scoring retained selector is unchanged. A separate aggregate-endpoint
search reached that score with an index assignment expression, but rewriting
the expression as a separate statement changed the frame to 88 bytes. Candidate
cleanup therefore requires a fresh complete-object comparison.

Another path disables CSE and reconstructs value reuse explicitly: distinct
validation and pruning cursors, an entry-end snapshot, a separate consolidation
index and a direct input limit for the group count. Loading the pruning head
before forming its link restores the native instruction order. A fresh allocator
capture and replay reproduce all 89 selected nodes. A modeled declaration order
then compiles at 99.203186%, with the native instruction sequence and frame but
remaining register differences. This is an alternative source investigation,
not completion or admission of the unit; the branch still has 171 of 173 exact
functions.


The next selector refinement retains a selected-slot assignment expression,
selection-boundary snapshot and signed initial-span snapshot. An intermediate
aggregate version reached 99.50199% but enlarged the frame to 88 bytes; removing
the endpoint aggregate and token-install alias restores the native 80-byte
frame and improves the score to **99.52191%**. The native instruction sequence
and 1,004-byte extent are unchanged. The remaining differences are 22 register
operands in token initialization and consolidation. The 3,000-case native PPC
comparison and complete `check_pr.py` checks pass with this retained source.
These snapshots express real consumed values, but their assignment forms are
matching constraints: equivalent separate statements change allocation.

The compiler trace reproduces all 93 selected nodes for this refinement.
Another 100,000 declaration-order model trials do not improve its remaining
three value assignments. Typed cursor fields, reversed initialization orders,
an inlined consolidation phase and optimization levels 2–4 were compiled as
alternatives without a retained improvement. An explicit-reuse variant with
borrowed workspace storage allows the model to reproduce the named native
registers, but actual compilation still changes initialization scheduling and
cursor uses; model agreement alone is not an exact source result. The whole
unit remains at 171 of 173 exact functions and is not yet admitted or ready for
the requested completion PR.


The accumulator now reaches **99.81595%**, retaining its native 652-byte extent
and 104-byte frame. A branch-local name pointer is shared by the initial copy
and length check; the conversion borrows its encoded destination. The append
and request paths use the actual global buffers directly. This restores every
body instruction and register operand. The only differences are the order of
the name and encoded-buffer address materializations in the prologue. No ABI,
global declaration, or optimization setting changed.

The cleaned integrated source passes the 3,000-case native PPC comparison,
including native string functions, conversion/emission callback arguments,
buffer writes and preserved registers. `tools/check_pr.py` passes the original
DOL check, all 3,622 linked-unit checks, retention and no-loss checks. The private
three-file source layout was regenerated and linked again: all 171 exact
functions and every data/rodata/BSS extent remain exact. Comparing every
loadable section with the original executable finds **28 differing bytes**:
24 in the selector and 4 in the accumulator, with none elsewhere. This private
link is evidence for the remaining work, not production admission or a 100%
completion claim.

The next investigation follows the first-differing-priority approach described
by [mwcc-debugger](https://github.com/cadmic/mwcc-debugger). A second accumulator
variant reaches 99.7546% with exact instruction order and frame; its append-only
name pointer is allocated ahead of the end bound, conversion pointer and slot
table, shifting four register choices. Compiler captures identify the relevant
cost/degree ordering. Typed array/pointer accessors, local reference bindings,
phase snapshots and scheduling controls were tested without resolving both
remaining functions. The inline-search adapter was also corrected to preserve
generated helpers preceding the target function, and fresh searches reproduce
their baseline scores before mutation. The unit remains 171/173 exact and its
claim remains active until the full source unit is exact and linked.


## Exact selector and four-byte complete-link remainder

`803EA9E8` now matches all 1,004 bytes, including its original `0x50` frame.
The retained implementation names the input bound, separates validation and
pruning cursors, and wraps the actual best-entry call in `select_download_length`.
That helper returns its consumed result through a local value. The group begins
with `slot = lookup`, `walk = slot`, then reads both its initial signed span and
flag through `walk`. This gives MWCC the native pointer copy and load order.
Reading those fields through `slot` instead allows the forward peephole pass to
fold the flag load into the preceding address addition and move it too early.
A search-generated unused header snapshot was removed before retention; the
cleaned, formatted implementation remains exactly matching.

The final selector object passes the 3,000-case native comparison harness:
callback arguments, slot and node mutations, failure paths, consolidation,
mode, and preserved registers agree. The complete `tools/check_pr.py` gate also
passes, including the original DOL, no regressions, all 3,622 already linked
units, and the 19,177-entry force-active inventory.

Regenerating all three genuine source groups gives 59/59, 59/59, and 54/55
exact functions, with all data, read-only data, and BSS exact. A new stock-linker
full-source executable preserves every loadable section's address and extent.
It differs from the original by **four bytes total**, all in `803EE2F4`'s two
buffer-address loads; the selector and every other byte agree. The unit is now
172/173 exact. Source admission and the complete-unit PR remain pending the
accumulator's final exact match.

For that remaining routine, stock-compiler allocation traces also reproduce
an alternative with exact instruction ordering and a three-way rotation of
the end, encoded-buffer alias, and slot-table registers. Source-only buffer and
loop-bound experiments continue against both alternatives; no compiler or
object-code patch is part of the implementation.
