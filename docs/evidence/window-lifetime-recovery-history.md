# Window lifetime recovery history

The [balloon lifetime recovery](balloon-native-lifetime.md) retired
the final raw call and removed `WindowConstructorAbi.h`. Its native destructor
automatically destroys the Addition base. For the original hidden deleting
flags and storage ownership, see
[the window lifetime evidence](window-native-lifetime.md).

The Soft keyboard moved to native lifetime after the
[draw-context split](window-soft-native-destruction.md).
The Hard keyboard merged the original keyboard unit through `0x80260450`.
The ChallengeResult, DD selection, ScrollBar, Word and ComCard follower
recoveries are recorded in [§5](../porting-exceptions.md#window-native-lifetime-emission-deferred-codegen).
Earlier recoveries follow.

The [task ownership follow-up](window-task-owner.md) replaces four
more raw factory calls with ordinary construction and removes their bindings
plus an unused information-window declaration. It removed the raw
constructors for Deposit, DuelResult, SubMagPhoton and MessageInfomation.

[Message descendant recovery](window-message-descendants.md) moves
Page, Quest, and Scroll to native construction. The subsequent
[Log follow-up](window-log-scroll-lifetime.md) resolves its native
constructor difference and removes the final Message constructor binding.
Its auxiliary plain-storage constructor is also native; the counter/release
protocol remains type-erased where a positive producer is still unknown.

[Native Base cleanup](window-base-cleanup.md) removes Deposit,
LockOn, and Photon from the raw destructor interface. Their constructor,
destructor, and render chains are native, with compiler-generated tables and
evidence-backed descriptor ownership. Other raw-storage callers remain.

[ChoiceSetting lifetime recovery](window-choice-lifetime.md) removes
one more raw Addition construction/cleanup pair. Both factories construct the
actual owners, with explicit position/count forwarding and compiler-owned
tables. The existing auxiliary release protocol remains type-erased because
no positive producer for field `0x7C` has been established.

[Equipment-window lifetime recovery](window-equipment-lifetime.md)
removes two MenuIconLine construction/cleanup pairs. Native word-client
constructors narrow at the base initializer; Kind's factory forwards the same
word contract. Two compiler-owned five-function tables replace original inputs.
The remaining lifetime interface and unrelated unknown ownership holds persist.

[ShortCut/page-indicator lifetime recovery](window-shortcut-page-lifetime.md)
removes another MenuIconLine construction/cleanup pair and six auxiliary raw
initializers. The shared plain indicator and typed release interface replace
false window ownership; its byte parameters reflect all observed caller
contracts. Remaining prefix interfaces and unrelated unknown ownership retain
their holds.

[Remaining MenuIconLine descendant recovery](window-item-list-lifetime.md)
removes all remaining raw MenuIconLine construction/cleanup calls and its
three bindings. At that checkpoint four Base and Addition entries remained. Native word carriers, explicit heading
forwarding, source-claim refinement and original remainder provenance are
qualified in the note; broader unresolved interfaces retain their holds.

[Numeric-readout lifetime recovery](window-numeric-readout-lifetime.md)
removes two more Base construction/cleanup pairs. Meseta/Cost/Quantity use
real construction, actual float scale fields and shared typed factory/update
interfaces. Existing word handles/text transport remain qualified; the
pre-existing Meseta factory scheduling control is unchanged. No new compiler
control or alignment override is introduced.

[Timer/UserSort lifetime recovery](window-timer-user-sort-lifetime.md)
removes two more Base construction/cleanup pairs. Native constructors,
automatic cleanup, virtual methods and actual allocation producers own two
naturally aligned compiler tables. The tab helper's sole receiver/context
contract supports the reconstructed member; broader Timer and entry-prefix
attributions remain qualified. No new compiler control is introduced.

[BreakIn lifetime recovery](window-break-in-lifetime.md) removes
another raw Base construction/cleanup pair. The Base-only window uses
native construction, automatic cleanup and its actual allocation producer;
its descriptor and compiler table emit with natural alignment. The zero
tail remains linker padding. No new compiler control is introduced, and
broader entry/position ownership remains qualified.

[SymbolChatHelp lifetime recovery](window-symbol-help-lifetime.md)
removes another raw Base construction/cleanup pair. Native lifetime and four
allocation producers use borrowed byte/word pointers; six helpers receive
the actual Help owner. Signed flag storage preserves the observed low-bit
contract with existing explicit byte conversions; original signedness is
qualified. Descriptor/table emission is natural, and the trailing original
word is retained. No new compiler control is introduced.

[Room/Area lifetime recovery](window-room-area-lifetime.md) removes
another raw Base construction/cleanup pair. True inheritance replaces flat
images and an allocator adapter; actual producers use ordinary new. The
existing two-float copy export retains its qualified legacy ABI and historical
name, with no wrapper or invented object owner. The existing queue-destruction
entry avoids duplicate inline emission. No new compiler control is introduced.

[SoundBalance lifetime recovery](window-sound-balance-lifetime.md)
removes another raw Base construction/cleanup pair. Actual draw-context and
borrowed settings views accompany explicit entry-word/text argument forwarding.
The historical entry getter ownership stays qualified. Existing scoped render
CSE and constructor FP controls remain; no new compiler control is introduced.
The original data suffix is retained rather than assigned as padding.

[FaceType lifetime recovery](window-face-type-lifetime.md) removes
another raw Base construction/cleanup pair. Actual window construction and
borrowed selection coexist with an explicitly opaque heading lifecycle; its
legacy child protocol is preserved rather than assigned a speculative class.
Descriptor/key-function organization is qualified without an original TU
claim. Native table emission and the existing Help alignment reproduce the
tail, with no new compiler control or manual padding.

[ChallengeResult interface follow-up](window-challenge-result-interface.md)
recovers float fields and explicit numeric-entry forwarding. The native lifetime
probe is not activated: constructor pooling and producer register differences
remain measured blockers, alongside upstream return-contract holds. Existing
string/section controls and manual-table/raw-lifetime debt remain; no new
compiler control or matching exception is introduced.

[CustomEquip lifetime recovery](window-custom-equip-lifetime.md)
removes another raw Base construction/cleanup pair. Its opaque heading protocol
remains qualified. The out-of-extent selection helper moves to the evidenced
CustomSelect receiver with pointer transport; that class's lifetime/early-return
hold remains. Descriptor/table emission is natural and the opaque original
suffix is retained. No compiler control or manual padding is introduced.

[LoadItemTexture lifetime recovery](window-load-item-texture-lifetime.md)
removes another raw Base construction/cleanup pair and recovers the actual
request/bind receivers. Loader destruction remains deferred; the texture list
is borrowed. The factory's existing CSE/FP scopes and upstream word interfaces
remain qualified. Descriptor and compiler table are native, with the opaque
original suffix retained and no new compiler control or manual padding.

[AreaMapDisp lifetime recovery](window-area-map-lifetime.md) removes
another raw Base pair, retaining the owned character-storage allocation/release
protocol and opaque heading ownership. Existing word/string-copy, draw-context
and boolean-result ABI views remain held after measured canonical probes.
CallBack is deferred pending its full callback contract. Native descriptor/table
emission preserves the original suffix without new controls or manual padding;
this does not claim portable interface completion.

[QuestBoardSelect lifetime recovery](window-quest-board-select-lifetime.md)
removes another raw Base pair and closes constructor text-width, slot-update
and render receiver forwarding. Its opaque heading and wider entry/controller
qualifications remain. The constructor's existing FP-contract scope stays;
no new control, manual table or padding is introduced. Native data emission
retains the original entry prefix and following table/tail suffix.

[ShortCut window lifetime recovery](window-shortcut-window-lifetime.md)
removes another raw Base pair, retaining deferred child close and opaque
heading release. The 1,044-byte setup helper remains original input under its
qualified machine ABI, with broader record/child interfaces held. Native
descriptor/table emission preserves original entry and following table/tail
inputs without new controls or manual padding.

[Status-family lifetime recovery](window-status-family-lifetime.md)
removes SimpleStatus's raw Base pair and the derived raw SimpleStatus chains.
Word contracts and genuine factories are shared; existing FP/string/propagation
controls remain. The original five-slot refresh versus four-slot destructor
asymmetry stays explicit and unresolved. Three native descriptor/table claims
refine original data with two qualified natural alignment gaps; no compiler
control, padding definition or manual table is added.

The later [accepted-main Parts integration](window-parts-accepted-main-integration.md)
supersedes the historical export/provider blocker in the following checkpoint;
original compiler-control provenance and portable interfaces remain qualified.

[SymbolChatParts compiled lifetime checkpoint](window-symbol-parts-lifetime.md)
removes a raw Addition pair from the matching source, retaining the generic
Scroll/opaque heading protocols. Actual executable input remains original:
the own 32.0f external reference blocks constant localization, and literal,
normal definition and actual-member probes did not establish a matching source
link. No section control, padding or alternate binding is introduced. This is
compiled-source progress without a claimed executable source-link gain.

[HelpItem layout prerequisites](window-help-item-layout.md) remove
misleading entry-field aliases from the legacy window image and qualify their
separate prefix views. Descriptor identity, page ownership and opaque callback
storage are explicit. Native inheritance/table activation remains held on the
measured constructor scheduling difference. No new compiler control, manual
vptr assignment, callback signature or lifetime exception is introduced.
