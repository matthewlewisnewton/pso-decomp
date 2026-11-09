#include "types.h"
#include "pso/misc/TLobby.h"

extern "C" {

int load_sct_file__8TGStreamFlPUc(void);
int load_file__8TGStreamFl(void);

    extern const void *disc_read_filename;
s32 TLobby::set_stream_and_load_file(const void *name) {
    disc_read_filename = name;
    return load_file__8TGStreamFl();
}

void TLobby::set_stream_state(const void *name) { disc_read_filename = name; load_sct_file__8TGStreamFlPUc(); }

}
