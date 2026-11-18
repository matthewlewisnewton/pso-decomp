# Addition's shared floating-point prefix

`TWindowAddition` owns the four floats at `0x60`, `0x64`, `0x68` and `0x6C`.
The class now ends at `0x70`. Its eight direct descendants previously reserved
their own copies of this same 16-byte prefix; those copies are removed together.
Their first retained fields still begin at `0x70`, and their total sizes remain
unchanged. Compile-time checks cover the shared size and offsets, every direct
descendant's first retained field, and the existing descendant total sizes.

The names remain offset placeholders (`m_60`, `m_64`, `m_68`, `m_6c`). The
first pair is written by the existing `set_position_xy` function and supplied
to `TWindowBase::setup_window_draw_context`, which forwards it to
`TWindowKeyBoardSoft::open_singleton` as scale input. Thus the existing setter
name should not be taken as proof that this pair is a screen position.
The second pair is subtracted from the draw context's inner coordinates;
the last float also participates in tweening and message/list scrolling.

The header correction removes misleading pointer/integer declarations of the
same float storage in several descendants. Existing float accesses through the
removed padding arrays now use the inherited `m_6c`. The setter and Addition
initializer write their owned float members directly. Other window fields,
constructor signatures, virtual declarations, and generated tables are unchanged.

## Validation

Baseline: `d94e626cf72f180672d5e925d1eab7d5cfdbeec6`, whose source is the
previously validated `74966a46e`. A complete locked native build and
`tools/check_pr.py --no-build` pass:

- Original DOL SHA-1: `0d85744b51d7379efb025a943d0cd5aaae2191a3`.
- Exact functions unchanged at 27,365; zero regressions or renames.
- Matched code/data and linked code/data unchanged.
- All 3,571 linked units remain exact; retention metadata is unchanged.
- `tools/list_port_exceptions.py --check` passes; no new exception.

This resolves the duplicated Addition prefix declaration. It does not activate
the separate constructor probe, recover default constructors, or qualify emitted
virtual-table ownership and its neighboring original data. The standing draft
hold remains until the construction/lifetime integration is independently
validated as a complete linked change.
