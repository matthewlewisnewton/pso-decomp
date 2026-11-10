# Technique controller recovery

Base: fork main `224eb99838471c243b20c305eddac75e7ff76c8f`.
Reference: upstream #208, `ae797d392bb93d5bf7164341870f78f864da23b0`,
`src/pso/technique/TTecCtrl.cpp` (unchanged through upstream `dd7a1a2d6`).

Recover `calc_technique_parameters` at `0x8022DBC4`, 5,044 bytes. Its level
clamping, cost scaling, per-technique cases and final bounds now match exactly.
The repeated angle conversion in case 3 is present in the executable and is
preserved; this recovery does not claim it is mathematically intended.

## Object ownership and interfaces

Fold the three already-linked fragments `TTecCtrl_8022C444`,
`TObjPlayer_8022C6C4` and `text_8022F164` into the existing `TTecCtrl` unit.
Text is `0x8022C444..0x8022F1C0` (11,644 bytes). The combined object owns its
four switch tables, compiler-emitted vtable, two conversion biases, float pool,
parameter/boost BSS and static initializer. All 21 functions and 1,036 data
bytes match. The old hand-written vtable is removed. The native constructor
wrapper still installs the compiler-produced vtable, as before.

Use the fork's BmlResource constructor/destructor and its typed technique-launch
calls, preserving prior interface improvements. Technique parameters now have
a 0x2C-byte bounded struct with size/offset assertions; unnamed fields retain
`pad_*` names because their full meaning is unresolved. The cost-scale table is
expressed as float pairs instead of pointer-cast numeric data. Existing unrelated
power-table representations remain unchanged.

The boost-table constructor at `0x8022F258` becomes a real
`TechniqueBoostTable` constructor: member construction plus `clear()` emits the
same 76 bytes as the old raw `__construct_array` wrapper. This prevents an
extra implicit constructor from appearing in the folded object. Its renamed
symbol and the compiler initializer name describe that recovered ownership.
The obsolete raw constructor/initializer headers are removed.

`classify_distance_band` takes the existing 16-bit client ID, passes all three
arguments to the calculator, and calls the boost helper directly. Its only
external caller uses the shared class declaration, retaining an explicit
signed-16 technique conversion that the original call made. Both objects stay
exact. Many other pre-existing calculator callers still have provisional local
return/argument declarations; this bounded recovery does not certify all those
interfaces. A port should consolidate them around the typed parameter interface.

## Compiler constraints and remaining debt

The upstream unit settings `-fp_contract on` and `-inline on,deferred` reproduce
fused cost arithmetic, the inlined lowered-limit helper's global-load order,
and vtable-before-switch-table emission. Functions are defined in reverse
address order for deferred emission. The existing charge-light function's
scoped `opt_propagation off` remains. Ports can drop the emission/optimizer
settings and should preserve FMA if bit-identical float results matter.

The calculator calls the existing `TTecAnti::copy_params` over parameter
storage, a provisional receiver boundary inherited from upstream. The folded
functions retain existing actor/light function-pointer casts, raw offset views,
pointer-valued integers and explicit mangled entry points. They reproduce
native interfaces but are not proof of original class ownership. Ports should
use a typed parameter-copy function, consistent actor/light declarations and
pointer-sized handles. No assembly, hardware access or intrinsic is introduced.

The previous conversion-pool symbol-rewriting hook is removed from configure.py:
all its readers now share this object. Localization verified no outside readers
before marking the initializer and nine constants local. The historical
conversion-pool evidence now records this retirement. The mechanical inventory
remains 5,772 pragmas in 876 files and 176 configured overrides; one old
post-process exception is replaced by the upstream compiler settings. Section
7's historical catch-up scope remains unchanged; section 5 records this recovery.

## Validation

Current-main build, baseline and retention passed before editing. Full build
and `tools/check_pr.py` pass; original DOL SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No exact function, code/data address
or linked range is lost. Four zero alignment bytes at `0x805DC7EC` leave reported
coverage when the final float symbol is corrected from eight bytes to four;
the full DOL hash proves their continued presence. This is allowed padding,
not a data-object regression. Retention adds seven entries and removes the old
initializer name, which is now compiler-local and retained by `.ctors`.

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,386 | 27,387 | 1 |
| Exact code bytes | 4,189,632 | 4,194,676 | 5,044 |
| Exact data bytes | 1,470,159 | 1,470,271 | 112 |
| Linked code bytes | 3,673,564 | 3,679,104 | 5,540 |
| Linked data bytes | 1,179,243 | 1,179,355 | 112 |
| Linked units | 3,586 | 3,584 | -2 |

The linked-unit reduction reflects folding three linked units into one; their
code/data remains source-linked. Actual ordered linker inputs: 3,584 source
objects and 1,386 fallbacks; SHA-256
`e2d023530564dd387eba5ae4d0794c890f611526b1f8ab60930ebdf02b497f67`.
