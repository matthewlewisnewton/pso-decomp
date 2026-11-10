# WS_Word task and scroll ownership

This follows PR #268 checkpoint `384cf280cb301b0839f4f11a21ebd6bf0699bfd9`.
The 912-byte task and its 52-byte scroll-offset helper now belong to the existing
0x90-byte Base-derived TWindowDD_WS_Word declaration. This is compiled method
and interface recovery; it does not activate native construction, destruction,
compiler tables or the task's whole source unit.

## Task, helper and result contracts

All-section original relocation inspection finds the task at 80341B28 only in
the WS_Word table. The scroll-offset helper at 80342220 has ten references, all
inside that task, with no observed address-taking or other caller. The task's
entry-list/selection/count/float fields fit WS_Word's existing image. Its helper
increments the actual word at 0x68, marks 0x8C and calls the existing sound helper.
Both declaration and definition move from the provisional DD receiver, and their
catalog symbols change together. There are no replacement wrapper bodies.

The task now names the actual fields: state at 0x60, selection/index words at
0x68/0x6C, count and visible limit at 0x74/0x78, shown count at 0x7C and float
scroll position at 0x88. The historical DD field names were offset from their
actual storage; they are not used as a layout claim for this window.

The initial status query has one original caller, this task. Its twenty-byte
body computes !(state & 1), returning zero or one in the word result register.
The original task compares the full register. The old byte declaration caused a
new byte-mask instruction when called through the actual member declaration.
Its declaration and definition now return s32, and the explicit member call
reproduces the original comparison and the unchanged query body. This does not
prove the unique original source spelling. The other scroll queries likewise
use their existing actual member declarations rather than no-argument C views.

The existing generic input/sound/Base update helpers and wider DD reinitialization,
element-list and render-context interfaces remain qualified. No complete identity
or native lifetime is inferred for their borrowed storage.

## Native lifetime probes remain held

The original constructor has one local factory caller. Its first word argument
is an element-list ID, including supported negative sentinels; its second word
is the visible-entry limit and updates the mutable shared layout record. The
list loader allocates an owned signed-halfword buffer at 0x80, or sets it null
for a missing list. The existing deleting function releases it with delete[].

A bounded constructor-only probe emitted 156 bytes against the original 148:
native vptr generation lost the shared data-base address and a member reload
added another instruction. A distinct coordinated native destructor/task/table
probe retained the 116-byte deleting body and 912-byte task. A local assigned
name pointer removed the reload, but the constructor still emitted 156 bytes:
position, descriptor and compiler table materialized separate addresses rather
than sharing the original data base. Neither probe is activated. No scheduling
control, artificial reference, manual vptr or replacement hand-written table is
introduced. Further lifetime recovery needs a supported source/data ownership
arrangement that reproduces that address generation while preserving all objects.

The original 148-byte C constructor, 116-byte deleting function and 92-byte local
factory are restored. The existing manual table, entry record, mutable position
and descriptor stay in the same 88-byte data image, and static initialization
retains its four-byte .ctors registration. Only the existing task relocation's
symbol name changes; its address and type remain identical. No competing native
table is emitted.

## Validation and remaining source-link blocker

The shared-gate full build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against 384cf280cb passes
with zero metric delta: 27,395 exact functions, 3,589 exact linked units and 3,653
source-bearing units. Retention is clean at 17,852 entries and port inventory
passes unchanged. Integrated main remains
`4e784e247d991f1fb25766fc80923242a9ba469a`.

The complete 664-byte constructor owner remains source-selected once. Its text,
88-byte data, four-byte .ctors entry and every resolved relocation match original
and preceding source objects. Its word status query remains exact. The helper
unit's complete compiled 2496-byte text and eight-byte conversion pool are
unchanged from captured 384c objects. All 24 compiled functions, including task
and offset helper, match their original function bytes and resolved relocations.

The helper unit still lacks the 916-byte TWindowDD__sub_80341674 body. Its complete
3412-byte original object remains selected once, and the compiled source object
is absent from executable inputs. No new task linkage or source coverage gain is
claimed. Hard keyboard, ComCard and protected-original provenance also pass,
including the original 1044-byte setup helper. No split, data range, gap,
retention name or compiler control changes.

Raw Base/Addition calls remain 24 across 13 units. Combined PR deltas against
fresh main remain +600 matched code, +1220 linked code, +1472 matched data and
+1428 linked data bytes. All other ownership/interface/constant/destruction holds
remain; PR stays draft.

The [renderer/vertex-storage audit](window-word-render-audit.md) records one
ordinary reconstruction of the missing body and its nonexact arithmetic result.
It retains the full original provider and explains the evidence needed before
another probe. Its shared-helper audit also corrects WS_String's local raw buffer
from 188 to 192 bytes, covering the reset helper's final color store without
changing the compiled object or asserting a complete rendering interface.
