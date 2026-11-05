#include "types.h"
#include "pso/object/TObjBgmColCtrl_8017E8E4.h"
#include "pso/object/TObjBgmColCtrl.h"

extern s32 lbl_805D62E4;

u8 TObjBgmColCtrl::is_active() {
    return (u8) (lbl_805D62E4 != 0);
}

    extern int TQuestBgmCtrl__bgm_issued_flag;
int get_quest_bgm_issued_flag(void) {  return TQuestBgmCtrl__bgm_issued_flag; }
