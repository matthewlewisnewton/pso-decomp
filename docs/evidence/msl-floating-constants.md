# MSL floating constants

This isolates the floating-constant part of
[`1370dcf359541a5e6d0a3cc218513559a7431b6d`](https://github.com/matthewlewisnewton/pso-decomp/commit/1370dcf359541a5e6d0a3cc218513559a7431b6d),
authored by matthewlewisnewton with Cursor coauthor credit, from the preserved
[`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98`](https://github.com/matthewlewisnewton/pso-decomp/commit/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98).
Existing MSL notices and third-party attribution remain unchanged.

## Source and ownership

The data-only `float.c` owns `.sdata` at `0x805D4600..0x805D4628` (40 bytes).
Its six word arrays preserve the native bit representations of `__float_nan`,
`__float_huge`, `__double_max`, `__double_huge`, `__extended_min` and
`__extended_max`. This includes the existing NaN representation; it is not a
floating-point behavior repair.

The existing MSL header already declares the single-precision constants as
`unsigned long[]`. The `ansi_fp.c`, `strtoul.c` and `render_util_tail.cpp`
declarations and reads now consistently use that word-array storage contract.
The four double/extended symbol names replace their address placeholders at
`0x805D4608`, `0x805D4610`, `0x805D4618` and `0x805D4620`; addresses and extents
do not change. `float.c` uses the existing GC/1.3 MSL compilation profile, with
no new steering flags or pragmas. The emitted data reproduces the original
40 bytes at alignment 8 and has no relocations.

This is one new data-only linked unit. The existing consumers already link;
there is no new function match or source-linked code gain.

## Validation

The comparison base is `e9b77fcfdcc2335c9a5a92886826022c80505e67`.

- Serialized native builds reproduce original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`. `check_pr.py` passes with no
  function, code, data, linked or address-coverage loss.
- Matched and linked data each gain 40 bytes. Matched functions remain 27,434,
  matched code 4,232,424 bytes and source-linked code 3,845,340 bytes. Linked
  units increase from 3,603 to 3,604.
- Of 3,632 existing active objects, 3,630 remain raw-identical, including
  `render_util_tail`. All allocated sections of the two remaining consumer
  objects are byte-identical; their 241 and 147 relocations are identical
  after only the four documented symbol-name substitutions. The new object
  contains just the exact 40-byte `.sdata` section.
- The sole linker-provider replacement is the original automatic data object
  at `0x805D4600` with compiled `float.c`. Remaining input order is unchanged:
  3,604 source inputs and 1,344 original fallback inputs.
- Fresh retention generation leaves all 18,441 entries unchanged. The generated
  port-exception inventory is unchanged; no new exception is introduced.
- All 306 original-free host tests pass. Portable `make -C ports/tests run`
  and `make -C ports/tests sanitize` pass with AddressSanitizer and UBSan enabled.

Native word sizes and float representation remain part of this existing MSL ABI;
the data definitions do not assert an LP64 host ABI. Original binaries,
proprietary tools and private build products remain local.
