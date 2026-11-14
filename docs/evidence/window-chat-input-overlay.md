# Chat input uses its existing class fields

This follows a89870dbea. The local RecoveredFields_8024775C_arg0 view was used
only inside the genuine TWindowChat::handle_chat_input member, where arg0 is
explicitly this. Its four accessed fields already have native declarations and
asserted offsets: inputMode u8 at 0x1C, flags u16 at 0x1E, composer at 0x20 and
hardKeyboard at 0x28. Removing that redundant overlay requires no new layout,
producer or ownership inference. The method now uses those existing fields.

The composer predicate uses the native KeyboardBase member: the existing Chat
constructor stores a newly constructed composer there, and the original-call
census proves the full-word result test. The hardware query still uses the same
Hard object. Input-mode byte truncation, subsequent signed-byte comparison,
flag masks, short-circuit order and null behavior are unchanged. The distinct
controller-input global view, external helper contracts and unknown Win_8024701C
caller remain unchanged. This is not clearance of those interfaces or of the
broader lifetime/table holds.

Independent scoped source review passes. The gated native build reproduces the
original DOL; all 3,655 captured compiled objects and the DOL are raw-identical
to the parent checkpoint. Aggregate no-loss, retention and exception checks
pass. No metric gain, source-owner expansion or readiness change is claimed.
