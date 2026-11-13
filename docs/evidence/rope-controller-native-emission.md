# Rope-controller native emission

The completed `TObjEZRopeSimulation.cpp` owns `800FEFCC..800FFA88`: twelve
functions, 2,748 code bytes and 180 data bytes. This folds the former rope-base
tail and the four-byte `tails_adjacent_name.cpp` split into the simulation.
The latter actually holds `TObjHMS_EZRope_Player__name`, as its constructor's
load at `800FF0AC` and the pointed-to class string establish.

The data order also connects these ranges: a material-color/default-record
block at `8049DCF0`, chain gravity at `8049DD20`, the derived vtable at
`8049DD2C` and the base vtable at `8049DD44`. The derived constructor addresses
its defaults and vtable relative to the first block. The source retains the
existing C constructor interfaces and their provisional receiver views; this
change does not claim that every legacy constructor/caller type is recovered.
The native derived destructor releases the three separately allocated record
arrays at offsets `3C`, `40` and `44`, then invokes the native base destructor.
Both vtables now come from the compiler.

Immediate emission with ascending definitions preserves instruction bodies but
reverses the vtables. The compiler also duplicates an explicitly defined named
double when folding its uses into a separate literal. Following the existing
[emission investigation](compiler-emission-evidence.md) and
[constant-pool recovery](chr-select-confirm-cell-store.md#native-float-pool-recovery),
reverse definitions with GC/2.6 `-inline deferred`, `auto_inline off` and the
existing scoped aggregate-copy inlining reproduce the complete object. Testing
`-inline off,deferred` instead outlines an assignment operator and changes the
three record-copy functions. Scalar word copies retain their sizes but allocate
the two loaded words differently. No source-order claim about Sega's original
files follows from the working arrangement.

The two class strings and the compiler-emitted double occupy
`8043DF18..8043DF48`. The literal uses `10430.38043493439` to convert radians to
the game's angle units. The localization tool finds no foreign original or
compiled consumers before making `lbl_8043DF40` local. The class-name pointers
occupy `805D2B50..805D2B58`; the existing float pool remains
`805DAA58..805DAA68`. Every allocated section matches in bytes, size, alignment
and relocations through the unit-link checks and full executable validation.

The data section ends at `8049DD5C`. The following four zero bytes align the
next unit's data to eight bytes; they are linker padding, not a source object.
The address-based no-loss check reports that padding separately.
