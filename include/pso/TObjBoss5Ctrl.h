#ifndef PSO_TOBJBOSS5CTRL_H
#define PSO_TOBJBOSS5CTRL_H

#include "pso/TObject.h"

class TObjBoss5Ctrl : public TObject {
public:
    TObject *floor_grass;
    TObject *floor_stone;
    TObject *pillar_controller;
    TObject *pillar_demo;
    s16 sound_countdown;

    TObjBoss5Ctrl(TObject *parent);
    virtual ~TObjBoss5Ctrl();
    virtual void run_task();

    static void play_pillar_sound();
    static TObjBoss5Ctrl *create();
};

extern "C" {
extern TObjBoss5Ctrl *boss5_ctrl_instance;
}

typedef char TObjBoss5Ctrl_size[sizeof(TObjBoss5Ctrl) == 0x30 ? 1 : -1];

#endif
