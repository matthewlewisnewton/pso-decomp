# Shared render-state and raw vertex-reset contracts

This follows PR #268 checkpoint `8382613545629686941fc963fbd1b07e31ac2131`.
Two render-state helpers now have consistent shared no-argument declarations.
The vertex reset has one explicit raw-storage ABI instead of incompatible window
member and caller-local declarations. Complete affected objects retain their
bytes, targets and providers. This removes two reconstruction barriers without
making the held DD renderer exact or activating another source unit.

## Active original callers and history

Independent scans of all 4,976 objects in the active original configuration find
six begin_render references, eight render_forward references and five reset
references. All are direct zero-addend text calls, with no address-taking or
other-section reference. Stale objects outside that inventory are excluded.

The shared no-argument state change was previously made in commit
`6b0339802a3e5569c8692ee56d6fa52bbd8c6e40`. The later
`9d6e74916785a263fc7c8b5e94a6eed7d92a7d95` restored a broad window snapshot for
merge coherence; it does not document an isolated failure of those contracts.
The current repair covers today's callers and providers rather than restoring
that historical snapshot.

## No incoming render-state argument

At 800FC400, begin_render replaces incoming r3 with localized_alphabet_list and
calls the texture-list setter. It never reads an incoming argument. The forward
helper at 800FC3E0 only calls it. Original callers leave heterogeneous residue
in r3, not a single supported context value.

Both helpers and all current source callers now use the same no-argument shared
static declarations. The corresponding catalog names use Fv. The eight forward
calls and existing direct calls use those members, replacing local C views;
Language's already-stored alphabet value is no longer passed as an unused input.
The 32-byte wrapper and 36-byte selector remain byte-exact. Their historical
TWindowSubStatusDisp naming does not establish window ownership.

The separate end_render_forward, begin_screen_draw and other state/ownership
interfaces are unchanged and retain their qualifications. No new return-value
view of a preceding void helper is used to explain residual r3.

## Explicit raw reset inputs

At 803403F8 the reset initializes eight 24-byte records in destination r3, using
depth from f1 at each record's +8. It overwrites r4 with -1 before writing the
color words. All five original callers explicitly supply r4=-1 immediately after
the float-returning depth helper. Incoming r4 has no behavioral effect, but its
consistent caller setup is preserved as an explicitly unused ABI word.

WindowVertexBufferAbi.h gives the historical C export one shared void declaration
with raw destination storage, unused word and float depth. The definition has
the same signature. The false TWindowDD member declaration is removed; no complete
native buffer class or TWindowDD receiver is asserted. The word is not named as
color, count or a recovered semantic flag. Its signedness and unique historical
source argument order cannot be inferred from a constant and two register banks;
the existing signed-word transport is retained.

The selected WS_String draw caller explicitly forwards the depth result instead
of relying on live f1 through a declaration that omitted it. Its 192-byte storage
extent and -1 word remain unchanged. No caller consumes a reset result, and the
52-byte callee's existing void behavior is retained. No wrapper or alternate
mangled export is introduced.

## Complete affected objects

All thirteen compiled texts are unchanged from 838. Every resolved text/data
target, allocated section header, flags, size, alignment and constant payload
is also unchanged:

| Unit | Text bytes | Selected provider |
| --- | ---: | --- |
| TWindowSubStatusDisp_800FC3E0 | 896 | Source |
| TWindowSubStatusDisp_800FBD74 | 1624 | Source |
| TWindowFukidasi | 10712 | Original; compiled reconstruction held |
| TKeyBoardControl | 9096 | Source |
| TWindowSubStatusDisp_8024FBA8 | 1380 | Source |
| TWindowSubStatusDisp_8025995C | 1108 | Source |
| TWindowMainMenu_802AD538 | 4600 | Source |
| TWindowSubSymbolChatHelp | 2408 | Source |
| TFontSmallTask | 2756 | Source |
| TLanguage_80132A5C | 1140 | Source |
| TWindowDD | 1244 | Original 2736-byte text |
| TWindowDD_803488A8 | 844 | Source |
| TWindowDD_80341A08 | 2496 | Original 3412-byte text |

Each selected source or retained original occurs exactly once in actual link
inputs. The ten selected complete source texts and text targets match original.
The three held compiled objects remain absent from executable inputs. No source
activation, split, layout, data/table claim or compiler control changes.

## Bounded renderer result and remaining holds

One fresh reconstruction of the missing 608-byte DD renderer used these shared
contracts, with no other organization, type or control change. It remains 608
bytes but differs in 37 aligned instruction words, down from 79. The reset word
setup and no-argument state call match original; residual register and instruction
order differences remain. All 17 prior functions and existing data were unchanged.
The probe is retained privately and the contract-only source is restored. No
renderer exactness or coverage gain is claimed; the result does not justify
local-variable or declaration permutations.

The full gated build retains DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Incremental check_pr passes with two
catalog renames and zero metric or coverage delta; the separately built main
`4bec40d6cca74a85e91c848ea2d9f25425a313ad` comparison also passes. Retention is
clean at 17,904. Port inventory passes after only five existing line locations
are refreshed, with no new control or exception.

DD's original 2736-byte provider remains selected, with the independent 884-byte
renderer still absent. Word's original 3412-byte provider and fused-arithmetic
hold, nameplate's 139-word difference and original provider, CustomSelect's
partial-initialization safety, callbacks, constants, ownership and protected
remainders retain their holds. The raw window ABI inventory remains 18 calls
across ten units and three bindings. The PR stays draft.
