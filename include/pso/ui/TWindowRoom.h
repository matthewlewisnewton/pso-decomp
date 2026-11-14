#ifndef PSO_UI_TWINDOWROOM_H
#define PSO_UI_TWINDOWROOM_H

#include "pso/misc/TWindowBase.h"

struct TWindowRoom : public TWindowBase {
    TWindowRoom(char *title);
    virtual ~TWindowRoom();
    void *get_title_entry();
    void draw_tab(void *context);
    virtual void run_task();
    virtual void render();
    f32 tabParameter;
};

typedef char TWindowRoomSize[sizeof(TWindowRoom) == 0x64 ? 1 : -1];
typedef char RoomTabParameterOffset[offsetof(TWindowRoom, tabParameter) == 0x60 ? 1 : -1];

#endif
