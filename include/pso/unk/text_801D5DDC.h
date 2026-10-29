#ifndef PSO_UNK_TEXT_801D5DDC_H
#define PSO_UNK_TEXT_801D5DDC_H

#include "types.h"

extern "C" {
// Sends 6x3A for the gauge's client id: its photon blast is no longer ready.
void send_6x3A_clear_photon_blast_ready_flag(u16 *client_id);
}

#endif
