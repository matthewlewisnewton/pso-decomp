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
and chat call compared 100% to the original objects. The locked `ninja -j2` rebuild and `check_pr.py --no-build` pass against
`c43d704a1694c2dec9d8098b4d19325c12c32ca9`: exact code, matched data and
linked coverage are unchanged, and all 3,536 linked units pass. The rebuilt
DOL SHA-1 is `0d85744b51d7379efb025a943d0cd5aaae2191a3`. The three rebuilt
source objects also retain byte-identical `.text` and identical relocation
records against saved pre-change objects. The address-based comparison against
the assigned base passes with the existing 892-byte matched-data gain. This repair does
not establish that the keyboard unit's unmatched renderer and input bodies are
complete, and does not modify the separately owned effect factory callsite.

The locked run waited 26.05 seconds, then built in 5.24 seconds wall time
(6.24 user, 1.50 system, 311,912 KiB maximum RSS); the checks took 6.66 seconds
wall time (6.16 user, 0.49 system, 154,148 KiB maximum RSS). The underlying
keyboard unit still links from original fallback. Independent review of this
ABI change remains required.
