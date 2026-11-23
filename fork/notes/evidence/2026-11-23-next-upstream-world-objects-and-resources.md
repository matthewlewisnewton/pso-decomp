# Recover world object and shared resource ownership

This review recovers the resource lifecycle for lobby and field creatures and the interfaces their loaders, path renderers, and release hooks use.

- Move factory, load, and release callbacks from player declarations onto the existing classes for the lobby pigeon, seaside bird, Jungle bird, Jungle shrimp, and Seabed dolphin. Preserve the floor and object table order.
- Carry the Ninja node and BML animation through path sampling. Use the native Ginja draw records, texture lists, and strip buffers for collection and scrolling.
- Share the named-file and nullable-release interfaces. Carry the real allocation and texture pointer types through the participating resource loaders.

The review at `c3b0000bea8218676b3e1667eeb19bbda8174f19` spans 235 paths and builds on the gameplay sound review `6e64253b42307a9ea82494d16f27beb0928cd213`. It includes upstream PR #375. The retail DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`, with 27,572 matching functions, 2,368 linked units, and zero coverage loss. Focused checks cover the ambient lifecycle and factories, path and fish sampling, Ginja strips, heap release and BML loading. [Validation](2026-11-23-post-sound-world-review-validation.json)

The source-quality benchmark removes 360 findings and adds 67 references to existing address-named ambient classes. It reports zero newly stale retention entries. The 14 flagged labels move lifecycle declarations to their existing owners.

- The lobby pigeon uses `TUnk_804E0898` at `0x802C09A8` and `0x802C09E0`.
- The seaside bird uses `TUnk_804E08D4` at `0x802C1324`, `0x802C1370`, and `0x802C13C8`.
- The Jungle bird uses `TUnk_804E0910` at `0x802C1AF8`, `0x802C1B44`, and `0x802C1B9C`.
- The Jungle shrimp uses `TUnk_804E094C` at `0x802C21A0`, `0x802C21EC`, and `0x802C2244`.
- The Seabed dolphin uses `TUnk_804E0988` at `0x802C28B4`, `0x802C2900`, and `0x802C2958`.

The six other label changes follow the shared release and named-file functions, typed strip buffers, and native path owner and arguments.
