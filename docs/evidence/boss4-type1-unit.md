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
