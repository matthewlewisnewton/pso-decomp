#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/system/StripBufferPair.h"
#include "pso/enemy/TObjEnemy.h"

#include <stddef.h>
#include "pso/misc/TLobby.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/enemy/TObjEneLappy.h"
#include "pso/misc/TWindowLockOn.h"
struct Stack_800F5D80 {
    s32 sp8;
    u8 pad_C[0x2];
    s16 spE;
};

extern "C" {
void collect_model_strips_by_texture(void *ctx, s32 model, s32 filter);
void count_model_strips_by_texture(void *ctx, s32 model, s32 filter);

extern void *plist_strip_write_ptr;
extern void *plist_strip_uv_write_ptr;
extern s32 plist_texture_matches_filter;

StripBufferPair::StripBufferPair(s32 model, s32 filter) {
    strip_count = 0;
    uv_count = 0;
    plist_texture_matches_filter = 0;
    count_model_strips_by_texture(this, model, filter);
    strips = ::operator new[](strip_count * 8);
    uvs = ::operator new[](uv_count * 4);
    plist_strip_write_ptr = strips;
    plist_strip_uv_write_ptr = uvs;
    plist_texture_matches_filter = 0;
    collect_model_strips_by_texture(this, model, filter);
}
void TObjEnemy::clear_lobby_object_state() {
    s32 arg0 = (s32)this;
    typedef char sp8_offset[(offsetof(Stack_800F5D80, sp8) == 0x0) ? 1 : -1];
    typedef char spE_offset[(offsetof(Stack_800F5D80, spE) == 0x6) ? 1 : -1];
    Stack_800F5D80 stack;
    if (((TObjEnemy *)((void *)arg0))->exchange_object_state(&stack.sp8, 1) != 0) {
        stack.sp8 = 0;
        stack.spE = 0;
        ((TObjEnemy *)((void *)arg0))->exchange_object_state(&stack.sp8, 0);
    }
}

}
