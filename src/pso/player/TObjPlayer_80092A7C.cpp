#include "types.h"
#include "pso/system/vector.h"
#include "pso/enemy/TUnk_80493450.h"
#include "pso/enemy/TObjEneBeast.h"
#include "pso/player/TObjPlayer.h"

void TUnk_80493450::vfunc_100() {  }
int TUnk_80493450::test_flag_256() { return 0; }
void TUnk_80493450::request_stand_action() { this->requested_action = 0; }
void TObjChara::initialize_position_copies() {
    VecCopy(&prev_position, VecCopy((Vec *)&m_290, VecCopy((Vec *)&m_29c, &position)));
}
