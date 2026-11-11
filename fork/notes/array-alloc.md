# array-alloc

Renamed `mem_alloc` (0x80147AA8) to `operator new[](size_t)` (`__nwa__FUl`) and `mem_free` (0x80147A80) to `operator delete[](void *)` (`__dla__FPv`). Addresses and names confirmed against symbols.txt and naming-three-way.tsv; upstream had no existing `__nwa__FUl`/`__dla__FPv`.

- New header include/pso/system/ArrayAllocation.h (from the fork). Per-file `mem_alloc`/`mem_free` declarations removed (~224, incl. TOBoss4Rock.h); the definitions in TOBoss4Rock.cpp are now `operator new[]`/`operator delete[]`.
- Call sites: `::operator new[](N)` / `::operator delete[](P)`. Where the old local declaration returned `s32`/`u8 *`/etc. or took `int`, a cast on the result / `(void *)` on the argument was added.
- No `.c` files reference either name. No config file referenced them (only symbols.txt).
- libs/.../NMWException.cp: `__destroy_new_array` called `extern "C" mem_free`; now `::operator delete[]`. It does NOT include ArrayAllocation.h (the runtime cflags have no `-i include`); the operator is implicitly declared and compiles fine. The fork did the same.
- Call sites with no/extra arguments (old decls `s32 mem_alloc();` and `mem_alloc(u32, s32)`):
  - TWindowSubComCard_80131BC4 and TWindowSnapShot_802A5B2C called `mem_alloc()` with no argument, relying on r3 still holding the previous call's result. Now `size = measure_text_overflow()/get_buffer_size(); operator new[](size)`; same code.
  - TTecMegid passed an extra second argument; dropped (matches).
- TWindowSubStatusDisp_80257BC0 `replace_owned_string`: `mem_alloc(n + 1)` became `operator new[](n + 1U)`; plain `n + 1` (signed to size_t) stopped sharing `n + 1` with the strncpy argument (93%). `1U`, `(s32)(n+1)` and `(u32)n + 1` all give 100%.
- Pitfall for scripted edits: a declaration-removal regex that allows leading whitespace also deletes indented call statements like `mem_free(x);`. Declarations must be matched from column 0.
- Comment in TBoss7DeRolLeC.h reworded ("mem_alloc'd" -> "allocated").
- Left on purpose: the symbol names inside the generated build/ asm only; nothing in src/include/config/libs references the old names.
