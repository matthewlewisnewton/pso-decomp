# Full-width keyboard-query contract

This checkpoint follows `c028ae42a3b9794c1492b6c4108376b448b1cae1` and resolves
the specific B0 return-forwarding hold in the previous global-query note using
new original-caller evidence, not a repeat of the wrapper-only probe.

## Original return-width evidence

A complete active-object relocation census finds three original direct calls
to 0x801321B4, with no original table/address-taking reference in that census:

- At 0x80132194, the same-unit caller tests the entire returned r3 with cntlzw.
- At 0x8025FCDC, Hard modifier processing compares the entire r3 to zero.
- At 0x801A58C4, the global wrapper forwards r3 unchanged to its integer callers.

The callee's original exits construct zero or one. Together these support a
full-width zero/nonzero contract. They do not uniquely establish signedness,
original source spelling or an original receiver class. Arbitrary runtime address
arithmetic is outside the reference census.

The reconstructed callee now returns s32 consistently. Its final predicate uses
`condition ? 1 : 0`, an ordinary integer-predicate form that evaluates its call
once. The global wrapper explicitly returns that integer result. The same-unit
function-pointer cast that previously pretended the bool function returned s32
is removed. A narrow shared header provides both declarations to the definitions
and their direct callers. Existing word-sized state-address transport remains;
this does not establish a portable pointer or ownership model.

## Bounded probes and validation

The earlier wrapper-only change failed because the callee was still bool-typed.
The new whole-chain s32 probe with a plain C++ bool return expression grew the
callee from 192 to 196 bytes with byte normalization absent from the original.
That intermediate patch/build evidence is retained. The natural integer-predicate
form restores the original full-width result without flags, inline assembly,
extra state, or changed control semantics.

The resulting capacity-gated build reproduces the original DOL. Every captured
compiled object is raw-identical, covering all caller/callee payloads, symbols,
relocations, data, tables and metadata. Independent source review found no
semantic blocker in the integer predicate and return-contract correction.
Aggregate checks, all 346 tool tests and portable behavior tests pass, with no
matching loss or retention drift.

This clears only the identified inconsistent query-return types and B0 forwarding
hold. The separate has_non_modifier_key receiver question, Hard table/destruction,
borrowed-composer lifetime, Word/ComCard and other window-family holds remain.
