# Legacy Zako clear-wrapper contract

This narrow interface repair keeps the existing C-linkage symbol
`TBoss4DarkFalz__sub_8030AD38` and its original provider unit. It gives the
wrapper one shared `void(void)` declaration and calls the existing canonical
`TBoss4DarkFalz::clear_uro_link_state()` static method instead of redeclaring
its mangled symbol as `int(void *)`.

The wrapper's sole caller already passes no argument and ignores its result.
Its cleanup body is unchanged. The underlying clearer and all buffer/storage,
shadow/material, texture and compiler-profile code are unchanged.

## Original reference and dataflow evidence

The inspected source base is d6fc686573510cc9612beb6a2d71576ad685301c.
Its native inputs differ from the independently built cb862cd99ef707159a73e33c302fdf753cdee5e1
baseline only in README.md. The complete inventory of 4,943 original ELF objects,
including named/section-relative/absolute relocation targets, and an independent
original-DOL direct/conditional branch and aligned data-pointer scan agree:

- Wrapper 0x8030AD38..0x8030AD57: one 32-byte provider, one REL24+0 caller at
  0x8004C0AC in `TBoss4DarkFalz::cleanup_global`, and no external interior-entry
  or data-pointer reference.
- Clearer 0x8030AD08..0x8030AD37: one 48-byte provider, two REL24+0 calls at
  0x8030AD44 and 0x8030ADA8, and no external interior-entry or data-pointer
  reference. The second call is the already-typed resource initializer.
- The wrapper saves/restores its frame and calls the clearer. It adds no input
  or result processing. The clearer overwrites incoming r3 and initializes all
  other working registers before use; it consumes no incoming argument.
- The clearer zeros two count words, 0x784 bytes apart, and the buffer index.
  It incidentally leaves a loop offset in r3. No caller consumes that value.
  In cleanup, the next instruction loads the resource pointer into r3 before
  deleting it. An incidental register value is not a status-return contract.

This supports a no-input/no-result source interface for the complete observed
call closure. It does not prove the historical prototype or exclude arbitrary
runtime-generated calls. The raw symbol is intentionally not renamed into a
new guessed class operation.

## Scope and preserved behavior

Only the wrapper header/provider and its cleanup caller's declaration change.
The provider uses the existing class header; no class layout or member
signature changes. Cleanup order stays: free global instance, invoke this
wrapper, delete the BML resource, then clear the resource global. The clear
body still writes only the two counts and index, leaving entry bytes, rotation
phase and the borrowed texture cache alone.

This lead came from the remaining PR #303 buffer assessment. It is not typed
buffer recovery or completion of the full fold. The opaque buffer definition,
its distinct aggregate views and queue-producer vector types still need a
coherent source/subobject repair. The held material-helper transaction and
compiler-profile migration are not revisited. Both affected provider units
already link from source, so no new matching/linking gain is claimed.

## Original-free characterization

Run `python3 -m unittest tools.tests.test_zako_clear_wrapper -v`.
Set `PSO_TEST_SANITIZERS=1` for fatal AddressSanitizer/UBSan checks.

The test compiles the literal checked-in wrapper and unchanged cleanup bodies
with the real wrapper header and a second fixture caller translation unit.
A compile-time check verifies `void (*)()`. It checks one clear call, 10,000
repeated calls, and cleanup ordering/resource reset with nonnull and null
resource fixtures. Fixture methods and the destructor record calls only; they
do not model enemy/resource layouts, buffer writes or native register state.
A separate 32-bit syntax/type check can include both real wrapper and class
headers without claiming broader host layout portability.

Native acceptance requires full object sections/symbols/relocations, exact DOL
and linked ELF, affected dependency closure and provider/retention/address-based
no-loss validation against an authenticated baseline. Source signature checks
and host fixtures alone are not evidence of native matching.
