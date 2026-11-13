#ifndef PSO_ITEM_TITEMSPECIALEVENT_H
#define PSO_ITEM_TITEMSPECIALEVENT_H
#include "types.h"
#include "pso/item/TItemObject.h"

class TItemSpecialEvent : public TItemObject {
public:
    TItemSpecialEvent(TObject *parent, u8 *item);
    // Declared first: apply_use_effect is the key function, so its TU emits the vtable.
    virtual void apply_use_effect();
    virtual ~TItemSpecialEvent();
    static TItemSpecialEvent *create(u8 *item);

    void send_obj_position_event(s32 kind);
    // The use effects of techniques 8 down to 0 (apply_use_effect's table).
    void set_phase_18();
    void fn_803530A0();
    void update_player_object();
    void fn_80353110();
    void fn_80353134();
    void update_shield();
    void fn_80353194();
    void fn_803531D0();
    void fn_803531F8();
};

#endif
