#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TObjRain.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TLobby_801E2F94.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/NinjaUtil.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/math/AngleLookup.h"
#include "pso/render/render_util.h"

extern "C" {
extern TCameraCtrl *camera_ctrl_instance;
int rand(void);
f32 normalize_vector(Vec *);
void draw_line_list(void *, int, int);
}

// draw_line_list consumes the first two pointers; the remaining words are
// retained from this descriptor and are not read by the rain renderer.
struct RainLineList {
    Vec *positions;
    u32 *colors;
    s32 unused[2];
};
extern const char TObjRain__class_name_string[] = "TObjRain";
const char *TObjRain__class_name = TObjRain__class_name_string;
struct RainStreakGeometry {
    Vec positions[2];
    u32 colors[2];
};
RainStreakGeometry TObjRain__streak_geometry = {
    {{0.0f, 0.0f, 0.0f}, {0.0f, 9.0f, 0.0f}},
    {0x80808030, 0x70707020}
};
RainLineList TObjRain__streak_line_list = {TObjRain__streak_geometry.positions, TObjRain__streak_geometry.colors, {0, 2}};

void TObjRain::draw_streaks() {
    Drop *drop;
    u32 i;
    set_additive_blend();
    drop = drops;
    for (i = 0; i < count; drop++, i++) {
        if (drop->active != 0) {
            set_line_width(5);
            VecCopy(TObjRain__streak_line_list.positions, &drop->position);
            Vec pos = drop->position;
            if (xz_distance_squared(&camera_ctrl_instance->position, &pos) < 90000.0f) {
                Vec dir = drop->velocity;
                normalize_vector(&dir);
                dir.x *= 12.0f;
                dir.y *= 12.0f;
                dir.z *= 12.0f;
                subtract_vector(&pos, &drop->velocity);
                VecCopy(TObjRain__streak_line_list.positions + 1, &pos);
                draw_line_list(&TObjRain__streak_line_list, 1, 5);
            }
        }
    }
    reset_line_width();
    set_default_alpha_blend();
}

void TObjRain::update_drops() {
    s32 active = 0;
    Drop *drop = drops;
    u32 i;
    for (i = 0; i < count; drop++, i++) {
        if (drop->active != 0) {
            vec3_add_to(&drop->position, &drop->velocity);
            if (drop->position.y < drop->floor_y) {
                drop->active = 0;
            } else {
                active++;
            }
        }
    }
    if (active == 0) {
        queue_destruction();
    }
}

#pragma push
#pragma fp_contract on
void TObjRain::init_drops() {
    s32 angle;
    Drop *d;
    s32 i;
    f32 radius;
    f32 x;
    f32 z;
    d = drops;
    for (i = 0; i < count; i++, d++) {
        radius = 150.0f * (0.000030517578f * (f32)rand());
        angle = (s32)(182.04445f * (-15.0f - 150.0f * (0.000030517578f * (f32)rand())));
        angle -= (s32)camera_ctrl_instance->m_194;
        x = radius * cos_table_lookup(angle);
        z = radius * sin_table_lookup(angle);
        d->position.x = camera_ctrl_instance->position.x + x;
        d->position.y = 120.0f + camera_ctrl_instance->position.y;
        d->position.z = camera_ctrl_instance->position.z + z;
        d->velocity.x = 1.2f * (0.000030517578f * (f32)rand());
        d->velocity.y = -(5.5f * (0.000030517578f * (f32)rand()) + 9.0f);
        d->velocity.z = 1.2f * (0.000030517578f * (f32)rand());
        d->floor_y = -20.0f;
        d->active = 1;
    }
}
#pragma pop

void TObjRain::render() { draw_streaks(); }
void TObjRain::run_task() { update_drops(); }
TObjRain::~TObjRain() {}
TObjRain::TObjRain(TObject *parent, u32 drop_count) : TObject(parent) {
    m_name = TObjRain__class_name;
    count = drop_count > 16 ? 16 : drop_count;
    init_drops();
}
