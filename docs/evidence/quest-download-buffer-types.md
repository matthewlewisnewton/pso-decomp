# Quest download buffer import and pending type recovery

This draft preserves the deferred source from upstream
[`6e52d78f641e37d66845e683e8fc3f013f3c2662`](https://github.com/zeroz41/pso-decomp/commit/6e52d78f641e37d66845e683e8fc3f013f3c2662)
(#168, author zeroz). The initial import contains the exact
`QuestDownloadBuffers.cpp` blob, without replaying that commit's unrelated or
already integrated changes. Upstream #167 changes a player function and is not
a dependency of this buffer import.

The baseline is fork main `0ea667b2ae02f09c65cd9464314c0d5993618c6c`.
Fork #226 deliberately deferred these definitions. This checkpoint has **zero
new matched or source-linked bytes**: the source has no split entry and is not
in `linked_units.txt`. The existing extraction and linker selection remain
unchanged. The imported declarations are a starting point, not qualified types.
A later commit adds two bounded cache layouts; their consumers and complete
ownership are still pending as described below.

## Storage census

The symbol metadata describes ten contiguous extents totaling 34,912 bytes.
It establishes addresses and sizes, not historical translation-unit ownership
or the C++ lifetime of objects accessed through those addresses.

| Symbol | Address | Bytes | Contract still needed |
| --- | --- | ---: | --- |
| `quest_vm_download_server_file_info` | `8058DE08` | 68 | Filename and cache interfaces |
| `quest_download_slot_table` | `8058DE4C` | 11,384 | 128 entries and ten cache pages |
| `quest_name_index_table` | `80590AC4` | 4,096 | Consistent four-byte name records and DMA view |
| `lbl_80591AC4` | `80591AC4` | 1,028 | ASK header and remaining four bytes |
| `lbl_80591EC8` | `80591EC8` | 8,192 | Cached byte data and bounded variable records |
| `lbl_80593EC8` | `80593EC8` | 4,416 | Bucket heads and cache-node lifetimes |
| `lbl_80595008` | `80595008` | 2,448 | Actual uses, extent and owner |
| `quest_download_slot_chain_table` | `80595998` | 2,240 | #203's 80 real 28-byte slot records |
| `lbl_80596258` | `80596258` | 12 | Header and accesses through the following payload |
| `quest_download_text_buffer` | `80596264` | 1,028 | Shared byte, wide-code and ID lifetimes |

The reviewed 40,000-byte node pool begins at `80596668`, after this range.
The separate 39-record input table starts at `805A0498`. Neither repair
establishes ownership or lifetime of these ten objects.

## Cache layouts recovered after the import

`QuestDownloadCacheTypes.h` gives the slot-cache extent 128 real eight-byte
entries followed by ten real 0x40C-byte pages. The entry fields are a byte
reference count, a byte value, an unsigned halfword page index, and two signed
halfword offsets/IDs. Acquisition and release update the reference count;
`803E779C` returns the other fields with the corresponding native load widths.
The page has two words (page index and state), a next pointer, and 1,024 data
bytes. Native `init_page_cache` initializes the ten page headers, terminates the
last next pointer, and clears the reference byte in all 128 entries.

The name index is **80 node pointers followed by 512 eight-byte nodes**, not
1,104 unrelated `void *` objects. Native `__VIRetraceHandler` clears the heads at
cached-data offsets +0x2000 through +0x213C and chains nodes from +0x2140 through
+0x3138. Each node has a byte-record pointer and a next pointer. Native
`803E8DA0` writes the record pointer and splices the node into a bucket;
`803E95BC` returns it to the free list by updating that same next member. There
is no evidence here of another active node variant requiring a union.

Two admitted development compiler probes, using the original imported source
and the typed definitions, produced identical allocated data sections: all ten
symbol offsets/extents/bindings, 34,912 zero BSS bytes, alignment 8, and no
relocations. All layout assertions passed without diagnostics. These are
targeted definition-layout checks, not consumer, full-build or source-link proof.
The two imported definitions now use these types; no shared consumer has been
edited or declared compatible by this checkpoint.

## Follow-up boundaries

The file/cache repair must reconcile every consumer, rather than replace only
the imported definition. `init_page_cache` currently casts the 68-byte file-info
symbol to `Cache_803E840C`, which spans 0x2CBC bytes. Its 128 eight-byte entries
and ten 0x40C-byte pages occupy the next symbol's entire 0x2C78-byte extent.
`read_ask_header` separately casts the same file-info symbol to a padded view
whose header is at +0x3CBC. A candidate repair can use the actual separate
filename, cache and header objects, but must preserve native symbol/addend
relocations and all consumers; physical adjacency does not prove a larger
filename or aggregate object.

The retained original object makes the relocation problem concrete:
`init_page_cache` loads the file-info symbol and derives the page start at
+0x444 and entries at +0x44; `read_ask_header` loads that same symbol and derives
the header at +0x3CBC. Neither function relocates directly against the cache or
header symbol. A separate-object source spelling may therefore alter exact
instructions/relocations. A complete owner spanning these ranges is a candidate
for investigation, not a conclusion from the available evidence.

Two producer bounds also remain open. The public filename path copies the
frontend's 128-byte filename storage into the 68-byte file-info extent using
`strcpy`, without a visible 67-character check. The name-index reader transfers
exactly 4,096 bytes, but the search high bound comes from an unchecked 16-bit
ASK header field. The 1,024 physical four-byte rows alone do not prove that
every producer supplies an in-range search bound.

The 2,448-byte symbol at `80595008` also cannot be qualified by a source-only
reference search: its missing native consumers `803EA428` and `803EA9E8` use
that base plus +0x990 for the following slot table. `803EA428` passes +0x8C0 to
the item-query producers and reads halfwords at +0x8C0/+0x8C8 and a word at
+0x8C4. This identifies a result workspace in the final 0xD0 bytes, but does
not establish the first 0x8C0 bytes' object type or a complete aggregate owner.

The slot-table definition must adopt #203's canonical record header together
with its reviewed consumers and allocator interfaces. The four exact functions
in #203 must survive the combination. The buffer work must not introduce an
alternative record model or replace the current #203 repair wholesale.

The text buffer is also the storage used by the pending EE580 recovery and the
DF64 caller. The frontend's 512 signed halfwords cover 1,024 bytes, not the
complete 1,028-byte symbol. Other paths use byte dictionaries, a text record
prefix and ID cells. A new union or larger integer array alone would not prove
lifetime transitions, retained values, variable-tail bounds or a 257-ID bound.
The header-plus-12 callers belong to this same audit. C284 and DF64 function/API
repairs remain separate dependencies and must be coordinated before their
frontend hunks change.

## Activation and acceptance

Type and consumer repairs belong in later commits, separately from the upstream
import. Once their source contracts pass independent review, qualify emitted
code/data, alignment, symbol bindings and relocations using admitted development
capacity. Reuse prior immutable evidence only when its actual inputs agree.
Then establish the data-owner boundary, regenerate the graph and retention data,
check actual native source selection, and run the original-DOL and address-based
no-loss checks against both the dependency base and current fork main.

The initial import performed source-provenance, symbol-extent and unchanged-
build-input checks only. The later cache-type commit adds the two targeted
compiler layout probes above. Neither checkpoint ran a game link, full build
or `check_pr.py`, and neither claims review-ready status. Keep the PR draft until the complete
contracts and these validation gates pass. Final current-main acceptance belongs
to the merge process.
