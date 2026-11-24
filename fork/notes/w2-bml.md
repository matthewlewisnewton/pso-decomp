# w2-bml: BmlResource constructor and destructor

0x80020004 is `BmlResource::BmlResource(s32, BmlResourceDescriptor *, s32, s32, void *)` and 0x8001FE7C is
`BmlResource::~BmlResource()`. symbols.txt uses the mangled names; no reference to the old names remains.

## What was done
- `BmlResource` now has the full member layout (0x440 bytes). The class lives in
  `pso/system/BmlResourceClass.h`; `BmlResource.h` includes it and keeps the `get_bml_model` declaration.
  Files that declare their own `get_bml_model` with another signature include only the Class header.
- Definitions in `src/pso/unk/TLobby_8001EF5C.cpp` were rewritten onto the real members. With a local
  alias (`self`) for `this`, or a local copy of the descriptor pointer, the register allocation differed
  (98.6 percent). Using members directly, plus `(u32)ptr != 0U` compares for the model/texture pointers (the
  members are s32 here, so a plain `!= NULL` gave a signed compare), gives 100 percent.
- Call sites: about 164 `new BmlResource(...)` expressions and about 218 `delete p;` statements.
  A `delete` on a non-BmlResource pointer type is written `delete (BmlResource *)(p);`; a descriptor of another
  declared type is passed as `(BmlResourceDescriptor *)(x)`; a `new` assigned to a u8 */s32/void * variable is cast.
- Kept as explicit calls (local `extern "C"` declaration under the mangled name): 94 files still reference
  `__ct__11BmlResourceFlP21BmlResourceDescriptorllPv` or `__dt__11BmlResourceFv`. These are the non-`1` flags,
  calls on storage not just allocated, `var_r0`/`temp_r3` decompiler-shaped allocations, function-pointer casts,
  and the 14 files below where `delete` or `new` changed the code.
- `text_802F0E24.cpp` defines its own `struct BmlResource`, so it was left alone.
- `BmlResourceLoad.h` and `BmlResourceLoader.h` still declare the explicit functions (names updated) for files
  that include them.

## Files reverted to explicit calls because the converted form scored below 100
TObjBoss2CeilJunk_8003A81C, TObjEneDubchik, TObjEneMe1Gee, TObjEneGyaranzo, TObjEneMe3Stelth, TLockOnCursor,
TOExplosiveMachine, text_80184C2C, TSceneSora, TChCrLoadGmNjReq, TObjSeabedSuisoBrakable, TOTrapChainSawEdge,
TAdMultiSaveGC_802FF0A0, TObjBoss8DemoRoom. (Probably the `delete` null check where the original has none, or
register differences; not investigated per call site.) Retrying them one call at a time could convert some.

## Not done
- The `var_r0`/`temp_r3` shaped allocations (about 40) were not converted.
- Descriptors typed as byte arrays or `void *[4]` are cast at the call site rather than retyped.
