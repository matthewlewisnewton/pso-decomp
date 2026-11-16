# Scalar collision-area helper at 0x803DF840

Validated on 2026-11-13 against fork base
`34742a01fa18f1df3b4d838871297333cc8d1c76`.

## Scope and behavior

`TObjPlayer__sub_803DF840` occupies `0x803DF840..0x803DF9D0` in
`pso/player/TObjPlayer_803DF7A8.cpp`: 400 bytes of scalar floating-point code.
Its existing callers in `TObjPlayer__sub_803DF9D0` add two triangle areas to
measure a projected quadrilateral, then compare that area with four triangles
formed around a candidate point. The existing `Point2_803E0CC8` record contains
the two float coordinates those calls consume. The placeholder function name
is retained; this behavior does not establish an original name or class owner.

The function constructs a line through its first two points, measures the
third point's distance from that line, and multiplies by half the first edge's
length. When the first two horizontal coordinates differ by less than `0.025f`,
it substitutes the vertical line through the first point. That approximation
is observable for nearly vertical edges and is preserved. Coincident finite
endpoints produce zero area.

## Native floating-point boundaries

Both lengths use the existing Ginja pattern: a reciprocal-square-root estimate,
three double-precision Newton refinements with `0.5` and `3.0`, then a volatile
single-precision store and reload. The two local float homes reproduce the
original stack offsets. The function inherits this source region's existing
`fp_contract off` setting.

The line expression uses a double carrier, followed by separate absolute-value
and float-rounding assignments. The division and final product explicitly use
the rounded float value. Combining the absolute value and its float conversion
into one assignment gives the same 400-byte function but changes two register
encodings, scoring 99.9%. Keeping the separate operations reproduces the complete
function. This is a measured compiler constraint, not proof of the original
local declaration. Direct point-field expressions also matter to CodeWarrior's
common-subexpression and register allocation passes.

The shared constants remain external definitions at their existing addresses;
no data ranges, compiler flags, splits, symbols or linkage selections change.

## Validation and limits

- Objdiff reports the function at 100%, including its constant relocations.
- A separate ELF comparison confirms identical 400-byte instruction bodies
  and all ten relocation records.
- The full build reproduces the original DOL SHA-1
  `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- `python3 tools/check_pr.py` passes: one newly exact function, 400 additional
  matched code bytes, and no code, data, coverage or linkage regressions.
- The host test exercises 4,103 finite cases, including both windings,
  degenerate triangles, near-vertical edges and deterministic random inputs.
  It checks input preservation and compares against determinant-based geometry
  with the native near-vertical rule. ASan and UBSan also pass.

The host reciprocal-square-root stub uses an accurate mathematical estimate;
it does not emulate the Gekko estimate bit for bit. Native matching is the
instruction-level proof. A port can use `fabs` and `sqrt` while preserving the
threshold and float rounding boundaries, and should validate its numerical
behavior separately.

The containing unit retains other unmatched functions and remains unlinked.
This change recovers only this scalar helper.
