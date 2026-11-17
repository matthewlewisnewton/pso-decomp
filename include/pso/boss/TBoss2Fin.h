#ifndef PSO_BOSS_TBOSS2FIN_H
#define PSO_BOSS_TBOSS2FIN_H
#include "pso/TObjEZRopeBase.h"
#include "types.h"

class TBoss2Fin : public TObjEZRopeBase {
public:
    TBoss2Fin(TObject *parent, const Vec *left_position, const Vec *right_position);
    virtual ~TBoss2Fin();
    virtual void run_task();
    virtual void render();
public:
    void init_link_points();
    static void init_effect_table();

    RopeAnchor anchor_storage[2];
    RopeCollisionSphere sphere_storage[3];
    const Vec *left_position;
    const Vec *right_position;
};

typedef char TBoss2Fin_size[sizeof(TBoss2Fin) == 0x88 ? 1 : -1];

#endif
