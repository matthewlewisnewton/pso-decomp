# DD scaled random receiver

`0x800B9F64` receives its actor in `r3` and forwards it to
`TObjChara::random_ratio` at `0x80011014`. It multiplies the returned float by
65535.0 and truncates the result to `s32`. The method therefore needs the
actual actor even though its former static declaration had no explicit
arguments.

The ratio helper uses the receiver's random state at `+0x160` in its
per-actor path; it can use a global random source in another phase. The DD
ownership is supported by the known callers but does not establish the
original source spelling. All implemented DD-family callers now pass their
actor explicitly; unrelated legacy random helper declarations remain outside
this recovery.
