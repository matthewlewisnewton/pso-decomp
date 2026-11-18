#include "pso/system/RlcArchive.h"
#include "pso/system/ControllerInputState.h"
#include "types.h"
#include "pso/unk/TUnk_804DDD28.h"
#include "pso/unk/TLobby.h"
#include "pso/ui/window/TWindowSnapShot.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/window/TWindowSnapShot_802A7D68.h"
#include "pso/ui/window/TWindowSubStatusDisp_8024FBA8.h"
#include "pso/unk/TLobby_80132ED0.h"
#include "pso/ui/window/TWindowDrawContext.h"
#include "pso/ui/window/TWindowBase.h"
#include "pso/ui/window/TWindowDD.h"
#include "pso/ui/window/TWindowDuelResult.h"
#include "pso/ui/window/TWindowSubComCard.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"
#include "pso/unk/WindowLayoutRecord.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC_801A6D60.h"
#include "pso/boss/darkfalz/TOBoss4Rock.h"

extern "C" {
extern s32 lbl_805D669C;
}
extern void *shared_snapshot_capture;

extern "C" {

int get_resource_file_size__6TLobbyFv(void);
int Dolphin_ARAlloc(void);

    extern int snapshot_aligned_buffer_size;
void TWindowSnapShot::init_default() { TLobby::aram_transfer_sync((s32)((void*)1), (u32)((void*)((TWindowSnapShot *)shared_snapshot_capture)->get_field_8()), lbl_805D669C, snapshot_aligned_buffer_size); }

void TWindowSnapShot__sub_802A7DA0(void) {  }

void TWindowSnapShot::alloc_buffer() { TWindowSnapShot__sub_802A7EAC(); snapshot_aligned_buffer_size = ((get_resource_file_size__6TLobbyFv() + 0x1f) & 0xffffffe0); lbl_805D669C = Dolphin_ARAlloc(); }

}

struct Base_802A7DDC { char pad[0x3C]; };
struct VObj_802A7DDC : Base_802A7DDC {
    virtual void m0(int);
};

struct Stack_802A7F00 {
    f32 sp8;
    f32 spC;
};

#pragma push
#pragma readonly_strings on
const char *TWindowSnapShot__name = "TWindowSnapShot";
#pragma pop

// inferred: window_snapshot_layout_entries, the layout table window_snapshot_layout points at
// (a sprite part and a text line).
struct SnapShotWindowLayout {
    u32 cols;
    u32 rows;
    SpritePartLayoutRecord rec_0;
    TextLayoutRecord rec_1;
};

extern s32 lbl_805D63F0;

SnapShotWindowLayout window_snapshot_layout_entries = {
    2, 1,
    {6, {372.0f, 240.0f}, {18.0f, 18.0f}, 178.0f, 203.0f, 0.5f, -1, &lbl_805D63F0, 0, 4},
    {3, {399.0f, 240.0f}, 0.5f, 0xFFFFFFFF, 0, NULL},
};

WindowDescriptor window_snapshot_layout = {
    {512.0f, 280.0f}, 50100.0f, &window_snapshot_layout_entries, 3,
};

extern "C" {
s32 TObjBoss2Tunnel__sub_8007CAE8(f32 *, f32);
s32 draw_visible_window_entries(void *, void *, void *);
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, int);
s32 verify_snapshot_checksum__15TObjBoss2TunnelFv(void);
s32 play_sound_effect(s32, s32, s32, s32);

void TWindowSnapShot::free_shared_instance() {
    struct VObj_802A7DDC *o;
    ((TWindowSnapShot *)shared_snapshot_capture)->update_both();
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
        var_r0 = (long) (((TWindowSnapShot *)temp_r3)->init_and_reset());
    }
    (*(u8 * *)&shared_snapshot_capture) = (unsigned char *) ((void *) var_r0);
    if ((u32) var_r0 == 0U) {
        return 0;
    }
    ((TWindowSnapShot *)var_r0)->start_capture((s32)player_motion_data_filename_ptr);
    return 1;
}

s32 TWindowSnapShot::get_size() { return *(s32 *)&this->m_name; }
s32 TWindowSnapShot::get_field_8() { return *(s32 *)&this->m_prev; }
int TWindowSnapShot::get_height() { return 600; }

int TWindowSnapShot__sub_802A7EAC(void) {  return (int)player_motion_data_filename_ptr; }

void TWindowSnapShot::play_open_sound() {
    play_sound_effect(0x52F16, 0, 0, 0);
    this->m_60 = (u8) (this->m_60 | 1);
}

void TWindowSnapShot::render() {
    Stack_802A7F00 stack;
    TWindowDrawContext *context = (TWindowDrawContext *)TWindowDD::draw_default_entry((s32)this);
    draw_window_frame(context);
    draw_visible_window_entries(this, &entry_list, context);
    if (!(m_60 & 2)) {
        if (context->open_tick > 0) {
            stack.sp8 = 18.0f + context->inner_x;
            stack.spC = context->inner_y;
            TObjBoss2Tunnel__sub_8007CAE8(&stack.sp8, 18.0f);
        }
    } else {
        draw_window_text(&context->inner_x, (const char *)get_localized_text_entry(0x24, 7), -1, 0, 1000000.0f);
    }
}

void TWindowSnapShot::run_task() {
    u8 *arg0 = (u8 *)this;
    if (!(this->window_flags & 2)) {
        this->open_tick = 0x01000000;
    }
    if ((TWindowShortListCtrl__check_controller_button((void *) ((u8 *)&controller_input_state + 0x20), 2) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state + 0x160), 2) != 0)) {
        play_open_sound();
    }
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((u8 *)&this->entry_list);
}

TWindowSnapShot::~TWindowSnapShot() {}
TWindowSnapShot::TWindowSnapShot(void *position)
    : TWindowBase((u8 *)&window_snapshot_layout, 4, (u8 *)position) {
    m_name = TWindowSnapShot__name;
    m_60 = 0;
    if (verify_snapshot_checksum__15TObjBoss2TunnelFv() == 0) {
        m_60 |= 2;
    }
    s32 entry = get_array_entry(1);
    TWindowDuelResult::set_default_status((void *)entry, get_localized_text_entry(0xF, 0x13));
}

void *shared_snapshot_capture;
u32 snapshot_image_buffer;
s32 snapshot_buffer_size;
s32 lbl_805D669C;
int snapshot_aligned_buffer_size;
