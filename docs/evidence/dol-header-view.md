# DOL image header view

PR #284 separates the header view and launch-context field typing from
the unresolved LaunchDol transfer recovery. Its integration baseline is
`25b4001837b8bdc46666d2ad736a7148a411f978`. It includes no loader
compiler override or experimental C++ body and does not depend on stacked #285.

## Layout and bounded interface

The original LaunchDol at `0x8042E8C4` reads its image base from context
offset `0x104`. Relative to that base, it accesses seven text file offsets at
`0x00`, eleven data file offsets at `0x1C`, their destination arrays at
`0x48`/`0x64`, their size arrays at `0x90`/`0xAC`, BSS address/size at
`0xD8`/`0xDC`, and the entry code pointer at `0xE0`. The copy loops add file
offsets to the image base. `DolImageHeader` is a descriptive binary-interface
view, not a recovered original type name. Its target-ABI assertions check all
these offsets and the view's `0xE4` size; the remaining DOL header padding is
not represented. It does not establish a portable host layout or allocate data.

`fn_8042EBA4` at `0x8042EBA4` stores the image address in that context field
and calls LaunchDol. Its existing shared API still accepts an `s32` address
word. `launch_switcher_dol` at `0x8007F970` passes the resource buffer address
it gave to `read_disc_file`; that legacy boundary remains unchanged. The
conversion to the header pointer is explicit at the context store. No cast
changes the entry-function ABI or hides an incompatible function declaration.

The three direct users of `ModemLaunchContext.h` on this baseline are
`text_8042EAD4.cpp`, `text_8042EE4C.cpp` and `text_8042E9FC.cpp`. The latter
two use other launch-record views and do not dereference the image field.
The switcher caller's declarations and implementation are unchanged. The
volatile context-pointer slot retains its existing qualifier and accesses.

## Transfer and ownership limits

This candidate leaves `text_8042E8C4.cpp`, compiler settings, exceptions,
symbols, splits, retention and linked-unit lists identical to main. In
particular, it does not change the generated assembly loader, recover a new
function or claim additional matching bytes. The unresolved nonlinking LR
transfer and #285's `0x8042E9FC..0x8042EA0F` stranded-epilogue range stay
outside this change. An independently reviewable layout improvement does not
resolve either hold.

## Available provenance

A read-only inventory of the original-input tree and the retail disc's 3,562
named filesystem entries found no ntUtl-named file or original object,
archive, linker map or C/C++ source file. The extracted tree is partial;
opaque nested containers were not searched for undocumented contents. Other
disc executables were inventoried without extracting or disassembling them.
This bounds the search and does not prove such artifacts never existed.

The original `PsoV3.dol` contains the ntUtl version marker
`ntUtl Ver 1.16.00 Build:Jul  8 2002 11:37:47` at file offset `0x474341`
(VMA `0x80480241`). It authenticates that embedded marker, not a compiler,
original source spelling or source-reachable transfer facility.

The available split objects and their `.note.split`/`.comment` sections come
from DTK; both project configs set `mw_comment_version: 10`. Recompiled probe
objects, reconstructed ELFs and linker-generated `.MAP` files are reproduction
evidence, not original ntUtl build artifacts. The installed GC/2.6 executable
has SHA-1 `1110a7a9924a09a608967efdf79ecf09900344e7`, which identifies the
tested compiler but does not authenticate its historical use for ntUtl.
Public compiler reconstructions and external SDK decompilations also do not
authenticate PSO's original source. This inventory supplies no new admissible
transfer route and changes no transfer hold.
