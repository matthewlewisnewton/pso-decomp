# Projectile entity-ID contract

Candidate based on fork integration `beaa7f52af2a7360e18deafc771648f51b709531`.
`TUnk_804909C4::run_task` passes its `u16 owner_id` to `check_player_hits`.
The latter forwards that ID to the shared `find_entity_by_id(u16)` API.
Recovering the parameter as `u16` removes the incompatible function-pointer
call while retaining the original generated instructions. A direct call with
the previous `s32` parameter instead inserts an unwanted narrowing instruction.
The symbol metadata now records the compiler-emitted `FUs` signature.

Targeted compilation with the baseline GC/2.6 compiler and flags passed.
Compared with the baseline source object, all allocated bytes and alignment
are unchanged: text 1064 bytes, rodata 24, data 100, sdata2 16. Symbol and
relocation tables are identical after accounting for the one intended name
change. No binary rewriting was used.

This is a partial source checkpoint, not a completed PR100 validation. The
predicate and table-helper contracts remain pending the shared-owner fix.
Fresh combined full build, original DOL hash, coverage gates and independent
review are required before releasing the held integration candidate.
