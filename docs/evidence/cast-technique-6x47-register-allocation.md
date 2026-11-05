# 6x47 cast-technique handler register allocation

Base: fork `main` `f6dedd375`, merged into PR
[#125](https://github.com/matthewlewisnewton/pso-decomp/pull/125). Unit
`pso/player/TObjPlayer_801C7430.cpp`, function `handle_6x47_cast_technique`
(`0x801CD550`, 364 bytes). Unit flags are the defaults (`GC/2.6`, `-O4,s`,
`-inline off`). Every shape below was compiled in the full unit and compared
with the split original object. Allocation was read with the MWCC debugger
(retrowin32 + `mwcc_debugger.py`, GC/2.6).

## Types the original code implies

- The handler copies, byte-swaps and validates a `G_CastTechnique_6x47`
  (`init`, `bswap`, `send` and the validator take the packet). It then works
  on the player's `TechniqueCastState` at `+0x428`. The four state methods it
  calls (`sth r4,4(r3)`, `stb r4,0(r3)`, `lbz 1(r3)`, `addi r3,r3,32`) and
  `check_technique_level` all take `this = player + 0x428`.
- The technique and target-count bytes load as `lbz`/`extsb` into signed
  values. The level byte loads as `lbz r0` and is sign-extended into its
  local at once (`extsb r28,r0`). This matches an unsigned wire byte stored
  into an `s8` local. With an `s8` field, the load goes straight to `r28` and
  the sign extension moves to the compare (`extsb r0,r28`).
- `copy_tech_params` (`0x801CC7E4`) is load, store, load, store. A `const`
  source lets MWCC hoist the second load above the first store, so its source
  parameter is non-const.
- `clamp_and_set_unit_value` gets the 32-bit technique in `r5` with no
  extension. An `s16` parameter adds `extsh r5,r27`, so the third parameter
  is `s32`, as the old `...FiUci` symbol encoded.

## Original birth of the technique id

    lbz     r4,12(r1)
    addi    r3,r30,1064
    extsb   r4,r4
    mr      r27,r4
    bl      set_technique__18TechniqueCastStateFs

The value is built in the argument register and copied to r27 before the
call. r27 then feeds the level check (`mr r4,r27`) and the clamp
(`mr r5,r27`). `set_technique` takes an `s16`, while the level check and the
clamp take an `s32`. The source keeps both: `s16 tech` dies at the
`set_technique` call and is coalesced into r4. `s32 tech_id = tech` is the r27
copy used by the two 32-bit calls. Coalescing never joined two named locals
here, so the copy survives.

## Shapes measured (91 instructions)

| Shape | Result |
|---|---|
| Final source (`s16 tech`, `s32 tech_id = tech`, member calls) | exact |
| One `s32` technique local for all three calls | born in r27, no r4 copy; 3 mismatches |
| One `s16 tech` for all three calls | `tech` takes r31 and pushes `effective` to r29; 8 mismatches |
| `u8 level` field declared `s8` | sign extension moves from the load to the compare |
| Clamp's third parameter `s16` | extra `extsh r5,r27` |
