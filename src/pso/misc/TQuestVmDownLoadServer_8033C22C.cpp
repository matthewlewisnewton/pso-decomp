#include "types.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/ui/TObjBagWarnWin_8006EF24.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/TAdPlayerLoadGC.h"
#include "pso/misc/TCheckMemoryCard.h"
#include "pso/misc/TWindowSubComCard.h"

void TCheckMemoryCard::init_from_keyboard_state() {
    s32 var_r31;
    s32 var_r6;

    if (TKeyBoardControl__sub_8000F8EC() == 0xF) {
        var_r31 = TQuestVmDownLoadServer__sub_8006EF6C(0xA);
        var_r6 = TQuestVmDownLoadServer__sub_8006EF6C(0xE);
        init(var_r31, -2, var_r6, 0);
        return;
    }
    var_r31 = TQuestVmDownLoadServer__sub_8006EF6C(0x62);
    var_r6 = TQuestVmDownLoadServer__sub_8006EF6C(0xE);
    if (m_28 & 0x20) {
        var_r31 = TQuestVmDownLoadServer__sub_8006EF6C(0x6D);
        var_r6 = TQuestVmDownLoadServer__sub_8006EF6C(0xE);
    }
    init(var_r31, -2, var_r6, 0);
}
