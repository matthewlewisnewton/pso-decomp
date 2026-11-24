# Parts propagation setting: independent provenance audit

This qualifies the [matching four-case control](window-symbol-parts-propagation-control.md)
without repeating it. The verified stack remains main
`e65f11ce6ec99c006909422f81da1c0a46ac062e`, focused
`37ed8308f9df0e8ff4426bcc187f378f337a2cbc` and continuation
`55036c5e414961a678e2631e556a913a223d8345` before this follow-up. No competing
head update or Parts PR was observed in the targeted open-PR check.

## Available project and object evidence

A read-only inventory finds 660 files in the extracted original-input tree and
no project, original relocatable object, archive, linker map, source or makefile
among the searched artifact extensions/names. The tracked repository has no MCP,
MCH or `.project` file. This is a bounded search: extraction is partial, opaque
containers are not inspected, and absence here is not proof such files never
existed. The broader historical inventory qualification is recorded in the
[DOL header note](dol-header-view.md).

The available `build/GPOE8P/obj` files are DTK splits reconstructed from the
linked DOL. The build rule runs `dtk dol split`, and the reproduction configuration
explicitly supplies `mw_comment_version: 10`. Their `.comment` and `.note.split`
metadata therefore cannot authenticate retail per-function optimization settings.
Neither a matching reconstructed ELF nor a generated linker map is an original
Parts project file.

The PSOV3 target begins in recovery commit
`685f84a4f99adf3dce9ccbcaaa75de1267783912`. The current game size/inline choices
are attributed to reconstruction comparisons in `6729dd3d581`; small-data inference
is documented in `46befc174e6`. The current configuration explains per-file
exceptions through matching behavior. These are useful reproduction records,
not preserved Sega project settings. No Parts propagation exception is present.

## Neighbor comparison

Actual MWCC commands are read from the current Ninja graph, rather than the
Clang editor index. These five sampled units use GC/2.6, inherited `-O4,s`,
`-inline off` and `-sdata2 4`, with no source `opt_propagation` pragma:

| Unit | Compiled text bytes | Original text and all owned resolved relocations |
| --- | ---: | --- |
| SubSymbolChatHelp | 2408 | Exact |
| SubSymbolChatParts | 4620 | Exact, retaining its extern load |
| SubSymbolChatPartsSet | 2440 | Exact |
| SubSymbolChat_80281814 | 8084 | Exact |
| SubSymbolChat_80285E10 | 784 | Exact |

These neighbors provide no independently recovered propagation-off context for
Parts. Their successful inherited-profile reconstructions also cannot prove that
a local setting was absent in retail Parts. Original machine code constrains
values, uses and ordering but does not uniquely recover a C++ source spelling or
pragma. The preceding extern/inherited and literal/off controls already illustrate
that ambiguity; no further compiler, placement or optimizer variant is justified.

## Outcome

Independent provenance remains unestablished. The literal/off match stays private
diagnostic evidence; no pragma, float localization, explicit constant placement
or provider activation follows. Parts' original provider, Word construction and
actual-destination holds, and all protected units remain intact.

A distinct source-quality lane is supported by direct callee/caller evidence:
the [shared selection accessor contract](window-word-selection-contract.md).
It repairs conflicting declarations without changing optimizer settings,
ownership, source providers or binary behavior. It does not resolve the Parts hold.

Private inventory and neighbor replay are in
`pr403-parts-provenance-audit/context.py`, `context.json` and `context.log`.
No original binary, object, map or raw disassembly is published. Independent
read-only review confirms the bounded provenance conclusion.
