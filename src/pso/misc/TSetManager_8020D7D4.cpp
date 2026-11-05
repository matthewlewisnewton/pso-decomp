#include "pso/TSetManager.h"
#include "pso/misc/TSetManager_8020D7D4.h"

extern "C" {
extern "C" void apply_floor_set_rows__11TSetManagerFv();
extern "C" void update_decoration_spawning__11TSetManagerFv();
void *set_manager_task_pmf_table[3] = {
    (void *)0x0, (void *)0xffffffff, (void *)&apply_floor_set_rows__11TSetManagerFv,
};
void *lbl_804C9454[3] = {
    (void *)0x0, (void *)0xffffffff, (void *)&update_decoration_spawning__11TSetManagerFv,
};
void *lbl_804C9460[6] = {
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0,
};
}
void TSetManager__sub_8020D7D4(void) {  }
typedef void (TSetManager::*Pmf_8020D7D8)();

void TSetManager::run_task() {
    static s8 init;
    if (!init) {
        ((Pmf_8020D7D8 *)lbl_804C9460)[0] = *(Pmf_8020D7D8 *)set_manager_task_pmf_table;
        ((Pmf_8020D7D8 *)lbl_804C9460)[1] = *(Pmf_8020D7D8 *)lbl_804C9454;
        init = 1;
    }
    (this->*((Pmf_8020D7D8 *)lbl_804C9460)[*(s32 *)((u8 *)this + 0x1C)])();
    ((void (*)(void *))TSetManager__sub_8020D7D4)(this);
}

TSetManager::~TSetManager() {}

#include "types.h"
