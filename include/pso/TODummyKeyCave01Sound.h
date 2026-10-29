#ifndef PSO_TODUMMYKEYCAVE01SOUND_H
#define PSO_TODUMMYKEYCAVE01SOUND_H

#include "pso/TObject.h"
#include "types.h"

class TODummyKeyCave01Sound : public TObject {
public:
    virtual ~TODummyKeyCave01Sound();
    void play_cave01_key_sound();
    virtual void run_task();
    s32 sound_kind;
    s32 delay_frames;
};

#endif
