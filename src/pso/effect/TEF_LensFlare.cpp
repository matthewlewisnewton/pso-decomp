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
// Convert through signed int before truncating to the eight-bit field. This
// preserves fctiwz/stb wrapping without a float-to-unsigned-byte range assumption.
union LensFlareGlareColor {
    u32 packed;
    struct { signed int a:8; u8 r, g, b; } channels;
};
typedef char LensFlareGlareColorSize[sizeof(LensFlareGlareColor) == 4 ? 1 : -1];
typedef char LensFlareGlareColorRGBOffsets[offsetof(LensFlareGlareColor, channels.r) == 1 &&
    offsetof(LensFlareGlareColor, channels.g) == 2 &&
    offsetof(LensFlareGlareColor, channels.b) == 3 ? 1 : -1];
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
f32 normalize_vector(Vec *);
}

struct Base_8008194C_80081278 { char pad[0x50]; };
struct VObj_8008194C_80081278 : Base_8008194C_80081278 {
    virtual void m0();
    virtual void m1();
};

extern "C" {
s32 __ct__8TObjBaseFP7TObject(void *, void *);
extern LensFlareElement lens_flare_reflected_element_descriptors[10];
extern s32 __vt__13TEF_LensFlare[];
extern const char *TEF_LensFlare__class_name;
u8 *TEF_LensFlare__ct(u8 *arg0, s32 arg1, s32 arg2);
void *__dt__13TEF_LensFlareFv(void *arg0, s16 arg1);
void __dl__7TObjectFPv(void *);

}
extern "C" {
extern const char TEF_LensFlare__class_name_string[] = "TEF_LensFlare";
const char *TEF_LensFlare__class_name = TEF_LensFlare__class_name_string;

// Static configuration, not frame data. The final word of each entry is
// retained as a float even though this renderer does not consume it.
LensFlareElement lens_flare_reflected_element_descriptors[10] = {
    {1, 0.1f, 0.8f, 0.0f, 0.7f, -10.0f},
    {2, 0.4f, 0.6f, 0.5f, 0.7f, -10.1f},
    {3, 0.6f, 0.8f, 0.6f, 0.7f, -10.2f},
    {1, 0.8f, 1.2f, 0.6f, 0.4f, -10.3f},
    {3, 1.0f, 1.2f,-0.3f, 0.7f, -10.4f},
    {4, 1.2f, 0.7f, 1.0f, 0.7f, -10.5f},
    {2, 1.4f, 1.7f, 0.0f, 0.7f, -10.6f},
    {5, 1.5f, 0.6f, 1.0f, 0.7f, -10.7f},
    {6, 1.8f, 1.5f, 0.0f, 0.7f, -10.8f},
    {2, 0.0f, 4.0f, 2.0f, 0.4f, -10.9f},
};
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
        sprite->position.x = 0.0f; sprite->position.y = 0.0f; sprite->position.z = 0.0f;
        sprite->reserved[0] = 0.0f; sprite->reserved[1] = 0.0f; sprite->reserved[2] = 0.0f;
        sprite->scale_x = 0.0f; sprite->scale_y = 0.0f;
        sprite->color = 0; sprite->flags = 0; sprite->angle = 0;
        sprite_position = &sprite_storage.position;
        set_additive_blend();
        if (scale.x >= 0.0f) {
            f32 radius = 10.0f * scale.x;
            if (is_player_near(radius * radius)) return;
        }
        TParticleCtrl::begin_effect_render();
        Vec direction;
        direction.x = position.x - camera_ctrl_instance->m_178;
        direction.y = position.y - camera_ctrl_instance->m_17c;
        direction.z = position.z - camera_ctrl_instance->m_180;
        if (0.0f != vec_squared_length(&direction)) normalize_vector(&direction);
        push_matrix_from(identity_matrix);
        Vec facing;
        Vec forward = lbl_80438E40;
        rotate_matrix_y(NULL, camera_ctrl_instance->m_194);
        rotate_matrix_x(NULL, camera_ctrl_instance->m_190);
        rotate_vector_by_matrix(0, &forward, &facing);
        pop_matrix();
        f32 center_x, center_y, inverse_strength, strength;
        f32 alignment = vec3_dot(&facing, &direction);
        if (alignment > 0.0f) {
            set_depth_buffer_settings_1();
            f32 screen[2];
            project_world_to_screen(NULL, &position, screen);
            Vec point;
            if (alignment > 0.99f) {
                f32 glow = 50.0f * (alignment - 0.98f);
                glow *= glow;
                LensFlareGlareColor color;
                color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
                color.channels.a = 255.0f * (0.9f * glow);
                point.x = screen[0]; point.y = screen[1]; point.z = 0.0f;
                sprite->color = color.packed;
                VecCopy(sprite_position, &point);
                sprite->scale_x = 20.0f * glow; sprite->scale_y = sprite->scale_x;
                begin_screen_draw(1);
                set_current_texture_list(lbl_804C5820[15].texture_list);
                set_draw_texture_and_color(lbl_804C5820[15].texture, -1);
                f32 x = point.x;
                f32 y = point.y;
                f32 half_width = lbl_804C5820[15].width;
                f32 half_height = lbl_804C5820[15].height;
                f32 sx = 2.0f * sprite->scale_x;
                f32 sy = 2.0f * sprite->scale_y;
                half_width *= sx; half_height *= sy;
                f32 quad[8];
                quad[0] = x - half_width; quad[2] = x + half_width;
                quad[1] = y - half_height; quad[3] = y + half_height;
                quad[4] = 0.0f; quad[5] = 0.0f;
                quad[6] = 1.0f; quad[7] = 1.0f;
                set_constant_material_color(sprite->color);
                draw_textured_quad_at_depth(quad, 0.5f);
                TWindowSubStatusDisp::get_player();
            }

            if (alignment > 0.6f) strength = 3.0f * (alignment - 0.6f);
            else strength = 0.0f;
            strength *= strength * strength * strength;
            center_x = 320.0f - screen[0];
            center_y = 240.0f - screen[1];
            LensFlareColor color;
            color.channels.a = 255; color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
            point.x = screen[0]; point.y = screen[1]; point.z = 0.0f;
            sprite->color = color.packed;
            VecCopy(sprite_position, &point);
            sprite->scale_x = 1.0f; sprite->scale_y = sprite->scale_x;
            begin_screen_draw(1);
            set_current_texture_list(lbl_804C5820[9].texture_list);
            set_draw_texture_and_color(lbl_804C5820[9].texture, -1);
            f32 x = point.x;
            f32 y = point.y;
            f32 half_width = lbl_804C5820[9].width;
            f32 half_height = lbl_804C5820[9].height;
            f32 sx = 2.0f * sprite->scale_x;
            f32 sy = 2.0f * sprite->scale_y;
            half_width *= sx; half_height *= sy;
            f32 quad[8];
            quad[0] = x - half_width; quad[2] = x + half_width;
            quad[1] = y - half_height; quad[3] = y + half_height;
            quad[4] = 0.0f; quad[5] = 0.0f;
            quad[6] = 1.0f; quad[7] = 1.0f;
            set_constant_material_color(sprite->color);
            draw_textured_quad_at_depth(quad, 0.5f);
            TWindowSubStatusDisp::get_player();
            LensFlareElement *element = elements;
            inverse_strength = 1.0f - strength;
            s32 i = 1;
            do {
                f32 size = element->scale * (1.0f - inverse_strength * element->attenuation);
                if (size < 0.0f) size = 0.0f;
                LensFlareColor color;
                // fctiwz followed by stb: signed truncation, then low-byte wrapping.
                color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
                color.channels.a = (s32)(255.0f * (strength * element->alpha));
                sprite->color = color.packed;
                point.x = center_x * element->displacement + screen[0];
                point.y = center_y * element->displacement + screen[1];
                point.z = 0.0f;
                VecCopy(sprite_position, &point);
                sprite->scale_x = size; sprite->scale_y = sprite->scale_x;
                begin_screen_draw(1);
                set_current_texture_list(lbl_804C5820[9 + element->texture].texture_list);
                set_draw_texture_and_color(lbl_804C5820[9 + element->texture].texture, -1);
                f32 x = point.x;
                f32 y = point.y;
                f32 half_width = lbl_804C5820[9 + element->texture].width;
                f32 half_height = lbl_804C5820[9 + element->texture].height;
                f32 sx = 2.0f * sprite->scale_x;
                f32 sy = 2.0f * sprite->scale_y;
                half_width *= sx; half_height *= sy;
                f32 quad[8];
                quad[0] = x - half_width; quad[2] = x + half_width;
                quad[1] = y - half_height; quad[3] = y + half_height;
                quad[4] = 0.0f; quad[5] = 0.0f;
                quad[6] = 1.0f; quad[7] = 1.0f;
                set_constant_material_color(sprite->color);
                draw_textured_quad_at_depth(quad, 0.5f);
                TWindowSubStatusDisp::get_player();
            } while ((++element, i++) < 9);
            restore_saved_depth_alpha_state();
        }
        TParticleCtrl::end_effect_render();
    }
}
#pragma pop

extern "C" {

u8 *TEF_LensFlare__ct(u8 *ef_lens_flare, s32 parent, s32 arg2) {
    __ct__8TObjBaseFP7TObject((void *)ef_lens_flare, (void *)parent);
    *(s32 **)((s8 *)ef_lens_flare + 0x18) = __vt__13TEF_LensFlare;
    ((TEF_LensFlare *)ef_lens_flare)->m_name = TEF_LensFlare__class_name;
    ((TEF_LensFlare *)(ef_lens_flare))->apply_object_set_data((void *)arg2);
    ((TEF_LensFlare *)ef_lens_flare)->elements = lens_flare_reflected_element_descriptors;
    return ef_lens_flare;
}

void TEF_LensFlare::run_task() {  }
void TEF_PvrWave::render() {  }

void TEF_PvrWave::run_task() {
    struct VObj_8008194C_80081278 *o = (struct VObj_8008194C_80081278 *)*(void **)((s8 *)this + 0x1C);
    o->m1();
}

}

extern "C" __declspec(section ".rodata") const Vec lbl_80438E40 = {0.0f, 0.0f, -1.0f};
