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
