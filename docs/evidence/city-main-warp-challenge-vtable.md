# TObjCityMainWarpChallenge vtable

`pso/object/TObjCityMainWarpChallenge.cpp` owns
`__vt__25TObjCityMainWarpChallenge` (0x54 bytes at 0x804B6188) and
`jumptable_804B61DC` (0x1C) immediately after it. CONTRIBUTING.md says not to
write vtables by hand. This note records why this unit does.

The binary slots at +0x3c, +0x40, and +0x4c are
`open_confirm_window__12TObjAreaWarpFUs`, `is_warp_enabled__12TObjAreaWarpFl`,
and `confirm_area_transfer__12TObjAreaWarpFPvi`. The shared headers declare
`open_confirm_window` non-virtual, `is_warp_enabled` static, and
`confirm_area_transfer(s32)`. A compiler vtable from those headers references
`TObjAreaWarp::confirm_area_transfer(long)` and leaves the other two slots
empty. Other linked area-warp units use the current header layout, so the
headers stay as they are.

The unit therefore keeps the recovered manual destructor (so MWCC does not emit
its own table) and a hand-written `__vt__25TObjCityMainWarpChallenge` with the
binary's targets. `-inline off,deferred` plus last-function-first source keeps
`.text` in address order and puts that table ahead of the jumptable. The
object matches the split: `.text` 0xAC8, `.data` 0x70, `.rodata` 8.
