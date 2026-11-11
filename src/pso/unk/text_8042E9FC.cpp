// Native reconstruction of the restore at 0x8042E9FC..0x8042EA10.
// This local fragment is not a separately callable C++ operation. Preserve
// its existing symbol/extent without asserting an original source boundary.
// The native linker otherwise discards it because no relocation names it.
// See docs/evidence/loader-restore-retention.md for the exception and port plan.
#ifdef __MWERKS__
#pragma push
#pragma force_active on
extern "C" {
static asm void pad_03_8042E9FC_text(void) {
#include "orig_asm/pso/unk/text_8042E9FC/pad_03_8042E9FC_text.inc"
}
}
#pragma pop
#endif
