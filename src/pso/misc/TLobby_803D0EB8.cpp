#include "pso/system/MiddlewareInterruptLock.h"
#include "types.h"
#include "pso/misc/TLobby.h"

extern u32 log_printf_callback;
extern s32 lobby_log_callback_arg;

void TLobby::set_callback(u32 arg0, s32 arg1) {
    if (arg0 == 0U) {
        log_printf_callback = 0U;
        lobby_log_callback_arg = 0;
        return;
    }
    log_printf_callback = arg0;
    lobby_log_callback_arg = arg1;
}

void TLobby::notify_dvd_read() {
    middleware_interrupt_lock_leave();
}

void TLobby::enter_lock() {
    middleware_interrupt_lock_enter();
}
