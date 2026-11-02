#include "types.h"
#include "pso/object/TObjButterflyLobby.h"
#include "pso/map/CsnResult.h"

extern "C" {
void *mem_alloc(u32 size);
extern u32 wall_query_scene_buffer;
s32 TObjPlayer__sub_80079118(s32 *_w0);
void TObjPlayer__sub_8007911C(void *, void *, u32);
s32 query_segment_wall_meshes(void *, void *, u32, void *);
u32 query_collision_segment_groups(void *, void *, u32);
extern char lbl_804389FC[];
extern u8 lbl_804FFD40[];
void mem_free(void*);

CsnHit *csnVector(const Vec *from, const Vec *to, u32 mask) {
    CsnHit *hit;
    TObjPlayer__sub_8007911C((void *)from, (void *)to, mask);
    hit = &lbl_80500140;
    if (query_collision_segment_groups((void *)from, (void *)to, mask) == 0) {
        hit = 0;
    } else if (query_segment_wall_meshes((void *)from, (void *)to, mask, lbl_804FFD40) == 0) {
        hit = 0;
    }
    TObjPlayer__sub_80079118((s32 *)lbl_804389FC);
    return hit;
}

void TObjButterflyLobby::free_singleton_805D4E6C() {
    if ((u32) wall_query_scene_buffer != 0U) {
        mem_free((void*)wall_query_scene_buffer);
        wall_query_scene_buffer = 0U;
    }
}
void TObjButterflyLobby::alloc_scene_buffer() { (*(int *)&wall_query_scene_buffer) = (int)mem_alloc((u32)((void*)20480)); }

}
