#include "types.h"
#include "pso/unk/text_80121E94.h"
extern "C" {
u32 create_shoot_model__10TObjPlayerFUiiif();
}
long belra_cannon_create_shot(u8 *arg0) {
  s32 temp_r4;
  u8 *temp_r6;
  if (create_shoot_model__10TObjPlayerFUiiif() != 0U)
  {
    temp_r6 = (unsigned char *) (*((void **) (((s8 *) arg0) + 0x188)));
    if (temp_r6 != 0)
    {
      temp_r4 = *((s32 *) (((s8 *) temp_r6) + 0));
      if (((u32) (temp_r4 & 7)) == 7)
      {
        *((s32 *) (((s8 *) temp_r6) + 0)) = (s32) (temp_r4 & 0xFFFFFFFD);
        *((s32 *) (((s8 *) temp_r6) + 0x14)) = -0x4000;
        *((s32 *) (((s8 *) temp_r6) + 0x1C)) = 0x8000;
      }
    }
  }
}
