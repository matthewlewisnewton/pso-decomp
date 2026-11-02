#include "pso/unk/text_8007A7B8.h"

// CodeWarrior emits the static initializer at 0x8007A6C8 from these three
// constructors, including its supported __construct_array callback for the
// contact pool. The intervening byte buffer is not dynamically initialized.
extern "C" {
Record_8007A7B8 lbl_804FF9C0[32];
typedef char lbl_804FF9C0_size[sizeof(lbl_804FF9C0) == 0x380 ? 1 : -1];
u8 lbl_804FFD40[0x400];
__declspec(section ".data") CsnHit lbl_80500140;
CsnQueryResult csn_query_map_object;
}
