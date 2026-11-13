# Chat child-opening receiver overlay removal

At c98c03f8f1, RecoveredFields_8024792C_arg0 was a redundant receiver view used
only in the genuine TWindowChat::open_next_input_window member, with arg0=this.
Its eight accessed offsets already have native declarations and assertions in
TWindowChat.h: inputMode, flags, composer, softKeyboard, hardKeyboard,
symbolChatWindow, wordSelectWindow and result. This checkpoint removes that
struct and its duplicate assertions in favor of the existing class fields.

The signed input-mode switch, output word values 1/2/3, constructor calls,
allocation failure handling and call order are preserved. Existing integer
constructor results are explicitly converted when stored in pointer fields;
this does not change the external constructor ABI. Result retains its existing
s32 word access. Composer subobject arithmetic remains byte-scaled, not scaled
by the window type. There is no new null guard, lifetime or ownership assumption.

The nested Parts receiver at composer+0x30, raw depth write at +0x50, legacy
reset/constructor helpers, result-buffer contract and remaining unknown caller
are deliberately unchanged and still qualified. Removing the outer Chat overlay
is not evidence that those nested interfaces or lifetime/table holds are solved.

Independent source review passes. The capacity-gated native build reproduces
the original DOL; all 3,655 captured compiled objects and that DOL are raw-identical
to the parent checkpoint. Aggregate no-loss, retention and exception checks pass.
No matching gain or readiness claim is made.
