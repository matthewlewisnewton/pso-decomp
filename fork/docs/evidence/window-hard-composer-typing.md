# Hard keyboard borrowed composer field

This checkpoint follows `2f0722e3b2a216aad694ef6b80974105d27fdabc`.
It supersedes only the statement in the historical Hard construction evidence
that offset 0x70 retains an integer-word declaration.

The two original constructor producers already establish a borrowed 0xB8
`TWindowKeyBoardBase` composer. The 0x74 Hard class now declares its final field
as `TWindowKeyBoardBase *m_composer`, retaining the same target layout. The
constructor assigns the pointer directly. Direct input helpers, LED updates,
task dispatch, release/reset forwarding and composer-flag reset now use this
pointer rather than integer or aliasing casts. Existing null guards, ordering
and reset calls are unchanged; no deletion or ownership transfer is introduced.

The capacity-gated full build passes. All 3,636 previously captured compiled
objects remain raw-byte-identical, as does the DOL. Thus no instruction, symbol,
relocation, table or PMF representation changes in this checkpoint. Independent
source review found no blocker in the five-file implementation. Fresh aggregate
checks pass with no metric loss or retention drift; all 346 tool tests and the
portable behavior suite pass.

Two raw offset-0x70 reads and the hand-mangled set_input_mode mixed receiver in
TKeyBoardControl_8025EC04.cpp remain qualified. This is not complete recovery of
every field consumer or a portable interface/lifetime claim. The original Hard
deleting wrapper/table provider, compiler-provenance and other window-family
holds remain untouched. No match or linked-data gain is claimed for this change.
