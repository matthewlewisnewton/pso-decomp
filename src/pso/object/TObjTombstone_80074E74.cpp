#include "types.h"
#include "pso/system/vector.h"
#include "pso/object/TObjTombstone.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/player/TObjPlayer.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
// The two callers pass a ten-float drop distribution, not a TObject.
struct TombstoneDropWeights { f32 values[10]; };
typedef char TombstoneDropWeights_size[sizeof(TombstoneDropWeights) == 0x28 ? 1 : -1];

typedef Vec V_80075070;

struct V_800751BC { f32 x, y, z; };

struct View_800751BC {
    u8 pad0[0x178];
    V_800751BC pos;
    u8 pad184[0xC];
    s32 f190;
    s32 f194;
    s32 f198;
};

struct P_800753DC { f32 values[2]; };

struct Off_800753DC { s16 x, y; };

extern "C" {
void *get_player_by_client_id(s32 i);
f32 xyz_distance(void *, void *);
extern const f32 TObjTombstone__data_805D9174;
extern const f32 TObjTombstone__data_805D9178;
extern const f32 TObjTombstone__data_805D917C;
extern const f32 lbl_805D9180;
extern const f32 TObjTombstone__data_805D9184;
extern const TombstoneDropWeights tombstone_reset_matrix_template;
extern f32 TObjTombstone__base_matrix[10];
// Retain the provisional linker label while correcting its receiver model.
void copy_matrix__13TObjTombstoneFPv(f32 *destination, const f32 *source);
f32 vector_length(void *);
void subtract_vector(void *, void *);
extern V_80075070 tombstone_position_table[];
extern s32 local_client_id;
extern const f32 lbl_805D9170;
s32 is_split_screen();
s32 get_screen_width__11TCameraCtrlFv();
s32 get_screen_height__11TCameraCtrlFv();
f32 vec3_dot(void *, void *);
void project_world_to_screen(s32, void *, void *);
void rotate_vector_by_matrix(s32, void *, void *);
void rotate_matrix_y(s32, s32);
void rotate_matrix_z(s32, s32);
void rotate_matrix_x(s32, s32);
void push_matrix_from(void *);
void push_matrix();
void pop_matrix();
extern V_800751BC lbl_80438780;
extern u8 identity_matrix[];
extern View_800751BC *camera_ctrl_instance;
u32 calc_text_width(const char *);
void draw_menu_font_string(const char *, u32, s32, f32, f32, f32);
f32 sin_table_lookup(s32);
u32 strlen(const char *);
s32 is_challenge_mode_active();
s32 get_current_floor();
s32 is_flag_set__6TLobbyFv();

void TObjTombstone__sub_80074E74(f32 *w) {
    f32 one;
    f32 sum;

    sum = w[0] + w[1 & 0xFFu] + w[2] + w[3];
    if (w[0] < TObjTombstone__data_805D9174 || w[1] < TObjTombstone__data_805D9174 ||
        w[2] < TObjTombstone__data_805D9174 || w[3] < TObjTombstone__data_805D9174 ||
        sum > TObjTombstone__data_805D9178) {
        return;
    }
    sum = w[4] + w[5] + w[6] + w[7] + w[8] + w[9];
    one = TObjTombstone__data_805D9178;
    if (w[4] < TObjTombstone__data_805D9174 || w[5] < TObjTombstone__data_805D9174 ||
        w[6] < TObjTombstone__data_805D9174 || w[7] < TObjTombstone__data_805D9174 ||
        w[8] < TObjTombstone__data_805D9174 || w[9] < TObjTombstone__data_805D9174 ||
        sum > one) {
        return;
    }
    copy_matrix__13TObjTombstoneFPv(TObjTombstone__base_matrix, w);
}

// GC/2.6 otherwise schedules alternating float registers for this array copy.
// The original copies each of the ten weights with one load/store pair.
#pragma push
#pragma scheduling off
void copy_matrix__13TObjTombstoneFPv(f32 *destination, const f32 *source) {
    destination[0] = source[0];
    destination[1] = source[1];
    destination[2] = source[2];
    destination[3] = source[3];
    destination[4] = source[4];
    destination[5] = source[5];
    destination[6] = source[6];
    destination[7] = source[7];
    destination[8] = source[8];
    destination[9] = source[9];
}
#pragma pop

void TObjTombstone::reset_matrix() {
    TombstoneDropWeights defaults = tombstone_reset_matrix_template;
    copy_matrix__13TObjTombstoneFPv(TObjTombstone__base_matrix, defaults.values);
}
}
extern Off_800753DC tombstone_name_label_offset_table[];
extern const f32 lbl_805D9188;
extern const f32 lbl_805D918C;
extern const f32 lbl_805D9190;
extern const f32 lbl_805D9194;
extern const f32 lbl_805D9198;
extern const f32 lbl_805D919C;
extern const f32 lbl_805D91A0;
void handle_6x96(void);
void handle_6x96(void) {  }
s32 TObjTombstone::check_owner() {
    s32 var_r3;

    if (TRaderMapCore::is_not_split_screen() == 1) {
        var_r3 = is_challenge_mode_active();
    } else {
        var_r3 = is_flag_set__6TLobbyFv();
    }
    if ((var_r3 == 0) || ((s8) this->m_c2 != get_current_floor())) {
        return 1;
    }
    return 0;
}

s32 TObjTombstone::is_other_tombstone_closer() {
    TObjTombstone *arg0 = this;
    f32 best;
    f32 d;
    TObjPlayer *pl;
    void *ppos;
    s32 i;
    best = TObjTombstone__data_805D917C;
    pl = static_cast<TObjPlayer *>(get_player_by_client_id(local_client_id));
    if (pl == 0) {
        return 0;
    }
    ppos = &pl->position;
    for (i = 0; i < 4; i++) {
        if (i != arg0->unk_AC && lbl_805D9170 != tombstone_position_table[i].y) {
            V_80075070 v = tombstone_position_table[i];
            subtract_vector(&v, ppos);
            v.y = TObjTombstone__data_805D9174;
            d = vector_length(&v);
            if (best > d) {
                best = d;
            }
        }
    }
    if (TObjTombstone__data_805D917C == best) {
        return 0;
    }
    V_80075070 w = arg0->position;
    subtract_vector(&w, ppos);
    w.y = TObjTombstone__data_805D9174;
    d = vector_length(&w);
    if (d < best || (d == best && arg0->unk_AC == local_client_id)) {
        return 0;
    }
    return 1;
}

s32 TObjTombstone::project_to_screen(void *arg0, f32 *arg1, void *arg2) {
    V_800751BC d;
    V_800751BC v = lbl_80438780;
    push_matrix_from(identity_matrix);
    rotate_matrix_y(0, camera_ctrl_instance->f194);
    rotate_matrix_x(0, camera_ctrl_instance->f190);
    rotate_matrix_z(0, camera_ctrl_instance->f198);
    rotate_vector_by_matrix(0, &v, &v);
    pop_matrix();
    VecCopy((Vec *)&d, (const Vec *)arg2);
    subtract_vector(&d, &camera_ctrl_instance->pos);
    if (vec3_dot(&v, &d) <= TObjTombstone__data_805D9174) {
        return 0;
    }
    push_matrix();
    project_world_to_screen(0, arg2, arg1);
    pop_matrix();
    if (is_split_screen() != 0) {
        arg1[0] -= (f32)get_screen_height__11TCameraCtrlFv();
        arg1[0] /= TCameraCtrl::get_view_scale();
        arg1[1] -= (f32)get_screen_width__11TCameraCtrlFv();
        arg1[1] /= TCameraCtrl::get_fov();
    }
    return 1;
}

void TObjTombstone::update_fade_by_distance() {
    f32 temp_f1;
    TObjPlayer *player;
    s32 camera = TCameraCtrl::get_camera_no();
    player = static_cast<TObjPlayer *>(get_player_by_client_id(TCameraCtrl::get_nth_view_player_id(camera)));
    if (player != NULL) {
        temp_f1 = xyz_distance(&player->position, &this->position);
        if (temp_f1 <= lbl_805D9180) {
            this->unk_B4 = (f32) TObjTombstone__data_805D9178;
        } else if (temp_f1 >= TObjTombstone__data_805D917C) {
            this->unk_B4 = (f32) TObjTombstone__data_805D9174;
        } else {
            this->unk_B4 = (f32) ((TObjTombstone__data_805D917C - temp_f1) / TObjTombstone__data_805D9184);
        }
        TObjTombstone::draw_name_labels(this);
    }
}
#pragma push
#pragma fp_contract on
#define self (static_cast<TObjTombstone *>(arg0_))
void TObjTombstone::draw_name_labels(void *arg0_) {
    u32 c2;
    u32 c1;
    P_800753DC screen;
    Vec pos;
    f32 m;
    f32 a;
    f32 b;
    u32 alpha;
    if (TObjTombstone__data_805D9174 == self->unk_B4) return;
    VecCopy(&pos, &self->position);
    pos.y += lbl_805D9188;
    if (TObjTombstone::project_to_screen(self, screen.values, &pos) == 0) return;
    m = TObjTombstone__data_805D9174;
    for (s32 i = 0; i < 6; i++) {
        f32 w = calc_text_width(self->name_lines[i]);
        if (m < w) m = w;
    }
    m *= lbl_805D918C;
    if (screen.values[0] - m < TObjTombstone__data_805D9174 || screen.values[0] + m > lbl_805D9190) {
        if ((self->m_b8 += -0.16666667f) < 0.0f) self->m_b8 = 0.0f;
        if ((self->unk_BC += -0.016666668f) < 0.0f) self->unk_BC = 0.0f;
    } else {
        if ((self->m_b8 += 0.16666667f) > 1.0f) self->m_b8 = 1.0f;
        if ((self->unk_BC += 0.16666667f) > 1.0f) self->unk_BC = 1.0f;
    }
    a = self->unk_B4 * self->m_b8;
    b = self->unk_B4 * self->unk_BC;
    alpha = (s32)(lbl_805D9180 * sin_table_lookup(self->m_230 << 8)) + 200;
    c1 = (u32)(alpha * a) << 24;
    c2 = ((u32)(alpha * b) << 24) | 0xFFFFFF;
    for (s32 i = 0; i < 6; i++) {
        char *name;
        P_800753DC p = screen;
        name = self->name_lines[i];
        if (strlen(name) != 0) {
            p.values[0] -= lbl_805D918C * TWindowSubStatusDisp::calc_text_width(name);
            if (a > TObjTombstone__data_805D9174) {
                s32 j;
                for (j = 0; j < 8; j++) {
                    Off_800753DC o = tombstone_name_label_offset_table[j];
                    draw_menu_font_string(name, c1, 1, p.values[0] + o.x, p.values[1] + o.y, lbl_805D918C);
                }
            }
            if (b > TObjTombstone__data_805D9174) {
                draw_menu_font_string(name, c2, 1, p.values[0], p.values[1], lbl_805D918C);
            }
            screen.values[1] += lbl_805D91A0;
        }
    }
}
#undef self
#pragma pop

extern "C" {
__declspec(section ".sdata2") extern const f32 TObjTombstone__data_805D9174 = 0.0f;
__declspec(section ".sdata2") extern const f32 TObjTombstone__data_805D9178 = 1.0f;
__declspec(section ".sdata2") extern const f32 TObjTombstone__data_805D917C = 50.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9180 = 40.0f;
__declspec(section ".sdata2") extern const f32 TObjTombstone__data_805D9184 = 10.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D9188 = 14.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D918C = 0.5f;
__declspec(section ".sdata2") extern const f32 lbl_805D9190 = 640.0f;
}
