# Recover world-object paths and shared resource ownership

The combined 227-path review is at `e54879686e7d1ddff26569b6ee2a0373690d01ac` on the validated combat queue. [Matching and source-quality evidence](2026-11-23-combined-world-and-cutover-validation.json)

- Give lobby and field creatures their own resource factories and release hooks. Carry the native Ninja node and BML animation through path sampling and drawing. Keep the existing floor and object table order.
- Share the typed named-resource and nullable-release declarations across map objects, archive loaders, NPCs, quest and UI callers. The assigned model and Ginja texture pointers follow the actual allocation and release owners.
- Use the Ginja draw records in the UV-scroll query and update, and use the native strip buffers and Ninja model type in the strip collectors.

The benchmark removes 364 findings and adds 69, with zero newly stale retention entries. The labeled lifecycle changes below move factory and release declarations from the player to the class that owns the resources.

- The lobby pigeon uses `TUnk_804E0898` at `0x802C09A8`, `0x802C09E0`.
- The seaside bird uses `TUnk_804E08D4` at `0x802C1324`, `0x802C1370`, `0x802C13C8`.
- The Jungle bird uses `TUnk_804E0910` at `0x802C1AF8`, `0x802C1B44`, `0x802C1B9C`.
- The Jungle shrimp uses `TUnk_804E094C` at `0x802C21A0`, `0x802C21EC`, `0x802C2244`.
- The Seabed dolphin uses `TUnk_804E0988` at `0x802C28B4`, `0x802C2900`, `0x802C2958`.
