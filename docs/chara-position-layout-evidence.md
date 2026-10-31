# Actor position layout guards

This change restores the compile-time layout protection omitted when the older
actor position views were reconciled with the current source. Its base is
`1e647e141ad4aab06ced441e829cbe1f182ffc80`, verified as the personal fork's `main`
after the default branch rename.

## Historical scope

Fork PR #12 (`f6e90177c775d81b03648d84649332574c6836c5`) added two anonymous
unions exposing `position_290` and `position_29c` alongside six existing split
fields, plus size and offset assertions. It contained no runtime function
changes. The same declarations were included in PR #11
(`d5970ad25d8f42dc1bea060e14843cbaf7a282a9`) and PR #53
(`de33150b1d185b80662326b472032a0a6855d644`). The BalClaw and Merill recovery
was separately reconciled into the merged integration stack; these declarations
were the remaining shared-layout hold.

## Current behavior and decision

`TObjChara::initialize_position_copies` in `TObjPlayer_80092A7C.cpp` still copies
the current position to the 12-byte regions beginning at `m_29c` and `m_290`,
then to the previous position. The BalClaw body constructor uses the same two
copies. Merill initialization calls that shared method; its idle logic copies
the home position to `m_29c` and the body center to `m_290`. Player movement and
enemy call sites continue to use the same regions for vector copies and
positional calculations. The following `target` pointer begins at `0x2A8`,
outside both regions.

The inspection found no runtime behavior uniquely supplied by the omitted
union aliases. They provided declaration-level vector views and removed some
casts. The current representation retains the observed operations through
existing accesses. This is a bounded supersession decision, not a claim that
the legacy casts are portable C++ or that all field semantics are recovered.
Changing their types or aliasing model would require a separate migration.

The patch leaves all storage and function bodies intact. It restores assertions
for the `0x334` class size, all six split-field offsets, and `target` at `0x2A8`,
using the header's existing typedef convention. Existing body-center and
velocity size/offset guards remain. Anonymous unions, compiler-extension
pragmas, and assertions for aliases that no longer exist are not reinstated.

## Integration condition

The assertion patch requires independent review before adoption. Historical
PRs #11, #12 and #53 remain open until this protection is merged and their
live heads are checked against the reviewed historical heads above. Closure
should describe the vector aliases as superseded representation, not claim
their exact declarations were preserved. This narrow patch does not replace
the prior family-specific semantic reviews.


## Validation

Baseline and candidate full builds passed with `ninja -j2` while holding
`/tmp/pso-decomp-full-build.lock`. Natural build times were 89.467 s and
50.041 s, respectively; lock waits were 0.000037 s and 0.000032 s. The initial
sandboxed compiler-wrapper attempt failed before verification; the successful
builds used the existing compiler wrapper outside that sandbox.

`tools/check_pr.py --no-build` passed against the saved baseline report:
27,241 exact functions, 4,114,032 exact code bytes, 1,287,955 exact data bytes,
3,329,452 linked code bytes, and 938,711 linked data bytes are unchanged.
All 3,537 source-linked units remain exact; no address coverage was lost.

Comparison of all 8,850 captured source/fallback ELF objects found no changes
to allocated sections, normalized relocations, or allocated symbols. The 5,067
link inputs and their order are unchanged (3,537 source, 1,530 fallback).
The final DOL retains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Whitespace validation passed. This assertion-only change adds no matching or
link-coverage gain.
