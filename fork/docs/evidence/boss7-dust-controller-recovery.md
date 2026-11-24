# Boss 7 dust controller recovery

Initial recovery base: fork main `cc00aff353b847cb6711db83d695b27fb1582508`.
Final integration base: fork main `84420bea523b79b3e2daf384b26fb1211560e0be`.

The existing `pso/boss/TObjBoss7DustCtrl.cpp` unit spans
`0x802F1200..0x802F15D4`: eight already matched and source-linked functions,
980 code bytes, and 1,184 data bytes. This change recovers its native C++
lifecycle and private scalar pool; it adds no function or code matches.

## Lifecycle and particle storage

The factory allocates 0x1C bytes and passes `tl_05` as the parent. The
constructor calls `TObject(TObject *)`, installs the compiler-owned vtable,
and assigns the existing class-name pointer. A real constructor and `new`
produce the same instructions as the old manual constructor and casted
function-pointer call. The class adds no fields to `TObject`.

The update transforms six 12-byte points into each of ten strips. Each
output record has a `Vec` followed by the ARGB word at +0xC; the transform
writes only its position. Initialization supplies color `0xFF709070`.
The two rotation angles per strip are twenty consecutive signed words;
a flat array permits their existing traversal without walking beyond a
single struct member. The ten phase angles remain a separate array.

The entry at `0x802F125C` returns the old ring index in r3 and advances the
stored index modulo ten. The dust constructor consumes that result, so its
old `void` declaration was inaccurate. Provisional helper names are retained.

## Compiler comparisons

The first native constructor implementation matched immediately. Replacing
the fake vertex records and local matrix declarations with `Vec`, typed
position/color records and the shared matrix APIs retained all update code.
Removing the unused float argument from the cosine call initially changed
only integer register allocation in the initializer (99.114586%).

The [indirect-scroll investigation](indirect-scroll-offset-propagation.md)
and [character-select investigation](chr-select-confirm-cell-store.md)
describe declaration scope and typed-expression effects. Function-scope
angle/index variants scored 99.322914% and 99.791664%; independent loop
indices with the angle declared before the first loop reproduce all
initializer instructions. Both the original and equivalent increment-in-
`for` render-loop forms were compared. No new compiler setting is needed.
The inherited `opt_propagation off` pragma is unnecessary and is removed.

## Rendering boundary

`0x803DF578` forwards r3 as a vertex buffer and r4 as its count to the
untextured strip routine; r5 selects the existing camera setup. It never
reads a player field. Its six calls in five units supply vertex buffers,
including these dust vertices, rather than `TObjPlayer` objects. The shared
free `draw_trail_strip` declaration replaces the false member interface in
all of those source callers.

The lower routine at `0x803DF5E4` reads three floats and one color word per
vertex, and neither routine retains the buffer. The buffer remains `void *`
at this boundary because existing callers use several record/overlay types;
this does not establish their C++ object lifetimes. A mutable pointer and
an `int` count retain the original four-vertex unrolling. Const-buffer,
long-count, unsigned-count, indexed-loop and while/do-loop probes differed.
The lower routine uses a signed-long remaining count internally. These
ordinary parameter types preserve both routines without an added pragma.
All direct callers use the shared declarations; no actor cast is needed.

## Scalar ownership

As in the [laser-light pool](laser-light-constant-pool.md) and
[Mylla pool](photon-mylla-constant-pool.md), literals emit the private
constants in native order:

| Address | Value | Use |
| --- | --- | --- |
| `805DEC70` | 0 | Translation and output reset |
| `805DEC74` | 6 | Vertical oscillation amplitude |
| `805DEC78` | 65536 / 6 | Helix point angle step |
| `805DEC7C` | 0.7 | Helix radius |
| `805DEC80` | 1 / 12 | Helix point height step |

The split claims exactly `0x805DEC70..0x805DEC84`. The old final eight-byte
symbol contains one loaded float and four bytes of alignment; its extent
is corrected to four. The following pool starts at `0x805DEC88` with eight-
byte alignment, so native linker alignment recreates the tail without a
padding object. This assignment describes observed ownership, not a
recovered historical filename. The localization tool checks the complete
fresh configured original/compiled consumer inventory before marking the
five private labels local.

## Validation

The unchanged base was built and passed the generated-retention check
before edits. The final unit has eight exact functions (980 code bytes)
and 1,204 exact data bytes. Its allocated section bytes, sizes and alignments
match the fresh split object, as do all 50 normalized relocation tuples.
The compiler marks `.sdata2` with ELF flags 3 where the extracted object
uses 2, the existing CodeWarrior constant-section convention; the payload,
alignment and linked DOL remain exact. The linker selects the compiled
controller object for the expanded range.

The full DOL retains SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Address-based comparison adds 20 matched and source-linked data bytes,
loses no exact functions, code or live data, and identifies only the four
zero alignment bytes at `0x805DEC84` leaving coverage. The number of
linked units is unchanged; the unit was already linked before recovery.
