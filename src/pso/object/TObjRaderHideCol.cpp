#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/object/TObjRaderHideCol.h"
#include "pso/system/NinjaUtil.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801AF2F0.h"

extern "C" {
extern s32 local_client_id;
// The original class-name storage includes three trailing zero bytes.
extern const char TObjRaderHideCol__class_name[0x14] = "TObjRaderHideCol";
const char *TObjRaderHideCol__name = TObjRaderHideCol__class_name;
}

void TObjRaderHideCol::render() {}

void TObjRaderHideCol::run_task() {
    TObjPlayer *player = get_player_by_client_id(local_client_id);
    if (player != NULL) {
        if (xyz_distance_squared(&position, &player->position) < hide_radius * hide_radius) {
            if (!(radar_hidden & 1)) {
                TRaderMapCore::hide_radar();
                radar_hidden = 1;
            }
        } else if (radar_hidden & 1) {
            TRaderMapCore::show_radar();
            radar_hidden = 0;
        }
    }
}

TObjRaderHideCol::~TObjRaderHideCol() {}

TObjRaderHideCol::TObjRaderHideCol(TObject *parent, void *set_data) : TObjBase(parent) {
    m_name = TObjRaderHideCol__name;
    apply_object_set_data(set_data);
    hide_radius = scale.x;
    radar_hidden = 0;
    disallow_rendering();
}
