#include "types.h"
#include "pso/effect/TEF_PvrWave.h"
#include "pso/effect/TEF_LensFlare.h"

#include "pso/TMainTask.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/vector.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/math/MatrixVector.h"
#include "pso/render/render_util.h"
#include <stddef.h>

// 8008172C..80081870 advances these records by 0x18, consuming offsets
// 0,4,8,C,10. The table contains ten records; this draw consumes nine.
struct LensFlareElement {
    s32 texture;
    f32 displacement;
    f32 scale;
    f32 attenuation;
    f32 alpha;
    f32 reserved;
};
struct LensFlareSpriteDefinition {
    u32 flags;
    GinjaTextureList *texture_list;
    s32 texture;
    s32 count;
    const f32 *uvs;
    f32 width;
    f32 height;
    u32 color;
    s32 reserved[2];
};
union LensFlareColor {
    u32 packed;
    struct { u8 a, r, g, b; } channels;
};
// Matches the sprite-node layout consumed by TQuadSpriteSclColRot::render.
// The link and type byte are unused in this stack scratch; do not initialize
// or dereference them to manufacture observable effects.
struct LensFlareSprite {
    LensFlareSprite *next;
    Vec position;
    f32 reserved[3];
    f32 scale_x, scale_y;
    u32 color;
    u8 flags;
    u8 type;
    u16 angle;
};
typedef char LensFlareElementSize[sizeof(LensFlareElement) == 0x18 ? 1 : -1];
typedef char LensFlareDefinitionSize[sizeof(LensFlareSpriteDefinition) == 0x28 ? 1 : -1];
typedef char LensFlareSpriteSize[sizeof(LensFlareSprite) == 0x2C ? 1 : -1];
typedef char LensFlareScaleOffset[offsetof(LensFlareSprite, scale_x) == 0x1C ? 1 : -1];
typedef char LensFlareColorOffset[offsetof(LensFlareSprite, color) == 0x24 ? 1 : -1];
extern "C" {
extern TCameraCtrl *camera_ctrl_instance;
extern LensFlareSpriteDefinition lbl_804C5820[];
extern const Vec lbl_80438E40;
f32 vec3_dot(const Vec *, const Vec *);
s32 normalize_vector(Vec *);
extern const f32 lbl_805D9338;
extern const f32 lbl_805D933C;
extern const f32 lbl_805D9340;
extern const f32 lbl_805D9344;
extern const f32 lbl_805D9348;
extern const f32 lbl_805D934C;
extern const f32 lbl_805D9350;
extern const f32 lbl_805D9354;
extern const f32 lbl_805D9358;
extern const f32 lbl_805D935C;
extern const f32 lbl_805D9360;
extern const f32 lbl_805D9364;
extern const f32 lbl_805D9368;
extern const f32 lbl_805D936C;
extern const f32 lbl_805D9370;
}

struct Base_8008194C_80081278 { char pad[0x50]; };
struct VObj_8008194C_80081278 : Base_8008194C_80081278 {
    virtual void m0();
    virtual void m1();
};

struct RecoveredGlobal_800818D8_lbl_8048E040 {
    s32 value;
    u8 remaining[0xEC];
};

struct RecoveredGlobal_800818D8_lbl_8048E130 {
    s32 value;
    u8 remaining[0x34];
};

extern "C" {
s32 __ct__8TObjBaseFP7TObject(void *, void *);
extern RecoveredGlobal_800818D8_lbl_8048E040 lens_flare_reflected_element_descriptors;
extern s32 __vt__13TEF_LensFlare[];
extern s32 TEF_LensFlare__class_name;
u8 *TEF_LensFlare__ct(u8 *arg0, s32 arg1, s32 arg2);
void *__dt__13TEF_LensFlareFv(void *arg0, s16 arg1);
void __dl__7TObjectFPv(void *);

}
TEF_LensFlare::~TEF_LensFlare() {

}

#pragma push
#pragma fp_contract on
void TEF_LensFlare::render() {
    if (TMainTask::get_render_pass() != 0 && camera_ctrl_instance != NULL) {
        LensFlareSprite sprite_storage;
        Vec *sprite_position;
        LensFlareSprite *sprite = &sprite_storage;
        sprite->position.x = lbl_805D9338; sprite->position.y = lbl_805D9338; sprite->position.z = lbl_805D9338;
        sprite->reserved[0] = lbl_805D9338; sprite->reserved[1] = lbl_805D9338; sprite->reserved[2] = lbl_805D9338;
        sprite->scale_x = lbl_805D9338; sprite->scale_y = lbl_805D9338;
        sprite->color = 0; sprite->flags = 0; sprite->angle = 0;
        sprite_position = &sprite_storage.position;
        set_additive_blend();
        if (scale.x >= lbl_805D9338) {
            f32 radius = lbl_805D933C * scale.x;
            if (is_player_near(radius * radius)) return;
        }
        TParticleCtrl::begin_effect_render();
        Vec direction;
        direction.x = position.x - camera_ctrl_instance->m_178;
        direction.y = position.y - camera_ctrl_instance->m_17c;
        direction.z = position.z - camera_ctrl_instance->m_180;
        if (lbl_805D9338 != vec_squared_length(&direction)) normalize_vector(&direction);
        push_matrix_from(identity_matrix);
        Vec facing;
        Vec forward = lbl_80438E40;
        rotate_matrix_y(NULL, camera_ctrl_instance->m_194);
        rotate_matrix_x(NULL, camera_ctrl_instance->m_190);
        rotate_vector_by_matrix(0, &forward, &facing);
        pop_matrix();
        f32 alignment = vec3_dot(&facing, &direction);
        if (alignment > lbl_805D9338) {
            set_depth_buffer_settings_1();
            f32 screen[2];
            project_world_to_screen(NULL, &position, screen);
            Vec point;
            if (alignment > lbl_805D9340) {
                f32 glow = lbl_805D9344 * (alignment - lbl_805D9348);
                glow *= glow;
                LensFlareColor color;
                color.channels.a = (s32)(lbl_805D934C * (lbl_805D9350 * glow));
                color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
                point.x = screen[0]; point.y = screen[1]; point.z = lbl_805D9338;
                sprite->color = color.packed;
                VecCopy(sprite_position, &point);
                sprite->scale_x = lbl_805D9354 * glow; sprite->scale_y = sprite->scale_x;
                begin_screen_draw(1);
                set_current_texture_list(lbl_804C5820[15].texture_list);
                set_draw_texture_and_color(lbl_804C5820[15].texture, -1);
                f32 x = point.x;
                f32 y = point.y;
                f32 half_width = lbl_804C5820[15].width;
                f32 half_height = lbl_804C5820[15].height;
                f32 sx = lbl_805D9358 * sprite->scale_x;
                f32 sy = lbl_805D9358 * sprite->scale_y;
                half_width *= sx; half_height *= sy;
                f32 quad[8];
                quad[0] = x - half_width; quad[2] = x + half_width;
                quad[1] = y - half_height; quad[3] = y + half_height;
                quad[4] = lbl_805D9338; quad[5] = lbl_805D9338;
                quad[6] = lbl_805D935C; quad[7] = lbl_805D935C;
                set_constant_material_color(sprite->color);
                draw_textured_quad_at_depth(quad, lbl_805D9360);
                TWindowSubStatusDisp::get_player();
            }
            f32 strength;
            if (alignment > lbl_805D9368) strength = lbl_805D9364 * (alignment - lbl_805D9368);
            else strength = lbl_805D9338;
            strength = strength * (strength * (strength * strength));
            f32 center_x = lbl_805D936C - screen[0];
            f32 center_y = lbl_805D9370 - screen[1];
            LensFlareColor color;
            color.channels.a = 255; color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
            point.x = screen[0]; point.y = screen[1]; point.z = lbl_805D9338;
            sprite->color = color.packed;
            VecCopy(sprite_position, &point);
            sprite->scale_x = lbl_805D935C; sprite->scale_y = sprite->scale_x;
            begin_screen_draw(1);
            set_current_texture_list(lbl_804C5820[9].texture_list);
            set_draw_texture_and_color(lbl_804C5820[9].texture, -1);
            f32 x = point.x;
            f32 y = point.y;
            f32 half_width = lbl_804C5820[9].width;
            f32 half_height = lbl_804C5820[9].height;
            f32 sx = lbl_805D9358 * sprite->scale_x;
            f32 sy = lbl_805D9358 * sprite->scale_y;
            half_width *= sx; half_height *= sy;
            f32 quad[8];
            quad[0] = x - half_width; quad[2] = x + half_width;
            quad[1] = y - half_height; quad[3] = y + half_height;
            quad[4] = lbl_805D9338; quad[5] = lbl_805D9338;
            quad[6] = lbl_805D935C; quad[7] = lbl_805D935C;
            set_constant_material_color(sprite->color);
            draw_textured_quad_at_depth(quad, lbl_805D9360);
            TWindowSubStatusDisp::get_player();
            LensFlareElement *element = elements;
            f32 one = lbl_805D935C;
            f32 inverse_strength = one - strength;
            f32 zero = lbl_805D9338;
            s32 i = 1;
            do {
                f32 size = element->scale * (one - inverse_strength * element->attenuation);
                if (size < zero) size = zero;
                LensFlareColor color;
                // fctiwz followed by stb: signed truncation, then low-byte wrapping.
                color.channels.a = (s32)(lbl_805D934C * (strength * element->alpha));
                color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
                sprite->color = color.packed;
                point.x = center_x * element->displacement + screen[0];
                point.y = center_y * element->displacement + screen[1];
                point.z = zero;
                VecCopy(sprite_position, &point);
                sprite->scale_x = size; sprite->scale_y = sprite->scale_x;
                begin_screen_draw(1);
                set_current_texture_list(lbl_804C5820[9 + element->texture].texture_list);
                set_draw_texture_and_color(lbl_804C5820[9 + element->texture].texture, -1);
                f32 x = point.x;
                f32 y = point.y;
                f32 half_width = lbl_804C5820[9 + element->texture].width;
                f32 half_height = lbl_804C5820[9 + element->texture].height;
                f32 sx = lbl_805D9358 * sprite->scale_x;
                f32 sy = lbl_805D9358 * sprite->scale_y;
                half_width *= sx; half_height *= sy;
                f32 quad[8];
                quad[0] = x - half_width; quad[2] = x + half_width;
                quad[1] = y - half_height; quad[3] = y + half_height;
                quad[4] = zero; quad[5] = zero;
                quad[6] = one; quad[7] = one;
                set_constant_material_color(sprite->color);
                draw_textured_quad_at_depth(quad, lbl_805D9360);
                TWindowSubStatusDisp::get_player();
                ++element;
            } while (i++ < 9);
            restore_saved_depth_alpha_state();
        }
        TParticleCtrl::end_effect_render();
    }
}
#pragma pop

extern "C" {

typedef char RecoveredGlobal_800818D8_lbl_8048E040_size[sizeof(RecoveredGlobal_800818D8_lbl_8048E040) == 0xF0 ? 1 : -1];
typedef char RecoveredGlobal_800818D8_lbl_8048E130_size[sizeof(RecoveredGlobal_800818D8_lbl_8048E130) == 0x38 ? 1 : -1];
u8 *TEF_LensFlare__ct(u8 *ef_lens_flare, s32 parent, s32 arg2) {
    __ct__8TObjBaseFP7TObject((void *)ef_lens_flare, (void *)parent);
    *(s32 **)((s8 *)ef_lens_flare + 0x18) = &(*(RecoveredGlobal_800818D8_lbl_8048E130 *)&__vt__13TEF_LensFlare).value;
    *(s32 *)((s8 *)ef_lens_flare + 0) = (s32) TEF_LensFlare__class_name;
    ((TEF_LensFlare *)(ef_lens_flare))->apply_object_set_data((void *)arg2);
    *(s32 **)((s8 *)ef_lens_flare + 0x90) = &lens_flare_reflected_element_descriptors.value;
    return ef_lens_flare;
}

void TEF_LensFlare::run_task() {  }
void TEF_PvrWave::render() {  }

void TEF_PvrWave::run_task() {
    struct VObj_8008194C_80081278 *o = (struct VObj_8008194C_80081278 *)*(void **)((s8 *)this + 0x1C);
    o->m1();
}

}
