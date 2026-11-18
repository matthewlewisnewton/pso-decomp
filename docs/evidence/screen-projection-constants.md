# Screen and projection constants

Base: fork main `2344b179717a97c9604db931189ad6d7dc6a9cc8`.

`ScreenProjectionConstants.cpp` recovers all twenty scalar objects in the
existing original-only `auto_11_805D93C0_sdata2` range,
`0x805D93C0..0x805D9410`. The range and every exported identity stay intact.
The descriptive filename identifies the observed consumers; the original
source filename and historical translation-unit boundary remain unresolved.
This is an 80-byte data-only recovery and adds no function matches.

## Consumer evidence

A census of all 8,679 configured original and compiled objects finds six
consumer units. Their original objects contain 70 references to these
symbols, all `lfs` loads:

| Consumer | Original references |
| --- | ---: |
| `pso/unk/text_80082C30.cpp` | 18 |
| `pso/misc/TCameraCtrl_80082FCC.cpp` | 16 |
| `pso/player/TObjPlayer_80083360.cpp` | 1 |
| `pso/player/TObjPlayer_80083594.cpp` | 6 |
| `pso/misc/TScene_800838C4.cpp` | 4 |
| `pso/player/TObjPlayer_80083B38.cpp` | 25 |

At `0x80082C30`, the first eight values build a textured screen rectangle.
`copy_screen_to_texture` uses its dimensions and offsets. The helper at
`0x80082FCC` converts screen coordinates with the following six constants.
Viewport setup reads 640 and 480; perspective setup reads 1.1333334.
The existing address labels are retained because their original names are
unknown. All six complete compiled consumer objects remain byte-identical
to the fresh baseline, including symbols and relocations.

## C and C++ comparison

With stock game GC/2.0 flags, handwritten externally linked `const f32`
definitions in both C and C++ emit exactly 80 bytes of `.sdata2` with
alignment eight. Every scalar occupies four bytes at its original offset;
all twenty global object bindings agree. There are no runtime relocations.
The plain C++ `const` control has internal linkage and emits no allocated
section because none of its objects is used locally. The final source uses
explicit `extern` definitions inside the existing consumers' C linkage.

The fork's [Mylla](photon-mylla-constant-pool.md) and
[laser-light](laser-light-constant-pool.md) investigations distinguish
private literal emission from exported constant storage and show that
instruction matches alone do not establish pool layout. Upstream commit
`9925c2c503` folds `0x80082C30..0x80084864` and a larger constant range into
`pso/player/TObjPlayer_80083594.cpp`, using ordinary literals. Its ownership
arrangement differs from this fork's six consumers. Here, separate ordinary
external definitions preserve their exports and existing data boundary,
without changing consumer expressions or compiler settings. No source is
copied from upstream.

## Validation

The fresh unchanged-main build and retention check pass. The final native
build and `tools/check_pr.py` pass against that baseline. Original and
rebuilt DOL SHA-1 are `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

The complete unit scores 100%; allocated bytes, section size/alignment,
exported symbol sizes, bindings and offsets match. Generated linker inputs
select its compiled object and omit its original fallback. Matched data
increases from 1,506,652 to 1,506,732 bytes; source-linked data increases
from 1,504,804 to 1,504,884 bytes; linked units increase from 3,615 to 3,616.
All function, code and total data coverage is preserved. The 20,396-name
retention block has no drift. GCC C++98 syntax and whitespace checks pass.
No compiler override, pragma, intrinsic or assembly is introduced.
