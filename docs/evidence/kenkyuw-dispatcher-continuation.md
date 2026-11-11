# TObjNpcKenkyuW dispatcher continuation

Base: `eef2806e17f2a5aaa291dc504213ff078ae43cb1`. The unit has nine exact
functions and one missing 228-byte entry, `TObjPlayer__sub_802A445C`.
The completed reconstruction matches all ten functions and enables source
linkage for the unit. The source keeps its existing external name because ownership is
provisional: the observed receiver layout is `TNeedleShoot`, not `TObjPlayer`.

The function destroys a projectile whose body is absent; otherwise it selects
one of three contact collectors using the mode at +0xb0. An absent contact
list invokes virtual slot +0x18. A receivable first actor stores its body at
+0x38 and invokes slot +0x24 with that actor. The +0x38 field occupies existing
padding and is typed as the observed contact-body pointer; the shared class size
remains 0xbc.

The original compares the hit-test result with `cmpwi r3,0`; its implementation
returns integer 0 or 1. Declaring that result `s32` avoids the caller's bool
narrowing (`clrlwi.`) and preserves the callee's exact instructions.

## Measured compiler constraints

The initial reconstruction was 96.49123%, 228 bytes, with the other nine functions
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

## Matching solution

The complete `.text` section is 2,376 bytes and all ten functions match. The
dispatcher uses scoped `scheduling off` and `global_optimizer off`; no assembly,
extra references, stores or no-op statements are introduced. Both settings are
limited to this function and are recorded in the porting exceptions register.

Disabling the global optimizer preserves the contact store within the virtual
call argument. Loading the contact into a local first gives the observed load,
receiver copy, store, and virtual dispatch order. The right operand of the comma
expression must be a value, `static_cast<void *>(actor)`: leaving it as the
lvalue `actor` produces an otherwise unnecessary stack store and a 32-byte
frame instead of the original 16-byte frame. Adding `register` alone does not
remove the store. An explicit local for the default collector's source argument
also preserves its observed load before the receiver copy.

This was derived by reading the compiler's usage analysis:
[`checkexpression`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/COptimizer.c#L303)
marks a local referenced by `EOBJREF` as non-register, whereas a direct
`EINDIRECT(EOBJREF)` is a value use. The compiler's
[`call_function`](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/optimizer/FunctionCalls.c#L617)
then evaluates the register arguments before loading the virtual target. The
source explanation is an inference from that code; the exact instruction,
stack-frame and relocation results were measured with the pinned GC/2.6 binary.
No compiler source was copied into this repository.

The first 111 failed experiments and the subsequent global-optimizer, lvalue
conversion and register tests are retained under ignored
`build/experiments/kenkyuw-continuation/` for local reproduction. The failed
experiments above are historical measurements, not completion evidence.

## Final validation

Validated against clean fork-main baseline
`08c178922f` (the immutable full SHA is available in this branch's ancestry).
Both that baseline and the source-linked candidate pass `tools/check_pr.py`.
The candidate has one new exact function (+228 matched code bytes), one new
linked unit (+2,376 complete code bytes), unchanged matched/complete data,
and no exact-function, data or linkage regressions. All 3,611 linked units
pass the linked-object check. The final DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`, identical to the original.

The generated final Ninja link edge for `build/GPOE8P/psov3.elf` directly
includes `build/GPOE8P/src/pso/npc/TObjNpcKenkyuW.o` and excludes its original
split object. The report marks the unit complete with 10/10 functions and
2,376/2,376 code bytes. Its split owns no allocated data sections.

Generated retention adds five symbols from this unit and removes none.
Regeneration also sorts the existing DHCP `build_release` and `build_request`
entries into their normal alphabetical positions without changing membership.
Baseline and candidate logs and the direct link-input query are retained with
the ignored experiment artifacts.
