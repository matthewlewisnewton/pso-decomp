#include "types.h"
#include "pso/enemy/berura/TObjEneRe7Berura_803E4CE0.h"
#include "pso/quest/TQuestListVM_8007EAF8.h"
#include "pso/object/ambient/TObjFish_800E2FFC.h"
#include "pso/object/ambient/TObjFish.h"
#include "pso/enemy/berura/TObjEneRe7Berura.h"
#include "pso/system/ModelNodePositionCapture.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"

struct Entry_800E2FFC { s32 id; u8 data[0xC]; };

struct Param_800E2FFC { s32 a; s32 b; s32 c; };

struct State_800E2FFC { s32 counter; Entry_800E2FFC *list; Param_800E2FFC *params; s32 pad; };

struct Entry_800E3074 { s32 id; u8 data[0xC]; };

struct Param_800E3074 { s32 a; s32 b; s32 c; };

struct State_800E3074 { s32 counter; Entry_800E3074 *list; Param_800E3074 *params; s32 pad; };

struct Arg_800E3074 { Entry_800E3074 *list; Param_800E3074 *params; };

extern "C" {
u8 * __ct__24ModelNodePositionCaptureFP22ModelNodePositionEntryP3Vec(void *, void *, s32);
State_800E2FFC model_node_position_capture_state;
void transform_to_view__11TCameraCtrlFii(s32 arg0, s32 arg1);

void ModelNodePositionCapture::capture_node(NJS_OBJECT *) {
    Entry_800E2FFC *p = model_node_position_capture_state.list;
    Param_800E2FFC *q = model_node_position_capture_state.params;
    s32 id;
    while ((id = p->id) != -1) {
        if (id == model_node_position_capture_state.counter) {
            transform_to_view__11TCameraCtrlFii((s32)p->data, (s32)q);
        }
        p++;
        q++;
    }
    model_node_position_capture_state.counter++;
}

void ModelNodePositionCapture::install() {
    Arg_800E3074 *arg = (Arg_800E3074 *)this;
    (*(State_800E3074 *)&model_node_position_capture_state).counter = 0;
    (*(State_800E3074 *)&model_node_position_capture_state).list = arg->list;
    (*(State_800E3074 *)&model_node_position_capture_state).params = arg->params;
    set_chunk_model_node_callback((ChunkModelNodeCallback)((void *)ModelNodePositionCapture::capture_node));
}

s32 ModelNodePositionCapture::is_valid(ModelNodePositionEntry *p) {
    s32 i;
    if (p == 0) {
        return 0;
    }
    for (i = 0; p->node_index != -1; i++, p++) {
        if (i >= 0x40) {
            return 0;
        }
    }
    return 1;
}

void ModelNodePositionCapture::destroy(ModelNodePositionCapture *capture) {
    __dt__24ModelNodePositionCaptureFv((s32)capture, (s16)(1));
}

s32 create__24ModelNodePositionCaptureFP22ModelNodePositionEntryP3Vec(u8 *list, s32 vecs) {
    s32 temp_r3;
    s32 var_r0;
    if (ModelNodePositionCapture::is_valid((ModelNodePositionEntry *)list) != 0) {
        temp_r3 = (int)::operator new(8);
        var_r0 = temp_r3;
        if (var_r0 != 0) {
            var_r0 = (long) (__ct__24ModelNodePositionCaptureFP22ModelNodePositionEntryP3Vec((void *) temp_r3, list, vecs));
        }
        return var_r0;
    }
    return 0;
}

s32 __dt__24ModelNodePositionCaptureFv(s32 arg0, s16 arg1) {
    if ((arg0 != 0) && (arg1 > 0)) {
        __dl__FPv();
    }
    return arg0;
}

}
