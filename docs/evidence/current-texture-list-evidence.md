# Current texture list

The original setter at `0x803DA798` is a free function: it stores its input in the current render context at +0x20 and returns 1. It does not dereference or validate the input; a null list is accepted by the setter, although later texture operations can dereference it. The context retains the pointer, so the list and its entries and texture objects must remain valid for the later draws that use them.

The original `set_texture_num` path follows list +0 to an array of 12-byte entries, then entry +8 to texture state. This supports the existing `GinjaTextureList` and `GinjaTextureEntry` layout. `NJS_TEXLIST` has a compatible binary prefix and entry stride, but that alone does not prove C++ type aliasing or object lifetime across all call sites. Existing integer-held handles and overlay pointers remain explicit casts at this boundary.

The original inventory contains 600 direct calls in 375 units, including 45 units linked from original objects. Thirty-nine source calls previously depended on a live input register; their original getter or incoming values are passed explicitly here, with each getter evaluated once. Two source calls supplied a second value that the original setter does not consume. The Jungle door's former nested setter/matrix-push call is split into the original two calls; the setter's integer result is not a matrix pointer.

Several producer functions still have heterogeneous or legacy declarations, including the BML texture getter, and some source units remain original fallbacks. This recovery does not establish all resource ownership, producer signatures, or C++ object lifetimes. The original source spelling is not established.
