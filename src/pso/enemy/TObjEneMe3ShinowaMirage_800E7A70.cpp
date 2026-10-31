#include "pso/misc/SampledMotionPoints.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/TObjEneMe3ShinowaMirage_800E7A70.h"
#include "pso/enemy/TObjEneMe3ShinowaMirage.h"

struct RecoveredGlobal_8031B170_lbl_804E8880
{
  s32 value;
  u8 remaining[0xCC];
};

struct VB_800E7A98 { u8 pad[0xC]; };

struct VO_800E7A98 : VB_800E7A98 { virtual ~VO_800E7A98(); };

extern "C" {
extern RecoveredGlobal_8031B170_lbl_804E8880 shinowa_mirage_motion_param_table;
extern const f32 TObjEneMe3ShinowaMirage__data_805DA5C4;
void mem_free(void *p);
extern void *lbl_80500FEC[];
extern void *TObjEneMe3ShinowaMirage__data_805D5298;
extern VO_800E7A98 *TObjEneMe3ShinowaMirage__data_805D52A0;
extern void *TObjEneMe3ShinowaMirage__data_805D52A4;
extern void *TObjEneMe3ShinowaMirage__data_805D52A8;
extern void *TObjEneMe3ShinowaMirage__data_805D52AC;
int create__21TObjEneMe3ShinowaRealFv(void*);

typedef struct RecoveredGlobal_8031B170_lbl_804E8880 RecoveredGlobal_8031B170_lbl_804E8880;
typedef char RecoveredGlobal_8031B170_lbl_804E8880_size[((sizeof(RecoveredGlobal_8031B170_lbl_804E8880)) == 0xD0) ? (1) : (-1)];
void TObjEneMe3ShinowaMirage::set_slot_min_clamped_value(s32 arg0, f32 farg0) {
  u8 *new_var;
  f32 var_f1;
  var_f1 = farg0;
  if (var_f1 < TObjEneMe3ShinowaMirage__data_805DA5C4)
  {
    var_f1 = TObjEneMe3ShinowaMirage__data_805DA5C4;
  }
  new_var = (u8 *)&shinowa_mirage_motion_param_table.value;
  new_var = new_var + (arg0 * 0x10);
  *((f32 *) (((s8 *) new_var) + 8)) = var_f1;
}

void TObjEneMe3ShinowaMirage::free_shared_resources() {
    if (TObjEneMe3ShinowaMirage__data_805D52A8 != 0) {
        delete (SampledMotionPoints *)TObjEneMe3ShinowaMirage__data_805D52A8;
        TObjEneMe3ShinowaMirage__data_805D52A8 = 0;
    }
    if (TObjEneMe3ShinowaMirage__data_805D52A4 != 0) {
        delete (SampledMotionPoints *)TObjEneMe3ShinowaMirage__data_805D52A4;
        TObjEneMe3ShinowaMirage__data_805D52A4 = 0;
    }
    if (TObjEneMe3ShinowaMirage__data_805D52AC != 0) {
        delete (SampledMotionPoints *)TObjEneMe3ShinowaMirage__data_805D52AC;
        TObjEneMe3ShinowaMirage__data_805D52AC = 0;
    }
    if (TObjEneMe3ShinowaMirage__data_805D52A0 != 0) {
        delete TObjEneMe3ShinowaMirage__data_805D52A0;
        TObjEneMe3ShinowaMirage__data_805D52A0 = 0;
    }
    if (lbl_80500FEC[0] != 0) {
        mem_free(lbl_80500FEC[0]);
        lbl_80500FEC[0] = 0;
    }
    if (TObjEneMe3ShinowaMirage__data_805D5298 != 0) {
        delete (BmlResource *)(TObjEneMe3ShinowaMirage__data_805D5298);
        TObjEneMe3ShinowaMirage__data_805D5298 = 0;
    }
}

int TObjEneMe3ShinowaMirage__sub_800E7B74(void* p) { return create__21TObjEneMe3ShinowaRealFv(p); }

}
