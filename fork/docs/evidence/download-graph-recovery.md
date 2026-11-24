# Download graph recovery

`pso/unk/text_8007ECF0.cpp` owns six functions. The draw function at
`0x8007F27C` builds a four-vertex fan and draws the border, filled portion,
and end marker. The download update writes the fraction at `0x1c` and the
graph initializer writes the bar color at `0x34`.

## Compiler comparison

With the default GC/2.6 compiler, the 380-byte draw function scored 85.75%.
The backend schedules the position-x load before the two-pixel margin and
reorders arithmetic and descriptor loads in the border pass. Changing
the assignment order or copying the input coordinates did not recover
the original schedule. The dialing rectangle recovery showed a precedent
for testing GC/1.3.2 on vertex setup code. With the same graph source,
GC/1.3.2 emits the original instruction order. The filled edge uses a
scoped `fp_contract on` to emit the original fused multiply-add.

GC/1.3.2 emitted indirect calls in the countdown routine when the source
called `sprintf` and the outlined text helper through incompatible
function-pointer casts. Using their direct, typed signatures restores the
three original branches and brings the complete unit to six exact
functions. The percent label uses an eight-byte buffer, the space between
the output address and the conversion scratch slot in its original frame.

## Data and renderer

The graph constructor and draw code reference the class-name string, two
coordinate pairs, and four-field descriptor at `0x80438A98..0x80438AC4`.
The descriptor occupies 16 bytes. The next four bytes align the conversion
pool at `0x80438AC8`. The countdown also references the adjacent format
strings. The unit's read-only data covers `0x80438A98..0x80438AF8`, including
five trailing alignment bytes before the next contribution. The small
read-only data covers 40 bytes.

The first four float definitions follow their initial consumer and use a
separate C-linkage namespace. This gives the linker the original symbols
and keeps CodeWarrior from folding later reads into duplicate literals.
The private conversion and float pool entries are compiler literals.
The localization tool checks the original and compiled consumer objects
before marking their split symbols local.

The renderer at `draw_tri_fan_2d__14TObjCMHairMenuFllf` reads the vertices,
colors, and count of a `ColorLineList`. The C-linkage declaration expresses
that receiver while preserving the symbol used by the remaining legacy
menu callers.
