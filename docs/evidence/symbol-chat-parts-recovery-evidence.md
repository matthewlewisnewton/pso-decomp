# Symbol chat parts unit linkage

The `pso/misc/TWindowSubSymbolChatParts.cpp` unit owns code at
`0x80284C04`–`0x80285E10`, the signed conversion bias at
`0x8044FC08`–`0x8044FC10`, and the 18-float literal pool at
`0x805DD7C8`–`0x805DD810`. These are unit boundaries from the current split;
they do not establish an original source filename or complete class ownership.

At fork main `e65f11ce6ec99c006909422f81da1c0a46ac062e`, all 20 functions,
4,620 code bytes and 80 data bytes compare exactly, but the unit cannot link
from source. Its grid renderer at `0x802857C4` references `lbl_805DD7F8`
without defining it. The compiler already emits that slot's `32.0f` value
as an anonymous literal used by the other renderers.

Replacing the named read with `32.0f` preserves every section size and data
byte, but changes eleven floating-point register operands in the 484-byte
renderer (99.421486%). Scoped `opt_common_subs off` and `opt_lifetimes off`
do not repair it. Scoped `opt_propagation off` retains the original row-height
load and floating-point lifetimes: all 20 functions and all owned data match
with the ordinary literal. The original `fp_contract on` scope remains.
This is an observed compiler constraint, not proof of an original pragma.
Ports can drop propagation steering and use the same literal and arithmetic.

The stale global names for the 18 compiler-pool floats are localized only
after checking the fresh original and compiled consumer inventory. The
conversion bias was already local. This removes no referenced export and
introduces no duplicate constants, linker alias, post-processing step or unit
compiler override.

## Validation

The final baseline is fork main
`0a85a72c1c09598512363e6d375616ebd1d1b63e`. Unchanged main passes the
full build, address-based no-loss comparison and retention freshness check.
The complete-unit change raises linked units from 3,601 to 3,602, linked
code from 3,834,576 to 3,839,196 bytes, and linked data from 1,199,511 to
1,199,591 bytes. Matched function, code and data counts are unchanged.

Raw `.text`, `.rodata` and `.sdata2` bytes equal the fresh original split,
with sizes 4,620, 8 and 72 bytes respectively. All 20 functions match and
the linker selects the compiled source object. The retention update adds
ten entry points from this unit and removes none.

The capacity-managed full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
`tools/check_pr.py --no-build` passes after that build, including the
address-based no-loss comparison, all linked-unit checks and retention freshness.
The port-exception inventory and whitespace checks pass.

## Historical grid-renderer investigation

`fn_802855C4` at 0x802855C4 renders the mode-1 part grid. The original object reads the signed count at 0x76, walks rows of four, skips rows outside the draw context bounds, and calls the part sprite setup with the selected mode and two referenced settings. The recovered function follows those operations. The temporary overlay names describe observed offsets, not verified ownership or original names.

A targeted GC/2.6 compile and objdiff against the original unit object from the clean `beaa7f52af2a7360e18deafc771648f51b709531` build give 98.55% for this formerly missing 512-byte function. All 19 previously exact functions compare at 100%, as do `.rodata` and `.sdata2`. The function still differs in floating-point register allocation. This is not a complete match or a claim that the unit links from source. The full build passed with `ninja -j2` under the shared build lock. `tools/check_pr.py --no-build` passed against the clean same-commit donor report: no exact-function or linked-unit regressions, 72 additional matched data bytes, and all 3,536 linked units remain exact.
