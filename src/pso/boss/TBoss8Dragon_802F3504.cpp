#include "types.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TUnk_804E4BF0.h"
#include "pso/object/TObjControl.h"

extern "C" {

s32 set_state_22__12TBoss8DragonFv();

s32 TBoss8Dragon::find_target_enemy() {
    s32 var_r31;

    if (boss8_dragon_leader_part == NULL) {
        return 0;
    }
    var_r31 = 1;
loop_3:
    if (get_enemy_entity(boss8_dragon_leader_part->get_part_entity_id(var_r31)) != NULL) {
        return 1;
    }
    var_r31 += 1;
    if (var_r31 >= 6) {
        return 0;
    }
    goto loop_3;
}

s32 TBoss8Dragon::is_any_part_alive() {
    s32 var_r31;

    if (boss8_dragon_leader_part == NULL) {
        return 1;
    }
    var_r31 = 1;
loop_3:
    if (get_enemy_entity(boss8_dragon_leader_part->get_part_entity_id(var_r31)) != NULL) {
        return 0;
    }
    var_r31 += 1;
    if (var_r31 >= 6) {
        return 1;
    }
    goto loop_3;
}

void TBoss8Dragon::update_all_parts() {
    s32 var_r31;

    if (boss8_dragon_leader_part != NULL) {
        var_r31 = 1;
        do {
            if (get_enemy_entity(boss8_dragon_leader_part->get_part_entity_id(var_r31)) != NULL) {
                set_state_22__12TBoss8DragonFv();
            }
            var_r31 += 1;
        } while (var_r31 < 6);
    }
}

}
