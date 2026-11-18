# Window native lifetime with deferred emission

Register entry: [§5 Window native lifetime emission (deferred codegen)](../porting-exceptions.md#window-native-lifetime-emission-deferred-codegen),
approved by Matt on Nov 14 2026, 1:35 PM PT. The [balloon follow-up](balloon-native-lifetime.md) retired the last raw site recorded in [§9](../porting-exceptions.md#9-window-lifetime-entry-points-for-legacy-raw-storage-functions).

## Change

The raw `TWindowBase` constructor/destructor calls in the DD selection window
(`TUnk_804EFBAC`), `TWindowDD_WS_ScrollBar`, `TWindowDD_WS_Word` and the ComCard
follower window (`TUnk_804CE964`) are replaced by real C++ constructors with
`TWindowBase` base initializers, real virtual destructors with automatic base
cleanup, compiler-generated vtables and ordinary `new` in their factories
(including `TWindowSimpleStatus::update_status_icons` for the follower).
`TWindowComCard.cpp` is split at `0x80249CBC`; the follower lives in
`TWindowComCard_80249CBC.cpp`. The follower's offset parameter is a non-const
`ComCardWindowOffset *`; the `const` form changed float-copy scheduling (84.6%).

## Why deferral

The original constructors reach the vtable from the same data base register as
the layout and descriptor arrays (for example ScrollBar: one base for
`0x804EFBC8`, descriptor at `+8`, vtable at `+0x1C`). MWCC pools only data
objects already defined when a function is generated. A compiler-generated
vtable is created at the end of the unit, so with default emission it is always
loaded separately. Standalone probes with the unit flags confirmed: a
hand-written table pools; a generated table never does, independent of key
function placement, inline or out-of-line constructors, weak or strong tables,
definition order, `static` linkage or typed aggregates. Only deferred
emission (`-inline off,deferred`) pools the generated table. Deferred emission
reverses definition order, so these units define functions bottom to top.

| Constructor | Default flags (best natural) | Deferred |
|---|---:|---:|
| `TUnk_804EFBAC` | 54.88% | 100% |
| `TWindowDD_WS_ScrollBar` | 61.46% | 100% |
| `TWindowDD_WS_Word` | 70.86% | 100% |
| `TUnk_804CE964` (non-const offset) | 100% | 100% |

All destructors match natively. Generated vtables are 0x18 bytes; the former
0x1C symbols included four bytes of alignment padding, and split ends are
adjusted so that padding stays covered (`TWindowComCard.cpp` `.data` ends at
`0x804CE918`).

## Verification

Against main `1563389ef3`: `check_pr` 0 regressions, matched data
1,504,728 -> 1,506,332 (+1,604), complete data 1,502,508 -> 1,504,112 (+1,604),
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`, `link_units.py check`
and `force-active --check` pass; 3,619 linked units.

This reconstructs emitted layout; it does not establish the retail build
options or original source order. Ports use the ordinary constructors,
destructors and `new`, and omit the override.
