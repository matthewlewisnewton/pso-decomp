#include "pso/system/vector.h"
#include "types.h"
#include "pso/boss/TBoss8Dragon_802F3AB4.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TUnk_804E4BF0.h"
#include "pso/boss/TObjBoss2Tunnel.h"

struct Stack_802F3A48 {
    s32 sp8;
    u8 trailing_storage[0x3C];
};

struct Vec_802F376C { f32 x, y, z; };

struct Ent_802F376C { u8 pad[0x38]; f32 x; f32 y; f32 z; };

struct Vec_802F3878 { f32 x, y, z; };

struct Ent_802F3878 { u8 pad[0x38]; f32 x; f32 y; f32 z; };

struct Vec_802F3974 { f32 x, y, z; };

struct Ent_802F3974 { u8 pad[0x38]; f32 x; f32 y; f32 z; };

extern "C" {
extern s32 tl_04;
u16 get_entity_id(void *);
u8 *get_enemy_entity(u16 arg0);
static const f32 lbl_805DED48 = 0.0f;
static const f32 lbl_805DED4C = 120.0f;

s32 TBoss8Dragon::is_closest_part() {
    Vec_802F376C v;
    f32 len;
    s32 i;
    if (boss8_dragon_leader_part == NULL) {
        return 1;
    }
    v.x = ((Ent_802F376C *)this)->x - ((Ent_802F376C *)this)->x;
    v.y = lbl_805DED48;
    v.z = ((Ent_802F376C *)this)->z - ((Ent_802F376C *)this)->z;
    len = normalize_vector_xz((Vec *)(&v));
    for (i = 1; i < 6; i++) {
        u16 id = boss8_dragon_leader_part->get_part_entity_id(i);
        if (id != get_entity_id(this)) {
            Ent_802F376C *e = (Ent_802F376C *)get_enemy_entity(id);
            if (e != NULL) {
                v.x = e->x - ((Ent_802F376C *)this)->x;
                v.y = lbl_805DED48;
                v.z = e->z - ((Ent_802F376C *)this)->z;
                if (!(normalize_vector_xz((Vec *)(&v)) >= len)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

#pragma push
#pragma fp_contract on
s32 TBoss8Dragon::push_apart_from_parts() {
    Vec_802F3878 v;
    f32 d;
    s32 i;
    if (boss8_dragon_leader_part == NULL) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        u16 id = boss8_dragon_leader_part->get_part_entity_id(i);
        if (id != get_entity_id(this)) {
            Ent_802F3878 *e = ((Ent_802F3878 *)get_enemy_entity(id));
            if (e != NULL) {
                v.x = e->x - ((Ent_802F3878 *)this)->x;
                v.y = lbl_805DED48;
                v.z = e->z - ((Ent_802F3878 *)this)->z;
                d = normalize_vector_xz((Vec *)(&v)) - lbl_805DED4C;
                if (!(d >= lbl_805DED48)) {
                    ((Ent_802F3878 *)this)->x = v.x * d + ((Ent_802F3878 *)this)->x;
                    ((Ent_802F3878 *)this)->z = v.z * d + ((Ent_802F3878 *)this)->z;
                    return 1;
                }
            }
        }
    }
    return 0;
}
#pragma pop

s32 TBoss8Dragon::is_near_other_part() {
    Vec_802F3974 v;
    s32 i;
    if (boss8_dragon_leader_part == NULL) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        u16 id = boss8_dragon_leader_part->get_part_entity_id(i);
        if (id != get_entity_id(this)) {
            Ent_802F3974 *e = ((Ent_802F3974 *)get_enemy_entity(id));
            if (e != NULL) {
                v.x = e->x - ((Ent_802F3974 *)this)->x;
                v.y = lbl_805DED48;
                v.z = e->z - ((Ent_802F3974 *)this)->z;
                if (!(normalize_vector_xz((Vec *)(&v)) >= lbl_805DED4C)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void *TUnk_804E4BF0::spawn_attack_object(Vec *pos, s32 angle, s32 hp, s32 part) {
    Stack_802F3A48 stack;
    if (this->setup_attack_slot(pos, angle, part, (u8 *)&stack.sp8) != 0) {
        return new TUnk_804F1A78((TObject *)tl_04, &stack.sp8, hp);
    }
    return NULL;
}

}
