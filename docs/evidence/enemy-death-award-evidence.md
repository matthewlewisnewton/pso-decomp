# Enemy experience and drop wrappers

`TObjEnemy::distribute_experience_and_request_drop` at `0x800F6B14` calls
`distribute_experience` and then `request_standard_drop` on the same enemy.
The latter wrapper at `0x800F6B48` calls the standard drop request helper.
Original references are direct calls: 24 to the combined wrapper and two to
the drop-only wrapper, including Lappy. Traced receivers are enemies, including
enemy paths whose enclosing functions currently have misleading Player names.

The native wrappers return `void`; callers do not have a supported result to
consume. This recovery does not establish ownership of the enclosing
functions or the lifetime of their actor overlays. The downstream standard
drop helper still has a `void *` declaration here while its owner declares a
specific opaque record pointer; that boundary needs separate reconciliation.
