# Ancient trap continuation

This continuation merges the Ancient base in #221 at `186bafe01` and main
at `0b6342088`. The source conflict is resolved in favor of the base's native
constructors, shared types, const debris initializers and literal pool.

The fresh merged build matches all 18 Ancient01 functions: `play_sounds`
(696 bytes) improves from 91.086205% to 100%; `vfunc_81` (540 bytes) and
the native constructor (612 bytes) remain 100%. All six owned sections
match: `.text` 3696, `.data` 692, `.rodata` 400, `.sdata2` 48, `.sdata` 8
and `.sbss` 8 bytes. The `.data` tail is linker alignment padding, as
explained in [the layout evidence](ancient-trap-recovery-wip.md).

The base's registered GC/2.0 unit profile and `const TObjChipParams`
initializers reproduce the debris-copy schedule without per-function pragmas
or clamp temporaries. The inherited inline slots generate the leading
`1.0f`/`0.0f` literals; the constructor contributes the final `0.33f`.
See [the existing per-flag evidence](porting-exceptions.md#totrapancient01cpp-unit-overrides-221).

The previous claim that `.sdata2` flags prohibit linkage was incorrect.
`readelf -SW` still shows flags 3 (`WA`) in the compiler object and 2 (`A`)
in the split object. These ELF headers are not byte-identical, but the actual
link takes `build/GPOE8P/src/pso/misc/TOTrapAncient01.o`, including its
literal pool, and the rebuilt DOL has the original SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. No section-flag rewrite is used.
The link checker accepts the unit under its existing rules.

Against the fresh main baseline, the combined result adds 2 exact functions
and 1236 matched code bytes, 1840 matched data bytes, 3696 source-linked code
bytes and 1940 source-linked data bytes. There are zero exact-function or
source-link regressions. The 12 fewer covered bytes are three four-byte
alignment gaps reported by `report_delta.py`; the final DOL preserves them.
