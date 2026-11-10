# Native window construction and table ownership

This continues PR #268 from the validated shared-prefix checkpoint
`b3fa2a885cfba859c3ba2f63c286b01f65a0070c`, on main
`6daa19a11db97b1b8222fd2665eba485ed3a74a4`. The final integration normally
merges current main `9924ce113b5e6dff309a5ae94065265d3066fb24` in source
checkpoint `5982db6bdf235927cf18431ae75da4d9a873d6f0`.
It supersedes the integration
blockers in the [historical constructor probe](window-constructor-chain-probe.md).
The original draft hold remains pending disposition of the bounded legacy
interfaces below; exact matching alone does not establish complete portability.

## Constructor chains and client widths

The functions at `0x802466E0` and `0x80244448`, previously project-named
`TWindowDD::construct_base` and `TWindowAddition::construct_with_parent`, are
now actual Base and Addition constructors. Addition initializes Base directly;
Message initializes Addition directly. Their destructors perform ordinary
automatic base cleanup. There are no invented empty default constructors.
The full source compilation does not require them.

Base and Addition accept a short client. Message accepts a word, narrowing
at its observed base call. The former `fn_80268384` / `fn_802683F4` are native
`TWindowMenuIconLine` constructor overloads: each initializes Addition, then
calls `vfunc_6(count, client)`. Native construction preserves the original word
forwarding followed by sign extension for that virtual call. Both constructors
now reproduce the complete original 228-byte unit and its eight normalized
text relocations. The earlier 224-byte result measured C wrappers calling a
constructor alias; it did not establish the behavior of genuine derived
constructors. Wider Base/Addition parameters are unnecessary.

The old `TWindowMenuIconLine__ct` at `0x80267E88` is the ordinary virtual
initializer `vfunc_6(u32, s32)`. The function at `0x80268310`, previously named
`TWindowSubStatusDisp::destroy_item_list_resources`, is MenuIconLine's actual
destructor: it destroys the two owned fields before Addition cleanup. All six
existing raw derived cleanup callers use its canonical native destructor
entry point with base-cleanup flag zero.

Other affected edges now have real constructors, preserving observed argument
contracts rather than inventing wider aliases for short constructors:

| Class | Constructor arguments | Base initialization |
| --- | --- | --- |
| InputNumber | position, three words, short client | Base directly |
| Deposit | short client | Base directly |
| DuelResult | word client | narrow at Base call |
| LockOn | word client, unsigned-short target | narrow client at Base call |
| SubMagPhoton | word position, count, client | narrow client at Base call |
| MessageInfomation | word layout, word client | Message directly |

MenuIconLine, Message, MessageInfomation, and LockOn factories use ordinary `new`.
Remaining raw-storage initializers use the shared ABI interface described below.

## Fields and virtual table provenance

The [Addition prefix repair](window-addition-prefix.md) owns floats at offsets
`0x60` through `0x6C`; all eight direct descendant layouts remain unchanged.
InputNumber instead derives directly from Base: its input flags begin at
`0x60`, and its size remains `0x7C`. Compile-time size and offset assertions
cover its inherited client and retained fields. It now has native destruction,
rendering, and task dispatch.

DuelResult's descriptor at `0x804CEFAC` is a 20-byte layout descriptor, now
named `window_duel_result_descriptor`. It is distinct from the actual virtual
table at `0x804CF020`. Its two floats at `0x60/0x64` and controller word at
`0x68` preserve the `0x6C` image. Destructor, rendering, and task dispatch are
native members; the old manually written table and duplicate local class are
removed. The existing data split already owned this table.

The compiler emits the following tables in the unit owning the key destructor:

| Class | Original range | Owning source unit |
| --- | --- | --- |
| Base | `[804CE018,804CE030)` | `TWindowDD_8024662C` |
| Addition | `[804CDFE8,804CE000)` | `TWindowAddition` |
| Message | `[804D0730,804D0748)` | `TWindowMessage` |
| MenuIconLine | `[804D0618,804D0634)` | `TWindowSubStatusDisp_802671F0` |
| InputNumber | `[804CF900,804CF918)` | `TWindowInputNumber_80256170` |
| DuelResult | `[804CF020,804CF038)` | `TWindowDuelResult` |

The first five claims add 124 matched and linked data bytes. MenuIconLine has
five function slots and a 28-byte table, despite the former 32-byte catalog
entry. The original last word at `0x804D0634` is zero without a relocation;
the next symbol begins at `0x804D0638`. That four-byte tail remains in original
fallback input `auto_07_804D0634_data.o`, which the generated link inputs retain.
No additional virtual slot is invented to consume it. Constructors in
`text_80268384` reference the table; the destructor-owning unit emits it.

## Bounded native ABI interface

`WindowConstructorAbi.h` centralizes declarations of the actual MWCC-emitted
constructor/destructor entry points for remaining C-named raw-storage
initializers and destroyers. Arguments match the recovered native declarations;
there are no substitute wrapper definitions or alternate-width function-pointer
views of these constructors. LockOn's target is unsigned short throughout its
constructor, factory, binder, and controller calls. The borrowed word-typed
function-pointer view of the binder is removed. The old
word/word constructor plus narrow factory hid this inconsistency: a canonical
word call inserted a zero extension absent from the original. Coordinating the
unsigned-short target contract avoids concealing that mismatch with a cast.
The sole producer, `TObjPlayer::get_battle_ctrl_id`, now returns `u16` and
calls the real `TMainCursor::get_id()` rather than viewing it through a
word-returning function-pointer cast. Its three paths return either `0xFFFF`
or that cursor ID. The controller carries `u16` throughout. The existing
ordinary binder keeps its project-assigned C name and opaque raw receiver,
with one shared declaration; it is not claimed as a recovered member.

The raw destroyers pass the native hidden flag zero for base cleanup. An explicit
C++ destructor expression emits minus one instead; although both avoid freeing
storage, the latter changes these call sequences. Native recovered destructors
use automatic base destruction. The original deleting behavior remains owned by
the compiler-emitted destructor and `TObject::operator delete`.

This is a compiler ABI boundary, not a claim that all remaining raw-storage
functions have portable C++ lifetime semantics. The porting exception register
documents replacement with real constructors/destructors or placement
construction where an external owner supplies storage. No new assembly,
intrinsic, pragma, per-unit compiler override, or hand-written table is added.

The follow-up [task ownership correction](window-task-owner.md) resolves the
independent `TWindowDuelResult::init` anomaly at `0x801C2528`: it belongs to
the existing `TUnk_804C3E60`, with a 0x24-byte allocation, TObject parent,
native constructor/destructor, and its own compiler-generated table. The
false DuelResult declaration is removed. Four more factories use ordinary
`new`, reducing the constructor ABI interface from nine declarations to five.

## Qualification

Validation uses independent outputs with the pinned GC/2.6 compiler and existing
flags under the shared build lock. The original-DOL hash, address-based report
comparison, linked-unit checks, and retention inventory qualify the complete
integration, including unchanged callers. The initial raw-byte and normalized
relocation checks remain useful evidence for the core four units and both Menu
constructors; they do not replace whole-program qualification.

Against a fresh build of main `9924ce113`, exact functions increase from
27,368 to 27,369, matched code increases by 600 bytes, linked code by 728 bytes,
and matched and linked data by 124 bytes. All 3,575 source-linked units remain
exact (main has 3,574). There are zero function, address-coverage, data, or
linked-unit regressions. A separate address-based comparison against the
preceding published checkpoint also passes, including the intervening main
changes. The native lifetime work adds no matched code beyond the retained
GuildWarning recovery. The build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

`tools/check_pr.py --no-build --baseline <fresh-main-report>` passes, including
all linked-unit checks and clean retention metadata (17,581 listed symbols,
zero additions or stale entries). `tools/list_port_exceptions.py --check`
also passes after refreshing the inventory. Main's independently built baseline
passes its corresponding checks. Final source review is independent and
read-only; the accompanying documentation freeze does not change code or link
configuration.

The follow-up preserves these code and linked-unit results and adds another
24 matched/linked data bytes, for 148 versus main. Retention increases to
17,583 names with zero drift. The task ownership note records the incremental
qualification against the published constructor checkpoint.

The subsequent [message descendant recovery](window-message-descendants.md)
adds native Page, Quest, and Scroll construction plus Log destruction/table
ownership. It adds another 24 matched/linked data bytes, for 172 versus main,
with unchanged exact functions and linked units. At that checkpoint Log was
the sole caller of the Message constructor ABI binding, with a measured
four-instruction native mismatch; the follow-up below resolves it. Retention
was clean at 17,587 entries.

The next [Base cleanup recovery](window-base-cleanup.md) replaces Deposit,
LockOn, and Photon raw destruction/rendering with native members and owns
their compiler tables plus two typed descriptors. It adds 112 matched/linked
data bytes, for 284 versus main, with unchanged exact functions and linked
units. Retention is clean at 17,601 entries. No new alignment override or
compiler exception is used; the note qualifies both original zero tails.

The same note records integration with subsequent main `001c33d3f`: a fresh
main baseline and integrated build reproduce the original DOL hash, with
27,370 exact functions and 3,576 exact linked units in the PR. Its incremental
contributions remain unchanged; retention is clean at 17,607 entries.
The subsequent typed file-API main `6e880491f` is also normally merged and
qualified against a fresh baseline, preserving these results and main's types.

The [main-menu window recovery](window-main-menu-lifetime.md) subsequently
removes another raw Base construction/cleanup pair, with a consistent word
client contract and compiler-owned descriptor/table. It adds 44 matched and
linked data bytes while preserving code and exact linked units. The specific
task-global second-word audit is recorded in the task ownership note; it does
not assign that unreferenced word a source owner.

The subsequent [Log and auxiliary-storage recovery](window-log-scroll-lifetime.md)
resolves Log's four-instruction mismatch by removing a decompiler receiver
alias, replaces five raw auxiliary allocations with ordinary construction,
and removes the final Message constructor binding. The remaining interface
has four constructor and three destructor declarations. No matching or linked
metric changes. The auxiliary counter/release protocol remains type-erased
because one caller's positive producer is unknown.

The Log follow-up also records the normal integration and fresh baseline
qualification of main `fe6cdb141`, retaining all contributions with 27,384 exact
functions and 3,585 exact linked units. Retention is clean at 17,650 entries.

The [ChoiceSetting follow-up](window-choice-lifetime.md) recovers the native
position/count constructor chain, both factories, and automatic Addition/base
cleanup. It adds two 24-byte compiler-owned tables and removes one raw Addition
construction/cleanup pair. The unknown auxiliary producer and task-global
second word remain unclaimed.

The [equipment-window follow-up](window-equipment-lifetime.md) recovers the
native EquipKind/List constructor and cleanup chains plus both factories,
with a consistent word-client contract and two 28-byte compiler tables. It
removes four more raw ABI calls, preserving the remaining ownership holds.

The [ShortCut/page-indicator follow-up](window-shortcut-page-lifetime.md)
recovers the separate plain 12-byte allocation across all six construction
sites, then native ShortCutList construction/cleanup and its real static
factory. It removes two more raw ABI calls and adds a 28-byte compiler table,
while retaining the unresolved prefix and unrelated ownership boundaries.

The [remaining MenuIconLine descendant recovery](window-item-list-lifetime.md)
adds native SubItemList, CheckBox, D0948 and its EF4E0 derived window. It
recovers the remaining constructor/cleanup edges and removes all three
MenuIconLine ABI bindings. Only the Base/Addition constructor/destructor
interface remains; the note qualifies a newly linked source prefix and
untouched original remainder without asserting an original TU boundary.

The [numeric-readout recovery](window-numeric-readout-lifetime.md) adds native
Meseta/Cost/Quantity construction, automatic Base cleanup, evidenced float
scale pairs and coordinated factory/value-update interfaces. It removes
four more raw Base calls and owns two compiler tables plus Quantity
layout metadata without alignment overrides.

The [Timer/UserSort recovery](window-timer-user-sort-lifetime.md) adds native
construction, automatic Base cleanup and virtual methods for two bounded
one-word descendants. Their actual allocation producers and Timer's sole
tab-helper receiver/context contract are coordinated. Two naturally aligned
compiler tables add 48 bytes, removing four more raw Base calls while
preserving the original remainder and unrelated ownership/interface holds.

The Timer/UserSort checkpoint normally integrates main's network-runtime
recovery and README follow-up through `18207f986`, preserving its two new
exact functions and source-linked unit. Current qualification retains 27,386
exact functions, 3,587 exact linked units and clean retention at 17,712 names.

The [BreakIn recovery](window-break-in-lifetime.md) adds genuine no-argument
construction, automatic Base cleanup and its sole ordinary-new producer.
The evidenced descriptor and compiler table own 44 bytes with natural
alignment, removing one more raw Base construction/cleanup pair. The
original remainder and broader ownership/interface holds remain intact.

The [SymbolChatHelp recovery](window-symbol-help-lifetime.md) adds native
construction and automatic cleanup with four ordinary-new producers. Its
borrowed selection/mode/toggle pointers and six helpers now use the actual
Help receiver. Descriptor and compiler table own 44 bytes; the trailing
word stays in a verified original suffix, without a new padding claim.
Remaining ownership/interface holds and the original text remainder persist.

The Help checkpoint also normally integrates main's PPPoE recovery and
README follow-up through `224eb9983`, retaining its new exact function and
source-linked unit. Current qualification has 27,387 exact functions,
3,588 exact linked units and clean retention at 17,736 names.

The [Room/Area recovery](window-room-area-lifetime.md) replaces flat images
with the evidenced Base/Room inheritance, genuine construction, automatic
cleanup and all three ordinary-new allocation producers. Two compiler tables
add 48 bytes; Room's descriptor stays original. The position-copy and shared
entry interfaces retain explicit qualifications, along with all original
remainders and unrelated holds.

The [SoundBalance recovery](window-sound-balance-lifetime.md) adds genuine
position construction, automatic Base cleanup and its sole ordinary-new
producer. Entry/text argument forwarding is explicit, settings remain a
borrowed prefix, and rendering uses the actual draw-context view. Descriptor
and compiler table add 44 bytes while the original suffix and existing
compiler/interface qualifications remain intact.

The [FaceType recovery](window-face-type-lifetime.md) adds genuine window
construction/cleanup, native virtual methods and its sole ordinary-new
producer. Selection is borrowed; the owned 0x24-byte heading stays opaque
under its observed legacy initializer/release protocol. The class-associated
descriptor and compiler table add 44 bytes without inventing a child class
or original translation-unit identity. Standing holds and original remainders
remain intact.

The [ChallengeResult interface follow-up](window-challenge-result-interface.md)
recovers its actual float scale fields and explicit death-count entry argument
without changing bytes. A native constructor/table probe reproduces data but
retains measured constructor/producer instruction differences. Only validated
interface progress is published; raw lifetime, manual table and upstream return
contracts retain their holds.

The [CustomEquip recovery](window-custom-equip-lifetime.md) adds native
construction/cleanup, rendering and its actual ordinary-new producer. The
owned heading stays opaque under the existing child protocol. A helper that
accessed beyond CustomEquip's extent now belongs to its evidenced CustomSelect
receiver and returns the actual record pointer; CustomSelect's lifetime hold
is retained. Descriptor and compiler table add 44 bytes with original data
and all protected remainders preserved.

The [LoadItemTexture recovery](window-load-item-texture-lifetime.md) adds
native construction/cleanup, two ordinary-new factories and the actual
texture-request receiver. Managed loader destruction stays queued; its
ready texture list is borrowed and bound through the address of its field.
Descriptor and compiler table add 44 bytes while the following original
suffix and existing controls/interface holds are preserved.

The [AreaMapDisp recovery](window-area-map-lifetime.md) adds native window
construction/cleanup and its actual ordinary-new producer, with actual float,
owned character-storage and opaque heading fields. Descriptor and compiler
table add 44 bytes while retaining the original suffix. Measured canonical
string/draw/result differences remain explicit interface holds; CallBack's
mixed callback family is deferred. No new matching control is introduced.

The [QuestBoardSelect recovery](window-quest-board-select-lifetime.md) adds
native window construction/cleanup and its actual ordinary-new producer.
Text getter/width and draw receiver forwarding are explicit; slot updates use
the real member rather than unsupported floating formals. Descriptor and
compiler table add 44 bytes with the original entry prefix and following
suffix preserved. Opaque heading and wider interface holds remain.

The [ShortCut window recovery](window-shortcut-window-lifetime.md) adds
native window construction/cleanup and its actual ordinary-new producer.
Optional message/symbol children retain deferred close; heading and borrowed
record interfaces stay qualified. The protected 1,044-byte setup helper stays
original input. Descriptor/compiler table add 44 bytes while preserving the
original entry prefix and following table/tail suffix, without new controls.

The [status-family recovery](window-status-family-lifetime.md) adds native
SimpleStatus, Status and PartyStatus chains with their actual factories,
without another raw base-lifetime binding. Five real icon slots replace the
opaque tail, while the original destructor's four-slot cleanup asymmetry
remains held. Three descriptor/compiler-table claims add 132 bytes. Proven
Status data refines the earlier 532-byte SoundBalance suffix into a 484-byte
original prefix, 44 source bytes and four alignment bytes; PartyStatus adds
another four-byte alignment gap. All unknown original bytes remain intact.

The [SymbolChatParts checkpoint](window-symbol-parts-lifetime.md) recovers
matching native source, typed borrowed state and genuine producer/receiver
interfaces. The executable still takes this unit from its original object:
its own external 32.0f reference blocks safe constant localization. No new
source-linked data/code or completed executable lifetime is claimed. The
matched 44-byte data split refines the earlier Help suffix into 156 original
prefix bytes, original target data and four qualified alignment bytes. Current
keyboard/technique main is merged with the relocated Base ABI fixes retained.

The [HelpItem prerequisites](window-help-item-layout.md) separate actual window
fields from entry position/color/string/value receivers and recover the true
20-byte descriptor identity. The page pointer and opaque callback layout are
asserted. Native Base activation remains held on a two-instruction constructor
scheduling difference; its matching legacy lifetime and original table stay
active. No code/data gain or new compiler control is claimed. The Parts constant
hold remains unchanged after reviewing the existing placement evidence.

The standing draft hold is retained for review of the remaining legacy ABI
boundary and historical interface holds. This recovery resolves the measured native
constructor, client-width, default-construction, and emitted-table integration
problems; it does not claim that every historical hold in the PR body is closed.


The [keyboard text-forwarding follow-up](window-keyboard-text-forwarding.md)
recovers the observed nine-call Control/composer text protocol. Both native
36-byte wrappers take their text argument explicitly; the lower 224-byte setter
retains its historical C export with a raw embedded-record receiver. Complete
record identity, capacity/storage aliasing, broader Soft interfaces and CMName
activation remain qualified. All changed objects preserve their complete text,
relocations and allocated sections; no new source/data activation is claimed.
The remaining 22 raw Base/Addition calls across 12 units and other lifetime,
constant, callback/renderer, producer/global ownership and original-remainder
holds persist. Latest main25b400 is separately built and integrated; PR stays draft.


The [keyboard copy/query follow-up](window-keyboard-copy-query-contracts.md)
recovers three actual Control members and composer sizing/export, including all
44 outer calls and Chat's separate export. Fresh allocation, integer query widths,
retained versus temporary result ownership and original failure/truncation behavior
are preserved. Complete text/relocation/provider checks pass for fourteen selected
source objects; held CMName remains original-selected. No match/data activation
or capacity/record-identity claim is added, and all remaining lifetime and ownership
holds persist.


The [composer flag-forwarding follow-up](window-keyboard-composer-flag-forwarding.md)
recovers two halfword flag leaves, their actual Control wrappers and a separate
Chat wrapper previously named as a SubShortCut icon operation. All fifteen outer
calls retain their composer-null guards and flag behavior; no object or buffer
is freed by these helpers. Thirteen complete selected source objects and all
resolved text/data targets remain exact against their qualified baselines.
The adjacent ShortCut close/reopen, Soft word setter, Control show/hide and
remaining lifetime/ownership interfaces retain their holds; no metric or source
activation gain is claimed.


The [Chat close/reopen follow-up](window-chat-reopen-contract.md) recovers the
two remaining helper receivers passed immediately after new TWindowChat, uses
the existing native void close/open members and retains both halfword masks.
The 64/16-byte bodies and all three complete selected source objects remain
exact. This resolves that wrapper's receiver/forwarding qualification while
preserving the Soft construction path and all remaining lifetime, constant,
record and ownership holds. No match metric or source activation gain is claimed.


The [balloon name-plate reconstruction](window-balloon-nameplate-reconstruction.md)
adds the previously absent renderer from GC evidence, with the actual balloon and
context inputs. The new800-byte body remains non-exact; all31 prior functions,
resolved targets and data are preserved, and original executable selection remains.
No compiler control, table/provider claim, metric gain or history split is added.
Exactness, constants, renderer ABI and prior lifetime/ownership holds stay explicit.
