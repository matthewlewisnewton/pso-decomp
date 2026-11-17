# Quadrilateral and sphere collision investigation (incomplete)

Based on fork main `9ab744a4ecb84b2ca88274ef5da4a3a0bd0636fb`. The
quadrilateral overlap body is adapted from [upstream PR #309](https://github.com/zeroz41/pso-decomp/pull/309)
and the sphere-contact candidate from [upstream PR #311](https://github.com/zeroz41/pso-decomp/pull/311),
at head `946bd833cf495a566c59094606c29ccd379d3bfa`. The latter remains open.
The containing fork unit is not linked; its matrix helpers remain unresolved.

The quadrilateral routine projects two four-point faces into XY, XZ and YZ and
checks edge intersections and containment. Its 4,524-byte compiled body matches
in objdiff when the shared literals at `0x805E0FD8..0x805E1000` are assigned to
the unit. The two existing collision helpers retain their original instruction
matches with those literals. The original and compiled object inventories
referenced the seven labels in that range only from this unit; they are made
local so compiler-emitted literals can supply the pool. Its entire 40-byte
`.sdata2` section compares equal. A scoped `opt_loop_invariants off` setting and
the local variable lifetimes follow upstream's measured solution. This does not
establish the original source's exact declarations or optimization settings.

The sphere candidate uses the original bounds helpers and the two existing
face tables. It reproduces the 1,848-byte instruction sequence apart from
constant relocations: objdiff scores 99.89%. Its original constants at
`0x805E1000..0x805E1020` are distinct from identical values in the earlier
pool, but the compiler pools the common literals in this combined fork unit.
Replacing the square-root constants with external symbols changed instruction
selection and lowered the score; scoped `pool_data off` left it at 99.89%. It
remains a candidate, not a match or a claim of complete behavioral validation.

The remaining seven matrix helpers include Gekko paired-single instructions.
A scalar C translation probe emitted 140 bytes versus the original 100 bytes;
a C++ vector probe emitted a stack frame and different load/sum instructions.
See [paired-single compiler research](paired-single-sdk-asm.md). No new assembly
exception is used here. `push_reordered_matrix_ps` and `push_identity_matrix_ps`
branch into the middle of their respective neighboring routines, so standalone
C functions also need to account for those shared instruction bodies.

The full `tools/check_pr.py` run passes on this checkpoint: +1 exact function,
+4,524 matched code bytes, +40 matched data bytes, no regressions, and the
original DOL hash. A host smoke test gave the expected overlap and separation
results for two axis-aligned rectangle pairs. Its reciprocal-square-root
substitute is not a Gekko estimate, so it is not native numerical validation.
