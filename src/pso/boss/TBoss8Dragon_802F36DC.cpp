#include "types.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TUnk_804E4BF0.h"
#include "pso/object/TObjControl.h"

extern "C" {

s32 is_split_screen();

bool TBoss8Dragon::has_enough_enemies() {
    s32 i;
    s32 count;

    if (is_split_screen() != 0) {
        return 1;
    }
    if (boss8_dragon_leader_part == NULL) {
        return 0;
    }
    count = 0;
    i = 0;
    do {
        if (get_enemy_entity(boss8_dragon_leader_part->get_part_entity_id(i)) != NULL) {
            count += 1;
        }
        i += 1;
    } while (i < 6);
    return count >= 3;
}

}
