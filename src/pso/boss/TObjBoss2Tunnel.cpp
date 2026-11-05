#include "types.h"
#include "pso/boss/TObjBoss2Tunnel.h"

extern "C" {

s32 TObjBoss2Tunnel__sub_8007DDB0(f32);
struct Obj_8007DE80 { f32 f0, f4, f8, fC, f10, f14, f18; };
extern const f32 TObjBoss2Tunnel__data_805D9234;

extern f32 lbl_805D923C;

void TObjBoss2Tunnel::advance_phase() {
    TObjBoss2Tunnel__sub_8007DDB0(*(f32 *)&this->_pad1C);
    *(f32 *)&this->_pad1C = (f32) (*(f32 *)&this->_pad1C + lbl_805D923C);
}

void TObjBoss2Tunnel::update_position() {
    eval_piecewise_curve(*(f32 *)&this->_pad1C);
}

#pragma push
#pragma fp_contract on
f32 TObjBoss2Tunnel::eval_piecewise_curve(f32 farg0) {
    Obj_8007DE80 *arg0 = (Obj_8007DE80 *)this;
    f32 t;
    f32 r = TObjBoss2Tunnel__data_805D9234;
    if (farg0 < r) {
        r = r;
    } else {
        if (farg0 < arg0->f10) {
            r = arg0->f0 * farg0 + arg0->f8;
        } else {
            t = arg0->f14;
            if (farg0 < t) {
                r = arg0->fC;
            } else if (farg0 < arg0->f18) {
                t = farg0 - t;
                r = arg0->f4 * t + arg0->fC;
            }
        }
    }
    return r;
}

#pragma pop

}
