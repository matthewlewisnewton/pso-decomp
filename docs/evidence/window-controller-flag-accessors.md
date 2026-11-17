# Window-controller flag unit

This source recovery starts at fork main `2344b179717a97c9604db931189ad6d7dc6a9cc8`.
The complete unit `TWindowCtrl_8024C6CC.cpp` already matches and links: 20 functions,
340 code bytes, no owned data. This change claims no new matching or linking gain.

The original halfword loads/stores at `0x8024C6CC..0x8024C7C4` and bit tests at
`0x8024C7D4..0x8024C810` address the existing `TWindowCtrl::m_1c`. The predicate at
`0x8024C7C4` reads the existing word at `m_3c`; its direct caller in
`update_target_info_window` passes the controller receiver and compares the full
return register with zero. The two final signed-halfword getters address the
inherited `TWindowBase::m_20`. Offset assertions protect those shared fields.
The address placeholders remain because these observations do not recover the
original method names. C linkage preserves the current exported names.

## Compiler checks

The actual GC 2.0 compiler and unit flags distinguish these equivalent forms:

- Clearing with a 16-bit positive mask emits `andi.`. A full-width complement,
  such as `~0x40`, retains the original `rlwinm`. Existing halfword flag setters in
  `TWindowSubTradeMain_80268468.cpp` and `TWindowSubTechnique.cpp` use the same
  full-width mask convention.
- A shared `bool` predicate declaration changes the caller's integer comparison
  into a byte test. Changing only the definition to return `s32` moves the extra
  byte mask into the provider. Disposable C and C++ probes with otherwise identical
  `return field != 0` bodies confirm that GC 2.0 emits the original four instructions
  for C, but an additional byte mask for C++.
- Returning the integer conditional `field != 0 ? 1 : 0` retains both the original
  provider and caller instructions with one shared `s32` declaration. The same
  caller-width issue is documented in [the main-phase predicate](main-phase-predicate-evidence.md)
  and [the Needle contact interface](kenkyuw-dispatcher-continuation.md).

Both affected objects retain their complete allocated section bytes, alignment,
exported symbol positions/sizes, and symbolic relocations (2 in the provider and
91 in the caller). The full native DOL hash, address-based no-loss check, linked-unit
check, and retention check pass. No class layout, split, compiler flag or linkset
change is needed.
