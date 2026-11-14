#ifndef PSO_MISC_TWINDOWSOUNDBALANCE_H
#define PSO_MISC_TWINDOWSOUNDBALANCE_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct SoundBalanceSettings {
    u8 unknown_00[4];
    s16 music_gain;
    s8 sound_effect_gain;
};

struct TWindowSoundBalance : public TWindowBase {
    TWindowSoundBalance(void *position);
    virtual ~TWindowSoundBalance();
    int is_active();
    virtual void render();
    u8 m_60;
    s8 selection;
    s16 music_gain;
    s16 sound_effect_gain;
    void set_sound_effect_gain(s16 gain);
    void set_music_gain(s16 gain);
    void play_open_sound();
    void handle_lr_input();
    void sub_8027095C();
    virtual void run_task();
    void apply_balance(void *arg1);
    void handle_cancel();
    u8 unk_66[0x2];
};

typedef char TWindowSoundBalance_size[sizeof(TWindowSoundBalance) == 0x68 ? 1 : -1];

typedef char SoundBalanceSettings_music[offsetof(SoundBalanceSettings, music_gain) == 4 ? 1 : -1];
typedef char SoundBalanceSettings_sfx[offsetof(SoundBalanceSettings, sound_effect_gain) == 6 ? 1 : -1];
typedef char TWindowSoundBalance_selection[offsetof(TWindowSoundBalance, selection) == 0x61 ? 1 : -1];
typedef char TWindowSoundBalance_music[offsetof(TWindowSoundBalance, music_gain) == 0x62 ? 1 : -1];
typedef char TWindowSoundBalance_sfx[offsetof(TWindowSoundBalance, sound_effect_gain) == 0x64 ? 1 : -1];

#endif
