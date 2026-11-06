#include "types.h"
#include "pso/enemy/TObjEneRecon.h"
extern f32 TObjEneRecon__data_805DF3D4;

#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
void TObjEneRecon::clamp_min_height() {
    u8 *arg0 = (u8 *)this;
  f32 new_var;
  f32 temp_f2;
  new_var = *((f32 *) (((s8 *) arg0) + 0x448));
  temp_f2 = *((f32 *) (((s8 *) arg0) + 0x3C));
  if ((new_var - temp_f2) < TObjEneRecon__data_805DF3D4)
  {
    *((f32 *) (((s8 *) arg0) + 0x448)) = (f32) (TObjEneRecon__data_805DF3D4 + temp_f2);
  }
  *((f32 *) (((s8 *) arg0) + 0x300)) = (f32) (*((f32 *) (((s8 *) arg0) + 0x448)));
}
