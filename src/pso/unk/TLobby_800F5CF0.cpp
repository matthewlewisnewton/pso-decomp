#include "types.h"
#include "pso/enemy/TObjEnemy.h"

#include <stddef.h>
#include "pso/system/ArrayAllocation.h"
#include "pso/unk/TLobby.h"
#include "pso/system/StripBufferPair.h"
#include "pso/boss/volopt/TBoss3Volopt.h"
#include "pso/enemy/lappy/TObjEneLappy.h"
#include "pso/ui/window/TWindowLockOn.h"
struct Stack_800F5D80 {
    s32 sp8;
    u8 pad_C[0x2];
    s16 spE;
};

extern "C" {
s32 exchange_object_state__9TObjEnemyFPvs(void *, void *, int);
s32 collect_model_strips_by_texture(void *, s32, s32, s32);
s32 count_model_strips_by_texture();

extern s32 plist_strip_write_ptr;
extern s32 plist_strip_uv_write_ptr;
extern s32 plist_texture_matches_filter;

StripBufferPair::StripBufferPair(s32 model, s32 filter) {
    s32 temp_r6;

    strip_count = 0;
    uv_count = 0;
    plist_texture_matches_filter = 0;
    count_model_strips_by_texture();
    strips = ::operator new[](strip_count * 8);
    uvs = ::operator new[](uv_count * 4);
    plist_strip_write_ptr = (s32)strips;
    temp_r6 = (s32)uvs;
    plist_strip_uv_write_ptr = temp_r6;
    plist_texture_matches_filter = 0;
    collect_model_strips_by_texture(this, model, filter, temp_r6);
}
void TObjEnemy::clear_lobby_object_state() {
    s32 arg0 = (s32)this;
    typedef char sp8_offset[(offsetof(Stack_800F5D80, sp8) == 0x0) ? 1 : -1];
    typedef char spE_offset[(offsetof(Stack_800F5D80, spE) == 0x6) ? 1 : -1];
    Stack_800F5D80 stack;
    if (exchange_object_state__9TObjEnemyFPvs((void *)arg0, &stack.sp8, 1) != 0) {
        stack.sp8 = 0;
        stack.spE = 0;
        exchange_object_state__9TObjEnemyFPvs((void *)arg0, &stack.sp8, 0);
    }
}

}
