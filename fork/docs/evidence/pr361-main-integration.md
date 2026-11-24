# Remaining upstream #180 units: current-main integration

This follow-up to fork PR #351 still contributes source-linked coverage beyond
main. It is not superseded by the Ginja vector work in PR #128. The integration
starts at PR #361 head `be748eb25ff964dedaf5ebe9ecae9d22206d8d8e` and merges
fork main `6daa19a11` without rewriting either history.

## Overlap with the Ginja vector work

Main already contains the approved `vec3_add_to`, `vec3_dot`, `vec3_cross` and
`normalize_vector` implementations and their compiled scalar fallbacks. The
conflicts in `text_803D8910.cpp` and `text_803D96A8.cpp` retain those main
implementations. In particular, this PR does not restore the older unconditional
assembly bodies for those four functions. The remaining matrix operations from
the upstream catch-up remain in `text_803D96A8.cpp`.

The porting register keeps main's specific Ginja approvals, removes the four
obsolete catch-up rows, and attributes this follow-up's newly delivered ranges
to PR #361. The loading-text constructor is a real C++ constructor, so its old
`extern "C" mangled name` exception row no longer describes the source and is
removed. Its fused multiply-add requirement remains documented separately.

`TEffStarLight2D_Base.cpp`'s local `normalize_vector` declaration now returns
`f32`, matching the implementation at `0x803D97B4`; the call ignores the result.
The legacy pointer boundary is otherwise unchanged.

## Unit boundaries and remaining source limitations

The two folds retain the upstream #180 layout: `TObjDFDemo5.cpp` owns
`0x8004F904..0x80050050` and its constructor, node tables and compiler vtable;
`TEffStarLight2D_Base.cpp` owns `0x80084BC4..0x80085774`, both effect classes,
their compiler vtables and their shared constant pool. The latter pool ends at
`0x805D9474`; the following four zero padding bytes remain unowned. The camera
split and the other matrix ranges retain the upstream catch-up implementation.

An exact build does not establish complete recovery of the original C++ types.
The effect and camera sources still contain provisional shadow records, raw
offsets, legacy C entry points and the assembly covered by the one-time upstream
catch-up exception in section 7 of the porting register. Their cleanup remains
future work; this PR's completion claim is the matching and source-linking of its
listed ranges under that exception. Independent review of the final head is
still required.

## Validation method

Build main `6daa19a11` and the merged source in separate fresh worktrees with
private `build/` and `orig/` directories. Copy only the installed toolchain and
original inputs, not prior object files or reports. Use the pinned tool versions
from `configure.py`, and serialize full builds with
`/tmp/pso-decomp-full-build.lock`.

Compare the merged branch against main's fresh report using `check_pr.py`.
Require the original DOL SHA-1, address-based no-loss checks, exact linked-unit
checks and generated force-active checks. Verify the generated exception
inventory and run the inherited host fallback harness. The PR description
records the exact validated head and measurements.
