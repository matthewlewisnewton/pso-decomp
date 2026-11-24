# Recover the footprint unit from upstream #208

This port starts at fork `9924ce113b5e6dff309a5ae94065265d3066fb24` and adapts
upstream [#208](https://github.com/zeroz41/pso-decomp/pull/208),
`ae797d392bb93d5bf7164341870f78f864da23b0`, without folding more upstream history.
The source remains at the fork's `pso/misc/TPlayerFootStamp.cpp` path.

## Unit ownership and class layout

The footprint unit owns `.text:0x802AF83C`–`0x802B01D8`. Its render and update
methods previously occupied the tail of the fork's `TObjMistCtrl.cpp`; those two
functions move into the footprint unit without losing their exact matches or
source linkage. The mist-control unit ends at `0x802AF83C` and remains linked.

The constructor at `0x802AF9C0` was missing. Upstream supplies it as a real
`TPlayerFootStamp(TObjPlayer *, s32)` constructor, with the original 0xC4-byte
allocation and compiler-generated vtable. It chooses footprint dimensions from
player class and height, projects the step onto the ground, constructs a rotated
quad, and initializes its 150-frame lifetime. The shared header verifies the
vertex size, class size and all recovered field offsets at compile time.
The separate texture-loader/setter unit stays linked; its padded shadow view is
replaced by the new `texture` member.

The claimed data is source-defined class dimension/height tables, a class-name
string and pointer, compiler-generated vtable and switch table, and floating-point
constants: `.rodata:0x804707F8`–`0x80470908`, `.data:0x804DE4F8`–`0x804DE540`,
`.sdata:0x805D3E88`–`0x805D3E8C`, `.sdata2:0x805DE1F8`–`0x805DE214`.
The localized literal symbols have no external consumers in the current split
inventory; linking and the final original-DOL hash validate their placement.

## Required shared-interface corrections

- The accessor at `0x8004C1EC` returns `this + 0x5C`, the existing
  `TObjBase::rotation` member (`CameraAngles`, whose yaw is offset 4). Existing
  Falz callers use it on players to set their yaw. Rename the misowned
  `TBoss4DarkFalz::get_hit_data` to `TObjBase::get_rotation`, return the existing
  shared type, and update those callers. This avoids importing upstream's cast
  from a player to an unrelated boss class. The getter and all affected callers
  retain their exact machine code.
- `fn_803D8DE0` at `0x803D8DE0` forwards a matrix plus vector source, destination
  and count to `PSMTXMultVecArraySR`. Its old one-argument declaration omitted
  three live arguments. Declare all four and forward them explicitly. Correct
  the SDK header to match its already-existing implementation
  `(const GC_Mtx, const Vec *, Vec *, u32)` and remove the obsolete header-name
  workaround. No SDK assembly body changes. `TDeadSpot` now uses the same wrapper
  declaration and a `Vec` basis array. Both the wrapper and its existing caller
  remain exact.
- Use the fork's typed ground-query, camera-position and current-texture-list
  APIs. Add the existing C++ `set_texture_num(s32)` declaration to the typed
  texture header so the new source does not include conflicting legacy texture
  declarations. The factory's existing `void *` interface and 32-bit texture
  handle are retained as compatibility boundaries, not claimed as portable APIs.

## Remaining compiler constraints

The one new per-unit override is recorded in section 5 of the
[porting exceptions register](../porting-exceptions.md). Each setting was removed
individually from the otherwise matching compile command:

| Probe | Result |
|---|---|
| `-fp_contract off` | Constructor falls to 90.710144%; other five functions remain exact. The scale/corner arithmetic requires fused multiply-adds. |
| `-inline off` instead of `off,deferred` | Constructor falls to 99.7619%, render to 99.84375%; `.data` is 33.333332% and `.sdata2` 14.285715%. Function, vtable, switch-table and constant emission order changes. |
| `-str reuse` without `readonly` | Constructor is 99.94824%; `.rodata` is 95.38461% and `.sdata` 50%. The class-name string and its relocation leave the required layout. |
| All three upstream settings | Every function and allocated section is 100%; the compiled object links into the original DOL. |

For a nonmatching port, drop the compiler switches, choose explicit fused
arithmetic behavior where needed, and let the compiler lay out strings and tables.
This port adds no assembly, intrinsic, raw-offset object view, shadow class or
hand-written vtable. It does not broaden the section 7 upstream exception scope.
Existing compatibility boundaries above remain candidates for later API cleanup.

## Validation and gain

Built the current-main baseline with the pinned tools and original inputs, saved
its report, and checked clean retention before changing source. The final build,
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`, address-aware
regression check, all linked units and retention check pass.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,368 | 27,369 | 1 |
| Exact code bytes | 4,183,640 | 4,185,572 | 1,932 |
| Exact data bytes | 1,469,407 | 1,469,759 | 352 |
| Linked code bytes | 3,643,320 | 3,645,480 | 2,160 |
| Linked data bytes | 1,166,675 | 1,167,051 | 376 |
| Linked units | 3,574 | 3,575 | 1 |

The 300 bytes moved from the mist-control unit were already linked and are not
counted again as new coverage. The six generated retention additions belong to
the footprint unit; none are removed. Eight zero alignment-padding bytes at
`.sdata:0x805D3E8C` and `.sdata2:0x805DE214` leave aggregate split coverage;
the checker explicitly permits them and no data object or prior match is lost.
Other #208 work and the network/data gaps remain deferred as described in the
[carrier audit](upstream-catchup-207.md).
