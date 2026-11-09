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
with unchanged exact functions and linked units. Log is now the sole caller
of the Message constructor ABI binding; its measured four-instruction native
constructor mismatch remains open. Retention is clean at 17,587 entries.

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

The standing draft hold is retained for review of the remaining legacy ABI
boundary and historical interface holds. This recovery resolves the measured native
constructor, client-width, default-construction, and emitted-table integration
problems; it does not claim that every historical hold in the PR body is closed.
