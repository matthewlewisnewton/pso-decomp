# ComCard construction and entry receivers

This follows PR #268 checkpoint `a3611ebc3cfba377927ef8495e0607aca39c508f`.
The basic 0x60-byte ComCard now has a genuine Base-initializing constructor and
three ordinary-new producers. The distinct 0x74-byte follower retains its raw
constructor and both producer paths. Neither deleting wrapper nor the existing
table providers are replaced in this checkpoint.

## Basic window construction

The native constructor takes position and a word-valued display record. It
initializes Base with the existing descriptor and client 4, assigns the name
pointer, and updates the entry list through field 0x24. All 104 bytes and resolved
relocations match the original. The three references are the local factories;
there is no descendant constructor reference to this export.

The indexed-record factory preserves its negative-index return and computes
records + index * 0x90 before allocation. The other factories preserve the missing
entry/keyboard checks and keyboard initialization. Ordinary new retains the
original allocation-null paths. All three producers match in the complete owner
text; no allocation or setup is reordered to force a match.

## Entry helper and follower ownership

The historical set_help_mode export receives an entry flags/kind/UV prefix, not
a complete ComCard window. ComCardEntryAbi.h gives the same C export an explicit
storage receiver without fabricating a complete entry class. Its 120-byte body
still accesses halfword flags at 0, the word at 0x34 and the same UV helper. All
three calls, including LockOn's entry-list call, preserve their targets.

The selection setter accesses offset 0x70, outside the basic window's 0x60-byte
extent. Its two callers are SimpleStatus's 0x74-byte follower paths. The existing
TUnk_804CE964 declaration is therefore its actual owner; the 72-byte method and
both callers are exact after the symbol rename. The follower's borrowed parent
is at 0x60, copied float offsets at 0x64/0x68 and word column/value at 0x6C/0x70.
The original constructor reads the parent's position at 0x40/0x44. This field
evidence does not establish native construction or ownership of that parent.

The follower's 244-byte C constructor and its two allocation paths remain
unchanged. A native initializer probe emitted 248 bytes: conversion-bias
materialization/order differed after automatic vptr initialization. Using the
observed two-float offset view and ordinary member initializers did not resolve
it. Those probes are not activated. Further recovery needs source evidence for
the conversion/constant expression and its ownership, rather than another
scheduling variant. The original deleting wrappers, their raw Base cleanup, and
all existing manual tables remain qualified. No competing compiler table is
emitted. SimpleStatus's five-child construction/four-child cleanup asymmetry is
also untouched.

## Validation and limits

Implementation commit `6f8c1191a74c1e6ef0183d22683730d88704e83b` is integrated
with fork main `4e784e247d991f1fb25766fc80923242a9ba469a` by merge
`abfb36d18690cb184e894eefe1b05b8b2fba331d`. Both isolated builds reproduce DOL
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

ComCard's complete 1844-byte text, SimpleStatus caller's 3640-byte text and
LockOn caller's 3556-byte text match original objects and captured a361 source
objects. Every resolved text relocation agrees. All source data/constants and
their relocations are unchanged; ComCard's existing 424 data bytes and 8-byte
conversion pool also match the original. Each of the three source objects is
selected once in the actual executable inputs, with its original counterpart
absent. There is no new data claim, gap, padding or compiler control. Previous
Palette, composer, Balloon and protected-original provenance checks also pass,
including the original 1044-byte setup helper.

Before the main update this family has zero report metric delta. After integration,
check_pr passes against both a361 and freshly built main: 27,395 exact functions,
3,589 exact linked units and 3,653 source-bearing units. Main contributes 2008
newly linked code bytes, 248 linked data bytes and one linked unit; none is
attributed to ComCard. Combined PR deltas versus fresh main remain +600 matched
code, +1220 linked code, +1472 matched data and +1428 linked data bytes. No exact
function, meaningful data or linked-address regression is introduced. Fourteen
previously qualified four-byte alignment ranges remain unchanged. Retention is
clean at 17,852 entries; the port inventory passes unchanged.

Only the basic raw constructor boundary is removed: 25 Base/Addition calls
remain across 13 source units, with the same four shared bindings. Follower,
Palette/Balloon destruction/table integration, ScrollBar, Parts, ChoiceSetting,
task-global and wider interface/ownership holds remain. PR stays draft.

The subsequent [bounded blocker audit](window-status-page-com-card-blocker-audit.md)
finds exact basic native cleanup and a coherent data partition, but the original
trailing word's ownership prevents a regression-free activation. The probe is
private and this checkpoint's complete source/data provider remains restored.

The subsequent [native render-body recovery](window-com-card-render-member.md)
uses the established draw-context receiver contract and actual Base members.
Its entire compiled object is byte-identical. The manual table, deleting wrapper,
unknown word and follower boundaries remain held and unchanged.
