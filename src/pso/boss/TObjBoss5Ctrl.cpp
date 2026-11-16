#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TObjBoss5Ctrl.h"
#include "pso/boss/TObjBoss5PillarDemo.h"
#include "pso/system/SoundEffect.h"

#pragma fp_contract on

TObjBoss5Ctrl *boss5_ctrl_instance;

extern "C" {
s32 rand();
s32 get_current_floor();
s32 is_room_enemy_set_cleared(s32, s32);
s32 is_split_screen();
TObject *create__19TObjBoss5FloorStoneFv();
TObject *create__19TObjBoss5FloorGrassFv();
TObject *create__19TObjBoss5PillarCtrlFv(TObject *parent);
// The original also calls this entry with a pillar-demo receiver. Its shared
// class ownership is unresolved; retain the observed TObject borrow here.
void play_sound_once__19TObjBoss5PillarCtrlFv(TObject *pillar);
extern TObject *tl_01;
extern const char lbl_80438128[] = "TObjBoss5Ctrl";
const char *lbl_805D2828 = lbl_80438128;
}

void TObjBoss5Ctrl::play_pillar_sound() {
    TObjBoss5Ctrl *controller = boss5_ctrl_instance;
    if (controller != NULL && controller->pillar_demo != NULL) {
        play_sound_once__19TObjBoss5PillarCtrlFv(controller->pillar_demo);
    }
}

void TObjBoss5Ctrl::run_task() {
    if (sound_countdown-- <= 0) {
        play_sound_effect(0x40033215, NULL, 0, 0);
        sound_countdown = (s16)(60.0f * ((1.0f / 32768.0f) * (f32)rand()) + 90.0f);
    }
}

TObjBoss5Ctrl::~TObjBoss5Ctrl() {
    if (pillar_demo != NULL) {
        pillar_demo->queue_destruction();
        pillar_demo = NULL;
    }
    if (pillar_controller != NULL) {
        pillar_controller->queue_destruction();
        pillar_controller = NULL;
    }
    if (floor_stone != NULL) {
        floor_stone->queue_destruction();
        floor_stone = NULL;
    }
    if (floor_grass != NULL) {
        floor_grass->queue_destruction();
        floor_grass = NULL;
    }
    boss5_ctrl_instance = NULL;
}

TObjBoss5Ctrl::TObjBoss5Ctrl(TObject *parent) : TObject(parent) {
    m_name = lbl_805D2828;
    floor_grass = NULL;
    floor_stone = NULL;
    pillar_controller = NULL;
    pillar_demo = NULL;
    sound_countdown = (s16)(60.0f * ((1.0f / 32768.0f) * (f32)rand()) + 90.0f);
    if (is_room_enemy_set_cleared(get_current_floor(), 1) == 0) {
        if (is_split_screen() == 0) {
            if (floor_grass == NULL) {
                floor_grass = create__19TObjBoss5FloorGrassFv();
            }
            if (floor_stone == NULL) {
                floor_stone = create__19TObjBoss5FloorStoneFv();
            }
            if (pillar_controller == NULL) {
                pillar_controller = create__19TObjBoss5PillarCtrlFv(this);
            }
        }
        if (pillar_demo == NULL) {
            pillar_demo = TObjBoss5PillarDemo::create();
        }
    }
}

TObjBoss5Ctrl *TObjBoss5Ctrl::create() {
    TObjBoss5Ctrl *controller = new TObjBoss5Ctrl(tl_01);
    boss5_ctrl_instance = controller;
    return controller;
}
