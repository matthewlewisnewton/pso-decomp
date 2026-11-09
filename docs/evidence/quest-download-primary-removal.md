# Primary byte-page removal (partial)

`sub_803EF208` (`0x803EF208`, 816 original bytes) is now defined as partial
C++: **95.303925%, 808 compiled bytes** in the standard and relocation-sensitive
reports. It removes a matching message from a primary cached page. It adds no
exact function or source-linked coverage.

## Real request and borrowed-name boundaries

The frontend and provider formerly declared the same C entry points using
different local request structs. Equal offsets did not make those C++ types
identical. The existing `Req_803EEF2C` definition now lives in the already shared
`QuestDownloadRecords.h`; former frontend/message views are typedef aliases.
The frontend constructs this actual request object, without overlay-casting it.

The native request is 16 bytes, aligned to four: borrowed name pointer at zero,
signed halfword length at four, byte at six, kind at seven, optional byte at
eight, and borrowed text pointer at twelve. Header checks cover its size and
accessed offsets; a private assertion-only native compile checks alignment.
The frontend's existing packet word is converted to the text pointer when stored
in this request. This is a native 32-bit address-carrier boundary, not evidence
of ownership or an arbitrary input extent. No shared scratch buffer is retyped.

`find_name_index` previously represented name bytes as a server `this` pointer.
Its body accesses no server object. It is now a provisional `extern "C"`
function retaining the exact native link name and taking `const char *name`.
Four existing calls and the new remover use that byte API; the nonvirtual class
declaration is removed. The function and prior callers remain byte-identical.
Other legacy member and storage interfaces are not declared resolved by this repair.

All 16 frontend function bodies, allocated bytes/layout, objects and normalized
relocations are preserved. Class layout, existing native symbols and all previous
provider function matches remain unchanged.

## Preserved removal behavior

The entry returns minus three for an invalid handle and minus six for mode
`0x8000`, before request access. It copies the bounded name into an 80-byte local,
finds its primary page, locates the page's two-byte terminator, and searches
sorted records using their stored name lengths. A name or message miss returns
zero without reference reset or dirty marking.

The existing `EEFC8` helper matches kind and encoded text, ignoring the stored
value/index and request optional byte. It returns zero for no match, minus one
for the sole message in a record, or a positive removed-byte count after already
compacting the record and reducing its length.

For minus one, the remover copies the tail from the old record end down over
the whole unchanged record. For a positive count, it starts the tail at
`record + new_length + removed_count`, the old record end. Both paths copy both
terminator bytes and preserve the stale suffix beyond the new terminator. A
removal then clears all 128 reference counts, marks the current page active and
returns three. No extra cleanup or validation policy is introduced.

The record cursor now starts directly at the cached page and remains live while
a second cursor locates its terminator, matching the native data-flow roles.
Whole-record removal uses a separate advancing destination cursor for the
constant-displacement tail copy. The helper chooses backward copying for a
positive displacement and forward copying for a negative displacement; its
source and shifted destination ranges must belong to the same backing array.
Backward pre-decrements occur only inside the range test, so an empty span or
a span starting at the first array element forms no before-array pointer.
The actual whole-record call uses negative displacement `-size`, with source
`record + size` and destination `record`. Partial-message compaction retains
its existing helper and already-compacted record-length handling.

Names must fit the local and page chains must be bounded and terminated. The
helper's 128-byte encoded-text local additionally requires width at most 127;
complete two-byte output units give at most 126 in the demonstrated inputs.
Request backing storage and the cached page must remain valid through the call.
These are unchecked native preconditions, not an arbitrary-input safety proof.

## Bounded instruction and independent-memory checks

The initial 456-case run retained the previous 234 lifecycle/packet cases and
adds 78 removal cases plus 144 dedicated name-index cases. Candidate execution
uses the recovered remover and the actual name search, cached-page hit,
`EEFC8`, reference-reset and dirty-state helper instructions.

The removal oracle independently edits a record/message list, constructs the
new active record and copies the old tail/marker into a complete expected
memory snapshot. It checks all nonstack data, including untouched request bytes,
all reference-count cells and stale page suffixes. Cases cover:

- first/middle/last records and messages, sole-message records, misses and
  lexical-prefix stops;
- optional bytes, different stored values and duplicate kind/text pairs where
  only the first match is removed;
- empty/ASCII/SJIS text through encoded width 126, two full 1,022-byte pages,
  and tail copies of 2/8/9/10 bytes around unrolled-loop boundaries;
- invalid-handle/read-only guards with a null request pointer.

The primary-page tests arrange an already cached page. They do not exercise a
cold miss or the complete I/O provider. Name search initially uses a trivial
floor row there; separate fixed-table cases exercise 1/2/3/5/16/127-row searches,
nonzero lower bounds, equality, four-byte prefixes, gaps and below/above bounds
against an independent floor model, without modifying input/table bytes.

Native/candidate nonstack memory, meaningful returns and normalized provider
traces agree. `strncmp` trace normalization records bytes examined through its
logical mismatch/NUL stop; unread stack padding is not treated as an input.
Stack-pointer/nonvolatile restoration is checked on successful returns.
String/lifecycle I/O hooks and finite test inputs remain bounded; this is not
full-provider, exhaustive alias, malformed-page or shipped-flow proof.

The current 528-case [lifecycle corpus](quest-download-cache-lifecycle.md)
retains all 456 cases and adds the direct reload boundaries documented there.
It passes with the updated removal body, including the independent full-page
oracle, marker/stale-suffix comparisons and existing lower-level witnesses.
The model script SHA-256 remains
`433f38840a9da1bdcb556691421074ac3440761553dbf1865a3a968a089d989c`;
the current compiled candidate SHA-256 is
`edbb4d36652ead814aadf48ae1ad078dff69144d122e29a976bd1ccb01ba0e71`.

A separate host C++98 test extracts the exact new helper and checks 980 valid
same-array cases against `memmove`, comparing every byte of the buffer. It
covers both overlap directions, disjoint ranges, zero displacement and empty
spans, including an array-start source. AddressSanitizer and
UndefinedBehaviorSanitizer pass; leak detection is disabled because the traced
runner does not support LeakSanitizer, and the helper/test buffers allocate no
dynamic storage. This supplements the native negative-displacement tests; it
does not establish PowerPC code generation or broader provider behavior.
Its source SHA-256 is
`caa1ade5088d0f7f3bfd36a6f3e6f96e71c0ea482d89a213c8f1092129577bd5`.

## Remaining work and held boundaries

At the initial checkpoint, four combinations of the two existing byte-shift
helpers were measured. The helper retained in both branches scored 86.40686%; the other combinations scored
84.34804%, 85.45098% and 85.303925%, all at 868 bytes, without exact regressions.
None of those alternatives was adopted. The later record-cursor change measured
87.65686% at 868 bytes. An explicit-destination interface measured 93.44118%
at 820 bytes. An initial advancing-cursor helper measured 97.411766% at 820
bytes but retained before-array pointer formation for some generic positive
copy inputs. The adopted range-safe helper scores 95.303925% at 808 bytes,
60 fewer than the initial recovery and eight fewer than the original.
Remaining differences include register/stack allocation and copy-loop lowering.
No pragma, padding, new enclosing object, null guard or pointer/status
sentinel is introduced. All 168 compiled candidate bodies bind to the native
build checkpoint; the other 167 bodies, all 16 frontend functions and provider
noncode data/layout/relocations are preserved. Full native/no-loss results and
exact-head independent review accompany publication.

At the initial removal checkpoint, the conversion target `EDF64` was left undefined: its frontend still names a
byte-owned shared buffer through a historical signed-halfword view. A signedness
change alone would not establish a live halfword array. `B4D4` also needs its
four-byte label versus five-byte NUL-scanned string boundary resolved. Existing
shared scratch/ID/lifetime holds remain in place; none is bypassed here.

The remover has its own handle/mode guards, not the separate `7900` mode guard.
Its observed frontend request is 31, omitted by the identified ordinary dispatcher
wrappers. This source recovery provides no enabled shipped mutation trace and
does not turn lower-level witnesses into claims of shipped failures. Earlier
[reachability caveats](quest-download-cache-relocation.md) still apply.

The unit remains **159/173 exact, five undefined and nine partial, unlinked**.
The separate search pointer-sentinel sign-off remains unresolved.
The separate [byte-consumer recovery](quest-download-byte-conversion.md) defines
`EDF64` as a partial without clearing the frontend producer's lifetime hold.
