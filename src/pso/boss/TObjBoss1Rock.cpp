#include "pso/system/ArrayAllocation.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaTypes.h"
void set_constant_material(const NJS_ARGB *color);
#include "types.h"
#include "pso/misc/MaterialColorFade.h"
#include "pso/system/memory.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TObjBoss1Rock.h"
#include "pso/object/TObjFish.h"

struct Ent_8002DF7C { u8 pad0[8]; s32 id; u8 padc[4]; };

struct Res_8002DF7C { u8 pad0[0x42C]; Ent_8002DF7C *ents; };

struct Obj_8002DF7C {
    u8 pad0[0x1C];
    u8 pos[0x18];
    s32 ry;
    s32 rx;
    f32 x3c;
    f32 color;
    u8 pad44[0x50 - 0x44];
    s32 idx;
};

extern "C" {
extern u8 *lbl_805D4B50;
extern s32 dragon_common_texture_list;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
extern const f32 lbl_805D8200;
void push_matrix(void);
s32 pop_matrix(void);
void post_translate_matrix(void *);
void set_chunk_material_override_pair(s32, s32, s32, s32);
void draw_chunk_object(void *);
void rotate_matrix_y(int, int);
void rotate_matrix_x(int, int);
}

#pragma push
#pragma fp_contract on
void TObjBoss1Rock::render() {
    Obj_8002DF7C *self = (Obj_8002DF7C *)this;
    if (self->color < lbl_805D8200) {
        saved_model_render_flags = model_render_flags;
        model_render_flags = saved_model_render_flags | 0x810;
        ((void (*)(s32, s32))set_chunk_material_override_pair)(0xFF00, 0x800);
        set_constant_material((const NJS_ARGB *)((&self->color)));
        push_matrix();
        set_current_texture_list((GinjaTextureList *)(dragon_common_texture_list));
        post_translate_matrix(self->pos);
        rotate_matrix_y(0, self->ry);
        rotate_matrix_x(0, self->rx);
        ((void (*)(s32))draw_chunk_object)((*(Res_8002DF7C **)&lbl_805D4B50)->ents[self->idx].id);
        pop_matrix();
        ((void (*)(s32, s32))set_chunk_material_override_pair)(0xFF00, 0);
        model_render_flags = saved_model_render_flags;
    } else {
        push_matrix();
        set_current_texture_list((GinjaTextureList *)(dragon_common_texture_list));
        post_translate_matrix(self->pos);
        rotate_matrix_y(0, self->ry);
        rotate_matrix_x(0, self->rx);
        ((void (*)(s32))draw_chunk_object)((*(Res_8002DF7C **)&lbl_805D4B50)->ents[self->idx].id);
        pop_matrix();
    }
}
#pragma pop
