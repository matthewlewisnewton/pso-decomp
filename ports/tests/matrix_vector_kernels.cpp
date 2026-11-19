#include "pso/math/MatrixVector.h"

extern "C" {
u8 *current_matrix;
}

struct GuardedMatrix {
    f32 before;
    Mtx34 matrix;
    f32 after;
};

static bool check_matrix(const GuardedMatrix &buffer, bool identity) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            const f32 expected = identity ? (row == col ? 1.0f : 0.0f) : 21.0f;
            if (buffer.matrix[row][col] != expected) return false;
        }
    }
    return buffer.before == 11.0f && buffer.after == 17.0f;
}

int main() {
    const Vec inputs[] = {{0, 0, 0}, {-3, 4, 0}, {2, -3, 6}, {0, 0, -12}, {.25f, 0, 0}};
    const f32 lengths[] = {0, 5, 7, 12, .25f};
    for (unsigned i = 0; i < sizeof(inputs) / sizeof(inputs[0]); ++i) {
        if (vector_length(&inputs[i]) != lengths[i]) return 1;
    }

    GuardedMatrix active, other;
    active.before = other.before = 11.0f;
    active.after = other.after = 17.0f;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) active.matrix[row][col] = other.matrix[row][col] = 21.0f;
    }
    current_matrix = (u8 *)active.matrix;
    set_matrix_identity((u8 *)other.matrix);
    if (!check_matrix(other, true) || !check_matrix(active, false)) return 2;
    set_matrix_identity(NULL);
    return check_matrix(active, true) ? 0 : 3;
}
