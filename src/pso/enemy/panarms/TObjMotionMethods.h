#ifndef PSO_ENEMY_PANARMS_TOBJMOTIONMETHODS_H
#define PSO_ENEMY_PANARMS_TOBJMOTIONMETHODS_H

// Source-private definitions, included only by TObjEnePanarms.cpp.
#pragma push
void TObjMotion::sub_800E2DE4(s32 flags) {
    animationFlags &= ~flags;
}
#pragma pop

#endif
