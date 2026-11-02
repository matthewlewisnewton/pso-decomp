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

This checkpoint performed source-provenance, symbol-extent and unchanged-build-
input checks only. It did not run a compiler, link, full build or `check_pr.py`,
and does not claim review-ready status. Keep the PR draft until the complete
contracts and these validation gates pass. Final current-main acceptance belongs
to the merge process.
