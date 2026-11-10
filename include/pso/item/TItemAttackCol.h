#ifndef PSO_ITEM_TITEMATTACKCOL_H
#define PSO_ITEM_TITEMATTACKCOL_H

#include "types.h"
#include <dolphin/mtx/GeoTypes.h>
#include "pso/system/FlagWord.h"

class TEffStarLight2D;
class TParticleCtrl;
struct ItemAttackColliderParams;
struct NJS_OBJECT;
typedef void (*AttackColliderContactCallback)(s32 item_id, Vec *position, Vec *velocity);
typedef void (*AttackColliderHitCallback)(s32 item_id, s32 *hit, Vec *velocity);

struct AttackColliderAngles {
    s32 x, y, z;
};
#include "pso/item/TUnk_804E355C.h"

struct TItemAttackCol : public TUnk_804E355C {
    TItemAttackCol(TObject *parent, ItemAttackColliderParams *params);
    virtual ~TItemAttackCol();
    virtual void vfunc_7();
    void check_object_hits();
    virtual void vfunc_6(s32 *);
    Vec start_position;
    Vec velocity;
    f32 m_dc;
    FlagWord collision_flags;
    u32 m_e4;
    NJS_OBJECT *model;
    u32 m_ec;
    AttackColliderAngles heading;
    AttackColliderAngles model_rotation;
    Vec model_scale;
    u32 m_114;
    u32 m_118;
    u32 m_11c;
    Vec m_120;
    TEffStarLight2D *star_light;
    TParticleCtrl *emitter;
    TParticleCtrl *secondary_emitter;
    AttackColliderContactCallback contact_callback;
    AttackColliderHitCallback hit_callback;
    TParticleCtrl *continuous_effect;
    static void add_to_active_list(void* a0);
    void shift_collision_bounds();
    void move_with_collision(void *arg1);
    virtual void render();
    virtual void run_task();
    static void create(void *arg0, void *arg1);
    void copy_pos(void* q);
};

typedef char TItemAttackCol_size[sizeof(TItemAttackCol) == 0x144 ? 1 : -1];
#endif
