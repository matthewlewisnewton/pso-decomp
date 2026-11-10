# Experimental LaunchDol C++ candidate

This is the incomplete source candidate removed from PR #284, preserved for
research. It is excluded from the production build and guarded by an explicit
`PSO_LAUNCH_DOL_EXPERIMENT` opt-in plus the target compiler check. Do not link
its object into the game, execute it as a replacement loader, or treat it as a
host fallback. Production `LaunchDol` continues to use its existing exact
whole-function generated assembly provider.

The prerequisite header/type recovery from PR #284 at immutable commit
`d70369041672d5c881d895dc0a27b96f612e4b0c` is now merged into main via
`b96d4c294f9f8ef84756fc394c9b042e0f36bfa9`. This refresh integrates main
`78a6f8fae432ad941677d392d332273e1079603b`. Relative to that main, no
production source, compiler profile, symbols, splits, retention or linkset
is changed by this experiment.
The body is preserved from historical commit
`a9eab37139ef10f53e3e9baf4f8d2dd1ade395aa`; only the compile guard and
warning comments are new.

## Known mismatch and semantic limits

The reproduced GC/2.6 comparison is **93.39744%**, with 332 emitted bytes
against the 312-byte target symbol. The first 296 bytes and their 10
relocations match. Three words differ across the combined loader/restore
span: the entry register load at `0x128`, control-register transfer at
`0x130`, and branch at `0x134`.

The candidate makes a linking CTR call and then has a normal frame restore.
The original makes a nonlinking LR transfer without restoring its frame.
That is a known semantic difference, not merely a fuzzy-score discrepancy.
Behavior equivalence has not been established; no host build or loader
execution is claimed. Even its section-table and cache-operation handling is
a source-recovery hypothesis, not an independently exercised loader.

The final 20 bytes of the compiled candidate match the stranded restore at
`0x8042E9FC..0x8042EA0F`, tracked by #285. This does not recover that symbol,
change its ownership, permit widening LaunchDol or create a linkable unit.
The transfer/address/ownership holds remain in place. No new assembly,
production compiler override or accounting change is proposed.

## Reproducing the comparison

First configure and build normally with the pinned tools and original inputs.
Use the GC/2.6 compiler through the normal wrapper, with its target include
paths and flags below, to compile **only this file** into an ignored private
output directory. The extra flags reproduce the historical probe; they are
not installed in `configure.py` or a production build rule.

```sh
mkdir -p build/launch-dol-experiment
"$PSO_WIBO" "$PSO_COMPILERS/GC/2.6/mwcceppc.exe" \
  -nodefaults -proc gekko -align powerpc -enum int -fp hardware \
  -Cpp_exceptions off -RTTI off -str reuse -maxerrors 1 -nosyspath \
  -i build/GPOE8P/include -i include -i src -i libs/dolphin/include \
  -i libs/dolphin/include/dolphin -char signed -use_lmw_stmw on \
  -O4,p -inline auto -lang=c++ -opt nocse,nostrength,noprop \
  -DPSO_LAUNCH_DOL_EXPERIMENT=1 \
  -c experiments/launch_dol/LaunchDol.cpp \
  -o build/launch-dol-experiment/LaunchDol.o
"$PSO_OBJDIFF" diff \
  -1 build/GPOE8P/obj/pso/unk/text_8042E8C4.o \
  -2 build/launch-dol-experiment/LaunchDol.o LaunchDol \
  -o build/launch-dol-experiment/diff.json
```

Set the three `PSO_` variables to your existing local tools. Follow the
repository's shared-capacity protocol for native builds and probes. Keep
objects, split originals, disassemblies and private build inputs local; this
PR publishes source and summarized evidence only.

## Research gate and provenance

Further experiments need a distinct, evidenced source-reachable transfer
facility or authentic original-toolchain evidence. Ordinary call spellings,
`noreturn` variants and computed-goto sweeps have not solved this boundary;
the existing compiler audit supplies no demonstrated LR-write facility.
Do not repeat those sweeps merely to vary syntax or force a score.

The original ntUtl version marker does not authenticate its compiler. DTK's
split-object MW comment is synthesized, reconstructed maps/probe objects are
not original build artifacts, and external SDK assembly decomps are analogies
only. See [the provenance inventory and header view](../../docs/evidence/dol-header-view.md)
and [the transfer follow-up](../../docs/evidence/launch-dol-cpp-recovery.md).
