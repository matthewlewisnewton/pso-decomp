#include "pso/system/BmlTextureList.h"
#include "types.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/system/BmlResource.h"
#include "pso/system/NinjaTypes.h"
#include "pso/object/TObjFish_8001ED90.h"

struct GinjaTextureList;

extern "C" {

extern GinjaTextureList *falz_zako_texture_list;
extern void *falz_zako_chunk_model;
extern s32 TBoss4ZakoDraw__rotation_phase;

void TBoss4DarkFalz::init_uro_link() {
    NJS_OBJECT *model;
    NJS_OBJECT *child;

    falz_zako_texture_list = TObjFish__sub_8001EDB0((BmlResource *)(TBoss4Uro::get_instance_count()), 8);
    model = get_bml_model(TBoss4Uro::get_instance_count(), 8);
    child = model->child;
    child->evalflags &= ~2u;
    if (child->model != 0) {
        falz_zako_chunk_model = child->model;
        TBoss4ZakoDraw__rotation_phase = 0;
        TBoss4DarkFalz::clear_uro_link_state();
    }
}

}
