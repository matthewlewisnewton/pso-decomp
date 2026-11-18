#ifndef PSO_MISC_TWINDOWMESSAGEQUEST_H
#define PSO_MISC_TWINDOWMESSAGEQUEST_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowMessage.h"

struct TWindowMessageQuest : public TWindowMessage {
    TWindowMessageQuest(s32 layout);
    virtual ~TWindowMessageQuest();
    virtual void render();
    s32 m_90;
};

typedef char TWindowMessageQuest_size[sizeof(TWindowMessageQuest) == 0x94 ? 1 : -1];

extern "C" {
void *__dt__19TWindowMessageQuestFv(void *arg0, s16 arg1);
}

typedef char TWindowMessageQuest_owned_field_offset[offsetof(TWindowMessageQuest, m_90) == 0x90 ? 1 : -1];

#endif
