#include "types.h"
#include "pso/boss/TBoss4Uro.h"

s32 TBoss4Uro::get_phase() { return *(s32 *)&this->_pad37c; }

    extern BmlResource *darkfalz_dat_resource;
BmlResource *TBoss4Uro::get_instance_count() { return darkfalz_dat_resource; }
