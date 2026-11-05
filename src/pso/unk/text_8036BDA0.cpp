#include "types.h"
#include "pso/protocol/subcommand_validation.h"
#include "pso/unk/text_8036BDA0.h"

s32 validate_6x47_cast_technique(G_CastTechnique_6x47 *packet) {
    s32 i;
    if (validate_subcommand_client(&packet->header) == 0) {
        return 0;
    }
    if (validate_technique_parameters(&packet->technique_number) == 0) {
        return 0;
    }
    for (i = 0; i < packet->target_count; i++) {
        if (validate_cast_target_entry(&packet->targets[i]) == 0) {
            return 0;
        }
    }
    return 1;
}
