# Rope-controller native emission

The completed `TObjEZRopeSimulation.cpp` owns `800FEFCC..800FFA88`: twelve
functions, 2,748 code bytes and 180 data bytes. This folds the former rope-base
tail and the four-byte `tails_adjacent_name.cpp` split into the simulation.
The latter actually holds `TObjHMS_EZRope_Player__name`, as its constructor's
load at `800FF0AC` and the pointed-to class string establish.

The data order also connects these ranges: a 16-byte `NJS_ARGB` at
`8049DCF0`, a zero `RopeAnchor` at `8049DD00`, a zero `RopeCollisionSphere` at
`8049DD10`, chain gravity at `8049DD20`, the derived vtable at `8049DD2C` and
the base vtable at `8049DD44`. The color and defaults are separate file-static
objects; their explicit zero initializers remain in `.data` without section
annotations. The derived constructor refers to the named defaults and lets
C++ initialize its vptr. GC/2.6 shares the unit's data base in `r30`, emitting
`addi r0, r30, 0x3C` for that native vtable and `addi r4, r30, 0x10/0x20` for
the defaults. An explicit vtable-symbol reference instead adds a `lis` and
grows the constructor from `0x18C` to `0x190`.

The base and derived constructors now use their real classes and pass the
parent through to `TObject`. The remaining base-constructor caller,
`TBoss2Fin`, also uses a native constructor, and De Rol Le allocates it with
`new` using its parent task and position-vector elements. The rope base,
HMS player and fin constructors retain their original sizes (`0x5C`, `0x18C`
and `0xA8`); the De Rol Le constructor remains exact too. The native derived
destructor releases the three separately allocated record arrays at offsets
`3C`, `40` and `44`, then invokes the native base destructor. Both vtables
come from the compiler. This does not establish every remaining legacy caller
or record field's original source type.

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
