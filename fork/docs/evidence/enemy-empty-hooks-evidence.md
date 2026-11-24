# Empty enemy-call interfaces

The original routines at `0x800BB7D0` and `0x800BB7D4` each contain only a
return instruction. An audit of allocated relocations in 5,090 original
objects found three direct calls to the first and ten to the second, with no
allocated data or virtual-table references. The inspected calls pass an
actor-like pointer in `r3`; calls to the second also pass `0xF1` or `0xF2`
in `r4`. No result dependency was observed at these sites.

The neutral `fn_800BB7D0(void *)` and `fn_800BB7D4(void *, s32)` interfaces
model those call sites and preserve their argument evaluation. They are
provisional: the empty bodies do not prove that the arguments were consumed,
their original types or signedness, a return type, function names, class
membership, or semantic purpose. The relocation scan cannot rule out a
runtime-computed reference. No dummy argument use is needed in the bodies.
