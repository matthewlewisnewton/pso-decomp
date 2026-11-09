# Quest-download cache relocation and observed entry gates

`sub_803E8924` (`0x803E8924`, 504 original bytes) is now defined as partial
C++: **97.70635%, 508 compiled bytes** in both the standard report and the
relocation-sensitive probe. It adds no exact function or source-linked coverage.
The existing `void(s32 cachedId)` boundary remains provisional.

## Preserved relocation behavior

The function returns immediately when the ID's signed page field already
selects the append page. Otherwise it decodes the record's little-endian
length, rotates for space if needed, reserves the destination span and writes
its trailing terminator. It then rechecks whether rotation selected the source
page. That second return deliberately retains the reservation without copying.

For another source page, it copies the bounded name into its real local buffer,
finds the sorted index stopping node, and checks record-pointer identity. On
identity it redirects the node before the forward byte copy, clears the old
name length and invalidates the old ID. The stopping node is unconditionally
dereferenced, as in the original. Valid cached IDs, bounded records/names,
append capacity and a consistent non-null search stop remain preconditions.

The source uses only the actual `lbl_80591EC8` byte array and the existing typed
bucket/node index. It changes neither node lifetimes nor ownership. It preserves
[the source-page reservation witness](quest-download-cache-lifecycle.md) and adds
no null guard, repair policy, fictitious object, padding or pragma.

Four ordinary count/lifetime forms were measured. The retained signed count
scores 97.70635%; decoding length before borrowing the original pointer is
unchanged. An unsigned count and a separate remaining-count variable each score
97.269844%. All compile to 508 bytes and preserve the previous exact functions
and five partial scores. Stack/name-buffer placement, register allocation and
an extra count transfer remain different; these bounded results do not show
that exact source is impossible.

## Continuous comparison with recovered relocation

The private harness now executes recovered relocation on the candidate side,
with the original instructions on the native side. Its 79 cases retain the
previous 73 lifecycle cases, including 160 mixed relocation calls, producer
snapshot reloads, capacity reuse and the source-page reservation/reuse witness.
Full nonstack data memory, normalized provider traces and meaningful returns
agree; stack pointers/nonvolatile registers restore on successful returns.
Expected precondition stops check their native fault types and sites, with
memory/trace agreement up to the stopped low-address access.

Six added cases execute the actual outer `EEDC0`, `EEF2C` and `EF958` entries.
With `lbl_805D7900 == 0`, they return three without cache writes, mutation calls
or access to deliberately null request inputs. Synthetic enabled-flag controls
with handle minus one return minus three. These controls prove those guards'
behavior; they do not establish that the enabled state occurs in the game.
The tests remain bounded, with hooked string/seek/read providers, rather than
full-provider or exhaustive reachability proofs.

## Observed ordinary flow versus lower-level witnesses

An independent named-reference census at draft `34dd35d745da73e5730f236f080fc7a0049b2531`
(main `6e880491f`) inspected all 4,970 active original objects. It rechecked
earlier dispatcher evidence against the native bytes. A subsequent rebind after
merging main `fe6cdb141` inspects 4,973 active objects and preserves the same
reference topology and wrapper/function bytes:

- Fifteen observed wrappers issue requests 15, 16, 19, 20, 21, 28 and 32 through
  40. They omit request 24, the sole identified dispatcher route into `EE2F4`,
  then `EE580`, then `EEDC0`/`EF958`. `EEF2C` is also called only from `EE2F4`.
- The mode flag has seven direct references, all SDA-relative. Its only named
  store writes zero at `0x803E5CAC`, from the zero value defined at `0x803E5BC0`.
  The other references read it; no named address escape was found.
- Ordinary startup loads the native resource `Ask_n.dic` into ARAM, configures
  its provider through `F0C04`, and initializes through requests 32/28. The
  inspected fixed local dictionary image selects page zero and initially has
  eight empty cache chains. Its private hash/metadata and the census are retained
  locally; no asset bytes are published.
- ASK startup checks signature and read lengths. It does not validate key
  uniqueness or the lifecycle bounds. The checksum routine's three callers
  belong to other `TQuestListVM` flows; no checksum gate was found in this chain.
- The cache write hook at `0x803E8788` returns minus one without writing. Save
  callers therefore do not establish persistence of modified cache bytes.

Under that fixed-image and observed ordinary-route scope, the lower-level
counterexamples are excluded: the mutation requests have no observed wrapper,
the observed mode store disables their entries, and the initial image contains
none of the counterexample records. The previous snapshot round trips copy
producer bytes into the test provider; they are not native persistence tests.

This does not establish a universal constant flag or rule out arbitrary exported
or computed calls, alias-derived writes, or replacement ARAM images. A positive
`EF958` path also needs a live cache slot, valid cached ID and cached-record key
bit. Direct relocation tests do not prove those upstream conditions occur.
No enabled game execution/request trace or shipped reachability witness was
obtained. The lower-level witnesses remain useful limits to a broader API claim,
not evidence of a shipped crash or a reason to alter original behavior.

Native/no-loss results and exact-head independent review accompany publication.
The unit remains incomplete and unlinked; the separate search sentinel sign-off
gate remains unresolved.
