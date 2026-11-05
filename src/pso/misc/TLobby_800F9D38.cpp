#include "types.h"
#include "pso/misc/TLobby.h"

extern "C" {

int load_sct_file__8TGStreamFlPUc(void);
int load_file__8TGStreamFl(void);

    extern int disc_read_filename;
s32 TLobby::set_stream_and_load_file(int a0) {
    disc_read_filename = a0;
    return load_file__8TGStreamFl();
}

void TLobby::set_stream_state(int a0) { disc_read_filename = a0; load_sct_file__8TGStreamFlPUc(); }

}
