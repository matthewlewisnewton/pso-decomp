struct NJS_OBJECT;
#include "types.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/quest/TQuestListVM_8007EAF8.h"
#include "pso/system/ModelNodePositionCapture.h"
#include "pso/object/TObjFish.h"
#include "pso/enemy/TObjEneRe7Berura.h"

struct ModelNodePositionCaptureState {
    s32 node_index;
    ModelNodePositionEntry *entries;
    Vec *positions;
    s32 unknown_0c;
};

extern "C" {
extern ModelNodePositionCaptureState model_node_position_capture_state;
void transform_to_view__11TCameraCtrlFii(s32, s32);
}

void ModelNodePositionCapture::capture_node(NJS_OBJECT *) {
    ModelNodePositionEntry *entry = model_node_position_capture_state.entries;
    Vec *position = model_node_position_capture_state.positions;
    s32 index;
    while ((index = entry->node_index) != -1) {
        if (index == model_node_position_capture_state.node_index) {
            transform_to_view__11TCameraCtrlFii((s32)&entry->offset, (s32)position);
        }
        entry++;
        position++;
    }
    model_node_position_capture_state.node_index++;
}

void ModelNodePositionCapture::install() {
    model_node_position_capture_state.node_index = 0;
    model_node_position_capture_state.entries = entries;
    model_node_position_capture_state.positions = positions;
    set_chunk_model_node_callback(capture_node);
}

s32 ModelNodePositionCapture::is_valid(ModelNodePositionEntry *entries) {
    ModelNodePositionEntry *entry = entries;
    s32 count;
    if (entry == 0) {
        return 0;
    }
    for (count = 0; entry->node_index != -1; count++, entry++) {
        if (count >= 0x40) {
            return 0;
        }
    }
    return 1;
}

void ModelNodePositionCapture::destroy(ModelNodePositionCapture *capture) {
    delete capture;
}

ModelNodePositionCapture *ModelNodePositionCapture::create(ModelNodePositionEntry *entries, Vec *positions) {
    if (is_valid(entries) != 0) {
        return new ModelNodePositionCapture(entries, positions);
    }
    return 0;
}

ModelNodePositionCapture::~ModelNodePositionCapture() {}
