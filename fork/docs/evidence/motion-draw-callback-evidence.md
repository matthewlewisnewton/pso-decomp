# Motion drawing and model callbacks

The original `draw_model_motion` at `0x803E4AF4` passes a root in r3, motion in r4, frame in f1, and a model-draw callback in r5 to the tree helper at `0x803E4BDC`. The tree helper forwards f1 to `bind_motion_context`; it is an input even though the previous source declaration omitted it. The blend tree uses f1 as its blend factor. The shape-bound path likewise forwards f1 to motion binding.

The draw callback receives one model payload pointer and produces an integer result. It is distinct from the void node-visit callback. `transform_chunk_object_tree` uses its result to decide child traversal for nodes with flag `0x100`; other paths ignore it. The chunk and Ginja draw targets and the Ginja queue share this callback interface. The original context pointer refers to separate 0x10-byte storage, with the callback slot at +0xC.

The original call inventory contains 101 calls to `draw_model_motion` and 20 to `bind_motion_context`; ten outer caller units and four binder caller units remain original fallbacks. Root and model payload types remain opaque at this boundary. Motion inputs can be null in the binder. Existing callers use heterogeneous storage overlays, and these changes do not establish their object lifetimes or ownership.

The existing chunk draw target source has paths that fall through without a defined C++ return value. The callback type records the observed result register and its use; it does not resolve those pre-existing source semantics. No claim is made that the source spelling or owners recovered here are the original names.

Adjacent queue-matrix and graph-traversal declarations still disagree across translation units. The separate `model_node_callback` and `motion_node_draw_callback` interfaces also remain outside this recovery; they must not be conflated with this model-draw callback or the chunk-node callback.
