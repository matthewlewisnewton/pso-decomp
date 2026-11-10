# ComCard native render body and explicit context receiver

This follows continuation #403's current-main refresh at `d4717a366a`, based on
main `b3062dc640`. It recovers the existing 80-byte basic ComCard render body
as the actual member, without activating the held destructor/table partition.

## Established receiver and helper contract

TWindowComCard already has the exact 0x60-byte Base-derived declaration and a
virtual render member. The original renderer at 80249AC0 is referenced only by
its own table: the sole all-section reference in the 4970-object active original
graph is ADDR32/addend zero at owner data offset 0xEC (804CE90C). No direct or
mixed-receiver caller is found.

The existing shared TWindowDD::draw_default_entry(s32) definition interprets its
input as a Base window, calls setup_window_draw_context and returns the context
word. Existing exact native renderers already use that declared contract. The
new body passes this explicitly, calls the inherited frame method, then forwards
this and the actual m_24 storage address to the unchanged entry-drawing boundary.
The former C-named body depended on the window remaining in the incoming
argument register across a no-argument helper view. No new receiver or return
contract is invented, and the context remains a qualified word-valued boundary.

The existing C-named renderer declaration remains only as the manual table's
entrypoint binding. Its export, receiver transport and table target are unchanged;
there is no new alias definition, wrapper, function-pointer view or native table.
The follower's existing implementation and helper views are unchanged.

## Exact complete object and executable

One ordinary direct-member probe reproduced the complete compiler object,
byte-for-byte. After the ABI-binding comment and final full build, before/after
ELF SHA-256 remains:

`b9753b342c5c111af2eb2b9a019ef8c6de0ca910529e436d45ad3d0f869f2e99`

This covers all 1844 text bytes, the 80-byte renderer, 424 data bytes, eight-byte
conversion pool, section headers, symbols and every relocation. No compiler
control, initializer, allocation, data order, split or retention change is made.
The capacity-gated full build preserves DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`.

check_pr against the published refresh passes with zero metric, function,
provider or address-coverage delta. Comparisons against refreshed focused #402
and current main also pass; all 3590 linked units remain exact. Retention,
port inventories and protected-original checks remain clean. Independent
read-only review confirms actual member ownership and the preserved ABI binding.

## Remaining holds

The raw deleting wrapper, manual 28-byte table and unknown word at
[804CE914,804CE918) remain untouched and source-linked as before. No padding
classification, ownership claim or four-byte regression exception is introduced.
This removes the render-body implementation hold only; it does not establish
complete portable native-class recovery or solve the earlier partition blocker.

The [historical bounded audit](window-status-page-com-card-blocker-audit.md)
remains valid for its stated probes. This standalone member recovery uses the
already-established receiver contract and does not repeat the partition attempt.
Follower construction, callbacks, constant ownership, partial initialization,
remaining raw lifetime interfaces and every other current hold remain explicit.
