#include "pso/camera/RadarMapViewState.h"

#pragma push
#pragma scheduling off
void initialize_radar_map_view(RadarMapViewState *view) {
    view->position.x = 0.0f;
    view->position.y = 0.0f;
    view->position.z = 0.0f;
    view->direction.x = 0.0f;
    view->direction.y = 0.0f;
    view->direction.z = -1.0f;
    view->rotation_y = 0;
    view->field1c = 0x2aaa;
    view->field20 = -1.0f;
    view->field24 = -60000.0f;
}
#pragma pop
