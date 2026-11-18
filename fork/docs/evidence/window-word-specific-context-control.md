# Word-specific compilation-context audit and bounded control

This follows continuation `1db9706d25cc97e55d1b02e2046430ae1a6242c8`, the
[Word pooling observation](window-word-data-pool-observation.md) and the
[independent Fish/Falz control](window-word-native-table-context.md). The stack
was clean at focused `3fb4ac0993` and main `baa0b4e482`; no competing head update
was observed. This investigation changes evidence only, not production Word
source, compiler settings, providers or holds.

## What provenance establishes

The fork's initial `150fd86535fe023c804b8c391c1b7773cf58495f` Word owner is a
generated decompiler slice with placeholder queries, a manual deleting body and
an external table label. Later recovery adds the raw initializer/factory and
manual data/table definitions. `f797082c213220eff5cbbd6cfbb7f78a0fe068b3`
adds the recovered startup stores and `.ctors` reference. This is recovery history,
not preserved retail build metadata or evidence of an original source order.
The inspected path-specific configure history identifies no Word deferred override.

Upstream was independently pinned at
[`8c507b2dacae5428291a823c3868ca486419660c`](https://github.com/zeroz41/pso-decomp/commit/8c507b2dacae5428291a823c3868ca486419660c).
Its relocated
[Word owner](https://github.com/zeroz41/pso-decomp/blob/8c507b2dacae5428291a823c3868ca486419660c/src/pso/ui/window/TWindowDD_80342254.cpp)
(blob `32688926ceed5666e9fad6e8795466a4205d924a`) still uses a manual table and
raw initializer. Its
[configuration](https://github.com/zeroz41/pso-decomp/blob/8c507b2dacae5428291a823c3868ca486419660c/configure.py)
(blob `261e1614d0bd1f9dcdb5ef39ffef44a6b80ad817`) supplies no Word-specific deferred
setting. Neither that source nor the fork history supplies native Word build-profile
provenance. This bounded search is not proof that no such evidence exists elsewhere.
No upstream source is imported.

Word itself supplies a concrete object constraint: the original initializer uses
one retained data address base for its descriptor, position and table. The
previous pinned-compiler observation found the native table unavailable during
immediate function generation. Fish demonstrated a real native-table timing
mechanism. Together these justify a diagnostic of timing in Word, rather than
assuming the Fish result proves Word's original context.

## One fixed-source diagnostic

The control freezes the previously failed native-destructor/table candidate and
its matching Word header. The initializer remains the same legacy C function;
this is not a new native-constructor attempt. Source SHA-256 is
`269e8aad937b52fdca5e6f3896e752dc7d5c859da0cf5af02f4f25a01d4e3c65`.
Only the argument after `-inline` changes from `off` to `off,deferred`.
There is no definition reordering, declaration/layout variant, manual table,
new reference, optimizer toggle or modified production configuration.

The same pinned GC/2.6 executable and production target options are retained.
Four read-only hardware breakpoints observe table declaration, function generation,
data-pool eligibility and anchor-reference addition, as in the Fish control.
The run holds the existing legacy capacity gate and debugger lock. Its complete
traced ELF equals a separate identical-options normal control byte for byte.

One initial runner invocation mistakenly selected the first `off` argument,
which belonged to `-Cpp_exceptions`. The compiler rejected that command before
source parsing, with zero observation events and no object emission. Its usage
error and empty trace are isolated privately. Correcting the selector to the
value immediately after `-inline` produced the single successful diagnostic
reported here; no source or profile candidate was evaluated by the rejected command.

## Timing recovers, exactness does not

The actual 24-byte compiler table is now declared before all seven functions.
During initializer generation it is a defined `.data+0x40` object and shares the
descriptor/position pool root. The observed group reaches three distinct objects
and becomes full, with virtual register 37. Thus deferred compilation resolves
the measured eligibility/timing problem in this exact frozen Word source pair.

That does **not** reproduce the original initializer:

| Quantity | Original / published | Immediate native-table candidate | Deferred diagnostic |
| --- | ---: | ---: | ---: |
| Retained initializer | 148 | 156 | 152 |
| Complete owner text | 664 | 672 | 668 |
| Owned data | 88 | 88 | 88 |
| .ctors record | 4 | 4 | 4 |

The deferred initializer shares the pre-Base-call address base for descriptor and
position, but still materializes the table separately after that call. The original
retains its base across the call and forms the table pointer from it. The diagnostic
initializer has nine text relocations against the original's seven, and different
register use. A full pool group is not by itself proof that every address use is
lowered through that base. Binding/lowering remains an evidence question; these
observations do not identify its cause or justify another declaration variant.

## Whole-object qualification and explicit failure boundary

All seven functions are compared separately against the original, including their
normalized, function-relative relocation offsets/types/resolved targets:

| Function | Original bytes | Diagnostic bytes | Body and relative targets |
| --- | ---: | ---: | --- |
| First query | 20 | 20 | Exact |
| Second query | 20 | 20 | Exact |
| Native deleting destructor | 116 | 116 | Exact |
| Retained initializer | 148 | 152 | Different |
| Factory | 92 | 92 | Exact |
| Startup stores | 72 | 72 | Exact |
| Following DD helper | 196 | 196 | Exact |

The complete 88 data bytes and all five normalized data relocation identities
match, including the compiler table's four function targets. All owned section
types, flags and alignments are preserved: text align4, data align8 and ctors
align4. The ctors record's four raw bytes and normalized function-target identity
also match.

However, function generation reverses the frozen source's definition order.
The startup function moves from original text offset396 to196, and the deleting
destructor from40 to512. Normalizing their symbolic identities to the original
catalog does not preserve those actual candidate addresses. Neither the ctors
reference nor table pointers qualify at linked addresses. The complete text is
668 bytes, has a different order and is not exact. Six exact bodies and exact
raw data therefore cannot qualify this owner. No full-game candidate build or
DOL pass is claimed; the object has already failed its required size/order gate.

## Result and stop condition

This control supports deferred compilation as a mechanism for early table
availability in Word, but refutes its sufficiency for the frozen raw initializer.
It does not establish the retail profile. No production source/profile change,
text reordering, provider update, lifetime activation or hold removal follows.
The lane stops after this diagnostic, without source-order or binding variants.

The C initializer still uses an explicit table-symbol transport boundary; the
control does not test a genuine Word constructor's compiler-generated vptr store.
The subsequent [native-construction control](window-word-native-vptr-control.md)
tests that distinct boundary with one fixed source in both contexts. Its deferred
constructor148 and all seven bodies/relative targets match, but reversed function
order and actual table/startup destinations still prevent activation.
Any future native-construction reconstruction must justify that source boundary
and its compilation context independently, preserve the complete text/data/ctors
and all callers, and pass full linked-original qualification and review. Timing
alone or success of an isolated body is insufficient.

Private replay scripts, receipts, traces, comparisons and objects are in
`pr403-word-specific-context/`; no original-game binary, object or raw disassembly
is published here. Independent read-only review confirms the bounded result and
the distinction between normalized identity and actual linked placement. The
published Word owner, renderer, original DOL and coverage remain unchanged, with
all other ownership, initialization, interface and original-provider holds retained.
