# Finish native actor, resource, and client interfaces

This 216-path follow-up closes the remaining source changes on the validated combat review `3101817acc4c8b0e430a78822de084988283c924`. The review is at `f273a58d6aae78d8051c9d66aa25781e3ad73c79`.

- Use the native character and collision records for wall probes, targeting, boss motion, and object breakup.
- Give the existing fade tasks their own initializers and completion callbacks. Preserve the Ninja polygon fields used by the renderer and the existing SDK math declarations.
- Share the typed archive, item, quest, and client records where their layouts are established. Keep documentation and tooling on the fork layer.

The full build matches retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` with 27,572 matching functions, 2,368 linked units and zero coverage loss. Focused probes cover fade setup and completion, player scale messages, weapon animation, Photon Blasts, collision, and technique behavior. [Validation](2026-11-23-complete-local-review-stack.json)

The benchmark removes 720 findings and adds 61. The five flagged labels follow the existing task classes and corrected parameters. There are zero newly stale retention entries.

- `0x800F8754` The fade-in initializer now owns its alpha, color, and completion callback on the existing fade task.
- `0x800F8878` The fade-out initializer now owns its alpha, color, and completion callback on the existing fade task.
- `0x802E6F10` The breakup actor initializes its own pieces from a typed readonly matrix.
- `0x802E7474` The breakup allocator receives the native Ninja node.
- `0x802E7568` The existing breakup object owns the initialized fields.
