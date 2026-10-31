#include "pso/misc/ParticleFactory.h"
#include "types.h"
#include "pso/player/TObjPlayer_80128AE4.h"
#include "pso/unk/text_80087278.h"
#include "pso/player/TObjPlayer.h"
#include "pso/unk/TUnk_804A4020.h"

struct Elem_80128A74 { u8 pad[0x1c]; u8 f1c[0x2c - 0x1c]; };

struct Obj_80128A74 { u8 pad[0xa4]; Elem_80128A74 *elems; s32 count; };

extern "C" {
Obj_80128A74 *find_entity_by_id(s32);
s32 play_sound_effect(s32, s32, s32, s32);

void TObjPlayer__sub_80128A74(s32 a, u32 b, s32 c, s32 d) {
    Obj_80128A74 *o;
    ((TObjPlayer *)b)->clear_rico_ring_flag();
    o = find_entity_by_id(c);
    if (o != 0 && o->elems != 0 && d < o->count) {
        spawn_particle_effect((const Vec *)(o->elems[d].f1c), 0x45);
    }
}

void TObjPlayer::notify_hit_target(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    if ((arg1 != 0U) && (arg3 != 0U)) {
        ((TObjPlayer *)arg1)->clear_rico_ring_flag();
        spawn_particle_effect((const Vec *)(arg3), 0x45);
        play_sound_effect(0x4001C112, 0, 0, 0);
    }
}

}
