#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/misc/TLobby.h"
#include "pso/network/client_id.h"
#include <stdlib.h>
#include "pso/system/BmlResource.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/system/ModelDrawContext.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/object/TObjFish_8001ED90.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/TMainTask.h"
#include "pso/TObject.h"
#include "pso/math/MatrixVector.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/render/render_util.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/misc/TCameraCtrl.h"

#include "pso/system/vector.h"
#include "pso/TLevelSelect.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TOKey.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/npc/TObjNpcEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/object/TObjFish.h"
#include "pso/misc/TOKeyJungleMain.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/TLobbyEventTheme.h"

extern "C" {
extern BmlResource *TObjFish__area_bml_resource;
extern s32 TObjFish__area_event_stage;
extern void* __vt__8TObjFish[];

s32 TObjFish::update_state() {
    if ((s32) TObjFish__area_event_stage == 0) {
        switch (*(s16 *)((s8 *)this + 0x90)) {
        case 0:
            if (is_lobby_event_active() == 0) {
                *(s16 *)((s8 *)this + 0x90) = 2;
                this->m_92 = 0x28;
            }
            goto Lend;
        case 2:
            this->m_92 = (this->m_92 - 1);
            if (this->m_92 <= 0) {
                *(s16 *)((s8 *)this + 0x90) = 3;
            }
            goto Lend;
        case 3:
        default:
            if (is_lobby_event_active() != 0) {
                *(s16 *)((s8 *)this + 0x90) = 0;
            }
        }
Lend:
        return (u8) (*(s16 *)((s8 *)this + 0x90) == 3);
    }
    return 1U;
}

#pragma push
extern const char lbl_80465A48[] = "lobby_suisou_sakana01_yellow.gj";
extern const char lbl_80465A68[] = "lobby_suisou_sakana02_red.gj";
extern const char lbl_80465A88[] = "lobby_suisou_sakana03_bule.gj";
extern const char lbl_80465AA8[] = "lobby_suisou_sakana01_yellow.njm";
extern const char lbl_80465ACC[] = "lobby_suisou_sakana02_red.njm";
extern const char lbl_80465AEC[] = "lobby_suisou_sakana03_bule.njm";
extern const char lbl_80465B0C[] = "bm_sakana_obj_lobby.bml";
extern const char lbl_80465B24[] = "sakana_jungle21.gj";
extern const char lbl_80465B38[] = "sakana_jungle22.gj";
extern const char lbl_80465B4C[] = "sakana_jungle23.gj";
extern const char lbl_80465B60[] = "sakana_jungle21.njm";
extern const char lbl_80465B74[] = "sakana_jungle22.njm";
extern const char lbl_80465B88[] = "sakana_jungle23.njm";
extern const char lbl_80465B9C[] = "bm_sakana_obj_jungle2.bml";
extern const char lbl_80465BB8[] = "sakana_jungle51.gj";
extern const char lbl_80465BCC[] = "sakana_jungle52.gj";
extern const char lbl_80465BE0[] = "sakana_jungle53.gj";
extern const char lbl_80465BF4[] = "sakana_jungle51.njm";
extern const char lbl_80465C08[] = "sakana_jungle52.njm";
extern const char lbl_80465C1C[] = "sakana_jungle53.njm";
extern const char lbl_80465C30[] = "bm_sakana_obj_jungle5.bml";
extern const char lbl_80465C4C[] = "sakana01_obj1.gj";
extern const char lbl_80465C60[] = "sakana02_obj1.gj";
extern const char lbl_80465C74[] = "sakana03_obj1.gj";
extern const char lbl_80465C88[] = "sakana01_obj1.njm";
extern const char lbl_80465C9C[] = "sakana02_obj1.njm";
extern const char lbl_80465CB0[] = "sakana03_obj1.njm";
extern const char lbl_80465CC4[] = "bm_sakana_obj_seabed1.bml";
extern const char lbl_80465CE0[] = "sakana04_obj1.gj";
extern const char lbl_80465CF4[] = "sakana05_obj1.gj";
extern const char lbl_80465D08[] = "sakana06_obj1.gj";
extern const char lbl_80465D1C[] = "sakana04_obj1.njm";
extern const char lbl_80465D30[] = "sakana05_obj1.njm";
extern const char lbl_80465D44[] = "sakana06_obj1.njm";
extern const char lbl_80465D58[] = "bm_sakana_obj_seabed2.bml";

extern const f32 lbl_80465D74[5][3] = { { 1.0f, 1.0f, 1.0f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.4f, 0.4f, 0.4f }, { 0.0f, 0.0f, 0.0f } };
extern const f32 lbl_80465DB0[5][3] = { { 30.0f, 30.0f, 30.0f }, { 5.0f, 20.0f, 30.0f }, { 5.0f, 5.0f, 5.0f }, { 30.0f, 30.0f, 30.0f }, { 30.0f, 30.0f, 30.0f } };
extern const char lbl_80465DEC[] = "TObjFish";
#pragma pop
}

struct SVec_8029D5C8 { s16 x, y, z; };
struct Fish_8029D5C8 {
    f32 x, y, z;
    f32 tx, ty, tz;
    u8 pad18[0xC];
    s32 ang;
    f32 frame;
    s16 rot;
    u8 pad2e[2];
    s16 kind;
    u8 pad32[2];
    s32 seen;
    u8 pad38[0xC];
};

extern "C" {

extern TCameraCtrl *camera_ctrl_instance;

#pragma push
#pragma fp_contract on
#pragma dont_inline off
#pragma inline_depth(4)
inline void wrap_8029D5C8(s16 *p) {
    if (*p > 0) {
        *p -= 0x4000;
    } else {
        *p += 0x4000;
    }
}

#define F(T, o) (*(T *)(arg0 + (o)))
void render__8TObjFishFv(u8 *arg0) {
    Fish_8029D5C8 *f;
    s32 n;
    struct { f32 x, y, z; } d;

    if (TMainTask::get_render_pass() != 1 &&
        ((TObjFish *)arg0)->update_object_view_visibility(400.0f, 200.0f) != 0 &&
        F(Fish_8029D5C8 *, 0xA0) != NULL && ((TObjFish *)arg0)->update_state() != 0) {
        f = F(Fish_8029D5C8 *, 0xA0);
        n = F(s32, 0x94);
        push_matrix();
        translate_matrix_vec3(0, arg0 + 0x38);
        rotate_matrix_y(0, F(s32, 0x60));
        if (camera_ctrl_instance != NULL) {
            d.x = camera_ctrl_instance->position.x - F(f32, 0x38);
            d.y = camera_ctrl_instance->position.y - F(f32, 0x3C);
            d.z = camera_ctrl_instance->position.z - F(f32, 0x40);
        }
        while (n-- != 0) {
            s16 a;
            s16 *pa;
            f32 r;
            pa = &a;
            *pa = (s16)f->ang - f->rot;
            if (*pa > 0) {
                *pa -= 0x4000;
            } else {
                *pa += 0x4000;
            }
            r = 0.2f * a;
            {
                struct { f32 x, y, z; } e, t;
                e.x = d.x - f->x;
                e.y = d.y - f->y;
                e.z = d.z - f->z;
                t.x = f->tx - f->x;
                t.y = f->ty - f->y;
                t.z = f->tz - f->z;
                if (f->seen == 0 || e.x * e.x + e.y * e.y + e.z * e.z < t.x * t.x + t.y * t.y + t.z * t.z) {
                    f->seen = 1;
                    f->tx = d.x;
                    f->ty = d.y;
                    f->tz = d.z;
                }
            }
            push_matrix();
            post_translate_matrix(&f->x);
            rotate_matrix_y(0, f->rot + (s32)r);
            set_draw_list_mask(3);
            if (get_current_floor_area() == AREA_SEABED_UPPER) {
                switch (f->kind) {
                case 1:
                    set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 1)));
                    draw_ginja_object((void *)get_bml_model(TObjFish__area_bml_resource, 1));
                    break;
                case 2:
                    set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 2)));
                    draw_ginja_object((void *)get_bml_model(TObjFish__area_bml_resource, 2));
                    break;
                default:
                    set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 0)));
                    draw_ginja_object((void *)get_bml_model(TObjFish__area_bml_resource, 0));
                    break;
                }
            } else {
                set_motion_packed_rotation();
                switch (f->kind) {
                case 1:
                    set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 1)));
                    draw_ginja_model_with_motion((void *)get_bml_model(TObjFish__area_bml_resource, 1), get_bml_motion(TObjFish__area_bml_resource, 1), f->frame);
                    break;
                case 2:
                    set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 2)));
                    draw_ginja_model_with_motion((void *)get_bml_model(TObjFish__area_bml_resource, 2), get_bml_motion(TObjFish__area_bml_resource, 2), f->frame);
                    break;
                default:
                    set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 0)));
                    draw_ginja_model_with_motion((void *)get_bml_model(TObjFish__area_bml_resource, 0), get_bml_motion(TObjFish__area_bml_resource, 0), f->frame);
                    break;
                }
                clear_motion_packed_rotation();
            }
            restore_draw_list_mask();
            pop_matrix();
            f++;
        }
        pop_matrix();
    }
}
#undef F

void TObjFish::run_task() {
    TObjFishEntry *f;
    s32 n;
    s32 k;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 best;
    s16 m;

    if (m_a0 == NULL) {
        return;
    }
    n = m_94;
    f = m_a0;
    while (n-- != 0) {
        k = m_98 + n;
        if (--f->timer <= 0) {
            f->timer = 0;
        }
        f->pos.x += f->velocity.x;
        f->pos.y += f->velocity.y;
        f->pos.z += f->velocity.z;
        if (fabs_float(f->pos.x) >= scale.x) {
            f->pos.x -= f->velocity.x;
            f->velocity.x = -f->velocity.x;
        }
        if (fabs_float(f->pos.y) >= scale.y) {
            f->pos.y -= f->velocity.y;
            f->velocity.y = -f->velocity.y;
        }
        if (fabs_float(f->pos.z) >= scale.z) {
            f->pos.z -= f->velocity.z;
            f->velocity.z = -f->velocity.z;
        }
        f->velocity.y = 0.85f * (1e-05f + f->velocity.y);
        f->velocity.x *= 0.98f;
        f->velocity.z *= 0.98f;
        if (f->mode == 1) {
            f32 ex;
            f32 ez;
            f32 ey;
            ex = f->target.x - f->pos.x;
            ey = f->target.y - f->pos.y;
            ez = f->target.z - f->pos.z;
            if (ex * ex + ey * ey + ez * ez < 10000.0f) {
                f->mode = 0;
            } else if (k & 7) {
                k >>= 3;
            } else {
                f++;
                continue;
            }
        }
        if ((k & 7) == 0 && f->timer == 0) {
            TObjCollidable *pl;
            TLobby::get_game_mode();
            pl = find_entity_by_id(local_client_id);
            best = 900.0f;
            if (pl != NULL) {
                f32 d;
                dx = (pl->position.x - position.x) - f->pos.x;
                dy = (pl->position.y - position.y) - f->pos.y;
                dz = (pl->position.z - position.z) - f->pos.z;
                d = dx * dx + dy * dy + dz * dz;
                if (best > d) {
                    best = d;
                }
            }
            if (best < 900.0f) {
                f32 s;
                f->timer = 0.5f * (200.0f * ((1.0f / 32768.0f) * (f32)rand()));
                s = 0.9f / newton_sqrtf(best);
                dx *= s;
                dy *= s;
                dz *= s;
                f->velocity.x = -dx;
                f->velocity.y = -dy;
                f->velocity.z = -dz;
            } else {
                f32 a = f->velocity.x * f->velocity.x;
                f32 b = f->velocity.y * f->velocity.y;
                f32 c = f->velocity.z * f->velocity.z;
                if (c + (a + b) <= 0.0009f) {
                    f->timer = 200.0f * ((1.0f / 32768.0f) * (f32)rand());
                    f->velocity.x += 0.9f * (2.0f * ((1.0f / 32768.0f) * (f32)rand() - 0.5f));
                    f->velocity.y += 0.9f * (2.0f * ((1.0f / 32768.0f) * (f32)rand() - 0.5f));
                    f->velocity.z += 0.9f * (2.0f * ((1.0f / 32768.0f) * (f32)rand() - 0.5f));
                } else {
                    dx = f->pos.x - f->target.x;
                    dy = f->pos.y - f->target.y;
                    dz = f->pos.z - f->target.z;
                    if (dx * dx + dy * dy + dz * dz > 10000.0f) {
                        f->mode = 1;
                    }
                }
            }
            if ((1.0f / 32768.0f) * (f32)rand() < 6.6666665f) {
                f->velocity.x += 0.02f * (2.0f * ((1.0f / 32768.0f) * (f32)rand() - 0.5f));
                f->velocity.y += 0.02f * ((1.0f / 32768.0f) * (f32)rand() - 0.5f);
                f->velocity.z += 0.02f * (2.0f * ((1.0f / 32768.0f) * (f32)rand() - 0.5f));
            }
        }
        if (fabs_float(f->velocity.z) > 0.0f && (k & 3) == 0) {
            f->target_angle = 10430.38043493439 * atan2_float(f->velocity.x, f->velocity.z);
        }
        f32 turn = (s16)(f->target_angle - f->angle);
        turn *= 0.12f;
        f->angle += (s32)turn;
        if ((k & 3) == 0) {
            turn = (s16)((s16)((s32)(10430.38043493439 * atan2_float(f->target.x - f->pos.x, f->target.z - f->pos.z)) - rotation.yaw) - f->yaw);
            turn *= 0.8f;
            f->yaw += (s32)turn;
        }
        m = f->anim;
        if (m < 0 || m > 2) {
            f->frame += lbl_80465D74[TObjFish__area_event_stage][0];
            if (f->frame >= lbl_80465DB0[TObjFish__area_event_stage][0]) {
                f->frame -= lbl_80465DB0[TObjFish__area_event_stage][0];
            }
        } else {
            f->frame += lbl_80465D74[TObjFish__area_event_stage][m];
            if (f->frame >= lbl_80465DB0[TObjFish__area_event_stage][f->anim]) {
                f->frame -= lbl_80465DB0[TObjFish__area_event_stage][f->anim];
            }
        }
        f->seen = 0;
        f++;
    }
    m_98++;
}
#pragma pop

}

struct Vec_8029E170 { f32 x, y, z; };
struct Ent_8029E170 {
    Vec_8029E170 pos;
    Vec_8029E170 v0c;
    Vec_8029E170 v18;
    s32 f24;
    f32 f28;
    s16 f2c;
    s16 f2e;
    s16 f30;
    s16 f32;
    s32 f34;
    s32 f38;
    u8 pad3c[8];
};

extern "C" {

int rand(void);

#pragma push
#pragma fp_contract on
s32 TObjFish::init_fish_school(void *arg1_arg, s32 arg2, s32 arg3) {
    Vec_8029E170 *arg1 = (Vec_8029E170 *)arg1_arg;
    Ent_8029E170 *p;
    s32 i;

    if (TObjFish__area_event_stage == 0 && is_lobby_event_active() != 0) {
        *(s16 *)((s8 *)((u8 *)this) + 0x90) = 0;
    } else {
        *(s16 *)((s8 *)((u8 *)this) + 0x90) = 3;
    }
    this->m_92 = 0;
    if (*(s32 *)&this->m_94 < 1) {
        return 0;
    }
    *(Ent_8029E170 * *)&this->m_a0 = (Ent_8029E170 *) TQuestVmDownLoadServer::alloc(*(s32 *)&this->m_94 * 0x44);
    if (*(Ent_8029E170 * *)&this->m_a0 == NULL) {
        return 0;
    }
    p = *(Ent_8029E170 * *)&this->m_a0;
    for (i = 0; i < *(s32 *)&this->m_94; i++) {
        p->pos.x = 2.0f * (arg1->x * ((1.0f / 32768.0f) * (f32) rand() - 0.5f));
        p->pos.y = 2.0f * (arg1->y * ((1.0f / 32768.0f) * (f32) rand() - 0.5f));
        p->pos.z = 2.0f * (arg1->z * ((1.0f / 32768.0f) * (f32) rand() - 0.5f));
        p->v18.x = 0.0f;
        p->v18.y = 0.0f;
        p->v18.z = 0.0f;
        if (i < arg2) {
            p->f30 = 0;
        } else if (i < arg2 + arg3) {
            p->f30 = 1;
        } else {
            p->f30 = 2;
        }
        p->f32 = 200.0f * ((1.0f / 32768.0f) * (f32) rand());
        p->f24 = 0;
        p->f28 = (1.0f / 32768.0f) * (f32) rand();
        p->f2c = 0;
        p->f2e = 0;
        p->f38 = 0;
        p->f34 = 0;
        p->v0c.x = 0.0f;
        p->v0c.y = 0.0f;
        p->v0c.z = 0.0f;
        p++;
    }
    return 1;
}
#pragma pop

}

#include "pso/ui/TAdSinglePlyChrSelectGC.h"


extern "C" {
u8 *TObjFish__create(u8 *arg0);
TObjBase *__ct__8TObjBaseFP7TObject(TObjBase *self, TObject *parent);
extern s32 lbl_805D3D58;
u8 *TObjFish__ct(u8 *arg0, TObject *parent, u8 *arg2);
void *__dt__8TObjFishFv(void *arg0, s16 arg1);

void *__dt__8TObjFishFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = (s32 *)__vt__8TObjFish;
        if (*(void **)((s8 *)arg0 + 0xA0) != NULL) { TAdSinglePlyChrSelectGC::safe_free((u32)(*(void **)((s8 *)arg0 + 0xA0))); ((TObjFish *)arg0)->m_a0 = 0; }
        __dt__8TObjBaseFv(arg0, 0);
        if (arg1 > 0) {
            TObject::operator delete(arg0);
        }
    }
    return arg0;
}

u8 *TObjFish__ct(u8 *fish, TObject *parent, u8 *arg2) {
    f32 temp_f0;
    f32 var_f1;
    __ct__8TObjBaseFP7TObject((TObjBase *)fish, parent);
    *(s32 **)((s8 *)fish + 0x18) = (s32 *)__vt__8TObjFish;
    *(s32 *)((s8 *)fish + 0) = (s32) lbl_805D3D58;
    ((TObjFish *)fish)->m_a0 = 0;
    VecCopy((Vec *)(fish + 0x38), (const Vec *)(arg2 + 0xC));
    copy_xyz(fish + 0x5C, arg2 + 0x18);
    VecCopy((Vec *)(fish + 0x68), (const Vec *)(arg2 + 0x24));
    var_f1 = ((TObjFish *)fish)->scale.x;
    temp_f0 = ((TObjFish *)fish)->scale.y;
    if (var_f1 < temp_f0) {
        var_f1 = temp_f0;
    }
    if (var_f1 < temp_f0) {
        var_f1 = temp_f0;
    }
    *(f32 *)((s8 *)fish + 0x9C) = var_f1;
    ((TObjFish *)fish)->m_94 = *(s32 *)((s8 *)arg2 + 0x30) + *(s32 *)((s8 *)arg2 + 0x34) + *(s32 *)((s8 *)arg2 + 0x38);
    ((TObjFish *)fish)->m_98 = 0;
    if ((s32) ((TObjFish *)fish)->m_94 < 1) {
        ((TObjFish *)fish)->m_94 = 1;
    }
    if (((TObjFish *)fish)->init_fish_school(fish + 0x68, (int) (*(s32 *)((s8 *)arg2 + 0x30)), (int) (*(s32 *)((s8 *)arg2 + 0x34))) == 0) {
        ((TObjFish *)fish)->queue_destruction();
    }
    return fish;
}

u8 *TObjFish__create(u8 *arg0) {
    u8 *fish;
    u8 *var_r0;
    if (is_split_screen() != 0) {
        return NULL;
    }
    fish = (u8 *)TObject::operator new(sizeof(TObjFish));
    var_r0 = fish;
    if (var_r0 != NULL) {
        var_r0 = (u8 *)(TObjFish__ct(fish, tl_05, arg0));
    }
    return var_r0;
}

void TObjFish::free_resource() {
    if (TObjFish__area_bml_resource != NULL) {
        delete TObjFish__area_bml_resource;
        TObjFish__area_bml_resource = NULL;
    }
}
void vfunc_6__8TObjBaseFPsl();
void get_name__8TObjBaseFv();
void get_center__8TObjBaseFv();
void apply_object_set_data__8TObjBaseFPv();
void classify_actor_view_detail__8TObjBaseFfff();
void render_shadows__7TObjectFv();
void reset_motion_fields__8TObjBaseFv();
void run_task__8TObjFishFv();
void update_object_view_visibility__8TObjBaseFff();
// Each area owns terminated model/motion name lists and a shared BML descriptor.
struct TObjFishAreaResource {
    const char *models[4];
    const char *motions[4];
    BmlResourceDescriptor descriptor;
};
typedef char TObjFishAreaResource_size[sizeof(TObjFishAreaResource) == 0x30 ? 1 : -1];
typedef char TObjFishAreaResource_descriptor_offset[offsetof(TObjFishAreaResource, descriptor) == 0x20 ? 1 : -1];

TObjFishAreaResource fish_resource_name_table[5] = {
    { { lbl_80465A48, lbl_80465A68, lbl_80465A88, NULL },
      { lbl_80465AA8, lbl_80465ACC, lbl_80465AEC, NULL },
      { lbl_80465B0C, fish_resource_name_table[0].models, fish_resource_name_table[0].motions, 3, 3 } },
    { { lbl_80465B24, lbl_80465B38, lbl_80465B4C, NULL },
      { lbl_80465B60, lbl_80465B74, lbl_80465B88, NULL },
      { lbl_80465B9C, fish_resource_name_table[1].models, fish_resource_name_table[1].motions, 3, 3 } },
    { { lbl_80465BB8, lbl_80465BCC, lbl_80465BE0, NULL },
      { lbl_80465BF4, lbl_80465C08, lbl_80465C1C, NULL },
      { lbl_80465C30, fish_resource_name_table[2].models, fish_resource_name_table[2].motions, 3, 3 } },
    { { lbl_80465C4C, lbl_80465C60, lbl_80465C74, NULL },
      { lbl_80465C88, lbl_80465C9C, lbl_80465CB0, NULL },
      { lbl_80465CC4, fish_resource_name_table[3].models, fish_resource_name_table[3].motions, 3, 3 } },
    { { lbl_80465CE0, lbl_80465CF4, lbl_80465D08, NULL },
      { lbl_80465D1C, lbl_80465D30, lbl_80465D44, NULL },
      { lbl_80465D58, fish_resource_name_table[4].models, fish_resource_name_table[4].motions, 3, 3 } },
};
void *__vt__8TObjFish[13] = {
    0,
    0,
    (void *)__dt__8TObjFishFv,
    (void *)run_task__8TObjFishFv,
    (void *)render__8TObjFishFv,
    (void *)render_shadows__7TObjectFv,
    (void *)vfunc_6__8TObjBaseFPsl,
    (void *)apply_object_set_data__8TObjBaseFPv,
    (void *)reset_motion_fields__8TObjBaseFv,
    (void *)get_center__8TObjBaseFv,
    (void *)update_object_view_visibility__8TObjBaseFff,
    (void *)classify_actor_view_detail__8TObjBaseFfff,
    (void *)get_name__8TObjBaseFv,
};

void TObjFish::load_area_resource() {
    TObjFishAreaResource *base = fish_resource_name_table;
    BmlResource *p;
    switch (get_current_floor_area()) {
    case AREA_JUNGLE_NORTH:
        TObjFish__area_event_stage = 1;
        p = new BmlResource(1, &base[1].descriptor, 0, 0, (void *)(0));
        TObjFish__area_bml_resource = p;
        break;
    case AREA_SEASIDE:
    case AREA_SEASIDE_NIGHT:
        TObjFish__area_event_stage = 2;
        p = new BmlResource(1, &base[2].descriptor, 0, 0, (void *)(0));
        TObjFish__area_bml_resource = p;
        break;
    case AREA_SEABED_UPPER:
        TObjFish__area_event_stage = 3;
        p = new BmlResource(1, &base[3].descriptor, 0, 0, (void *)(0));
        TObjFish__area_bml_resource = p;
        break;
    case AREA_SEABED_LOWER:
        TObjFish__area_event_stage = 4;
        p = new BmlResource(1, &base[4].descriptor, 0, 0, (void *)(0));
        TObjFish__area_bml_resource = p;
        break;
    case AREA_LOBBY:
    default:
        TObjFish__area_event_stage = 0;
        p = new BmlResource(1, &base[0].descriptor, 0, 0, (void *)(0));
        TObjFish__area_bml_resource = p;
        break;
    }
}

}
