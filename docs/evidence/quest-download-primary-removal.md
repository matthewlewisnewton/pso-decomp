# Primary byte-page removal (partial)

`sub_803EF208` (`0x803EF208`, 816 original bytes) is now defined as partial
C++: **86.40686%, 868 compiled bytes** in the standard and relocation-sensitive
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

Names must fit the local and page chains must be bounded and terminated. The
helper's 128-byte encoded-text local additionally requires width at most 127;
complete two-byte output units give at most 126 in the demonstrated inputs.
Request backing storage and the cached page must remain valid through the call.
These are unchecked native preconditions, not an arbitrary-input safety proof.

## Bounded instruction and independent-memory checks

The private 456-case run retains the previous 234 lifecycle/packet cases and
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

## Remaining work and held boundaries

Four combinations of the two existing byte-shift helpers were measured. The
retained helper in both branches scores 86.40686%; the other combinations score
84.34804%, 85.45098% and 85.303925%, all at 868 bytes, without exact regressions.
No alternative was adopted. Remaining differences include copy-loop lowering,
register/stack allocation and scheduling. No pragma, padding, new enclosing object, null guard or pointer/status
sentinel is introduced. The 167 modeled provider functions and all 16 frontend
functions bind to the native build checkpoint; full native/no-loss results and
exact-head independent review accompany publication.

The conversion target `EDF64` was left undefined: its frontend still names a
byte-owned shared buffer through a historical signed-halfword view. A signedness
change alone would not establish a live halfword array. `B4D4` also needs its
four-byte label versus five-byte NUL-scanned string boundary resolved. Existing
shared scratch/ID/lifetime holds remain in place; none is bypassed here.

The remover has its own handle/mode guards, not the separate `7900` mode guard.
Its observed frontend request is 31, omitted by the identified ordinary dispatcher
wrappers. This source recovery provides no enabled shipped mutation trace and
does not turn lower-level witnesses into claims of shipped failures. Earlier
[reachability caveats](quest-download-cache-relocation.md) still apply.

The unit remains **159/173 exact, six undefined and eight partial, unlinked**.
The separate search pointer-sentinel sign-off remains unresolved.
