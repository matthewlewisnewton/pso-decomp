#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_8024FBA8.h"
#include "pso/misc/TLobby_80132ED0.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowSnapShot.h"
#include "pso/misc/SnapshotCaptureAbi.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowDuelResult.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct Base_802A7DDC { char pad[0x3C]; };
struct VObj_802A7DDC : Base_802A7DDC {
    virtual void m0(int);
};

struct Stack_802A7F00 {
    f32 sp8;
    f32 spC;
};

struct RecoveredGlobal_802A7FB0_lbl_8050E208 {
    s32 value;
    u8 remaining[0x1AC];
};

extern const char *player_motion_data_filename_ptr;
extern void *shared_snapshot_capture;
extern "C" {
s32 TObjBoss2Tunnel__sub_8007CAE8(f32 *, f32);
s32 draw_visible_window_entries(void *, void *, void *);
extern const f32 lbl_805DE018;
extern const f32 lbl_805DE01C;
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, int);
s32 TWindowShortListCtrl__check_controller_button(void *, int);
extern RecoveredGlobal_802A7FB0_lbl_8050E208 controller_input_state;
s32 verify_snapshot_checksum__15TObjBoss2TunnelFv(void);
extern WindowLayoutDescriptor window_snapshot_layout;
extern const char *TWindowSnapShot__name;

void __dl__7TObjectFPv(void *);

void free_shared_instance__15TWindowSnapShotFv() {
    struct VObj_802A7DDC *o;
    update_both__15TWindowSnapShotFv((SnapshotCaptureStorage *)shared_snapshot_capture);
    o = (struct VObj_802A7DDC *)shared_snapshot_capture;
    if (o != NULL) {
        o->m0(1);
    }
    shared_snapshot_capture = NULL;
}
}

s32 load_player_motion_data(void) {
    s32 temp_r3;
    s32 var_r0;
    if ((void *) (*(u8 * *)&shared_snapshot_capture) != NULL) {
        return 0;
    }
    temp_r3 = (int)::operator new(0x40);
    var_r0 = temp_r3;
    if (var_r0 != 0) {
        var_r0 = (long) (init_and_reset__15TWindowSnapShotFv((SnapshotCaptureStorage *)temp_r3));
    }
    (*(u8 * *)&shared_snapshot_capture) = (unsigned char *) ((void *) var_r0);
    if ((u32) var_r0 == 0U) {
        return 0;
    }
    start_capture__15TWindowSnapShotFPCv((SnapshotCaptureStorage *)var_r0, player_motion_data_filename_ptr);
    return 1;
}

s32 get_size__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) { return *(s32 *)capture; }
s32 get_field_8__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) { return *(s32 *)((u8 *)capture + 8); }
int get_height__15TWindowSnapShotFv() { return 600; }

const char *TWindowSnapShot__sub_802A7EAC(void) {  return player_motion_data_filename_ptr; }

void TWindowSnapShot::play_open_sound() {
    play_sound_effect(0x52F16, 0, 0, 0);
    this->m_60 = (u8) (this->m_60 | 1);
}

void TWindowSnapShot::render() {
    Stack_802A7F00 stack;
    u8 *temp_r3;
    temp_r3 = ((u8 *)TWindowDD::draw_default_entry((s32)this));
    draw_window_frame(temp_r3);
    draw_visible_window_entries(this, &m_24, temp_r3);
    if (!(m_60 & 2)) {
        if ((s32) *(s32 *)((s8 *)temp_r3 + 0x30) > 0) {
            stack.sp8 = lbl_805DE018 + *(f32 *)((s8 *)temp_r3 + 0x10);
            stack.spC = *(f32 *)((s8 *)temp_r3 + 0x14);
            TObjBoss2Tunnel__sub_8007CAE8(&stack.sp8, lbl_805DE018);
        }
    } else {
        draw_window_text((f32 *)(temp_r3 + 0x10), (const char *)(get_localized_text_entry(0x24, 7)), -1, 0, (f32)lbl_805DE01C);
    }
}

typedef char RecoveredGlobal_802A7FB0_lbl_8050E208_size[sizeof(RecoveredGlobal_802A7FB0_lbl_8050E208) == 0x1B0 ? 1 : -1];
void TWindowSnapShot::run_task() {
    u8 *arg0 = (u8 *)this;
    if (!(this->m_2c & 2)) {
        this->m_5c = 0x01000000;
    }
    if ((TWindowShortListCtrl__check_controller_button((void *) ((u8 *)&controller_input_state.value + 0x20), 2) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.value + 0x160), 2) != 0)) {
        play_open_sound();
    }
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((u8 *)&this->m_24);
}

TWindowSnapShot::~TWindowSnapShot() {}
TWindowSnapShot::TWindowSnapShot(void *position)
    : TWindowBase((u8 *)&window_snapshot_layout, 4, (u8 *)position) {
    s32 temp_r31;
    m_name = TWindowSnapShot__name;
    m_60 = 0U;
    if (verify_snapshot_checksum__15TObjBoss2TunnelFv() == 0) {
        m_60 = (u8) (m_60 | 2);
    }
    temp_r31 = (s32)get_array_entry(1);
    TWindowDuelResult::set_default_status((void *) temp_r31, get_localized_text_entry(0xF, 0x13));
}
