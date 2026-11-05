# Motion table setters

The two `TObjMotion` setters at `0x8002AE84` and `0x8002AE7C` store their
pointer argument at offsets `0xD8` and `0xDC` respectively. Those fields are
the existing `TObjMotionAction *action_table` and `BmlMotionEntry *motion_list`.
Actions select entries in the motion list, and the tables are not claimed
deeply const: existing code modifies action speed and motion interpolation
state.

The member signatures now take the respective pointer types. Many older
callers still obtain addresses from integer fields, generic arrays or local
overlays; casts preserve those existing boundaries but do not prove object
lifetime or establish the concrete type of every producer. Two legacy
hand-mangled action-table calls retain an unused extra argument and
incompatible declarations; their enclosing caller recovery remains separate.
The original object inventory has 69 action-table and 47 motion-list calls;
some corresponding units have no implemented setter call in the current
source, so this migration does not claim all original callers are native.
