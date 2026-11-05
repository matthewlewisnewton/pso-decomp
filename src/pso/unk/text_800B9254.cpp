#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"

extern "C" {

s32 enemy_clear_target__12TObjEneDD_STFUs(void *);
s32 is_player_entity_id(u16);
s32 vfunc_83__9TObjEneDDFv(void *);
u32 get_player_by_client_id(u16);

s32 TObjEneDD_ST::vfunc_83() {
    if ((is_player_entity_id(*(u16 *)((s8 *)this + 0x38C)) != 0) && (get_player_by_client_id(*(u16 *)((s8 *)this + 0x38C)) == 0U)) {
        enemy_clear_target__12TObjEneDD_STFUs(this);
    }
    vfunc_83__9TObjEneDDFv(this);
}

}
