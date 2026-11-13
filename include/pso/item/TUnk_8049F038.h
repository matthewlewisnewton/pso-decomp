#ifndef PSO_ITEM_TUNK_8049F038_H
#define PSO_ITEM_TUNK_8049F038_H
#include "pso/object/TObjMotion.h"

// The equipment effect's collision object follows one joint of a player.
// No independent class name survives in this range.
class TUnk_8049F038 : public TObjCollidable {
public:
    TUnk_8049F038(TObject *parent, u16 client, s32 joint);
    virtual ~TUnk_8049F038();
    virtual void *get_center();
    virtual void run_task();

    u16 client_id;
    s32 joint;
    CollisionBody body;
};
typedef char TUnk_8049F038_size[sizeof(TUnk_8049F038) == 0xE0 ? 1 : -1];
typedef char TUnk_8049F038_client_id_offset[offsetof(TUnk_8049F038, client_id) == 0xac ? 1 : -1];
typedef char TUnk_8049F038_joint_offset[offsetof(TUnk_8049F038, joint) == 0xb0 ? 1 : -1];
typedef char TUnk_8049F038_body_offset[offsetof(TUnk_8049F038, body) == 0xb4 ? 1 : -1];
#endif
