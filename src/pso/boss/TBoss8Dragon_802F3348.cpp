#include "types.h"
#include "pso/boss/TBoss8Dragon_802F3348.h"
#include "pso/misc/TLobby_8007C550.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TUnk_804E4BF0.h"
#include "pso/object/TObjControl.h"

struct Ent_802F33C8 { u8 pad0[0x38]; f32 x, y, z; u8 pad44[0x60 - 0x44]; s32 rot; };

extern "C" {
f32 calc_random_ratio__10TObjPlayerFv(void *);
void subtractive_rng_seed(void *, s32);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
static const f32 lbl_805DED40 = 65535.0f;
static const f32 lbl_805DED44 = 320.0f;
u8 *TBoss8Dragon__sub_802F3348(s32 arg0) {
    if (boss8_dragon_leader_part == NULL) {
        return NULL;
    }
    return get_enemy_entity(boss8_dragon_leader_part->get_part_entity_id(arg0));
}
u16 TBoss8Dragon::get_global_part_count(s32 arg0) {
    if (boss8_dragon_leader_part == NULL) {
        return 0xFFFFU;
    }
    return boss8_dragon_leader_part->get_part_entity_id(arg0);
}
void TBoss8Dragon::place_parts_in_ring(s32 arg1, s32 arg2) {
    s32 n = (s32)this;
    Vec v;
    u8 buf[0xEC];
    s32 ang;
    s32 step;
    s32 i;
    Ent_802F33C8 *e;
    __ct__14SubtractiveRngFv(buf);
    if (n <= 5 && boss8_dragon_leader_part != NULL) {
        subtractive_rng_seed(buf, arg2);
        ang = (s32)(lbl_805DED40 * calc_random_ratio__10TObjPlayerFv(buf));
        step = 0x10000 / (n + 1);
        e = (Ent_802F33C8 *)get_enemy_entity(boss8_dragon_leader_part->get_part_entity_id(0));
        e->x = lbl_805DED44 * sin_table_lookup(ang);
        e->z = lbl_805DED44 * cos_table_lookup(ang);
        e->rot = (u16)(ang + 0x8000);
        for (i = 0; i < n; i++) {
            ang += step;
            v.x = lbl_805DED44 * sin_table_lookup(ang);
            v.y = e->y;
            v.z = lbl_805DED44 * cos_table_lookup(ang);
            boss8_dragon_leader_part->spawn_attack_object(&v, (ang + 0x8000) & 0xFFFF, arg1, i + 1);
        }
    }
}

}
