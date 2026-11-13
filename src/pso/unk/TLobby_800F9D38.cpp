#include "types.h"
#include "pso/unk/TLobby.h"

extern "C" {

int load_sct_file__8TGStreamFlPUc(void);
int load_file__8TGStreamFl(void);

    extern int disc_read_filename;
void TLobby::set_stream_and_load_file(const void *name) { disc_read_filename = (int)name; load_file__8TGStreamFl(); }

void TLobby::set_stream_state(const void *name) { disc_read_filename = (int)name; load_sct_file__8TGStreamFlPUc(); }

}
