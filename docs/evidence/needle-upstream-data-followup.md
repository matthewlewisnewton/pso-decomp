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

## Open qualification

The shared `copy_model_node` provider still accesses model records through
unrelated integer and byte-block views. Its canonical copy/lifetime contract
requires coordination with the Dragon owner before this draft can pass source
qualification. This branch does not modify that shared provider.

The draft is not native validated or ready to merge. Layout assertions and a
host syntax comparison do not prove MWCC output. Pending checks are paired
Needle/Behavior/immediate-consumer compilation in development capacity, all
prior exact functions, physical relocations, actual bank order/alignment and
source linkage, followed by the merge owner's current-main original-DOL and
strict no-loss acceptance. No new exact or linked gain is claimed. Existing
#226 data and active-union repairs are retained; README and linked-unit policy
are unchanged.
