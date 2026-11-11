// Synthetic compiler control; never compiled or linked by the game build.
// CREATOR_SHORT selects the external declaration. CAST_SHORT selects only
// the caller's explicit conversion. No callee definition is visible.
#include "types.h"

#if CREATOR_SHORT
typedef s16 CreatorResult;
#else
typedef s32 CreatorResult;
#endif
#if CAST_SHORT
#define STATUS(call) ((s16)(call))
#else
#define STATUS(call) (call)
#endif

class TLobby {
public:
    static void clear_slot_for_handle(u32);
    static void deactivate_entry_by_key(u32);
};
struct DispatchState {
    s32 lock_handle;
    s32 queue_handle;
    u32 protocol_thread_handle;
    u32 timer_thread_handle;
    unsigned char remaining[0xe8];
};
typedef char dispatch_size[sizeof(DispatchState) == 0xf8 ? 1 : -1];

extern "C" {
CreatorResult creator(void (*)(void), u32 *);
void protocol_loop(void);
void timer_loop(void);
DispatchState state;
s16 open_queue(s32 *);
s16 open_mutex(s32 *);
void release_mutex(u32);
void resume_thread(u32);

s32 status_minimal(void) {
    if (STATUS(creator(protocol_loop, &state.protocol_thread_handle)) < 0) {
        return -1;
    }
    return 0;
}

// Preserve the actual initializer's two creator calls, preceding two short
// status checks, cleanup branches and output-handle lifetimes. Names and the
// unobserved remainder of the global state are synthetic. The global keeps
// its native 0xf8-byte size and same-TU BSS ownership for relocation controls.
s16 status_dispatcher(void) {
    s32 *queue;
    u32 *proto_thread;
    u32 *timer_thread;
    queue = &state.queue_handle;
    if (open_queue(queue) < 0) return -0x100;
    if (open_mutex(&state.lock_handle) < 0) {
        TLobby::clear_slot_for_handle(*queue);
        return -0x100;
    }
    proto_thread = &state.protocol_thread_handle;
    if (STATUS(creator(protocol_loop, proto_thread)) < 0) {
        TLobby::clear_slot_for_handle(*queue);
        release_mutex(state.lock_handle);
        return -0x100;
    }
    timer_thread = &state.timer_thread_handle;
    if (STATUS(creator(timer_loop, timer_thread)) < 0) {
        TLobby::deactivate_entry_by_key(*proto_thread);
        TLobby::clear_slot_for_handle(*queue);
        release_mutex(state.lock_handle);
        return -0x100;
    }
    resume_thread(*proto_thread);
    resume_thread(*timer_thread);
    return 0;
}
}
