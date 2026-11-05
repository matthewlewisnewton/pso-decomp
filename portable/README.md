# Portable alternatives

This folder holds source that is not part of the `PsoV3` build. The matching
decompilation links every unit either from byte-identical compiled source or
from the original disc objects; nothing here is compiled by the GameCube
build or validated by `tools/check_pr.py`.

Each file mirrors the `src/` path of the unit it stands in for and provides
portable implementations of that unit's hand-written Gekko assembly
kernels, for potential non-GameCube targets. These implementations are
functional, not byte-matching; the matching behavior of each kernel, and
why CodeWarrior cannot compile it, is recorded under `docs/evidence/`.

- `pso/math/MatrixVector.cpp` — `vector_length` (`0x803D8BD8`) and
  `matrix_identity` (`0x803D8CA8`); see
  [MatrixVector hand-written kernels](../docs/evidence/matrixvector-asm-kernels-evidence.md).
