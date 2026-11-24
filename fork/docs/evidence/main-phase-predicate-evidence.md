# Main-phase predicate return

The DD predicate at `0x800B9CF4` compares the current main phase with `0xF`
and returns a complete `0` or `1` in `r3`. Its known callers test that full
register. Declaring the result as `s32` captures that observable contract and
avoids adding a byte mask at direct calls. The original source return spelling
is not established by the binary.

Several callers still declare a hand-mangled compatibility name, and some pass
an unused receiver argument. Their cleanup is separate; this change only
corrects the existing shared declaration and definition.
