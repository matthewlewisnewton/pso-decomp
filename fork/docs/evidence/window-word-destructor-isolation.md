# Word destructor/table isolation and preserved initializer hold

This bounded test follows continuation `a04e2deb195aa84a0ff8134c73eac7852e74895b`
on main `c822df035d`. The earlier coordinated native Word probe reproduced the
destructor but failed its native constructor. This test asks a different question:
can the destructor and compiler-owned table be recovered while keeping the
published C initializer and factory? It makes no new native-constructor attempt.

## Evidence and test boundary

Word's original 0x90-byte producer and list loader establish the buffer at 0x80:
the loader assigns an allocated signed-halfword array or null, and destruction
releases it with delete[]. The 116-byte deleting body then performs Base cleanup
and the observed deleting protocol. The active original-object census finds one
reference to that deleting entry: its own vtable data relocation, with no direct
caller or other-section reference. No new destructor ABI binding is needed.

The candidate defines the actual Word destructor with buffer release/clear and
automatic Base destruction. The compiler emits its four-function, 24-byte table
in the same owning unit. The manual table is removed. The retained C initializer
references that actual emitted table using its existing vptr transport boundary;
it does not become a genuine C++ constructor or establish portable object
lifetime. No default constructor, wrapper, new compiler control, manual replacement
table, source padding, reference-hoisting device or data-layout variant is added.

## Component exactness does not qualify the complete program

The first ordinary candidate produces these measured results:

| Component | Published | Candidate | Result |
| --- | ---: | ---: | --- |
| Deleting destructor | 116 | 116 | Instructions and normalized relocation identities exact |
| User metadata plus table data | 88 | 88 | All raw bytes and five relocation identities exact |
| Compiler table within that data | 24 | 24 | Four original function targets; no extra slot |
| Factory body | 92 | 92 | Instruction bytes exact |
| Retained C initializer | 148 | 156 | Fails exactness despite unchanged operations |
| Complete owner text | 664 | 672 | Fails complete-unit qualification |
| .ctors record | 4 | 4 | Unlinked bytes and target identity agree; linked placement unqualified |

Table emission changes address materialization in the unchanged-source C
initializer. The original retains one data-base address across descriptor,
position and vtable use. The candidate materializes the compiler table separately
and changes register homes. The later text consequently shifts by eight bytes.
The full capacity-gated build fails the original DOL hash.

The relocation comparisons above normalize symbol identities and addends to the
original catalog; they do not prove the shifted linked addresses are preserved.
The matching destructor, table and factory components therefore cannot be
activated independently in this tested organization. The candidate remains private.

This isolates a stronger stop condition than the earlier native-constructor
probe: compiler-owned table emission also breaks address sharing in the retained
C initializer. Changing only the constructor spelling, removing a member reload,
or retaining the old initializer is insufficient. It does not prove native
recovery impossible or authenticate a unique original source organization.

## Restoration and next concrete evidence

All four candidate source/header/configuration files are restored to the published
checkpoint. A second gated build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The complete constructor-owner and
renderer ELF objects are byte-identical to their captured published versions.
check_pr passes with zero metric, function/data coverage or linked-address change;
3599 linked units are exact and retention18563 is unchanged. Independent read-only
review confirms the failed-probe evidence and the stop condition.

Further work needs independent evidence for the compiler/source ownership
relationship that permits the observed descriptor/position/vtable address sharing.
A matching native unit with the same three local metadata objects and compiler
profile would be a useful comparison. WS_String's current constructor is not that
control: it receives position from its caller and its descriptor has a separate
original provider. Adjacency and identical final bytes alone do not establish an
aggregate or justify moving declarations. No further table-placement, initializer
or optimizer variant is attempted without such evidence.

The native Word constructor, destructor/table and raw initializer lifetime holds
remain. The complete matched Word renderer, native task, raw reset/UV helpers,
other original providers and all prior coverage qualifications remain intact.

The subsequent [data-pool observation](window-word-data-pool-observation.md)
resolves the immediate compiler-mechanism question for the frozen pair: the
compiler table is undefined during function generation, so only two eligible
metadata objects reach the pool rather than the manual table's three. Final class
cleanup defines the real table afterward. This narrows the missing evidence but
does not qualify a source or profile change, activation or lifetime claim.
