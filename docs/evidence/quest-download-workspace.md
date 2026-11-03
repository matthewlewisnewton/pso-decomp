# Quest download workspace byte storage

This selects the existing `lbl_80595008` symbol, `u8[0x990]`, at
`0x80595008..0x80595998` (2,448 bytes). The slot array selected by #262 begins
at the next address. The cache unit that ends at `0x80595008` is already
selected on main. Consumer function bodies are unchanged.

`symbols.txt` already names this object `lbl_80595008`, size `0x990`. That is
the placeholder stored for the address, so the definition keeps it. C linkage
matches that unmangled name. The compiled unit is one zero-initialized `.bss`
object: size 2,448, alignment 8, global symbol `lbl_80595008`. There is no
second definition and no aggregate that includes the slot array or the cache.

The first 2,240 bytes (`0x8C0`) stay uninterpreted. They are not padding, and
they are not the slot records: those are the separate object
`quest_download_slot_chain_table` at `0x80595998`. The last 208 bytes are
still interpreted only by original provider code. This definition does not
recover a query struct, a typed subobject lifetime, or a proof of the original
producer's bounds. A path in that original code can write past the final
208-byte region; reachability stays unproved. The symbol inventory does not
rule out computed aliases.

## Current-main validation

The same build as [the prefix note](quest-download-display-prefix.md#current-main-validation)
covers this unit. Baseline is current main
`b305c93d6315a67533b81580eb8ea019269b31c6`.

`QuestDownloadWorkspace` scores 2,448/2,448 data bytes at 100%, with no
functions, and the unit is complete. Together with the 12-byte prefix, this
change adds **2,460** matched and source-linked bytes on top of #262. The
combined stack against current main adds 4,700 data bytes and three
source-selected units (slots, workspace, prefix). Exact functions are
unchanged. The 1,028-byte scratch object at `0x80596264` stays original.

No original artifacts are copied into the source. Provider functions stay
unmatched.
