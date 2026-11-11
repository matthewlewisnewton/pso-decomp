#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/CurrentTextureList.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/ParticleOrbit.h"
#include "pso/misc/TParticleCtrl.h"
#include "pso/render/render_util.h"
#include "pso/system/vector.h"
#include "pso/misc/TUnk_8048E778.h"
#include "pso/misc/TUnk_8048E7A8.h"
#include "pso/misc/TUnk_8048E728.h"
#include "pso/misc/TUnk_8048E790.h"

#include "types.h"
#include "pso/misc/TParticleCtrl_80327D30.h"
#include "pso/player/TObjPlayer_80083594.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/ModelDrawContext.h"
#include "pso/misc/ParticleDefinition.h"
#include "pso/unk/TUnk_804C57F0.h"
#include <stddef.h>

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off


struct Vec_8008A92C { f32 x, y, z; };

struct Obj_8008AC24 {
    u8 pad_0[0x18];
    s32 *f18;
    u16 f1C;
    u8 pad_1E[6];
    u16 f24;
    s16 f26;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    u8 pad_44[0x18];
    f32 f5C;
    u8 pad_60[8];
    f32 f68;
    u8 pad_6C[8];
    f32 f74;
    u8 pad_78[0x1D];
    s8 f95;
    s16 f96;
    s32 f98;
    s32 f9C;
    s32 fA0;
    u8 pad_A4[0x20];
    f32 fC4;
    f32 fC8;
    u8 pad_CC[4];
    f32 fD0;
    f32 fD4;
    s32 fD8;
    s32 fDC;
};

struct Desc_8008AC24 {
    u8 pad_0[0x18];
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    u8 pad_2C[4];
    f32 f30;
    f32 f34;
    u8 pad_38[0x10];
    s32 f48;
    s32 f4C;
    u8 pad_50[0x10];
    f32 f60;
    f32 f64;
    f32 f68;
    u8 pad_6C[8];
    f32 f74;
    u8 pad_78[0x10];
    u8 f88;
};

struct Vec_8008AC24 { f32 x, y, z; };

struct IVec_8008AC24 { s32 x, y, z; };

extern void *TParticleCtrl__data_80511F70[0x6C];
struct OObj_8008B060 {
    u8 pad_0[0x18]; s32 *f18; u16 f1C; u8 pad_1E[6]; u16 f24; s16 f26;
    f32 f28; f32 f2C; f32 f30; f32 f34; f32 f38; f32 f3C; f32 f40; u8 pad_44[0x18];
    f32 f5C; u8 pad_60[8]; f32 f68; u8 pad_6C[8]; f32 f74; u8 pad_78[0x1D];
    s8 f95; s16 f96; s32 f98; s32 f9C; s32 fA0; u8 pad_A4[0x20];
    f32 fC4; f32 fC8; u8 pad_CC[4]; f32 fD0; f32 fD4; s32 fD8; s32 fDC;
};

struct ODesc_8008B060 {
    u8 pad_0[0x18]; f32 f18; f32 f1C; f32 f20; f32 f24; f32 f28; u8 pad_2C[4];
    f32 f30; f32 f34; u8 pad_38[0x10]; s32 f48; s32 f4C; u8 pad_50[0x10];
    f32 f60; f32 f64; f32 f68; u8 pad_6C[8]; f32 f74; u8 pad_78[0x10]; u8 f88;
};

struct OVec_8008B060 { f32 x, y, z; };

struct OIVec_8008B060 { s32 x, y, z; };

extern "C" {
void *alloc_particle_memory(int);
extern s32 TParticleCtrl__data_8048E790[];
__declspec(section ".sdata2") extern const f32 lbl_805D9550[2];
s32 rand(void);
s32 is_split_screen();
void append_node_to_tail__13TParticleCtrlFPvPv(void *, void *);
f32 cos_table_lookup(s32);
s32 scale_matrix(s32, f32, f32, f32);
s32 rotate_matrix_y(s32, s32);
s32 rotate_matrix_z(s32, s32);
s32 rotate_matrix_x(s32, s32);
s32 push_matrix(void);
s32 pop_matrix();
s32 post_translate_matrix(void *);
s32 draw_ginja_object(u32);
extern u8 *camera_ctrl_instance;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
void __ct__7TObjectFP7TObject(void *, void *);
}
void setup_particle_tev(s32 arg0);
void load_projected_texture_matrix(f32 farg0);
extern void *__vt__13TParticleCtrl[];
extern s32 TParticleCtrl__class_name_descriptor;
extern void *tl_07;
extern void *tl_clipout;
extern const f32 TParticleCtrl__data_805D94E0;
extern const f32 TParticleCtrl__data_805D94E4;

#include "pso/misc/TLobby.h"
#include "pso/misc/TOKeyMachine01.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {

u8 *create_orbit_particle(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, u16 arg4, s16 arg5) {
    u8 *particle_memory;
    u8 *var_r0;
    particle_memory = (u8 *)(((u8 *)alloc_particle_memory(0xE0)));
    var_r0 = particle_memory;
    if (var_r0 != NULL) {
        var_r0 = (u8 *)(init_orbit_sprite_particle(particle_memory, arg0, arg1, arg2, arg3, arg4, arg5));
    }
    return var_r0;
}
void *TParticleCtrl::alloc_child_particle(void *arg1, void *arg2, void *arg3) {
    void *o;
    o = alloc_particle_memory(0xe0);
    if (o != NULL) {
        o = ((TUnk_8048E790 *)o)->init_random_particle(this, arg1, arg2, arg3);
    }
    return o;
}
void TUnk_8048E790::retire_orbit_particle() {
    u8 *arg0 = (u8 *)this;
    if (this->age >= 1.0f) {
        queue_destruction();
    }
}


extern "C" {
f32 sin_table_lookup(s32);
f32 fabs_float(f32);
s32 push_matrix_from(void *);
void rotate_vector_by_current_matrix(const Vec *, Vec *);
extern f32 identity_matrix[3][4];
}
static inline f32 orbit_color(f32 value) {
    if (value < 0.0f) return 0.0f;
    if (value < 1.0f) return value;
    return 1.0f;
}
static inline f32 orbit_faded_color(f32 fade, f32 value) {
    return value < 0.0f ? 0.0f : fade * (value < 1.0f ? value : 1.0f);
}

#pragma push
#pragma fp_contract on
// The original orbit and color interpolations use fused operations.
void TUnk_8048E790::run_task() {
    Vec follow_offset, orbit, rise;
    orbit_angle += (s32)(182.0444488525390625f * step.x);
    if (flags & 0x10) {
        TObjCollidable *entity = find_entity_by_id(target_id);
        if (entity == NULL) {
            queue_destruction();
            return;
        }
        Vec *center = (Vec *)entity->get_center();
        if (unk_98 && m_9c && unk_A0) {
            attach.x = center_x - origin.x;
            attach.z = center_z - origin.z;
            pos.x = radius * cos_table_lookup(orbit_angle) + center->x;
            pos.z = radius * sin_table_lookup(orbit_angle) + center->z;
        } else {
            attach.x = center_x - origin.x;
            attach.z = center_z - origin.z;
            pos.x = radius * cos_table_lookup(orbit_angle) + center->x;
            pos.z = radius * sin_table_lookup(orbit_angle) + center->z;
            pos.y = center->y;
            vertical_offset += step.y;
            follow_offset.x = 0.0f;
            follow_offset.z = 0.0f;
            follow_offset.y = vertical_offset;
            push_matrix_from(identity_matrix);
            rotate_matrix_x(0, unk_98);
            rotate_matrix_y(0, m_9c);
            rotate_matrix_z(0, unk_A0);
            rotate_vector_by_current_matrix(&follow_offset, &follow_offset);
            pop_matrix();
            pos.x += follow_offset.x;
            pos.y += follow_offset.y;
            pos.z += follow_offset.z;
        }
    } else if (unk_98 && m_9c && unk_A0) {
        pos.x = radius * cos_table_lookup(orbit_angle) + center_x;
        pos.z = radius * sin_table_lookup(orbit_angle) + center_z;
    } else {
        orbit.x = radius * cos_table_lookup(orbit_angle);
        orbit.z = radius * sin_table_lookup(orbit_angle);
        orbit.y = 0.0f;
        vertical_offset += step.y;
        rise.x = 0.0f;
        rise.z = 0.0f;
        rise.y = vertical_offset;
        push_matrix_from(identity_matrix);
        rotate_matrix_x(0, unk_98);
        rotate_matrix_y(0, m_9c);
        rotate_matrix_z(0, unk_A0);
        rotate_vector_by_current_matrix(&orbit, &orbit);
        rotate_vector_by_current_matrix(&rise, &rise);
        pop_matrix();
        pos.x = rise.x + (center_x + orbit.x);
        pos.z = rise.z + (center_z + orbit.z);
        pos.y = rise.y + (origin.y + orbit.y);
    }
    if (unk_98 && m_9c && unk_A0) pos.y += step.y;
    m_28 *= param->scale_decay;
    unk_2C *= param->scale_decay;
    f32 envelope[2]; // [0] normalized age, [1] resulting opacity
    f32 fade_in = 1.0f;
    f32 fade_out = fade_in;
    // This emitter variant uses +0x50/+0x38/+0x3C as its RGB rates.
    ParticleParam *d = param;
    envelope[0] = age;
    if (d->fade_in_end > envelope[0]) fade_in = envelope[0] * fade_in_scale;
    if (1.0f - envelope[0] < d->fade_out_start)
        fade_out = (1.0f - envelope[0]) * fade_out_scale;
    f32 channels[3]; // red, green, blue
    envelope[1] = fade_in < fade_out ? fade_in : fade_out;
    ParticleDefinition *definition = static_cast<ParticleDefinition *>(
        static_cast<TUnk_804C57F0 *>(TParticleCtrl__data_80511F70[sprite_index])->m_28);
    if (definition->flags & 1) {
        if (flags & 0x100) {
            channels[0] = orbit_faded_color(envelope[1], d->speed_decay * envelope[0] + color_base[0]);
            channels[1] = orbit_faded_color(envelope[1], d->unk_38 * envelope[0] + color_base[1]);
            channels[2] = orbit_faded_color(envelope[1], d->unk_3C * envelope[0] + color_base[2]);
        } else {
            channels[0] = orbit_faded_color(envelope[1], d->speed_decay * envelope[0] + d->color_base[0]);
            channels[1] = orbit_faded_color(envelope[1], d->unk_38 * envelope[0] + d->color_base[1]);
            channels[2] = orbit_faded_color(envelope[1], d->unk_3C * envelope[0] + d->color_base[2]);
        }
        envelope[1] = 1.0f;
    } else if (flags & 0x100) {
        channels[0] = orbit_color(d->speed_decay * envelope[0] + color_base[0]);
        channels[1] = orbit_color(d->unk_38 * envelope[0] + color_base[1]);
        channels[2] = orbit_color(d->unk_3C * envelope[0] + color_base[2]);
    } else {
        channels[0] = orbit_color(d->speed_decay * envelope[0] + d->color_base[0]);
        channels[1] = orbit_color(d->unk_38 * envelope[0] + d->color_base[1]);
        channels[2] = orbit_color(d->unk_3C * envelope[0] + d->color_base[2]);
    }
    // Native ARGB bytes; a little-endian port must pack the four shifts.
    u32 col;
    reinterpret_cast<u8 *>(&col)[0] = (u8)(254.0f * envelope[1]);
    reinterpret_cast<u8 *>(&col)[1] = (u8)(254.0f * channels[0]);
    reinterpret_cast<u8 *>(&col)[2] = (u8)(254.0f * channels[1]);
    reinterpret_cast<u8 *>(&col)[3] = (u8)(254.0f * channels[2]);
    color = col;
    m_dc += (s32)(182.0444488525390625f * param->color_rate[0]);
    age += age_rate;
    f32 spin = (8.0f * step.x) * step.y;
    if (fabs_float(spin) > 10.0f) spin = 10.0f;
    if (speed < 0.0f)
        m_96 += (s32)(182.0444488525390625f * spin);
    else m_96 -= (s32)(182.0444488525390625f * spin);
    s32 frames = static_cast<ParticleDefinition *>(
        static_cast<TUnk_804C57F0 *>(TParticleCtrl__data_80511F70[sprite_index])->m_28)->uv_count;
    if (param->flags & 0x10) frame = (s32)(age * (f32)(frames - 1));
    else {
        frame++;
        if (frames <= frame) frame = 0;
    }
    m_28 *= m_a4;
    unk_2C *= unk_A8;
    if (motion) {
        motion_frame += motion_step;
        if ((f32)(motion->nbFrame - 1) <= motion_frame)
            motion_frame = (f32)(motion->nbFrame - 1);
    }
    retire_orbit_particle();
}
#pragma pop
void TUnk_8048E790::render() {
    u8 *arg0 = (u8 *)this;
    Vec_8008A92C sp8;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f3;
    s32 temp_r4;
    u16 temp_r3;
    if (all_parents_unqueued_for_destruction() != 0) {
        temp_f3 = *(f32 *)((s8 *)this->param + 0x70) * cos_table_lookup(this->m_dc);
        this->m_88 = (f32) (this->m_28 * (1.0f + temp_f3));
        *(f32 *)((s8 *)arg0 + 0x8C) = (f32) (this->unk_2C * (1.0f - temp_f3));
        this->m_88 = (f32) (this->m_88 * this->m_a4);
        *(f32 *)((s8 *)arg0 + 0x8C) = (f32) (*(f32 *)((s8 *)arg0 + 0x8C) * *(f32 *)((s8 *)arg0 + 0xA8));
        temp_r3 = *(u16 *)((s8 *)arg0 + 0x24);
        if (temp_r3 & 0x200) {
            if (((is_split_screen() == 0) || !(*(u16 *)((s8 *)arg0 + 0x24) & 0x400)) && ((u32) *(u32 *)&this->unk_B4 != 0U) && ((u32) this->m_b0 != 0U)) {
                sp8.x = this->pos.x + this->attach.x;
                sp8.y = this->pos.y + this->attach.y;
                sp8.z = this->pos.z + this->attach.z;
                push_matrix();
                post_translate_matrix(&sp8);
                temp_f1_2 = this->m_88;
                scale_matrix(0, temp_f1_2, temp_f1_2, temp_f1_2);
                rotate_matrix_z(0, *(s32 *)&this->unk_A0);
                rotate_matrix_x(0, *(s32 *)&this->unk_98);
                rotate_matrix_y(0, this->m_9c);
                saved_model_render_flags = model_render_flags;
                if (*(u16 *)((s8 *)arg0 + 0x24) & 0x400) {
                    TParticleCtrl::begin_effect_render();
                    load_projected_texture_matrix(1.33f);
                }
                rotate_matrix_y(0, (s32) this->m_96);
                if ((*(u16 *)((s8 *)arg0 + 0x24) & 0x1000) && ((void *) camera_ctrl_instance != NULL)) {
                    rotate_matrix_y(0, *(s32 *)((s8 *)camera_ctrl_instance + 0x194));
                }
                TParticleCtrl::end_effect_render();
                if (*(u16 *)((s8 *)arg0 + 0x24) & 0x400) {
                    setup_particle_tev(0);
                } else {
                    temp_r4 = model_render_flags;
                    saved_model_render_flags = temp_r4;
                    model_render_flags = temp_r4 | 0x8021;
                    if (is_particle_sprite_additive() != 0) {
                        ((TUnk_8048E728 *)arg0)->apply_particle_model_fade_color(1);
                    } else {
                        ((TUnk_8048E728 *)arg0)->apply_particle_model_fade_color(0);
                    }
                }
                set_current_texture_list((GinjaTextureList *)(*(u32 *)&this->unk_B4));
                set_draw_list_mask(3);
                if (this->motion != NULL) {
                    draw_ginja_model_with_motion(reinterpret_cast<void *>(this->m_b0), this->motion, this->motion_frame);
                } else {
                    draw_ginja_object(this->m_b0);
                }
                if (*(u16 *)((s8 *)arg0 + 0x24) & 0x400) {
                    reset_particle_tev();
                }
                model_render_flags = saved_model_render_flags;
                TParticleCtrl::end_effect_render();
                pop_matrix();
            }
        } else {
            if (temp_r3 & 0x2000) {
                ((TUnk_8048E728 *)arg0)->draw_particle_refraction_quad();
                return;
            }
            if (*(u8 *)((s8 *)this->param + 0x88) & 0x20) {
                append_node_to_tail__13TParticleCtrlFPvPv(((void **)((u8 *)&TParticleCtrl__data_80511F70 + 0xD8))[*(u16 *)((s8 *)arg0 + 0x1C)], arg0 + 0x6C);
                return;
            }
            append_node_to_tail__13TParticleCtrlFPvPv(((void **)&TParticleCtrl__data_80511F70)[*(u16 *)((s8 *)arg0 + 0x1C)], arg0 + 0x6C);
        }
    }
}

void *__dt__13TUnk_8048E790Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = TParticleCtrl__data_8048E790;
        __dt__13TUnk_8048E728Fv((u8 *)arg0, 0);
        if (arg1 > 0) {
            ((TUnk_8048E728 *)arg0)->free_from_heap();
        }
    }
    return arg0;
}
}
#pragma push
#pragma fp_contract on
u8 *init_orbit_sprite_particle(u8 *object, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4, u16 arg5, s16 arg6) {
    Obj_8008AC24 *o = (Obj_8008AC24 *)object;
    Desc_8008AC24 *d = (Desc_8008AC24 *)arg1;
    Vec_8008AC24 *p = (Vec_8008AC24 *)arg2;
    IVec_8008AC24 *v = (IVec_8008AC24 *)arg3;
    s32 temp_r0;
    init_particle_base(object, arg1, arg4);
    o->f18 = TParticleCtrl__data_8048E790;
    o->f98 = v->x;
    o->f9C = v->y;
    o->fA0 = v->z;
    o->fC4 = (2.0f * d->f18) * (((1.0f / 32768.0f) * (f32)rand()) - 0.5f) + p->x;
    o->fC8 = (2.0f * d->f20) * (((1.0f / 32768.0f) * (f32)rand()) - 0.5f) + p->z;
    o->f74 = (2.0f * d->f1C) * (((1.0f / 32768.0f) * (f32)rand()) - 0.5f) + p->y;
    o->f30 = p->x;
    o->f38 = p->z;
    o->f34 = o->f74;
    o->f24 = arg5;
    if (o->f24 & 0x80) {
        o->f95 = 1;
    }
    o->f26 = arg6;
    o->f28 = d->f28 * ((1.0f / 32768.0f) * (f32)rand()) + d->f24;
    o->f2C = o->f28;
    temp_r0 = (s32)((f32)d->f4C * ((1.0f / 32768.0f) * (f32)rand()) + (f32)d->f48);
    if (d->f88 & 1) {
        o->f5C = 1.0f / (f32)*(s32 *)((s8 *)(*(void **)((s8 *)(*(s32 *)((s8 *)&TParticleCtrl__data_80511F70 + (o->f1C * 4))) + 0x28)) + 0xC);
    } else {
        o->f5C = 1.0f / (f32)temp_r0;
    }
    o->f3C = d->f74 * ((1.0f / 32768.0f) * (f32)rand()) + d->f30;
    o->f40 = d->f68 * ((1.0f / 32768.0f) * (f32)rand()) + d->f34;
    o->fD8 = (s32)(182.0444488525390625f * (lbl_805D9550[0] * ((1.0f / 32768.0f) * (f32)rand())));
    o->fD0 = d->f64 * ((1.0f / 32768.0f) * (f32)rand()) + d->f60;
    o->fDC = (s32)(182.0444488525390625f * (lbl_805D9550[0] * ((1.0f / 32768.0f) * (f32)rand())));
    o->f96 = o->fD8;
    o->f68 = ((1.0f / 32768.0f) * (f32)rand()) - 0.5f;
    o->fD4 = 0.0f;
    if (o->f24 & 0x2000) {
        request_indirect_effect(0x1F);
    }
    return object;
}
#pragma pop

#pragma push
#pragma fp_contract on

void *TUnk_8048E790::init_random_particle(void *arg1, void *arg2, void *arg3, void *arg4) {
    OObj_8008B060 *o = (OObj_8008B060 *)this;
    ODesc_8008B060 *d = (ODesc_8008B060 *)arg1;
    OVec_8008B060 *p = (OVec_8008B060 *)arg2;
    OIVec_8008B060 *v = (OIVec_8008B060 *)arg3;
    s32 temp_r0;
    init_particle_base(this, arg1, (s32)arg4);
    o->f18 = TParticleCtrl__data_8048E790;
    o->f98 = v->x;
    o->f9C = v->y;
    o->fA0 = v->z;
    o->fC4 = (2.0f * d->f18) * (((1.0f / 32768.0f) * (f32)rand()) - 0.5f) + p->x;
    o->fC8 = (2.0f * d->f20) * (((1.0f / 32768.0f) * (f32)rand()) - 0.5f) + p->z;
    o->f74 = (2.0f * d->f1C) * (((1.0f / 32768.0f) * (f32)rand()) - 0.5f) + p->y;
    o->f30 = p->x;
    o->f38 = p->z;
    o->f34 = o->f74;
    o->f28 = d->f28 * ((1.0f / 32768.0f) * (f32)rand()) + d->f24;
    o->f2C = o->f28;
    temp_r0 = (s32)((f32)d->f4C * ((1.0f / 32768.0f) * (f32)rand()) + (f32)d->f48);
    if (d->f88 & 1) {
        o->f5C = 1.0f / (f32)*(s32 *)((s8 *)(*(void **)((s8 *)(*(s32 *)((s8 *)((s32 *)&TParticleCtrl__data_80511F70) + (o->f1C * 4))) + 0x28)) + 0xC);
    } else {
        o->f5C = 1.0f / (f32)temp_r0;
    }
    o->f3C = d->f74 * ((1.0f / 32768.0f) * (f32)rand()) + d->f30;
    o->f40 = d->f68 * ((1.0f / 32768.0f) * (f32)rand()) + d->f34;
    o->fD8 = (s32)(182.0444488525390625f * (lbl_805D9550[0] * ((1.0f / 32768.0f) * (f32)rand())));
    o->fD0 = d->f64 * ((1.0f / 32768.0f) * (f32)rand()) + d->f60;
    o->fDC = (s32)(182.0444488525390625f * (lbl_805D9550[0] * ((1.0f / 32768.0f) * (f32)rand())));
    o->f96 = o->fD8;
    o->f68 = ((1.0f / 32768.0f) * (f32)rand()) - 0.5f;
    o->fD4 = 0.0f;
    if (o->f24 & 0x2000) {
        request_indirect_effect(0x1F);
    }
    return this;
}
#pragma pop

// The last scalar and its trailing zero occupy the original eight-byte object.
extern "C" __declspec(section ".sdata2") const f32 lbl_805D9550[2] = { 360.0f, 0.0f };
