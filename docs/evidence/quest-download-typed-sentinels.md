# Typed download-list sentinels and slot state

This continues the named-word decision at PR #366 head
`985b2c2c56c067a176a229237046220c18ca90c7`. It improves the source representation;
it adds no matching or linkage coverage and does not recover original spelling.

## Semantic pointer names

The search/caller cluster now uses typed names for four different roles:

| Name | Pointer type and role |
|---|---|
| `QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE` | `QuestDownloadMatchToken *`, unavailable slot input |
| `QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED` | `QuestDownloadSegment *`, failed segment search |
| `QUEST_DOWNLOAD_ENTRY_LIST_FAILED` | `QuestDownloadEntryNode *`, failure propagated by the entry generator |
| `QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE` | `QuestDownloadItemNode *`, item input skipped by the consumer |

Each preserves the native all-ones word. Six comparisons now compare pointers
directly with their semantic names, replacing five pointer-to-integer views and
the prior token comparison cast. The generator's existing `void *` boundary
remains; returning the typed entry sentinel uses an ordinary pointer-to-void
conversion. No signature, cleanup, allocation, traversal or skip order changes.
The three result/item macros and common word macro remain local to this cluster;
the token-unavailable name is shared with the slot declaration and its resets.

NULL still means an empty result or allocation exhaustion, and a returned list
is still traversed and released only after excluding failure. The consumer's
separate integer allocation error remains `-1`. These contracts are not merged.

[Melee's typed reserved pointers](https://github.com/doldecomp/melee/blob/2f8eab8ebd7a2d25541e125abfa246defe1bacec/src/sysdolphin/baselib/texp.h#L10-L12)
and [direct comparisons](https://github.com/doldecomp/melee/blob/2f8eab8ebd7a2d25541e125abfa246defe1bacec/src/sysdolphin/baselib/texp.c#L11-L23)
provide an idiom precedent. [Twilight Princess's three-way pointer result](https://github.com/zeldaret/tp/blob/c8fa8c9e2aab72cf4e5db0e5d1c84a9ea6ee6eb0/libs/JSystem/src/JKernel/JKRDvdAramRipper.cpp#L22-L53)
uses its non-null sentinel for a different local meaning. Neither project proves
PSO's source, semantics or portable integer-to-pointer behavior. PSO's native
instructions establish the roles above; the conversion remains target-specific.

## Slot+0 audit

An audit of all 4,968 active original objects found named slot/workspace
references only in the provider (46 relocations) and frontend (14). It excluded
21 stale physical objects. The private census SHA-256 is
`fc42cc819e9842a6ef42519d505b7afc1be33d8a28349f286f1abbfdcf359586`.
Native data-flow review follows derived member addresses as well as named
relocations. This is a bounded named-reference audit, not a claim about every
possible computed address or shipped execution.

| Boundary | Observed slot+0 operation |
|---|---|
| `init_entries`, `0x803EAF2C` onward | Stores all ones across 80 slots |
| Full reset `sub_803EADD4`, store at `0x803EADF4` | Stores all ones; the other reset mode preserves slot+0 |
| Retained `sub_803EA9E8`, `0x803EAA34..0x803EAA6C` | Checks unavailable, calls the finder, rejects its all-ones result, stores the length byte at +0x18, then stores the accepted pointer or NULL at +0 |
| Search, `0x803E9ACC` onward | Checks unavailable, then NULL, otherwise traverses four-byte match tokens |
| Retained `sub_803EA428` | Writes item/head links and metadata, not slot+0 |
| Frontend references | Access text-head state at +0xC, not slot+0 |

No additional integer encoding, partial-byte slot+0 store or ownership transfer
was found. The source therefore represents slot+0 consistently as
`QuestDownloadMatchToken *tokens`. Full reset and initialization store the named
unavailable pointer. This removes the previous integer-status write followed by
an inactive pointer-arm union read. It adds no pointee access type: search
already used this token type.

The record remains 0x1C bytes: tokens at 0, items at 4, entry head at 8, text
head at 0xC. Compile-time checks retain those offsets and the real 80-slot owner
remains 0x8C0 bytes. No storage is enlarged, overlapped or given a new owner.

## Retained boundary and validation limits

`sub_803EA9E8` remains original code. The finder and its original dictionary
table still have the provisional `Ent_803E9DE0` source declaration. Its four
fields match the observed token format, but this change does not certify the
producer/table's canonical C++ type, lifetime or ownership. No interface or
unrecovered body is invented to make that boundary appear complete.

Both steps receive a full native build and main/previous-head no-loss checks.
The typed-name step preserves complete provider/frontend/buffer object files.
The pointer-field step preserves all 168 provider bodies, all 16 frontend bodies,
all allocated code/data/BSS bytes, named object layout and relocation targets.
Removing the anonymous union renumbers five provider and one frontend compiler
anonymous-object names; those relocation targets are checked by their actual
section, offset and size. No instruction, address, constant or linker target is
rewritten. The actual `QuestDownloadBuffers` owner object is unchanged.

All 173 provider report entries remain unchanged, including the exact search,
both callers, reset and initializer. Original DOL SHA-1 remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Previous bounded runtime evidence is
retained through unchanged executable code/data, with no new runtime execution
claim. Independent exact-head review accompanies publication.

This is a real source-type improvement with no match gain. The unit remains
159/173 exact, five undefined and nine partial, unlinked. Shared scratch/ID
lifetimes, provisional producer interfaces, unchecked input/node preconditions,
cache ownership and lifecycle/reachability limitations remain unresolved.
