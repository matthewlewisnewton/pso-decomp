# Keyboard composer native lifetime

This follows PR #268 checkpoint
`744ca04f63d697d9a22e28419e1afac55da31db7`. TWindowKeyBoardBase now has genuine
Base construction/destruction and ordinary-new producers. Its native compiler
table owns the existing 24-byte range at 804CFAB8. The historical text-holder
initializer has its actual storage receiver; no native holder class is invented.

## Constructor and buffer ownership

Original references identify exactly two 0xB8 producers, in Chat and
KeyBoardControl, with no subclass. The constructor forwards descriptor/client
four/layout position B7 to Base, initializes both holder pointers, then preserves
the original resets, active-holder selection, language snapshot and tail fields.
The Japanese branch alone allocates the 0x194-byte array at 0x9C and sets B0 to 0x94;
no additional field initialization is inferred outside that branch.

Destruction preserves array 0x9C cleanup, holder 0x84 cleanup with flag -1, holder 0x6C
cleanup with flag -1, then automatic Base destruction. The existing holder cleanup
helper frees its backing array. A negative flag prevents deletion of embedded
storage. No ownership is assigned to the active-holder pointer at 0x68, which points
inside the same window. Complete constructor 240 and destructor 124 bytes match.

The byte at 0x65 now uses s8, consistent with its original signed -1 initialization
and existing signed-byte selection stores 0x08..0x13. This bounded representation
correction produces the original sentinel instruction; it does not establish
uniquely original source signedness. Existing other receiver views remain
qualified. Layout assertions retain the two 24-byte spans 0x6C..0x84 and 0x84..0x9C,
along with the existing 0xB8 total-size assertion.

## Correct the holder initializer receiver

The old init_text_buffer_holder method was named as a KeyboardBase member but
its only two callers pass this+6C and this+84. Its 64-byte body initializes a
24-byte text record, not a complete window. The same historical export is now an
ordinary C function with a void* storage receiver. Its name, body and resolved
call targets remain unchanged. The false window-member declaration is removed.

The flat scalar record representation and existing reset/cleanup byte views are
retained. This is not recovery of nontrivial embedded C++ holder objects, native
holder constructors/destructors or a portable aliasing contract. Wider buffer,
keyboard-input and mixed Soft/Hard receiver interfaces remain separate holds.
No new raw initializer binding, wrapper body or function-pointer cast is added.

## Native table and preserved original prefix

The compiler table is exactly 24 bytes with four original slot targets:
destructor, task, render and inherited TObject shadow. All raw table bytes and
four resolved relocations match. Its existing FAB8 start is naturally aligned.
The preceding descriptor and other keyboard data remain original input.

The former 96-byte original provider at 804CFA70 is refined into its unchanged
72-byte prefix and the 24-byte native table. The prefix includes the descriptor,
its neighboring unknown words and conversion-exclusion data, and remains selected
once. No descriptor/data ownership beyond the table is claimed. No gap, source
padding, manual table or compilation control is introduced.

## Validation and remaining work

The shared-capacity serialized build reproduces DOL SHA-1
`0d85744b51d7379efb025a943d0cd5aaae2191a3`. check_pr against 744ca04f63 passes:
+24 matched/linked data bytes, zero exact-function/code/unit/coverage/address
regression. Totals remain 27,395 exact functions and 3,588 exact linked units.
Retention is clean at 17,850; port inventory passes unchanged.

Four complete text sections and all resolved text relocation targets match main
originals: composer 692, holder/LensFlare owner 588, Control producer 3284 and Chat
producer 3808 bytes. All four compiled objects are actual linker inputs once.
Existing unrelated data/constant sections remain unchanged. The historical
holder initializer is independently exact, and emits no competing table.
Original prefix 72 and native table 24 have distinct verified providers.

Balloon construction/destruction/initializer holds, Menu/List/controller folding,
ChatSymbol, WS_String, Parts and every protected remainder retain their prior
validation. The protected 1,044-byte helper remains original and unchanged.
This family removes another raw Base pair, leaving 27 calls across 13 source units
and the four shared Base/Addition ABI bindings. ScrollBar, Parts constant,
ChoiceSetting/global ownership, callback and wider interface holds remain.
PR stays draft.

Integrated main remains `12cc95ca737a3a8757c17f45df06a9af4821d872`. Combined PR
deltas versus its separately validated source baseline are +600 matched code,
+1220 linked code, +1472 matched data and +1428 linked data bytes. The fourteen
qualified four-byte alignment gaps are unchanged.
