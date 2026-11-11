#include "types.h"
#include "pso/object/lobby/TObjButterflyLobby.h"
#include "pso/system/ArrayAllocation.h"

struct Hit_8007A5D8 { u8 pad[0x40]; };

extern "C" {
extern u32 wall_query_scene_buffer;
s32 TObjPlayer__sub_80079118(s32 *_w0);
void TObjPlayer__sub_8007911C(void *, void *, u32);
s32 query_segment_wall_meshes(void *, void *, u32, void *);
u32 query_collision_segment_groups(void *, void *, u32);
extern char lbl_804389FC[];
extern u8 lbl_804FFD40[];
extern Hit_8007A5D8 lbl_80500140;
Hit_8007A5D8 *csnVector(void *from, void *to, u32 mask);

Hit_8007A5D8 *csnVector(void *from, void *to, u32 mask) {
    Hit_8007A5D8 *hit;
    TObjPlayer__sub_8007911C(from, to, mask);
    hit = &lbl_80500140;
    if (query_collision_segment_groups(from, to, mask) == 0) {
        hit = 0;
    } else if (query_segment_wall_meshes(from, to, mask, lbl_804FFD40) == 0) {
        hit = 0;
    }
    TObjPlayer__sub_80079118((s32 *)lbl_804389FC);
    return hit;
}

void TObjButterflyLobby::free_singleton_805D4E6C() {
    if ((u32) wall_query_scene_buffer != 0U) {
        ::operator delete[]((void*)wall_query_scene_buffer);
        wall_query_scene_buffer = 0U;
    }
}
void TObjButterflyLobby::alloc_scene_buffer() { (*(int *)&wall_query_scene_buffer) = (int)::operator new[]((u32)((void*)20480)); }

}
