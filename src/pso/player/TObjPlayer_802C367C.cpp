#include "pso/player/PlayerLevelTable.h"
#include "types.h"
#include "pso/player/TObjPlayer_802C367C.h"
#include "pso/unk/text_802C3AC0.h"
#include "pso/player/TObjPlayer.h"

typedef struct S_802C3720 {
    u8 pad0[0x3A4];
    u32 f3A4;
} S_802C3720;

struct Char_802C38B4 {
    u8 pad0;
    s8 f1;
    s8 f2;
    u8 pad3[0x34C - 3];
    struct stats stats;
    s16 f35A;
    u8 pad35C[4];
    f32 f360;
    s32 level;
    s32 exp;
    s32 meseta;
};

extern "C" {
s8 *get_action_data__10TObjPlayerFv(void *);
s32 get_current_state_field__10TObjPlayerFcl(char, s32);
extern const f32 lbl_805DE530;
int TObjPlayer__sub_802C456C(void*, void*, void*);
}
int init_character_action_config(void*);
extern "C" {
s32 TObjPlayer__sub_802C46E0(s32, s32, s32, s32, s32);

int init_new_character_data(void* p) { *(unsigned char*)(p) = 0; ((TObjPlayer *)p)->clear_item_slots(); init_character_action_config((char*)p + 0x3c0); init_class_starting_inventory(p); ((TObjPlayer *)p)->m_36c = 300; ((TObjPlayer *)p)->set_action_state((u8)((void*)1)); return 1; }

void TObjPlayer::clear_30_slots() { { int i; for (i = 0; i < 30; i++) { TObjPlayer__sub_802C456C(this, (void*)i, (void*)0); } } }

void TObjPlayer::reset_action_palette() {
    s32 i;
    s8 *p;
    p = get_action_data__10TObjPlayerFv(this);
    for (i = 0; i < 0x14; i++) {
        *p = TObjPlayer::get_item_count_max();
        p++;
    }
    if (((S_802C3720 *)this)->f3A4 & 0x80) {
        ((TObjPlayer *)((S_802C3720 *)this))->set_action_palette_slot(0, 0);
    }
    ((TObjPlayer *)((S_802C3720 *)this))->clear_30_slots();
}

void init_technique_levels(s32 flags, s8 *counts) {
    s32 i;
    s8 *p = counts;
    for (i = 0; i < 0x14; i++, p++) {
        *p = TObjPlayer::get_item_count_max();
    }
    if (flags & 0x80) {
        *counts = 0;
    }
}

void TObjPlayer::setup_effect_slots(s32 arg0, s32 arg1) {
    TObjPlayer__sub_802C46E0(arg1, 0, 0, 1, 0);
    TObjPlayer__sub_802C46E0(arg1, 1, 0, 1, 0);
    TObjPlayer__sub_802C46E0(arg1, 0, 1, 2, 0);
    TObjPlayer__sub_802C46E0(arg1, 0, 2, 2, 1);
    if (arg0 & 0x60) {
        TObjPlayer__sub_802C46E0(arg1, 0, 3, 4, 0);
        return;
    }
    TObjPlayer__sub_802C46E0(arg1, 0, 3, 3, 0);
}

void init_character_stats_for_level(char cls, void *c, s32 level) {
    struct stats st;
    level = TObjPlayer::clamp_index_to_max(level);
    copy_stats__10TObjPlayerFPv(&st, get_class_base_stats(cls));
    if (level != 0) {
        apply_class_level_growth(cls, level, &st);
    }
    ((Char_802C38B4 *)c)->stats.atp = st.atp;
    ((Char_802C38B4 *)c)->stats.mst = st.mst;
    ((Char_802C38B4 *)c)->stats.evp = st.evp;
    ((Char_802C38B4 *)c)->stats.hp = st.hp;
    ((Char_802C38B4 *)c)->stats.dfp = st.dfp;
    ((Char_802C38B4 *)c)->stats.ata = st.ata;
    ((Char_802C38B4 *)c)->stats.lck = st.lck;
    ((Char_802C38B4 *)c)->f35A = 0x28;
    ((Char_802C38B4 *)c)->f360 = lbl_805DE530;
    ((Char_802C38B4 *)c)->level = level;
    ((Char_802C38B4 *)c)->exp = get_current_state_field__10TObjPlayerFcl(cls, level);
    ((Char_802C38B4 *)c)->meseta = 300;
    ((Char_802C38B4 *)c)->f1 = 0;
    ((Char_802C38B4 *)c)->f2 = 0;
    ((TObjPlayer *)c)->set_flag_e7(0);
    ((TObjPlayer *)c)->set_flag_103(0);
    ((TObjPlayer *)c)->set_action_flags(0);
    ((TObjPlayer *)c)->set_byte_13b(0);
    ((TObjPlayer *)c)->set_field_157(0);
}

void init_new_character_stats(void *arg0) {
    init_character_stats_for_level(((char *)arg0)[0x3A1], arg0, 0);
}
}
