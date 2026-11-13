#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/player/demo_mode.h"
#include "pso/enemy/TObjEneDarkGunCenter.h"
#include "pso/TObjControl.h"
#include "pso/object/TObjControl.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/enemy/DarkGunner.h"

extern "C" {
void TObjPlayer__sub_800A0654(void *);
s32 TObjPlayer__sub_800A06B4(void *);
void fn_800A0798(void *);
void fn_800A0884(void *);
extern const f64 lbl_8043A488[];
extern const f32 lbl_805D9970;
extern const f32 lbl_805D9974;
extern TObject *tl_04;
}

#pragma defer_codegen on

TObjEneDarkGunCenter::~TObjEneDarkGunCenter() {}

extern "C" void TObjEneDarkGunCenter__sub_800A0E80() {}

extern "C" void TObjEneDarkGunCenter__sub_800A0E7C() {}

void *TObjEneDarkGunCenter::create(void *arg0) {
    TObjControl *control = new TObjControl(tl_04);
    void *center = TObject::operator new(sizeof(TObjEneDarkGunCenter));
    if (center != NULL) {
        center = TObjEneDarkGunCenter__ct((u8 *)center, control, arg0);
    }
    return center;
}

void TObjEneDarkGunCenter::run_task() {
    s32 ang;
    s32 i;
    s32 t;
    s32 id;
    TObjEnemy *e;
    if (check_demo_mode() == 1) {
        TObjEneDarkGunCenter__sub_800A0B18(this);
        return;
    }
    sub_800A0994();
    switch (state) {
    case 0:
        if (is_actor_cadence_frame(0x1e) != 0) {
            id = find_nearest_visible_player(this, 0, lbl_805D9970);
            if (id != 0xFFFF) {
                target = get_player_by_client_id(id);
                ang = (s32)(lbl_8043A488[0] * atan2_float(target->position.z - position.z, target->position.x - position.x)) + 0x4000;
                for (i = 0; i < linked_enemy_count; i++) {
                    e = (TObjEnemy *)get_enemy_entity(linked_enemy_ids[i]);
                    if (e != NULL) {
                        e->rotation.yaw = ang;
                    }
                    ang += 0x1555;
                }
                state_timer = 0x5a;
                state = 1;
            } else {
                TObjPlayer__sub_800A0654(this);
            }
        }
        break;
    case 1:
        state_timer--;
        if (state_timer <= 0) {
            hide_linked_enemies();
            state_timer = 0xd2;
            state = 2;
        }
        break;
    case 2:
        state_timer--;
        if (TObjPlayer__sub_800A06B4(this) != 0 || state_timer <= 0) {
            state = 3;
        }
        break;
    case 3:
        if (find_nearest_visible_player(this, 0, lbl_805D9970) != 0xFFFF) {
            hide_linked_enemies();
            fn_800A0884(this);
        } else {
            state = 0;
        }
        break;
    case 4:
        state_timer--;
        if (state_timer <= 0) {
            fn_800A0798(this);
        }
        break;
    case 5:
        state_timer--;
        if (state_timer <= 0) {
            state = 3;
        }
        break;
    case 6:
        state_timer--;
        if (state_timer <= 0) {
            state = 3;
        }
        break;
    }
    t = empty_group_timer;
    if (t < 0) {
        if (linked_enemy_count > 0) {
            empty_group_timer = 0x5a;
        } else {
            empty_group_timer = t - 1;
            if ((f32)(t - 1) <= lbl_805D9974) {
                empty_group_timer = 0x5a;
            }
        }
    } else {
        if (linked_enemy_count > 0) {
            empty_group_timer = 0x5a;
        } else if ((empty_group_timer = t - 1) <= 0) {
            send_entity_set_flags();
            queue_destruction();
        }
    }
}

void TObjEneDarkGunCenter::render() {}

extern "C" void TObjEneDarkGunCenter__sub_800A0B18(void *) {}

extern "C" {
const f32 lbl_805D9970 = 1000.0f;
const f32 lbl_805D9974 = -30.0f;
}
