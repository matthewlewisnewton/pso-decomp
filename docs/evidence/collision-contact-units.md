# Quadrilateral and sphere collision units

Validated against fork main `9a8d9fdd91f55173526f947ca140ce65e4626dc5`.
The quadrilateral overlap body is adapted from [upstream PR #309](https://github.com/zeroz41/pso-decomp/pull/309)
and sphere contact from [upstream PR #311](https://github.com/zeroz41/pso-decomp/pull/311)
at head `946bd833cf495a566c59094606c29ccd379d3bfa`. The latter was open at
this checkpoint. The native names of the quadrilateral and several helper
interfaces remain provisional.

## Ranges and ownership

The previous fork range `0x803DF7A8..0x803E1FC8` held the collision routines and
later matrix helpers together. It is separated at `0x803E112C`, the start of
the sphere routine, and `0x803E18C0`, the following projection routine. The
sphere routine has its own ordered face and edge tables at
`0x8047E498..0x8047E56C` and a separate literal pool at
`0x805E1000..0x805E1020`; the earlier collision code uses a distinct pool at
`0x805E0FD8..0x805E1000`, including identical numeric values. This separation
also follows upstream's independently chosen boundaries. The layout supports
these splits but does not prove the original source filenames.

The edge-order table contains five 32-bit indices, including the closing zero.
Its previous 24-byte symbol extent included the four zero alignment bytes before
the next eight-byte-aligned data. The table is 20 bytes; the padding remains in
the original layout. The original and compiled object inventories showed no
other unit referencing the now-local table and literal symbols. Source emits
the tables and literals rather than importing game data.

## Matching and linking

The quadrilateral routine projects two four-point faces into XY, XZ and YZ and
checks edge intersections and containment. Its 4,524-byte body matches with
scoped `opt_loop_invariants off` and the variable lifetimes in upstream's
solution. Earlier helpers retain their matches when using the claimed literals.
The sphere routine matches all 1,848 bytes, including its references to the
separate tables and constants. Its bounds calls retain existing linker symbol
names and use explicit pointer arguments; those names do not establish class
ownership. The edge loop uses ordinary array indices for both corner lookups.
After reading the edge endpoints it binds a const reference to the adjacent-face
entry, then uses that entry to select the normal. GC/2.0 scales the corner index
once and reuses the register for both table loads.

The combined unit pooled both sets of numeric literals, leaving the sphere
routine at 99.89% despite matching instruction encodings. Replacing its
square-root literals with external symbols changed instruction selection;
scoped `pool_data off` did not improve the result. Separate ranges reproduce
both pools and allow both complete collision units to link from source. The
remaining `TObjPlayer_803E18C0.cpp` range retains the original fallback because
seven paired-single matrix helpers remain unmatched. Two of those entry points
branch into the middle of neighboring instruction bodies. No new assembly is
used for them.

## Validation

- Both collision units match every function and owned data section; the rebuilt
  DOL passes the original SHA-1 check when they are linked from source.
- `tools/check_pr.py` compares the current-base build by address and checks
  source linkage and generated retention metadata. It reports two new exact
  functions, 6,372 additional matched code bytes, 284 matched data bytes,
  8,472 linked code bytes, 284 linked data bytes, and two linked units, with
  no regressions or denominator changes. Retention adds four names and removes
  none.
- `tools/probes/test_sphere_contact.py`, including its `--sanitize` mode,
  checks four inside, separated and face-contact examples using the production
  sphere body and host bounds stubs. The host reciprocal-square-root substitute
  is not the Gekko estimate; these cases do not establish complete numerical
  behavior.
