#include "types.h"
#include "pso/misc/TCameraCtrl.h"

extern "C" {

int target_player0__11TCameraCtrlFi(void);

    extern const float lbl_805D8F7C;
void TCameraCtrl::reset_state() { *(float *)&this->m_70 = lbl_805D8F7C; *(int *)&this->unk_2C = 0; *(int *)&this->m_34 = 0; target_player0__11TCameraCtrlFi(); reset_behind_player(); }

}
