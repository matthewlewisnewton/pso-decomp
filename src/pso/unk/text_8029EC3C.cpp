#include "pso/map/CsnQuery.h"
#include "types.h"
#include "pso/system/vector.h"
#include "pso/object/base/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/map/FloorArea.h"
#include "pso/player/TObjPlayer_80011014.h"

struct Ray_8029EC3C { Vec o; Vec d; };


extern "C" {
void *get_player_by_client_id(s32);
f32 vec_squared_length(u8 *arg0);
void reflect_matrix_in_plane(s32, void *);
extern s32 local_client_id;
extern Vec sora_reflection_ray_direction;
extern const f32 lbl_805DDD88;
extern const f32 lbl_805DDD8C;
s32 fn_8029EC3C(Vec *pos, s32 arg1);
#pragma push
#pragma fp_contract on
s32 fn_8029EC3C(Vec *pos, s32 arg1) {
    Ray_8029EC3C ray;
    Vec a;
    Vec b;
    Vec d;
    void *p;
    CsnHit *r;
    CsnContact *e;
    f32 scale;
    p = get_player_by_client_id(local_client_id);
    if (p == 0) return 0;
    scale = 80.0f;
    if (get_current_floor_area() == AREA_SEABED_UPPER) {
        if ((s16)((TObjBase *)p)->get_room() == 0x5A) {
            scale = 300.0f;
        } else {
            scale = 80.0f;
        }
    }
    VecCopy((Vec *)&a, (const Vec *)pos);
    b.x = scale * sora_reflection_ray_direction.x + a.x;
    b.y = a.y - lbl_805DDD88 * sora_reflection_ray_direction.y;
    b.z = scale * sora_reflection_ray_direction.z + a.z;
    d.x = b.x - pos->x;
    d.z = b.z - pos->z;
    d.y = b.y - pos->y;
    if (lbl_805DDD8C == vec_squared_length((u8 *)&d)) {
        ray.o.x = pos->x;
        ray.o.y = pos->y;
        ray.o.z = pos->z;
        ray.d.x = sora_reflection_ray_direction.x;
        ray.d.y = sora_reflection_ray_direction.y;
        ray.d.z = sora_reflection_ray_direction.z;
        reflect_matrix_in_plane(0, &ray);
        return 1;
    }
    if (lbl_805DDD8C == sora_reflection_ray_direction.x && lbl_805DDD8C == sora_reflection_ray_direction.z) {
        r = csnVecterUnder(&a, arg1);
    } else {
        r = csnVector(&a, &b, arg1);
    }
    if (r != 0) {
        e = r->contact;
        if (!(e->flags & 0x4000)) return 0;
        ray.o.x = e->point.x;
        ray.o.y = e->point.y;
        ray.o.z = e->point.z;
        ray.d.x = e->normal.x;
        ray.d.y = e->normal.y;
        ray.d.z = e->normal.z;
        reflect_matrix_in_plane(0, &ray);
        return 1;
    }
    return 0;
}
#pragma pop

}
