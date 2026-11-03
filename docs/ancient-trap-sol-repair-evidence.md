# Ancient trap update control-flow constraints

`TOTrapAncient01::vfunc_81` has 540 instruction bytes and a 23-entry area
dispatch table at `0x804B4A78`. Its no-op area entries target the shared
epilogue at function offset `0x200`. Redirecting them to an equivalent sound
handler exit can preserve instructions while changing the table relocations.
Check instructions and every table target together.

The initial nonpositive-scale branch jumps to the ordinary `grounded` label
inside the switch's lexical extent. The four positive-scale sound handlers
return. The grounded block scopes its automatic initializations, and the
no-op case labels follow that block at the shared epilogue. The jump crosses
no automatic initialization. The area expression is evaluated only on the
positive-scale path; grounded execution does not consult it.

This source arrangement preserves the original dense table with GC/2.6 and
the unit's `-O4,s -inline off,deferred -sdata2 4` configuration. Moving the
no-op cases to a different exit can change the table or replace it with a
comparison tree. Deferred generation also affects when compiler controls
take effect, so a pragma around the function body may not control its final
emission.

Changes must preserve the adjacent 92-byte table at `0x804B4A1C`, the native
360-byte vtable at `.data` offset `0x50`, and the full original data extent
described in [Ancient trap layout and matching constraints](ancient-trap-recovery-wip.md).
This arrangement explains the required compiler output; it does not establish
the spelling used by the original authors.
