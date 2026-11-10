#include "pso/system/CurrentTextureList.h"
#include "pso/TParticleCtrl.h"
#include "pso/render/render_util.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"
#include "pso/misc/TUnk_8048E778.h"
#include "pso/misc/TUnk_8048E790.h"
#include "pso/misc/TUnk_8048E728.h"
#include "pso/misc/TUnk_8048E7A8.h"

#include "types.h"
#include "pso/misc/TParticleCtrl_80327D30.h"
#include "pso/player/TObjPlayer_80083594.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include <stddef.h>

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

struct RecoveredGlobal_8008C21C_TParticleCtrl__data_8048E7A8 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8008C21C_TParticleCtrl__data_80511F70 {
    s32 value;
    u8 remaining[0x1AC];
};

struct RecoveredGlobal_8008BF58_TParticleCtrl__data_8048E7A8 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8008BF58_TParticleCtrl__data_80511F70 {
    s32 value;
    u8 remaining[0x1AC];
};

struct Vec_8008BAF8 { f32 x, y, z; };

struct Ang_8008BAF8 { s32 x, y, z; };

struct Scr_8008BAF8 { f32 x, y; };

extern "C" {
void *alloc_particle_memory(int);
void queue_destruction__7TObjectFv(void *arg0);
f32 vec_squared_length(u8 *arg0);
u8 *__dt__13TUnk_8048E728Fv(u8 *arg0, s16 arg1);
u8 *create_radial_particle(u8 *arg0, u8 *arg1, s32 arg2, u16 arg3, s16 arg4);
void *__dt__13TUnk_8048E7A8Fv(void *arg0, s16 arg1);
void TKeyBoardControl__sub_8000F91C(s32 arg0);
void TKeyBoardControl__sub_8000F9CC(s32 arg0);
void destroy_keyboard_objects(void * _w0);
s32 rand(void);
s32 is_split_screen();
s32 is_particle_sprite_additive__13TUnk_8048E728Fv(void *, s32);
s32 append_node_to_tail__13TParticleCtrlFPvPv(s32, void *);
s32 all_parents_unqueued_for_destruction__7TObjectFv();
s32 rotate_matrix_y(s32, s32);
s32 push_matrix(f32);
s32 pop_matrix();
s32 post_translate_matrix(void *);
s32 draw_ginja_object(u32);
s32 draw_ginja_model_with_motion(u32, u32, f32);
extern u8 *camera_ctrl_instance;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
f32 atan2_float(f32, f32);
f32 vector_length(void *);
void project_world_to_screen(s32, void *, void *);
static const Ang_8008BAF8 radial_particle_zero_angles = {0, 0, 0};
void __ct__7TObjectFP7TObject(void *, void *);
}
void * create_random_particle(void *arg0, void *arg1, void *arg2);
extern s32 TParticleCtrl__data_8048E7A8[];
void stop_cue_stream(void);
void *init_particle_base(void *arg0, void *arg1, s32 arg2);
extern RecoveredGlobal_8008C21C_TParticleCtrl__data_80511F70 TParticleCtrl__data_80511F70;
u8 *construct_radial_particle(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, u16 arg4, s16 arg5);
void setup_particle_tev(s32 arg0);
void load_projected_texture_matrix(f32 farg0);
void direction_to_rotation_xz(u8 *arg0, s32 *arg1, s32 *arg2);
extern void *__vt__13TParticleCtrl[];
extern s32 TParticleCtrl__class_name_descriptor;
extern void *tl_07;
extern void *tl_clipout;
extern const f32 TParticleCtrl__data_805D94E0;
extern const f32 TParticleCtrl__data_805D94E4;

#define COPY_PARTICLE_DIRECTION(particle, direction) do {                      \
    s32 component;                                                             \
    component = direction->x;                                                  \
    particle->direction.x = component;                                         \
    component = direction->z;                                                  \
    particle->direction.z = component;                                         \
    component = direction->y;                                                  \
    particle->direction.y = component;                                         \
} while (0)
#define CLEAR_PARTICLE_DIRECTION(particle, unused) do {                        \
    particle->direction.x = 0;                                                 \
    particle->direction.y = 0;                                                 \
    particle->direction.z = 0;                                                 \
} while (0)

#define INITIALIZE_PARTICLE(particle, position, particle_index, field30,       \
                            field34, field38, use_self, particle_flags,        \
                            direction_action, direction_source) do {           \
    __ct__7TObjectFP7TObject(particle, tl_07);                                 \
    particle->vtable = __vt__13TParticleCtrl;                                  \
    particle->descriptor = TParticleCtrl__class_name_descriptor;                       \
    particle->field4C = 0;                                                     \
    particle->field50 = 0;                                                     \
    particle->field54 = 0;                                                     \
    particle->field48 = 0;                                                     \
    particle->field40 = TParticleCtrl__data_805D94E4;                          \
    particle->field44 = TParticleCtrl__data_805D94E4;                          \
    particle->field1C = TParticleCtrl__data_805D94E0;                          \
    particle->field20 = 0;                                                     \
    particle->field24 = TParticleCtrl__data_805D94E4;                          \
    particle->particle_index = particle_index;                                 \
    VecCopy(&particle->position, position);                      \
    particle->flags = particle_flags;                                          \
    particle->field2E = 0xFFFF;                                                \
    direction_action(particle, direction_source);                              \
    particle->field30 = field30;                                               \
    particle->field34 = field34;                                               \
    particle->field38 = field38;                                               \
    particle->field3C = 0;                                                     \
    if (use_self != 0) {                                                       \
        particle->owner = particle;                                            \
    } else if (particle->flags & 0x800) {                                      \
        if (particle->flags & 0x4000) {                                        \
            particle->owner = tl_clipout;                                      \
        } else {                                                               \
            particle->owner = tl_07;                                           \
        }                                                                      \
    } else {                                                                   \
        particle->owner = tl_07;                                               \
    }                                                                          \
} while (0)

#include "pso/misc/TLobby.h"
#include "pso/misc/TOKeyMachine01.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {

u8 *create_radial_particle(u8 *arg0, u8 *arg1, s32 arg2, u16 arg3, s16 arg4) {
    u8 *particle_memory;
    u8 *var_r0;
    particle_memory = (u8 *)(((u8 *)alloc_particle_memory(0xC4)));
    var_r0 = particle_memory;
    if (var_r0 != NULL) {
        var_r0 = (u8 *)(construct_radial_particle(particle_memory, arg0, arg1, arg2, arg3, arg4));
    }
    return var_r0;
}
}
void * create_random_particle(void *arg0, void *arg1, void *arg2) {
    void *o;
    o = alloc_particle_memory(0xc4);
    if (o != NULL) {
        o = ((TParticleCtrl *)o)->init_random_particle((u8 *)arg0, (u8 *)arg1, (s32)arg2);
    }
    return o;
}

void TUnk_8048E7A8::check_radial_particle_retire() {
    u8 *arg0 = (u8 *)this;
    if ((this->m_58 >= 1.0f) || (0.0f == vec_squared_length((arg0 + 0x3C)))) {
        queue_destruction__7TObjectFv((arg0));
    }
}

// Views of the emitter and sprite records used by the radial update.
struct RadialEmitter {
    u8 reserved00[0x2C];
    f32 scale_decay;
    u8 reserved30[0x20];
    f32 speed_decay;
    u8 reserved54[4];
    f32 fade_in_end;
    f32 fade_out_start;
    u8 reserved60[0xC];
    f32 color_rate[3];
    u8 reserved78[4];
    f32 color_base[3];
    u8 flags;
};

struct RadialSpriteSet {
    u32 flags;
    u8 reserved04[8];
    s32 frame_count;
};

struct RadialSpriteTexture {
    u8 reserved00[0x28];
    RadialSpriteSet *sprites;
};

// The shared particle base still exposes the update fields as legacy slots.
struct RadialParticleUpdate {
    u8 object[0x1C];
    u16 sprite_index;
    u8 reserved1E[2];
    RadialEmitter *param;
    u16 flags;
    u16 target_id;
    f32 scale_x;
    f32 scale_y;
    Vec origin;
    Vec step;
    u8 reserved48[4];
    f32 color_base[3];
    f32 age;
    f32 age_rate;
    f32 fade_in_scale;
    f32 fade_out_scale;
    f32 speed;
    u8 reserved6C[4];
    Vec pos;
    Vec attach;
    u8 reserved88[8];
    u32 color;
    s8 frame;
    u8 reserved95[0x23];
    NJS_MOTION *motion;
    f32 motion_frame;
    f32 motion_rate;
};

typedef char RadialParticleUpdateSize[(sizeof(RadialParticleUpdate) == sizeof(TUnk_8048E7A8)) ? 1 : -1];
typedef char RadialParticlePositionOffset[(offsetof(RadialParticleUpdate, pos) == 0x70) ? 1 : -1];
typedef char RadialParticleMotionRateOffset[(offsetof(RadialParticleUpdate, motion_rate) == 0xC0) ? 1 : -1];

static inline RadialSpriteSet *radial_sprite_set(u16 index) {
    return reinterpret_cast<RadialSpriteTexture **>(&TParticleCtrl__data_80511F70)[index]->sprites;
}

static inline f32 fade_radial_channel(f32 value, f32 alpha) {
    return value < 0.0f ? 0.0f : alpha * (value < 1.0f ? value : 1.0f);
}

static inline f32 clamp_radial_channel(f32 value) {
    return value < 0.0f ? 0.0f : (value < 1.0f ? value : 1.0f);
}

union RadialColor {
    u32 color;
    struct { u8 a, r, g, b; } argb;
};

#pragma push
#pragma fp_contract on
void TUnk_8048E7A8::run_task() {
    RadialColor color;
    Vec target;
    f32 age_and_alpha[2]; // Age and minimum fade factor for this update.
    f32 fade_in;
    f32 fade_out;
    f32 remaining;
    f32 channels[3];
    RadialEmitter *param;
    s32 frames;
    u32 last_frame;
    RadialParticleUpdate &particle = *reinterpret_cast<RadialParticleUpdate *>(this);

    particle.speed *= particle.param->speed_decay;
    approach_vector_fixed_distance(&particle.pos, &particle.origin, &target, particle.speed);
    particle.step.x = target.x - particle.pos.x;
    particle.step.y = target.y - particle.pos.y;
    particle.step.z = target.z - particle.pos.z;
    vec3_add_to(&particle.pos, &particle.step);
    fade_in = 1.0f;
    fade_out = fade_in;
    particle.scale_x *= particle.param->scale_decay;
    particle.scale_y *= particle.param->scale_decay;
    particle.age += particle.age_rate;
    param = particle.param;
    age_and_alpha[0] = particle.age;
    if (param->fade_in_end > age_and_alpha[0]) {
        fade_in = age_and_alpha[0] * particle.fade_in_scale;
    }
    remaining = 1.0f - age_and_alpha[0];
    if (remaining < param->fade_out_start) {
        fade_out = remaining * particle.fade_out_scale;
    }
    age_and_alpha[1] = fade_in < fade_out ? fade_in : fade_out;

    // Additive sprites fade their RGB channels and keep full alpha.
    if (radial_sprite_set(particle.sprite_index)->flags & 1) {
        if (particle.flags & 0x100) {
            channels[0] = fade_radial_channel(
                param->color_rate[0] * age_and_alpha[0] + particle.color_base[0], age_and_alpha[1]);
            channels[1] = fade_radial_channel(
                param->color_rate[1] * age_and_alpha[0] + particle.color_base[1], age_and_alpha[1]);
            channels[2] = fade_radial_channel(
                param->color_rate[2] * age_and_alpha[0] + particle.color_base[2], age_and_alpha[1]);
        } else {
            channels[0] = fade_radial_channel(
                param->color_rate[0] * age_and_alpha[0] + param->color_base[0], age_and_alpha[1]);
            channels[1] = fade_radial_channel(
                param->color_rate[1] * age_and_alpha[0] + param->color_base[1], age_and_alpha[1]);
            channels[2] = fade_radial_channel(
                param->color_rate[2] * age_and_alpha[0] + param->color_base[2], age_and_alpha[1]);
        }
        age_and_alpha[1] = 1.0f;
    } else if (particle.flags & 0x100) {
        channels[0] = clamp_radial_channel(param->color_rate[0] * age_and_alpha[0] + particle.color_base[0]);
        channels[1] = clamp_radial_channel(param->color_rate[1] * age_and_alpha[0] + particle.color_base[1]);
        channels[2] = clamp_radial_channel(param->color_rate[2] * age_and_alpha[0] + particle.color_base[2]);
    } else {
        channels[0] = clamp_radial_channel(param->color_rate[0] * age_and_alpha[0] + param->color_base[0]);
        channels[1] = clamp_radial_channel(param->color_rate[1] * age_and_alpha[0] + param->color_base[1]);
        channels[2] = clamp_radial_channel(param->color_rate[2] * age_and_alpha[0] + param->color_base[2]);
    }

    color.argb.a = 254.0f * age_and_alpha[1];
    color.argb.r = 254.0f * channels[0];
    color.argb.g = 254.0f * channels[1];
    color.argb.b = 254.0f * channels[2];
    particle.color = color.color;
    frames = radial_sprite_set(particle.sprite_index)->frame_count;
    if (particle.param->flags & 0x10) {
        particle.frame = particle.age * (frames - 1);
    } else {
        particle.frame++;
        if (frames <= particle.frame) {
            particle.frame = 0;
        }
    }

    if (particle.flags & 0x10) {
        TObjCollidable *actor = find_entity_by_id(particle.target_id);
        if (actor == NULL) {
            queue_destruction__7TObjectFv(this);
            return;
        }
        const Vec *center = static_cast<const Vec *>(actor->get_center());
        particle.attach.x = center->x - particle.origin.x;
        particle.attach.y = center->y - particle.origin.y;
        particle.attach.z = center->z - particle.origin.z;
    }
    if (particle.motion != NULL) {
        particle.motion_frame += particle.motion_rate;
        last_frame = particle.motion->nbFrame - 1;
        if ((f32)last_frame <= particle.motion_frame) {
            particle.motion_frame = last_frame;
        }
    }
    check_radial_particle_retire();
}
#pragma pop

static const f64 radial_angle_units_per_radian = 10430.38043493439;

void TUnk_8048E7A8::render() {
    u8 *arg0 = (u8 *)this;
    Scr_8008BAF8 s1;
    Scr_8008BAF8 s2;
    Vec_8008BAF8 end;
    Vec_8008BAF8 pos;
    f32 len;
    u16 flags;
    if (all_parents_unqueued_for_destruction__7TObjectFv() == 0) {
        return;
    }
    if (*(u8 *)((s8 *)(*(u8 * *)&this->m_20) + 0x88) & 4) {
        if (*(u16 *)((s8 *)arg0 + 0x24) & 0x10) {
            pos.x = this->m_70 + *(f32 *)&this->unk_7C;
            pos.y = *(f32 *)&this->unk_74 + this->m_80;
            pos.z = this->m_78 + *(f32 *)&this->unk_84;
        } else {
            VecCopy((Vec *)&pos, (const Vec *)&this->m_70);
        }
        end.x = pos.x + this->m_3c;
        end.y = pos.y + *(f32 *)&this->unk_40;
        end.z = pos.z + this->m_44;
        len = vector_length((u8 *)&this->m_3c);
        if (0.0f == len) {
            return;
        }
        project_world_to_screen(0, &pos, &s1);
        project_world_to_screen(0, &end, &s2);
        s2.x = s2.x - s1.x;
        s2.y = s2.y - s1.y;
        this->m_96 = (s16)(radial_angle_units_per_radian * atan2_float(s2.y, s2.x));
        this->m_88 = *(f32 *)((s8 *)(*(u8 * *)&this->m_20) + 0x60) * len;
        *(f32 *)((s8 *)arg0 + 0x8C) = *(f32 *)((s8 *)(*(u8 * *)&this->m_20) + 0x64) * len;
    } else {
        this->m_88 = this->m_28;
        *(f32 *)((s8 *)arg0 + 0x8C) = *(f32 *)&this->unk_2C;
    }
    this->m_88 = this->m_88 * this->m_a4;
    *(f32 *)((s8 *)arg0 + 0x8C) = *(f32 *)((s8 *)arg0 + 0x8C) * *(f32 *)((s8 *)arg0 + 0xA8);
    flags = *(u16 *)((s8 *)arg0 + 0x24);
    if (flags & 0x200) {
        if (((is_split_screen() == 0) || !(*(u16 *)((s8 *)arg0 + 0x24) & 0x400)) && (*(u32 *)&this->unk_B4 != 0U) && (this->m_b0 != 0U)) {
            Ang_8008BAF8 ang = radial_particle_zero_angles;
            Vec_8008BAF8 pos2;
            direction_to_rotation_xz((u8 *)&this->m_3c, &ang.x, &ang.z);
            if (*(u8 *)((s8 *)(*(u8 * *)&this->m_20) + 0x88) & 4) {
                pos2.x = this->m_70 + *(f32 *)&this->unk_7C;
                pos2.y = *(f32 *)&this->unk_74 + this->m_80;
                pos2.z = this->m_78 + *(f32 *)&this->unk_84;
            } else {
                VecCopy((Vec *)&pos2, (const Vec *)&this->m_70);
            }
            ((void (*)(void))push_matrix)();
            post_translate_matrix(&pos2);
            scale_matrix(0, this->m_88, this->m_88, this->m_88);
            if (*(u8 *)((s8 *)(*(u8 * *)&this->m_20) + 0x88) & 4) {
                rotate_matrix_z(0, ang.z);
                rotate_matrix_x(0, ang.x);
                rotate_matrix_y(0, ang.y);
            }
            if ((*(u16 *)((s8 *)arg0 + 0x24) & 0x1000) && (camera_ctrl_instance != NULL)) {
                rotate_matrix_y(0, *(s32 *)((s8 *)camera_ctrl_instance + 0x194));
            }
            TParticleCtrl::begin_effect_render();
            if (*(u16 *)((s8 *)arg0 + 0x24) & 0x400) {
                load_projected_texture_matrix(1.33f);
            }
            rotate_matrix_y(0, this->m_96);
            if (*(u16 *)((s8 *)arg0 + 0x24) & 0x400) {
                setup_particle_tev(0);
            } else {
                s32 temp_r4 = model_render_flags;
                saved_model_render_flags = temp_r4;
                model_render_flags = temp_r4 | 0x8021;
                if (is_particle_sprite_additive__13TUnk_8048E728Fv(arg0, temp_r4) != 0) {
                    ((TUnk_8048E728 *)arg0)->apply_particle_model_fade_color(1);
                } else {
                    ((TUnk_8048E728 *)arg0)->apply_particle_model_fade_color(0);
                }
            }
            set_current_texture_list((GinjaTextureList *)(*(u32 *)&this->unk_B4));
            set_draw_list_mask(3);
            if (this->m_b8 != 0U) {
                draw_ginja_model_with_motion(this->m_b0, this->m_b8, *(f32 *)&this->unk_BC);
            } else {
                draw_ginja_object(this->m_b0);
            }
            if (*(u16 *)((s8 *)arg0 + 0x24) & 0x400) {
                reset_particle_tev();
            } else {
                model_render_flags = saved_model_render_flags;
            }
            TParticleCtrl::end_effect_render();
            pop_matrix();
        }
    } else {
        if (flags & 0x2000) {
            ((TUnk_8048E728 *)arg0)->draw_particle_refraction_quad();
            return;
        }
        if (*(u8 *)((s8 *)this->m_20 + 0x88) & 0x20) {
            append_node_to_tail__13TParticleCtrlFPvPv(((s32 *)((u8 *)&TParticleCtrl__data_80511F70 + 0xD8))[*(u16 *)((s8 *)arg0 + 0x1C)], arg0 + 0x6C);
            return;
        }
        append_node_to_tail__13TParticleCtrlFPvPv(((s32 *)&TParticleCtrl__data_80511F70)[*(u16 *)((s8 *)arg0 + 0x1C)], arg0 + 0x6C);
    }
}

void *__dt__13TUnk_8048E7A8Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = TParticleCtrl__data_8048E7A8;
        __dt__13TUnk_8048E728Fv((u8 *)arg0, 0);
        if (arg1 > 0) {
            ((TUnk_8048E728 *)arg0)->free_from_heap();
        }
    }
    return arg0;
}

#pragma push
#pragma fp_contract on
typedef char RecoveredGlobal_8008C21C_TParticleCtrl__data_8048E7A8_size[sizeof(RecoveredGlobal_8008C21C_TParticleCtrl__data_8048E7A8) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8008C21C_TParticleCtrl__data_80511F70_size[sizeof(RecoveredGlobal_8008C21C_TParticleCtrl__data_80511F70) == 0x1B0 ? 1 : -1];

#pragma push
#pragma fp_contract on
typedef char RecoveredGlobal_8008BF58_TParticleCtrl__data_8048E7A8_size[sizeof(RecoveredGlobal_8008BF58_TParticleCtrl__data_8048E7A8) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8008BF58_TParticleCtrl__data_80511F70_size[sizeof(RecoveredGlobal_8008BF58_TParticleCtrl__data_80511F70) == 0x1B0 ? 1 : -1];
static const f32 radial_rand_scale = 1.0f / 32768.0f;

u8 *construct_radial_particle(u8 *object, u8 *arg1, u8 *arg2, s32 arg3, u16 arg4, s16 arg5) {
    struct Fields_arg0 { u8 pad_0[24]; s32 * field_18; u16 field_1C; u8 pad_1E[6]; u16 field_24; s16 field_26; f32 field_28; f32 field_2C; f32 field_30; f32 field_34; f32 field_38; f32 field_3C; f32 field_40; f32 field_44; u8 pad_48[20]; f32 field_5C; u8 pad_60[8]; f32 field_68; u8 pad_6C[4]; f32 field_70; f32 field_74; f32 field_78; u8 pad_7C[25]; s8 field_95; };
    struct Fields_arg1 { u8 pad_0[24]; f32 field_18; f32 field_1C; f32 field_20; f32 field_24; f32 field_28; u8 pad_2C[4]; f32 field_30; u8 pad_34[4]; f32 field_38; u8 pad_3C[12]; s32 field_48; s32 field_4C; u8 pad_50[56]; u8 field_88; };
    struct Fields_arg2 { f32 field_0; f32 field_4; f32 field_8; };
    s32 temp_r0;
    init_particle_base(object, arg1, arg3);
    ((Fields_arg0*)object)->field_18 = &(*(RecoveredGlobal_8008BF58_TParticleCtrl__data_8048E7A8 *)&TParticleCtrl__data_8048E7A8).value;
    ((Fields_arg0*)object)->field_70 = (f32) ((((Fields_arg1*)arg1)->field_18 * ((radial_rand_scale * (f32) rand()) - 0.5f)) + ((Fields_arg2*)arg2)->field_0);
    ((Fields_arg0*)object)->field_74 = (f32) ((((Fields_arg1*)arg1)->field_1C * ((radial_rand_scale * (f32) rand()) - 0.5f)) + ((Fields_arg2*)arg2)->field_4);
    ((Fields_arg0*)object)->field_78 = (f32) ((((Fields_arg1*)arg1)->field_20 * ((radial_rand_scale * (f32) rand()) - 0.5f)) + ((Fields_arg2*)arg2)->field_8);
    ((Fields_arg0*)object)->field_24 = arg4;
    if (((Fields_arg0*)object)->field_24 & 0x80) {
        ((Fields_arg0*)object)->field_95 = 1;
    }
    ((Fields_arg0*)object)->field_26 = arg5;
    ((Fields_arg0*)object)->field_30 = (f32) ((Fields_arg2*)arg2)->field_0;
    ((Fields_arg0*)object)->field_34 = (f32) ((Fields_arg2*)arg2)->field_4;
    ((Fields_arg0*)object)->field_38 = (f32) ((Fields_arg2*)arg2)->field_8;
    ((Fields_arg0*)object)->field_28 = (f32) ((((Fields_arg1*)arg1)->field_28 * (radial_rand_scale * (f32) rand())) + ((Fields_arg1*)arg1)->field_24);
    ((Fields_arg0*)object)->field_2C = (f32) ((Fields_arg0*)object)->field_28;
    temp_r0 = (s32) (((f32) ((Fields_arg1*)arg1)->field_4C * (radial_rand_scale * (f32) rand())) + (f32) ((Fields_arg1*)arg1)->field_48);
    if (((Fields_arg1*)arg1)->field_88 & 1) {
        ((Fields_arg0*)object)->field_5C = (f32) (1.0f / (f32) *(s32 *)((s8 *)(*(void **)((s8 *)(*(s32 *)((s8 *)(&(*(RecoveredGlobal_8008BF58_TParticleCtrl__data_80511F70 *)&TParticleCtrl__data_80511F70).value) + (((Fields_arg0*)object)->field_1C * 4))) + 0x28)) + 0xC));
    } else {
        ((Fields_arg0*)object)->field_5C = (f32) (1.0f / (f32) temp_r0);
    }
    ((Fields_arg0*)object)->field_68 = (f32) ((((Fields_arg1*)arg1)->field_38 * (radial_rand_scale * (f32) rand())) + ((Fields_arg1*)arg1)->field_30);
    ((Fields_arg0*)object)->field_3C = (f32) 0.0f;
    ((Fields_arg0*)object)->field_40 = (f32) 0.0f;
    ((Fields_arg0*)object)->field_44 = (f32) 0.0f;
    if (((Fields_arg0*)object)->field_24 & 0x2000) {
        request_indirect_effect(0x1F);
    }
    return object;
}
#pragma pop

u8 *TParticleCtrl::init_random_particle(u8 *arg1, u8 *arg2, s32 arg3) {
    struct Fields_arg0 { u8 pad_0[24]; s32 * field_18; u16 field_1C; u8 pad_1E[6]; u16 field_24; u8 pad_26[2]; f32 field_28; f32 field_2C; f32 field_30; f32 field_34; f32 field_38; f32 field_3C; f32 field_40; f32 field_44; u8 pad_48[20]; f32 field_5C; u8 pad_60[8]; f32 field_68; u8 pad_6C[4]; f32 field_70; f32 field_74; f32 field_78; };
    struct Fields_arg1 { u8 pad_0[24]; f32 field_18; f32 field_1C; f32 field_20; f32 field_24; f32 field_28; u8 pad_2C[4]; f32 field_30; u8 pad_34[4]; f32 field_38; u8 pad_3C[12]; s32 field_48; s32 field_4C; u8 pad_50[56]; u8 field_88; };
    struct Fields_arg2 { f32 field_0; f32 field_4; f32 field_8; };
    s32 temp_r0;
    init_particle_base(this, arg1, arg3);
    ((Fields_arg0*)((u8 *)this))->field_18 = &(*(RecoveredGlobal_8008C21C_TParticleCtrl__data_8048E7A8 *)&TParticleCtrl__data_8048E7A8).value;
    ((Fields_arg0*)((u8 *)this))->field_70 = (f32) ((((Fields_arg1*)arg1)->field_18 * ((radial_rand_scale * (f32) rand()) - 0.5f)) + ((Fields_arg2*)arg2)->field_0);
    ((Fields_arg0*)((u8 *)this))->field_74 = (f32) ((((Fields_arg1*)arg1)->field_1C * ((radial_rand_scale * (f32) rand()) - 0.5f)) + ((Fields_arg2*)arg2)->field_4);
    ((Fields_arg0*)((u8 *)this))->field_78 = (f32) ((((Fields_arg1*)arg1)->field_20 * ((radial_rand_scale * (f32) rand()) - 0.5f)) + ((Fields_arg2*)arg2)->field_8);
    ((Fields_arg0*)((u8 *)this))->field_30 = (f32) ((Fields_arg2*)arg2)->field_0;
    ((Fields_arg0*)((u8 *)this))->field_34 = (f32) ((Fields_arg2*)arg2)->field_4;
    ((Fields_arg0*)((u8 *)this))->field_38 = (f32) ((Fields_arg2*)arg2)->field_8;
    ((Fields_arg0*)((u8 *)this))->field_28 = (f32) ((((Fields_arg1*)arg1)->field_28 * (radial_rand_scale * (f32) rand())) + ((Fields_arg1*)arg1)->field_24);
    ((Fields_arg0*)((u8 *)this))->field_2C = (f32) ((Fields_arg0*)((u8 *)this))->field_28;
    temp_r0 = (s32) (((f32) ((Fields_arg1*)arg1)->field_4C * (radial_rand_scale * (f32) rand())) + (f32) ((Fields_arg1*)arg1)->field_48);
    if (((Fields_arg1*)arg1)->field_88 & 1) {
        ((Fields_arg0*)((u8 *)this))->field_5C = (f32) (1.0f / (f32) *(s32 *)((s8 *)(*(void **)((s8 *)(*(s32 *)((s8 *)&TParticleCtrl__data_80511F70.value + (((Fields_arg0*)((u8 *)this))->field_1C * 4))) + 0x28)) + 0xC));
    } else {
        ((Fields_arg0*)((u8 *)this))->field_5C = (f32) (1.0f / (f32) temp_r0);
    }
    ((Fields_arg0*)((u8 *)this))->field_68 = (f32) ((((Fields_arg1*)arg1)->field_38 * (radial_rand_scale * (f32) rand())) + ((Fields_arg1*)arg1)->field_30);
    ((Fields_arg0*)((u8 *)this))->field_3C = (f32) 0.0f;
    ((Fields_arg0*)((u8 *)this))->field_40 = (f32) 0.0f;
    ((Fields_arg0*)((u8 *)this))->field_44 = (f32) 0.0f;
    if (((Fields_arg0*)((u8 *)this))->field_24 & 0x2000) {
        request_indirect_effect(0x1F);
    }
    return ((u8 *)this);
}
#pragma pop

void destroy_keyboard_objects(void * _w0) { queue_destruction__7TObjectFv((_w0)); TKeyBoardControl__sub_8000F91C(2); TKeyBoardControl__sub_8000F9CC(18); TLobby::stop_audio_streams(); stop_cue_stream(); }
