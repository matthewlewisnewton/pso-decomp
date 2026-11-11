# Quest-download display recovery

`TQuestVmDownLoadServer__sub_803EB4D4` at `0x803EB4D4` matches all 704
original bytes with the unchanged GC/1.2.5 compiler and unit options.
The containing provider unit remains incomplete and unlinked.

The routine counts complete text-node groups, subtracts the current selection
and one, and clamps the remaining count to zero. It writes three decimal
positions in the existing display prefix, converts that prefix to the wide
output buffer, and emits the visible groups. Continuation nodes use flag bit
zero; flag `0x80` selects the existing input-table conversion path. The selected
group receives attribute seven, and the remaining output capacity is padded.
No text resources or new backing storage are defined by this recovery.

## Inline boundaries and frame

The group count, conversion and group advance are inline helpers in the
existing depth-one `Conv_803EBA98` region. Moving a plain call to the neighboring
out-of-line routines into this body does not reproduce the native traversal.
The conversion keeps separate input snapshots and an advancing output cursor.
Its local declaration order also affects the native register assignment.

With both scalar inputs passed by value, every instruction outside frame
setup and restoration agrees, but the compiled frame is `0x48` bytes instead
of `0x40`. Passing both inputs by readonly reference reduces the frame to
`0x38`. Passing the start by value and length by readonly reference reproduces
the original `0x40` frame and all instruction bytes. The only caller binds the
reference to `lbl_805D78EC`; the helper copies it before making any provider
call. No new pragma, compiler override or reserved stack array is used.

This is a matching source arrangement, not proof of the original parameter
spelling or source definition order. The owning unit and public link name are
unchanged.

## Validation

The starting main commit is `554d21699c873ccf9be1b2268eba37cd3a32e48b`.
A fresh original split, unchanged-main build, baseline report and retention
check were produced before editing. The isolated display checkpoint passes
`tools/check_pr.py`: one new exact function, 704 additional matched code bytes,
no matched-function, matched-data, coverage or source-linkage losses, and all
3,626 linked units remain exact. The rebuilt DOL matches its original SHA-1.
Direct object comparison also reports 100% with
`functionRelocDiffs=data_value`.
