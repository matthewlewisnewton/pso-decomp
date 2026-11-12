# w4-small

## pso/object/trap/TOTrapAncient01.cpp: not linked
Tried the fork's recipe: `-inline off,deferred` (and then the fork's full flag set: `-fp_contract on`,
`-str reuse,readonly`, `-pooldata=off`, `-opt nolifetimes`) with every function in the extern "C" block
listed in reverse order. All functions still matched, but the `.sdata2` pool did not change:
compiled `1.25, 1.0, 0.0, 15, 400, 20, ...`, original `1.0, 0.0, 1.25, 15, 400, 20, ...`.
With the source in forward order the pool is `30, 0.5, 0.0, 1.0, 0.33, 15, 20, 400, ..., 1.25`, and the
text is in source order in both cases, so here deferred does not reverse emission of ordinary
functions; it only changes where constants are allocated. The original's pool order (1.0/0.0 from
vfunc_82 before 1.25 from play_sounds, but 15.0 from vfunc_82 after 1.25) is not explained by any
simple function order. Reverted. Remaining link reasons are unchanged: `data .sdata2:91.66667%` plus
localizable `missing` symbols (the localize tool reports "no missing-only units" until the pool is right).

## pso/ui/window/TWindowSubStatusDisp_8026DFE8.cpp: linked
TWindowShortCut::initialize_preview matched 100% from the fork body with no change to its logic.
The `shortcut_*` constants are already named in symbols.txt and owned by the original
`auto_11_805DD348_sdata2` object, so the unit links without claiming `.sdata2`; the function only
declares them extern. `m_64`/`m_68` of TWindowShortCut were renamed `text_preview`/`symbol_preview`
(TWindowShortCut.cpp updated, no codegen change). Local extern "C" declarations are used for
`fn_80076BC4(s32 *)`, `open_symbol_chat__11TWindowChatFPl` (returns `u8 *`) and the measure/format
helpers, because the shared headers declare them differently (void return, no arguments).
