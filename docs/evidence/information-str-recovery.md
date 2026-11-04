# TChCrTagInformationStr recovery

This source recovers the native class, its factory, and the parent/selection
call boundary. The compiled unit matches every function and data section, and
`linked_units.txt` takes it from source.

The target GC/2.6 profile produces all 1,164 original code bytes, the 24-byte
vtable and the 16-byte literal range at 0x804755F0..0x80475600. The original
split object has 47 relocations. The compiled object places the same 8-byte
literals at `.rodata+0` and `.rodata+8` under the compiler-local names `@14`
and `@38`, which are the `scope:local` symbols `lbl_804755F0` and
`lbl_804755F8`, and it also emits the vtable and factory relocations. The link
check accepts that object, and the linked DOL SHA-1 matches the original.
The literal range belongs to this unit: the original split-object reference
census finds its references only in this unit and its former data definition.
The 315/280 position pair is one 8-byte aggregate literal at 0x804755F0; the
render copy reads it as a single 8-byte block, so the former 4-byte split at
0x804755F4 had no separate object behind it. A full configured build produces
the original DOL SHA-1, and `tools/check_pr.py` reports the recovered function
and literal range with no regressions.

The angle increment computes `0x10000 / (ring * 4)` at its sole use. CodeWarrior
hoists this invariant and reproduces the original register allocation. Moving
it into a separately assigned local changes three register choices. The ring
values 1..4 preserve the original positive divisors and integer truncation,
including the twelve-way ring. The indefinitely incremented frame counter is
unsigned so its wrap has defined modulo-32 semantics; this preserves all bytes.
`run_task` keeps the `opt_common_subs off` region that already surrounded it on
main. Removing that region drops the function to 98.80597% (268 bytes, 12
words): the same float updates, with f0/f1/f2 reassigned. This source does not
add locals to force that assignment.

The known factory accepts selections 0..14. Each renders seven entries from
group 0x11 or 0x12. The five bundled language archives contain 21 and 84 entries
in those groups, respectively. Every reachable character span terminates inside
its buffer and is disjoint from relocation slots. The recovered object retains
no text pointer in a member.

`render` calls the already-linked `get_localized_text_entry` (24 bytes in
`TLobby_80132ED0`). That function is declared to return `s32` and loads the
group/entry word through integer lvalues; `draw_menu_text` takes `const char *`,
so the call site casts the returned word. The cast emits no instruction. The
table walk's scalar-storage type stays in the localization unit and is not
changed here. Several other units still declare the same getter with
disagreeing return types; migrating those declarations is outside this object.
