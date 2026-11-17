#include "pso/system/CurrentTextureList.h"
#include "pso/misc/ParticleDefinition.h"
#include "pso/unk/text_801E4F04.h"
#include "types.h"
#include <stddef.h>
#include "pso/misc/TQuadSpriteNormal.h"

#include "pso/system/vector.h"
#include "pso/unk/TUnk_804C57F0.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/unk/text_803D853C.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/render/render_util.h"

struct SpriteUV { f32 u0, v0, u1, v1; };

struct SpriteQuad { f32 x0, y0, x1, y1; SpriteUV uv; };

struct SpriteNode {
    struct SpriteNode *next;
    Vec pos;
    Vec ofs;
    u8 pad1C[0x24 - 0x1C];
    s32 field_24;
    u8 pad28;
    u8 type;
};

struct SpriteList { SpriteNode *head; u8 unused[0x28]; };

// Bounded view of the shared projection state; unused fields remain unresolved.
struct SpriteCamera { u8 pad0[8]; f32 cx; f32 cy; u8 pad10[8]; f32 sw; f32 aspect; u8 pad20[8]; };

typedef char SpriteNode_type_offset[offsetof(SpriteNode, type) == 0x29 ? 1 : -1];
typedef char SpriteList_size[sizeof(SpriteList) == 0x2C ? 1 : -1];
typedef char SpriteQuad_size[sizeof(SpriteQuad) == 0x20 ? 1 : -1];

extern "C" {
extern SpriteCamera lbl_8058D4F8;
static const f32 lbl_805DC460 = 480.0f;
static const f32 lbl_805DC464 = -1.0f;
static const f32 lbl_805DC468 = 1.0f;

extern s32 __vt__17TQuadSpriteNormal[];
}

#pragma push
#pragma fp_contract on
void TQuadSpriteNormal::render() {
    SpriteQuad q;
    Vec out;
    Vec pos;
    u32 flags;
    f32 sw;
    f32 sh;
    f32 cx;
    f32 cy;
    f32 one;
    s32 uv_byte_offset;
    s32 list_byte_offset;
    s32 i;
    SpriteNode *n;
    // The shared sprite base still exposes its list and active count as raw fields.
    if (*(s32 *)unk_24 == 0) {
        return;
    }
    flags = ((ParticleDefinition *)m_28)->flags;
    if (flags & 2) {
        if (flags & 4) {
            set_inverse_alpha_blend();
        } else {
            set_default_alpha_blend();
        }
    } else if (flags & 4) {
        set_inverse_color_blend();
    } else {
        set_additive_blend();
    }
    sw = lbl_8058D4F8.sw;
    cx = lbl_8058D4F8.cx;
    cy = lbl_8058D4F8.cy;
    sh = sw * (lbl_805DC460 / (lbl_805DC460 * lbl_8058D4F8.aspect));
    TParticleCtrl::begin_effect_render();
    begin_screen_draw(1);
    set_current_texture_list(((ParticleDefinition *)m_28)->texlist);
    set_draw_texture_and_color(((ParticleDefinition *)m_28)->texture, ((ParticleDefinition *)m_28)->color);
    one = lbl_805DC464;
    // Separate byte strides preserve GC/2.6's original register allocation.
    for (i = 0, uv_byte_offset = 0, list_byte_offset = 0; i < ((ParticleDefinition *)m_28)->uv_count; i++, uv_byte_offset += sizeof(SpriteUV), list_byte_offset += sizeof(SpriteList)) {
        f32 *uv = (f32 *)((u8 *)((ParticleDefinition *)m_28)->uvs + uv_byte_offset);
        n = *(SpriteNode **)((u8 *)(*(SpriteList **)unk_1C) + list_byte_offset);
        q.uv.u0 = uv[0];
        q.uv.v0 = uv[1];
        q.uv.u1 = uv[2];
        q.uv.v1 = uv[3];
        while (n != NULL) {
            f32 d, sx, sy, x, y, w, h;
            pos.x = n->pos.x + n->ofs.x;
            pos.y = n->pos.y + n->ofs.y;
            pos.z = n->pos.z + n->ofs.z;
            if ((s32)n->type != 1) {
                matrix_mult_vec(NULL, &pos, &out);
                out.y = -out.y;
            } else {
                VecCopy(&out, &pos);
            }
            if (out.z <= one || (s32)n->type == 1) {
                if ((s32)n->type != 1) {
                    d = lbl_805DC468 / -out.z;
                    sx = sh * d;
                    sy = sw * d;
                    x = out.x * sx + cx;
                    y = out.y * sy + cy;
                    w = sx;
                    h = sy;
                } else {
                    h = w = lbl_805DC468;
                    d = out.z;
                    x = out.x;
                    y = out.y;
                }
                w *= ((ParticleDefinition *)m_28)->width;
                h *= ((ParticleDefinition *)m_28)->height;
                q.x0 = x - w;
                q.x1 = x + w;
                q.y0 = y - h;
                q.y1 = y + h;
                draw_textured_quad_at_depth(&q, d);
            }
            n = n->next;
        }
    }
    TWindowSubStatusDisp::get_player();
    TParticleCtrl::end_effect_render();
    quad_sprite_reset_entries();
    set_default_alpha_blend();
}
#pragma pop

TQuadSpriteNormal::~TQuadSpriteNormal() {

}

extern const char lbl_80449860[] = "TQuadSpriteNormal";
const char *TQuadSpriteNormal__class_name = lbl_80449860;

// Retain the provisional C lifetime boundary until the shared base constructor
// and its other sprite callers are recovered together. All three arguments pass
// through unchanged to quad_sprite_base_ct. The vtable itself is compiler-emitted.
void *TQuadSpriteNormal__ct(void *quad_sprite_normal, TObject *parent, ParticleDefinition *definition) {
    quad_sprite_base_ct(quad_sprite_normal, parent, definition);
    *(s32 **)((s8 *)quad_sprite_normal + 0x18) = __vt__17TQuadSpriteNormal;
    ((TQuadSpriteNormal *)quad_sprite_normal)->m_name = TQuadSpriteNormal__class_name;
    return quad_sprite_normal;
}
