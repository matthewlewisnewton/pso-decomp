#include "types.h"
#include "pso/npc/TObjNpcFemaleDwarf.h"
#include "pso/object/TObjControl.h"
#include "pso/player/TObjPlayer.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/task/TMainTask.h"

const char *bm_n_efsw_i_body_motion_names[1] = { NULL };
__declspec(section ".data") const char *bm_n_efsw_i_body_model_names[2] = { "n_efsw_i_body.nj", NULL };
BmlResourceDescriptor bm_n_efsw_i_body_resource_descriptor = { "bm_n_efsw_i_body.bml", bm_n_efsw_i_body_model_names, bm_n_efsw_i_body_motion_names, 1, 0 };
const char *TObjNpcFemaleDwarf__name = "TObjNpcFemaleDwarf";
BmlResource *TObjNpcFemaleDwarf__static_data;

s32 __vt__18TObjNpcFemaleDwarf[];

void *TObjNpcFemaleDwarf__create(void *set_data) {
    TObjControl *control = new TObjControl(tl_04);
    void *npc = TObject::operator new(sizeof(TObjNpcFemaleDwarf));
    if (npc != NULL) {
        npc = TObjNpcFemaleDwarf__ct((TObjNpcFemaleDwarf *)npc, control, set_data);
    }
    return npc;
}

void TObjNpcFemaleDwarf::unload_static_data() {
    if (TObjNpcFemaleDwarf__static_data != NULL) {
        delete TObjNpcFemaleDwarf__static_data;
        TObjNpcFemaleDwarf__static_data = NULL;
    }
}

void TObjNpcFemaleDwarf::load_static_resource() {
    BmlResource *resource = new BmlResource(1, &bm_n_efsw_i_body_resource_descriptor, 0, 0, NULL);
    TObjNpcFemaleDwarf__static_data = resource;
}

TObjNpcFemaleDwarf::~TObjNpcFemaleDwarf() {}

TObjNpcFemaleDwarf *TObjNpcFemaleDwarf__ct(TObjNpcFemaleDwarf *npc, TObjControl *control, void *set_data) {
    npc->construct_female_base();
    *(s32 **)((u8 *)npc + 0x18) = __vt__18TObjNpcFemaleDwarf;
    npc->m_name = TObjNpcFemaleDwarf__name;
    npc->apply_set_data(set_data);
    ((TObjChara *)npc)->initialize_position_copies();
    npc->model = (void *)TObjNpcFemaleDwarf__static_data->models->model;
    npc->texlist = (s32)TObjNpcFemaleDwarf__static_data->models->m_c;
    npc->setup_common();
    return npc;
}
