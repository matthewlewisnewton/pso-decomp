# DHCP domain and DNS output contract

This bounded repair concerns the accessor at `0x80424910`, originally annotated
`validate_slot_buffers__6TLobbyFlPvPvPv`. It follows the lease/router declaration
repairs and does not reopen the rejected allocation, queue-adjacency or private
ABI probes. Preserve original behavior, including failures and stale outputs.

## Four explicit arguments

The old declaration is a **static** TLobby method. Its first argument is an
explicit argument, not an implicit `this`. The definition returns a word and
accepts `s32, void *, void *, void *`; its sole source caller instead declares
an opaque four-pointer function returning a short. Across 5,021 original split
objects, exactly one zero-addend `R_PPC_REL24` targets the accessor: misc object
`TLobby_801461EC.o`, offset `0x4DC`. The native call at `0x801466C8` supplies
four arguments in r3–r6 and consumes the result with signed-short extension.
Observed direct references do not rule out unseen or constructed callers.

The unread first argument remains opaque and in place. The remaining arguments
are the domain destination in r4 and two four-byte DNS destinations in r5/r6.
The domain destination is the existing `u32 lbl_8050C684[64]` storage (256 bytes);
use only a `char *` object-byte view at the call, without changing its storage.
The other destinations are existing `s32` words at `0x805D56DC` and `0x805D56E0`.
The original option table identifies getter ID 3 as a 0x100-byte string, populated
from DHCP option 15, and IDs 4/5 as four-byte words populated from the first two
words of option 6. These observations support outputs, not a historical class,
typedef, argument meaning or ownership claim.

## Behavior retained

The accessor clears the volatile diagnostic, accepts states 3/4/5 and otherwise
sets diagnostic 2 and returns -1. In accepted states it calls getters in order
4, 5, 3, retaining error precedence 0xE, 0xF, 0xD, and returns zero even after
getter failures. Every getter call still executes after earlier failure. The
generic getter permits null outputs and copies stored data to a nonnull output
even when its present flag is clear. No early exit, clearing or synchronization
is added. The string getter has no destination-bound parameter; the table size
and destination allocation are not a bounds or ingress-safety proof.

## Discriminating controls

Twelve isolated controls use actual source bodies, declarations, active pragmas,
`types.h` and resolved native compiler profiles: GC/1.2.5n `-O4,p -inline off`
for the producer and GC/2.6 `-O4,s -inline off -sdata2 4` for the full caller TU.
They run under the existing workspace/capacity locks without changing production
source or native outputs. Four static-member controls independently vary output
typing and result width; three positive C controls vary ownership/signature.
All seven reproduce the complete 224-byte function and relocation tuples with a
32-byte frame. An explicitly negative control drops the first argument: its
220-byte result differs and is never a production candidate.

Four caller controls vary result width and output typing independently. Both
short-result forms reproduce the complete 308-byte caller and relocation tuples
under only the explicit export-target mapping. Both word-result forms produce
304 bytes with different status checking. No control proves a unique historical
signature; together with native callers and return values, they support one
truthful shared current interface, with the unread argument retained.

## Accepted shared interface and validation

Use C linkage `s16 dhcp_copy_domain_and_dns(void *, char *, s32 *, s32 *)` in
`DhcpClient.h`. Remove the static member and conflicting local alias; rename
only the producer signature/export, preserve its entire body and all four
caller arguments, and add the domain byte-view conversion. Rename the one
symbol annotation at the same address/size. No force-active entry existed;
none is added. Link selection, splits, compiler settings and other APIs stay.

The first native candidate passes. Both **complete compiled** producer and
caller ELFs agree after exactly one audited symbol-name mapping, allowing only
its string-offset/physical-layout consequences. Symbol/section order, semantic
metadata, all code/data/debug payloads and every raw relocation byte remain
identical. The other 3,663 of 3,665 compiled objects are raw-identical. Separately
regenerated original-reference objects change their `.strtab` ordering: they are
**not** claimed whole-object equal; all other canonical sections and mapped
symbol records agree. These reference objects are not the selected providers.

Original DOL SHA-1 remains `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
Incremental no-loss, coverage and retention checks have zero drift, apart from
the recorded symbol rename. Comparison against sealed main `96fda4ce` passes:
3,599 exact linked units, 18,428 retention entries without drift, existing +88
data bytes and no new function/code gain or loss. Ordered providers remain
3,599 source and 1,347 original inputs. All fourteen existing host tests pass.
Independent source/native review passes; exact-head review gates publication.

Only this accessor contract is repaired. Lease/router declarations remain
validated. Adjacent initialization/hostname interfaces, locked allocator,
queue adjacency, private creator/raw-callback/reset ABI and metadata holds stay.
The scanner remains lengthless with its original behavior. Keep draft.
