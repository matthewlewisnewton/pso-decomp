#include "pso/unk/text_80049FD8.h"

#include "pso/TMainTask.h"
#include "pso/TObjChip.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/object/TObjVoloptPillar.h"
#include "pso/system/BmlResource.h"

void fn_80049FD8(TObjVoloptPillar *pillar) {
    const s32 debris_model_index = 14; // fe_obj_vo_tenjo_hahen01.nj
    const TObjChipParams params = {
        {0.5f, 0.03f, 0.25f},
        {pillar->position.x, pillar->position.y, pillar->position.z},
        {4.5f, -3.0f, 4.5f},
        {0x400, 0x100, 0x400},
        {4, 60},
        {0.0f, 1.0f},
        (s32)boss3_volopt_resources->models[debris_model_index].model,
        (s32)boss3_volopt_resources->models[debris_model_index].m_c,
        2,
    };

    // The legacy constructor takes a mutable pointer and only copies from it.
    new TObjChip(tl_05, const_cast<TObjChipParams *>(&params));
    new TObjChip(tl_05, const_cast<TObjChipParams *>(&params));
    new TObjChip(tl_05, const_cast<TObjChipParams *>(&params));
}
