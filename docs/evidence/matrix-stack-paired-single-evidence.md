# Matrix stack helper paired-single evidence

The seven remaining functions in `src/pso/unk/text_803D96A8.cpp` use
paired-single displacement accesses:

| Function | Target form |
|---|---|
| `normalize_vector` | scalar `frsqrte` with no `frsp`, then `fres` |
| `transform_point_by_current_matrix` | `psq_l`/`psq_st` with displacement and W bit |
| `rotate_vector_by_current_matrix` | `psq_l`/`psq_st` with displacement and W bit |
| `rotate_matrix_by_node_angles` | `psq_l`/`psq_st` with displacement and W bit |
| `push_matrix` | `psq_lu`/`psq_stu` with displacement |
| `scale_current_matrix` | `psq_l`/`psq_st` with displacement and W bit |
| `post_translate_matrix` | `psq_l`/`psq_st` with displacement |

This unit is built with the `ginja` profile in `build.ninja`:

```
GC/2.6  -O3,p -inline off -opt nopeephole  -use_lmw_stmw on -fp hardware
```

C/C++ formulations tested with exactly those flags, against the target
disassembly in `build/GPOE8P/asm/pso/unk/text_803D96A8.s`:

- typed `Vec`, `f32[3]`, and `Mtx` element arithmetic lowers to scalar
  `lfs`/`fmuls`/`stfs`;
- `__vec2x32float__` accesses through pointers, struct fields, casts
  (`PSQ_MOVE`), `register`, `volatile`, arrays and loops lower to indexed
  `psq_lx`/`psq_stx`, never the displacement `psq_l`/`psq_st` or update forms;
- the indexed form was reproduced with GC/1.0, 1.1, 1.2.5, 1.3, 1.3.2, 2.0,
  2.5, 2.6, 2.7, 3.0a3 and Wii 1.0-1.7;
- `memcpy` and struct assignment lower to a call or a scalar/indexed copy,
  not `psq_lu`/`psq_stu`;
- `__frsqrte` on `f32` always emits `frsqrte` followed by `frsp`; the target
  `normalize_vector` has `frsqrte` with no `frsp`.

No supported C/C++ spelling reproduces the target bytes with these compiler
settings. The original bodies were therefore written in assembly (or with
inline assembly), and under the contribution rule that forbids hand-written
assembly they remain unmatched. The earlier `orig_asm` bodies for this group
were removed rather than retained as copied assembly.
