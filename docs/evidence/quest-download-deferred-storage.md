# Quest download slot storage and remaining contracts

This continuation depends on fork PR #238 at
`41be9450cb01b633ae9abcee6b402f91b1a562de`. It preserves that PR's six-object,
29,184-byte selection and adds the canonical 2,240-byte slot array as a separate
source owner. The original scoped upstream import and subsequent type repairs
remain in the dependency history. The other 3,488 bytes remain original.

The four symbols below occupy 5,728 bytes. Native extents identify boundaries;
they do not by themselves establish historical C++ types or translation units.

| Object | Address range (end exclusive) | Bytes | Next source step |
| --- | --- | ---: | --- |
| `lbl_80595008` | `80595008..80595998` | 2,448 | Resolve the first `0x8C0` bytes and the final `0xD0` query workspace's producer contract. |
| `quest_download_slot_chain_table` | `80595998..80596258` | 2,240 | Selected canonical `QuestDownloadSlot[80]`; native result described below. |
| `lbl_80596258` | `80596258..80596264` | 12 | Qualify the display-prefix character storage and its boundary with shared scratch. |
| `quest_download_text_buffer` | `80596264..80596668` | 1,028 | Reconcile byte records, wide characters and ID views, bounds and phase lifetimes. |

## Slot ownership

`QuestDownloadSlots.cpp` supplies one C-linkage definition using the existing
canonical record header. Its trivial slot objects have static storage duration
and normal zero initialization. The existing provider `init_entries` initializes
the 80 slots before normal use. Pointer fields refer to separately owned nodes;
the slot array neither supplies their storage nor starts their lifetimes.

The split and linked-unit list select exactly `80595998..80596258` from this
definition, leaving the 2,448-byte workspace and 1,040-byte prefix/scratch
remainder original. There is one selected slot definition, with no alias, extra
capacity or aggregate spanning the adjacent objects.

The current frontend already uses the canonical slot declaration. Its bodies,
the public headers, provider bodies and private pointer/count API work are
unchanged. The standalone data prerequisite therefore does not require importing
the private provider/API composition. Independent source, object, eligibility
and actual-graph reviews passed for this bounded dependency assessment.

Direct-symbol references are not a complete consumer inventory. Native A428 and
A9E8 also reach slots from `lbl_80595008 + 0x990 + index * 0x1C`.
The native validation preserves those addresses and actual relocation results,
as well as all direct slot references. Compiler pooling is not evidence for
combining the two objects into one C++ aggregate. Existing index-domain obligations remain
visible; defining storage alone does not prove every consumer's bounds.

## Remaining contracts

A428 uses query workspace at `lbl_80595008 + 0x8C0`; A9E8 uses the same symbol
as an address anchor for slots. These uses do not type the preceding `0x8C0`
bytes. F0268/F06B8 and F03B4 establish a query prefix and six-byte items, but the
second producer pass's capacity bound remains unresolved. A conditional excess
write is not proof of a reachable original-game overflow. Do not enlarge the
owner, declare unknown bytes to be unused padding, or silently change behavior.

The frontend copies a string into the 12-byte prefix. The original constant at
`8047E68C` has its first NUL at offset 10, so that initialization copies 11 bytes
within the object; this does not establish subsequent scratch bounds. Native B4D4 writes its
display-count characters at offsets 5 through 7 and passes the prefix to C95C.
BEFC/C460 also use that symbol as an address anchor for scratch at `+0xC`.
That arithmetic must become valid separate-object source access if those
consumers are recovered; a larger fabricated character array is not a fix.
The scratch address is four modulo eight, so any separate-object layout must
also preserve the actual boundary and alignment without invented padding.

Scratch consumers include the frontend wide-character conversion, EE580's ID
output and B8BC/BA98/BC88's variable byte records. The frontend currently declares
1,024 bytes through a halfword array, while the native object occupies 1,028.
The final four bytes, record-tail representation, serialization capacity,
ID-output bound, aliasing and phase/reentry lifetime contracts remain unresolved.
Shared frontend/DF64/EE580 and slot/pool consumer edits remain with their existing
owner until a precise release. No such bodies are changed by this continuation.

All sixteen missing provider functions are required only for selecting the
whole mixed provider source unit. They are not a blanket prerequisite for a
qualified independent data owner. Particular missing functions still supply
necessary semantic evidence: A428/A9E8/F03B4 for workspace and slot boundaries,
B4D4 for the prefix, and EE580/DF64 for shared scratch use.

## Development validation

The exact native candidate was `140bc0ace7fcfe2deca0894ea09adb2c306f73e6`,
compared with the authenticated `6607f3d2c0406f794e3d187fede3c6756ac51f4f`
baseline underlying #238. The baseline was reused without rebuilding. A normal
candidate build included one slot compile; its object exactly matches the prior
independently reviewed standalone diagnostic object.

The genuine report scores all 2,240 slot bytes at 100%, and the unchanged
`unit_is_exact` score, symbol, section, size, alignment and order checks pass.
The consumed linker response selects the slot source object once. Its linked
symbol remains at `0x80595998`, size 2,240, with eight-byte alignment. All
allocated ELF section addresses and extents remain unchanged, and all 5,013
unaffected selected objects are identical to the baseline.

The generated DOL is byte-identical to the original, SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. Normal `check_pr.py --no-build`
checks pass after that native build; all nine unfiltered code/data/function
coverage, exactness and linkage loss groups are zero. The full report records
+2,240 matched data bytes and +2,240 source-linked data bytes, with no change
to code or function counts. No one-unit report substitutes for the full report.

Independent final native-output review passed for this exact historical pair,
including unchanged diagnostics and all final ELF allocated bytes, flags and
alignment. The immutable review packet has SHA-256
`ca312cb20c0a8bb4588faa3e9e36b49e063edf6b9077b39c0194f1d62127df72`.
The publication commit changes only this evidence document from the tested
candidate. Latest-main acceptance remains a separate merge-process gate.
Original objects, native binaries, proprietary tools and detailed private
evidence remain local.
