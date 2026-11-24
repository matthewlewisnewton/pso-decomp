# DHCP accessor contracts

This independent extraction starts at main
`cda82a7aad7de1bf9b86470002df3f68d1c8c039`. It carries the bounded repairs
from #303 checkpoints `140421a2b4a782356e8bd3e8f6f1d58b24de1c3a`
(option setter), `32256785a7f5eb1f1b530344ac20e9101373102e` (lease),
`fbab7d9cbdcc47d33cb78d3dd0cb635cd7301e05` (router),
`aae25e4582a1c9ff572073f2e25f5c978ec4e6a0` (domain/DNS), and
`deef135946b7f834a12a6e6bde9247ab69b70791` (hostname and characterization).
Those commits are attribution and prior evidence, not prerequisites.

Main has no DHCP shared header. The new `DhcpAccessors.h` contains only these
five interfaces; it imports no receive record, parser, state layout or ownership
change. All five definition bodies are text-identical to main. The existing
generic option getter, table, storage, volatile accesses and caller sequence
also remain unchanged.

## Evidence for the shared interfaces

| Address | Shared interface | Direct original caller evidence |
|---|---|---|
| `80425288` | `s32(s16, s16, void *)` option setter | 24 calls: seven in PacketRuntime, seventeen in text_80421620 |
| `8042455C` | `s16(char *)` hostname | misc TLobby_801461EC relocation `0x430` |
| `8042474C` | `s16(s32 *, s32 *, s32 *)` lease/renew/rebind | misc relocation `0x4B0` |
| `8042489C` | `s16(void *, s32 *)` router | misc relocation `0x490` |
| `80424910` | `s16(void *, char *, s32 *, s32 *)` domain/DNS | misc relocation `0x4DC` |

These references are zero-addend `R_PPC_REL24` calls. Bounded native/reference
inventories cannot exclude dynamically constructed calls or recover a unique
historical typedef. The four status producers return only literal 0/-1; their
sole caller already declares short results and consumes the low signed halfword.
Earlier independent producer/caller controls separated return width from output
typing and found that the short-result callers retain the original checks.
This reasoning does not apply to unresolved reset functions forwarding arbitrary
word results.

The lease/router destinations are existing signed words. Domain storage remains
the existing 256-byte word array, viewed as `char *` only at the call. DNS outputs
remain existing signed words. The router/domain first argument remains unread,
opaque and present. The old `validate_slot_buffers` declaration was static, so
this argument was explicit, not an implicit receiver. The option table and actual
getter IDs support the name `dhcp_copy_domain_and_dns`; its symbol annotation
keeps address `80424910` and size `0xE0`.

## Original behavior preserved

Lease, router and domain/DNS accept states 3/4/5. Invalid states set diagnostic 2
and return -1. Active states return zero even when getters fail; every later
getter still executes. Lease diagnostics retain precedence 0x11/0x12/0x13;
domain/DNS calls getters 4, 5, 3 with precedence 0xE/0xF/0xD. Router failure
sets 0x10. Null outputs remain permitted. The generic getter still copies stored
data to a nonnull output even when the presence flag reports failure. Its string
copy has no destination-bound parameter.

The option setter returns zero for a known ID and -1 otherwise. It copies the
table's fixed size, using the supplied short length only for string termination
or clearing. The hostname setter computes the full length, tests its low 16 bits,
and retains the fixed 32-byte table copy. No source/destination bound, clearing,
early exit, locking or hardening is introduced.

The three hostname tests are copied unchanged from the attributed checkpoint.
They extract the current actual setter bodies into an original-free host harness.
Fully allocated fixtures preserve rejection of null and lengths 0/32/65536/65568,
32-byte copying for lengths 1/31, and acceptance of lengths 65537/65567 after
narrowing. These are characterization tests, not packet reachability, native ABI,
exploit or safety proofs.

## Scope limits

Receive-prefix/message ownership, lengthless scanning, private reset/creator ABI,
raw callback registration, locked allocation and queue adjacency remain separate.
No other #303 source change is a prerequisite. No compiler flags, pragmas, split
boundaries, providers or behavior repairs are included. The generated exception
inventory changes only one source line reference.

## Fresh extraction validation

The serialized native build preserves original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Comparison uses the authenticated
unchanged-main build, its 229 tool hashes and active manifest, rather than cached
directory counts. Of 3,632 active compiled objects, 3,630 are raw-identical. The
PacketRuntime producer and misc caller agree as complete ELFs after exactly the
recorded domain/DNS symbol-name mapping and its string-offset/file-placement
consequences. Section/symbol order, semantic metadata and all code/data/debug
payloads and raw relocation bytes remain identical.

Of 4,946 active original-reference objects, the same two change their symbol
string table and string ordering after regeneration. They are not claimed raw
identical: every mapped string remains, with identical symbol-record ordering,
semantic metadata and other section/relocation payloads. Ordered providers stay
3,606 source and 1,340 fallback inputs. No provider is replaced.

`check_pr.py` passes address-based no-loss and exact-source-link checks, with
18,575 retention entries and zero drift. Matched functions/code/data remain
27,438 / 4,237,032 bytes / 1,477,195 bytes; only the recorded function rename
changes report identity. All 309 Python tests, portable and ASan/UBSan tests,
Python syntax, generated inventory and whitespace checks pass.
