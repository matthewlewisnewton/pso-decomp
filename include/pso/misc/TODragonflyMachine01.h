#ifndef PSO_MISC_TODRAGONFLYMACHINE01_H
#define PSO_MISC_TODRAGONFLYMACHINE01_H

#include "types.h"
#include "pso/misc/TODragonfly.h"

struct TODragonflyMachine01 : public TODragonfly {
    TODragonflyMachine01 *initialize(void *set_data);
    virtual ~TODragonflyMachine01();
    virtual void render();
    s16 yaw_animation_state;
    s16 yaw_animation_cycles;
    int animation_yaw;
    void update_yaw_animation();
    static void rotate_animated_node();
    virtual void run_task();
    static void *create(void *arg0);
    static void unload_static_data();
    static void create_attack_effect();
};

typedef char TODragonflyMachine01_size[sizeof(TODragonflyMachine01) == 0x108 ? 1 : -1];

#endif
