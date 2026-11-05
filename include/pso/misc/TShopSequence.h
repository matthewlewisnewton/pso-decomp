#ifndef PSO_MISC_TSHOPSEQUENCE_H
#define PSO_MISC_TSHOPSEQUENCE_H

#include "types.h"
#include "pso/TShopWindowBase.h"

struct TShopSequence : public TShopWindowBase {
    virtual ~TShopSequence();
    virtual void restore_player_state();
    virtual void close_window();
    bool sub_802239EC();
    s32 get_child_field1c();
    u32 create_message_window(s32, s32);
    void close_message_window();
    virtual void vfunc_6();
    virtual void vfunc_7();
    virtual void vfunc_8();
    virtual void vfunc_9();
    virtual int vfunc_10();
    static void close_if_single_screen();
};

#endif
