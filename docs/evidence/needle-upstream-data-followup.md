# Needle upstream data follow-up

This draft imports the Needle portion of upstream
`1eadd7feea746a6f5bd1c4d905ff7700e6b724b1` and preserves the authored builder
commit `c5e453d76e407c851294cd61442585d8336f9ae6` with a cherry-pick trailer.
Both are Scott Lowry's work. The unrelated equipment jump table in the first
commit remains excluded. The fork base is
`0ea667b2ae02f09c65cd9464314c0d5993618c6c`.

The corrective commit gives Needle a genuine constructor/destructor, a live
`Vec` position, particle/motion pointers and twelve target flags. State dispatch
passes the actual receiver. Legacy helper labels are retained as typed free
boundaries because their old Tentacle class association was false. The spawn
caller uses the player's existing position. Shared resource getters use their
index argument and consistent declarations in their immediate consumers.

The node bank uses actual `DragonModelNode` objects with child/sibling fields;
the vector bank uses `Vec`. Their expected extents are:

| Bank | Start | Bytes | Elements |
| --- | --- | --- | --- |
| Model nodes | `0x80541528` | 784 | 14 × 56 |
| Segment positions | `0x80541838` | 168 | 14 × 12 |
| Angles | `0x805418E0` | 56 | 14 × 4 |

The adjacent motion-state symbol is not claimed. Only its three observed
pointer slots are declared; the original fallback retains its trailing bytes.
No buffer or padding object is invented.

## Bounded native follow-up

The released `copy_model_node` provider now uses the compiler-supported
`__memcpy` representation copy for its first 52 bytes. The final four-byte float
access is retained and explicitly unresolved. Ordinary `memcpy` produced a
180-byte function; using the intrinsic for a temporary float produced 128 bytes.
Keeping the original float access produces the original 116 bytes. Under the
unchanged GC/2.6 profile, the owning Dragon object's allocated sections and all
2,591 relocations into allocated sections are identical to its paired baseline, and all
reported code/data sections remain exact. This removes integer/byte-block
prefix overlays; it does not qualify the tail storage or create a new gain.
The vendor documents the intrinsic as an inline block copy (Metrowerks
[MPC5xx Targeting Manual, page 161](https://www.nxp.com/docs/en/user-guide/MPC5xxUG.pdf)).

Paired native diagnostics compiled Needle, Behavior and the immediate Player
consumer against exact baseline/candidate header snapshots. They found and
corrected signed timer comparisons, the Tentacle predicate's return width, and
a texture getter that was declared `void` while its caller consumed a result.
The getter now returns the underlying provider's existing integer address and
uses its canonical declaration. Needle also uses the canonical particle-attach
declaration. The particle restart helper retains the baseline source's local
address reuse because separating those locals introduced an extra MWCC move;
this is an emission constraint, not a claim about the original source locals.

The final bounded checks show no prior-exact function regressions in Needle or
Player. Player's object is unchanged. Behavior retains one raw constructor-call
relocation mismatch after the known constructor-symbol rename; final
address-aware relocation and link proof remains pending. The genuine Needle
destructor, state dispatcher, signed comparisons and predicate callers are exact. The constructor remains
nonexact (408 bytes against 416), including a remaining `memcpy` call and float
scheduling differences. The genuine constructor also emits the 24-byte Needle
vtable after the Tentacle vtable, whereas its original address `804E4830`
precedes the current unit claim at `804E4848`. Its ownership and emitted order
need explicit repair before source linking; the current split is not expanded
to conceal this mismatch. The builder's report also needs address-aware treatment
of the new section-base relocations; its raw symbol score is not acceptance.

The candidate Needle object emits exactly 1,008 `.bss` bytes with alignment 8:
node bank at offset 0, positions at 784, angles at 952. The adjacent motion-state
storage is not defined. The inherited `.rodata` and `.sdata2` mismatches also remain.
This proves emitted bank layout, not native source
linkage: this unit is still held and remains fallback in the final link policy.
All native diagnostics used scheduled development capacity. Unchanged baseline
objects were reused; no configure, full link or acceptance lane was used.

## Open qualification

The provider's final `f32` access at offset `0x34` still requires a live float
in both records. `NJS_OBJECT` and Dragon8's local node declare byte tails there;
identical offsets do not establish compatible objects. Their owners must resolve
the shared storage contract. The Needle resource getter and traversal also need
proof of the loaded BML graph's node types, terminal links and borrowed payload
lifetime. No reinterpret cast or matching instruction result closes these holds.

This draft is not source-qualified or ready to merge. Pending checks are the
remaining constructor and address-aware builder comparison, complete affected
consumer qualification, actual ordered native source inputs and retained fallback
coverage, followed by the merge owner's current-main original-DOL and strict
no-loss acceptance. No new exact or linked gain is claimed. Existing #226 data
and active-union repairs remain; README and linked-unit policy are unchanged.
