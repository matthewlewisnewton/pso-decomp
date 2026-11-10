# Focused GuildWarning replacement for PR #268

This draft reconstructs the validated `6daa19a11..74966a46e` GuildWarning slice
as hunks on current main `1a9c290489ea7a20edaf5f960e57bfffef5a5e14`. It does not import
old whole-file window implementations. The paired continuation is initially
stacked on this branch and retains the later window recovery and its holds.

The original PR branch is preserved at
`2b99de553e82eff0ab0bb70263c943bb68e23fb4`, tree
`e3c70688aa16f8122e0cdaf2a590f6e8e2ba8859`. Its history and conversation remain
available for provenance. The imported [GuildWarning note](guildwarning-wip.md)
is a historical record for its stated checkpoint; its old main and draft-hold
narrative are not this replacement's current validation results.

## Scope and boundaries

GuildWarning has its observed 0x34-byte image: signed-word mode at 0x1C,
timer at 0x20 and four message-window pointers at 0x24. Its constructor, instance
helpers, task, cleanup and 600-byte renderer use the shared declaration.
Project-assigned member names are not claimed as recovered original names.
The coordinate constants remain external original providers.

The shared layout lookup returns the observed two-float WindowLayoutPosition.
Only the four-argument Message factory's size input becomes const void*: the
shared declaration, definition, delegation, symbol and all existing callers
move together. Its layout-word, u8-pointer result and existing helper views
remain qualified legacy boundaries. Native Message/Addition/Base lifetime and
field-prefix changes belong to the continuation, not this focused slice.

## Current validation

The capacity-gated full build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The first qualification used the independently verified shared 78a6 report;
main advanced during the split, so final qualification rebuilds against
1a9c290489 with pinned tools and isolated outputs.
check_pr against that baseline passes: +600 matched code, +728 linked code,
one exact function and one linked unit, with unchanged data coverage and no
function, meaningful-data or linked-address loss. All linked units are
exact. Retention remains clean; port inventories pass unchanged.

All twenty-five changed source units have original-exact provided function
bytes and resolved text relocation targets. Twenty-four whole text sections
match directly. Boss2Tunnel's 49 original functions/9528 bytes and their targets
match individually; its two pre-existing non-DOL helper emissions (108 bytes)
retain the established dead-strip treatment, with no new exclusion or control.
The original constants, table providers and compiler configuration are retained.

Independent review verifies that the source patch is exactly the historical
31-file hunk set on current main, including all required callers. No table,
padding, data range, retention override or new compiler control is introduced.

## Attribution and draft status

This is reconstructed work by Matthew Lewis Newton, with the original Cursor
and DeepSeek V4.1 Flash 1017 contributor trailers retained. Representative
historical sources include `47214ee8f8`, `a3cac5ea22`, `6e5e6f1e27`,
`578026aa58` and `305840ba0f`. The continuation archives the complete branch-only
commit messages, authors and co-author trailers; the original branch remains
the canonical full history, including superseded attempts.

Both replacements stay draft. Exact recovery of this slice does not waive
Message/Base/Addition boundary concerns, the continuation's source-quality
holds, or any original-provider limitation. Neither PR is approved or merged
by this reconstruction.
