# Word native lifetime and complete emitted object

This reconstruction continues PR #403 from `7874908788`. It supersedes the
placement failure in [the fixed-source native control](window-word-native-vptr-control.md),
without treating the selected compilation arrangement as historical source or
retail compiler-option provenance.

The original owner requires seven functions at text offsets 0, 20, 40, 156,
304, 396 and 468, with sizes 20, 20, 116, 148, 92, 72 and 196. Its native table
at `804EFC90` must point to the deleting destructor, task, renderer and inherited
shadow renderer. The constructor shares one data base for the descriptor,
position and table. The earlier controls established why immediate generation
could not pool the compiler-owned table and why deferred generation could.

The contributor guide and [compiler-emission evidence](compiler-emission-evidence.md)
allow an explained source arrangement that reproduces native emission. This
change reverses the seven definitions and uses `-inline off,deferred` for this
owner. Deferred emission reverses their order again in the object. No function,
metadata object, reference, padding word or translation unit is added to steer
emission. The existing split boundaries and data definitions stay intact.

Word now has an ordinary two-word constructor, deleting destructor generated
from the native destructor, ordinary-new factory and compiler-generated vtable.
The constructor initializes Base with the existing descriptor and position,
then performs the observed name, list ID, count, selection, scroll and flag
stores and reset/loader calls. The destructor releases and clears the existing
buffer before automatic Base destruction. The list-ID field replaces the opaque
four-byte field at offset `0x70`, with an offset assertion. The raw initializer,
manual deleting protocol and manual table are removed. Their three catalog
entries are renamed at the same original addresses, and retention is regenerated.

A comparison with the original split object verifies every allocated section's
bytes, size, flags, type and alignment: text 664, data 88 and ctors 4 bytes.
All seven function offsets and sizes match. All 41 relocation records match in
section, offset, type and actual resolved address including addends; definitions
are resolved using their emitted offsets, rather than catalog normalization that
could hide a placement error. This includes the startup record's destination
`803423E0` and all four real table targets. The complete linked build reproduces
original DOL SHA-1 `0d85744b51d7379efb025a943d0cd5aaae2191a3`.

The shared reset and list-loader interfaces remain qualified target ABI
boundaries. Raw storage, buffer ownership, helper typing and original compiler
provenance are separate questions; this change establishes native construction,
destruction, table emission and original linked placement, without claiming a
complete portable model for the surrounding window family. Matching coverage
is unchanged because the previous raw implementation was already exact.
