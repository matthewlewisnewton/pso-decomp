#include "pso/misc/TextEntryMeasurement.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/ControllerInputState.h"
#include "pso/misc/TWindowDrawContext.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/misc/TWindowSubComCard_80244774.h"
#include "pso/misc/TLobby_80226070.h"
#include "pso/misc/TUnk_804CF930.h"
#include "types.h"
#include "pso/misc/TWindowChoiceSetting.h"
#include "pso/ui/TAdMultiPlyChrSelectGC.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowSoundBalance.h"
#include "pso/item/TItemMag.h"
#include "pso/item/TItemProShield.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, int);
s32 TWindowShortListCtrl__check_controller_button(int, int);

// Existing word-valued entry-field ABI; complete widget ownership remains provisional.
s32 get_field_20__17TWindowSubComCardFv(void *entry);
extern u8 lbl_804D0CE0[];
WindowLayoutDescriptor window_sound_balance_settings = {
    {470.0f, 60.0f}, 50100.0f, lbl_804D0CE0, 3
};
extern const char *TWindowSoundBalance__name;
static const f32 lbl_805DD414 = 231.0f;
extern const f32 lbl_805DD418;
s32 draw_visible_window_entries(s32, s32, void *);

void TWindowSoundBalance::set_sound_effect_gain(s16 gain) {
    if (sound_effect_gain != gain) {
        sound_effect_gain = gain;
        TLobby__sub_8022614C(gain);
        TUnk_804CF930 *gauge = (TUnk_804CF930 *)get_array_entry(3);
        gauge->target = gain + 100;
        gauge->calc_bar_width();
    }
}

void TWindowSoundBalance::set_music_gain(s16 gain) {
    if (music_gain != gain) {
        music_gain = gain;
        update_music_stream_gain(gain);
        TUnk_804CF930 *gauge = (TUnk_804CF930 *)get_array_entry(2);
        gauge->target = gain + 250;
        gauge->calc_bar_width();
    }
}

void TWindowSoundBalance::apply_balance(void *context) {
    s32 temp;

    temp = (s32)get_array_entry((s32)selection);
    draw_selection_bar((TWindowDrawContext *)context, (u8 *)temp, is_active());
}

void TWindowSoundBalance::handle_cancel() {
    if (is_active() == 0) {
        play_sound_effect(0x52F16, 0, 0, 0);
        this->m_60 = (u8) (this->m_60 | 2);
    }
}


void TWindowSoundBalance::play_open_sound() {
    play_sound_effect(0x52D01, 0, 0, 0);
    this->m_60 = (u8) (this->m_60 | 1);
}

static const f32 lbl_805DD408 = 0.025f;

void TWindowSoundBalance::sub_8027095C() {
    ControllerInputContext *input = &controller_input_state.controllers[0];
    s16 gain;
    s16 range;
    s16 step;
    if (is_flag_set__11TLoadingCurFv(input, 0xC0) != 0 ||
        is_flag_set__11TLoadingCurFv(&controller_input_state.keyboard, 0xC0) != 0) {
        if (selection != 0) {
            gain = sound_effect_gain;
            range = 100;
        } else {
            gain = music_gain;
            range = 250;
        }
        step = lbl_805DD408 * range;
        if (is_flag_set__11TLoadingCurFv(input, 0x80) != 0 ||
            is_flag_set__11TLoadingCurFv(&controller_input_state.keyboard, 0x80) != 0) {
            gain += step;
        }
        if (is_flag_set__11TLoadingCurFv(input, 0x40) != 0 ||
            is_flag_set__11TLoadingCurFv(&controller_input_state.keyboard, 0x40) != 0) {
            gain -= step;
        }
        if (gain > 0) gain = 0;
        if (gain < -range) gain = -range;
        if (selection != 0) {
            set_sound_effect_gain(gain);
        } else {
            set_music_gain(gain);
        }
    }
}

static const f32 lbl_805DD40C = 174.0f;
static const f32 lbl_805DD410 = 348.0f;

void TWindowSoundBalance::handle_lr_input() {
    u8 *input;
    input = (u8 *)&controller_input_state.controllers[0];
    if ((TAdMultiPlyChrSelectGC::dispatch_draw_command((int)input, 0x30, 6, 1) != 0) || (TWindowChoiceSetting::apply_choice((s32)((void *) ((u8 *)&controller_input_state.keyboard)), 0x30, 6, 1) != 0)) {
        play_sound_effect(0x54100, (const Vec *)((0U)), 0, 0);
        if ((TAdMultiPlyChrSelectGC::dispatch_draw_command((int)input, 0x10, 6, 1) != 0) || (TWindowChoiceSetting::apply_choice((s32)((void *) ((u8 *)&controller_input_state.keyboard)), 0x10, 6, 1) != 0)) {
            this->selection = (this->selection - 1);
        }
        if ((TAdMultiPlyChrSelectGC::dispatch_draw_command((int)input, 0x20, 6, 1) != 0) || (TWindowChoiceSetting::apply_choice((s32)((void *) ((u8 *)&controller_input_state.keyboard)), 0x20, 6, 1) != 0)) {
            this->selection = (this->selection + 1);
        }
        if ((s8) this->selection < 0) {
            this->selection = 0U;
        }
        if ((s8) this->selection > 1) {
            this->selection = 1U;
        }
    }
}

#pragma push
#pragma opt_common_subs off
void TWindowSoundBalance::render() {
    TWindowSoundBalance *self = this;
    TWindowDrawContext *entry = (TWindowDrawContext *)TWindowDD::draw_default_entry((s32)self);
    self->draw_window_frame(entry);
    draw_visible_window_entries((s32)self, (s32)&self->m_24, entry);
    entry->inner_x += lbl_805DD40C;
    entry->inner_w -= lbl_805DD410;
    self->apply_balance(entry);
}
#pragma pop

void TWindowSoundBalance::run_task() {
    u8 *input;
    if (is_active() == 0) {
        handle_lr_input();
        sub_8027095C();
        input = (u8 *)&controller_input_state.controllers[0];
        if ((TWindowShortListCtrl__check_controller_button((int)input, 4) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.keyboard), 4) != 0)) {
            play_open_sound();
        }
        if ((TWindowShortListCtrl__check_controller_button((int)input, 2) != 0) || (test_flag_4c__23TAdSinglePlyChrSelectGCFv((void *) ((u8 *)&controller_input_state.keyboard), 2) != 0)) {
            handle_cancel();
        }
    }
    ((TWindowDD *)this)->initialize_subwindow();
    update_fade();
    update_window_entry_list(&m_24);
}

TWindowSoundBalance::~TWindowSoundBalance() {}
#pragma push
#pragma fp_contract on
TWindowSoundBalance::TWindowSoundBalance(void *position)
    : TWindowBase((u8 *)&window_sound_balance_settings, 4, (u8 *)position) {
    u8 *e;
    SoundBalanceSettings *st;
    m_name = TWindowSoundBalance__name;
    m_60 = 0;
    selection = 0;
    music_gain = 1;
    sound_effect_gain = 1;
    e = (u8 *)get_array_entry(0);
    *(f32 *)(e + 8) = lbl_805DD414 - lbl_805DD418 * calc_text_width((char *)get_field_20__17TWindowSubComCardFv(e));
    measure_text_entry(e);
    e = (u8 *)get_array_entry(1);
    *(f32 *)(e + 8) = lbl_805DD414 - lbl_805DD418 * calc_text_width((char *)get_field_20__17TWindowSubComCardFv(e));
    measure_text_entry(e);
    st = (SoundBalanceSettings *)TAdSinglePlyChrSelectGC::get_global_state();
    if (st == NULL) {
        set_music_gain(0);
        set_sound_effect_gain(0);
    } else {
        set_music_gain(st->music_gain);
        set_sound_effect_gain(st->sound_effect_gain);
    }
}

#pragma pop

}
