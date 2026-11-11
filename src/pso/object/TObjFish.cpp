#include "pso/system/BmlTextureList.h"
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
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/npc/TObjNpcEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/object/TObjFish.h"
#include "pso/misc/TOKeyJungleMain.h"
#include "pso/map/FloorArea.h"
#include "pso/misc/TLobbyEventTheme.h"

extern "C" {
BmlResource *TObjFish__area_bml_resource;
s32 TObjFish__area_event_stage;

s32 TObjFish::update_state() {
    if ((s32) TObjFish__area_event_stage == 0) {
        switch (m_90) {
        case 0:
            if (is_lobby_event_active() == 0) {
                m_90 = 2;
                this->m_92 = 0x28;
            }
            goto Lend;
        case 2:
            this->m_92 = (this->m_92 - 1);
            if (this->m_92 <= 0) {
                m_90 = 3;
            }
            goto Lend;
        case 3:
        default:
            if (is_lobby_event_active() != 0) {
                m_90 = 0;
            }
        }
Lend:
        return (u8) (m_90 == 3);
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
const char *TObjFish__class_name = lbl_80465DEC;
#pragma pop
}

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

void TObjFish::render() {
    TObjFishEntry *f;
    s32 n;
    struct { f32 x, y, z; } d;

    if (TMainTask::get_render_pass() != 1 &&
        update_object_view_visibility(400.0f, 200.0f) != 0 &&
        m_a0 != NULL && update_state() != 0) {
        f = m_a0;
        n = (s32)m_94;
        push_matrix();
        translate_matrix_vec3(0, (u8 *)&position);
        rotate_matrix_y(0, rotation.yaw);
        if (camera_ctrl_instance != NULL) {
            d.x = camera_ctrl_instance->position.x - position.x;
            d.y = camera_ctrl_instance->position.y - position.y;
            d.z = camera_ctrl_instance->position.z - position.z;
        }
        while (n-- != 0) {
            s16 a;
            s16 *pa;
            f32 r;
            pa = &a;
            *pa = (s16)f->yaw - f->angle;
            if (*pa > 0) {
                *pa -= 0x4000;
            } else {
                *pa += 0x4000;
            }
            r = 0.2f * a;
            {
                struct { f32 x, y, z; } e, t;
                e.x = d.x - f->pos.x;
                e.y = d.y - f->pos.y;
                e.z = d.z - f->pos.z;
                t.x = f->target.x - f->pos.x;
                t.y = f->target.y - f->pos.y;
                t.z = f->target.z - f->pos.z;
                if (f->seen == 0 || e.x * e.x + e.y * e.y + e.z * e.z < t.x * t.x + t.y * t.y + t.z * t.z) {
                    f->seen = 1;
                    f->target.x = d.x;
                    f->target.y = d.y;
                    f->target.z = d.z;
                }
            }
            push_matrix();
            post_translate_matrix(&f->pos.x);
            rotate_matrix_y(0, f->angle + (s32)r);
            set_draw_list_mask(3);
            if (get_current_floor_area() == AREA_SEABED_UPPER) {
                switch (f->anim) {
                case 1:
                    set_current_texture_list(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 1));
                    draw_ginja_object(get_bml_model(TObjFish__area_bml_resource, 1));
                    break;
                case 2:
                    set_current_texture_list(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 2));
                    draw_ginja_object(get_bml_model(TObjFish__area_bml_resource, 2));
                    break;
                default:
                    set_current_texture_list(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 0));
                    draw_ginja_object(get_bml_model(TObjFish__area_bml_resource, 0));
                    break;
                }
            } else {
                set_motion_packed_rotation();
                switch (f->anim) {
                case 1:
                    set_current_texture_list(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 1));
                    draw_ginja_model_with_motion(get_bml_model(TObjFish__area_bml_resource, 1), get_bml_motion(TObjFish__area_bml_resource, 1), f->frame);
                    break;
                case 2:
                    set_current_texture_list(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 2));
                    draw_ginja_model_with_motion(get_bml_model(TObjFish__area_bml_resource, 2), get_bml_motion(TObjFish__area_bml_resource, 2), f->frame);
                    break;
                default:
                    set_current_texture_list(TObjFish__sub_8001EDB0(TObjFish__area_bml_resource, 0));
                    draw_ginja_model_with_motion(get_bml_model(TObjFish__area_bml_resource, 0), get_bml_motion(TObjFish__area_bml_resource, 0), f->frame);
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

extern "C" {

int rand(void);

#pragma push
#pragma fp_contract on
s32 TObjFish::init_fish_school(void *arg1_arg, s32 arg2, s32 arg3) {
    Vec *arg1 = (Vec *)arg1_arg;
    TObjFishEntry *p;
    s32 i;

    if (TObjFish__area_event_stage == 0 && is_lobby_event_active() != 0) {
        m_90 = 0;
    } else {
        m_90 = 3;
    }
    this->m_92 = 0;
    if ((s32)m_94 < 1) {
        return 0;
    }
    m_a0 = (TObjFishEntry *)TQuestVmDownLoadServer::alloc((s32)m_94 * sizeof(TObjFishEntry));
    if (m_a0 == NULL) {
        return 0;
    }
    p = m_a0;
    for (i = 0; i < (s32)m_94; i++) {
        p->pos.x = 2.0f * (arg1->x * ((1.0f / 32768.0f) * (f32) rand() - 0.5f));
        p->pos.y = 2.0f * (arg1->y * ((1.0f / 32768.0f) * (f32) rand() - 0.5f));
        p->pos.z = 2.0f * (arg1->z * ((1.0f / 32768.0f) * (f32) rand() - 0.5f));
        p->velocity.x = 0.0f;
        p->velocity.y = 0.0f;
        p->velocity.z = 0.0f;
        if (i < arg2) {
            p->anim = 0;
        } else if (i < arg2 + arg3) {
            p->anim = 1;
        } else {
            p->anim = 2;
        }
        p->timer = 200.0f * ((1.0f / 32768.0f) * (f32) rand());
        p->yaw = 0;
        p->frame = (1.0f / 32768.0f) * (f32) rand();
        p->angle = 0;
        p->target_angle = 0;
        p->mode = 0;
        p->seen = 0;
        p->target.x = 0.0f;
        p->target.y = 0.0f;
        p->target.z = 0.0f;
        p++;
    }
    return 1;
}
#pragma pop

}

#include "pso/ui/TAdSinglePlyChrSelectGC.h"


extern "C" {
TObjFish::~TObjFish() {
    if (m_a0 != NULL) {
        TAdSinglePlyChrSelectGC::safe_free(m_a0);
        m_a0 = NULL;
    }
}

// The placement record passed by object factory 0x220. Only these fields
// are read by the fish constructor; the leading set metadata stays opaque.
struct TObjFishSetData {
    u8 metadata[0xC];
    Vec position;
    CameraAngles rotation;
    Vec scale;
    s32 counts[3];
};
typedef char TObjFishSetData_counts_offset[offsetof(TObjFishSetData, counts) == 0x30 ? 1 : -1];

TObjFish::TObjFish(TObject *parent, void *set_data) : TObjBase(parent) {
    TObjFishSetData *data = (TObjFishSetData *)set_data;
    f32 temp_f0;
    f32 var_f1;
    m_name = TObjFish__class_name;
    m_a0 = NULL;
    VecCopy(&position, &data->position);
    copy_xyz(&rotation, &data->rotation);
    VecCopy(&scale, &data->scale);
    var_f1 = scale.x;
    temp_f0 = scale.y;
    if (var_f1 < temp_f0) {
        var_f1 = temp_f0;
    }
    // The original compares scale.y twice here, rather than reading scale.z.
    if (var_f1 < temp_f0) {
        var_f1 = temp_f0;
    }
    m_9c = var_f1;
    m_94 = data->counts[0] + data->counts[1] + data->counts[2];
    m_98 = 0;
    if ((s32)m_94 < 1) {
        m_94 = 1;
    }
    if (init_fish_school(&scale, data->counts[0], data->counts[1]) == 0) {
        queue_destruction();
    }
}

void *TObjFish__create(void *set_data) {
    if (is_split_screen() != 0) {
        return NULL;
    }
    return new TObjFish(tl_05, set_data);
}

void TObjFish::free_resource() {
    if (TObjFish__area_bml_resource != NULL) {
        delete TObjFish__area_bml_resource;
        TObjFish__area_bml_resource = NULL;
    }
}
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
// Defer the final loader until the native vtable has been emitted.
#pragma push
#pragma defer_codegen on
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

// Keep this restoration at EOF: another declaration would emit the loader early.
#pragma pop
