# LLM context

Start with the repository's applicable agent instructions, then read the
[contributor guide](../../CONTRIBUTING.md) and [architecture](../architecture.md).
Use the [evidence index](../evidence/README.md) to find investigation notes
relevant to the task. Notes may describe historical commits, incomplete work, or
validation at a particular checkpoint; check their dates, bases, and stated
limits against the current source before treating them as current.

For unit-link tasks, follow the contributor guide's retention freshness rule: qualify the exact build inputs,
check unchanged main first, and route existing global drift into a separate validated synchronization PR.
After that lands, regenerate unit deltas from the synchronized base; keep the generated block consistent.

This directory is for assistant-oriented context and pointers. Contributor
guidance lives in the
[contributor index](../contributors/README.md), and local queue/tool references in
the [operations index](../operations/README.md). Shared investigation evidence is
maintained separately to avoid duplicating technical claims.
