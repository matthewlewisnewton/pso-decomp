#ifndef PSO_MISC_TOTRAPSEABED01_H
#define PSO_MISC_TOTRAPSEABED01_H

#include "types.h"
#include "pso/misc/TOTrap.h"

struct TOTrapSeabed01 : public TOTrap {
    virtual ~TOTrapSeabed01();
    void draw_object_tree(NJS_OBJECT *object);
    void render_effect_layers();
    virtual int vfunc_67(f32 damage_scale);
    virtual void vfunc_84();
    virtual void vfunc_81();
    virtual void vfunc_82();
    void sub_802C9D38();
    void check_hold_player();
    void sub_802C9C18(s32);
    virtual void vfunc_6(s16 *, s32);
    virtual void render();
    virtual f32 receive_physical_attack(void *, f32);
    virtual void play_sounds();
    u32 m_344;
    s32 m_348;
    s32 m_34c;
    DirectAttackPayload attack;
    u32 m_358;
    void clamp_params_and_init();
    static void *create(void *arg0);
    static void free_static_resources();
    static void load_resources();
    void draw();
    static void trigger_by_id(u32 arg0);
};

typedef char TOTrapSeabed01_size[sizeof(TOTrapSeabed01) == 0x35C ? 1 : -1];
#endif
