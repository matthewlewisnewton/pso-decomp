#ifndef PSO_BOSS_TOBJBOSS1MOKOHILL_SOLOM_H
#define PSO_BOSS_TOBJBOSS1MOKOHILL_SOLOM_H
#include "types.h"
#include "pso/TObject.h"

// The burrowing trail TBoss1Dragon keeps at 0x6D8. While m_1c is set it
// follows the dragon; while m_3c is also set it drops a hill every 10 units.
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
