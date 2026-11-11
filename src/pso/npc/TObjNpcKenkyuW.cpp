#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/misc/TNeedleShoot.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/object/TObjMotion.h"
#include "pso/unk/text_8014B8A4.h"
#include "pso/npc/TObjNpcKenkyuW.h"
#include "pso/system/vector.h"
#include "pso/player/TObjPlayer.h"
#include "pso/npc/TUnk_804A9F50.h"

struct RecoveredGlobal_802A3C30_lbl_804DCE48 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_802A3C30_lbl_804DCE48_size[sizeof(RecoveredGlobal_802A3C30_lbl_804DCE48) == 0x10 ? 1 : -1];

struct RecoveredGlobal_802A3CD8___vt__14TObjNpcKenkyuW {
    s32 value;
    u8 remaining[0x174];
};

#include "pso/technique/TechniqueContact.h"
#include "pso/misc/TLobby.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcLappy.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct Pl_802A3DE8 {
    u8 pad0[0x30];
    u32 flags;
};

extern "C" {
extern RecoveredGlobal_802A3C30_lbl_804DCE48 bm_npc_kenkyu_w_resource_descriptor;
extern u32 TObjNpcKenkyuW__model_resource;
s32 TObjFish__sub_8001EDB0(int, int);
extern s32 __vt__14TObjNpcKenkyuW[];
extern s32 TObjNpcKenkyuW__name;
s32 obj_is_hit_receivable(void *);
extern TechniqueContactList technique_contact_list;
void vector_length(void *);
int get_player_data__10TObjPlayerFi(int a0);
s32 get_entity_id(void *);
extern const f32 lbl_805DDF60;
extern const f32 lbl_805DDF64;

void *find_entity_by_id(u16 id);

void __dl__7TObjectFPv(void *);

void TObjNpcKenkyuW::destroy_instance() {
    if ((u32) TObjNpcKenkyuW__model_resource != 0U) {
        delete (BmlResource *)((void*)TObjNpcKenkyuW__model_resource);
        TObjNpcKenkyuW__model_resource = 0U;
    }
}

void TObjNpcKenkyuW::load_resource_instance() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&bm_npc_kenkyu_w_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&TObjNpcKenkyuW__model_resource) = var_r0;
}

void *__dt__14TObjNpcKenkyuWFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__14TObjNpcKenkyuW;
        ((TUnk_804A9F50 *)arg0)->destroy_npc_lappy_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}
typedef char RecoveredGlobal_802A3CD8___vt__14TObjNpcKenkyuW_size[sizeof(RecoveredGlobal_802A3CD8___vt__14TObjNpcKenkyuW) == 0x178 ? 1 : -1];
u8 *TObjNpcKenkyuW__ct(u8 *player, s32 arg1, s32 arg2) {
    construct_male_npc_base((player));
    *(s32 **)((s8 *)player + 0x18) = &(*(RecoveredGlobal_802A3CD8___vt__14TObjNpcKenkyuW *)&__vt__14TObjNpcKenkyuW).value;
    *(s32 *)((s8 *)player + 0) = (s32) TObjNpcKenkyuW__name;
    ((TObjNpcKenkyuW *)(player))->apply_set_data((void *)arg2);
    ((TObjChara *)player)->initialize_position_copies();
    *(s32 *)((s8 *)player + 0x34) = (s32)get_bml_model((BmlResource *)((*(s32 *)&TObjNpcKenkyuW__model_resource)), 0);
    ((TObjNpcKenkyuW *)player)->texlist = TObjFish__sub_8001EDB0((int) ((*(s32 *)&TObjNpcKenkyuW__model_resource)), 0);
    ((TObjNpcBase *)player)->setup_common();
    return player;
}

void TNeedleShoot::clear_technique_contacts() {
    for (s32 i=0;i<16;++i) {
        technique_contact_list.actors[i]=0;
        technique_contact_list.bodies[i]=0;
    }
    technique_contact_list.count=0;
}

s32 TNeedleShoot::is_hit_receivable_target(TechniqueContactActor *arg1) {
    if (arg1 == NULL) {
        return 0;
    }
    if (obj_is_hit_receivable(arg1) != 0) {
        return 1;
    }
    return 0;
}
#define L_802A3DE8 technique_contact_list
TechniqueContactList *TNeedleShoot::fn_802A3DE8(void *src) {
    Vec a;
    Vec d;
    Vec *sd;
    Pl_802A3DE8 *p;
    s32 i;
    TechniqueContactBody *r;
    VecCopy((Vec *)&a, (const Vec *)&m_6c);
    clear_technique_contacts();
    if (((u8 *)m_68) == 0) return &L_802A3DE8;
    sd = (Vec *)get_shoot_data();
    d.x = a.x - sd->x;
    d.y = a.y - sd->y;
    d.z = a.z - sd->z;
    vector_length(&d);
    a.x = lbl_805DDF60 * (a.x + sd->x);
    a.y = lbl_805DDF60 * (a.y + sd->y);
    a.z = lbl_805DDF60 * (a.z + sd->z);
    VecCopy((Vec *)(((u8 *)m_68) + 0x38), (const Vec *)&a);
    copy_xyz(((u8 *)m_68) + 0x5C, &m_a0);
    for (i = 0; i < TLobby::get_lobby_flag(); i++) {
        p = (Pl_802A3DE8 *)get_player_data__10TObjPlayerFi(i);
        if (p == 0) continue;
        if ((p->flags & 0x20000000) || (p->flags & 0x10000000)) {
            if ((u16)get_entity_id(p) == (u16)get_entity_id(src)) continue;
            r = (TechniqueContactBody *)((TObjCollidable *)((u8 *)((u8 *)m_68)))->find_actor_body_contact((u8 *)p, (f32)lbl_805DDF64);
            if (r == 0) continue;
            L_802A3DE8.bodies[L_802A3DE8.count] = r;
            L_802A3DE8.actors[L_802A3DE8.count] = (TechniqueContactActor *)p;
            if (++L_802A3DE8.count >= 0x10) {
                L_802A3DE8.count = 0xF;
                break;
            }
        } else if ((p->flags & 0x40000000) && !(p->flags & 0x80000000)) {
            if (((TObjCollidable *)((u8 *)((u8 *)m_68)))->find_actor_body_contact((u8 *)p, (f32)lbl_805DDF64) != 0) return 0;
        }
    }
    return &L_802A3DE8;
}
#define L_802A41CC technique_contact_list

#define L_802A3FDC technique_contact_list
TechniqueContactList *TNeedleShoot::fn_802A3FDC(void *src) {
    Vec a;
    Vec d;
    s32 i;
    Vec *sd;
    u32 id;
    Pl_802A3DE8 *p;
    TechniqueContactBody *r;
    VecCopy((Vec *)&a, (const Vec *)&m_6c);
    clear_technique_contacts();
    if (((u8 *)m_68) == 0) return &L_802A3FDC;
    sd = ((Vec *)get_shoot_data());
    d.x = a.x - sd->x;
    d.y = a.y - sd->y;
    d.z = a.z - sd->z;
    vector_length(&d);
    a.x = lbl_805DDF60 * (a.x + sd->x);
    a.y = lbl_805DDF60 * (a.y + sd->y);
    a.z = lbl_805DDF60 * (a.z + sd->z);
    VecCopy((Vec *)(((u8 *)m_68) + 0x38), (const Vec *)&a);
    copy_xyz(((u8 *)m_68) + 0x5C, &m_a0);
    for (i = TLobby::get_game_mode(); i < TLobby::get_lobby_flag(); i++) {
        p = ((Pl_802A3DE8 *)get_player_data__10TObjPlayerFi(i));
        if (p == 0) continue;
        if (p->flags & 0x20000000) {
            if ((u16)get_entity_id(p) != (u16)get_entity_id(src)) {
                r = (TechniqueContactBody *)((TObjCollidable *)((u8 *)((u8 *)m_68)))->find_actor_body_contact((u8 *)p, (f32)lbl_805DDF64);
                if (r != 0) {
                    L_802A3FDC.bodies[L_802A3FDC.count] = r;
                    L_802A3FDC.actors[L_802A3FDC.count] = (TechniqueContactActor *)p;
                    if (++L_802A3FDC.count >= 0x10) {
                        L_802A3FDC.count = 0xF;
                        break;
                    }
                }
            }
        } else if ((p->flags & 0x40000000) && !(p->flags & 0x80000000)) {
            if (((TObjCollidable *)((u8 *)((u8 *)m_68)))->find_actor_body_contact((u8 *)p, (f32)lbl_805DDF64) != 0) return 0;
        }
    }
    return &L_802A3FDC;
}

TechniqueContactList *TNeedleShoot::collect_technique_contacts(void *src) {
    Vec a;
    Vec d;
    Vec *sd;
    Pl_802A3DE8 *p;
    s32 i;
    s32 n;
    TechniqueContactBody *r;
    VecCopy((Vec *)&a, (const Vec *)&m_6c);
    clear_technique_contacts();
    if (((u8 *)m_68) == 0) return &L_802A41CC;
    sd = (Vec *)get_shoot_data();
    d.x = a.x - sd->x;
    d.y = a.y - sd->y;
    d.z = a.z - sd->z;
    vector_length(&d);
    a.x = lbl_805DDF60 * (a.x + sd->x);
    a.y = lbl_805DDF60 * (a.y + sd->y);
    a.z = lbl_805DDF60 * (a.z + sd->z);
    VecCopy((Vec *)(((u8 *)m_68) + 0x38), (const Vec *)&a);
    copy_xyz(((u8 *)m_68) + 0x5C, &m_a0);
    if ((u16)get_entity_id(src) < 4) {
        n = TLobby::get_lobby_flag();
        for (i = 0; i < n; i++) {
            p = (Pl_802A3DE8 *)get_player_data__10TObjPlayerFi(i);
            if (p == 0) continue;
            if ((u16)get_entity_id(p) == (u16)get_entity_id(src)) continue;
            r = (TechniqueContactBody *)((TObjCollidable *)(((u8 *)m_68)))->find_actor_body_contact((u8 *)p, (f32)lbl_805DDF64);
            if (r == 0) continue;
            if ((p->flags & 0x20000000) || (p->flags & 0x10000000)) {
                L_802A41CC.bodies[L_802A41CC.count] = r;
                L_802A41CC.actors[L_802A41CC.count] = (TechniqueContactActor *)p;
                if (++L_802A41CC.count >= 0x10) {
                    L_802A41CC.count = 0xF;
                    break;
                }
            }
        }
    } else {
        s32 j;
        for (j = 0; j < 4; j++) {
            p = (Pl_802A3DE8 *)find_entity_by_id(j);
            if (p == 0) continue;
            if ((u16)get_entity_id(p) == (u16)get_entity_id(src)) continue;
            r = (TechniqueContactBody *)((TObjCollidable *)(((u8 *)m_68)))->find_actor_body_contact((u8 *)p, (f32)lbl_805DDF64);
            if (r == 0) continue;
            if (p->flags & 0x10000000) {
                L_802A41CC.bodies[L_802A41CC.count] = r;
                L_802A41CC.actors[L_802A41CC.count] = (TechniqueContactActor *)p;
                if (++L_802A41CC.count >= 0x10) {
                    L_802A41CC.count = 0xF;
                    break;
                }
            }
        }
    }
    return &L_802A41CC;
}


// The callers are TNeedleShoot subclasses. The unused argument remains part
// of their existing call interface; contact mode is stored in m_b0.
void TNeedleShoot::check_actor_contacts(s32 ignored) {
    TechniqueContactList *contacts;
    if (m_68 == 0) {
        TObject::queue_destruction();
        return;
    }
    switch (m_b0) {
    case 1:
        contacts = collect_technique_contacts((void *)m_1c);
        break;
    case 2:
        contacts = fn_802A3FDC((void *)m_1c);
        break;
    default:
        contacts = fn_802A3DE8((void *)m_1c);
        break;
    }
    if (contacts == NULL) {
        vfunc_6();
    } else if (is_hit_receivable_target(contacts->actors[0])) {
        TechniqueContactActor *target = contacts->actors[0];
        if (target != NULL) {
            contact_body = contacts->bodies[0];
            vfunc_9(target);
        }
    }
}

}
