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
