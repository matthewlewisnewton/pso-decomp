# 6x47 cast-technique handler register allocation

Base: fork `main` `7ba27eaf2`, merged into PR
[#125](https://github.com/matthewlewisnewton/pso-decomp/pull/125). Unit
`pso/player/TObjPlayer_801C7430.cpp`, function `handle_6x47_cast_technique`
(`0x801CD550`, 364 bytes). Unit flags are the defaults (`GC/2.6`, `-O4,s`,
`-inline off`). Passes and allocation were read with the MWCC debugger
(retrowin32 + `mwcc_debugger.py`, GC/2.6), and every result was checked
against the split original object.

## Original birth of the technique id

    lbz     r4,12(r1)
    addi    r3,r30,1064
    extsb   r4,r4
    mr      r27,r4
    bl      set_technique_id__10TObjPlayerFs

The value is built in the argument register and copied to r27 before the call.
r27 then feeds the level check (`mr r4,r27`) and the clamp (`mr r5,r27`).
`effective` is r31, and `player` is r30 throughout.

## Mechanism

- Coalescing joins a virtual register to a physical one when the virtual dies
  at the move (`mr r4,v` before the call). It never joined two named locals
  in this function (`mr r43,r35` and `mr r42,r41` both survived in the old
  body).
- Backend copy propagation rewrites a copied local into non-move uses, then
  deletes the copy. It leaves the copy alone when every use is itself a move.
  With `s16 tech` and `(long)tech` at the check, the copy into the frontend
  temp is kept, but `tech` must survive the call (home-first `lbz r31`). A
  `s16` copy of an `s32` used through a conversion is propagated and
  deleted, so one local again survives the call.
- An `s16 tech` passed to `set_technique_id(s16)`, plus `s32 tech_id = tech`
  before the call, gives `tech_id` move-only uses: the check and the clamp
  both take 32-bit ids. `tech` dies at the call and is coalesced into r4,
  so `tech_id` is the r27 copy.
- Frontend CSE temps are numbered above every local and are coloured first.
  `(s32)player` passed to both the clamp and the phase runner becomes one
  such temp. It takes r31, pushes `player` and `effective` down, and no
  declaration order recovers the original. Passing the player pointer
  unconverted to one of the two calls (the phase-runner call style used by
  this file's other client-id handlers) leaves no temp.
- With no temps, locals are coloured in reverse declaration-number order
  (first declared first). Each takes the lowest saved register already in use
  that its coloured neighbours leave free, else the next new one below. A
  brute-force model of the interference graph found 28 orders that give the
  original. All of them colour `i` or `effective` first. The source uses
  `i, player, effective, count, valid, dst, level, tech, tech_id, src`.

## Shapes measured (91 instructions)

| Shape | Result |
|---|---|
| Old body (`s16 tech`, `(s32)player` twice) | 8 operand mismatches |
| `s32 t; s16 tech = t` / `s8 t` / same-type copy | copy propagated; 8 mismatches |
| `s32 tech_id = (s16)pkt.tech`, call `(s16)tech_id` | `lbz r0` / `extsb r4,r0`; 2 mismatches |
| `s16 tech`, `s32 tech_id = tech`, `(s32)player` twice, old declaration order | original birth, but `player` r31; 34 mismatches |
| Same, kept declaration order | `effective` r29 plus an `mr r31,r30` parking copy; 92 instructions |
| Kept source: `player` unconverted at the phase-runner call | exact |
