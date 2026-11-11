# BML model accessor contract

This extracts the BML contract family from PR #303 at
[`3ed9b21ae3d8b887e18642e3e561063fb1eb2c98`](https://github.com/matthewlewisnewton/pso-decomp/commit/3ed9b21ae3d8b887e18642e3e561063fb1eb2c98).
Both the header and definition on the extraction base returned `s32`; this
change makes both return `NJS_OBJECT *`. It is a source-contract correction,
not newly recovered code, data, or linked units.

## Accessor and consumers

`get_bml_model` at `0x8001EDC4` loads the table at resource offset `0x42C`,
indexes its 16-byte entries and returns the word at entry offset 8. Callers
use that value as a model hierarchy node. `BmlResource.h` now supplies the
single C-linkage declaration, with a `BmlResource *` resource and `s32` index.
Every source file mentioning the accessor directly includes that header.
There are no local accessor prototypes, function-pointer casts or macros.

The complete source inventory is reproducible with:

```
git grep -l -w get_bml_model -- src
python3 -m unittest discover -s tools/tests -p test_bml_accessor_contract.py -v
```

The initial extraction has 183 source files mentioning the accessor, not
183 newly changed users. Some already used the canonical header correctly.
The split manifest's 191 paths also included dependent headers and resource
declarations, so it was not a count of direct calls. Cosmetic-only changes
to already compatible calls are left out of this extraction.

Two old one-argument declarations had hidden forwarded indices:

- DarkGunner's helper at `0x800A3230` preserves incoming `r4` across the model
  call and reuses it for the texture call; the caller at `0x800A305C` supplies
  1. The model call now passes `(s32)a1`. The outer `void *` index parameter
  and texture accessor are retained as bounded legacy interfaces.
- The radar helper at `0x801FB9A4` ignores its first argument, replaces `r3`
  with the frame resource, and forwards `r4`. Its constructor calls at
  `0x801FB4D4`, `0x801FB4E4` and `0x801FB4F4` pass `&m_90` with indices 2, 0
  and 1. Its shared declaration is therefore the static
  `NJS_OBJECT *init_map_ptr(const s32 *, s32)`. The sole symbol rename is
  `init_map_ptr__13TRaderMapCoreFv` to the emitted `FPCll` signature. Neither
  the interior-word context nor the old metadata proves a class receiver.
  The helper's existing name is still provisional.

The dolphin loader at `0x802C2958` copies the real 16-byte
`NpcAnimationBinding`, replaces its motions pointer with the resource's
motions at `0x430`, and passes the copy to `register_animated_chunk`.
The former six-argument accessor cast artificially put copy temporaries in
`r5`–`r8`. These are not accessor parameters. The two-argument call and
native binding copy reproduce the original function without steering code.

## Bounded dependent declarations

`TBoss4Uro::get_instance_count` at `0x8004C1A4` returns the shared Falz BML
resource, not a count. Its return and corresponding resource locals/fields
are now `BmlResource *`; its misleading existing name is not reinterpreted
as ownership evidence. The `TBoss4Zako.cpp` unit still has its own legacy Uro
overlay, so its existing explicit-symbol declaration is retained with the
correct pointer return. That class-overlay inconsistency is not resolved
by this accessor change.

The rock model array and already recovered Falz death-demo model records
store model pointers. Their fields now agree with the accessor. The rock
array allocation uses the element pointer size, which is still four bytes
on the native target. Associated texture/motion accessor declarations follow
the resource parameter type where those locals changed. This does not
claim that all other accessor or rendering declarations are reconciled.

The still-unfolded Zako draw fragments at `0x8030A96C` and `0x8030AD58`
receive only compatible accessor/resource declarations and calls. Their
splits, layout, data ownership and compiler profiles remain unchanged.
`TChCrLoadAfsTextureReq.cpp` receives only the BML header, removal of its
local prototype, and a typed model call. Character-load lifetime, slot,
cursor and completion handling are not part of this split.

## Remaining boundaries

`BmlModelEntry::model` remains the existing signed 32-bit word. The accessor
converts that word to a pointer; it does not change the archive table layout.
Legacy integer resource storage, model fields and integer-parameter APIs
retain explicit conversions at their boundaries. In particular,
`find_model_node__FUll` remains `find_model_node(u32, s32)` and
`TBreakUpMdl::init_from_model` remains integer-parametered. These boundaries
are not 64-bit-pointer portable.

Several consumers retain local model-node overlays, raw offsets, and
rendering interfaces whose precise common type is unresolved. Their casts
describe those existing data boundaries; they do not redefine the accessor
or establish recovered class ownership. DarkGunner now uses the shared node
fields, but still reads the second model word through the existing integer
view. No indexing, bounds, lifetime or failure behavior is corrected here.

## Provenance and validation

The source work includes Matthew Newton and Cursor's Falz typing commit
[`d116a606e614be50d1b62714a197891508a13889`](https://github.com/matthewlewisnewton/pso-decomp/commit/d116a606e614be50d1b62714a197891508a13889),
and the later canonical-call corrections
[`e1f672fa7bc0a04cd9a57ff83aeda3bae41fb9f4`](https://github.com/matthewlewisnewton/pso-decomp/commit/e1f672fa7bc0a04cd9a57ff83aeda3bae41fb9f4)
and [`8fbec215f0378fa0381454e66f061c931ea11446`](https://github.com/matthewlewisnewton/pso-decomp/commit/8fbec215f0378fa0381454e66f061c931ea11446).
The final frozen source, rather than an earlier commit message claiming a
pointer-typed archive entry, controls this extraction.

Acceptance requires an authenticated clean-main report and exact candidate:
native DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`, address-based
`check_pr.py` no-loss, link/provider provenance, regenerated retention and
exception inventory, and full allocated-section/alignment/relocation
comparison of affected objects. Tooling and portable behavior/sanitizer
tests are additional checks, not a claim that the BML ABI is host-portable.
No new pragma, compiler override, assembly or porting exception is introduced.
