# LaunchDol recovery follow-up

PR #284 now carries only the validated DOL header view, launch-context field
and caller conversion described in [DOL image header view](dol-header-view.md).
The whole-function generated assembly provider, compiler settings, symbols,
splits and linked coverage remain those of the integration baseline
`25b4001837b8bdc46666d2ad736a7148a411f978`.

## Historical experimental candidate

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
