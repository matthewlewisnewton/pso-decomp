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

## Remaining inherited debt

This change preserves the already-exact resource/rendering code, including its
hand-written vtable and constructor/destructor wrappers, provisional raw views,
function-pointer casts and 32-bit resource handles. These are pre-existing
matching shortcuts newly selected from source, not newly recovered class or
vtable evidence. A port should use normal class lifetime/virtual dispatch and
consistent typed resource/render interfaces. The new update itself uses typed
fields and shared helper interfaces. No assembly, intrinsic or hardware access
is introduced. The mechanical inventory remains 5,772 pragmas in 876 files;
configured overrides increase from 176 to 177. Section 5 records this scope;
section 7's historical import inventory remains unchanged.

## Validation

Current-main build, baseline and retention passed before editing. Full build
and `tools/check_pr.py` pass with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; no exact function, code/data address,
linked range or padding is lost. All nine functions (4,704 bytes) and all 1,404
data bytes are exact. Retention adds 45 names and removes none.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,386 | 27,387 | 1 |
| Exact code bytes | 4,189,632 | 4,191,676 | 2,044 |
| Exact data bytes | 1,470,159 | 1,470,231 | 72 |
| Linked code bytes | 3,673,564 | 3,678,268 | 4,704 |
| Linked data bytes | 1,179,243 | 1,180,647 | 1,404 |
| Linked units | 3,586 | 3,587 | 1 |

Actual ordered linker inputs: 3,587 source objects and 1,387 fallbacks;
SHA-256 `79ecb4ded139711b86bbe548670f2c6e3cf888f79bbe8ef6f8aba45ff8512bdc`.
