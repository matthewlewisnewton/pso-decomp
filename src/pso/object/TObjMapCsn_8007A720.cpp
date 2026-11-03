#include "types.h"
#include "pso/object/TObjMapCsn.h"
#include "pso/unk/text_8007A7A0.h"

extern "C" {
    extern const float lbl_805D9204;
void*TObjMapCsn::get_data_ptr() { return (char*)this + 0x1c; }

extern s32 map_csn_ctrl_instance;

s32 TObjMapCsn::get_map_count() {
    return map_csn_ctrl_instance;
}
}

CsnQueryResult::CsnQueryResult() {
    index = -1;
    best = lbl_805D9204;
}

CsnHit::CsnHit() {
    fn_8007A7A0(this);
}
