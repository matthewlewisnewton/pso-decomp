# ChallengeResult scale/entry recovery and native lifetime blocker

This follows PR #268 checkpoint
`9803cb70ecb0c7f9c3ead8285846ddd6b2ecbe28`, including current main
`224eb99838471c243b20c305eddac75e7ff76c8f`. This is validated intermediate
interface progress. It does not activate the native ChallengeResult lifetime
or replace its existing manual table.

## Published source-correct changes

The original constructor writes two floats at window offsets 0x60/0x64, and
render supplies their address to the draw-context setup. The class's opaque
eight-byte tail becomes f32 scale_x/scale_y, with explicit offset assertions
and the existing size assertion of 0x68. Render uses those actual fields and
inherited Base operations. No class image or instruction changes.

After filling the death-count entry's word at 0x20, the constructor now passes
that actual entry explicitly to the shared draw_right_aligned_number(void*)
declaration. The former no-argument local prototype depended on the entry
pointer remaining live in r3. The shared helper reads that word and updates
entry dimensions. This corrects the argument boundary without asserting a
complete widget class or changing the helper's other callers.

The raw constructor/destructor/task and manual table remain in their existing
form, with the original symbol catalog unchanged. These holds are not lifted.
Existing string pooling and the capped-time explicit rodata placement remain;
no compiler control, wrapper, alternate symbol or extra operation is added.

## Bounded native probe: measured limitations

Original reference inspection supports a native `(void *teamName, s32
clearSeconds, s32 deaths)` constructor and empty automatic Base cleanup.
There is one original direct constructor caller in Ending's new(0x68) path,
no observed address-taken constructor reference and no descendant. The task
slot supports a real run_task override; the four table slots are destructor,
task, render and TObject shadow.

A native probe compiled with a compiler-owned table in its correct location.
The complete 232-byte data section matched, including the existing entry,
descriptor and string arrays. Native task/destructor and explicit number
forwarding were also supported. Activation is held by two measured code
mismatches:

- The native constructor is 452 bytes versus the original 448. Original
  descriptor, string-table and vtable addresses share a pooled data base;
  the native form materializes separate addresses. This is a four-byte
  complete-constructor mismatch, not evidence that native recovery is
  impossible or that the original table could not be compiler-owned.
- The complete 148-byte Ending producer has two register-allocation
  differences in its earlier layout-result comparison: r29 versus original
  r30 at offsets 0x30/0x38. Allocation/argument call order and the remaining
  producer instructions match. The complete unit stays the same size.

Three ordinary source organizations were checked without new controls:
typed versus existing descriptor representation, C++ method definitions
outside the legacy extern-C block, and pointer/word result locals matching
the existing result boundary. They did not remove those differences. The
unmatched native probe is excluded from the published tree. A future attempt
needs a new evidence-backed source lead; no steering control or speculative
ownership change is justified by these measurements.

## Upstream return boundaries stay held

The producer's existing local word-return view of
get_card_window_value__16TObjOnlineEndingFv differs from the actual shared
s16 declaration. The callee returns a sign-extended word on every observed
path: constant 999 or a signed halfword load from save data. That explains
the word consumed by the current constructor, but does not recover a single
portable shared return contract. Main's s16 type is unchanged.

The producer also retains its existing team-name word transport. The name
getter's pointer declaration and other affected callers have not been
coordinated. The published producer is restored unchanged; this intermediate
work does not claim either upstream boundary is fully recovered.

## Validation and standing holds

Complete original/compiled unrelocated text is identical in the two changed
source units and restored producer, each actual source link input once:

| Unit | Bytes |
| --- | ---: |
| TWindowChallengeResult | 592 |
| text_80246CE8 | 84 |
| TObjOnlineEnding_802E4B80 | 1,836 |

ChallengeResult's complete 232-byte data is unchanged. Full build reproduces
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr
passes with no change to any function, code, data, linked-unit or coverage
metric: 27,387 exact functions and 3,588 exact linked units retained.
Retention is clean at 17,747 names, and the porting inventory passes.

Relative to fresh main 224eb9983, the combined PR retains +600 matched code,
+1,220 linked code and +912 matched/linked data bytes. The eleven previously
qualified alignment gaps are unchanged. The raw Base/Addition boundary stays
at 52 calls across 26 source units.

Protected original Help/SoundBalance data suffixes of 204/532 bytes and the
1,044-byte text remainder [8026E1D4,8026E5E8) remain original inputs exactly
once, with unchanged unrelocated and resolved bytes. ChoiceSetting's unknown
0x7C producer, task-global word 805D5D94, Snapshot separation, ChallengeResult
native activation and broader ownership/interface holds remain unresolved.
The PR stays draft and must not be marked ready or merged.
