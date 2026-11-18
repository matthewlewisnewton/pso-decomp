#ifndef PSO_ITEM_TITEMSPECIALEVENT_H
#define PSO_ITEM_TITEMSPECIALEVENT_H
#include <stddef.h>
#include "types.h"
#include "pso/item/TItemObject.h"

// Inferred from item tool factory slot 20, used for event badges, Candy and Cake.
class TItemSpecialEvent : public TItemObject {
public:
    TItemSpecialEvent(TObject *parent, u8 *item);
    // Declared first: apply_use_effect is the key function, so its TU emits the vtable.
    virtual void apply_use_effect();
    virtual ~TItemSpecialEvent();
    static TItemSpecialEvent *create(u8 *item);

    void send_obj_position_event(s32 kind);
    // The use effects of techniques 8 down to 0 (apply_use_effect's table).
    void sub_8035307C();
    void sub_803530A0();
    void sub_803530C4();
    void sub_80353110();
    void sub_80353134();
    void sub_80353158();
    void sub_80353194();
    void sub_803531D0();
    void sub_803531F8();
};

typedef char TItemSpecialEventOwnerOffset[(offsetof(TItemSpecialEvent, owner) == 0xF0) ? 1 : -1];

#endif
