# Fish behavior recovery

Base: fork main `224eb99838471c243b20c305eddac75e7ff76c8f`.
Reference: upstream #240, `dd7a1a2d6e200a69462fff12172ff35aaa460c93`,
`src/pso/object/ambient/TObjFish.cpp` and its entry layout.

Recover `TObjFish::run_task` at `0x8029D974` (2,044 bytes): movement, boundary
reflection, player avoidance, target return, turning and animation advancement.
Use the fork's shared actor lookup, math and client interfaces and its typed
`rotation.yaw` field. The 0x44-byte fish entry has size/offset assertions, and
`m_a0` is now its pointer. The two existing animation tables are expressed as
five rows of three values with identical data.

## Constants and compiler constraints

Claim the native float pool `0x805DDD40..0x805DDD88` (72 bytes). Literals in the
update, renderer and initializer reproduce that pool. The former separately
named 10430.38043493439 double is removed because the compiler now emits it from
the update's expressions. Keeping both definitions creates a duplicate eight
bytes and shifts its symbol. The conversion bias and angle double remain in
the existing `.rodata` range. Localization verified no outside readers before
marking 20 compiler-generated constants local; no binary assets were copied.

Retain upstream's unit-level `-pool off`: otherwise MWCC shares a rodata base
register, saves an extra register and emits a 0xC0-byte frame rather than 0xB0.
The update scores 90.8317% with pooling, and 100% with the original independent
table/constant references. Existing `fp_contract on`, `dont_inline off` and
`inline_depth(4)` pragmas cover the update as they cover the neighboring
renderer; no pragma is added. Ports can drop pool/inline steering and should
preserve required float contraction, the double-precision angle conversion and
signed 16-bit angle wrapping if identical behavior is required.

## Shared-interface correction on current main

The follow-up integrates fork main `387621104107ed1ff8c650bf2f50ef00c6859ba4`
and fixes the recovered renderer's actual call interfaces. It subsequently
synchronizes with main `65b21c210ae980e9d2fe4aef1a3314ed84df1ddd`, preserving
the keyboard and technique recoveries and their folded-unit configuration.
The later synchronization with main `12cc95ca737a3a8757c17f45df06a9af4821d872`
retains the PPP/session recovery and its exception rows. Fish source, declarations
and compiler settings are unchanged by these synchronization merges.
The synchronization with main `4e784e247d991f1fb25766fc80923242a9ba469a`
also retains the dispatcher/TCP extraction and its existing compiler settings;
it adds no fish implementation change or fish output-layout steering.
After that publication, main advanced through the Vol Opt debris and Canadin
recoveries. The final refresh waits for the stable progress-table head
`b2a90ff1eabedf275aaed6cc16acbbd3e8b4a36c` and preserves those current-main
changes and their existing compiler/mapping settings without changing fish code.
The subsequent refresh integrates stable main
`25b4001837b8bdc46666d2ad736a7148a411f978`, including the Dark Falz demo,
memory-card, dialing rectangle, character-select plate, network and Moja
recoveries. Fish source, header and compiler settings remain unchanged.
After the shared-entry/renderer cleanup below, synchronization with main
`4bec40d6cca74a85e91c848ea2d9f25425a313ad` retains the download graph,
game-mode selection and partial LaunchDol header/caller work. It preserves the
shared fish record and native renderer without changing fish source or settings.
The later synchronization with main
`545f2e729fcff6175f2b83ddf741fd2ea870951c` retains the Gal Gryphon loader
recovery and unit consolidation, again without changing fish source or settings.
Synchronization with main `9dcde8562fbd176110243274f18215c3cbbbc19a`
retains the network-config lifecycle and photon-blast recovery, including their
shared interfaces, ntInf profile boundary and documented network compiler
exception. Fish source, header and compiler settings remain unchanged.
The following refresh integrates main
`78a6f8fae432ad941677d392d332273e1079603b`, preserving the Recon debris
recovery and its documented compiler, pooling and symbol-mapping settings.
Fish source, header and settings are unchanged by this integration as well.
The next refresh integrates main
`f0f05f3afe56fd2b71e9dc1fe946e2fa03c84b86`, retaining the Falz cutscene,
TLobby carrier, Moja constructor, challenge enemy-set and ground-collision
recoveries. The Falz unit's legacy filename `TObjFish_8033CCC8.cpp` does not
make its compiler settings part of this Fish behavior unit. Its particle table
`fish_spawn_entry_table` at `0x80477ED8` and this school's resource table
`fish_resource_name_table` at `0x804DC640` are distinct; both retention rows are
preserved. Fish source, header and settings are unchanged.
The following refresh integrates stable main
`1a18b4bd7577af4ee367317064e020d1f91ce5a8`, retaining the rope-collision
simulation and ADX stream-decoder recoveries and their shared interfaces, folds
and retention metadata. Fish source, header and settings remain unchanged.
The old zero-argument
`draw_ginja_object()` declaration depended on the preceding model getter leaving
its return value in r3. The renderer now passes that model explicitly and uses
the shared Ginja, motion draw, BML getter and matrix declarations. Its visibility
call uses the real base-class virtual declaration rather than a synthetic class.
`update_state` returns a full-register integer result, preserving the native
`cmpwi` call contract without a function-pointer cast or low-byte test.

Resource ownership uses `BmlResource *`; camera reads use the shared,
offset-asserted `TCameraCtrl::position`. Five 0x30-byte area records contain
terminated filename lists and `BmlResourceDescriptor` fields, including real
16-bit model/motion counts. This replaces pointer slots holding packed integers.
Size and descriptor-offset assertions preserve the original object layout.
The existing lifetime wrappers now pass the parent explicitly to the verified
base-constructor ABI and use the declared object allocator/deallocator and school
initializer directly. No new compiler option, pragma or output-layout steering
is added by this interface correction.

## Shared entry storage and renderer ownership

The follow-up to published head `98f946cd3b` removes the renderer's
`Fish_8029D5C8` and initializer's `Ent_8029E170`/`Vec_8029E170` views. Both now
use the same `TObjFishEntry` as `run_task`. The initializer allocates the
`m_a0` array with a 0x44-byte stride and initializes the exact fields later read
and updated by those two consumers. Size and offset assertions cover its target,
velocity, yaw, frame, angle, animation, timer, visibility and return-mode fields.
The school state at object offset `0x90` is a signed halfword member, matching
the existing loads and stores. Signed count comparisons remain unchanged.

The renderer is now the declared `TObjFish::render` override, rather than a free
function named after its mangled symbol. It uses the shared object position,
rotation, count and entry-pointer members instead of the raw-offset macro.
Initialization assigns the typed entry pointer directly, without accessing its
slot through a pointer-to-pointer cast to an unrelated record type. The shared
vector type also replaces the initializer's duplicate vector declaration.

This is a source/interface improvement, not a matching gain. All nine functions,
allocated section payloads and relocations remain exact with the existing fish
settings and definition order. The inherited manual vtable still names ABI
symbols, including the renderer, and is not a recovered native vtable.

## Remaining inherited debt

The hand-written vtable and constructor/destructor wrappers remain unchanged in
structure, including manual vptr writes, and still block treating this as clean
native lifetime/virtual-dispatch recovery. The duplicate entry views have been
removed, but some shared model/texture getters and heap helpers still carry
legacy 32-bit address values. The explicit conversions at those
shared boundaries need pointer-sized types and target heap services in a port.
These are inherited limitations, not evidence that all original class/interface
ownership has been recovered. Matching completeness alone does not resolve them.
No assembly, intrinsic, hardware access or new emission pragma is introduced by
the follow-up. Existing `-pool off`, FMA and inline settings remain as documented
above; the final inventory after main synchronization is 5,770 pragmas in 878 files
and 189 unit overrides, including current main's existing compiler and mapping
settings. The refresh introduces no additional fish compiler setting.

### Why native lifetime remains held

The earlier native-constructor/destructor experiment established the expected
class lifetime operations and virtual slots. Under unchanged immediate emission,
eight functions match, but the loader's data references and the complete data
layout do not. The generated vtable starts at `.data+0x140`, after the switch
table at `+0xF0`; the original requires the vtable at `+0xF0` and switch table at
`+0x124`. The emission-pragma solution is not part of this PR.

Further ownership review found direct vtable references in the constructor and
destructor, while the resource-table references occur only in the final loader
at `0x8029E5E8`. Unlike the Moja recovery, Fish has no demonstrated shared
constructor/table/vtable anchor. A separate loader translation unit might avoid
the emission conflict mechanically, but these references do not establish such
an original boundary. The reconstructed split object's filename is not original
debug or source-file evidence. Moja's documented deferred-emission setting does
not supply a no-steering solution for Fish.

Before trying another native-lifetime organization, the missing evidence is an
independently supported object/source boundary or resource-table ownership, or
declaration/header ownership that naturally emits the original order with the
unchanged fish settings. No speculative unit split or source-order permutation
is included in this follow-up.

## Validation

The initial recovery was validated against the base above. The shared-interface
correction is separately compared against the freshly built PR-plus-current-main
baseline `c3a77888e3c4e14bed709b60db8f6870f3ee1063`. The final integration is
also checked against independently built unchanged main `1a18b4bd75`; both build
and retention checks pass, and the subsequent synchronization loses no exact
function or linked range. The earlier `65b21c210` synchronization inherited four
zero padding bytes removed from report coverage by main's unit folding. Canadin
consolidation changes unit counts without losing address coverage, as checked
against the previously published head `03c1430e3f`. The `25b4001837` refresh
inherits eight further zero-padding bytes leaving coverage from main's unit
folding: four bytes each in `.sdata` at `0x805D2794` and `0x805D279C`.
That comparison against previous published head `953770c4c8` loses no exact
function, live code/data address or linked range. The `545f2e729` refresh
inherited a one-unit linked-count reduction from Gryphon consolidation without
address coverage loss. The earlier refresh against `f0f05f3afe` loses no matching,
live code/data/link coverage or padding compared with unchanged main. Compared
with previous published head `ee08464abd`, it inherits four zero-padding bytes
leaving `.data` coverage at `0x804EFA04` from main's Falz consolidation; no exact
function, live data range or linked range is lost. Its compiled fish
object was byte-identical to its predecessor.

The latest refresh against main `1a18b4bd75` likewise loses no exact function,
live code/data address, linked range or padding compared with unchanged main.
Compared with previous published head `62cba4efef`, it inherits four permitted
zero-padding bytes leaving `.sdata2` coverage at `0x805DAA54` from main's rope
unit consolidation. No exact function, live data or linked range is lost.
The compiled fish object remains byte-identical to that previous head.

The original DOL still matches. The full native build and `tools/check_pr.py`
pass with original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
All nine fish functions (4,704 bytes) and all 1,404 data bytes are exact.
Independent comparison verifies the four allocated section payloads, sizes and
alignment and all 302 normalized relocations. This is not whole-ELF identity:
the compiled `.sdata2` has inherited writable flags where the split original is
read-only. All 3,591 linked units are exact. Retention lists 17,872 names with
zero drift; the PR adds 45 names to current main and removes none. All 268
tooling tests pass.

Gains against current main `1a18b4bd75` (the interface correction itself has
no metric loss or gain against its PR-plus-main baseline):

| Measure | Before | After | Gain |
|---|---:|---:|---:|
| Exact functions | 27,416 | 27,417 | 1 |
| Exact code bytes | 4,213,640 | 4,215,684 | 2,044 |
| Exact data bytes | 1,472,575 | 1,472,647 | 72 |
| Linked code bytes | 3,737,624 | 3,742,328 | 4,704 |
| Linked data bytes | 1,190,727 | 1,192,131 | 1,404 |
| Linked units | 3,590 | 3,591 | 1 |

Actual ordered linker inputs: 3,591 source objects and 1,359 fallbacks;
SHA-256 of newline-delimited paths including the final newline:
`5401f6b4a98eaeb13a1565f44499081d8d26be24bfc305a125ec18576b0a7eda`.
