# Byte-input conversion consumer (partial)

`sub_803EDF64` (`0x803EDF64`, 896 original bytes) now has a partial C++
implementation. It is **60.044643% in the standard report, 59.848213% in the
relocation-sensitive comparison, 1,016 compiled bytes**. The first published
byte-consumer recovery was 1.3303572% / 0.22767857% and 1,580 bytes. Sharing the
prefix copy and recovering an advancing cursor removes 564 compiled bytes.
This remains a partial with instruction, register and size differences, not
an exactness or linking gain.

## Consumer boundary and preserved behavior

The provisional entry borrows `const u8 *input`; its count remains in
halfwords, matching the native ABI. Live input-word reads decode two bytes in
native big-endian order. The definition of `quest_download_text_buffer` remains the actual
`u8[0x404]` owner. No halfword array or union is invented over that storage.

The existing keyword and fallback lookups accept halfword ranges. When the scan
reaches them, it copies the needed representation once into a real local
`u16 words[4]` using ordinary `memcpy`. This copies four, six or eight bytes on
the native big-endian target; it is not a typed view over the global bytes or
a claim of host-endian portability. Keyword lookup borrows all initialized
words, then fallback borrows one fewer only if keyword lookup returns null.
Both lookups return a table pointer or null, and neither retain nor modify
their local input. No intervening input write requires a second copy.

The advancing byte cursor names word `consumed - 1`, with two-byte steps after
the count-exit check. Lookup sees at most four keyword words or three fallback
words; a fifth scanned word is rejected before another lookup. The state used
only by the multiword branch lives in a block ending before the mapping labels,
so the early vowel path bypasses no initialization. The separate readonly table
ownership boundaries are unchanged.

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
consumer, all five actual lookup/mapping helper bodies and the actual native
80-byte `memcpy`. It does not hook the copy's result. The readonly tables
are loaded privately from the original-hash-verified DOL; raw table contents,
derived keyword inputs and disassembly are not committed.

The **72,676 cases** include every single low byte with five attribute patterns
and both modes, all 65,536 low-byte pairs, bounded longer/random inputs, 512-word
inputs and limited representation-alias diagnostics. Review identified that
the initial fixed samples missed keyword successes. The final run derives
upper/lowercase cases from all six private keyword rows, reaches all six, and
asserts that a keyword hit skips fallback. The shared-copy continuation adds
192 keyword-derived alias diagnostics. Coverage records **240 keyword hits,
568 keyword misses, 490 fallback hits and 78 fallback misses**, and **808 native
prefix copies** of four, six or eight bytes. Each copy also checks nonoverlap
with the actual local destination; lookup-value traces and nonstack memory
comparisons check its effects.

The comparison checks complete nonstack data, meaningful returns, stack pointer
and nonvolatile restoration, lookup input values and actual returned table
pointers. Copying into a local prefix changes the borrowed address; normalization
compares the values and count consumed by the real lookup, not local addresses.
It does not substitute a lookup result hook.

A separate **2,259-case native sequence run**, with **42,904 consumer calls**,
executes the unchanged frontend producer, actual native copy and JIS-to-SJIS
helper around both consumer bodies. It compares all nonstack bytes, returns, preserved registers,
consumer inputs and the untouched four-byte scratch tail. It includes source
lengths 511, 512, 513 and 700, empty inputs, both packet flags/modes and limited
aliases. This demonstrates bounded native phase agreement, not a C++ lifetime,
arbitrary-alias, whole-provider or shipped-flow proof.

The consumer object SHA-256 is
`0c60fe30714c1d40df9293be2719e37d684af73836f58ecc433ea8389bd26033`.
The direct differential script SHA-256 is
`c0da2ccea97a299f64e3834676054d9f553e74e911d55cce23dd48204f075e15`;
the frontend sequence script SHA-256 is
`a763f78e99b93c0850f2a45b33b9576628a14b811e6a5805a9ff612e7c1a7145`.

The extracted changed function and declarations also pass standard C++98 syntax
checking with pedantic errors. This specifically checks that recovering branch
lifetimes does not rely on CodeWarrior accepting a jump past an initialization.

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

The shared-prefix pointer loop measured 36.513393% at 1,224 bytes; the ordinary
copy measured 57.83482% at 1,016 before branch-local state/cursor initialization.
Advancing the output pointer instead of indexing its second element regressed
to 59.424107% at 1,020 bytes; capturing the first full word over the original
short lifetime left the best result unchanged. Neither was adopted. All probes
preserved the prior exact functions. No new pragma or compiler override was used.
The retained function remains 120 bytes larger than the original. Its explicit
representation loads, real prefix copy, register allocation and scheduling still
need work; these results do not establish that exact source is impossible.

Existing 159 exact provider functions, eight prior partial scores and all 16
frontend functions are preserved. Native build/no-loss checks, allocated-data
and relocation comparisons and exact-head source review accompany publication.
The unit is **159/173 exact, five undefined and nine partial, unlinked**.
The search pointer-sentinel decision, shared-storage holds and earlier
[reachability caveats](quest-download-cache-relocation.md) remain unresolved.
