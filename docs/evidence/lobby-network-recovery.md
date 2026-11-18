# Lobby network recovery at 0x804050DC

Recovery started at `84420bea523b79b3e2daf384b26fb1211560e0be`. The pull request
uses `a6284306fa676770c5b2e6c1d2e53e94915b5d54` as its verification baseline.
The original address range contains 281 functions and 84,260 code bytes.
All 281 functions and all 888 allocated data/BSS bytes now match in the
three source-linked objects. The starting build had 244 exact functions
(57,268 code bytes) and 508 matching data/BSS bytes.

## Source and data organization

The former unit is organized in three compiler-supported object groups, with
shared declarations and inline helpers in `LobbyNetworkInternal.h`:

| Source suffix | Text range | Data range | BSS range |
|---|---|---|---|
| `804050DC` | `804050DC–8040FF0C` | `804FD690–804FD6E0` | `805C1AD8–805C1B78` |
| `8040FF0C` | `8040FF0C–8041112C` | `804FD6E0–804FD7D8` | `805C1B78–805C1BB8` |
| `8041112C` | `8041112C–80419A00` | `804FD7D8–804FD890` | `805C1BB8–805C1C50` |

Definitions follow native address order. Ordinary compiler-generated switches
produce the tables; no table contents are copied from the executable. The
IPv4 ICMP table occupies 76 bytes, followed by four bytes of object alignment.
The IPv6 input table occupies 244 bytes, likewise followed by four alignment
bytes. The final group emits the interface-event and existing neighbor tables.
Keeping all tables in the former single object loses the intervening alignment.
This organization reproduces the data contributions and their alignment; it is
not, by itself, proof of the historical translation-unit boundaries. The original
DOL hash verifies all three groups’ linked contributions.

## Review revisions

The three objects use the same explicit-inline default. The shared header has
zero pragma lines. The source groups have 47, 6 and 20 respectively. A stock
compiler comparison tested each retained change of setting and its restoration.
The [exception register](../porting-exceptions.md#lobby-network-recovery)
identifies the affected regions.

The receiver audit covered all three units, the shared header, and callers of
the renamed exports. The 88 casts that passed unrelated records as `TLobby`
are gone. Buffer initialization takes `NetBufferRef *`, DNS builders take
`DnsQuery *`, and packet release takes `NetPacket *`. DNS query kind and
lookup family come from the shared request layout. The PPP transmitter uses
the link's protocol states and error counters. IPv4 packet length, fragment
count and fragment descriptors use the packet layout.

The peer notification at `80408428` allocates a packet when a queued payload
exists, dispatches it, releases it and detaches the peer. The loopback reset
at `8041509C` clears the entry and cancels the loopback state. Binding the
returned peer or status locally reproduces the original 88-byte and 24-byte
frames respectively. Both previously unused arrays are gone. The DNS sender
at `8040B1C4` also loses two unused arrays when its send descriptor is local
to the send helper. The two PPP senders at `80406328` and `80406624` use
their frame, cursor and protocol fields in place of stack-padding arrays.

## Recovered behavior and interfaces

The receive candidate at `8040DE4C` must keep the wire header distinct from the
allocated packet record. The original uses the header for protocol selection,
payload addresses, and ICMP errors, and the record for dispatch and release.
Reusing one pointer for both changes behavior despite a high fuzzy match score.

The DNS name reader at `8040BD40` accumulates each uncompressed label length
and its length byte. The native count is not reset to the current label length.
The bounded compressed-name branch has its own output cursor. Adapting
upstream `NetDns.c` from `9925c2c503` with its scoped `opt_lifetimes off`,
separate decoded-source cursor, and reuse of the short limit for the compression
offset matches all 256 bytes. This replaces the earlier inline-wrapper candidate.

The IPv6 forwarding parameters use the existing `NetIPv6SendParameters`
structure. Its two addresses and flow/traffic/hop/protocol fields replace an
unsafe assumption about adjacency of separate local arrays. Direct field
access preserves the native stack offsets without keeping redundant pointer
aliases alive.

The event dispatcher at `80411604` and its callers share a signed 16-bit
interface ID. The ordinary C++ definition reproduces the complete function.
The PPP writer at `804066D8` uses one compiler scope around its definition.
Its inlined time query calls the C++ interface. All compiler directives in the
three source groups fall between function definitions.

The route lookup at `8040EF00` and the socket-flag predicate both take and
return a signed 16-bit value. The ICMPv6 error sender at `8040D510` takes
an `Icmp6ErrorInfo *`, a packet pointer, a signed 16-bit packet length and a
signed 16-bit interface ID. The IPv6 forwarder at `804105E0` returns the
signed 16-bit status supplied by its send routines. Each of these four
interfaces has one shared declaration. Both IPv6 extension-option paths use
the saved datagram length while the input loop advances its remaining count.

Several pre-existing network boundaries use scoped short-result declarations
for providers whose broader declarations return words. These include DNS,
IPv4/IPv6 dispatch, and neighbor-option callbacks. The scoped declarations
preserve the evidenced caller behavior and remain explicitly bounded legacy
interfaces; they do not establish a new public API. Broadly changing all return
widths regressed exact callers. DNS query-builder member parameters retain the
original short width, with the legacy name-encoder declaration local to each
builder. A port should reconcile each provider and all callers together rather
than infer a shared API from one call site.

The ICMP error sender at `8040CE58` returns a word-sized result from its scoped
legacy `8040E780` call. Keeping that result and the sender's return type as
`s32` preserves its exact body, including the final `mr` instead of `extsh`.
It also removes the extra sign extension in the IPv4 input caller at
`8040DE4C`. Narrowing both the provider declaration and the local result had
made the sender match in isolation while imposing the wrong caller conversion.
The actual `8040E780` definition remains short-returning; this is another
bounded legacy declaration that a port must reconcile across callers.

The shared handler callback parameter widths were narrowed only where the
native argument handling and existing exact bodies support it. Changes to the
corresponding mangled symbols accompany those declarations. Existing code and
data matches are checked by original address, independently of symbol names.

The buffer release at `8041579C` now matches all 440 bytes. A short owner
cursor and reuse of the consumed segment byte offset before the index phase
reproduce the native pointer and counter lifetimes without changing its
`void *` interface. The IPv4 sender at `8040E780` retains its scoped short-result declarations.

The receive routine at `80405700` matches all 884 bytes with an inlined
implementation that receives the entry-local byte by reference and declares
its receive count first. This reproduces the native register lifetimes and
stack offset without an emitted helper call. It is an evidenced compiler
organization constraint, not proof of the original helper structure.

The fragment reassembly routine at `80418D7C` matches all 1,244 bytes after
adapting [upstream PR #296](https://github.com/zeroz41/pso-decomp/pull/296)
(commits `84db72222f` and `0506307692`) to the existing local types and method
boundaries. Its final copy loop reuses the insertion-search fragment cursor.
The packet pointer temporarily holds the last fragment through an explicit
pointer conversion, then is assigned the allocated packet before packet access.
Keeping the separate pool-list pointer preserves the native lifetime grouping.

The PPP frame writer at `804066D8` matches all 1,036 bytes with the negotiated
LCP options, two header-field helpers, and the output buffer descriptor from
[upstream PR #299](https://github.com/zeroz41/pso-decomp/pull/299). The frame
length is explicitly narrowed at the getter call here and in the length check
at `804053B8` to support the widened getter in PR #573.

The IPv6 prefix event handler at `80412618` matches all 1,676 bytes. It uses
the typed prefix event and interface access from
[upstream PR #298](https://github.com/zeroz41/pso-decomp/pull/298). The cursor
first points at the event, loads the length and prefix through its typed view,
then points at the prefix bytes. This preserves both native registers and
omits the upstream empty condition that reads an uninitialized pointer.

The packet checksum at `80406BD8` (736 bytes) follows
[upstream PR #304](https://github.com/zeroz41/pso-decomp/pull/304), including
the fragment cursor and segment index lifetime. The buffer copy at `80406FD8`
(748 bytes) follows [upstream PR #292](https://github.com/zeroz41/pso-decomp/pull/292).
Its pool-to-pool branch reuses the count, entry, and segment pointer during
destination decoding. Both routines retain their existing public signatures.

The DNS answer parser at `8040BA38` matches all 776 bytes using the body from
[upstream PR #306](https://github.com/zeroz41/pso-decomp/pull/306). A short
holds the decoded name length before the cursor advances, then the remaining
input length for the record checks. The record cases share one host pointer.

The Ethernet socket lookup at `804092FC` matches all 160 bytes. Its inline
lookup takes the socket and reads its connection ID before walking the link
table. The IPv6 address update at `80412CA4` matches all 1,420 bytes with a
typed interface lookup and scoped common-subexpression elimination, following
the linked upstream unit. Its short prefix-length parameter also matches the
existing caller declaration in `text_80421620.cpp`. The IPv6 receiver now
uses the shared `NetworkAddress` type for its two addresses.

The Ethernet socket opener at `804094B8` matches all 596 bytes when the
duplicate lookup and free-slot lookup both read their cursors from the socket
pool. The free-slot search advances the remaining count. The IPv6 forwarder
at `804105E0` matches all 888 bytes with an early pointer to the hop limit in
the send parameters. It reads and decrements that field after initialization.

The IPv4 receive path at `8040DE4C` matches all 1,288 bytes. The cursor
reads the wire header’s length field and later walks the raw sockets in
28-byte steps. The packet length becomes the subscription index in r28.
The loop compares its signed halfword and passes the full word to the
callback. A short records delivery in r24. The UDP port-unreachable path
keeps its ICMP result in r23 while it releases the reassembled fragments
and packet record. The packet header, record, and two status values have
separate lifetimes.

The `80412CA4` failure cleanup inherits a runtime assumption: if the socket
flag is clear, removing a route can use the address returned for interface
zero. That helper only populates the address when the interface is active.
The exact match does not establish this invariant for every caller.

## Validation

The final build uses the pinned GC/1.2.5n compiler and the original GPOE8P
inputs. The three objects contribute the following matched ranges.

| Object | Functions | Code bytes | Allocated data/BSS bytes | Retention symbols added |
|---|---:|---:|---:|---:|
| `TLobby_804050DC` | 166 | 44,592 | 240 | 89 |
| `TLobby_8040FF0C` | 9 | 4,640 | 312 | 4 |
| `TLobby_8041112C` | 106 | 35,028 | 336 | 70 |
| **Total** | **281** | **84,260** | **888** | **163** |

The rebuilt DOL is byte-identical to the original. Its SHA-1 is
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The baseline comparison
records 37 newly exact functions and zero regressions. All 3,631 linked
units pass the linkage and retention checks. An independent ELF comparison
verified function order, allocated section bytes including linker padding,
and all 1,810 relocation sites and targets across the three objects.

The DNS resolver at `8040A8B0` matches all 1,204 bytes. Its query-slot
claim advances the caller's query pointer under the lock. When selecting a
server, the indexed lookup saves the current attempt before testing the
server and the retry limit. The caller keeps the selected server address
for all three UDP calls.

IPv4 forwarding at `8040E354` matches all 1,068 bytes. The fragmented
and unfragmented paths each keep their own packet record and wire-header
cursor. In the fragment loop a short stores the tail byte count. The
payload cursor advances by the aligned byte count, while the transmitted
length includes the tail.

IPv4 sending at `8040E780` matches all 1,208 bytes. The sender first scans
the packet fragments to count how many fit. Its copy loop maintains
separate source and destination byte offsets, the destination index, and
the number of bytes still needed. When only part of a fragment fits, the
sender uses the short remaining count for fragment lengths and a widened
copy for byte totals and the buffer-advance call. The temporary packet
occupies an eight-byte-aligned workspace.

IPv6 input at `8040FFF8` now matches all 1,512 bytes. The input checks the
length before saving the interface index and restores that index after the
ICMPv6 handler. The raw-socket scan reads its active flag as an unsigned
halfword. The C++ body uses the project’s interface-lookup and record-release
adapters. The source was adapted from [upstream PR #310](https://github.com/zeroz41/pso-decomp/pull/310),
head `6c7e082755`.

The adjacent lobby unit at `803FC178` was recovered separately in
[PR #573](https://github.com/matthewlewisnewton/pso-decomp/pull/573).
