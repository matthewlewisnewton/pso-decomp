# Callback closure and remaining source-quality gates

Read-only checkpoint on `8602ea2b7f8cf4b5a1d87be620716761645c0fdd`.
No implementation, original provider or readiness change is made by this audit.
The [retained census](window-callback-reference-census.json) records the named
relocation edges found across 5,061 available original split objects. It is not
a whole-program points-to proof: raw addresses, computed access, runtime mutation
and objects outside that inventory are not excluded.

## The previously dynamic callback path has two concrete producers

| Boundary | Observed original references |
| --- | --- |
| Callback factory | Six direct zero-addend calls |
| SubSymbolChat callback-forwarding wrapper | Two direct zero-addend calls |
| Callback constructor | One direct call, from the factory |
| Callback field setter | One direct call, from that constructor |
| SubSymbolChat close_child target | One HA/LO registration pair |
| Character-select transition target | One HA/LO registration pair |

Five factory calls install fixed targets: Agreement text, Ep3 message, serial
screen, password screen and player status. The sixth forwards its argument
through SubSymbolChat's wrapper. That wrapper's two original callers each supply
a fixed function address: SubSymbolChat close_child and character-selection
update_transition_anim_if_active. Thus the named relocation-backed producer graph
has seven observed target functions, not an unidentified dynamic producer.

The first five implementations now accept window/context explicitly. Dispatch
passes the Base-derived CallBack window in r3 and draw_default_entry's result
in r4; all five consume these at their frame calls. The two remaining targets
instead reload a singleton/global, null-test it and invoke its target operation.
Their inspected original bodies do not consume incoming r3/r4. This establishes
an ignore-both-arguments execution contract for those two known callback targets,
not compatibility of the current no-argument C++ function-pointer types.

This closes the **unidentified producer in this inspected graph** prerequisite.
It does not close the mixed callback ABI hold: storage still uses
`void (*)(TWindowCallBack*, s32)`, five targets use `void(void*,void*)`, two use
`void()`, and factory/constructor/setter transport a function address through
object-pointer/integer views. A safe next source-validation step is one atomic
shared callback contract across these seven targets, both wrapper callers,
factory, constructor, setter and invocation. The two global-mediated callbacks
must explicitly accept and ignore the two arguments, without an adapter that
changes code or silently preserving incompatible function-pointer calls.
Native mangling/catalog/retention changes must be derived from actual declarations;
whole-object relocation and no-loss checks must include every producer/consumer.
The closure census makes this a bounded experiment, not permission to assume
unknown runtime paths are impossible.

## Closing a window is not a destruction or dispatch barrier

Original Base close at 80244A14 calls request_close then sets bit 0x10 in the
**window** flags at +0x2C. request_close updates those phase flags, possibly calls
a sound helper, and does not directly clear the callback or disable rendering.
TObject render_nodes checks DISALLOW_RENDER in the separate **object** flags;
render_deferred_nodes checks its deferred-render bit. Neither operation tests the
Base close-request bit at +0x2C. CallBack render itself tests its callback pointer,
not that close flag. These are distinct flag words even where bit values coincide.

Consequently, "the owner called close" is insufficient evidence that there can
be no later callback. The two global-mediated callbacks do not capture their
producer task pointer; teardown closes the stored window and clears the global.
That excludes treating their callback field as an owning/captured task pointer,
but does not prove generation identity if a replacement task repopulates the
global before an old window retires, or rule out reentrant dispatch.

To retire the corresponding deferred-lifetime hold, follow an actual owner-close
origin through window phase advancement, destruction-enabled task traversal and
both render paths, including replacement/global-publication order. Either prove
old callback removal or dispatch suppression before the relevant replacement/
borrowed-resource release, or characterize the original cross-generation behavior
without inventing a safety guard. Full-layer teardown is already a bounded
control in the ComCard evidence; repeating that control does not prove all exits.

## Remaining gate chart (not a readiness checklist satisfied by CI)

| Family / gate | What is established | Still required |
| --- | --- | --- |
| CallBack common ABI | Seven named targets and explicit frame inputs; native window lifetime | Atomic compatible function-pointer transport/invocation, then separate deferred/global-generation evidence |
| Soft keyboard | Native destruction and compiler 24-byte table | Borrowed composer/PMF receiver and lifetime contracts; do not reopen solved native table work |
| Hard keyboard | Real composer and input/query/countdown receivers | Original-grounded native destructor/table provider ordering and shared borrowed/PMF interfaces; no repeated trailing-word census |
| Word | Existing renderer/provider and compiler-context controls | Word-specific constructor/initializer/data-table order provenance or fully explained native source; analogy alone insufficient |
| ComCard / followers | Native base construction, actual close origins, bounded full teardown | Conversion-pool/native follower source, trailing-word/table ownership and actual phase/borrowed-parent validity outside full teardown |
| CustomSelect | Client-generation, packet replay and reload/scene-exit controls | Partial-initialization/nonzero allocation qualification and legitimate-session notification/lifetime ordering |
| ChoiceSetting | Native lifetimes/tables and heading producer | Positive auxiliary +0x7C producer and task-global ownership; negative relocation census alone insufficient |
| Palette | Native destructor/table with qualified original data | Callback/tag lifetime, negative cleanup, first-record reset and unchecked-index/external contracts |
| Balloon / Parts / CMName / raw buffers | Existing provider and integration evidence | Remaining destruction ABI/order, compiler provenance, record capacity and external/capture interfaces as their family notes state |

All other explicit holds remain. A successful no-loss build validates execution
identity; it does not independently settle any row's source-quality requirements.

## Audit validation scope

Only these notes, the reference census and the review index change. No native
build or new metric gain is claimed. The retained executable still has SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`; production sources/configuration are
unchanged from the independently reviewed, validated 8602ea2 checkpoint.
