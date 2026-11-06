# Locked-cache matrix stack base (`init_matrix_stack`)

`TObjPlayer::init_matrix_stack` (`0x803DEC98`, `src/pso/system/ChunkMaterialState.cpp`)
puts the matrix stack at `0xE0000000`, the GameCube locked data cache. The SDK's
TRK keeps the same base as an integer (`lc_base = 0xE0000000` in
`libs/TRK_MINNOW_DOLPHIN/dolphin_trk.c`).

Original code:

```
lis    r0, 0xe000
stw    r0, matrix_stack_base@sda21(r0)
stw    r0, current_matrix@sda21(r0)
subi   r0, r4, 0x1
mulli  r3, r0, 0x30
subis  r0, r3, 0x2000          ; + 0xE0000000
stw    r0, matrix_stack_limit@sda21(r0)
lis    r3, identity_matrix@ha
addi   r3, r3, identity_matrix@l
cmplwi r3, 0x0
bne    1f
lis    r3, 0xe000              ; null path: the constant again
1: bl  PSMTXIdentity
lwz    r3, matrix_stack_base@sda21(r0)
...    bl move_data__FPvPCvUl
```

The constant has no relocation. It is loaded once for the two stores, folded
into `subis` for the limit, and loaded again with `lis r3` on the identity
null path.

## Forms tried (GC/2.6, default `-O4,s` flags)

| Form | Function | Difference |
|---|---|---|
| `matrix_stack_base = (u8 *)0xE0000000` (shipped) | 100% | none |
| `u8 matrix_stack_lc[] : 0xE0000000` (absolute object, the `hw_regs.h` form), base and limit from it | 83.6% | `lis r3`, value kept in `r3`; limit is `add r0, r3, r0`; null path is `mr r3, r0` / `b` |
| same, limit kept as the integer `(arg1 - 1) * 0x30 + 0xE0000000` | 85.8% | `subis` matches; stores still use `r3` and the null path reuses it |
| `Mtx`-typed absolute array | 85.8% | same as above |
| identity selected with `if (m == 0) m = matrix_stack_base;` | 92.6% | stores in `r5`, null path `mr r3, r5` |
| a second absolute object at the same address for the null path | 85.8% | MWCC still reuses `r3`: absolute addresses are numbered by value |
| integer stores, absolute object only on the null path and the `move_data` argument | 83.4% | null path reuses the store's `lis r3`; `move_data` gets `lis r3` instead of `lwz` |
| `extern u8 matrix_stack_hw[] : 0xE0000000` (earlier pass on this PR) | not exact | `add` plus `mr`/`b`, as above |

MWCC treats the address of an absolute object as a value that it keeps in a
register and reuses on the null path. An integer constant is not kept that way.
It is loaded again on each path, which is what the original does. A linker
symbol for the base would add `@ha`/`@l` relocations, and the original has none.

## Matrix stack typing in this PR

`ChunkMaterialState.cpp` types `matrix_stack_base` and `matrix_stack_limit` as
`u8 *`, so the limit is pointer arithmetic and `move_data` gets the base with
no cast. The integer-to-pointer conversion happens once, at the locked-cache
constant. `text_803D96A8.cpp` keeps the base's `u32` declarations because every
function there treats the stack as integers (`current_matrix` is `u32`, and
`concat_matrix__11TCameraCtrlFUlUl` takes `u32` matrices). `push_matrix_from` therefore
converts `next` and `current_matrix` to `void *` for `move_data`, where the base
used a `(TLobby *)next` receiver. Typing `current_matrix` as a pointer there would
also mean renaming `concat_matrix__11TCameraCtrlFUlUl` and editing its callers,
one of which is in #290's `TObjBoss2Tunnel.cpp`.

Port: allocate the matrix stack as an ordinary array; nothing else depends on
the locked cache.
