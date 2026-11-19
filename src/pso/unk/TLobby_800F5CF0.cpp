#include "pso/render/ChunkTextureStripCollector.h"
#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/enemy/TObjEnemy.h"

#include <stddef.h>
#include "pso/unk/TLobby.h"
#include "pso/boss/volopt/TBoss3Volopt.h"
#include "pso/enemy/lappy/TObjEneLappy.h"
#include "pso/ui/window/TWindowLockOn.h"
#include "pso/boss/darkfalz/TOBoss4Rock.h"
struct Stack_800F5D80 {
    s32 sp8;
    u8 pad_C[0x2];
    s16 spE;
};

extern "C" {
s32 exchange_object_state__9TObjEnemyFls(void *, void *, int);
StripBufferPair::StripBufferPair(s32 model, s32 filter) {
    strip_count = 0;
    uv_count = 0;
    plist_texture_matches_filter = 0;
    count_model_strips_by_texture(this, (NJS_OBJECT *)model, filter);
    strips = (StripReference *)::operator new[](strip_count * sizeof(*strips));
    uvs = (s16 *)::operator new[](uv_count * 2 * sizeof(*uvs));
    plist_strip_write_ptr = strips;
    plist_strip_uv_write_ptr = uvs;
    plist_texture_matches_filter = 0;
    collect_model_strips_by_texture(this, (NJS_OBJECT *)model, filter);
}
void TObjEnemy::clear_lobby_object_state() {
    s32 arg0 = (s32)this;
    typedef char sp8_offset[(offsetof(Stack_800F5D80, sp8) == 0x0) ? 1 : -1];
    typedef char spE_offset[(offsetof(Stack_800F5D80, spE) == 0x6) ? 1 : -1];
    Stack_800F5D80 stack;
    if (exchange_object_state__9TObjEnemyFls((void *)arg0, &stack.sp8, 1) != 0) {
        stack.sp8 = 0;
        stack.spE = 0;
        exchange_object_state__9TObjEnemyFls((void *)arg0, &stack.sp8, 0);
    }
}

}
