# Chunk model node callbacks

The original setter at `0x803E4CE0` stores a single global callback. Its callers and the three traversal dispatch sites support the shared contract `void (*)(NJS_OBJECT*)`: dispatch passes the current node, and none of the dispatchers uses a return value. The original binary does not establish the source spelling of the type or independently prove the declared return type. The audited setter calls register 37 distinct callback targets; the player cache also forwards a node to a secondary callback with the same contract.

The callback is global state. In particular, the cache's `apply_with_callback` installs its capture callback and then clears the callback; it does not restore an earlier one. These operations are not reentrant.

The `TUnk_804F1C58` cache is a 0x3C-byte `TObject`-derived object. The original constructor and traversal code support the following fields:

| Offset | Role |
| --- | --- |
| 0x1C | Borrowed node-tree root (`NJS_OBJECT*`) |
| 0x20 | Motion (`NJS_MOTION*`) |
| 0x24 | Frame |
| 0x28 | Owned matrix array |
| 0x2C | Signed node count |
| 0x30 | Draw cursor |
| 0x34 | Draw-node callback |
| 0x38 | Capture callback |

The original cache sampling call passes the current frame in `f1`. Cached drawing uses global storage, rather than reading the array from `m_28`. Despite its existing name, `draw_node_tree_if_visible` gates on the motion pointer being non-null.

The sole original cache construction and capture-callback registration occur in `text_802EDE90`, which remains an empty-source fallback. The constructor still uses raw initialization and a pre-existing `TObjBoss2Tunnel::count_tree_nodes` receiver alias; this work does not establish that receiver's actual type. Other model interfaces remain heterogeneous, so the node callback evidence should not be used to narrow model pointers globally. Some changed callback source units also remain binary fallbacks until their implementations are recovered.
