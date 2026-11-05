# Indirect controller: native observations salvaged from #267

Salvaged from the unmerged PR
[#267](https://github.com/matthewlewisnewton/pso-decomp/pull/267), which was
superseded by [#291](https://github.com/matthewlewisnewton/pso-decomp/pull/291).
#291 ported `pso/effect/TEffIndirectCtrl_802A88AC.cpp` under the unit defaults
(`GC/2.6`) plus the approved `-opt noprop` switch (see
[indirect-scroll-offset-propagation.md](indirect-scroll-offset-propagation.md)
and `docs/porting-exceptions.md`). #267 tried a GC/2.0 fold with
`-inline off,deferred`.
[#161](https://github.com/matthewlewisnewton/pso-decomp/pull/161) builds that
fold as one linked unit, `pso/effect/TEffIndirectCtrl.cpp`, with upstream
#180's range (`0x802A8140`-`0x802A9588`); its compiler and switches are
registered in `docs/porting-exceptions.md`, and the recovery notes are in
[indirect-dispatch-recovery.md](../indirect-dispatch-recovery.md). The
observations below are #267's findings about the original binary; where #161's
exact build confirms or settles one, the bullet says so.

## Unit range

- #267 grouped the manager destructor at `0x802A81B8`, its
  constructor/registration functions, the indirect rendering helpers and the
  controller through `0x802A9284` into one native fold (23 functions, 4,300
  text bytes, 149 resolved text relocations under its GC/2.0 build). The two
  preceding scene routines stay in their own fragment. This was an
  evidence-backed fold, not a claim about the original filename. #161 also
  takes in the two scene routines at `0x802A8140`, matching upstream #180's
  unit, and the split entry is identical to upstream's in every section.
- The native read-only (112 bytes), initialized data (84 bytes) and small
  constant (8 bytes) blocks of that range matched at the original addresses.
  These 204 bytes describe native ranges, not newly recovered bytes.

## `TEffIndirectCtrl::run_task` (`0x802A88B0`)

- The original snapshots three nonvirtual, no-argument member pointers before
  dispatch, in the order scroll, update-and-flush, wave update. The receiver
  is the controller, and the recipe mode is checked before the indirect call.
- Details #267 had to preserve: the guard, signed recipe bytes, unsigned phase
  accumulation, floating point multiplication order, the plain integer `rand`
  result, and the final update flag. #267 expressed the dispatch with the
  compiler's own member-pointer representation rather than encoding it by hand.

## Manager object (original class name unresolved)

- Constructor `(s32 kind, TObject *parent)`, 80 bytes, with inherited
  `TObject` allocation. Its four callers use ordinary `new` expressions with
  the original allocation and null checks.
- It registers the full incoming kind but stores only one byte, at `0x1C`.
- Destructor: 88 bytes. Native constructor/destructor stores and layout give
  a size of `0x20`, with the inherited vptr at `0x18`.
- Manager children created by the explosion routines receive the explosion
  task's `TObject` base.

## Helper interfaces

- The exported tile buffer is `u32`, matching its separate allocation/free
  owner. The static player helper takes six arguments.
- Full-width kind lookup compares only the low byte. The setup and wave helpers
  return `void`; the scroll helper narrows its full-width amplitude inside the
  callee.
- The texel helper fits one `u32(u8, u8, u32)` interface: the formula uses only
  bits 0..7 of each coordinate, with unsigned width and result arithmetic, and
  the callers' byte conversions match without a function-pointer cast. #161
  declares `u32 get_indirect_tile_coord(u8, u8, s32)` and calls it directly.
  A `u16` return makes the callers add `clrlwi r4,r3,16`, so the full-width
  return is confirmed. The buffer's elements are read with `lhzx`, so #161
  keeps `indirect_effect_tile_buffer` as `u16 *`.
