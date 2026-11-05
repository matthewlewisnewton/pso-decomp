# Character-select confirm: typed tables and the cell store

Base: fork `main` `7ba27eaf2`, merged into PR
[#214](https://github.com/matthewlewisnewton/pso-decomp/pull/214). Unit
`pso/ui/TAdMultiPlyChrSelectGC_802C50EC.cpp`, function
`TAdMultiPlyChrSelectGC__sub_802C5688` (`0x802C5688`, 700 bytes). Unit flags
are `GC/2.6`, `-O4,s`, `-inline on`, `-fp_contract on` (section 5 of the
porting-exceptions register). Allocation was read with the MWCC debugger
(retrowin32 + `mwcc_debugger.py`, GC/2.6) and the
[mweppc](https://github.com/doldecomp/mweppc) decompilation.

## Observed allocation

With the cell reached through `s32 *entry = &grid[row][col]`, the function
compiled to the original except for one register pair (99.74%):

| Role | Original | Pointer to the cell |
|---|---|---|
| cell offset `row * 20 + col * 4` | `r9` | `r10` |
| `player * 4` (shown flag and slot-id index) | `r10` | `r9` |
| `f4EC * 4` (slot-id value) | `r9` | `r10` |

## Mechanism

- Virtual registers are numbered as arguments, then named locals (reverse
  declaration order), then frontend `@` temps (latest created first), then
  backend temps in creation order (`allocate_local_vregs` in `CodeGen.c`).
  The nodes below are all in the first simplify level, so they are coloured
  from the highest number down, each taking the lowest free register.
- For the cell offset to get `r9`, the grid base (`r6`), the player (`r7`) and
  the table base (`r8`) have to be coloured before it, and `player * 4` after
  it. That needs `player * 4` < cell offset < player in virtual-register
  number.
- The shown-flag and slot-id tables were `void *[4]` reached through `(s32 *)`
  cast macros. `IRO_FindAssigned` only recognises an `EOBJREF` base, so a
  store through `ETYPCON(EOBJREF)` or through a pointer counts as indirect and
  kills every global load (`GetExprKillsByIndirectAssignment`). The frontend
  therefore re-read the active player before the slot-id store. The backend
  merged the two `player << 2` afterwards as backend temp r64, which is
  coloured before the named `entry` (r33).
- With the tables typed as `s32[4]` / `f32[4]` and the cell indexed in place,
  all three stores are direct stores to known objects. The player load stays
  available, so the frontend makes it `@151`, the cell address `@152`,
  `f4EC * 4` `@153`, and `player << 2` `@154` (r49, r48, r47, r46). That
  colours player `r7`, cell `r9`, `f4EC * 4` `r9` and `player * 4` `r10`,
  as in the original.

## Source shapes

| Shape | Result |
|---|---|
| `void *` tables with cast macros, pointer to the cell (old source) | 99.74%, pair swapped |
| Typed tables, pointer to the cell | 99.74%, pair swapped (the pointer store still kills the player) |
| Cast macros, cell indexed in place | 99.74%, pair swapped (the cast store kills the player) |
| Typed tables, cell indexed in place | exact |
| Named `s32 *shown = &shown_flags[player]` after the reject branch | propagated away; 99.74% |
| Cell store before the shown-flag store (cast macros) | 98.34% |
| Slot-id store before the cell store (cast macros) | 89.01%, `stmw` prologue |

Every other function in the unit compiles to the same bytes with the typed
tables (`.text` 7288, `.data` 184, `.rodata` 8).
