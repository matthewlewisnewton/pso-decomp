# Documentation

## Contributor guides

The [contributor index](contributors/README.md) links to onboarding, project
architecture, and validation.

## Queue and tool operations

The [operations index](operations/README.md) links to reusable local queue and
evidence-tool reference material, separate from human contribution instructions.
Live snapshots, per-worker status and private handoff packets remain local.

## Recovery and verification evidence

The [evidence index](evidence/README.md) collects the tracked investigation notes,
including historical checkpoints and work in progress. They record the scope and
validation at the time of each investigation; they are not a current status report.
Consult the source and current checks before relying on an old result.

The [Moja compiler-tracing case study](evidence/moja-compiler-tracing.md) explains
how frontend temporaries, register allocation, and constant-pool emission exposed
a matching replacement for redundant index arithmetic.

## Porting exceptions

The [porting exceptions register](porting-exceptions.md) lists every asm body,
compiler-specific construct, per-unit compiler override and approved regression
that a port to another platform must rewrite.

## LLM context

[LLM context](llm/README.md) is a compact entry point for assistants working in
this repository. The contributor guides and evidence remain available to both
people and assistants; the evidence is not a separate set of project rules.
