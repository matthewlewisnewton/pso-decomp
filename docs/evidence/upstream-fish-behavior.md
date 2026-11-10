# Fish behavior recovery

Base: fork main `224eb99838471c243b20c305eddac75e7ff76c8f`.
Reference: upstream #240, `dd7a1a2d6e200a69462fff12172ff35aaa460c93`,
`src/pso/object/ambient/TObjFish.cpp` and its entry layout.

Recover `TObjFish::run_task` at `0x8029D974` (2,044 bytes): movement, boundary
reflection, player avoidance, target return, turning and animation advancement.
Use the fork's shared actor lookup, math and client interfaces and its typed
`rotation.yaw` field. The 0x44-byte fish entry has size/offset assertions, and
`m_a0` is now its pointer. The two existing animation tables are expressed as
five rows of three values with identical data.

## Constants and compiler constraints

Claim the native float pool `0x805DDD40..0x805DDD88` (72 bytes). Literals in the
update, renderer and initializer reproduce that pool. The former separately
named 10430.38043493439 double is removed because the compiler now emits it from
the update's expressions. Keeping both definitions creates a duplicate eight
bytes and shifts its symbol. The conversion bias and angle double remain in
the existing `.rodata` range. Localization verified no outside readers before
marking 20 compiler-generated constants local; no binary assets were copied.

Retain upstream's unit-level `-pool off`: otherwise MWCC shares a rodata base
register, saves an extra register and emits a 0xC0-byte frame rather than 0xB0.
The update scores 90.8317% with pooling, and 100% with the original independent
table/constant references. Existing `fp_contract on`, `dont_inline off` and
`inline_depth(4)` pragmas cover the update as they cover the neighboring
renderer; no pragma is added. Ports can drop pool/inline steering and should
preserve required float contraction, the double-precision angle conversion and
signed 16-bit angle wrapping if identical behavior is required.

## Shared-interface correction on current main

The follow-up integrates fork main `387621104107ed1ff8c650bf2f50ef00c6859ba4`
and fixes the recovered renderer's actual call interfaces. It subsequently
synchronizes with main `65b21c210ae980e9d2fe4aef1a3314ed84df1ddd`, preserving
the keyboard and technique recoveries and their folded-unit configuration.
The later synchronization with main `12cc95ca737a3a8757c17f45df06a9af4821d872`
retains the PPP/session recovery and its exception rows. Fish source, declarations
and compiler settings are unchanged by these synchronization merges.
The synchronization with main `4e784e247d991f1fb25766fc80923242a9ba469a`
also retains the dispatcher/TCP extraction and its existing compiler settings;
it adds no fish implementation change or fish output-layout steering.
After that publication, main advanced through the Vol Opt debris and Canadin
recoveries. The final refresh waits for the stable progress-table head
`b2a90ff1eabedf275aaed6cc16acbbd3e8b4a36c` and preserves those current-main
changes and their existing compiler/mapping settings without changing fish code. The old zero-argument
`draw_ginja_object()` declaration depended on the preceding model getter leaving
its return value in r3. The renderer now passes that model explicitly and uses
the shared Ginja, motion draw, BML getter and matrix declarations. Its visibility
call uses the real base-class virtual declaration rather than a synthetic class.
`update_state` returns a full-register integer result, preserving the native
`cmpwi` call contract without a function-pointer cast or low-byte test.

Resource ownership uses `BmlResource *`; camera reads use the shared,
offset-asserted `TCameraCtrl::position`. Five 0x30-byte area records contain
terminated filename lists and `BmlResourceDescriptor` fields, including real
16-bit model/motion counts. This replaces pointer slots holding packed integers.
Size and descriptor-offset assertions preserve the original object layout.
The existing lifetime wrappers now pass the parent explicitly to the verified
base-constructor ABI and use the declared object allocator/deallocator and school
initializer directly. No new compiler option, pragma or output-layout steering
is added by this interface correction.

## Remaining inherited debt

The hand-written vtable and constructor/destructor wrappers remain unchanged in
structure, including manual vptr writes, and still block treating this as clean
native lifetime/virtual-dispatch recovery. The renderer and initializer also
retain separate raw entry views, and some shared model/texture getters and heap
helpers carry legacy 32-bit address values. The explicit conversions at those
shared boundaries need pointer-sized types and target heap services in a port.
These are inherited limitations, not evidence that all original class/interface
ownership has been recovered. Matching completeness alone does not resolve them.
No assembly, intrinsic, hardware access or new emission pragma is introduced by
the follow-up. Existing `-pool off`, FMA and inline settings remain as documented
above; the final inventory after main synchronization is 5,773 pragmas in 877 files
and 180 unit overrides, including main's existing dispatcher/TCP and Vol Opt
settings. The refresh introduces no additional fish compiler setting.

## Validation

The initial recovery was validated against the base above. The shared-interface
correction is separately compared against the freshly built PR-plus-current-main
baseline `c3a77888e3c4e14bed709b60db8f6870f3ee1063`. The final integration is
also checked against independently built unchanged main `b2a90ff1e`; both build
and retention checks pass, and the subsequent synchronization loses no exact
function or linked range. The earlier `65b21c210` synchronization inherited four
zero padding bytes removed from report coverage by main's unit folding; the
later synchronizations remove no further coverage. Canadin consolidation changes
unit counts without losing address coverage, as checked against the previously
published head `03c1430e3f`. The original DOL
still matches. Full build
and `tools/check_pr.py` pass with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Against current main `b2a90ff1e`,
no exact function, code/data address, linked range or padding is lost. All nine functions (4,704 bytes) and all 1,404
data bytes are exact. Retention adds 45 names and removes none.

Gains against current main `b2a90ff1e` (the interface correction itself has
no metric loss or gain against its PR-plus-main baseline):

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,396 | 27,397 | 1 |
| Exact code bytes | 4,203,136 | 4,205,180 | 2,044 |
| Exact data bytes | 1,470,455 | 1,470,527 | 72 |
| Linked code bytes | 3,707,636 | 3,712,340 | 4,704 |
| Linked data bytes | 1,186,023 | 1,187,427 | 1,404 |
| Linked units | 3,585 | 3,586 | 1 |

Actual ordered linker inputs: 3,586 source objects and 1,383 fallbacks;
SHA-256 of newline-delimited paths including the final newline:
`c6c63601c08b7ddc94eaca899b4e8e24c15775bda4dfc36def38a3b266613e5b`.
