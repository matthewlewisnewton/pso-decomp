# Keyboard constructor client argument

The original soft-keyboard constructor receives its third argument in `r5`,
preserves it across `get_window_layout_position`, then sign-extends its low
16 bits at `0x80262774` before calling `TWindowDD::construct_base`. The base
constructor's member signature is `u8 *(u8 *, s16, u8 *)`; it receives the
window in `r3`, descriptor in `r4`, short client in `r5` and layout pointer in
`r6`.

Both original callers pass the client as a register value without narrowing it
at that call: `TKeyBoardControl__ct` at `0x80131E54` forwards `r30`, while
`TWindowChat::open_next_input_window` at `0x802479CC` loads the client global
into `r5`. The code uses a 32-bit incoming carrier for both keyboard
constructors and narrows it only at the member call. It does not claim the
original source spelling. The chat caller now includes the same soft-keyboard
constructor declaration and passes the observed register values without the
previous pointer-typed substitute.

The coordinated constructor, forwarding constructor and chat caller were
compiled in temporary objects before this change. Their `.text` bytes and all
relocation records matched the prior source objects, and the two constructors
and chat call compared 100% to the original objects. The full locked build and
address-based regression checks for this commit are pending. This repair does
not establish that the keyboard unit's unmatched renderer and input bodies are
complete, and does not modify the separately owned effect factory callsite.
