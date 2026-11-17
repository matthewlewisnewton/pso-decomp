#include "pso/misc/CameraViewVectors.h"
#include "pso/misc/TUnk_80488B08.h"
#include "pso/misc/TUnk_80488B38.h"
#include "pso/system/ControllerInputState.h"

extern "C" {
f32 sin_table_lookup(s32 angle);
f32 cos_table_lookup(s32 angle);
extern s32 TCameraCtrl__fixed_npc_camera_active;
extern u8 TCameraCtrl__override_flags;
}

TUnk_80488B08::TUnk_80488B08() : TUnk_80488A28() {
    m_38 = 4;
    TCameraCtrl__fixed_npc_camera_active = 0;
}

extern "C" {
Vec *TCameraCtrl__sub_8006BAB4(CameraViewVectors *views, s32 index) {
    return &views->targets[index];
}

Vec *TCameraCtrl__sub_8006BAC8(CameraViewVectors *views, s32 index) {
    return &views->positions[index];
}

u8 TCameraCtrl__sub_8006BADC() {
    return TCameraCtrl__override_flags;
}

void *TCameraCtrl__vt4() {
    return new TUnk_80488B38();
}
}

#pragma push
#pragma fp_contract on
void TUnk_80488B38::run_task() {
    ControllerInputState *pad = &controller_input_state;
    u32 buttons = pad->controllers[1].buttons;
    s16 stick_x = pad->controllers[1].stick_x;
    s16 stick_y = pad->controllers[1].stick_y;
    f32 radius;

    if (buttons & 0x20000) {
        distance += 2.2f;
    } else if (buttons & 0x10000) {
        distance -= 2.2f;
    }
    if (distance < 10.0f) {
        distance = 10.0f;
    }
    if (distance > 300.0f) {
        distance = 300.0f;
    }
    m_30 += stick_x * 3;
    m_2c += stick_y * 3;
    radius = distance * cos_table_lookup(m_2c);
    position.x = radius * sin_table_lookup(m_30) + target.x;
    position.y = target.y - distance * sin_table_lookup(m_2c);
    position.z = radius * cos_table_lookup(m_30) + target.z;
}
#pragma pop

TUnk_80488B38::~TUnk_80488B38() {}

TUnk_80488B38::TUnk_80488B38() : TUnk_80488A28() {
    distance = 10.0f;
    m_38 = 0;
}
