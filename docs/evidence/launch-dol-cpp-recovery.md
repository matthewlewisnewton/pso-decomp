# LaunchDol recovery follow-up

PR #284 now carries only the validated DOL header view, launch-context field
and caller conversion described in [DOL image header view](dol-header-view.md).
The whole-function generated assembly body, compiler settings, symbols,
splits and linked coverage remain those of the integration baseline
`25b4001837b8bdc46666d2ad736a7148a411f978`.

## Historical experimental candidate

The separate research draft preserves that candidate in
[`experiments/launch_dol`](../../experiments/launch_dol/README.md), outside
the production build. Its explicit opt-in is for private compile comparison,
not a host port or permission to replace the exact provider.

The incomplete C++ loader remains inspectable at immutable commit
[`a9eab37139ef10f53e3e9baf4f8d2dd1ade395aa`](https://github.com/matthewlewisnewton/pso-decomp/blob/a9eab37139ef10f53e3e9baf4f8d2dd1ade395aa/src/pso/unk/text_8042E8C4.cpp).
It is removed from the active implementation in this narrowed scope, along
with its per-unit compiler override. Its temporary GC/2.6 probe scored
93.39744%, emitted 332 bytes against the 312-byte LaunchDol symbol, and left
three differing transfer words. That is experimental matching evidence,
not an exact function, a working host fallback or proof of behavior
equivalence. No host build or execution of that candidate was established.

The original handoff at `0x8042E9EC..0x8042E9FB` uses a nonlinking LR
transfer without restoring the frame. An ordinary C++ entry call in the
probe uses CTR and returns through a generated frame restore. A future
source candidate needs evidence for the actual transfer semantics and a
source-reachable implementation before it can replace the exact provider.
No new assembly, compiler steering, symbol widening or accounting change is
authorized by narrowing this PR.

The following stranded restore at `0x8042E9FC..0x8042EA0F` remains #285's
separate range; `init_modem_check_params` begins at `0x8042EA10`. A matching
suffix inside a larger compiled C++ function does not recover that symbol or
make it an independent link input. Its address and ownership hold remains.

## Provenance limits

The original-input inventory is summarized in the header-view evidence.
DTK-generated MW comments and reconstructed maps do not authenticate the
original ntUtl compiler or source. The bounded GC/2.6 backend investigation
found no admissible source-reachable LR handoff, without proving universal
impossibility.

The pinned explicit-assembly reboot routines in
[Melee](https://github.com/doldecomp/melee/blob/2f8eab8ebd7a2d25541e125abfa246defe1bacec/libs/dolphin/src/dolphin/os/OSReboot.c#L30-L43)
and
[Sunshine](https://github.com/doldecomp/sms/blob/4b2fd238058bf70822ca226e17f02879a7a46eb4/libs/dolphin/src/os/OSReboot.c#L28-L41)
are consistent with the handoff/stranded-restore interpretation. They are
analogies, not authenticated PSO source or evidence of a C++ transfer
facility. No new experiment follows from those comparisons alone.

## Typed interface and const-correct continuation

The continuation of #393 from `51a7496f2a242e9acf521fa870cb9864f8b8ac16`
uses one `extern "C"` declaration of `LaunchDol(ModemLaunchContext *)` in
`ModemLaunchContext.h`. The existing generated-assembly definition previously
accepted `void *`, while `text_8042EAD4.cpp` separately declared the context
pointer. Its original accesses at context offsets `0x104` and `0x108` and the
typed caller support sharing the context interface. Both pointer forms use the
same target ABI; the shared declaration now lets the compiler check agreement.
The provider also includes the existing SDK and memory headers instead of local
prototypes, including the incorrect `int` return declaration of `OSResetSystem`.
The generated body and its original address range are unchanged.

The experimental source makes the launch-record/image pointer variables and
size intermediates const, and exposes section sources as pointers to const bytes.
All 332 candidate code bytes and ten relocations are unchanged. Moving locals
into loop scope and replacing the comparison temporary with literal zero did
change emitted code, so those edits were not retained. The
[experiment notes](../../experiments/launch_dol/README.md) describe the source
constraints and unchanged transfer mismatch.

The official Freescale [Power Architecture Build Tools Reference, revised
7 October 2008](https://community.nxp.com/pwmxy87654/attachments/pwmxy87654/cw-development-tools/8896/1/Power%20Arch%20Build%20Tools%20Reference.pdf),
printed pages 300–304, documents synchronization, cache, arithmetic and buffer
intrinsics without documenting an LR handoff facility. This later manual does
not authenticate the compiler used for PSO or prove that no other facility
existed. It supplies no new transfer route to probe. The unresolved transfer
and #285 ownership limits above still apply.

Fresh baseline and candidate builds use the checked-in splits and symbols with
the pinned tools. Both reproduce DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; `tools/check_pr.py` passes with
zero code, data, function or linked-unit delta. The loader, its caller, the other
two direct context-header users and the switcher caller have byte-identical
compiled ELF objects before and after the change. Retention and the exception
inventory checks pass. A fresh private probe retains the 93.39744% comparison;
its first 296 bytes, ten relocations and their original DOL call targets agree.
No loader execution or additional C++ linkage is claimed, and the experiment
remains incomplete.
