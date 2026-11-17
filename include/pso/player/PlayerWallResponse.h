#ifndef PSO_PLAYER_PLAYERWALLRESPONSE_H
#define PSO_PLAYER_PLAYERWALLRESPONSE_H
#include "types.h"
#include "pso/map/WallQuery.h"

struct TObjCollidable;
extern "C" {
f32 TObjPlayer__sub_8017A1A4(TObjCollidable *actor, s32 body);
f32 vec3_dot(const Vec *a, const Vec *b);
f32 vector_length(const Vec *vector);
f32 TObjPlayer__sub_801BF814(void *state);
// Historical export labels; all three receivers below are vectors.
void calc_move__10TObjPlayerFPvPv(Vec *velocity, Vec *direction, Vec *out);
void calc_wall_slide_point__10TObjPlayerFPvPv(Vec *value, Vec *normal, Vec *out);
void calc_move_velocity__10TObjPlayerFPvPvf(Vec *direction, Vec *out, f32 length);
}
#endif
