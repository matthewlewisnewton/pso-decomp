#ifndef PSO_BOSS_TOBJBOSS7DUSTCTRL_H
#define PSO_BOSS_TOBJBOSS7DUSTCTRL_H

#include "pso/TObjBoss7DustCtrl.h"
#include <dolphin/mtx.h>

extern "C" {
s32 TObjBoss7DustCtrl__sub_802F125C(void);
void TObjBoss7DustCtrl__sub_802F1450(void);
void boss7_dust_draw_at(const Vec *position, s32 slot);
void fn_802F1454(void);
}

#endif
