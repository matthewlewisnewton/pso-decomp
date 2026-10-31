# Symbol chat window receiver boundary

The three original entry points at 0x80284D68, 0x802859A8 and 0x802859E8 have symbols naming `TWindowSubSymbolChat`, but operate on the parts window. The chat's `create_parts()` allocates 0x90 bytes and invokes `TWindowSubSymbolChatParts__ct`; its state machine stores that result at `m_4c` and passes it to all three entries. The entries use offsets 0x76 and 0x78 beyond the chat object's verified 0x60-byte size. The declarations now take `TWindowSubSymbolChatParts *` while preserving the original external symbol names; no claim is made about the original source spelling.

Targeted GC/2.6 object comparison after this change retains the 19 exact functions and both data sections of `TWindowSubSymbolChatParts`, and all functions and data sections of `TWindowSubSymbolChat_80281814` remain exact. Full regression and linkage verification are pending.
