#ifndef PSO_UI_WINDOW_TWINDOWDUELRESULT_H
#define PSO_UI_WINDOW_TWINDOWDUELRESULT_H

#include "types.h"
#include "pso/ui/window/TWindowBase.h"

struct PageIndicator;

struct TWindowDuelResult : public TWindowBase {
    TWindowDuelResult(s32 client);
    virtual ~TWindowDuelResult();
    virtual void run_task();
    virtual void render();
    void build_ranking_page();
    void build_statistics_page();
    void update_ranking_page();
    void update_statistics_page();
    void rebuild_page();
    void update_page();

    u8 unknown_30[0x2C];
    s32 open_tick;
    f32 scale_x;
    f32 scale_y;
    PageIndicator *page_indicator;
    static int set_default_status(void* p, int a1);
};

typedef char TWindowDuelResult_size[sizeof(TWindowDuelResult) == 0x6C ? 1 : -1];
#endif
