# CodeWarrior source order and emitted layout

Source definition order is not always the emitted order. In an isolated investigation of Gee at commit
`b81c006d6d26845af026e67e0846c3b53205674e`, the project's GC/2.6 compiler identified itself as Metrowerks
Embedded PowerPC 2.4.7 build 107. Reverse definitions with `-inline off,deferred` matched the original object's
reported sections, including its native vtables. A reconstructed ascending-definition variant with immediate
compilation retained all 102 function offsets, sizes and instruction matches, but put the vtables at different
`.data` offsets. Its `.data` match was 91.15854%; the comparison found 18 positional `.text` and 170 positional
`.data` relocation differences. Identical raw section bytes alone did not establish identical relocation targets.

The independent investigation compared 29 selected compiler/source arrangements and their diagnostics, function
layouts, allocated sections and symbolic relocations. None of the tested supported alternatives preserved all of
Gee's native emission with ascending definitions. The finite test does not prove that no alternative exists or
recover the original source order. Some newer pragmas produced illegal-pragma warnings despite a successful compiler
exit, so inspect diagnostics rather than assuming a flag or pragma took effect. The investigation's independent
review confirmed the central comparison; it did not certify a new integrated build.

For another unit, compare against its own original split object with the actual compiler and settings. Check code,
data, alignment, symbols and relocations, then run the full build, original-hash, address-coverage and source-link
checks in [CONTRIBUTING.md](../CONTRIBUTING.md). Explain a non-obvious source arrangement and its evidence in the
change. A matching source arrangement is an implementation choice, not evidence of the historical source order.
