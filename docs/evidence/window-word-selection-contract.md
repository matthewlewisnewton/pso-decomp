# Shared raw Word selection accessor contract

The existing accessor at `80342158` was declared as `s16(int)`, `s32(s32)`,
`s32(void*)` and `int(u8*)` in different units. A shared declaration now matches
its unchanged definition, `int(u8*)`. Former short-return callers retain explicit
`s16` conversions, and existing pointer/word transports remain explicit. This
removes conflicting C function types without assigning a receiver class or
changing binary behavior.

This follows continuation `55036c5e414961a678e2631e556a913a223d8345`, focused
`37ed8308f9df0e8ff4426bcc187f378f337a2cbc` and unchanged main
`e65f11ce6ec99c006909422f81da1c0a46ac062e`. The separate
[Parts provenance audit](window-parts-control-provenance-audit.md) establishes no
independent justification for its compiler control; that lane remains held.

## Definition and original callers

The 36-byte definition reads the table pointer at receiver+0x80. If nonzero, it
loads a signed halfword indexed by the word at +0x68; otherwise it returns 0x685.
Its complete body and relative resolved targets match original. Returning that
sign-extended value through the current `int` definition does not establish the
unique original prototype or table ownership.

A census of 4,966 active original objects and 249,768 relocations finds nine
references across five caller units. Every reference is a zero-addend direct
REL24 call to the entrypoint; no address-taking or interior reference appears.
The two comparison callers in the constructor-owner and 803426CC units immediately
sign-extend r3. Other sites store a halfword, discard the result, or use a word
result before later narrowing. The small post-call instruction census is not a
complete value-flow proof; source consumers are reviewed separately.

`WindowWordSelectionAbi.h` declares the existing export once. Five caller-local
declarations and the two duplicates in the old owner header are removed. All four
calls in the two former short-return units retain explicit signed-halfword views,
including the discarded result. Word-valued receiver storage is still converted
to a raw pointer; no object is created or ownership inferred by that conversion.
Indexing, fallback, result consumption and null behavior remain unchanged.

The discarded-result caller's subsequent no-argument classification helper still
has its historical live-register qualification. General mapper/index bounds,
raw buffer storage and other helper interfaces are not recovered by this shared
declaration. There is no wrapper, overload, alternate symbol, new table, layout
change, matching pragma or source-order adjustment.

## One candidate, complete-object preservation

One isolated declaration/caller candidate reproduces all seven dependent complete
ELFs byte for byte. The production rebuild reproduces the same identities:

| Unit suffix | Text bytes | Complete ELF versus prior published object |
| --- | ---: | --- |
| 80341A08, accessor owner | 3412 | Identical |
| 80342254 | 664 | Identical |
| 803426CC | 980 | Identical |
| 80342AA0 | 276 | Identical |
| 80342E40 | 636 | Identical |
| 8034725C | 3288 | Identical |
| 80347F34, indirect header consumer | 460 | Identical |

This covers every section/header, function, symbol and relocation, rather than
only changed call bodies. The complete Ninja graph and ordered linker inputs
also remain byte-identical. Parts, DD, the incomplete formatter, Fukidasi and all
other original providers/remainders remain selected as before. Native Word
construction/order/table-destination and other lifetime/ownership holds stay.

The capacity-gated full build passes in 4.04 seconds and preserves original DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The report is byte-identical to
the prior published build. Address-based acceptance, all 3,601 exact linked units,
18,584-name retention and port inventory checks pass with zero metric change.
Previously validated focused/main comparisons and historical coverage
qualifications are preserved by the identical report, objects and graph; a new
standalone main build is not claimed. No coverage gate or qualification changes.

Private evidence is in `pr403-word-selection-abi/`: `commands.json`, `compile.py`,
`receipt.json`, `final-objects.json`, `build-receipt.json`, build log and
`vs-prior.json`. The active original caller audit is
`pr403-parts-provenance-audit/accessor.py` / `accessor.json`. Original objects,
binaries and raw disassembly are not published. Independent source and final
frozen-head review are required before publication; the PR remains draft.
