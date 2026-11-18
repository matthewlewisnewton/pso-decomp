# Loading particle distance constant

Base: fork main `7ebf37b813`.

The entire fallback unit `auto_11_805D7EC0_sdata2` contains a single
`65.0f` scalar followed by four zero alignment bytes. Original relocations
from `TNowLoading::run_task` (`0x8001D19C`) and its constructor
(`0x8001D3A8`) load that scalar for the camera-direction multiply-adds
that position the loading particles. The existing `TNowLoading.cpp` owns
both functions. Assigning the scalar to that unit removes the fallback;
this establishes a supported data owner, not the original source filename.

The first experiment defined the existing extern before the functions.
GC/2.6 retained all nine exact functions but emitted two copies of `65.0f`,
giving a 75% data match for the eight-byte pool. Following the late-definition
arrangement in [bridge constant ownership](bridge-item-light-constant-pool.md)
and [Dark Falz demo linkage](dfdemo0-native-linkage.md) avoided the duplicate,
but emitted the named object in `.sdata` under this unit's existing immediate
compilation settings, with both C and C++ linkage.

Ordinary float literals, as in [laser-light constant ownership](laser-light-constant-pool.md),
emit exactly the required four-byte `.sdata2` scalar and retain every instruction.
The split ends at `0x805D7EC4`; the next unit begins at `0x805D7EC8`.
Correct the old eight-byte symbol extent to four and leave the trailing bytes
as linker alignment padding, without an explicit padding object. A census of
all 8,563 current configured original and compiled objects finds no undefined
reference requiring this private symbol to remain global; the symbol is localized
with `localize_split_globals.py` after the exact-object scan.

The completed owner has nine exact functions, 1,288 code bytes and 28 data bytes.
All allocated runtime sections match in bytes, sizes and alignment: `.text`
1,288/4, `.data` 24/8 and `.sdata2` 4/8. All 64 runtime relocation tuples
match after resolving defined targets to section offsets and retaining external
names and addends. No compiler setting, assembly or porting exception is added.

The baseline and final native builds pass. The linker input list selects
`src/pso/misc/TNowLoading.o` and has no original loading-unit or pool fallback.
`tools/check_pr.py` passes: matched and source-linked data each increase by four
bytes, with no function, code, data or linked-unit regression. Its only coverage
removal is the four zero alignment bytes, recreated by the linker. The entire
fallback pool disappears from the active configured inventory. The rebuilt DOL
retains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`; generated retention metadata
and the 3,616-unit source linkset remain unchanged. Existing provisional loading
interfaces are outside this constant-ownership change.
