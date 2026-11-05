# MatrixVector hand-written kernels

`vector_length` at `0x803D8BD8` and `matrix_identity` at `0x803D8CA8` in
`pso/math/MatrixVector.cpp` are hand-written Gekko assembly in the original
object, not compiler output:

- `vector_length` sums the squares in single precision (the same instruction
  chain as the matched `vec_squared_length`) and then applies a bare
  `frsqrte` estimate refined by `fres`, both in place in f1, with no
  conversion. CodeWarrior types `__frsqrte` f64→f64 and `__fres` f32→f32 in
  every shipped GC version (1.0 through 3.0a5, C and C++), so every typed
  composition inserts an `frsp` between them; union and pointer punting go
  through memory, and division always compiles to `fdivs`/`fdiv`. The
  conversion-free chain is not reachable from C or C++ source.
- `matrix_identity` builds its stores from paired singles: it loads the
  first float of the shared `.sdata` pair `lbl_805D46AC` ({1.0f, 0.0f}, in a
  data block no unit owns yet), zeroes a pair with `ps_sub`, builds the
  {1,0} pairs with `ps_merge01` and stores them with `psq_st`. CW 2.6 has no
  paired-single intrinsics (its FP builtins are only `__fabs`/`__fabsf`,
  `__fmadd(s)`, `__fmsub(s)`, `__fnmadd(s)`, `__fnmsub(s)`,
  `__fnabs`/`__fnabsf`, `__fres`, `__frsqrte`, `__fsel`) and never
  auto-emits paired singles from C++.

Both functions interleave in `.text` with functions that match as CW 2.6
C++ (`scale_matrix_vec3`, `rotate_matrix_about_axis`, `translate_matrix_vec3`,
`set_matrix_identity`, ...), so a separate library object or another
compiler cannot explain them: the emitted order places their bodies in the
same compilation. Reading 1.0f from the external `lbl_805D46AC` pair
instead of a pooled literal is the same data flow as the other hand-written
kernels of this math neighborhood: `matrix_apply_translation` reads {1.0f}
at `0x805D46B4` and `rotate_vector_by_current_matrix` reads {0.0f, 0.0f} at
`0x805D46B8`.

## Representation

The unit keeps the two signatures as `asm` functions whose bodies
`tools/orig_asm.py` writes from the disc at build time, like the SDK's
assembly and the MusyX asm kernels; nothing from the game is committed.
Portable, non-matching implementations of the two kernels are checked in
under `portable/pso/math/MatrixVector.cpp`, outside the PsoV3 build, for
potential non-GameCube targets. Two details of the matching representation
are load-bearing:

- the extern `lbl_805D46AC` must be a complete small array (`extern f32
  lbl_805D46AC[2];`) so CW emits the original's SDA21 relocation instead of
  ADDR16;
- `lbl_805E0EE0`, the unit's own int-to-double pool constant, is
  `scope:local` after `localize_split_globals.py` (no other object
  references it), so the linked unit needs no source definition.

## Functional C equivalents, for reference

These do not match: CW inserts the forced `frsp` and emits scalar stores.

```c
// One extra frsp; the estimate math is the same.
f32 vector_length(const Vec *v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 sum = x * x;
    f32 z = v->z;
    sum = (y * y) + sum;
    sum = (z * z) + sum;
    return __fres((f32)__frsqrte(sum));
}

// Scalar stores of the same twelve floats; zero derives from the loaded
// value so the unit pools no new constant.
void matrix_identity(u8 *arg0) {
    f32 *m = (f32 *)arg0;
    f32 one = lbl_805D46AC[0];
    f32 zero = one - one;
    m[0] = one; m[1] = zero; m[2] = zero; m[3] = zero;
    m[4] = zero; m[5] = one; m[6] = zero; m[7] = zero;
    m[8] = zero; m[9] = zero; m[10] = one; m[11] = zero;
}
```

## Validation

`ninja` DOL SHA OK; `tools/check_pr.py` PASS with +2 exact functions
(`0x803D8BD8`, `0x803D8CA8`) and +1 linked unit (3559 linked, all exact), no
regressions. The probe scripts compiled every shipped CW version with the
unit's flags against candidate sources; the byte-exact `asm` bodies were
verified by objdiff (unit 9/9, data 100%) and by the linked DOL hash.
