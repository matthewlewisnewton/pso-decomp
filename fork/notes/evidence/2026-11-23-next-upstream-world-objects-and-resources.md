# Recover world object and shared resource ownership

Recover the typed resource interfaces used by world objects, NPCs and texture animation. Preserve the original factory ordering and resource lifetimes.

- Use the native Ginja and Ninja model records through UV scrolling and drawing. Make chunk strip counting and collection private operations of `StripBufferPair`.
- Pass shared texture and allocation types through the world and NPC resource loaders. Preserve the existing nullable-release and named-file contracts.
- Read the five tables in `JudgeItem.rel` through one resource record. Special, grind and percentage rolls share the weighted-entry format and use their respective score tables.

## Source quality

The current benchmark removes 271 findings and adds three across 154 source files. The three findings are declarations for `has_texture_scroll_entry`, `set_ginja_texture_wrap_repeat` and `collect_scroll_uv_entries__19TOComputerMachine01FiPvi` in `GinjaUvScroll.h`. The declarations share the typed Ginja records while preserving the existing linkage. The first two helpers also preserve their null-record behavior. The four strip labels follow their private C++ methods. The two other changed labels follow the shared nullable release function and the typed Ninja texture-list parameter. The benchmark reports zero flagged labels and zero newly stale retention entries.

## Validation

Local review `a72efc88aa` covers 156 paths on the frontend candidate `d3ec0458b9`. The retail DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`, with 27,572 matching functions, 2,295 linked units and zero coverage loss against fork main. The retail and rebuilt executables both pass the strip selection, winding, scrolling, allocation failure and release cases, as well as JudgeItem loading, ten score lookups and six weighted roll cases. The local cumulative build passes coverage and retains all 1,147 original data bytes. [Validation](2026-11-23-followups-on-latest-pr385-and-pr386.json)
