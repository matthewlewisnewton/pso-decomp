# Array allocation entry points

The entries at `0x80147AA8` and `0x80147A80` implement global array allocation
and deallocation. Their source signatures are `operator new[](size_t)` and
`operator delete[](void *)`; the target encodes those names as `__nwa__FUl` and
`__dla__FPv`. The allocation size and pointer are 32 bits on this target.

The runtime's `__destroy_new_array` calls the deallocator after removing its
16-byte array cookie. The Lobby character-slot path pairs an allocation of
`12 * 0x42C + 16` bytes with `__construct_new_array` and that destruction helper.
The two allocation bodies retain the original `xmalloc`/`xfree` calls, null
handling and instruction sequences. These relationships support the recovered
array-allocation ABI; they do not establish historical source spelling.

`pso/system/ArrayAllocation.h` supplies one declaration pair. Existing buffer
clients call the allocation functions directly and retain their raw-storage
behavior. Typed array construction requires a new expression and a separate
lifetime proof. Existing placement construction and scalar allocation/deletion
remain distinct operations.

Two callers now pass their preceding size getter's result explicitly. Megid's
allocator call uses its byte count; the old extra argument was a redundant
ordinary field read. String allocation converts its length to `size_t` before
adding the terminator. Pointer/integer carriers retain the target's existing
32-bit representation.

The symbol transition preserves both original entry addresses and extents.
Paired target-profile object comparisons preserve allocated section bytes and
layout, global exports, and physical relocation targets across the affected
consumer/header frontier. Compiler-local static and literal counters may change
names while retaining the same binding, type, extent, section location and
relocated address. Original call sites continue to target the same two entries.
Normal full-build, original-DOL and no-loss checks remain the integration gates.
