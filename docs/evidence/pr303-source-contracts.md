# PR #303 shared source contracts

The source audit of candidate `95d2c2bf37644746979e4bcc52c2092e12352322`
found declaration inconsistencies despite byte-identical target output. This
continuation reconciles those contracts. The earlier candidate is preserved
on a local branch; no publication is part of these changes.

## DHCP packet storage and reply flag

`pso/network/DhcpClient.h` supplies one definition of `BootpPacket`,
`DhcpMessage`, `DhcpClientBuffers`, and the shared volatile state/reply flag.
Previously the timer unit defined the storage as `DhcpClientBuffers`, while
the callback unit declared the same object through unrelated `G_804249F0`.
Their reply flag declarations also disagreed about `volatile`.

The storage consists of three 1,500-byte regions. The builders use the first
region, the callback at `0x804249F0` hands the UDP receiver the third region,
and its reply handler at `0x80424A48` copies accepted packets from the third
to the second. Compile-time checks cover header size/field offsets, message
size, region offsets `0`, `0x5DC`, `0xBB8`, and total size `0x1194`.
The callback uses the same header members as the builders. Both units take
their flag qualifiers from the shared header. This establishes consistent
declarations; it does not claim that `volatile` provides thread synchronization.

## Floating constants

The newly supplied MSL `float.c` defines `unsigned long` word arrays, as the
existing MSL headers declare them. Both `strtoul.c` and `render_util_tail.cpp`
now use those word-array declarations and explicitly interpret the float bit
patterns, following the existing `ansi_fp.c` convention. No reader declares
these objects as `float[]` or `const f32[]`. No constant bytes or target
arithmetic change.

## BML model accessor

The definition and shared header returned `NJS_OBJECT *`, but callers used
conflicting integer, void, byte-pointer and local node-pointer prototypes for
that same C-linkage function. Macros and function-pointer casts also hid
incompatible declarations, including one fabricated six-argument call.

All 179 source files referencing the accessor now directly include
`BmlResource.h` and compile against its single canonical declaration.
No local accessor prototype or incompatible accessor function-pointer cast
remains. Legacy integer resource/model words use explicit conversions at
their calls or storage boundaries; this does not invent new field types or
claim that those words can hold pointers on a 64-bit port. Other accessor
families are outside this change. No wrapper, alias, assembly, or compiler
override is used to conceal the conflicting declarations.

The dolphin loader at `0x802C2958` now copies the real `NpcAnimationBinding`
object, replaces its motions pointer with `BmlResource::motions`, and supplies
that local binding to `register_animated_chunk`. This produces the original
four-word copy followed by its first-word overwrite. The old six-argument
accessor cast merely forced the copy temporaries into registers `r5`–`r8`;
those registers are not model-accessor arguments. The real two-argument call
and native binding copy retain the exact 184-byte function with no compiler
override or steering helper. The other Pigeon and Rafoie accessor casts/macros
are also ordinary shared-header calls now.

Two one-argument prototypes had hidden model-index arguments:

- At `0x800A3230`, the DarkGunner helper receives its index in `r4`, saves it
  across the model call, and reuses it for the texture call. Its caller at
  `0x800A305C` supplies 1. The model call now passes `(s32)a1` explicitly.
  The existing outer `void *` parameter remains a bounded legacy interface.
  The resource initialization's accessor function-pointer casts also become
  ordinary shared-header calls; node reads use the shared `NJS_OBJECT` fields.
- The radar constructor's three calls at `0x801FB4D4`, `0x801FB4E4`, and
  `0x801FB4F4` pass `&core->m_90` and indices 2, 0, 1, then store the returned
  model pointers in its three frame-model words. The helper at `0x801FB9A4`
  ignores the context, loads the resource into `r3`, forwards incoming `r4`
  to the accessor, and returns its result. It now has the shared static
  declaration `NJS_OBJECT *init_map_ptr(const s32 *, s32)`; a nonstatic
  receiver would incorrectly treat an interior word as a `TRaderMapCore`.
  The old `Fv` symbol was metadata, not evidence of a no-argument source
  signature. The metadata now uses the compiler-emitted `FPCll` signature,
  and the constructor calls the shared declaration instead of declaring a
  mangled symbol by hand. The existing helper name remains provisional.

## Validation before current-main integration

The shared DHCP/float repair and complete accessor migration both reproduce
the original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Against the preserved candidate report, exact functions, matched/complete
code/data, coverage, and linked units are unchanged; the radar signature is
the only function rename. The pinned compiler also emits the exact original
radar helper, its constructor calls, the DarkGunner helper and its caller.
Fresh full validation after integrating current main is recorded separately
below.

## Current-main integration

Merged main `560addd4270d97c8f14fbb1025d07ec3f5f751d2`, preserving the
three new units and inherited exception records from its #207 carrier. The
only conflicts were the two exception documents. Their merged inventory
contains 5,765 pragmas in 871 files and 175 unit overrides; this continuation
introduces no new pragma or override.

A separately built main baseline passes the original DOL hash, source-linkage
and retention checks. The merged continuation also builds to the original
DOL hash and passes `check_pr.py --no-build` against that fresh baseline:

| Measure | Current main | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,367 | 27,370 | +3 |
| Matched code bytes | 4,182,748 | 4,184,928 | +2,180 |
| Matched data bytes | 1,469,283 | 1,469,371 | +88 |
| Complete code bytes | 3,641,308 | 3,653,528 | +12,220 |
| Complete data bytes | 1,166,551 | 1,171,439 | +4,888 |
| Linked units | 3,573 | 3,573 | 0 |

There are no address-level regressions or coverage losses against current
main. Retention contains 17,591 names, with no missing or stale entry. All
3,573 linked units are exact. The three new matches are the same DHCP functions
as the initial PR; the declaration repairs deliberately add no match count.
The DarkGunner unit remains 43/43 with exact code/data; the radar constructor
unit remains 4/4 and its helper unit 3/3. Their original compiled source inputs
remain on the DOL's link edge. The porting-exception inventory check passes.

Against the preserved pre-contract candidate, the additional functions/data
and three additional linked units all come from current main. Its 4-byte
total-data decrease is main's dropped zero alignment padding, already
documented by the #207 carrier; the address-level delta check passes.

The four audited contract conflicts are reconciled. Other legacy accessor
families, integer storage fields, the character-select no-argument function
cast/receiver-as-index convention, and the opaque DHCP lease-parser/cookie
interfaces remain bounded inherited work. This continuation does not claim
complete original-source type recovery or host-pointer portability. Keep
the PR draft pending review and the separate publication authorization.

## Final main checkpoint

A final remote check found main had advanced through #319 to
`9924ce113b5e6dff309a5ae94065265d3066fb24`. This was merged without conflicts,
and both the detached baseline and continuation were rebuilt from their
updated split inputs. The prior validation above remains historical evidence.
Against this newer baseline:

| Measure | Main `9924ce113` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,368 | 27,371 | +3 |
| Matched code bytes | 4,183,640 | 4,185,820 | +2,180 |
| Matched data bytes | 1,469,407 | 1,469,495 | +88 |
| Complete code bytes | 3,643,320 | 3,655,540 | +12,220 |
| Complete data bytes | 1,166,675 | 1,171,563 | +4,888 |
| Linked units | 3,574 | 3,574 | 0 |

The full build retains the original DOL hash, and the address/linkage/retention
checks and porting inventory pass. `make -C ports/tests run` also passes the
host vector fallback and item factory callback checks brought by main.
The same three DHCP matches account for the entire incremental match gain.

## Typed-file-API main refresh

The next refresh merges main `6e880491f335b26239b4553f0882c04676a0a6e7`,
which includes #308's typed file APIs and #368's footprint recovery. The PR
head before this merge was `c9b3f518054c429f5384fb4c2f11360cd366e567`.
No other active task owned #303, and the existing remote head was unchanged.

The texture loader retains main's `loaded_bml` member and typed loader
interface, taking the model through the shared accessor and converting only
at its legacy output word. The sky scene retains main's `BmlResource *`
archive and the shared model accessor, with the existing integer model slot
as its explicit boundary. Neither unit restores a conflicting model-accessor
prototype. The remaining automatic source merges preserve main's new handle
and filename interfaces while retaining the pointer-returning model accessor.

Main also changes `TLobby::start_load_default` to return `void *`. Its former
source file was already folded into the character-select unit by #303, so
that return-type change is applied to the owning definition there. The old
fragment stays deleted: restoring it would duplicate the folded functions.
The exception documents combine both branches' records and regenerate the
inventory (5,765 pragmas in 871 files, 176 compiler overrides).

Both the fresh detached main baseline and merged branch pass the original
DOL hash and full address/linkage/retention checks. Against this main:

| Measure | Main `6e880491f` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,369 | 27,372 | +3 |
| Matched code bytes | 4,185,572 | 4,187,752 | +2,180 |
| Matched data bytes | 1,469,759 | 1,469,847 | +88 |
| Complete code bytes | 3,645,480 | 3,657,700 | +12,220 |
| Complete data bytes | 1,167,051 | 1,171,939 | +4,888 |
| Linked units | 3,575 | 3,575 | 0 |

There are no regressions or coverage losses. Retention has 17,600 entries,
with no missing or stale entries. The affected texture-loader unit stays
12/12, sky scene 9/9, and folded character-select unit 9/9, all with exact
code/data and source linkage. All 179 accessor-using source files still
include the canonical header, without accessor macros or function-pointer
casts. Host vector and item-factory tests and the exception inventory pass.
The prior GitHub metadata failure is separate from this branch integration;
no title/body write is retried here. Keep the PR draft pending current checks.

## Network-runtime main refresh

The next refresh merges main `18207f98696bab4911ca2cecac1c19381e2ea506`
into PR head `0a88bed9af6d85d586a0265027077f464a734627`. Main includes the
#361 unit folds and #369 network-runtime recovery. No other active task
owned #303, and its remote head still matched the local starting commit.

Only retention metadata and the two exception documents conflicted. Both
sides' live retention entries are preserved; fresh split inputs confirm no
missing/stale entries. The exception documents retain main's additional
units and registered native-code debt, together with this branch's Falz
override. The regenerated inventory has 44 assembly source lines in 11 files,
5,769 pragmas in 875 files, and 177 unit overrides. This refresh adds no new
assembly, pragma, or compiler override beyond the changes already in main.

Main's newly folded `TObjDFDemo5` constructor consumes the canonical model
accessor. Its `TObjDFDemo5Part::model` field is now `NJS_OBJECT *`: the
constructor assigns the accessor's model pointers, and all four reads feed
`draw_model_motion`. This removes the old pointer-to-integer boundary and
redundant draw casts while preserving the 0x118 class size and exact compiled
unit (8/8 functions, all data exact, linked). The incoming packet-pool return
type is consistently `s16` in its shared headers and definition. No local
accessor prototype or function-pointer cast is restored; all 180 source
files using the accessor include its canonical header.

Both fresh main and the merged branch reproduce the original DOL hash and
pass address/linkage/retention checks. Against this main:

| Measure | Main `18207f986` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,385 | 27,388 | +3 |
| Matched code bytes | 4,189,044 | 4,191,224 | +2,180 |
| Matched data bytes | 1,470,159 | 1,470,247 | +88 |
| Complete code bytes | 3,667,732 | 3,679,952 | +12,220 |
| Complete data bytes | 1,175,627 | 1,180,515 | +4,888 |
| Linked units | 3,585 | 3,585 | 0 |

There are no regressions or coverage losses. Retention has 17,658 entries,
with no missing or stale symbols. Network packet runtime stays 24/24 and
the incoming OS network-runtime unit stays 53/53; both remain exact and linked.
Host vector and item-factory tests and the exception inventory pass. The
earlier failed metadata write is not retried by this refresh; keep the PR
draft while its latest source checks and readiness are verified.

## PPPoE main refresh

Main advanced to `224eb99838471c243b20c305eddac75e7ff76c8f` through #370.
The remote PR head was still `46ee82d720db5f04c33b13ea4e767b285abaf22b`,
with no other active owner. This merge was clean: only main's PPPoE recovery,
metadata and associated `s16 post_send_message` contract were added. The
member declaration, C-linkage declaration and definition consistently use
`s16`; #303's shared DHCP/BML contracts are unchanged. All 180 model-accessor
source consumers still include the canonical header without accessor aliases.

Both the fresh main baseline and continuation reproduce the original DOL
hash and pass `check_pr.py`, retention and exception-inventory checks. The
continuation has 27,389 exact functions, 4,191,812 matched code bytes and
1,470,247 matched data bytes: +3 functions, +2,180 code bytes and +88 data
bytes against main, with no regressions or coverage losses. Complete code
and data increase by 12,220 and 4,888 bytes. All 3,586 linked units are exact;
retention has 17,672 entries with no missing/stale entries. PPPoE remains
20/20 and message transport 26/26, exact and linked. Host vector and item-
factory tests pass. The failed metadata write is not retried by this refresh.


## Focused DHCP main refresh

This continuation merges main `387621104107ed1ff8c650bf2f50ef00c6859ba4`
into prior PR head `4ba2964bdcec61fdb3f5c674b2b0fcc14db7dd75`. No competing
active #303 owner was found; the remote head was unchanged. Main commit
`7d20a0e818ef6c8aae1c7c03dfa44e48933bcae1` extracts the three DHCP bodies
from this draft. They are now main's matches, so this continuation claims
**zero new exact functions and zero new matched code bytes** against main.
The shared DHCP layout, canonical BML interfaces, source fixes and unit folds
remain relevant; the draft is not closed or declared review-ready.

The overlapping DHCP conflicts retain this branch's single `DhcpClientBuffers`
layout, `DhcpMessage` methods, names and volatile state contracts. Main's new
`NetworkReceiveCallback` header is retained and used by the UDP opening helper,
its declaration, the callback definition and both callers. The callback takes
`u8 *record` and decodes the existing protocol record inside its body. The
DHCP discovery caller now names that shared C-linkage callback directly; its
unused, incompatible `TLobby::dhcp_handle_reply(s16, void *)` alias declaration
is removed. No function-pointer cast, fabricated receiver or duplicate local
callback prototype is introduced. Main's `TTcpSocket` callback changes remain.
The existing exact thread-state function order from this branch is preserved.

Retention metadata keeps the branch's renamed message builders rather than
main's superseded TLobby spellings. Fresh exact-split inputs confirm 17,672
entries with none missing or stale. The exception inventory is regenerated;
only the existing address-class-mask hit's line number changes. No new pragma,
assembly, compiler override or matching exception is added by this refresh.

Both isolated builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main's linkage/retention checks
pass, and the continuation's complete `check_pr.py` passes against freshly
built main:

| Measure | Main `387621104` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,389 | 27,389 | 0 |
| Matched code bytes | 4,191,812 | 4,191,812 | 0 |
| Matched data bytes | 1,470,159 | 1,470,247 | +88 |
| Complete code bytes | 3,685,784 | 3,685,784 | 0 |
| Complete data bytes | 1,184,043 | 1,184,131 | +88 |
| Linked units | 3,587 | 3,586 | -1 |

There are no regressions or code/data/function/address-coverage losses. The
unit-count reduction reflects the two existing Falz/character-select folds
and the float source unit, not dropped linked ranges. All 3,586 linked units
are exact. DHCP stays 42/42, packet runtime 24/24 and TCP socket 28/28, with
all code/data exact and actual source linker inputs. The affected Falz,
character-select and model-demo units likewise link from source. All 180
model-accessor consumers still include the canonical header. Host vector and
item-factory callback tests, whitespace and port-inventory checks pass.

The earlier failed title/body update is not retried. Keep draft pending
metadata reconciliation and current-head readiness review. Inherited integer
storage and opaque protocol/parser boundaries remain documented limitations.


## Keyboard and technique main refresh

Merge main `65b21c210ae980e9d2fe4aef1a3314ed84df1ddd` into prior reviewed
head `6c7b18984553da59229f1dbdaf589f8f8853a564`. The remote head was unchanged
and no other active owner was working on #303. Only the exception register
and generated inventory conflicted. Keep main's keyboard/technique entries
and retirement of the technique conversion-pool hook, together with this
branch's Falz override and DHCP volatile-state explanation. Regeneration
reports 5,768 pragmas in 874 files and 177 compiler overrides. There are no
manual source resolutions, new assembly or new compiler exceptions here.
The dispatcher reset-status signature investigated separately for #376 is
unchanged; this refresh does not duplicate that repair.

Both baseline and continuation builds ran through the existing build-capacity
wrapper in exclusive legacy mode, honoring its shared coordination paths.
Both reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Complete `check_pr.py` checks
pass against the fresh main report, including retention from current splits.

| Measure | Main `65b21c210` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,392 | 27,392 | 0 |
| Matched code bytes | 4,199,532 | 4,199,532 | 0 |
| Matched data bytes | 1,470,367 | 1,470,455 | +88 |
| Complete code bytes | 3,699,992 | 3,699,992 | 0 |
| Complete data bytes | 1,185,151 | 1,185,239 | +88 |
| Linked units | 3,585 | 3,584 | -1 |

No function, code/data address, linked range or padding is lost. The unit
count difference remains the existing two folds plus float unit. All 3,584
linked units are exact. Technique controller is 21/21, keyboard control
30/30, soft keyboard 27/27, DHCP 42/42 and packet runtime 24/24; their code,
data and actual source linker inputs are exact. Retention has 17,707 entries,
none missing or stale. All 180 accessor consumers retain the canonical
header; host vector and item-factory tests, whitespace and the port inventory
pass. Main owns the three DHCP matches already, so this continuation receives
zero new function/code credit. The source-contract repairs and folds remain
relevant. Keep draft with the previously documented interface limitations;
the earlier failed title/body write is not retried.


## DHCP lease parser packet interface

Starting from reviewed PR head
`a01e5955163b0ddf8a802ef95c3089e29fa77aad` on main
`65b21c210ae980e9d2fe4aef1a3314ed84df1ddd`, replace the false
`TLobby::parse_dhcp_lease_times()` receiver with the shared C-linkage function
`dhcp_parse_lease_times(u8 *cookie_and_options)` in `DhcpClient.h`.
The definition at `0x804245E4` immediately treated `this` as bytes and never
read a TLobby field. Both callers pass DHCP cookie/options storage: the
configuration parser at `0x80423440` passes its cookie byte cursor, and the
renew/rebind step at `0x80423E80` passes the accepted reply's cookie. The
shared BOOTP layout asserts cookie offset `0xEC`. Options `0x33`, `0x3A`
and `0x3B` supply lease, renewal and rebinding times; no lobby ownership is
supported by these operations.

Both callers now use that shared declaration directly. Remove the unused
TLobby member declaration and its packet-to-object casts, and name the
existing address `dhcp_parse_lease_times` in symbol metadata. The parser's
algorithm and native pointer argument remain unchanged; no adapter,
function-pointer cast, padding or steering is introduced. The parser stays
360 bytes exact, its configuration caller 680 bytes exact and request caller
940 bytes exact. Complete caller/callee units remain DHCP 42/42 and packet
runtime 24/24, with exact code/data and compiled source linker inputs.

This bounded change does not claim bounded packet decoding: the existing
option scanner has no input-length argument. Its local return declarations
also remain inconsistent (`s32` callers versus `u8` definition), a separate
inherited interface to investigate with full matching checks. Cookie stores,
native address words and other provisional accessors remain. The separately
owned #376 dispatcher reset-status repair is untouched.

The full build reproduces the original DOL hash. Incremental checks against
`a01e59551` show zero changes to matched functions, code/data, linkage and
coverage; only this one function name changes. Fresh-main checks retain the
branch's +88 matched/linked data bytes, zero new functions/code and no losses.
All 3,584 linked units and 17,707 retention entries pass. No port-exception
inventory change is introduced.

The branch retains source-level value after main extracted its three DHCP
matches: shared DHCP packet/buffer/volatile-state contracts, the new truthful
lease-parser interface, canonical BML declarations across 180 consumers and
the repaired calls, consistent float object declarations, and the existing
Falz/character-select folds. The 88 data bytes remain unique. Those source
repairs are not superseded by main's focused DHCP extraction. This does not
make all provisional interfaces complete or the stale PR metadata current;
keep draft and do not close the PR as stale.


## PPP session main refresh

Merge main `12cc95ca737a3a8757c17f45df06a9af4821d872` into reviewed head
`ab7da74eb5d300ccb50eee4dc74bd163e4a37821`. The remote head was unchanged
and no competing active #303 owner was found. Main brings #374 PPP/session
control. Resolve only retention metadata and the exception summary: keep the
four new live retention names once each and preserve both sides' exception
records. Fresh-split retention checks pass. No source conflict or manual
source repair is included. The shared `s16 map_state_to_mode_id` declaration
and definition merge consistently. Shared DHCP/BML contracts and the free
lease parser remain intact. #376 dispatcher/reset-status work is unchanged.

Both isolated builds use the existing exclusive capacity wrapper and reproduce
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main's
full checks pass against preserved main `65b21c210`; the continuation's full
checks pass against fresh main `12cc95ca7`:

| Measure | Main | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,394 | 27,394 | 0 |
| Matched code bytes | 4,202,324 | 4,202,324 | 0 |
| Matched data bytes | 1,470,367 | 1,470,455 | +88 |
| Complete code bytes | 3,704,816 | 3,704,816 | 0 |
| Complete data bytes | 1,185,687 | 1,185,775 | +88 |
| Linked units | 3,586 | 3,585 | -1 |

No function, data/code address, linked range or padding is lost. All 3,585
linked units are exact; retention has 17,711 names with no missing/stale
entry. The session unit is 16/16, transport 39/39, DHCP 42/42 and packet
runtime 24/24, all exact code/data and linked from compiled source. All 180
model-accessor consumers retain the canonical header. Host vector and item-
factory tests, inventory and whitespace pass. No extra match credit is
claimed for the DHCP functions already in main. Keep draft with existing
interface limitations. The failed metadata update is not retried.


## Dispatcher/TCP main refresh

Merge main `4e784e247d991f1fb25766fc80923242a9ba469a` into reviewed head
`bf5c46ee64a00d7f4e3884b12810b635e85dc411`. The remote head was unchanged
and no other active #303 owner was found. Main now contains the reviewed
#376 dispatcher/TCP extraction and typed dispatcher-state cleanup. Only the
two exception documents conflict. Retain main's new dispatcher/TCP records
and the existing Falz/DHCP entries, then regenerate the inventory: 5,770
pragmas in 876 files and 179 compiler overrides. No manual source resolution
or new exception beyond main is introduced. The shared DHCP/BML contracts
and free lease parser remain unchanged.

The canonical dispatcher reset now forwards `s32` status, while the native
DHCP caller's `s16(int)` boundary is deliberately retained with main's
explanation and rejected-probe evidence. This merge does not claim to finish
that ABI repair or override #376's reviewed scope. The dispatcher thread
handles and reset clear range retain main's shared typed state and assertions.

Both builds ran through the existing exclusive capacity wrapper and reproduce
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main passes
full checks against preserved main `12cc95ca7`; the continuation passes full
checks against fresh main `4e784e247`:

| Measure | Main | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,394 | 27,394 | 0 |
| Matched code bytes | 4,202,324 | 4,202,324 | 0 |
| Matched data bytes | 1,470,367 | 1,470,455 | +88 |
| Complete code bytes | 3,706,824 | 3,706,824 | 0 |
| Complete data bytes | 1,185,935 | 1,186,023 | +88 |
| Linked units | 3,587 | 3,586 | -1 |

No exact function, code/data address, linked range or padding is lost. All
3,586 linked units are exact; retention has 17,713 names with no missing/stale
entry. Dispatcher 12/12, DHCP 42/42 and packet runtime 24/24 remain exact
code/data and actual source linker inputs. The incomplete TCP unit remains
40/45 and the prefix 243/281, both on original-object fallback; neither is
claimed recovered. All 180 accessor consumers retain the canonical header.
Host vector and item-factory tests, exception inventory and whitespace pass.
Keep draft with inherited interface limitations; the failed metadata write
is not retried.


## Shared DHCP option-length return contract

On reviewed head `2f2e34a814effd03440f235583491d4077b6d5f9` and main
`4e784e247d991f1fb25766fc80923242a9ba469a`, audit every source occurrence
and original call reference to `find_dhcp_option__6TLobbyFPvUcPv` at
`0x80424830`. Only packet runtime and the DHCP unit call it: eight calls in
the lease parser/reply callback and five in the configuration parser, 13 total.
No competing worker was changing these files. Earlier evidence recorded the
inconsistent return declarations but no rejected canonical-word probe.

The definition previously returned `u8`, with a file-scope `u8` declaration;
all 13 calls used `s32` declarations, including two block-scope shadows.
Every return path produces either zero or `len`, loaded from one unsigned
byte. Thus every result is representable in `s32`, including lengths above
127 without sign extension. The native code returns that byte-loaded value
in the integer result register, and callers compare/copy the word result.
A zero result also reports no match; it does not distinguish that case from
a matched zero-length option. This evidence supports a consistent word return
without asserting that machine code uniquely proves the original C type.

Declare the existing C-linkage symbol once in `DhcpClient.h`, returning `s32`,
and make the definition return `s32`. Remove the redundant file/block local
declarations in both units. The tag, byte-pointer input and output pointer,
local `u8 len`, byte loads, loop, stores, symbol identity and all call sites
remain unchanged. No parameter, length contract, conversion adapter, cast,
pragma, padding or compiler override is added. Both callers already include
the shared header. The option scanner's missing input length and unchecked
native scan behavior remain unresolved; no packet-validation improvement is
claimed. Dispatcher/reset-status and TCP interfaces are untouched.

The capacity-gated probe reproduces the original DOL hash, and both complete
compiled source objects (`NetworkPacketRuntime` and `text_80421620`) compare
byte-for-byte equal to their pre-probe objects, including metadata and
relocations. The 108-byte scanner remains exact. Complete units stay packet
runtime 24/24 and DHCP 42/42 with exact code/data and compiled source inputs.
Full incremental checks show zero metric/coverage/retention changes; only
shared declarations and source consistency improve. The generated exception
inventory changes only the existing DHCP address-mask hit's line number.
The branch's comparison with main still has +88 data bytes and zero new
functions/code; main owns the prior DHCP matches. Keep draft with the other
documented interfaces and stale metadata. No metadata write is retried.


## Canadin and debris main refresh

Merge main `b2a90ff1eabedf275aaed6cc16acbbd3e8b4a36c` into reviewed head
`460ce612da6407609f4460e14c47447f49a7f980`. The remote head is unchanged;
no competing #303 owner is active. Main supplies the Canadin loader/folds and
Vol Opt pillar debris unit. Only the two exception documents conflict.
Preserve incoming records and this branch's entries; regenerate inventory
(5,770 pragmas in 876 files, 180 compiler overrides). No manual source
resolution or repeated technical probe is included. Shared scanner word-return,
free lease-parser, DHCP/BML contracts and existing interface holds are unchanged.
All 180 model-accessor consumers still include the canonical header.

Both capacity-gated builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main passes full checks against
preserved main `4e784e247`; the continuation passes against fresh main:

| Measure | Main `b2a90ff1e` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,396 | 27,396 | 0 |
| Matched code bytes | 4,203,136 | 4,203,136 | 0 |
| Matched data bytes | 1,470,455 | 1,470,543 | +88 |
| Complete code bytes | 3,707,636 | 3,707,636 | 0 |
| Complete data bytes | 1,186,023 | 1,186,111 | +88 |
| Linked units | 3,585 | 3,584 | -1 |

No exact function, code/data address, linked range or padding is lost. All
3,584 linked units are exact; retention has 17,719 names with no missing/stale
entries. Canadin is 101/101, debris 1/1, dispatcher 12/12, DHCP 42/42 and
packet runtime 24/24, all exact code/data and compiled source linker inputs.
TCP remains 40/45 and on original fallback. Unit-count reductions from folding
are structural; no linked ranges are lost. Host vector and item-factory tests,
exception inventory and whitespace pass. Keep draft with the existing native
interface limitations and stale metadata; no previously failed write is retried.


## Demo 4 main refresh after pre-push advance

Before publishing the validated Canadin/debris refresh, main advanced again
to `3ee5a151c72efc2763fb72e1d8deaae26e9aade2` (Dark Falz demo 4 recovery).
Integrate it into the unpublished Canadin checkpoint
`b3bbaf6314e3e63f7afd30861bf9d2c1c048746f`; the stale exception-summary
sentence found during that checkpoint's review is corrected there. The remote
PR remains `460ce612da6407609f4460e14c47447f49a7f980` with no competing owner.

Retention conflict resolution keeps the live `dfdemo4_strip_nodes` entry and
omits main's superseded `dhcp_build_packet__6TLobbyFv` spelling; this branch
already retains its shared `DhcpMessage::build_request` name. Regenerate the
exception inventory (5,769 pragmas, 876 files, 181 compiler overrides), keeping
both branches' entries. No assembly, pragma or override beyond main is added.

Incoming `TObjDFDemo4Part::model` was an integer. Both constructor loops assign
the canonical `NJS_OBJECT *` model accessor, and the only reads pass those
fields to `draw_model_motion`. Use `NJS_OBJECT *` storage, matching the existing
demo 5 repair, and remove the two redundant draw casts. The native class size
assertion remains `0x11C`. The strip-node table's separate `s32 model` selector
and provisional texture-list words are unchanged. This preserves the typed
accessor contract rather than restoring incompatible local prototypes or
concealing it with integer casts. Scanner, lease-parser and other holds remain
unchanged; no earlier technical probe or failed metadata write is repeated.

Both new capacity-gated builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main's full comparison with
preserved `b2a90ff1e` passes. Its fold removes only two four-byte zero-alignment
coverage ranges at `.sdata 0x805D2794` and `0x805D279C`, accepted by the checker;
no original data object or linked range is lost. Against fresh main:

| Measure | Main `3ee5a151c` | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,397 | 27,397 | 0 |
| Matched code bytes | 4,203,648 | 4,203,648 | 0 |
| Matched data bytes | 1,470,687 | 1,470,775 | +88 |
| Complete code bytes | 3,708,148 | 3,708,148 | 0 |
| Complete data bytes | 1,186,255 | 1,186,343 | +88 |
| Linked units | 3,582 | 3,581 | -1 |

There are no regressions or code/data/address/link/padding losses against
fresh main. All 3,581 linked units are exact; retention has 17,726 entries,
none missing or stale. Demo 4 is 7/7, Canadin 101/101, DHCP 42/42 and packet
runtime 24/24 with exact code/data and actual compiled source inputs. TCP
retains its original fallback. All 181 accessor-using source files include
the canonical header. Host vector and item-factory tests, inventory and
whitespace pass. Keep draft with the remaining documented interfaces and
stale metadata; no formal approval or main merge is performed.


## Dialing rectangle main advance during publication

After the reviewed `e94c94e4c1b072d4186b3cc955b654a01dd534b4` push, GitHub
still reported conflicts and listed no CI run. A fresh fetch established that
main had advanced during publication to
`8d2b58ef2fdf777456fff67f24438826860f8a1d` (#378 dialing rectangle).
Integrate it rather than attributing the conflict to a source-validation or
metadata failure. Only the exception documents conflict; keep both sides'
records and regenerate inventory (5,769 pragmas, 876 files, 182 overrides).
No additional manual source fix is made. Main's typed dialing/rectangle
interfaces, all previous BML/DHCP repairs and the demo 4 pointer fields remain.

Both capacity-gated builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main passes against preserved
`3ee5a151c`, and the continuation passes against fresh main `8d2b58ef2`:

| Measure | Main | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,398 | 27,398 | 0 |
| Matched code bytes | 4,203,884 | 4,203,884 | 0 |
| Matched data bytes | 1,470,691 | 1,470,779 | +88 |
| Complete code bytes | 3,708,520 | 3,708,520 | 0 |
| Complete data bytes | 1,186,259 | 1,186,347 | +88 |
| Linked units | 3,583 | 3,582 | -1 |

No exact function, data/code address, linked range or padding is lost against
fresh main. All 3,582 linked units are exact; 17,726 retention entries pass
without drift. Dialing rectangle 4/4, demo 4 7/7, DHCP 42/42 and packet runtime
24/24 remain exact and use compiled source inputs; TCP retains original
fallback. All 181 accessor-using sources remain canonical. Host vector and
item-factory tests, inventory and whitespace pass. No technical probe,
failed metadata write, formal approval or main merge is repeated/performed.
Keep draft with the documented remaining interfaces and stale metadata.


## Memory-card main advance caught by ancestor guard

The pre-push ancestor guard for the README-only checkpoint
`6a3dd8fdd9606ed709d10cfd59a0c8afb7eabf8b` stopped before executing its
push: main advanced to `4618606af4bec0db175a176d9fadabd098936a04` with
#379 memory-card layout recovery. The already reviewed `f61b80410` progress
was preserved remotely. Integrate this source snapshot; only exception
documents conflict. Retain both branches' records and regenerate inventory
(5,769 pragmas, 876 files, 183 overrides). No additional source correction
or technical probe is made. The scanner, lease parser, model-pointer repairs,
canonical BML consumers and remaining interface holds remain unchanged.

Both capacity-gated builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Main passes full checks against
the preserved `8d2b58ef2` report (the intervening `c23775bb4` changes only
README, with identical source/build inputs). The continuation passes against
fresh main `4618606af`:

| Measure | Main | Continuation | Delta |
|---|---:|---:|---:|
| Exact functions | 27,399 | 27,399 | 0 |
| Matched code bytes | 4,204,184 | 4,204,184 | 0 |
| Matched data bytes | 1,470,935 | 1,471,023 | +88 |
| Complete code bytes | 3,708,820 | 3,708,820 | 0 |
| Complete data bytes | 1,186,503 | 1,186,591 | +88 |
| Linked units | 3,582 | 3,581 | -1 |

There are no regressions or data/code/address/link/padding losses against
fresh main. All 3,581 linked units are exact; 17,727 retention names pass
without drift. Memory-card 7/7, demo 4 7/7, DHCP 42/42 and packet runtime
24/24 use exact compiled source inputs; TCP retains original fallback.
All 181 accessor users remain canonical. Host vector and item-factory tests,
inventory and whitespace pass. The interrupted build-service request was
verified not to have created its processes; validation resumed through the
same capacity wrapper after recovery. Keep draft with the documented
remaining interfaces and stale metadata; no metadata write is retried.


## Character-select plate and network-info main refresh

Merge main `4ae3511286473eb94ba91236c37e94f7b0475109` into reviewed head
`3b92a510ba9b3c697a38d647850dc2b462f3748f`. The remote head is unchanged
and no competing #303 owner is active. Only the generated exception inventory
conflicts. Keep incoming character-select/network-info records alongside the
existing branch entries and regenerate: 5,771 pragmas, 876 files, 183 overrides.
No source conflict repair or existing interface hold is changed.

Both capacity-gated builds reproduce the original DOL hash. Main's full
comparison with preserved `4618606af` and the continuation's full comparison
with fresh main pass. Against main: 27,402 exact functions and 4,204,908 matched
code bytes are unchanged; matched data is 1,471,075 (+88), complete code
3,709,656 (unchanged), complete data 1,186,643 (+88). No exact function, data,
linked range, address or padding coverage is lost. All 3,582 linked units and
17,739 retention entries pass. Character-select plate 38/38, network-info
requests 2/2, DHCP 42/42 and packet runtime 24/24 remain exact and source-linked;
TCP retains original fallback. All 181 model consumers remain canonical.
Host tests, inventory and whitespace pass. This checkpoint synchronizes main
before any new bounded interface probe; it does not claim a predicate or
volatility repair. Keep draft and preserve the metadata hold.


## Moja main checkpoint before predicate work

After the reviewed `61be011207223474b8e85fec0423e5ab55384a5c` checkpoint,
main advanced to `3c9a6a9719f80438125926bd90a368fd57e0951d`. Publish the
reviewed checkpoint as intermediate draft progress, then integrate Moja.
Only exception documents conflict; preserve both sides and regenerate inventory
(5,771 pragmas, 876 files, 184 overrides). No source repair or predicate probe
is included yet. Existing scanner, lease-parser, model and interface holds
remain unchanged.

Both capacity-gated builds reproduce the original DOL hash. Main's comparison
with preserved `4ae351128` and the branch's comparison with fresh main pass.
The branch has 27,403 exact functions and 4,205,596 matched code bytes (both
unchanged against main), 1,471,811 matched data bytes (+88), 3,710,492 complete
code bytes (unchanged), and 1,187,379 complete data bytes (+88). There are no
regressions or data/address/link/padding losses. All 3,582 linked units and
17,739 retention entries pass; Moja 5/5 and the DHCP/packet runtime units are
exact and source-linked. Host tests, inventory and whitespace pass. This is
the separately validated baseline for a subsequent bounded predicate probe;
no metadata hold is retried and the PR stays draft.


## Character-select predicate word return and explicit receiver

On separately synchronized checkpoint
`84c74a4a72e61d0c21737ae034fc880d3b3ee3bf`, the predicate
`is_selection_done__23TAdSinglePlyChrSelectGCFPv` at `0x8028D5D4` and its
shared header return `u8`, while the other caller redeclares `s32(void *)`.
`get_result` at `0x8028D5E8` calls it through an incompatible no-argument
`s32 (*)()` cast. Repository history/evidence records this as inherited debt;
no rejected probe for this specific repair was found. All source/original
references are the predicate definition and two caller sites. No overlapping
worker is changing these units.

Both native consumers compare the whole result word. The predicate returns
only zero or one: it tests the existing signed word at opaque input offset
`0x2C` for equality to two, retaining the explicit `u8` normalization. In
`get_result`, incoming r3 remains the receiver through the predicate call at
`0x8028D5FC`. This supports one shared `s32(void *)` declaration and a direct
`is_selection_done(this)` call. It does not prove the predicate's input is a
specific class. Preserve `void *`, the byte-normalized expression, symbol,
raw field view and all algorithmic behavior. Replace the second unit's local
prototype with the shared header and remove the function-pointer cast.

The capacity-gated build reproduces the original DOL SHA-1. Both complete
compiled objects compare byte-for-byte with the preserved pre-probe objects,
including metadata and relocations. The predicate remains 20 bytes exact and
`get_result` 64 bytes exact. Their complete unit stays 9/9 and the other caller
unit 14/14, with all code/data exact and actual compiled source linker inputs.
Full incremental checks have zero metric, name, retention or coverage changes.
Fresh-main checks preserve +88 data bytes, zero new functions/code and no
losses. All 3,582 linked units and 17,739 retention entries pass. Host tests,
exception inventory and whitespace pass; no new compiler construct is added.

The no-argument predicate call/return mismatch is resolved. The separate
allocator receiver-as-index convention, DHCP bounds and other native protocol
interfaces remain documented debt. No length contract is invented. The
volatility candidate at `lbl_805D7B0C` was not probed: its remaining plain
read/store need their own scheduling/observability proof. Output-pointer
families B40/B44/B48 require broader API tracing and are not guessed here.
The metadata hold is unchanged; keep draft pending current-head review/CI.


## Shared volatile DHCP step-word contract

On reviewed head `893e8fddb3f780cd1f3bf9847fc3be6f16a08782` and main
`25b4001837b8bdc46666d2ad736a7148a411f978`, audit all named source and
original references to the four-byte step word `lbl_805D7B0C` at `0x805D7B0C`.
References occur only in packet runtime, the DHCP unit and original BSS storage.
There are 32 source accesses: 26 in the DHCP unit already see `volatile s32`;
six in packet runtime see a plain declaration, including four stores through
explicit volatile lvalues. Values written are -1/0 in runtime and -1/0/1/2
in the DHCP state steps. No other worker owns these complete units.

Move one `extern volatile s32` declaration into the already shared
`DhcpClient.h`. Remove both local declarations and replace the four cast
stores with direct assignments. All values, expressions, source statement
order and control flow remain unchanged. The two newly-qualified accesses
are the receive callback's step gate read and reset helper's zero store.
The original reset stores state, step and reply flags in that source order;
no reordering is needed to reproduce it. This reconciles an existing native
observability contract, not proof of unique original qualifiers. Volatile
is not claimed to provide atomicity or thread synchronization.

The capacity-gated candidate build completed successfully and explicitly
recompiled both affected objects before comparison. Both complete objects
compare byte-for-byte with their saved pre-change versions, including metadata
and relocations. Thus the callback read and reset store, their ordering and
all other generated accesses remain unchanged. The DOL reproduces original
SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Complete units remain
packet runtime 24/24 and DHCP 42/42, with exact code/data and compiled source
link inputs. Full incremental comparison has zero metric, name, coverage or
retention changes. Fresh-main comparison retains +88 data bytes and zero new
functions/code with no losses; all 3,582 linked units and 17,739 retention
entries pass. Host tests and whitespace pass. The generated exception inventory
changes only the existing DHCP address-mask hit's line number.

The step-word declaration/cast discrepancy is resolved without compiler
steering, a new algorithm or synchronization mechanism. Lengthless scanning,
allocator conventions and broader output-pointer APIs remain separate; no
length/type contract is guessed for them. Keep draft with the other documented
limits and metadata hold. No held write is retried.


## Main refresh through `4bec40d6c`

Refresh reviewed head `4f029010a` against main
`4bec40d6cca74a85e91c848ea2d9f25425a313ad`. Only the generated and curated
exception-register summaries conflict. Regenerate the inventory, update its
summary counts, and retain main's download-graph and selection-plate evidence.
All source/config changes merge automatically. Main's LaunchDol recovery,
download graph and menu units remain unchanged; no main-owned compiler
exception, external handoff hold or source boundary is weakened. The DHCP
shared volatile contract, scanner return repair, lease parser and selection
predicate sources are unchanged from the reviewed parent.

Fresh capacity-gated native builds of main and this candidate both reproduce
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. Full comparison
against that freshly built main passes: zero new exact functions or code,
+88 matched and linked data bytes, no function/data/coverage loss, all 3,584
linked units exact and 17,752 retention entries without drift. Main has
3,585 linked units; the existing fold accounts for the one-unit structural
difference. Seven existing symbol renames remain; they are not new matches.
Host vector/item-factory tests, generated inventory and whitespace pass.

This is synchronization, not a new interface probe. Lengthless scanning,
allocator/output-pointer questions and the failed-metadata-write hold remain
bounded as documented above. Keep draft pending exact-head review and CI.


## Gryphon reconciliation through main `545f2e729`

Refresh reviewed head `499d57b29` against main
`545f2e729fcff6175f2b83ddf741fd2ea870951c`, which integrates the Gal Gryphon
resource loader and folds its source ranges into `Boss5GryphonBehavior`.
No competing branch owner is active. Resolve the retention-list conflict by
keeping both the existing Falz buffer and all new Gryphon entries. Preserve
main's loader, source split, globals, canonical motion accessor and typed
resource/texture globals. Preserve this branch's canonical `NJS_OBJECT *`
BML model accessor; convert its result explicitly only at the existing
integer-valued particle attachment boundary. Remove redundant resource casts
now that main provides the typed resource global. No local incompatible
accessor prototype or function-pointer cast is restored. All 181 source
accessor users still include the canonical BML header.

Fresh capacity-gated builds of exact main and the candidate reproduce original
DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`. All four overlapping
Gryphon objects compare byte-for-byte to fresh main, including metadata and
relocations: behavior 168/168, shock wave 6/6, snarl 7/7 and tornado 4/4, all
exact code/data and linked from compiled source. Full fresh-main comparison
passes with zero new exact functions/code, the existing +88 matched/linked
data bytes, and no losses. All 3,583 linked units and 17,796 retention entries
pass with no drift; main has 3,584 linked units because of the existing branch
fold. Host tests, inventory and whitespace pass. Inventory totals are unchanged.
The DHCP scanner/lease parser/volatile and selection predicate source repairs
are unchanged from the reviewed parent.

This reconciliation carries main's recovery without attributing its new match
to this branch. Lengthless scanning, allocator/output-pointer questions and
metadata holds remain unchanged. No exhausted probe or held write is retried.
Keep draft pending exact-head review and CI.


## Network configuration and photon-blast refresh through `9dcde8562`

Refresh reviewed head `19f7ad1f2` against main
`9dcde8562fbd176110243274f18215c3cbbbc19a`. No competing owner is active.
Source, splits, retention and configuration merge automatically; all 17
incoming source/header paths (including deletions) match main. Preserve
main's network-config lifecycle split/profile and photon-blast recovery.
Only the curated and generated exception summaries conflict: regenerate the
inventory, retain main's initializer evidence, and align the summary to
5,773 pragmas in 876 files, 186 overrides and 263 scheduling pragmas. The
existing DHCP scanner/lease/volatile and selection-predicate files are unchanged.

Fresh capacity-gated main and candidate builds reproduce original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Complete network-config lifecycle,
player-load and photon-blast objects compare byte-for-byte to fresh main,
including metadata/relocations. They remain exact and source-linked: 3/3,
9/9 and 8/8 respectively. Full fresh-main comparison passes: zero new
functions/code, existing +88 matched/linked data bytes and no losses. All
3,583 linked units and 17,799 retention entries pass without drift. Main
has 3,584 linked units; the existing branch fold explains the difference.
Host vector/item-factory tests, exception inventory and whitespace pass.

The unchanged-main baseline report is pinned locally with its build, original
DOL and retention-check provenance so other owners can verify and reuse it;
no binaries are shared. This refresh claims no match beyond main. All length,
allocator/output-pointer and metadata holds remain. No exhausted probe or
held write is retried. Keep draft pending exact-head review and CI.


## Recon refresh through main `78a6f8fae` with a shared baseline

Refresh reviewed head `99842fbf8` against main
`78a6f8fae432ad941677d392d332273e1079603b`. No competing owner is active.
All five incoming Recon source/header paths match main, and the earlier DHCP
scanner/lease/volatile and selection-predicate repairs are unchanged. Source
and configuration merge automatically. Resolve only exception-summary conflicts
by regenerating the inventory and retaining main's Recon compiler evidence.
Summary totals are 5,773 pragmas in 876 files, with 187 per-unit overrides.

Reuse the unchanged-main baseline sealed by the #375 owner instead of launching
a duplicate main build. Independently verify its archived report/build/check/
ordered-link artifacts, all 91 recorded tool/compiler hashes, five exact-main
tracked configuration blobs and ordered-link digest. The pinned report SHA-256
is `595fcf53782eb2e830d0180f8a5e760478883159b11c1a219a95dfd4d47e025a`.
The seal records the original-main graph hashes; the owner's checkout has since
advanced, so its current generated graph and objects are not substituted for
the sealed baseline. Copy only the sealed reports/receipts into this task.
The successful gated baseline receipt and native build log verify the original
DOL, 3,585 linked units and 17,786 retention entries without drift.

The candidate's own capacity-gated native build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Recon remains 5/5 exact code/data
and source-linked. Full comparison against the verified sealed main report
passes: zero new functions/code, the existing +88 matched/linked data bytes,
and no losses. All 3,584 linked units and 17,799 retention entries pass without
drift. The existing fold accounts for the one-unit structural difference from
main. Host tests, generated inventory and whitespace pass.

This refresh claims no Recon match beyond main. Lengthless scanning, allocator/
output-pointer questions and the metadata restriction remain unchanged. No
exhausted probe or held write is retried. Keep draft pending exact-head review
and hosted checks.


## Shared DHCP reply-output and request-status contracts

At reviewed head `846b8d8b1` on main `78a6f8fae`, trace every source and native
reference to `lbl_805D7B40`, `lbl_805D7B44` and `lbl_805D7B48`. Each is one
four-byte original `.sbss` slot. The complete call chain is connection sequence
-> `TLobby__sub_801465C0(s32 *)` -> blocking `80424D58` -> registration
`80424DCC` -> ACK processing -> parser `80423440`. The supplied destinations
are `&lbl_805D56D8` (declared `s32`), the caller's `s32 *arg0`, and `&sp8`
(a local `s32`). The parser writes assigned address, subnet mask and broadcast
respectively through these pointers, then clears each. The native option table
independently maps those source words to four-byte entries. No other caller or
address-taken reference was found.

Put the three `extern s32 *` declarations and both request prototypes in the
shared DHCP header. Replace runtime's conflicting `void *` declarations and
parameters, remove the parser's duplicate declarations, and include the shared
header in the upstream lobby caller. `80424D58` now returns `s16`, agreeing
with its sole native caller's `extsh.` at `0x80146664` and its complete result
set {-1, 0, 1}. The registration function retains `s32`, agreeing with its
sole caller's full-word comparison at `0x80424D6C`. This establishes one
truthful source contract without claiming a uniquely recoverable original
typedef. No symbol, original provider, layout, allocation, algorithm, value,
statement order, retention entry or link selection changes.

Outputs remain borrowed. Success writes and clears them before state 3. Failure
leaves them populated until reset; this change does not add cancellation cleanup,
ownership transfer, synchronization or lifetime enforcement. Unused opaque
arguments remain opaque. Adjacent hostname/lease/router/init result interfaces
remain separate debt, including the previously held dispatcher-reset boundary.

The capacity-gated build explicitly recompiles runtime, parser and lobby caller.
All three complete objects compare byte-for-byte with their saved pre-change
objects, including metadata and relocations. They remain 24/24, 42/42 and
40/40 respectively, exact code/data and compiled-source-linked. The DOL
reproduces original SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Full incremental checks show zero metric/name/coverage/retention changes.
Verified main comparison keeps +88 data bytes, zero new functions/code and no
losses; all 3,584 linked units and 17,799 retention entries pass without drift.
Host vector/item-factory tests and whitespace pass. The exception inventory
changes only the existing mask-expression line number. No compiler steering,
adapter, new cast or artificial object ownership is introduced.

The lengthless scanner is still held: the original signed `base - cursor`
guard at `0x80424888` does not establish a forward-read bound. Received length
is available to the callback but is not carried with the accepted reply into
all parser calls. A 1500-byte allocation alone cannot establish the received
record extent, so no length or malformed-packet behavior is invented.

Allocator tracing confirms a numeric slot in native r3, with size in r4, rather
than a TLobby object. A complete repair must also reconcile the request task's
offset-0x24 slot field and methods currently assigned to character selection,
plus the allocator/reset caller declarations. The reset helper's extra argument
spelling and the slot-validation helper do not prove an enforced range. Do not
substitute a guessed class or add bounds. This broader caller/task audit remains
separate from the completed three-slot repair. The metadata hold is unchanged;
keep draft pending exact-head review and hosted checks.


## Current-main Falz integration after the DHCP contract checkpoint

Publish the independently reviewed DHCP contract checkpoint `adc1a464e`,
then integrate main `30d8a1266113d69d2d36bee04bf054f85866ce45`, which advanced
during that work with the Falz Type 1 death-cutscene recovery. Only exception
summary documents conflict; retain main's new evidence and regenerate totals
(5,773 pragmas, 876 files, 188 overrides). DHCP repair source files are unchanged.

The first combined build exposes the newly recovered Falz model record's
integer `object` field: it cannot accept this branch's canonical `NJS_OBJECT *`
return. All uses are assignment from that accessor and the two model-drawing
calls. Make the field `NJS_OBJECT *` and pass it directly to drawing. Keep the
existing texture word and archive-accessor boundaries; do not restore a false
model getter or hide the new field mismatch with an integer conversion. The
existing native class-size assertion remains 0x90. All 182 source model-getter
consumers include the canonical header.

A fresh capacity-gated native main build is sealed locally with its report,
check/link receipts, original DOL verification, exact configuration/graph text
snapshots and tool/compiler hashes for reuse. The corrected candidate's gated
build also reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Its complete Falz object is
byte-identical to fresh main, including metadata and relocations; the unit
remains 6/6 exact code/data and source-linked. All three DHCP repair objects
remain byte-identical to the saved pre-repair objects as well. Full fresh-main
comparison passes: zero new functions/code, existing +88 data bytes and no
losses, 3,585 exact linked units and 17,811 retention entries without drift.
Main has 3,586 linked units because of the existing branch fold. Host tests,
inventory and whitespace pass. No new steering or original-provider change.

The output/status contract repair remains the substantive checkpoint; no Falz
match credit is attributed beyond main. Scanner length, allocator/task ownership,
adjacent legacy APIs and the metadata restriction remain bounded as above.
Keep draft pending current-head independent review and hosted checks.


Main then advances to `1a9c290489ea7a20edaf5f960e57bfffef5a5e14` solely
by publishing the README progress table for source commit `30d8a1266`.
Merge that publication too. Its complete diff is README-only; source,
configuration, tools, splits and build/link inputs are identical to the
freshly built baseline. README is not a Ninja input, so the native and
regression validation above remains applicable without a redundant build.


## Numeric load-slot API and request-task ownership

Start at reviewed head `0b3db2fb6` on main `1a9c29048`. All four model-load
request records store a signed slot in their `ctx` word at +8. The request
constructor copies it to +0x24 in the 0x78-byte `TChCrLoadGmNjReq`; it is not
a lobby address. Native allocator r3 is used only as a numeric index, while r4
is a signed size. The zero-size wrapper simply forwards that index. All native
and source calls reconcile: two cursor-get callers, one direct advance caller
and the wrapper's advance call, with no additional address-taken reference.

Replace the two false TLobby methods with shared C-linkage functions
`advance_character_load_buffer(s32 slot, s32 size)` returning the existing
32-bit address word and `get_character_load_buffer(s32 slot)` returning the
existing pointer. Preserve every unsigned address operation, signed slot/size
comparison, array index, allocation size, store, return and validation call.
The existing validation helper's void early returns do not enforce bounds;
no new guard or assumed valid slot range is introduced. Original buffer
providers and native address-word representation remain unchanged.

The native task dispatcher passes its unchanged request `this` to 0x8028C650,
which then passes the same pointer to 0x8028C8E0. Move those two methods from
`TAdSinglePlyChrSelectGC` to their real `TChCrLoadGmNjReq` owner. Declare
its signed slot at +0x24, state at +0x2C, fixed character copy at +0x30, claimed
word at +0x6C and signed lifetime counter at +0x70. The 48-byte copy does not
guarantee NUL termination. Assert these offsets and the existing 0x78 size.
Replace the constructor/release helper's fake field overlays with these actual
fields. Pass the real task explicitly for dispatch and queued destruction, and
pass the incoming parent explicitly to base construction as native r4 already
does. Both allocator callers now pass a numeric slot directly. The texture
unit's unrelated inherited destruction declarations/cast remain separate; this
change adds the canonical destruction header only to the menu task dispatcher.
The existing character-selection layout is otherwise left unchanged.

Naturally emitted symbols and symbol metadata change only four exports:
`start_character_load_task` and `try_acquire_slot` gain the correct task owner;
the two buffer helpers gain the free-function names above. No new hand-mangled
stand-in, adapter, assembly, padding or compiler steering is introduced.

The first capacity-gated candidate build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All six edited units remain exact
code/data and source-linked: texture/update 12/12, load starter 1/1, request task
4/4, release helper 1/1, slot acquisition unit 14/14 and folded cursor unit 9/9.
Complete ELF comparisons cover sections, section metadata, normalized string
tables, symbols and every relocation, canonicalizing only the four export
renames. All six match. Five raw objects differ only because of those names;
all other 3,580 compiled objects are byte-identical. The set of 3,585 compiled
source inputs and 1,362 selected original inputs is unchanged, with no provider
substitution. Full incremental checks show zero metric/coverage/retention
changes and precisely four function renames. All 3,585 linked units and 17,811
retention entries pass without drift. Verified-main comparison retains +88
data bytes, zero new functions/code and no losses. Host tests, inventory and
whitespace pass.

## Received-length audit: exact remaining evidence gap

Trace all native/source producers and parser calls without changing behavior.
UDP input 0x80420DE4 removes eight header bytes from packet totals/fragments;
the loaded UDP `len` field does not establish the callback extent. Producer
0x80421F10 constructs a stack record with handle/flags +0, signed 16-bit length
+2 and destination +4. It computes packet total minus first-fragment length
and narrows with `sth`. Dispatcher 0x80421FB8 allows event 0 to reduce length,
clamps against the original signed length, copies fragments to the supplied
destination, then invokes event 1. Zero-length/NULL checks are not DHCP bounds.

DHCP event 0 supplies scratch at +0xBB8 without capping length to 1500. ACK
states 2/4/5 copy exactly the record length into reply at +0x5DC and retain only
bytes plus a flag. No accepted-reply extent or tail clear is present. The timer
later passes only a pointer to configuration/lease parsing. All references are
accounted for: 13 scanner calls, two lease-parser callers and one configuration
caller. The scanner's signed `base - cursor` comparison is not a forward bound;
tag/length reads and the callback's header reads lack an established minimum.

There is no persisted accepted-reply extent, parser length argument or proven
end-to-end DHCP payload range to propagate. Region capacity, signed field width,
packet-pool capacity and outgoing packet size do not provide that evidence.
Adding storage, bounds or guards would alter native behavior, so no such probe
is attempted. A shared eight-byte receive prefix is a possible separate source
cleanup, but the dispatcher also serves raw IPv4/IPv6 producers 0x80421938 and
0x80421AD8 with different tails and an incompatible local callback cast. Audit
those producers and registrations together before changing that interface.

The reset-helper extra-argument contract, native pointer/address-word globals,
other legacy callback interfaces and metadata restriction remain held. Keep
draft pending final exact-head review and hosted checks.


## Current-main integration after the slot-ownership checkpoint

Publish reviewed checkpoint `8a4b57975`, then integrate main
`b3062dc640fa3ab9463269dca4e80fa057df5ec7`, which advanced during the audit
with the sprite and challenge-enemy-set work. Only exception documents conflict.
Retain main's source/configuration changes and evidence; regenerate summary
totals to 5,773 pragmas in 876 files and 189 overrides. The repaired request-task,
slot helper and release-helper source files are unchanged from the checkpoint.
The automatic TLobby header merge retains main's unrelated API cleanup and the
reviewed removal of the false allocator members.

Fresh capacity-gated main and candidate builds reproduce the original DOL
SHA-1. A reusable main seal preserves report/check/link receipts, exact graph/
configuration text and tool/compiler hashes locally. Full comparison against
that main passes: zero new functions/code, the existing +88 data bytes, no
losses, all 3,587 linked units exact and 17,812 retention entries without drift.
Main has 3,588 linked units; the existing branch fold explains the difference.
Both incoming complete objects compare byte-for-byte with fresh main:
`ChallengeEnemySet` 1/1 and sprite 8/8, exact code/data and source-linked.
All six slot/task objects still pass the complete ELF comparison with only
the four intentional export names normalized. Host tests, inventory and
whitespace pass. No additional technical probe, source workaround or exception
is introduced. Keep draft and the previously documented holds.


## Character-load reset, address words and completion contracts

After the numeric-slot/owner repair, audit the remaining character-load
interfaces against every source and native reference. The reset helper at
0x8028D738 consumes only the numeric slot in r3, and its shared declaration and
definition already agree on `s32(s32)`. Both callers ignore the result. In
`TChCrLoadReq::reset_request`, r4 is a residual appearance-table offset, not a
second argument read by the callee. Include the existing shared header and
remove that false second parameter and local `void(s32, s32)` declaration.
All three complete affected/caller objects remain byte-identical.

The two buffer globals have only two source units of use. Their native storage
is four bytes; allocation sizes are 0x28000 and 0x50000, and cursor addition,
end comparisons and failure behavior use unsigned 32-bit address arithmetic.
Declare both globals once as `u32` in `CharacterLoadBuffer.h`, remove conflicting
local pointer/word declarations, and make allocation-to-word conversion explicit
at both producers. Remove redundant word-to-pointer-to-word conversions at the
existing `safe_free(u32)` callers. This is a shared native representation, not a
claim to recover an original pointer typedef. Keep the cursor arithmetic and
pre-check advance unchanged: replacing these operations with pointer arithmetic
would require unsupported allocation-range assumptions on failed requests.
`safe_free`'s inherited no-argument `xfree` source declaration is separate debt;
this change does not claim to repair that implementation.

The texture-request unit contains two calls to TObject destruction. The native
callee consumes only r3, sets object flags at +4 and has no return-value
contract. Use its existing shared `void(void *)` header and direct calls, removing
the incompatible function cast, local `s32(void *, int, int)` declaration and
fake extra arguments. The model-request method in that same unit belongs to
`TChCrLoadGmNjReq`. All four producer records pass a signed completion mask at
+0xC and a borrowed `u32 *` flags word at +0x10; its constructor stores those at
+0x20 and +0x28. Give those two actual fields truthful types and assert offsets.
After the existing release/store operations, the natural
`*completion_flags &= ~completion_mask` followed by destruction expresses the
native `lwz/andc/stw` sequence. Add no ownership or synchronization promise and
preserve the release, flag-store and destruction order.

The capacity-gated native build passes and reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All seven complete objects affected by
the adjacent probes, including both allocation/cursor units, the constructor,
texture/update method and all slot-task callers, are raw byte-identical; code,
data, symbols, metadata and relocations therefore agree without normalization.
All 3,662 compiled source objects are unchanged by those probes. Combined
incremental checks against the pre-reset report show no metric, coverage,
function, provider or retention changes: all 3,587 linked units are exact and
17,812 retention entries have zero drift. Host tests, exception inventory and
whitespace pass. No new compiler pragma, wrapper, dummy argument or steering
local is introduced. The DHCP extent gap, dispatcher callback contracts and
allocator/free internals remain bounded separately. Keep draft.


## Main integration after the reset/address/completion checkpoint

Publish the independently reviewed contract checkpoint `b68b6afb9`, then merge
main `f0f05f3afe56fd2b71e9dc1fe946e2fa03c84b86`. The source/configuration merge
is automatic; reconcile only exception documents and regenerate the inventory
(5,774 pragmas in 877 files; 189 per-unit overrides). Preserve main's Moja
constructor and collision-query recovery, including source-provider selections.

Fresh capacity-gated main and candidate builds reproduce the original DOL
SHA-1. The sealed main report, successful build/check receipts, ordered inputs,
configuration/graph snapshots and compiler/tool hashes are independently
verified. Against that exact baseline, full checks pass with zero new functions,
zero code delta, the existing +88 data bytes and no losses. All 3,588 branch
linked units are exact; all 17,833 retention entries have zero drift. Main has
3,589 linked units, with the branch's existing fold explaining the difference.
The eight repaired/related complete objects remain raw byte-identical to their
saved checkpoint objects. All three incoming Moja, collision-query and player
objects are raw byte-identical to fresh main. Host tests, inventory and
whitespace pass. The DHCP length, callback and allocator implementation holds
remain separate; keep draft and the metadata restriction.


## Explicit allocation/free wrapper arguments

The preceding address-word cleanup exposes one additional bounded wrapper
mismatch at 0x8007EB94..0x8007EBDC. `memory.h` already declares
`void *xmalloc(u32)` and `void xfree(void *)`, consistent with their definitions.
Native global `operator new` forwards its size in r3 directly to xmalloc.
Native `safe_free` compares its address in r3 with zero and, if nonzero, calls
xfree with that same r3. The free implementation then forwards the pointer and
supplies allocator context in r4.

Include the existing memory header and remove the false local
`int xmalloc__FUl(void *)` and no-argument `s32 xfree__FPv()` declarations.
Global new now returns `xmalloc(size)` directly. Keep `safe_free(u32 address)`'s
public address-word interface and original null check, spelling the actual
call as `xfree((void *)address)`. The conversion is the explicit existing native
word/pointer boundary. No allocation size, allocator, provider, failure rule,
exception behavior or ownership promise changes.

The capacity-gated native build passes, reproducing the original DOL SHA-1.
The complete wrapper object is raw byte-identical, including both functions,
all metadata/symbols and every relocation. All ordered source and original link
inputs are unchanged (3,588 source; 1,360 fallback). Incremental validation has
zero metric, coverage, function or retention drift. Against sealed main
`f0f05f3af`, the existing +88 data bytes, zero new functions/code and no-loss
result remain: 3,588 exact linked units and 17,833 valid retention entries.
The direct wrapper mismatch is resolved; this does not infer wider allocator
ownership or rewrite unrelated address-word APIs. DHCP extent propagation and
broader dispatcher callback contracts remain separate, and metadata is still
held. Keep draft pending current checks and final review.


## Shared receive prefix across UDP and raw IP

Audit the receive contract across all three native producer paths rather than
inferring a DHCP-only callback layout. Raw IPv4 at 0x80421AD8, raw IPv6 at
0x80421938 and UDP at 0x80421F10 all construct an eight-byte prefix: signed
16-bit selector/flags at +0, signed 16-bit length at +2, destination pointer at
+4. Their tails differ: IPv4 has two address words (record size 0x10), IPv6 has
two 16-byte addresses (size 0x28), and UDP has two 20-byte NetworkAddress records
plus a port at +0x30 (size 0x34). The UDP record-copy helper copies 0x32 bytes of
meaningful fields, so copying only the common prefix would lose metadata.

Define `NetworkReceivePrefix` once with offset/size assertions. Embed an actual
first-member prefix in every producer record and assert every tail offset and
complete size. Pass the complete producer records through the existing void
record interface; the dispatcher interprets their initial member through the
shared prefix. Use the same prefix view in DHCP, replacing its separate padded
record overlay. The signed length, buffer assignment, all address/port stores,
clamping and fragment-copy sequence are unchanged. Callback byte-pointer
exports, registration address words and the full UDP record-copy helper stay
unchanged. No symbol rename or compiler steering is needed.

The dispatcher at 0x80421FE8 executes `extsh.` on the event-0 return. Replacing
its short-result view with an unconverted full-word result would change a value
such as 0x10000 from accepted to rejected. Both known callback implementations
also narrow their event argument. Keep the existing callback/result interfaces
while their broader contracts remain unproven. Raw IPv4 delivery loads a
callback from table +0x10, stride 0x1C (0x8040E288); raw IPv6 uses +0x28, stride
0x34 (0x80410510). The available source and registrations do not establish one
canonical C++ function type for every raw callback implementation. This prefix
repair neither claims to resolve that ABI debt nor guesses a callback type.

The accepted DHCP extent still is not persisted before pointer-only parsing.
The shared signed field is not a minimum packet size or an input bound; no
length guard, tail clear, added storage or receive behavior is introduced.
The EXI declaration reserved for separate modem work is preserved exactly, and
ModemRuntime, NetworkMessageTransport and SocketProtocolRuntime are unedited.

Final capacity-gated native validation reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. All four saved complete network
objects are raw byte-identical, including metadata/symbols and relocations;
all 3,662 compiled source objects have unchanged hashes. Ordered linker inputs
are unchanged (3,588 source; 1,360 original fallback). Incremental full checks
have zero metric, function, coverage or retention drift. Against sealed main
`f0f05f3af`, retain the existing +88 data bytes, zero new functions/code, no
losses, all 3,588 linked units exact and 17,833 retention entries without drift.
Host tests pass. Regenerate the exception inventory for shifted source lines;
its counts remain unchanged. Keep draft and the metadata restriction.


## Main integration for rope collision and ADX decoding

Integrate main `1a18b4bd7577af4ee367317064e020d1f91ce5a8` into reviewed receive-prefix
head `ac0a1995b`. Source, headers and configuration merge automatically; only
exception documents conflict. Preserve main's rope collision and ADX decoding
recovery, retain the existing branch contracts in TLobby.h, regenerate the
inventory, and synchronize curated counts (5,767 pragmas in 877 files; 189
per-unit overrides). No received-prefix, DHCP, callback or metadata hold changes.

A single fresh capacity-gated main baseline is sealed locally with report,
successful build/check receipts, ordered providers, exact graph/config snapshots
and tool/compiler hashes for independently verified reuse. Main and candidate
reproduce the original DOL SHA-1. Full no-loss comparison passes with the
existing +88 data bytes, zero new functions/code and no losses. All 3,589 branch
linked units are exact and all 17,840 retention entries have zero drift.
Main has 3,590 linked units; the prior branch fold explains the difference.
All ten incoming complete source objects are byte-identical to fresh main,
and every saved receive-prefix, slot/reset/completion and allocator-wrapper
object comparison remains raw byte-identical, including relocations. Actual
branch inputs are 3,589 source and 1,357 original fallback objects. Host tests,
exception inventory and whitespace pass. Keep draft and all existing holds.


## Reset returns the shared native address word

With the allocation globals, cursors and related buffer API already expressed
as native `u32` words, the reset helper still returned `s32` and read the extended
base through `*(s32 *)&chr_select_load_buffer`. Audit this separately from the
held network dispatcher reset-status interface. At 0x8028D788 and 0x8028D7B4,
the native reset computes an address in r3, stores that same word in the cursor
array and returns it. The absent-base path returns zero; both source/native
callers discard the result. Both allocation producers already explicitly convert
allocated pointers to unsigned address words.

Use one `u32 TLobby__sub_8028D738(s32 slot)` declaration in
`CharacterLoadBuffer.h` and include it directly at both callers. Remove the old
signed declaration from `TLobby_8028D714.h`. The defining function uses one
unsigned address variable and direct unsigned word arithmetic, eliminating the
signed global overlay. Preserve the signed slot/index variables, `slot < 4`
branch, call to `TLobby__sub_8028D7D0`, and its current lack of enforcement.
This recovers a shared native representation, not an original pointer typedef
or class owner. No new slot bound, guard, pointer arithmetic, allocation behavior,
export name or provider is introduced.

The capacity-gated build reproduces the original DOL SHA-1. All three complete
affected objects, including both callers, are raw byte-identical with unchanged
symbols and relocations. All 3,663 recorded compiled-object hashes and ordered
linker inputs are unchanged (3,589 source; 1,357 original fallback). Incremental
checks have zero metric, function, coverage or retention drift; full comparison
with sealed main `1a18b4bd7` retains the existing +88 data bytes, zero new
functions/code, no losses, all 3,589 linked units exact and 17,840 retention
entries without drift. Host tests, inventory and whitespace pass. Keep draft;
DHCP extent, callback ABI, network reset-status and metadata holds remain.


## Match legacy DHCP behavior, including its bugs

The matching target is the original behavior, including apparent bugs. Keep
hardening ideas separate from the exact path. The missing accepted-reply extent,
unchecked scanner and fixed-size option copy are documented legacy behavior;
this PR does not silently add length fields, input guards or tail clears.

A new bounded ingress audit does not supply a hidden DHCP size invariant.
Ethernet ingress rejects individual frames above 1514 bytes, but IPv4 reassembly
can combine up to eight fragments using two 0x2000 pools. Two ordinary fragment
payloads of 1480 and 1000 bytes fit those resources and yield 2472 bytes after
UDP-header removal. That is a resource-feasibility example, not an exploit or an
end-to-end DHCP demonstration. IPv4 checks header size/version/checksum and that
declared total length covers the IP header, without proving total length fits
the received bytes. UDP copies its eight-byte header and subtracts it without an
established BOOTP minimum. Neither frame MTU nor allocation capacity proves
`BOOTP minimum <= DHCP payload <= 1500`; no such bound is inserted here.

Add original-free host characterization tests in
`tools/tests/test_dhcp_legacy_characterization.py`. They compile the actual
checked-in scanner, option-setter and option-record definitions, not rewritten
copies of their algorithms. Fully allocated fixtures cover padding/end markers,
zero/255 option lengths, stale bytes after a logical short copy, an advertised
value spanning old bytes, scanning beyond the purported forward limit,
fixed-table-size option copies/string termination and NULL-value clear rules.
All seven cases pass, as does the full 275-test tool suite. GCC permissive mode
is used only in this host harness to admit the original explicit 32-bit address
casts on a 64-bit host. The fixtures stay within allocated arrays. These tests
characterize host-observed logic and byte persistence; they do not prove native ABI,
ingress safety, the complete ACK/timer handshake, or an exploitable packet.
No game source, native build graph or selected provider changes for these tests.

## Raw callback target audit and rejected reset-status probe

The raw-callback audit now closes the inspected registration graph. IPv4 config
0x803F8930 installs BSS table 0x805B4F84 with one entry; IPv6 config 0x803F87E0
installs 0x805B38A0 with one entry. Their sole callers are protocol initialization.
Initialization explicitly clears the active flags at 0x8040DE04/0x8040FFAC;
receive dispatch requires the flag to equal one before loading callback words.
No raw registration writer, concrete callback address or address-taking data
edge was found in this DOL/source graph. The exposed UDP registration path
creates/binds/connects a UDP entry and cannot populate either raw table. These
are dormant library paths in the inspected graph, not proof of a canonical ABI
for hypothetical providers or arbitrary external code writing their BSS.

Separately, exhaustive native runtime-reset returns are only -1 or 0, and the
sole wrapper consumer interprets signed 16-bit status. That supported one new,
bounded shared `s16(void)` wrapper/header/caller probe without claiming the
historical typedef. Source-quality review passed. Native validation rejected it:
the wrapper gained a sign-extension instruction (four code bytes), while the
caller retained its instruction body but grew its frame from 0x10 to 0x18.
The original-DOL check failed. Fully restore the candidate rather than add
padding, casts, compiler pragmas, change the underlying return type or rewrite
counter lifetimes to compensate. The reset-status mismatch remains documented.

The restoration build reproduces original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Dispatcher, startup caller, runtime
and packet-runtime complete objects are byte-identical to their saved versions,
including relocations; independent review verifies restoration. Main
`79768ce7d` adds only Moja documentation to validated native main `1a18b4bd7`.
The documentation merge is published; prior native validation remains scoped to
unchanged source/configuration inputs, with no old receipt relabeled as a new
build. Keep draft and the metadata restriction. Any DHCP hardening remains a
separate behavior-changing project, not an exact-match repair.


## Latest-main reconciliation after characterization checkpoint

Publish characterization checkpoint `19d5cbeb6`, then integrate main
`5f837b43888ac935b8a74fad20701c9195ee7338`, which advanced during that work.
Retain its De Rol Le and player-unit recovery, texture-reader cursor and adjacent
original-data/category accounting, and all source evidence. The configuration
conflict joins main's packet-header retention name with the existing DHCP
release/request names; none is dropped. The Boss7 automatic merge retains the
shared canonical BML declaration and explicit resource-pointer boundary.
Regenerate inventory and curated counts (5,770 pragmas in 878 files; 189
per-unit overrides). DHCP code and the characterization tests are unchanged.

Fresh main and candidate capacity-gated builds reproduce the original DOL.
A new pinned baseline is sealed for independently verified reuse without
relabeling older receipts. Full comparison passes: existing +88 data bytes,
zero new code/functions, no losses, all 3,591 linked units exact and 18,276
retention entries without drift. All seven incoming complete objects match
fresh main; all 19 saved contract-object comparisons remain raw byte-identical,
including relocations. Actual branch inputs are 3,591 source and 1,356 original
fallbacks. Main has 3,592 source inputs and 1,358 fallbacks; the prior branch
fold/provider choices remain visible. Seven actual-source characterization
cases still pass after the merge. Original behavior, including the documented
bugs, is retained. The reset-status mismatch and metadata restriction remain;
no hardening or speculative ABI change is introduced.


## Spatial-audio and ADXF main refresh

Verify remote head `9f798d728` and no competing owner, then integrate main
`fffd67d0c35e1fdaf17880c563739750e7c35813`. GitHub reports a real dirty conflict,
not merely a pending calculation. Source merges automatically. Join both sides
of the retention-list conflicts (new spatial-audio functions/data plus the
existing character-buffer helper/cursor); no entry is dropped. Preserve main's
ADXF/spatial-audio source, SDK declarations, compiler settings and generic
pragma-register prose, together with the prior branch contracts. Regenerate
inventory to 5,772 pragmas in 878 files and 190 per-unit overrides. No DHCP,
callback, reset-status or characterization-test change is made.

Fresh capacity-gated main and candidate builds reproduce the original DOL
SHA-1. A new pinned main report/build/check/provider/provenance seal is available
locally for independent reuse. Full comparison passes with the existing +88
data bytes, zero new functions/code and no losses: all 3,593 linked units exact
and 18,300 retention entries without drift. Actual branch inputs are 3,593 source
and 1,354 original fallbacks; main has 3,594 source and 1,356 fallbacks. Prior
branch folds and original-only accounting remain explicit and unchanged.

Nine of the ten incoming complete source objects are raw byte-identical to
fresh main. `TLobby_802409AC.o` is not whole-object identical: its `.debug` gains
36 bytes in three DWARF1 records and `.rela.debug` gains two references (24
bytes), with corresponding debug-reference shifts. Independent section/record
review finds all other payloads identical, including both text sections, all
allocated data, symbols, string tables, compiler metadata and every non-debug
relocation. The unit's retained source declarations affect debug type interning;
this debug-only difference is disclosed rather than normalized away or called
whole-object equality. All 19 saved contract-object comparisons remain raw
byte-identical, including relocations. Seven actual-source characterization
cases, inventory and whitespace pass. Keep original behavior and bugs, the
metadata restriction and all documented interface holds; keep draft.
