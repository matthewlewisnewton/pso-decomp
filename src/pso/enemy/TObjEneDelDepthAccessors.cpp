#include "pso/enemy/TObjEneDelDepth.h"
#include "pso/enemy/DelDepthData.h"

BmlResource *TObjEneDelDepth::get_data() {
    return TObjEneDelDepth__shared_resource;
}

f32 TObjEneDelDepth::get_bomb_speed() {
    return bombSpeed;
}
