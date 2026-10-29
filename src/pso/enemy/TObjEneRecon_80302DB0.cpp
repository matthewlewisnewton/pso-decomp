#include "types.h"
#include "pso/unk/TObjEneDellBiter_Eff_TpAbsorb1.h"
#include "pso/enemy/TObjEneRecon_80302DB0.h"
#include "pso/enemy/TObjEneRecon.h"

    extern unsigned char scene_sora_recon_active_flag;
void TObjEneRecon::set_active() { scene_sora_recon_active_flag = 1; }
