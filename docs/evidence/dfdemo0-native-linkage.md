# Dark Falz demo unit: native linkage

Base: `e258b1e91233fb9ddcbf72c9c168784a346153ff` (personal-fork main).
Overall wave baseline: `909d120b21f7e875e71a5c1d0d3a7799a08078e9`.

The unit `pso/object/TObjDFDemo0.cpp` owns text `0x8004E020–0x8004E6D0`,
rodata `0x80437370–0x80437378`, data `0x80485640–0x80485674`, and
sdata2 `0x805D8988–0x805D89B0`. Its six functions already matched before this
change; the gain is complete native linkage, not newly matched functions.

## Constant ownership

The fresh split-object and compiled-object census found one external consumer:
`text_8004E6D0.o` loads `lbl_805D8990` at `0x8004E884`. That zero must remain
exported at sdata2 offset `0x8`.

Five explicit C++ float definitions preserve the middle of the constant block.
Their placement after their consuming functions avoids an extra compiler-pooled
copy of 30.0 and preserves the existing instruction selection. The first two and
last three float literals remain compiler-pooled. The conversion double and those
five private float symbols are localized only after the complete consumer census
confirms no external references. No consumer source or vtable layout is changed.

## Exact object evidence

All six function names, offsets, and sizes match. All 95 runtime relocation tuples
match after resolving local targets to section offsets and retaining external
symbol names and addends. The allocated sections match byte-for-byte, including
sizes and alignment:

| Section | Bytes | Alignment | SHA-256 |
| --- | ---: | ---: | --- |
| `.text` | 1712 | 4 | `bf7c27bca6c5616efa83069cd77086b864031fd454c09e11b530b583f9bf821e` |
| `.rodata` | 8 | 8 | `07af8387624cf8f36152797d2f561246f21237d1d22b5c13006eacfa6f475e43` |
| `.data` | 52 | 8 | `7955cb2de90dd9efc6df9fdbf5f5d10c114f4135a9a6b52db1003be749e32f7a` |
| `.sdata2` | 40 | 8 | `2e50d525029fb114e003a0e5bd444d781e490ff3ba7bf03f5324633936a9cb35` |

## Native validation

- Clean base full build: PASS (104.48 seconds).
- Final full build, under the shared maintenance and legacy exclusive gates,
  using pinned Ninja with `-j2 -d keeprsp`: PASS (9.45 seconds).
- `tools/check_pr.py --no-build --baseline /tmp/worker2-dfdemo0-base-report.json`:
  PASS; no match or linkage regressions, and the generated retention list is current.
- The address-based comparison against the overall wave baseline also passes.
  Intervening fork changes are not attributed to this unit.
- Incremental complete code: `+1712`; complete data: `+100`; linked units:
  `3553 → 3554`. Matched code, data, and function counts are unchanged.

The actual `build/GPOE8P/psov3.elf.rsp` has 5,013 input arguments. It contains
`build/GPOE8P/src/pso/object/TObjDFDemo0.o` once and contains no
`build/GPOE8P/obj/pso/object/TObjDFDemo0.o` fallback.

Response-file SHA-256: `1734ebd784c7f80d46de52aa4d18fd27af62c07b86b568dd0785c9e2d4ac9b91`.

Compiled-object SHA-256: `0b48ee4f30aa3f227c8e61a4a280431d67d4e30beff179fa3d6ca284aa1c7813`.

Original and linked DOL SHA-1: `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
