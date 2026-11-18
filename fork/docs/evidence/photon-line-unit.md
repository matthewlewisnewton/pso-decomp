# Photon line unit

Recovery base: fork main `c17ee9946c4d6887e37a01c390320bb25e9a793c`.
`pso/misc/TPhotonLine.cpp` owns four functions at
`0x801ACAF0..0x801ACE1C` (812 bytes). They already matched and linked, but
all of the unit's data still came from automatic original-data objects.

## Class and creation boundary

The constructor copies its parameter position to the actor's current and home
positions, multiplies the direction by speed into the velocity at +0x334,
and stores the hit scale at +0x344 and resolved owner at +0x350. Ten ID entries
start at +0x354, followed by the unsigned hit count at +0x368. The sole creator,
`TPhotonEstlla::spawn_line`, allocates 0x378 bytes. The shared class now declares
these fields and the 32-byte parameter record with size and offset assertions.
Unknown bytes retain unnamed storage.

The update tests the next position 60 units above the actor, queues destruction
on obstruction, and records contacted entity IDs before dispatching photon
hits and particles 0x162/0x163. The original inserts a ninth unique ID and stops
before dispatching its hit; this ordering is preserved. Movement updates x/z
only. Destruction unregisters the actor and frees its collision bodies before
the base destructor runs.

Native members replace the old overlay-based update and destructor, and a real
constructor replaces the free constructor and explicit vptr store. The compiler
emits the 316-byte vtable. The sole creator uses ordinary `new` and the shared
parameter record, preserving all 1,924 bytes of its nine-function unit.
The upstream `TObjPlayer::get_battle_param` declaration still returns an integer
address carrier; this bounded use converts it to the actor pointer consumed by
the original update. This change does not recover that lookup's broader API.

## Compile, compare, research, revise

The initial data reconstruction and native destructor preserve every instruction.
The literal 60.0 introduces an anonymous constant relocation until the unit
claims its original pool. A separately compiled C update also matches all
408 bytes; production remains C++.

The first fully typed constructor is 93.01515%: a const parameter permits
CodeWarrior to retain speed in a register and load hit scale early. A mutable
parameter restores the repeated speed loads and every original instruction.
The input is still only read. This records an observed compiler constraint,
not a claim about historical source spelling.

The [Gol Dragon fireball](gol-dragon-fireball-unit.md),
[Dragon fireball](dragon-fireball-unit.md),
[critical-hit effect](critical-hit-effect-unit.md), and
[compiler-emission investigation](compiler-emission-evidence.md) provide the
comparison cases for native construction, data ownership, alignment tails and
compiler-generated tables. A normal named `const char[]` puts this unit's class
string in read-only storage; the initial pointer-to-literal form instead put it
before the collision body in writable data. No new compiler control is needed.

## Data ownership and validation

The unit now owns these original ranges:

| Section | Range | Source contents |
| --- | --- | --- |
| `.rodata` | `0x80446E10..0x80446E20` | `TPhotonLine` class string |
| `.data` | `0x804C37D8..0x804C3940` | 44-byte collision body and compiler-generated vtable |
| `.sdata` | `0x805D3500..0x805D3508` | class-name pointer |
| `.sdata2` | `0x805DC1D8..0x805DC1E0` | 60.0f height offset |

The string, pointer and float each have four trailing zero alignment bytes.
The old pointer and float symbol extents included those tails; their real sizes
are four bytes. The float becomes local to its sole consumer. Split extents
retain the original alignment tails without artificial padding objects.

All four functions, all 392 covered data bytes, allocated-section byte contents
and normalized relocations match. The unchanged-main and final builds reproduce
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
`tools/check_pr.py` passes: no address-based code, function, data or linkage loss;
all 3,618 linked units exact; retention metadata current. The linker selects the
compiled TPhotonLine object once and its original fallback zero times.
Matched and source-linked data each increase by 392 bytes. Code/function counts
and the linkset are unchanged. Repository portable behavior and sanitizer checks
also pass.
