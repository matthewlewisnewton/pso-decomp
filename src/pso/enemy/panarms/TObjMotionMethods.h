#ifndef PSO_ENEMY_PANARMS_TOBJMOTIONMETHODS_H
#define PSO_ENEMY_PANARMS_TOBJMOTIONMETHODS_H

// Source-private definitions, included only by TObjEnePanarms.cpp.
#pragma push
void TObjMotion::clear_motion_flags(s32 flags) {
    motion_flags &= ~flags;
}
#pragma pop

#endif
