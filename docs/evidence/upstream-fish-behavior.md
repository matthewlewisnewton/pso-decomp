# Fish behavior and native lifetime recovery

Initial fork base: `224eb99838471c243b20c305eddac75e7ff76c8f`.
Behavior reference: upstream #240, `dd7a1a2d6e200a69462fff12172ff35aaa460c93`,
`src/pso/object/ambient/TObjFish.cpp` and its entry layout.
Native lifetime/global follow-up base: `cbe750b9197533f64ff472f00467a4776181b97a`.
Shared pointer-API follow-up base: `754117ce13cb8508a711f4d8abc37494a805df64`.
Combined validation base: fork main `08c178922fb8da57f44c2d9fc4efb5ebdecf05b4`.

## Behavior and shared interfaces

`TObjFish::run_task` at `0x8029D974` (2,044 bytes) recovers movement, boundary
reflection, player avoidance, target return, turning and animation advancement.
The renderer, update and initializer share the offset-asserted 0x44-byte
`TObjFishEntry`. The school state at +0x90 is a signed halfword and the entry
pointer at +0xA0 has its real type. The renderer is the native class override.

Shared draw/getter/matrix interfaces replace the previous zero-argument draw
call that depended on a preceding getter leaving a value in r3. Visibility uses
the real base-class virtual; `update_state` returns a full-register integer,
preserving the original `cmpwi` call contract. Camera reads use the asserted
`TCameraCtrl::position`. Five 0x30-byte resource records contain terminated model
and motion filename lists and typed `BmlResourceDescriptor` fields, including
16-bit counts. No vtable or packed-pointer resource descriptor is hand-written.

## Constants and existing compiler settings

The native float pool is `0x805DDD40..0x805DDD88` (72 bytes). Update, renderer
and initializer literals reproduce it. Keeping the former separately named
10430.38043493439 double duplicates eight bytes and moves the compiler pool.
The conversion bias and angle double remain in `.rodata`. Localization checked
outside references before marking 20 compiler-generated constants local.

The existing unit-level `-pool off` preserves independent table and constant
references. Pooling adds a saved register and changes the update frame from
0xB0 to 0xC0; the update scores 90.8317% instead of 100%. Existing
`fp_contract on`, `dont_inline off` and `inline_depth(4)` settings are retained.
Ports can drop pooling/inlining steering while preserving required float
contraction, double-precision angle conversion and signed 16-bit angle wrapping.

## Native lifetime and owned globals

The follow-up to `cbe750b9197533f64ff472f00467a4776181b97a` replaces the
hand-written vtable, explicit vptr writes and lifetime wrappers with a native
constructor, destructor and `new TObjFish` factory. The placement record uses
its observed position, rotation, scale and count fields; its leading metadata
remains opaque. The constructor name is mapped to its native ABI symbol.

Matt approved the scoped deferred-emission exception on 2026-11-10. The final
resource loader is compiled with `defer_codegen on`; the pushed setting is
restored at EOF, after the closing linkage block. Restoring it inside the block,
or adding another declaration after the final restoration, emits the loader too
early. The required `.data` order is resource table at +0, native vtable at +0xF0,
and switch table at +0x124. Immediate compilation puts the switch table at +0xF0
and vtable at +0x140. These objects have identical raw section bytes but different
relocations, so byte comparison alone does not establish a match. The scoped
control matches payloads, alignment and normalized relocations using the actual
GC/2.6 compiler. Ordinary definition orders, header extraction, inline methods,
construction placement and simple inline/template dependencies did not recover
that order under unchanged settings. This bounded experiment does not prove
that no other source arrangement can work or identify the historical source order.

The original object inventory has no outside code references to the resource
table, the resource pointer, area state or class-name pointer. The two `.sbss`
words at `0x805D65E8..0x805D65F0` are now defined as `BmlResource *` and `s32`
in Fish. The class-name pointer at `0x805D3D58..0x805D3D5C` is a `const char *`
pointing to the existing `TObjFish` string. Its old eight-byte synthetic symbol
included an unreferenced trailing zero word; that word remains outside the
claimed live pointer range. No second semantic field is invented. The zero word
is probable alignment padding, rather than demonstrated class data.

No artificial loader unit is introduced. The loader is the only code reader of
the resource table, and the constructor/destructor are the only vtable readers;
these references establish no independent original source-file split. Existing
`-pool off`, floating-point and inline settings remain. Ports can remove emission
steering while retaining native class lifetime.

## Shared pointer contracts

`BmlModelEntry::model` is `NJS_OBJECT *`, and its texture-list field at +0xC is
`GinjaTextureList *`. The model and texture accessors return those pointer types
through canonical shared declarations. The model-entry size and both offsets are
asserted for the native target. Loading and binding retain the same target layout.
Fish passes these returned pointers directly to its renderer and texture selector.

The release wrapper at `0x8007EBB4` takes `void *`: it checks for null and passes
the unchanged allocation to `xfree`. Its inherited static class attribution is
provisional; no original class ownership is claimed. The allocator at
`0x8007EBFC` already returns `void *`. Fish's destructor now releases its typed
entry pointer directly. All callers use the corrected release declaration; the
symbol mapping follows the pointer parameter. The `free_data_file` forwarding
wrapper and shared declarations now return `void`, matching the callee and both
consumers, which discard the result. The signboard cleanup explicitly passes its
buffer instead of relying on an unstated `r3` argument.

Other recovered actors still store some addresses in target-sized integer fields,
and parts of the BML loading/callback API retain provisional integer interfaces.
Conversions at those existing boundaries remain explicit; this change does not
claim a whole-project 64-bit port. The shared fields and APIs used directly by
Fish no longer force pointer-to-integer round trips.

## Validation

The native full build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. `tools/check_pr.py` is run against
the current-main and previous-published-head baselines above. Address-based comparison loses no exact
function, live data or linked range against either baseline. No padding is lost
against either baseline. Constructor and heap-release symbol renames are compared
by original address. The pointer-API follow-up preserves all coverage totals
relative to its published-head baseline.

All nine Fish functions (4,704 bytes) and 1,416 data bytes match and link from
source. The six allocated sections match in payload, size and alignment,
including the four-byte `.sdata` pointer and eight-byte zero-filled `.sbss`.
All 303 normalized relocations match. This is not whole-ELF identity: inherited
`.sdata2` flags remain writable in the compiled object versus read-only in the
reconstructed original object.

Against pre-lifetime PR head `cbe750b919`, the change adds 12 matched and linked data
bytes, with no Fish function/code-count change. The current-main integration
retains the reviewed Fish implementation from `0a5749d454`, including native
lifetime, all three globals and the scoped emission setting. Against fork main:

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,444 | 27,445 | 1 |
| Exact code bytes | 4,241,872 | 4,243,916 | 2,044 |
| Exact data bytes | 1,477,679 | 1,477,763 | 84 |
| Linked code bytes | 3,890,476 | 3,895,180 | 4,704 |
| Linked data bytes | 1,357,627 | 1,359,043 | 1,416 |
| Linked units | 3,610 | 3,611 | 1 |

The native-lifetime/global change adds the three owned globals, their class-name
string and the native constructor, and removes the superseded constructor name
relative to pre-lifetime head `cbe750b919`: +5/-1. With current-main integration,
the retention list has 18,699 names and zero drift, +49/-0 versus pinned main.
The heap-release parameter correction renames its mapped symbol from `FUl` to
`FPv`; it requires no retention change.
These changes follow the exact regenerated original-object inventory; no
unrelated retention normalization is included.
Fish remains linked, and the pointer-API follow-up changes no linked-unit membership. Two additional original fallback fragments result from claiming live global ranges inside the
previous autogenerated data owners; the adjacent unclaimed bytes are preserved.

All gains are supported by the generated linker input list as well as objdiff.
The exception inventory records the scoped deferred-loader setting and its
portable alternative. The direct shared pointer contracts are recovered; the remaining legacy actor
and loading boundaries described above are separate portability work.

The final standalone full native build is reused by `check_pr.py --no-build`
against both pinned baselines. Complete allocated section payloads, sizes,
alignment and normalized relocations also match for the BML getter and loader,
heap release, data-file forwarding wrapper and signboard cleanup units. Tooling
tests, Python syntax, portable behavior checks, ASan/UBSan, exception inventory
and independent exact-head review are required before fork publication.
