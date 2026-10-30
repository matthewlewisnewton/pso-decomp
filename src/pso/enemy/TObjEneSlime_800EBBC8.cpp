#include "pso/player/demo_mode.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/TObjEneSlime_800EBBC8.h"
#include "pso/object/TObjDFHorming.h"
#include "pso/enemy/TObjEneSlime.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/player/TObjPlayer.h"

struct RecoveredGlobal_800EBC28___vt__12TObjEneSlime {
    s32 value;
    u8 remaining[0x14C];
};

extern "C" {
s32 __ct__9TObjEnemyFP7TObject(void *);
extern s32 __vt__12TObjEneSlime[];
extern s32 lbl_805D2AD8;
void __dl__7TObjectFPv(void *);
void *__dt__9TObjEnemyFv(TObjEnemy *arg0, s16 arg1);

void *__dt__12TObjEneSlimeFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__12TObjEneSlime;
        ((TObjEneSlime *)arg0)->release_split_slimes();
        __dt__9TObjEnemyFv((TObjEnemy *)arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern u32 slime_bml_resource;

typedef char RecoveredGlobal_800EBC28___vt__12TObjEneSlime_size[sizeof(RecoveredGlobal_800EBC28___vt__12TObjEneSlime) == 0x150 ? 1 : -1];
u8 *TObjEneSlime__ct(TObjEneSlime *ene_slime, s32 arg1, u8 *arg2) {
    s32 temp_r0;
    __ct__9TObjEnemyFP7TObject(ene_slime);
    *(s32 **)((s8 *)ene_slime + 0x18) = &(*(RecoveredGlobal_800EBC28___vt__12TObjEneSlime *)&__vt__12TObjEneSlime).value;
    *(s32 *)((s8 *)ene_slime + 0) = (s32) lbl_805D2AD8;
    ((TObjEneSlime *)(ene_slime))->apply_set_data(arg2);
    ((TObjEneSlime *)(ene_slime))->clear_lobby_object_state();
    ((TBoss3Volopt *)ene_slime)->reset_photon_effect();
    TBoss4DarkFalz__sub_8004B4F0(((u8 *)ene_slime + 0x374), (arg2));
    ene_slime->m_3b4 = (s32) *(s16 *)((s8 *)arg2 + 2);
    temp_r0 = ene_slime->m_3b4;
    if (temp_r0 < 1) {
        if (check_demo_mode() != 0) {
            ene_slime->m_3b4 = 3;
        }
    } else if (temp_r0 > 4) {
        ene_slime->m_3b4 = 4;
    }
    ene_slime->actorFlags = (s32) (ene_slime->actorFlags | 0x02000000);
    ene_slime->init_slots();
    return (u8 *)ene_slime;
}

void TObjEneSlime::free_instance() {
    if ((u32) slime_bml_resource != 0U) {
        delete (BmlResource *)((void*)slime_bml_resource);
        slime_bml_resource = 0U;
    }
}

}
