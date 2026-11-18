#ifndef PSO_UI_WARNING_WINDOW_UPDATE_H
#define PSO_UI_WARNING_WINDOW_UPDATE_H
#include "pso/ui/WarningWindowState.h"
#include "pso/misc/TWindowBase.h"
extern "C" s32 TWindowCtrlMain__sub_8024CE58();

template <class Window, class Policy>
inline void update_warning_window(Window *self) {
    s32 countdown;
    if (self->warning.window == NULL) {
        if (TWindowCtrlMain__sub_8024CE58() != 0) {
            if (Policy::should_show(self) != 0) {
                countdown = self->warning.countdown - 1;
                self->warning.countdown = countdown;
                if (countdown < 0) {
                    self->warning.countdown = 0;
                }
            } else {
                self->warning.countdown = 0x1E;
            }
            if (self->warning.countdown == 0) {
                Policy::open(self);
            }
        }
    } else if (Policy::should_show(self) == 0) {
        self->warning.window->close();
        self->warning.window = NULL;
        self->warning.countdown = 0x1E;
    }
}
#endif
