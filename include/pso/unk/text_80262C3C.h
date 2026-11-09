#ifndef PSO_UNK_TEXT_80262C3C_H
#define PSO_UNK_TEXT_80262C3C_H

#include "types.h"

struct TWindowLockOn;
extern "C" {
void TWindowLockOn__update_for_enemy(s32 a0, s32 a1);
s32 TWindowLockOn__update_for_item(s32 a0, s32 a1);
s32 TWindowLockOn__update_for_other_player(s32 a0, s32 a1);
void *__dt__13TWindowLockOnFv(void *arg0, s16 arg1);
bool is_lockable_target__13TWindowLockOnFi(s32 arg0);
void render__13TWindowLockOnFv(TWindowLockOn *arg0);
void update_for_target__13TWindowLockOnFii(s32 arg0, s32 arg1);
}

#endif
