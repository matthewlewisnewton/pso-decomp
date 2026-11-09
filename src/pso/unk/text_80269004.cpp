#include "pso/misc/WindowConstructorAbi.h"
#include "types.h"
struct Obj_80269004 { u8 p0[0x18]; void *f18; };

extern "C" {
void TWindowMenuInfomation__ct(u8 *arg0, u32 arg1);
extern u8 choice_setting_popup_window_descriptor[];
extern u8 choice_setting_popup_vtable[];
Obj_80269004 *fn_80269004(Obj_80269004 *self, void *parent, void *arg2);
Obj_80269004 *fn_80269004(Obj_80269004 *self, void *parent, void *arg2) {
    __ct__15TWindowAdditionFPUcsPUc((TWindowAddition *)(self), (u8 *)(choice_setting_popup_window_descriptor), (s16)(4), (u8 *)(parent));
    self->f18 = choice_setting_popup_vtable;
    TWindowMenuInfomation__ct((u8 *)self, (u32)arg2);
    return self;
}

}
