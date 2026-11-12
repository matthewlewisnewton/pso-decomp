#include "types.h"
#include "pso/system/Adxf.h"
#include "pso/unk/TLobby.h"
#include "pso/item/TItemLoad.h"

void TItemLoad::free_texture() { if (*(unsigned int *)&this->m_flags != 0) { ADXF_Close((AdxfHandle *)(*(void* *)&this->m_flags)); *(int *)&this->m_flags = 0; *(int *)&this->m_next = 0; } }
