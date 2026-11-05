#include "types.h"
#include "pso/boss/TObjBoss2Tunnel.h"

typedef struct Curve_8007E16C {
    f32 accel;
    f32 decel;
    f32 peak;
    f32 accelEnd;
    f32 decelStart;
    f32 end;
    f32 accelDist;
    f32 decelPos;
    f32 dist;
} Curve_8007E16C;

typedef struct Curve_8007E210 {
    f32 accel;
    f32 decel;
    f32 peak;
    f32 accelEnd;
    f32 decelStart;
    f32 end;
    f32 accelDist;
    f32 decelPos;
    f32 dist;
} Curve_8007E210;

extern "C" {
f32 sample_acceleration_curve(Curve_8007E16C *c, f32 t);
f32 newton_sqrtf(f32);
void init_acceleration_curve(Curve_8007E210 *c, f32 a, f32 d, f32 length, f32 speed);
extern const f32 TObjBoss2Tunnel__data_805D9234;
extern const f32 TObjBoss2Tunnel__data_805D926C;
extern const f32 lbl_805D9288;
extern const f32 lbl_805D928C;
extern const f32 lbl_805D9294;

void __dl__FPv(void);
s32 reset_floats__15TObjBoss2TunnelFv();

s32 TObjBoss2Tunnel::dt(s32 arg0, s16 arg1) {
    if ((arg0 != 0) && (arg1 > 0)) {
        __dl__FPv();
    }
    return arg0;
}

s32 TObjBoss2Tunnel::reset_floats(s32 arg0) {
    reset_floats__15TObjBoss2TunnelFv();
    return arg0;
}

#pragma push
#pragma fp_contract on
f32 sample_acceleration_curve(Curve_8007E16C *c, f32 t) {
    if (t < TObjBoss2Tunnel__data_805D9234) {
        return TObjBoss2Tunnel__data_805D9234;
    }
    if (t < c->accelEnd) {
        {
        f32 k = TObjBoss2Tunnel__data_805D926C * c->accel;
        k *= t;
        return t * k;
        }
    }
    if (t < c->decelStart) {
        t -= c->accelEnd;
        return t * c->peak + c->accelDist;
    }
    if (t < c->end) {
        t = c->end - t;
        {
        f32 k = TObjBoss2Tunnel__data_805D926C * c->decel;
        k *= t;
        return t * k + c->dist;
        }
    }
    return c->dist;
}
#pragma pop

int TObjBoss2Tunnel::check_param_threshold(f32 arg1) {
    return arg1 >= *(f32 *)&this->m_down;
}
void init_acceleration_curve(Curve_8007E210 *c, f32 a, f32 d, f32 length, f32 speed) {
    f32 sq;
    f32 up;
    f32 down;
    f32 p;
    c->accel = a;
    if (c->accel <= TObjBoss2Tunnel__data_805D9234) {
        c->accel = lbl_805D9288;
    }
    c->decel = d;
    if (c->decel >= TObjBoss2Tunnel__data_805D9234) {
        c->decel = lbl_805D928C;
    }
    sq = speed * speed;
    c->dist = length;
    c->peak = speed;
    up = (TObjBoss2Tunnel__data_805D926C * sq) / c->accel;
    down = (TObjBoss2Tunnel__data_805D926C * -sq) / c->decel;
    if (up + down >= c->dist) {
        f32 k2 = lbl_805D9294 * c->accel;
        c->peak = newton_sqrtf((c->dist * (k2 *= c->decel)) / (c->decel - c->accel));
        sq = c->peak * c->peak;
        c->accelEnd = c->decelStart = c->peak / c->accel;
        c->accelDist = c->decelPos = (TObjBoss2Tunnel__data_805D926C * sq) / c->accel;
        c->end = c->decelStart + (-c->peak / c->decel);
        return;
    }
    c->accelDist = up;
    c->accelEnd = c->peak / c->accel;
    c->decelPos = c->dist - down;
    c->decelStart = c->accelEnd + (c->decelPos - up) / c->peak;
    c->end = c->decelStart + (-c->peak / c->decel);
}

}
