#include "pso/system/ArrayAllocation.h"
#include "pso/misc/TWindowDrawContext.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TUnk_804CF0B8.h"
#include "pso/misc/TWindowFukidasi.h"
#include "pso/TObjCMHairMenu.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/misc/TWindowCtrlMain.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubSymbolChat.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowSubStatusDisp_800FBD74.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet_80247EFC.h"
#include "pso/object/TObjFish.h"

__declspec(section ".sdata2") extern const f32 lbl_805DCDC0[2];


s32 draw_small_font_string_clipped(f32 *, const char *, u32, f32);

struct Pt_80250A24 { f32 x, y; };

struct Fuki_80250A24 {
    u8 pad0[0x38];
    f32 size[2];
    u8 pad40[0x48 - 0x40];
    f32 rsize[2];
    u8 pad50[0x90 - 0x50];
    f32 center[2];
};

struct Fuki_802506E8 {
    u8 pad0[0x38];
    f32 size[2];
    u8 pad40[0x48 - 0x40];
    f32 rsize[2];
    u8 pad50[0x90 - 0x50];
    f32 center[2];
};

extern "C" {
f32 fabs_float(f32);
f32 atan2_float(f32, f32);
f32 newton_sqrtf(f32);
int rand(void);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
f32 xyz_distance(void *, void *);
s32 rest_balloon__15TWindowFukidasiFv(Fuki_80250A24 *b, f32 *rect, f32 *arg2);
s32 try_place_bubble__15TWindowFukidasiFPvPvPv(Fuki_802506E8 *b, f32 *rect, f32 *o);
// Text entry returned by get_array_entry; TWindowMessage reads the same layout.
struct Entry_80250380 {
    u16 flags;
    u8 pad2[0x10 - 0x2];
    f32 w;
    f32 h;
    u8 pad18[0x24 - 0x18];
    u32 color;
};

struct Fuki_80250F70 {
    u8 pad0[0x38]; f32 anchor[2];
    u8 pad40[0x50];
    f32 head[2];
};

struct Fuki_802504C0 {
    u8 pad0[0x20]; s16 viewport; u8 pad22[0xE];
    f32 rect[2]; f32 anchor[2];
    u8 pad40[0x30];
    u8 phase; u8 options; u8 kind; u8 slot;
};

struct Fuki_80250F70;

struct Fuki_802504C0;

struct Fuki_80251028 {
    u8 pad0[0x20]; s16 viewport; u8 pad22[0xE];
    f32 rect[2]; f32 anchor[2];
    u8 pad40[0x30];
    u8 phase; u8 options; u8 kind; u8 slot;
};

struct Fuki_80251380 {
    u8 pad0[0x20];
    s16 viewport;
};

struct Vec_80251380 {
    f32 x, y, z;
};

struct Cam_80251380 {
    u8 pad0[0x178];
    f32 pos[3];
    u8 pad184[0x190 - 0x184];
    s32 rx;
    s32 ry;
    s32 rz;
};

struct RecoveredGlobal_80251BA0_lbl_804CF080
{
  s32 value;
  u8 remaining[0x20];
};

typedef struct RecoveredGlobal_80251BA0_lbl_804CF080 RecoveredGlobal_80251BA0_lbl_804CF080;

struct Prim_802521E8 {
    f32 *verts;
    u32 *colors;
    s32 flags;
    s32 count;
};

// One skewed row of the balloon body, handed to DVDConvertEntrynumToPath.
struct BalloonSlice { f32 x, y, z, width, f10, lean, rowHeight, f1c, u, v, uw, f2c, f30, vh, pad[4]; };

struct Ent_802511E4 {
    u8 pad0[0x38];
    f32 pos[3];
};

struct Cam_802511E4 {
    u8 pad0[8];
    f32 x;
    f32 y;
};

struct Fuki_80251594 {
    u8 pad0[0x30];
    f32 rect[2];
    f32 anchor[2];
    f32 pos[2];
    f32 size[2];
    u32 steps;
    u8 pad54[0x71 - 0x54];
    u8 options;
    u8 pad72[0x80 - 0x72];
    f32 margin;
    u8 pad84[4];
    f32 center[2];
    f32 head[2];
};


s32 obj_isState3_324__9TObjCharaFv();
s32 is_split_screen();
s32 get_screen_width__11TCameraCtrlFv();
s32 get_screen_height__11TCameraCtrlFv();
Ent_802511E4 * find_entity_by_id(u16);
u32 get_battle_ctrl_flag__10TObjPlayerFUs(u16);
u32 get_player_by_client_id(u32);
s32 get_array_entry__13TUnk_804CE018Fi(void *, s32);

s32 get_field_20__17TWindowSubComCardFv();
s32 refresh_status_display__9TWindowDDFv(void *);
s32 draw_resolved_window__15TWindowFukidasiFllll(Fuki_80250F70 *, f32 *, f32 *, s32);
f32 * get_message_by_type__11TWindowCtrlFScl(u8, int);
s32 TWindowFukidasi__sub_802505C0(Fuki_80251028 *b, f32 *rect, f32 *out);
s32 shift_rect_with_head__15TWindowFukidasiFPvPvPv(Fuki_80250F70 *b, f32 *rect, f32 *out);
void refresh_rect_placement__15TWindowFukidasiFPv(Fuki_80251028 *b);
void TWindowFukidasi__sub_80251790(TUnk_804CF0B8 *b);
void TWindowFukidasi__sub_80252C38(void *p);
void clear_flag_20__13TUnk_804CF0B8Fv();
s32 fn_80252CBC(void);
void draw_visible_window_entries(void *, void *, TWindowDrawContext *);
s32 init_window_layout_entries(void *, void *, int);
s32 reset_float_field__15TWindowHelpItemFv();
s32 measure_message_text_width(void *, f32);
}
extern "C" {
s32 strcmp(s32, s32);
s32 strncpy(s32, s32, s32);
f32 vec3_dot(void *, void *);
void project_world_to_screen(s32, f32 *, f32 *);
void rotate_vector_by_matrix(s32, void *, void *);
void rotate_matrix_y(s32, s32);
void rotate_matrix_z(s32, s32);
void rotate_matrix_x(s32, s32);
s32 push_matrix_from(void *src);
void push_matrix();
void pop_matrix();

extern Cam_802511E4 TCameraCtrl__data_804FF634;
extern u32 TWindowFukidasi__balloon_color_table[];
extern Vec_80251380 fukidasi_forward_vec;
extern RecoveredGlobal_80251BA0_lbl_804CF080 window_fukidasi_layout_entries;
extern u8 identity_matrix[];
extern const char *window_fukidasi_class_name;
extern Cam_80251380 *camera_ctrl_instance;
extern void *lbl_805D63F0;

void complete_speech_balloon(u8 *arg0) {
    s32 t;
    TUnk_804CF0B8 *self = (TUnk_804CF0B8 *)arg0;
    self->m_70 = 4;
    self->m_71 |= 0x40;
    self->calc_text_size(&self->m_38);
    ((s32 (*)(void *))refresh_rect_placement__15TWindowFukidasiFPv)(arg0);
    TWindowFukidasi__sub_80252C38(arg0);
    ((TUnk_804CF0B8 *)arg0)->set_flag2c_bit100();
    ((TUnk_804CE018 *)arg0)->save_position();
    self->m_80 = 1.0f;
    self->sync_display_pos();
    self->m_5c = 0x186A0;
    t = self->m_72;
    switch (t) {
    case 0:
        get_array_entry__13TUnk_804CE018Fi(arg0, 0);
        reset_float_field__15TWindowHelpItemFv();
        break;
    case 1:
    case 2:
        break;
    }
}

s32 is_speech_balloon_ready(u8 *arg0) {
    s32 t = ((TUnk_804CF0B8 *)arg0)->m_72;
    switch (t) {
    case 0:
        get_array_entry__13TUnk_804CE018Fi(arg0, 0);
        return fn_80252CBC();
    case 1:
    case 2:
        break;
    }
    return 0;
}

void TWindowFukidasi::rearm_balloon(s32 arg1) {
    u32 n;

    if (this->sub_80246948() != 0) {
        this->m_70 = 5;
    }
    this->init_flags(arg1);
    switch ((s32) this->m_72) {
    case 0:
        n = TWindowKeyBoardSoft::strnlen((s8 *)(((void * (*)(void *))get_field_20__17TWindowSubComCardFv)(((void * (*)(void *, int))get_array_entry__13TUnk_804CE018Fi)(this, 0))), (u32)0x100);
        this->m_74 = (s16) ((3.3f * (f32) n) + 55.5f);
        break;
    case 1:
        this->m_74 = 0x5A;
        break;
    case 2:
        break;
    }
}

__declspec(section ".rodata") extern const f64 TWindowFukidasi__data_8044ED70[1] = {10430.38043493439};

s32 TWindowFukidasi::check_card_match_enabled(s32 arg1) {
    if (this->m_72 != 0) {
        return 0;
    }
    get_array_entry__13TUnk_804CE018Fi(this, 0);
    return (u32) __cntlzw(strcmp(get_field_20__17TWindowSubComCardFv(), arg1)) >> 5;
}

void TUnk_804CF0B8::clamp_text_size(f32 *out) {
    f32 size[2];
    this->calc_text_size(size);
    if (this->m_38 > size[0]) {
        out[0] = size[0];
    } else {
        out[0] = this->m_38;
    }
    if (this->m_3c > size[1]) {
        out[1] = size[1];
    } else {
        out[1] = this->m_3c;
    }
}

void TUnk_804CF0B8::calc_text_size(f32 *out) {
    Entry_80250380 *e;
    switch (this->m_72) {
    case 0:
        e = (Entry_80250380 *)this->get_array_entry(0);
        out[0] = 0.1f + (8.0f + e->w);
        out[1] = 0.1f + (20.0f + e->h);
        break;
    case 1:
        TWindowSubSymbolChat__sub_802483F0((int)&this->m_24, out);
        break;
    case 2:
        break;
    }
}

void TUnk_804CF0B8::sync_display_pos() { this->m_60 = this->m_80; this->m_64 = this->m_80; }

s32 TUnk_804CF0B8::approach(f32 farg0) {
    f32 temp_f31;

    temp_f31 = 0.47f * (farg0 - this->m_80);
    if (fabs_float(temp_f31) < 0.011f) {
        this->m_80 = farg0;
        return 1;
    }
    this->m_80 = (f32) (this->m_80 + temp_f31);
    return 0;
}

void TUnk_804CF0B8::sub_802504A8() {
    if (!(this->m_71 & 0x10)) {
        this->m_70 = 7;
    }
}

// Original pool emits 1000.0 before place_rect's 0.5 literal.
__declspec(section ".sdata2") extern const f32 TWindowFukidasi__data_805DCD08[1] = {1000.0f};

void TUnk_804CF0B8::place_rect_at_head_or_slot() {
    Fuki_802504C0 *b = (Fuki_802504C0 *)this;
    if (is_speaker_far_or_offscreen() != 0) {
        f32 *m;
        if ((s8)b->slot == -1) {
            ((TUnk_804CF0B8 *)b)->set_flag();
            ((TUnk_804CF0B8 *)b)->set_flag2c_bit200();
            b->slot = ((TUnk_804CF0B8 *)b)->alloc_nearest_free_slot();
        }
        m = get_message_by_type__11TWindowCtrlFScl(b->slot, b->viewport);
        b->rect[0] = m[0] - 0.5f * b->anchor[0];
        b->rect[1] = m[1] - 0.5f * b->anchor[1];
        ((TUnk_804CF0B8 *)b)->clamp_position(b->rect, 1.0f);
    } else {
        f32 p[2];
        if ((s8)b->slot != -1) {
            ((TUnk_804CF0B8 *)b)->clear_visible_flag();
            ((TUnk_804CF0B8 *)b)->clear_flag2c_bit200();
            TWindowCtrl::release_slot((s8 *)&b->slot);
        }
        project_anchor((f32 *)(0), p);
        b->rect[0] = p[0] - 0.5f * b->anchor[0];
        b->rect[1] = p[1] - 0.5f * b->anchor[1];
    }
}

// Original pool emits 19.0 before sub_802505C0's epsilon literal.
__declspec(section ".sdata2") extern const f32 lbl_805DCD10[1] = {19.0f};

s32 TWindowFukidasi__sub_802505C0(Fuki_80251028 *b, f32 *rect, f32 *out) {
    f32 x = ((TWindowCtrlMain *)b->viewport)->get_position_z();
    f32 w = (((TWindowCtrlMain *)b->viewport)->get_ctrl_field14() - ((TWindowCtrlMain *)b->viewport)->get_position_z()) - b->anchor[0];
    f32 y;
    f32 h;
    f32 t;
    t = 3.0517578e-05f * (f32) rand();
    out[0] = t * w + x;
    y = ((TWindowCtrlMain *)b->viewport)->get_field10();
    h = (((TWindowCtrlMain *)b->viewport)->get_field_18() - ((TWindowCtrlMain *)b->viewport)->get_field10()) - b->anchor[1];
    t = 3.0517578e-05f * (f32) rand();
    out[1] = t * h + y;
    return (u32) __cntlzw((u32) draw_resolved_window__15TWindowFukidasiFllll((Fuki_80250F70 *)b, out, b->anchor, 4)) >> 5;
}

#define F70_80250A24 ((Fuki_80250F70 *)b)
#define CLAMP_80250A24 ((s32 (*)(Fuki_80250F70 *, f32 *, f32))clamp_position__13TUnk_804CF0B8FPvf)
#define DRAW_80250A24 ((void *(*)(Fuki_80250F70 *, f32 *, f32 *, s32))draw_resolved_window__15TWindowFukidasiFllll)

struct Cam_80251380;
#define F70_802506E8 ((Fuki_80250F70 *)b)
#define CLAMP_802506E8 ((s32 (*)(Fuki_80250F70 *, f32 *, f32))clamp_position__13TUnk_804CF0B8FPvf)
#define DRAW_802506E8 ((void *(*)(Fuki_80250F70 *, f32 *, f32 *, s32))draw_resolved_window__15TWindowFukidasiFllll)
s32 try_place_bubble__15TWindowFukidasiFPvPvPv(Fuki_802506E8 *b, f32 *rect, f32 *o) {
    f32 world[3];
    f32 edge[2];
    f32 dx;
    f32 dy;
    f32 reach;
    s32 a;
    s32 angle;
    ((TUnk_804CF0B8 *)F70_802506E8)->project_anchor(world, NULL);
    reach = (TWindowFukidasi__data_805DCD08[0]) / xyz_distance(camera_ctrl_instance->pos, world);
    dx = (0.5f * b->rsize[0] + rect[0]) - b->center[0];
    dy = (0.5f * b->rsize[1] + rect[1]) - b->center[1];
    a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(dy, dx)));
    edge[0] = dx - reach * cos_table_lookup(a);
    edge[1] = dy - reach * sin_table_lookup(a);
    edge[0] /= 14.0f + b->rsize[0];
    edge[1] /= 10.0f + b->rsize[1];
    angle = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    ((TWindowFukidasi *)b)->get_boundary_offset(angle + 0x8000, edge);
    a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    edge[0] += reach * cos_table_lookup(a);
    edge[1] += reach * sin_table_lookup(a);
    o[0] = (b->center[0] + edge[0]) - 0.5f * b->size[0];
    o[1] = (b->center[1] + edge[1]) - 0.5f * b->size[1];
    if (CLAMP_802506E8(F70_802506E8, o, 1.0f) != 0) {
        return 0;
    }
    if (DRAW_802506E8(F70_802506E8, o, b->size, 4) == NULL) {
        return 1;
    }
    angle = (s32) ((f32) a + (32768.0f * (3.0517578e-05f * (f32) rand()) - 16384.0f));
    ((TWindowFukidasi *)b)->get_boundary_offset(angle, edge);
    a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    edge[0] += reach * cos_table_lookup(a);
    edge[1] += reach * sin_table_lookup(a);
    o[0] = (b->center[0] + edge[0]) - 0.5f * b->size[0];
    o[1] = (b->center[1] + edge[1]) - 0.5f * b->size[1];
    if (CLAMP_802506E8(F70_802506E8, o, 1.0f) != 0) {
        return 0;
    }
    return (u32) __cntlzw((u32) DRAW_802506E8(F70_802506E8, o, b->size, 4)) >> 5;
}

s32 rest_balloon__15TWindowFukidasiFv(Fuki_80250A24 *b, f32 *rect, f32 *arg2) {
    Pt_80250A24 *o = (Pt_80250A24 *)arg2;
    f32 world[3];
    f32 edge[2];
    f32 dist;
    f32 dx;
    f32 dy;
    f32 reach;
    f32 t;
    s32 a;
    s32 angle;
    ((TUnk_804CF0B8 *)F70_80250A24)->project_anchor(world, NULL);
    reach = (TWindowFukidasi__data_805DCD08[0]) / xyz_distance(camera_ctrl_instance->pos, world);
    dx = (0.5f * b->rsize[0] + rect[0]) - b->center[0];
    dy = (0.5f * b->rsize[1] + rect[1]) - b->center[1];
    dist = newton_sqrtf(dx * dx + dy * dy);
    if (dist < 3.0f) {
        angle = 0xD400;
    } else {
        a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(dy, dx)));
        edge[0] = dx - reach * cos_table_lookup(a);
        edge[1] = dy - reach * sin_table_lookup(a);
        edge[0] /= 14.0f + b->rsize[0];
        edge[1] /= 10.0f + b->rsize[1];
        angle = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    }
    ((TWindowFukidasi *)b)->get_boundary_offset(angle, edge);
    a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    edge[0] += reach * cos_table_lookup(a);
    edge[1] += reach * sin_table_lookup(a);
    if (fabs_float(dist - newton_sqrtf(edge[0] * edge[0] + edge[1] * edge[1])) < 10.0f) {
        return 0;
    }
    o->x = (b->center[0] + edge[0]) - 0.5f * b->size[0];
    o->y = (b->center[1] + edge[1]) - 0.5f * b->size[1];
    if (CLAMP_80250A24(F70_80250A24, (f32 *)o, 1.0f) != 0) {
        return 0;
    }
    if (DRAW_80250A24(F70_80250A24, (f32 *)o, b->size, 4) == NULL) {
        return 1;
    }
    t = 3.0517578e-05f * (f32) rand();
    edge[0] += t * (dx - edge[0]);
    edge[1] += t * (dy - edge[1]);
    o->x = (b->center[0] + edge[0]) - 0.5f * b->size[0];
    o->y = (b->center[1] + edge[1]) - 0.5f * b->size[1];
    if (DRAW_80250A24(F70_80250A24, (f32 *)o, b->size, 4) == NULL) {
        return 1;
    }
    angle = (s32) ((f32) a + (32768.0f * (3.0517578e-05f * (f32) rand()) - 16384.0f));
    ((TWindowFukidasi *)b)->get_boundary_offset(angle, edge);
    a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    edge[0] += reach * cos_table_lookup(a);
    edge[1] += reach * sin_table_lookup(a);
    o->x = (b->center[0] + edge[0]) - 0.5f * b->size[0];
    o->y = (b->center[1] + edge[1]) - 0.5f * b->size[1];
    if (CLAMP_80250A24(F70_80250A24, (f32 *)o, 1.0f) != 0) {
        return 0;
    }
    if (DRAW_80250A24(F70_80250A24, (f32 *)o, b->size, 4) == NULL) {
        return 1;
    }
    angle = (s32) (65536.0f * (3.0517578e-05f * (f32) rand()));
    ((TWindowFukidasi *)b)->get_boundary_offset(angle, edge);
    a = (s32) ((TWindowFukidasi__data_8044ED70[0]) * ((f64)atan2_float(edge[1], edge[0])));
    edge[0] += reach * cos_table_lookup(a);
    edge[1] += reach * sin_table_lookup(a);
    o->x = (b->center[0] + edge[0]) - 0.5f * b->size[0];
    o->y = (b->center[1] + edge[1]) - 0.5f * b->size[1];
    if (CLAMP_80250A24(F70_80250A24, (f32 *)o, 1.0f) != 0) {
        return 0;
    }
    return (u32) __cntlzw((u32) DRAW_80250A24(F70_80250A24, (f32 *)o, b->size, 4)) >> 5;
}

s32 shift_rect_with_head__15TWindowFukidasiFPvPvPv(Fuki_80250F70 *b, f32 *rect, f32 *out) {
    f32 x = b->head[0];
    f32 y = b->head[1];
    ((TUnk_804CF0B8 *)b)->project_anchor(0, b->head);
    out[0] = rect[0] + (b->head[0] - x);
    out[1] = rect[1] + (b->head[1] - y);
    ((TUnk_804CF0B8 *)b)->clamp_position(out, 1.0f);
    if (draw_resolved_window__15TWindowFukidasiFllll(b, out, b->anchor, 4) == 0) {
        return 1;
    }
    return 0;
}

void refresh_rect_placement__15TWindowFukidasiFPv(Fuki_80251028 *b) {
    if (((TUnk_804CF0B8 *)b)->is_speaker_far_or_offscreen() != 0) {
        f32 *m;
        if ((s8)b->slot == -1) {
            ((TUnk_804CF0B8 *)b)->set_flag();
            ((TUnk_804CF0B8 *)b)->set_flag2c_bit200();
            b->slot = ((TUnk_804CF0B8 *)b)->alloc_nearest_free_slot();
        }
        m = get_message_by_type__11TWindowCtrlFScl(b->slot, b->viewport);
        b->rect[0] = m[0] - 0.5f * b->anchor[0];
        b->rect[1] = m[1] - 0.5f * b->anchor[1];
        ((TUnk_804CF0B8 *)b)->clamp_position(b->rect, 1.0f);
    } else {
        f32 a[2];
        f32 c[2];
        f32 d[2];
        f32 e[2];
        f32 *res;
        if ((s8)b->slot != -1) {
            ((TUnk_804CF0B8 *)b)->clear_visible_flag();
            ((TUnk_804CF0B8 *)b)->clear_flag2c_bit200();
            TWindowCtrl::release_slot((s8 *)&b->slot);
        }
        res = NULL;
        if (((TWindowFukidasi *)b)->is_bit10_set() == 0) {
            if (shift_rect_with_head__15TWindowFukidasiFPvPvPv((Fuki_80250F70 *)b, b->rect, a) != 0) {
                res = a;
            }
            if (rest_balloon__15TWindowFukidasiFv((Fuki_80250A24 *)(b), a, c) != 0) {
                res = c;
            }
        } else {
            ((TWindowFukidasi *)b)->hide();
            if (shift_rect_with_head__15TWindowFukidasiFPvPvPv((Fuki_80250F70 *)b, b->rect, a) != 0) {
                res = a;
            }
            if (try_place_bubble__15TWindowFukidasiFPvPvPv((Fuki_802506E8 *)(b), a, d) != 0) {
                res = d;
            }
            if (res != d && rest_balloon__15TWindowFukidasiFv((Fuki_80250A24 *)(b), d, c) != 0) {
                res = c;
            }
            if (res == NULL && TWindowFukidasi__sub_802505C0(b, b->rect, e) != 0) {
                res = e;
            }
        }
        if (res != NULL) {
            b->rect[0] = res[0];
            b->rect[1] = res[1];
        }
    }
}

// Original pool emits this 0.0 before project_anchor's 320 literal.
__declspec(section ".sdata2") extern const f32 TWindowFukidasi__data_805DCD30[1] = {0.0f};

s32 TUnk_804CF0B8::project_anchor(f32 *pos, f32 *out) {
    Ent_802511E4 *e;
    f32 tmp[3];

    if (this->speaker_id == 0xFFFF) {
        return 0;
    }
    e = find_entity_by_id(this->speaker_id);
    if (e == NULL) {
        return 0;
    }
    if (((u32 (*)(u16))get_player_by_client_id)(this->speaker_id) != 0 && get_battle_ctrl_flag__10TObjPlayerFUs(this->speaker_id) == 0) {
        return 0;
    }
    if (pos == NULL) {
        pos = tmp;
    }
    pos[0] = e->pos[0];
    pos[1] = e->pos[1] + this->m_7c;
    pos[2] = e->pos[2];
    if (out == NULL) {
        return 1;
    }
    push_matrix();
    project_world_to_screen(0, pos, out);
    pop_matrix();
    if (is_split_screen() != 0) {
        out[0] -= (f32)get_screen_height__11TCameraCtrlFv();
        out[0] /= TCameraCtrl::get_view_scale();
        out[1] -= (f32)get_screen_width__11TCameraCtrlFv();
        out[1] /= TCameraCtrl::get_fov();
    }
    out[0] += TCameraCtrl__data_804FF634.x - 320.0f;
    out[1] += TCameraCtrl__data_804FF634.y - 240.0f;
    return 1;
}

s32 TUnk_804CF0B8::is_speaker_far_or_offscreen() {
    Fuki_802504C0 *arg0 = (Fuki_802504C0 *)this;
    f32 pos[3];
    f32 scr[2];
    f32 m;
    f32 xx;
    f32 yy;
    f32 zz;
    clear_flag_20__13TUnk_804CF0B8Fv();
    if (project_anchor(pos, scr) == 0) {
        return 1;
    }
    if (((TUnk_804CF0B8 *)arg0)->is_flag_set() != 0) {
        m = -50.0f;
    } else {
        m = (TWindowFukidasi__data_805DCD30[0]);
    }
    if (scr[0] < ((TWindowCtrlMain *)(((Fuki_80251380 *)arg0)->viewport))->get_position_z() - m) {
        return 1;
    }
    if (scr[1] < ((TWindowCtrlMain *)(((Fuki_80251380 *)arg0)->viewport))->get_field10() - m) {
        return 1;
    }
    if (scr[0] > m + ((TWindowCtrlMain *)(((Fuki_80251380 *)arg0)->viewport))->get_ctrl_field14()) {
        return 1;
    }
    if (scr[1] > m + ((TWindowCtrlMain *)(((Fuki_80251380 *)arg0)->viewport))->get_field_18()) {
        return 1;
    }
    Vec_80251380 v = fukidasi_forward_vec;
    f32 d[3];
    push_matrix_from(identity_matrix);
    rotate_matrix_y(0, camera_ctrl_instance->ry);
    rotate_matrix_x(0, camera_ctrl_instance->rx);
    rotate_matrix_z(0, camera_ctrl_instance->rz);
    rotate_vector_by_matrix(0, &v, &v);
    pop_matrix();
    d[0] = pos[0] - camera_ctrl_instance->pos[0];
    d[1] = pos[1] - camera_ctrl_instance->pos[1];
    d[2] = pos[2] - camera_ctrl_instance->pos[2];
    if (vec3_dot(&v, d) <= (TWindowFukidasi__data_805DCD30[0])) {
        return 1;
    }
    xx = d[0] * d[0];
    yy = d[1] * d[1];
    zz = d[2] * d[2];
    if (zz + (xx + yy) > 40.0f * m + 14400.0f) {
        return 1;
    }
    ((TUnk_804CF0B8 *)arg0)->sub_80252C68();
    return ((TUnk_804CF0B8 *)arg0)->get_flag_bit1() != 0 ? 1 : 0;
}

void TUnk_804CF0B8::follow_anchor() {
    Fuki_80251594 *b = (Fuki_80251594 *)this;
    f32 cx;
    f32 cy;
    f32 dx;
    f32 dy;

    cx = 0.5f * b->anchor[0] + b->rect[0];
    cy = 0.5f * b->anchor[1] + b->rect[1];
    if (b->options & 0x40) {
        b->center[0] = cx;
        b->center[1] = cy;
    } else {
        dx = 0.21f * (cx - b->center[0]);
        dy = 0.21f * (cy - b->center[1]);
        if (fabs_float(dx) < 0.1f) {
            b->center[0] = cx;
        } else {
            b->center[0] += dx;
        }
        if (fabs_float(dy) < 0.1f) {
            b->center[1] = cy;
        } else {
            b->center[1] += dy;
        }
    }
    if (b->steps == 0) {
        b->size[0] = b->anchor[0];
        b->size[1] = b->anchor[1];
    } else {
        b->size[0] += (b->anchor[0] - b->size[0]) / (f32)b->steps;
        b->size[1] += (b->anchor[1] - b->size[1]) / (f32)b->steps;
        b->steps--;
    }
    b->pos[0] = b->center[0] - 0.5f * b->size[0];
    b->pos[1] = b->center[1] - 0.5f * b->size[1];
    ((TUnk_804CF0B8 *)b)->clamp_position(b->pos, b->margin);
    b->center[0] = 0.5f * b->size[0] + b->pos[0];
    b->center[1] = 0.5f * b->size[1] + b->pos[1];
    project_anchor(NULL, b->head);
}

void TWindowFukidasi__sub_80251790(TUnk_804CF0B8 *b) {
    u32 flags;

    if (b->is_active() != 0 && b->m_5c < 0x1000000) {
        b->m_5c += TWindowSubStatusDisp::get_card_window_flags(b->m_20) + 1;
    }
    flags = b->m_2cu;
    if ((flags & 2) && (!(flags & 1) || (flags & 4))) {
        b->m_2cu &= ~4;
        b->sub_802504A8();
    }
}

void TWindowFukidasi::get_boundary_offset(s32 angle, f32 *out) {
    f32 ax;
    f32 ay;
    f32 kx;
    f32 ky;
    s32 neg;
    ax = 0.5f * (0.5f * this->m_38 + 14.0f);
    ay = 0.5f * (0.5f * this->m_3c + 10.0f);
    out[0] = ax * cos_table_lookup(angle);
    out[1] = ay * sin_table_lookup(angle);
    if ((angle + 0x2000) & 0x4000) {
        kx = sin_table_lookup(angle - 0x4000) / cos_table_lookup(angle - 0x4000);
        if (!(angle & 0x8000)) {
            kx = -kx;
        }
        if (angle & 0x8000) {
            ky = -1.0f;
        } else {
            ky = 1.0f;
        }
    } else {
        neg = (angle + 0x2000) & 0x8000;
        if (neg) {
            kx = -1.0f;
        } else {
            kx = 1.0f;
        }
        ky = sin_table_lookup(angle) / cos_table_lookup(angle);
        if (neg) {
            ky = -ky;
        }
    }
    out[0] += ax * kx;
    out[1] += ay * ky;
}

void TUnk_804CF0B8::set_color(u16 arg1) {
    this->color = 0xFFF8F8F8;
    if (((u32)arg1 < 0xCU) && (get_player_by_client_id((u32)arg1) != 0U) && (obj_isState3_324__9TObjCharaFv() == 0)) {
        this->color = TWindowFukidasi__balloon_color_table[(u16)arg1];
    }
}

s32 TUnk_804CF0B8::clamp_position(void *arg1, f32 farg0) {
    f32 *point = (f32 *)arg1;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    s32 var_r31;

    var_r31 = 0;
    temp_f1 = 20.0f + ((TWindowCtrlMain *)(s32)this->m_20)->get_position_z();
    if (point[0] < temp_f1) {
        point[0] = temp_f1;
        var_r31 = 1;
    }
    temp_f1_2 = (((TWindowCtrlMain *)(s32)this->m_20)->get_ctrl_field14() - 20.0f) - (this->m_48 * farg0);
    if (point[0] > temp_f1_2) {
        point[0] = temp_f1_2;
        var_r31 = 1;
    }
    temp_f1_3 = 40.0f + ((TWindowCtrlMain *)(s32)this->m_20)->get_field10();
    if (point[1] < temp_f1_3) {
        point[1] = temp_f1_3;
        var_r31 = 1;
    }
    temp_f1_4 = (((TWindowCtrlMain *)(s32)this->m_20)->get_field_18() - 40.0f) - (this->m_4c * farg0);
    if (point[1] > temp_f1_4) {
        point[1] = temp_f1_4;
        var_r31 = 1;
    }
    return var_r31;
}

void TWindowFukidasi::open(u32 *parts, s32 flags) {
    s32 var_r31;
    u8 temp_r0;

    var_r31 = 0;
    this->init_flags(flags);
    if (this->m_72 != 1) {
        this->m_72 = 1;
        ((TWindowSubStatusDisp *)&this->m_24)->destroy_all_items();
        ((TWindowSubSymbolChat *)&this->m_24)->init_layout_entries(this->m_20);
        if (this->m_70 != 0) {
            var_r31 = 1;
        }
    } else {
        temp_r0 = this->m_70;
        if ((temp_r0 != 0) && (temp_r0 != 4)) {
            var_r31 = 1;
        }
    }
    if (var_r31 != 0) {
        this->m_70 = 5;
        this->clear_flag();
        if (TWindowSubStatusDisp::get_card_window_scale(this->m_20) > (TWindowFukidasi__data_805DCD30[0])) {
            this->m_5c = 0;
        }
    }
    set_symbol_chat_parts__20TWindowSubSymbolChatFiPv((s32)&this->m_24, parts);
    TWindowSubSymbolChat::play_symbol_sound((*parts >> 5U) & 0xF);
    this->m_74 = 0x5A;
}

void TWindowFukidasi::set_text(const char *str, s32 flags) {
    u32 len;
    Entry_80250380 *e;
    this->init_flags(flags);
    this->clear_flag();
    if (this->m_72 != 0) {
        this->m_72 = 0;
        ((TWindowSubStatusDisp *)&this->m_24)->destroy_all_items();
        init_window_layout_entries(&this->m_24, &window_fukidasi_layout_entries.value, this->m_20);
    }
    e = (Entry_80250380 *)this->get_array_entry(0);
    if (flags & 1) {
        set_text_entry_string((u8 *)e, (u32)str, 0x20);
    } else {
        set_text_entry_string((u8 *)e, (u32)str, 0);
    }
    if (flags & 4) {
        e->flags |= 0x40;
        refresh_status_display__9TWindowDDFv(e);
    } else {
        measure_message_text_width(e, 200.0f);
    }
    if (flags & 0x80) {
        e->flags |= 0x200;
    } else {
        e->flags &= ~0x200;
    }
    e->color = 0xFF000000;
    len = TWindowKeyBoardSoft::strnlen((s8 *)str, 0x100);
    this->m_74 = (s16)((3.3f * (f32)len) + 55.5f);
    if (TWindowSubStatusDisp::get_card_window_scale(this->m_20) > (TWindowFukidasi__data_805DCD30[0])) {
        this->m_5c = 0;
    }
    play_sound_effect(0x53705, 0, 0, 0);
    if (this->m_70 != 0) {
        this->m_70 = 5;
    }
}

// Original pool emits 1000000.0 before init_flags' 60000 literal.
__declspec(section ".sdata2") extern const f32 lbl_805DCD54[1] = {1000000.0f};

void TWindowFukidasi::init_flags(s32 flags) {
    this->m_58 = (f32) (TWindowFukidasi__data_805DCD30[0]);
    ((TLobby *)this)->set_field_1c(60000.0f);
    if (this->sub_80246948() != 0) {
        this->m_2c = (s32) (this->m_2c | 1);
    }
    this->m_71 = (u8) (this->m_71 & ~0x50);
    if (flags & 2) {
        this->m_71 = (u8) (this->m_71 | 8);
    } else {
        this->m_71 = (u8) (this->m_71 & 0xFFFFFFF7);
    }
    if (flags & 0x20) {
        this->m_71 = (u8) (this->m_71 | 2);
        this->set_flag();
        this->set_flag2c_bit200();
        this->m_73 = 4;
        return;
    }
    this->m_71 = (u8) (this->m_71 & 0xFFFFFFFD);
}

void TUnk_804CF0B8::sub_80251DF0(u16 arg1, s32 str, s16 arg3, f32 farg0) {
    s32 temp_r3;

    this->m_name = window_fukidasi_class_name;
    this->m_70 = 0;
    this->m_71 = 0;
    this->m_72 = 2;
    this->m_73 = -1;
    this->speaker_id = arg1;
    this->m_20 = arg3;
    if (str != 0) {
        temp_r3 = TWindowKeyBoardSoft::strnlen((s8 *)str, (u32)0x18);
        this->name = (char *)::operator new[](temp_r3 + 1);
        strncpy((s32)this->name, str, temp_r3 + 1);
    } else {
        this->name = NULL;
    }
    this->set_color(arg1);
    this->m_80 = (f32) (TWindowFukidasi__data_805DCD30[0]);
    this->m_7c = farg0;
    this->m_48 = (f32) (TWindowFukidasi__data_805DCD30[0]);
    this->m_4c = (f32) (TWindowFukidasi__data_805DCD30[0]);
    this->clear_flag();
    this->clear_flag2c_bit100();
}

// The original entry receives the window, draw context and color.
struct NamePlateQuad { f32 x0, y0, x1, y1, u0, v0, u1, v1; };
extern "C" {
void apply_context_transform_to_rect(TWindowDrawContext *ctx, f32 *rect);
void set_text_draw_params(TWindowDrawContext *, s32, s32, f32, f32);
}
void TUnk_804CF0B8::draw_name_plate(TWindowDrawContext *ctx, u32 color) {
    f32 pos[2];
    NamePlateQuad q;
    f32 depth, width;
    u32 textColor, plateColor;
    if (this->name && ctx->open_tick >= 0) {
        width = (f32)(u32)get_name_text_width(this->name);
        s32 alpha = ctx->open_tick < 6 ? (s32)(0.16666667f * (f32)(ctx->open_tick * 255)) : 255;
        textColor = (u32)alpha << 24;
        plateColor = color & 0x00ffffff;
        plateColor |= textColor;
        pos[0] = ctx->x - 11.0f;
        pos[1] = ctx->y - 10.0f;
        depth = -1.0f / (0.0598f + ctx->depth);
        begin_screen_draw(1);
        TWindowSubStatusDisp::render_forward();
        set_draw_texture_and_color(0, plateColor);
        q.x0 = pos[0]; q.y0 = pos[1]; q.x1 = 16.0f + q.x0; q.y1 = (lbl_805DCD10[0]) + q.y0;
        q.u0 = 0.56640625f; q.v0 = 0.92578125f; q.u1 = 0.62890625f; q.v1 = 1.0f;
        apply_context_transform_to_rect(ctx, &q.x0); draw_textured_quad_at_depth(&q.x0, depth);
        f32 right;
        if (width < 20.0f)
            right = 12.0f + ((20.0f + pos[0]) - 16.0f);
        else
            right = 12.0f + ((pos[0] + width) - 16.0f);
        q.x0 = right; q.y0 = pos[1]; q.x1 = 16.0f + q.x0; q.y1 = (lbl_805DCD10[0]) + q.y0;
        q.u0 = 0.69140625f; q.v0 = 0.92578125f; q.u1 = 0.75390625f; q.v1 = 1.0f;
        apply_context_transform_to_rect(ctx, &q.x0); draw_textured_quad_at_depth(&q.x0, depth);
        if (width > 20.0f) {
            f32 reach = pos[0] + width;
            q.x0 = 16.0f + pos[0]; q.y0 = pos[1];
            q.x1 = (reach - 16.0f) + 12.0f; q.y1 = (lbl_805DCD10[0]) + q.y0;
            q.u0 = 0.62890625f; q.v0 = 0.92578125f; q.u1 = 0.69140625f; q.v1 = 1.0f;
            apply_context_transform_to_rect(ctx, &q.x0); draw_textured_quad_at_depth(&q.x0, depth);
        }
        TWindowSubStatusDisp::get_player();
        f32 textX = pos[0];
        textX += 6.0f;
        pos[0] = textX;
        if (width < 20.0f)
            pos[0] = 0.5f * (20.0f - width) + textX;
        pos[1] += 3.0f;
        set_text_draw_params(ctx, 0, 1, -1.0f / (0.07475f + ctx->depth), 100000.0f);
        draw_small_font_string_clipped(pos, this->name, textColor, (lbl_805DCD54[0]));
    }
}

void TUnk_804CF0B8::draw_tail(TWindowDrawContext *ctx, u32 color, f32 *off, f32 depth) {
    f32 verts[6];
    f32 pos[3];
    Prim_802521E8 prim;
    u32 colors[3];
    f32 scr[2];
    f32 cx;
    f32 cy;
    f32 x0;
    f32 s;
    f32 y0;
    s32 angle;
    if (this->is_balloon_visible() != 0) {
        this->project_anchor(pos, scr);
        cx = this->center[0];
        cy = this->center[1];
        angle = (TWindowFukidasi__data_8044ED70[0]) * atan2_float(cy - scr[1], cx - scr[0]);
        s = (TWindowFukidasi__data_805DCD08[0]) / xyz_distance(camera_ctrl_instance->pos, pos);
        x0 = s * cos_table_lookup(angle) + scr[0];
        y0 = s * sin_table_lookup(angle) + scr[1];
        prim.verts = verts;
        prim.flags = 0;
        prim.colors = colors;
        prim.count = 3;
        colors[2] = colors[1] = colors[0] = (color << 8) | (color >> 24);
        verts[0] = x0;
        verts[1] = y0;
        verts[2] = off[0] + (this->m_80 * (12.0f * cos_table_lookup(angle + 0x4000)) + cx);
        verts[3] = off[1] + (this->m_80 * (12.0f * sin_table_lookup(angle + 0x4000)) + cy);
        verts[4] = off[0] + (this->m_80 * (12.0f * cos_table_lookup(angle - 0x4000)) + cx);
        verts[5] = off[1] + (this->m_80 * (12.0f * sin_table_lookup(angle - 0x4000)) + cy);
        ((TObjCMHairMenu *)(&prim))->draw_tri_fan_2d(3, 2, 0.04485f + this->m_54);
    }
}

void TUnk_804CF0B8::draw_body_row(BalloonSlice *s, TWindowDrawContext *ctx, f32 offsetX, f32 rowTop, f32 fullWidth, f32 rowHeight) {
    f32 left;
    f32 cap;
    f32 w;

    if (fullWidth < 64.0f) {
        cap = 0.5f * fullWidth;
    } else {
        cap = 32.0f;
    }
    left = offsetX + (this->m_40 - 0.342f * rowTop);

    s->x = left;
    s->width = cap;
    s->lean = 0.342f * -rowHeight;
    s->u = 0.3828125f;
    s->uw = cap / 256.0f;
    s->x = ctx->pivot[0] + ctx->scale[0] * (s->x - ctx->pivot[0]);
    s->width *= ctx->scale[0];
    s->lean *= ctx->scale[0];
    DVDConvertEntrynumToPath(&s->x);
    s->x = left + fullWidth - cap;
    s->x = ctx->pivot[0] + ctx->scale[0] * (s->x - ctx->pivot[0]);
    s->u = (194.0f - cap) / 256.0f;
    DVDConvertEntrynumToPath(&s->x);
    w = (fullWidth - 64.0f) * ctx->scale[0];
    if (w >= (TWindowFukidasi__data_805DCD30[0])) {
        s->x = 32.0f + left;
        s->x = ctx->pivot[0] + ctx->scale[0] * (s->x - ctx->pivot[0]);
        s->width = w;
        s->u = 0.5078125f;
        DVDConvertEntrynumToPath(&s->x);
    }
}

void TUnk_804CF0B8::draw_body(TWindowDrawContext *ctx, u32 argb, f32 *offset, f32 depth) {
    BalloonSlice s;
    f32 width;
    f32 capY;
    f32 mid;
    f32 d;
    f32 t;
    width = this->m_48 + 0.342f * this->m_4c;
    s.f30 = s.f2c = s.f10 = TWindowFukidasi__data_805DCD30[0];
    begin_screen_draw(1);
    set_current_texture_list((GinjaTextureList *)(lbl_805D63F0));
    set_draw_texture_and_color(1, argb);
    if (this->m_4c < 64.0f) {
        capY = 0.5f * this->m_4c;
    } else {
        capY = 32.0f;
    }
    s.z = -1.0f / depth;
    s.y = this->m_44 + offset[1];
    s.rowHeight = capY;
    s.v = TWindowFukidasi__data_805DCD30[0];
    f32 recip = 0.00390625f;
    s.vh = capY * recip;
    s.y = ctx->pivot[1] + ctx->scale[1] * (s.y - ctx->pivot[1]);
    s.rowHeight *= ctx->scale[1];
    draw_body_row(&s, ctx, offset[0], TWindowFukidasi__data_805DCD30[0], width, capY);
    s.y = (this->m_4c + (this->m_44 + offset[1])) - capY;
    s.y = ctx->pivot[1] + ctx->scale[1] * (s.y - ctx->pivot[1]);
    f32 edge = 96.0f;
    t = edge - capY;
    s.v = t * recip;
    draw_body_row(&s, ctx, offset[0], this->m_4c - capY, width, capY);
    d = this->m_4c - 64.0f;
    mid = d * ctx->scale[1];
    if (mid >= TWindowFukidasi__data_805DCD30[0]) {
        f32 y = 32.0f + this->m_44;
        s.y = y + offset[1];
        s.y = ctx->pivot[1] + ctx->scale[1] * (s.y - ctx->pivot[1]);
        s.v = 0.125f;
        s.rowHeight = mid;
        draw_body_row(&s, ctx, offset[0], 32.0f, width, d);
    }
    TWindowSubStatusDisp::get_player();
}

void TUnk_804CF0B8::render() {
    f32 off[2];
    TWindowDrawContext *v;
    switch (this->m_70) {
    case 0:
        this->project_anchor(NULL, this->head);
        this->place_rect_at_head_or_slot();
        this->center[0] = 0.5f * this->m_38 + this->m_30;
        this->center[1] = 0.5f * this->m_3c + this->m_34f;
        this->m_70 = 1;
        break;
    case 2:
        ((void (*)(void *))refresh_rect_placement__15TWindowFukidasiFPv)(this);
        break;
    case 4:
        ((void (*)(void *))refresh_rect_placement__15TWindowFukidasiFPv)(this);
        break;
    case 6:
        ((void (*)(void *))refresh_rect_placement__15TWindowFukidasiFPv)(this);
        break;
    case 8:
        this->place_rect_at_head_or_slot();
        break;
    case 9:
        break;
    }
    this->follow_anchor();
    v = get_draw_context__11TWindowBaseFPv(this);
    v->scale[0] /= TCameraCtrl::get_view_scale();
    v->scale[1] /= TCameraCtrl::get_fov();
    off[0] = 3.0f * this->m_80;
    off[1] = 2.5f * this->m_80;
    draw_body(v, 0xFF000000, off, 0.0299f + this->m_54);
    this->draw_tail(v, 0xFF000000, off, lbl_805DCDC0[0] + this->m_54);
    off[0] = TWindowFukidasi__data_805DCD30[0];
    off[1] = TWindowFukidasi__data_805DCD30[0];
    draw_body(v, this->color, off, lbl_805DCDC0[0] + this->m_54);
    this->draw_tail(v, this->color, off, 0.04485f + this->m_54);
    if (this->is_active() != 0) {
        draw_visible_window_entries(this, &this->m_24, v);
        this->draw_name_plate(v, this->color);
    }
}

void TUnk_804CF0B8::run_task() {
    switch (this->m_70) {
    case 1:
        this->calc_text_size(&this->m_38);
        this->m_50 = 6;
        this->clear_flag();
        this->set_flag2c_bit100();
        this->m_70 = 2;
    case 2:
        if (approach(1.0f) != 0) {
            this->m_70 = 3;
        }
        sync_display_pos();
        break;
    case 3:
        TWindowFukidasi__sub_80252C38(this);
        this->set_flag2c_bit100();
        this->m_70 = 4;
    case 4:
        if (this->m_71 & 8) {
            this->m_74 = this->m_74 - 1;
            this->m_58 += 0.1f;
            this->m_depth += 0.1f;
            if (this->m_74 < 0) {
                this->m_70 = 7;
            }
        }
        break;
    case 5:
        this->clamp_text_size(&this->m_38);
        this->m_50 = 6;
        this->clear_flag();
        this->set_flag2c_bit100();
        this->m_70 = 6;
    case 6:
        if (approach(0.5f) != 0) {
            this->m_70 = 1;
        }
        sync_display_pos();
        break;
    case 7:
        this->clear_flag();
        this->clear_flag2c_bit100();
        this->m_2c &= ~1;
        this->m_71 |= 0x10;
        this->m_70 = 8;
    case 8:
        if (approach(TWindowFukidasi__data_805DCD30[0]) != 0) {
            this->m_70 = 9;
        }
        sync_display_pos();
        break;
    case 9:
        this->queue_destruction();
        break;
    }
    TWindowFukidasi__sub_80251790(this);
    if (this->is_active() != 0) {
        this->update_window_entry_list(&this->m_24);
    }
}
}

// Second element is unreferenced; it is the pair at 805DCDC0, not its own literal.
__declspec(section ".sdata2") extern const f32 lbl_805DCDC0[2] = {0.01495f, 0.0f};
