# Recover native frontend, world, combat, and client interfaces

## Summary

Recover the remaining C++ interfaces carried by the fork. The four commits separate the work by subsystem and share the same retail matching baseline.

| Commit | Paths | Recovery |
| --- | ---: | --- |
| Frontend windows, chat, and HUD | 198 | Use the native window and sprite records for menus, equipment, radar, Symbol Chat, and scroll bars. Pass the native draw context through selection and capacity labels, and use the actual deferred-render queue receiver. |
| World objects and shared resources | 156 | Use native Ninja and Ginja records through scene resource loading and UV handling. Give strip traversal to its buffer and share one typed layout for the five JudgeItem tables. |
| Combat, techniques, and actor state | 464 | Share the cast, target, collision, enemy placement, and state records across players, NPCs, and enemies. Recover weapon and Photon Blast interfaces and retain the original player scale packet layout. |
| Client, actor, and resource interfaces | 189 | Use the native movement and fade records, typed client replies, the item drop and RNG owners, and the quest text buffer. |

Some paths are shared between commits. The combined diff spans 845 paths, including the symbol and link manifests and one per-unit compiler setting.

## Validation

The locally validated head `2b89d90b12` builds on rehearsal tree `775f500b83`, which matches GitHub's tested gameplay sound merge tree on master `d339fbdcd5`. The retail DOL matches byte for byte, with SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All 27,572 functions match and all 2,295 source units link. The coverage checks show zero lost matched or linked code and non-padding data against both the sound base and fork main. All 1,147 original data bytes are accounted for, including 167 bytes of original alignment padding.

Each cumulative commit matches retail independently. The combined image is byte-identical to the image that passed the action palette, scroll bar, Symbol Chat, strip selection and release, JudgeItem load and rolls, all five enemy spawn routes, quest text trimming, and RNG seeding and channel probes.

## Source quality

Upstream’s #393 checker removes 5,987 findings and adds 364 across 842 source files. It reports 265 function-label changes at the existing addresses and zero newly stale retention entries. Four labels follow the typed draw-context signatures. The two Mericarol shadow constants retain their upstream data labels and use explicit typed storage to preserve the retail data order.

Using the existing `WindowDrawContext` pointer and native resource buffers reduces added repeated casts from 83 to 55 and added `void *` argument casts from 57 to 19. The typed menu helpers remove 11 pointer-to-integer casts. Existing integer-address interfaces still take address conversions, including PRS decompression. The ownership checker flags `SubtractiveRng::reseed` because it delegates to the shared seed function. That function initializes the receiver, which the method then returns.

| Flagged address | Why the linker label changes |
| --- | --- |
| `0x8002E62C` | The existing breakup-piece constructor takes a read-only 3-by-4 matrix. |
| `0x800D80E4` | The ground-spot constructor takes a read-only position and a Ninja texture list. |
| `0x8032BCBC` | The deferred-render queue owns the dispatch function and accepts a `TObject` from its three callers. |
| `0x803375F0` | Ground snapping belongs to the projectile spawned by Morfos and uses its `Vec`. |
| `0x80337824` | That projectile’s constructor takes a read-only position and a `TObjChara *` owner. |
| `0x8035A69C` | The node-recording task owns the draw callback and receives a Ninja object. |
| `0x8035A740` | The same task owns the visibility-checked draw callback. |
| `0x8035A860` | The node-recording task constructor receives a Ninja object. |

## CodeWarrior settings

The main-menu unit uses a per-unit inline setting to preserve the two word-pair copies in the generated row-position assignment. The scroll bar extent setter, Dragon hierarchy clone, wall query, debris construction, and ground adjustment retain scoped scheduling settings. Gibbles retains its loop-invariant settings. Barta, Gi-Barta, Megid, and two weapon idle callbacks retain scoped inlining. Disc-error message initialization uses optimization level 2 for the original argument setup. The retail build covers these settings.
