#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/TObjEneMe3SinowZoa.h"

struct RecoveredGlobal_8031B170_lbl_804E8880
{
  s32 value;
  u8 remaining[0xCC];
};

struct Base_8031B198 { u8 pad[0xC]; };

struct Obj_8031B198 : Base_8031B198 {
    virtual ~Obj_8031B198();
};

struct G_8031B198 { u32 p; u32 rest[3]; };

extern "C" {
extern RecoveredGlobal_8031B170_lbl_804E8880 lbl_804E8880;
extern const f32 lbl_805DF38C;
void mem_free(void *p);
extern G_8031B198 lbl_80542FDC;
extern u32 TObjEneMe3SinowZoa__data_805D6AD8;
extern Obj_8031B198 *TObjEneMe3SinowZoa__data_805D6AE0;
typedef struct RecoveredGlobal_8031B170_lbl_804E8880 RecoveredGlobal_8031B170_lbl_804E8880;
typedef char RecoveredGlobal_8031B170_lbl_804E8880_size[((sizeof(RecoveredGlobal_8031B170_lbl_804E8880)) == 0xD0) ? (1) : (-1)];
void TObjEneMe3SinowZoa::set_entry_value_clamped(s32 arg0, f32 farg0) {
  u8 *new_var;
  f32 var_f1;
  var_f1 = farg0;
  if (var_f1 < lbl_805DF38C)
  {
    var_f1 = lbl_805DF38C;
  }
  new_var = (u8 *)&lbl_804E8880.value;
  new_var = new_var + (arg0 * 0x10);
  *((f32 *) (((s8 *) new_var) + 8)) = var_f1;
}
void TObjEneMe3SinowZoa::free_resources() {
    if (TObjEneMe3SinowZoa__data_805D6AE0 != NULL) {
        delete TObjEneMe3SinowZoa__data_805D6AE0;
        TObjEneMe3SinowZoa__data_805D6AE0 = NULL;
    }
    if (lbl_80542FDC.p != 0) {
        mem_free((void *)lbl_80542FDC.p);
        lbl_80542FDC.p = 0;
    }
    if (TObjEneMe3SinowZoa__data_805D6AD8 != 0) {
        delete (BmlResource *)(TObjEneMe3SinowZoa__data_805D6AD8);
        TObjEneMe3SinowZoa__data_805D6AD8 = 0;
    }
}

}
