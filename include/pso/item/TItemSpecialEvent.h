#ifndef PSO_ITEM_TITEMSPECIALEVENT_H
#define PSO_ITEM_TITEMSPECIALEVENT_H
#include "types.h"
#include <stddef.h>
#include "pso/item/TItemObject.h"

// Tool group 20 (item data byte 1): Chocolate, Candy, Cake, the seven event
// badges, Bouquet and Decoction. ItemPMT type 20 records point at text IDs
// 0x78-0x84 (skipping 0x7B). The executable has no class-name string or vtable
// RTTI for this class; TItemSpecialEvent is an explicit inferred name for the
// special-event item group, not a recovered symbol. See
// docs/evidence/titem-special-event-group-evidence.md.
class TItemSpecialEvent : public TItemObject {
public:
    TItemSpecialEvent(TObject *parent, u8 *item);
    // Declared first: its TU (0x803531FC) emits the vtable, not the files
    // holding the destructor and constructor.
    virtual void apply_use_effect();
    virtual ~TItemSpecialEvent();
    static TItemSpecialEvent *create(u8 *item);

    // Use-effect steps selected by technique index. Each one reads TItem's
    // typed owner pointer (TItem::owner at +0xF0, asserted below), never a
    // raw offset. The original object emitted them in the ending-picture
    // unit, so the definitions stay in TEndingPic.cpp.
    // send_obj_position_event keeps the name already used for 0x80353018.
    // The other steps stay sub_<addr>: set_phase_18, update_player_object,
    // and update_shield had no executable name evidence.
    void send_obj_position_event(s32 arg1);
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
