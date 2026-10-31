#include "pso/misc/ParticleFactory.h"
#include "types.h"
#include "pso/misc/PositionSoundEffects.h"
#include "pso/unk/text_80087278.h"
#include "pso/enemy/TObjEneRe4Sorcerer_800EDB98.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/map/FloorArea.h"

typedef struct Vec_800D8C48 {
    f32 x, y, z;
} Vec_800D8C48;

extern "C" {
void *create_timed_particle_emitter(void *owner, s32 id, s32 b, s32 c);

extern const f32 lbl_805DA3C0;
s32 play_sound_effect(int, void *, int, int);
s32 TBreakUpMdl__ct(void*, s32, s32, s32, s32, s32, s32);
void* __nw__7TObjectFUl(s32);

extern s32 tl_05;

void TBoss3Volopt::create_breakup_mdl(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void* obj = __nw__7TObjectFUl(0x54);
    if (obj != 0) {
        TBreakUpMdl__ct(obj, tl_05, arg0, arg1, arg2, arg3, arg4);
    }
}

void TBoss3Volopt::play_area_variant_sound() {
    s32 arg0 = (s32)this;
    s32 area;
    area = get_current_floor_area();
    switch (area) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_sound_effect(0x3AB3C, (void *)arg0, 0, 0);
        return;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_sound_effect(0x4003AD32, (void *)arg0, 0, 0);
        return;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4003B22A, (void *)arg0, 0, 0);
        return;
    case AREA_TOWER:
        play_sound_effect(0x4003A35A, (void *)arg0, 0, 0);
        return;
    case AREA_VR_TEMPLE_ALPHA:
    case AREA_VR_TEMPLE_BETA:
        play_sound_effect(0x3AD43, (void *)arg0, 0, 0);
        return;
    case AREA_VR_SPACESHIP_ALPHA:
    case AREA_VR_SPACESHIP_BETA:
        play_sound_effect(0x4003AD3F, (void *)arg0, 0, 0);
        return;
    default:
        play_sound_effect((int) (::remap_area_sound_id(0x4003AD06, 0x1E)), (void *)arg0, 0, 0);
        return;
    }
}

void TBoss3Volopt::play_area_se_with_particle() {
    s32 arg0 = (s32)this;
    Vec_800D8C48 v;
    f32 y;
    switch (get_current_floor_area()) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_sound_effect(0x3AB3C, (void *)arg0, 0, 0);
        break;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_sound_effect(0x4003AD32, (void *)arg0, 0, 0);
        break;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4003B22A, (void *)arg0, 0, 0);
        break;
    case AREA_TOWER:
        play_sound_effect(0x4003A35A, (void *)arg0, 0, 0);
        break;
    case AREA_VR_TEMPLE_ALPHA:
    case AREA_VR_TEMPLE_BETA:
        play_sound_effect(0x3AD43, (void *)arg0, 0, 0);
        break;
    case AREA_VR_SPACESHIP_ALPHA:
    case AREA_VR_SPACESHIP_BETA:
        play_sound_effect(0x4003AD3F, (void *)arg0, 0, 0);
        break;
    default:
        play_sound_effect(::remap_area_sound_id(0x4003AD06, 0x1E), (void *)arg0, 0, 0);
        break;
    }
    VecCopy((Vec *)&v, (const Vec *)arg0);
    y = v.y;
    v.y = y + lbl_805DA3C0;
    spawn_particle_effect(&v, 0xE6);
}

void play_area_sound_and_particles_a(const Vec *position) {
    s32 arg0 = (s32)position;
    switch (get_current_floor_area()) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_sound_effect(0x3AB3C, (void *)arg0, 0, 0);
        break;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_sound_effect(0x4003AB31, (void *)arg0, 0, 0);
        break;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4003B22A, (void *)arg0, 0, 0);
        break;
    case AREA_TOWER:
        play_sound_effect(0x4003A359, (void *)arg0, 0, 0);
        break;
    default:
        play_sound_effect(TBoss3Volopt::remap_area_sound_id(0x4003AB20), (void *)arg0, 0, 0);
        break;
    }
    spawn_position_particles((const Vec *)arg0);
}

void play_area_sound_and_particles_b(const Vec *position) {
    s32 arg0 = (s32)position;
    switch (get_current_floor_area()) {
    case AREA_CENTRAL_CONTROL_AREA:
    case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST:
    case AREA_MOUNTAIN:
    case AREA_SEASIDE:
        play_sound_effect(0x3AB3C, (void *)arg0, 0, 0);
        break;
    case AREA_SEABED_UPPER:
    case AREA_SEABED_LOWER:
        play_sound_effect(0x4003AB31, (void *)arg0, 0, 0);
        break;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4003B22A, (void *)arg0, 0, 0);
        break;
    case AREA_TOWER:
        play_sound_effect(0x4003A359, (void *)arg0, 0, 0);
        break;
    default:
        play_sound_effect(TBoss3Volopt::remap_area_sound_id(0x4003AB37), (void *)arg0, 0, 0);
        break;
    }
    spawn_position_particles((const Vec *)arg0);
}

void spawn_position_particles(const Vec *position) {
    Vec shifted_position;
    f32 y;
    VecCopy(&shifted_position, position);
    create_timed_particle_emitter((void *)position, 0xEA, 0xA, 0x1E);
    y = shifted_position.y;
    shifted_position.y = y + lbl_805DA3C0;
    spawn_particle_effect(&shifted_position, 0xE9);
}

}
