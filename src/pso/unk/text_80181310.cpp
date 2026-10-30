#include "pso/math/FloatRounding.h"
#include "types.h"
#include "pso/boss/TBoss8Dragon_8002CC48.h"
#include "pso/unk/text_801811FC.h"
#include "pso/TObject.h"

struct Rec_80181310 { s32 timer; s32 count; void *objs[2]; };

struct Ctrl_80181310 { u8 pad0[0x24]; s32 counter; Rec_80181310 recs[5]; };

extern "C" {
void *construct_city_air_car(void *, void *, s32, s32, f32);
void *__nw__7TObjectFUl(u32);
s32 rand(void);
extern f32 air_car_lane_spacing_table[];
extern f32 air_car_lane_speed_scale_table[];
extern const f32 lbl_805DBBC0;
extern const f32 lbl_805DBBC4;
extern const f32 lbl_805DBBCC;
extern const f32 lbl_805DBBD0;
extern const f32 lbl_805DBBD4;
extern const f32 lbl_805DBBD8;
extern const f32 lbl_805DBBDC;
void run_task__19TObjCityAirCar_CtrlFv(Ctrl_80181310 *self);
void run_task__19TObjCityAirCar_CtrlFv(Ctrl_80181310 *self) {
    s32 i;
    Rec_80181310 *r;
    s32 timer;
    s32 count;
    s32 j;
    s32 k;
    s32 type;
    f32 speed;
    void *last;
    void *o;
    for (i = 0; i < 5; i++) {
        r = &self->recs[i];
        count = r->count;
        timer = r->timer;
        for (j = 0; j < count; j++) {
            if (r->objs[j] == NULL || ((TObject *)(r->objs[j]))->all_parents_unqueued_for_destruction() == 0) {
                count--;
                for (k = j; k < count; k++) {
                    r->objs[k] = r->objs[k + 1];
                }
                r->objs[count] = NULL;
                j--;
            }
        }
        if (count < 2 && --timer <= 0) {
            timer = lerp__9TDeadSpotFff(lbl_805DBBCC, lbl_805DBBD0);
            if (i == 0 || i == 1) {
                type = floor_to_float(lbl_805DBBD4 * (lbl_805DBBD8 * rand()));
            } else {
                type = (s32)floor_to_float(lbl_805DBBDC * (lbl_805DBBD8 * rand())) + 1;
            }
            if (i == 1 || i == 2) {
                self->counter++;
                if (type == 4) {
                    if (self->counter >= 40) {
                        self->counter = 0;
                    } else {
                        type = 2;
                    }
                }
            }
            speed = air_car_lane_speed_scale_table[i] * lerp__9TDeadSpotFff(lbl_805DBBC0, lbl_805DBBD4);
            if (count > 0) {
                last = r->objs[count - 1];
                if (fn_80181204(last) < lbl_805DBBC4 * air_car_lane_spacing_table[i]) {
                    speed = fn_801811FC(last);
                }
            }
            o = __nw__7TObjectFUl(0xAC);
            if (o != NULL) {
                o = construct_city_air_car(o, self, i, type, speed);
            }
            r->objs[count++] = o;
        }
        r->count = count;
        r->timer = timer;
    }
}

}
