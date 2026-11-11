#ifndef PSO_BOSS_DRAGON_TOBJBOSS1MOKOHILL_SOLOM_H
#define PSO_BOSS_DRAGON_TOBJBOSS1MOKOHILL_SOLOM_H
#include "types.h"
#include "pso/system/task/TObject.h"

class TObjBoss1MokoHill_SoloM : public TObject {
public:
    virtual ~TObjBoss1MokoHill_SoloM();
    virtual void render();
    virtual void run_task();
    void set_field_3c();
    void set_field_1c();
    void spawn_child_object();
    s32 m_1c;
    u8 unk_20[0xC];
    f32 m_2c;
    f32 m_30;
    f32 m_34;
    u8 unk_38[0x4];
    s32 m_3c;
};
typedef char TObjBoss1MokoHill_SoloM_size[sizeof(TObjBoss1MokoHill_SoloM) == 0x40 ? 1 : -1];

#endif
