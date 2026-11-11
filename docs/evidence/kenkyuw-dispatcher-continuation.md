# TObjNpcKenkyuW dispatcher continuation

Base: `eef2806e17f2a5aaa291dc504213ff078ae43cb1`. The unit has nine exact
functions and one missing 228-byte entry, `TObjPlayer__sub_802A445C`.
This checkpoint reconstructs that entry in C++; it does not complete or link
the unit. The source keeps its existing external name because ownership is
provisional: the observed receiver layout is `TNeedleShoot`, not `TObjPlayer`.

The function destroys a projectile whose body is absent; otherwise it selects
one of three contact collectors using the mode at +0xb0. An absent contact
list invokes virtual slot +0x18. A receivable first actor stores its body at
+0x38 and invokes slot +0x24 with that actor. The +0x38 field occupies existing
padding; the shared class size remains 0xbc.

The original compares the hit-test result with `cmpwi r3,0`; its implementation
returns integer 0 or 1. Declaring that result `s32` avoids the caller's bool
narrowing (`clrlwi.`) and preserves the callee's exact instructions.

## Measured compiler constraints

The best reconstruction is 96.49123%, 228 bytes, with the other nine functions
exact. At the hit-test call the original emits `mr r3,r30` then `lwz r4,0(r31)`;
GC/2.6 schedules the load first. Relocations and function size agree.

| Experiment | Best result for the missing function |
| --- | --- |
| Local scheduling settings and volatile accesses | 96.49123% |
| Inline collector/contact/hit-test helpers | 96.49123% |
| Scoped optimizer options, with scheduling on/off | 96.49123% |
| Compatible GC 2.0, 2.0p1, 2.5, 2.6, 2.7 releases | 96.49123%; nine other functions exact |
| Earlier/later compiler releases | No improvement; existing exact functions lost or compilation failed |
| Early returns, loops, gotos and boolean/pointer switches | 96.49123% |
| Explicit source/receiver temporaries and propagation settings | 96.49123% |
| Separate contact temporaries and member-function pointers | 96.49123% |
| Inline contact setters returning the receiver | 96.49123% |

With scheduling and propagation disabled, explicitly loading the default
collector's source argument fixes that block's order. The remaining mismatch
moves to the virtual hit call: the contact store precedes the receiver copy,
while the original copies the receiver between loading and storing the body.
Comma expressions introducing the store into the call also change stack
allocation or instruction order. These are measured failures, not a proof that
no suitable C++ source exists.

The earlier investigation is in the preserved `decomp-tobjnpc-kenkyuw` branch,
`docs/evidence/kenkyuw-dispatcher-hit-test-scheduling.md`. Compiler research
reference: https://github.com/doldecomp/mweppc . No external source was copied.

Experiment scripts, candidate sources and raw objdiff reports are retained in
ignored `build/experiments/kenkyuw-continuation/`; `results.json` lists each
compiled candidate. The checkpoint uses the best straightforward reconstruction
without experimental pragmas. It must remain original-backed until all code and
unit linkage pass the normal checks.
