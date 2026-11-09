# Correcting the task formerly attributed to DuelResult

This follows validated PR #268 checkpoint
`307a9e062f97b845a8f826a4c58440c7bc5445b8`, including main
`9924ce113b5e6dff309a5ae94065265d3066fb24`.

The function at `0x801C2528`, previously assigned to
`TWindowDuelResult::init`, constructs the existing address-named
`TUnk_804C3E60`. Its sole constructor caller allocates `0x24` bytes. Table
`0x804C3E60` dispatches to this task's destructor and `run_task`, with inherited
TObject rendering slots. DuelResult has a `0x6C` image and a different table
at `0x804CF020`.

The native constructor takes `(TObject *parent, s32 gain, s32 duration)` and
initializes TObject directly. Its fields are a signed countdown at `0x1C`
and signed gain offset at `0x20`; size and offset assertions cover them.
The native destructor clears the current-instance pointer, then automatically
destroys TObject. The compiler owns the 24-byte table, newly claimed to the
destructor's existing `text_801C23A8` source unit.

Both factory callers play a cue stream before requesting gain `-50` for a
duration. The task decrements the duration, scales the gain during the final
15 ticks, and resets the gain to zero before queuing destruction.
`TLobby::set_and_notify` writes the stream-gain setting and updates music
stream gain. This is not a DuelResult window lifetime. There is no class-name
string/store supporting a semantic class name, so the existing address-based
name is retained. The misleading factory/global project names become
`fn_801C23A8` and `lbl_805D5D90`; both callers share one typed declaration.
The historical source filename is retained and does not assert ownership.

The global is an external pointer declaration, with no source definition or
new `.sbss` claim. Its existing eight-byte catalog entry is preserved: the
observed pointer occupies the first word; the second word is not recovered
or silently consumed. The character-selection reset still clears only the
observed pointer. The already matching task update body is preserved.

An additional audit at checkpoint `6af091722` scanned 4,982 original split
ELFs. Five direct relocations target this symbol: four in the task unit and
one in the character-selection reset. All are SDA21 references with addend
zero; none targets the second word at `0x805D5D94`. The containing `.sbss`
section is NOBITS, so that word is initially zero by BSS semantics, not a
stored original word. Its eight-byte symbol size and `.skip 8` are generated
from catalog metadata and do not independently prove an eight-byte source type.
The next pointer starts at `0x805D5D98`; four-byte pointer alignment does not
require the intervening word. Unknown original section boundaries or computed
accesses remain possible. These findings do not prove padding or a second
pointer, so the range and unclaimed word are preserved.

Complete unrelocated text is identical for both relevant units:

| Source unit | Original and recovered bytes |
| --- | ---: |
| `text_801C23A8` | 384 |
| `TWindowDuelResult_801C2528` | 140 |

The complete linked build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Address-based comparison
against `307a9e062` preserves all 27,369 exact functions and 3,575 exact
linked units, with no code or data regression. Matched and linked data
increase by 24 bytes. Retention is clean at 17,583 names.

The follow-up also replaces the Deposit, two DuelResult, and SubMagPhoton
raw constructor calls with ordinary `new`. Deposit's factory stores the
typed construction result directly; retaining a temporary introduces an
extra move under its existing optimization settings. No flag or pragma is
changed to accommodate it. All four factories preserve complete original
instruction bytes. Their constructor bindings, plus the unused information
window binding, leave `WindowConstructorAbi.h`; it now has five constructor
and three destructor declarations. Factories include class interfaces
directly, and eleven unused ABI includes are removed.

The specific DuelResult ownership anomaly is resolved. The standing draft
hold remains for the remaining raw-storage lifetime boundary and historical
interface holds. The ABI interface still transports Base, Addition, Message,
and MenuIconLine entry points; this does not claim that their remaining raw
callers have portable C++ lifetime semantics.
