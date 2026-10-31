# Persistent positional sound

The original entry point at `0x80226578` is a free function that takes a sound ID, an opaque identity value, an optional position, a signed adjustment and flags. It returns a slot or a negative result; the refresh path can propagate errors other than `-1`. The identity is stored and compared by the looping-voice allocator. This supports an opaque pointer interface, not a particular actor class or a receiver.

The front-end request lookup matches an active request by sound ID. When it refreshes an existing request, it reuses the identity already stored on that request rather than necessarily replacing it with the incoming one. The position pointer can be retained by the request and the voice for later reads; callers must keep its storage valid for the relevant lifetime. Null position is accepted, but does not necessarily clear a position previously associated with a reused voice.

The original call inventory has 195 direct calls in 86 units, including 14 units linked from original fallback objects. Explicit pointer casts at existing byte-array or integer-held position fields do not establish `Vec` object lifetimes or ownership. The original source spelling and exact identity type are not proven.

The immediate position-admission and slot-position forwarding calls now pass the arguments observed in the original code. The pre-existing two-argument declarations and calls of `fn_802264B8` remain: its body uses the slot only, while original callers set an additional register. They are retained for matching and require separate recovery; they are not evidence of a meaningful second parameter. The existing `TOTrapAncient01::check_trigger_flag` ownership alias, downstream integer-address interfaces, and the independently larger one-shot `play_sound_effect` interface also remain outside this bounded migration.

The new-request path forwards the full adjustment value. The refresh path stores it as a signed 16-bit field and reloads it sign-extended, so the shared entry-point adjustment must not be globally narrowed to `s16`.
