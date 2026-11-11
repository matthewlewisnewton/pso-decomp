# GuildWarning recovery on current main

PR #268 remains relevant: main `6daa19a11db97b1b8222fd2665eba485ed3a74a4`
still lacks the 600-byte renderer at `0x80211774`. The previous PR head is
`3004a1a51343272ec7f2cf388d4959e7ca2ae08a`.

## Integration scope

The normal merge retains main's newer `TWindowBase` / `TWindowAddition`
hierarchy, `TWindowMessage::create` and `TWindowMessage::append_line` ownership,
and typed quest VM. The old PR's broad TLobby window-interface retypes conflict
with that work and are superseded by main for this recovery. Their original
commits remain in this branch's history. The existing unpushed continuation
`sol61-pr268` at `2fe55e2e0`, including its dirty follow-up files, is preserved
in its original worktree and is not included here.

The retained recovery covers GuildWarning's fields, constructor, instance
helpers, lifetime methods and renderer. It calls the current window members
directly. The layout lookup and its defining unit share
`WindowLayoutPosition *get_window_layout_position(s32)` from one header;
the two-float layout is the same as main's previous local type.

The actual four-argument message factory's size input is now `const void *`.
Its body passes that address to the helper that copies two floats into the
message-window settings. Keeping it as an integer made MWCC hoist an extra
address conversion in the renderer loop, consuming another register and
growing its stack frame. The header, definition, real member callers and
project-assigned symbol change together to
`create__14TWindowMessageFlPCvUll`. Main's existing C-named local declarations
are retargeted to that symbol; their other legacy types are unchanged.
The three-argument overload keeps its existing interface and converts the
size word at the delegation boundary.

The factory still accepts the layout as a word and returns `u8 *`. Those
two existing boundaries require an explicit layout conversion and return
pointer conversion here. This recovery does not assign window operations
back to TLobby or assert a new constructor contract to remove them. The
factory's existing function-pointer view of its size-copy helper is unchanged;
this is not a claim that all its interfaces are unified.

The mode is an `s32`, stored at `0x1C`; the timer is at `0x20`; the four message
windows begin at `0x24`; the whole GuildWarning object is `0x34` bytes. Compile
time size/offset checks record these facts. The renderer's two `sub_` member
names and the constructor's mode parameter retarget project-assigned symbols;
they are not recovered original C++ names. The split-owned coordinate constants
remain external references, rather than newly defined game data.

## Validation

The baseline was freshly built from main `6daa19a11` with pinned tools and
local original inputs in an isolated checkout. It has 27,364 exact functions
and 3,570 linked units. Its DOL SHA-1 and linked-unit check pass, and its
retention check has zero additions or removals.

The integration build (`ninja -j2`) reproduces the original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The full
`tools/check_pr.py --no-build` comparison against that fresh main report passes:

- Exact functions: 27,364 → 27,365; one new exact renderer, zero regressions.
- Matched code: 4,180,388 → 4,180,988 bytes (+600).
- Linked code: 3,636,556 → 3,637,284 bytes (+728).
- Linked units: 3,570 → 3,571; all linked units exact.
- Matched and linked data unchanged; four project-assigned function renames.
- Retention metadata unchanged: zero additions or removals.
- `tools/list_port_exceptions.py --check` passes; no new exception.

Every function in the 728-byte renderer unit is exact, as are the existing
GuildWarning helpers, constructor and destructor. The layout lookup unit
remains exact. Address-based no-loss validation also covers the factory and
all its changed callers.

Candidate build outputs are private; unchanged compiler outputs were copied only from this
fresh local main baseline, and split objects are regenerated from the
candidate's checked-in symbol/configuration inputs before validation. Every
changed source unit is explicitly recompiled; copied object timestamps are
not used as evidence for changed code.

## Draft hold

The standing instruction in this PR is **do not merge or mark ready** until
the window construction/lifetime contracts are resolved. It remains in force.
Main's C-named `TWindowMessage__ct` and `construct_with_parent` are unchanged;
the earlier attempts to force them into real C++ constructors emitted extra
base calls/vtable stores. Those previous measurements do not prove that no
future solution exists, and this pass does not retry or resolve them.

Current-main integration and exact code matching alone do not lift that hold.
The earlier wider window-interface cleanup is not claimed complete.
