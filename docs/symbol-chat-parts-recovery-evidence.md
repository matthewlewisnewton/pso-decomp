# Symbol chat parts recovery (WIP)

`fn_802855C4` at 0x802855C4 renders the mode-1 part grid. The original object reads the signed count at 0x76, walks rows of four, skips rows outside the draw context bounds, and calls the part sprite setup with the selected mode and two referenced settings. The recovered function follows those operations. The temporary overlay names describe observed offsets, not verified ownership or original names.

A targeted GC/2.6 compile and objdiff against the original unit object from the clean `beaa7f52af2a7360e18deafc771648f51b709531` build give 96.72% for this formerly missing 512-byte function. All 19 previously exact functions compare at 100%, as do `.rodata` and `.sdata2`. The function still differs in register allocation and its signed-byte load sequence. This is not a complete match or a claim that the unit links from source. Full build and link coverage validation remain pending.
