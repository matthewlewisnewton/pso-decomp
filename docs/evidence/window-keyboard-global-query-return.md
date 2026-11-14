# Explicit global keyboard-query return

This checkpoint follows `6b36ec6c53d2d61e733d102282f0bf3e7d351f61`.
The original 40-byte helper at 0x801A58D8 loads the global keyboard-state address,
calls the existing s32 query at 0x80132310 and returns without altering its r3
result. Player and window-controller callers test that integer result. Yet the
source definition and its two header declarations were void, discarding the
callee result and relying on incidental register preservation.

The wrapper now explicitly returns the existing s32 result, and both header
entries agree. No argument, callee body, condition, symbol, caller, global
representation or ownership is changed. This recovers the observed integer
return contract without claiming an exact original source spelling.

The capacity-gated build reproduces the original DOL. Every captured compiled
object remains raw-identical, including the wrapper and all its consumers.
Independent source review found no blocker in this two-file repair. Aggregate
checks, all 346 tool tests and portable behavior tests pass, with no retention
drift or matching loss.

## Rejected wider probe and retained holds

The adjacent helper at 0x801A58B0 also forwards a result, but its callee is
currently declared bool. A bounded attempt to return that value as s32 changed
the generated owner and failed the original-DOL check. That candidate was not
published; its patch and build evidence were retained. B0 and all related caller
imports were restored before validating the independent D8 correction. Do not
repeat that probe without new evidence about the callee return-width contract.

This does not establish has_non_modifier_key's original receiver contract.
Original Hard code passes its receiver, whereas the global-state helper chain
does not use that incoming value. Static/member ownership cannot be inferred
from that alone. Hard table/destruction, borrowed lifetime, Word/ComCard and
other window-family holds remain unchanged.

Subsequent [full-width caller evidence](window-keyboard-integer-query-contract.md)
resolves the B0 return-forwarding hold; the failed wrapper-only probe remains
historical evidence, and receiver/lifetime holds are not cleared by it.
