#ifndef PSO_TOBJEZBONEROTPLAYER_H
#define PSO_TOBJEZBONEROTPLAYER_H

#include "pso/TObjEZBoneRotBase.h"

struct TObjPlayer;

class TObjEZBoneRotPlayer : public TObjEZBoneRotBase {
public:
    TObjEZBoneRotPlayer(TObjPlayer *player, NJS_OBJECT *root, EZBoneRotDesc *desc);
    virtual ~TObjEZBoneRotPlayer();
    virtual void run_task();
    static TObjEZBoneRotPlayer *create(TObjPlayer *player, NJS_OBJECT *root, EZBoneRotDesc *desc);
    void start_bone_rotation_sequence(s32 phase);
    void calc_bone_offsets_recursive(NJS_OBJECT *node, s32 phase, s32 amplitude);
    void advance_bone_rotation();

    TObjPlayer *m_player;
    s32 m_previous_yaw;
};

typedef char EZBoneRotPlayerSize[sizeof(TObjEZBoneRotPlayer) == 0xA0 ? 1 : -1];
typedef char EZBoneRotPlayerOwnerOffset[offsetof(TObjEZBoneRotPlayer, m_player) == 0x98 ? 1 : -1];

#endif
