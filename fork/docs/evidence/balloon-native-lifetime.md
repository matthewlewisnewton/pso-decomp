# Speech-balloon native lifetime

`TUnk_804CF0B8::~TUnk_804CF0B8` at `0x80252AE4` releases the visible
slot when held and deletes the owned name. Automatic destruction calls the
`TWindowAddition` base destructor with the native flag zero. CodeWarrior
emits the vptr reset and the conditional storage release through
`TObject::operator delete`. The constructor at `0x80252B74` uses the same
compiler-generated table at `0x804CF0B8`.

Declaring `run_task` first among the overrides of the inherited virtual
slots places table emission in `TWindowFukidasi.cpp`. Deferred generation
puts the vtable before the unit's jump tables. The virtual slots still
follow the inherited order.

## Constant emission

With GC/2.0 and uniform deferral, the inline angle literal lands after
both conversion biases. A named constant with external linkage lands before
both, because the compiler emits it when it parses the definition.

The first three functions, through `rearm_balloon` at `0x802501F4`, use
immediate emission and stay in address order. The length cast in
`rearm_balloon` supplies the unsigned bias at `0x8044ED68`. The late
definition of `balloon_angle_units_per_radian` follows it at `0x8044ED70`.
The signed cast of `rand()` in `0x802505C0` supplies the third double at
`0x8044ED78` when the compiler generates the rest of the functions. The
deferred definitions are in reverse address order. The angle scale is
`32768.0 / 3.141592f`, which gives the original double bit pattern
`0x40C45F30B21788BB`.

The float pool begins with `1000.0f`, `0.5f` and `19.0f` at
`0x805DCD08`. The new start has natural eight-byte alignment. The shared
`newton_sqrtf` body supplies the zero as before. The live header inline
`measure_text_entry` shares the text measurement operation between
ChallengeResult and the balloon. ChallengeResult owns the linked body at
`0x80246F8C` and its literal at `0x805DCB70`. The balloon's weak copy
supplies the pooled `1000000.0f` at `0x805DCD54`, which the name-plate
renderer at `0x802521B8` also loads. The linker keeps the earlier
ChallengeResult body. The split audit found no foreign consumer of the
balloon's literal before localizing its label.

## Verification

The balloon main unit matches all 32 functions and 320 data bytes. Its destructor also matches all 144 bytes,
and the expanded ChallengeResult unit matches all four functions and 328
data bytes. The full build passes the address-based and link checks against
refreshed #562 tip `71380235fc` and matches DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.
