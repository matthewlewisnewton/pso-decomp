# Chat task uses the native composer predicate

This follows cee0379e5e. TWindowChat's constructor stores an ordinary-new
TWindowKeyBoardBase in its composer field. The earlier composer-lifetime evidence
identifies the original 0xB8 producer and matching constructor. Its run_task now
calls that real member through the composer pointer instead of transporting the
pointer through three integer casts to a hand-mangled extern C alias.

The prior full-width predicate census includes this original call: its result
is immediately compared with cmpwi r3,0. The native declaration returns int,
consistent with the existing raw declaration and observed complete-word test.
No guard, receiver, ordering, flag write or null behavior is changed. This is
not an additional lifetime proof and adds no ownership or null-check assumption.
The two remaining raw calls through recovered Chat overlays are unchanged;
this checkpoint does not claim those interfaces are recovered.

The gated native build reproduces the original DOL. All 3,655 captured compiled
objects and the DOL are raw-byte-identical to the parent checkpoint. Aggregate
no-loss checks, retention and exception inventories pass. Independent source
review accepts the scoped receiver/call correction. No match gain is claimed;
all substantive family, table, lifetime and raw-interface holds remain.
