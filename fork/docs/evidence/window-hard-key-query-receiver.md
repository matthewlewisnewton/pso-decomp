# Explicit Hard keyboard key-query receiver

This checkpoint follows `c1a368a49714562c830d2fc17aa04b303e848f67`.
The Hard render and task methods previously called a hand-mangled declaration
of is_key_active with no declared receiver. Both now call the existing genuine
Hard member directly. Its definition at 0x80260444 reads Hard's m_60 mask 0x200;
there is no ambiguity about these two enclosing Hard receivers.

Existing outer guards, short-circuit order, composer query and subsequent calls
remain unchanged. The separate has_non_modifier_key legacy declaration/call is
not altered: its global-state behavior and static/member interface need their
own evidence, and are not inferred from this receiver correction.

The first ordinary member-call probe passes the capacity-gated original-DOL
build with every captured compiled object raw-identical. No symbol, relocation,
provider, retention entry, compiler control or layout changes are introduced.
Independent source review found no blocker in the two-file change. Aggregate
checks, all 346 tool tests and portable behavior tests pass; retention remains
at 19,454 entries without drift.

This supersedes only the no-argument Hard member-query qualification in earlier
keyboard evidence. It does not clear original table/destruction, global key
state, borrowed-composer lifetime, Soft PMF or other window-family holds.
