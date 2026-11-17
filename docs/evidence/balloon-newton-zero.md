# Speech-balloon zero from the live square-root helper

The balloon's `rest_balloon` calls `newton_sqrtf` at `0x80250AB8` and
`0x80250BCC`. The surviving helper at `0x8001978C` performs three Newton
refinements, using the existing half and three doubles at `0x80434098` and
`0x804340A0`. Its initial comparison uses a float zero. These are live calls
and the existing helper body; no extra function or unreachable path is added.

`NewtonSqrtInline.h` holds the single definition. In
`TObjPlayer_80011014.cpp`, its include replaces the old definition between
`fabs_double` and `register_object`. Earlier callers see the existing
function declaration. GC/2.6 with the unchanged `-inline off` emits the weak
body at that definition position, preserving all 226 functions' original
order. Keeping the helper's existing external double reads also preserves
its data layout. Including the definition before those callers would emit
the weak copy immediately after the first caller and change the text order.

The balloon includes the same header before its callers. Its weak copy
appears immediately after `rest_balloon`, creating the zero pool slot at
`0x805DCD30`, before `project_anchor`'s 320 and 240 literals. The linker
keeps the earlier TObjPlayer copy. Later balloon functions reuse the zero,
so it remains at that position after the duplicate helper is discarded.
This replaces the balloon's explicit zero object and compatible pointer
reads with ordinary `0.0f` expressions. The other three materialized
constants are unchanged.

The helper retains its existing reciprocal-square-root intrinsic, volatile
single-precision result and operation order. TObjPlayer keeps its existing
`fp_contract on` scope around the implementation include. The header adds no
pragma; the balloon compiles its discarded copy under its existing settings.
No compiler option, alignment override, exception or alternate definition is
introduced.
The existing external double objects remain original inputs; this change
does not claim source ownership for them.

A fresh original-object reference audit found no consumers of
`TWindowFukidasi__data_805DCD30` outside the balloon. The standard
`localize_split_globals.py --write pso/misc/TWindowFukidasi.cpp` command
therefore marks that split symbol local, matching its anonymous pooled
representation. The generated retention list is refreshed with
`link_units.py force-active --write`.

Both units retain 100% in every allocated section and their original
function order after excluding the discarded weak copy. The full DOL,
linked-unit, retention, exception-inventory and address-based no-regression
gates qualify the change. Matched code remains 4,302,440 bytes and matched
data 1,506,380 bytes; the DOL SHA-1 remains
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

This is a constant-source recovery, not native balloon destruction.
`WindowConstructorAbi.h` and its remaining §9 call site are still required.
The deferred native-destructor experiment improves to `.sdata2` 97.82609%
with this header, but its 19.0f and angle-conversion double still occupy the
wrong pool positions, and 1000.0f remains outside its owned pool. That
experiment is not part of the qualified change.
