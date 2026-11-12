#include "types.h"
#include "pso/effect/TEF_LensFlare.h"
#include "pso/effect/TEF_PvrWave.h"
#include "pso/camera/TCameraCtrl.h"
#include "pso/effect/particle/TParticleCtrl.h"
#include "pso/math/MatrixVector.h"
#include "pso/object/ambient/TObjFish.h"
#include "pso/render/render_util.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/task/TMainTask.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"
#include "pso/ui/window/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"

struct Base_8008194C_80081278 { char pad[0x50]; };
struct VObj_8008194C_80081278 : Base_8008194C_80081278 {
    virtual void m0();
    virtual void m1();
};

extern "C" {
s32 __ct__8TObjBaseFP7TObject(void *, void *);
extern s32 __vt__13TEF_LensFlare[];
void *__dt__13TEF_LensFlareFv(void *arg0, s16 arg1);
void __dl__7TObjectFPv(void *);

extern const char TEF_LensFlare__class_name_string[] = "TEF_LensFlare";
const char *TEF_LensFlare__class_name = TEF_LensFlare__class_name_string;

LensFlareElement lens_flare_reflected_element_descriptors[10] = {
    {1, 0.1f, 0.8f, 0.0f, 0.7f, -10.0f},
    {2, 0.4f, 0.6f, 0.5f, 0.7f, -10.1f},
    {3, 0.6f, 0.8f, 0.6f, 0.7f, -10.2f},
    {1, 0.8f, 1.2f, 0.6f, 0.4f, -10.3f},
    {3, 1.0f, 1.2f, -0.3f, 0.7f, -10.4f},
    {4, 1.2f, 0.7f, 1.0f, 0.7f, -10.5f},
    {2, 1.4f, 1.7f, 0.0f, 0.7f, -10.6f},
    {5, 1.5f, 0.6f, 1.0f, 0.7f, -10.7f},
    {6, 1.8f, 1.5f, 0.0f, 0.7f, -10.8f},
    {2, 0.0f, 4.0f, 2.0f, 0.4f, -10.9f},
};

}
TEF_LensFlare::~TEF_LensFlare() {

}

struct LensFlareColor {
    struct { u8 a, r, g, b; } channels;
} ATTRIBUTE_ALIGN(4);
struct LensFlareGlareColor {
    struct { signed int a:8; u8 r, g, b; } channels;
};
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

// An entry of the particle sprite table (lbl_804C5820, 0x28 bytes each).
struct FlareSpriteTexture {
    u32 flags;
    s32 param;
    s32 tex;
    u8 pad_c[0x8];
    f32 sx;
    f32 sy;
    u8 pad_1c[0xC];
};

extern "C" {
extern TCameraCtrl *camera_ctrl_instance;
extern FlareSpriteTexture lbl_804C5820[];
extern const Vec lbl_80438E40;
f32 vec3_dot(const Vec *, const Vec *);
f32 normalize_vector(Vec *);
}

#pragma push
// The descriptor loop keeps its induction pointer separate from the hoisted
// definition-table base; default propagation swaps those two callee-saved
// registers. This is the only frontend control the object still needs.
// Porting exception (approved by Matt 2026-11-04, see docs/porting-exceptions.md):
// no honest source form reproduces MWCC's output without it. Remove when
// porting off MWCC.
#pragma opt_propagation off
void TEF_LensFlare::render() {
    Vec *sprite_position;
    if (TMainTask::get_render_pass() != 0 && camera_ctrl_instance != NULL) {
        LensFlareSprite sprite_storage;
        LensFlareSprite *sprite = &sprite_storage;
        sprite->position.x = 0.0f; sprite->position.y = 0.0f; sprite->position.z = 0.0f;
        sprite->reserved[0] = 0.0f; sprite->reserved[1] = 0.0f; sprite->reserved[2] = 0.0f;
        sprite->scale_x = 0.0f; sprite->scale_y = 0.0f;
        sprite->color = 0; sprite->flags = 0; sprite->angle = 0;
        sprite_position = &sprite_storage.position;
        set_additive_blend();
        if (this->scale.x >= 0.0f) {
            f32 radius = 10.0f * this->scale.x;
            if (this->is_player_near(radius * radius)) return;
        }
        TParticleCtrl::begin_effect_render();
        Vec direction;
        direction.x = this->position.x - camera_ctrl_instance->pos_x;
        direction.y = this->position.y - camera_ctrl_instance->pos_y;
        direction.z = this->position.z - camera_ctrl_instance->pos_z;
        if (0.0f != vec_squared_length(&direction)) normalize_vector(&direction);
        push_matrix_from(&identity_matrix);
        Vec facing;
        Vec forward = lbl_80438E40;
        rotate_matrix_y(NULL, camera_ctrl_instance->yaw);
        rotate_matrix_x(NULL, camera_ctrl_instance->pitch);
        rotate_vector_by_matrix(0, &forward, &facing);
        pop_matrix();
        f32 center_x, center_y, inverse_strength, strength;
        f32 alignment = vec3_dot(&facing, &direction);
        if (alignment > 0.0f) {
            set_depth_buffer_settings_1();
            f32 screen[2];
            project_world_to_screen(NULL, &this->position, screen);
            Vec point;
            if (alignment > 0.99f) {
                f32 glow = 50.0f * (alignment - 0.98f);
                glow *= glow;
                LensFlareGlareColor color;
                color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
                color.channels.a = 255.0f * (0.9f * glow);
                point.x = screen[0]; point.y = screen[1]; point.z = 0.0f;
                __memcpy(&sprite->color, &color, sizeof(color));
                VecCopy(sprite_position, &point);
                sprite->scale_x = 20.0f * glow; sprite->scale_y = sprite->scale_x;
                begin_screen_draw(1);
                set_current_texture_list((GinjaTextureList *)lbl_804C5820[15].param);
                set_draw_texture_and_color(lbl_804C5820[15].tex, -1);
                f32 x = point.x;
                f32 y = point.y;
                f32 sx;
                f32 twice;
                f32 half_width = lbl_804C5820[15].sx;
                f32 half_height = lbl_804C5820[15].sy;
                twice = 2.0f;
                sx = twice * sprite->scale_x;
                f32 sy = twice * sprite->scale_y;
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
            LensFlareColor color;
            color.channels.a = 255; color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
            strength *= strength * strength * strength;
            __memcpy(&sprite->color, &color, sizeof(color));
            // Pair displacement and point setup to retain the original scalar lifetimes.
            const f32 screen_x = screen[0];
            center_x = 320.0f - screen_x;
            point.x = screen_x;
            const f32 screen_y = screen[1];
            center_y = 240.0f - screen_y;
            point.y = screen_y;
            point.z = 0.0f;
            VecCopy(sprite_position, &point);
            sprite->scale_x = 1.0f; sprite->scale_y = sprite->scale_x;
            begin_screen_draw(1);
            set_current_texture_list((GinjaTextureList *)lbl_804C5820[9].param);
            set_draw_texture_and_color(lbl_804C5820[9].tex, -1);
            f32 x = point.x;
            f32 y = point.y;
            f32 sx;
            f32 twice;
            f32 half_width = lbl_804C5820[9].sx;
            f32 half_height = lbl_804C5820[9].sy;
            twice = 2.0f;
            sx = twice * sprite->scale_x;
            f32 sy = twice * sprite->scale_y;
            half_width *= sx; half_height *= sy;
            f32 quad[8];
            quad[0] = x - half_width; quad[2] = x + half_width;
            quad[1] = y - half_height; quad[3] = y + half_height;
            quad[4] = 0.0f; quad[5] = 0.0f;
            quad[6] = 1.0f; quad[7] = 1.0f;
            set_constant_material_color(sprite->color);
            draw_textured_quad_at_depth(quad, 0.5f);
            TWindowSubStatusDisp::get_player();
            // Reflected draws walk the first nine descriptor records.
            s32 i;
            LensFlareElement *element = this->elements;
            inverse_strength = 1.0f - strength;
            i = 0;
            while (i++ < 9) {
                f32 size = element->size * (1.0f - inverse_strength * element->shrink);
                if (size < 0.0f) size = 0.0f;
                LensFlareColor color;
                // fctiwz followed by stb: signed truncation, then low-byte wrapping.
                color.channels.r = 255; color.channels.g = 255; color.channels.b = 255;
                color.channels.a = (s32)(255.0f * (strength * element->brightness));
                __memcpy(&sprite->color, &color, sizeof(color));
                point.x = center_x * element->position + screen[0];
                point.y = center_y * element->position + screen[1];
                point.z = 0.0f;
                VecCopy(sprite_position, &point);
                sprite->scale_x = size; sprite->scale_y = sprite->scale_x;
                begin_screen_draw(1);
                GinjaTextureList *texture_list = (GinjaTextureList *)lbl_804C5820[9 + element->sprite].param;
                set_current_texture_list(texture_list);
                set_draw_texture_and_color(lbl_804C5820[9 + element->sprite].tex, -1);
                // Preserve the native float lifetimes: capture x, read y at the bounds.
                f32 sy;
                f32 sx = 2.0f * sprite->scale_x;
                const f32 x = point.x;
                f32 half_width = lbl_804C5820[9 + element->sprite].sx;
                f32 half_height = lbl_804C5820[9 + element->sprite].sy;
                sy = 2.0f * sprite->scale_y;
                half_height *= sy;
                f32 quad[8];
                quad[4] = 0.0f;
                half_width *= sx;
                quad[0] = x - half_width;
                quad[5] = 0.0f;
                quad[6] = 1.0f;
                quad[2] = x + half_width;
                quad[1] = point.y - half_height;
                quad[3] = point.y + half_height;
                quad[7] = 1.0f;
                set_constant_material_color(sprite->color);
                draw_textured_quad_at_depth(quad, 0.5f);
                TWindowSubStatusDisp::get_player();
                ++element;
            }
            restore_saved_depth_alpha_state();
        }
        TParticleCtrl::end_effect_render();
    }
}
#pragma pop
extern "C" {

TEF_LensFlare::TEF_LensFlare(TObject *parent, void *set_data) : TObjBase(parent) {
    m_name = TEF_LensFlare__class_name;
    apply_object_set_data(set_data);
    elements = lens_flare_reflected_element_descriptors;
}

void TEF_LensFlare::run_task() {  }
void TEF_PvrWave::render() {  }

void TEF_PvrWave::run_task() {
    struct VObj_8008194C_80081278 *o = (struct VObj_8008194C_80081278 *)*(void **)((s8 *)this + 0x1C);
    o->m1();
}

}

extern "C" __declspec(section ".rodata") const Vec lbl_80438E40 = {0.0f, 0.0f, -1.0f};
