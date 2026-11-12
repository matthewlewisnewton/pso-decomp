#include "types.h"
#include "pso/system/Adxf.h"
#include "pso/unk/TLobby.h"

    extern int lobby_download_state_ptr;
void TLobby::destroy_instance() { ADXF_Close((AdxfHandle *)lobby_download_state_ptr); lobby_download_state_ptr = 0; }
