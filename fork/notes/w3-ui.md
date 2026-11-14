# w3-ui notes

## Matches that needed a trick

- TAdDialingGC_80328B20 and text_8007ECF0 only match with `mw_version` GC/1.3.2 (entries added to
  GAME_EXCEPTIONS). Under 1.3.2 the function-pointer-cast calls to sprintf and
  draw_outlined_string_right_aligned in draw_countdown_timer have to be plain calls.
- TAdDialingGC_80328B20: `draw_dialing_rectangle` matches with the fork's locals (`ColorLineVertex vertices[4]`,
  `ColorLineList rectangle`, `u32 colors[4]`) and a `const u32 color`. The NJS_POINT2COL version never got past
  91%. Its `-120.0f` is the pooled constant at 0x805DF6F8, so the split now claims .sdata2 0x805DF6F8-0x805DF700
  and the symbol became local `@11`.
- text_8007ECF0: the sdata2 pool is built by defining lbl_805D9298..805D92A4, 805D92AC and 805D92B8 in
  `__declspec(section ".sdata2")`, as the fork did; fn_8007F3F8 must read 805D9298/805D929C through those
  symbols or the object gets three extra pool entries. The "%3d%" format string is defined in `.rodata` because as
  a literal it lands in small data.
- TRaderMapCore::draw_compass matched with the fork's body (SpriteDescriptor-shaped local, nested color rotate).
  The unit also needed lbl_805DC548/54C/550 written as literals so the object emits the pool the split owns.
- TWindowSnapShot_802A5B2C: both read_be32 functions use the fork's s64 accumulator with `__rlwinm` lane masks.
- TChCrTagInformationStr: split object order is create, render, run_task, dtor, ctor; keeps upstream's render body
  (the fork's variant is 99.89%).

## Not linked

- TWindowHelpItem_80243408 (with TWindowActionPalette and text_802437C4, which already link): all functions match.
  The split gives this unit .data 0x804CDCA8-0x804CDFE8 (tables, lbl_804CDE50, twindow_action_palette_layout,
  __vt__20TWindowActionPalette, jumptable). The original was one translation unit; the vtable's key function
  (the destructor) is in the TWindowActionPalette unit, so a compiled HelpItem unit cannot emit the vtable, and
  the layout data is only referenced from the ActionPalette unit. Linking would need either a hand-written vtable
  in this unit (against CONTRIBUTING) or merging the three units. Not attempted.
- TWindowFukidasi: needs .sdata2 starting at 0x805DCD0C (4 mod 8). The compiled object's .sdata2 is 8-aligned and
  no linked unit here starts sdata2 off an 8 boundary; the fork used the `cw_align` build option, which does not
  exist here. Also ~47 externs would have to become literals/definitions. Skipped.

## Step 0 rename (801E35C4)

naming-three-way.tsv has no row for 801E35C4 and none of my units needed it to link, so it was not applied.
