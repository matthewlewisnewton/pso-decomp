# Finish native actor, resource, and client interfaces

This 189-path follow-up carries the final actor, resource and client recoveries over the combat and techniques batch. The current local head is `9731d94a7f` on combat candidate `cd29476f2f`.

- Pass native character and collision records through wall-slide and player-overlap queries. Use typed breakup pieces and model pointers in the existing Barba Ray effects.
- Preserve the screen fade constructors and callbacks while drawing through `NJS_POINT2COL`. Share the existing glyph-quad layout and carry the player's native texture list through model loading and rendering.
- Pass typed archives, particle controllers, packets and client responses through their existing callers. Keep the established names and fields where their meaning is known.
- Use the subtractive RNG as the reseed receiver and the item drop table as the channel-ratio receiver. Call `trim_whitespace(char *)` for the quest text buffer.

The full build matches retail SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3` with 27,572 matching functions, 2,295 linked units and zero coverage loss. Focused probes cover fade setup and completion, player scale messages, weapon animation, Photon Blasts, collision, technique behavior, forwarding the original user-search answer, eight text trim cases, five reseed inputs, and six RNG channel cases. [Validation](2026-11-23-followups-on-latest-pr385-and-pr386.json)

The upstream source-quality checker removes 582 findings and adds 20 across 187 source paths. The advisories cover preserved linkage for shared calls, established labels such as the controller-activity helper, unresolved members in otherwise typed records, and declaration parameter names that differ from their definitions. The ownership checker flags `SubtractiveRng::reseed` because it delegates to the shared seed function. The receiver is the RNG whose state that function rewrites, and the method returns that same RNG. The twelve linker-label changes follow the recovered owners and signatures. At `0x802421A4`, `handle_user_search_answer` accepts the same `TUserAns &` as the command `0x41` callback and forwards that record to the Guild Card update. The benchmark flags zero labels and zero newly stale retention entries.
