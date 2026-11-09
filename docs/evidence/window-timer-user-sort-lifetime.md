# Native Timer and UserSort window lifetimes

This follows PR #268 checkpoint
`bea88ffa0d2f44a37eab86103b320e9035deddd3`, including main
`fe6cdb14138b2413778c08f21fd1851170c22ab5`. This bounded recovery covers
TWindowTimer and TWindowUserSort. It does not resolve the historically
Timer-attributed gogo-ball functions or the broader entry/position interfaces.

## Construction, cleanup and allocation producers

Both classes have size 0x64: the 0x60-byte Base prefix and one owned word
at 0x60. Existing sizes and new field-offset assertions check that layout.
Their original destructors install the derived table, clean up Base and
conditionally release the object. Neither has own child cleanup, and no
native descendant was found. Native empty destructors now express automatic
Base cleanup and compiler deletion behavior.

Timer has a genuine no-argument constructor. It initializes Base with the
existing layout descriptor, client 4 and get_zero_vec2(), sets its name and
flag word, updates its position selection and saves position. It does not
invoke an invented default Base constructor. Both static factories use
ordinary new TWindowTimer, then retain their respective post-construction
layout initializer. The original unconditional initializer calls, including
the existing allocation-failure behavior, are preserved. The two callers in
TWindowCtrl retain the existing word-valued factory result and handle fields.

The layout initializer definitions and Timer callers now share declarations
accepting TWindowTimer *. Their original flag accesses become m_60 instead
of unrelated duplicate prefix structs; no extra construction argument is
invented. The entry-prefix float views and easing helper remain qualified
legacy interfaces, rather than claims of complete entry ownership.

UserSort has a position/value constructor. Its sole allocation producer is
the SubComCard task's state 0x1F: allocate 0x64, pass layout position 0x8A
and the selected-record word, and store the result in handle 0x78. That site
now uses new TWindowUserSort. The constructor explicitly initializes Base
with client 4, sets the name and owned value word, then invokes the existing
card-text entry helper on the prefix at this+0x24. That helper's historical
SubStatusDisp attribution remains held: this change does not claim that a
complete SubStatusDisp object lives there. The selected-record and outer
handle boundaries retain their existing word transport.

## Native render/task methods and helper contract

Both render methods use the shared TWindowDD::draw_default_entry declaration
with an explicit receiver word, replacing a no-argument declaration that
depended on the incoming register. Timer's task is a native method; UserSort's
existing native task remains. Neither adds virtual slots.

The original Timer tab helper at 80287DD8 has exactly one observed reference:
a zero-addend REL24 from Timer render. The caller passes the Timer receiver
in r3 and draw context in r4; the helper uses only the context. The recovery
uses ordinary void TWindowTimer::draw_tab(s32 context). Its declaration,
definition, call and catalog agree with the actual compiler-emitted
`draw_tab__12TWindowTimerFl`; the old two-word static mangle is removed,
without an alias. This reconstructs the sole observed receiver/context
contract, rather than uniquely proving the original source declaration.

## Compiler tables and verification

The native key functions emit exactly the existing four-function tables:

| Owner | Source claim | Bytes |
| --- | --- | ---: |
| Timer | [804D2E88,804D2EA0) | 24 |
| UserSort | [804D3060,804D3078) | 24 |

Both starts are naturally eight-byte aligned. Only the tables are newly
claimed; the adjacent 20-byte descriptors and their entry arrays remain
original inputs. Original and compiled unrelocated table data are identical,
and the full link verifies their targets. No manual table, extra virtual,
alignment override, padding definition or compiler control is added.

Complete original/compiled unrelocated text is identical in all six affected
or header-dependent units, each selected as actual source link input once:

| Unit | Bytes |
| --- | ---: |
| TWindowTimer | 1,048 |
| TWindowUserSort | 648 |
| text_80287AD8 | 320 |
| TWindowSubComCard_80271E7C | 13,404 |
| TWindowCtrl_8024A1A8 | 2,356 |
| TObjSinBoard | 10,020 |

The complete DOL reproduces SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes
with all 27,384 exact functions and 3,586 exact linked units retained, no
function/code/data/coverage regression and 48 additional matched/linked data
bytes. Retention is clean at 17,692 names (+10, -2 stale); the porting
inventory passes. Against fresh main fe6cdb141, the combined PR retains
+600 matched code, +1,220 linked code and +688 matched/linked data bytes.
The existing nine qualified four-byte gaps remain the only coverage loss.

## Remaining holds

Two Base construction/cleanup pairs leave the raw interface, reducing it to
62 calls across 32 source units: 27 Base pairs and four Addition pairs. The
two constructor and two destructor bindings remain. No remaining caller is
silently treated as recovered.

The original 1,044-byte remainder at [8026E1D4,8026E5E8) remains original
link input exactly once. Its unrelocated bytes still equal the original
suffix and its resolved DOL range is unchanged. ChoiceSetting's unknown
0x7C producer, task-global word 805D5D94 and wider legacy-interface holds
remain unresolved. The PR stays draft and must not be marked ready or merged.
