#include "types.h"
extern "C" {
s32 validate_subcommand_client(void *packet);
}
s32 validate_technique_parameters(void *parameters);
s32 validate_cast_target_entry(void *entry);
struct G_CastTechnique_6x47;
s32 validate_6x47_cast_technique(G_CastTechnique_6x47 *cast);
s32 validate_6x47_cast_technique(G_CastTechnique_6x47 *cast) {
    u8 *packet = (u8 *)cast;
    s32 i;
    if (validate_subcommand_client(packet) == 0) {
        return 0;
    }
    if (validate_technique_parameters(packet + 4) == 0) {
        return 0;
    }
    for (i = 0; i < (s8)packet[7]; i++) {
        if (validate_cast_target_entry(packet + 8 + i * 4) == 0) {
            return 0;
        }
    }
    return 1;
}
