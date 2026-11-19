#include "pso/map/CsnQuery.h"
#include "pso/map/TObjMapCsn.h"

extern s32 map_csn_ctrl_instance;
extern CsnContact lbl_804FF9C0[32];
__declspec(section ".sdata2") extern const f32 csn_zero;
__declspec(section ".sdata2") extern const f32 csn_empty_ray_depth;

void *TObjMapCsn::get_data_ptr() { return (char *)this + 0x1C; }

s32 TObjMapCsn::get_map_count() { return map_csn_ctrl_instance; }

WallRayResult::WallRayResult() {
    index = -1;
    depth = csn_empty_ray_depth;
}

CsnHit::CsnHit() { reset(); }

void CsnHit::reset() {
    hit_mask = 0;
    contact = lbl_804FF9C0;
}

CsnContact::CsnContact() { clear(); }

void CsnContact::clear() {
    point.x = point.y = point.z = csn_zero;
    normal.x = normal.y = normal.z = csn_zero;
    flags = 0;
}
