#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TBoss6CrushRock.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D8F74.h"

extern "C" f32 vector_length(const Vec *v);

void TBoss6CrushRock::render() {
    if (is_falz_alive() != 0) {
        push_matrix();
        post_translate_matrix(&position.x);
        rotate_matrix_y(NULL, angles.y);
        rotate_matrix_x(NULL, angles.x);
        rotate_matrix_z(NULL, angles.z);
        set_current_texture_list(texture_list);
        draw_ginja_object(model);
        pop_matrix();
    }
}

void TBoss6CrushRock::run_task() {
    if (is_falz_alive() == 0) {
        queue_destruction();
        return;
    }
    angles.x += angular_velocity.x;
    angles.y += angular_velocity.y;
    angles.z += angular_velocity.z;
    velocity.y += -0.25f;
    vec3_add_to(&position, &velocity);
    if (position.y < 0.0f) {
        position.y = 0.0f;
        velocity.x *= 0.25f;
        velocity.y *= -0.25f;
        velocity.z *= 0.25f;
        if (vector_length(&velocity) < 0.1f) {
            queue_destruction();
        }
    }
}
