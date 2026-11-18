# Chat predicate full-word return contract

This checkpoint follows `5a4168109a93513a882cf7fa3a41a42336c904ac` and
resolves only the outer helper's return-type inconsistency identified in
[the receiver-cohort note](window-chat-predicate-receiver.md).

The existing original-object census finds five direct calls to 8024701C across
four units. Four callers compare the full returned word with zero; the fifth
forwards it unchanged. Their reconstructed declarations already return s32.
The original callee constructs full-word 1 for its first two successful branches
and normalizes the final hardware-helper result to 0/1. This supports an integer
predicate contract, not unique original signedness or source spelling.

The definition and local declaration now return s32. Early returns preserve the
composer query before the flag read, and the flag test before the conditional
hardware query. The latter is evaluated once and returned as an integer 0/1.
No receiver, field access, allocation, null handling or helper ownership changes.

## Bounded compiler experiment

An initial s32 local-result/common-return form with an integer ternary was
semantically sound but did not match. It changed the final normalization from
`subfe r3,r0,r3` to `subfe r0,r0,r3` followed by `mr r3,r0`, growing the helper
from 100 to 104 bytes and shifting subsequent definitions. The original DOL
check failed and the report lost this one 100-byte exact function. That candidate
was rejected and the unchanged source rebuilt; complete object and DOL identity
was verified before testing the distinct early-return form. No compiler controls,
assembly or relaxed validation were introduced.

The early-return form reproduces the original 100-byte helper and entire object.
The capacity-gated full build passes with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 3,626 active compiled objects,
identified from the unchanged objdiff configuration, are raw-byte-identical to
the freshly rebuilt unchanged control. This includes full section payloads,
symbol metadata, data, tables and relocation records. The generated Ninja graph,
split configuration and DOL are also identical, preserving ordered link inputs.
The wider captured inventory of 8,705 objects is identical as well, but includes
original and inactive files and is not the active compiled-unit count.

Aggregate checks pass against the preceding head: no matched function/code/data,
linked unit or coverage changes; 3,616 linked units remain exact and 19,528
retention names have no drift. Comparison with the existing independently built
pinned main `7ebf37b81371f6c04b17fceb9120716255d4f02d` also passes. Its inherited
qualified coverage tails remain unchanged; this does not establish new padding
provenance or claim validation against later main commits. All 346 tool tests
and the portable behavior and ASan/UBSan targets pass. Independent source review
accepts the early-return semantics and limited contract correction.

The observed callers still use mixed int/u32/void* parameter declarations versus
the definition's TWindowChat*. This is not a fully reconciled portable signature.
The historical export spelling is retained; original member ownership, raw
hardware-helper ownership, borrowed lifetimes, Hard table extent and all other
window-family holds remain. No matching coverage is newly recovered.
