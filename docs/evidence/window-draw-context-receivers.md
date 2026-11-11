# Explicit ComCard follower and String draw-context receivers

Two renderers declared the existing draw-context helper with no argument,
implicitly depending on the incoming window in r3. They now call the established
`TWindowDD::draw_default_entry(s32)` declaration with their existing receiver
word. The ComCard follower retains its context pointer cast; String retains its
raw pointer/context storage and subsequent transform. No receiver class, lifetime,
layout, return width or data ownership is reconstructed by this repair.

This follows continuation `96903239e2942532d7c389416dd348870e11f2cf`, focused
`37ed8308f9df0e8ff4426bcc187f378f337a2cbc` and unchanged main
`e65f11ce6ec99c006909422f81da1c0a46ac062e`. Current refs and the targeted open
window-PR search showed no competing update before investigation.

## Existing definition and original calls

The shared 56-byte helper at 80244CF4 already takes a window word, calls Base's
`setup_window_draw_context` with the depth-helper result and returns the context
word. Its declared contract is already used by the basic ComCard renderer and
other recovered renderers. The [basic ComCard note](window-com-card-render-member.md)
qualifies that existing receiver boundary separately from its lifetime/table hold.

A census of 4,966 active original objects and 249,768 relocations finds 28 references
to this helper, all zero-addend direct REL24 calls. The two changed sites are the
follower renderer at 80249DE4 and String's renderer in owner 80340EA8. Both already
retain `arg0 = (s32)this`; forwarding it introduces no allocation or ownership
claim. Two conflicting caller-local declarations are removed. Remaining legacy
draw-context callers and adjacent entry-drawing interfaces are unchanged.

## Whole-object and selected-input proof

One isolated candidate reproduces both complete compiler ELFs byte for byte:
ComCard's 1844-byte text owner and String's 832-byte owner. The subsequent production
rebuild reproduces the same identities. This covers all section headers, bytes,
symbols, tables, constants and relocations, including ComCard's existing 424 data
bytes and unknown trailing word, and String/ScrollBar's retained startup/data.
The complete Ninja graph and ordered linker inputs are unchanged. Both owners
remain selected from source exactly once, with their original objects absent.
No new source activation or coverage gain is claimed.

The full capacity-gated build passes in 3.96 seconds with original DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. The report remains byte-identical
to the prior published checkpoint. Address-based acceptance, all 3,601 exact
linked units, retention 18,584 and port inventory pass with zero metric change.
Prior focused/main comparisons and all historical coverage qualifications are
preserved by the identical report, graph and objects; a new standalone main
build is not claimed.

ComCard's trailing-word/table ownership and follower conversion-pool lifetime
holds remain. ScrollBar construction, broader String helper/interface
qualifications, Word function order and actual table/startup destinations,
Parts compiler provenance/export linkage and every
other original-provider/ownership/interface hold remain. No constant placement,
compiler setting, raw Base/Addition binding or protected remainder changes.

## Separate numeric-input contract: rejected, not activated

Reassessment also found an independently supported receiver mismatch at
`update_numeric_parameter_input__9TWindowDDFPv` (80342F84). Its exact 312-byte
definition and existing header use `u8(u8*)`, while four caller units declare
`s32()` and omit the receiver. An active original census finds six zero-addend
direct calls, with no address-taking or interior reference.

One private candidate uses that existing header and explicitly passes each
window, without changing the callee's types or logic. All six caller functions
retain their sizes but each changes one instruction: the published word-result
copy becomes unsigned-byte masking. The complete callee ELF remains identical.
Therefore all four caller objects fail complete identity. Correct receiver
transport does not qualify the combined return contract.

This candidate is not applied to production, and no full-game candidate pass is
claimed. No widened-return alternative, optimizer control, result-view wrapper or
source-layout variant is tried. New return-contract provenance is needed before
revisiting this boundary. The callee's remaining implicit-register helpers and
mixed child interfaces also stay qualified. The failed candidate does not affect
the two independently exact draw-context repairs above.

Private evidence: `pr403-draw-context-receivers/` contains the commands, scratch
compile receipt, original caller census, full-build receipt, complete-object
hashes and acceptance result. `pr403-numeric-input-contract/` retains its commands,
receipt, census, comparison and instruction-field proof. Original binaries,
objects and raw disassembly are not published. Independent source review supports
the bounded repair and the numeric stop condition; frozen-head review remains a
publication gate. The PR remains draft.
