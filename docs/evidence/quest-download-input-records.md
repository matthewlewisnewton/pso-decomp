# Quest-download input records and partial DC20 recovery

The input table at `0x805A0498` is a real `0x138`-byte object in
`TQuestVmDownLoadServer_803E6970.cpp`. It is now defined as
`QuestDownloadInputEntry[39]`, replacing the scalar-plus-padding wrappers
and alternate local record views. Its two record cursors,
`lbl_805D78C4` and `lbl_805D78C8`, have the same record-pointer type.

| Offset | Field | Evidence |
| --- | --- | --- |
| +0 | `u16 ch` | 6970 and 6B70 read the halfword; DC20 writes it |
| +2 | `u16 reserved` | No interpretation or new write is introduced |
| +4 | `s32 len` | 6B70 and sum_entry_sizes read it; DC20 writes 1 or 2 |

All of these consumers advance eight bytes. Native A428 also reads +0 at
eight-byte strides. The original symbol extent is 312 bytes, giving 39
records; the append limit of 36 does not justify shrinking that object.
Compile-time checks cover the record extent, both accessed field offsets,
and the complete table extent. The actual definition stays in place with
the same linkage, alignment and object order. This supplies real static
record lifetimes; consumers no longer reinterpret the padding wrapper as
an array. The unrelated raw input buffer and its existing interfaces are
not retyped by this change.

## DC20 behavior

`TQuestVmDownLoadServer__sub_803EDC20` (`0x803EDC20`, 388 original bytes)
now has a C++ definition. It scans existing input characters to count their
encoded width, consumes pending Shift-JIS lead/trail pairs, skips rejected
characters, and appends character/length/code records. The initial width
scan is a real helper in the existing inline region; no pragma or compiler
option is added or changed.

The existing packet entry point takes a `u32` input address. Converting
that actual native address carrier to a byte pointer is confined to the
entry boundary. This retains the existing consumer ABI; it is not a claim
that a 32-bit carrier is a suitable interface for a wider-pointer port.
The shared C69C and C8D8 converter interfaces are unchanged.

The native capacity checks distinguish double-byte appends
(`count < 36 && encoded < 78`) from single-byte appends
(`count < 36 && encoded < 79`). The 39-record table and 40-byte code array
fit those accepted writes when the initialized cursors and count are
consistent. Existing consumers still require valid start/count ranges;
this is not an arbitrary-state bounds proof.

On capacity failure, DC20 returns integer `-1` immediately. Earlier stores
can remain, while the cursor/count globals are published only after the
whole input succeeds. Reserved halfwords remain untouched. No rollback,
extra initialization, pointer sentinel, or new allocator contract is
introduced.

## Current recovery status

DC20 is **inexact: 94.41237%**, with the correct 388-byte extent. It is
intermediate implementation progress and adds no exact function or
source-linked coverage. The remaining differences concern:

- pending-lead initialization and the accumulator's zero-seed copy;
- the temporary scan end versus persistent entry cursor coalescing;
- testing the converter result's low halfword through r0 versus r3;
- single-byte append constant registers and store/increment scheduling.

The current-head private type-only control preserved every allocated
section byte and layout, global object layout, and symbolic allocated
relocation. Adding DC20 preserved all 159 previously exact functions and
all noncode bytes/layout. Final full-build/no-loss results are recorded
with the published checkpoint; equal function extent alone is not evidence
of exactness or source linkage.

The record reconstruction and partial converter were independently
reviewed as a bounded continuation. Earlier private work at
`0da93e5d79316cad3d9dbe8bfd408284f41a6684` supplied useful evidence, but its
older dependency stack, propagation pragma and historical behavior tests
are not imported or treated as validation of this composition.

### Follow-up on the published source

At source checkpoint `dc0f10db1`, seven changed data-flow variants plus the
unchanged control tested shared zero resets, a word-sized conversion result
with a low-halfword test, an explicit mask, and combinations of these forms.
Most reproduced the same 388-byte, 94.41237% body. The redundant explicit
mask produced 392 bytes at 93.329895%. No variant was adopted, no shared
converter interface was widened, and no impossibility claim follows.

A fresh bounded comparison of the actual original/current instructions and
an independent append model passed 3,000 initialized valid states: 1,951
successes and 1,049 errors, including 639 errors retaining partial writes.
It compared complete data memory, native/source stack bytes, provider calls,
SP restoration and nonvolatile registers. It uses the actual character-pair
conversion formula and a bounded opaque code-mapper callback. This is not
full-provider, malformed-state, exhaustive safety, exactness or linkage proof.
The private control's allocated bytes match the previously validated native
checkpoint; historical tests from the frozen stack are not substituted for
this new run.

The containing unit remains incomplete and unlinked. This input recovery
did **not** resolve the then-pending search pointer-sentinel decision. The later
[named macro decision](quest-download-search-evidence.md) is separate from the
shared-storage and input-boundary limitations retained here.
