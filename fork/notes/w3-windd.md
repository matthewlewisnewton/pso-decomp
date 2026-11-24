# w3-windd notes

## Done
- TWindowDD.cpp: 8034055C needed `opt_propagation off` and the get_draw_count result copied after the loop index is set (`i = 0; count = result;`). 80340A78 needed the fork's named-temporary structure (fp_contract on, opt_propagation off, opt_common_subs off) and the 805DFC50.. constants as externs. Data: .data split end 0x804EFBC8, .ctors ref, rodata 804785D8 renamed to local @175.
- TWindowSubStatusDisp_80256B94.cpp: 0.0f and 2.0f became literals (no externs); the 30 pool floats renamed to the compiler's @N locals in symbols.txt. Vtable renames (__vt__13TUnk_804CF918/930) were not needed for the link and were not done.
- format_word_select_spanish: needs the inline helper append_spanish_word_form (pragma dont_inline off / inline_depth(1)), declaration order k,n,s,i,pos, the case-2 loop on i, and lbl_805DFCC0/CC4 as `extern const char[4]` (the compiler's own string literals give a 2-byte symbol and break data_value comparison).

## Not linked: TWindowDD_803430BC.cpp
All functions match. Linking breaks the DOL hash: the original has a 4-byte zero pad at 0x804EFDBC between jump table 1 (size 0x54) and jump table 2 (0x804EFDC0, 8-aligned). The fork had two units split at 0x8034435C so the pad came from alignment between objects. Here it is one unit, so it is blocked on alignment (cw_align-like); split boundaries not moved.

## Not matched
- TWindowDD_80341A08 80341674 (99.36% best): last highlight block. Target puts top in f0 and bottom in f1 and stores with separate addi 0x18; ours allocates f1/f0 swapped and merges the stores. Float literals must be the lbl_805DFCA4/805DFCA8/805DFCAC externs and `0.0f != frac` operand order. Tried: scoped loop variables, block-local temporaries, v++->b form, reordering; none changed the allocation. Reverted.
- TWindowSubStatusDisp_8027FD88 8027FF6C (98.84%): only register assignment of the title/spacer/value pointers differs (target r29/r27/r28, ours r28/r29/r27). Tried fork's variable names, declaration at use, heading_slot enum, const char* name. Reverted.
- TWindowSubStatusDisp_8026DFE8 8026E1D4: function absent here (0%). Not attempted: needs a full port of the fork's TWindowShortCut::initialize_preview, a header declaration, a text_preview/symbol_preview member (here m_64/m_68), and extern names for 12 sdata2 constants (shortcut_* in the fork; lbl_805DDxxx here). Out of budget.
