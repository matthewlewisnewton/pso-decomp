#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/CurrentTextureList.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TObjBoss2Tunnel_8007E418.h"
#include "pso/misc/ParticleBallistic.h"
#include "pso/misc/TParticleCtrl.h"
#include "pso/render/render_util.h"
#include "pso/system/vector.h"
#include "pso/misc/TUnk_8048E790.h"
#include "pso/misc/TUnk_8048E7A8.h"
#include "pso/misc/TUnk_8048E728.h"
#include "pso/misc/TUnk_8048E778.h"

#include "types.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/ModelDrawContext.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/misc/CameraHelpers.h"
#include "pso/misc/ParticleDefinition.h"
#include "pso/unk/TUnk_804C57F0.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/unk/text_8023601C.h"

#include "pso/misc/TParticleCtrl_80327D30.h"
#include "pso/player/TObjPlayer_80083594.h"
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

struct Stack_80088844 {
    f32 sp8;
    f32 spC;
    f32 sp10;
};

struct Fields0_800896E4 {
    u8 pad_0[0x18]; s32 *field_18; u16 field_1C; u8 pad_1E[6]; u16 field_24; s16 field_26;
    f32 field_28; f32 field_2C; f32 field_30; f32 field_34; f32 field_38; f32 field_3C; f32 field_40; f32 field_44;
    u8 pad_48[0x14]; f32 field_5C; u8 pad_60[8]; f32 field_68; u8 pad_6C[4]; f32 field_70; f32 field_74; f32 field_78;
    u8 pad_7C[0x19]; s8 field_95; s16 field_96; s32 field_98; s32 field_9C; s32 field_A0;
    u8 pad_A4[0x20]; f32 field_C4; f32 field_C8; f32 field_CC;
};

struct Fields1_800896E4 {
    u8 pad_0[0x18]; f32 field_18; f32 field_1C; f32 field_20; f32 field_24; f32 field_28; u8 pad_2C[4];
    f32 field_30; f32 field_34; f32 field_38; f32 field_3C; u8 pad_40[8]; s32 field_48; s32 field_4C;
    u8 pad_50[4]; f32 field_54; u8 pad_58[0x30]; u8 field_88;
};

struct Fields2_800896E4 { f32 field_0; f32 field_4; f32 field_8; };

struct Fields3_800896E4 { s32 field_0; s32 field_4; s32 field_8; };

struct Vec_800890F4 { f32 x, y, z; };

struct Ang_800890F4 { s32 x, y, z; };

struct Scr_800890F4 { f32 x, y; };

struct Def_800890F4 {
    u8 pad0[0x64];
    f32 sx;
    f32 sy;
    u8 pad6C[0x88 - 0x6C];
    u8 flags;
};

struct Part_800890F4 {
    u8 pad0[0x1C];
    u16 tex;
    u8 pad1E[0x20 - 0x1E];
    Def_800890F4 *def;
    u16 flags;
    u8 pad26[0x28 - 0x26];
    f32 w;
    f32 h;
    u8 pad30[0x6C - 0x30];
    u8 f6C[4];
    Vec_800890F4 pos;
    Vec_800890F4 ofs;
    f32 sw;
    f32 sh;
    u8 pad90[0x96 - 0x90];
    s16 angle;
    u8 pad98[0x9C - 0x98];
    s32 rotY;
    u8 padA0[0xA4 - 0xA0];
    f32 scx;
    f32 scy;
    u8 padAC[0xB0 - 0xAC];
    u32 model;
    u32 texlist;
    u32 motion;
    f32 frame;
    u8 padC0[0xC4 - 0xC0];
    Vec_800890F4 vel;
};

extern "C" {
// Retain the original eight-byte angular-range object in small data.
#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
extern const f32 lbl_805D9520[2];
void *alloc_particle_memory(int);
f32 vec_squared_length(u8 *arg0);
extern s32 TParticleCtrl__data_8048E778[];
s32 rand(void);
extern void *TParticleCtrl__data_80511F70[0x6C];
s32 is_particle_sprite_additive__13TUnk_8048E728Fv(void *, s32);
s32 append_node_to_tail__13TParticleCtrlFPvPv(s32, void *);
s32 all_parents_unqueued_for_destruction__7TObjectFv();
s32 rotate_matrix_y(s32, s32);
s32 push_matrix(f32);
s32 pop_matrix();
s32 post_translate_matrix(void *);
s32 draw_ginja_object(u32);
extern u8 *camera_ctrl_instance;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
f32 vector_length(void *);
void restore_saved_depth_alpha_state();
f32 vec3_dot(void *, void *);
void project_world_to_screen(int, void *, void *);
void push_matrix_from(void *);
void rotate_vector_by_current_matrix(void *, void *);
static const Vec_800890F4 ballistic_camera_horizontal = { 0.0f, 0.0f, -1.0f };
static const Vec_800890F4 ballistic_camera_vertical = { 0.0f, 0.0f, -1.0f };
static const Vec_800890F4 ballistic_forward = { 0.0f, 0.0f, 1.0f };
static const Ang_800890F4 ballistic_zero_angles = { 0, 0, 0 };
}
void setup_particle_tev(s32 arg0);
void load_projected_texture_matrix(f32 farg0);
void direction_to_rotation_xz(u8 *arg0, s32 *arg1, s32 *arg2);

#include "pso/misc/TLobby.h"
#include "pso/misc/TOKeyMachine01.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

u8 *create_ballistic_particle(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, u16 arg4, s16 arg5) {
    u8 *temp_r3;
    u8 *var_r0;
    temp_r3 = (u8 *)(((u8 *)alloc_particle_memory(0xD0)));
    var_r0 = temp_r3;
    if (var_r0 != NULL) {
        var_r0 = (u8 *)(construct_ballistic_particle(temp_r3, arg0, arg1, arg2, arg3, arg4, arg5));
    }
    return var_r0;
}
void *TParticleCtrl::create_random_spread(void *arg0, void *arg1, void *arg2) {
    void *o;
    o = alloc_particle_memory(0xd0);
    if (o != NULL) {
        o = ((TUnk_8048E778 *)o)->init_particle_random_spread(arg0, arg1, arg2);
    }
    return o;
}
void TUnk_8048E778::retire_ballistic_particle_if_done() {
    u8 *arg0 = (u8 *)this;
    Stack_80088844 stack;
    if (*(u8 *)((s8 *)this->param + 0x88) & 8) {
        stack.sp8 = this->pos.x - this->origin.x;
        stack.spC = this->pos.y - *(f32 *)((s8 *)arg0 + 0x34);
        stack.sp10 = this->pos.z - this->origin.z;
        if (0.0f == vec_squared_length((u8 *)&stack.sp8)) {
            queue_destruction();
            return;
        }
    }
    if (this->age >= 1.0f) {
        queue_destruction();
    }
}

#pragma push
// The update uses fused colour interpolation and a fused bounce impulse.
#pragma fp_contract on
inline f32 ballistic_channel(f32 value) {
    return value < 0.0f ? 0.0f : (value < 1.0f ? value : 1.0f);
}

inline f32 fade_ballistic_channel(f32 value, f32 alpha) {
    return value < 0.0f ? 0.0f : alpha * (value < 1.0f ? value : 1.0f);
}

void TUnk_8048E778::run_task() {
    f32 t[2]; // Age and opacity; this grouping preserves native FPR allocation.
    f32 ch[3]; // Red, green, blue.
    if (param->flags & 8) {
        if (age >= 0.5f) {
            approach_camera_vector(&pos, &origin, fabs_float(step.y));
        } else {
            vec3_add_to(&pos, &step);
            VecCopy(&velocity, &step);
        }
    } else {
        if (flags & 2) {
            push_matrix_from(identity_matrix);
            rotate_matrix_x(0, unk_98);
            rotate_matrix_y(0, m_9c);
            rotate_matrix_z(0, unk_A0);
            rotate_vector_by_current_matrix(&step, &velocity);
            pop_matrix();
        } else if (unk_98 == 0 && m_9c == 0 && unk_A0 == 0) {
            VecCopy(&velocity, &step);
        } else {
            push_matrix_from(identity_matrix);
            rotate_matrix_z(0, unk_A0);
            rotate_matrix_x(0, unk_98);
            rotate_matrix_y(0, m_9c);
            rotate_vector_by_current_matrix(&step, &velocity);
            pop_matrix();
        }
        vec3_add_to(&pos, &velocity);
    }
    ParticleParam *p = param;
    if ((p->flags & 2) && origin.y > pos.y) {
        step.y = p->unk_60 * (p->unk_3C * (0.000030517578125f * (f32)rand()) + p->unk_34);
    }
    f32 fade_in = 1.0f;
    f32 fade_out = fade_in;
    step.x *= param->speed_decay;
    step.z *= param->speed_decay;
    step.y += param->gravity;
    m_28 *= param->scale_decay;
    unk_2C *= param->scale_decay;
    age += age_rate;
    p = param;
    t[0] = age;
    if (p->fade_in_end > t[0]) {
        fade_in = t[0] * fade_in_scale;
    }
    if (1.0f - t[0] < p->fade_out_start) {
        fade_out = (1.0f - t[0]) * fade_out_scale;
    }
    t[1] = fade_in < fade_out ? fade_in : fade_out;

    if (static_cast<ParticleDefinition *>(static_cast<TUnk_804C57F0 *>(TParticleCtrl__data_80511F70[sprite_index])->m_28)->flags & 1) {
        if (flags & 0x100) {
            ch[0] = fade_ballistic_channel(p->color_rate[0] * t[0] + color_base[0], t[1]);
            ch[1] = fade_ballistic_channel(p->color_rate[1] * t[0] + color_base[1], t[1]);
            ch[2] = fade_ballistic_channel(p->color_rate[2] * t[0] + color_base[2], t[1]);
        } else {
            ch[0] = fade_ballistic_channel(p->color_rate[0] * t[0] + p->color_base[0], t[1]);
            ch[1] = fade_ballistic_channel(p->color_rate[1] * t[0] + p->color_base[1], t[1]);
            ch[2] = fade_ballistic_channel(p->color_rate[2] * t[0] + p->color_base[2], t[1]);
        }
        t[1] = 1.0f;
    } else {
        if (flags & 0x100) {
            ch[0] = ballistic_channel(p->color_rate[0] * t[0] + color_base[0]);
            ch[1] = ballistic_channel(p->color_rate[1] * t[0] + color_base[1]);
            ch[2] = ballistic_channel(p->color_rate[2] * t[0] + color_base[2]);
        } else {
            ch[0] = ballistic_channel(p->color_rate[0] * t[0] + p->color_base[0]);
            ch[1] = ballistic_channel(p->color_rate[1] * t[0] + p->color_base[1]);
            ch[2] = ballistic_channel(p->color_rate[2] * t[0] + p->color_base[2]);
        }
    }
    // Native big-endian ARGB, using legal unsigned-byte access to a live word.
    u32 packed;
    reinterpret_cast<u8 *>(&packed)[0] = 254.0f * t[1];
    reinterpret_cast<u8 *>(&packed)[1] = 254.0f * ch[0];
    reinterpret_cast<u8 *>(&packed)[2] = 254.0f * ch[1];
    reinterpret_cast<u8 *>(&packed)[3] = 254.0f * ch[2];
    color = packed;
    if (0.0f == param->gravity && 0.0f == param->unk_34 && 0.0f == param->unk_30) {
        m_96 += (s32)(182.04445f * param->unk_60);
    } else if (!(param->flags & 4)) {
        f32 spin = step.y * (param->unk_64 * step.x);
        if (fabs_float(spin) > 20.0f) {
            spin = 20.0f;
        }
        if (speed < 0.0f) {
            m_96 += (s32)(182.04445f * spin);
        } else {
            m_96 -= (s32)(182.04445f * spin);
        }
    }
    s32 frames = static_cast<ParticleDefinition *>(static_cast<TUnk_804C57F0 *>(TParticleCtrl__data_80511F70[sprite_index])->m_28)->uv_count;
    if (param->flags & 0x10) {
        frame = (s32)(age * (f32)(frames - 1));
    } else {
        ++frame;
        if (frames <= frame) {
            frame = 0;
        }
    }
    if (flags & 0x10) {
        TObjCollidable *target = find_entity_by_id(target_id);
        if (target == NULL) {
            queue_destruction();
            return;
        }
        Vec *center = static_cast<Vec *>(target->get_center());
        if (center != NULL) {
            if (flags & 0x20) {
                Vec point;
                offset_point_toward_camera((u8 *)center, (u8 *)&point, 8.0f);
                attach.x = point.x - origin.x;
                attach.y = point.y - origin.y;
                attach.z = point.z - origin.z;
            } else {
                attach.x = center->x - origin.x;
                attach.y = center->y - origin.y;
                attach.z = center->z - origin.z;
            }
        }
    }
    motion_frame += motion_frame_step;
    if (motion != NULL && (f32)(motion->nbFrame - 1) <= motion_frame) {
        motion_frame = (f32)(motion->nbFrame - 1);
    }
    retire_ballistic_particle_if_done();
}
#pragma pop

#pragma push
// The original renderer addresses each initializer separately.
#pragma pool_data off
void TUnk_8048E778::render() {
    Part_800890F4 *p = (Part_800890F4 *)this;
    u16 flags;
    int id;
    if (all_parents_unqueued_for_destruction__7TObjectFv() == 0) {
        return;
    }
    if (p->def->flags & 4) {
        Vec_800890F4 b;
        Vec_800890F4 a;
        Scr_800890F4 s0;
        Scr_800890F4 s1;
        f32 len;
        if (p->flags & 0x10) {
            a.x = p->pos.x + p->ofs.x;
            a.y = p->pos.y + p->ofs.y;
            a.z = p->pos.z + p->ofs.z;
        } else {
            VecCopy((Vec *)&a, (const Vec *)&p->pos);
        }
        b.x = a.x + p->vel.x;
        b.y = a.y + p->vel.y;
        b.z = a.z + p->vel.z;
        len = vector_length(&p->vel);
        project_world_to_screen(0, &a, &s0);
        project_world_to_screen(0, &b, &s1);
        s1.x -= s0.x;
        s1.y -= s0.y;
        p->angle = 10430.38043493439 * atan2_float(s1.y, s1.x);
        p->sw = p->def->sx * len;
        p->sh = p->def->sy * len;
    } else if (p->def->flags & 0x40) {
        Vec_800890F4 a = ballistic_camera_horizontal;
        Vec_800890F4 b = ballistic_camera_vertical;
        Vec_800890F4 c = ballistic_forward;
        f32 d1;
        f32 d2;
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, p->rotY);
        rotate_vector_by_current_matrix(&c, &c);
        pop_matrix();
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, *(s32 *)(camera_ctrl_instance + 0x194));
        rotate_vector_by_current_matrix(&a, &a);
        pop_matrix();
        push_matrix_from(identity_matrix);
        rotate_matrix_y(0, *(s32 *)(camera_ctrl_instance + 0x190));
        rotate_vector_by_current_matrix(&b, &b);
        pop_matrix();
        d1 = vec3_dot(&c, &a);
        d2 = vec3_dot(&c, &b);
        if (d2 < 0.0f) {
            d2 *= -1.0f;
        }
        if (d1 < 0.0f) {
            d1 *= -1.0f;
        }
        flags = p->flags;
        if (flags & 8) {
            p->sw = p->w;
            p->sh = p->h * d2;
        } else if (flags & 4) {
            p->sw = p->w * d1;
            p->sh = p->h;
        } else {
            p->sw = p->w * d1;
            p->sh = p->h * d2;
        }
    } else {
        p->sw = p->w;
        p->sh = p->h;
    }
    p->sw *= p->scx;
    p->sh *= p->scy;
    flags = p->flags;
    if (flags & 0x200) {
        Vec_800890F4 t;
        if (is_split_screen() != 0 && (p->flags & 0x400)) {
            return;
        }
        if (p->texlist == 0) {
            return;
        }
        if (p->model == 0) {
            return;
        }
        t.x = p->pos.x + p->ofs.x;
        t.y = p->pos.y + p->ofs.y;
        t.z = p->pos.z + p->ofs.z;
        Ang_800890F4 r = ballistic_zero_angles;
        direction_to_rotation_xz((u8 *)&p->vel, &r.x, &r.z);
        ((s32 (*)())push_matrix)();
        post_translate_matrix(&t);
        scale_matrix(0, p->sw, p->sw, p->sw);
        rotate_matrix_z(0, r.z);
        rotate_matrix_x(0, r.x);
        if (p->flags & 0x1000) {
            if (camera_ctrl_instance != NULL) {
                rotate_matrix_y(0, *(s32 *)(camera_ctrl_instance + 0x194));
            }
        } else {
            rotate_matrix_y(0, r.y);
            rotate_matrix_y(0, p->angle);
        }
        if (p->flags & 0x400) {
            load_projected_texture_matrix(1.33f);
        }
        TParticleCtrl::begin_effect_render();
        if (p->flags & 0x400) {
            setup_particle_tev(0);
        } else {
            s32 st = model_render_flags;
            saved_model_render_flags = st;
            model_render_flags = st | 0x8021;
            if (is_particle_sprite_additive__13TUnk_8048E728Fv(p, st) != 0) {
                ((TUnk_8048E728 *)p)->apply_particle_model_fade_color(1);
            } else {
                ((TUnk_8048E728 *)p)->apply_particle_model_fade_color(0);
            }
        }
        set_current_texture_list((GinjaTextureList *)(p->texlist));
        set_draw_list_mask(3);
        if (p->motion != 0) {
            draw_ginja_model_with_motion((void *)p->model, (void *)p->motion, p->frame);
        } else {
            draw_ginja_object(p->model);
        }
        if (p->flags & 0x400) {
            reset_particle_tev();
        } else {
            model_render_flags = saved_model_render_flags;
        }
        restore_draw_list_mask();
        TParticleCtrl::end_effect_render();
        pop_matrix();
    } else if (flags & 0x2000) {
        ((TUnk_8048E728 *)p)->draw_particle_refraction_quad();
    } else if (flags & 0x800) {
        if (p->def->flags & 0x20) {
            id = p->tex + 0x36;
        } else {
            id = p->tex;
        }
        set_depth_buffer_settings_2();
        ((TUnk_8048E778 *)p)->draw_sprite_quad(id);
        restore_saved_depth_alpha_state();
    } else if (p->def->flags & 0x20) {
        id = p->tex + 0x36;
        append_node_to_tail__13TParticleCtrlFPvPv(((s32 *)&TParticleCtrl__data_80511F70)[id], p->f6C);
    } else {
        append_node_to_tail__13TParticleCtrlFPvPv(((s32 *)&TParticleCtrl__data_80511F70)[p->tex], p->f6C);
    }
}

#pragma pop

void *__dt__13TUnk_8048E778Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = TParticleCtrl__data_8048E778;
        __dt__13TUnk_8048E728Fv((u8 *)arg0, 0);
        if (arg1 > 0) {
            ((TUnk_8048E728 *)arg0)->free_from_heap();
        }
    }
    return arg0;
}
#pragma push
#pragma fp_contract on
u8 *construct_ballistic_particle(void *a0, void *a1, void *a2, void *a3, s32 arg4, u16 arg5, s16 arg6) {
    Fields0_800896E4 *p = (Fields0_800896E4 *)a0;
    Fields1_800896E4 *d = (Fields1_800896E4 *)a1;
    Fields2_800896E4 *pos = (Fields2_800896E4 *)a2;
    Fields3_800896E4 *c = (Fields3_800896E4 *)a3;
    s32 temp_r0;
    f32 *v;
    init_particle_base(a0, a1, arg4);
    p->field_18 = TParticleCtrl__data_8048E778;
    p->field_C4 = 0.0f;
    p->field_C8 = 0.0f;
    p->field_CC = 0.0f;
    p->field_24 = arg5;
    if (p->field_24 & 0x80) {
        p->field_95 = 1;
    }
    p->field_26 = arg6;
    p->field_98 = c->field_0;
    p->field_9C = c->field_4;
    p->field_A0 = c->field_8;
    p->field_70 = (d->field_18 * ((0.000030517578125f * (f32)rand()) - 0.5f)) + pos->field_0;
    p->field_78 = (d->field_20 * ((0.000030517578125f * (f32)rand()) - 0.5f)) + pos->field_8;
    if (d->field_88 & 2) {
        p->field_74 = pos->field_4 + d->field_1C;
    } else {
        p->field_74 = (d->field_1C * ((0.000030517578125f * (f32)rand()) - 0.5f)) + pos->field_4;
    }
    p->field_30 = pos->field_0;
    p->field_38 = pos->field_8;
    if (d->field_88 & 2) {
        p->field_34 = pos->field_4;
    } else {
        p->field_34 = pos->field_4;
    }
    p->field_28 = (d->field_28 * (0.000030517578125f * (f32)rand())) + d->field_24;
    p->field_2C = p->field_28;
    temp_r0 = (s32)(((f32)d->field_4C * (0.000030517578125f * (f32)rand())) + (f32)d->field_48);
    if (d->field_88 & 1) {
        p->field_5C = 1.0f / (f32)((s32 **)(((void **)&TParticleCtrl__data_80511F70)[p->field_1C]))[0x28 / 4][0xC / 4];
    } else {
        p->field_5C = 1.0f / (f32)temp_r0;
    }
    p->field_3C = (d->field_38 * (0.000030517578125f * (f32)rand())) + d->field_30;
    p->field_40 = (d->field_3C * (0.000030517578125f * (f32)rand())) + d->field_34;
    v = &p->field_3C;
    p->field_44 = 0.0f;
    rotate_vec_xz(v, v, (s32)(182.04445f * (lbl_805D9520[0] * (0.000030517578125f * (f32)rand()))));
    if (0.0f == d->field_54 && 0.0f == d->field_34 && 0.0f == d->field_30) {
        p->field_96 = 0;
        p->field_68 = 0.0f;
    } else {
        p->field_96 = (s16)(182.04445f * (lbl_805D9520[0] * (0.000030517578125f * (f32)rand())));
        p->field_68 = (0.000030517578125f * (f32)rand()) - 0.5f;
    }
    if (p->field_24 & 0x2000) {
        request_indirect_effect(0x1F);
    }
    return (u8 *)a0;
}
#pragma pop

struct BF0_80089B50 {
    u8 pad_0[0x18]; s32 *field_18; u16 field_1C; u8 pad_1E[6]; u16 field_24; s16 field_26;
    f32 field_28; f32 field_2C; f32 field_30; f32 field_34; f32 field_38; f32 field_3C; f32 field_40; f32 field_44;
    u8 pad_48[0x14]; f32 field_5C; u8 pad_60[8]; f32 field_68; u8 pad_6C[4]; f32 field_70; f32 field_74; f32 field_78;
    u8 pad_7C[0x19]; s8 field_95; s16 field_96; s32 field_98; s32 field_9C; s32 field_A0;
    u8 pad_A4[0x20]; f32 field_C4; f32 field_C8; f32 field_CC;
};
struct BF1_80089B50 {
    u8 pad_0[0x18]; f32 field_18; f32 field_1C; f32 field_20; f32 field_24; f32 field_28; u8 pad_2C[4];
    f32 field_30; f32 field_34; f32 field_38; f32 field_3C; u8 pad_40[8]; s32 field_48; s32 field_4C;
    u8 pad_50[4]; f32 field_54; u8 pad_58[0x30]; u8 field_88;
};
struct BF2_80089B50 { f32 field_0; f32 field_4; f32 field_8; };

#pragma push
#pragma fp_contract on
void *TUnk_8048E778::init_particle_random_spread(void *a1, void *a2, void *a3) {
    BF0_80089B50 *p = (BF0_80089B50 *)this;
    BF1_80089B50 *d = (BF1_80089B50 *)a1;
    BF2_80089B50 *pos = (BF2_80089B50 *)a2;
    s32 temp_r0;
    f32 *v;
    init_particle_base(this, a1, (s32)a3);
    p->field_18 = TParticleCtrl__data_8048E778;
    p->field_C4 = 0.0f;
    p->field_C8 = 0.0f;
    p->field_CC = 0.0f;
    p->field_70 = (d->field_18 * ((0.000030517578125f * (f32)rand()) - 0.5f)) + pos->field_0;
    p->field_78 = (d->field_20 * ((0.000030517578125f * (f32)rand()) - 0.5f)) + pos->field_8;
    if (d->field_88 & 2) {
        p->field_74 = pos->field_4 + d->field_1C;
    } else {
        p->field_74 = (d->field_1C * ((0.000030517578125f * (f32)rand()) - 0.5f)) + pos->field_4;
    }
    p->field_30 = pos->field_0;
    p->field_38 = pos->field_8;
    if (d->field_88 & 2) {
        p->field_34 = pos->field_4;
    } else {
        p->field_34 = pos->field_4;
    }
    p->field_28 = (d->field_28 * (0.000030517578125f * (f32)rand())) + d->field_24;
    p->field_2C = p->field_28;
    temp_r0 = (s32)(((f32)d->field_4C * (0.000030517578125f * (f32)rand())) + (f32)d->field_48);
    if (d->field_88 & 1) {
        p->field_5C = 1.0f / (f32)((s32 **)(((void **)&TParticleCtrl__data_80511F70)[p->field_1C]))[0x28 / 4][0xC / 4];
    } else {
        p->field_5C = 1.0f / (f32)temp_r0;
    }
    p->field_3C = (d->field_38 * (0.000030517578125f * (f32)rand())) + d->field_30;
    p->field_40 = (d->field_3C * (0.000030517578125f * (f32)rand())) + d->field_34;
    v = &p->field_3C;
    p->field_44 = 0.0f;
    rotate_vec_xz(v, v, (s32)(182.04445f * (lbl_805D9520[0] * (0.000030517578125f * (f32)rand()))));
    if (0.0f == d->field_54 && 0.0f == d->field_34 && 0.0f == d->field_30) {
        p->field_96 = 0;
        p->field_68 = 0.0f;
    } else {
        p->field_96 = (s16)(182.04445f * (lbl_805D9520[0] * (0.000030517578125f * (f32)rand())));
        p->field_68 = (0.000030517578125f * (f32)rand()) - 0.5f;
    }
    if (p->field_24 & 0x2000) {
        request_indirect_effect(0x1F);
    }
    return this;
}
#pragma pop

extern "C" {
#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
const f32 lbl_805D9520[2] = { 360.0f, 0.0f };
}
