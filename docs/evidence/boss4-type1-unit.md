# Dark Falz type 1 source unit

`pso/boss/TBoss4Type1.cpp` owns `0x800525AC..0x80055678` and the
state table, collision data, and vtable at `0x80485AE0..0x80486370`.
The table's eleven 0x2c-byte entries carry three native `TBoss4Type1`
member-function pointers; the state dispatchers call them on the same receiver.
The upstream reconstruction used `TBoss4Type2` as the callback owner, but the
controller constructor installs the type 1 vtable and the network dispatch in
`TObjDFHorming` reaches it through `TBoss4DarkFalz__type1_instance`. The handlers
and their shared helpers therefore use the type 1 receiver, avoiding a member
call through an unrelated class. This changes symbol names, not instructions.
The compiler emits the 26 pointer constants and the initializer at `0x80055328`.
The vtable's seven empty status callbacks are in the adjacent, already-linked
`TObjPlayer_80055678.cpp` unit and are now declared as type 1 members.

The position generator at `0x80054FC0` fills a 64-entry array: it reserves
points around the active players and tries random candidates subject to the
arena and distance tests. Its second argument is the minimum distance from
an optional position. It uses the original random-call sequence and fused
floating-point arithmetic. The two constants at `0x80437628` and `0x805D8B28`
are compiler pools; the localization tool found no references from another
split. The unit uses its already-pooled `40.42f` value for its internal calls.

The state-table and native-class reconstruction adapts upstream commits
`6d4c7d18ee8e4615f8a6b627ef475432a79816f0` and
`f7b5dd56172c40050a5bb2d914a1982f4168096e`; the generator adapts
`bf460d72b531f011798c6928f4dff86be7eebfcf`. The fork's existing battle
parameter, sound, collision, and model-node interfaces are retained. The
position-selection output uses a full three-component local; the vector
subtraction and callback calls pass their observed arguments directly. The
Tenchu Furu and Ra Foie factories take their parent explicitly, and the shared
previous-position helper uses the actor base receiver. Their existing callers
are updated with those contracts.

The pre-existing strip-scrolling and two-component-copy helpers still have
legacy receiver views shared by other units. This change does not establish
portable ownership for those interfaces; they remain a bounded follow-up.
The class fields beyond the observed state and constructor/destructor accesses
remain bounded by padding; those names do not claim a complete original layout.

With GC/2.6, `-sdata 4` keeps the effect-ID pair in `.data`. The final six
functions are defined in reverse order under scoped deferred code generation,
which permits the compiler-generated vtable to share the unit's data base and
leaves the resulting functions in original address order. The generator needs
floating-point contraction. The porting exceptions register records these
settings. Exact function scores alone do not establish linkability: the unit
also needs the symbol extents, compiler-local constants, data layout, alignment,
relocations, and generated retention metadata checked together.


## Independent review on current main (2026-11-13)

Reviewed the original PR #446 commit `44bfff3c72a73a69a9f4b48c32e3e1e7513b3871`
and its three cited upstream implementations, then integrated fork main
`34742a01fa18f1df3b4d838871297333cc8d1c76`. The integration preserves main's
typed BML texture-list access. Merge conflicts in compiler settings and retention
metadata were resolved by preserving both units' entries; the exception inventory
was regenerated. The review also corrected the state-table owner comment,
recorded the effect-ID placement reason beside the compiler override, refreshed
the register counts, and added the upstream adaptation to the third-party index.

The base was extracted from that immutable main commit into a separate directory.
Both builds generated fresh split objects and config inventories from their own
source trees and the local original disc; neither reused compiled game objects.
The tool executables and compiler installation were copied from the local build
cache (dtk 1.8.4, objdiff-cli 3.6.1, GC/2.6 with the repository's per-unit settings).
Configuration used explicit local tool paths; both full `ninja -j2` builds passed.
Unchanged main passed the full no-build gate against its own saved baseline,
including all 3,616 linked units and a retention check with zero drift.

The reviewed source tree passes `tools/check_pr.py --no-build` against that fresh
main baseline:

- Matched functions: 27,499 to 27,501 (+2); matched code: 4,294,708 to
  4,296,388 (+1,680); matched data: 1,490,204 to 1,492,356 (+2,152).
- Linked code: 4,086,576 to 4,099,068 (+12,492); linked data: 1,479,048 to
  1,482,024 (+2,976); linked units: 3,616 to 3,617 (+1).
- No function, address, data or link regressions. All 60 unit functions, 12,492
  code bytes and 2,976 data bytes are exact. Every unit section is 100% matched.
- All 3,617 source-linked units pass the link check; retention metadata has
  19,430 entries, zero additions and zero stale entries.
- The rebuilt `build/GPOE8P/psov3.dol` has SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3` on both base and reviewed trees.
- Python syntax, all 346 synthetic tool tests, portable behavior tests,
  ASan/UBSan checks, changed-line whitespace, and
  `tools/list_port_exceptions.py --check` pass.

The review covered constructor/destructor ownership, native vtable slots and
state callbacks, the position generator, shared factory/position callers,
symbol boundaries and source-link selection. No blocking findings remain.
The pre-existing shared helper ownership limits described above remain unchanged.
