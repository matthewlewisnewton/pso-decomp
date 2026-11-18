#include "types.h"
#include "pso/system/vector.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TLoadCtrl.h"

// Upstream #183 (0fdea2fa9). Opens this unit's .sdata2 at the 8-byte-aligned
// address 0x805DC748. The following float pool is 0x805DC74C..0x805DC760.
extern const u32 lbl_805DC748 = 1;

struct RecoveredGlobal_8022727C_lbl_804CB850 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_802272B4_lbl_804CB850 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80227248_lbl_804CB850 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80226CB0_lbl_804CB850 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80226CF4_lbl_804CB850 {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_8022733C_lbl_804CB850 {
    s32 value;
    u8 remaining[0x8];
};

struct Ent_802269B4 {
    s32 flags;
    s32 f4;
    u32 f8;
    u8 pad[0x18 - 0xC];
    s16 timer;
    u8 pad2[0x28 - 0x1A];
};

struct Passage_80226FA0 { s16 first, repeat, count, transition, next; };

struct Program_80226FA0 { char archive[32]; s32 count, ntsc, pal; Passage_80226FA0 *modes[2]; };

extern "C" {
int TLobby__sub_80226308(void);
    extern int lbl_805D62B0;
    extern int lbl_805D62B4;
    extern int lbl_805D62B8;
int TLobby__sub_80226B64(void);
int set_and_notify__6TLobbyFi(void*);
void start_audio_stream_file(void *, s32);
void play_cue_stream_file(s32 arg0);
s32 TLobby__sub_803C94DC(int, int);
s32 TLobby__sub_803C9CB0(int);
extern s32 lbl_805D62E4;
extern s32 music_fade_slot_index;
void TLobby__sub_802272B4(void);
s32 set_field_40_and_notify__6TLobbyFs(int, int);
void set_cue_stream_gain(s32 arg0);
void TLobby__sub_8022733C(void);
void *get_player_by_client_id(s32 i);
void stop_sound_request(s32 idx);
s32 fn_802264B8(int, int);
s32 TLobby__sub_8023F880(s32 arg0);
s32 TLobby__sub_803C5D00(void *);
s32 TLobby__sub_803C97B8(u8 *arg0);
}
void stop_audio_stream(u8 *arg0);
extern s32 lbl_804CB850[];
extern s32 lbl_805D6330;
extern s32 lbl_805D6300;
extern s32 music_target_id;
void set_dark_falz_music_request(s32 arg0);
void stop_cue_stream(void);
extern u8 *lobby_current_slot_entry;
void set_music_streams_volume(s32 arg0);
void update_music_fade(void);
extern Ent_802269B4 lbl_805145F0[];
extern f32 lbl_80514C50[];
extern u32 camera_ctrl_instance;
extern s32 local_client_id;
extern s8 lbl_805D6279;
void update_sound_request_slots(void);
void append_music_stream_segment(u8 *arg0, s32 arg1, s32 arg2);
extern s32 lbl_805D62E0;
extern s32 lbl_805D62F0;
extern s32 lbl_805D62F4;
extern Program_80226FA0 *lbl_805D6304;
extern s32 music_sequencer_passage_index;
extern s32 music_passage_index;
extern s32 lbl_805D6310;
extern s32 music_active_mode_index;
extern s32 music_sequencer_fade_state;
extern s32 music_sequencer_timer;
extern s16 lbl_805D6334;
void update_music_sequencer(void);
extern "C" {
void TLobby__sub_8022644C(void);

void TLobby::update_lobby_subsystems() { TLobby__sub_8022644C(); stop_cue_stream(); }

// Dead-stripped from the DOL: no code of it survives. The TU's .sdata2 pool opens
// with 0.0 (0x805DC74C) ahead of check_sound_admission_range's 90000/40/260/127
// although that function loads 0.0 last, so a function before it used 0.0 first.
// From upstream #183 (0fdea2fa9), unchanged. The fork's real functions do not
// reference 0.0 first.
void clear_sound_listener_position(void) {
    lbl_80514C50[2] = 0.0f;
    lbl_80514C50[1] = 0.0f;
    lbl_80514C50[0] = 0.0f;
}

f32 xz_distance_squared(const Vec *a, const Vec *b);
f32 newton_sqrtf(f32 x);

s32 check_sound_admission_range(const Vec *pos) {
    if (pos == NULL) {
        return 0;
    }
    if (camera_ctrl_instance == 0U) {
        return 0;
    }
    f32 dist_sq = xz_distance_squared(pos, (const Vec *)lbl_80514C50);
    if (dist_sq < 90000.0f) {
        f32 t = (newton_sqrtf(dist_sq) - 40.0f) / 260.0f;
        return (s32)-(127.0f * (t > 0.0f ? t : 0.0f));
    }
    return -0x100;
}
}

void update_sound_request_slots(void) {
    s32 i;
    s32 r;
    u32 p;
    Ent_802269B4 *e;
    s16 *t;
    if (lbl_805D62B0 != 0) {
        p = (u32)get_player_by_client_id((local_client_id));
        if (p != 0U) {
            VecCopy((Vec *)lbl_80514C50, (const Vec *)(p + 0x38));
        } else if (camera_ctrl_instance != 0U) {
            VecCopy((Vec *)lbl_80514C50, (const Vec *)(camera_ctrl_instance + 0x178));
        } else {
            lbl_80514C50[2] = 0.0f;
            lbl_80514C50[1] = 0.0f;
            lbl_80514C50[0] = 0.0f;
        }
        if (lbl_805D6279 == 0) {
            for (i = 0; i < 0x28; i++) {
                r = TLobby__sub_8023F880(i);
                if (r == -1 || r == 1) {
                    e = &lbl_805145F0[i];
                    t = &e->timer;
                    e->flags &= ~0x200;
                    if (*t > 0) {
                        (*t)--;
                        if ((e->flags & 0x1000) && e->f8 != 0U && fn_802264B8(i, 1) == 0) {
                            *t = 0;
                            stop_sound_request(i);
                            e->flags &= ~0x400;
                        }
                    } else {
                        stop_sound_request(i);
                        e->flags &= ~0x400;
                    }
                } else {
                    e = &lbl_805145F0[i];
                    if (!(e->flags & 0x200)) {
                        e->flags &= ~0x400;
                    } else {
                        e->timer--;
                        if (e->timer <= 0) {
                            e->flags &= ~0x600;
                            stop_sound_request(i);
                        }
                    }
                }
            }
        }
        update_music_fade();
    }
}

int TLobby__sub_80226B64(void) { TLobby::update_lobby_subsystems(); TLobby::init_layout_positions(); TLobby__sub_80226308(); lbl_805D62B4 = 0; lbl_805D62B8 = 0; lbl_805D62B0 = 1; return 0; }

extern "C" {
extern s8 lbl_805D6278;
extern s32 lbl_805D6280;
extern s32 lbl_805D6294;
extern s32 lbl_805D62A8;
extern s32 lbl_805D62BC;
extern s32 lbl_805D62C0;
extern s32 lbl_805D62C4;
extern s32 lbl_805D62C8;
extern s16 lbl_805D62CC;
extern s8 lbl_805D62CE;
extern s8 lbl_805D62CF;
extern s8 lbl_805D62D0;
extern s8 lbl_805D62D1;
extern u8 lbl_80514C30[0x20];

s32 TLobby__sub_80226BA4(void) {
    s32 i;
    lbl_805D6278 = 0;
    lbl_805D62C4 = 0;
    lbl_805D62CC = 0;
    lbl_805D62C8 = 0;
    lbl_805D62C0 = 0;
    lbl_805D62BC = 0;
    lbl_805D62D0 = 0;
    lbl_805D62CE = 0;
    lbl_805D62CF = 0;
    lbl_805D62D1 = 0;
    lbl_805D62B0 = 1;
    lbl_805D6279 = 0;
    lbl_805D62B8 = 0;
    lbl_80514C30[0] = 0;
    lbl_805D6280 = 0;
    lbl_805D62A8 = 0;
    lbl_805D6294 = 0;
    TLobby::init_layout_positions();
    for (i = 0; i < 40; i++) {
        lbl_805145F0[i].flags = 1;
    }
    return 1;
}
}

extern "C" char lbl_80514D00[2][0x20];
u8 *TLobby::get_current_slot_entry() {
    if ((s32) lbl_805D62E4 == 1) {
        return (u8 *)lbl_80514D00[music_fade_slot_index];
    }
    return lobby_current_slot_entry;
}

int TLobby::set_and_notify_default() { return set_and_notify__6TLobbyFi((void*)(0)); }
int TLobby::send_neg30() { return set_and_notify__6TLobbyFi((void*)(-30)); }

typedef char RecoveredGlobal_80226CB0_lbl_804CB850_size[sizeof(RecoveredGlobal_80226CB0_lbl_804CB850) == 0xC ? 1 : -1];
void set_cue_stream_gain(s32 arg0) {
    s32 var_r4;
    var_r4 = arg0;
    if (var_r4 <= -0x140) {
        var_r4 = -0x3E7;
    }
    if ((u32) *(u32 *)((s8 *)(&(*(RecoveredGlobal_80226CB0_lbl_804CB850 *)&lbl_804CB850).value) + 8) != 0U) {
        set_field_40_and_notify__6TLobbyFs((int) (*(u32 *)((s8 *)(&(*(RecoveredGlobal_80226CB0_lbl_804CB850 *)&lbl_804CB850).value) + 8)), var_r4);
    }
}

typedef char RecoveredGlobal_80226CF4_lbl_804CB850_size[sizeof(RecoveredGlobal_80226CF4_lbl_804CB850) == 0xC ? 1 : -1];
void set_music_streams_volume(s32 arg0) {
    s32 var_r31;
    var_r31 = arg0;
    if (var_r31 <= -0x140) {
        var_r31 = -0x3E7;
    }
    if ((s32) lbl_805D6330 == 0) {
        set_field_40_and_notify__6TLobbyFs((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80226CF4_lbl_804CB850 *)&lbl_804CB850).value) + 0)), var_r31);
    }
    set_field_40_and_notify__6TLobbyFs((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_80226CF4_lbl_804CB850 *)&lbl_804CB850).value) + 4)), var_r31);
}
extern "C" {

void TLobby::release_bgm_resource() {
    if ((s32) lbl_805D6330 != 0) {
        stop_audio_stream((u8 *)(*(s32 *)((s8 *)lbl_804CB850 + 4)));
        lbl_805D6330 = 0;
        TLobby::init_layout_positions();
    }
}

extern void *lbl_80514C60[];
extern const char *bgm_stream_files[];
int get_music_base_gain(void);

void TLoadCtrl__sub_80226DA0(s32 index) {
    if (index < 0 || index >= 4) {
        return;
    }
    if (lbl_805D6330 == 0) {
        void *buf;
        TLoadCtrl::step();
        /* the original marks the stream busy while evaluating the call's arguments */
        ((void (*)(const char *, void *))TLobby::set_stream_state)(bgm_stream_files[index],
                                                                    (lbl_805D6330 = 1, buf = lbl_80514C60[0]));
        ((TLobby *)lbl_804CB850[1])->adxt_start_mem_idx((u8 *)buf, 0);
        set_field_40_and_notify__6TLobbyFs(lbl_804CB850[1], get_music_base_gain());
        TLobby__sub_803C94DC(lbl_804CB850[1], 0);
    }
}

void *lbl_80514C60[0x20];
__declspec(section ".data") s32 lbl_80514CE0[2];
__declspec(section ".data") s32 lbl_80514CE8[2];
__declspec(section ".data") s32 lbl_80514CF0[2];
__declspec(section ".data") f32 music_fade_volumes[2];
__declspec(section ".data") char lbl_80514D00[2][0x20];
u8 lbl_80514D40[0x218];
}

extern "C" {
void fn_8036A450(s32 arg0);
int TKeyBoardControl__sub_8000F828(void);
s32 TKeyBoardControl__sub_801E3E24(s32 id, const char *name, void *buf, s32 size);
void TLobby__sub_803C5D24(u8 *arg0);
char *strncpy(char *dst, const char *src, u32 n);
}
extern s16 lbl_805D371C;
extern Program_80226FA0 *music_programs[];

void init_music_sequencer(s32 program) {
    fn_8036A450(program);
    lbl_805D371C = 0;
    TLobby::release_bgm_resource();
    lbl_805D6300 = program;
    lbl_805D6304 = music_programs[program];
    lbl_805D6310 = 0;
    TLobby::stop_audio_streams();
    lbl_805D62E0 = 1;
    lbl_805D62E4 = 1;
    music_fade_slot_index = 0;
    music_sequencer_fade_state = 0;
    music_target_id = 0;
    music_active_mode_index = 0;
    lbl_80514CE8[0] = 0;
    lbl_80514CE8[1] = 0;
    music_sequencer_timer = 0;
    if (TKeyBoardControl__sub_8000F828() == 1) {
        lbl_805D62F4 = lbl_805D6304->pal;
    } else {
        lbl_805D62F4 = lbl_805D6304->ntsc;
    }
    lbl_80514CE0[0] = lbl_805D6304->modes[0][0].first;
    lbl_80514CE0[1] = lbl_80514CE0[0] + 1;
    music_sequencer_passage_index = 0;
    music_passage_index = 1;
    TKeyBoardControl__sub_801E3E24(190, lbl_805D6304->archive, lbl_80514D40, 128);
    append_music_stream_segment((u8 *)lbl_804CB850[0], 190, lbl_80514CE0[0]);
    append_music_stream_segment((u8 *)lbl_804CB850[0], 190, lbl_80514CE0[1]);
    TLobby__sub_803C5D24((u8 *)lbl_804CB850[0]);
    TLobby::close_option_window();
    strncpy(lbl_80514D00[0], lbl_805D6304->archive, 32);
    strncpy(lbl_80514D00[1], lbl_805D6304->archive, 32);
}
void update_music_sequencer(void) {
    Passage_80226FA0 *passage;
    Passage_80226FA0 *next;
    if (lbl_805D62E0 != 1) {
        return;
    }
    if (lbl_805D62E4 != 1) {
        return;
    }
    lbl_80514CE8[music_fade_slot_index]++;
    if (music_sequencer_timer > 0) {
        music_sequencer_timer--;
    } else if (music_sequencer_fade_state == 0 && music_target_id != music_active_mode_index) {
        music_sequencer_fade_state = 1;
        music_sequencer_timer = 600;
    }
    if (lbl_80514CE8[music_fade_slot_index] < lbl_805D62F4 && TLobby__sub_803C5D00((void *)((s32 *)&lbl_804CB850)[0]) != 1) {
        return;
    }
    passage = &lbl_805D6304->modes[music_active_mode_index][music_sequencer_passage_index];
    switch (music_sequencer_fade_state) {
    case 0:
        if (++music_passage_index >= passage->count) {
            music_sequencer_passage_index = passage->next;
            music_passage_index = 0;
            next = &lbl_805D6304->modes[music_active_mode_index][music_sequencer_passage_index];
            if (lbl_805D6310) {
                lbl_805D62F0 = next->repeat;
            } else {
                lbl_805D62F0 = next->first;
                lbl_805D6310 = 1;
            }
        } else {
            lbl_805D62F0 = passage->first + music_passage_index;
        }
        break;
    case 1:
        music_sequencer_passage_index = passage->next;
        music_passage_index = 0;
        music_active_mode_index = 1 - music_active_mode_index;
        music_sequencer_timer = 600;
        if (passage->transition >= 0) {
            lbl_805D62F0 = passage->transition;
            music_sequencer_fade_state = 2;
        } else {
            lbl_805D62F0 = lbl_805D6304->modes[music_target_id][music_sequencer_passage_index].first;
            lbl_805D6310 = 1;
            music_sequencer_fade_state = 0;
        }
        break;
    case 2:
        if (lbl_805D6310) {
            lbl_805D62F0 = passage->repeat;
        } else {
            lbl_805D62F0 = passage->first;
            lbl_805D6310 = 1;
        }
        music_sequencer_fade_state = 0;
        break;
    }
    lbl_80514CE0[music_fade_slot_index] = lbl_805D62F0;
    lbl_805D6334 = music_fade_slot_index;
    append_music_stream_segment((u8 *)((void *)((s32 *)&lbl_804CB850)[0]), 190, lbl_80514CE0[music_fade_slot_index]);
    music_fade_slot_index = 1 - music_fade_slot_index;
    lbl_80514CE8[music_fade_slot_index] = 0;
    lbl_80514CF0[music_fade_slot_index] = TLobby__sub_803C97B8((u8 *)((void *)((s32 *)&lbl_804CB850)[music_fade_slot_index]));
}

void set_dark_falz_music_request(s32 arg0) {
    if ((s32) lbl_805D6300 == 4) {
        music_target_id = arg0;
    }
}

void TLobby::set_target_id(s32 arg0) {
    if ((s32) lbl_805D6300 != 4) {
        music_target_id = arg0;
    }
}
typedef char RecoveredGlobal_8022727C_lbl_804CB850_size[sizeof(RecoveredGlobal_8022727C_lbl_804CB850) == 0xC ? 1 : -1];

typedef char RecoveredGlobal_80227248_lbl_804CB850_size[sizeof(RecoveredGlobal_80227248_lbl_804CB850) == 0xC ? 1 : -1];
void stop_cue_stream(void) {
    if ((u32) *(u32 *)((s8 *)(&(*(RecoveredGlobal_80227248_lbl_804CB850 *)&lbl_804CB850).value) + 8) != 0U) {
        stop_audio_stream((u8 *)((int) (*(u32 *)((s8 *)(&(*(RecoveredGlobal_80227248_lbl_804CB850 *)&lbl_804CB850).value) + 8))));
    }
}

void play_cue_stream_file(s32 name) {
    if ((void *) *(u8 **)((s8 *)(&(*(RecoveredGlobal_8022727C_lbl_804CB850 *)&lbl_804CB850).value) + 8) != NULL) {
        start_audio_stream_file(*(u8 **)((s8 *)(&(*(RecoveredGlobal_8022727C_lbl_804CB850 *)&lbl_804CB850).value) + 8), name);
    }
}
typedef char RecoveredGlobal_802272B4_lbl_804CB850_size[sizeof(RecoveredGlobal_802272B4_lbl_804CB850) == 0xC ? 1 : -1];
void TLobby__sub_802272B4(void) {
    s32 temp_r3;
    TLobby__sub_803C94DC((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_802272B4_lbl_804CB850 *)&lbl_804CB850).value) + (music_fade_slot_index * 4))), 0);
    TLobby__sub_803C94DC((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_802272B4_lbl_804CB850 *)&lbl_804CB850).value) + 8)), 0);
    temp_r3 = TLobby__sub_803C9CB0((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_802272B4_lbl_804CB850 *)&lbl_804CB850).value) + (music_fade_slot_index * 4))));
    if ((temp_r3 == 0) || (temp_r3 == 5)) {
        lbl_805D62E4 = 0;
        return;
    }
    lbl_805D62E4 = 1;
}
typedef char RecoveredGlobal_8022733C_lbl_804CB850_size[sizeof(RecoveredGlobal_8022733C_lbl_804CB850) == 0xC ? 1 : -1];
void TLobby__sub_8022733C(void) {
    TLobby__sub_803C94DC((int) (*(s32 *)((s8 *)((u8 *)(&(*(RecoveredGlobal_8022733C_lbl_804CB850 *)&lbl_804CB850).value) + (music_fade_slot_index * 4)) + 0)), 1);
    TLobby__sub_803C94DC((int) (*(s32 *)((s8 *)(&(*(RecoveredGlobal_8022733C_lbl_804CB850 *)&lbl_804CB850).value) + 8)), 1);
    lbl_805D62E4 = 2;
}

extern "C" {
s32 music_active_mode_index;
s32 music_target_id;
s32 music_sequencer_fade_state;
s32 music_sequencer_timer;
}

// Stream resources and passage programs selected by the music sequencer.
extern "C" {
u32 lbl_804CB838[6] = {0, 0, 0, 0, 0, 0};
}

s32 lbl_804CB850[3] = {0, 0, 0};

static __declspec(section ".rodata") const char bass_stream_name[] ATTRIBUTE_ALIGN(4) = "bass.acx";
static __declspec(section ".rodata") const char map1_stream_name[] ATTRIBUTE_ALIGN(4) = "map1.acx";
static __declspec(section ".rodata") const char map2_stream_name[] ATTRIBUTE_ALIGN(4) = "map2.acx";
static __declspec(section ".rodata") const char quest_stream_name[] ATTRIBUTE_ALIGN(4) = "quest.acx";

const char *bgm_stream_files[] = {bass_stream_name, map1_stream_name, map2_stream_name, quest_stream_name, NULL};

// Area music: each program names its .afs archive and two passage lists (modes[0]/[1]).
static Passage_80226FA0 forest_mode0_passages[6] = {
    {0, 24, 4, 25, 1},
    {4, 4, 4, 26, 2},
    {8, 8, 4, 27, 3},
    {12, 12, 4, 28, 4},
    {16, 16, 4, 29, 5},
    {20, 20, 4, 30, 0},
};
static Passage_80226FA0 forest_mode1_passages[6] = {
    {31, 55, 4, 56, 1},
    {35, 35, 4, 57, 2},
    {39, 39, 4, 58, 3},
    {43, 43, 4, 59, 4},
    {47, 47, 4, 60, 5},
    {51, 51, 4, 61, 0},
};
static Program_80226FA0 forest_music = {"slbgm_forest.afs", 6, 146, 242, {forest_mode0_passages, forest_mode1_passages}};

static Passage_80226FA0 ancient_mode0_passages[6] = {
    {0, 0, 4, 24, 1},
    {4, 23, 4, 25, 2},
    {8, 8, 2, 26, 3},
    {10, 10, 4, 27, 4},
    {14, 14, 5, 28, 5},
    {19, 19, 4, 29, 1},
};
static Passage_80226FA0 ancient_mode1_passages[6] = {
    {30, 49, 4, 50, 2},
    {30, 49, 4, 50, 2},
    {34, 34, 2, 51, 3},
    {36, 36, 4, 52, 4},
    {40, 40, 5, 53, 5},
    {45, 45, 4, 54, 1},
};
static Program_80226FA0 ancient_music = {"slbgm_ancient.afs", 6, 184, 298, {ancient_mode0_passages, ancient_mode1_passages}};

static Passage_80226FA0 dark_mode0_passages[2] = {
    {0, 0, 2, -1, 1},
    {2, 12, 10, -1, 1},
};
static Passage_80226FA0 dark_mode1_passages[2] = {
    {13, 21, 8, -1, 0},
    {13, 21, 8, -1, 0},
};
static Program_80226FA0 dark_music = {"slbgm_dark.afs", 2, 321, 268, {dark_mode0_passages, dark_mode1_passages}};

static Passage_80226FA0 cave_mode0_passages[6] = {
    {0, 24, 4, 25, 1},
    {4, 4, 4, 26, 2},
    {8, 8, 4, 27, 3},
    {12, 12, 4, 28, 4},
    {16, 16, 4, 29, 5},
    {20, 20, 4, 30, 0},
};
static Passage_80226FA0 cave_mode1_passages[6] = {
    {31, 55, 4, 56, 1},
    {35, 35, 4, 57, 2},
    {39, 39, 4, 58, 3},
    {43, 43, 4, 59, 4},
    {47, 47, 4, 60, 5},
    {51, 51, 4, 61, 0},
};
static Program_80226FA0 cave_music = {"slbgm_cave.afs", 6, 157, 260, {cave_mode0_passages, cave_mode1_passages}};

static Passage_80226FA0 machine_mode0_passages[5] = {
    {0, 20, 4, 21, 1},
    {4, 4, 4, 22, 2},
    {8, 8, 4, 23, 3},
    {12, 12, 4, 24, 4},
    {16, 16, 4, 25, 0},
};
static Passage_80226FA0 machine_mode1_passages[5] = {
    {26, 46, 4, 47, 1},
    {30, 30, 4, 48, 2},
    {34, 34, 4, 49, 3},
    {38, 38, 4, 50, 4},
    {42, 42, 4, 51, 0},
};
static Program_80226FA0 machine_music = {"slbgm_machine.afs", 5, 121, 206, {machine_mode0_passages, machine_mode1_passages}};

static Passage_80226FA0 jungle_mode0_passages[7] = {
    {7, 35, 4, 0, 1},
    {11, 11, 4, 1, 2},
    {15, 15, 4, 2, 3},
    {19, 19, 4, 3, 4},
    {23, 23, 4, 4, 5},
    {27, 27, 4, 5, 6},
    {31, 31, 4, 6, 0},
};
static Passage_80226FA0 jungle_mode1_passages[7] = {
    {36, 64, 4, 65, 1},
    {40, 40, 4, 66, 2},
    {44, 44, 4, 67, 3},
    {48, 48, 4, 68, 4},
    {52, 52, 4, 69, 5},
    {56, 56, 4, 70, 6},
    {60, 60, 4, 71, 0},
};
static Program_80226FA0 jungle_music = {"slbgm_jungle.afs", 7, 156, 206, {jungle_mode0_passages, jungle_mode1_passages}};

static Passage_80226FA0 seabed_mode0_passages[6] = {
    {0, 0, 4, 27, 1},
    {4, 26, 4, 28, 2},
    {8, 8, 4, 29, 3},
    {12, 12, 4, 30, 4},
    {16, 16, 4, 31, 5},
    {20, 20, 6, 32, 1},
};
static Passage_80226FA0 seabed_mode1_passages[6] = {
    {33, 33, 4, 60, 1},
    {37, 59, 4, 61, 2},
    {41, 41, 4, 62, 3},
    {45, 45, 4, 63, 4},
    {49, 49, 4, 64, 5},
    {53, 53, 6, 65, 1},
};
static Program_80226FA0 seabed_music = {"slbgm_seabed.afs", 6, 171, 206, {seabed_mode0_passages, seabed_mode1_passages}};

static Passage_80226FA0 space_mode0_passages[8] = {
    {0, 0, 4, 29, 1},
    {4, 28, 4, 30, 2},
    {8, 8, 2, 31, 3},
    {10, 10, 4, 32, 4},
    {14, 14, 2, 33, 5},
    {16, 16, 4, 34, 6},
    {20, 20, 4, 35, 7},
    {24, 24, 4, 36, 1},
};
static Passage_80226FA0 space_mode1_passages[8] = {
    {41, 65, 4, 66, 1},
    {41, 65, 4, 66, 2},
    {45, 45, 2, 67, 3},
    {47, 47, 4, 68, 4},
    {51, 51, 2, 69, 5},
    {53, 53, 4, 70, 6},
    {57, 57, 4, 71, 7},
    {61, 61, 4, 72, 1},
};
static Program_80226FA0 space_music = {"slbgm_space.afs", 8, 192, 206, {space_mode0_passages, space_mode1_passages}};

static Passage_80226FA0 ruin_mode0_passages[7] = {
    {0, 22, 2, 23, 1},
    {2, 2, 4, 24, 2},
    {6, 6, 2, 25, 3},
    {8, 8, 4, 26, 4},
    {12, 12, 2, 27, 5},
    {14, 14, 4, 28, 6},
    {18, 18, 4, 29, 0},
};
static Passage_80226FA0 ruin_mode1_passages[7] = {
    {30, 52, 2, 53, 1},
    {32, 32, 4, 54, 2},
    {36, 36, 2, 55, 3},
    {38, 38, 4, 56, 4},
    {42, 42, 2, 57, 5},
    {44, 44, 4, 58, 6},
    {48, 48, 4, 59, 0},
};
static Program_80226FA0 ruin_music = {"slbgm_ruin.afs", 7, 171, 206, {ruin_mode0_passages, ruin_mode1_passages}};

Program_80226FA0 *music_programs[] = {
    &forest_music, &cave_music, &machine_music, &ancient_music, &dark_music,
    &jungle_music, &seabed_music, &ruin_music, &space_music,
};
