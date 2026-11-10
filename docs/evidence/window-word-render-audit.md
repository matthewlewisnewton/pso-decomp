# Word renderer audit and shared vertex-buffer extent

This follows PR #268 checkpoint `76695998f6e1571c73a18a5bde9d062523b5dec8`.
The audit targeted WS_Word's missing 916-byte renderer as a potential source-link
blocker. One ordinary reconstruction remains nonexact and is not published or
activated. The same audit found and fixes a concrete bounds defect in the
source-selected WS_String draw helper.

## Correct the raw local buffer extent

The local `Buf` in TWindowDD_803488A8.cpp declared 0xBC (188) bytes. Its reset
callee at 803403F8 writes eight records with a 24-byte stride. The last record's
color store covers offsets 188 through 191, four bytes beyond that declared
object. Extra space in the generated stack frame does not enlarge the source
object. The original WS_String draw frame is 240 bytes, with its buffer at
stack offset 8 and saved general registers beginning at offset 212.

`Buf` now declares 0xC0 (192) bytes, enough for all eight records including the
last color word. This is a raw storage extent correction, without a claim of
complete native vertex identity or portable storage aliasing. The helper's
existing call declarations and all compiler controls remain unchanged.

The first ordinary probe produces an object file identical in every byte to
the preceding compiled object. Its complete 844-byte text matches original,
including the 164-byte WS_String draw body and unchanged stack layout. Thus
section headers, data/constants, symbol records and relocations are unchanged,
not merely the instruction bytes. The source object remains selected once.

## Machine evidence for the missing Word renderer

The original 80341674 body uses the same 192-byte buffer as four pairs of
24-byte vertices. The reset helper stores depth from f1 at each record's +8,
initializes the coordinates and UVs, and assigns color -1 itself. It ignores
incoming r4; the original renderer nevertheless supplies r4=-1. Existing source
views disagree about that boundary, so no canonical helper signature is claimed.

The draw wrapper at 801E32E8 preserves the vertex pointer in r3, count in r4
and mode in r6. It forwards r5 to the texture selector, then forwards the saved
vertex/count/mode to draw_textured_vertices. That downstream implementation
consumes records with x, y, w, s, t and a color word at offsets 0, 4, 8, 12, 16
and 20. Its count controls GXBegin and the record loop. This supports the byte
extent; it does not establish that these historical methods belong to a window.

The Word renderer draws fractional boundary rows, whole rows and an optional
selection overlay using runtime window height, context scale and scroll values.
An ordinary reconstruction preserving those operations and all fourteen helper
calls in order compiled to 980 bytes against original 916: 188 aligned
instruction words differ over the common extent, with 64 additional bytes.
The original has ten fused multiply/add/subtract operations; this probe emitted
none. No new pragma, compiler flag, intrinsic, scheduling device or provider
change was used. The eight-byte conversion pool stayed identical, and all 24
previously compiled function bodies remained unchanged.

That candidate is retained privately as a failed probe, and the exact published
Word source was restored and rebuilt. No runtime operand proof establishes that
the separated arithmetic rounds identically. In particular, the bounded integer
argument used for balloon name centering does not apply to these runtime floats.
The actual Word build flags contain no explicit fp_contract setting; this result
is evidence about this probe, not a claim that every possible source must fail.

## Stop condition and remaining evidence

Another renderer probe needs a supported source/interface mechanism for the
observed fused operations under the allowed controls, plus exact object,
constant/relocation and complete-link validation. Runtime operand bounds could
help establish behavioral equivalence, but would not alone satisfy byte-exact
source linkage. Type/declaration permutations or moving the body into a
controlled region solely to influence output are not a supported next step.

WS_Word's complete original 3412-byte provider remains selected once; its
compiled 2496-byte source remains absent from executable inputs. The native
912-byte task and 52-byte offset helper retain their prior exactness. No Word
source-link, lifetime, table, constant or ownership hold is lifted.

For the buffer extent fix, the capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Both incremental and fresh-main
check_pr comparisons pass with zero new metric, rename or activation delta.
Retention is clean at 17,895 and port inventory passes. Main remains integrated
at `4bec40d6cca74a85e91c848ea2d9f25425a313ad`. The nameplate original-provider
hold and all other existing technical holds persist; the PR remains draft.


The later [shared state/reset recovery](window-render-state-reset-contracts.md) establishes the observed unused reset word and explicit float depth through one shared raw ABI, plus no-argument begin/forward state helpers. This supplies new contract evidence without resolving Word's fused arithmetic or changing its provider. One separate DD renderer probe remains nonexact by 37 words; no additional matching claim follows.
