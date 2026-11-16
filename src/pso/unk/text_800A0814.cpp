#include "types.h"
#include "pso/object/TObjControl.h"
#include "pso/enemy/TObjEneDarkGunCenter.h"
#include "pso/player/TObjPlayer.h"

void TObjEneDarkGunCenter::hide_linked_enemies() {
    s32 i;
    for (i = 0; i < linked_enemy_count; i++) {
        void *e = get_enemy_entity(linked_enemy_ids[i]);
        if (e != 0) {
            ((TObjPlayer *)e)->set_hidden_flag();
        }
    }
    state_timer = 0x78;
    state = 4;
}
