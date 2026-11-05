#include "pso/enemy/TObjEneDD_ST.h"

extern "C" void enemy_clear_target__12TObjEneDD_STFUs(void *);
extern "C" void *lbl_805D2A34;

TObjEneDD_ST::~TObjEneDD_ST() {}

TObjEneDD_ST::TObjEneDD_ST(TObject *parent) : TObjEneDD(parent) {
    m_name = (const char *)lbl_805D2A34;
    enemy_clear_target__12TObjEneDD_STFUs(this);
    init_float_params();
    enemy_init_acquire_period(30);
    enemy_init_validate_period(30);
}
