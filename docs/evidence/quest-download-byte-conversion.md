# Byte-input conversion consumer (partial)

`sub_803EDF64` (`0x803EDF64`, 896 original bytes) now has a partial C++
implementation. It is **1.3303572% in the standard report, 0.22767857% in the
relocation-sensitive comparison, 1,580 compiled bytes**. This is algorithm recovery with substantial remaining
instruction, register and size differences, not an exactness or linking gain.

## Consumer boundary and preserved behavior

The provisional entry borrows `const u8 *input`; its count remains in
halfwords, matching the native ABI. Two byte loads decode each native big-endian
input word. The definition of `quest_download_text_buffer` remains the actual
`u8[0x404]` owner. No halfword array or union is invented over that storage.

The existing keyword and fallback lookups accept halfword ranges. Their
adapters copy the needed prefix into a real local `u16 words[4]` and borrow it
only for the synchronous lookup. Both lookups read the prefix, return a table
pointer or null, and neither retain nor modify the local input. The consumer's
scan reaches these calls with at most four keyword words or three fallback
words; a fifth scanned word is rejected before another lookup. The separate
readonly table ownership boundaries are unchanged.

The recovery retains the classifier, initial state/output writes, mode-dependent
key mapping, doubled-letter and apostrophe cases, keyword/fallback selection,
one/two output words and integer error returns. Output count is initialized
before the branches, and unsuccessful conversion can leave a partial output.
The second output conversion reads its input word after the first output store,
preserving the native order for overlapping representations. Class zero is
absent from the pinned classifier; the recovery adds no invented validation for
other classifier contents, invalid extents or arbitrary input counts.

The frontend call declaration now uses the same byte-input boundary, with an
explicit character-representation conversion at the call. Its producer still
uses the historical signed-halfword view of the byte-owned shared storage.
**That source-level lifetime and storage hold remains unresolved.** Byte-safe
consumer reads and native execution agreement do not establish that producer's
C++ array lifetime. The source pair is not declared ready to link.

## Bounded native checks

The private instruction differential executes the original and compiled
consumer plus all five actual lookup/mapping helper bodies. The readonly tables
are loaded privately from the original-hash-verified DOL; raw table contents,
derived keyword inputs and disassembly are not committed.

The **72,484 cases** include every single low byte with five attribute patterns
and both modes, all 65,536 low-byte pairs, bounded longer/random inputs, 512-word
inputs and limited representation-alias diagnostics. Review identified that
the initial fixed samples missed keyword successes. The final run derives
upper/lowercase cases from all six private keyword rows, reaches all six, and
asserts that a keyword hit skips fallback. Coverage records **96 keyword hits,
520 keyword misses, 490 fallback hits and 30 fallback misses**.

The comparison checks complete nonstack data, meaningful returns, stack pointer
and nonvolatile restoration, lookup input values and actual returned table
pointers. Copying into a local prefix changes the borrowed address; normalization
compares the values and count consumed by the real lookup, not local addresses.
It does not substitute a lookup result hook.

A separate **2,259-case native sequence run**, with **42,904 consumer calls**,
executes the unchanged frontend producer and JIS-to-SJIS helper around both
consumer bodies. It compares all nonstack bytes, returns, preserved registers,
consumer inputs and the untouched four-byte scratch tail. It includes source
lengths 511, 512, 513 and 700, empty inputs, both packet flags/modes and limited
aliases. This demonstrates bounded native phase agreement, not a C++ lifetime,
arbitrary-alias, whole-provider or shipped-flow proof.

The consumer object SHA-256 is
`ca7e5093ff88abe80dc5977bde379daa49a08e47b7bde8d94835e048a8704dd2`.
The direct differential script SHA-256 is
`4d85463f6662f8d7d1b344b701c85e8d9297ac94586493ad542c82629152edf1`;
the frontend sequence script SHA-256 is
`264f74cef030f06795982441d63708f7045a344b61058b3abeeb3f80b322a531`.

## Shared-buffer investigation and remaining work

The frontend writes at most 512 halfwords in the first `0x400` scratch bytes,
adds no terminator, and consumes them synchronously. This does not establish
exclusive access through every callback or repair the source-level view.
Later ID-list construction and byte-list serialization reuse the same storage;
their capacity, callback and ownership boundaries remain held. Adjacent ID
deduplication does not establish a global unique-count bound. No larger array,
union or padding is introduced as a substitute for those proofs.

Private attempts to repair the exact frontend producer using scalar `memcpy`,
explicit byte stores or a placement-created halfword array all regressed its
existing exact body. Even the best source-order-preserving explicit-byte form
scored 96.768295% at 336 bytes versus the original 328. None was adopted. An
earlier byte-store diagnostic changed source-read/store ordering under aliases
and is not evidence of an equivalent repair. These finite probes are not an
impossibility proof; an honest exact producer boundary remains future work.

Existing 159 exact provider functions, eight prior partial scores and all 16
frontend functions are preserved. Native build/no-loss checks, allocated-data
and relocation comparisons and exact-head source review accompany publication.
The unit is **159/173 exact, five undefined and nine partial, unlinked**.
The search pointer-sentinel decision, shared-storage holds and earlier
[reachability caveats](quest-download-cache-relocation.md) remain unresolved.
