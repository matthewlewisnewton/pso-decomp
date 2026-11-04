# TChCrTagInformationStr recovery

This source checkpoint recovers the native class and its actual factory and
parent/selection call boundary. It remains unlinked while the directly reached
localization getter's storage contract is unresolved.

The target GC/2.6 profile produces all 1,164 original code bytes, the 24-byte
vtable and the 16-byte literal range at 0x804755F0..0x80475600. All 47 allocated
relocation positions and types agree, with the factory/constructor signatures
and two compiler-local literal targets mapped to their original addresses.
The literal range belongs to this unit: the original split-object reference
census finds its references only in this unit and its former data definition.
The 315/280 position pair is one 8-byte aggregate literal at 0x804755F0; the
render copy reads it as a single 8-byte block, so the former 4-byte split at
0x804755F4 had no separate object behind it. A full configured build produces
the original DOL SHA-1, and `tools/check_pr.py` reports the recovered function
and literal range with no regressions. Regenerated native link inputs remain a
gate.

The angle increment computes `0x10000 / (ring * 4)` at its sole use. CodeWarrior
hoists this invariant and reproduces the original register allocation. Moving
it into a separately assigned local changes three register choices. The ring
values 1..4 preserve the original positive divisors and integer truncation,
including the twelve-way ring. The indefinitely incremented frame counter is
unsigned so its wrap has defined modulo-32 semantics; this preserves all bytes.

The known factory accepts selections 0..14. Each renders seven entries from
group 0x11 or 0x12. The five bundled language archives contain 21 and 84 entries
in those groups, respectively. Every reachable character span terminates inside
its buffer and is disjoint from relocation slots. The recovered object retains
no text pointer in a member. Those facts do not establish table-object lifetimes
or qualify arbitrary replacement archives.

The current localization implementation reads group and entry words through
integer lvalues without an established scalar-storage lifetime, and several
legacy return/global declarations disagree. This is a real activation
prerequisite. A conditional scalar getter reproduces all 24 original bytes,
but the tested byte-copy/explicit-construction producer and metadata/keyboard
views remain inexact. No pointer-return migration, whole-buffer word overlay,
source-correctness waiver or inexact provider is included in this checkpoint.
