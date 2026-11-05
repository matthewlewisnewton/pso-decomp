#ifndef PSO_MISC_TLOBBY_802268F4_H
#define PSO_MISC_TLOBBY_802268F4_H

#include "types.h"

extern "C" {
int TLobby__sub_80226B64(void);
void TLobby__sub_802272B4(void);
void TLobby__sub_8022733C(void);
void play_cue_stream_file(s32 name);
void set_cue_stream_gain(s32 arg0);
}
void init_music_sequencer(s32 program);
void set_dark_falz_music_request(s32 arg0);
void set_music_streams_volume(s32 arg0);
void stop_cue_stream(void);
void update_music_sequencer(void);
void update_sound_request_slots(void);

#endif
