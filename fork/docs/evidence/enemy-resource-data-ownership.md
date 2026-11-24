# Enemy resource data ownership

Base: fork main `8aaabc087559d217358101920f7cefae081ad884` with GC/2.0.
Three related enemy units recover 64 data bytes using their existing resource
lifetimes and consumers. No function bodies are rewritten to force a match.

| Owner | Range | Gain |
|---|---|---:|
| TObjEneMe1Canadin | `.sbss 0x805D4FD0–0x805D4FE0` | 16 |
| TObjEneMoja | `.sbss 0x805D50C8–0x805D50E0` | 24 |
| TObjEneDellBiterEffects | `.sdata2 0x805DEFA0–0x805DEFB8` | 24 |

Canadin extends its already-owned following small-BSS range with the resource
pointer, render-node index, existing signed address-word cursor and leader-breakup
pointer, in original order. All 32 original references belong to the owner.
The cursor retains its existing native address representation: it advances
through vector history in 12-byte steps. No speculative pointee or class field
is introduced. Four exact four-byte symbols fill the added range without padding.

Moja owns six pointers allocated/populated and deleted/cleared by its resource
lifecycle: base-stat, attack, resistance and movement tables, the BML resource,
and sampled motion points. All 49 original references are accounted for: 38 in
the owner, six in the neighboring Moja behavior unit, two in `bindModel`, and
three in the NPC constructor. All direct global stores are in the owner.
The shared `MojaResourceState.h` gives every consumer the same C-linkage types.
The existing canonical BML model/motion fields replace partial duplicate views
at the same verified offsets. The selected-attack `m_318` field keeps its legacy
address-word boundary with an explicit pointer conversion; no class/API layout
or allocation/free behavior changes.

DellBiter's six private finite floats are 5, 16, 2.5, 0, 0.02 and 0.8, in original
order. An identical duplicate zero declaration was the prior discovery filter's
obstacle, not a conflicting type. Ten original references belong solely to this
unit. Ordinary `static const` definitions reproduce the complete pool and code.
A fresh scan of all 5,061 original objects and 3,620 compiled consumers finds no
external references. After exact compilation, the supported missing-only
`localize_split_globals.py` marks precisely these six labels local. Addresses,
extents and bytes are unchanged; no cross-unit name is hidden.

## Validation

Native head `fa582047c429252c7eceee181f5a921e872789bd` reproduces original
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Full PR, actual source-link,
retention, both exception inventories and strict original-address no-loss checks
including padding pass. Matched data increases 1,505,752 → 1,505,816;
source-linked data increases 1,503,856 → 1,503,920. All 3,614 linked units remain
exact. Function/code counts and coverage denominators are unchanged.
Retention adds six resource names and removes none.

Across the six affected source objects, all 44,428 code bytes and 2,530 runtime
relocation sites/targets remain identical at original addresses and match the
original objects. Allocated sections and alignment match, including existing
zero alignment tails. All 3,614 other compiled source objects are byte-identical
to fresh main. Shared global types and ownership were also reviewed separately
from the native match; that review does not claim every legacy actor interface
has been recovered.

The scan considered 1,545 unowned named BSS/SBSS objects up to 64 bytes; this is
discovery coverage, not proof that all remaining candidates are difficult.
Known DHCP/player/character-selection section-order cycles, larger opaque tables
and active overlapping work remain deferred. No new compiler exception, source
padding, handwritten vtable or asset payload is introduced here.
